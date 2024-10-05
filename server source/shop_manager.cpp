Search:
void CShopManager::Buy(LPCHARACTER ch, BYTE pos)
{
	[...]

	if (SHOP_SUBHEADER_GC_OK != ret) // ¹®Á¦°¡ ÀÖ¾úÀ¸¸é º¸³½´Ù.
	{
		TPacketGCShop pack;

		pack.header	= HEADER_GC_SHOP;
		pack.subheader	= ret;
		pack.size	= sizeof(TPacketGCShop);

		ch->GetDesc()->Packet(&pack, sizeof(pack));
	}
}

Add in under:
void CShopManager::BuyFromGlass(LPCHARACTER ch_seller, LPCHARACTER ch_buyer, BYTE pos, int iBuyType)
{
	if (!ch_seller || !ch_buyer){
		sys_err("Seller Or Buyer character pointer is NULL !");
		return;
	}
	if (!ch_seller->GetDesc() || !ch_buyer->GetDesc()){
		sys_err("Seller Or Buyer desc is NULL !");
		return;
	}
	if (!ch_seller->IsPC() || !ch_buyer->IsPC()){
		sys_err("Seller Or Buyer isn't PC !");
		return;
	}



	if (ch_buyer->GetShop() || ch_buyer->GetShopOwner()){
		sys_err("Close opened shop and npc's and try again");
		return;
	}

	if (ch_buyer->GetMyShop()){
		ch_buyer->ChatPacket(CHAT_TYPE_INFO, "You can not buy item when your shop is active");
		return;
	}
	if (!ch_seller->GetMyShop()){
		ch_buyer->ChatPacket(CHAT_TYPE_INFO, "%s isn't shop owner", ch_seller->GetName());
		return;
	}

	CShop* pkShop = ch_seller->GetMyShop();
	if (!pkShop){
		ch_buyer->ChatPacket(CHAT_TYPE_INFO, "Seller shop isn't founded");
		return;
	}

	if (!pkShop->IsPCShop())
	{
		ch_buyer->ChatPacket(CHAT_TYPE_INFO, "Seller shop isn't pc shop");
		return;
	}

	if (iBuyType == SHOP2_SEARCHER_TYPE_BUY)
	{
		if (ch_buyer->GetMapIndex() != ch_seller->GetMapIndex()){
			ch_buyer->ChatPacket(CHAT_TYPE_INFO, "You are isn't same map with seller");
			return;
		}

		if (!ch_buyer->CountSpecifyItem(60005)){
			ch_buyer->ChatPacket(CHAT_TYPE_INFO, "You don't have trading glass");
			return;
		}
	}

	if (iBuyType == SHOP2_SEARCHER_TYPE_BUY_PREMIUM)
	{
		if (!ch_buyer->CountSpecifyItem(60006)){
			ch_buyer->ChatPacket(CHAT_TYPE_INFO, "You don't have trading glass+");
			return;
		}
	}

	//PREVENT_ITEM_COPY
	ch_buyer->SetMyShopTime();
	//END_PREVENT_ITEM_COPY

	int ret = pkShop->BuyFromGlass(ch_seller, ch_buyer, pos);

	if (SHOP_SUBHEADER_GC_OK != ret) // ¹®Á¦°¡ ÀÖ¾úÀ¸¸é º¸³½´Ù.
	{
		TPacketGCShop pack;

		pack.header = HEADER_GC_SHOP;
		pack.subheader = ret;
		pack.size = sizeof(TPacketGCShop);

		ch_buyer->GetDesc()->Packet(&pack, sizeof(pack));
	}
}

#include "target.h"
void CShopManager::FindFromGlass(LPCHARACTER ch_seller, LPCHARACTER ch_buyer)
{
	if (!ch_seller || !ch_buyer){
		sys_err("Seller Or Buyer character pointer is NULL !");
		return;
	}
	if (!ch_seller->GetDesc() || !ch_buyer->GetDesc()){
		sys_err("Seller Or Buyer desc is NULL !");
		return;
	}
	if (!ch_seller->IsPC() || !ch_buyer->IsPC()){
		sys_err("Seller Or Buyer isn't PC !");
		return;
	}



	if (ch_buyer->GetShop() || ch_buyer->GetShopOwner()){
		sys_err("Close opened shop and npc's and try again");
		return;
	}

	if (ch_buyer->GetMyShop()){
		ch_buyer->ChatPacket(CHAT_TYPE_INFO, "You can not buy item when your shop is active");
		return;
	}
	if (!ch_seller->GetMyShop()){
		ch_buyer->ChatPacket(CHAT_TYPE_INFO, "%s isn't shop owner", ch_seller->GetName());
		return;
	}

	CShop* pkShop = ch_seller->GetMyShop();
	if (!pkShop){
		ch_buyer->ChatPacket(CHAT_TYPE_INFO, "Seller shop isn't founded");
		return;
	}

	if (!pkShop->IsPCShop())
	{
		ch_buyer->ChatPacket(CHAT_TYPE_INFO, "Seller shop isn't pc shop");
		return;
	}

	//PREVENT_ITEM_COPY
	ch_buyer->SetMyShopTime();
	//END_PREVENT_ITEM_COPY


	TargetInfo * pInfo_check = CTargetManager::instance().GetTargetInfo(ch_buyer->GetPlayerID(), TARGET_TYPE_VID, ch_seller->GetVID());
	if (pInfo_check) {
		ch_buyer->ChatPacket(CHAT_TYPE_INFO, "This seller already targeted");
		return;
	}

	CTargetManager::Instance().CreateTarget(ch_buyer->GetPlayerID() /* dwPID */, 3169 /*dwQuestIndex*/, "SHOPSEARCH_TARGET" /* TargetName */, 3 /* Type */, ch_seller->GetVID() /* Arg1 */, 0 /* Arg2 */, ch_seller->GetMapIndex() /* MapIndex */, "1" /* desc */);
	TargetInfo * pInfo = CTargetManager::instance().GetTargetInfo(ch_buyer->GetPlayerID(), TARGET_TYPE_VID, ch_seller->GetVID());

	if (pInfo){
		ch_buyer->ChatPacket(CHAT_TYPE_INFO, "Seller target created");
	}
	else {
		ch_buyer->ChatPacket(CHAT_TYPE_INFO, "Target create failed. You need to be in the same map with seller");
		return;
	}
}

void CShopManager::RemoveAllItemsFromMysql(DWORD dwSellerPID){
	std::auto_ptr<SQLMsg> pmsg(DBManager::instance().DirectQuery("DELETE FROM shop_onsales_items WHERE seller_pid='%u'", dwSellerPID));

	if (pmsg->uiSQLErrno != 0) {
		sys_err("Shop Item Remove All Query Failed, Error code: %ld", pmsg->uiSQLErrno);
		return;
	}

	sys_log(0, "PID: %u - Logout from game and removed all item from mysql", dwSellerPID);
}
