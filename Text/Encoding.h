#ifndef ENCODING_H
#define ENCODING_H

#include "../ByteArray.h"
#include "../CharArray.h"
#include "Encoder.h"
#include "Decoder.h"

class UTF8Encoding;
class UTF16Encoding;
class UTF32Encoding;

class Encoding {
public:
    inline ByteArray GetBytes(const CharArray &chars) const { return this->GetEncoder().GetBytes(chars, 0, chars.length()); }
    inline long GetByteLength(const CharArray &chars) const { return this->GetEncoder().GetLength(chars, 0, chars.length()); }
    inline CharArray GetChars(const ByteArray &bytes) const { return this->GetDecoder().GetChars(bytes); }
    inline long GetCharLength(const ByteArray &bytes) const { return this->GetDecoder().GetLength(bytes, 0, bytes.length()); }

    virtual Encoder &GetEncoder() const = 0;
    virtual Decoder &GetDecoder() const = 0;

    static UTF8Encoding UTF8;
    static UTF16Encoding UTF16;
    static UTF32Encoding UTF32;

    static String16 ToBase64String(ByteArray bytes);
    static ByteArray FromBase64String(String16 str);
};

class UTF8Encoding final : public Encoding {
public:
    Encoder &GetEncoder() const override { return Encoder::UTF8; }
    Decoder &GetDecoder() const override { return Decoder::UTF8; }
};
class UTF16Encoding final : public Encoding{
    Encoder &GetEncoder() const override { return Encoder::UTF16; }
    Decoder &GetDecoder() const override { return Decoder::UTF16; }
};
class UTF32Encoding final : public Encoding {
public:
    Encoder &GetEncoder() const override { return Encoder::UTF32; }
    Decoder &GetDecoder() const override { return Decoder::UTF32; }
};

#endif
