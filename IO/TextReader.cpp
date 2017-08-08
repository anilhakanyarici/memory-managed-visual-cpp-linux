#define tmplen 1024
#include "TextReader.h"
#include "TextStream.h"
#include "../Exception.h"

struct TextReader::_impl
{
    CharStream *_baseStream;
    int _blockPos;
    int _tmplen;
    CharArray _preReadBlock;
    long readPreBlock();
    bool _eof = false;
    uint _refc = 1;
};

TextReader::TextReader(CharStream *baseStream)
{
    if(!baseStream->canRead())
        throw NotSupportedException("Base stream must be readable.");
    this->_pImpl = new TextReader::_impl();
    this->_pImpl->_baseStream = baseStream;
    this->_pImpl->_blockPos = tmplen;
    this->_pImpl->_tmplen = tmplen;
    this->_pImpl->_preReadBlock = CharArray(tmplen);
}

bool TextReader::endOfStream() const
{
    return this->_pImpl->_eof;
}

CharStream &TextReader::baseStream() const
{
    return *this->_pImpl->_baseStream;
}

Char16 TextReader::Peek()
{
    if(this->_pImpl->_tmplen <= this->_pImpl->_blockPos){
        if(0 == this->_pImpl->readPreBlock())
            return Char16(0);
        this->_pImpl->_blockPos = 0;
    }
    if(this->_pImpl->_eof)
        return Char16(0);
    return this->_pImpl->_preReadBlock[this->_pImpl->_blockPos];
}

long TextReader::ReadBlock(CharArray &buffer, long offset, long count)
{
    if(offset < 0)
        throw ArgumentOutOfRangeException("Offset cannot be less than zero.", "offset");
    if(offset > buffer.length())
        throw ArgumentOutOfRangeException("Offset must be less than buffer length.", "offset");
    if(count < 0)
        throw ArgumentOutOfRangeException("Count cannot be less than zero.");

    if(this->_pImpl->_tmplen <= this->_pImpl->_blockPos){
        long read = this->_pImpl->_baseStream->Read(buffer, offset, count);
        this->_pImpl->_eof = read == 0;
        return read;
    }
    else{
        int readable = this->_pImpl->_tmplen - this->_pImpl->_blockPos;
        long read = readable < count ? readable : count;
        if(buffer.length() < offset + read)
            buffer.Resize(offset + read);
        Char16 *buffData = buffer.data();
        Char16 *tmpData = this->_pImpl->_preReadBlock.data();
        for(long i = 0; i < read; i++)
            buffData[offset++] = tmpData[this->_pImpl->_blockPos++];
        count -= read;
        if(count > 0){
            long read2 = this->_pImpl->_baseStream->Read(buffer, offset, count);
            read += read2;
            this->_pImpl->_eof = read2 == 0;
        }
        return read;
    }
}

String16 TextReader::ReadBlock(long count)
{
    CharArray buffer = CharArray(count);
    long read = this->ReadBlock(buffer, 0, count);
    return String16(buffer, 0, read);
}

long TextReader::ReadChar(CharArray &buffer, long offset)
{
    if(offset < 0)
        throw ArgumentOutOfRangeException("Offset cannot be less than zero.", "offset");
    if(offset > buffer.length())
        throw ArgumentOutOfRangeException("Offset must be less than buffer length.", "offset");

    if(this->_pImpl->_tmplen <= this->_pImpl->_blockPos){
        if(0 == this->_pImpl->readPreBlock())
            return 0;
        this->_pImpl->_blockPos = 0;
    }
    buffer[offset] = this->_pImpl->_preReadBlock[this->_pImpl->_blockPos++];
    return 1;
}

Char16 TextReader::ReadChar()
{
    if(this->_pImpl->_tmplen <= this->_pImpl->_blockPos){
        if(0 == this->_pImpl->readPreBlock())
            return Char16(0);
        this->_pImpl->_blockPos = 0;
    }
    return this->_pImpl->_preReadBlock[this->_pImpl->_blockPos++];
}

long TextReader::ReadLine(CharArray &buffer, long offset)
{
    return this->ReadTo(buffer, offset, Char16('\n'));
}

String16 TextReader::ReadLine()
{
    CharArray array = CharArray(64);
    long read = this->ReadLine(array, 0);
    return String16(array, 0, read);
}

long TextReader::ReadToSpace(CharArray &buffer, long offset)
{
    return this->ReadTo(buffer, offset, Char16((ushort)32));
}

String16 TextReader::ReadToSpace()
{
    CharArray array = CharArray(64);
    long read = this->ReadToSpace(array, 0);
    return String16(array, 0, read);
}

