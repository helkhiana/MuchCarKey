modded class ActionGetOutTransport: ActionInteractBase
{	
	PluginMCKLogs m_MCKLogger = PluginMCKLogs.Cast(GetPlugin(PluginMCKLogs));	
	override void OnEndServer( ActionData action_data )
	{
		super.OnEndServer(action_data);
		if (action_data.m_Player && action_data.m_Player.GetIdentity())
		{
			HumanCommandVehicle vehCommand = action_data.m_Player.GetCommand_Vehicle();
			if( vehCommand )
			{								
				CarScript car = CarScript.Cast(vehCommand.GetTransport());
				if (car && g_Game.GetMCKConfig().AreExtendedLogsActivated())
					m_MCKLogger.LogMCKActivity("Player " + action_data.m_Player.GetIdentity().GetName() + " (" + action_data.m_Player.GetPosition() + " steam64id=" + action_data.m_Player.GetIdentity().GetPlainId() + ") exited vehicle " + car.GetDisplayName() + " (" + car.m_CarScriptId + ")");
			}
		}
	}
};
