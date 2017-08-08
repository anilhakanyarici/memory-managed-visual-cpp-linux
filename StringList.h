#ifndef STRINGLIST_H
#define STRINGLIST_H

class String16;

class StringList final
{
public:
    StringList();
    StringList(const StringList &list);

    ~StringList();

    long charCount() const;
    int count() const;

    StringList &Add(const String16 &item);
    void Clear();
    StringList Clone() const;
    void CopyTo(int offset, StringList &destination, int destOffset, int count) const;
    int FindIndex(const String16 &item) const;
    String16 Join(const String16 &seperator);
    StringList &Insert(int index, const String16 &item);
    bool Remove(const String16 &item);
    StringList &RemoveAt(int index);

    String16 &operator [](int i);
    String16 operator [](int i) const;

    StringList &operator =(const StringList &list);
    StringList &operator ,(const String16 &item);

private:
    struct _impl;
    _impl *_pImpl;
};

#endif // STRINGLIST_H
