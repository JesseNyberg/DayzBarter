modded class MissionBase {
	
	void MissionBase()
	{
		GetRPCManager().AddRPC("BarterMod", "RPCBuy", this, SingleplayerExecutionType.Both);
		// GetRPCManager().AddRPC("BarterMod", "RPCBarterLevelUp", this, SingleplayerExecutionType.Both);
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

	// Function to write the player's skill level to a file
	bool WritePlayerSkillLevel(string fileName, int skillLevel) {
		PlayerBase player = PlayerBase.Cast(GetGame().GetPlayer());
		FileHandle file = OpenFile(fileName, FileMode.WRITE);
		if (file != 0) {
			FPrint(file, skillLevel);
			CloseFile(file);
			return true;
		}
		return false; // Return false if the file can't be written
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

		// Check if the file exists
		if (FileExist(fileName)) {
			// File exists, read the current skill level
			int currentSkillLevel = ReadPlayerSkillLevel(fileName);
			
			if (currentSkillLevel == 0) {
				Print("BARTER: The reading of the skill file FAILED");
				return false;
			}

			// Increment the skill level
			currentSkillLevel += skillIncrement;

			// Save the updated skill level back to the file
			if (WritePlayerSkillLevel(fileName, currentSkillLevel)) {
				Print("BARTER: Skill level incremented for " + steamID + ". New skill level: " + currentSkillLevel);
				return true;
			} else {
				Print("BARTER: Failed to update skill level for " + steamID);
				return false;
			}
		} else {
			// File doesn't exist, create it with an initial value of 1
			if (WritePlayerSkillLevel(fileName, 1)) {
				Print("BARTER: Skill level file created for " + steamID + ". Initial skill level: 1");
				return true;
			} else {
				Print("BARTER: Failed to create skill level file for " + steamID);
				return true;
			}
		}
	}
	
	bool IsItemOnPlayer(PlayerBase player, string recipeProduct, out array<EntityAI> removableObjects) 
	{
		array<EntityAI> items = new array<EntityAI>;
    
		if(player.GetInventory().EnumerateInventory(1,items)) {    
			for(int i = 0; i < items.Count(); i++) {
				EntityAI item = items.Get(i);
				if(item.GetType() == recipeProduct) {
					if (item.IsRuined())
					{
						player.MessageImportant("One of the recipe items was ruined!");
						continue; 
					}
					removableObjects.Insert(item);
					return true;
				}
			}
		}
		return false;
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
			
			Print("BARTER: RPCBuy is started");

			PlayerBase player = data.param1;
			array<string> SrecipeEntities = data.param2;
			string SfinalProduct = data.param3;
			

			if (player) {
				Print("BARTER: if player");
				
				array<EntityAI> removableObjects = new array<EntityAI>;
				
				foreach (string itemRecipeString : SrecipeEntities) {
					if (itemRecipeString) {
						bool hasItem = IsItemOnPlayer(player, itemRecipeString, removableObjects);
						Print("BARTER: has item is " + hasItem);
					}
				}

				if (removableObjects.Count() == SrecipeEntities.Count()) {
					Print("BARTER: Player has the items needed for buying");
					
					foreach (EntityAI itemToDelete : removableObjects) {
						GetGame().ObjectDelete(itemToDelete);
					}
					
					player.GetInventory().CreateInInventory(SfinalProduct);
					
					string steamID = player.GetIdentity().GetId();
					int skillIncrement = 1;
					if (ManagePlayerSkillLevel(steamID, skillIncrement)) {
						player.m_currentSkillLevel += 1;
					}
					//player.MessageFriendly("You successfully traded " + SrecipeProduct1 + " and " + SrecipeProduct2 + " for " + SfinalProduct + "!");
				} else {
					player.MessageImportant("You don't have the items necessary for this trade!");
					Print("BARTER: Player doesn't have the items needed for buying");
				}
			}
		}
	}
	
/* 	void RPCBarterLevelUp(CallType type, ref ParamsReadContext ctx, ref PlayerIdentity sender, ref Object target) {
		if (type == CallType.Server) {
			Param1<PlayerBase> data;
			
			if (!ctx.Read(data)) {
				return;
			}
			
			Print("BARTER: RPCArtifact started");
			
			PlayerBase player = data.param1;
			
			if (player) {
				string artifactClassName = "Potato";
				
				array<EntityAI> removableObjects = new array<EntityAI>;

				bool hasArtifact = IsItemOnPlayer(player, artifactClassName, removableObjects);
				
				if (hasArtifact) {
					Print("BARTER: Player has the artifact");
					foreach (EntityAI item : removableObjects) {
						GetGame().ObjectDelete(item);
					}
					string steamID = player.GetIdentity().GetId();
					int skillIncrement = 1; // Change this as needed
					ManagePlayerSkillLevel(steamID, skillIncrement);
					player.m_currentSkillLevel += 1;
				} else {
					Print("BARTER: Artifact not found in inventory");
				}
				
				
			}
			
		}
	} */
	
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