class MCK_Config
{	
	//old config path
	static const string MODCONFIG_ROOT_FOLDER = "$profile:MCK_CarLockPickConfig/";
    static const string CONFIG_PATH = MODCONFIG_ROOT_FOLDER + "CarLockPickConfig.json";
	//new  config path
	static const string CONFIG_ROOT = "$profile:MuchCarKey/";
    static const string FULLPATH = "$profile:MuchCarKey/MCK_Config.json";

	private int version;
    private bool CanCraftKey;
    private bool CanPickCarLocks;
	private string RaidTool;
	private ref array<string> RaidTools;
	private int ToolDamage;
	private float ChanceToPickLock;
	private float TimeToPickLock;
    private bool ActivateExtendedLogs;
	private bool LifetimeMaintenanceEnabled;
	private int MaxLifetime;
	private int MaxLifetimeWithoutAnyPlayerInteraction;

	void MCK_Config()
	{
		if (!GetGame().IsServer()) return;
		
		if (!FileExist(CONFIG_ROOT))
        {
            Print("[MCK_Config] '" + CONFIG_ROOT + "' does NOT exist, creating directory!");
            MakeDirectory(CONFIG_ROOT);
        }

        if (!FileExist(FULLPATH))
        {
			if(FileExist(CONFIG_PATH))
			{			
				Print("[MCK_Config] '" + CONFIG_PATH + "' found, loading old config!");
				JsonFileLoader<MCK_Config>.JsonLoadFile(CONFIG_PATH, this);
				Print("[MCK_Config] deleting old config");
				DeleteFile(CONFIG_PATH);
				DeleteFile(MODCONFIG_ROOT_FOLDER);
				Load();
				return;

			}
            Print("[MCK_Config] '" + FULLPATH + "' does NOT exist, creating default config!");
            Default();
            return; 
        }

        Load();
    }

	void Load()
    {
		Print("[MCK_Config] '" + FULLPATH + "' found, loading existing config!");
		JsonFileLoader<MCK_Config>.JsonLoadFile(FULLPATH, this);
		VersionChecker();
    }

	void VersionChecker()
	{
		if(!version)
		{
			version = 1;
			ActivateExtendedLogs = true;
			LifetimeMaintenanceEnabled = true;
			MaxLifetime = 1296000;
			MaxLifetimeWithoutAnyPlayerInteraction = 432000;
			Save();
		}
	}

	protected void Save()
    {
        JsonFileLoader<MCK_Config>.JsonSaveFile(FULLPATH, this);
    }

	protected void Default()
    {
		CanCraftKey = true;
        RaidTool = "Lockpick";
        RaidTools = new array<string>;
		RaidTools.Insert(RaidTool);
		ChanceToPickLock = -1;
        TimeToPickLock = 200;
        ToolDamage = 50;
        CanPickCarLocks = false;
		version = 1;
		ActivateExtendedLogs = true;
		LifetimeMaintenanceEnabled = true;
		MaxLifetime = 1296000;
		MaxLifetimeWithoutAnyPlayerInteraction = 432000;
		Save();
	}

	float Get_ChanceToPickLock()
	{
		return ChanceToPickLock;
	}

	float Get_TimeToPickLock()
	{
		return TimeToPickLock;
	}

	float Get_ToolDamage()
	{
		return ToolDamage;
	}

	bool Get_CanPickCarLocks()
	{
		return CanPickCarLocks;
	}

	string Get_RaidTool()
	{
		return RaidTool;
	}

	bool Get_CanCraftKey()
	{
		return CanCraftKey;
	}

	array<string> Get_RaidTools()
	{
		if(RaidTools.Count() < 1 && RaidTool && RaidTool != string.Empty)
		{
			RaidTools = new array<string>;
			RaidTools.Insert(RaidTool);
		}
		return RaidTools;
	}

	bool IsLifetimeMaintenanceEnabled()
	{
		return LifetimeMaintenanceEnabled;
	}
	bool AreExtendedLogsActivated()
	{
		return ActivateExtendedLogs;
	}

	int Get_MaxLifetime()
	{
		return MaxLifetime;
	}

	int Get_MaxLifetimeWithoutAnyPlayerInteraction()
	{
		return MaxLifetimeWithoutAnyPlayerInteraction;
	}
};