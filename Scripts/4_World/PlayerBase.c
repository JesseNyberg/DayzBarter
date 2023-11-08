modded class PlayerBase
{
	bool m_IsTrader = false;
	int m_currentSkillLevel = 0;
	
	override void Init()
    {
        super.Init();
        RegisterNetSyncVariableBool("m_IsTrader");
		RegisterNetSyncVariableInt("m_currentSkillLevel", 0, 1000);
    }
	
	void setTraderStatus() 
	{
		m_IsTrader = true;
		//Print("BARTER: Trader status has been set to an npc");
	}
	

	
	override void OnPlayerLoaded()
	{
		super.OnPlayerLoaded();
	}

	
	bool isTrader()
	{
		//Print("BARTER: Trader status has been called for checking");
		return m_IsTrader;
	}
	
	override void SetActions()
	{
		super.SetActions(); 

		AddAction(ActionTradeWithNPC);
		
		//Print("BARTER: Actions set!");
	}
}