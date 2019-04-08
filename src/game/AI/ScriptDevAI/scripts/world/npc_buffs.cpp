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
 # to be removed from here (->ncp_text). This is data for database projects.
 ###*/
#define TALK_MUST_UNLEARN_WEAPON    "You must forget your weapon type specialty before I can help you. Go to Everlook in Winterspring and seek help there."

#define TALK_HAMMER_LEARN           "Ah, a seasoned veteran you once were. I know you are capable, you merely need to ask and I shall teach you the way of the hammersmith."
#define TALK_AXE_LEARN              "Ah, a seasoned veteran you once were. I know you are capable, you merely need to ask and I shall teach you the way of the axesmith."
#define TALK_SWORD_LEARN            "Ah, a seasoned veteran you once were. I know you are capable, you merely need to ask and I shall teach you the way of the swordsmith."

#define TALK_HAMMER_UNLEARN         "Forgetting your Hammersmithing skill is not something to do lightly. If you choose to abandon it you will forget all recipes that require Hammersmithing to create!"
#define TALK_AXE_UNLEARN            "Forgetting your Axesmithing skill is not something to do lightly. If you choose to abandon it you will forget all recipes that require Axesmithing to create!"
#define TALK_SWORD_UNLEARN          "Forgetting your Swordsmithing skill is not something to do lightly. If you choose to abandon it you will forget all recipes that require Swordsmithing to create!"

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

#define S_FORTITUDE               9787
#define S_WISDOM                 9788
#define S_MIGHT                17040
#define S_SALVATION                   17041
#define S_KINGS                 17039
#define S_ARCANE              9787
#define S_MARKOFTHEWILD                 9788
#define S_SPIRIT                17040


 /*###
 # specialization trainers
 ###*/

 /* Alchemy */
#define N_TRAINER_TRANSMUTE     22427 // Zarevhi
#define N_TRAINER_ELIXIR        19052 // Lorokeem
#define N_TRAINER_POTION        17909 // Lauranna Thar'well

/*###
# formulas to calculate unlearning cost
###*/

int32 GetUnlearnCostMedium(Player* pPlayer)                 // blacksmith, leatherwork
{
	uint32 level = pPlayer->getLevel();

	if (level < 51)
		return 250000;
	if (level < 66)
		return 500000;
	return 1000000;
}

