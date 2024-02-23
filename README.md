# DayZ Bartering system


## Description
### **DayZ Bartering system is an alternative to countless trading mods**

- #### DayZ has a lot of trading mods, but in reality, would a post apocalyptic world have currency?
- #### The DayZ Bartering system makes the trading more realistic: instead of using currency, you trade items for items.

## Features







https://github.com/JesseNyberg/DayZ-BarteringSystem/assets/67522887/a0d02d22-ba4a-4622-99ed-dc88f6f935ff








- ### **Unlimited recipes**: 
  - #### You can choose as many "recipes" as you want, that the player needs to get the final product.
    
- ### **Barter level system**: 
  - #### After every barter, you get one level to your barter level. This level is persistent and is saved to a file.
    - #### The idea of the skill is to restrict specific traders to a specific barter level.
 
- ### **Sleek UI**: 
  - #### Many mods have a dull looking UI due to the minimalistic Enfusion layout system. Not anymore!
  
- ### **Categories**: 
  - #### The items are in categories and categories are barter specific.

- ### **VIP status**: 
  - #### Barterers can be restricted to only VIPS, the VIPS can be set in the config folder (config/VIPS)
 
- ### **Configurable Barterables and NPC spawns**:
  - #### Configure where the barterers spawn and what clothing they have on them.
  - #### Configure what the barterers have for sale. 

  
- ### **AI Missions**: 
  - #### While the main point of this mod is to add a bartering system, I have also added AI missions:
    - #### Mayor mansion mission, Medical supply mission, Weapons cache mission, Cult mission.
      - #### You might know these missions from the Arma 2 OA Dayz Mod!



## Configuration
 - #### NPC Configuration example (BarterConfig\NPCConfig.json):
  ```
{
   "barterNPCList":[
      {
         "id":1,
         "npcModel":"SurvivorM_Cyril",
         "barterRequirement":0,
         "VIP":false,
         "position":[
            925.505066,
            182.328217,
            7625.565918
         ],
         "orientation":[
            -10.271118,
            0.0,
            0.0
         ],
         "npcClothing":[
            "BaseballCap_Camo",
            "BO_MaskaFace_Black",
            "TacticalGloves_Black",
            "SFE_TacticalTop_rgr",
            "SFE_WasVest_Olive",
            "SFE_TacticalPants_MultiCam",
            "MilitaryBoots_Beige"
         ]
      }
   ]
}
  ```

 - #### Recipe Configuration example (BarterConfig\recipeConfig.json):
  ```
{
   "barterers":[
      {
         "npcID":6,
         "items":[
            {
               "id":"5000",
               "category":"Bandits",
               "finalProducts":[
                  {
                     "itemName":"TTsKO_Jacket_Camo",
                     "quantity":1
                  }
               ],
               "requiredItems":[
                  {
                     "itemName":"SewingKit",
                     "quantity":100
                  },
                  {
                     "itemName":"M65Jacket_Black",
                     "quantity":1
                  }
               ]
            }
         ]
      }
   ]
}
  ```
  

---
