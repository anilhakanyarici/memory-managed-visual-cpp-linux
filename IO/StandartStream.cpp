#include "StandartStream.h"
#include "../Exception.h"
#include "IOException.h"
#include "stdio.h"
#include "string.h"
#include "../Terminal.h"

uint scan_utf32Char(){
    byte c[4];
    fread(c, 1, 1, stdin);
    byte head = c[0];
    int continuationBytesLen = ((head & 0xf0) == 0xf0) + ((head & 0xe0) == 0xe0) + ((head & 0xc0) == 0xc0);
    fread(&c[1], 1, continuationBytesLen, stdin);
    if(continuationBytesLen == 0) return c[0];
    else if(continuationBytesLen == 1)return (c[0] - 192) * 64 + c[1] - 128;
    else if(continuationBytesLen == 2) return (c[0] - 224) * 4096 + (c[1] - 128) * 64 + c[2] - 128;
    else return (c[0] - 240) * 262144 + (c[1] - 128) * 4096 + (c[2] - 128) * 64 + c[3] - 128;
}
void print_utf32Char(_IO_FILE *&fo, const uint &unicode, const bool &spaceAfterNonBMP){
    byte c[5];
    if(unicode < 0x80){
        c[0] = unicode;
        fwrite(c, 1, 1, fo);
    } else if(unicode < 0x0800){
        c[0] = unicode / 64 + 192;
        c[1] = unicode % 64 + 128;
        fwrite(c, 1, 2, fo);
    } else if((0x0800 <= unicode && unicode < 0xd800) || (0xdfff < unicode && unicode <= 0xffff)){
        c[0] = unicode / 4096 + 224;
        c[1] = (unicode % 4096) / 64 + 128;
        c[2] = unicode % 64 + 128;
        fwrite(c, 1, 3, fo);
    } else if(unicode < 0x110000){
        c[0] = unicode / 262144 + 240;
        c[1] = (unicode % 262144) / 4096 + 128;
        c[2] = (unicode % 4096) / 64 + 128;
        c[3] = unicode % 64 + 128;
        c[4] = 32;
        fwrite(c, 1, 4 + spaceAfterNonBMP, fo);
    } else {
        c[0] = 239;
        c[1] = 191;
        c[2] = 189;
        fwrite(c, 1, 3, fo);
    }
}

StandartStream::StandartStream(int iotype)
{
    this->iotype = iotype;
}

long StandartStream::length() const
{
    return 0;
}
void StandartStream::length(long length)
{
    throw NotSupportedException("Seeking operations does not supported for StandartStream.");
    UseParameter(length);
}
long StandartStream::position() const
{
    throw NotSupportedException("Seeking operations does not supported for StandartStream.");
}
CharStream &StandartStream::position(long position)
{
    throw NotSupportedException("Seeking operations does not supported for StandartStream.");
    UseParameter(position);
}

