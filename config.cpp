class CfgPatches
{
    class MuchCarKey
    {
        units[]={};
        weapons[]={};
        requiredVersion=0.1;
		requiredAddons[] = {"DZ_Data", "UAPIBase"};
    };
};

class CfgMods
{
    class MuchCarKey
    {
        dir="MuchCarKey";
        picture = "";
        action = "";
        hideName = 1;
        hidePicture = 1;
        name = "MuchCarKey";
        credits = "";
        author = "helkhiana";
        authorID = "0";
        version = "0.1";
        extra = 0;
        type = "mod";
        
        dependencies[] = {"Game", "World", "Mission"};
        
        class defs
        {
			class gameScriptModule
            {
                value = "";
                files[] = {"MuchCarKey/Scripts/3_Game"};
			};

            class worldScriptModule
            {
                value = "";
                files[] = {"MuchCarKey/Scripts/4_World"};
			};

			class missionScriptModule
            {
                value = "";
                files[] = {"MuchCarKey/Scripts/5_Mission"};
			};
		};
        
    };
};

class CfgVehicles
{
	class Inventory_Base;
    class HouseNoDestruct;
	class Container_Base;
	class MCK_KeyGrinder: HouseNoDestruct
	{
		scope = 1;
		model = "\DZ\structures\furniture\various\grinder.p3d";
	};

