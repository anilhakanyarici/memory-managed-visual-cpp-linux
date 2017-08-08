#include <cstdio>
#include <cstdlib>
#include <cmath>
#include "Convert.h"
#include "Exception.h"
#include "Text/Encoding.h"
#include "Char16.h"

String16 Convert::ToString(bool value)
{
    if(value)
        return "true";
    else return "false";
}
String16 Convert::ToString(byte value)
{
    int a = value;
    return Convert::ToString(a);
}
String16 Convert::ToString(char value)
{
    return String16(Char16(value));
}
String16 Convert::ToString(Char16 value)
{
    return String16(value);
}
String16 Convert::ToString(short value)
{
    char buffer[50];
    int len = sprintf(buffer, "%hd", value);
    buffer[len] = 0;
    String16 s = buffer;
    return s;
}
String16 Convert::ToString(ushort value)
{
    char buffer[50];
    int len = sprintf(buffer, "%hu", value);
    buffer[len] = 0;
    String16 s = buffer;
    return s;
}
String16 Convert::ToString(int value)
{
    char buffer[50];
    int len = sprintf(buffer, "%d", value);
    buffer[len] = 0;
    String16 s = buffer;
    return s;
}
String16 Convert::ToString(int value, const String16 &format)
{
    ByteArray utf8 = Encoding::UTF8.GetBytes(format.charsReference());
    char buffer[50];
    for(int i = 0; i < utf8.length(); i++)
        buffer[i] = (char)utf8[i];
    buffer[utf8.length()] = '\0';
    int len = sprintf(buffer, buffer, value);
    buffer[len] = 0;
    String16 s = buffer;
    return s;
}
String16 Convert::ToString(uint value)
{
    char buffer[50];
    int len = sprintf(buffer, "%u", value);
    buffer[len] = 0;
    String16 s = buffer;
    return s;
}
String16 Convert::ToString(uint value, const String16 &format)
{
    ByteArray utf8 = Encoding::UTF8.GetBytes(format.charsReference());
    char buffer[50];
    for(int i = 0; i < utf8.length(); i++)
        buffer[i] = (char)utf8[i];
    buffer[utf8.length()] = '\0';
    int len = sprintf(buffer, buffer, value);
    buffer[len] = 0;
    String16 s = buffer;
    return s;
}
String16 Convert::ToString(long value)
{
    char buffer[50];
    int len = sprintf(buffer, "%ld", value);
    buffer[len] = 0;
    String16 s = buffer;
    return s;
}
String16 Convert::ToString(long value, const String16 &format)
{
    ByteArray utf8 = Encoding::UTF8.GetBytes(format.charsReference());
    char buffer[50];
    for(int i = 0; i < utf8.length(); i++)
        buffer[i] = (char)utf8[i];
    buffer[utf8.length()] = '\0';
    int len = sprintf(buffer, buffer, value);
    buffer[len] = 0;
    String16 s = buffer;
    return s;
}
String16 Convert::ToString(ulong value)
{
    char buffer[50];
    int len = sprintf(buffer, "%lu", value);
    buffer[len] = 0;
    String16 s = buffer;
    return s;
}
String16 Convert::ToString(ulong value, const String16 &format)
{
    ByteArray utf8 = Encoding::UTF8.GetBytes(format.charsReference());
    char buffer[50];
    for(int i = 0; i < utf8.length(); i++)
        buffer[i] = (char)utf8[i];
    buffer[utf8.length()] = '\0';
    int len = sprintf(buffer, buffer, value);
    buffer[len] = 0;
    String16 s = buffer;
    return s;
}
String16 Convert::ToString(float value)
{
    char buffer[50];
    int len = 0;
    if(value < 0.0000001)
        len = sprintf(buffer, "%.7e", value);
    else
        len = sprintf(buffer, "%.7f", value);
    buffer[len] = 0;
    String16 s = buffer;
    if(value >= 0.0000001)
        s = s.TrimEnd("0.");
    return s;
}
String16 Convert::ToString(float value, const String16 &format)
{
    ByteArray utf8 = format.ToCString();
    char buffer[50];
    buffer[utf8.length()] = '\0';
    int len = sprintf(buffer, (char *)utf8.data(), value);
    buffer[len] = 0;
    String16 s = buffer;
    return s;
}
String16 Convert::ToString(double value)
{
    char buffer[50];
    int len = 0;
    if(value < 0.0000000000000001)
        len = sprintf(buffer, "%.16e", value);
    else
        len = sprintf(buffer, "%.16f", value);
    buffer[len] = 0;
    String16 s = buffer;
    if(value >= 0.0000000000000001)
        s = s.TrimEnd("0.");
    return s;
}
String16 Convert::ToString(double value, const String16 &format)
{
    ByteArray utf8 = format.ToCString();
    char buffer[50];
    buffer[utf8.length()] = '\0';
    int len = sprintf(buffer, (char *)utf8.data(), value);
    buffer[len] = 0;
    String16 s = buffer;
    return s;
}

