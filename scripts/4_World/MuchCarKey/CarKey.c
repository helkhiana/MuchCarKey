class MCK_CarKey_Base : ItemBase
{
    int m_MCKId = -1;

    void MCK_CarKey_Base()
    {        
        RegisterNetSyncVariableInt( "m_MCKId", -1, int.MAX - 1);
    }

	void ResetKey()
	{
		m_MCKId = -1;
        Synchronize();
	}

    override void OnStoreSave( ParamsWriteContext ctx )
	{   
		super.OnStoreSave( ctx );
        ctx.Write(m_MCKId);
	}
	
	override bool OnStoreLoad( ParamsReadContext ctx, int version )
	{
		if ( !super.OnStoreLoad( ctx, version ) )
			return false;

        if (!ctx.Read(m_MCKId))
            m_MCKId = -1;

        Synchronize();
		
		return true;
	}
	
	override bool NameOverride(out string output)
	{
		if(m_MCKId > 0)
		{
			string DisplayName;
			GetGame().ObjectGetDisplayName(this, DisplayName);	
			output = DisplayName + " [Assigned]";
			return true;
		}
		return super.NameOverride(output);
	}

    int GenerateNewID()
    {      
		if(g_Game.GetMCKConfig().GetVersion() >= 2)
		{
			return g_Game.GetMCKConfig().GetNextCarKeyStoreID();
		}
		else
		{
        	return Math.RandomIntInclusive(1, int.MAX - 1);
		}
    }

    void SetNewMCKId(int newid)
    {
        m_MCKId = newid;
        Synchronize();
    }

    int GetMCKId()
    {
        return m_MCKId;
    }
	
	bool IsMCKAssigned()
	{
		return m_MCKId > 0;
	}

    protected void Synchronize()
	{
		if (GetGame().IsServer())
			SetSynchDirty();
    }
    
	override int GetViewIndex()
	{
		if( MemoryPointExists( "invView2" ) )
		{
			MCK_CarKeyTag_Base tag = MCK_CarKeyTag_Base.Cast(FindAttachmentBySlotName("CarKeyTag"));
			if(tag)
                return 0;
            else
                return 1;
		}
		return 0;
	} 

    override void SetActions()
	{
		super.SetActions();

		AddAction(ActionUnlockCar);
        AddAction(ActionLockCar);
        AddAction(ActionResetKeyId);
        AddAction(ActionAssignNewKey);
        AddAction(ActionCraftDuplicateKey);
	}

    #ifdef UNIVERSALAPI
	override void OnUApiSave(UApiEntityStore data){
		super.OnUApiSave(data);
		data.Write("m_MCKId", m_MCKId);
	}
	
	override void OnUApiLoad(UApiEntityStore data){
		super.OnUApiLoad(data);
		data.Read("m_MCKId", m_MCKId);
        Synchronize();
	}
    #endif
};
class MCK_CarKey_Blue: MCK_CarKey_Base{};
class MCK_CarKey_Green: MCK_CarKey_Base{};
class MCK_CarKey_Red: MCK_CarKey_Base{};
class MCK_CarKey_White: MCK_CarKey_Base{};
class MCK_CarKey_Yellow: MCK_CarKey_Base{};
class MCK_CarKey_Purple: MCK_CarKey_Base{};
class MCK_CarKey_Pink: MCK_CarKey_Base{};

class MCK_MasterKey : ItemBase 
{
    override void SetActions()
	{
		super.SetActions();

		AddAction(ActionUnlockCar);
        AddAction(ActionLockCar);
        AddAction(ActionResetKeyId);
	}
};

class MCK_ResetKey : ItemBase 
{
    override void SetActions()
	{
		super.SetActions();
        AddAction(ActionResetKeyId);
	}
};

class MCK_InfoKey : ItemBase 
{
    override void SetActions()
	{
		super.SetActions();
        AddAction(ActionGetInfoKey);
	}
};