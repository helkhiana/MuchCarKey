class ActionLockCar: ActionLockUnlockCar
{	
	void ActionLockCar()
	{
		ActionLockUnlockCar();
	}
		
	override string GetText()
	{
		return "#lock_door";
	}

	override bool ActionCondition( PlayerBase player, ActionTarget target, ItemBase item )
	{
		if(!target)
			return false;

		if (!target.GetObject())
			return false;

		CarScript carScript = CarScript.Cast(target.GetObject());
		if(!carScript)
		{
			carScript = CarScript.Cast(target.GetParent());   
			if(!carScript)
				return false;
		}
        MCK_CarKey_Base carKey = MCK_CarKey_Base.Cast(item);
		if (carScript && carKey)
		{
			if (carScript.m_HasCKAssigned && carScript.CanDoAction() && carKey.m_MCKId == carScript.m_CarKeyId)
				return true;
		}

		MCK_MasterKey masterKey = MCK_MasterKey.Cast(item);
		if (carScript && masterKey)
		{
			if (carScript.CanDoAction())
				return true;
		}

        return false;
	}
	
	override void OnFinishProgressServer( ActionData action_data )
	{	
		PlayerBase player = action_data.m_Player;
		CarScript carScript = CarScript.Cast(action_data.m_Target.GetObject());
		if(!carScript)
		{
			carScript = CarScript.Cast(action_data.m_Target.GetParent());
		}
		if( carScript )
		{
			carScript.m_IsCKLocked = true;
			carScript.SynchronizeValues();
			carScript.ResetLifetime();
			
			PluginMCKLogs m_MCKLogger = PluginMCKLogs.Cast(GetPlugin(PluginMCKLogs));
			m_MCKLogger.LogMCKActivity("Player " + player.GetIdentity().GetName() + " (" + player.GetPosition() + " steam64id=" + player.GetIdentity().GetPlainId() + ") locked vehicle " + carScript.GetDisplayName() + " (" + carScript.m_CarScriptId + ")");		
		}
	}
};