#ifndef DEFS_H
#define DEFS_H

#include <cmath>
#include <typeinfo>

#define UseParameter(parameter) parameter = parameter

typedef unsigned short ushort;
typedef unsigned int uint;
typedef unsigned long ulong;
typedef unsigned char byte;
typedef void * ObjectPointer;

struct WrappedByte;
struct WrappedShort;
struct WrappedUnsignedShort;
struct WrappedInt;
struct WrappedUnsignedInt;
struct WrappedLong;
struct WrappedUnsignedLong;

typedef WrappedByte wbyte;
typedef WrappedShort wshort;
typedef WrappedUnsignedShort wushort;
typedef WrappedInt wint;
typedef WrappedUnsignedInt wuint;
typedef WrappedLong wlong;
typedef WrappedUnsignedLong wulong;

#define Delegate(delegateType, returnType, parameters...) typedef returnType (*delegateType) (parameters)

#define PIMPL \
    private: \
    struct _impl;\
    _impl *_pImpl = nullptr;

#ifndef SHORT_MAX
#define SHORT_MAX 0x7FFF
#endif
#ifndef SHORT_MIN
#define SHORT_MIN -0x8000
#endif
#ifndef USHORT_MAX
#define USHORT_MAX 0xFFFF
#endif
#ifndef USHORT_MIN
#define USHORT_MIN 0
#endif
#ifndef INT_MAX
#define INT_MAX 0x7FFFFFFF
#endif
#ifndef INT_MIN
#define INT_MIN -0x80000000
#endif
#ifndef UINT_MAX
#define UINT_MAX 0xFFFFFFFFu
#endif
#ifndef UINT_MIN
#define UINT_MIN 0u
#endif
#ifndef LONG_MAX
#define LONG_MAX 0x7FFFFFFFFFFFFFFFl
#endif
#ifndef LONG_MIN
#define LONG_MIN -0x8000000000000000l
#endif
#ifndef ULONG_MAX
#define ULONG_MAX 0xFFFFFFFFFFFFFFFFul
#endif
#ifndef ULONG_MIN
#define ULONG_MIN 0ul
#endif
#ifndef FLOAT_NAN
#define FLOAT_NAN (float)sqrt(-1)
#endif
#ifndef DOUBLE_NAN
#define DOUBLE_NAN sqrt(-1)
#endif

class Char16;
class String16;

class IStringable
{
public:
    virtual String16 ToString() const = 0;
};
template<typename T> class IEquatable{
public:
    virtual bool Equals(const T &other) const = 0;
    virtual long GetHashCode() const { return ((long)this); }
};
class Comparer
{
public:
    static bool Compare(const void *lhs, const void *rhs, long length);
};
template<typename T> class GenericComparer{
public:
    static bool Compare(const T *lhs, const T *rhs)
    {
        if(typeid(T).__is_pointer_p())
            return lhs == rhs;
        if(typeid(IEquatable<T>).before(typeid(T)))
            return ((IEquatable<T> *)lhs)->Equals(*rhs);
        return Comparer::Compare(lhs, rhs, sizeof(T));
    }
};
typedef Char16 Char;
typedef String16 String;


typedef void (*SignalCallback) (void);
#define SignalCB(func) ((SignalCallback)(&func))
#endif //DEFS_H


