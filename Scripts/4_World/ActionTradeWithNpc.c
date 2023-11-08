class ActionTradeWithNPC : ActionInteractBase
{
	
    void ActionTradeWithNPC()
    {
        m_CommandUID = DayZPlayerConstants.CMD_ACTIONMOD_ATTACHITEM;
		//Print("BARTER: ActionTradeWithNPC constructor called!");
    }
	
	override void CreateConditionComponents()  
	{	
		m_ConditionItem = new CCINone;
		m_ConditionTarget = new CCTCursor;
	}


    override bool ActionCondition(PlayerBase player, ActionTarget target, ItemBase item)
    {
        PlayerBase targetNPC = PlayerBase.Cast(target.GetObject());
        float maxInteractionDistance = 2.0; 
		
		//Print("BARTER: Action condition is being checked");
		
		
        if (targetNPC && targetNPC.isTrader() && vector.Distance(player.GetPosition(), targetNPC.GetPosition()) <= maxInteractionDistance)
        {
			TARGETED_TRADER_NPC = targetNPC.GetType();
						
            return true;
        } else {
			//Print("BARTER: ActionCondition checked but conditions not met.");
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
			if (targetNPC.GetType() == "SurvivorM_Elias")
			{
				if (player.m_currentSkillLevel >= 8)
				{
					GetGame().GetUIManager().EnterScriptedMenu(BARTER_UI, null);
				}
				else
				{
					player.MessageImportant("You do not have enough barter level to barter with this person");
					return;
				}
			}
			else
			{
				GetGame().GetUIManager().EnterScriptedMenu(BARTER_UI, null);
			}
		}
	}
}