Search:
RemoveItem(ch->GetOfflineShopOwner()->GetOfflineShopRealOwner(), bPos);

Add it under:
RemoveFromMysql(ch->GetOfflineShopOwner()->GetOfflineShopRealOwner(), bPos);

---

Search:
DBManager::instance().DirectQuery("DELETE FROM player.offline_shop_npc WHERE owner_id = %u", npc->GetOfflineShopRealOwner());

Add it under:
RemoveAllItemsFromMysql(npc->GetOfflineShopRealOwner());


---

Add in the bottom of the page:

void COfflineShop::RemoveAllItemsFromMysql(DWORD dwSellerPID){
	std::auto_ptr<SQLMsg> pmsg(DBManager::instance().DirectQuery("DELETE FROM shop_onsales_items WHERE seller_pid='%u'", dwSellerPID));

	if (pmsg->uiSQLErrno != 0) {
		sys_err("Shop Item Remove All Query Failed, Error code: %ld", pmsg->uiSQLErrno);
		return;
	}

	sys_log(0, "PID: %u - Logout from game and removed all item from mysql", dwSellerPID);
}

void COfflineShop::RemoveFromMysql(DWORD dwSellerPID, BYTE bPos){
	std::auto_ptr<SQLMsg> pmsg(DBManager::instance().DirectQuery("DELETE FROM shop_onsales_items WHERE item_pos='%d' AND seller_pid='%u'", bPos, dwSellerPID));

	if (pmsg->uiSQLErrno != 0) {
		sys_err("Shop Item Remove Query Failed, Error code: %ld", pmsg->uiSQLErrno);
		return;
	}
}
