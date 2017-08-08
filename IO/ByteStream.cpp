#include "ByteStream.h"
#include "IOException.h"

ByteStream &ByteStream::operator <(const ByteArray &buffer)
{
    this->Write(buffer, 0, buffer.length());
    return *this;
}
long ByteStream::operator >(ByteArray &buffer)
{
    long count = buffer.length();
    long offset = 0;
    long read = 0;

    do{
        offset += read;
        read = this->Read(buffer, offset, count - offset);
    }while(offset < count && read > 0);

    return offset;
}
