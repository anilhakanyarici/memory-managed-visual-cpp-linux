#include "DateTime.h"
#include "Convert.h"
#include "Exception.h"
#include "Char16.h"
#include "String16.h"
#include "IO/BinaryReader.h"
#include "IO/BinaryWriter.h"

DateTime::DateTime()
{
    this->_time_ = time(0);
    this->_tmStruct = localtime(&this->_time_);
}
DateTime::DateTime(long time)
{
    this->_time_ = time;
    this->_tmStruct = localtime(&this->_time_);
}
DateTime::DateTime(int year, int month, int day, int hour, int minute, int second)
{
    time_t raw;
    time(&raw);
    tm *_tm = localtime(&raw);
    _tm->tm_year = year - 1900;
    _tm->tm_mon = month - 1;
    _tm->tm_mday = day;
    _tm->tm_hour = hour;
    _tm->tm_min = minute;
    _tm->tm_sec = second;
    this->_time_ = mktime(_tm);
    this->_tmStruct = _tm;
}

DateTime DateTime::Now()
{
    return DateTime();
}

void DateTime::AddYear(int year)
{
    this->_tmStruct->tm_year += year;
    this->_time_ = mktime(this->_tmStruct);
}
int DateTime::day() const
{
    return this->_tmStruct->tm_mday;
}
void DateTime::AddMonth(int month)
{
    this->_tmStruct->tm_mon += month;
    this->_time_ = mktime(this->_tmStruct);
}
long DateTime::ToLong() const
{
    return (long)this->_time_;
}
String16 DateTime::ToString() const
{
    StringList joiners = StringList();
    joiners.Add(Convert::ToString(this->day(), "%.2d"));
    joiners.Add("/");
    joiners.Add(Convert::ToString(this->month(), "%.2d"));
    joiners.Add("/");
    joiners.Add(Convert::ToString(this->year()));
    joiners.Add(" ");
    joiners.Add(Convert::ToString(this->hour(), "%.2d"));
    joiners.Add(":");
    joiners.Add(Convert::ToString(this->minute(), "%.2d"));
    joiners.Add(":");
    joiners.Add(Convert::ToString(this->second(), "%.2d"));

    return joiners.Join("");
}
String16 DateTime::ToString(String16 format) const
{
    format = format.Replace("%ss", Convert::ToString(this->second(), "%.2d"));
    format = format.Replace("%s", Convert::ToString(this->second()));
    format = format.Replace("%dddd", this->dayOfWeek());
    format = format.Replace("%ddd", this->dayOfWeek().SubString(0, 3));
    format = format.Replace("%dd", Convert::ToString(this->day(), "%.2d"));
    format = format.Replace("%d", Convert::ToString(this->day()));
    format = format.Replace("%MMMM", this->monthOfYear());
    format = format.Replace("%MMM", this->monthOfYear().SubString(0, 3));
    format = format.Replace("%MM", Convert::ToString(this->month(), "%.2d"));
    format = format.Replace("%M", Convert::ToString(this->month()));
    format = format.Replace("%mm", Convert::ToString(this->minute(), "%.2d"));
    format = format.Replace("%m", Convert::ToString(this->minute()));
    format = format.Replace("%yyyy", Convert::ToString(this->year(), "%.4d"));
    format = format.Replace("%yyy", Convert::ToString(this->year(), "%.3d"));
    format = format.Replace("%yy", Convert::ToString(this->year() % 100, "%.2d"));
    format = format.Replace("%y", Convert::ToString(this->year() % 100));
    format = format.Replace("%HH", Convert::ToString(this->hour(), "%.2d"));
    format = format.Replace("%H", Convert::ToString(this->hour()));
    String16 affix = "AM";
    int h = this->hour();
    h = (h + 11) % 12 + 1;
    if(this->hour() >= 12){
        affix = "PM";
    }
    format = format.Replace("%hh", Convert::ToString(h, "%.2d").Append(affix));
    format = format.Replace("%h", Convert::ToString(h).Append(affix));
    return format;
}
DateTime DateTime::ToUniversalTime() const
{
    tm* _tm = gmtime(&this->_time_);
    time_t utc = mktime(_tm);
    return DateTime((long)utc);
}
int DateTime::year() const
{
    return this->_tmStruct->tm_year + 1900;
}

void DateTime::GetSerializationData(BinaryWriter *writer) const
{
    writer->Write((long)this->_time_);
}

bool DateTime::SetSerializationData(BinaryReader *reader)
{
    long time;
    if(!reader->Read(time)) return false;
    this->_time_ = time;
    this->_tmStruct = localtime(&this->_time_);
    return true;
}

bool DateTime::Equals(const Object &obj) const
{
    DateTime other = (const DateTime &)obj;
    return (long)other._time_ == (long)this->_time_;
}

long DateTime::GetHashCode() const
{
    return (long)this->_time_;
}
void DateTime::AddDay(int day)
{
    this->_tmStruct->tm_mday += day;
    this->_time_ = mktime(this->_tmStruct);
}
void DateTime::AddHour(int hour)
{
    this->_tmStruct->tm_hour += hour;
    this->_time_ = mktime(this->_tmStruct);
}
void DateTime::AddMinute(int min)
{
    this->_tmStruct->tm_min += min;
    this->_time_ = mktime(this->_tmStruct);
}
void DateTime::AddSecond(int sec)
{
    this->_tmStruct->tm_sec += sec;
    this->_time_ = mktime(this->_tmStruct);
}
String16 DateTime::dayOfWeek() const
{
    switch (this->_tmStruct->tm_wday) {
    case 0:
        return "Sunday";
    case 1:
        return "Monday";
    case 2:
        return "Tuesday";
    case 3:
        return "Wednesday";
    case 4:
        return "Thursday";
    case 5:
        return "Friday";
    case 6:
        return "Saturday";
    }
    throw Exception("Wrong DateTime struct.");
}
int DateTime::dayOfYear() const
{
    return this->_tmStruct->tm_yday;
}
int DateTime::hour() const
{
    return this->_tmStruct->tm_hour;
}
int DateTime::minute() const
{
    return this->_tmStruct->tm_min;
}
int DateTime::month() const
{
    return this->_tmStruct->tm_mon + 1;
}
String16 DateTime::monthOfYear() const
{
    switch(this->_tmStruct->tm_mon){
    case 0:
        return "January";
    case 1:
        return "February";
    case 2:
        return "March";
    case 3:
        return "April";
    case 4:
        return "May";
    case 5:
        return "June";
    case 6:
        return "July";
    case 7:
        return "August";
    case 8:
        return "September";
    case 9:
        return "October";
    case 10:
        return "November";
    case 11:
        return "December";
    }
    throw Exception("Wrong DateTime struct.");
}
int DateTime::second() const
{
    return this->_tmStruct->tm_sec;
}
