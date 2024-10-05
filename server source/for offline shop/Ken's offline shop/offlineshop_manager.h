Search:
		void			WithdrawMoney(LPCHARACTER ch, DWORD dwRequiredMoney);
		BYTE			LeftItemCount(LPCHARACTER ch);

Add it under:
		void	InsertInMysql(LPCHARACTER lpSeller, LPITEM item, BYTE bPos, DWORD dwItemPrice);
		void	RemoveFromMysql(DWORD dwSellerPID, BYTE bPos);
		void	RemoveAllItemsFromMysql(DWORD dwSellerPID);
