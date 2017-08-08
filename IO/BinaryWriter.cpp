#include "BinaryWriter.h"
#include "../Exception.h"
#include "../ISerializable.h"

struct BinaryWriter::_impl
{
    ByteStream *_baseStream;
    ByteArray _temp;
    uint _refc = 1;
};

BinaryWriter::BinaryWriter(ByteStream *baseStream)
{
    if(!baseStream->canWrite())
        throw NotSupportedException("Base stream must be writable.");
    this->_pImpl = new BinaryWriter::_impl();
    this->_pImpl->_baseStream = baseStream;
    this->_pImpl->_temp = ByteArray(32);
}

const ByteStream &BinaryWriter::baseStream() const
{
    return *this->_pImpl->_baseStream;
}

long BinaryWriter::Flush()
{
    return this->_pImpl->_baseStream->Flush();
}

BinaryWriter &BinaryWriter::Write(bool value)
{
    byte *tmpData = this->_pImpl->_temp.data();
    tmpData[0] = (byte)value;
    return this->Write(this->_pImpl->_temp, 0, 1);
}

BinaryWriter &BinaryWriter::Write(byte value)
{
    byte *tmpData = this->_pImpl->_temp.data();
    tmpData[0] = value;
    return this->Write(this->_pImpl->_temp, 0, 1);
}

BinaryWriter &BinaryWriter::Write(char value)
{
    byte *tmpData = this->_pImpl->_temp.data();
    tmpData[0] = (byte)value;
    return this->Write(this->_pImpl->_temp, 0, 1);
}

BinaryWriter &BinaryWriter::Write(Char16 value)
{
    return this->Write(value.unicode());
}

BinaryWriter &BinaryWriter::Write(short value)
{
    byte *tmpData = this->_pImpl->_temp.data();
    byte *valData = (byte *)&value;
    tmpData[0] = valData[0];
    tmpData[1] = valData[1];
    return this->Write(this->_pImpl->_temp, 0, 2);
}

BinaryWriter &BinaryWriter::Write(ushort value)
{
    byte *tmpData = this->_pImpl->_temp.data();
    byte *valData = (byte *)&value;
    tmpData[0] = valData[0];
    tmpData[1] = valData[1];
    return this->Write(this->_pImpl->_temp, 0, 2);
}

BinaryWriter &BinaryWriter::Write(int value)
{
    byte *tmpData = this->_pImpl->_temp.data();
    byte *valData = (byte *)&value;
    tmpData[0] = valData[0];
    tmpData[1] = valData[1];
    tmpData[2] = valData[2];
    tmpData[3] = valData[3];
    return this->Write(this->_pImpl->_temp, 0, 4);
}

BinaryWriter &BinaryWriter::Write(uint value)
{
    byte *tmpData = this->_pImpl->_temp.data();
    byte *valData = (byte *)&value;
    tmpData[0] = valData[0];
    tmpData[1] = valData[1];
    tmpData[2] = valData[2];
    tmpData[3] = valData[3];
    return this->Write(this->_pImpl->_temp, 0, 4);
}

BinaryWriter &BinaryWriter::Write(long value)
{
    byte *tmpData = this->_pImpl->_temp.data();
    byte *valData = (byte *)&value;
    tmpData[0] = valData[0];
    tmpData[1] = valData[1];
    tmpData[2] = valData[2];
    tmpData[3] = valData[3];
    tmpData[4] = valData[4];
    tmpData[5] = valData[5];
    tmpData[6] = valData[6];
    tmpData[7] = valData[7];
    return this->Write(this->_pImpl->_temp, 0, 8);
}

BinaryWriter &BinaryWriter::Write(ulong value)
{
    byte *tmpData = this->_pImpl->_temp.data();
    byte *valData = (byte *)&value;
    tmpData[0] = valData[0];
    tmpData[1] = valData[1];
    tmpData[2] = valData[2];
    tmpData[3] = valData[3];
    tmpData[4] = valData[4];
    tmpData[5] = valData[5];
    tmpData[6] = valData[6];
    tmpData[7] = valData[7];
    return this->Write(this->_pImpl->_temp, 0, 8);
}

