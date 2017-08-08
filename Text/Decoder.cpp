#include <cstring>
#include "Decoder.h"
#include "../Exception.h"

UTF8Decoder Decoder::UTF8 = UTF8Decoder();
UTF16Decoder Decoder::UTF16 = UTF16Decoder();
UTF32Decoder Decoder::UTF32 = UTF32Decoder();

bool UTF8Decoder::Decode(const ByteArray &fromBytes, long bytesOffset, long byteCount, CharArray &toChars, long charsOffset, long charCount, long *bytesUsed, long *charsUsed)
{
    long byteLi = bytesOffset + byteCount;
    long charLi = charsOffset + charCount;
    if(bytesOffset < 0)
        throw ArgumentOutOfRangeException("Offset cannot be less than zero.", "bytesOffset");
    if(byteCount < 0)
        throw ArgumentOutOfRangeException("ByteCount cannot be less than zero.");
    if(byteLi > fromBytes.length())
        throw OutOfRangeException("Block boundries was out of range of bytes block.");
    if(charsOffset < 0)
        throw ArgumentOutOfRangeException("charsOffset cannot be less than zero.", "charsOffset");
    if(charCount < 0)
        throw ArgumentOutOfRangeException("charCount cannot be less than zero.");
    if(charLi > toChars.length())
        throw OutOfRangeException("Block boundries was out of range of chars block.");
    byte *bytes = fromBytes.data();
    Char16 *chars = toChars.data();

    long i = bytesOffset;
    long j = charsOffset;
    for( ; i < byteLi && j < charLi; ){
        if(bytes[i] > 239){
            if(byteLi - i < 4) { break; }
            uint unicode = (bytes[i] - 240) * 262144 + (bytes[i + 1] - 128) * 4096 + (bytes[i + 2] - 128) * 64 + bytes[i + 3] - 128;
            i += 4;
            if(unicode > 0x10FFFF){ //Out of definition of RFC 3629
                chars[j++] = Char16((ushort)0xfffd); //Add Replacement character.
                chars[j++] = Char16((ushort)0xfffd);
            }else{
                ushort ch = (unicode - 0x10000) / 0x400 + 0xd800;
                ushort cl = (unicode - 0x10000) % 0x400 + 0xdc00;
                chars[j++] = Char16(ch);
                chars[j++] = Char16(cl);
            }
        }else if(bytes[i] < 128){
            chars[j++] = Char16((ushort)bytes[i++]);
        } else if(bytes[i] > 223){
            if(byteLi - i < 3) { break; }
            uint unicode = ((bytes[i] - 224) * 4096 + (bytes[i + 1] - 128) * 64 + bytes[i + 2] - 128);
            if (0xd7ff < unicode && unicode < 0xe000) chars[j++] = Char16((ushort)0xfffd); //Why the fuck are the surrogate characters encoded with UTF8?
            else chars[j++] = Char16((ushort)unicode);
            i += 3;
        } else if(bytes[i] > 191){
            if(byteLi - i < 2) { break; }
            chars[j++] = Char16((ushort)((bytes[i] - 192) * 64 + bytes[i + 1] - 128));
            i += 2;
        } else {
            chars[j++] = Char16((ushort)0xfffd); //Unrecognized character.
            i++;
        }
    }
    *bytesUsed = i - bytesOffset;
    *charsUsed = j - charsOffset;
    return *bytesUsed == byteCount || *charsUsed == charCount;
}
CharArray UTF8Decoder::GetChars(const ByteArray &bytes)
{
    long len = this->GetLength(bytes, 0, bytes.length());
    CharArray chars = CharArray(len);
    long bytesUsed, charsUsed;
    if(!this->Decode(bytes, 0, bytes.length(), chars, 0, chars.length(), &bytesUsed, &charsUsed))
    {
        Char16 replacement = Char16((ushort)0xfffd);
        for(int i = charsUsed; i < len; i++)
            chars[i] = replacement;
    }
    return chars;
}
long UTF8Decoder::GetLength(const ByteArray &bytes, long offset, long count) const
{
    long len = 0;
    long utf8Start = offset;
    long iLast = offset + count;
    byte *data = bytes.data();
    while(utf8Start < iLast){
        int head = data[utf8Start];
        int cl = 1 + ((head & 0xf0) == 0xf0) + ((head & 0xe0) == 0xe0) + ((head & 0xc0) == 0xc0);
        len += 1 + (cl >> 2);
        utf8Start += cl;
    }
    return len;
}

