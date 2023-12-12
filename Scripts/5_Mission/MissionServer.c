modded class MissionServer
{
    ref NPCManager m_NPCManager; 
	ref AIMissions aiMissions;
	ref BartererList bartererList;

    override void OnInit()
    {
        super.OnInit();
        
        m_NPCManager = new NPCManager();
		
		Print("BARTER: MissionServer initialized!");
		
		aiMissions = new AIMissions();
		bartererList = new BartererList();
		GetRPCManager().AddRPC("BarterMod", "RespondBartererList", this, SingeplayerExecutionType.Server);
		LoadBartererList();
		
		int randomMissionTime = Math.RandomInt(1200 * 1000, 6300 * 1000);
		GetGame().GetCallQueue(CALL_CATEGORY_GAMEPLAY).CallLater(aiMissions.randomMission, randomMissionTime, false);
		
		GetGame().GetCallQueue(CALL_CATEGORY_GAMEPLAY).CallLater(restartNotification, 12600 * 1000, false, "Restart", "30 minutes until restart!", 4);
		GetGame().GetCallQueue(CALL_CATEGORY_GAMEPLAY).CallLater(restartNotification, 13500 * 1000, false, "Restart", "15 minutes until restart!", 4);
		GetGame().GetCallQueue(CALL_CATEGORY_GAMEPLAY).CallLater(restartNotification, 14100 * 1000, false, "Restart", "5 minutes until restart!", 4);
		GetGame().GetCallQueue(CALL_CATEGORY_GAMEPLAY).CallLater(restartNotification, 14220 * 1000, false, "Restart", "3 minutes until restart!", 4);
		
		
    }
	
	void restartNotification(string title, string message, int duration) {
		ExpansionNotification(title, message, EXPANSION_NOTIFICATION_ICON_INFO, COLOR_EXPANSION_NOTIFICATION_INFO, duration).Create();
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

		if (FileExist(fileName)) {
			int readSkillLevel = ReadPlayerSkillLevel(fileName);

			if (readSkillLevel == 0) {
				Print("BARTER: Reading the file in InitPlayerSkillLevel failed");
			}

			player.m_currentSkillLevel = readSkillLevel;
		} else {
			player.m_currentSkillLevel = 0;
		}
	}
	
	override void InvokeOnConnect(PlayerBase player, PlayerIdentity identity) {
        super.InvokeOnConnect(player, identity);
		InitPlayerSkillLevel(player);
	}
}

