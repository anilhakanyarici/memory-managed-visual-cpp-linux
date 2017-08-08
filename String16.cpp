#include "String16.h"
#include "Exception.h"
#include "ByteArray.h"

String16::String16() { }
String16::String16(Char16 c) { this->_chars.Resize(1); this->_chars[0] = c; }
String16::String16(const char *cString) { this->_chars = CharArray(cString); }
String16::String16(const String16 &str) { this->_chars = str._chars.Clone(); }
String16::String16(const CharArray &array, bool deepCopy) { if(deepCopy) this->_chars = array.Clone(); else this->_chars = array; }
String16::String16(const CharArray &array, long offset, long count) { this->_chars = array.Slice(offset, count); }

String16 String16::Append(const String16 &str) const
{
    long thisLen = this->_chars.length();
    long strLen = str._chars.length();
    CharArray a = CharArray(thisLen + strLen);
    Char16 *aData = a.data();
    Char16 *thisData = this->_chars.data();
    Char16 *strData = str._chars.data();
    for(long i = 0; i < thisLen; i++)
        aData[i] = thisData[i];
    for(long i = 0; i < strLen; i++)
        aData[i + thisLen] = strData[i];
    return String16(a, false);
}
bool String16::Contains(Char16 ch) const
{
    Char16 *data = this->_chars.data();
    for(long i = 0; i < this->_chars.length(); i++)
        if(ch == data[i])
            return true;
    return false;
}
long String16::Count(long startIndex, const String16 &subStr) const
{
    if(startIndex > this->_chars.length() - subStr.length())
        return 0;
    long count = 0;
    long index = this->FindIndex(startIndex, subStr);
    while(index != -1){
        count++;
        index += subStr.length();
        startIndex = index;
        index = this->FindIndex(startIndex, subStr);
    }
    return count;
}
const CharArray &String16::charsReference() const { return this->_chars; }
Char16 *String16::data(long index) const
{
    return this->_chars.data(index);
}
bool String16::EndsWith(const String16 &end) const
{
    if(this->_chars.length() < end._chars.length())
        return false;
    long j = 0;
    Char16 *endData = end._chars.data();
    Char16 *thisData = this->_chars.data();
    for(long i = this->_chars.length() - end._chars.length(); i < this->_chars.length(); i++){
        if(endData[j] != thisData[i])
            return false;
        j++;
    }
    return true;
}
bool String16::Equals(const String16 &other) const { return this->_chars.Equals(other._chars); }
long String16::FindIndex(long startIndex, const String16 &subset) const { return this->_chars.FindIndex(startIndex, subset._chars); }
long String16::GetHashCode() const
{
    ushort *data = (ushort *)this->data();
    long h1 = 5381, h2 = 5381;
    long len = this->length();
    for(long i = this->length() & 1; i < len; i += 2){
        h1 = ((h1 << 5) + h1) ^ data[i];
        h2 = ((h2 << 5) + h2) ^ ((long)data[i + 1] << 16);
    }
    return h1 + ((h2 + (len & 1) * data[0]) * 1566083941l);
}
bool String16::isEmpty() const
{
    return this->_chars.length() == 0 || (this->_chars.length() == 1 && this->_chars[0] == '\0');
}
bool String16::isNumeric() const
{
    Char16 *data = this->_chars.data();
    long charLen = this->_chars.length();
    if(charLen >= 2 && (data[0] == '.' || data[charLen - 1] == '.'))
        return false;
    charLen--;

    for(long i = 1; i < charLen; i++)
        if(!data[i].isDigit() || data[i] != '.')
            return false;
    return true;
}
bool String16::isInteger() const
{
    Char16 *data = this->_chars.data();
    long charLen = this->_chars.length();
    for(long i = 0; i < charLen; i++)
        if(!data[i].isDigit())
            return false;
    return true;
}
long String16::length() const { return this->_chars.length(); }
StringList String16::Split(const String16 &seperator) const
{
    StringList list = StringList();
    if(seperator.isEmpty())
        return list;
    long index = this->FindIndex(0, seperator);
    if(index == -1)
        return list.Add(*this);
    long start = 0;
    while(index != -1){
        list.Add(this->SubString(start, index - start));
        index += seperator.length();
        start = index;
        index = this->FindIndex(start, seperator);
    }
    if(start < this->_chars.length())
        list.Add(this->SubString(start, this->_chars.length() - start));
    return list;
}
bool String16::StartWith(const String16 &start) const
{
    if(start._chars.length() > this->_chars.length())
        return false;
    Char16 *startData = start._chars.data();
    Char16 *thisData = this->_chars.data();
    for(long i = 0; i < start._chars.length(); i++){
        if(startData[i] != thisData[i])
            return false;
    }
    return true;
}
String16 String16::SubString(long offset, long count) const { return String16(this->_chars, offset, count); }
String16 String16::Replace(const String16 &oldValue, const String16 &newValue) const
{
    if(oldValue.isEmpty())
        throw ArgumentException("Old value cannot be empty.", "oldValue");
    long index = this->FindIndex(0, oldValue);
    if(index == -1)
        String16(this->_chars);
    long start = 0;
    long arrayIndex = 0;
    long oldCount = this->Count(index + oldValue.length(), oldValue) + 1;

    CharArray array = CharArray(this->_chars.length() + (newValue.length() - oldValue.length()) * oldCount);

    long newLen = newValue.length();
    Char16 *arrayData = array.data();
    Char16 *thisData = this->_chars.data();
    Char16 *newData = newValue._chars.data();

    while(index != -1){
        for(long i = start; i < index; i++, arrayIndex++)
            arrayData[arrayIndex] = thisData[i];
        for(long i = 0; i < newLen; i++, arrayIndex++)
            arrayData[arrayIndex] = newData[i];

        index += oldValue.length();
        start = index;
        index = this->FindIndex(start, oldValue);
    }
    long thisLen = this->_chars.length();
    for(long i = start; i < thisLen; i++, arrayIndex++)
        arrayData[arrayIndex] = thisData[i];
    return String16(array, false);
}
CharArray String16::ToArray() const { return this->_chars.Clone(); }

