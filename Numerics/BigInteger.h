#ifndef BIGINTEGER_H
#define BIGINTEGER_H

#include "../Defs.h"
#include "../String16.h"
#include "../ISerializable.h"

class BigInteger final : public Object, public ISerializable, public IEquatable<BigInteger>
{
public:
    BigInteger();
    BigInteger(int value);
    BigInteger(uint value);
    BigInteger(long value);
    BigInteger(ulong value);

    BigInteger(const BigInteger &big);

    ~BigInteger(){ delete[] this->_digits; }

    bool isZero() const { return this->_sign == 0; }
    bool isOne() const { return this->_digitLength == 1 && this->_digits[0] == 1 && this->_sign == 1; }
    bool isMinusOne() const { return this->_digitLength == 1 && this->_digits[0] == 1 && this->_sign == -1; }
    bool isNegative() const { return this->_sign == -1; }
    bool isPositive() const { return this->_sign == 1; }
    bool isPowerOfTwo() const;
    bool isEven() const { return (this->_digits[0] & 1) == 0; }
    bool isOdd() const { return (this->_digits[0] & 1); }
    int sign() const { return this->_sign; }
    int digitLength() const { return this->_digitLength; }
    uint *data() const{ return this->_digits; }

    inline BigInteger &Add(int value) { return this->Add((long)value); }
    inline BigInteger &Sub(int value) { return this->Sub((long)value); }
    inline BigInteger &Mul(int value) { return this->Mul((long)value); }
    inline BigInteger &Div(int divisor) { return this->Div((long)divisor); }
    inline BigInteger &Rem(int modulus) { return this->Rem((long)modulus); }
    BigInteger &DivRem(int divisor, int &remainder) { long rem; this->DivRem((long)divisor, rem); remainder = (int)rem; return *this; }
    inline BigInteger &Add(uint value) { return this->Add((ulong)value); }
    inline BigInteger &Sub(uint value) { return this->Sub((ulong)value); }
    inline BigInteger &Mul(uint value) { return this->Mul((ulong)value); }
    inline BigInteger &Div(uint divisor) { return this->Div((ulong)divisor); }
    inline BigInteger &Rem(uint modulus) { return this->Rem((ulong)modulus); }
    BigInteger &DivRem(uint divisor, uint &remainder) { ulong rem; this->DivRem((ulong)divisor, rem); remainder = (uint)rem; return *this; }
    BigInteger &Add(long value);
    BigInteger &Sub(long value);
    BigInteger &Mul(long value);
    BigInteger &Div(long divisor);
    BigInteger &Rem(long modulus);
    BigInteger &DivRem(long divisor, long &remainder);
    BigInteger &Add(ulong value);
    BigInteger &Sub(ulong value);
    BigInteger &Mul(ulong value);
    BigInteger &Div(ulong divisor);
    BigInteger &Rem(ulong modulus);
    BigInteger &DivRem(ulong divisor, ulong &remainder);
    BigInteger &Add(const BigInteger &value);
    BigInteger &Sub(const BigInteger &value);
    BigInteger &Mul(const BigInteger &value);
    BigInteger &Div(const BigInteger &divisor);
    BigInteger &Rem(const BigInteger &modulus);
    BigInteger &DivRem(const BigInteger &divisor, BigInteger &remainder);

    static BigInteger Add(const BigInteger &left, const BigInteger &right);
    static BigInteger Sub(const BigInteger &left, const BigInteger &right);
    static BigInteger Mul(const BigInteger &left, const BigInteger &right);
    static BigInteger Div(const BigInteger &dividend, const BigInteger &divisor);
    static BigInteger Rem(const BigInteger &dividend, const BigInteger &divisor);
    static BigInteger DivRem(const BigInteger &dividend, const BigInteger &divisor, BigInteger &remainder);
    static BigInteger Or(const BigInteger &left, const BigInteger &right);
    static BigInteger And(const BigInteger &left, const BigInteger &right);
    static BigInteger Xor(const BigInteger &left, const BigInteger &right);

    BigInteger &Shift(int shift);
    BigInteger &And(const BigInteger &value);
    BigInteger &Or(const BigInteger &value);
    BigInteger &Xor(const BigInteger &value);
    BigInteger &Not();
    BigInteger &Decrease();
    BigInteger &Increase();
    BigInteger &Negate();
    BigInteger &Square();
    BigInteger &Abs();
    BigInteger &Pow(uint exponent);

    void Assign(uint value);
    BigInteger Clone() const;
    static BigInteger Parse(const char *chars);
    static BigInteger Parse(const String16 &value);

