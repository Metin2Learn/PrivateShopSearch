Search:
	void CreateTargetEffect(DWORD dwID, DWORD dwChrVID);
	void CreateTargetEffect(DWORD dwID, long lx, long ly);

Change:
	void CreateTargetEffect(DWORD dwID, DWORD dwChrVID);
	void CreateTargetEffect2(DWORD dwID, DWORD dwChrVID);
	void CreateTargetEffect(DWORD dwID, long lx, long ly);
	void CreateTargetEffect2(DWORD dwID, long lx, long ly);

---

Search:
	std::map<DWORD, DWORD> m_kMap_dwTargetID_dwChrID;

Add it under:
	std::map<DWORD, DWORD> m_kMap_dwTargetID_dwChrID2;