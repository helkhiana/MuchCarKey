modded class ActionStartEngine : ActionContinuousBase
{	
	private bool m_LastInventoryCheckReturnValue = false;
	private int m_LastInventoryCheck = 0;
	private int m_LastInventoryCheckTimer = 5000;

	override bool ActionCondition(PlayerBase player, ActionTarget target, ItemBase item)
	{	
		if(!super.ActionCondition(player, target, item))
		{
			return false;
		}		

		return MCK_StartEngineCondition(player);
	}

	bool MCK_StartEngineCondition(PlayerBase player)
	{
		MCK_EngineStartSettings settings = g_Game.GetMCKConfig().GetEngineStartSettings();
		if(settings)
		{
			if (player.GetCommand_Vehicle())
			{
				CarScript carScript = CarScript.Cast(player.GetCommand_Vehicle().GetTransport());
				if (!carScript)
				{
					return false;
				}

				if(settings.CanStartWithoutKey || (settings.CanStartUnassignedVehiclesWithoutKey && !carScript.m_HasCKAssigned))
				{
					return true;
				}
				
				return MCK_CanPlayerStartEngine(player, carScript);
			}
		}
		return true;
	}	

	bool MCK_CanPlayerStartEngine(PlayerBase player, CarScript carScript)
	{
		MCK_EngineStartSettings settings = g_Game.GetMCKConfig().GetEngineStartSettings();
		if(settings)
		{
			if(settings.CanStartWithKeyInHandOnly)
			{
				if(!player.GetItemInHands())
				{
					return false;
				}
				if(player.GetItemInHands().IsInherited(MCK_MasterKey))
				{
					return true;
				}
				MCK_CarKey_Base carKey = MCK_CarKey_Base.Cast(player.GetItemInHands());
				if (carScript && carKey)
				{
					if (carScript.m_HasCKAssigned && carKey.m_MCKId == carScript.m_CarKeyId)
					{	
						return true;
					}
				}
				return false;
			}
			if(settings.CanStartWithKeyInInventory)
			{
				int currentTime = GetGame().GetTime();
				if(currentTime - m_LastInventoryCheck > m_LastInventoryCheckTimer)
				{
					m_LastInventoryCheck = currentTime;
					m_LastInventoryCheckReturnValue = MCK_PlayerHasCorrectKeyInInventory(player, carScript.m_CarKeyId);
					return m_LastInventoryCheckReturnValue;
				}
				else
				{
					return m_LastInventoryCheckReturnValue;
				}
			}
		}
		return true;
	}

	bool MCK_PlayerHasCorrectKeyInInventory(PlayerBase player, int mckId)
	{
		array<EntityAI> entities = new array<EntityAI>;
		
		player.GetInventory().EnumerateInventory(InventoryTraversalType.PREORDER, entities);
		
		for (int i = 0; i < entities.Count(); i++)
		{
			EntityAI item = entities.Get(i);
			if (item)
			{
				if(item.IsInherited(MCK_MasterKey))
				{
					return true;
				}
				MCK_CarKey_Base carKey = MCK_CarKey_Base.Cast(item);
				if (carKey)
				{
					if (carKey.m_MCKId == mckId)
					{	
						return true;
					}
				}
			}
		}
		return false;
	}
};
