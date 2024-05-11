class MCK_Config
{	
	//new  config path
	static const string CONFIG_ROOT = "$profile:MuchCarKey/";
    static const string FULLPATH = "$profile:MuchCarKey/MCK_Config.json";

	private int version = 3;
    private bool CanCraftKey = true;
    private bool CanPickCarLocks = false;
	private string RaidTool = "Lockpick";
	private ref array<string> RaidTools = { "Lockpick" };
	private int ToolDamage = 50;
	private float ChanceToPickLock = -1;
	private float TimeToPickLock = 200;
    private bool ActivateExtendedLogs = true;
	private bool LifetimeMaintenanceEnabled = false;
	private int MaxLifetime = 1296000;
	private int MaxLifetimeWithoutAnyPlayerInteraction = 432000;
    private bool CanPlayersResetKey = false;
    private bool HideInventoryWhenDoorsClosed = false;

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
            Print("[MCK_Config] '" + FULLPATH + "' does NOT exist, creating default config!");
            Save();
            return; 
        }
		CanPlayersResetKey = false;
        Load();
    }

	void Load()
    {
		Print("[MCK_Config] '" + FULLPATH + "' found, loading existing config!");
		JsonFileLoader<MCK_Config>.JsonLoadFile(FULLPATH, this);
		VersionChecker();
    }
	int DesiredVersion()
	{
		return 3;
	}

	void VersionChecker()
	{
		if(version != DesiredVersion())
		{
			version = DesiredVersion();
			HideInventoryWhenDoorsClosed = false;
			Save();
		}
	}

	protected void Save()
    {
        JsonFileLoader<MCK_Config>.JsonSaveFile(FULLPATH, this);
    }

	int GetVersion()
	{
		return version;
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
	
	bool Get_CanPlayersResetKey()
	{
		return CanPlayersResetKey;
	}
	
	bool Get_HideInventory()
	{
		return HideInventoryWhenDoorsClosed;
	}


	int GetNextVehicleStoreID() 
	{
		string path = "\\vehicleid.bin";
		int storeId = LoadStoreID(path);
		storeId++;
		SaveStoreID(storeId, path);
		return storeId;
	}
	
	int GetNextCarKeyStoreID() 
	{
		string path = "\\carkeyid.bin";
		int storeId = LoadStoreID(path);
		storeId++;
		SaveStoreID(storeId, path);
		return storeId;
	}

	void SaveStoreID(int storeID, string path) 
	{
		FileSerializer fs = new FileSerializer();
		fs.Open(CONFIG_ROOT + path, FileMode.WRITE);
		fs.Write(storeID);
		fs.Close();
	}

	int LoadStoreID(string path) 
	{
		int storeID = 0;
		FileSerializer fs = new FileSerializer();
		if (!fs.Open(CONFIG_ROOT + path, FileMode.READ)) 
		{
			SaveStoreID(storeID, path);
			return storeID;
		}
		fs.Read(storeID);
		fs.Close();
		return storeID;
	}
};