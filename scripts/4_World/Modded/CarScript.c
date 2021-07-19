modded class CarScript
{
	bool m_IsCKLocked = false;
	bool m_HasCKAssigned = false;
	int m_CarKeyId = 0;
	int m_CarScriptId = 0;
	int m_LastInteractedWithUnixTime = -1;	
	bool m_HadPlayerInteraction = false;
	PluginMCKLogs m_MCKLogger = PluginMCKLogs.Cast(GetPlugin(PluginMCKLogs));

	void CarScript()
	{
		RegisterNetSyncVariableBool("m_IsCKLocked");
		RegisterNetSyncVariableBool("m_HasCKAssigned");
		RegisterNetSyncVariableInt("m_CarKeyId", 0, int.MAX - 1);
		RegisterNetSyncVariableInt("m_CarScriptId", 0, int.MAX - 1);
	}

	void ResetLifetime()
	{
		m_LastInteractedWithUnixTime = JMDate.Now(false).GetTimestamp();
		m_HadPlayerInteraction = true;
	}
	
	override void OnEngineStart()
	{
		super.OnEngineStart();
		m_LastInteractedWithUnixTime = JMDate.Now(false).GetTimestamp();
	}

	override void EEDelete(EntityAI parent)
	{
		super.EEDelete(parent);
		if (GetGame().IsServer())
			m_MCKLogger.LogMCKActivity(GetDisplayName() + " (" + m_CarScriptId + " - pos " + GetPosition() + ") " + " is being deleted.");
	}

	override void EEInit()
	{
		super.EEInit();
		if (!GetGame().IsServer())
			return;
		if (m_CarScriptId == 0)
			m_CarScriptId = Math.RandomIntInclusive(1, int.MAX - 1);
		m_MCKLogger.LogMCKActivity(GetDisplayName() + " (" + m_CarScriptId + " - pos " + GetPosition() + ") initialized.");
		SynchronizeValues();
	}

	override void OnStoreSave(ParamsWriteContext ctx)
	{
		super.OnStoreSave(ctx);

		Param4<bool, bool, int, int> mck_CarScriptData = new Param4<bool, bool, int, int>(m_IsCKLocked, m_HasCKAssigned, m_CarKeyId, m_CarScriptId);
		ctx.Write(mck_CarScriptData);
		ctx.Write(m_LastInteractedWithUnixTime);
		ctx.Write(m_HadPlayerInteraction);
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
			m_LastInteractedWithUnixTime = JMDate.Now(false).GetTimestamp();
		if (!ctx.Read(m_HadPlayerInteraction))
			m_HadPlayerInteraction = false;

		SynchronizeValues();

		return true;
	}
	
	override void OnCEUpdate()
	{
		super.OnCEUpdate();
		if(m_LastInteractedWithUnixTime == -1)
		{
			m_LastInteractedWithUnixTime = JMDate.Now(false).GetTimestamp();
			m_MCKLogger.LogMCKActivity(GetDisplayName() + " (" + m_CarScriptId + " - pos " + GetPosition() + ") interaction timestamp was -1. it is now: " + TimestampToString(m_LastInteractedWithUnixTime));
		}

		HandleLifetime();		
	}

	void HandleLifetime()
	{
		int deltaInSeconds = JMDate.Now(false).GetTimestamp() - m_LastInteractedWithUnixTime;
		if(g_Game.GetMCKConfig().IsLifetimeMaintenanceEnabled())
		{
			if(deltaInSeconds > g_Game.GetMCKConfig().Get_MaxLifetime())
			{
				m_MCKLogger.LogMCKActivity(GetDisplayName() + " (" + m_CarScriptId + " - pos " + GetPosition() + ") deltaInSeconds was " + deltaInSeconds + " . Deleting car due to no player interaction. Last time refreshed: " + TimestampToString(m_LastInteractedWithUnixTime));
				Delete();
			}
			if(deltaInSeconds > g_Game.GetMCKConfig().Get_MaxLifetimeWithoutAnyPlayerInteraction() && !m_HadPlayerInteraction)
			{
				m_MCKLogger.LogMCKActivity(GetDisplayName() + " (" + m_CarScriptId + " - pos " + GetPosition() + ") deltaInSeconds was " + deltaInSeconds + " . Deleting car due to no player interaction. Last time refreshed: " + TimestampToString(m_LastInteractedWithUnixTime));
				Delete();
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