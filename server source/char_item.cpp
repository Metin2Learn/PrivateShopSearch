Search:
							case 27996: // µ¶º´
								item->SetCount(item->GetCount() - 1);
								/*if (GetSkillLevel(SKILL_CREATE_POISON))
								  AddAffect(AFFECT_ATT_GRADE, POINT_ATT_GRADE, 3, AFF_DRINK_POISON, 15*60, 0, true);
								  else
								  {
								// µ¶´Ù·ç±â°¡ ¾øÀ¸¸é 50% Áï»ç 50% °ø°İ·Â +2
								if (number(0, 1))
								{
								if (GetHP() > 100)
								PointChange(POINT_HP, -(GetHP() - 1));
								else
								Dead();
								}
								else
								AddAffect(AFFECT_ATT_GRADE, POINT_ATT_GRADE, 2, AFF_DRINK_POISON, 15*60, 0, true);
								}*/
								break;

Add in under:
							case 60004:
								ChatPacket(CHAT_TYPE_COMMAND, "OpenShopSearchGUI");
								ChatPacket(CHAT_TYPE_COMMAND, "SetShopSearchType 1");
								break;

							case 60005:
								ChatPacket(CHAT_TYPE_COMMAND, "OpenShopSearchGUI");
								ChatPacket(CHAT_TYPE_COMMAND, "SetShopSearchType 2");
								break;

							case 60006:
								ChatPacket(CHAT_TYPE_COMMAND, "OpenShopSearchGUI");
								ChatPacket(CHAT_TYPE_COMMAND, "SetShopSearchType 3");
								break;

