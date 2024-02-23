
class NPCList {
	ref array<BarterNPC> barterNPCList;
}

class BarterNPC {
	int id;
	string npcModel;
	int barterRequirement;
	bool VIP;
	vector position;
	vector orientation;
	ref array<string> npcClothing;
}

class NPCManager
{
	ref NPCList npcList;
	
	private PlayerBase tempNpc;
	private vector tempPosition;

    void NPCManager()
    {
		npcList = new NPCList;
		LoadBarterConfig();
    }

    void ~NPCManager()
    {
    }
	
	void CreateNPCClothing(PlayerBase npc, array<string> clothingStrings) {
		foreach (string clothingString : clothingStrings) {
			EntityAI clothingEntity = EntityAI.Cast(npc.GetInventory().CreateInInventory(clothingString));
		}
	}
	
	void LoadBarterConfig() {
		string filePath = BARTER_RECIPE_FOLDER + "NPCConfig.json";
		
		if (FileExist(filePath) && FileExist(BARTER_RECIPE_FOLDER)) {
			JsonFileLoader<NPCList>.JsonLoadFile(filePath, npcList);
			Print("BARTER: NPC JSON FILE LOADED");
		} else {
			MakeDirectory(BARTER_RECIPE_FOLDER);
			JsonFileLoader<NPCList>.JsonSaveFile(filePath, npcList);
			Print("BARTER: NPC JSON FILE SAVED");
		}
	
		SpawnNPC();
	}

    void SpawnNPC()
    {
        if (GetGame().IsServer())
        {
			
			foreach (BarterNPC barterNpc : npcList.barterNPCList) {
				tempNpc = PlayerBase.Cast(GetGame().CreateObject(barterNpc.npcModel, barterNpc.position, false, false));
				tempNpc.SetOrientation(barterNpc.orientation);
				CreateNPCClothing(tempNpc, barterNpc.npcClothing);
				tempNpc.setTraderStatus();
				tempNpc.SetAllowDamage(false);
				tempNpc.setTraderID(barterNpc.id);
				tempNpc.setTraderVIP(barterNpc.VIP);
				tempNpc.setBarterRequirement(barterNpc.barterRequirement);
			}
			
        }
    }
}
