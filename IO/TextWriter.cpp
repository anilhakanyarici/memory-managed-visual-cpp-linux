#include "TextWriter.h"
#include "TextStream.h"
#include "../Exception.h"

struct TextWriter::_impl
{
    CharStream *_baseStream;
    uint _refc = 1;
};

TextWriter::TextWriter(CharStream *baseStream)
{
    if(!baseStream->canWrite())
        throw NotSupportedException("Base stream must be writable.");
    this->_pImpl = new TextWriter::_impl();
    this->_pImpl->_baseStream = baseStream;
}

CharStream &TextWriter::baseStream() const
{
    return *this->_pImpl->_baseStream;
}

long TextWriter::Flush()
{
    return this->_pImpl->_baseStream->Flush();
}

TextWriter &TextWriter::Write(const CharArray &buffer, long offset, long count)
{
    this->_pImpl->_baseStream->Write(buffer, offset, count);
    return *this;
}
TextWriter &TextWriter::WriteLine(const CharArray &buffer, long offset, long count)
{
    this->_pImpl->_baseStream->WriteLine(buffer, offset, count);
    return *this;
}

TextWriter &TextWriter::Write(bool value)
{
    CharArray array;
    if(value)
        array = CharArray("true");
    else
        array = CharArray("false");
    return this->Write(array, 0, array.length());
}
TextWriter &TextWriter::Write(char value)
{
    return this->Write(Char16(value));
}
TextWriter &TextWriter::Write(byte value)
{
    return this->Write((short)value);
}
TextWriter &TextWriter::Write(Char16 value)
{
    CharArray array = CharArray(1);
    array.data()[0] = value;
    return this->Write(array, 0, 1);
}
TextWriter &TextWriter::Write(short value)
{
    char buffer[50];
    int len = sprintf(buffer, "%hd", value);
    buffer[len] = 0;
    CharArray chars = CharArray(len);
    Char16 *data = chars.data();
    for(int i = 0; i < len; i++)
        data[i] = Char16((ushort)buffer[i]);
    return this->Write(chars, 0, len);
}
TextWriter &TextWriter::Write(ushort value)
{
    char buffer[50];
    int len = sprintf(buffer, "%hu", value);
    buffer[len] = 0;
    CharArray chars = CharArray(len);
    Char16 *data = chars.data();
    for(int i = 0; i < len; i++)
        data[i] = Char16((ushort)buffer[i]);
    return this->Write(chars, 0, len);
}
TextWriter &TextWriter::Write(int value)
{
    char buffer[50];
    int len = sprintf(buffer, "%d", value);
    buffer[len] = 0;
    CharArray chars = CharArray(len);
    Char16 *data = chars.data();
    for(int i = 0; i < len; i++)
        data[i] = Char16((ushort)buffer[i]);
    return this->Write(chars, 0, len);
}
TextWriter &TextWriter::Write(uint value)
{
    char buffer[50];
    int len = sprintf(buffer, "%u", value);
    buffer[len] = 0;
    CharArray chars = CharArray(len);
    Char16 *data = chars.data();
    for(int i = 0; i < len; i++)
        data[i] = Char16((ushort)buffer[i]);
    return this->Write(chars, 0, len);
}
TextWriter &TextWriter::Write(long value)
{
    char buffer[50];
    int len = sprintf(buffer, "%ld", value);
    buffer[len] = 0;
    CharArray chars = CharArray(len);
    Char16 *data = chars.data();
    for(int i = 0; i < len; i++)
        data[i] = Char16((ushort)buffer[i]);
    return this->Write(chars, 0, len);
}
TextWriter &TextWriter::Write(ulong value)
{
    char buffer[50];
    int len = sprintf(buffer, "%lu", value);
    buffer[len] = 0;
    CharArray chars = CharArray(len);
    Char16 *data = chars.data();
    for(int i = 0; i < len; i++)
        data[i] = Char16((ushort)buffer[i]);
    return this->Write(chars, 0, len);
}
TextWriter &TextWriter::Write(float value)
{
    char buffer[50];
    int len = 0;
    if(value < 0.0000001)
        len = sprintf(buffer, "%.7e", value);
    else
        len = sprintf(buffer, "%.7f", value);
    buffer[len] = 0;
    CharArray chars = CharArray(len);
    Char16 *data = chars.data();
    for(int i = 0; i < len; i++)
        data[i] = Char16((ushort)buffer[i]);
    String16 s = String16(chars, false);
    if(value >= 0.0000001)
        s = s.TrimEnd("0.");
    return this->Write(s.charsReference(), 0, s.length());
}
TextWriter &TextWriter::Write(double value)
{
    char buffer[50];
    int len = 0;
    if(value < 0.0000000000000001)
        len = sprintf(buffer, "%.16e", value);
    else
        len = sprintf(buffer, "%.16f", value);
    buffer[len] = 0;
    CharArray chars = CharArray(len);
    Char16 *data = chars.data();
    for(int i = 0; i < len; i++)
        data[i] = Char16((ushort)buffer[i]);
    String16 s = String16(chars, false);
    if(value >= 0.0000000000000001)
        s = s.TrimEnd("0.");
    return this->Write(s.charsReference(), 0, s.length());
}
TextWriter &TextWriter::Write(const String16 &value)
{
    return this->Write(value.charsReference());
}
TextWriter &TextWriter::Write(const char *value)
{
    return this->Write(CharArray(value));
}
TextWriter &TextWriter::Write(const CharArray &array)
{
    return this->Write(array, 0, array.length());
}
TextWriter &TextWriter::Write(const IStringable &value)
{
    return this->Write(value.ToString());
}

