#include "MemoryStream.h"
#include "../Exception.h"

struct MemoryStream::_impl{
    ByteArray _buffer;
    long _position = 0;
    long _length = 0;
};

MemoryStream::MemoryStream()
{
    this->_pImpl = new MemoryStream::_impl();
    this->_pImpl->_buffer.Resize(256);
}

MemoryStream::MemoryStream(const ByteArray &buffer)
{
    this->_pImpl = new MemoryStream::_impl();
    this->_pImpl->_buffer = buffer;
    this->_pImpl->_length = buffer.length();
}

void MemoryStream::Clear()
{
    if(this->_pImpl == nullptr)
        throw ObjectClosedException("Object has already closed.", "MemoryStream");
    this->_pImpl->_buffer.Resize(256);
    this->_pImpl->_length = 0;
    this->_pImpl->_position = 0;
}

void MemoryStream::length(long length)
{
    if(this->_pImpl == nullptr)
        throw ObjectClosedException("Object has already closed.", "MemoryStream");
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

long MemoryStream::position() const
{
    if(this->_pImpl == nullptr)
        throw ObjectClosedException("Object has already closed.", "MemoryStream");
    return this->_pImpl->_position;
}

ByteStream &MemoryStream::position(long position)
{
    if(this->_pImpl == nullptr)
        throw ObjectClosedException("Object has already closed.", "MemoryStream");
    if(position < 0)
        throw ArgumentOutOfRangeException("Stream position cannot be less than zero.", "position");
    if(position > this->_pImpl->_length)
        throw ArgumentOutOfRangeException("Stream position cannot be greater than stream length.", "position");
    this->_pImpl->_position = position;
    return *this;
}

void MemoryStream::Close()
{
    if(this->_pImpl == nullptr)
        return;
    delete this->_pImpl;
    this->_pImpl = nullptr;
}

long MemoryStream::Flush()
{
    if(this->_pImpl == nullptr)
        throw ObjectClosedException("Object has already closed.", "MemoryStream");
    return -1;
}

const ByteArray &MemoryStream::getBuffer() const
{
    if(this->_pImpl == nullptr)
        throw ObjectClosedException("Object has already closed.", "MemoryStream");
    return this->_pImpl->_buffer;
}

long MemoryStream::Read(ByteArray &buffer, long offset, long count)
{
    if(this->_pImpl == nullptr)
        throw ObjectClosedException("Object has already closed.", "MemoryStream");
    if(offset < 0)
        throw ArgumentOutOfRangeException("Offset cannot be less than zero.", "offset");
    if(offset > buffer.length())
        throw ArgumentOutOfRangeException("Offset cannot be greater than buffer length.", "offset");
    if(count < 0)
        throw InvalidOperationException("Count cannot be less than zero.");
    long readable = this->_pImpl->_length - this->_pImpl->_position;
    if(readable < count)
        count = readable;
    if (count == 0)
        return 0;
    if(offset + count > buffer.length())
        buffer.Resize(offset + count);

    byte *data = this->_pImpl->_buffer.data();
    byte *buffData = buffer.data();

    long lastIndex = offset + count;
    for(long i = offset; i < lastIndex; i++){
        buffData[i] = data[this->_pImpl->_position++];
    }
    return count;
}

ByteArray MemoryStream::ToArray() const
{
    if(this->_pImpl == nullptr)
        throw ObjectClosedException("Object has already closed.", "MemoryStream");
    ByteArray array = ByteArray(this->_pImpl->_length);
    this->_pImpl->_buffer.CopyTo(0, array, 0, this->_pImpl->_length);
    return array;
}

bool MemoryStream::isClosed() const { return this->_pImpl == nullptr; }

long MemoryStream::length() const
{
    if(this->_pImpl == nullptr)
        throw ObjectClosedException("Object has already closed.", "MemoryStream");
     return this->_pImpl->_length;
}

long MemoryStream::Write(const ByteArray &buffer, long offset, long count)
{
    if(this->_pImpl == nullptr)
        throw ObjectClosedException("Object has already closed.", "MemoryStream");
    if(count < 0)
        throw InvalidOperationException("Count cannot be less than zero.");
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

long MemoryStream::Seek(long offset, SeekOrigin origin)
{
    if(this->_pImpl == nullptr)
        throw ObjectClosedException("Object has already closed.", "MemoryStream");
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
