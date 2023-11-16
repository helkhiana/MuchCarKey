class ActionResetKeyIdCB : ActionContinuousBaseCB
{
	override void CreateActionComponent()
	{
		m_ActionData.m_ActionComponent = new CAContinuousTime(10);
	}
};

class ActionResetKeyId: ActionLockUnlockCar
{	
	void ActionResetKeyId()
	{
		ActionLockUnlockCar();
        m_CallbackClass = ActionResetKeyIdCB;        
	}
		
	override string GetText()
	{
		return "Reset key";
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
		
        MCK_ResetKey resetKey = MCK_ResetKey.Cast(item);
        MCK_CarKey_Base carKey = MCK_CarKey_Base.Cast(item);
		if (carScript && resetKey || carKey && carKey.m_MCKId == carScript.m_CarKeyId)
		{
			if(!carScript.m_HasCKAssigned || !g_Game.GetMCKConfig().Get_CanPlayersResetKey())
				return false;

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
			carScript.ResetVehicle();
			MCK_CarKey_Base carKey = MCK_CarKey_Base.Cast(action_data.m_MainItem);            
            if(carKey)
            {
				carKey.ResetKey();
			}
			PluginMCKLogs m_MCKLogger = PluginMCKLogs.Cast(GetPlugin(PluginMCKLogs));     
			m_MCKLogger.LogMCKActivity("Player " + player.GetIdentity().GetName() + " (" + player.GetPosition() + " steam64id=" + player.GetIdentity().GetPlainId() + ") reset key for vehicle " + carScript.GetDisplayName() + " (ID: " + carScript.m_CarScriptId + ")");
		}
	}    
};