#ifndef ENCODER_H
#define ENCODER_H

#include "../String16.h"
#include "../ByteArray.h"

class UTF8Encoder;
class UTF16Encoder;
class UTF32Encoder;

class Encoder
{
public:
    virtual ByteArray GetBytes(const CharArray &chars, long offset, long count) = 0;
    virtual bool Encode(const CharArray &fromChars, long charsOffset, long charCount, ByteArray &toBytes, long bytesOffset, long byteCount, long *charsUsed, long *bytesUsed) = 0;
    virtual long GetLength(const CharArray &chars, long offset, long count) const = 0;

    static UTF8Encoder UTF8;
    static UTF16Encoder UTF16;
    static UTF32Encoder UTF32;
};

class UTF8Encoder final : public Encoder
{
public:
    bool Encode(const CharArray &fromChars, long charsOffset, long charCount, ByteArray &toBytes, long bytesOffset, long byteCount, long *charsUsed, long *bytesUsed) override;
    ByteArray GetBytes(const CharArray &chars, long offset, long count) override;
    long GetLength(const CharArray &chars, long offset, long count) const override;
};
class UTF16Encoder final : public Encoder
{
public:
    bool Encode(const CharArray &fromChars, long charsOffset, long charCount, ByteArray &toBytes, long bytesOffset, long byteCount, long *charsUsed, long *bytesUsed) override;
    ByteArray GetBytes(const CharArray &chars, long offset, long count) override;
    long GetLength(const CharArray &chars, long offset, long count) const override;
};
class UTF32Encoder final : public Encoder
{
public:
    bool Encode(const CharArray &fromChars, long charsOffset, long charCount, ByteArray &toBytes, long bytesOffset, long byteCount, long *charsUsed, long *bytesUsed) override;
    ByteArray GetBytes(const CharArray &chars, long offset, long count) override;
    long GetLength(const CharArray &chars, long offset, long count) const override;
};
#endif // ENCODER_H
