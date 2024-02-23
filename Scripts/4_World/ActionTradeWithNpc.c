class ActionTradeWithNPC : ActionInteractBase
{
	
    void ActionTradeWithNPC()
    {
        m_CommandUID = DayZPlayerConstants.CMD_ACTIONMOD_ATTACHITEM;
    }
	
	override void CreateConditionComponents()  
	{	
		m_ConditionItem = new CCINone;
		m_ConditionTarget = new CCTCursor;
	}

    override bool ActionCondition(PlayerBase player, ActionTarget target, ItemBase item)
    {
		
        PlayerBase targetNPC = PlayerBase.Cast(target.GetObject());
        float maxInteractionDistance = 2.5; 
		
        if (targetNPC && targetNPC.isTrader() && vector.Distance(player.GetPosition(), targetNPC.GetPosition()) <= maxInteractionDistance)
        {
			TARGETED_TRADER_NPC = targetNPC.getTraderID();
            return true;
        } else {
			
		}
        return false;
    }

    override string GetText()
    {
        return "Barter";
    }
	
	override void OnStartClient(ActionData action_data)
	{
		Print("BARTER: On start client called");
		super.OnStartClient(action_data);
		
		PlayerBase player = PlayerBase.Cast(action_data.m_Player);
		PlayerBase targetNPC = PlayerBase.Cast(action_data.m_Target.GetObject());
		
		if (!GetGame().IsServer() && targetNPC)
		{
			if (targetNPC.getTraderVIP()) {
				if (!player.getPlayerVIP()) {
					ExpansionNotification("Barter", "You need to be a VIP to barter with this person.").Error(player.GetIdentity());
					return;
				}
			}
				
			if (player.getBarterLevel() >= targetNPC.getBarterRequirement())
				GetGame().GetUIManager().EnterScriptedMenu(BARTER_UI, null);
			else
				ExpansionNotification("Barter", "You need to have a barter skill level of " + targetNPC.getBarterRequirement() + " to barter with this person.").Error(player.GetIdentity());
		}
	}
}