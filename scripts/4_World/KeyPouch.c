class MCK_KeyPouch : Container_Base 
{    
	ref array<string> m_AllowedCargo = { "MCK_CarKey_Base", "MCK_CarKeyTag_Base" };

	override bool CanReceiveItemIntoCargo (EntityAI item)
	{
        if(!super.CanReceiveItemIntoCargo(item))
        {
            return false;
        }		
		
		return MCK_IsAnyKindOfAllowed(item);
	}
	
	override bool CanSwapItemInCargo (EntityAI child_entity, EntityAI new_entity)
	{
        if(!super.CanSwapItemInCargo(child_entity,new_entity))
        {
            return false;
        }		

		return MCK_IsAnyKindOfAllowed(child_entity) && MCK_IsAnyKindOfAllowed(new_entity);		
	}

	override bool AreChildrenAccessible()
	{
		return true;
	}

    bool MCK_IsAnyKindOfAllowed(EntityAI item)
    {
        foreach( string allowedCargo : m_AllowedCargo )
		{
			if(item.IsKindOf(allowedCargo))
			{
				return true;
			}
		}
        return false;
    }
};

class MCK_KeyPouch_ADMIN : MCK_KeyPouch 
{
    void MCK_KeyPouch_ADMIN()
    {
        m_AllowedCargo = { "MCK_CarKey_Base", "MCK_CarKeyTag_Base", "MCK_MasterKey",  "MCK_ResetKey", "MCK_InfoKey" };
    }
};