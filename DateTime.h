#ifndef DATETIME_H
#define DATETIME_H

#include <ctime>
#include "Defs.h"
#include "ISerializable.h"
#include "Object.h"

struct DateTime final : public Object, public ISerializable
{
public:
    DateTime();
    DateTime(long time);
    DateTime(int year, int month, int day) : DateTime(year, month, day, 0, 0, 0){ }
    DateTime(int year, int month, int day, int hour, int minute, int second);

    static DateTime Now();

    int day() const;
    String16 dayOfWeek() const;
    int dayOfYear() const;
    int hour() const;
    int minute() const;
    int month() const;
    String16 monthOfYear() const;
    int second() const;
    int year() const;

    void AddDay(int day);
    void AddHour(int hour);
    void AddMinute(int min);
    void AddMonth(int month);
    void AddSecond(int sec);
    void AddYear(int year);
    long ToLong() const;
    String16 ToString() const override;
    String16 ToString(String16 format) const;
    DateTime ToUniversalTime() const;

private:
    time_t _time_;
    tm* _tmStruct;

    // ISerializable interface
public:
    void GetSerializationData(BinaryWriter *writer) const override;
    bool SetSerializationData(BinaryReader *reader) override;

    // Object interface
public:
    bool Equals(const Object &obj) const override;
    long GetHashCode() const override;
};

#endif // DATETIME_H
