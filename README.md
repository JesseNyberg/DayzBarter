# DayZ Bartering system


## Description
### **DayZ Bartering system is an alternative to countless trading mods**

- #### DayZ has a lot of trading mods, but in reality, would a post apocalyptic world have currency?
- #### The DayZ Bartering system makes the trading more realistic: instead of using currency, you trade items for items.

## Features

https://github.com/JesseNyberg/DayZ-BarteringSystem/assets/67522887/f7c4e1dc-e53e-43fb-bd01-7737a25895cf


- ### **Unlimited recipes**: 
  - #### You can choose as many "recipes" as you want, that the player needs to get the final product.
    
- ### **Barter level system**: 
  - #### After every barter, you get one level to your barter level. This level is persistent and is saved to a file.
    - #### The idea of the skill is to restrict specific traders to a specific barter level.
 
- ### **Sleek UI**: 
  - #### Many mods have a dull looking UI due to the minimalistic Enfusion layout system. Not anymore!

 
- ### **Configurable Barterables and NPC spawns**:
  - #### Configure where the barterers spawn and what clothing they have on them.
  - #### Configure what the barterers have for sale. 

  
- ### **AI Missions**: 
  - #### While the main point of this mod is to add a bartering system, I have also added AI missions:
    - #### Mayor mansion mission, Medical supply mission, Weapons cache mission, Cult mission.
      - #### You might know these missions from the Arma 2 OA Dayz Mod!



## Configuration
  - ### The following folder is created when the mod is first started: DayZServer\profileFolder\BarterConfig
    - #### The files NPCConfig.json and recipeConfig.json are created, but are empty by default. 

  
- #### NPC Clothing and spawnpoints example     
```
{
  "barterNPCList": [
    {
      "name": "BanditNPC",
      "npcModel": "SurvivorM_Boris",
      "position": [9741.773438, 299.0, 8929.278320],
      "orientation": [-70.466454, 0.118899, 0.051448],
      "npcClothing": ["WinterCoif_Blue", "NioshFaceMask", "SportGlasses_Blue", "PaddedGlove_Brown", "Hoodie_Red", "Jeans_Black", "Sneakers_Gray"]
    },
    {
      "name": "CovenantNPC",
      "npcModel": "SurvivorM_Francis",
      "position": [11588.751953, 57.920631, 14647.999023],
      "orientation": [-34.746475, 0.0, 0.0],
      "npcClothing": ["SFE_shemagh_OD", "BaseballCap_CMMG_Black", "BO_OakleyGlasses", "TacticalGloves_Black", "SFE_TacticalTop_Mcb", "SFE_TacticalPants_mcb", "MilitaryBoots_Redpunk", "SFE_WasVest_Black"]
    }
  ]
}
```

- #### Barterables config example:  
```
{
  "barterers": [
    {
      "npc": "SurvivorM_Boris",
      "items": [
        {
          "finalProduct": "CJ_Materials_Circuit_Board",
          "requiredItems": ["HDSN_Detonator", "AmmoBox_9x19_25Rnd"]
        },
        {
          "finalProduct": "Truck_01_Door_2_1_Black",
          "requiredItems": ["Truck_01_Door_2_1_BlueRust", "GorkaPants_Autumn", "GorkaEJacket_Autumn"]
        }
      ]
    },
    {
      "npc": "SurvivorM_Elias",
      "items": [
        {
          "finalProduct": "ExpansionCircuitBoard_MK2",
          "requiredItems": ["CJ_Materials_Circuit_Board", "SmallProtectorCase"]
        },
        {
          "finalProduct": "BO_GasMask",
          "requiredItems": ["Collectable_SSD", "GasMask"]
        }
      ]
    }
  ]
}
```

---