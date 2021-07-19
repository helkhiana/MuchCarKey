class PluginMCKLogs extends PluginBase
{
	bool			m_LogEnabled	= false;
	FileHandle		m_MCKLogFile;
	string			m_profileFolder		= "$profile:";
	string			m_MCKLogName 			= "MCKActivity";
	
	int year, month, day, hour, minute, second;
	string sYear, sMonth, sDay, sHour, sMinute, sSecond, currentDateTime, currentTime;
	
	void PluginMCKLogs()
	{
		Print("Init: PluginMCKLogs");
		
		if (!FileExist(m_profileFolder))
			MakeDirectory(m_profileFolder);	

		InitiateLogs(m_MCKLogName);
	}
	
	void ~PluginMCKLogs()
	{
		Print("~PluginMCKLogs Closed");
		if (GetGame().IsServer())
		{
			// Close Log File
			CloseFile(m_MCKLogFile);
		}
	}

	void InitiateLogs(string logFileName)
	{
		//setting currentDateTime
		SetCurrentTime();
		string currentFileName = m_profileFolder + "/" + logFileName + currentDateTime + ".log";
	
		// Create New Log
		if (this.CreateNewLogFile(currentFileName))
		{				
			m_LogEnabled = true;
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
	
	void LogMCKActivity(string text)
	{
		if (GetGame().IsMultiplayer())
		{
			SetCurrentTime();			
			FPrintln(m_MCKLogFile, currentTime + text);
		}
	}
};