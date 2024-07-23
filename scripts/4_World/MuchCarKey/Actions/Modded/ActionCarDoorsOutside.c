modded class ActionCarDoorsOutside
{
    override bool ActionCondition(PlayerBase player, ActionTarget target, ItemBase item)
    {
        CarScript carScript;
        if (Class.CastTo(carScript, target.GetParent()))
        {
            if (carScript.m_IsCKLocked)
                return false;
        }

        return super.ActionCondition(player, target, item);
    }
};