    static inline int Compare(int left, const BigInteger &right) { return -BigInteger::Compare(right, (long)left); }
    static inline int Compare(uint left, const BigInteger &right) { return -BigInteger::Compare(right, (ulong)left); }
    static inline int Compare(long left, const BigInteger &right) { return -BigInteger::Compare(right, left); }
    static inline int Compare(ulong left, const BigInteger &right) { return -BigInteger::Compare(right, left); }
    static inline int Compare(const BigInteger &left, int right) { return BigInteger::Compare(left, (long)right); }
    static inline int Compare(const BigInteger &left, uint right) { return BigInteger::Compare(left, (ulong)right); }
    static int Compare(const BigInteger &left, long right);
    static int Compare(const BigInteger &left, ulong right);
    static int Compare(const BigInteger &left, const BigInteger &right);

    BigInteger &operator =(int value);
    BigInteger &operator =(uint value);
    BigInteger &operator =(long value);
    BigInteger &operator =(ulong value);

    BigInteger &operator =(const BigInteger &big);

    friend BigInteger operator +(const BigInteger &left, int right) { BigInteger r = right; return BigInteger::Add(left, r); }
    friend BigInteger operator -(const BigInteger &left, int right) { BigInteger r = right; return BigInteger::Sub(left, r); }
    friend BigInteger operator *(const BigInteger &left, int right) { BigInteger r = right; return BigInteger::Mul(left, r); }
    friend BigInteger operator /(const BigInteger &left, int right) { BigInteger r = right; return BigInteger::Div(left, r); }
    friend BigInteger operator %(const BigInteger &left, int right) { BigInteger r = right; return BigInteger::Rem(left, r); }
    friend BigInteger operator +(const BigInteger &left, uint right) { BigInteger r = right; return BigInteger::Add(left, r); }
    friend BigInteger operator -(const BigInteger &left, uint right) { BigInteger r = right; return BigInteger::Sub(left, r); }
    friend BigInteger operator *(const BigInteger &left, uint right) { BigInteger r = right; return BigInteger::Mul(left, r); }
    friend BigInteger operator /(const BigInteger &left, uint right) { BigInteger r = right; return BigInteger::Div(left, r); }
    friend BigInteger operator %(const BigInteger &left, uint right) { BigInteger r = right; return BigInteger::Rem(left, r); }
    friend BigInteger operator +(const BigInteger &left, long right) { BigInteger r = right; return BigInteger::Add(left, r); }
    friend BigInteger operator -(const BigInteger &left, long right) { BigInteger r = right; return BigInteger::Sub(left, r); }
    friend BigInteger operator *(const BigInteger &left, long right) { BigInteger r = right; return BigInteger::Mul(left, r); }
    friend BigInteger operator /(const BigInteger &left, long right) { BigInteger r = right; return BigInteger::Div(left, r); }
    friend BigInteger operator %(const BigInteger &left, long right) { BigInteger r = right; return BigInteger::Rem(left, r); }
    friend BigInteger operator +(const BigInteger &left, ulong right) { BigInteger r = right; return BigInteger::Add(left, r); }
    friend BigInteger operator -(const BigInteger &left, ulong right) { BigInteger r = right; return BigInteger::Sub(left, r); }
    friend BigInteger operator *(const BigInteger &left, ulong right) { BigInteger r = right; return BigInteger::Mul(left, r); }
    friend BigInteger operator /(const BigInteger &left, ulong right) { BigInteger r = right; return BigInteger::Div(left, r); }
    friend BigInteger operator %(const BigInteger &left, ulong right) { BigInteger r = right; return BigInteger::Rem(left, r); }
    inline friend BigInteger operator +(const BigInteger &left, const BigInteger &right) { return BigInteger::Add(left, right); }
    inline friend BigInteger operator -(const BigInteger &left, const BigInteger &right) { return BigInteger::Sub(left, right); }
    inline friend BigInteger operator *(const BigInteger &left, const BigInteger &right) { return BigInteger::Mul(left, right); }
    inline friend BigInteger operator /(const BigInteger &left, const BigInteger &right) { return BigInteger::Div(left, right); }
    inline friend BigInteger operator %(const BigInteger &left, const BigInteger &right) { return BigInteger::Rem(left, right); }

