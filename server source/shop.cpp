Search:
		char name[36];
		snprintf(name, sizeof(name), "%-20s(#%-5d) (x %d)", item_table->szName, (int) item.vnum, item.count);

		sys_log(0, "SHOP_ITEM: %-36s PRICE %-5d", name, item.price);

Add in under:
		if (IsPCShop())
			InsertInMysql(m_pkPC, pkItem, iPos, item.price);


---

Search:
		snprintf(buf, sizeof(buf), "%s %u(%s) %u %u", item->GetName(), ch->GetPlayerID(), ch->GetName(), dwPrice, item->GetCount());
		LogManager::instance().ItemLog(m_pkPC, item, "SHOP_SELL", buf);

Add in under:
		RemoveFromMysql(m_pkPC->GetPlayerID(), pos);


---

Search:
int CShop::Buy(LPCHARACTER ch, BYTE pos)
{
	[...]

	if (item)
		sys_log(0, "SHOP: BUY: name %s %s(x %d):%u price %u", ch->GetName(), item->GetName(), item->GetCount(), item->GetID(), dwPrice);

    ch->Save();

    return (SHOP_SUBHEADER_GC_OK);
}

Add in under:
int CShop::BuyFromGlass(LPCHARACTER ch_seller, LPCHARACTER ch_buyer, BYTE pos)
{
	if (pos >= m_itemVector.size())
	{
		sys_log(0, "Shop::BuyFromGlass : Invalid position %d - Seller: %s , Buyer: %s", pos, ch_seller->GetName(), ch_buyer->GetName());
		return SHOP_SUBHEADER_GC_INVALID_POS;
	}

	if (m_pkPC != ch_seller)
	{
		sys_log(0, "Wrong shop owner");
		return SHOP_SUBHEADER_GC_SOLD_OUT;
	}

	sys_log(0, "Shop::BuyFromGlass : Buy event: Seller %s Buyer %s pos %d", ch_seller->GetName(), ch_buyer->GetName(), pos);


	SHOP_ITEM& r_item = m_itemVector[pos];
	if (r_item.price < 0)
	{
		LogManager::instance().HackLog("SHOP_BUY_GOLD_OVERFLOW", ch_buyer);
		return SHOP_SUBHEADER_GC_NOT_ENOUGH_MONEY;
	}


	LPITEM pkSelectedItem = ITEM_MANAGER::instance().Find(r_item.itemid);
	if (!pkSelectedItem)
	{
		sys_log(0, "Shop::BuyFromGlass : Critical: This user seems to be a hacker : invalid pcshop item : BuyerPID:%u SellerPID:%u",
			ch_buyer->GetPlayerID(),
			ch_seller->GetPlayerID());

		return SHOP_SUBHEADER_GC_SOLD_OUT;
	}

	if ((pkSelectedItem->GetOwner() != m_pkPC))
	{
		sys_log(0, "Shop::BuyFromGlass : Critical: This user seems to be a hacker : invalid pcshop owner : BuyerPID:%u SellerPID:%u",
			ch_buyer->GetPlayerID(),
			ch_seller->GetPlayerID());

		return SHOP_SUBHEADER_GC_SOLD_OUT;
	}

	if ((pkSelectedItem->GetOwner() != ch_seller))
	{
		sys_log(0, "Shop::BuyFromGlass : Critical: This user seems to be a hacker : invalid pcshop owner2 : BuyerPID:%u SellerPID:%u",
			ch_buyer->GetPlayerID(),
			ch_seller->GetPlayerID());

		return SHOP_SUBHEADER_GC_SOLD_OUT;
	}


	DWORD dwPrice = r_item.price;
	if (ch_buyer->GetGold() < (int)dwPrice)
	{
		sys_log(1, "Shop::BuyFromGlass : Not enough money : %s has %d, price %d", ch_buyer->GetName(), ch_buyer->GetGold(), dwPrice);
		return SHOP_SUBHEADER_GC_NOT_ENOUGH_MONEY;
	}

	LPITEM item = r_item.pkItem;
	if (!item)
	{
		sys_log(1, "Shop::BuyFromGlass : Item not found Seller: %s Buyer: %s", ch_seller->GetName(), ch_buyer->GetName());
		return SHOP_SUBHEADER_GC_SOLD_OUT;
	}


	int iEmptyPos;
	if (item->IsDragonSoul())
		iEmptyPos = ch_buyer->GetEmptyDragonSoulInventory(item);
	else
		iEmptyPos = ch_buyer->GetEmptyInventory(item->GetSize());


	if (iEmptyPos < 0)
	{
		sys_log(1, "Shop::BuyFromGlass at PC Shop : Inventory full - Seller: %s Buyer: %s size %d", ch_seller->GetName(), ch_buyer->GetName(), item->GetSize());
		return SHOP_SUBHEADER_GC_INVENTORY_FULL;
	}

	ch_buyer->PointChange(POINT_GOLD, -dwPrice, false);



	ch_seller->SyncQuickslot(QUICKSLOT_TYPE_ITEM, item->GetCell(), 255);

	char buf[512];

	if (item->GetVnum() >= 80003 && item->GetVnum() <= 80007)
	{
		snprintf(buf, sizeof(buf), "%s FROM: %u TO: %u PRICE: %u", item->GetName(), ch_buyer->GetPlayerID(), ch_seller->GetPlayerID(), dwPrice);
		LogManager::instance().GoldBarLog(ch_buyer->GetPlayerID(), item->GetID(), SHOP_BUY, buf);
		LogManager::instance().GoldBarLog(ch_seller->GetPlayerID(), item->GetID(), SHOP_SELL, buf);
	}


	item->RemoveFromCharacter();
	if (item->IsDragonSoul())
		item->AddToCharacter(ch_buyer, TItemPos(DRAGON_SOUL_INVENTORY, iEmptyPos));
	else
		item->AddToCharacter(ch_buyer, TItemPos(INVENTORY, iEmptyPos));
	ITEM_MANAGER::instance().FlushDelayedSave(item);


	snprintf(buf, sizeof(buf), "%s %u(%s) %u %u", item->GetName(), ch_seller->GetPlayerID(), ch_seller->GetName(), dwPrice, item->GetCount());
	LogManager::instance().ItemLog(ch_buyer, item, "SHOP_BUY_GLASS", buf);

	snprintf(buf, sizeof(buf), "%s %u(%s) %u %u", item->GetName(), ch_buyer->GetPlayerID(), ch_buyer->GetName(), dwPrice, item->GetCount());
	LogManager::instance().ItemLog(ch_seller, item, "SHOP_SELL_GLASS", buf);

	RemoveFromMysql(ch_seller->GetPlayerID(), pos);

	r_item.pkItem = NULL;
	BroadcastUpdateItem(pos);

	ch_buyer->ChatPacket(CHAT_TYPE_COMMAND, "RemoveItemFromList %s %d", ch_seller->GetName(), pos);
	m_pkPC->PointChange(POINT_GOLD, dwPrice, false);

	if (item)
		sys_log(0, "SHOP BuyFromGlass: BUY: name %s %s(x %d):%u price %u", ch_buyer->GetName(), item->GetName(), item->GetCount(), item->GetID(), dwPrice);

	ch_buyer->Save();

	return (SHOP_SUBHEADER_GC_OK);
}

