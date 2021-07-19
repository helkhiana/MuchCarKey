class ActionLockCarInside: ActionLockUnlockCar
{	
	void ActionLockCarInside()
	{
		ActionLockUnlockCar();

		m_FullBody = false;
		m_CommandUID = DayZPlayerConstants.CMD_ACTIONMOD_STARTENGINE;
		m_StanceMask = DayZPlayerConstants.STANCEMASK_ALL;
	}

	override void CreateConditionComponents()
	{
		super.CreateConditionComponents();

		m_ConditionItem = new CCINone;
		m_ConditionTarget = new CCTNonRuined(0.8);
	}

	override bool CanBeUsedInVehicle()
	{
		return true;
	}
		
	override string GetText()
	{
		return "#lock_door";
	}

	override bool ActionCondition( PlayerBase player, ActionTarget target, ItemBase item )
	{
		if(!target) 
			return false;

		CarScript carScript;
		if (Class.CastTo(carScript, target.GetParent()))
		{
			if (carScript.m_HasCKAssigned && !carScript.m_IsCKLocked && player.IsInVehicle() && !carScript.CheckOpenedDoors())
				return true;
		}

        return false;
	}
	
	override void OnFinishProgressServer( ActionData action_data )
	{	
		PlayerBase player = action_data.m_Player;
		CarScript carScript = CarScript.Cast(action_data.m_Target.GetParent());
		if( carScript )
		{
			carScript.m_IsCKLocked = true;
			carScript.SynchronizeValues();
			m_MCKLogger.LogMCKActivity("Player " + player.GetIdentity().GetName() + " (" + player.GetPosition() + " steam64id=" + player.GetIdentity().GetPlainId() + ") locked vehicle " + carScript.GetDisplayName() + " (" + carScript.m_CarScriptId + ") from inside");
		}
	}
};