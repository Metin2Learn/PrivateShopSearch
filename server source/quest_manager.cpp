Search:
			TargetInfo * pInfo = CTargetManager::instance().GetTargetInfo(pc, TARGET_TYPE_VID, pkChrTarget->GetVID());
			if (test_server)
			{
				sys_log(0, "CQuestManager::Click(pid=%d, npc_name=%s) - target_info(%x)", pc, pkChrTarget->GetName(), pInfo);
			}

			if (pInfo)
			{
				bool bRet;
				if (m_mapNPC[QUEST_NO_NPC].OnTarget(*pPC, pInfo->dwQuestIndex, pInfo->szTargetName, "click", bRet))
					return bRet;
			}

			DWORD dwCurrentNPCRace = pkChrTarget->GetRaceNum();

Change:
			TargetInfo * pInfo = CTargetManager::instance().GetTargetInfo(pc, TARGET_TYPE_VID, pkChrTarget->GetVID());
			if (test_server)
			{
				sys_log(0, "CQuestManager::Click(pid=%d, npc_name=%s) - target_info(%x)", pc, pkChrTarget->GetName(), pInfo);
			}

			if (pInfo)
			{
				if (pkChrTarget->IsPC())
					if (pkChrTarget->GetMyShop())
						CTargetManager::instance().DeleteTarget(pc, 3169, "SHOPSEARCH_TARGET");

				bool bRet;
				if (m_mapNPC[QUEST_NO_NPC].OnTarget(*pPC, pInfo->dwQuestIndex, pInfo->szTargetName, "click", bRet))
					return bRet;
			}

			DWORD dwCurrentNPCRace = pkChrTarget->GetRaceNum();

