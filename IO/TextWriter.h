#ifndef TEXTWRITER_H
#define TEXTWRITER_H

#include "../Defs.h"
#include "CharStream.h"
#include "ByteStream.h"
#include "../Convert.h"
#include "../Text/Encoding.h"

class TextWriter final
{
    PIMPL
public:
    TextWriter(CharStream *baseStream);

    CharStream &baseStream() const;

    long Flush();

    TextWriter &Write(const CharArray &buffer, long offset, long count);
    TextWriter &WriteLine(const CharArray &buffer, long offset, long count);

    TextWriter &Write(bool value);
    TextWriter &Write(char value);
    TextWriter &Write(byte value);
    TextWriter &Write(Char16 value);
    TextWriter &Write(short value);
    TextWriter &Write(ushort value);
    TextWriter &Write(int value);
    TextWriter &Write(uint value);
    TextWriter &Write(long value);
    TextWriter &Write(ulong value);
    TextWriter &Write(float value);
    TextWriter &Write(double value);
    TextWriter &Write(const String16 &value);
    TextWriter &Write(const char *value);
    TextWriter &Write(const CharArray &array);
    TextWriter &Write(const IStringable &value);

    TextWriter &WriteLine();
    TextWriter &WriteLine(bool value);
    TextWriter &WriteLine(char value);
    TextWriter &WriteLine(byte value);
    TextWriter &WriteLine(Char16 value);
    TextWriter &WriteLine(short value);
    TextWriter &WriteLine(ushort value);
    TextWriter &WriteLine(int value);
    TextWriter &WriteLine(uint value);
    TextWriter &WriteLine(long value);
    TextWriter &WriteLine(ulong value);
    TextWriter &WriteLine(float value);
    TextWriter &WriteLine(double value);
    TextWriter &WriteLine(const String16 &value);
    TextWriter &WriteLine(const char *value);
    TextWriter &WriteLine(const CharArray &array);
    TextWriter &WriteLine(const IStringable &value);

    TextWriter &WriteSpace();

    inline TextWriter &operator < (bool value) { return this->Write(value); }
    inline TextWriter &operator << (bool value) { return this->WriteLine(value); }
    inline TextWriter &operator < (char value) { return this->Write(value); }
    inline TextWriter &operator << (char value) { return this->WriteLine(value); }
    inline TextWriter &operator < (byte value) { return this->Write(value); }
    inline TextWriter &operator << (byte value) { return this->WriteLine(value); }
    inline TextWriter &operator < (Char16 value) { return this->Write(value); }
    inline TextWriter &operator << (Char16 value) { return this->WriteLine(value); }
    inline TextWriter &operator < (short value) { return this->Write(value); }
    inline TextWriter &operator << (short value) { return this->WriteLine(value); }
    inline TextWriter &operator < (ushort value) { return this->Write(value); }
    inline TextWriter &operator << (ushort value) { return this->WriteLine(value); }
    inline TextWriter &operator < (int value) { return this->Write(value); }
    inline TextWriter &operator << (int value) { return this->WriteLine(value); }
    inline TextWriter &operator < (uint value) { return this->Write(value); }
    inline TextWriter &operator << (uint value) { return this->WriteLine(value); }
    inline TextWriter &operator < (long value) { return this->Write(value); }
    inline TextWriter &operator << (long value) { return this->WriteLine(value); }
    inline TextWriter &operator < (ulong value) { return this->Write(value); }
    inline TextWriter &operator << (ulong value) { return this->WriteLine(value); }
    inline TextWriter &operator < (float value) { return this->Write(value); }
    inline TextWriter &operator << (float value) { return this->WriteLine(value); }
    inline TextWriter &operator < (double value) { return this->Write(value); }
    inline TextWriter &operator << (double value) { return this->WriteLine(value); }
    inline TextWriter &operator < (const String16 &value) { return this->Write(value); }
    inline TextWriter &operator << (const String16 &value) { return this->WriteLine(value); }
    inline TextWriter &operator < (const char *value) { return this->Write(value); }
    inline TextWriter &operator << (const char *value) { return this->WriteLine(value); }
    inline TextWriter &operator < (const CharArray &value) { return this->Write(value); }
    inline TextWriter &operator << (const CharArray &value) { return this->WriteLine(value); }
    inline TextWriter &operator < (const IStringable &value) { return this->Write(value); }
    inline TextWriter &operator << (const IStringable &value) { return this->WriteLine(value); }

    TextWriter(const TextWriter &writer);
    TextWriter &operator =(const TextWriter &writer);
    ~TextWriter();
};

#endif // TEXTWRITER_H
