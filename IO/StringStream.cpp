#include "StringStream.h"
#include "../Exception.h"

struct StringStream::_impl{
    CharArray _buffer;
    long _position = 0;
    long _length = 0;
};

StringStream::StringStream()
{
    this->_pImpl = new StringStream::_impl();
    this->_pImpl->_buffer.Resize(256);
}

StringStream::StringStream(const CharArray &buffer)
{
    this->_pImpl = new StringStream::_impl();
    this->_pImpl->_buffer = buffer;
    this->_pImpl->_length = buffer.length();
}

void StringStream::Clear()
{
    if(this->_pImpl == nullptr)
        throw ObjectClosedException("Object has already closed.", "StringStream");
    this->_pImpl->_buffer.Resize(256);
    this->_pImpl->_length = 0;
    this->_pImpl->_position = 0;
}

void StringStream::length(long length)
{
    if(this->_pImpl == nullptr)
        throw ObjectClosedException("Object has already closed.", "StringStream");
    if(length < 0)
        throw ArgumentOutOfRangeException("Stream length cannot be less than zero.", "length");

    long newSize = this->_pImpl->_buffer.length();
    while(newSize <= length)
        newSize <<= 1;
    if(length >= this->_pImpl->_buffer.length())
        this->_pImpl->_buffer.Resize(newSize);
    for(int i = this->_pImpl->_length; i < length; i++)
        this->_pImpl->_buffer[i] = 0;
    this->_pImpl->_length = length;
}

long StringStream::position() const
{
    if(this->_pImpl == nullptr)
        throw ObjectClosedException("Object has already closed.", "StringStream");
    return this->_pImpl->_position;
}

CharStream &StringStream::position(long position)
{
    if(this->_pImpl == nullptr)
        throw ObjectClosedException("Object has already closed.", "StringStream");
    if(position < 0)
        throw ArgumentOutOfRangeException("Stream position cannot be less than zero.", "position");
    if(position > this->_pImpl->_length)
        throw ArgumentOutOfRangeException("Stream position cannot be greater than stream length.", "position");
    this->_pImpl->_position = position;
    return *this;
}

void StringStream::Close()
{
    if(this->_pImpl == nullptr)
        return;
    delete this->_pImpl;
    this->_pImpl = nullptr;
}

long StringStream::Flush()
{
    if(this->_pImpl == nullptr)
        throw ObjectClosedException("Object has already closed.", "StringStream");
    return -1;
}

const CharArray &StringStream::getBuffer() const
{
    if(this->_pImpl == nullptr)
        throw ObjectClosedException("Object has already closed.", "StringStream");
    return this->_pImpl->_buffer;
}

long StringStream::Read(CharArray &buffer, long offset, long count)
{
    if(this->_pImpl == nullptr)
        throw ObjectClosedException("Object has already closed.", "StringStream");
    if(offset < 0)
        throw ArgumentOutOfRangeException("Offset cannot be less than zero.", "offset");
    if(offset > buffer.length())
        throw ArgumentOutOfRangeException("Offset cannot be greater than buffer length.", "offset");
    if(count < 0)
        throw InvalidOperationException("Count cannot be less than zero.");
    if(buffer.length() == 0)
        buffer.Resize(64);
    long readable = this->_pImpl->_length - this->_pImpl->_position;
    if(readable < count)
        count = readable;
    if (count == 0)
        return 0;
    if(offset + count > buffer.length())
        buffer.Resize(offset + count);

    Char16 *buffData = this->_pImpl->_buffer.data();
    Char16 *data = buffer.data();

    long lastIndex = offset + count;
    for(long i = offset; i < lastIndex; i++)
        data[i] = buffData[this->_pImpl->_position++];

    return count;
}