long StandartStream::Read(CharArray &buffer, long offset, long count)
{
    if(!this->canRead())
        throw NotSupportedException("Standart Error stream is not readable.");
    if(offset < 0)
        throw ArgumentOutOfRangeException("Offset cannot be less than zero.", "offset");
    if(offset > buffer.length())
        throw ArgumentOutOfRangeException("Offset cannot be greater than buffer length.", "offset");
    if(count < 0)
        throw InvalidOperationException("Count cannot be less than zero.");
    if(count == 0)
        return 0;

    if(offset + count > buffer.length())
        buffer.Resize(offset + count);
    Char16 *data = buffer.data();
    long i = offset;
    long iLast = i + count;
    if(this->surrogate.unicode() != 0){
        data[i++] = this->surrogate;
        this->surrogate = Char16((ushort)0);
    }
    for( ; i < iLast; i++){
        uint unicode = scan_utf32Char();
        if(unicode <= 0xffff) data[i] = Char16((ushort)unicode);
        else {
            ushort ch = (unicode - 0x10000) / 0x400 + 0xd800;
            ushort cl = (unicode - 0x10000) % 0x400 + 0xdc00;
            data[i++] = Char16(ch);
            if(i == iLast) this->surrogate = Char16(cl);
            else data[i] = Char16(cl);
        }
    }
    return i - offset;
}
long StandartStream::ReadLine(CharArray &buffer, long offset)
{
    if(!this->canRead())
        throw NotSupportedException("Standart Error stream is not readable.");
    if(offset < 0)
        throw ArgumentOutOfRangeException("Offset cannot be less than zero.", "offset");
    if(offset > buffer.length())
        throw ArgumentOutOfRangeException("Offset cannot be greater than buffer length.", "offset");

    if(offset + 2 > buffer.length())
        buffer.Resize(buffer.length() << 1);
    if(buffer.length() == 0)
        buffer.Resize(64);
    long i = offset;

    Char16 *data = buffer.data();
    if(this->surrogate.unicode() != 0){
        data[i++] = this->surrogate;
        this->surrogate = Char16((ushort)0);
    }
    for( ; ;i++){
        uint unicode = scan_utf32Char();
        if(unicode == '\n') { break;}
        if(i + 2 > buffer.length()){
            buffer.Resize(buffer.length() << 1);
            data = buffer.data();
        }
        if(unicode <= 0xffff) data[i] = Char16((ushort)unicode);
        else {
            ushort ch = (unicode - 0x10000) / 0x400 + 0xd800;
            ushort cl = (unicode - 0x10000) % 0x400 + 0xdc00;
            data[i++] = Char16(ch);
            data[i] = Char16(cl);
        }
    }
    return i - offset;
}
long StandartStream::Seek(long offset, SeekOrigin origin)
{
    throw NotSupportedException("Seeking operations does not supported for StandartStream.");
    UseParameter(offset);
    UseParameter(origin);
}
long StandartStream::Write(const CharArray &buffer, long offset, long count)
{
    if(offset < 0)
        throw ArgumentOutOfRangeException("Offset cannot be less than zero.", "offset");
    if(offset > buffer.length())
        throw ArgumentOutOfRangeException("Offset must be less than buffer length.", "offset");
    if(count < 0)
        throw ArgumentOutOfRangeException("Count cannot be less than zero.");
    if(offset + count > buffer.length())
        throw OutOfRangeException("Block boundries was out of range of source block.");

    _IO_FILE *fo = stdout;
    if(this->iotype == 0)
        fo = stderr;

    Char16 *data = buffer.data();
    long i = offset;
    long iLast = i + count;
    Char16 current;
    for( ; i < iLast; i++){
        current = data[i];
        if(current.isSurrogate()){
            uint unicode = current.unicode();
            if(i + 2 > iLast){
                print_utf32Char(fo, unicode, true);
                break;
            }
            unicode = (unicode - 0xd800) * 0x400 + data[++i].unicode() - 0xdc00 + 0x10000;
            print_utf32Char(fo, unicode, true);
        } else print_utf32Char(fo, current.unicode(), true);
    }
    return i - offset;
}
long StandartStream::WriteLine(const CharArray &buffer, long offset, long count)
{
    if(offset < 0)
        throw ArgumentOutOfRangeException("Offset cannot be less than zero.", "offset");
    if(offset > buffer.length())
        throw ArgumentOutOfRangeException("Offset must be less than buffer length.", "offset");
    if(count < 0)
        throw ArgumentOutOfRangeException("Count cannot be less than zero.");
    if(offset + count > buffer.length())
        throw OutOfRangeException("Block boundries was out of range of source block.");

    _IO_FILE *fo = stdout;
    if(this->iotype == 0)
        fo = stderr;

    Char16 *data = buffer.data();
    long i = offset;
    long iLast = i + count;
    Char16 current;
    for( ; i < iLast; i++){
        current = data[i];
        if(current.isSurrogate()){
            uint unicode = current.unicode();
            if(i + 2 > iLast){
                print_utf32Char(fo, unicode, true);
                break;
            }
            unicode = (unicode - 0xd800) * 0x400 + data[++i].unicode() - 0xdc00 + 0x10000;
            print_utf32Char(fo, unicode, true);
        } else print_utf32Char(fo, current.unicode(), true);
    }
    print_utf32Char(fo, '\n', true);
    return i - offset;
}