int32 GetUnlearnCostLow(Player* pPlayer)                    // blacksmith
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
			case N_TRAINER_TRANSMUTE:                                //Zarevhi
					pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_CAST_FORTITUDE, GOSSIP_SENDER_LEARN, GOSSIP_ACTION_INFO_DEF + 1);
					pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_CAST_WISDOM, GOSSIP_SENDER_LEARN, GOSSIP_ACTION_INFO_DEF + 2);
          pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_CAST_SALVATION, GOSSIP_SENDER_LEARN, GOSSIP_ACTION_INFO_DEF + 3);
					pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_CAST_KINGS, GOSSIP_SENDER_LEARN, GOSSIP_ACTION_INFO_DEF + 4);
          pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_CAST_ARCANE, GOSSIP_SENDER_LEARN, GOSSIP_ACTION_INFO_DEF + 5);
					pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_CAST_MARKOFTHEWILD, GOSSIP_SENDER_LEARN, GOSSIP_ACTION_INFO_DEF + 6);
          pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_CAST_SPIRIT, GOSSIP_SENDER_ULEARN, GOSSIP_ACTION_INFO_DEF + 7);
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
		if (!pPlayer->HasSpell(S_TRANSMUTE))
		{
			pPlayer->CastSpell(pPlayer, S_LEARN_TRANSMUTE, TRIGGERED_OLD_TRIGGERED);
		}
		pPlayer->CLOSE_GOSSIP_MENU();
		break;
	case GOSSIP_ACTION_INFO_DEF + 2:
		if (!pPlayer->HasSpell(S_ELIXIR))
		{
			pPlayer->CastSpell(pPlayer, S_LEARN_ELIXIR, TRIGGERED_OLD_TRIGGERED);
		}
		pPlayer->CLOSE_GOSSIP_MENU();
		break;
	case GOSSIP_ACTION_INFO_DEF + 3:
		if (!pPlayer->HasSpell(S_POTION))
		{
			pPlayer->CastSpell(pPlayer, S_LEARN_POTION, TRIGGERED_OLD_TRIGGERED);
		}
		pPlayer->CLOSE_GOSSIP_MENU();
		break;
		//Unlearn Alchemy
	case GOSSIP_ACTION_INFO_DEF + 4:
		if (pPlayer->HasSpell(S_POTION))
		{
			//ProcessUnlearnAction(player, creature, S_UNLEARN_TRANSMUTE, 0, DoHighUnlearnCost(player));
			if (pPlayer->GetMoney() >= uint32(GetUnlearnCostLow(pPlayer)))
			{
				pPlayer->CastSpell(pPlayer, S_UNLEARN_TRANSMUTE, TRIGGERED_OLD_TRIGGERED);
				ProfessionUnlearnSpells(pPlayer, S_UNLEARN_TRANSMUTE);
				pPlayer->ModifyMoney(-GetUnlearnCostLow(pPlayer));
				pPlayer->CLOSE_GOSSIP_MENU();
			}
			else
				pPlayer->SendBuyError(BUY_ERR_NOT_ENOUGHT_MONEY, pCreature, 0, 0);
		}
		else
		{
			pPlayer->SendEquipError(EQUIP_ERR_CANT_DO_RIGHT_NOW, nullptr, nullptr);
			pPlayer->CLOSE_GOSSIP_MENU();
		}
		break;
	case GOSSIP_ACTION_INFO_DEF + 5:
		//ProcessUnlearnAction(player, creature, S_UNLEARN_ELIXIR, 0, DoHighUnlearnCost(player));
		if (pPlayer->HasSpell(S_ELIXIR))
		{
			if (pPlayer->GetMoney() >= uint32(GetUnlearnCostLow(pPlayer)))
			{
				pPlayer->CastSpell(pPlayer, S_UNLEARN_ELIXIR, TRIGGERED_OLD_TRIGGERED);
				ProfessionUnlearnSpells(pPlayer, S_UNLEARN_ELIXIR);
				pPlayer->ModifyMoney(-GetUnlearnCostLow(pPlayer));
				pPlayer->CLOSE_GOSSIP_MENU();
			}
			else
				pPlayer->SendBuyError(BUY_ERR_NOT_ENOUGHT_MONEY, pCreature, 0, 0);
		}
		else
		{
			pPlayer->SendEquipError(EQUIP_ERR_CANT_DO_RIGHT_NOW, nullptr, nullptr);
			pPlayer->CLOSE_GOSSIP_MENU();
		}
		break;
	case GOSSIP_ACTION_INFO_DEF + 6:
		//ProcessUnlearnAction(player, creature, S_UNLEARN_POTION, 0, DoHighUnlearnCost(player));
		if (pPlayer->HasSpell(S_POTION))
		{
			if (pPlayer->GetMoney() >= uint32(GetUnlearnCostLow(pPlayer)))
			{
				pPlayer->CastSpell(pPlayer, S_UNLEARN_POTION, TRIGGERED_OLD_TRIGGERED);
				ProfessionUnlearnSpells(pPlayer, S_UNLEARN_POTION);
				pPlayer->ModifyMoney(-GetUnlearnCostLow(pPlayer));
				pPlayer->CLOSE_GOSSIP_MENU();
			}
			else
				pPlayer->SendBuyError(BUY_ERR_NOT_ENOUGHT_MONEY, pCreature, 0, 0);
		}
		else
		{
			pPlayer->SendEquipError(EQUIP_ERR_CANT_DO_RIGHT_NOW, nullptr, nullptr);
			pPlayer->CLOSE_GOSSIP_MENU();
		}
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
		case N_TRAINER_TRANSMUTE:
			pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_LEARN_TRANSMUTE, GOSSIP_SENDER_CHECK, uiAction);
			//unknown textID ()
			pPlayer->SEND_GOSSIP_MENU(pPlayer->GetGossipTextId(pCreature), pCreature->GetObjectGuid());
			break;
		case N_TRAINER_ELIXIR:
			pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_LEARN_ELIXIR, GOSSIP_SENDER_CHECK, uiAction);
			//unknown textID ()
			pPlayer->SEND_GOSSIP_MENU(pPlayer->GetGossipTextId(pCreature), pCreature->GetObjectGuid());
			break;
		case N_TRAINER_POTION:
			pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_LEARN_POTION, GOSSIP_SENDER_CHECK, uiAction);
			//unknown textID ()
			pPlayer->SEND_GOSSIP_MENU(pPlayer->GetGossipTextId(pCreature), pCreature->GetObjectGuid());
			break;
		}
	}
}

