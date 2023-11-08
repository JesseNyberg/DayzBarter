class AIMissions : eAICommandManagerClient {
	
	ref array<ref eAIGroup> m_AIGroups = new array<ref eAIGroup>;
	
	 ref TStringArray missionFunctions = {
        "MayorMissionNovaya",
		"CultMissionPrud",
		"MedicalSupplyMission",
		"WeaponCacheMission"
		
    };
	
	void SpawnAIGroup(int AIAmount, vector spawnPosition, array<vector> waypoints, string loadout, int speedLimit, int threatSpeedLimit, eAIWaypointBehavior behavior, bool canBeLooted = false, bool unlimitedReload = true)
	{
		eAIFactionWest west = new eAIFactionWest();
		eAIGroup m_Group = null;
		
		for (int i = 0; i < AIAmount; i++) {
			eAIBase ai = SpawnAI_Patrol(spawnPosition, loadout);
			ai.SetMovementSpeedLimits(speedLimit, threatSpeedLimit);
			ai.eAI_SetAccuracy(0.85, 1.0);
			ai.Expansion_SetCanBeLooted(false);
			ai.eAI_SetUnlimitedReload(true);

			m_Group = ai.GetGroup();
			m_Group.SetWaypointBehaviour(behavior);
			m_Group.SetFaction(west);
			m_Group.SetFormationState(eAIGroupFormationState.NONE);

			foreach (vector waypoint : waypoints) {
				m_Group.AddWaypoint(waypoint);
			}
			
			m_AIGroups.Insert(m_Group);
		}
	}
	
    void randomMission() {
        string randomMission = missionFunctions[Math.RandomInt(0, missionFunctions.Count())];

        CallMission(randomMission);
    }
	
    void CallMission(string missionName) {
        switch (missionName) {
            case "MayorMissionNovaya":
                MayorMissionNovaya();
                break;
			case "CultMissionPrud":
                CultMissionPrud();
                break;
			case "MedicalSupplyMission":
                MedicalSupplyMission();
                break;
			case "WeaponCacheMission":
                WeaponCacheMission();
                break;
        }
    }
	
	void clearMissionAI() {
		foreach (eAIGroup groupOfAI : m_AIGroups) {
			if (groupOfAI)
				groupOfAI.ClearAI();
		}
		m_AIGroups.Clear();
	}
	
	void clearObjects(array<Object> objectsToDelete) {
		
		foreach (Object object : objectsToDelete) {
			if (object) { 
				GetGame().ObjectDelete(object);
			}
		}
		
 	}
	
	void MayorMissionNovaya() {
		// Roamer AI's
		SpawnAIGroup(4, "4331.134766 341.695282 14468.859375", {"4331.134766 341.695282 14468.859375", "4386.891113 340.169922 14473.710938", "4392.601074 352.328094 14535.487305", "4325.199219 355.108582 14552.604492", "4294.653809 344.300415 14487.539063", "4294.653809 344.300415 14487.539063"}, "AIMajurinMansikka.json", 1, 3, eAIWaypointBehavior.LOOP, false, true);
		SpawnAIGroup(4, "4326.708984 350.323822 14516.596680", {"4326.708984 350.323822 14516.596680", "4311.175781 350.321350 14504.283203", "4309.230469 350.310364 14488.117188", "4363.899902 350.291351 14480.090820", "4366.572754 350.304718 14496.294922", "4353.651855 350.300537 14514.662109", "4329.877441 350.501129 14519.128906"}, "AIMajurinMansikka.json", 1, 3, eAIWaypointBehavior.LOOP, false, true);
		SpawnAIGroup(3, "4303.337402 354.614502 14553.935547", {"4303.337402 354.614502 14553.935547", "4300.491699 343.048126 14476.500000", "4384.842285 339.527466 14468.657227", "4398.509766 355.110535 14549.507813", "4313.920410 354.539459 14549.896484"}, "AIMajurinMansikka.json", 1, 3, eAIWaypointBehavior.LOOP, false, true);
		SpawnAIGroup(2, "4350.762207 351.236603 14522.908203", {"4350.762207 351.236603 14522.908203", "4372.141113 353.960602 14544.174805", "4399.004883 356.137878 14554.993164", "4452.304199 369.272034 14652.373047"}, "AIMajurinMansikka.json", 1, 3, eAIWaypointBehavior.LOOP, false, true);
		SpawnAIGroup(2, "4365.108887 352.282288 14533.697266", {"4365.108887 352.282288 14533.697266", "4374.699707 353.328827 14540.841797", "4404.666504 355.274292 14549.439453", "4436.694336 364.327698 14609.957031", "4458.391602 369.126251 14649.098633"}, "AIMajurinMansikka.json", 1, 3, eAIWaypointBehavior.LOOP, false, true);


		// Static AI
		SpawnAIGroup(1, "4335.750977 351.299255 14493.353516", {"4335.750977 351.299255 14493.353516"}, "AIMajurinMansikka.json", 1, 3, eAIWaypointBehavior.ALTERNATE, false, true);
		SpawnAIGroup(1, "4340.302734 351.179443 14492.632813", {"4340.302734 351.179443 14492.632813"}, "AIMajurinMansikka.json", 1, 3, eAIWaypointBehavior.ALTERNATE, false, true);
		SpawnAIGroup(1, "4335.512207 354.864990 14490.242188", {"4335.512207 354.864990 14490.242188"}, "AIMajurinMansikka.json", 1, 3, eAIWaypointBehavior.ALTERNATE, false, true);
		SpawnAIGroup(1, "4339.861328 354.864990 14489.310547", {"4339.861328 354.864990 14489.310547"}, "AIMajurinMansikka.json", 1, 3, eAIWaypointBehavior.ALTERNATE, false, true);
		
		SpawnAIGroup(1, "4356.923828 351.309998 14495.769531", {"4356.923828 351.309998 14495.769531"}, "AIMajurinMansikka.json", 1, 3, eAIWaypointBehavior.ALTERNATE, false, true);
		SpawnAIGroup(1, "4355.247559 351.310028 14494.801758", {"4355.247559 351.310028 14494.801758"}, "AIMajurinMansikka.json", 1, 3, eAIWaypointBehavior.ALTERNATE, false, true);
		SpawnAIGroup(1, "4354.059082 351.310913 14502.032227", {"4354.059082 351.310913 14502.032227"}, "AIMajurinMansikka.json", 1, 3, eAIWaypointBehavior.ALTERNATE, false, true);
		SpawnAIGroup(1, "4338.042480 351.306458 14510.843750", {"4338.042480 351.306458 14510.843750"}, "AIMajurinMansikka.json", 1, 3, eAIWaypointBehavior.ALTERNATE, false, true);
		SpawnAIGroup(1, "4341.602051 351.307434 14509.300781", {"4341.602051 351.307434 14509.300781"}, "AIMajurinMansikka.json", 1, 3, eAIWaypointBehavior.ALTERNATE, false, true);
		SpawnAIGroup(1, "4321.015137 351.310944 14502.438477", {"4321.015137 351.310944 14502.438477"}, "AIMajurinMansikka.json", 1, 3, eAIWaypointBehavior.ALTERNATE, false, true);
		SpawnAIGroup(1, "4347.121094 354.861053 14503.372070", {"4347.121094 354.861053 14503.372070"}, "AIMajurinMansikka.json", 1, 3, eAIWaypointBehavior.ALTERNATE, false, true);
		SpawnAIGroup(1, "4343.700684 354.862274 14509.638672", {"4343.700684 354.862274 14509.638672"}, "AIMajurinMansikka.json", 1, 3, eAIWaypointBehavior.ALTERNATE, false, true);
		SpawnAIGroup(1, "4324.300781 354.861053 14505.408203", {"4324.300781 354.861053 14505.408203"}, "AIMajurinMansikka.json", 1, 3, eAIWaypointBehavior.ALTERNATE, false, true);
		SpawnAIGroup(1, "4317.743164 354.861053 14499.921875", {"4317.743164 354.861053 14499.921875"}, "AIMajurinMansikka.json", 1, 3, eAIWaypointBehavior.ALTERNATE, false, true);
		SpawnAIGroup(1, "4324.465332 354.861053 14505.470703", {"4324.465332 354.861053 14505.470703"}, "AIMajurinMansikka.json", 1, 3, eAIWaypointBehavior.ALTERNATE, false, true);
		SpawnAIGroup(1, "4352.282715 358.307281 14507.326172", {"4352.282715 358.307281 14507.326172"}, "AIMajurinMansikka.json", 1, 3, eAIWaypointBehavior.ALTERNATE, false, true);
		SpawnAIGroup(1, "4363.045898 358.307281 14492.771484", {"4363.045898 358.307281 14492.771484"}, "AIMajurinMansikka.json", 1, 3, eAIWaypointBehavior.ALTERNATE, false, true);
		SpawnAIGroup(1, "4331.183594 358.287506 14511.160156", {"4331.183594 358.287506 14511.160156"}, "AIMajurinMansikka.json", 1, 3, eAIWaypointBehavior.ALTERNATE, false, true);
		SpawnAIGroup(1, "4313.970703 358.287476 14500.495117", {"4313.970703 358.287476 14500.495117"}, "AIMajurinMansikka.json", 1, 3, eAIWaypointBehavior.ALTERNATE, false, true);
		
		// Mayor AI
		SpawnAIGroup(1, "4329.576172 354.861053 14506.604492", {"4329.576172 354.861053 14506.604492"}, "Majuri_Majurinmansikka.json", 0, 0, eAIWaypointBehavior.ALTERNATE, false, true);


		
		ItemBase container = ItemBase.Cast( GetGame().CreateObject("BO_MilitaryCrateStack", "4330.407715 354.864990 14508.438477", false, false));
		container.GetInventory().CreateInInventory("Potato");
		
		NotificationSystem.SimpleNoticiation("A known corrupt mayor is in town with his personal guards. Take them out and retrieve their loot (North of Novaya Petrovska)");
		
		int deleteDelay = 3600 * 1000;
		GetGame().GetCallQueue(CALL_CATEGORY_GAMEPLAY).CallLater(clearMissionAI, deleteDelay, false);
		GetGame().GetCallQueue(CALL_CATEGORY_GAMEPLAY).CallLater(GetGame().ObjectDelete, deleteDelay, false, container);
	}
	
	void CultMissionPrud() {
		// Roamer AI's
		SpawnAIGroup(4, "6533.828125 334.637909 9320.370117", {"6533.828125 334.637909 9320.370117", "6519.212891 334.238129 9325.432617", "6493.125000 333.994263 9287.652344", "6524.303711 335.116333 9266.854492", "6549.198242 335.551178 9311.098633"}, "NBCLoadout.json", 1, 3, eAIWaypointBehavior.LOOP, false, true);
		SpawnAIGroup(4, "6542.518066 335.113007 9300.847656", {"6542.518066 335.113007 9300.847656", "6549.145020 335.549988 9311.090820", "6524.171387 334.394165 9332.436523", "6493.015137 333.138397 9322.437500", "6478.533691 333.744080 9290.494141", "6530.921875 335.189606 9256.424805"}, "NBCLoadout.json", 1, 3, eAIWaypointBehavior.LOOP, false, true);
		SpawnAIGroup(4, "6503.906738 334.431610 9276.807617", {"6503.906738 334.431610 9276.807617", "6525.464844 335.059082 9267.892578", "6548.937988 335.577209 9310.794922", "6514.381348 334.067932 9333.962891", "6477.785645 333.843750 9288.736328", "6524.399414 335.129761 9266.682617", "6488.390625 334.549713 9282.001953"}, "NBCLoadout.json", 1, 3, eAIWaypointBehavior.LOOP, false, true);
		SpawnAIGroup(4, "6504.208496 333.830719 9307.474609", {"6504.208496 333.830719 9307.474609", "6492.833984 334.214783 9283.935547", "6525.894043 335.059021 9267.982422", "6550.620117 335.515900 9312.705078", "6515.788086 334.124237 9333.909180"}, "NBCLoadout.json", 1, 3, eAIWaypointBehavior.LOOP, false, true);
		
		// Static AI
		SpawnAIGroup(1, "6533.862793 334.754272 9310.730469", {"6533.862793 334.754272 9310.730469"}, "NBCLoadout.json", 1, 3, eAIWaypointBehavior.ALTERNATE, false, true);
		SpawnAIGroup(1, "6532.701660 334.755219 9307.619141", {"6532.701660 334.755219 9307.619141"}, "NBCLoadout.json", 1, 3, eAIWaypointBehavior.ALTERNATE, false, true);
		SpawnAIGroup(1, "6524.984375 334.755219 9312.909180", {"6524.984375 334.755219 9312.909180"}, "NBCLoadout.json", 1, 3, eAIWaypointBehavior.ALTERNATE, false, true);
		SpawnAIGroup(1, "6522.389648 334.700195 9313.767578", {"6522.389648 334.700195 9313.767578"}, "NBCLoadout.json", 1, 3, eAIWaypointBehavior.ALTERNATE, false, true);
		SpawnAIGroup(1, "6515.789551 334.691956 9303.717773", {"6515.789551 334.691956 9303.717773"}, "NBCLoadout.json", 1, 3, eAIWaypointBehavior.ALTERNATE, false, true);
		SpawnAIGroup(1, "6516.066895 334.900909 9290.026367", {"6516.066895 334.900909 9290.026367"}, "NBCLoadout.json", 1, 3, eAIWaypointBehavior.ALTERNATE, false, true);
		SpawnAIGroup(1, "6526.416016 339.908081 9291.657227", {"6526.416016 339.908081 9291.657227"}, "NBCLoadout.json", 1, 3, eAIWaypointBehavior.ALTERNATE, false, true);
		SpawnAIGroup(1, "6524.332031 351.977600 9290.831055", {"6524.332031 351.977600 9290.831055"}, "NBCLoadout.json", 1, 3, eAIWaypointBehavior.ALTERNATE, false, true);
		SpawnAIGroup(1, "6511.470703 334.695313 9300.480469", {"6511.470703 334.695313 9300.480469"}, "NBCLoadout.json", 1, 3, eAIWaypointBehavior.ALTERNATE, false, true);
		SpawnAIGroup(1, "6534.102051 337.930725 9310.946289", {"6534.102051 337.930725 9310.946289"}, "NBCLoadout.json", 1, 3, eAIWaypointBehavior.ALTERNATE, false, true);
		SpawnAIGroup(1, "6532.974609 337.928314 9308.441406", {"6532.974609 337.928314 9308.441406"}, "NBCLoadout.json", 1, 3, eAIWaypointBehavior.ALTERNATE, false, true);
		SpawnAIGroup(1, "6529.171387 334.509308 9317.621094", {"6529.171387 334.509308 9317.621094"}, "NBCLoadout.json", 1, 3, eAIWaypointBehavior.ALTERNATE, false, true);
		SpawnAIGroup(1, "6536.806152 334.694092 9313.251953", {"6536.806152 334.694092 9313.251953"}, "NBCLoadout.json", 1, 3, eAIWaypointBehavior.ALTERNATE, false, true);

		
		ItemBase container = ItemBase.Cast( GetGame().CreateObject("BO_MilitaryCrate_Green", "6527.232422 351.964569 9292.250000", false, false));
		container.GetInventory().CreateInInventory("Potato");
		
		NotificationSystem.SimpleNoticiation("The cultist group has gathered in the abandoned church near the lake Prud.");
		
		int deleteDelay = 3600 * 1000;
		GetGame().GetCallQueue(CALL_CATEGORY_GAMEPLAY).CallLater(clearMissionAI, deleteDelay, false);
		GetGame().GetCallQueue(CALL_CATEGORY_GAMEPLAY).CallLater(GetGame().ObjectDelete, deleteDelay, false, container);
	}
	
	void MedicalSupplyMission() {
		// Roamer AI's
		SpawnAIGroup(6, "8952.627930 291.523254 8540.450195", {"8952.627930 291.523254 8540.450195", "8944.233398 290.355164 8520.263672", "8992.196289 280.759308 8500.657227", "9007.598633 286.140533 8553.053711", "8954.490234 294.891602 8565.521484"}, "NBC_AIMissio_useampi_ase.json", 1, 3, eAIWaypointBehavior.LOOP, false, true);
		SpawnAIGroup(6, "8961.95 291.867 8551.71", {"8961.95 291.867 8551.71", "8957.35 288.417 8522.08", "8977.22 285.29 8521.61", "8981.6 288.799 8549.43"}, "NBC_AIMissio_useampi_ase.json", 1, 3, eAIWaypointBehavior.LOOP, false, true);

		// Static AI's
		SpawnAIGroup(1, "8971.9 286.998 8528.93", {"8971.9 286.998 8528.93"}, "NBC_AIMissio_useampi_ase.json", 1, 3, eAIWaypointBehavior.ALTERNATE, false, true);
		SpawnAIGroup(1, "8963.43 288.8 8532.12", {"8963.43 288.8 8532.12"}, "NBC_AIMissio_useampi_ase.json", 1, 3, eAIWaypointBehavior.ALTERNATE, false, true);
		SpawnAIGroup(1, "8973.35 288.876 8543.24", {"8973.35 288.876 8543.24"}, "NBC_AIMissio_useampi_ase.json", 1, 3, eAIWaypointBehavior.ALTERNATE, false, true);
		SpawnAIGroup(1, "8972.66 288.352 8539.16", {"8972.66 288.352 8539.16"}, "NBC_AIMissio_useampi_ase.json", 1, 3, eAIWaypointBehavior.ALTERNATE, false, true);
		SpawnAIGroup(1, "8968.99 288.903 8539.29", {"8968.99 288.903 8539.29"}, "NBC_AIMissio_useampi_ase.json", 1, 3, eAIWaypointBehavior.ALTERNATE, false, true);
		SpawnAIGroup(1, "8966.21 288.637 8534.72", {"8966.21 288.637 8534.72"}, "NBC_AIMissio_useampi_ase.json", 1, 3, eAIWaypointBehavior.ALTERNATE, false, true);
		SpawnAIGroup(1, "8967.75 290.428 8547.89", {"8967.75 290.428 8547.89"}, "NBC_AIMissio_useampi_ase.json", 1, 3, eAIWaypointBehavior.ALTERNATE, false, true);

		
		
		Object obj1 = Object.Cast(GetGame().CreateObject("mxb_MASH", "8965.2646484375 291.2648620605469 8543.9140625"));
		obj1.SetOrientation("102.84294891357422 -10.04096508026123 6.584305286407471");

		Object obj2 = Object.Cast(GetGame().CreateObject("Land_Wreck_V3S", "8975.26953125 290.01116943359377 8542.7138671875"));
		obj2.SetOrientation("12.756011009216309 7.099127769470215 9.779825210571289");

		Object obj3 = Object.Cast(GetGame().CreateObject("Land_Wreck_V3S", "8973.7978515625 288.8773193359375 8534.447265625"));
		obj3.SetOrientation("-11.638029098510743 9.3049898147583 6.260361194610596");

		Object obj4 = Object.Cast(GetGame().CreateObject("mxb_MASH", "8963.3603515625 289.8230285644531 8532.1767578125"));
		obj4.SetOrientation("76.55650329589844 -6.6384782791137699 9.374675750732422");

		Object obj5 = Object.Cast(GetGame().CreateObject("mxb_MASH", "8963.9541015625 290.5894775390625 8538.2587890625"));
		obj5.SetOrientation("98.9998779296875 -9.220953941345215 7.049163341522217");

		Object obj6 = Object.Cast(GetGame().CreateObject("XK_Big_Box2", "8973.2509765625 288.5453186035156 8541.833984375"));
		obj6.SetOrientation("-80.9999771118164 9.194626808166504 -7.221067905426025");

		Object obj7 = Object.Cast(GetGame().CreateObject("XK_Box_7", "8972.8017578125 288.4271545410156 8540.7880859375"));
		obj7.SetOrientation("9.0 7.12780237197876 9.266865730285645");

		Object obj8 = Object.Cast(GetGame().CreateObject("XK_Box_1", "8964.51953125 288.029296875 8529.5947265625"));
		obj8.SetOrientation("162.00009155273438 -9.828597068786621 -5.9728922843933109");

		Object obj9 = Object.Cast(GetGame().CreateObject("BetterClutterCutter4x4", "8969.3388671875 288.0166015625 8534.1953125"));
		obj9.SetOrientation("-99.513671875 7.012886047363281 -9.097343444824219");

		Object obj10 = Object.Cast(GetGame().CreateObject("BetterClutterCutter4x4", "8970.0146484375 289.0959777832031 8542.1923828125"));
		obj10.SetOrientation("96.1043701171875 -9.29987621307373 7.523402690887451");

		Object obj11 = Object.Cast(GetGame().CreateObject("StaticObj_Decal_dirt_damage_long3", "8967.3603515625 290.3429870605469 8536.044921875"));
		obj11.SetOrientation("-170.99986267089845 0.0 -0.0");

		Object obj12 = Object.Cast(GetGame().CreateObject("StaticObj_Decal_dirt_damage_long3", "8970.328125 290.72119140625 8541.5419921875"));
		obj12.SetOrientation("158.89915466308595 -10.9147310256958 -4.961037635803223");

		Object obj13 = Object.Cast(GetGame().CreateObject("Land_Wreck_Uaz", "8972.4326171875 287.430419921875 8527.1328125"));
		obj13.SetOrientation("44.9999885559082 -0.9019474387168884 10.834819793701172");

		ItemBase container = ItemBase.Cast(GetGame().CreateObject("BO_MilitaryCrateLarge_Green", "8975.1796875 289.3372802734375 8542.1298828125"));
		container.SetOrientation("103.92999267578125 -4.590911388397217 10.402400016784668");
		container.GetInventory().CreateInInventory("Potato");
		
		array<Object> objectsToDelete = {obj1, obj2, obj3, obj4, obj5, obj6, obj7, obj8, obj9, obj10, obj11, obj12, obj13, container};


		NotificationSystem.SimpleNoticiation("A medical supply mission has appeared");
		
		int deleteDelay = 3600 * 1000;
		GetGame().GetCallQueue(CALL_CATEGORY_GAMEPLAY).CallLater(clearMissionAI, deleteDelay, false);
		GetGame().GetCallQueue(CALL_CATEGORY_GAMEPLAY).CallLater(clearObjects, deleteDelay, false, objectsToDelete);

	}
	
	void WeaponCacheMission() {
		// Roamer AI's
		SpawnAIGroup(6, "6974.750977 270.314301 5374.815918", {"6974.750977 270.314301 5374.815918", "6984.889648 271.112701 5401.129883", "7011.294434 268.021667 5391.036133", "7011.309082 265.468872 5340.411133", "6972.654785 269.134369 5343.968750"}, "MilitarySpecopsNight.json", 1, 3, eAIWaypointBehavior.LOOP, false, true);
		SpawnAIGroup(6, "6989.181152 270.050995 5392.954102", {"6989.181152 270.050995 5392.954102", "6986.269531 268.360474 5358.598145", "7003.508789 266.872253 5356.335938", "7002.621582 268.844391 5393.245605"}, "MilitarySpecopsNight.json", 1, 3, eAIWaypointBehavior.LOOP, false, true);

		
		// At the tent AI's
		SpawnAIGroup(1, "7000.967773 267.265228 5361.105469", {"7000.967773 267.265228 5361.105469", "6993.841797 267.813934 5360.869629"}, "MilitarySniper.json", 1, 3, eAIWaypointBehavior.LOOP, false, true);
		SpawnAIGroup(1, "6992.566895 268.399719 5370.898926", {"6992.566895 268.399719 5370.898926", "6999.826660 267.855316 5371.640137"}, "MilitarySniper.json", 1, 3, eAIWaypointBehavior.LOOP, false, true);
		
		// Static AI's
		SpawnAIGroup(1, "6999.506836 267.614105 5366.254883", {"6999.506836 267.614105 5366.254883"}, "MilitarySpecopsNight.json", 1, 3, eAIWaypointBehavior.ALTERNATE, false, true);
		SpawnAIGroup(1, "6994.668457 268.035461 5367.029785", {"6994.668457 268.035461 5367.029785"}, "MilitarySpecopsNight.json", 1, 3, eAIWaypointBehavior.ALTERNATE, false, true);
		SpawnAIGroup(1, "6991.110352 268.997314 5379.515625", {"6991.110352 268.997314 5379.515625"}, "MilitarySpecopsNight.json", 1, 3, eAIWaypointBehavior.ALTERNATE, false, true);
		SpawnAIGroup(1, "6991.616211 268.641815 5373.963867", {"6991.616211 268.641815 5373.963867"}, "MilitarySpecopsNight.json", 1, 3, eAIWaypointBehavior.ALTERNATE, false, true);
		SpawnAIGroup(1, "6998.662109 268.185181 5376.310059", {"6998.662109 268.185181 5376.310059"}, "MilitarySpecopsNight.json", 1, 3, eAIWaypointBehavior.ALTERNATE, false, true);
		SpawnAIGroup(1, "6993.026855 269.374084 5388.149414", {"6993.026855 269.374084 5388.149414"}, "MilitarySpecopsNight.json", 1, 3, eAIWaypointBehavior.ALTERNATE, false, true);
		SpawnAIGroup(1, "6998.246582 268.809418 5386.705566", {"6998.246582 268.809418 5386.705566"}, "MilitarySpecopsNight.json", 1, 3, eAIWaypointBehavior.ALTERNATE, false, true);
		

		Object obj1 = Object.Cast(GetGame().CreateObject("vbldr_mil_tent_big4", "6995.5908203125 270.01202392578127 5382.95654296875"));
		obj1.SetOrientation("-9.000001907348633 3.986046075820923 4.520951747894287");

		Object obj2 = Object.Cast(GetGame().CreateObject("vbldr_mil_camonet_side_east", "6995.04833984375 269.8048095703125 5372.73779296875"));
		obj2.SetOrientation("170.99998474121095 -3.690272092819214 -4.192538738250732");

		Object obj3 = Object.Cast(GetGame().CreateObject("SV_Damaged_Kamaz2", "6992.38671875 269.9211120605469 5373.5771484375"));
		obj3.SetOrientation("90.13844299316406 -4.719655990600586 3.0408143997192385");

		Object obj4 = Object.Cast(GetGame().CreateObject("Land_Wreck_Uaz", "6991.689453125 270.3271484375 5388.654296875"));
		obj4.SetOrientation("35.99998092651367 0.08079028129577637 6.359891891479492");

		Object obj5 = Object.Cast(GetGame().CreateObject("SV_Damaged_Kamaz2", "6983.1455078125 271.2414855957031 5381.95654296875"));
		obj5.SetOrientation("-162.00009155273438 -1.7205665111541749 -6.24317741394043");

		Object obj6 = Object.Cast(GetGame().CreateObject("StaticObj_Misc_WoodenCrate_5x", "6985.06982421875 270.62908935546877 5381.29541015625"));
		obj6.SetOrientation("-71.9999771118164 6.189953804016113 -1.7278847694396973");

		Object obj7 = Object.Cast(GetGame().CreateObject("StaticObj_Misc_WoodenCrate_3x", "6983.271484375 271.8201904296875 5381.90283203125"));
		obj7.SetOrientation("18.000038146972658 1.7242130041122437 6.243182182312012");

		ItemBase container = ItemBase.Cast(GetGame().CreateObject("mmg_palette_storage", "6997.643066 268.125275 5373.694336"));
		container.SetOrientation("4.26525 2.73363 0.998696");
		container.GetInventory().CreateInInventory("Potato");
		
		array<Object> objectsToDelete = {obj1, obj2, obj3, obj4, obj5, obj6, obj7, container};


		NotificationSystem.SimpleNoticiation("A weapon cache mission has appeared");
		
		int deleteDelay = 3600 * 1000;
		GetGame().GetCallQueue(CALL_CATEGORY_GAMEPLAY).CallLater(clearMissionAI, deleteDelay, false);
		GetGame().GetCallQueue(CALL_CATEGORY_GAMEPLAY).CallLater(clearObjects, deleteDelay, false, objectsToDelete);
	}

}