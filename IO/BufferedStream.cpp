#include "BufferedStream.h"
#include "../Exception.h"

struct BufferedStream::_impl
{
    ByteArray _buffer;
    StreamMode _mode;
    long _length;
    long _read;
    ByteStream *_base;
};

BufferedStream::BufferedStream(ByteStream *baseStream, StreamMode mode, long bufferSize)
{
    if(bufferSize < 1)
        throw ArgumentException("Buffer size cannot be less than 1.", "bufferSize");
    switch (mode) {
    case StreamMode::Write:
        if(!baseStream->canWrite())
            throw NotSupportedException("Base stream must be writable.");
        break;
    case StreamMode::Read:
        if(!baseStream->canRead())
            throw NotSupportedException("Base stream must be readable.");
        break;
    default:
        throw InvalidOperationException("Stream mode was not recognized.");
        break;
    }

    this->_pImpl = new BufferedStream::_impl();
    this->_pImpl->_buffer = ByteArray(bufferSize);
    this->_pImpl->_mode = mode;
    this->_pImpl->_read = 0;
    this->_pImpl->_length = 0;
    this->_pImpl->_base = baseStream;
}

long BufferedStream::availableDataLength()
{
    if(this->_pImpl == nullptr)
        throw ObjectClosedException("BufferedStream was closed.", "BufferedStream");
    if(this->canRead())
        return this->_pImpl->_length - this->_pImpl->_read;
    else return this->_pImpl->_length;
}

ByteStream &BufferedStream::baseStream() const
{
    if(this->_pImpl == nullptr)
        throw ObjectClosedException("BufferedStream was closed.", "BufferedStream");
    return *this->_pImpl->_base;
}

bool BufferedStream::canRead() const
{
    if(this->_pImpl == nullptr)
        return false;
    return this->_pImpl->_mode == StreamMode::Read;
}

bool BufferedStream::canSeek() const
{
    return false;
}

bool BufferedStream::canWrite() const
{
    if(this->_pImpl == nullptr)
        return false;
    return this->_pImpl->_mode == StreamMode::Write;
}

bool BufferedStream::isClosed() const
{
    return this->_pImpl == nullptr;
}

long BufferedStream::length() const
{
    throw NotSupportedException("Seeking operations was not supported.");
}

void BufferedStream::length(long length)
{
    throw NotSupportedException("Seeking operations was not supported.");
    UseParameter(length);
}

long BufferedStream::position() const
{
    throw NotSupportedException("Seeking operations was not supported.");
}

ByteStream &BufferedStream::position(long position)
{
   throw NotSupportedException("Seeking operations was not supported.");
    UseParameter(position);
}

void BufferedStream::Close()
{
    if(this->_pImpl == nullptr)
        return;
    delete this->_pImpl;
    this->_pImpl = nullptr;
}

long BufferedStream::Flush()
{
    if(this->_pImpl == nullptr)
        throw ObjectClosedException("BufferedStream was closed.");
    if(!this->canWrite())
        throw NotSupportedException("Writing operations not supported for this BufferedStream.");
    this->_pImpl->_base->Write(this->_pImpl->_buffer, 0, this->_pImpl->_length);
    this->_pImpl->_length = 0;
    return this->_pImpl->_base->Flush();
}

long BufferedStream::Read(ByteArray &buffer, long offset, long count)
{
    if(this->_pImpl == nullptr)
        throw ObjectClosedException("BufferedStream was closed.");
    if(!this->canRead())
        throw NotSupportedException("Reading operations not supported for this BufferedStream.");
    if(offset < 0)
        throw ArgumentOutOfRangeException("Offset cannot be less than zero.", "offset");
    if(offset > buffer.length())
        throw ArgumentOutOfRangeException("Offset cannot be greater than buffer length.", "offset");
    if(count < 0)
        throw ArgumentOutOfRangeException("Count cannot be less than zero.");

    if(this->_pImpl->_read == this->_pImpl->_length){
        long read = this->_pImpl->_base->Read(this->_pImpl->_buffer, 0, this->_pImpl->_buffer.length());
        this->_pImpl->_length = read;
        this->_pImpl->_read = 0;
    }
    long readable = this->_pImpl->_length - this->_pImpl->_read;
    long read = count < readable ? count : readable;
    if(read <= 0)
        return read;
    if(offset + read > buffer.length())
        buffer.Resize(offset + read);
    this->_pImpl->_buffer.CopyTo(this->_pImpl->_read, buffer, offset, read);
    this->_pImpl->_read += read;
    count -= read;
    if(count > 0){
        return read + this->Read(buffer, offset + count, count);
    } else return read;
}

long BufferedStream::Seek(long offset, SeekOrigin origin)
{
    throw NotSupportedException("Seeking operations was not supported.");
    UseParameter(offset);
    UseParameter(origin);
}

long BufferedStream::Write(const ByteArray &buffer, long offset, long count)
{
    if(this->_pImpl == nullptr)
        throw ObjectClosedException("BufferedStream was closed.");
    if(!this->canWrite())
        throw NotSupportedException("Writing operations not supported for this BufferedStream.");
    if(offset < 0)
        throw ArgumentOutOfRangeException("Offset cannot be less than zero.", "offset");
    if(offset + count > buffer.length())
        throw OutOfRangeException("Block boundries was out of range of source block.");
    if(count < 0)
        throw ArgumentOutOfRangeException("Count cannot be less than zero.");

    long writable = this->_pImpl->_buffer.length() - this->_pImpl->_length;
    long write = count < writable ? count : writable;

    buffer.CopyTo(offset, this->_pImpl->_buffer, this->_pImpl->_length, write);
    count -= write;
    this->_pImpl->_length += write;

    if(this->_pImpl->_length == this->_pImpl->_buffer.length())
        this->Flush();
    if(count == 0)
        return write;
    else return write + this->Write(buffer, offset + write, count);
}