void SendConfirmUnlearn_npc_prof_Alchemy(Player* pPlayer, Creature* pCreature, uint32 uiAction)
{
	if (uiAction)
	{
		uint32 eCreature = pCreature->GetEntry();
		switch (eCreature)
		{
		case N_TRAINER_TRANSMUTE:                                     //Zarevhi
			pPlayer->ADD_GOSSIP_ITEM_EXTENDED(0, GOSSIP_UNLEARN_TRANSMUTE, GOSSIP_SENDER_CHECK, uiAction, BOX_UNLEARN_ALCHEMY_SPEC, GetUnlearnCostLow(pPlayer), false);
			//unknown textID ()
			pPlayer->SEND_GOSSIP_MENU(pPlayer->GetGossipTextId(pCreature), pCreature->GetObjectGuid());
			break;
		case N_TRAINER_ELIXIR:                                     //Lorokeem
			pPlayer->ADD_GOSSIP_ITEM_EXTENDED(0, GOSSIP_UNLEARN_ELIXIR, GOSSIP_SENDER_CHECK, uiAction, BOX_UNLEARN_ALCHEMY_SPEC, GetUnlearnCostLow(pPlayer), false);
			//unknown textID ()
			pPlayer->SEND_GOSSIP_MENU(pPlayer->GetGossipTextId(pCreature), pCreature->GetObjectGuid());
			break;
			pPlayer->ADD_GOSSIP_ITEM_EXTENDED(0, GOSSIP_UNLEARN_SMITH_SPEC, GOSSIP_SENDER_CHECK, uiAction, BOX_UNLEARN_ARMORORWEAPON, GetUnlearnCostLow(pPlayer), false);
		case N_TRAINER_POTION:                                     //Lauranna Thar'well
			//AddGossipItemFor(player, 0, GOSSIP_UNLEARN_POTION, GOSSIP_SENDER_CHECK, action,    BOX_UNLEARN_ALCHEMY_SPEC, DoHighUnlearnCost(player), false);
			pPlayer->ADD_GOSSIP_ITEM_EXTENDED(0, GOSSIP_UNLEARN_POTION, GOSSIP_SENDER_CHECK, uiAction, BOX_UNLEARN_ALCHEMY_SPEC, GetUnlearnCostLow(pPlayer), false);
			//unknown textID ()
			pPlayer->SEND_GOSSIP_MENU(pPlayer->GetGossipTextId(pCreature), pCreature->GetObjectGuid());
			break;
		}


	}
}

bool GossipSelect_npc_prof_Alchemy(Player* pPlayer, Creature* pCreature, uint32 uiSender, uint32 uiAction)
{
	switch (uiSender)
	{
	case GOSSIP_SENDER_MAIN:    SendActionMenu_npc_prof_Alchemy(pPlayer, pCreature, uiAction); break;
	case GOSSIP_SENDER_LEARN:   SendConfirmLearn_npc_prof_Alchemy(pPlayer, pCreature, uiAction); break;
	case GOSSIP_SENDER_UNLEARN: SendConfirmUnlearn_npc_prof_Alchemy(pPlayer, pCreature, uiAction); break;
	case GOSSIP_SENDER_CHECK:   SendActionMenu_npc_prof_Alchemy(pPlayer, pCreature, uiAction); break;
	}
	return true;
}

/*###
# start menues blacksmith
###*/

bool HasWeaponSub(Player* pPlayer)
{
	return pPlayer->HasSpell(S_HAMMER) || pPlayer->HasSpell(S_AXE) || pPlayer->HasSpell(S_SWORD);
}

bool GossipHello_npc_prof_blacksmith(Player* pPlayer, Creature* pCreature)
{
	if (pCreature->isQuestGiver())
		pPlayer->PrepareQuestMenu(pCreature->GetObjectGuid());
	if (pCreature->isVendor())
		pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, GOSSIP_TEXT_BROWSE_GOODS, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_TRADE);
	if (pCreature->isTrainer())
		pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_TRAINER, GOSSIP_TEXT_TRAIN, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_TRAIN);

	uint32 eCreature = pCreature->GetEntry();
	// WEAPONSMITH & ARMORSMITH
	if (pPlayer->GetSkillValueBase(SKILL_BLACKSMITHING) >= 225)
	{
		switch (eCreature)
		{
		case 11145:                                     // Myolor Sunderfury
		case 11176:                                     // Krathok Moltenfist
			if (!pPlayer->HasSpell(S_ARMOR) && !pPlayer->HasSpell(S_WEAPON) && pPlayer->GetReputationRank(REP_ARMOR) == REP_FRIENDLY)
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_ARMOR_LEARN, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);
			if (!pPlayer->HasSpell(S_WEAPON) && !pPlayer->HasSpell(S_ARMOR) && pPlayer->GetReputationRank(REP_WEAPON) == REP_FRIENDLY)
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_WEAPON_LEARN, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 2);
			break;
		case 11146:                                     // Ironus Coldsteel
		case 11178:                                     // Borgosh Corebender
			if (pPlayer->HasSpell(S_WEAPON))
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_WEAPON_UNLEARN, GOSSIP_SENDER_UNLEARN, GOSSIP_ACTION_INFO_DEF + 3);
			break;
		case 5164:                                      // Grumnus Steelshaper
		case 11177:                                     // Okothos Ironrager
			if (pPlayer->HasSpell(S_ARMOR))
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_ARMOR_UNLEARN, GOSSIP_SENDER_UNLEARN, GOSSIP_ACTION_INFO_DEF + 4);
			break;
		}
	}
	// WEAPONSMITH SPEC
	if (pPlayer->HasSpell(S_WEAPON) && pPlayer->getLevel() > 49 && pPlayer->GetSkillValueBase(SKILL_BLACKSMITHING) >= 250)
	{
		switch (eCreature)
		{
		case 11191:                                     // Lilith the Lithe
			if (!HasWeaponSub(pPlayer))
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_LEARN_HAMMER, GOSSIP_SENDER_LEARN, GOSSIP_ACTION_INFO_DEF + 5);
			if (pPlayer->HasSpell(S_HAMMER))
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_UNLEARN_HAMMER, GOSSIP_SENDER_UNLEARN, GOSSIP_ACTION_INFO_DEF + 8);
			break;
		case 11192:                                     // Kilram
			if (!HasWeaponSub(pPlayer))
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_LEARN_AXE, GOSSIP_SENDER_LEARN, GOSSIP_ACTION_INFO_DEF + 6);
			if (pPlayer->HasSpell(S_AXE))
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_UNLEARN_AXE, GOSSIP_SENDER_UNLEARN, GOSSIP_ACTION_INFO_DEF + 9);
			break;
		case 11193:                                     // Seril Scourgebane
			if (!HasWeaponSub(pPlayer))
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_LEARN_SWORD, GOSSIP_SENDER_LEARN, GOSSIP_ACTION_INFO_DEF + 7);
			if (pPlayer->HasSpell(S_SWORD))
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_UNLEARN_SWORD, GOSSIP_SENDER_UNLEARN, GOSSIP_ACTION_INFO_DEF + 10);
			break;
		}
	}

	pPlayer->SEND_GOSSIP_MENU(pPlayer->GetGossipTextId(pCreature), pCreature->GetObjectGuid());
	return true;
}

