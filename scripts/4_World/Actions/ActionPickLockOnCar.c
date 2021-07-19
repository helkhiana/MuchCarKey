class ActionPickLockOnCarCB : ActionContinuousBaseCB
{
    override void CreateActionComponent()
    {
        float raidTime = g_Game.GetMCKConfig().Get_TimeToPickLock();
        if (raidTime > 0)
        {
            m_ActionData.m_ActionComponent = new CAContinuousRepeat(raidTime);
        }
        else
        {
            m_ActionData.m_ActionComponent = new CAContinuousTime(100);
        }
    }
}

class ActionPickLockOnCar : ActionLockUnlockCar
{
    void ActionPickLockOnCar()
    {
        m_CallbackClass = ActionPickLockOnCarCB;
        m_CommandUID = DayZPlayerConstants.CMD_ACTIONFB_INTERACT;
        m_FullBody = true;
        m_StanceMask = DayZPlayerConstants.STANCEMASK_ERECT | DayZPlayerConstants.STANCEMASK_CROUCH;
    }

    override void CreateConditionComponents()
    {
        m_ConditionItem = new CCINonRuined;
        m_ConditionTarget = new CCTNone;
    }

    override string GetText()
    {
        return "Pick Lock";
    }

    override bool ActionCondition(PlayerBase player, ActionTarget target, ItemBase item)
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
        
        ref array<string> raidTools = g_Game.GetMCKConfig().Get_RaidTools();
        if(raidTools.Find(item.GetType()) == -1)
            return false;

        bool canPickCarLocks = g_Game.GetMCKConfig().Get_CanPickCarLocks();
        if (carScript && canPickCarLocks && carScript.m_HasCKAssigned && !IsCarDoorHood(target) && carScript.m_IsCKLocked)
            return true;

        return false;
    }

    override void OnFinishProgressServer(ActionData action_data)
    {
        PlayerBase player = PlayerBase.Cast(action_data.m_Player);      
        int toolDamage = g_Game.GetMCKConfig().Get_ToolDamage();
        float chanceToPickLock = g_Game.GetMCKConfig().Get_ChanceToPickLock();
        CarScript carScript = CarScript.Cast(action_data.m_Target.GetObject());
		if(!carScript)
			carScript = CarScript.Cast(action_data.m_Target.GetParent());

		if( carScript )
		{
            int roll = Math.RandomInt(0, 100);
            if (chanceToPickLock == -1 || roll < chanceToPickLock)
            {
                carScript.m_IsCKLocked = false;
                carScript.m_CarKeyId = 0;
                carScript.m_HasCKAssigned = false;
                carScript.SynchronizeValues();

                m_MCKLogger.LogMCKActivity("Player " + player.GetIdentity().GetName() + " (" + player.GetPosition() + " steam64id=" + player.GetIdentity().GetPlainId() + ") picked lock for vehicle " + carScript.GetDisplayName() + " (" + carScript.m_CarScriptId + ")");
            }
            action_data.m_MainItem.DecreaseHealth(toolDamage, false);
        }
    }
};