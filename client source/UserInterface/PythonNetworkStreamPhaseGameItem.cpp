Search:
bool CPythonNetworkStream::SendShopBuyPacket(BYTE bPos)
{
	if (!__CanActMainInstance())
		return true;

	TPacketCGShop PacketShop;
	PacketShop.header = HEADER_CG_SHOP;
	PacketShop.subheader = SHOP_SUBHEADER_CG_BUY;

	if (!Send(sizeof(TPacketCGShop), &PacketShop))
	{
		Tracef("SendShopBuyPacket Error\n");
		return false;
	}

	BYTE bCount=1;
	if (!Send(sizeof(BYTE), &bCount))
	{
		Tracef("SendShopBuyPacket Error\n");
		return false;
	}

	if (!Send(sizeof(BYTE), &bPos))
	{
		Tracef("SendShopBuyPacket Error\n");
		return false;
	}

	return SendSequence();
}

Add it under:
bool CPythonNetworkStream::SendShopSearchBuyPacket(const char* cSeller, BYTE bPos, int iBuyType)
{
	if (!__CanActMainInstance())
		return true;

	TPacketCGShop2 PacketShop;
	PacketShop.header = HEADER_CG_SHOP2;
	PacketShop.subheader = SHOP2_SUBHEADER_CG_BUY;
	strncpy(PacketShop.cSellerName, cSeller, 24);
	PacketShop.bItemPos = bPos;
	PacketShop.iBuyType = iBuyType;

	if (!Send(sizeof(TPacketCGShop2), &PacketShop))
	{
		Tracef("SendShopSearchBuyPacket Error\n");
		return false;
	}

	return SendSequence();
}

bool CPythonNetworkStream::SendShopSearchFindPacket(int iJob, int iType, int iSubType, int iMinLevel, int iMaxLevel, int iMinRefine, int iMaxRefine, int iMinPrice, int iMaxPrice, const char* pcItemName)
{
	if (!__CanActMainInstance())
		return true;

	TPacketCGShop2 PacketShop;
	PacketShop.header = HEADER_CG_SHOP2;
	PacketShop.subheader = SHOP2_SUBHEADER_CG_SEARCH;
	PacketShop.iJob = iJob;
	PacketShop.iType = iType;
	PacketShop.iSubtype = iSubType;
	PacketShop.iMinLevel = iMinLevel;
	PacketShop.iMaxLevel = iMaxLevel;
	PacketShop.iMinRefine = iMinRefine;
	PacketShop.iMaxRefine = iMaxRefine;
	PacketShop.iMinPrice = iMinPrice;
	PacketShop.iMaxPrice = iMaxPrice;
	strncpy(PacketShop.cItemNameForSearch, pcItemName, 24);

	if (!Send(sizeof(TPacketCGShop2), &PacketShop))
	{
		Tracef("SendShopSearchFindPacket Error\n");
		return false;
	}

	return SendSequence();
}
