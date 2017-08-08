#include "StringList.h"
#include "String16.h"
#include "Exception.h"

struct stringNode
{
    String16 element;
    stringNode *next;
    stringNode *prev;
};

struct StringList::_impl
{
    stringNode *_root = nullptr;
    stringNode *_last = nullptr;
    int _count = 0;
    uint _refc = 1;

    stringNode *findElement(int index) const;
};

StringList::StringList()
{
    this->_pImpl = new StringList::_impl();
    this->_pImpl->_last = nullptr;
    this->_pImpl->_root = nullptr;
}

StringList::StringList(const StringList &list)
{
    this->_pImpl = list._pImpl;
    this->_pImpl->_refc++;
}

StringList::~StringList()
{
    if(this->_pImpl->_refc == 1){
        this->Clear();
        delete this->_pImpl;
    } else this->_pImpl->_refc--;
}

StringList &StringList::Add(const String16 &item)
{
    if(this->_pImpl->_count == 0){
        stringNode *e = new stringNode();
        e->prev = nullptr;
        e->next = nullptr;
        e->element = item;
        this->_pImpl->_root = e;
        this->_pImpl->_last = e;
    } else {
        stringNode *e = new stringNode();
        this->_pImpl->_last->next = e;
        e->prev = this->_pImpl->_last;
        e->element = item;
        e->next = nullptr;
        this->_pImpl->_last = e;
    }
    this->_pImpl->_count++;
    return *this;
}

long StringList::charCount() const
{
    stringNode *node = this->_pImpl->_root;
    long charLen = 0;
    for(int i = 0; i < this->_pImpl->_count; i++){
        charLen += node->element.length();
        node = node->next;
    }
    return charLen;
}

void StringList::Clear()
{
    stringNode *cur = nullptr;
    while(this->_pImpl->_count > 0){
        cur = this->_pImpl->_last;
        this->_pImpl->_count--;
        this->_pImpl->_last = cur->prev;
        delete cur;
    }
    this->_pImpl->_root = nullptr;
    this->_pImpl->_last = nullptr;
}

StringList StringList::Clone() const
{
    if(this->_pImpl->_count == 0)
        return StringList();

    StringList clone = StringList();
    stringNode *e = new stringNode();
    e->prev = nullptr;
    e->next = nullptr;
    e->element = this->_pImpl->_root->element;
    clone._pImpl->_root = e;
    clone._pImpl->_last = e;

    stringNode *thisNode = this->_pImpl->_root;

    for(int i = 1; i < this->_pImpl->_count; i++){
        thisNode = thisNode->next;
        e = new stringNode();
        clone._pImpl->_last->next = e;
        e->prev = clone._pImpl->_last;
        e->element = thisNode->element;
        e->next = nullptr;
        clone._pImpl->_last = e;
    }
    clone._pImpl->_count = this->_pImpl->_count;
    return clone;
}

int StringList::count() const
{
    return this->_pImpl->_count;
}

void StringList::CopyTo(int offset, StringList &destination, int destOffset, int count) const
{
    if(offset < 0)
        throw ArgumentOutOfRangeException("Offset cannot be less than zero.", "offset");
    if(destOffset < 0)
        throw ArgumentOutOfRangeException("Destination offset cannot be less than zero.", "destOffset");
    if(offset + count > this->_pImpl->_count)
        throw OutOfRangeException("Block boundries was out of range of source block.");
    if(destOffset + count > destination._pImpl->_count)
        throw OutOfRangeException("Block boundries was out of range of destination block.");

    int lastIndex = destOffset + count;
    stringNode *e = this->_pImpl->findElement(offset);
    stringNode *d = destination._pImpl->findElement(destOffset);
    for(int i = destOffset; i < lastIndex; i++){
        d->element = e->element;
        e = e->next;
        d = d->next;
    }
}

int StringList::FindIndex(const String16 &item) const
{
    int len = this->_pImpl->_count;
    int offset = 0;
    stringNode *cur = this->_pImpl->_root;
    while(!cur->element.Equals(item) && offset++ < len && (cur = cur->next) != 0);

    if(offset == len)
        return -1;
    return offset;
}

String16 StringList::Join(const String16 &seperator)
{
    if(this->_pImpl->_count < 1)
        return String16();

    stringNode *node = this->_pImpl->_root;
    int loop = this->_pImpl->_count - 1;
    long charLen = seperator.length() * loop;
    for(int i = 0; i < this->_pImpl->_count; i++){
        charLen += node->element.length();
        node = node->next;
    } node = this->_pImpl->_root;
    CharArray array = CharArray(charLen);
    Char16 *arrayData = array.data();
    long arrayIndex = 0;
    for(int i = 0; i < loop; i++){
        long strLen = node->element.length();
        Char16 *data = node->element.charsReference().data();
        for(long j = 0; j < strLen; j++, arrayIndex++)
            arrayData[arrayIndex] = data[j];
        data = seperator.charsReference().data();
        strLen = seperator.length();
        for(long j = 0; j < strLen; j++, arrayIndex++)
            arrayData[arrayIndex] = data[j];
        node = node->next;
    }
    long strLen = node->element.length();
    Char16 *data = node->element.charsReference().data();
    for(long j = 0; j < strLen; j++, arrayIndex++)
        arrayData[arrayIndex] = data[j];
    return String16(array);
}

