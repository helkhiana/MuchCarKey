static string TimestampToString(int timestamp)
{
    return CF_Date.Epoch(timestamp).ToString("YYYY-MM-DD hh:mm:ss"); 
};

static string SecondsToDays(int seconds)
{
    string Date = "";
    int days = seconds / (24 * 3600);
    Date += days.ToString() + "d ";
    seconds = seconds % (24 * 3600);
    int hours = seconds / 3600;
    Date += hours.ToString() + "h ";
    seconds = seconds % 3600;
    int minutes = seconds / 60;
    seconds = seconds % 60;
    Date += minutes.ToString() + "m ";
    Date += seconds.ToString() + "s ";
    return Date;
};