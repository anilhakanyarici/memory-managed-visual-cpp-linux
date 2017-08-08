#ifndef STRINGBUILDER_H
#define STRINGBUILDER_H

#include "../String16.h"

class StringBuilder final : public IStringable
{
public:
    StringBuilder();
    StringBuilder(const CharArray &buffer, long length);
    StringBuilder(const String16 &str);

    StringBuilder &Append(const String16 &str);
    long Count(long startIndex, const String16 &subStr) const;
    CharArray GetBuffer() const;
    long FindIndex(long start, const String16 &subStr) const;
    long Length() const;
    StringBuilder &Replace(const String16 &oldValue, const String16 &newValue);
    StringBuilder &SubString (long offset, long count);
    StringBuilder &ToLower();
    String16 ToString() const override;
    StringBuilder &ToTitleCase();
    StringBuilder &ToUpper();

private:
    CharArray _buffer;
    long _size;
};

#endif // STRINGBUILDER_H
