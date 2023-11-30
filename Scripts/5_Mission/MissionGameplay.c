modded class MissionGameplay 
{

		override void OnKeyRelease(int key)
	{
		super.OnKeyRelease(key);
		

		if ( key == KeyCode.KC_ESCAPE )
		{	
            PlayerBase player = PlayerBase.Cast(GetGame().GetPlayer());
			
            if (player && player.m_barterMenuOpen)
            {
				GetGame().GetUIManager().CloseMenu(BARTER_UI);
				
				player.m_barterMenuOpen = false;

                UnlockControls();
            }
		}
	}

    private void UnlockControls()
    {
        GetGame().GetMission().PlayerControlEnable(true);
        GetGame().GetInput().ResetGameFocus();
        GetGame().GetUIManager().ShowUICursor( false );
        GetGame().GetMission().GetHud().Show( true );
    }
};