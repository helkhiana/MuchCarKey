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
                DisplayReport(action_data.m_Player, carScript);
            }
		}
	}

	void DisplayReport(PlayerBase player, CarScript target)
	{
		SendMCKMessageToClient(player, "Vehicle Report:");
		SendMCKMessageToClient(player, "Vehicle: " + target);
		SendMCKMessageToClient(player, "Vehicle key id: " + target.m_CarKeyId);
		SendMCKMessageToClient(player, "Vehicle id: " + target.m_CarScriptId);
		//SendMCKMessageToClient(player, "Vehicle original owner: " + target.m_OriginalOwner);
		SendMCKMessageToClient(player, "Last time interacted: " + TimestampToString(target.GetLastInteractedWithTime()));
		SendMCKMessageToClient(player, "Remaining lifetime: " + SecondsToDays(target.GetRemainingTimeTilDespawn()));
		//SendMCKMessageToClient(player, "Max lifetime from types: " + SecondsToDays(target.GetLifetimeMax()));
	}
	
	void SendMCKMessageToClient(Object reciever, string message)
	{
		//Printing to server too
		PluginMCKLogs m_MCKLogger = PluginMCKLogs.Cast(GetPlugin(PluginMCKLogs));
		m_MCKLogger.LogMCKActivity(message);
		PlayerBase man;
		if (GetGame().IsServer() && Class.CastTo(man, reciever) && reciever.IsAlive() && message != "")
		{
			Param1<string> reportParam = new Param1<string>("");
			reportParam.param1 = message;
			GetGame().RPCSingleParam(man, ERPCs.RPC_USER_ACTION_MESSAGE, reportParam, true, man.GetIdentity());
		}
	}
};