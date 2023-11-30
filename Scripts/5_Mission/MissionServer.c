modded class MissionServer
{
    ref NPCManager m_NPCManager; // Our NPC manager reference
	ref AIMissions aiMissions;
	ref BartererList bartererList;

    override void OnInit()
    {
        super.OnInit();
        
        // Initialize our NPC manager to spawn the NPC
        m_NPCManager = new NPCManager();
		
		Print("BARTER: MissionServer initialized!");
		
		aiMissions = new AIMissions();
		bartererList = new BartererList();
		GetRPCManager().AddRPC("BarterMod", "RespondBartererList", this, SingeplayerExecutionType.Server);
		LoadBartererList();
		
		int randomMissionTime = Math.RandomInt(1200 * 1000, 6300 * 1000);
		GetGame().GetCallQueue(CALL_CATEGORY_GAMEPLAY).CallLater(aiMissions.randomMission, randomMissionTime, false);
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
	
	void InitPlayerSkillLevel(PlayerBase player) {
		string steamID = player.GetIdentity().GetId();
		string fileName = SKILLDATA_FOLDER + steamID + ".txt";

		// Check if the file exists
		if (FileExist(fileName)) {
			// File exists, read the current skill level
			int readSkillLevel = ReadPlayerSkillLevel(fileName);

			if (readSkillLevel == 0) {
				Print("BARTER: Reading the file in InitPlayerSkillLevel failed");
			}

			// Set the player's customSkillLevel based on the file data
			player.m_currentSkillLevel = readSkillLevel;
		} else {
			// File doesn't exist, set the player's skill level to 0
			player.m_currentSkillLevel = 0;
		}
	}
	
	override void InvokeOnConnect(PlayerBase player, PlayerIdentity identity) {
        super.InvokeOnConnect(player, identity);
		InitPlayerSkillLevel(player);
	}
}

