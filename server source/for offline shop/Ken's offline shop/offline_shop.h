Search:
		bool			RemoveItem(DWORD dwVID, BYTE bPos);
		BYTE			GetLeftItemCount(DWORD dwPID);

Add it under:
		void	RemoveFromMysql(DWORD dwSellerPID, BYTE bPos);
		void	RemoveAllItemsFromMysql(DWORD dwSellerPID);
