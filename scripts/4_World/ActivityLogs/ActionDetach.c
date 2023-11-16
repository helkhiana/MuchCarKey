modded class ActionDetach: ActionInteractBase
{
	override void OnExecuteServer( ActionData action_data )
	{
		super.OnExecuteServer(action_data);
		if (action_data.m_Player && action_data.m_Player.GetIdentity())
		{
			PlayerBase player = PlayerBase.Cast(action_data.m_Player);
			Object target = Object.Cast(action_data.m_Target.GetObject());
			CarScript car = CarScript.Cast(action_data.m_Target.GetParent());
			if (car && g_Game.GetMCKConfig().AreExtendedLogsActivated())
			{				
				PluginMCKLogs m_MCKLogger = PluginMCKLogs.Cast(GetPlugin(PluginMCKLogs));
				m_MCKLogger.LogMCKActivity("Player " + player.GetIdentity().GetName() + " (" + player.GetPosition() + " steam64id=" + player.GetIdentity().GetPlainId() + ") detached item=" + Object.GetDebugName(target) + " from vehicle " + car.GetDisplayName() + " (ID: " + car.m_CarScriptId + ")");
			}				
		}
	}
};