	class MCK_CarKey_Base: Inventory_Base
	{
		scope=2;
		displayName="#mck_name_carkey";
		descriptionShort="#mck_description_carkey";
		model="\MuchCarKey\data\carkey.p3d";
		rotationFlags=8;
		weight=100;
		itemSize[]={1,2};
		fragility=0.0099999998;
		attachments[] =
		{
			"CarKeyTag"
		};
		hiddenSelections[]=
		{
			"metal",
			"key_plastic"
		};
		hiddenSelectionsTextures[]=
		{
			"MuchCarKey\data\carkey_co.paa",
			"MuchCarKey\data\carkey_co.paa"
		};	
		hiddenSelectionsMaterials[]=
		{
			"MuchCarKey\data\carkey_metal.rvmat",
			"MuchCarKey\data\carkey_tag.rvmat"
		};
        class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints=100;
					healthLevels[]=
					{
						
						{
							1.0,
							
							{
								"MuchCarKey\data\carkey_metal.rvmat",
								"MuchCarKey\data\carkey_tag.rvmat"
							}
						},
						
						{
							0.69999999,
							
							{
								"MuchCarKey\data\carkey_metal.rvmat",
								"MuchCarKey\data\carkey_tag.rvmat"
							}
						},
						
						{
							0.5,
							
							{
								"MuchCarKey\data\carkey_damage.rvmat",
								"MuchCarKey\data\carkey_damage.rvmat"
							}
						},
						
						{
							0.30000001,
							
							{
								"MuchCarKey\data\carkey_damage.rvmat",
								"MuchCarKey\data\carkey_damage.rvmat"
							}
						},
						
						{
							0.0,
							
							{
								"MuchCarKey\data\carkey_destruct.rvmat",
								"MuchCarKey\data\carkey_destruct.rvmat"
							}
						}
					};
				};
			};	
        };		
	};

	class MCK_CarKey_Blue: MCK_CarKey_Base
	{
		scope=2;
		displayName="Blue #mck_name_carkey";
		hiddenSelectionsTextures[]=
		{
			"MuchCarKey\data\carkey_co.paa",
			"MuchCarKey\data\key_variants\key_blue_co.paa"
		};
	};

	class MCK_CarKey_Green: MCK_CarKey_Base
	{
		scope=2;
		displayName="Green #mck_name_carkey";
		hiddenSelectionsTextures[]=
		{
			"MuchCarKey\data\carkey_co.paa",
			"MuchCarKey\data\key_variants\key_green_co.paa"
		};
	};

	class MCK_CarKey_Red: MCK_CarKey_Base
	{
		scope=2;
		displayName="Red #mck_name_carkey";
		hiddenSelectionsTextures[]=
		{
			"MuchCarKey\data\carkey_co.paa",
			"MuchCarKey\data\key_variants\key_red_co.paa"
		};
	};

	class MCK_CarKey_White: MCK_CarKey_Base
	{
		scope=2;
		displayName="White #mck_name_carkey";
		hiddenSelectionsTextures[]=
		{
			"MuchCarKey\data\carkey_co.paa",
			"MuchCarKey\data\key_variants\key_white_co.paa"
		};
	};

	class MCK_CarKey_Yellow: MCK_CarKey_Base
	{
		scope=2;
		displayName="Yellow #mck_name_carkey";
		hiddenSelectionsTextures[]=
		{
			"MuchCarKey\data\carkey_co.paa",
			"MuchCarKey\data\key_variants\key_yellow_co.paa"
		};
	};
	
	class MCK_CarKey_Purple: MCK_CarKey_Base
	{
		scope=2;
		displayName="Purple #mck_name_carkey";
		hiddenSelectionsTextures[]=
		{
			"MuchCarKey\data\carkey_co.paa",
			"MuchCarKey\data\key_variants\key_purple_co.paa"
		};
	};
	class MCK_CarKey_Pink: MCK_CarKey_Base
	{
		scope=2;
		displayName="Pink #mck_name_carkey";
		hiddenSelectionsTextures[]=
		{
			"MuchCarKey\data\carkey_co.paa",
			"MuchCarKey\data\key_variants\key_pink_co.paa"
		};
	};

	class MCK_RemoteCarkey_Base: MCK_CarKey_Base
	{
		scope=2;
		displayName="Remote Car Key";
		hiddenSelectionsTextures[]=
		{
			"MuchCarKey\data\carkey_co.paa",
			"MuchCarKey\data\key_variants\key_blue_co.paa"
		};
	};

	class MCK_CarKeyTag_Base: Inventory_Base
	{
		scope=2;
		displayName="#mck_name_carkeytag";
		descriptionShort="#mck_description_carkeytag";
		model="\MuchCarKey\data\carkey_tag.p3d";
		rotationFlags=17;
		weight=100;
		itemSize[]={1,2};
		inventorySlot[] = { "CarKeyTag" };
		fragility=0.0099999998;
		hiddenSelections[]=
		{
			"leather_tag"
		};
		hiddenSelectionsTextures[]=
		{
			"MuchCarKey\data\carkey_co.paa"
		};	
		hiddenSelectionsMaterials[]=
		{
			"MuchCarKey\data\carkey_tag.rvmat"
		};
        class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints=100;
					healthLevels[]=
					{
						
						{
							1.0,
							
							{
								"MuchCarKey\data\carkey_tag.rvmat"
							}
						},
						
						{
							0.69999999,
							
							{
								"MuchCarKey\data\carkey_tag.rvmat"
							}
						},
						
						{
							0.5,
							
							{
								"MuchCarKey\data\carkey_damage.rvmat"
							}
						},
						
						{
							0.30000001,
							
							{
								"MuchCarKey\data\carkey_damage.rvmat"
							}
						},
						
						{
							0.0,
							
							{
								"MuchCarKey\data\carkey_destruct.rvmat"
							}
						}
					};
				};
			};	
        };		
	};

	class MCK_CarKeyTag_OlgaBlack: MCK_CarKeyTag_Base
	{
		scope=2;
		displayName="Olga 24 Black Tag";
		hiddenSelectionsTextures[]=
		{
			"MuchCarKey\data\tag_variants\tag_olgablack_co.paa"
		};
	};
	class MCK_CarKeyTag_OlgaWhite: MCK_CarKeyTag_Base
	{
		scope=2;
		displayName="Olga 24 White Tag";
		hiddenSelectionsTextures[]=
		{
			"MuchCarKey\data\tag_variants\tag_olgawhite_co.paa"
		};
	};
	class MCK_CarKeyTag_OlgaWine: MCK_CarKeyTag_Base
	{
		scope=2;
		displayName="Olga 24 Wine Tag";
		hiddenSelectionsTextures[]=
		{
			"MuchCarKey\data\tag_variants\tag_olgawine_co.paa"
		};
	};	

	class MCK_CarKeyTag_AdaBlue: MCK_CarKeyTag_Base
	{
		scope=2;
		displayName="Ada 4x4 Blue Tag";
		hiddenSelectionsTextures[]=
		{
			"MuchCarKey\data\tag_variants\tag_adablue_co.paa"
		};
	};
	class MCK_CarKeyTag_AdaWhite: MCK_CarKeyTag_Base
	{
		scope=2;
		displayName="Ada 4x4 White Tag";
		hiddenSelectionsTextures[]=
		{
			"MuchCarKey\data\tag_variants\tag_adawhite_co.paa"
		};
	};
	class MCK_CarKeyTag_AdaGreen: MCK_CarKeyTag_Base
	{
		scope=2;
		displayName="Ada 4x4 Green Tag";
		hiddenSelectionsTextures[]=
		{
			"MuchCarKey\data\tag_variants\tag_adagreen_co.paa"
		};
	};

	class MCK_CarKeyTag_GunterBlue: MCK_CarKeyTag_Base
	{
		scope=2;
		displayName="Gunter 2 Blue Tag";
		hiddenSelectionsTextures[]=
		{
			"MuchCarKey\data\tag_variants\tag_gunterblue_co.paa"
		};
	};
	class MCK_CarKeyTag_GunterBlack: MCK_CarKeyTag_Base
	{
		scope=2;
		displayName="Gunter 2 Black Tag";
		hiddenSelectionsTextures[]=
		{
			"MuchCarKey\data\tag_variants\tag_gunterblack_co.paa"
		};
	};
	class MCK_CarKeyTag_GunterRed: MCK_CarKeyTag_Base
	{
		scope=2;
		displayName="Gunter 2 Red Tag";
		hiddenSelectionsTextures[]=
		{
			"MuchCarKey\data\tag_variants\tag_gunterred_co.paa"
		};
	};

	class MCK_CarKeyTag_SarkaGrey: MCK_CarKeyTag_Base
	{
		scope=2;
		displayName="Sarka 120 Grey Tag";
		hiddenSelectionsTextures[]=
		{
			"MuchCarKey\data\tag_variants\tag_sarkagrey_co.paa"
		};
	};
	class MCK_CarKeyTag_SarkaRed: MCK_CarKeyTag_Base
	{
		scope=2;
		displayName="Sarka 120 Red Tag";
		hiddenSelectionsTextures[]=
		{
			"MuchCarKey\data\tag_variants\tag_sarkared_co.paa"
		};
	};
	class MCK_CarKeyTag_SarkaYellow: MCK_CarKeyTag_Base
	{
		scope=2;
		displayName="Sarka 120 Yellow Tag";
		hiddenSelectionsTextures[]=
		{
			"MuchCarKey\data\tag_variants\tag_sarkayellow_co.paa"
		};
	};

	
	class MCK_CarKeyTag_Black: MCK_CarKeyTag_Base
	{
		scope=2;
		displayName="Black Tag";
		hiddenSelectionsTextures[]=
		{
			"MuchCarKey\data\tag_variants\tag_black_co.paa"
		};
	};
	class MCK_CarKeyTag_Blue: MCK_CarKeyTag_Base
	{
		scope=2;
		displayName="Blue Tag";
		hiddenSelectionsTextures[]=
		{
			"MuchCarKey\data\tag_variants\tag_blue_co.paa"
		};
	};
	class MCK_CarKeyTag_Green: MCK_CarKeyTag_Base
	{
		scope=2;
		displayName="Green Tag";
		hiddenSelectionsTextures[]=
		{
			"MuchCarKey\data\tag_variants\tag_green_co.paa"
		};
	};
	class MCK_CarKeyTag_Grey: MCK_CarKeyTag_Base
	{
		scope=2;
		displayName="Grey Tag";
		hiddenSelectionsTextures[]=
		{
			"MuchCarKey\data\tag_variants\tag_grey_co.paa"
		};
	};
	class MCK_CarKeyTag_Red: MCK_CarKeyTag_Base
	{
		scope=2;
		displayName="Red Tag";
		hiddenSelectionsTextures[]=
		{
			"MuchCarKey\data\tag_variants\tag_red_co.paa"
		};
	};
	class MCK_CarKeyTag_White: MCK_CarKeyTag_Base
	{
		scope=2;
		displayName="White Tag";
		hiddenSelectionsTextures[]=
		{
			"MuchCarKey\data\tag_variants\tag_white_co.paa"
		};
	};
	class MCK_CarKeyTag_Yellow: MCK_CarKeyTag_Base
	{
		scope=2;
		displayName="Yellow Tag";
		hiddenSelectionsTextures[]=
		{
			"MuchCarKey\data\tag_variants\tag_yellow_co.paa"
		};
	};
	class MCK_CarKeyTag_Purple: MCK_CarKeyTag_Base
	{
		scope=2;
		displayName="Purple Tag";
		hiddenSelectionsTextures[]=
		{
			"MuchCarKey\data\key_variants\key_purple_co.paa"
		};
	};
	class MCK_CarKeyTag_Pink: MCK_CarKeyTag_Base
	{
		scope=2;
		displayName="Pink Tag";
		hiddenSelectionsTextures[]=
		{
			"MuchCarKey\data\key_variants\key_pink_co.paa"
		};
	};

    class MCK_MasterKey: Inventory_Base
    {
        scope=2;
		displayName="#mck_name_masterkey";
		descriptionShort="#mck_description_masterkey";        
		model="\MuchCarKey\data\fullcarkey.p3d";
		rotationFlags=17;
		weight=100;
		itemSize[]={1,2};
		fragility=0.0099999998;
		hiddenSelections[]=
		{
			"key_plastic",
			"leather_tag"
		};
		hiddenSelectionsTextures[]=
		{
			"MuchCarKey\data\carkey_masterkey_co.paa",
			"MuchCarKey\data\carkey_masterkey_co.paa"
		};	
		hiddenSelectionsMaterials[]=
		{
			"MuchCarKey\data\carkey_masterkey_tag.rvmat",
			"MuchCarKey\data\carkey_masterkey_tag.rvmat"
		};
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints=1000000;
    			};
    		};
    	};
    };
    
    class MCK_ResetKey: MCK_MasterKey
    {
        scope=2;
		displayName="#mck_name_resetkey";
		descriptionShort="#mck_description_resetkey";        
		hiddenSelectionsTextures[]=
		{
			"MuchCarKey\data\carkey_resetkey_co.paa",
			"MuchCarKey\data\carkey_resetkey_co.paa"
		};	
		hiddenSelectionsMaterials[]=
		{
			"MuchCarKey\data\carkey_resetkey_tag.rvmat",
			"MuchCarKey\data\carkey_resetkey_tag.rvmat"
		};
    };

    class MCK_InfoKey: MCK_MasterKey
    {
        scope=2;
		displayName="#mck_name_infokey";
		descriptionShort="#mck_description_infokey";        
		hiddenSelectionsTextures[]=
		{
			"MuchCarKey\data\carkey_infokey_co.paa",
			"MuchCarKey\data\carkey_infokey_co.paa"
		};	
		hiddenSelectionsMaterials[]=
		{
			"MuchCarKey\data\carkey_tag.rvmat",
			"MuchCarKey\data\carkey_tag.rvmat"
		};
    };

	class MCK_KeyPouch: Container_Base
	{
		scope = 2;
		displayName = "#mck_name_keypouch";
		descriptionShort = "#mck_description_keypouch";
		model = "\MuchCarKey\data\key_pouch\keypouch.p3d";
		rotationFlags=1;
		weight = 130;
		itemSize[] = {3,2};
		itemsCargoSize[] = {4,3};
		canBeDigged = 0;
		allowOwnedCargoManipulation = 1;    
		hiddenSelections[]=
		{
			"all"
		};    
		hiddenSelectionsTextures[]=
		{
			"MuchCarKey\data\key_pouch\keypouch_co.paa"
		};
		hiddenSelectionsMaterials[]=
		{
			"MuchCarKey\data\key_pouch\keypouch.rvmat"
		};
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints=100;
					healthLevels[]=
					{
						{
							1.0,
							{
								"MuchCarKey\data\key_pouch\keypouch.rvmat"
							}
						},						
						{
							0.69999999,
							{
								"MuchCarKey\data\key_pouch\keypouch.rvmat"
							}
						},						
						{
							0.5,							
							{
								"MuchCarKey\data\key_pouch\keypouch_damage.rvmat"
							}
						},						
						{
							0.30000001,
							{
								"MuchCarKey\data\key_pouch\keypouch_damage.rvmat"
							}
						},						
						{
							0.0,							
							{
								"MuchCarKey\data\key_pouch\keypouch_destruct.rvmat"
							}
						}
					};
				};
			};
		};
	};

	class MCK_KeyPouch_ADMIN: MCK_KeyPouch
	{
		scope = 2;
		displayName = "ADMIN #mck_name_keypouch";
		descriptionShort = "#mck_description_keypouch This pouch is meant for admins to store their admin keys.";  
		hiddenSelectionsTextures[]=
		{
			"MuchCarKey\data\key_pouch\keypouch_red_co.paa"
		};
	};
};

class CfgSlots
{
	class Slot_CarKeytag
	{
		name="CarKeyTag";
		displayName="Car Key Tag";
		ghostIcon="missing";
	};
};

class CfgNonAIVehicles
{
	class ProxyAttachment;
	class Proxycarkey_tag: ProxyAttachment
	{
		scope=2;
		inventorySlot[] = { "CarKeyTag" };
		model="\MuchCarKey\data\carkey_tag.p3d";
	};
};