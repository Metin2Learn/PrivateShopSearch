Search:
	void	Buy(LPCHARACTER ch, BYTE pos);

Add in under:
	void	BuyFromGlass(LPCHARACTER ch_seller, LPCHARACTER ch_buyer, BYTE pos, int iBuyType);
	void	FindFromGlass(LPCHARACTER ch_seller, LPCHARACTER ch_buyer);
	void	RemoveAllItemsFromMysql(DWORD dwSellerPID);
