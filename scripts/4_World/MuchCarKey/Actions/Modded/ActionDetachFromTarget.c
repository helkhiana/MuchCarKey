modded class ActionDetachFromTarget: ActionInteractBase
{
	override bool ActionCondition( PlayerBase player, ActionTarget target, ItemBase item )
	{
		if (target)
		{
            CarScript carScript = CarScript.Cast(target.GetObject());
			if(!carScript)
				carScript = CarScript.Cast(target.GetParent());
			if (carScript && carScript.m_IsCKLocked)
                return false;
		}

        return super.ActionCondition(player, target, item);
	}
};