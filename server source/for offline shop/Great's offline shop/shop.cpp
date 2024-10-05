Add in the bottom of the page:
void CShop::RemoveAllItemsFromMysql(DWORD dwSellerPID){
	std::auto_ptr<SQLMsg> pmsg(DBManager::instance().DirectQuery("DELETE FROM shop_onsales_items WHERE seller_pid='%u'", dwSellerPID));

	if (pmsg->uiSQLErrno != 0) {
		sys_err("Shop Item Remove All Query Failed, Error code: %ld", pmsg->uiSQLErrno);
		return;
	}

	sys_log(0, "PID: %u - Logout from game and removed all item from mysql", dwSellerPID);
}