    inline BigInteger &operator +=(int value){ return this->Add(value); }
    inline BigInteger &operator +=(uint value){ return this->Add(value); }
    inline BigInteger &operator +=(long value){ return this->Add(value); }
    inline BigInteger &operator +=(ulong value){ return this->Add(value); }
    inline BigInteger &operator +=(const BigInteger &value){ return this->Add(value); }
    inline BigInteger &operator -=(int value){ return this->Sub(value); }
    inline BigInteger &operator -=(uint value){ return this->Sub(value); }
    inline BigInteger &operator -=(long value){ return this->Sub(value); }
    inline BigInteger &operator -=(ulong value){ return this->Sub(value); }
    inline BigInteger &operator -=(const BigInteger &value){ return this->Sub(value); }
    inline BigInteger &operator *=(int value){ return this->Mul(value); }
    inline BigInteger &operator *=(uint value){ return this->Mul(value); }
    inline BigInteger &operator *=(long value){ return this->Mul(value); }
    inline BigInteger &operator *=(ulong value){ return this->Mul(value); }
    inline BigInteger &operator *=(const BigInteger &value){ return this->Mul(value); }
    inline BigInteger &operator /=(int value){ return this->Div(value); }
    inline BigInteger &operator /=(uint value){ return this->Div(value); }
    inline BigInteger &operator /=(long value){ return this->Div(value); }
    inline BigInteger &operator /=(ulong value){ return this->Div(value); }
    inline BigInteger &operator /=(const BigInteger &value){ return this->Div(value); }
    inline BigInteger &operator %=(int value){ return this->Rem(value); }
    inline BigInteger &operator %=(uint value){ return this->Rem(value); }
    inline BigInteger &operator %=(long value){ return this->Rem(value); }
    inline BigInteger &operator %=(ulong value){ return this->Rem(value); }
    inline BigInteger &operator %=(const BigInteger &value){ return this->Rem(value); }

    inline friend BigInteger operator ^(const BigInteger &left, const BigInteger &right) { return BigInteger::Xor(left, right); }
    inline friend BigInteger operator |(const BigInteger &left, const BigInteger &right) { return BigInteger::Or(left, right); }
    inline friend BigInteger operator &(const BigInteger &left, const BigInteger &right) { return BigInteger::And(left, right); }
    inline friend BigInteger operator >>(BigInteger value, int shift) { return value.Shift(-shift); }
    inline friend BigInteger operator <<(BigInteger value, int shift) { return value.Shift(shift); }
    inline friend BigInteger operator ~(BigInteger value) { return value.Not(); }

    inline BigInteger &operator ^=(const BigInteger &value) { return this->Xor(value); }
    inline BigInteger &operator &=(const BigInteger &value) { return this->And(value); }
    inline BigInteger &operator |=(const BigInteger &value) { return this->Or(value); }
    inline BigInteger &operator >>=(int shift) { return this->Shift(-shift); }
    inline BigInteger &operator <<=(int shift) { return this->Shift(shift); }

    inline friend BigInteger operator -(BigInteger value) { return value.Negate(); }
    inline friend BigInteger operator +(BigInteger value) { return value.Abs(); }
    inline BigInteger operator --() { return this->Decrease(); }
    inline BigInteger operator ++() { return this->Increase(); }
    inline BigInteger operator --(int) { return operator --(); }
    inline BigInteger operator ++(int) { return operator ++(); }

