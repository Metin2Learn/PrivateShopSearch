Search:
std::string g_strEffectName = "d:/ymir work/effect/etc/direction/direction_land.mse";

Add it under:
std::string g_strEffectShopSearch = "d:/ymir work/effect/etc/direction/direction_land2.mse";


---

Search:
		std::map<DWORD, DWORD>::iterator itor = m_kMap_dwTargetID_dwChrID.begin();
		for (; itor != m_kMap_dwTargetID_dwChrID.end(); ++itor)
		{
			DWORD dwTargetID = itor->first;
			DWORD dwChrID = itor->second;

			CInstanceBase * pInstance = CPythonCharacterManager::Instance().GetInstancePtr(dwChrID);

			if (!pInstance)
				continue;

			TPixelPosition kPixelPosition;
			pInstance->NEW_GetPixelPosition(&kPixelPosition);

			CreateSpecialEffect(dwTargetID,
								+kPixelPosition.x,
								-kPixelPosition.y,
								+kPixelPosition.z,
								g_strEffectName.c_str());
		}

Add it under:
		std::map<DWORD, DWORD>::iterator itor2 = m_kMap_dwTargetID_dwChrID2.begin();
		for (; itor2 != m_kMap_dwTargetID_dwChrID2.end(); ++itor2)
		{
			DWORD dwTargetID2 = itor2->first;
			DWORD dwChrID2 = itor2->second;

			CInstanceBase * pInstance2 = CPythonCharacterManager::Instance().GetInstancePtr(dwChrID2);

			if (!pInstance2)
				continue;

			TPixelPosition kPixelPosition2;
			pInstance2->NEW_GetPixelPosition(&kPixelPosition2);

			CreateSpecialEffect(dwTargetID2,
				+kPixelPosition2.x,
				-kPixelPosition2.y,
				+kPixelPosition2.z,
				g_strEffectShopSearch.c_str());
		}

---

Search:
	m_kMap_dwTargetID_dwChrID.clear();

Add it under:
	m_kMap_dwTargetID_dwChrID2.clear();


---

Search:
void CPythonBackground::CreateTargetEffect(DWORD dwID, DWORD dwChrVID)
{
	m_kMap_dwTargetID_dwChrID.insert(make_pair(dwID, dwChrVID));
}

Add it under:
void CPythonBackground::CreateTargetEffect2(DWORD dwID, DWORD dwChrVID)
{
	m_kMap_dwTargetID_dwChrID2.insert(make_pair(dwID, dwChrVID));
}

---

Search:
void CPythonBackground::CreateTargetEffect(DWORD dwID, long lx, long ly)
{
	if (m_kMap_dwTargetID_dwChrID.end() != m_kMap_dwTargetID_dwChrID.find(dwID))
		return;

	CMapOutdoor& rkMap=GetMapOutdoorRef();

	DWORD dwBaseX;
	DWORD dwBaseY;
	rkMap.GetBaseXY(&dwBaseX, &dwBaseY);

	int ilx = +(lx-int(dwBaseX));
	int ily = -(ly-int(dwBaseY));

	float fHeight = rkMap.GetHeight(float(ilx), float(ily));

	if (0.0f == fHeight)
	{
		SReserveTargetEffect ReserveTargetEffect;
		ReserveTargetEffect.ilx = ilx;
		ReserveTargetEffect.ily = ily;
		m_kMap_dwID_kReserveTargetEffect.insert(make_pair(dwID, ReserveTargetEffect));
		return;
	}

	CreateSpecialEffect(dwID, ilx, ily, fHeight, g_strEffectName.c_str());
}

Add it under:
void CPythonBackground::CreateTargetEffect2(DWORD dwID, long lx, long ly)
{
	if (m_kMap_dwTargetID_dwChrID2.end() != m_kMap_dwTargetID_dwChrID2.find(dwID))
		return;

	CMapOutdoor& rkMap = GetMapOutdoorRef();

	DWORD dwBaseX;
	DWORD dwBaseY;
	rkMap.GetBaseXY(&dwBaseX, &dwBaseY);

	int ilx = +(lx - int(dwBaseX));
	int ily = -(ly - int(dwBaseY));

	float fHeight = rkMap.GetHeight(float(ilx), float(ily));

	if (0.0f == fHeight)
	{
		SReserveTargetEffect ReserveTargetEffect;
		ReserveTargetEffect.ilx = ilx;
		ReserveTargetEffect.ily = ily;
		m_kMap_dwID_kReserveTargetEffect.insert(make_pair(dwID, ReserveTargetEffect));
		return;
	}

	CreateSpecialEffect(dwID, ilx, ily, fHeight, g_strEffectShopSearch.c_str());
}

---

Search:
	if (m_kMap_dwTargetID_dwChrID.end() != m_kMap_dwTargetID_dwChrID.find(dwID))
	{
		m_kMap_dwTargetID_dwChrID.erase(dwID);
	}

Add it under:
	if (m_kMap_dwTargetID_dwChrID2.end() != m_kMap_dwTargetID_dwChrID2.find(dwID))
	{
		m_kMap_dwTargetID_dwChrID2.erase(dwID);
	}
