class MCK_RemoteCarkey_Base: MCK_CarKey_Base
{   
    CarScript FindNearbyVehicle(PlayerBase player)
    {
        float radius = 3.0;
        array<Object> objectsInVicinity = new array<Object>();
        array<CargoBase> cargo = new array<CargoBase>();
        
        vector playerPos = player.GetPosition();
        GetGame().GetObjectsAtPosition3D(playerPos, radius, objectsInVicinity, cargo);
        foreach (Object actorInRadius : objectsInVicinity)
        {
            CarScript carScript = CarScript.Cast(actorInRadius);
            if (!carScript)
            {
                continue;
            }
            if(!carScript.m_HasCKAssigned)
            {
                continue;
            }
            if (m_MCKId == carScript.m_CarKeyId)
            {	                
                MCK_RemoteKeySettings settings = g_Game.GetMCKConfig().GetRemoteKeySettings();
                if(settings)
                {
                    foreach(string classname : settings.VehiclesWithRemoteKey)
                    {
                        if(carScript.IsKindOf(classname))
                        {
                            return carScript;
                        }
                    }
                    return null;
                }
                return carScript;
            }
        }
        return null;
    }

    override void SetActions()
	{
		super.SetActions();

		AddAction(ActionMCKRemoteOpenClose);
	}
};