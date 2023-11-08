modded class MissionServer
{
    ref NPCManager m_NPCManager; // Our NPC manager reference

    override void OnInit()
    {
        super.OnInit();
        
        // Initialize our NPC manager to spawn the NPC
        m_NPCManager = new NPCManager();
		
		Print("BARTER: MissionServer initialized!");
		
		AIMissions aiMissions = new AIMissions();
		
		int randomMissionTime = Math.RandomInt(1800 * 1000, 10800 * 1000);
		GetGame().GetCallQueue(CALL_CATEGORY_GAMEPLAY).CallLater(aiMissions.randomMission, randomMissionTime, false);
		
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

