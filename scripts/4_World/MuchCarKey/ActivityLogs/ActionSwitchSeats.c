#ifdef SERVER
modded class ActionSwitchSeats: ActionBase
{
	override void Start( ActionData action_data )
	{
		super.Start( action_data );
		if (action_data.m_Player && action_data.m_Player.GetIdentity())
		{
			HumanCommandVehicle vehCommand = action_data.m_Player.GetCommand_Vehicle();
			if( vehCommand )
			{				
				CarScript car = CarScript.Cast(vehCommand.GetTransport());
				if (car && g_Game.GetMCKConfig().AreExtendedLogsActivated())
				{
					int componentIndex = action_data.m_Target.GetComponentIndex();
					int crew_index = car.CrewPositionIndex(componentIndex);
					string position = "";
					switch( crew_index )
					{
						case 0:
							position = "Driver seat";
							break;
						case 1:
							position = "CoDriver seat";
							break;
						case 2:
							position = "Passenger Left seat";
							break;
						case 3:
							position = "Passenger Right seat";
							break;
					}
					if(GetGame().IsServer())
					{
						MCK_LogActivity("Player " + action_data.m_Player.GetIdentity().GetName() + " (" + action_data.m_Player.GetPosition() + " steam64id=" + action_data.m_Player.GetIdentity().GetPlainId() + ") switched seats in vehicle " + car.GetDisplayName() + " (ID: " + car.m_CarScriptId + ")" + " to " + position);	
					}
				}
			}				
		}
	}
};
#endif