modded class PlayerBase
{
	bool m_IsTrader = false;
	bool m_barterMenuOpen = false;
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
	}
		
	bool isTrader()
	{
		return m_IsTrader;
	}
	
	override void SetActions()
	{
		super.SetActions(); 

		AddAction(ActionTradeWithNPC);
	}
}
