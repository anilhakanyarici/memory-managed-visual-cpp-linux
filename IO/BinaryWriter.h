#ifndef BINARYWRITER_H
#define BINARYWRITER_H

#include "ByteStream.h"
#include "../Text/Encoding.h"

class ISerializable;
class BinaryWriter
{
    PIMPL
public:
    BinaryWriter(ByteStream *baseStream);

    const ByteStream &baseStream() const;

    long Flush();

    BinaryWriter &Write(const ByteArray &buffer, long offset, long count);

    BinaryWriter &Write(bool value);
    BinaryWriter &Write(byte value);
    BinaryWriter &Write(char value);
    BinaryWriter &Write(Char16 value); //UTF16
    BinaryWriter &Write(short value);
    BinaryWriter &Write(ushort value);
    BinaryWriter &Write(int value);
    BinaryWriter &Write(uint value);
    BinaryWriter &Write(long value);
    BinaryWriter &Write(ulong value);
    BinaryWriter &Write(float value);
    BinaryWriter &Write(double value);
    BinaryWriter &Write(const ByteArray &value);
    BinaryWriter &Write(const ISerializable &value);
    BinaryWriter &Write(const CharArray &value, Encoder &encoder = Encoder::UTF8);
    BinaryWriter &Write(const String16 &value, Encoder &encoder = Encoder::UTF8);
    BinaryWriter &Write(const char *value, Encoder &encoder = Encoder::UTF8);
    BinaryWriter &Write7BitEncodedLong(long value);

    inline BinaryWriter &operator < (bool value) { return this->Write(value); }
    inline BinaryWriter &operator << (bool value) { return this->Write(value); }
    inline BinaryWriter &operator < (char value) { return this->Write(value); }
    inline BinaryWriter &operator << (char value) { return this->Write(value); }
    inline BinaryWriter &operator < (byte value) { return this->Write(value); }
    inline BinaryWriter &operator << (byte value) { return this->Write(value); }
    inline BinaryWriter &operator < (Char16 value) { return this->Write(value); }
    inline BinaryWriter &operator << (Char16 value) { return this->Write(value); }
    inline BinaryWriter &operator < (short value) { return this->Write(value); }
    inline BinaryWriter &operator << (short value) { return this->Write(value); }
    inline BinaryWriter &operator < (ushort value) { return this->Write(value); }
    inline BinaryWriter &operator << (ushort value) { return this->Write(value); }
    inline BinaryWriter &operator < (int value) { return this->Write(value); }
    inline BinaryWriter &operator << (int value) { return this->Write(value); }
    inline BinaryWriter &operator < (uint value) { return this->Write(value); }
    inline BinaryWriter &operator << (uint value) { return this->Write(value); }
    inline BinaryWriter &operator < (long value) { return this->Write(value); }
    inline BinaryWriter &operator << (ulong value) { return this->Write(value); }
    inline BinaryWriter &operator < (float value) { return this->Write(value); }
    inline BinaryWriter &operator << (float value) { return this->Write(value); }
    inline BinaryWriter &operator < (double value) { return this->Write(value); }
    inline BinaryWriter &operator << (double value) { return this->Write(value); }
    inline BinaryWriter &operator < (const String16 &value) { return this->Write(value); }
    inline BinaryWriter &operator << (const String16 &value) { return this->Write(value); }
    inline BinaryWriter &operator < (const char *value) { return this->Write(value); }
    inline BinaryWriter &operator << (const char *value) { return this->Write(value); }
    inline BinaryWriter &operator < (const CharArray &value) { return this->Write(value); }
    inline BinaryWriter &operator << (const CharArray &value) { return this->Write(value); }
    inline BinaryWriter &operator < (const ByteArray &value) { return this->Write(value); }
    inline BinaryWriter &operator << (const ByteArray &value) { return this->Write(value); }

    BinaryWriter(const BinaryWriter &writer);
    BinaryWriter &operator =(const BinaryWriter &writer);
    ~BinaryWriter();
};
#endif // BINARYWRITER_H