void SendActionMenu_npc_prof_blacksmith(Player* pPlayer, Creature* pCreature, uint32 uiAction)
{
	switch (uiAction)
	{
	case GOSSIP_ACTION_TRADE:
		pPlayer->SEND_VENDORLIST(pCreature->GetObjectGuid());
		break;
	case GOSSIP_ACTION_TRAIN:
		pPlayer->SEND_TRAINERLIST(pCreature->GetObjectGuid());
		break;
		// Learn Armor/Weapon
	case GOSSIP_ACTION_INFO_DEF + 1:
		if (!pPlayer->HasSpell(S_ARMOR))
		{
			pPlayer->CastSpell(pPlayer, S_LEARN_ARMOR, TRIGGERED_OLD_TRIGGERED);
			// pCreature->CastSpell(pPlayer, S_REP_ARMOR, TRIGGERED_OLD_TRIGGERED);
		}
		pPlayer->CLOSE_GOSSIP_MENU();
		break;
	case GOSSIP_ACTION_INFO_DEF + 2:
		if (!pPlayer->HasSpell(S_WEAPON))
		{
			pPlayer->CastSpell(pPlayer, S_LEARN_WEAPON, TRIGGERED_OLD_TRIGGERED);
			// pCreature->CastSpell(pPlayer, S_REP_WEAPON, TRIGGERED_OLD_TRIGGERED);
		}
		pPlayer->CLOSE_GOSSIP_MENU();
		break;
		// Unlearn Armor/Weapon
	case GOSSIP_ACTION_INFO_DEF + 3:
		if (HasWeaponSub(pPlayer))
		{
			// unknown textID (TALK_MUST_UNLEARN_WEAPON)
			pPlayer->SEND_GOSSIP_MENU(pPlayer->GetGossipTextId(pCreature), pCreature->GetObjectGuid());
		}
		else if (EquippedOk(pPlayer, S_UNLEARN_WEAPON))
		{
			if (pPlayer->GetMoney() >= uint32(GetUnlearnCostLow(pPlayer)))
			{
				pPlayer->CastSpell(pPlayer, S_UNLEARN_WEAPON, TRIGGERED_OLD_TRIGGERED);
				ProfessionUnlearnSpells(pPlayer, S_UNLEARN_WEAPON);
				pPlayer->ModifyMoney(-GetUnlearnCostLow(pPlayer));
				pCreature->CastSpell(pPlayer, S_REP_ARMOR, TRIGGERED_OLD_TRIGGERED);
				pPlayer->CLOSE_GOSSIP_MENU();
			}
			else
				pPlayer->SendBuyError(BUY_ERR_NOT_ENOUGHT_MONEY, pCreature, 0, 0);
		}
		else
		{
			pPlayer->SendEquipError(EQUIP_ERR_CANT_DO_RIGHT_NOW, nullptr, nullptr);
			pPlayer->CLOSE_GOSSIP_MENU();
		}
		break;
	case GOSSIP_ACTION_INFO_DEF + 4:
		if (EquippedOk(pPlayer, S_UNLEARN_ARMOR))
		{
			if (pPlayer->GetMoney() >= uint32(GetUnlearnCostLow(pPlayer)))
			{
				pPlayer->CastSpell(pPlayer, S_UNLEARN_ARMOR, TRIGGERED_OLD_TRIGGERED);
				ProfessionUnlearnSpells(pPlayer, S_UNLEARN_ARMOR);
				pPlayer->ModifyMoney(-GetUnlearnCostLow(pPlayer));
				pCreature->CastSpell(pPlayer, S_REP_WEAPON, TRIGGERED_OLD_TRIGGERED);
			}
			else
				pPlayer->SendBuyError(BUY_ERR_NOT_ENOUGHT_MONEY, pCreature, 0, 0);
		}
		else
			pPlayer->SendEquipError(EQUIP_ERR_CANT_DO_RIGHT_NOW, nullptr, nullptr);
		pPlayer->CLOSE_GOSSIP_MENU();
		break;
		// Learn Hammer/Axe/Sword
	case GOSSIP_ACTION_INFO_DEF + 5:
		pPlayer->CastSpell(pPlayer, S_LEARN_HAMMER, TRIGGERED_OLD_TRIGGERED);
		pPlayer->CLOSE_GOSSIP_MENU();
		break;
	case GOSSIP_ACTION_INFO_DEF + 6:
		pPlayer->CastSpell(pPlayer, S_LEARN_AXE, TRIGGERED_OLD_TRIGGERED);
		pPlayer->CLOSE_GOSSIP_MENU();
		break;
	case GOSSIP_ACTION_INFO_DEF + 7:
		pPlayer->CastSpell(pPlayer, S_LEARN_SWORD, TRIGGERED_OLD_TRIGGERED);
		pPlayer->CLOSE_GOSSIP_MENU();
		break;
		// Unlearn Hammer/Axe/Sword
	case GOSSIP_ACTION_INFO_DEF + 8:
		if (EquippedOk(pPlayer, S_UNLEARN_HAMMER))
		{
			if (pPlayer->GetMoney() >= uint32(GetUnlearnCostMedium(pPlayer)))
			{
				pPlayer->CastSpell(pPlayer, S_UNLEARN_HAMMER, TRIGGERED_OLD_TRIGGERED);
				ProfessionUnlearnSpells(pPlayer, S_UNLEARN_HAMMER);
				pPlayer->ModifyMoney(-GetUnlearnCostMedium(pPlayer));
			}
			else
				pPlayer->SendBuyError(BUY_ERR_NOT_ENOUGHT_MONEY, pCreature, 0, 0);
		}
		else
			pPlayer->SendEquipError(EQUIP_ERR_CANT_DO_RIGHT_NOW, nullptr, nullptr);
		pPlayer->CLOSE_GOSSIP_MENU();
		break;
	case GOSSIP_ACTION_INFO_DEF + 9:
		if (EquippedOk(pPlayer, S_UNLEARN_AXE))
		{
			if (pPlayer->GetMoney() >= uint32(GetUnlearnCostMedium(pPlayer)))
			{
				pPlayer->CastSpell(pPlayer, S_UNLEARN_AXE, TRIGGERED_OLD_TRIGGERED);
				ProfessionUnlearnSpells(pPlayer, S_UNLEARN_AXE);
				pPlayer->ModifyMoney(-GetUnlearnCostMedium(pPlayer));
			}
			else
				pPlayer->SendBuyError(BUY_ERR_NOT_ENOUGHT_MONEY, pCreature, 0, 0);
		}
		else
			pPlayer->SendEquipError(EQUIP_ERR_CANT_DO_RIGHT_NOW, nullptr, nullptr);
		pPlayer->CLOSE_GOSSIP_MENU();
		break;
	case GOSSIP_ACTION_INFO_DEF + 10:
		if (EquippedOk(pPlayer, S_UNLEARN_SWORD))
		{
			if (pPlayer->GetMoney() >= uint32(GetUnlearnCostMedium(pPlayer)))
			{
				pPlayer->CastSpell(pPlayer, S_UNLEARN_SWORD, TRIGGERED_OLD_TRIGGERED);
				ProfessionUnlearnSpells(pPlayer, S_UNLEARN_SWORD);
				pPlayer->ModifyMoney(-GetUnlearnCostMedium(pPlayer));
			}
			else
				pPlayer->SendBuyError(BUY_ERR_NOT_ENOUGHT_MONEY, pCreature, 0, 0);
		}
		else
			pPlayer->SendEquipError(EQUIP_ERR_CANT_DO_RIGHT_NOW, nullptr, nullptr);
		pPlayer->CLOSE_GOSSIP_MENU();
		break;
	}
}

