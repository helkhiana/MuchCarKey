modded class PluginManager
{
	override void Init()
	{
		super.Init();
		if (GetGame().IsServer())
		{
			RegisterPlugin( "PluginMCKLogs", false, true);
		}		
	}
};