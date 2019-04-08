/* This file is part of the ScriptDev2 Project. See AUTHORS file for Copyright information
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

 /* ScriptData
 SDName: Npc_buffs
 SD%Complete: 
 SDComment:
 SDCategory: NPCs
 EndScriptData */

#include "AI/ScriptDevAI/include/precompiled.h"


 /*###
 # generic defines
 ###*/

#define GOSSIP_SENDER_LEARN         50
#define GOSSIP_SENDER_UNLEARN       51
#define GOSSIP_SENDER_CHECK         52

 /*###
 # gossip item and box texts
 ###*/

#define GOSSIP_CAST_FORTITUDE         "I wish to have the fortitude buff"
#define GOSSIP_CAST_WISDOM       "I wish to have the wisdom buff"
#define GOSSIP_CAST_MIGHT      "I wish to have the might buff"
#define GOSSIP_CAST_SALVATION    "I wish to have the salvation buff"
#define GOSSIP_CAST_KINGS       "I wish to have the kings buff"
#define GOSSIP_CAST_ARCANE       "I wish to have the arcane brilliance buff"
#define GOSSIP_CAST_MARKOFTHEWILD       "I wish to have the mark of the wild buff"
#define GOSSIP_CAST_SPIRIT       "I wish to have the spirit buff"

 /*###
 # spells defines
 ###*/

#define S_FORTITUDE             23948
#define S_WISDOM                25290
#define S_MIGHT               	25291
#define S_SALVATION             1038
#define S_KINGS                 20217
#define S_ARCANE              	16876
#define S_MARKOFTHEWILD         9885
#define S_SPIRIT                27841

 /* Buff NPC */
#define N_BUFFNPC     98000 


/*###
# formulas to calculate buff cost
###*/

int32 GetBuffCostMedium(Player* pPlayer)           
{
	uint32 level = pPlayer->getLevel();

	if (level < 51)
		return 250000;
	if (level < 66)
		return 500000;
	return 1000000;
}

int32 GetBuffCostCostLow(Player* pPlayer)                  
{
	if (pPlayer->getLevel() < 66)
		return 50000;
	return 100000;
}


/* #Buffs##*/
inline bool IsLevel70(Player* pPlayer)
{
	if (pPlayer->getLevel() == 70)
		return;

}

bool GossipHello_npc_buffs(Player* pPlayer, Creature* pCreature)
{
	if (pCreature->isQuestGiver())
		pPlayer->PrepareQuestMenu(pCreature->GetObjectGuid());
	if (pCreature->isVendor())
		pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, GOSSIP_TEXT_BROWSE_GOODS, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_TRADE);
	if (pCreature->isTrainer())
		pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_TRAINER, GOSSIP_TEXT_TRAIN, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_TRAIN);
	uint32 eCreature = pCreature->GetEntry();

	if (pPlayer->getLevel() == 70)
	{
			switch (eCreature)
			{
			case N_BUFFNPC:                              
					pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_CAST_FORTITUDE, GOSSIP_SENDER_LEARN, GOSSIP_ACTION_INFO_DEF + 1);
					pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_CAST_WISDOM, GOSSIP_SENDER_LEARN, GOSSIP_ACTION_INFO_DEF + 2);
          				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_CAST_MIGHT, GOSSIP_SENDER_LEARN, GOSSIP_ACTION_INFO_DEF + 3);
					pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_CAST_SALVATION, GOSSIP_SENDER_LEARN, GOSSIP_ACTION_INFO_DEF + 4);
          				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_CAST_KINGS, GOSSIP_SENDER_LEARN, GOSSIP_ACTION_INFO_DEF + 5);
					pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_CAST_ARCANE, GOSSIP_SENDER_LEARN, GOSSIP_ACTION_INFO_DEF + 6);
          				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_CAST_MARKOFTHEWILD, GOSSIP_SENDER_ULEARN, GOSSIP_ACTION_INFO_DEF + 7);
					pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_CAST_SPIRIT, GOSSIP_SENDER_ULEARN, GOSSIP_ACTION_INFO_DEF + 8);
				break;
			}
	}
	pPlayer->SEND_GOSSIP_MENU(pPlayer->GetGossipTextId(pCreature), pCreature->GetObjectGuid());
	return true;
}

