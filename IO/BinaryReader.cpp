#include "BinaryReader.h"
#include "../Exception.h"
#include "../ISerializable.h"

struct BinaryReader::_impl
{
    ByteStream *_baseStream;
    ByteArray _temp;
    uint _refc = 1;
};

BinaryReader::BinaryReader(ByteStream *baseStream)
{
    if(!baseStream->canRead())
        throw NotSupportedException("Base stream must be readable.");
    this->_pImpl = new BinaryReader::_impl();
    this->_pImpl->_baseStream = baseStream;
    this->_pImpl->_temp = ByteArray(32);
}

const ByteStream &BinaryReader::baseStream() const
{
    return *this->_pImpl->_baseStream;
}

bool BinaryReader::Read(ByteArray &buffer, long offset, long count)
{
    while(count > 0){
        long read = this->_pImpl->_baseStream->Read(buffer, offset, count);
        if(read < 1)
            return false;
        count -= read;
        offset += read;
    } return true;
}

bool BinaryReader::Read(bool &value)
{
    byte *tmpData = this->_pImpl->_temp.data();
    bool read = this->Read(this->_pImpl->_temp, 0, 1);
    value = (bool)tmpData[0];
    return read;
}

bool BinaryReader::Read(byte &value)
{
    byte *tmpData = this->_pImpl->_temp.data();
    bool read =this->Read(this->_pImpl->_temp, 0, 1);
    value = tmpData[0];
    return read;
}

bool BinaryReader::Read(char &value)
{
    byte *tmpData = this->_pImpl->_temp.data();
    bool read =this->Read(this->_pImpl->_temp, 0, 1);
    value = (char)tmpData[0];
    return read;
}

bool BinaryReader::Read(Char16 &value)
{
    byte *tmpData = this->_pImpl->_temp.data();
    bool read =this->Read(this->_pImpl->_temp, 0, 2);
    ushort unicode = *((ushort *)tmpData);
    value = Char16(unicode);
    return read;
}

bool BinaryReader::Read(short &value)
{
    byte *tmpData = this->_pImpl->_temp.data();
    bool read =this->Read(this->_pImpl->_temp, 0, 2);
    value =  *((short *)tmpData);
    return read;
}

bool BinaryReader::Read(ushort &value)
{
    byte *tmpData = this->_pImpl->_temp.data();
    bool read =this->Read(this->_pImpl->_temp, 0, 2);
    value =  *((ushort *)tmpData);
    return read;
}

bool BinaryReader::Read(int &value)
{
    byte *tmpData = this->_pImpl->_temp.data();
    bool read =this->Read(this->_pImpl->_temp, 0, 4);
    value =  *((int *)tmpData);
    return read;
}

bool BinaryReader::Read(uint &value)
{
    byte *tmpData = this->_pImpl->_temp.data();
    bool read =this->Read(this->_pImpl->_temp, 0, 4);
    value =  *((uint *)tmpData);
    return read;
}

bool BinaryReader::Read(long &value)
{
    byte *tmpData = this->_pImpl->_temp.data();
    bool read =this->Read(this->_pImpl->_temp, 0, 8);
    value =  *((long *)tmpData);
    return read;
}

bool BinaryReader::Read(ulong &value)
{
    byte *tmpData = this->_pImpl->_temp.data();
    bool read =this->Read(this->_pImpl->_temp, 0, 8);
    value =  *((ulong *)tmpData);
    return read;
}

bool BinaryReader::Read(float &value)
{
    byte *tmpData = this->_pImpl->_temp.data();
    bool read =this->Read(this->_pImpl->_temp, 0, 4);
    value =  *((float *)tmpData);
    return read;
}

bool BinaryReader::Read(double &value)
{
    byte *tmpData = this->_pImpl->_temp.data();
    bool read =this->Read(this->_pImpl->_temp, 0, 8);
    value =  *((double *)tmpData);
    return read;
}

bool BinaryReader::Read(ByteArray &value)
{
    long len;
    bool read = this->Read7BitEncodedLong(len);
    if(!read)
        return read;
    value.Resize(len);
    return this->Read(value, 0, len);
}

bool BinaryReader::Read(ISerializable &value)
{
    return value.SetSerializationData(this);
}

bool BinaryReader::Read(CharArray &value, Decoder &decoder)
{
    long len;
    bool read = this->Read7BitEncodedLong(len);
    if(!read)
        return read;
    ByteArray array = ByteArray(len);
    read = this->Read(array, 0, len);
    if(!read)
        return read;
    long bytesUsed, charsUsed;
    long charLen = decoder.GetLength(array, 0, len);
    value.Resize(charLen);
    decoder.Decode(array, 0, len, value, 0, charLen, &bytesUsed, &charsUsed);
    return read;
}

bool BinaryReader::Read(String16 &value, Decoder &decoder)
{
    long len;
    bool read = this->Read7BitEncodedLong(len);
    if(!read)
        return read;
    ByteArray array = ByteArray(len);
    read = this->Read(array, 0, len);
    if(!read)
        return read;
    long bytesUsed, charsUsed;
    long charLen = decoder.GetLength(array, 0, len);
    CharArray chars = CharArray(charLen);
    decoder.Decode(array, 0, len, chars, 0, charLen, &bytesUsed, &charsUsed);
    value = chars;
    return read;
}

bool BinaryReader::Read7BitEncodedLong(long &value)
{
    ulong count = 0;
    int shift = 0;
    byte b = 0;
    do {
        if (shift == 63)
            throw FormatException("Long had wrong 7 bit encode.");

        bool read = this->Read(b);
        if(!read)
            return read;
        count |= (b & 0x7Fl) << shift;
        shift += 7;
    } while ((b & 0x80) != 0);
    value = count;
    return true;
}

BinaryReader::BinaryReader(const BinaryReader &reader)
{
    this->_pImpl = reader._pImpl;
    if(this->_pImpl != nullptr)
        this->_pImpl->_refc++;
}

BinaryReader &BinaryReader::operator =(const BinaryReader &reader)
{
    if(this->_pImpl != reader._pImpl){
        if(this->_pImpl != nullptr){
            if(this->_pImpl->_refc == 1){
                delete this->_pImpl;
            } else this->_pImpl->_refc--;
        }
        this->_pImpl = reader._pImpl;
        if(reader._pImpl != nullptr)
            this->_pImpl->_refc++;
    } return *this;
}

BinaryReader::~BinaryReader()
{
    if(this->_pImpl != nullptr){
        if(this->_pImpl->_refc == 1){
            delete this->_pImpl;
        } else this->_pImpl->_refc--;
    }
}
