class ActionLockCar: ActionLockUnlockCar
{			
	override string GetText()
	{
		return "#mck_action_lock";
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
            carScript.LockVehicle();			
			MCK_LogActivity("Player " + player.GetIdentity().GetName() + " (" + player.GetPosition() + " steam64id=" + player.GetIdentity().GetPlainId() + ") locked vehicle " + carScript.GetDisplayName() + " (ID: " + carScript.m_CarScriptId + ")");		
		}
	}
};