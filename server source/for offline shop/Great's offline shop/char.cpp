Add in the bottom of the page:
void CHARACTER::RemoveFromMysql(BYTE bPos){
	std::auto_ptr<SQLMsg> pmsg(DBManager::instance().DirectQuery("DELETE FROM shop_onsales_items WHERE item_pos='%d' AND seller_pid='%u'", bPos, GetPlayerID()));

	if (pmsg->uiSQLErrno != 0) {
		sys_err("Shop Item Remove Query Failed, Error code: %ld", pmsg->uiSQLErrno);
		return;
	}
}


void CHARACTER::RemoveMyAllItems(){
	std::auto_ptr<SQLMsg> pmsg(DBManager::instance().DirectQuery("DELETE FROM shop_onsales_items WHERE seller_pid='%u'", GetPlayerID()));

	if (pmsg->uiSQLErrno != 0) {
		sys_err("Shop Item Remove All Query Failed, Error code: %ld", pmsg->uiSQLErrno);
		return;
	}

	sys_log(0, "PID: %u - Logout from game and removed all item from mysql", GetPlayerID());
}

void CHARACTER::InsertInMysql(LPITEM item, BYTE bPos, DWORD dwItemPrice)
{
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

	const char* c_szSellerName = GetName(); DWORD dwSellerPID = GetPlayerID();

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
