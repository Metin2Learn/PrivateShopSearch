Search:
		bool SendShopBuyPacket(BYTE byCount);

Add it under:
		bool SendShopSearchBuyPacket(const char* cSeller, BYTE bPos, int iBuyType);
		bool SendShopSearchFindPacket(int iJob, int iType, int iSubType, int iMinLevel, int iMaxLevel, int iMinRefine, int iMaxRefine, int iMinPrice, int iMaxPrice, const char* pcItemName);
