#include "Object.h"
#include "String16.h"
#include "Convert.h"

Object::Object()
{

}

bool Object::Equals(const Object &obj) const
{
    return this->GetHashCode() == obj.GetHashCode();
}
long Object::GetHashCode() const
{
    return ((long)this);
}

String16 Object::ToString() const
{
    return "Object";
}

Object Object::operator =(const char *str)
{
    return String16(str);
}
Object Object::operator =(byte value)
{
    return WrappedByte(value);
}
Object Object::operator =(short value)
{
    return WrappedShort(value);
}
Object Object::operator =(ushort value)
{
    return WrappedUnsignedShort(value);
}
Object Object::operator =(int value)
{
    return WrappedInt(value);
}
Object Object::operator =(uint value)
{
    return WrappedUnsignedInt(value);
}
Object Object::operator =(long value)
{
    return WrappedLong(value);
}
Object Object::operator =(ulong value)
{
    return WrappedUnsignedLong(value);
}

String16 WrappedShort::ToString() const
{
    return Convert::ToString(this->_value);
}

WrappedShort WrappedShort::Parse(const String16 &value)
{
    short v = Convert::ToInt16(value);
    return WrappedShort(v);
}
String16 WrappedUnsignedShort::ToString() const
{
    return Convert::ToString(this->_value);
}
WrappedUnsignedShort WrappedUnsignedShort::Parse(const String16 &value)
{
    ushort v = Convert::ToUInt16(value);
    return WrappedUnsignedShort(v);
}
String16 WrappedInt::ToString() const
{
    return Convert::ToString(this->_value);
}
WrappedInt WrappedInt::Parse(const String16 &value)
{
    int v = Convert::ToInt32(value);
    return WrappedInt(v);
}
String16 WrappedUnsignedInt::ToString() const
{
    return Convert::ToString(this->_value);
}

WrappedUnsignedInt WrappedUnsignedInt::Parse(const String16 &value)
{
    uint v = Convert::ToUInt32(value);
    return WrappedUnsignedInt(v);
}
String16 WrappedLong::ToString() const
{
    return Convert::ToString(this->_value);
}
WrappedLong WrappedLong::Parse(const String16 &value)
{
    long v = Convert::ToInt64(value);
    return WrappedLong(v);
}
String16 WrappedUnsignedLong::ToString() const
{
    return Convert::ToString(this->_value);
}
WrappedUnsignedLong WrappedUnsignedLong::Parse(const String16 &value)
{
    ulong v = Convert::ToUInt64(value);
    return WrappedUnsignedLong(v);
}
String16 WrappedByte::ToString() const
{
    return Convert::ToString(this->_value);
}
WrappedByte WrappedByte::Parse(const String16 &value)
{
    byte v = (byte)Convert::ToInt16(value);
    return WrappedByte(v);
}
