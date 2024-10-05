Search:
import stringCommander

Add it under:
import uiPrivateShopSearch

---

Search:
		self.playerGauge = None

Add it under:
		self.PrivateShopSearch = None

---

Search:
		self.playerGauge = uiPlayerGauge.PlayerGauge(self)
		self.playerGauge.Hide()

Add it under:
		self.PrivateShopSearch = uiPrivateShopSearch.PrivateShopSearch()
		self.PrivateShopSearch.Close()

---

Search:
self.affectShower = None

Add it under:
self.PrivateShopSearch = None

---

Search:
			# PRIVATE_SHOP_PRICE_LIST
			"MyShopPriceList"		: self.__PrivateShop_PriceList,
			# END_OF_PRIVATE_SHOP_PRICE_LIST

Add it under:
			"OpenShopSearchGUI"			: self.PrivateShopSearch.OpenWindow,
			"SetShopSearchType"			: self.PrivateShopSearch.SetWorkType,
			"GetSearchedItemData"		: self.PrivateShopSearch.GetItemListFromServer,
			"CreateSearchedItemList"	: self.PrivateShopSearch.CreateGUIList,
			"RemoveItemFromList"		: self.PrivateShopSearch.RemoveItemFromList,