void SendConfirmLearn_npc_prof_blacksmith(Player* pPlayer, Creature* pCreature, uint32 uiAction)
{
	if (uiAction)
	{
		uint32 eCreature = pCreature->GetEntry();
		switch (eCreature)
		{
		case 11191:
			pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_LEARN_HAMMER, GOSSIP_SENDER_CHECK, uiAction);
			// unknown textID (TALK_HAMMER_LEARN)
			pPlayer->SEND_GOSSIP_MENU(pPlayer->GetGossipTextId(pCreature), pCreature->GetObjectGuid());
			break;
		case 11192:
			pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_LEARN_AXE, GOSSIP_SENDER_CHECK, uiAction);
			// unknown textID (TALK_AXE_LEARN)
			pPlayer->SEND_GOSSIP_MENU(pPlayer->GetGossipTextId(pCreature), pCreature->GetObjectGuid());
			break;
		case 11193:
			pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_LEARN_SWORD, GOSSIP_SENDER_CHECK, uiAction);
			// unknown textID (TALK_SWORD_LEARN)
			pPlayer->SEND_GOSSIP_MENU(pPlayer->GetGossipTextId(pCreature), pCreature->GetObjectGuid());
			break;
		}
	}
}

void SendConfirmUnlearn_npc_prof_blacksmith(Player* pPlayer, Creature* pCreature, uint32 uiAction)
{
	if (uiAction)
	{
		uint32 eCreature = pCreature->GetEntry();
		switch (eCreature)
		{
		case 11146:                                     // Ironus Coldsteel
		case 11178:                                     // Borgosh Corebender
		case 5164:                                      // Grumnus Steelshaper
		case 11177:                                     // Okothos Ironrager
			pPlayer->ADD_GOSSIP_ITEM_EXTENDED(0, GOSSIP_UNLEARN_SMITH_SPEC, GOSSIP_SENDER_CHECK, uiAction, BOX_UNLEARN_ARMORORWEAPON, GetUnlearnCostLow(pPlayer), false);
			// unknown textID (TALK_UNLEARN_AXEORWEAPON)
			pPlayer->SEND_GOSSIP_MENU(pPlayer->GetGossipTextId(pCreature), pCreature->GetObjectGuid());
			break;

		case 11191:
			pPlayer->ADD_GOSSIP_ITEM_EXTENDED(0, GOSSIP_UNLEARN_HAMMER, GOSSIP_SENDER_CHECK, uiAction, BOX_UNLEARN_WEAPON_SPEC, GetUnlearnCostMedium(pPlayer), false);
			// unknown textID (TALK_HAMMER_UNLEARN)
			pPlayer->SEND_GOSSIP_MENU(pPlayer->GetGossipTextId(pCreature), pCreature->GetObjectGuid());
			break;
		case 11192:
			pPlayer->ADD_GOSSIP_ITEM_EXTENDED(0, GOSSIP_UNLEARN_AXE, GOSSIP_SENDER_CHECK, uiAction, BOX_UNLEARN_WEAPON_SPEC, GetUnlearnCostMedium(pPlayer), false);
			// unknown textID (TALK_AXE_UNLEARN)
			pPlayer->SEND_GOSSIP_MENU(pPlayer->GetGossipTextId(pCreature), pCreature->GetObjectGuid());
			break;
		case 11193:
			pPlayer->ADD_GOSSIP_ITEM_EXTENDED(0, GOSSIP_UNLEARN_SWORD, GOSSIP_SENDER_CHECK, uiAction, BOX_UNLEARN_WEAPON_SPEC, GetUnlearnCostMedium(pPlayer), false);
			// unknown textID (TALK_SWORD_UNLEARN)
			pPlayer->SEND_GOSSIP_MENU(pPlayer->GetGossipTextId(pCreature), pCreature->GetObjectGuid());
			break;
		}
	}
}

