modded class CarScript
{
	bool m_IsCKLocked = false;
	bool m_HasCKAssigned = false;
	int m_CarKeyId = 0;
	int m_CarScriptId = 0;
	int m_LastInteractedWithUnixTime = -1;	
	bool m_HadPlayerInteraction = false;
	string m_OriginalOwner = "No Owner";
	private bool m_Initialised = false;
	PluginMCKLogs m_MCKLogger;

	void CarScript()
	{
		RegisterNetSyncVariableBool("m_IsCKLocked");
		RegisterNetSyncVariableBool("m_HasCKAssigned");
		RegisterNetSyncVariableInt("m_CarKeyId", int.MIN, int.MAX - 1);
		RegisterNetSyncVariableInt("m_CarScriptId", int.MIN, int.MAX - 1);
		if(GetGame().IsServer())
		{
			m_MCKLogger = PluginMCKLogs.Cast(GetPlugin(PluginMCKLogs));
		}
	}

	void ResetLifetime()
	{
		m_LastInteractedWithUnixTime = CF_Date.Now(false).GetTimestamp();
		m_HadPlayerInteraction = true;
		SetMCKLifetime();
	}
	
	override void OnEngineStart()
	{
		super.OnEngineStart();
		m_LastInteractedWithUnixTime = CF_Date.Now(false).GetTimestamp();
		SetMCKLifetime();
	}

	override bool NameOverride(out string output)
	{
		if(m_OriginalOwner != "No Owner" && m_OriginalOwner != ""  )
		{
			//TODO: do RPC to sync for client
			string DisplayName;		
			GetGame().ObjectGetDisplayName(this, DisplayName);	
			output = m_OriginalOwner + "'s " + DisplayName;
			return true;
		}
		return super.NameOverride(output);
	}

	override void EEKilled(Object killer)
	{
		if (GetGame().IsServer())
		{
			if(!m_EngineDestroyed)
			{
				PlayerBase player = PlayerBase.Cast(killer);
				string killerString = "";
				if(player)
				{
					killerString = player.GetIdentity().GetName() + " steam64id=" + player.GetIdentity().GetPlainId();
				}
				else
				{
					EntityAI entity = EntityAI.Cast(killer);
					if(entity && entity.GetHierarchyRootPlayer())
					{
						player = PlayerBase.Cast(entity.GetHierarchyRootPlayer());
						killerString = player.GetIdentity().GetName() + " steam64id=" + player.GetIdentity().GetPlainId() + " with " + entity.ToString();
					}
					else
					{
						killerString = entity.ToString();
					}
				}
				m_MCKLogger.LogMCKActivity(GetDisplayName() + " (" + m_CarScriptId + " - pos " + GetPosition() + ") " + " has been destroyed by: " + killerString);
			}
		}
		super.EEKilled(killer);
	}

	override void EEDelete(EntityAI parent)
	{
		super.EEDelete(parent);
		if (GetGame().IsServer())
		{
			m_MCKLogger.LogMCKActivity(GetDisplayName() + " (" + m_CarScriptId + " - pos " + GetPosition() + ") " + " is being deleted.");
			if(GetLifetime() <= 0)
			{
				m_MCKLogger.LogMCKActivity(GetDisplayName() + " (" + m_CarScriptId + " - pos " + GetPosition() + ") Remaining DB lifetime: " + SecondsToDays(this.GetLifetime()) + ". Deleting car due to no player interaction. Last time refreshed: " + TimestampToString(m_LastInteractedWithUnixTime));
			}
		}
	}

	override void EEInit()
	{
		super.EEInit();
		if (!GetGame().IsServer())
			return;			
			
		if(!m_Initialised)
		{
			GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(this.DelayedInit, 3000, false);
		}
	}

	void DelayedInit()
	{		
		GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).Remove(this.DelayedInit);
		if(m_Initialised)
		{
			return;
		}			
		SetMCKLifetime();
		if (m_CarScriptId == 0)
		{
			//m_CarScriptId = Math.RandomIntInclusive(1, int.MAX - 1);
			string thisObjectInstance = this.ToString();
			m_CarScriptId = thisObjectInstance.Hash();
			m_LastInteractedWithUnixTime = CF_Date.Now(false).GetTimestamp();
		}
		m_MCKLogger.LogMCKActivity(GetDisplayName() + " (" + m_CarScriptId + " - pos " + GetPosition() + ") initialized." + " Remaining lifetime: " + SecondsToDays(GetRemainingTimeTilDespawn()));
		SynchronizeValues();
		m_Initialised = true;
	}

	override void AfterStoreLoad()
	{	
		super.AfterStoreLoad();	
		DelayedInit();
	}

	override void OnStoreSave(ParamsWriteContext ctx)
	{
		super.OnStoreSave(ctx);

		Param4<bool, bool, int, int> mck_CarScriptData = new Param4<bool, bool, int, int>(m_IsCKLocked, m_HasCKAssigned, m_CarKeyId, m_CarScriptId);
		ctx.Write(mck_CarScriptData);
		ctx.Write(m_LastInteractedWithUnixTime);
		ctx.Write(m_HadPlayerInteraction);
		//ctx.Write(m_OriginalOwner);
	}

	override bool OnStoreLoad(ParamsReadContext ctx, int version)
	{
		if (!super.OnStoreLoad(ctx, version))
			return false;

		
		Param4<bool, bool, int, int> mck_CarScriptData = new Param4<bool, bool, int, int>(false, false, 0, 0);
		if (ctx.Read(mck_CarScriptData))
		{
			m_IsCKLocked = mck_CarScriptData.param1;
			m_HasCKAssigned = mck_CarScriptData.param2;
			m_CarKeyId = mck_CarScriptData.param3;
			m_CarScriptId = mck_CarScriptData.param4;
		}

		if (!ctx.Read(m_LastInteractedWithUnixTime))
			m_LastInteractedWithUnixTime = CF_Date.Now(false).GetTimestamp();
		if (!ctx.Read(m_HadPlayerInteraction))
			m_HadPlayerInteraction = false;
		// if (!ctx.Read(m_OriginalOwner))
		// 	m_OriginalOwner = "No Owner";

		SynchronizeValues();

		return true;
	}
	
	override void EEOnCECreate()
	{
		super.EEOnCECreate();		
		DelayedInit();		
	}

	override void OnCEUpdate()
	{
		super.OnCEUpdate();
		HandleLifetime();		
	}

	void SetMCKLifetime()
	{		
		if(g_Game.GetMCKConfig().IsLifetimeMaintenanceEnabled())
		{			
			this.SetLifetime(g_Game.GetMCKConfig().Get_MaxLifetime());
		};
	}

	int GetElapsedTimeSinceInteraction()
	{
		return CF_Date.Now(false).GetTimestamp() - m_LastInteractedWithUnixTime;
	}

	int GetRemainingTimeTilDespawn()
	{
		if(g_Game.GetMCKConfig().IsLifetimeMaintenanceEnabled())
		{
			int remainingTime = g_Game.GetMCKConfig().Get_MaxLifetimeWithoutAnyPlayerInteraction();
			if(m_HadPlayerInteraction)
			{
				remainingTime = g_Game.GetMCKConfig().Get_MaxLifetime();
			}
			remainingTime = remainingTime - GetElapsedTimeSinceInteraction();
			return remainingTime;
		}
		return GetLifetime();
	}

	void HandleLifetime()
	{
		int deltaInSeconds = GetElapsedTimeSinceInteraction();
		if(g_Game.GetMCKConfig().IsLifetimeMaintenanceEnabled())
		{
			if(deltaInSeconds > g_Game.GetMCKConfig().Get_MaxLifetime())
			{
				m_MCKLogger.LogMCKActivity(GetDisplayName() + " (" + m_CarScriptId + " - pos " + GetPosition() + "). Time elapsed since last interaction was " + SecondsToDays(deltaInSeconds) + ". Deleting car due to no player interaction. Last time refreshed: " + TimestampToString(m_LastInteractedWithUnixTime));
				Delete();
				return;
			}
			if(deltaInSeconds > g_Game.GetMCKConfig().Get_MaxLifetimeWithoutAnyPlayerInteraction() && !m_HadPlayerInteraction)
			{
				m_MCKLogger.LogMCKActivity(GetDisplayName() + " (" + m_CarScriptId + " - pos " + GetPosition() + "). Time elapsed since last interaction was " + SecondsToDays(deltaInSeconds) + ". Deleting car due to no player interaction. Last time refreshed: " + TimestampToString(m_LastInteractedWithUnixTime));
				Delete();
				return;
			}
		}
	}

	override bool CanDisplayAttachmentSlot(string slot_name)
	{
		if (!super.CanDisplayAttachmentSlot(slot_name))
			return false;

		return !m_IsCKLocked;
	}

	override bool CanDisplayAttachmentCategory(string category_name)
	{
		if (!super.CanDisplayAttachmentCategory(category_name))
			return false;

		return !m_IsCKLocked;
	}

	void SynchronizeValues()
	{
		if (GetGame().IsServer())
			SetSynchDirty();
	}

	bool CheckOpenedDoors()
	{
		TStringArray attachmentNames = new TStringArray;
		ConfigGetTextArray("attachments", attachmentNames);
		foreach (string att : attachmentNames)
		{
			if (CarDoor.Cast(FindAttachmentBySlotName(att)))
			{
				int doorState = GetCarDoorsState(att);
				if (doorState == CarDoorState.DOORS_OPEN || doorState == CarDoorState.DOORS_MISSING)
					return true;
			}
			
		}

		return false;
	}

	bool HasDoors()
	{
		TStringArray attachmentNames = new TStringArray;
		ConfigGetTextArray("attachments", attachmentNames);
		foreach (string att : attachmentNames)
		{
			if (CarDoor.Cast(FindAttachmentBySlotName(att)))
				return true;
		}

		return false;
	}

	bool ShouldShowInv()
	{
		if (HasDoors())
			return !m_IsCKLocked && CheckOpenedDoors();
		else
			return !m_IsCKLocked;

		return false;
	}

	bool CanDoAction()
	{
		if (HasDoors())
			return !m_IsCKLocked && !CheckOpenedDoors();
		else
			return !m_IsCKLocked;

		return false;
	}

	override bool IsInventoryVisible()
	{
		return ShouldShowInv() && (GetGame().GetPlayer() && (!GetGame().GetPlayer().GetCommand_Vehicle() || GetGame().GetPlayer().GetCommand_Vehicle().GetTransport() == this));
	}
};