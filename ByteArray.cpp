#include <cstring>
#include "ByteArray.h"
#include "Exception.h"

struct ByteArray::_impl{
    byte *_data;
    long _size;
    uint _refc;
    bool _deepCopy = true;
};

ByteArray::ByteArray()
{

}
ByteArray::ByteArray(long length)
{
    if(length < 0)
        throw InvalidOperationException("Array length cannot be negative.");
    if(length == 0)
        return;
    this->_pImpl = new ByteArray::_impl();
    this->_pImpl->_data = new byte[length];
    this->_pImpl->_size = length;
    this->_pImpl->_refc = 1;
}
ByteArray::ByteArray(const char *utf8Str)
{
    if(utf8Str == nullptr)
        throw ArgumentNullException("UTF8 string pointer cannot be null.", "utf8Str");
    long length = strlen(utf8Str);
    this->_pImpl = new ByteArray::_impl();
    this->_pImpl->_data = new byte[length];
    for(long i = 0; i < length; i++)
        this->_pImpl->_data[i] = utf8Str[i];
    this->_pImpl->_size = length;
    this->_pImpl->_refc = 1;
}
ByteArray::ByteArray(byte *dataSource, long length, bool deepCopy)
{
    if(dataSource == nullptr)
        throw ArgumentNullException("Source pointer cannot be null.", "dataSource");
    if(length < 0)
        throw InvalidOperationException("Array length cannot be negative.");
    if(length == 0)
        return;
    this->_pImpl = new ByteArray::_impl();
    if(deepCopy){
        this->_pImpl->_data = new byte[length];
        for(long i = 0; i < length; i++)
            this->_pImpl->_data[i] = dataSource[i];
        this->_pImpl->_size = length;
        this->_pImpl->_refc = 1;
    } else {
        this->_pImpl->_data = dataSource;
        this->_pImpl->_size = length;
        this->_pImpl->_refc = 1;
        this->_pImpl->_deepCopy = false;
    }

}
ByteArray::ByteArray(const ByteArray &array)
{
    this->_pImpl = array._pImpl;
    if(this->_pImpl != nullptr)
        this->_pImpl->_refc++;
}

ByteArray::~ByteArray()
{
    if(this->_pImpl != nullptr){
        if(this->_pImpl->_refc == 1){
            if(this->_pImpl->_deepCopy)
                delete[] this->_pImpl->_data;
            delete this->_pImpl;
        } else this->_pImpl->_refc--;
    }
}