void SendActionMenu_npc_buffs(Player* pPlayer, Creature* pCreature, uint32 uiAction)
{
	switch (uiAction)
	{
	case GOSSIP_ACTION_TRADE:
		pPlayer->SEND_VENDORLIST(pCreature->GetObjectGuid());
		break;
	case GOSSIP_ACTION_TRAIN:
		pPlayer->SEND_TRAINERLIST(pCreature->GetObjectGuid());
		break;
		//Casted spells
	case GOSSIP_ACTION_INFO_DEF + 1:
		pPlayer->CastSpell(pPlayer, S_FORTITUDE, TRIGGERED_OLD_TRIGGERED);
		pPlayer->CLOSE_GOSSIP_MENU();
		break;
	case GOSSIP_ACTION_INFO_DEF + 2:
		pPlayer->CastSpell(pPlayer, S_WISDOM, TRIGGERED_OLD_TRIGGERED);
		pPlayer->CLOSE_GOSSIP_MENU();
		break;
	case GOSSIP_ACTION_INFO_DEF + 3:
		Player->CastSpell(pPlayer, S_MIGHT, TRIGGERED_OLD_TRIGGERED);
		pPlayer->CLOSE_GOSSIP_MENU();
		break;
	case GOSSIP_ACTION_INFO_DEF + 4:
		pPlayer->CastSpell(pPlayer, S_SALVATION, TRIGGERED_OLD_TRIGGERED);
		pPlayer->CLOSE_GOSSIP_MENU();
		break;
	case GOSSIP_ACTION_INFO_DEF + 5:
		pPlayer->CastSpell(pPlayer, S_KINGS, TRIGGERED_OLD_TRIGGERED);
		pPlayer->CLOSE_GOSSIP_MENU();
		break;
	case GOSSIP_ACTION_INFO_DEF + 6:
		pPlayer->CastSpell(pPlayer, S_ARCANE, TRIGGERED_OLD_TRIGGERED);
		pPlayer->CLOSE_GOSSIP_MENU();
		break;
	case GOSSIP_ACTION_INFO_DEF + 7:
		pPlayer->CastSpell(pPlayer, S_MARKOFTHEWILD, TRIGGERED_OLD_TRIGGERED);
		pPlayer->CLOSE_GOSSIP_MENU();
		break;
	case GOSSIP_ACTION_INFO_DEF + 8:
		pPlayer->CastSpell(pPlayer, S_SPIRIT, TRIGGERED_OLD_TRIGGERED);
		pPlayer->CLOSE_GOSSIP_MENU();
		break;
	}
}

void SendConfirmLearn_npc_buffs(Player* pPlayer, Creature* pCreature, uint32 uiAction)
{
	if (uiAction)
	{
		//uint32 eCreature = pCreature->GetEntry();
		switch (pCreature->GetEntry())
		{
		case N_BUFFNPC:
			pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_CAST_FORTITUDE, GOSSIP_SENDER_CHECK, uiAction);
			pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_CAST_WISDOM, GOSSIP_SENDER_CHECK, uiAction);
			pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_CAST_MIGHT, GOSSIP_SENDER_CHECK, uiAction);
			pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_CAST_SALVATION, GOSSIP_SENDER_CHECK, uiAction);
			pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_CAST_KINGS, GOSSIP_SENDER_CHECK, uiAction);
			pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_CAST_ARCANE, GOSSIP_SENDER_CHECK, uiAction);
			pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_CAST_MARKOFTHEWILD, GOSSIP_SENDER_CHECK, uiAction);
			pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_CAST_SPIRIT, GOSSIP_SENDER_CHECK, uiAction);
			//unknown textID ()
			pPlayer->SEND_GOSSIP_MENU(pPlayer->GetGossipTextId(pCreature), pCreature->GetObjectGuid());
			break;
		}
	}
}


bool GossipSelect_npc_buffs(Player* pPlayer, Creature* pCreature, uint32 uiSender, uint32 uiAction)
{
	switch (uiSender)
	{
	case GOSSIP_SENDER_MAIN:    SendActionMenu_npc_buffs(pPlayer, pCreature, uiAction); break;
	case GOSSIP_SENDER_LEARN:   SendConfirmLearn_npc_buffs(pPlayer, pCreature, uiAction); break;
	case GOSSIP_SENDER_UNLEARN: SendConfirmUnlearn_npc_buffs(pPlayer, pCreature, uiAction); break;
	case GOSSIP_SENDER_CHECK:   SendActionMenu_npc_buffs(pPlayer, pCreature, uiAction); break;
	}
	return true;
}


void AddSC_npc_professions()
{
	Script* pNewScript = new Script;
	pNewScript->Name = "npc_buffs";
	pNewScript->pGossipHello = &GossipHello_npc_buffs;
	pNewScript->pGossipSelect = &GossipSelect_npc_buffs;
	pNewScript->RegisterSelf();

}