bool GossipSelect_npc_prof_blacksmith(Player* pPlayer, Creature* pCreature, uint32 uiSender, uint32 uiAction)
{
	switch (uiSender)
	{
	case GOSSIP_SENDER_MAIN:    SendActionMenu_npc_prof_blacksmith(pPlayer, pCreature, uiAction); break;
	case GOSSIP_SENDER_LEARN:   SendConfirmLearn_npc_prof_blacksmith(pPlayer, pCreature, uiAction); break;
	case GOSSIP_SENDER_UNLEARN: SendConfirmUnlearn_npc_prof_blacksmith(pPlayer, pCreature, uiAction); break;
	case GOSSIP_SENDER_CHECK:   SendActionMenu_npc_prof_blacksmith(pPlayer, pCreature, uiAction); break;
	}
	return true;
}

/*bool QuestComplete_npc_prof_blacksmith(Player* pPlayer, Creature* pCreature, const Quest* pQuest)
{
	if ((pQuest->GetQuestId() == 5283) || (pQuest->GetQuestId() == 5301))             // armorsmith
		pCreature->CastSpell(pPlayer, 17451, TRIGGERED_OLD_TRIGGERED);
	if ((pQuest->GetQuestId() == 5284) || (pQuest->GetQuestId() == 5302))             // weaponsmith
		pCreature->CastSpell(pPlayer, 17452, TRIGGERED_OLD_TRIGGERED);
	return true;
}*/

/*###
# start menues leatherworking
###*/

