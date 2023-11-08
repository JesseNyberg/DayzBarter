class NPCManager
{
    PlayerBase barterNPC; // Reference to our spawned NPC
    vector m_SpawnPosition = "6196 13 2384"; // You can change this to any coordinates you want.
	PlayerBase barterNPC2;
	vector m_SpawnPosition2 = "6261 305 7777";

    void NPCManager()
    {
        // Spawn NPC when the manager is created.
        SpawnNPC();
    }

    void ~NPCManager()
    {
        // Destructor logic if needed
    }

    void SpawnNPC()
    {
        // Spawn NPC only on the server side.
        if (GetGame().IsServer())
        {
            barterNPC = PlayerBase.Cast(GetGame().CreateObject("SurvivorM_Denis", m_SpawnPosition, false, false));
			barterNPC2 = PlayerBase.Cast(GetGame().CreateObject("SurvivorM_Elias", m_SpawnPosition2, false, false));

            if (barterNPC)
            {
                barterNPC.SetPosition(m_SpawnPosition);
                barterNPC.setTraderStatus();
            }
			if (barterNPC2)
            {
                barterNPC2.SetPosition(m_SpawnPosition2);
                barterNPC2.setTraderStatus();
            }
        }
    }
}