long StringStream::ReadLine(CharArray &buffer, long offset)
{
    if(this->_pImpl == nullptr)
        throw ObjectClosedException("Object has already closed.", "StringStream");
    if(offset < 0)
        throw ArgumentOutOfRangeException("Offset cannot be less than zero.", "offset");
    if(offset > buffer.length())
        throw ArgumentOutOfRangeException("Offset cannot be greater than buffer length.", "offset");

    Char16 *data = buffer.data();
    Char16 *buffData = this->_pImpl->_buffer.data();

     long nPos = this->_pImpl->_position;
     while(nPos < this->_pImpl->_length && buffData[nPos].unicode() != 12) nPos++;
     long count = nPos - this->_pImpl->_position;
     if(offset + count > buffer.length())
         buffer.Resize(offset + count);

     for(int i = this->_pImpl->_position; i < nPos; i++)
         data[offset++] = buffData[i];
     this->_pImpl->_position = nPos + 1;
     return count;
}

CharArray StringStream::ToArray() const
{
    if(this->_pImpl == nullptr)
        throw ObjectClosedException("Object has already closed.", "StringStream");
    CharArray array = CharArray(this->_pImpl->_length);
    this->_pImpl->_buffer.CopyTo(0, array, 0, this->_pImpl->_length);
    return array;
}

String16 StringStream::ToString() const
{
    return String16(this->_pImpl->_buffer, 0, this->_pImpl->_length);
}

bool StringStream::isClosed() const { return this->_pImpl == nullptr; }

long StringStream::length() const
{
    if(this->_pImpl == nullptr)
        throw ObjectClosedException("Object has already closed.", "StringStream");
     return this->_pImpl->_length;
}

long StringStream::Write(const CharArray &buffer, long offset, long count)
{
    if(this->_pImpl == nullptr)
        throw ObjectClosedException("Object has already closed.", "StringStream");
    if(count < 0)
        throw InvalidOperationException("Count cannot be less than zero.");
    if(buffer[offset + count].isHighSurrogate())
        count--;
    long writable = this->_pImpl->_length - this->_pImpl->_position;
    if(writable <= count){
        long length = this->_pImpl->_position + count;
        long newSize = this->_pImpl->_buffer.length();
        while(newSize <= length)
            newSize <<= 1;
        if(length >= this->_pImpl->_buffer.length())
            this->_pImpl->_buffer.Resize(newSize);
        this->_pImpl->_length = length;
    }
    buffer.CopyTo(offset, this->_pImpl->_buffer, this->_pImpl->_position, count);
    this->_pImpl->_position += count;
    return count;
}

long StringStream::WriteLine(const CharArray &buffer, long offset, long count)
{
    if(this->_pImpl == nullptr)
        throw ObjectClosedException("Object has already closed.", "StringStream");
    if(count < 0)
        throw InvalidOperationException("Count cannot be less than zero.");
    count++;
    long writable = this->_pImpl->_length - this->_pImpl->_position;
    if(writable <= count){
        long length = this->_pImpl->_position + count;
        long newSize = this->_pImpl->_buffer.length();
        while(newSize <= length)
            newSize <<= 1;
        if(length >= this->_pImpl->_buffer.length())
            this->_pImpl->_buffer.Resize(newSize);
        this->_pImpl->_length = length;
    }
    buffer.CopyTo(offset, this->_pImpl->_buffer, this->_pImpl->_position, count - 1);
    this->_pImpl->_position += count;
    this->_pImpl->_buffer[this->_pImpl->_position++] = Char16('\n');
    this->_pImpl->_length++;
    return count - 1;
}

long StringStream::Seek(long offset, SeekOrigin origin)
{
    if(this->_pImpl == nullptr)
        throw ObjectClosedException("Object has already closed.", "StringStream");
    switch (origin) {
    case SeekOrigin::Begin:
        this->position(offset);
        return this->position();
        break;
    case SeekOrigin::Current:
        this->position(this->position() + offset);
        break;
    case SeekOrigin::End:
        this->position(this->length() - offset);
        break;
    }
    return this->position();
}
