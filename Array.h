#ifndef ARRAY_H
#define ARRAY_H

#include "Defs.h"

template<typename T> class Array
{
    struct _impl
    {
        T *_data = nullptr;
        uint _refc = 1;
        int _len;
    } *_pImpl = nullptr;

public:
    Array();
    Array(int length);
    Array(T *dataSource, int length);

    Array(const Array<T> &array);
    ~Array();
    Array<T> &operator=(const Array<T> &array);

    T *data(int index = 0);
    int length();
    void Resize(int newSize);
    void CopyTo(long offset, Array<T> destination, long destOffset, long count) const;
    Array<T> Clone() const;
    Array<T> Slice(long offset, long count, bool deepCopy = true) const;

    T &operator[](int index);
    T operator[](int index) const;

};

template<typename T>
Array<T>::Array(){}

template<typename T>
Array<T>::Array(int length)
{
    this->_pImpl = new _impl();
    this->_pImpl->_len = length;
    this->_pImpl->_data = new T[length];
}

template<typename T>
Array<T>::Array(T *dataSource, int length)
{
    this->_pImpl = new _impl();
    this->_pImpl->_data = new T[length];
    for(long i = 0; i < length; i++)
        this->_pImpl->_data[i] = dataSource[i];
    this->_pImpl->_len = length;
    this->_pImpl->_refc = 1;
}

template<typename T>
Array<T>::Array(const Array<T> &array)
{
    this->_pImpl = array._pImpl;
    if(this->_pImpl != nullptr)
        this->_pImpl->_refc++;
}

template<typename T>
Array<T>::~Array()
{
    if(this->_pImpl != nullptr){
        if(this->_pImpl->_refc == 1){
            delete[] this->_pImpl->_data;
            delete this->_pImpl;
        } else this->_pImpl->_refc--;
    }
}

template<typename T>
Array<T> &Array<T>::operator=(const Array<T> &array)
{
    if(this->_pImpl != array._pImpl){
        if(this->_pImpl != nullptr){
            if(this->_pImpl->_refc == 1){
                delete[] this->_pImpl->_data;
                delete this->_pImpl;
            } else this->_pImpl->_refc--;
        }
        this->_pImpl = array._pImpl;
        if(array._pImpl != nullptr)
            this->_pImpl->_refc++;
    } return *this;
}

template<typename T>
T *Array<T>::data(int index)
{
    return &this->_pImpl->_data[index];
}

template<typename T>
int Array<T>::length() { return this->_pImpl == nullptr ? 0 : this->_pImpl->_len; }

template<typename T>
void Array<T>::Resize(int newSize)
{
    if(this->_pImpl == nullptr){
        this->_pImpl = new _impl();
        this->_pImpl->_data = new T[newSize];
        this->_pImpl->_refc = 1;
        this->_pImpl->_size = newSize;
        return;
    }
    if(newSize == this->_pImpl->_size)
        return;

    T *newArray = new T[newSize];
    int copySize = newSize < this->_pImpl->_size ? newSize : this->_pImpl->_size;
    for(int i = 0; i < copySize; i++)
        newArray[i] = this->_pImpl->_data[i];
    delete[] this->_pImpl->_data;
    this->_pImpl->_data = newArray;
    this->_pImpl->_size = newSize;
}

template<typename T>
void Array<T>::CopyTo(long offset, Array<T> destination, long destOffset, long count) const
{
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

template<typename T>
Array<T> Array<T>::Clone() const
{
    if(this->_pImpl == nullptr)
        return Array<T>();
    Array<T> clone = Array<T>(this->_pImpl->_size);
    this->CopyTo(0, clone, 0, this->_pImpl->_size);
    return clone;
}

template<typename T>
Array<T> Array<T>::Slice(long offset, long count, bool deepCopy) const { return ByteArray(&this->_pImpl->_data[offset], count, deepCopy); }

template<typename T>
T &Array<T>::operator[](int index) { return this->_pImpl->_data[index]; }

template<typename T>
T Array<T>::operator[](int index) const { return this->_pImpl->_data[index]; }

#endif // ARRAY_H
