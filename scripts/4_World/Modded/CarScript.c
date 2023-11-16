modded class CarScript
{
	bool m_IsCKLocked;
	bool m_HasCKAssigned;
	int m_CarKeyId;
	int m_CarScriptId;
	int m_LastInteractedWithUnixTime;	
	bool m_HadPlayerInteraction;
	string m_OriginalOwnerId;
	string m_OriginalOwnerName;
	private bool m_Initialised;//client only
	PluginMCKLogs m_MCKLogger;

	void CarScript()
	{
		m_IsCKLocked = false;
		m_HasCKAssigned = false;
		m_CarKeyId = 0;
		m_CarScriptId = 0;
		m_LastInteractedWithUnixTime = -1;
		m_HadPlayerInteraction = false;
		m_OriginalOwnerId =  "";
		m_OriginalOwnerName = "";
		m_Initialised = false;
		RegisterNetSyncVariableBool("m_IsCKLocked");
		RegisterNetSyncVariableBool("m_HasCKAssigned");
		RegisterNetSyncVariableInt("m_CarKeyId", int.MIN, int.MAX - 1);
		RegisterNetSyncVariableInt("m_CarScriptId", int.MIN, int.MAX - 1);
		if(GetGame().IsServer())
		{
			m_MCKLogger = PluginMCKLogs.Cast(GetPlugin(PluginMCKLogs));
		}
	}  

	void ResetVehicle()
	{
		m_CarKeyId = 0;
		m_IsCKLocked = false;
		m_HasCKAssigned = false;
		m_HadPlayerInteraction = false;
		m_OriginalOwnerName = "";
		m_OriginalOwnerId =  "";
		SetLastInteractedWithTimeToNow();
		SetMCKLifetime();
		SynchronizeValues();
	}

	void ResetLifetime()
	{
		SetLastInteractedWithTimeToNow();
		m_HadPlayerInteraction = true;
		SetMCKLifetime();
	}
	
	override void OnEngineStart()
	{
		super.OnEngineStart();
		SetLastInteractedWithTimeToNow();
		SetMCKLifetime();
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
				m_MCKLogger.LogMCKActivity(GetDisplayName() + " (ID: " + m_CarScriptId + " - pos " + GetPosition() + ") " + " has been destroyed by: " + killerString);
			}
		}
		super.EEKilled(killer);
	}

	override void EEDelete(EntityAI parent)
	{
		super.EEDelete(parent);
		if (GetGame().IsServer())
		{
			m_MCKLogger.LogMCKActivity(GetDisplayName() + " (ID: " + m_CarScriptId + " - pos " + GetPosition() + ") " + " is being deleted.");
			if(GetLifetime() <= 0)
			{
				m_MCKLogger.LogMCKActivity(GetDisplayName() + " (ID: " + m_CarScriptId + " - pos " + GetPosition() + ") Remaining DB lifetime: " + SecondsToDays(this.GetLifetime()) + ". This happened due to lifetime from types running out.");
			}
		}
	}

	override void DeferredInit()
	{
		super.DeferredInit();	
		if (!GetGame().IsServer())
			return;			
		if(m_Initialised)
		{
			return;
		}			
		SetMCKLifetime();
		if (m_CarScriptId == 0)
		{			
			if(g_Game.GetMCKConfig().GetVersion() >= 2)
			{
				m_CarScriptId = g_Game.GetMCKConfig().GetNextVehicleStoreID();
			}
			else
			{
				m_CarScriptId = Math.RandomIntInclusive(1, int.MAX - 1);	
			}		
			SetLastInteractedWithTimeToNow();
		}
		m_MCKLogger.LogMCKActivity(GetDisplayName() + " (ID: " + m_CarScriptId + " - pos " + GetPosition() + ") initialized." + " Remaining lifetime: " + SecondsToDays(GetRemainingTimeTilDespawn()));
		SynchronizeValues();
		m_Initialised = true;
	}

	override bool NameOverride(out string output)
	{
		if(m_OriginalOwnerName != "")
		{
			string DisplayName;
			GetGame().ObjectGetDisplayName(this, DisplayName);	
			output = m_OriginalOwnerName + "'s " + DisplayName;
			return true;
		}
		return super.NameOverride(output);
	}

	override void OnStoreSave(ParamsWriteContext ctx)
	{
		super.OnStoreSave(ctx);

		Param4<bool, bool, int, int> mck_CarScriptData = new Param4<bool, bool, int, int>(m_IsCKLocked, m_HasCKAssigned, m_CarKeyId, m_CarScriptId);
		ctx.Write(mck_CarScriptData);
		ctx.Write(m_LastInteractedWithUnixTime);
		ctx.Write(m_HadPlayerInteraction);
		ctx.Write(m_OriginalOwnerName);
		ctx.Write(m_OriginalOwnerId);
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
			SetLastInteractedWithTimeToNow();
		if (!ctx.Read(m_HadPlayerInteraction))
			m_HadPlayerInteraction = false;
		if(g_Game.GetMCKConfig().GetVersion() >= 2)
		{
			 if (!ctx.Read(m_OriginalOwnerName))
		 		m_OriginalOwnerName = "";
			 if (!ctx.Read(m_OriginalOwnerId))
		 		m_OriginalOwnerId = "";
		}

		SynchronizeValues();

		return true;
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
	int GetLastInteractedWithTime()
	{
		if(m_LastInteractedWithUnixTime <= 0)
		{
			SetLastInteractedWithTimeToNow();
		}
		return m_LastInteractedWithUnixTime;
	}
	void SetLastInteractedWithTimeToNow()
	{
		m_LastInteractedWithUnixTime = CF_Date.Now(false).GetTimestamp();
	}
	int GetElapsedTimeSinceInteraction()
	{
		return CF_Date.Now(false).GetTimestamp() - GetLastInteractedWithTime();
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
			bool expiredDueToNoPlayerInteraction = deltaInSeconds > g_Game.GetMCKConfig().Get_MaxLifetimeWithoutAnyPlayerInteraction() && !m_HadPlayerInteraction;
			bool expiredDueToMaxLifetimeRunningOut = deltaInSeconds > g_Game.GetMCKConfig().Get_MaxLifetime();
			if(expiredDueToNoPlayerInteraction || expiredDueToMaxLifetimeRunningOut)
			{
				m_MCKLogger.LogMCKActivity(GetDisplayName() + " (ID: " + m_CarScriptId + " - pos " + GetPosition() + "). Time elapsed since last interaction was " + SecondsToDays(deltaInSeconds) + ". MCK is deleting car due to no player interaction. Last time refreshed: " + TimestampToString(GetLastInteractedWithTime()));
				Delete();
				return;
			}
		}
	}

	override bool CanDisplayAttachmentSlot(int slot_id)
	{
		if (!super.CanDisplayAttachmentSlot(slot_id))
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