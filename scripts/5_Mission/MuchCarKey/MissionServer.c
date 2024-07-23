modded class MissionServer
{
    private ref MCK_Config m_Config;

    void MissionServer()
    {
        GetRPCManager().AddRPC("Config", "GetMCKServerConfig", this, SingeplayerExecutionType.Server);
    }

    override void OnInit()
    {
        super.OnInit();
               
        m_Config = new MCK_Config;
        g_Game.SetMCKConfig(m_Config);
    }

    void GetMCKServerConfig(CallType type, ParamsReadContext ctx, PlayerIdentity sender, Object target)
    {
        if (type == CallType.Server && sender != null)                    
            GetRPCManager().SendRPC("Config", "ClientStoreMCKConfig", new Param1<ref MCK_Config>( m_Config ), true, sender);
    }
};