String16 Convert::ToString(void *pointer)
{
    char buffer[50];
    int len = sprintf(buffer, "%p", pointer);
    buffer[len] = 0;
    String16 s = buffer;
    return s;
}

bool Convert::ToBool(const String16 &value)
{
    String16 lower = ((String16&)value).ToLower();
    if(lower.Equals("true"))
        return true;
    else if(lower.Equals("false"))
        return false;
    else
        throw FormatException("Input was not a Boolean expression.");
}
short Convert::ToInt16(const String16 &value)
{
    if(!value.isInteger())
        throw FormatException("Attempted to convert non numeric characters to number.");
    ByteArray enc = Encoding::UTF8.GetBytes(value.charsReference());
    char cStyle[enc.length() + 1];
    for(int i = 0; i < enc.length(); i++)
        cStyle[i] = (char)enc[i];
    cStyle[enc.length()] = '\0';
    short v = strtol(cStyle, 0, 10);
    return v;
}
ushort Convert::ToUInt16(const String16 &value)
{
    if(!value.isInteger())
        throw FormatException("Attempted to convert non numeric characters to number.");
    ByteArray enc = Encoding::UTF8.GetBytes(value.charsReference());
    char cStyle[enc.length() + 1];
    for(int i = 0; i < enc.length(); i++)
        cStyle[i] = (char)enc[i];
    cStyle[enc.length()] = '\0';
    ushort v = strtoul(cStyle, 0, 10);
    return v;
}
int Convert::ToInt32(const String16 &value)
{
    if(!value.isInteger())
        throw FormatException("Attempted to convert non numeric characters to number.");
    ByteArray enc = Encoding::UTF8.GetBytes(value.charsReference());
    char cStyle[enc.length() + 1];
    for(int i = 0; i < enc.length(); i++)
        cStyle[i] = (char)enc[i];
    cStyle[enc.length()] = '\0';
    int v = strtol(cStyle, 0, 10);
    return v;
}
uint Convert::ToUInt32(const String16 &value)
{
    if(!value.isInteger())
        throw FormatException("Attempted to convert non numeric characters to number.");
    ByteArray enc = Encoding::UTF8.GetBytes(value.charsReference());
    char cStyle[enc.length() + 1];
    for(int i = 0; i < enc.length(); i++)
        cStyle[i] = (char)enc[i];
    cStyle[enc.length()] = '\0';
    uint v = strtoul(cStyle, 0, 10);
    return v;
}
long Convert::ToInt64(const String16 &value)
{
    if(!value.isInteger())
        throw FormatException("Attempted to convert non numeric characters to number.");
    ByteArray enc = Encoding::UTF8.GetBytes(value.charsReference());
    char cStyle[enc.length() + 1];
    for(int i = 0; i < enc.length(); i++)
        cStyle[i] = (char)enc[i];
    cStyle[enc.length()] = '\0';
    long v = strtol(cStyle, 0, 10);
    return v;
}
ulong Convert::ToUInt64(const String16 &value)
{
    if(!value.isInteger())
        throw FormatException("Attempted to convert non numeric characters to number.");
    ByteArray enc = Encoding::UTF8.GetBytes(value.charsReference());
    char cStyle[enc.length() + 1];
    for(int i = 0; i < enc.length(); i++)
        cStyle[i] = (char)enc[i];
    cStyle[enc.length()] = '\0';
    ulong v = strtoul(cStyle, 0, 10);
    return v;
}
float Convert::ToFloat(const String16 &value)
{
    if(!value.isNumeric())
        throw FormatException("Attempted to convert non numeric characters to number.");
    ByteArray enc = Encoding::UTF8.GetBytes(value.charsReference());
    char cStyle[enc.length() + 1];
    for(int i = 0; i < enc.length(); i++)
        cStyle[i] = (char)enc[i];
    cStyle[enc.length()] = '\0';
    double v = strtod(cStyle, 0);
    return (float)v;
}
double Convert::ToDouble(const String16 &value)
{
    if(!value.isNumeric())
        throw FormatException("Attempted to convert non numeric characters to number.");
    ByteArray enc = Encoding::UTF8.GetBytes(value.charsReference());
    char cStyle[enc.length() + 1];
    for(int i = 0; i < enc.length(); i++)
        cStyle[i] = (char)enc[i];
    cStyle[enc.length()] = '\0';
    double v = strtod(cStyle, 0);
    return v;
}
