Search:
	if (speed_server)
		CSpeedServerManager::instance().Initialize();

Add in under:
	DBManager::Instance().DirectQuery("TRUNCATE player.shop_onsales_items");
