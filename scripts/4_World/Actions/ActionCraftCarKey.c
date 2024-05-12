class ActionCraftCarKeyCB : ActionContinuousBaseCB
{
	override void CreateActionComponent()
	{
		m_ActionData.m_ActionComponent = new CAContinuousTime(15);
	}
};

class ActionCraftCarKey: ActionLockUnlockCar
{	
	void ActionCraftCarKey()
	{
		m_CommandUID = DayZPlayerConstants.CMD_ACTIONFB_INTERACT;
		m_FullBody = true;
		m_StanceMask = DayZPlayerConstants.STANCEMASK_ERECT | DayZPlayerConstants.STANCEMASK_CROUCH;
        m_CallbackClass = ActionCraftCarKeyCB;        
	}
		
	override string GetText()
	{
		return "#mck_action_craft";
	}

	override bool ActionCondition( PlayerBase player, ActionTarget target, ItemBase item )
	{
		if(!target) 
			return false;

		if (!target.GetObject() || !target.GetObject().IsInherited(MCK_KeyGrinder))
			return false;
		
        if(!g_Game.GetMCKConfig().Get_CanCraftKey())
			return false;

        Wrench wrench = Wrench.Cast(item);
		if (wrench)
			return true;

        return false;
	}
	
	override void OnFinishProgressServer( ActionData action_data )
	{	
		PlayerBase player = action_data.m_Player;
		Wrench wrench = Wrench.Cast(action_data.m_MainItem);            
		if(wrench)
		{
			MCK_CarKey_Base duplicateKey = MCK_CarKey_Base.Cast( GetGame().CreateObject("MCK_CarKey_Base", player.GetPosition()) );			
			wrench.Delete();
			MCK_LogActivity("Player " + player.GetIdentity().GetName() + " (" + player.GetPosition() + " steam64id=" + player.GetIdentity().GetPlainId() + ") crafted new key.");
		}
	}    
};