bool UTF16Decoder::Decode(const ByteArray &fromBytes, long bytesOffset, long byteCount, CharArray &toChars, long charsOffset, long charCount, long *bytesUsed, long *charsUsed)
{
    long byteLi = bytesOffset + byteCount;
    long charLi = charsOffset + charCount;

    if(bytesOffset < 0)
        throw ArgumentOutOfRangeException("Offset cannot be less than zero.", "bytesOffset");
    if(byteCount < 0)
        throw ArgumentOutOfRangeException("ByteCount cannot be less than zero.");
    if(byteLi > fromBytes.length())
        throw OutOfRangeException("Block boundries was out of range of bytes block.");
    if(charsOffset < 0)
        throw ArgumentOutOfRangeException("charsOffset cannot be less than zero.", "charsOffset");
    if(charCount < 0)
        throw ArgumentOutOfRangeException("charCount cannot be less than zero.");
    if(charLi > toChars.length())
        throw OutOfRangeException("Block boundries was out of range of chars block.");

    byte *bytes = fromBytes.data();
    Char16 *chars = toChars.data();

    long i = bytesOffset;
    long j = charsOffset;
    byteLi >>= 1;

    for( ; (i >> 1) < byteLi && j < charLi ; ){
        ushort unicode = bytes[i] | (bytes[i + 1] << 8);
        if(0xd800 <= unicode && unicode < 0xdc00){
            if((i + 4) > (byteLi << 1)) break;
        }
        chars[j++] = Char16(unicode);
        i += 2;
    }
    *bytesUsed = i - bytesOffset;
    *charsUsed = j - charsOffset;
    return *bytesUsed == byteCount || *charsUsed == charCount;
}
CharArray UTF16Decoder::GetChars(const ByteArray &bytes)
{
    long len = (bytes.length() + 1) >> 1;
    CharArray chars = CharArray(len);
    long bytesUsed, charsUsed;
    if(!this->Decode(bytes, 0, bytes.length(), chars, 0, len, &bytesUsed, &charsUsed)){
        chars[len - 1] = Char16((ushort)0xfffd);
    }
    return chars;
}
long UTF16Decoder::GetLength(const ByteArray &bytes, long offset, long count) const
{
    return (count + 1) >> 1;
    UseParameter(offset);
    void *b = (void *)&bytes;
    UseParameter(b);
}

bool UTF32Decoder::Decode(const ByteArray &fromBytes, long bytesOffset, long byteCount, CharArray &toChars, long charsOffset, long charCount, long *bytesUsed, long *charsUsed)
{
    long byteLi = bytesOffset + byteCount;
    long charLi = charsOffset + charCount;

    if(bytesOffset < 0)
        throw ArgumentOutOfRangeException("Offset cannot be less than zero.", "bytesOffset");
    if(byteCount < 0)
        throw ArgumentOutOfRangeException("ByteCount cannot be less than zero.");
    if(byteLi > fromBytes.length())
        throw OutOfRangeException("Block boundries was out of range of bytes block.");
    if(charsOffset < 0)
        throw ArgumentOutOfRangeException("charsOffset cannot be less than zero.", "charsOffset");
    if(charCount < 0)
        throw ArgumentOutOfRangeException("charCount cannot be less than zero.");
    if(charLi > toChars.length())
        throw OutOfRangeException("Block boundries was out of range of chars block.");

    byte *bytes = fromBytes.data();
    Char16 *chars = toChars.data();

    long i = bytesOffset;
    long j = charsOffset;

    for( ; i < byteLi && j < charLi; ){
        if(i + 4 > byteLi) break;
        uint unicode = bytes[i] | (bytes[i + 1] << 8) | (bytes[i + 2] << 16) | (bytes[i + 3] << 24);
        if(unicode > 0xffff){
            if(j + 2 > charLi) break;
            ushort ch = (unicode - 0x10000) / 0x400 + 0xd800;
            ushort cl = (unicode - 0x10000) % 0x400 + 0xdc00;
            chars[j++] = Char16(ch);
            chars[j++] = Char16(cl);
        } else chars[j++] = Char16((ushort)unicode);
        i += 4;
    }

    *bytesUsed = i - bytesOffset;
    *charsUsed = j - charsOffset;
    return *bytesUsed == byteCount || *charsUsed == charCount;
}
CharArray UTF32Decoder::GetChars(const ByteArray &bytes)
{
    long len = this->GetLength(bytes, 0, bytes.length());
    CharArray chars = CharArray(len);
    long bytesUsed, charsUsed;
    if(!this->Decode(bytes, 0, bytes.length(), chars, 0, chars.length(), &bytesUsed, &charsUsed)){
        chars[len - 1] = Char16((ushort)0xfffd);
    }
    return chars;
}
long UTF32Decoder::GetLength(const ByteArray &bytes, long offset, long count) const
{
    uint *utf32Codes = (uint *)(bytes.data() + offset);
    long utf32Len = (offset + count) / 4;
    long utf16Len = 0;
    for(int i = offset / 4; i < utf32Len; i++){
        uint unicode = utf32Codes[i];
        utf16Len += 1 + (unicode > 0xffff);
    }
    return utf16Len + ((count & 3) > 0);
}