    inline friend bool operator <(int left, const BigInteger &right) { return BigInteger::Compare(left, right) == -1; }
    inline friend bool operator >(int left, const BigInteger &right) { return BigInteger::Compare(left, right) == 1; }
    inline friend bool operator ==(int left, const BigInteger &right) { return BigInteger::Compare(left, right) != 0; }
    inline friend bool operator !=(int left, const BigInteger &right) { return BigInteger::Compare(left, right) == 0; }
    inline friend bool operator <=(int left, const BigInteger &right) { return BigInteger::Compare(left, right) < 1; }
    inline friend bool operator >=(int left, const BigInteger &right) { return BigInteger::Compare(left, right) > -1; }
    inline friend bool operator <(uint left, const BigInteger &right) { return BigInteger::Compare(left, right) == -1; }
    inline friend bool operator >(uint left, const BigInteger &right) { return BigInteger::Compare(left, right) == 1; }
    inline friend bool operator ==(uint left, const BigInteger &right) { return BigInteger::Compare(left, right) != 0; }
    inline friend bool operator !=(uint left, const BigInteger &right) { return BigInteger::Compare(left, right) == 0; }
    inline friend bool operator <=(uint left, const BigInteger &right) { return BigInteger::Compare(left, right) < 1; }
    inline friend bool operator >=(uint left, const BigInteger &right) { return BigInteger::Compare(left, right) > -1; }
    inline friend bool operator <(long left, const BigInteger &right) { return BigInteger::Compare(left, right) == -1; }
    inline friend bool operator >(long left, const BigInteger &right) { return BigInteger::Compare(left, right) == 1; }
    inline friend bool operator ==(long left, const BigInteger &right) { return BigInteger::Compare(left, right) != 0; }
    inline friend bool operator !=(long left, const BigInteger &right) { return BigInteger::Compare(left, right) == 0; }
    inline friend bool operator <=(long left, const BigInteger &right) { return BigInteger::Compare(left, right) < 1; }
    inline friend bool operator >=(long left, const BigInteger &right) { return BigInteger::Compare(left, right) > -1; }
    inline friend bool operator <(ulong left, const BigInteger &right) { return BigInteger::Compare(left, right) == -1; }
    inline friend bool operator >(ulong left, const BigInteger &right) { return BigInteger::Compare(left, right) == 1; }
    inline friend bool operator ==(ulong left, const BigInteger &right) { return BigInteger::Compare(left, right) != 0; }
    inline friend bool operator !=(ulong left, const BigInteger &right) { return BigInteger::Compare(left, right) == 0; }
    inline friend bool operator <=(ulong left, const BigInteger &right) { return BigInteger::Compare(left, right) < 1; }
    inline friend bool operator >=(ulong left, const BigInteger &right) { return BigInteger::Compare(left, right) > -1; }
    inline bool operator <(int value) const { return BigInteger::Compare(*this, value) == -1; }
    inline bool operator >(int value) const { return BigInteger::Compare(*this, value) == 1; }
    inline bool operator !=(int value) const { return BigInteger::Compare(*this, value) != 0; }
    inline bool operator ==(int value) const { return BigInteger::Compare(*this, value) == 0; }
    inline bool operator >=(int value) const { return BigInteger::Compare(*this, value) < 1; }
    inline bool operator <=(int value) const { return BigInteger::Compare(*this, value) > -1; }
    inline bool operator <(uint value) const { return BigInteger::Compare(*this, value) == -1; }
    inline bool operator >(uint value) const { return BigInteger::Compare(*this, value) == 1; }
    inline bool operator !=(uint value) const { return BigInteger::Compare(*this, value) != 0; }
    inline bool operator ==(uint value) const { return BigInteger::Compare(*this, value) == 0; }
    inline bool operator >=(uint value) const { return BigInteger::Compare(*this, value) < 1; }
    inline bool operator <=(uint value) const { return BigInteger::Compare(*this, value) > -1; }
    inline bool operator <(long value) const { return BigInteger::Compare(*this, value) == -1; }
    inline bool operator >(long value) const { return BigInteger::Compare(*this, value) == 1; }
    inline bool operator !=(long value) const { return BigInteger::Compare(*this, value) != 0; }
    inline bool operator ==(long value) const { return BigInteger::Compare(*this, value) == 0; }
    inline bool operator >=(long value) const { return BigInteger::Compare(*this, value) < 1; }
    inline bool operator <=(long value) const { return BigInteger::Compare(*this, value) > -1; }
    inline bool operator <(ulong value) const { return BigInteger::Compare(*this, value) == -1; }
    inline bool operator >(ulong value) const { return BigInteger::Compare(*this, value) == 1; }
    inline bool operator !=(ulong value) const { return BigInteger::Compare(*this, value) != 0; }
    inline bool operator ==(ulong value) const { return BigInteger::Compare(*this, value) == 0; }
    inline bool operator >=(ulong value) const { return BigInteger::Compare(*this, value) < 1; }
    inline bool operator <=(ulong value) const { return BigInteger::Compare(*this, value) > -1; }
    inline bool operator <(const BigInteger &value) const { return BigInteger::Compare(*this, value) == -1; }
    inline bool operator >(const BigInteger &value) const { return BigInteger::Compare(*this, value) == 1; }
    inline bool operator !=(const BigInteger &value) const { return BigInteger::Compare(*this, value) != 0; }
    inline bool operator ==(const BigInteger &value) const { return BigInteger::Compare(*this, value) == 0; }
    inline bool operator <=(const BigInteger &value) const { return BigInteger::Compare(*this, value) < 1; }
    inline bool operator >=(const BigInteger &value) const { return BigInteger::Compare(*this, value) > -1; }

    operator int() const;
    operator uint() const;
    operator long() const;
    operator ulong() const;
    inline operator String16() const { return this->ToString(); }

    static BigInteger Pow(BigInteger value, uint exponent);
    static BigInteger Factorial(uint value);
    static BigInteger PollardRhoFactorization(BigInteger &value);
    static BigInteger GreatestCommonDivisor(const BigInteger &left, const BigInteger &right);
    static BigInteger LeastCommonMultiple(const BigInteger &left, const BigInteger &right);
    static BigInteger ModPow(BigInteger value, const BigInteger &exponent, const BigInteger &modulus);
    static BigInteger SquareRoot(const BigInteger &value);
    static BigInteger ModInverse(const BigInteger &value, const BigInteger &modulus);

private:
    int _digitLength;
    uint *_digits;
    int _sign;

    BigInteger(uint* digits, int length, int sign, bool internal);

public:
    // ISerializable interface
    void GetSerializationData(BinaryWriter *writer) const override;
    bool SetSerializationData(BinaryReader *reader) override;

    // IEquatable<BigInteger> interface
    bool Equals(const BigInteger &other) const override;

    // Object interface
    long GetHashCode() const override;
    bool Equals(const Object &obj) const override;
    String16 ToString() const override;
};

#endif // BIGINTEGER_H
