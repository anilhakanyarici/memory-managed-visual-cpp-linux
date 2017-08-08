//"B滑ÇŞA滑Ç滑🂤Ş𝐐Ğ"
#ifndef STRING16_H
#define STRING16_H

#include "CharArray.h"
#include "StringList.h"

class ByteArray;

class String16 final : public Object, public IEquatable<String16>
{
public:
    String16();
    String16(Char16 c);
    String16(const char *cString);
    String16(const String16 &str);
    String16(const CharArray &array, bool deepCopy = true);
    String16(const CharArray &array, long offset, long count);

    const CharArray &charsReference() const;
    Char16 *data(long index = 0) const;
    bool isEmpty() const;
    bool isNumeric() const;
    bool isInteger() const;
    long length() const;

    String16 Append(const String16 &str) const;
    bool Contains(Char16 ch) const;
    long Count(long startIndex, const String16 &subStr) const;
    bool EndsWith(const String16 &end) const;
    bool Equals(const String16 &other) const override;
    long FindIndex(long startIndex, const String16 &subset) const;
    long GetHashCode() const override;
    StringList Split(const String16 &seperator) const;
    bool StartWith(const String16 &start) const;
    String16 SubString (long offset, long count) const;
    String16 Replace(const String16 &oldValue, const String16 &newValue) const;
    CharArray ToArray() const;
    ByteArray ToCString() const;
    String16 ToLower() const;
    String16 ToString() const override { return *this; }
    String16 ToTitleCase() const;
    String16 ToUpper() const;
    inline String16 Trim() const { return this->Trim(" \0"); }
    String16 Trim(const String16 &charSet) const;
    String16 TrimEnd(const String16 &charSet) const;
    String16 TrimStart(const String16 &charSet) const;

    static String16 Format(const String16 &format, const StringList &args);

    String16 &operator =(const char *cString);
    String16 &operator =(const CharArray &charsArray);
    String16 &operator =(const String16 &str);

    StringList operator ,(const String16 &item) const;

private:
    CharArray _chars;

    // Object interface
public:
    bool Equals(const Object &obj) const override;
};

#endif // STRING16_H
