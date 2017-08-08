#ifndef BINARYREADER_H
#define BINARYREADER_H

#include "ByteStream.h"
#include "../CharArray.h"
#include "../Text/Decoder.h"

class ISerializable;
class BinaryReader
{
    PIMPL
public:
    BinaryReader(ByteStream *baseStream);

    const ByteStream &baseStream() const;

    bool Read(ByteArray &buffer, long offset, long count);

    bool Read(bool &value);
    bool Read(byte &value);
    bool Read(char &value);
    bool Read(Char16 &value); //UTF16
    bool Read(short &value);
    bool Read(ushort &value);
    bool Read(int &value);
    bool Read(uint &value);
    bool Read(long &value);
    bool Read(ulong &value);
    bool Read(float &value);
    bool Read(double &value);
    bool Read(ByteArray &value);
    bool Read(ISerializable &value);
    bool Read(CharArray &value, Decoder &decoder = Decoder::UTF8);
    bool Read(String16 &value, Decoder &decoder = Decoder::UTF8);
    bool Read7BitEncodedLong(long &value);

    inline bool operator > (bool &value) { return this->Read(value); }
    inline bool operator >> (bool &value) { return this->Read(value); }
    inline bool operator > (char &value) { return this->Read(value); }
    inline bool operator >> (char &value) { return this->Read(value); }
    inline bool operator > (byte &value) { return this->Read(value); }
    inline bool operator >> (byte &value) { return this->Read(value); }
    inline bool operator > (Char16 &value) { return this->Read(value); }
    inline bool operator >> (Char16 &value) { return this->Read(value); }
    inline bool operator > (short &value) { return this->Read(value); }
    inline bool operator >> (short &value) { return this->Read(value); }
    inline bool operator > (ushort &value) { return this->Read(value); }
    inline bool operator >> (ushort &value) { return this->Read(value); }
    inline bool operator > (int &value) { return this->Read(value); }
    inline bool operator >> (int &value) { return this->Read(value); }
    inline bool operator > (uint &value) { return this->Read(value); }
    inline bool operator >> (uint &value) { return this->Read(value); }
    inline bool operator > (long &value) { return this->Read(value); }
    inline bool operator >> (ulong &value) { return this->Read(value); }
    inline bool operator > (float &value) { return this->Read(value); }
    inline bool operator >> (float &value) { return this->Read(value); }
    inline bool operator > (double &value) { return this->Read(value); }
    inline bool operator >> (double &value) { return this->Read(value); }
    inline bool operator > (String16 &value) { return this->Read(value); }
    inline bool operator >> (String16 &value) { return this->Read(value); }
    inline bool operator > (CharArray &value) { return this->Read(value); }
    inline bool operator >> (CharArray &value) { return this->Read(value); }
    inline bool operator > (ByteArray &value) { return this->Read(value); }
    inline bool operator >> (ByteArray &value) { return this->Read(value); }

    BinaryReader(const BinaryReader &reader);
    BinaryReader &operator =(const BinaryReader &reader);
    ~BinaryReader();
};

#endif // BINARYREADER_H
