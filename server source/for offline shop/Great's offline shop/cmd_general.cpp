Search:
		while (it != i.end()) {
			LPCHARACTER pc = *it++;
			if (pc)
				if (pc->GetRaceNum() == 30000 && pc->GetPrivShop() == id) {
					pc->DeleteMyShop();
					return;
				}

Change:
		while (it != i.end()) {
			LPCHARACTER pc = *it++;
			if (pc)
				if (pc->GetRaceNum() == 30000 && pc->GetPrivShop() == id) {
					pc->DeleteMyShop();
					pc->RemoveMyAllItems();
					return;
				}


---

Search:
				for (int ia = 0; ia < 7; ia++)
				{
					const TPlayerItemAttribute& attr = item->GetAttribute(ia);
					sprintf(query, "%s, attrtype%d='%u'", query, ia, attr.bType);
					sprintf(query, "%s, attrvalue%d='%d'", query, ia, attr.sValue);

				}
				DBManager::instance().DirectQuery(query);
				ITEM_MANAGER::Instance().RemoveItem(item, "Priv shop");
Change:
				for (int ia = 0; ia < 7; ia++)
				{
					const TPlayerItemAttribute& attr = item->GetAttribute(ia);
					sprintf(query, "%s, attrtype%d='%u'", query, ia, attr.bType);
					sprintf(query, "%s, attrvalue%d='%d'", query, ia, attr.sValue);

				}
				DBManager::instance().DirectQuery(query);
				ch->InsertInMysql(item, display, price);
				ITEM_MANAGER::Instance().RemoveItem(item, "Priv shop");