TextWriter &TextWriter::WriteLine()
{
    CharArray array = CharArray(1);
    array.data()[0] = '\n';
    return this->Write(array, 0, 1);
}

TextWriter &TextWriter::WriteLine(bool value)
{
    CharArray array;
    if(value)
        array = CharArray("true");
    else
        array = CharArray("false");
    return this->WriteLine(array, 0, array.length());
}
TextWriter &TextWriter::WriteLine(char value)
{
    return this->WriteLine(Char16(value));
}
TextWriter &TextWriter::WriteLine(byte value)
{
    return this->WriteLine((short)value);
}
TextWriter &TextWriter::WriteLine(Char16 value)
{
    CharArray array = CharArray(1);
    array.data()[0] = value;
    return this->WriteLine(array, 0, 1);
}
TextWriter &TextWriter::WriteLine(short value)
{
    char buffer[50];
    int len = sprintf(buffer, "%hd", value);
    buffer[len] = 0;
    CharArray chars = CharArray(len);
    Char16 *data = chars.data();
    for(int i = 0; i < len; i++)
        data[i] = Char16((ushort)buffer[i]);
    return this->WriteLine(chars, 0, len);
}
TextWriter &TextWriter::WriteLine(ushort value)
{
    char buffer[50];
    int len = sprintf(buffer, "%hu", value);
    buffer[len] = 0;
    CharArray chars = CharArray(len);
    Char16 *data = chars.data();
    for(int i = 0; i < len; i++)
        data[i] = Char16((ushort)buffer[i]);
    return this->WriteLine(chars, 0, len);
}
TextWriter &TextWriter::WriteLine(int value)
{
    char buffer[50];
    int len = sprintf(buffer, "%d", value);
    buffer[len] = 0;
    CharArray chars = CharArray(len);
    Char16 *data = chars.data();
    for(int i = 0; i < len; i++)
        data[i] = Char16((ushort)buffer[i]);
    return this->WriteLine(chars, 0, len);
}
TextWriter &TextWriter::WriteLine(uint value)
{
    char buffer[50];
    int len = sprintf(buffer, "%u", value);
    buffer[len] = 0;
    CharArray chars = CharArray(len);
    Char16 *data = chars.data();
    for(int i = 0; i < len; i++)
        data[i] = Char16((ushort)buffer[i]);
    return this->WriteLine(chars, 0, len);
}
TextWriter &TextWriter::WriteLine(long value)
{
    char buffer[50];
    int len = sprintf(buffer, "%ld", value);
    buffer[len] = 0;
    CharArray chars = CharArray(len);
    Char16 *data = chars.data();
    for(int i = 0; i < len; i++)
        data[i] = Char16((ushort)buffer[i]);
    return this->WriteLine(chars, 0, len);
}
TextWriter &TextWriter::WriteLine(ulong value)
{
    char buffer[50];
    int len = sprintf(buffer, "%lu", value);
    buffer[len] = 0;
    CharArray chars = CharArray(len);
    Char16 *data = chars.data();
    for(int i = 0; i < len; i++)
        data[i] = Char16((ushort)buffer[i]);
    return this->WriteLine(chars, 0, len);
}
TextWriter &TextWriter::WriteLine(float value)
{
    char buffer[50];
    int len = 0;
    if(value < 0.0000001)
        len = sprintf(buffer, "%.7e", value);
    else
        len = sprintf(buffer, "%.7f", value);
    buffer[len] = 0;
    CharArray chars = CharArray(len);
    Char16 *data = chars.data();
    for(int i = 0; i < len; i++)
        data[i] = Char16((ushort)buffer[i]);
    String16 s = String16(chars, false);
    if(value >= 0.0000001)
        s = s.TrimEnd("0.");
    return this->WriteLine(s.charsReference(), 0, s.length());
}
TextWriter &TextWriter::WriteLine(double value)
{
    char buffer[50];
    int len = 0;
    if(value < 0.0000000000000001)
        len = sprintf(buffer, "%.16e", value);
    else
        len = sprintf(buffer, "%.16f", value);
    buffer[len] = 0;
    CharArray chars = CharArray(len);
    Char16 *data = chars.data();
    for(int i = 0; i < len; i++)
        data[i] = Char16((ushort)buffer[i]);
    String16 s = String16(chars, false);
    if(value >= 0.0000000000000001)
        s = s.TrimEnd("0.");
    return this->WriteLine(s.charsReference(), 0, s.length());
}
TextWriter &TextWriter::WriteLine(const String16 &value)
{
    return this->WriteLine(value.charsReference());
}
TextWriter &TextWriter::WriteLine(const char *value)
{
    return this->WriteLine(CharArray(value));
}
TextWriter &TextWriter::WriteLine(const CharArray &array)
{
    return this->WriteLine(array, 0, array.length());
}
TextWriter &TextWriter::WriteLine(const IStringable &value)
{
    return this->WriteLine(value.ToString());
}

TextWriter &TextWriter::WriteSpace()
{
    CharArray array = CharArray(1);
    array.data()[0] = Char16(32);
    return this->Write(array, 0, 1);
}

TextWriter::TextWriter(const TextWriter &writer)
{
    this->_pImpl = writer._pImpl;
    if(this->_pImpl != nullptr)
        this->_pImpl->_refc++;
}
TextWriter &TextWriter::operator =(const TextWriter &writer)
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

TextWriter::~TextWriter()
{
    if(this->_pImpl != nullptr){
        if(this->_pImpl->_refc == 1){
            delete this->_pImpl;
        } else this->_pImpl->_refc--;
    }
}
