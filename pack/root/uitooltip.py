Search:
	def __init__(self, width = TOOL_TIP_WIDTH, isPickable=False):
		ui.ThinBoard.__init__(self, "TOP_MOST")

		if isPickable:
			pass
		else:
			self.AddFlag("not_pick")

		self.AddFlag("float")

Add in under:
		self.OnlyDownTooltip = 0


---

Search:
	def SetToolTipPosition(self, x = -1, y = -1):
		self.xPos = x
		self.yPos = y

	def ShowToolTip(self):
		self.SetTop()
		self.Show()

		self.OnUpdate()

	def HideToolTip(self):
		self.Hide()

Add in under:
	def OnlyDown(self):
		self.OnlyDownTooltip = 1


---

Search:
		if -1 == self.xPos and -1 == self.yPos:

			(mouseX, mouseY) = wndMgr.GetMousePosition()

			if mouseY < wndMgr.GetScreenHeight() - 300:
				y = mouseY + 40
			else:
				y = mouseY - height - 30

			x = mouseX - width/2

		else:

			x = self.xPos - width/2
			y = self.yPos - height

Change:
		if -1 == self.xPos and -1 == self.yPos:

			(mouseX, mouseY) = wndMgr.GetMousePosition()

			if not self.OnlyDownTooltip:
				if mouseY < wndMgr.GetScreenHeight() - 300:
					y = mouseY + 40
				else:
					y = mouseY - height - 30
			else:
				y = mouseY + 40

			x = mouseX - width/2

		else:

			x = self.xPos - width/2
			y = self.yPos - height


---

Search:
	def ClearToolTip(self):
		self.isShopItem = False
		self.toolTipWidth = self.TOOL_TIP_WIDTH
		ToolTip.ClearToolTip(self)

Add it under:
	def OnlyDown(self):
		ToolTip.OnlyDown(self)


---

Search:
	def __SetItemTitle(self, itemVnum, metinSlot, attrSlot):

Change:
	def __SetItemTitle(self, itemVnum, metinSlot, attrSlot, IsGlass = 0):


---

Search:
	def __SetItemTitle(self, itemVnum, metinSlot, attrSlot, IsGlass = 0):
		if self.__IsPolymorphItem(itemVnum):
			self.__SetPolymorphItemTitle(metinSlot[0])
		else:
			if self.__IsAttr(attrSlot):
				self.__SetSpecialItemTitle()
				return

			self.__SetNormalItemTitle()

Change:
	def __SetItemTitle(self, itemVnum, metinSlot, attrSlot, IsGlass = 0):
		if IsGlass:
			self.AppendTextLine(item.GetItemName(), grp.GenerateColor(1.0, 0.7843, 0.0, 1.0))
			return

		if self.__IsPolymorphItem(itemVnum):
			self.__SetPolymorphItemTitle(metinSlot[0])
		else:
			if self.__IsAttr(attrSlot):
				self.__SetSpecialItemTitle()
				return

			self.__SetNormalItemTitle()

---

Search:
	def AddItemData(self, itemVnum, metinSlot, attrSlot = 0, flags = 0, unbindTime = 0):

Change:
	def AddItemData(self, itemVnum, metinSlot, attrSlot = 0, flags = 0, unbindTime = 0, IsGlass = 0):


---

Search:
		if app.ENABLE_COSTUME_SYSTEM:
			if item.ITEM_TYPE_COSTUME == itemType:
				isCostumeItem = 1
				isCostumeHair = item.COSTUME_TYPE_HAIR == itemSubType
				isCostumeBody = item.COSTUME_TYPE_BODY == itemSubType

				#dbg.TraceError("IS_COSTUME_ITEM! body(%d) hair(%d)" % (isCostumeBody, isCostumeHair))

		self.__AdjustMaxWidth(attrSlot, itemDesc)
		self.__SetItemTitle(itemVnum, metinSlot, attrSlot)

Change:
		if app.ENABLE_COSTUME_SYSTEM:
			if item.ITEM_TYPE_COSTUME == itemType:
				isCostumeItem = 1
				isCostumeHair = item.COSTUME_TYPE_HAIR == itemSubType
				isCostumeBody = item.COSTUME_TYPE_BODY == itemSubType

				#dbg.TraceError("IS_COSTUME_ITEM! body(%d) hair(%d)" % (isCostumeBody, isCostumeHair))

		self.__AdjustMaxWidth(attrSlot, itemDesc)
		self.__SetItemTitle(itemVnum, metinSlot, attrSlot, 1)

		if IsGlass:
			itemImage = ui.ImageBox()
			itemImage.SetParent(self)
			itemImage.Show()

			itemImage.LoadImage(item.GetIconImageFileName())
			itemImage.SetPosition(itemImage.GetWidth() * 2.5, self.toolTipHeight)

			self.toolTipHeight += itemImage.GetHeight()
			self.childrenList.append(itemImage)
			self.ResizeToolTip()


