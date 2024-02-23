modded class MissionBase {
	
	void MissionBase()
	{
		GetRPCManager().AddRPC("BarterMod", "RPCBuy", this, SingleplayerExecutionType.Both);
	}
	
	int ReadPlayerBarterLevel(string fileName) {
		FileHandle file = OpenFile(fileName, FileMode.READ);
		
		if (file != 0) {
			string currentLevel;
			
			if (FGets(file, currentLevel)) {
				int barterLevel = currentLevel.ToInt();
				CloseFile(file);
				return barterLevel;
			}
			CloseFile(file);
		}
		return 0; 
	}

	bool WritePlayerBarterLevel(string fileName, int barterLevel) {
		PlayerBase player = PlayerBase.Cast(GetGame().GetPlayer());
		FileHandle file = OpenFile(fileName, FileMode.WRITE);
		
		if (file != 0) {
			FPrint(file, barterLevel);
			CloseFile(file);
			return true;
		}
		return false;
	}
	
	bool ManagePlayerBarterLevel(string steamID, int skillIncrement) {
		
		string fileFolder = BARTER_LEVEL_FOLDER;
		
		if (!FileExist(fileFolder)) {
			if (!MakeDirectory(fileFolder)) {
				Print("BARTER: Failed to make directory!");
				return false;
			}
		}
		
		string fileName = fileFolder + steamID + ".txt";

		if (FileExist(fileName)) {
			int barterLevel = ReadPlayerBarterLevel(fileName);
			
			if (barterLevel == 0) {
				Print("BARTER: The reading of the skill file FAILED");
				return false;
			}

			barterLevel += skillIncrement;

			if (WritePlayerBarterLevel(fileName, barterLevel)) {
				return true;
			} else {
				Print("BARTER: Failed to update skill level for " + steamID);
				return false;
			}
		} else {
			if (WritePlayerBarterLevel(fileName, 1)) {
				return true;
			} else {
				Print("BARTER: Failed to create skill level file for " + steamID);
				return true;
			}
		}
	}
	
	int FindRequiredItemIndex(ItemBase item, ref array<ref RequiredItem> requiredItems) {
		for (int i = 0; i < requiredItems.Count(); i++) {
			if (requiredItems[i].itemName == item.GetType()) {
				return i;
			}
		}
		return -1; 
	}
	
	bool IsItemOnPlayer(PlayerBase player, BarterItem barterItem) {
		array<EntityAI> itemsArray = new array<EntityAI>;
		map<string, float> itemQuantities = new map<string, float>;

		if (player.GetInventory().EnumerateInventory(1, itemsArray)) {
			foreach (EntityAI itemEntity : itemsArray) {
				ItemBase item;
				
				if (ItemBase.CastTo(item, itemEntity)) {

					string itemType = item.GetType();
					if (item.HasQuantity()) {
						float currentQuantity = item.GetQuantity();
						if (itemQuantities.Contains(itemType)) {
							itemQuantities[itemType] = itemQuantities[itemType] + currentQuantity;
						} else {
							itemQuantities[itemType] = currentQuantity;
						}
					} else {
						if (itemQuantities.Contains(itemType)) {
							itemQuantities[itemType] = itemQuantities[itemType] + 1;
						} else {
							itemQuantities[itemType] = 1;
						}
					}
				}
			}
		}

		foreach (RequiredItem requiredItem : barterItem.requiredItems) {
			if (!itemQuantities.Contains(requiredItem.itemName) || itemQuantities[requiredItem.itemName] < requiredItem.quantity) {
				return false;
			}
		}

		foreach (RequiredItem rqrItem : barterItem.requiredItems) {
			float quantityToRemove = rqrItem.quantity;
			bool ruinedItem = false;
			
			foreach (EntityAI entityItem : itemsArray) {
				ItemBase itemBase;
				if (ItemBase.CastTo(itemBase, entityItem) && itemBase.GetType() == rqrItem.itemName) {
					if (itemBase.IsRuined()) {
						ruinedItem = true;
						ExpansionNotification("Barter", "One of the recipe items was ruined!").Error(player.GetIdentity());
						break;
					}
					
					if (itemBase.HasQuantity()) {
						float itemQuantity = itemBase.GetQuantity();
						if (itemQuantity >= quantityToRemove) {
							itemBase.SetQuantity(itemQuantity - quantityToRemove);
							break;
						} else {
							quantityToRemove -= itemQuantity;
							GetGame().ObjectDelete(itemBase);
						}
					} else if (quantityToRemove > 0) {
						GetGame().ObjectDelete(itemBase);
						quantityToRemove--;
					}
				}
			}
		}
		
		if (ruinedItem)
			return false;

		return true;
	}


	
	EntityAI createEntity(string entityName) {
		EntityAI entity = EntityAI.Cast(GetGame().CreateObject(entityName, "0 0 0", true, false, true));
		return entity;
	}
	
	void RPCBuy(CallType type, ref ParamsReadContext ctx, ref PlayerIdentity sender, ref Object target) {
		if (type == CallType.Server) {
			Param2<PlayerBase, ref BarterItem> data;
			
			if (!ctx.Read(data)) {
				return;
			}
			
			PlayerBase player = data.param1;
			BarterItem barterItem = data.param2;
			
			if (player && barterItem) {
				bool hasItem = IsItemOnPlayer(player, barterItem);
				
				if (hasItem) {
					
					
					foreach (FinalItem finalItem : barterItem.finalProducts) {
						EntityAI finalEntity = createEntity(finalItem.itemName);
						
						bool inventoryNotFull = player.GetInventory().CanAddEntityToInventory(finalEntity);
						
						if (inventoryNotFull) {
							ItemBase finalBase;
							if (Class.CastTo(finalBase, finalEntity));

							if (finalBase.HasQuantity()) {
								finalBase = player.GetInventory().CreateInInventory(finalItem.itemName);
								finalBase.SetQuantity(finalItem.quantity);
							} else {
								for (int i = 0; i < finalItem.quantity; i++) {
									player.GetInventory().CreateInInventory(finalItem.itemName);
								}
							}							
						} else {
							player.SpawnEntityOnGroundPos(finalItem.itemName, player.GetPosition());
						}
					}
					string steamID = player.GetIdentity().GetPlainId();
					int skillIncrement = 1;
					
					if (ManagePlayerBarterLevel(steamID, skillIncrement)) {
						player.setBarterLevel(player.getBarterLevel() + skillIncrement);
						GetRPCManager().SendRPC("BarterMod", "RPCUpdateLevelText", new Param1<int>(player.getBarterLevel()), true, sender);
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