void CShop::InsertInMysql(LPCHARACTER lpSeller, LPITEM item, BYTE bPos, DWORD dwItemPrice)
{
	if (!lpSeller){ sys_err("Empty SELLER !"); return; }
	if (!item){ sys_err("Empty ITEM !"); return; }

	long socket1; long socket2; long socket3;
	socket1 = item->GetSocket(0); socket2 = item->GetSocket(1); socket3 = item->GetSocket(2);

	BYTE attr1type; BYTE attr2type; BYTE attr3type; BYTE attr4type; BYTE attr5type; BYTE attr6type; BYTE attr7type;
	attr1type = item->GetAttributeType(0); attr2type = item->GetAttributeType(1); attr3type = item->GetAttributeType(2);
	attr4type = item->GetAttributeType(3); attr5type = item->GetAttributeType(4); attr6type = item->GetAttributeType(5);
	attr7type = item->GetAttributeType(6);

	int attr1value; int attr2value; int attr3value; int attr4value; int attr5value; int attr6value; int attr7value;
	attr1value = item->GetAttributeValue(0); attr2value = item->GetAttributeValue(1); attr3value = item->GetAttributeValue(2);
	attr4value = item->GetAttributeValue(3); attr5value = item->GetAttributeValue(4); attr6value = item->GetAttributeValue(5);
	attr7value = item->GetAttributeValue(6);

	const char* c_szSellerName = lpSeller->GetName(); DWORD dwSellerPID = lpSeller->GetPlayerID();

	DWORD dwItemVnum = item->GetVnum(); const char* c_szItemName = item->GetName(); DWORD dwItemCount = item->GetCount();
	int iItemRefine = item->GetRefineLevel(); int iItemLevel; int iItemType = item->GetType();
	int iItemSubtype = item->GetSubType(); DWORD iItemAntiflag = item->GetAntiFlag();

	if (item->GetLimitType(0))
		iItemLevel = item->GetLimitValue(0);
	else
		iItemLevel = 0;

	std::auto_ptr<SQLMsg> pmsg(DBManager::instance().DirectQuery(
		"INSERT INTO shop_onsales_items%s(seller_pid, seller_name, item_name, item_vnum, item_count, item_refine, item_price, item_level, item_pos, item_type, item_subtype, item_antiflag, socket0, socket1, socket2, attrtype0, attrvalue0, attrtype1, attrvalue1, attrtype2, attrvalue2, attrtype3, attrvalue3, attrtype4, attrvalue4, attrtype5, attrvalue5, attrtype6, attrvalue6) "
		"VALUES('%u', '%s', '%s', %u, %u, %d, %u, %d, %d, %d, %d, %u, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d)",
		get_table_postfix(), dwSellerPID, c_szSellerName, c_szItemName, dwItemVnum, dwItemCount, iItemRefine, dwItemPrice, iItemLevel, bPos, iItemType, iItemSubtype, iItemAntiflag, socket1, socket2, socket3, attr1type, attr1value, attr2type, attr2value, attr3type, attr3value, attr4type, attr4value, attr5type, attr5value, attr6type, attr6value, attr7type, attr7value
	));

	if (pmsg->uiSQLErrno != 0) {
		sys_err("Shop Item Insert Query Failed, Error code: %ld", pmsg->uiSQLErrno);
		return;
	}
}

void CShop::RemoveFromMysql(DWORD dwSellerPID, BYTE bPos){
	std::auto_ptr<SQLMsg> pmsg(DBManager::instance().DirectQuery("DELETE FROM shop_onsales_items WHERE item_pos='%d' AND seller_pid='%u'", bPos, dwSellerPID));

	if (pmsg->uiSQLErrno != 0) {
		sys_err("Shop Item Remove Query Failed, Error code: %ld", pmsg->uiSQLErrno);
		return;
	}
}
