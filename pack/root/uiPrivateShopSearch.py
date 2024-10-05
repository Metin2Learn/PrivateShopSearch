from ui_wrapper import _ui
import dbg, net, player, grp, wndMgr, item
import ui, constInfo, uiScriptLocale, uiToolTip, uiCommon

class PrivateShopSearch(ui.ScriptWindow):
	def __init__(self):
		ui.ScriptWindow.__init__(self)

		self.QuestionDialog = None
		self.GOLD_COLOR	= 0xFFFEE3AE
		self.RED_COLOR = 0xFF8b0000
		self.ORJ_COLOR = grp.GenerateColor(0.0, 0.0, 0.0, 1.0)

		self.ItemList = []
		self.ItemCount = len(self.ItemList)

		self.WorkType = 0
		self.CurrentPageNumber = 1
		self.List_Button_Objects = {}
		self.ClickedButtonIndex = -99
		self.ItemIdxToItemPos = {}

		self.SelectedJob = ""
		self.SelectedCategory = ""
		self.SelectedSubCategory = ""


		self.LC_TEXT = {
			# Common
			"PrivateShopSearchDialog": 			"Search",
			"PRIVATESHOPSEARCH_ITEMNAME": 		"Name",
			"PRIVATESHOPSEARCH_LEVEL": 			"Level",
			"PRIVATESHOPSEARCH_REFINE": 		"Item Level",
			"PRIVATESHOPSEARCH_PRICE": 			"Price",
			"PRIVATESHOPSEARCH_JOB": 			"Class",
			"PRIVATESHOPSEARCH_ITEMTYPE":		"Items",
			"PRIVATESHOPSEARCH_SEARCH":			"Search",
			"PRIVATESHOPSEARCH_BUY": 			"Buy",
			"PRIVATESHOPSEARCH_CATEGORY": 		"Category",
			"PRIVATESHOPSEARCH_SUBCATEGORY": 	"Subcategory",
			"PRIVATESHOPSEARCH_ITEMCOUNT":		"Count",
			"PRIVATESHOPSEARCH_ITEMPRICE":		"Price",
			"PRIVATESHOPSEARCH_SELLERNAME":		"Seller",

			# Notifications
			"BUYTITEM":				"Do you want to buy the selected item?",
			"SELECTITEM":			"Item Selected",
			"EMPTYITEMLIST":		"Item listy is empty. Failed to get items information",
			"UNKNOWNERROR":			"Unknown Error",
			"MISSINGOPTION":		"Have a missing argument",
			"EMPTYITEM":			"Item not selected",
			"SELECTSUBCAT":			"You need select correct Subcategory",
			"ITEMNOTFOUND":			"Item not found",
			"WRONGCATEGORY":		"You need select correct category",
			"WRONGJOB":				"You need select correct job",

			# Jobs
			"Savasci":				"Warrior",
			"Ninja":				"Ninja",
			"Sura":					"Sura",
			"Saman":				"Shaman",
			"Lycan":				"Lycan",

			# Types
			"Silahlar": 			"Weapons",
			"Ekipman": 				"Equipment",
			"Tuketim Nesneleri": 	"Consumables",
			"Malzemeler": 			"Materials",
			"Ruh Taslari": 			"Spirit Stones",
			"Baliklar": 			"Fish",
			"Kemer": 				"Belts",
			"Nesne Gelistirmeleri": "Item Improvement",
			"Balikcilik": 			"Fishing Poles",
			"Essiz": 				"Unique",
			"Yetenek Kitaplari": 	"Skill Books",
			"Gorev": 				"Quest",
			"Pet Sistemi": 			"Pet System",
			"Sandiklar": 			"Chests",
			"Unutkanlik Kitabi": 	"Book of Forgetfulness",
			"Hediye Kutulari": 		"Gift Boxes",
			"Kazma": 				"Pickaxes",
			"Iksirler": 			"Potions",
			"Kostumler": 			"Costumes",
			"Ejderha Tasi Simyasi": "Dragon Stone Alchemy",
			"Diger": 				"Miscellaneous",

			# Subtypes
			"Tek el kiliclar":		"One-Handed Swords",
			"Cift el kiliclar":		"Two-Handed Swords",
			"Hancerler":			"Daggers",
			"Yay":					"Bows",
			"Yelpaze":				"Fans",
			"Canlar":				"Bells",
			"Penceler":				"Claws",
			"Ok Cantasi":			"Quivers",
			"Ok":					"Arrow",

			"Kostum":				"Costume",
			"Sac Stili":			"Hairstyle",
			"Omuz Kusaklari":		"Shoulder Sashes",
			"Binek":				"Mount",

			"Zirhlar":				"Armour",
			"Kupeler":				"Earrings",
			"Kasklar":				"Helmets",
			"Kolyeler":				"Necklaces",
			"Ayakkabilar":			"Shoes",
			"Bilezik":				"Bracelets",
			"Kalkanlar":			"Shields",

			"Oniks":				"Onyx",
			"Safir":				"Sapphire",
			"Yesim":				"Jade",
			"Yakut":				"Ruby",
			"Elmas":				"Diamond",
			"Grena":				"Garnet",

			"Pet Yumurtalari":		"Pet Eggs",
			"Pet Beceri Kitaplari":	"Pet Skill Books",

			"Canli Balik":			"Alive Fish",
			"Olu Balik":			"Dead Fish",

			"Iksirler":				"Potions",
			"Ozutler":				"Elixirs",
			"HP Nesneleri":			"HP Items",
			"Sebnem":				"Dew",

			"Ince Kumas":			"Fine Cloth",
			"Parsomenler":			"Scrolls",
			"Tas Sanati":			"Stone Handbook",
			"Elmas":				"Diamond",

			"Beyaz Inci":			"White Pearl",
			"Mavi Inci":			"Blue Pearl",
			"Kankirmizisi Inci":	"Blood Pearl",
			"Mucehver":				"Gemstones",
			"Enerji Parcasi":		"Energy Fragments",
			"Kristal":				"Crystal",
			"Cevher":				"Ore"
		}

		self.Real_Job_List = [
			self.LC_TEXT["Savasci"],
			self.LC_TEXT["Ninja"],
			self.LC_TEXT["Sura"],
			self.LC_TEXT["Saman"],
			self.LC_TEXT["Lycan"]
		]
		self.Real_Category_List = [
			self.LC_TEXT["Silahlar"],
			self.LC_TEXT["Ekipman"],
			self.LC_TEXT["Tuketim Nesneleri"],
			self.LC_TEXT["Malzemeler"],
			self.LC_TEXT["Ruh Taslari"],
			self.LC_TEXT["Baliklar"],
			self.LC_TEXT["Kemer"],
			self.LC_TEXT["Nesne Gelistirmeleri"],
			self.LC_TEXT["Balikcilik"],
			self.LC_TEXT["Essiz"],
			self.LC_TEXT["Yetenek Kitaplari"],
			self.LC_TEXT["Gorev"],
			self.LC_TEXT["Pet Sistemi"],
			self.LC_TEXT["Sandiklar"],
			self.LC_TEXT["Unutkanlik Kitabi"],
			self.LC_TEXT["Hediye Kutulari"],
			self.LC_TEXT["Kazma"],
			self.LC_TEXT["Iksirler"],
			self.LC_TEXT["Kostumler"],
			self.LC_TEXT["Ejderha Tasi Simyasi"],
			self.LC_TEXT["Diger"]
		]
		self.Real_SubCategory_List = [
			self.LC_TEXT["Tek el kiliclar"],
			self.LC_TEXT["Cift el kiliclar"],
			self.LC_TEXT["Hancerler"],
			self.LC_TEXT["Yay"],
			self.LC_TEXT["Yelpaze"],
			self.LC_TEXT["Canlar"],
			self.LC_TEXT["Penceler"],
			self.LC_TEXT["Ok Cantasi"],
			self.LC_TEXT["Ok"],
			self.LC_TEXT["Kostum"],
			self.LC_TEXT["Sac Stili"],
			self.LC_TEXT["Omuz Kusaklari"],
			self.LC_TEXT["Binek"],
			self.LC_TEXT["Zirhlar"],
			self.LC_TEXT["Kupeler"],
			self.LC_TEXT["Kasklar"],
			self.LC_TEXT["Kolyeler"],
			self.LC_TEXT["Ayakkabilar"],
			self.LC_TEXT["Bilezik"],
			self.LC_TEXT["Kalkanlar"],
			self.LC_TEXT["Oniks"],
			self.LC_TEXT["Safir"],
			self.LC_TEXT["Yesim"],
			self.LC_TEXT["Yakut"],
			self.LC_TEXT["Elmas"],
			self.LC_TEXT["Grena"],
			self.LC_TEXT["Pet Yumurtalari"],
			self.LC_TEXT["Pet Beceri Kitaplari"],
			self.LC_TEXT["Canli Balik"],
			self.LC_TEXT["Olu Balik"],
			self.LC_TEXT["Iksirler"],
			self.LC_TEXT["Ozutler"],
			self.LC_TEXT["HP Nesneleri"],
			self.LC_TEXT["Sebnem"],
			self.LC_TEXT["Ince Kumas"],
			self.LC_TEXT["Parsomenler"],
			self.LC_TEXT["Tas Sanati"],
			self.LC_TEXT["Elmas"],
			self.LC_TEXT["Beyaz Inci"],
			self.LC_TEXT["Mavi Inci"],
			self.LC_TEXT["Kankirmizisi Inci"],
			self.LC_TEXT["Mucehver"],
			self.LC_TEXT["Enerji Parcasi"],
			self.LC_TEXT["Kristal"],
			self.LC_TEXT["Cevher"],
			self.LC_TEXT["Diger"]
		]

		self.RealJobValues = {
			self.LC_TEXT["Savasci"]:	0,
			self.LC_TEXT["Ninja"]:		1,
			self.LC_TEXT["Sura"]:		2,
			self.LC_TEXT["Saman"]:		3,
			self.LC_TEXT["Lycan"]:		4
		}
		self.RealTypeValues = {
			self.LC_TEXT["Silahlar"]:				1,
			self.LC_TEXT["Ekipman"]:				2,
			self.LC_TEXT["Tuketim Nesneleri"]:		3,
			self.LC_TEXT["Malzemeler"]:				4,
			self.LC_TEXT["Ruh Taslari"]:			10,
			self.LC_TEXT["Baliklar"]:				12,
			self.LC_TEXT["Kemer"]:					34,
			self.LC_TEXT["Nesne Gelistirmeleri"]:	14,
			self.LC_TEXT["Balikcilik"]:				13,
			self.LC_TEXT["Essiz"]:					16,
			self.LC_TEXT["Yetenek Kitaplari"]:		17,
			self.LC_TEXT["Gorev"]:					18,
			self.LC_TEXT["Pet Sistemi"]:			35,
			self.LC_TEXT["Sandiklar"]:				20,
			self.LC_TEXT["Unutkanlik Kitabi"]:		22,
			self.LC_TEXT["Hediye Kutulari"]:		23,
			self.LC_TEXT["Kazma"]:					24,
			self.LC_TEXT["Iksirler"]:				3,
			self.LC_TEXT["Kostumler"]:				28,
			self.LC_TEXT["Ejderha Tasi Simyasi"]:	29,
			self.LC_TEXT["Diger"]:					99
		}
		self.RealSubTypeValues = {
			self.LC_TEXT["Tek el kiliclar"]:		0,
			self.LC_TEXT["Cift el kiliclar"]:		3,
			self.LC_TEXT["Hancerler"]:				1,
			self.LC_TEXT["Yay"]:					2,
			self.LC_TEXT["Ok"]:						6,
			self.LC_TEXT["Yelpaze"]:				5,
			self.LC_TEXT["Canlar"]:					4,
			self.LC_TEXT["Penceler"]:				7,
			self.LC_TEXT["Ok Cantasi"]:				8,
			self.LC_TEXT["Kostum"]:					0,
			self.LC_TEXT["Sac Stili"]:				1,
			self.LC_TEXT["Omuz Kusaklari"]:			2,
			self.LC_TEXT["Binek"]:					3,
			self.LC_TEXT["Zirhlar"]:				0,
			self.LC_TEXT["Kupeler"]:				6,
			self.LC_TEXT["Kasklar"]:				1,
			self.LC_TEXT["Kolyeler"]:				5,
			self.LC_TEXT["Ayakkabilar"]:			4,
			self.LC_TEXT["Bilezik"]:				3,
			self.LC_TEXT["Kalkanlar"]:				2,
			self.LC_TEXT["Oniks"]:					5,
			self.LC_TEXT["Safir"]:					3,
			self.LC_TEXT["Yesim"]:					2,
			self.LC_TEXT["Yakut"]:					1,
			self.LC_TEXT["Elmas"]:					0,
			self.LC_TEXT["Grena"]:					4,
			self.LC_TEXT["Pet Yumurtalari"]:		0,
			self.LC_TEXT["Pet Beceri Kitaplari"]:	4,
			self.LC_TEXT["Canli Balik"]:			0,
			self.LC_TEXT["Olu Balik"]:				1,
			self.LC_TEXT["Iksirler"]:				0,
			self.LC_TEXT["Ozutler"]:				12,
			self.LC_TEXT["HP Nesneleri"]:			11,
			self.LC_TEXT["Sebnem"]:					1,
			self.LC_TEXT["Ince Kumas"]:				20,
			self.LC_TEXT["Parsomenler"]:			2,
			self.LC_TEXT["Tas Sanati"]:				14,
			self.LC_TEXT["Elmas"]:					20,
			self.LC_TEXT["Beyaz Inci"]:				5,
			self.LC_TEXT["Mavi Inci"]:				4,
			self.LC_TEXT["Kankirmizisi Inci"]:		3,
			self.LC_TEXT["Mucehver"]:				8,
			self.LC_TEXT["Enerji Parcasi"]:			0,
			self.LC_TEXT["Kristal"]:				7,
			self.LC_TEXT["Cevher"]:					21,
			self.LC_TEXT["Diger"]:					99
		}
		# kostüme kostüm silah eklenecek

		self.GUIFunc()

	def __del__(self):
		self.__RemoveLastSearch()
		self.Close()
		ui.ScriptWindow.__del__(self)

	def GUIFunc(self):
		self.Board = _ui().BoardWithTitleBar(None, 1, 0, 10, 590, 370, self.LC_TEXT["PrivateShopSearchDialog"], self.OpenWindow)
		self.Board.OnPressEscapeKey = ui.__mem_func__(self.Close)

		self.ItemNameImg = _ui().ImageBox(self.Board, "d:/ymir work/ui/privatesearch/private_leftNameImg.sub", 10, 275)
		self.ItemNameText = _ui().TextLine(self.ItemNameImg, self.LC_TEXT["PRIVATESHOPSEARCH_ITEMNAME"], 60, 5)
		self.ItemNameText.SetHorizontalAlignCenter(), self.ItemNameText.SetPackedFontColor(self.GOLD_COLOR)

		self.ItemNameSlot = _ui().ImageBox(self.Board, "d:/ymir work/ui/privatesearch/private_leftSlotImg.sub", 12, 295)
		self.ItemNameValue = _ui().EditLine(self.ItemNameSlot, "", 2, 3, 136, 15, 20)


		self.LevelImg = _ui().ImageBox(self.Board, "d:/ymir work/ui/privatesearch/private_leftNameImg.sub", 10, 135)
		self.LevelText = _ui().TextLine(self.LevelImg, self.LC_TEXT["PRIVATESHOPSEARCH_LEVEL"], 60, 5)
		self.LevelText.SetHorizontalAlignCenter(), self.LevelText.SetPackedFontColor(self.GOLD_COLOR)
		self.LevelText2 = _ui().TextLine(self.Board, "~", 65, 158)

		self.minLevelSlot = _ui().ImageBox(self.Board, "d:/ymir work/ui/privatesearch/private_leftSlotHalfImg.sub", 12, 155)
		self.minLevelValue = _ui().EditLine(self.minLevelSlot, "0", 2, 3, 36, 15, 3)
		self.minLevelValue.SetNumberMode()
		self.maxLevelSlot = _ui().ImageBox(self.Board, "d:/ymir work/ui/privatesearch/private_leftSlotHalfImg.sub", 90, 155)
		self.maxLevelValue = _ui().EditLine(self.maxLevelSlot, "120", 2, 3, 36, 15, 3)
		self.minLevelValue.SetNumberMode()


		self.refineImg = _ui().ImageBox(self.Board, "d:/ymir work/ui/privatesearch/private_leftNameImg.sub", 10, 175)
		self.refineText = _ui().TextLine(self.refineImg, self.LC_TEXT["PRIVATESHOPSEARCH_REFINE"], 60, 5)
		self.refineText.SetHorizontalAlignCenter(), self.refineText.SetPackedFontColor(self.GOLD_COLOR)
		self.refineText2 = _ui().TextLine(self.Board, "~", 65, 200)

		self.minrefineSlot = _ui().ImageBox(self.Board, "d:/ymir work/ui/privatesearch/private_leftSlotHalfImg.sub", 12, 195)
		self.minrefineValue = _ui().EditLine(self.minrefineSlot, "0", 2, 3, 36, 15, 3)
		self.minrefineValue.SetNumberMode()
		self.maxrefineSlot = _ui().ImageBox(self.Board, "d:/ymir work/ui/privatesearch/private_leftSlotHalfImg.sub", 90, 195)
		self.maxrefineValue = _ui().EditLine(self.maxrefineSlot, "9", 2, 3, 36, 15, 3)
		self.maxrefineValue.SetNumberMode()


		self.GoldImg = _ui().ImageBox(self.Board, "d:/ymir work/ui/privatesearch/private_leftNameImg.sub", 10, 215)
		self.GoldText = _ui().TextLine(self.GoldImg, self.LC_TEXT["PRIVATESHOPSEARCH_PRICE"], 60, 5)
		self.GoldText.SetHorizontalAlignCenter(), self.GoldText.SetPackedFontColor(self.GOLD_COLOR)

		self.GoldminSlot = _ui().ImageBox(self.Board, "d:/ymir work/ui/privatesearch/private_leftSlotImg.sub", 12, 235)
		self.GoldminValue = _ui().EditLine(self.GoldminSlot, "0", 2, 3, 115, 15, 10)
		self.GoldminValue.SetNumberMode()

		self.GoldmaxSlot = _ui().ImageBox(self.Board, "d:/ymir work/ui/privatesearch/private_leftSlotImg.sub", 12, 255)
		self.GoldmaxValue = _ui().EditLine(self.GoldmaxSlot, "1999999999", 2, 3, 135, 15, 10)
		self.GoldmaxValue.SetNumberMode()


		self.ItemNameJobSlot = _ui().ImageBox(self.Board, "d:/ymir work/ui/privatesearch/private_leftNameImg.sub", 10, 35)
		self.ItemNameJobText = _ui().TextLine(self.ItemNameJobSlot, self.LC_TEXT["PRIVATESHOPSEARCH_JOB"], 60, 5)
		self.ItemNameJobText.SetHorizontalAlignCenter(), self.ItemNameJobText.SetPackedFontColor(self.GOLD_COLOR)


		self.ItemTypeImg = _ui().ImageBox(self.Board, "d:/ymir work/ui/privatesearch/private_leftNameImg.sub", 10, 75)
		self.ItemTypeName = _ui().TextLine(self.ItemTypeImg, self.LC_TEXT["PRIVATESHOPSEARCH_ITEMTYPE"], 60, 5)
		self.ItemTypeName.SetHorizontalAlignCenter(), self.ItemTypeName.SetPackedFontColor(self.GOLD_COLOR)


		self.SearchButton = _ui().Button(self.Board, self.LC_TEXT["PRIVATESHOPSEARCH_SEARCH"], "", 10, 328, self.SearchButton_Func, "d:/ymir work/ui/privatesearch/private_findbuttonImg01.sub", "d:/ymir work/ui/privatesearch/private_findbuttonImg02.sub", "d:/ymir work/ui/privatesearch/private_findbuttonImg03.sub")
		self.BuyButton = _ui().Button(self.Board, self.LC_TEXT["PRIVATESHOPSEARCH_BUY"], "", 455, 338, self.empty, "d:/ymir work/ui/privatesearch/private_findbuttonImg01.sub", "d:/ymir work/ui/privatesearch/private_findbuttonImg02.sub", "d:/ymir work/ui/privatesearch/private_findbuttonImg03.sub")


		self.LeftTop = _ui().ImageBox(self.Board, "d:/ymir work/ui/privatesearch/private_mainboxlefttop.sub", 133, 36)
		self.RightTop = _ui().ImageBox(self.Board, "d:/ymir work/ui/privatesearch/private_mainboxrighttop.sub", 561, 36)
		self.LeftBottom = _ui().ImageBox(self.Board, "d:/ymir work/ui/privatesearch/private_mainboxleftbottom.sub", 133, 320)
		self.RightBottom = _ui().ImageBox(self.Board, "d:/ymir work/ui/privatesearch/private_mainboxrightbottom.sub", 561, 320)

		self.leftcenterImg = _ui().ExpandedImageBox(self.Board, "d:/ymir work/ui/privatesearch/private_leftcenterImg.tga", 133, 52)
		self.leftcenterImg.SetRenderingRect(0.0, 0.0, 0, 15)
		self.rightcenterImg = _ui().ExpandedImageBox(self.Board, "d:/ymir work/ui/privatesearch/private_rightcenterImg.tga", 560, 52)
		self.rightcenterImg.SetRenderingRect(0.0, 0.0, 0, 15)
		self.topcenterImg = _ui().ExpandedImageBox(self.Board, "d:/ymir work/ui/privatesearch/private_topcenterImg.tga", 149, 36)
		self.topcenterImg.SetRenderingRect(0.0, 0.0, 24, 0)
		self.bottomcenterImg = _ui().ExpandedImageBox(self.Board, "d:/ymir work/ui/privatesearch/private_bottomcenterImg.tga", 149, 320)
		self.bottomcenterImg.SetRenderingRect(0.0, 0.0, 24, 0)
		self.centerImg = _ui().ExpandedImageBox(self.Board, "d:/ymir work/ui/privatesearch/private_centerImg.tga", 149, 52)
		self.centerImg.SetRenderingRect(0.0, 0.0, 24, 15)


		self.TabMenuImg = _ui().ImageBox(self.Board, "d:/ymir work/ui/tab_menu_01.tga", 136, 39)
		self.ResultNameText1 = _ui().TextLine(self.TabMenuImg, self.LC_TEXT["PRIVATESHOPSEARCH_ITEMNAME"], 67, 4) # PRIVATESHOPSEARCH_ITEMNAME
		self.ResultNameText2 = _ui().TextLine(self.TabMenuImg, self.LC_TEXT["PRIVATESHOPSEARCH_SELLERNAME"], 207, 4) # PRIVATESHOPSEARCH_SELLER
		self.ResultNameText3 = _ui().TextLine(self.TabMenuImg, self.LC_TEXT["PRIVATESHOPSEARCH_ITEMCOUNT"], 303, 4) # PRIVATESHOPSEARCH_COUNT
		self.ResultNameText4 = _ui().TextLine(self.TabMenuImg, self.LC_TEXT["PRIVATESHOPSEARCH_ITEMPRICE"], 377, 4) # PRIVATESHOPSEARCH_PRICE

		self.first_prev_button = _ui().Button(self.Board, "", "", 210, 315, self.LastPrevPageButton_Func, "d:/ymir work/ui/privatesearch/private_first_prev_btn_01.sub", "d:/ymir work/ui/privatesearch/private_first_prev_btn_02.sub", "d:/ymir work/ui/privatesearch/private_first_prev_btn_01.sub")
		self.prev_button = _ui().Button(self.Board, "", "", 240, 315, self.PrevPageButton_Func, "d:/ymir work/ui/privatesearch/private_prev_btn_01.sub", "d:/ymir work/ui/privatesearch/private_prev_btn_02.sub", "d:/ymir work/ui/privatesearch/private_prev_btn_01.sub")
		self.next_button = _ui().Button(self.Board, "", "", 453, 315, self.NextPageButton_Func, "d:/ymir work/ui/privatesearch/private_next_btn_01.sub", "d:/ymir work/ui/privatesearch/private_next_btn_02.sub", "d:/ymir work/ui/privatesearch/private_next_btn_01.sub")
		self.last_next_button = _ui().Button(self.Board, "", "", 483, 315, self.LastNextPageButton_Func, "d:/ymir work/ui/privatesearch/private_last_next_btn_01.sub", "d:/ymir work/ui/privatesearch/private_last_next_btn_00.sub", "d:/ymir work/ui/privatesearch/private_last_next_btn_01.sub")


		self.page_slot, self.page_numbertext = _ui().SlotWithText(self.Board, "1", 335, 313, 22, 16)


		self.page_slot.Hide(), self.first_prev_button.Hide(), self.prev_button.Hide(), self.next_button.Hide(), self.last_next_button.Hide()
		self.SearchButton.Down(), self.SearchButton.Disable()
		self.BuyButton.Down(), self.BuyButton.Disable()


		self.ItemSubCategoryComboBox = _ui().ComboBox(self.Board, self.LC_TEXT["PRIVATESHOPSEARCH_SUBCATEGORY"], 10, 117, 120)
		self.ItemSubCategoryComboBox.SetEvent(self.SortItemSubCategorys)


		self.ItemCategoryComboBox = _ui().ComboBox(self.Board, self.LC_TEXT["PRIVATESHOPSEARCH_CATEGORY"], 10, 97, 120)
		self.ItemCategoryComboBox.SetEvent(self.SetItemCategorys)


		self.ItemNameJobComboBox = _ui().ComboBox(self.Board, self.LC_TEXT["PRIVATESHOPSEARCH_JOB"], 10, 57, 120)
		self.ItemNameJobComboBox.SetEvent(self.SetSelectedJob)
		listedItemCount = 0
		for tmpJobList in self.Real_Job_List:
			self.ItemNameJobComboBox.InsertItem(listedItemCount, tmpJobList)
			listedItemCount += 1


	def SetSelectedJob(self, x):
		tmpSelectedJob = str(self.ItemNameJobComboBox.GetCurrentText())
		if tmpSelectedJob == "" or tmpSelectedJob == self.LC_TEXT["PRIVATESHOPSEARCH_JOB"]:
			self.Notification = _ui().Popup(self.LC_TEXT["WRONGJOB"], None, None)
			return

		self.SelectedJob = tmpSelectedJob

		if self.ItemCategoryComboBox.GetItemCount():
			self.ItemCategoryComboBox.SetCurrentItem(self.LC_TEXT["PRIVATESHOPSEARCH_CATEGORY"])
			self.ItemCategoryComboBox.ClearItem()
		if self.ItemSubCategoryComboBox.GetItemCount():
			self.ItemSubCategoryComboBox.SetCurrentItem(self.LC_TEXT["PRIVATESHOPSEARCH_SUBCATEGORY"])
			self.ItemSubCategoryComboBox.ClearItem()

		listedItemCount = 0
		for tmpCatList in self.Real_Category_List:
			self.ItemCategoryComboBox.InsertItem(listedItemCount, tmpCatList)
			listedItemCount += 1

		self.CheckSearchButtonStatus()

	def SetItemCategorys(self, x):
		tmpSelectedJob = str(self.ItemNameJobComboBox.GetCurrentText())
		tmpSelectedCategory = str(self.ItemCategoryComboBox.GetCurrentText())
		if tmpSelectedCategory == "" or tmpSelectedCategory == self.LC_TEXT["PRIVATESHOPSEARCH_CATEGORY"]:
			self.Notification = _ui().Popup(self.LC_TEXT["WRONGCATEGORY"], None, None)
			return

		self.SelectedCategory = tmpSelectedCategory

		#if self.ItemSubCategoryComboBox.GetItemCount():
		self.ItemSubCategoryComboBox.SetCurrentItem(self.LC_TEXT["PRIVATESHOPSEARCH_SUBCATEGORY"])
		self.ItemSubCategoryComboBox.ClearItem()

		listedItemCount = 0
		if self.RealTypeValues.get(tmpSelectedCategory) == self.RealTypeValues[self.LC_TEXT["Silahlar"]]:  # First 8 subtype - weapon type

			if self.RealJobValues.get(tmpSelectedJob) == self.RealJobValues[self.LC_TEXT["Lycan"]]:
				self.ItemSubCategoryComboBox.InsertItem(listedItemCount, self.LC_TEXT["Penceler"])
				listedItemCount += 1

			elif self.RealJobValues.get(tmpSelectedJob) == self.RealJobValues[self.LC_TEXT["Ninja"]]:
				ninja_weapons_subtype_list = [
					self.LC_TEXT["Tek el kiliclar"], self.LC_TEXT["Hancerler"],
					self.LC_TEXT["Ok"], self.LC_TEXT["Ok Cantasi"], self.LC_TEXT["Yay"]
				]

				for i in ninja_weapons_subtype_list:
					self.ItemSubCategoryComboBox.InsertItem(listedItemCount, i)
					listedItemCount += 1

			elif self.RealJobValues.get(tmpSelectedJob) == self.RealJobValues[self.LC_TEXT["Sura"]]:
				self.ItemSubCategoryComboBox.InsertItem(listedItemCount, self.LC_TEXT["Tek el kiliclar"])
				listedItemCount += 1

			elif self.RealJobValues.get(tmpSelectedJob) == self.RealJobValues[self.LC_TEXT["Saman"]]:
				shaman_weapons_subtype_list = [
					self.LC_TEXT["Yelpaze"], self.LC_TEXT["Canlar"]
				]

				for i in shaman_weapons_subtype_list:
					self.ItemSubCategoryComboBox.InsertItem(listedItemCount, i)
					listedItemCount += 1

			elif self.RealJobValues.get(tmpSelectedJob) == self.RealJobValues[self.LC_TEXT["Savasci"]]:
				warrior_weapons_subtype_list = [
					self.LC_TEXT["Tek el kiliclar"], self.LC_TEXT["Cift el kiliclar"]
				]

				for i in warrior_weapons_subtype_list:
					self.ItemSubCategoryComboBox.InsertItem(listedItemCount, i)
					listedItemCount += 1

			else:
				self.Notification = _ui().Popup(self.LC_TEXT["UNKNOWNERROR"], None, None)
				return

		elif self.RealTypeValues.get(tmpSelectedCategory) == self.RealTypeValues[self.LC_TEXT["Kostumler"]]: # After 4 subtype - costumes type
			for i in range(10, 14):
				self.ItemSubCategoryComboBox.InsertItem(listedItemCount, self.Real_SubCategory_List[i - 1])
				listedItemCount += 1

		elif self.RealTypeValues.get(tmpSelectedCategory) == self.RealTypeValues[self.LC_TEXT["Ekipman"]]: # After 8 subtype - equipment type
			for i in range(14, 21):
				self.ItemSubCategoryComboBox.InsertItem(listedItemCount, self.Real_SubCategory_List[i - 1])
				listedItemCount += 1

		elif self.RealTypeValues.get(tmpSelectedCategory) == self.RealTypeValues[self.LC_TEXT["Ejderha Tasi Simyasi"]]: # After 6 subtype - dss type
			for i in range(21, 27):
				self.ItemSubCategoryComboBox.InsertItem(listedItemCount, self.Real_SubCategory_List[i - 1])
				listedItemCount += 1

		elif self.RealTypeValues.get(tmpSelectedCategory) == self.RealTypeValues[self.LC_TEXT["Pet Sistemi"]]: # After 2 subtype - pet type
			for i in range(27, 29):
				self.ItemSubCategoryComboBox.InsertItem(listedItemCount, self.Real_SubCategory_List[i - 1])
				listedItemCount += 1

		elif self.RealTypeValues.get(tmpSelectedCategory) == self.RealTypeValues[self.LC_TEXT["Baliklar"]]: # After 2 subtype - fish type
			for i in range(29, 31):
				self.ItemSubCategoryComboBox.InsertItem(listedItemCount, self.Real_SubCategory_List[i - 1])
				listedItemCount += 1

		elif tmpSelectedCategory == self.LC_TEXT["Iksirler"]: # After 4 subtype - potion type
			for i in range(31, 35):
				self.ItemSubCategoryComboBox.InsertItem(listedItemCount, self.Real_SubCategory_List[i - 1])
				listedItemCount += 1

		elif tmpSelectedCategory == self.LC_TEXT["Tuketim Nesneleri"]: # After 4 subtype - consumable type
			for i in range(35, 39):
				self.ItemSubCategoryComboBox.InsertItem(listedItemCount, self.Real_SubCategory_List[i - 1])
				listedItemCount += 1

		elif self.RealTypeValues.get(tmpSelectedCategory) == self.RealTypeValues[self.LC_TEXT["Nesne Gelistirmeleri"]]: # After 7 subtype - item improvement type
			for i in range(39, 46):
				self.ItemSubCategoryComboBox.InsertItem(listedItemCount, self.Real_SubCategory_List[i - 1])
				listedItemCount += 1

		else:
			self.ItemSubCategoryComboBox.InsertItem(listedItemCount, str(self.LC_TEXT["Diger"]))
			listedItemCount += 1

		self.CheckSearchButtonStatus()

	def SortItemSubCategorys(self, x):
		tmpSelectedSubCategory = str(self.ItemSubCategoryComboBox.GetCurrentText())

		if tmpSelectedSubCategory == "" or tmpSelectedSubCategory == self.LC_TEXT["PRIVATESHOPSEARCH_SUBCATEGORY"]:
			self.Notification = _ui().Popup(self.LC_TEXT["SELECTSUBCAT"], None, None)
			return

		self.SelectedSubCategory = tmpSelectedSubCategory

		self.CheckSearchButtonStatus()

	def CheckSearchButtonStatus(self):
		if self.SelectedJob and self.SelectedCategory and self.SelectedSubCategory:
			self.SearchButton.SetUp(), self.SearchButton.Enable()

	def __RemoveLastSearch(self):
		self.List_Button_Objects.clear() # Remove gui last item list
		self.ItemIdxToItemPos.clear() # Remove idx to pos dict
		del self.ItemList[:] # Remove last item list
		self.ItemCount = 0 # Set zero item count
		self.CurrentPageNumber = 1 # Set page number default
		self.ClickedButtonIndex = -99 # Set clicked button to null

	def SearchButton_Func(self):
		_job_index = self.RealJobValues[self.SelectedJob]
		_type_index = self.RealTypeValues[self.SelectedCategory]
		_subtype_index = self.RealSubTypeValues[self.SelectedSubCategory]

		self.__RemoveLastSearch()

		#dbg.TraceError("Job: %d Type: %d Subtype: %d Min lv: %d Max lv: %d Min refine: %d Max refine: %d Min gold: %d Max gold: %d Name: %s" % (int(_job_index), _type_index, _subtype_index, int(self.minLevelValue.GetText()), int(self.maxLevelValue.GetText()), int(self.minrefineValue.GetText()), int(self.maxrefineValue.GetText()), int(self.GoldminValue.GetText()), int(self.GoldmaxValue.GetText()), str(self.ItemNameValue.GetText())))
		net.SendShopSearchFindPacket(int(_job_index), int(_type_index), int(_subtype_index), int(self.minLevelValue.GetText()), int(self.maxLevelValue.GetText()), int(self.minrefineValue.GetText()), int(self.maxrefineValue.GetText()), int(self.GoldminValue.GetText()), int(self.GoldmaxValue.GetText()), str(self.ItemNameValue.GetText()))

	def BuyButton_Func(self):
		if self.ClickedButtonIndex == -99:
			self.Notification = _ui().Popup(self.LC_TEXT["EMPTYITEM"], None, None)
			return

		QuestionDialog = uiCommon.QuestionDialog()
		QuestionDialog.SetText(str(self.LC_TEXT["BUYTITEM"]))
		QuestionDialog.SetAcceptEvent(lambda arg=True: self.AnswerQuestionDialog(arg))
		QuestionDialog.SetCancelEvent(lambda arg=False: self.AnswerQuestionDialog(arg))
		QuestionDialog.Open()
		self.QuestionDialog = QuestionDialog

	def AnswerQuestionDialog(self, answer):
		if not self.QuestionDialog:
			return

		if answer:
			self.BuyButton_Real_Func()

		self.QuestionDialog.Close()
		self.QuestionDialog = None

	def BuyButton_Real_Func(self):
		if self.ClickedButtonIndex == -99:
			self.Notification = _ui().Popup(self.LC_TEXT["EMPTYITEM"], None, None)
			return

		selectedSellerName = ""
		for i in self.ItemList:
			if str(i[0]) == str(self.ClickedButtonIndex):
				selectedSellerName = i[1]

		if selectedSellerName == "":
			self.Notification = _ui().Popup(self.LC_TEXT["ITEMNOTFOUND"], None, None)
			return

		selectedItemPos = self.ItemIdxToItemPos[self.ClickedButtonIndex]
		net.SendShopSearchBuyPacket(selectedSellerName, selectedItemPos, self.WorkType)

		self.List_Button_Objects["%d_line_button" % self.ClickedButtonIndex].SetColor(self.GOLD_COLOR) #orj
		self.ClickedButtonIndex = -99

	def SelectItemFromList(self, idx):
		if self.ClickedButtonIndex != -99:
			self.List_Button_Objects["%d_line_button" % self.ClickedButtonIndex].SetColor(self.ORJ_COLOR)

		if self.ClickedButtonIndex == idx:
			self.ClickedButtonIndex = -99
			return

		self.ClickedButtonIndex = idx
		self.List_Button_Objects["%d_line_button" % idx].SetColor(self.RED_COLOR)

		self.BuyButton.SetUp(), self.BuyButton.Enable()

	def __CreateGameTypeToolTip(self, row, itemVnum, socket_list, attr_list):
		tooltipItem = uiToolTip.ItemToolTip()

		tooltipItem.AddItemData(int(itemVnum), socket_list, attr_list, IsGlass = 1)
		tooltipItem.OnlyDown()

		return tooltipItem

	def __RecvListObject(self, row, range_sequence, item_name, item_count, item_price, seller_name, item_vnum, item_pos, socket_list, attr_list):
		self.List_Button_Objects["%d_line_button" % row] = _ui().ResizeableButton(self.Board, 137, 45 + (22 * range_sequence), 435, 19, "", "", lambda: self.SelectItemFromList(row))
		self.List_Button_Objects["%d_line_button" % row].SetToolTipWindow(self.__CreateGameTypeToolTip(row, int(item_vnum), socket_list, attr_list))

		self.List_Button_Objects["%d_line_itemname" % row] = _ui().TextLine(self.List_Button_Objects["%d_line_button" % row], str(item_name), 50, 4)
		self.List_Button_Objects["%d_line_sellername" % row] = _ui().TextLine(self.List_Button_Objects["%d_line_button" % row], str(seller_name), 185, 4)
		self.List_Button_Objects["%d_line_itemcount" % row] = _ui().TextLine(self.List_Button_Objects["%d_line_button" % row], str(item_count), 315, 4)
		self.List_Button_Objects["%d_line_price" % row] = _ui().TextLine(self.List_Button_Objects["%d_line_button" % row], str(item_price), 378, 4)

		self.ItemIdxToItemPos[row] = item_pos

	def SetWorkType(self, x):
		self.WorkType = int(x)
		self.BuyButton.SetEvent(self.BuyButton_Func)

	def RemoveItemFromList(self, seller, pos):
		for i in self.ItemList:
			if str(i[1]) == str(seller) and str(i[-1]) == str(pos):
				self.ItemList.remove(i)
				self.CreateGUIList() #reload

	def GetItemListFromServer(self, row, seller_name, item_vnum, item_count, item_refine, item_price, item_level,
								socket0, socket1, socket2,
								attrtype0, attrvalue0, attrtype1, attrvalue1, attrtype2, attrvalue2, attrtype3, attrvalue3,
								attrtype4, attrvalue4, attrtype5, attrvalue5, attrtype6, attrvalue6,
								applytype0, applyvalue0, applytype1, applyvalue1, applytype2, applyvalue2, applytype3, applyvalue3,
								applytype4, applyvalue4, applytype5, applyvalue5, applytype6, applyvalue6, applytype7, applyvalue7,
								item_pos):
		item.SelectItem(int(item_vnum))
		self.ItemList.append([row, seller_name, item.GetItemName(), item_vnum, item_count, item_refine, item_price, item_level, socket0, socket1, socket2, attrtype0, attrvalue0, attrtype1, attrvalue1, attrtype2, attrvalue2, attrtype3, attrvalue3, attrtype4, attrvalue4, attrtype5, attrvalue5, attrtype6, attrvalue6, applytype0, applyvalue0, applytype1, applyvalue1, applytype2, applyvalue2, applytype3, applyvalue3, applytype4, applyvalue4, applytype5, applyvalue5, applytype6, applyvalue6, applytype7, applyvalue7, item_pos])
		if self.ItemCount < 1:
			dbg.TraceError(str(self.ItemList))
		self.ItemCount += 1

	def CreateGUIList(self):
		if self.ItemCount == 0:
			self._Notification = _ui().Popup(self.LC_TEXT["EMPTYITEMLIST"], None, None)
			return

		sorted(self.ItemList, key=lambda x: x[6])
		range_control_value = len(self.List_Button_Objects)

		NewList = []
		for x in self.ItemList:

			range_control_value += 1
			if range_control_value == 12:
				range_control_value = 1

			range_sequence = int(range_control_value)
			row = int(x[0])
			item_name = str(x[2])
			item_count = str(x[4])
			item_price = str(x[6])
			seller_name = str(x[1])
			item_vnum = int(x[3])
			item_pos = int(x[-1])
			socket_list = [int(x[y]) for y in xrange(8, 11)]
			attr_list =  [(int(x[a]), int(x[a+1])) for a in xrange(11, 41, 2)]

			#dbg.TraceError("%d %d %s %s %s %s %d %d %s %s" % (row, range_sequence, item_name, item_count, item_price, seller_name, item_vnum, item_pos, socket_list, attr_list))
			NewList.append([row, range_sequence, item_name, item_count, item_price, seller_name, item_vnum, item_pos, socket_list, attr_list])
			#self.__RecvListObject(row, range_sequence, item_name, item_count, item_price, seller_name, item_vnum, item_pos, socket_list, attr_list)

			#if self.ItemList.index(x) >= 11:
			#	self.List_Button_Objects["%d_line_button" % self.ItemList.index(x)].Hide()

		# Aq ymiri. Düz listeleyince tooltip mouse'un altında açılırsa resizeable buttonlarn altında kalıyor
		# Tersine listelendi, mouse'un üzerinde açılan tooltiplerin altta kalması sağlandı ve üstte açılması engellendi
		for x in reversed(NewList):
			self.__RecvListObject(x[0], x[1], x[2], x[3], x[4], x[5], x[6], x[7], x[8], x[9])

		self.BuyButton.SetUp(), self.BuyButton.Enable()
		if self.ItemCount > 11:
			self.page_slot.Show(), self.next_button.Show(), self.last_next_button.Show()


	def NextPageButton_Func(self):
		self.CurrentPageNumber += 1
		Page_Range_Max = self.CurrentPageNumber * 11 - 1
		Page_Range_Min = Page_Range_Max - 10

		for i in xrange(self.ItemCount):
			if i >= Page_Range_Min and i <= Page_Range_Max:
				self.List_Button_Objects["%d_line_button" % i].Show()
			else:
				self.List_Button_Objects["%d_line_button" % i].Hide()

		self.page_slot.Show(), self.page_numbertext.SetText(str(self.CurrentPageNumber))

		if self.CurrentPageNumber != 1:
			self.first_prev_button.Show(), self.prev_button.Show()
		if self.ItemCount > 11 * self.CurrentPageNumber:
			self.next_button.Show(), self.last_next_button.Show()
		else:
			self.next_button.Hide(), self.last_next_button.Hide()


	def LastNextPageButton_Func(self):
		CalcPageCount = self.ItemCount / 11
		CalcLastPageItemStartIndex = CalcPageCount * 11
		CalcLastPageItemCount = self.ItemCount-CalcLastPageItemStartIndex
		self.CurrentPageNumber = CalcPageCount + 1

		for i in xrange(self.ItemCount):
			if self.List_Button_Objects["%d_line_button" % i].IsShow():
				self.List_Button_Objects["%d_line_button" % i].Hide()

		for i in xrange(CalcLastPageItemCount):
			self.List_Button_Objects["%d_line_button" % int(CalcLastPageItemStartIndex + i)].Show()

		self.page_slot.Show(), self.page_numbertext.SetText(str(self.CurrentPageNumber))

		if self.CurrentPageNumber != 1:
			self.first_prev_button.Show(), self.prev_button.Show()
		if self.ItemCount > 11 * self.CurrentPageNumber:
			self.next_button.Show(), self.last_next_button.Show()
		else:
			self.next_button.Hide(), self.last_next_button.Hide()

	def PrevPageButton_Func(self):
		self.CurrentPageNumber -= 1
		Page_Range_Max = self.CurrentPageNumber * 11 - 1
		Page_Range_Min = Page_Range_Max - 11

		RangedItemCount = 0
		for i in xrange(self.ItemCount):
			if i >= Page_Range_Min and i <= Page_Range_Max:
				RangedItemCount += 1
				self.List_Button_Objects["%d_line_button" % i].Show()
			else:
				self.List_Button_Objects["%d_line_button" % i].Hide()

		self.page_numbertext.SetText(str(self.CurrentPageNumber))

		if RangedItemCount >= 11:
			self.next_button.Show(), self.last_next_button.Show()
		if self.CurrentPageNumber != 1:
			self.first_prev_button.Show(), self.prev_button.Show()
		else:
			self.first_prev_button.Hide(), self.prev_button.Hide()

	def LastPrevPageButton_Func(self):
		self.CurrentPageNumber = 1

		RangedItemCount = 0
		for i in xrange(self.ItemCount):
			if i >= 0 and i <= 10:
				RangedItemCount += 1
				self.List_Button_Objects["%d_line_button" % i].Show()
			else:
				self.List_Button_Objects["%d_line_button" % i].Hide()

		self.page_numbertext.SetText(str(self.CurrentPageNumber))

		if RangedItemCount >= 11:
			self.next_button.Show(), self.last_next_button.Show()
		if self.CurrentPageNumber != 1:
			self.first_prev_button.Show(), self.prev_button.Show()
		else:
			self.first_prev_button.Hide(), self.prev_button.Hide()

	def empty(self):
		pass

	def OpenWindow(self):
		if self.Board.IsShow():
			self.Board.Hide()
		else:
			self.Board.Show()

	def Close(self):
		self.__RemoveLastSearch()
		self.Board.Hide()
		self.Hide()
		return True

	def OnPressEscapeKey(self):
		#self.__del__()
		self.Close()
		return True

#PrivateShopSearch()
