modded class MissionBase {
	
	void MissionBase()
	{
		GetRPCManager().AddRPC("BarterMod", "RPCBuy", this, SingleplayerExecutionType.Both);
	}
	
	int ReadPlayerSkillLevel(string fileName) {
		FileHandle file = OpenFile(fileName, FileMode.READ);
		if (file != 0) {
			string currentLevel;
			
			if (FGets(file, currentLevel)) {
				int skillLevel = currentLevel.ToInt();
				CloseFile(file);
				return skillLevel;
			}
			CloseFile(file);
		}
		return 0; 
	}

	bool WritePlayerSkillLevel(string fileName, int skillLevel) {
		PlayerBase player = PlayerBase.Cast(GetGame().GetPlayer());
		FileHandle file = OpenFile(fileName, FileMode.WRITE);
		if (file != 0) {
			FPrint(file, skillLevel);
			CloseFile(file);
			return true;
		}
		return false;
	}
	
	bool ManagePlayerSkillLevel(string steamID, int skillIncrement) {
		
		string fileFolder = SKILLDATA_FOLDER;
		
		if (!FileExist(fileFolder)) {
			if (!MakeDirectory(fileFolder)) {
				Print("BARTER: Failed to make directory!");
				return false;
			}
		}
		
		string fileName = fileFolder + steamID + ".txt";

		if (FileExist(fileName)) {
			int currentSkillLevel = ReadPlayerSkillLevel(fileName);
			
			if (currentSkillLevel == 0) {
				Print("BARTER: The reading of the skill file FAILED");
				return false;
			}

			currentSkillLevel += skillIncrement;

			if (WritePlayerSkillLevel(fileName, currentSkillLevel)) {
				return true;
			} else {
				Print("BARTER: Failed to update skill level for " + steamID);
				return false;
			}
		} else {
			if (WritePlayerSkillLevel(fileName, 1)) {
				return true;
			} else {
				Print("BARTER: Failed to create skill level file for " + steamID);
				return true;
			}
		}
	}
	
	bool IsItemOnPlayer(PlayerBase player, array<string> recipeStrings, out array<EntityAI> removableObjects) {
		array<EntityAI> items = new array<EntityAI>;
		
		if (player.GetInventory().EnumerateInventory(1, items)) {
			foreach (EntityAI item : items) {
				int index = recipeStrings.Find(item.GetType());
				
				if (index != -1) { 
					if (item.IsRuined()) {
						ExpansionNotification("Barter", "One of the recipe items was ruined!").Error(player.GetIdentity());
						return false;
					}
					removableObjects.Insert(item); 
					recipeStrings.RemoveOrdered(index); 
				}
			}
		}
		return recipeStrings.Count() == 0; 
	}
	
	EntityAI createEntity(string entityName) {
		EntityAI entity = EntityAI.Cast(GetGame().CreateObject(entityName, "0 0 0", true, false, true));
		return entity;
	}
	
	void RPCBuy(CallType type, ref ParamsReadContext ctx, ref PlayerIdentity sender, ref Object target) {
		if (type == CallType.Server) {
			Param3<PlayerBase, array<string>, string> data;
			
			if (!ctx.Read(data)) {
				return;
			}
			
			PlayerBase player = data.param1;
			array<string> SrecipeEntities = data.param2;
			string SfinalProduct = data.param3;
			
			if (player) {
				
				array<EntityAI> removableObjects = new array<EntityAI>;
				
				bool hasItem = IsItemOnPlayer(player, SrecipeEntities, removableObjects);
				
				if (hasItem) {
					
					foreach (EntityAI itemToDelete : removableObjects) {
						GetGame().ObjectDelete(itemToDelete);
					}
					
					EntityAI finalProduct = createEntity(SfinalProduct);
					bool inventoryNotFull = player.GetInventory().CanAddEntityToInventory(finalProduct);
					
					if (inventoryNotFull) {
						EntityAI finalProductEntity = player.GetInventory().CreateInInventory(SfinalProduct);
					} else {
						player.SpawnEntityOnGroundPos(SfinalProduct, player.GetPosition());
					}
					
					string steamID = player.GetIdentity().GetId();
					int skillIncrement = 1;
					
					if (ManagePlayerSkillLevel(steamID, skillIncrement)) {
						player.m_currentSkillLevel += 1;
						GetRPCManager().SendRPC("BarterMod", "RPCUpdateLevelText", new Param1<int>(player.m_currentSkillLevel), true, sender);
					}
					
					ExpansionNotification("Barter", "Successful barter").Success(player.GetIdentity());
				} else {
					ExpansionNotification("Barter", "You don't have the items needed for this barter.").Error(player.GetIdentity());
				}
			}
		}
	}
		
    override UIScriptedMenu CreateScriptedMenu(int id) {
        UIScriptedMenu menu = NULL;
        menu = super.CreateScriptedMenu(id);
        if (!menu) {
            switch (id) {
            case BARTER_UI:
                menu = new BarterUI;
                break;
            }
            if (menu) {
                menu.SetID(id);
            }
        }
        return menu;
    }
}