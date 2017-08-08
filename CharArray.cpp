#include <cstring>
#include "CharArray.h"
#include "Exception.h"

struct CharArray::_impl{
    Char16 *_data;
    long _size;
    uint _refc;
    bool _deepCopy = true;
};

CharArray::CharArray()
{

}
CharArray::CharArray(long length)
{
    if(length < 0)
        throw InvalidOperationException("Array length cannot be negative.");
    if(length == 0)
        return;
    this->_pImpl = new CharArray::_impl();
    this->_pImpl->_data = new Char16[length];
    this->_pImpl->_size = length;
    this->_pImpl->_refc = 1;
}
CharArray::CharArray(const char *utf8Str)
{
    long length = 0;
    long utf8Start = 0;
    long iLast = strlen(utf8Str);
    byte *data = (byte *)utf8Str;
    while(utf8Start < iLast){
        int head = data[utf8Start];
        int cl = 1 + ((head & 0xf0) == 0xf0) + ((head & 0xe0) == 0xe0) + ((head & 0xc0) == 0xc0);
        length += 1 + (cl >> 2);
        utf8Start += cl;
    }
    this->_pImpl = new CharArray::_impl();
    this->_pImpl->_data = new Char16[length];
    this->_pImpl->_size = length;
    this->_pImpl->_refc = 1;

    long i = 0;
    long j = 0;
    for( ; i < iLast; ){
        if(data[i] > 239){
            uint unicode = (data[i] - 240) * 262144 + (data[i + 1] - 128) * 4096 + (data[i + 2] - 128) * 64 + data[i + 3] - 128;
            i += 4;
            if(unicode > 0x10FFFF){ //Out of definition of RFC 3629
                this->_pImpl->_data[j++] = Char16((ushort)0xfffd); //Add Replacement character.
                this->_pImpl->_data[j++] = Char16((ushort)0xfffd);
            }else{
                ushort ch = (unicode - 0x10000) / 0x400 + 0xd800;
                ushort cl = (unicode - 0x10000) % 0x400 + 0xdc00;
                this->_pImpl->_data[j++] = Char16(ch);
                this->_pImpl->_data[j++] = Char16(cl);
            }
        }else if(data[i] < 128){
            this->_pImpl->_data[j++] = Char16((ushort)data[i++]);
        } else if(data[i] > 223){
            if(iLast - i < 3) { break; }
            uint unicode = ((data[i] - 224) * 4096 + (data[i + 1] - 128) * 64 + data[i + 2] - 128);
            if (0xd7ff < unicode && unicode < 0xe000) this->_pImpl->_data[j++] = Char16((ushort)0xfffd); //Why the fuck are the surrogate characters encoded with UTF8?
            else this->_pImpl->_data[j++] = Char16((ushort)unicode);
            i += 3;
        } else if(data[i] > 191){
            this->_pImpl->_data[j++] = Char16((ushort)((data[i] - 192) * 64 + data[i + 1] - 128));
            i += 2;
        } else {
            this->_pImpl->_data[j++] = Char16((ushort)0xfffd); //Unrecognized character.
            i++;
        }
    }
}
CharArray::CharArray(Char16 *dataSource, long length, bool deepCopy)
{
    if(dataSource == nullptr)
        throw ArgumentNullException("Source pointer cannot be null.", "dataSource");
    if(length < 0)
        throw InvalidOperationException("Array length cannot be negative.");
    if(length == 0)
        return;
    this->_pImpl = new CharArray::_impl();
    if(deepCopy){
        this->_pImpl->_data = new Char16[length];
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
CharArray::CharArray(const CharArray &array)
{
    this->_pImpl = array._pImpl;
    if(this->_pImpl != nullptr)
        this->_pImpl->_refc++;
}

CharArray::~CharArray()
{
    if(this->_pImpl != nullptr){
        if(this->_pImpl->_refc == 1){
            if(this->_pImpl->_deepCopy)
                delete[] this->_pImpl->_data;
            delete this->_pImpl;
        } else this->_pImpl->_refc--;
    }
}

CharArray CharArray::Clone() const
{
    if(this->_pImpl == nullptr)
        return CharArray();
    CharArray clone = CharArray(this->_pImpl->_size);
    this->CopyTo(0, clone, 0, this->_pImpl->_size);
    return clone;
}
void CharArray::CopyTo(long offset, CharArray destination, long destOffset, long count) const
{
    if(count == 0)
        return;
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
        Char16 *tmp = new Char16[count];
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
Char16 *CharArray::data(long index) const
{
    if(this->_pImpl == nullptr || this->length() == 0)
        return nullptr;
    if(index < 0 || index >= this->_pImpl->_size)
        throw ArgumentOutOfRangeException("Segmentation fault.", "offset");
    return &this->_pImpl->_data[index];
}
long CharArray::FindIndex(long start, CharArray subset) const
{
    if(this->_pImpl == nullptr)
        return -1;
    if(start < 0)
        throw ArgumentOutOfRangeException("Start index cannot be less than zero.", "start");
    if(start > this->_pImpl->_size)
        throw ArgumentOutOfRangeException("Start index cannot be greater than array length.", "start");
    if(subset.length() == 0)
        return start;

    Char16 *data = this->_pImpl->_data;
    Char16 *ssData = subset._pImpl->_data;
    Char16 f = ssData[0];
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
bool CharArray::Equals(const CharArray &array) const
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
void CharArray::FillZero()
{
    if(this->_pImpl == nullptr)
        return;
    for(int i = 0; i < this->_pImpl->_size; i++)
        this->_pImpl->_data[i] = Char16();
}
long CharArray::length() const
{
    if(this->_pImpl == nullptr)
        return 0;
    return this->_pImpl->_size;
}
void CharArray::Resize(long newSize)
{
    if(newSize < 0)
        throw InvalidOperationException("Array length cannot be negative.");
    if(this->_pImpl == nullptr){
        this->_pImpl = new CharArray::_impl();
        this->_pImpl->_data = new Char16[newSize];
        this->_pImpl->_refc = 1;
        this->_pImpl->_size = newSize;
        return;
    }
    if(newSize == this->_pImpl->_size)
        return;

    Char16 *newArray = new Char16[newSize];
    long copySize = newSize < this->_pImpl->_size ? newSize : this->_pImpl->_size;
    for(long i = 0; i < copySize; i++)
        newArray[i] = this->_pImpl->_data[i];
    delete[] this->_pImpl->_data;
    this->_pImpl->_data = newArray;
    this->_pImpl->_size = newSize;
}
void CharArray::Reverse()
{
    if(this->_pImpl == nullptr || this->_pImpl->_size == 0)
        return;
    long e = this->_pImpl->_size >> 1;
    long uiLast = this->_pImpl->_size - 1;
    for(long i = 0; i < e; i++){
        Char16 eFirst = this->_pImpl->_data[i];
        this->_pImpl->_data[i] = this->_pImpl->_data[uiLast];
        this->_pImpl->_data[uiLast] = eFirst;
        uiLast--;
    }
}
CharArray CharArray::Slice(long offset, long count, bool deepCopy) const
{
    if(this->_pImpl == nullptr)
        throw OutOfRangeException("Block boundries was out of range of source block.");
    if(offset < 0)
        throw ArgumentOutOfRangeException("Offset cannot be less than zero.", "offset");
    if(offset + count > this->_pImpl->_size)
        throw OutOfRangeException("Block boundries was out of range of source block.");
    return CharArray(&this->_pImpl->_data[offset], count, deepCopy);
}

CharArray &CharArray::operator=(const CharArray &array)
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
Char16 &CharArray::operator[](long index)
{
    if(index < 0)
        throw IndexOutOfRangeException("Index cannot be less than zero.");
    if(this->_pImpl == nullptr)
        throw IndexOutOfRangeException("Array was empty.");
    if(index >= this->_pImpl->_size)
        throw IndexOutOfRangeException("Index must be less than array length.");
    return this->_pImpl->_data[index];
}
Char16 CharArray::operator[](long index) const
{
    if(index < 0)
        throw IndexOutOfRangeException("Index cannot be less than zero.");
    if(this->_pImpl == nullptr)
        throw IndexOutOfRangeException("Array was empty.");
    if(index >= this->_pImpl->_size)
        throw IndexOutOfRangeException("Index must be less than array length.");
    return this->_pImpl->_data[index];
}

CharArray &CharArray::operator ,(CharArray array)
{
    long len = this->_pImpl->_size;
    this->Resize(this->_pImpl->_size + array._pImpl->_size);
    for(int i = 0; i < array._pImpl->_size; i++)
        this->_pImpl->_data[i + len] = array._pImpl->_data[i];
    return *this;
}

bool CharArray::Equals(const Object &obj) const
{
    return this->Equals((const Char &)obj);
}

long CharArray::GetHashCode() const
{
    return (long)this->_pImpl;
}

String16 CharArray::ToString() const
{
    CharArray thisArray = *this;
    return String16(thisArray);
}
