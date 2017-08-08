#ifndef BYTEARRAY_H
#define BYTEARRAY_H

#include "Defs.h"
#include "Object.h"

class ByteArray final : public Object, public IEquatable<ByteArray>
{
    PIMPL
public:
    ByteArray();
    ByteArray(long length);
    ByteArray(const char *utf8Str);
    ByteArray(byte *dataSource, long length, bool deepCopy = true);
    ByteArray(const ByteArray &array);

    ~ByteArray();

    byte *data(long index = 0) const;
    long length() const;

    ByteArray Clone() const;
    void CopyTo(long offset, ByteArray destination, long destOffset, long count) const;
    bool Equals(const ByteArray &array) const;
    void FillZero();
    long FindIndex(long start, ByteArray subset) const;
    void Resize(long newSize);
    void Reverse();
    ByteArray Slice(long offset, long count, bool deepCopy = true) const;

    ByteArray &operator=(const ByteArray &array);

    byte &operator[](long index);
    byte operator[](long index) const;

    // Object interface
public:
    bool Equals(const Object &obj) const override;
    long GetHashCode() const override;
};

#endif // BYTEARRAY_H
