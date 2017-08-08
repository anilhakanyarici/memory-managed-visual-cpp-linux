#ifndef CHARARRAY_H
#define CHARARRAY_H

#include "Defs.h"
#include "Char16.h"

class CharArray final : public Object, public IEquatable<CharArray>
{
    PIMPL
public:
    CharArray();
    CharArray(long length);
    CharArray(const char *utf8Str);
    CharArray(Char16 *dataSource, long length, bool deepCopy = true);
    CharArray(const CharArray &array);

    ~CharArray();

    Char16 *data(long index = 0) const;
    long length() const;

    CharArray Clone() const;
    void CopyTo(long offset, CharArray destination, long destOffset, long count) const;
    bool Equals(const CharArray &array) const override;
    void FillZero();
    long FindIndex(long start, CharArray subset) const;
    void Resize(long newSize);
    void Reverse();
    CharArray Slice(long offset, long count, bool deepCopy = true) const;

    CharArray &operator=(const CharArray &array);

    Char16 &operator[](long index);
    Char16 operator[](long index) const;

    CharArray &operator ,(CharArray array);

   // Object interface
public:
    bool Equals(const Object &obj) const override;
    long GetHashCode() const override;
    String16 ToString() const override;
};

#endif // CHARARRAY_H
