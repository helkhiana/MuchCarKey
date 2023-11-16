modded class ActionPushCar : ActionContinuousBase
{
    override bool ActionCondition(PlayerBase player, ActionTarget target, ItemBase item)
    {
		if (target)
		{
            CarScript carScript = CarScript.Cast(target.GetObject());
			if(!carScript)
				carScript = CarScript.Cast(target.GetParent());
			if (carScript && carScript.m_IsCKLocked)
                return false;
		}

        return super.ActionCondition(player, target, item);
    }
    
    //extended  logs
	override void OnEndServer(ActionData action_data)
	{
        super.OnEndServer(action_data);
		if (action_data.m_Player && action_data.m_Player.GetIdentity())
		{
			ActionPushCarData pushCarData = ActionPushCarData.Cast(action_data);
            if (pushCarData.m_Car)
            {
				CarScript car = CarScript.Cast(pushCarData.m_Car);
				if (car && g_Game.GetMCKConfig().AreExtendedLogsActivated())
				{					
					PluginMCKLogs m_MCKLogger = PluginMCKLogs.Cast(GetPlugin(PluginMCKLogs));
					m_MCKLogger.LogMCKActivity("Player " + action_data.m_Player.GetIdentity().GetName() + " (" + action_data.m_Player.GetPosition() + " steam64id=" + action_data.m_Player.GetIdentity().GetPlainId() + ") pushed " + car.GetDisplayName() + " (ID: " + car.m_CarScriptId + ")");
				}					
			}
		}
    }
};