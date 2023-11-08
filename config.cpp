class CfgPatches
{
	class Barter
	{
		units[] = {};
		weapons[] = {};
		requiredVersion = 0.1;
		requiredAddons[] = {};
	};
};

class CfgMods
{
	class BarterMod
	{
		type = "mod";
		dependencies[] = {"Game","World","Mission"};
		class defs
		{
			// class engineScriptModule
			// {
				// files[] = {"0_DayZExpansion_Market_Preload/Common","0_DayZExpansion_Market_Preload/1_Core"};
			// };
			// class gameLibScriptModule
			// {
				// files[] = {"0_DayZExpansion_Market_Preload/Common","0_DayZExpansion_Market_Preload/2_GameLib"};
			// };
			 class gameScriptModule
			 {
				 files[] = {"DayzBarter/Scripts/3_Game"};
			 };
			class worldScriptModule
			{
				files[] = {"DayzBarter/Scripts/4_World"};
			};
			class missionScriptModule
			{
				files[] = {"DayzBarter/Scripts/5_Mission"};
			};
		};
	};
};