bool GossipHello_npc_prof_leather(Player* pPlayer, Creature* pCreature)
{
	if (pCreature->isQuestGiver())
		pPlayer->PrepareQuestMenu(pCreature->GetObjectGuid());
	if (pCreature->isVendor())
		pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, GOSSIP_TEXT_BROWSE_GOODS, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_TRADE);
	if (pCreature->isTrainer())
		pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_TRAINER, GOSSIP_TEXT_TRAIN, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_TRAIN);

	uint32 eCreature = pCreature->GetEntry();

	if (pPlayer->HasSkill(SKILL_LEATHERWORKING) && pPlayer->GetSkillValueBase(SKILL_LEATHERWORKING) >= 250 && pPlayer->getLevel() > 49)
	{
		switch (eCreature)
		{
		case 7866:                                      // Peter Galen
		case 7867:                                      // Thorkaf Dragoneye
			if (pPlayer->HasSpell(S_DRAGON))
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_UNLEARN_DRAGON, GOSSIP_SENDER_UNLEARN, GOSSIP_ACTION_INFO_DEF + 1);
			break;
		case 7868:                                      // Sarah Tanner
		case 7869:                                      // Brumn Winterhoof
			if (pPlayer->HasSpell(S_ELEMENTAL))
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_UNLEARN_ELEMENTAL, GOSSIP_SENDER_UNLEARN, GOSSIP_ACTION_INFO_DEF + 2);
			break;
		case 7870:                                      // Caryssia Moonhunter
		case 7871:                                      // Se'Jib
			if (pPlayer->HasSpell(S_TRIBAL))
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_UNLEARN_TRIBAL, GOSSIP_SENDER_UNLEARN, GOSSIP_ACTION_INFO_DEF + 3);
			break;
		}
	}

	pPlayer->SEND_GOSSIP_MENU(pPlayer->GetGossipTextId(pCreature), pCreature->GetObjectGuid());
	return true;
}

void SendActionMenu_npc_prof_leather(Player* pPlayer, Creature* pCreature, uint32 uiAction)
{
	switch (uiAction)
	{
	case GOSSIP_ACTION_TRADE:
		pPlayer->SEND_VENDORLIST(pCreature->GetObjectGuid());
		break;
	case GOSSIP_ACTION_TRAIN:
		pPlayer->SEND_TRAINERLIST(pCreature->GetObjectGuid());
		break;
		// Unlearn Leather
	case GOSSIP_ACTION_INFO_DEF + 1:
		if (EquippedOk(pPlayer, S_UNLEARN_DRAGON))
		{
			if (pPlayer->GetMoney() >= uint32(GetUnlearnCostMedium(pPlayer)))
			{
				pPlayer->CastSpell(pPlayer, S_UNLEARN_DRAGON, TRIGGERED_OLD_TRIGGERED);
				ProfessionUnlearnSpells(pPlayer, S_UNLEARN_DRAGON);
				pPlayer->ModifyMoney(-GetUnlearnCostMedium(pPlayer));
			}
			else
				pPlayer->SendBuyError(BUY_ERR_NOT_ENOUGHT_MONEY, pCreature, 0, 0);
		}
		else
			pPlayer->SendEquipError(EQUIP_ERR_CANT_DO_RIGHT_NOW, nullptr, nullptr);
		pPlayer->CLOSE_GOSSIP_MENU();
		break;
	case GOSSIP_ACTION_INFO_DEF + 2:
		if (EquippedOk(pPlayer, S_UNLEARN_ELEMENTAL))
		{
			if (pPlayer->GetMoney() >= uint32(GetUnlearnCostMedium(pPlayer)))
			{
				pPlayer->CastSpell(pPlayer, S_UNLEARN_ELEMENTAL, TRIGGERED_OLD_TRIGGERED);
				ProfessionUnlearnSpells(pPlayer, S_UNLEARN_ELEMENTAL);
				pPlayer->ModifyMoney(-GetUnlearnCostMedium(pPlayer));
			}
			else
				pPlayer->SendBuyError(BUY_ERR_NOT_ENOUGHT_MONEY, pCreature, 0, 0);
		}
		else
			pPlayer->SendEquipError(EQUIP_ERR_CANT_DO_RIGHT_NOW, nullptr, nullptr);
		pPlayer->CLOSE_GOSSIP_MENU();
		break;
	case GOSSIP_ACTION_INFO_DEF + 3:
		if (EquippedOk(pPlayer, S_UNLEARN_TRIBAL))
		{
			if (pPlayer->GetMoney() >= uint32(GetUnlearnCostMedium(pPlayer)))
			{
				pPlayer->CastSpell(pPlayer, S_UNLEARN_TRIBAL, TRIGGERED_OLD_TRIGGERED);
				ProfessionUnlearnSpells(pPlayer, S_UNLEARN_TRIBAL);
				pPlayer->ModifyMoney(-GetUnlearnCostMedium(pPlayer));
			}
			else
				pPlayer->SendBuyError(BUY_ERR_NOT_ENOUGHT_MONEY, pCreature, 0, 0);
		}
		else
			pPlayer->SendEquipError(EQUIP_ERR_CANT_DO_RIGHT_NOW, nullptr, nullptr);
		pPlayer->CLOSE_GOSSIP_MENU();
		break;
	}
}

