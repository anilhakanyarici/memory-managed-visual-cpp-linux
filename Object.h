#ifndef OBJECT_H
#define OBJECT_H

#include "Defs.h"

class Object : public IStringable
{
public:
    Object();

    virtual bool Equals(const Object &obj) const;
    virtual long GetHashCode() const;

public:
    virtual String16 ToString() const;

    Object operator =(const char * str);
    Object operator =(byte value);
    Object operator =(short value);
    Object operator =(ushort value);
    Object operator =(int value);
    Object operator =(uint value);
    Object operator =(long value);
    Object operator =(ulong value);
};
struct WrappedByte : public Object
{
private:
    byte _value;
public:
    WrappedByte(byte value) { this->_value = value; }

    byte value() const { return this->_value; }

    String16 ToString() const override;
    long GetHashCode() const override { return this->_value; }
    bool Equals(const Object &obj) const override { return this->_value == ((const WrappedByte &)obj).value(); }

    static WrappedByte Parse(const String16 &value);

    WrappedByte operator =(byte value) { return WrappedByte(value); }
    byte operator =(const WrappedByte &walue) { return walue.value(); }
};
struct WrappedShort : public Object
{
private:
    short _value;
public:
    WrappedShort(short value) { this->_value = value; }

    short value() const { return this->_value; }

    String16 ToString() const override;
    long GetHashCode() const override { return this->_value; }
    bool Equals(const Object &obj) const override { return this->_value == ((const WrappedShort &)obj).value(); }

    static WrappedShort Parse(const String16 &value);

    WrappedShort operator =(short value) { return WrappedShort(value); }
    short operator =(const WrappedShort &walue) { return walue.value(); }
};
struct WrappedUnsignedShort : public Object
{
private:
    short _value;
public:
    WrappedUnsignedShort(ushort value) { this->_value = value; }

    ushort value() const { return this->_value; }

    String16 ToString() const override;
    long GetHashCode() const override { return this->_value; }
    bool Equals(const Object &obj) const override { return this->_value == ((const WrappedUnsignedShort &)obj).value(); }

    static WrappedUnsignedShort Parse(const String16 &value);

    WrappedUnsignedShort operator =(ushort value) { return WrappedUnsignedShort(value); }
    ushort operator =(const WrappedUnsignedShort &walue) { return walue.value(); }
};
struct WrappedInt : public Object
{
private:
    int _value;
public:
    WrappedInt(int value) { this->_value = value; }

    int value() const { return this->_value; }

    String16 ToString() const override;
    long GetHashCode() const override { return this->_value; }
    bool Equals(const Object &obj) const override { return this->_value == ((const WrappedInt &)obj).value(); }

    static WrappedInt Parse(const String16 &value);

    WrappedInt operator =(int value) { return WrappedInt(value); }
    int operator =(const WrappedInt &walue) { return walue.value(); }
};
struct WrappedUnsignedInt : public Object
{
private:
    uint _value;
public:
    WrappedUnsignedInt(uint value) { this->_value = value; }

    uint value() const { return this->_value; }

    String16 ToString() const override;
    long GetHashCode() const override { return this->_value; }
    bool Equals(const Object &obj) const override { return this->_value == ((const WrappedUnsignedInt &)obj).value(); }

    static WrappedUnsignedInt Parse(const String16 &value);

    WrappedUnsignedInt operator =(uint value) { return WrappedUnsignedInt(value); }
    uint operator =(const WrappedUnsignedInt &walue) { return walue.value(); }
};
struct WrappedLong : public Object
{
private:
    long _value;
public:
    WrappedLong(long value) { this->_value = value; }

    long value() const { return this->_value; }

    String16 ToString() const override;
    long GetHashCode() const override { return this->_value; }
    bool Equals(const Object &obj) const override { return this->_value == ((const WrappedLong &)obj).value(); }

    static WrappedLong Parse(const String16 &value);

    WrappedLong operator =(long value) { return WrappedLong(value); }
    long operator =(const WrappedLong &walue) { return walue.value(); }
};
struct WrappedUnsignedLong : public Object
{
private:
    ulong _value;
public:
    WrappedUnsignedLong(long value) { this->_value = value; }

    ulong value() const { return this->_value; }

    String16 ToString() const override;
    long GetHashCode() const override { return this->_value; }
    bool Equals(const Object &obj) const override { return this->_value == ((const WrappedUnsignedLong &)obj).value(); }

    static WrappedUnsignedLong Parse(const String16 &value);

    WrappedUnsignedLong operator =(ulong value) { return WrappedUnsignedLong(value); }
    ulong operator =(const WrappedUnsignedLong &walue) { return walue.value(); }
};
#endif // OBJECT_H
