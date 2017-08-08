#include "Encoder.h"
#include "../Exception.h"

UTF8Encoder Encoder::UTF8 = UTF8Encoder();
UTF16Encoder Encoder::UTF16 = UTF16Encoder();
UTF32Encoder Encoder::UTF32 = UTF32Encoder();

bool UTF8Encoder::Encode(const CharArray &fromChars, long charsOffset, long charCount, ByteArray &toBytes, long bytesOffset, long byteCount, long *charsUsed, long *bytesUsed)
{
    long charLi = charsOffset + charCount;
    long byteLi = bytesOffset + byteCount;

    if(charsOffset < 0)
        throw ArgumentOutOfRangeException("charsOffset cannot be less than zero.", "charsOffset");
    if(charCount < 0)
        throw ArgumentOutOfRangeException("charCount cannot be less than zero.");
    if(charLi > fromChars.length())
        throw OutOfRangeException("Block boundries was out of range of chars block.");
    if(bytesOffset < 0)
        throw ArgumentOutOfRangeException("Offset cannot be less than zero.", "bytesOffset");
    if(byteCount < 0)
        throw ArgumentOutOfRangeException("ByteCount cannot be less than zero.");
    if(byteLi > toBytes.length())
        throw OutOfRangeException("Block boundries was out of range of bytes block.");

    Char16 *chars = fromChars.data();
    byte *bytes = toBytes.data();

    uint unicode = 0;
    long i = charsOffset;
    long j = bytesOffset;
    for( ; i < charLi; i++){
        unicode = chars[i].unicode();
        if(0xd800 <= unicode && unicode <= 0xdfff){ //If surrogate
            if(byteLi - j < 4) break;
            if(charLi - i < 2){ break; } else {
                unicode = (unicode - 0xd800) * 0x400 + (chars[++i].unicode() - 0xdc00) + 0x10000;
                if(unicode > 0x10ffff){
                    bytes[j++] = '\\';
                    bytes[j++] = 239;
                    bytes[j++] = 191;
                    bytes[j++] = 189;
                }else{
                    bytes[j++] = (byte)(unicode / 262144 + 240);
                    bytes[j++] = (byte)((unicode % 262144) / 4096 + 128);
                    bytes[j++] = (byte)((unicode % 4096) / 64 + 128);
                    bytes[j++] = (byte)(unicode % 64 + 128);
                }
            }
        } else {
            if(unicode < 0x80){
                if(byteLi - j < 1) break;
                bytes[j++] = (byte)unicode;
            } else if(unicode < 0x0800){
                if(byteLi - j < 2) break;
                bytes[j++] = (byte)(unicode / 64 + 192);
                bytes[j++] = (byte)(unicode % 64 + 128);
            } else { // 0x0800 <= unicode && (unicode < 0xd800 || 0xdfff < unicode)
                if(byteLi - j < 3) break;
                bytes[j++] = (byte)(unicode / 4096 + 224);
                bytes[j++] = (byte)((unicode % 4096) / 64 + 128);
                bytes[j++] = (byte)(unicode % 64 + 128);
            }
        }
    }
    *charsUsed = i - charsOffset;
    *bytesUsed = j - bytesOffset;
    return *charsUsed == charCount || *bytesUsed == bytesOffset;
}
ByteArray UTF8Encoder::GetBytes(const CharArray &chars, long offset, long count)
{
    long len = this->GetLength(chars, offset, count);
    ByteArray bytes = ByteArray(len);
    long charsUsed, bytesUsed;
    if(!this->Encode(chars, offset, count, bytes, 0, len, &charsUsed, &bytesUsed)){
        if((len - bytesUsed) == 4){
            bytes[len - 4] = '\\';
            bytes[len - 3] = 239;
            bytes[len - 2] = 191;
            bytes[len - 1] = 189;
        } else if ((len - bytesUsed) == 3) {
            bytes[len - 3] = 239;
            bytes[len - 2] = 191;
            bytes[len - 1] = 189;
        }
        else for(int i = bytesUsed; i < len; i++)
            bytes[i] = '?';
    }
    return bytes;
}
long UTF8Encoder::GetLength(const CharArray &chars, long offset, long count) const
{
    long len = 0;
    Char16 *data = chars.data();
    long iLast = offset + count;
    for(int i = offset; i < iLast; i++){
        ushort unicode = data[i].unicode();
        int cl = 1 + (unicode > 0x7f) + (unicode > 0x800) + (0xd800 <= unicode && unicode < 0xe000);
        i += (cl >> 2);
        len += cl;
    }
    return len;
}

