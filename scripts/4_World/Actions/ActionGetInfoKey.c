class ActionGetInfoKeyCB : ActionContinuousBaseCB
{
	override void CreateActionComponent()
	{
		m_ActionData.m_ActionComponent = new CAContinuousTime(1);
	}
};

class ActionGetInfoKey: ActionLockUnlockCar
{	
	void ActionGetInfoKey()
	{
		ActionLockUnlockCar();
        m_CallbackClass = ActionGetInfoKeyCB;        
	}
		
	override string GetText()
	{
		return "Get Info";
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

        MCK_InfoKey infoKey = MCK_InfoKey.Cast(item);
		if (carScript && infoKey)
		{
			if(!carScript.m_HasCKAssigned)
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
			MCK_InfoKey infoKey = MCK_InfoKey.Cast(action_data.m_MainItem);            
            if(infoKey)
            {          
                MCKReport.DisplayReport(action_data.m_Player, carScript);
            }
		}
	}    
};

class MCKReport
{
	static void DisplayReport(PlayerBase player, CarScript target)
	{
		SendMessageToClient(player, "Vehicle Report:");
		SendMessageToClient(player, "Car key id: " + target.m_CarKeyId);
		SendMessageToClient(player, "Car id: " + target.m_CarScriptId);
		//SendMessageToClient(player, "Last time interacted: " + TimestampToString(target.m_LastInteractedWithUnixTime));
	}
	
	private static void SendMessageToClient(Object reciever, string message)
	{
		PlayerBase man;
		if (GetGame().IsServer() && Class.CastTo(man, reciever) && reciever.IsAlive() && message != "")
		{
			Param1<string> reportParam = new Param1<string>("");
			reportParam.param1 = message;
			GetGame().RPCSingleParam(man, ERPCs.RPC_USER_ACTION_MESSAGE, reportParam, true, man.GetIdentity());
		}
	}
};