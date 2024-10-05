Search:
					if (pc->GetShopTime() < get_global_time() || shop->GetItemCount() <= 0)
						pc->DeleteMyShop();

Change:
					if (pc->GetShopTime() < get_global_time() || shop->GetItemCount() <= 0)
					{
						shop->RemoveAllItemsFromMysql(pc->GetPlayerID());
						pc->DeleteMyShop();
					}
