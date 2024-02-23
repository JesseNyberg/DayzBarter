modded class MissionServer
{
    ref NPCManager m_NPCManager; 
	ref BartererList bartererList;

    override void OnInit()
    {
        super.OnInit();
        
        m_NPCManager = new NPCManager();
		
		Print("BARTER: MissionServer initialized!");
		
		bartererList = new BartererList();
		GetRPCManager().AddRPC("BarterMod", "RespondBartererList", this, SingeplayerExecutionType.Server);
		LoadBartererList();
				
    }
		
	void LoadBartererList() {
		string filePath = BARTER_RECIPE_FOLDER + "recipeConfig.json";
		
		if (FileExist(filePath)) {
			JsonFileLoader<BartererList>.JsonLoadFile(filePath, bartererList);
			Print("BARTER: JSON FILE LOADED");
		} else {
			MakeDirectory(BARTER_RECIPE_FOLDER);
			JsonFileLoader<BartererList>.JsonSaveFile(filePath, bartererList);
			Print("BARTER: JSON FILE SAVED");
		}
		
	}
	
	void RespondBartererList(CallType callType, ref ParamsReadContext ctx, ref PlayerIdentity sender, ref Object target) {
        if (callType == CallType.Server) {
            SendBartererListToClient(sender);
			Print("BARTER: Respond for barterer list request in MissionServer!");
        }
    }
	
	void SendBartererListToClient(PlayerIdentity playerIdentity) {
        Param1<ref BartererList> param = new Param1<ref BartererList>(bartererList);
		Print("BARTER: Sending barterer list to BarterUI (client");
        GetRPCManager().SendRPC("BarterMod", "RPCReceiveBartererList", param, true, playerIdentity);
    }
	
	bool ReadPlayerVIP(PlayerBase player) {
		string steamID = player.GetIdentity().GetPlainId();
		string filePath = VIP_CONFIG_FOLDER + steamID + ".txt";
		FileHandle file;
		
		if (FileExist(filePath)) {
			file = OpenFile(filePath, FileMode.READ);
			
			if (file != 0) {
				string VIPStatusString;
				
				if (FGets(file, VIPStatusString)) {
					 bool isVIP = VIPStatusString == "true";
					 player.setPlayerVIP(isVIP);
					
					CloseFile(file);
					return true;
				}
				CloseFile(file);
			}
			
		} else {
			MakeDirectory(VIP_CONFIG_FOLDER);
			file = OpenFile(filePath, FileMode.WRITE);
			
			if (file != 0)
			{
				FPrint(file, "false");
				CloseFile(file);
				return true;
			}
		}
		return false; 
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
	
	void InitPlayerBarterLevel(PlayerBase player) {
		string steamID = player.GetIdentity().GetPlainId();
		string fileName = BARTER_LEVEL_FOLDER + steamID + ".txt";

		if (FileExist(fileName)) {
			int readBarterLevel = ReadPlayerBarterLevel(fileName);

			if (readBarterLevel == 0) {
				Print("BARTER: Reading the file in InitPlayerBarterLevel failed");
			}

			player.setBarterLevel(readBarterLevel);
		} else {
			player.setBarterLevel(0);
		}
	}
	
	override void InvokeOnConnect(PlayerBase player, PlayerIdentity identity) {
        super.InvokeOnConnect(player, identity);
		InitPlayerBarterLevel(player);
		ReadPlayerVIP(player);
	}
}

