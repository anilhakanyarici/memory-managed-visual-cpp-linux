#include "CharStream.h"
#include "IOException.h"

long CharStream::operator >(CharArray &buffer)
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

long CharStream::operator >>(String16 &buffer)
{
    CharArray array;
    long count = this->ReadLine(array, 0);
    array.Resize(count);
    buffer = array;
    return count;
}
long CharStream::operator >>(CharArray &buffer)
{
    return this->ReadLine(buffer, 0);
}
CharStream &CharStream::operator <(const CharArray &buffer)
{
    this->Write(buffer, 0, buffer.length());
    return *this;
}

CharStream &CharStream::operator <(const String16 &buffer)
{
    this->Write(buffer.charsReference(), 0, buffer.length());
    return *this;
}
CharStream &CharStream::operator <<(const CharArray &buffer)
{
    this->WriteLine(buffer, 0, buffer.length());
    return *this;
}

CharStream &CharStream::operator <<(const String16 &buffer)
{
    this->WriteLine(buffer.charsReference(), 0, buffer.length());
    return *this;
}
