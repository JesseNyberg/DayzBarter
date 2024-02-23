modded class PlayerBase
{
	private bool m_IsTrader = false;
	private bool m_barterMenuOpen = false;
	private int m_barterLevel = 0;
	private int m_traderID;
	private bool m_traderVIP;
	private bool m_playerVIP;
	private int m_barterRequirement;
	
	override void Init()
    {
        super.Init();
        RegisterNetSyncVariableBool("m_IsTrader");
		RegisterNetSyncVariableBool("m_traderVIP");
		RegisterNetSyncVariableBool("m_playerVIP");
		RegisterNetSyncVariableInt("m_barterLevel", 0, 1000);
		RegisterNetSyncVariableInt("m_traderID");
		RegisterNetSyncVariableInt("m_barterRequirement");
    }
		
	bool isTrader()
	{
		return m_IsTrader;
	}
	
	bool getBarterMenuOpen() {
		return m_barterMenuOpen;
	}
	
	int getBarterLevel() {
		return m_barterLevel;
	}
	
	int getBarterRequirement() {
		return m_barterRequirement;
	}
	
	int getTraderID() {
		return m_traderID;
	}
	
	void setTraderStatus() 
	{
		m_IsTrader = true;
	}
	
	bool getPlayerVIP() {
		return m_playerVIP;
	}
	
	bool getTraderVIP() {
		return m_traderVIP;
	}
	
	void setPlayerVIP(bool status) {
		m_playerVIP = status;
	}
	
	void setTraderVIP(bool status) {
		m_traderVIP = status;
	}
	
	void setBarterMenuOpen(bool status) {
		m_barterMenuOpen = status;
	}
	
	void setBarterLevel(int barterLevel) {
		m_barterLevel = barterLevel;
	}
	
	void setBarterRequirement(int barterRequirement) {
		m_barterRequirement = barterRequirement;
	}
		
	void setTraderID(int traderID) {
		m_traderID = traderID;
	}
	
	override void SetActions()
	{
		super.SetActions(); 

		AddAction(ActionTradeWithNPC);
	}
}