void SendConfirmUnlearn_npc_prof_leather(Player* pPlayer, Creature* pCreature, uint32 uiAction)
{
	if (uiAction)
	{
		uint32 eCreature = pCreature->GetEntry();
		switch (eCreature)
		{
		case 7866:                                      // Peter Galen
		case 7867:                                      // Thorkaf Dragoneye
			pPlayer->ADD_GOSSIP_ITEM_EXTENDED(0, GOSSIP_UNLEARN_DRAGON, GOSSIP_SENDER_CHECK, uiAction, BOX_UNLEARN_LEATHER_SPEC, GetUnlearnCostMedium(pPlayer), false);
			// unknown textID ()
			pPlayer->SEND_GOSSIP_MENU(pPlayer->GetGossipTextId(pCreature), pCreature->GetObjectGuid());
			break;
		case 7868:                                      // Sarah Tanner
		case 7869:                                      // Brumn Winterhoof
			pPlayer->ADD_GOSSIP_ITEM_EXTENDED(0, GOSSIP_UNLEARN_ELEMENTAL, GOSSIP_SENDER_CHECK, uiAction, BOX_UNLEARN_LEATHER_SPEC, GetUnlearnCostMedium(pPlayer), false);
			// unknown textID ()
			pPlayer->SEND_GOSSIP_MENU(pPlayer->GetGossipTextId(pCreature), pCreature->GetObjectGuid());
			break;
		case 7870:                                      // Caryssia Moonhunter
		case 7871:                                      // Se'Jib
			pPlayer->ADD_GOSSIP_ITEM_EXTENDED(0, GOSSIP_UNLEARN_TRIBAL, GOSSIP_SENDER_CHECK, uiAction, BOX_UNLEARN_LEATHER_SPEC, GetUnlearnCostMedium(pPlayer), false);
			// unknown textID ()
			pPlayer->SEND_GOSSIP_MENU(pPlayer->GetGossipTextId(pCreature), pCreature->GetObjectGuid());
			break;
		}
	}
}

bool GossipSelect_npc_prof_leather(Player* pPlayer, Creature* pCreature, uint32 uiSender, uint32 uiAction)
{
	switch (uiSender)
	{
	case GOSSIP_SENDER_MAIN:    SendActionMenu_npc_prof_leather(pPlayer, pCreature, uiAction); break;
	case GOSSIP_SENDER_UNLEARN: SendConfirmUnlearn_npc_prof_leather(pPlayer, pCreature, uiAction); break;
	case GOSSIP_SENDER_CHECK:   SendActionMenu_npc_prof_leather(pPlayer, pCreature, uiAction); break;
	}
	return true;
}

/*###
# start menues for GO (engineering and leatherworking)
###*/

/*bool GOUse_go_soothsaying_for_dummies(Player* pPlayer, GameObject* pGo)
{
	pPlayer->PlayerTalkClass->GetGossipMenu()->AddMenuItem(0,GOSSIP_LEARN_DRAGON, GOSSIP_SENDER_INFO, GOSSIP_ACTION_INFO_DEF, "", 0);
	pPlayer->SEND_GOSSIP_MENU(5584, pGo->GetObjectGuid());
	return true;
}*/

/*###
#
###*/

void AddSC_npc_professions()
{
	Script* pNewScript = new Script;
	pNewScript->Name = "npc_prof_blacksmith";
	pNewScript->pGossipHello = &GossipHello_npc_prof_blacksmith;
	pNewScript->pGossipSelect = &GossipSelect_npc_prof_blacksmith;
	pNewScript->RegisterSelf();

	pNewScript = new Script;
	pNewScript->Name = "npc_prof_leather";
	pNewScript->pGossipHello = &GossipHello_npc_prof_leather;
	pNewScript->pGossipSelect = &GossipSelect_npc_prof_leather;
	pNewScript->RegisterSelf();

	pNewScript = new Script;
	pNewScript->Name = "npc_prof_Alchemy";
	pNewScript->pGossipHello = &GossipHello_npc_prof_Alchemy;
	pNewScript->pGossipSelect = &GossipSelect_npc_prof_Alchemy;
	pNewScript->RegisterSelf();

	/*pNewScript = new Script;
	pNewScript->Name = "go_soothsaying_for_dummies";
	pNewScript->pGOUse =  &GOUse_go_soothsaying_for_dummies;
	// pNewScript->pGossipSelect = &GossipSelect_go_soothsaying_for_dummies;
	pNewScript->RegisterSelf();*/
}
