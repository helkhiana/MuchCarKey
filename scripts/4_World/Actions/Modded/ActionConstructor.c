modded class ActionConstructor
{
    override void RegisterActions(TTypenameArray actions)
    {
        super.RegisterActions(actions);
        
        actions.Insert(ActionUnlockCar);
        actions.Insert(ActionLockCar);
        actions.Insert(ActionUnlockCarInside);
        actions.Insert(ActionLockCarInside);
        actions.Insert(ActionAssignNewKey);
        actions.Insert(ActionResetKeyId);
        actions.Insert(ActionCraftDuplicateKey);
        actions.Insert(ActionCraftCarKey);
        actions.Insert(ActionPickLockOnCar);
        actions.Insert(ActionGetInfoKey);
    }
};