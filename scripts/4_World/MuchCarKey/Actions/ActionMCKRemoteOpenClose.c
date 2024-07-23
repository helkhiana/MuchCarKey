class ActionMCKRemoteOpenClose: ActionSingleUseBase
{
	private int m_LastActionCheck = 0;
	private int m_LastActionCheckTimer = 3000; //miliseconds

	void ActionMCKRemoteOpenClose()
	{
        m_Text = "Remote lock/unlock vehicle";
	}
	
	override void CreateConditionComponents()  
	{
		m_ConditionItem = new CCINonRuined;
		m_ConditionTarget = new CCTNone;
	}

	override bool HasTarget()
	{
		return false;
	}

	override bool ActionCondition( PlayerBase player, ActionTarget target, ItemBase item )
	{
		MCK_RemoteCarkey_Base carKey = MCK_RemoteCarkey_Base.Cast(item);
		if (carKey)
		{
            int currentTime = GetGame().GetTime();
            if(currentTime - m_LastActionCheck > m_LastActionCheckTimer)
            {
			    return carKey.IsMCKAssigned();
            }
		}
		return false;
	}
	
	override void OnExecuteServer( ActionData action_data )
	{
		//find car nearby with id
        PlayerBase player = PlayerBase.Cast(action_data.m_Player);
        MCK_RemoteCarkey_Base carKey = MCK_RemoteCarkey_Base.Cast(action_data.m_MainItem);
        if(player && carKey)
        {
            CarScript carScript = carKey.FindNearbyVehicle(player);
            if(carScript)
            {
                if(carScript.m_IsCKLocked)
                {
                    carScript.UnlockVehicle();
                }
                else
                {
                    carScript.LockVehicle();
                }
            }
        }
	}

    override void OnExecuteClient( ActionData action_data )
	{
        int currentTime = GetGame().GetTime();
        if(currentTime - m_LastActionCheck > m_LastActionCheckTimer)
        {
            m_LastActionCheck = currentTime;
        }
    }
};