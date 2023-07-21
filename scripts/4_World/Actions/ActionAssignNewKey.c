class ActionAssignNewKeyCB : ActionContinuousBaseCB
{
	override void CreateActionComponent()
	{
		m_ActionData.m_ActionComponent = new CAContinuousTime(5);
	}
};

class ActionAssignNewKey: ActionLockUnlockCar
{	
	void ActionAssignNewKey()
	{
		ActionLockUnlockCar();
        m_CallbackClass = ActionAssignNewKeyCB;        
	}
		
	override string GetText()
	{
		return "Assign new key";
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
			if(carScript.m_HasCKAssigned)
				return false;

			if (carScript.CanDoAction() && carKey.GetMCKId() <= 0)
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
			MCK_CarKey_Base carKey = MCK_CarKey_Base.Cast(action_data.m_MainItem);            
            if(carKey)
            {
                int mck_id = carKey.GenerateNewID();
				carKey.SetNewMCKId(mck_id);                

                carScript.m_CarKeyId = mck_id;
                carScript.m_HasCKAssigned = true;
				carScript.SynchronizeValues(); 
				carScript.ResetLifetime();
				
				PluginMCKLogs m_MCKLogger = PluginMCKLogs.Cast(GetPlugin(PluginMCKLogs));
				m_MCKLogger.LogMCKActivity("Player " + player.GetIdentity().GetName() + " (" + player.GetPosition() + " steam64id=" + player.GetIdentity().GetPlainId() + ") assigned new owner and key (ID: " + mck_id + " ) to vehicle " + carScript.GetDisplayName() + " (" + carScript.m_CarScriptId + ")");
            }
		}
	}    
};