ByteArray ByteArray::Clone() const
{
    if(this->_pImpl == nullptr)
        return ByteArray();
    ByteArray clone = ByteArray(this->_pImpl->_size);
    this->CopyTo(0, clone, 0, this->_pImpl->_size);
    return clone;
}
void ByteArray::CopyTo(long offset, ByteArray destination, long destOffset, long count) const
{
    if(this->_pImpl == nullptr || destination._pImpl == nullptr)
        throw OutOfRangeException("Block boundries was out of range of source block.");
    if(offset < 0)
        throw ArgumentOutOfRangeException("Offset cannot be less than zero.", "offset");
    if(destOffset < 0)
        throw ArgumentOutOfRangeException("Destination offset cannot be less than zero.", "destOffset");
    if(offset + count > this->_pImpl->_size)
        throw OutOfRangeException("Block boundries was out of range of source block.");
    if(destOffset + count > destination._pImpl->_size)
        throw OutOfRangeException("Block boundries was out of range of destination block.");
    if(count < 0)
        throw ArgumentOutOfRangeException("Count cannot be less than zero.");

    if(this->_pImpl == destination._pImpl && offset < destOffset){
        byte *tmp = new byte[count];
        for(int i = 0; i < count; i++)
            tmp[i] = this->_pImpl->_data[i + offset];
        for(int i = 0; i < count; i++)
            this->_pImpl->_data[i + destOffset] = tmp[i];
        delete[] tmp;
    } else {
        long lastIndex = destOffset + count;
        for(long i = destOffset; i < lastIndex; i++){
            destination._pImpl->_data[i] = this->_pImpl->_data[offset++];
        }
    }
}
byte *ByteArray::data(long index) const
{
    if(this->_pImpl == nullptr || this->length() == 0)
        return nullptr;
    if(index < 0 || index >= this->_pImpl->_size)
        throw ArgumentOutOfRangeException("Segmentation fault.", "offset");
    return &this->_pImpl->_data[index];
}
bool ByteArray::Equals(const ByteArray &array) const
{
    if(this->_pImpl == nullptr && array._pImpl == nullptr)
        return true;
    if(this->_pImpl == nullptr || array._pImpl == nullptr)
        return false;

    if(this->_pImpl->_size != array._pImpl->_size)
        return false;
    for(int i = 0; i < this->_pImpl->_size; i++)
        if(this->_pImpl->_data[i] != array._pImpl->_data[i])
            return false;
    return true;
}
void ByteArray::FillZero()
{
    if(this->_pImpl == nullptr)
        return;
    for(int i = 0; i < this->_pImpl->_size; i++)
        this->_pImpl->_data[i] = 0;
}
long ByteArray::FindIndex(long start, ByteArray subset) const
{
    if(start < 0)
        throw ArgumentOutOfRangeException("Start index cannot be less than zero.", "start");
    if(start > this->_pImpl->_size)
        throw ArgumentOutOfRangeException("Start index cannot be greater than array length.", "start");
    if(subset.length() == 0)
        return start;

    byte *data = this->_pImpl->_data;
    byte *ssData = subset._pImpl->_data;
    byte f = ssData[0];
    for(int i = start; i < this->_pImpl->_size; i++){
        bool isEqual = true;
        if(data[i] == f){
            for(int j = 1; j < subset._pImpl->_size; j++){
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
long ByteArray::length() const
{
    if(this->_pImpl == nullptr)
        return 0;
    return this->_pImpl->_size;
}
void ByteArray::Resize(long newSize)
{
    if(newSize < 0)
        throw InvalidOperationException("Array length cannot be negative.");
    if(this->_pImpl == nullptr){
        this->_pImpl = new ByteArray::_impl();
        this->_pImpl->_data = new byte[newSize];
        this->_pImpl->_refc = 1;
        this->_pImpl->_size = newSize;
        return;
    }
    if(newSize == this->_pImpl->_size)
        return;

    byte *newArray = new byte[newSize];
    long copySize = newSize < this->_pImpl->_size ? newSize : this->_pImpl->_size;
    for(long i = 0; i < copySize; i++)
        newArray[i] = this->_pImpl->_data[i];
    delete[] this->_pImpl->_data;
    this->_pImpl->_data = newArray;
    this->_pImpl->_size = newSize;
}
void ByteArray::Reverse()
{
    if(this->_pImpl == nullptr || this->_pImpl->_size == 0)
        return;
    long e = this->_pImpl->_size >> 1;
    long uiLast = this->_pImpl->_size - 1;
    for(long i = 0; i < e; i++){
        byte eFirst = this->_pImpl->_data[i];
        this->_pImpl->_data[i] = this->_pImpl->_data[uiLast];
        this->_pImpl->_data[uiLast] = eFirst;
        uiLast--;
    }
}
ByteArray ByteArray::Slice(long offset, long count, bool deepCopy) const
{
    if(this->_pImpl == nullptr)
        throw OutOfRangeException("Block boundries was out of range of source block.");
    if(offset + count > this->_pImpl->_size)
        throw OutOfRangeException("Block boundries was out of range of source block.");
    return ByteArray(&this->_pImpl->_data[offset], count, deepCopy);
}

ByteArray &ByteArray::operator=(const ByteArray &array)
{
    if(this->_pImpl != array._pImpl){
        if(this->_pImpl != nullptr){
            if(this->_pImpl->_refc == 1){
                if(this->_pImpl->_deepCopy)
                    delete[] this->_pImpl->_data;
                delete this->_pImpl;
            } else this->_pImpl->_refc--;
        }
        this->_pImpl = array._pImpl;
        if(array._pImpl != nullptr)
            this->_pImpl->_refc++;
    } return *this;
}
byte &ByteArray::operator[](long index)
{
    if(index < 0)
        throw IndexOutOfRangeException("Index cannot be less than zero.");
    if(this->_pImpl == nullptr)
        throw IndexOutOfRangeException("Array was empty.");
    if(index >= this->_pImpl->_size)
        throw IndexOutOfRangeException("Index must be less than array length.");
    return this->_pImpl->_data[index];
}
byte ByteArray::operator[](long index) const
{
    if(index < 0)
        throw IndexOutOfRangeException("Index cannot be less than zero.");
    if(this->_pImpl == nullptr)
        throw IndexOutOfRangeException("Array was empty.");
    if(index >= this->_pImpl->_size)
        throw IndexOutOfRangeException("Index must be less than array length.");
    return this->_pImpl->_data[index];
}

bool ByteArray::Equals(const Object &obj) const
{
    return this->Equals((const ByteArray &)obj);
}
long ByteArray::GetHashCode() const
{
    return (long)this->_pImpl;
}
