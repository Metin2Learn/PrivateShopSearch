Search:
		virtual int	Buy(LPCHARACTER ch, BYTE pos);

Add in under:
		virtual int	BuyFromGlass(LPCHARACTER ch_seller, LPCHARACTER ch_buyer, BYTE pos);
		void	InsertInMysql(LPCHARACTER lpSeller, LPITEM item, BYTE bPos, DWORD dwItemPrice);
		void	RemoveFromMysql(DWORD dwSellerPID, BYTE bPos);
