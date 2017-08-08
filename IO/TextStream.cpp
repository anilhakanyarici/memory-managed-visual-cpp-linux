#include "TextStream.h"
#include "SPVT/Exception.h"

#define tmplen 1024

struct TextStream::_impl{
    ByteStream *_base;
    Encoding *_encoding;
    ByteArray _tempBuffer;
    int _tempPos;
    CharArray _charBuffer;
    int _charPos;
    int _bufferedCharCount;
    ByteArray _writeBuffer;
    long _writePos;
    StreamMode _mode;
};

TextStream::TextStream(ByteStream *baseStream, StreamMode mode, Encoding *encoding)
{
    this->_pImpl = new TextStream::_impl();
    switch (mode) {
    case StreamMode::Read:
        if(!baseStream->canRead())
            throw NotSupportedException("Base stream was not readable.");
        this->_pImpl->_tempPos = 0;
        this->_pImpl->_tempBuffer.Resize(tmplen);
        this->_pImpl->_charPos = 0;
        this->_pImpl->_bufferedCharCount = 0;
        this->_pImpl->_charBuffer.Resize(tmplen + 1);
        break;
    case StreamMode::Write:
        if(!baseStream->canWrite())
            throw NotSupportedException("Base stream was not writable.");
        this->_pImpl->_writePos = 0;
        this->_pImpl->_writeBuffer.Resize(tmplen);
        break;
    default:
        throw InvalidOperationException("Stream mode was not recognized.");
        break;
    }
    this->_pImpl->_mode = mode;
    this->_pImpl->_base = baseStream;
    this->_pImpl->_encoding = encoding;
}

ByteStream &TextStream::baseStream() const
{
    if(this->_pImpl == nullptr)
        throw ObjectClosedException("Object has already closed.", "TextStream");
    return *this->_pImpl->_base;
}

Encoding &TextStream::codec() const
{
    if(this->_pImpl == nullptr)
        throw ObjectClosedException("Object has already closed.", "TextStream");
    return *this->_pImpl->_encoding;
}

bool TextStream::canRead() const { return this->_pImpl->_mode == StreamMode::Read; }

bool TextStream::canWrite() const { return this->_pImpl->_mode == StreamMode::Write; }

bool TextStream::isClosed() const { return this->_pImpl == nullptr; }

long TextStream::length() const
{
    throw NotSupportedException("Seeking operations are not supported for TextStream.");
}

void TextStream::length(long length)
{
    throw NotSupportedException("Seeking operations are not supported for TextStream.");
    UseParameter(length);
}

long TextStream::position() const
{
    throw NotSupportedException("Seeking operations are not supported for TextStream.");
}

CharStream &TextStream::position(long position)
{
    throw NotSupportedException("Seeking operations are not supported for TextStream.");
    UseParameter(position);
}

void TextStream::Close()
{
    if(this->_pImpl == nullptr)
        return;
    delete this->_pImpl;
    this->_pImpl = nullptr;
}

long TextStream::Flush()
{
    if(this->_pImpl == nullptr)
        throw ObjectClosedException("Object has already closed.", "TextStream");
    if(!this->canWrite())
        throw NotSupportedException("Base stream was not writable.");
    long wrote = this->_pImpl->_base->Write(this->_pImpl->_writeBuffer, 0, this->_pImpl->_writePos);
    this->_pImpl->_writePos = 0;
    return wrote;
}

long TextStream::Read(CharArray &buffer, long offset, long count)
{
    if(!this->canRead())
        throw NotSupportedException("Base stream was not readable.");
    if(this->_pImpl == nullptr)
        throw ObjectClosedException("Object has already closed.", "TextStream");
    if(this->_pImpl->_base->isClosed())
        return -1;
    if(offset < 0)
        throw ArgumentOutOfRangeException("Offset cannot be less than zero.", "offset");
    if(offset > buffer.length())
        throw ArgumentOutOfRangeException("Offset must be less than buffer length.", "offset");
    if(count < 0)
        throw ArgumentOutOfRangeException("Count cannot be less than zero.");
    if(offset + count > buffer.length())
        buffer.Resize(offset + count);

    long charRead = 0;
    Char16 *data = buffer.data();
    Char16 *bufferData = this->_pImpl->_charBuffer.data();

    int readableBuffered = this->_pImpl->_bufferedCharCount - this->_pImpl->_charPos;
    if(readableBuffered > 0){
        charRead = count < readableBuffered ? count : readableBuffered;
        for(int i = 0; i < charRead; i++)
            data[offset++] = bufferData[i + this->_pImpl->_charPos];
        this->_pImpl->_charPos += charRead;
        if(count == charRead)
            return charRead;
        count -= charRead;
    }

    int fill = tmplen - this->_pImpl->_tempPos;
    int read = this->_pImpl->_base->Read(this->_pImpl->_tempBuffer, this->_pImpl->_tempPos, fill);
    if(read < 1){
        if(this->_pImpl->_tempPos > 0){
            data[offset] = Char16((ushort)0xfffd);
            this->_pImpl->_tempPos = 0;
            return charRead + 1;
        }
        return charRead;
    }
    Decoder &decoder = this->_pImpl->_encoding->GetDecoder();
    long bytesUsed, charsUsed;
    this->_pImpl->_tempPos += read;
    if(!decoder.Decode(this->_pImpl->_tempBuffer, 0, this->_pImpl->_tempPos, this->_pImpl->_charBuffer, 0, tmplen, &bytesUsed, &charsUsed)){
        byte* tmpData = this->_pImpl->_tempBuffer.data();
        int remain = this->_pImpl->_tempPos - bytesUsed;
        for(int i = 0; i < remain; i++)
            tmpData[i] = tmpData[bytesUsed + i];
        this->_pImpl->_tempPos = remain;
    } else this->_pImpl->_tempPos = 0;
    this->_pImpl->_bufferedCharCount = charsUsed;
    this->_pImpl->_charPos = 0;
    return charRead + this->Read(buffer, offset, count);
}

