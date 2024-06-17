
class PluginMCKLogs extends PluginBase
{
	bool			m_LogEnabled	= false;
	bool			m_DoFileLogs	= false;
	FileHandle		m_MCKLogFile;
	string			m_profileFolder = "$profile:";
	string			m_MCKLogName	= "MCKActivity";
	
	int year, month, day, hour, minute, second;
	string sYear, sMonth, sDay, sHour, sMinute, sSecond, currentDateTime, currentTime;

#ifdef SERVER
	override void OnInit()
	{
		if (GetGame().IsServer())
		{		
			Print("Init: PluginMCKLogs");
			m_DoFileLogs = g_Game.GetMCKConfig().DoFileLogs;
			if(m_DoFileLogs)
			{
				//setting currentDateTime
				SetCurrentTime();
				string currentFileName = m_profileFolder + "/" + m_MCKLogName + currentDateTime + ".log";
			
				// Create New Log
				if (CreateNewLogFile(currentFileName))
				{				
					m_LogEnabled = true;
				}				
			}
		}
	}

	override void OnDestroy()
	{
		if (GetGame().IsServer())
		{
			// Close Log File
			Print("~PluginMCKLogs Closed");
			if(m_DoFileLogs && m_LogEnabled)
			{
				CloseFile(m_MCKLogFile);
			}
		}
	}
	
	bool CreateNewLogFile(string logFilePath)
	{
		if (GetGame().IsServer())
		{
			SetCurrentTime();		
			m_MCKLogFile = OpenFile(logFilePath, FileMode.WRITE);
			if (m_MCKLogFile != 0)
			{
				FPrintln(m_MCKLogFile, "Log Created: " + currentDateTime);
				return true;
			}
			Print("Unable to create" + logFilePath + " file in Profile.");
			return false;
		}
		return false;
	}

	void SetCurrentTime()
	{
		// Setting Time Variables for new file name
		GetYearMonthDay(year, month, day);
		GetHourMinuteSecond(hour, minute, second);
		
		// Setting String for Time Variables for new file name
		sYear = year.ToString();
		
		sMonth = month.ToString();
		if (sMonth.Length() == 1)
		{
			sMonth = "0" + sMonth;
		}
		
		sDay = day.ToString();
		if (sDay.Length() == 1)
		{
			sDay = "0" + sDay;
		}
		
		sHour = hour.ToString();
		if (sHour.Length() == 1)
		{
			sHour = "0" + sHour;
		}
		
		sMinute = minute.ToString();
		if (sMinute.Length() == 1)
		{
			sMinute = "0" + sMinute;
		}
		
		sSecond = second.ToString();
		if (sSecond.Length() == 1)
		{
			sSecond = "0" + sSecond;
		}
		
		currentDateTime = "_" + sYear + "-" + sMonth + "-" + sDay + "_" + sHour + "-" + sMinute + "-" + sSecond;
		currentTime = sHour + ":" + sMinute + ":" + sSecond + " | ";
	}

#endif	
	void LogMCKActivity(string text)
	{
		#ifdef SERVER
		if (GetGame().IsServer() && m_LogEnabled)
		{
			SetCurrentTime();			
			FPrintln(m_MCKLogFile, currentTime + text);
		}
		#endif	
	}
};

static void MCK_LogActivity(string message)
{	
	#ifdef SERVER
	PluginMCKLogs m_MCKLogger = PluginMCKLogs.Cast(GetPlugin(PluginMCKLogs));
	if(m_MCKLogger)
	{					
		m_MCKLogger.LogMCKActivity(message);
	}
	#endif	
}