Search:
int CInputMain::Shop(LPCHARACTER ch, const char * data, size_t uiBytes)
{
	[...]

		case SHOP_SUBHEADER_CG_SELL2:
			{
				if (uiBytes < sizeof(BYTE) + sizeof(BYTE))
					return -1;

				BYTE pos = *(c_pData++);
				BYTE count = *(c_pData);

				sys_log(0, "INPUT: %s SHOP: SELL2", ch->GetName());
				CShopManager::instance().Sell(ch, pos, count);
				return sizeof(BYTE) + sizeof(BYTE);
			}

		default:
			sys_err("CInputMain::Shop : Unknown subheader %d : %s", p->subheader, ch->GetName());
			break;
	}

	return 0;
}

Add in under:
void CInputMain::Shop2(LPCHARACTER ch, const char * data)
{
	struct command_shop2 * p = (struct command_shop2 *) data;
	int shop2_subheader = (int)p->subheader;

	if (!ch){
		sys_err("TPacketCGShop2 packet coming from unknown target");
		return;
	}

	if (test_server)
		sys_log(0, "CInputMain::Shop2() ==> SubHeader %d", shop2_subheader);


	int iFloodResult = ch->GetQuestFlag("item_search.flood_check");
	if (iFloodResult){
		if (get_global_time() < iFloodResult + 5 /* limit */) {
			ch->ChatPacket(CHAT_TYPE_INFO, "You can not use too fast");
			return;
		}
	}


	if (shop2_subheader == SHOP2_SUBHEADER_CG_SEARCH)
	{
		if (!p->iType && !p->iSubtype){
			sys_err("TPacketCGShop2: SHOP2_SUBHEADER_CG_SEARCH  USER: %s -- HAVE A EMPTY ARGUMENT", ch->GetName());
			return;
		}

		sys_log(0, "TPacketCGShop2: SHOP2_SUBHEADER_CG_SEARCH  USER: %s", ch->GetName());


		if (quest::CQuestManager::instance().GetPCForce(ch->GetPlayerID())->IsRunning())
		{
			ch->ChatPacket(CHAT_TYPE_INFO, "You can not use this in now");
			return;
		}


		char szQuery[1024];
		if (p->iType == 99) {
			sprintf(szQuery,
			"SELECT * FROM shop_onsales_items \
			WHERE item_type=5 OR item_type=6 OR item_type=7 OR item_type=8 OR item_type=9 OR item_type=11 \
			OR item_type=15 OR item_type=19 OR item_type=21 OR item_type=25 OR item_type=26 OR item_type=27 \
			OR item_type=30 OR item_type=31 OR item_type=32 OR item_type=33 OR item_type=36 OR item_type > 36 \
			AND item_level >= %d AND item_level <= %d \
			AND item_refine >= %d AND item_refine <= %d AND item_price >= %d AND item_price <= %d \
			ORDER BY item_price ASC LIMIT 120",
			p->iMinLevel, p->iMaxLevel,
			p->iMinRefine, p->iMaxRefine, p->iMinPrice, p->iMaxPrice);
		}
		if (p->iSubtype == 99) {
			sprintf(szQuery,
			"SELECT * FROM shop_onsales_items \
			WHERE item_type=%d AND item_level >= %d AND item_level <= %d \
			AND item_refine >= %d AND item_refine <= %d AND item_price >= %d AND item_price <= %d \
			ORDER BY item_price ASC LIMIT 120",
			p->iType, p->iMinLevel, p->iMaxLevel,
			p->iMinRefine, p->iMaxRefine, p->iMinPrice, p->iMaxPrice);
		}
		else if (p->iType == 12) {
			sprintf(szQuery,
			"SELECT * FROM shop_onsales_items \
			WHERE item_type=%d OR item_type=%d AND item_subtype=%d AND item_level >= %d AND item_level <= %d \
			AND item_refine >= %d AND item_refine <= %d AND item_price >= %d AND item_price <= %d \
			ORDER BY item_price ASC LIMIT 120",
			12, 6, p->iSubtype, p->iMinLevel, p->iMaxLevel,
			p->iMinRefine, p->iMaxRefine, p->iMinPrice, p->iMaxPrice);
		}
		else{
			sprintf(szQuery,
			"SELECT * FROM shop_onsales_items \
			WHERE item_type=%d AND item_subtype=%d AND item_level >= %d AND item_level <= %d \
			AND item_refine >= %d AND item_refine <= %d AND item_price >= %d AND item_price <= %d \
			ORDER BY item_price ASC LIMIT 120",
			p->iType, p->iSubtype, p->iMinLevel, p->iMaxLevel,
			p->iMinRefine, p->iMaxRefine, p->iMinPrice, p->iMaxPrice);
		}
		std::auto_ptr<SQLMsg> pSearchQuery(DBManager::instance().DirectQuery(szQuery));


		if (pSearchQuery->uiSQLErrno != 0) {
			sys_err("Item Search Query Failed, Error code: %ld", pSearchQuery->uiSQLErrno);
			return;
		}
		if (!pSearchQuery->Get()->uiNumRows){
			ch->ChatPacket(CHAT_TYPE_INFO, "Search failed. Doesn't found result.");
			sys_err("Item Search Query Failed, Rows couldn't get");
			return;
		}

		int i_x = 0;
		while (MYSQL_ROW row1 = mysql_fetch_row(pSearchQuery->Get()->pSQLResult))
		{
			const char * c_szSellerName = row1[1]; const char * c_szItemName = row1[2]; const char * c_szItemVnum = row1[3];
			const char * c_szItemCount = row1[4]; const char * c_szItemRefine = row1[5]; const char * c_szItemPrice = row1[6];
			const char * c_szItemLevel = row1[7]; const char * c_szItemPos = row1[8];

			const char * c_szSocket0 = row1[12]; const char * c_szSocket1 = row1[13]; const char * c_szSocket2 = row1[14];

			const char * c_szAttrType1 = row1[15]; const char * c_szAttrValue1 = row1[16]; const char * c_szAttrType2 = row1[17];
			const char * c_szAttrValue2 = row1[18]; const char * c_szAttrType3 = row1[19]; const char * c_szAttrValue3 = row1[20];
			const char * c_szAttrType4 = row1[21]; const char * c_szAttrValue4 = row1[22]; const char * c_szAttrType5 = row1[23];
			const char * c_szAttrValue5 = row1[24]; const char * c_szAttrType6 = row1[25]; const char * c_szAttrValue6 = row1[26];
			const char * c_szAttrType7 = row1[27]; const char * c_szAttrValue7 = row1[28];

			const char * c_szApplyType1 = row1[29]; const char * c_szApplyValue1 = row1[30]; const char * c_szApplyType2 = row1[31];
			const char * c_szApplyValue2 = row1[32]; const char * c_szApplyType3 = row1[33]; const char * c_szApplyValue3 = row1[34];
			const char * c_szApplyType4 = row1[35]; const char * c_szApplyValue4 = row1[36]; const char * c_szApplyType5 = row1[37];
			const char * c_szApplyValue5 = row1[38]; const char * c_szApplyType6 = row1[39]; const char * c_szApplyValue6 = row1[40];
			const char * c_szApplyType7 = row1[41]; const char * c_szApplyValue7 = row1[42]; const char * c_szApplyType8 = row1[43];
			const char * c_szApplyValue8 = row1[44];

			const char* c_szItemNameForSearch = p->cItemNameForSearch;
			DWORD dwVnumFromTable = 0;
			str_to_number(dwVnumFromTable, c_szItemVnum);

			TItemTable* table = ITEM_MANAGER::instance().GetTable(dwVnumFromTable);
			if (p->iType == 1 || p->iType == 2)
			{
				if (table && p->iJob == 0 && (table->dwAntiFlags & ITEM_ANTIFLAG_ASSASSIN && table->dwAntiFlags & ITEM_ANTIFLAG_SHAMAN && table->dwAntiFlags & ITEM_ANTIFLAG_SURA) ||
					table && p->iJob == 1 && (table->dwAntiFlags & ITEM_ANTIFLAG_WARRIOR  && table->dwAntiFlags & ITEM_ANTIFLAG_SHAMAN && table->dwAntiFlags & ITEM_ANTIFLAG_SURA) ||
					table && p->iJob == 2 && (table->dwAntiFlags & ITEM_ANTIFLAG_ASSASSIN && table->dwAntiFlags & ITEM_ANTIFLAG_SHAMAN && table->dwAntiFlags & ITEM_ANTIFLAG_WARRIOR) ||
					table && p->iJob == 3 && (table->dwAntiFlags & ITEM_ANTIFLAG_ASSASSIN && table->dwAntiFlags & ITEM_ANTIFLAG_WARRIOR && table->dwAntiFlags & ITEM_ANTIFLAG_SURA))
				{
					if (strlen(p->cItemNameForSearch) && strstr(c_szItemName, c_szItemNameForSearch)){
						if (ch)
						{
							ch->ChatPacket(CHAT_TYPE_COMMAND,
								"GetSearchedItemData %d %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s",

								i_x, c_szSellerName, c_szItemVnum, c_szItemCount, c_szItemRefine, c_szItemPrice, c_szItemLevel,

								c_szSocket0, c_szSocket1, c_szSocket2,

								c_szAttrType1, c_szAttrValue1, c_szAttrType2, c_szAttrValue2, c_szAttrType3, c_szAttrValue3,
								c_szAttrType4, c_szAttrValue4, c_szAttrType5, c_szAttrValue5, c_szAttrType6, c_szAttrValue6,
								c_szAttrType7, c_szAttrValue7,

								c_szApplyType1, c_szApplyValue1, c_szApplyType2, c_szApplyValue2, c_szApplyType3, c_szApplyValue3,
								c_szApplyType4, c_szApplyValue4, c_szApplyType5, c_szApplyValue5, c_szApplyType6, c_szApplyValue6,
								c_szApplyType7, c_szApplyValue8,

								c_szItemPos
								);
						}
					}
				}
			}
			else{
				if (ch)
				{
					ch->ChatPacket(CHAT_TYPE_COMMAND,
						"GetSearchedItemData %d %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s",

						i_x, c_szSellerName, c_szItemVnum, c_szItemCount, c_szItemRefine, c_szItemPrice, c_szItemLevel,

						c_szSocket0, c_szSocket1, c_szSocket2,

						c_szAttrType1, c_szAttrValue1, c_szAttrType2, c_szAttrValue2, c_szAttrType3, c_szAttrValue3,
						c_szAttrType4, c_szAttrValue4, c_szAttrType5, c_szAttrValue5, c_szAttrType6, c_szAttrValue6,
						c_szAttrType7, c_szAttrValue7,

						c_szApplyType1, c_szApplyValue1, c_szApplyType2, c_szApplyValue2, c_szApplyType3, c_szApplyValue3,
						c_szApplyType4, c_szApplyValue4, c_szApplyType5, c_szApplyValue5, c_szApplyType6, c_szApplyValue6,
						c_szApplyType7, c_szApplyValue8,

						c_szItemPos
						);
				}
			}


			++i_x;
		}
		if (ch){
			ch->ChatPacket(CHAT_TYPE_COMMAND, "CreateSearchedItemList");
			ch->SetQuestFlag("item_search.flood_check", get_global_time());
		}

	}
	else if (shop2_subheader == SHOP2_SUBHEADER_CG_BUY)
	{
		if (!strlen(p->cSellerName)){
			sys_err("TPacketCGShop2: SHOP2_SUBHEADER_CG_BUY  USER: %s -- HAVE A EMPTY ARGUMENT", ch->GetName());
			return;
		}

		//if (!isdigit(p->bItemPos)){
		//	sys_err("TPacketCGShop2: SHOP2_SUBHEADER_CG_BUY  USER: %s -- ITEM POS ISN'T NUMBER", ch->GetName());
		//	return;
		//}

		sys_log(0, "TPacketCGShop2: SHOP2_SUBHEADER_CG_BUY  USER: %s POS: %d SELLER: %s", ch->GetName(), p->bItemPos, p->cSellerName);

		LPCHARACTER seller_ch = CHARACTER_MANAGER::instance().FindPC(p->cSellerName);
		if (!seller_ch){
			ch->ChatPacket(CHAT_TYPE_INFO, "%s isn't online or in other channel", p->cSellerName);
			return;
		}
		if (!seller_ch->IsPC() || !seller_ch->GetDesc()){
			ch->ChatPacket(CHAT_TYPE_INFO, "%s isn't PC or isn't active", p->cSellerName);
			return;
		}
		if (seller_ch == ch){
			ch->ChatPacket(CHAT_TYPE_INFO, "You can not buy item from yourself");
			return;
		}
		if (quest::CQuestManager::instance().GetPCForce(ch->GetPlayerID())->IsRunning() ||
			quest::CQuestManager::instance().GetPCForce(seller_ch->GetPlayerID())->IsRunning())
		{
			ch->ChatPacket(CHAT_TYPE_INFO, "You can not use this in now");
			return;
		}

		ch->SetQuestFlag("item_search.flood_check", get_global_time());
		if (p->iBuyType == SHOP2_SEARCHER_TYPE_FIND)
			CShopManager::instance().FindFromGlass(seller_ch, ch);
		else
			CShopManager::instance().BuyFromGlass(seller_ch, ch, p->bItemPos, p->iBuyType);
	}
	else
	{
		sys_err("CInputMain::Shop2 : Unknown subheader '%d' - From: %s", shop2_subheader, ch->GetName());
		return;
	}
}


---


Search:
		case HEADER_CG_SHOP:
			if ((iExtraLen = Shop(ch, c_pData, m_iBufferLeft)) < 0)
				return -1;
			break;

Add in under:
		case HEADER_CG_SHOP2:
			Shop2(ch, c_pData);
			break;
