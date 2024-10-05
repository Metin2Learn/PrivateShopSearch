Search:
	CTargetManager::instance().Logout(GetPlayerID());

	MessengerManager::instance().Logout(GetName());

Add in under:
	CShopManager::instance().RemoveAllItemsFromMysql(GetPlayerID());


---

Search:
void CHARACTER::CloseMyShop()
{
	if (GetMyShop())
	{
		m_stShopSign.clear();
		CShopManager::instance().DestroyPCShop(this);
		m_pkMyShop = NULL;

Add in under:
		CShopManager::instance().RemoveAllItemsFromMysql(GetPlayerID());