BinaryWriter &BinaryWriter::Write(float value)
{
    byte *tmpData = this->_pImpl->_temp.data();
    byte *valData = (byte *)&value;
    tmpData[0] = valData[0];
    tmpData[1] = valData[1];
    tmpData[2] = valData[2];
    tmpData[3] = valData[3];
    return this->Write(this->_pImpl->_temp, 0, 4);
}

BinaryWriter &BinaryWriter::Write(double value)
{
    byte *tmpData = this->_pImpl->_temp.data();
    byte *valData = (byte *)&value;
    tmpData[0] = valData[0];
    tmpData[1] = valData[1];
    tmpData[2] = valData[2];
    tmpData[3] = valData[3];
    tmpData[4] = valData[4];
    tmpData[5] = valData[5];
    tmpData[6] = valData[6];
    tmpData[7] = valData[7];
    return this->Write(this->_pImpl->_temp, 0, 8);
}

BinaryWriter &BinaryWriter::Write(const ByteArray &value)
{
    this->Write7BitEncodedLong(value.length());
    return this->Write(value, 0, value.length());
}

BinaryWriter &BinaryWriter::Write(const ISerializable &value)
{
    value.GetSerializationData(this);
    return *this;
}

BinaryWriter &BinaryWriter::Write(const CharArray &value, Encoder &encoder)
{
    ByteArray encode = encoder.GetBytes(value, 0, value.length());
    this->Write7BitEncodedLong(encode.length());
    return this->Write(encode, 0, encode.length());
}

BinaryWriter &BinaryWriter::Write(const String16 &value, Encoder &encoder)
{
    ByteArray encode = encoder.GetBytes(value.charsReference(), 0, value.length());
    this->Write7BitEncodedLong(encode.length());
    return this->Write(encode, 0, encode.length());
}

BinaryWriter &BinaryWriter::Write(const char *value, Encoder &encoder)
{
    CharArray chars = CharArray(value);
    ByteArray encode = encoder.GetBytes(chars, 0, chars.length());
    this->Write7BitEncodedLong(encode.length());
    return this->Write(encode, 0, encode.length());
}

BinaryWriter &BinaryWriter::Write7BitEncodedLong(long value)
{
    ulong v = (ulong) value;
    int bitInd = 0;
    byte *tmpData = this->_pImpl->_temp.data();
    while (v >= 128) {
        tmpData[bitInd++] = (byte)(v | 128);
        v >>= 7;
    }
    tmpData[bitInd++] = (byte)v;
    return this->Write(this->_pImpl->_temp, 0, bitInd);
}

BinaryWriter::BinaryWriter(const BinaryWriter &writer)
{
    this->_pImpl = writer._pImpl;
    if(this->_pImpl != nullptr)
        this->_pImpl->_refc++;
}

BinaryWriter &BinaryWriter::operator =(const BinaryWriter &writer)
{
    if(this->_pImpl != writer._pImpl){
        if(this->_pImpl != nullptr){
            if(this->_pImpl->_refc == 1){
                delete this->_pImpl;
            } else this->_pImpl->_refc--;
        }
        this->_pImpl = writer._pImpl;
        if(writer._pImpl != nullptr)
            this->_pImpl->_refc++;
    } return *this;
}

BinaryWriter::~BinaryWriter()
{
    if(this->_pImpl != nullptr){
        if(this->_pImpl->_refc == 1){
            delete this->_pImpl;
        } else this->_pImpl->_refc--;
    }
}

BinaryWriter &BinaryWriter::Write(const ByteArray &buffer, long offset, long count)
{
    this->_pImpl->_baseStream->Write((ByteArray)buffer, offset, count);
    return *this;
}

