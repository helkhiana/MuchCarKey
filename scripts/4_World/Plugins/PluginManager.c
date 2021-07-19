modded class PluginManager
{
	override void Init()
	{
		if (GetGame().IsServer() || !GetGame().IsMultiplayer())
		{
			RegisterPlugin( "PluginMCKLogs", false, true);
		}		
		super.Init();
	}
};