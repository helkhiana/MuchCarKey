modded class PlayerBase
{
    override void SetActions(out TInputActionMap InputActionMap)
    {
        super.SetActions(InputActionMap);

        AddAction(ActionUnlockCarInside, InputActionMap);
        AddAction(ActionLockCarInside, InputActionMap);
        AddAction(ActionPickLockOnCar, InputActionMap);
    }
};