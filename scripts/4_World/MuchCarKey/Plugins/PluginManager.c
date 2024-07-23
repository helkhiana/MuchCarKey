modded class PluginManager
{
	override void Init()
	{
		super.Init();
		#ifdef SERVER	
			RegisterPlugin( "PluginMCKLogs", false, true);
		#endif
	}
};