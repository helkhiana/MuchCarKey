modded class MissionGameplay
{
	void MissionGameplay()
	{
		GetRPCManager().AddRPC("Config", "ClientStoreMCKConfig", this, SingeplayerExecutionType.Client);
		GetRPCManager().SendRPC("Config", "GetMCKServerConfig", null, true, null);
	}

	void ClientStoreMCKConfig(CallType type, ref ParamsReadContext ctx, ref PlayerIdentity sender, ref Object target)
    {
        ref Param1<ref MCK_Config> data;
        if (type == CallType.Client)
		{
			if (!ctx.Read(data)) return;
			g_Game.SetMCKConfig( data.param1 );			
		}
    }
};