#include <sys/time.h>
#include "Random.h"
#include "Exception.h"

Random::Random()
{
    timeval tv;
    gettimeofday(&tv, 0);
    long s = (long)tv.tv_usec;
    s = (long)((s + 0xfffffffe) % 0xffffffff + 1) * 0x11EDC6F41;
    this->_x = s;
    this->_y = this->_x * this->_x;
    this->_z = this->_y * this->_y;
    this->_w = this->_z * this->_z;
    this->_v = this->_w * this->_w;
}
Random::Random(uint seed)
{
    long s = (((long)seed + 0xfffffffe) % 0xffffffff + 1) * 0x11EDC6F41;
    this->_x = s;
    this->_y = this->_x * this->_x;
    this->_z = this->_y * this->_y;
    this->_w = this->_z * this->_z;
    this->_v = this->_w * this->_w;
}

int Random::NextInt32()
{
    long t = (this->_x ^ (this->_x >> 7));
    this->_x = this->_y;
    this->_y = this->_z;
    this->_z = this->_w;
    this->_w = this->_v;
    this->_v = (this->_v ^ (this->_v << 6)) ^ (t ^ (t << 13));
    long r = (2 * this->_y + 1) * this->_v;
    return (int) r;
}

int Random::NextInt32(int min, int max)
{
    if(min < max){
        long r = this->NextInt32();
        long delta = max - min;
        r %= delta;
        r += delta;
        r %= delta;
        r += min;
        return r;
    }
    throw InvalidOperationException("Minimum value must be less than maximum value.");
}
float Random::NextFloat()
{
    uint ui = (uint)this->NextInt32();
    return (float)ui / 0xffffffff;

}

void Random::NextBytes(ByteArray &bytes)
{
    for(int i = 0; i < bytes.length(); i++)
        bytes[i] = (byte)this->NextInt32();
}

String16 Random::String(int charCount)
{
    return this->String(charCount, "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxvz0123456789 !#$%&()*+-./:;<>=?@[]^_{}~");
}

String16 Random::String(int charCount, const String16 &charSet)
{
    CharArray setArr = charSet.charsReference();
    CharArray array = CharArray(charCount);
    for(int i = 0; i < charCount; i++)
        array[i] = setArr[this->NextInt32(0, charSet.length())];
    return String16(array);
}