long TextStream::ReadLine(CharArray &buffer, long offset)
{
    if(!this->canRead())
        throw NotSupportedException("Base stream was not readable");
    if(this->_pImpl == nullptr)
        throw ObjectClosedException("Object has already closed.", "TextStream");
    if(this->_pImpl->_base->isClosed())
        return -1;
    if(offset < 0)
        throw ArgumentOutOfRangeException("Offset cannot be less than zero.", "offset");
    if(offset > buffer.length())
        throw ArgumentOutOfRangeException("Offset must be less than buffer length.", "offset");

    byte lineSeperator = '\n';
    if(buffer.length() == 0)
        buffer.Resize(64);
    Char16 *data = buffer.data();
    long charStart = offset;
    int read = this->Read(this->_pImpl->_charBuffer, tmplen, 1);
    while(read > 0 && this->_pImpl->_charBuffer[tmplen].unicode() != lineSeperator){
        if(charStart == buffer.length()){
            buffer.Resize(buffer.length() << 1);
            data = buffer.data();
        }
        data[charStart++] = this->_pImpl->_charBuffer[tmplen];
        read = this->Read(this->_pImpl->_charBuffer, tmplen, 1);
    }
    return charStart - offset;
}

long TextStream::Seek(long offset, SeekOrigin origin)
{
    throw NotSupportedException("Seeking operations are not supported for TextStream.");
    UseParameter(offset);
    UseParameter(origin);
}

long TextStream::Write(const CharArray &buffer, long offset, long count)
{
    if(!this->canWrite())
        throw NotSupportedException("Base stream was not writable");
    if(this->_pImpl == nullptr)
        throw ObjectClosedException("Object has already closed.", "TextStream");
    if(this->_pImpl->_base->isClosed())
        return -1;
    if(offset < 0)
        throw ArgumentOutOfRangeException("Offset cannot be less than zero.", "offset");
    if(offset > buffer.length())
        throw ArgumentOutOfRangeException("Offset must be less than buffer length.", "offset");
    if(count < 0)
        throw ArgumentOutOfRangeException("Count cannot be less than zero.");
    if(offset + count > buffer.length())
        throw OutOfRangeException("Block boundries was out of range of source block.");

    Encoder &encoder = this->_pImpl->_encoding->GetEncoder();
    long bytesUsed, charsUsed;
    long byteLen = encoder.GetLength(buffer, offset, count);
    long bLast = byteLen + this->_pImpl->_writePos;
    if(this->_pImpl->_writeBuffer.length() <= bLast){
        long newSize = this->_pImpl->_writeBuffer.length();
        while(newSize <= bLast)
            newSize <<= 1;
        this->_pImpl->_writeBuffer.Resize(newSize);
    }
    encoder.Encode(buffer, offset, count, this->_pImpl->_writeBuffer, this->_pImpl->_writePos, byteLen, &charsUsed, &bytesUsed);
    this->_pImpl->_writePos += bytesUsed;
    return charsUsed;
}

long TextStream::WriteLine(const CharArray &buffer, long offset, long count)
{
    if(!this->canWrite())
        throw NotSupportedException("Base stream was not writable");
    if(this->_pImpl == nullptr)
        throw ObjectClosedException("Object has already closed.", "TextStream");
    if(this->_pImpl->_base->isClosed())
        return -1;
    if(offset < 0)
        throw ArgumentOutOfRangeException("Offset cannot be less than zero.", "offset");
    if(offset > buffer.length())
        throw ArgumentOutOfRangeException("Offset must be less than buffer length.", "offset");
    if(count < 0)
        throw ArgumentOutOfRangeException("Count cannot be less than zero.");
    if(offset + count > buffer.length())
        throw OutOfRangeException("Block boundries was out of range of source block.");

    Encoder &encoder = this->_pImpl->_encoding->GetEncoder();
    long bytesUsed, charsUsed;
    long byteLen = encoder.GetLength(buffer, offset, count) + 1;
    long bLast = byteLen + this->_pImpl->_writePos;
    if(this->_pImpl->_writeBuffer.length() <= bLast){
        long newSize = this->_pImpl->_writeBuffer.length();
        while(newSize <= bLast)
            newSize <<= 1;
        this->_pImpl->_writeBuffer.Resize(newSize);
    }
    if(encoder.Encode(buffer, offset, count, this->_pImpl->_writeBuffer, this->_pImpl->_writePos, byteLen, &charsUsed, &bytesUsed)){
        this->_pImpl->_writePos += bytesUsed;
        CharArray lineEnding = CharArray(1);
        lineEnding[0] = Char16('\n');
        this->Write(lineEnding, 0, 1);
    } else {
        this->_pImpl->_writePos += bytesUsed;
        CharArray lineEnding = CharArray(2);
        lineEnding[0] = Char16('?');
        lineEnding[1] = Char16('\n');
        this->Write(lineEnding, 0, 2);
    }
    return charsUsed;
}
