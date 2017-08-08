#ifndef RANDOM_H
#define RANDOM_H

#include "Defs.h"
#include "ByteArray.h"
#include "String16.h"

class Random
{

public:
    Random();
    Random(uint seed);

    int NextInt32();
    int NextInt32(int min, int max);
    float NextFloat();
    void NextBytes(ByteArray &bytes);
    String16 String(int charCount);
    String16 String(int charCount, const String16 &charSet);

private:
    long _x;
    long _y;
    long _z;
    long _w;
    long _v;
};

#endif // RANDOM_H