long TextReader::ReadTo(CharArray &buffer, long offset, Char16 ch)
{
    if(offset < 0)
        throw ArgumentOutOfRangeException("Offset cannot be less than zero.", "offset");
    if(offset > buffer.length())
        throw ArgumentOutOfRangeException("Offset must be less than buffer length.", "offset");

    if(buffer.length() == 0)
        buffer.Resize(64);
    Char16 *tmpData = this->_pImpl->_preReadBlock.data();
    Char16 *buffData = buffer.data();
    bool lineOrEOF = false;
    long read = 0;
    while(true){
        int pos = this->_pImpl->_blockPos;
        for( ;pos < this->_pImpl->_tmplen; ){
            Char16 cur = tmpData[pos];
            if((lineOrEOF = cur == ch))
                break;
            pos++;
        }
        int blkCount = pos - this->_pImpl->_blockPos;
        if(blkCount > buffer.length() - offset){
            buffer.Resize(blkCount + offset);
            buffData = buffer.data();
        }
        read += blkCount;
        for( ;this->_pImpl->_blockPos < pos; )
            buffData[offset++] = tmpData[this->_pImpl->_blockPos++];
        if(lineOrEOF){
            this->_pImpl->_blockPos++;
            break;
        }

        Char16 singChar = this->ReadChar();
        ushort unicode = singChar.unicode();
        lineOrEOF = unicode == 0 || unicode == ch.unicode();
        if(lineOrEOF) break;
        if(offset == buffer.length()){
            buffer.Resize(buffer.length() << 1);
            buffData = buffer.data();
        }
        buffData[offset++] = singChar;
        read++;
    }
    return read;
}

String16 TextReader::ReadTo(Char16 ch)
{
    CharArray array = CharArray(64);
    long read = this->ReadTo(array, 0, ch);
    return String16(array, 0, read);
}

long TextReader::ReadTo(CharArray &buffer, long offset, const String16 &endText)
{
    if(offset < 0)
        throw ArgumentOutOfRangeException("Offset cannot be less than zero.", "offset");
    if(offset > buffer.length())
        throw ArgumentOutOfRangeException("Offset must be less than buffer length.", "offset");
    if(endText.isEmpty())
        return 0;
    if(buffer.length() == 0)
        buffer.Resize(64);
    long count = 0;
    CharArray temp = CharArray(endText.length());
    temp[0] = endText.charsReference()[0];
    Char16 *endTextData = endText.data();
    Char16 *tmpData = temp.data();
    long endTextLen = endText.length();
    Char16 first = endText.charsReference()[0];
    while(true){
        long read = this->ReadTo(buffer, offset, first);
        Char16 *buffData = buffer.data();
        offset += read;
        count += read;
        if(this->_pImpl->_eof)
            return count;
        bool equals = true;
        for(long i = 1; i < endTextLen; i++){
            if(this->Peek() != endTextData[i] || this->_pImpl->_eof){
                equals = false;
                if(offset + i > buffer.length()){
                    buffer.Resize(offset + i);
                    buffData = buffer.data();
                }
                for(long j = 0; j < i; j++)
                    buffData[offset++] = tmpData[j];
                count += i;
                break;
            }
            read = this->ReadChar(temp, i);
            count += read;
            if(read == 0){
                this->_pImpl->_eof = true;
                return count;
            }
        }
        if(equals)
            return count;
    }
}

String16 TextReader::ReadTo(const String16 &endText)
{
    CharArray array = CharArray(64);
    long read = this->ReadTo(array, 0, endText);
    return String16(array, 0, read);
}

long TextReader::ReadToEnd(CharArray &buffer, long offset)
{
    long read = 0;
    long count = 0;
    while(0 < (read = this->ReadBlock(buffer, offset, 1024)))
        count += read;
    this->_pImpl->_eof = true;
    return count;
}

String16 TextReader::ReadToEnd()
{
    CharArray array = CharArray(64);
    long read = this->ReadToEnd(array, 0);
    return String16(array, 0, read);
}

bool TextReader::operator >(String16 &str)
{
    CharArray array;
    long len = this->ReadToSpace(array, 0);
    array.Resize(len);
    str = array;
    return !this->_pImpl->_eof || len > 0;
}

bool TextReader::operator >>(String16 &str)
{
    CharArray array;
    long len = this->ReadLine(array, 0);
    array.Resize(len);
    str = array;
    return !this->_pImpl->_eof || len > 0;
}

bool TextReader::operator >>=(String16 &str)
{
    CharArray array;
    long len = this->ReadToEnd(array, 0);
    array.Resize(len);
    str = array;
    return !this->_pImpl->_eof || len > 0;
}


TruncateReader TextReader::operator %(const char *endText)
{
    return TruncateReader(this, endText);
}

TruncateReader TextReader::operator %(const String16 &endText)
{
    return TruncateReader(this, endText);
}

TextReader::TextReader(const TextReader &reader)
{
    this->_pImpl = reader._pImpl;
    if(this->_pImpl != nullptr)
        this->_pImpl->_refc++;
}
TextReader &TextReader::operator =(const TextReader &reader)
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
TextReader::~TextReader()
{
    if(this->_pImpl != nullptr){
        if(this->_pImpl->_refc == 1){
            delete this->_pImpl;
        } else this->_pImpl->_refc--;
    }
}

long TextReader::_impl::readPreBlock()
{
    long read = this->_baseStream->Read(this->_preReadBlock, 0, tmplen);
    this->_tmplen = read;
    this->_eof = read == 0;
    return read;
}

TruncateReader::TruncateReader(TextReader *reader, const String16 &endText)
{
    this->_reader = reader;
    this->_endText = endText;
}

TruncateReader::TruncateReader(const TruncateReader &tr)
{
    this->_reader = tr._reader;
    this->_endText = tr._endText;
}

TruncateReader &TruncateReader::operator =(const TruncateReader &tr)
{
    this->_reader = tr._reader;
    this->_endText = tr._endText;
    return *this;
}

bool TruncateReader::operator >(String16 &str)
{
    CharArray array;
    long len = this->_reader->ReadTo(array, 0, this->_endText);;
    array.Resize(len);
    str = array;
    return !this->_reader->endOfStream()  || len > 0;
}
