modded class DayZGame
{
    private ref MCK_Config m_Config;

    ref MCK_Config GetMCKConfig()
    {
        if (!m_Config)
        {
            SetMCKConfig(new MCK_Config);
        }
        
	    return m_Config;
    }

    void SetMCKConfig(MCK_Config config)
	{
		m_Config = config;
	}
};