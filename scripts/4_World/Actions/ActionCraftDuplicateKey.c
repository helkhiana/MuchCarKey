class ActionCraftDuplicateKeyCB : ActionContinuousBaseCB
{
	override void CreateActionComponent()
	{
		m_ActionData.m_ActionComponent = new CAContinuousTime(15);
	}
};

class ActionCraftDuplicateKey: ActionLockUnlockCar
{	
	void ActionCraftDuplicateKey()
	{
		m_CommandUID = DayZPlayerConstants.CMD_ACTIONFB_INTERACT;
		m_FullBody = true;
		m_StanceMask = DayZPlayerConstants.STANCEMASK_ERECT | DayZPlayerConstants.STANCEMASK_CROUCH;
        m_CallbackClass = ActionCraftDuplicateKeyCB;        
	}
		
	override string GetText()
	{
		return "Duplicate key";
	}

	override bool ActionCondition( PlayerBase player, ActionTarget target, ItemBase item )
	{
		if(!target) 
			return false;

		if (!target.GetObject() || !target.GetObject().IsInherited(MCK_KeyGrinder))
			return false;
			       
        MCK_CarKey_Base carKey = MCK_CarKey_Base.Cast(item);
		if (carKey)
		{
			if(carKey.m_MCKId <= 0)
				return false;
			
			return true;            
		}

        return false;
	}
	
	override void OnFinishProgressServer( ActionData action_data )
	{	
		PlayerBase player = action_data.m_Player;
		MCK_CarKey_Base carKey = MCK_CarKey_Base.Cast(action_data.m_MainItem);            
		if(carKey)
		{
			int mck_id = carKey.m_MCKId;
			carKey.DecreaseHealth( 50, false );
			MCK_CarKey_Base duplicateKey = MCK_CarKey_Base.Cast( GetGame().CreateObject(carKey.GetType(), player.GetPosition()) );			
			duplicateKey.SetNewMCKId(mck_id);
			PluginMCKLogs m_MCKLogger = PluginMCKLogs.Cast(GetPlugin(PluginMCKLogs));
			m_MCKLogger.LogMCKActivity("Player " + player.GetIdentity().GetName() + " (" + player.GetPosition() + " steam64id=" + player.GetIdentity().GetPlainId() + ") duplicated key (ID: " + mck_id + " )");
		}
	}    
};