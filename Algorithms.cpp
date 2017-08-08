#include "Defs.h"

bool Comparer::Compare(const void *lhs, const void *rhs, long length)
{
    if(lhs == rhs)
        return true;
    long longLen = length >> 4;
    long *lhsData = (long *)lhs;
    long *rhsData = (long *)rhs;
    bool equals = true;
    for(long i = 0; i < longLen && (equals = lhsData[i] == rhsData[i]); i++);
    if(!equals)
        return false;
    long rLen = length & 15;
    length = length << 4;
    byte * rLhs = (byte *)lhs;
    byte * rRhs = (byte *)rhs;
    for(int i = 0; i < rLen && equals; i++){
        long index = length + i;
        equals = rLhs[index] == rRhs[index];
    }
    return equals;
}
