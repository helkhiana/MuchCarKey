class ActionLockUnlockCarCB : ActionContinuousBaseCB
{
	override void CreateActionComponent()
	{
		m_ActionData.m_ActionComponent = new CAContinuousTime(1);
	}
};

class ActionLockUnlockCar: ActionContinuousBase
{	
	void ActionLockUnlockCar()
	{
		m_CallbackClass = ActionLockUnlockCarCB;
		m_CommandUID = DayZPlayerConstants.CMD_ACTIONFB_INTERACT;
		m_FullBody = true;
		m_StanceMask = DayZPlayerConstants.STANCEMASK_ERECT | DayZPlayerConstants.STANCEMASK_CROUCH;
	}

	override void CreateConditionComponents()
	{
		m_ConditionItem = new CCINonRuined;
		m_ConditionTarget = new CCTNone;
	}

	override bool CanBeUsedInVehicle()
	{
		return false;
	}

	protected bool IsCarDoorHood(ActionTarget target)
	{
		CarDoor carDoor = CarDoor.Cast(target.GetObject());

		CarScript car;
		if (Class.CastTo(car, target.GetParent()) && carDoor)
		{
			array<string> selections = new array<string>();
			carDoor.GetActionComponentNameList(target.GetComponentIndex(), selections);
					
			for (int i = 0; i < selections.Count(); i++)
			{
				string m_AnimSource = car.GetAnimSourceFromSelection(selections[i]);
				if(m_AnimSource == "DoorsHood")
					return true;
			}
		}

		return false;
	}
};