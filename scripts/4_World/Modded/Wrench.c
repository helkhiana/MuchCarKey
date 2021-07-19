modded class Wrench : ItemBase 
{
    override void SetActions()
	{
		super.SetActions();

		AddAction(ActionCraftCarKey);
	}
};