bool UTF16Encoder::Encode(const CharArray &fromChars, long charsOffset, long charCount, ByteArray &toBytes, long bytesOffset, long byteCount, long *charsUsed, long *bytesUsed)
{
    long charLi = charsOffset + charCount;
    long byteLi = bytesOffset + byteCount;

    if(charsOffset < 0)
        throw ArgumentOutOfRangeException("charsOffset cannot be less than zero.", "charsOffset");
    if(charCount < 0)
        throw ArgumentOutOfRangeException("charCount cannot be less than zero.");
    if(charLi > fromChars.length())
        throw OutOfRangeException("Block boundries was out of range of chars block.");
    if(bytesOffset < 0)
        throw ArgumentOutOfRangeException("Offset cannot be less than zero.", "bytesOffset");
    if(byteCount < 0)
        throw ArgumentOutOfRangeException("ByteCount cannot be less than zero.");
    if(byteLi > toBytes.length())
        throw OutOfRangeException("Block boundries was out of range of bytes block.");

    long i = charsOffset;
    long j = bytesOffset;
    Char16 *chars = fromChars.data();
    byte *bytes = toBytes.data();

    if(chars[charLi - 1].isSurrogate() && !chars[charLi - 2].isSurrogate())
        charLi--;

    byteLi >>= 1;

    for( ; (i < charLi) && ((j >> 1) < byteLi); ){
        ushort unicode = chars[i++].unicode();
        bytes[j++] = unicode;
        bytes[j++] = unicode >> 8;
    }
    *charsUsed = i - charsOffset;
    *bytesUsed = j - bytesOffset;
    return *charsUsed == charCount || *bytesUsed == bytesOffset;

}
ByteArray UTF16Encoder::GetBytes(const CharArray &chars, long offset, long count)
{
    ByteArray bytes = ByteArray(count << 1);
    long bytesUsed, charsUsed;
    if(!this->Encode(chars, offset, count, bytes, 0, bytes.length(), &charsUsed, &bytesUsed)){
        bytes[bytes.length() - 2] = 0xfd;
        bytes[bytes.length() - 1] = 0xff;
    }
    return bytes;
}
long UTF16Encoder::GetLength(const CharArray &chars, long offset, long count) const
{
    return count << 1;
    UseParameter(offset);
    void *c = (void *)&chars;
    UseParameter(c);
}

bool UTF32Encoder::Encode(const CharArray &fromChars, long charsOffset, long charCount, ByteArray &toBytes, long bytesOffset, long byteCount, long *charsUsed, long *bytesUsed)
{
    long charLi = charsOffset + charCount;
    long byteLi = bytesOffset + byteCount;

    if(charsOffset < 0)
        throw ArgumentOutOfRangeException("charsOffset cannot be less than zero.", "charsOffset");
    if(charCount < 0)
        throw ArgumentOutOfRangeException("charCount cannot be less than zero.");
    if(charLi > fromChars.length())
        throw OutOfRangeException("Block boundries was out of range of chars block.");
    if(bytesOffset < 0)
        throw ArgumentOutOfRangeException("Offset cannot be less than zero.", "bytesOffset");
    if(byteCount < 0)
        throw ArgumentOutOfRangeException("ByteCount cannot be less than zero.");
    if(byteLi > toBytes.length())
        throw OutOfRangeException("Block boundries was out of range of bytes block.");

    Char16 *chars = fromChars.data();
    byte *bytes = toBytes.data();

    long i = charsOffset;
    long j = bytesOffset;
    for( ; i < charLi && j < byteLi; i++){
        if(j + 4 > byteLi) break;
        uint unicode = chars[i].unicode();
        if(0xd800 <= unicode && unicode < 0xe000){
            if(i + 2 > charLi) break;
            unicode = (unicode - 0xd800) * 0x400 + chars[++i].unicode() - 0xdc00 + 0x10000;
        }
        bytes[j++] = unicode;
        bytes[j++] = unicode >> 8;
        bytes[j++] = unicode >> 16;
        bytes[j++] = unicode >> 24;
    }
    *charsUsed = i - charsOffset;
    *bytesUsed = j - bytesOffset;

    return *charsUsed == charCount || *bytesUsed == bytesOffset;
}
ByteArray UTF32Encoder::GetBytes(const CharArray &chars, long offset, long count)
{
    long len = this->GetLength(chars, offset, count);
    ByteArray bytes = ByteArray(len);
    long bytesUsed, charsUsed;
    if(!this->Encode(chars, offset, count, bytes, 0, bytes.length(), &charsUsed, &bytesUsed)){
        bytes[len - 4] = 0xfd;
        bytes[len - 3] = 0xff;
        bytes[len - 2] = 0;
        bytes[len - 1] = 0;
    }
    return bytes;
}
long UTF32Encoder::GetLength(const CharArray &chars, long offset, long count) const
{
    Char16 *data = chars.data();
    long iLast = count + offset;
    long utf32Len = 0;
    for(int i = offset; i < iLast; i++){
        ushort unicode = data[i].unicode();
        utf32Len += 4;
        i += (0xd800 <= unicode && unicode < 0xe000);
    }
    return utf32Len;
}
