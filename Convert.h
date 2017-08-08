#ifndef CONVERT_H
#define CONVERT_H

#include "Defs.h"
#include "String16.h"

class Convert
{
public:

    static String16 ToString(bool value);
    static String16 ToString(byte value);
    static String16 ToString(char value);
    static String16 ToString(Char16 value);
    static String16 ToString(short value);
    static String16 ToString(ushort value);
    static String16 ToString(int value);
    static String16 ToString(int value, const String16 &format);
    static String16 ToString(uint value);
    static String16 ToString(uint value, const String16 &format);
    static String16 ToString(long value);
    static String16 ToString(long value, const String16 &format);
    static String16 ToString(ulong value);
    static String16 ToString(ulong value, const String16 &format);
    static String16 ToString(float value);
    static String16 ToString(float value, const String16 &format); //format from snprintf
    static String16 ToString(double value);
    static String16 ToString(double value, const String16 &format); //format from snprintf
    static String16 ToString(void *pointer);

    static bool ToBool(const String16 &value);
    static short ToInt16(const String16 &value);
    static ushort ToUInt16(const String16 &value);
    static int ToInt32(const String16 &value);
    static uint ToUInt32(const String16 &value);
    static long ToInt64(const String16 &value);
    static ulong ToUInt64(const String16 &value);
    static float ToFloat(const String16 &value);
    static double ToDouble(const String16 &value);
};

#endif // CONVERT_H
