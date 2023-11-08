modded class MissionGameplay 
{
    private ref BarterUI barterMenu;

    override void OnUpdate(float timeslice) {
        super.OnUpdate(timeslice);
        
        Input input = GetGame().GetInput();
        if (input.LocalPress("UAUIBack", true)) 
        {
            if (barterMenu != NULL && GetGame().GetUIManager().GetMenu() == barterMenu) {
                GetGame().GetUIManager().HideScriptedMenu(barterMenu);
                UnlockControls();
            }
        }
    }

    private void LockControls()
    {
        GetGame().GetMission().PlayerControlDisable(INPUT_EXCLUDE_ALL);
        GetGame().GetUIManager().ShowUICursor( true );
        GetGame().GetMission().GetHud().Show( false );
    }

    private void UnlockControls()
    {
        GetGame().GetMission().PlayerControlEnable(true);
        GetGame().GetInput().ResetGameFocus();
        GetGame().GetUIManager().ShowUICursor( false );
        GetGame().GetMission().GetHud().Show( true );
    }
};