StringList &StringList::Insert(int index, const String16 &item)
{
    if(index < 0)
        throw ArgumentOutOfRangeException("Index cannot be less than zero.", "index");
    if(index > this->_pImpl->_count)
        throw ArgumentOutOfRangeException("Index cannot be greater than array length.", "index");
    if(index == 0){
        stringNode *newElement = new stringNode();
        if(this->_pImpl->_count > 0)
            this->_pImpl->_root->prev = newElement;
        else
            this->_pImpl->_last = newElement;
        newElement->next = this->_pImpl->_root;
        this->_pImpl->_root = newElement;
        newElement->element = item;
        newElement->prev = nullptr;
    } else if(this->_pImpl->_count == index){
        stringNode *newElement = new stringNode();
        newElement->element = item;
        newElement->prev = this->_pImpl->_last;
        newElement->next = nullptr;
        this->_pImpl->_last->next = newElement;
        this->_pImpl->_last = newElement;
        this->_pImpl->_last->next = nullptr;
    } else {
        stringNode *e = this->_pImpl->findElement(index);
        stringNode *newElement = new stringNode();
        stringNode *prev = e->prev;
        prev->next = newElement;
        newElement->next = e;
        newElement->prev = prev;
        e->prev = newElement;
        newElement->element = item;
    }
    this->_pImpl->_count++;
    return *this;
}

bool StringList::Remove(const String16 &item)
{
    int len = this->count();
    int offset = 0;
    stringNode *cur = this->_pImpl->_root;
    while(!cur->element.Equals(item)&& offset++ < len && (cur = cur->next) != 0);

    if(offset == 0){
        stringNode *e = this->_pImpl->_root;
        this->_pImpl->_root = this->_pImpl->_root->next;
        if(this->_pImpl->_count > 1)
            this->_pImpl->_root->prev = nullptr;
        delete e;
        this->_pImpl->_count--;
    } else if(this->_pImpl->_count - 1 == offset){
        stringNode *e = this->_pImpl->_last;
        this->_pImpl->_last = this->_pImpl->_last->prev;
        this->_pImpl->_last->next = nullptr;
        delete e;
        this->_pImpl->_count--;
    } else if (offset == len){
        return false;
    } else {
        stringNode *e = cur;
        e->prev->next = e->next;
        e->next->prev = e->prev;
        delete e;
        this->_pImpl->_count--;
    }
    return true;
}

StringList &StringList::RemoveAt(int index)
{
    if(index < 0)
        throw ArgumentOutOfRangeException("Index cannot be less than zero.", "index");
    if(index >= this->_pImpl->_count)
        throw ArgumentOutOfRangeException("Index must be less than array length.", "index");

    if(index == 0){
        stringNode *e = this->_pImpl->_root;
        this->_pImpl->_root = this->_pImpl->_root->next;
        if(this->_pImpl->_count > 1)
            this->_pImpl->_root->prev = nullptr;
        delete e;
    } else if(this->_pImpl->_count - 1 == index){
        stringNode *e = this->_pImpl->_last;
        this->_pImpl->_last = this->_pImpl->_last->prev;
        this->_pImpl->_last->next = nullptr;
        delete e;
    } else {
        stringNode *e = this->_pImpl->findElement(index);
        e->prev->next = e->next;
        e->next->prev = e->prev;
        delete e;
    }
    this->_pImpl->_count--;
    return *this;
}

String16 &StringList::operator[](int i)
{
    if(i < 0)
        throw IndexOutOfRangeException("Index cannot be less than zero.");
    if(i >= this->_pImpl->_count)
        throw IndexOutOfRangeException("Index must be less than array length.");
    stringNode *e = this->_pImpl->findElement(i);
    return e->element;
}

String16 StringList::operator[](int i) const
{
    if(i < 0)
        throw IndexOutOfRangeException("Index cannot be less than zero.");
    if(i >= this->_pImpl->_count)
        throw IndexOutOfRangeException("Index must be less than array length.");
    stringNode *e = this->_pImpl->findElement(i);
    return e->element;
}

StringList &StringList::operator =(const StringList &list)
{
    if(this->_pImpl != list._pImpl){
        if(this->_pImpl->_refc == 1){
            this->Clear();
            delete this->_pImpl;
        } else this->_pImpl->_refc--;
        this->_pImpl = list._pImpl;
        this->_pImpl->_refc++;
    } return *this;
}

StringList &StringList::operator ,(const String16 &item)
{
    this->Add(item);
    return *this;
}

stringNode *StringList::_impl::findElement(int index) const
{
    if(index > this->_count >> 1){
        stringNode *e = this->_last;
        for(int i = this->_count - 1; i > index; i--){
            e = e->prev;
        }
        return e;
    } else {
        stringNode *e = this->_root;
        for(int i = 0; i < index; i++){
            e = e->next;
        }
        return e;
    }
}
