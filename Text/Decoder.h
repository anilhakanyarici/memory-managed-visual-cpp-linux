#ifndef DECODER_H
#define DECODER_H

#include "../ByteArray.h"
#include "../CharArray.h"

class UTF8Decoder;
class UTF16Decoder;
class UTF32Decoder;

class Decoder
{
public:
    virtual CharArray GetChars(const ByteArray &bytes) = 0;
    virtual bool Decode(const ByteArray &fromBytes, long bytesOffset, long byteCount, CharArray &toChars, long charsOffset, long charCount, long *bytesUsed, long *charsUsed) = 0;
    virtual long GetLength(const ByteArray &bytes, long offset, long count) const = 0;

    static UTF8Decoder UTF8;
    static UTF16Decoder UTF16;
    static UTF32Decoder UTF32;
};

class UTF8Decoder final : public Decoder
{
public:
    bool Decode(const ByteArray &fromBytes, long bytesOffset, long byteCount, CharArray &toChars, long charsOffset, long charCount, long *bytesUsed, long *charsUsed) override;
    CharArray GetChars(const ByteArray &bytes) override;
    long GetLength(const ByteArray &bytes, long offset, long count) const override;
};
class UTF16Decoder final : public Decoder
{
public:
    bool Decode(const ByteArray &fromBytes, long bytesOffset, long byteCount, CharArray &toChars, long charsOffset, long charCount, long *bytesUsed, long *charsUsed) override;
    CharArray GetChars(const ByteArray &bytes) override;
    long GetLength(const ByteArray &bytes, long offset, long count) const override;
};
class UTF32Decoder final : public Decoder
{
public:
    bool Decode(const ByteArray &fromBytes, long bytesOffset, long byteCount, CharArray &toChars, long charsOffset, long charCount, long *bytesUsed, long *charsUsed) override;
    CharArray GetChars(const ByteArray &bytes) override;
    long GetLength(const ByteArray &bytes, long offset, long count) const override;
};
#endif // DECODER_H