ByteArray String16::ToCString() const
{
    long len = Encoder::UTF8.GetLength(this->_chars, 0, this->_chars.length());
    ByteArray bytes = ByteArray(len + 1);
    long charsUsed, bytesUsed;
    if(!Encoder::UTF8.Encode(this->_chars, 0, this->_chars.length(), bytes, 0, len, &charsUsed, &bytesUsed)){
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
    bytes[len] = '\0';
    return bytes;
}
String16 String16::ToLower() const
{
    if(this->_chars.length() == 0)
        return String16();
    CharArray copy = CharArray(this->_chars.length());
    Char16 *data = this->_chars.data();
    Char16 *copyData = copy.data();

    for(long i = 0; i < copy.length(); i++)
        copyData[i] = data[i].ToLower();
    return String16(copy);
}
String16 String16::ToTitleCase() const
{
    if(this->_chars.length() == 0)
        return String16();
    CharArray copy = CharArray(this->_chars.length());
    Char16 *data = this->_chars.data();
    Char16 *copyData = copy.data();

    copyData[0] = data[0].ToUpper();
    for(long i = 1; i < copy.length(); i++)
        copyData[i] = data[i].ToLower();
    return String16(copy);
}
String16 String16::ToUpper() const
{
    if(this->_chars.length() == 0)
        return String16();
    CharArray copy = CharArray(this->_chars.length());
    Char16 *data = this->_chars.data();
    Char16 *copyData = copy.data();

    for(long i = 0; i < copy.length(); i++)
        copyData[i] = data[i].ToUpper();
    return String16(copy);
}
String16 String16::Trim(const String16 &charSet) const
{
    long sPos = 0;
    long ePos = this->_chars.length() - 1;
    Char16 *data = this->_chars.data();
    while(sPos < ePos && charSet.Contains(data[sPos])) sPos++;
    while(ePos >= sPos && charSet.Contains(data[ePos])) ePos--;
    return this->SubString(sPos, ePos - sPos + 1);
}
String16 String16::TrimEnd(const String16 &charSet) const
{
    long ePos = this->_chars.length();
    Char16 *data = this->_chars.data();
    while(ePos >= 0 && charSet.Contains(data[--ePos]));
    return this->SubString(0, ePos + 1);
}
String16 String16::TrimStart(const String16 &charSet) const
{
    long sPos = 0;
    long ePos = this->_chars.length();
    Char16 *data = this->_chars.data();
    while(sPos <= ePos && charSet.Contains(data[sPos++]));
    return this->SubString(sPos - 1, ePos - sPos + 1);
}

String16 String16::Format(const String16 &format, const StringList &args)
{
    String16 placeHolder = "%s";
    if(format.isEmpty())
        throw ArgumentException("Formattable parameter cannot be empty.", "format");
    long index = format.FindIndex(0, placeHolder);
    if(index == -1 && args.count() > 0)
        throw ArgumentException("Placeholders (%%s) count must be equals arguments count.", "format");
    long start = 0;
    long arrayIndex = 0;
    int argsIndex = 0;
    long placeHolderCount = format.Count(index + placeHolder.length(), placeHolder) + 1;
    if(placeHolderCount != args.count())
        throw ArgumentException("Placeholders (%%s) count must be equals arguments count.", "format");

    CharArray array = CharArray(format._chars.length() - (placeHolderCount << 1) + args.charCount());
    String16 curr = args[argsIndex];
    long newLen = curr.length();
    Char16 *arrayData = array.data();
    Char16 *thisData = format._chars.data();
    Char16 *newData = curr.data();

    while(index != -1){
        for(long i = start; i < index; i++, arrayIndex++)
            arrayData[arrayIndex] = thisData[i];
        for(long i = 0; i < newLen; i++, arrayIndex++)
            arrayData[arrayIndex] = newData[i];
        argsIndex++;
        if(argsIndex == args.count()){
            start = index + placeHolder.length();
            break;
        }
        curr = args[argsIndex];
        newLen = curr.length();
        newData = curr.data();

        index += placeHolder.length();
        start = index;
        index = format.FindIndex(start, placeHolder);
    }
    long thisLen = format._chars.length();
    for(long i = start; i < thisLen; i++, arrayIndex++)
        arrayData[arrayIndex] = thisData[i];
    return String16(array, false);
}

String16 &String16::operator =(const String16 &str) { this->_chars = str._chars.Clone(); return *this; }
String16 &String16::operator =(const CharArray &charsArray) { this->_chars = charsArray; return *this; }
String16 &String16::operator =(const char *cString) { this->_chars = CharArray(cString); return *this; }
StringList String16::operator ,(const String16 &item) const
{
    StringList list = StringList();
    list.Add(*this);
    list.Add(item);
    return list;
}

bool String16::Equals(const Object &obj) const
{
    return this->Equals((const String16 &)obj);
}

