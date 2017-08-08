#include "StringBuilder.h"
#include "../Exception.h"

StringBuilder::StringBuilder()
{
    this->_buffer = CharArray(256);
    this->_size = 0;
}
StringBuilder::StringBuilder(const CharArray &buffer, long length)
{
    this->_buffer = buffer;
    this->_size = length;
}
StringBuilder::StringBuilder(const String16 &str)
{
    long strLen = str.length();
    long reqSize = this->_size + strLen;
    long newSize = 1;
    while(newSize < reqSize)
        newSize <<= 1;
    this->_buffer.Resize(newSize);
    str.charsReference().CopyTo(0, this->_buffer, 0, strLen);
    this->_size = strLen;
}

StringBuilder &StringBuilder::Append(const String16 &str)
{
    long strLen = str.length();
    long reqSize = this->_size + strLen;
    if(reqSize > this->_buffer.length()){
        long newSize = this->_buffer.length();
        while(newSize < reqSize)
            newSize <<= 1;
        this->_buffer.Resize(newSize);
    }
    Char16 *bufData = this->_buffer.data();
    Char16 *strData = str.data();
    for(int j = 0; j < strLen; j++)
        bufData[this->_size++] = strData[j];
    return *this;
}
long StringBuilder::Count(long startIndex, const String16 &subStr) const
{
    if(startIndex > this->_buffer.length() - subStr.length())
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
CharArray StringBuilder::GetBuffer() const
{
    return this->_buffer;
}
long StringBuilder::FindIndex(long start, const String16 &subStr) const
{
    if(start < 0)
        throw ArgumentOutOfRangeException("Start index cannot be less than zero.", "start");
    if(start > this->_size)
        throw ArgumentOutOfRangeException("Start index cannot be greater than array length.", "start");
    if(subStr.length() == 0)
        return start;

    Char16 *data = this->_buffer.data();
    Char16 *ssData = subStr.data();
    Char16 f = ssData[0];
    long ssLen = subStr.length();
    for(int i = start; i < this->_size; i++){
        bool isEqual = true;
        if(data[i] == f){
            for(int j = 1; j < ssLen; j++){
                if(data[i + j] != ssData[j]){
                    isEqual = false;
                    break;
                }
            }
            if(isEqual)
                return i;
        }
    }
    return -1;
}
long StringBuilder::Length() const
{
    return this->_size;
}
StringBuilder &StringBuilder::Replace(const String16 &oldValue, const String16 &newValue)
{
    if(oldValue.isEmpty())
        throw ArgumentException("Old value cannot be empty.", "oldValue");
    long index = this->FindIndex(0, oldValue);
    if(index == -1)
        return *this;
    long start = 0;
    long arrayIndex = 0;
    long oldCount = this->Count(index + oldValue.length(), oldValue) + 1;

    long reqSize = this->_buffer.length() + (newValue.length() - oldValue.length()) * oldCount;
    long newSize = this->_buffer.length();
    if(reqSize > this->_buffer.length()){
        long newSize = this->_buffer.length();
        while(newSize < reqSize)
            newSize <<= 1;
    }

    CharArray array = CharArray(newSize);

    long newLen = newValue.length();
    Char16 *arrayData = array.data();
    Char16 *thisData = this->_buffer.data();
    Char16 *newData = newValue.data();

    while(index != -1){
        for(long i = start; i < index; i++, arrayIndex++)
            arrayData[arrayIndex] = thisData[i];
        for(long i = 0; i < newLen; i++, arrayIndex++)
            arrayData[arrayIndex] = newData[i];

        index += oldValue.length();
        start = index;
        index = this->FindIndex(start, oldValue);
    }
    for(long i = start; i < this->_size; i++, arrayIndex++)
        arrayData[arrayIndex] = thisData[i];
    this->_size = reqSize;
    this->_buffer = array;
    return *this;
}
StringBuilder &StringBuilder::SubString(long offset, long count)
{
    if(offset < 0)
        throw ArgumentOutOfRangeException("Offset cannot be less than zero.", "offset");
    if(offset + count > this->_size)
        throw OutOfRangeException("Block boundries was out of range of source block.");
    if(offset == 0){
        this->_size = count;
        return *this;
    }
    Char16 *data = this->_buffer.data();
    for(long i = 0; i < count; i++)
        data[i] = data[offset++];
    return *this;
}
StringBuilder &StringBuilder::ToLower()
{
    if(this->_size == 0)
        return *this;
    Char16 *data = this->_buffer.data();
    for(long i = 0; i < this->_size; i++)
        data[i] = data[i].ToLower();
    return *this;
}
String16 StringBuilder::ToString() const
{
    return String16(this->_buffer, 0, this->_size);
}
StringBuilder &StringBuilder::ToTitleCase()
{
    if(this->_size == 0)
        return *this;
    Char16 *data = this->_buffer.data();
    data[0] = data[0].ToUpper();
    for(long i = 1; i < this->_size; i++)
        data[i] = data[i].ToLower();
    return *this;
}
StringBuilder &StringBuilder::ToUpper()
{
    if(this->_size == 0)
        return *this;
    Char16 *data = this->_buffer.data();
    for(long i = 0; i < this->_size; i++)
        data[i] = data[i].ToUpper();
    return *this;
}
