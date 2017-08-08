#include "BigInteger.h"
#include "../Exception.h"
#include "../Text/Encoding.h"
#include "../IO/BinaryReader.h"
#include "../IO/BinaryWriter.h"

struct InternalBasicOperators
{
    static uint *Add(uint *left, int leftLength, uint *right, int rightLength, int &resultLength)
    {
        uint *operands[2] { left, right };
        int lengths[2] { leftLength, rightLength };
        int lgtr = leftLength < rightLength;

        int max = lengths[lgtr];
        int min = lengths[!lgtr];
        uint *maxOperand = operands[lgtr];
        uint *minOperand = operands[!lgtr];

        uint *result = new uint[max + 1];
        ulong carry = 0;
        for (int i = 0; i < min; i++){
            ulong sum = (ulong)minOperand[i] + (ulong)maxOperand[i] + carry;
            carry = sum >> 32;
            result[i] = (uint)(sum);
        }

        if (carry > 0){
            for (int i = min; i < max; i++){
                ulong sum = (ulong)maxOperand[i] + carry;
                carry = sum >> 32;
                result[i] = (uint)(sum);
            }
            result[max] = (uint)(carry);
            resultLength = max + (carry > 0);
        }
        else{
            for (int i = min; i < max; i++)
                result[i] = maxOperand[i];
            resultLength = max;
        }
        return result;
    }
    static uint *AddSingle(uint *left, int leftLength, uint right, int &resultLength)
    {
        ulong sum = (ulong)left[0] + right;
        uint carry = sum >> 32;
        uint* result = new uint[leftLength + 1];
        result[0] = (uint)sum;
        for(int i = 1; i < leftLength; i++){
            sum = (ulong)carry + left[i];
            result[i] = (uint)sum;
            carry = sum >> 32;
        }
        result[leftLength] = carry;
        resultLength = leftLength + (result[leftLength] != 0);
        return result;
    }
    static uint *DivRem(uint *numerator, int numeratorLength, uint *denominator, int denominatorLength, int &quotientLength, int &remainderLength)
    {
        if(denominatorLength == 1){
            remainderLength = 1;
            uint divisor = denominator[0];
            uint *q = new uint[numeratorLength];
            q[numeratorLength - 1] = 0;

            ulong dividend = numerator[numeratorLength - 1];
            int qPos = numeratorLength - 1;
            int rPos = qPos;
            if (dividend >= divisor)
            {
                ulong quot = dividend / divisor;
                q[qPos--] = (uint)quot;
                numerator[rPos] = (uint)(dividend % divisor);
            }
            else
                qPos--;
            rPos--;
            while (rPos > -1)
            {
                int rPosPlusOne = rPos + 1;
                dividend = ((ulong)numerator[rPosPlusOne] << 32) | numerator[rPos];
                ulong quot = dividend / divisor;
                q[qPos--] = (uint)quot;
                numerator[rPosPlusOne] = 0;
                numerator[rPos--] = (uint)(dividend % divisor);
            }
            if (q[numeratorLength - 1] == 0)
                quotientLength = numeratorLength - 1;
            else
                quotientLength = numeratorLength;

            return q;
        } else {
            int numLastU = numeratorLength - 1;
            int opLDiff = numLastU - (denominatorLength - 1);
            quotientLength = opLDiff;
            for (int iu = numLastU; ; iu--)
            {
                if (iu < opLDiff)
                {
                    quotientLength = 1 + quotientLength;
                    break;
                }
                if (denominator[iu - opLDiff] != numerator[iu])
                {
                    if (denominator[iu - opLDiff] < numerator[iu])
                        quotientLength = 1 + quotientLength;
                    break;
                }
            }

            uint *quotient = new uint[quotientLength];

            uint denFirst = denominator[denominatorLength - 1];
            uint denSecond = denominator[denominatorLength - 2];
            int leftShiftBit = InternalBasicOperators::countOfZeroBitStart(denFirst);
            int rightShiftBit = 32 - leftShiftBit;
            if (leftShiftBit > 0)
            {
                denFirst = (denFirst << leftShiftBit) | (denSecond >> rightShiftBit);
                denSecond <<= leftShiftBit;
                if (denominatorLength > 2)
                    denSecond |= denominator[denominatorLength - 3] >> rightShiftBit;
            }

            for (int uInd = quotientLength; --uInd >= 0;)
            {
                uint hiNumDig = (uInd + denominatorLength <= numLastU) ? numerator[uInd + denominatorLength] : 0;

                ulong currNum = ((ulong)hiNumDig << 32) | numerator[uInd + denominatorLength - 1];
                uint nextNum = numerator[uInd + denominatorLength - 2];
                if (leftShiftBit > 0)
                {
                    currNum = (currNum << leftShiftBit) | (nextNum >> rightShiftBit);
                    nextNum <<= leftShiftBit;
                    if (uInd + denominatorLength >= 3)
                        nextNum |= numerator[uInd + denominatorLength - 3] >> rightShiftBit;
                }
                ulong rQuot = currNum / denFirst;
                ulong rRem = (uint)(currNum % denFirst);
                if (rQuot > 0xFFFFFFFF)
                {
                    rRem += denFirst * (rQuot - 0xFFFFFFFF);
                    rQuot = 0xFFFFFFFF;
                }
                while (rRem <= 0xFFFFFFFF && rQuot * denSecond > (((ulong)((uint)rRem) << 32) | nextNum))
                {
                    rQuot--;
                    rRem += denFirst;
                }
                if (rQuot > 0)
                {
                    ulong borrow = 0;
                    for (int u = 0; u < denominatorLength; u++)
                    {
                        borrow += denominator[u] * rQuot;
                        uint uSub = (uint)borrow;
                        borrow >>= 32;
                        if (numerator[uInd + u] < uSub)
                            borrow++;
                        numerator[uInd + u] -= uSub;
                    }
                    if (hiNumDig < borrow)
                    {
                        uint uCarry = 0;
                        for (int iu2 = 0; iu2 < denominatorLength; iu2++)
                        {
                            uCarry = InternalBasicOperators::addCarry(&numerator[uInd + iu2], denominator[iu2], uCarry);
                        }
                        rQuot--;
                    }
                    numLastU = uInd + denominatorLength - 1;
                }
                quotient[uInd] = (uint)rQuot;
            }

            remainderLength = denominatorLength;

            while (numerator[remainderLength - 1] == 0 && remainderLength > 1)
                remainderLength = remainderLength - 1;
            while (quotient[quotientLength - 1] == 0 && quotientLength > 1)
                quotientLength = quotientLength - 1;
            return quotient;
        }
    }
    static void Rem(uint *numerator, int numeratorLength, uint *denominator, int denominatorLength, int &remainderLength)
    {
        if(denominatorLength == 1){
            remainderLength = 1;
            uint divisor = denominator[0];

            ulong dividend = numerator[numeratorLength - 1];
            int rPos = numeratorLength - 1;
            if (dividend >= divisor)
                numerator[rPos] = (uint)(dividend % divisor);
            rPos--;
            while (rPos > -1)
            {
                int rPosPlusOne = rPos + 1;
                dividend = ((ulong)numerator[rPosPlusOne] << 32) | numerator[rPos];
                numerator[rPosPlusOne] = 0;
                numerator[rPos--] = (uint)(dividend % divisor);
            }
        } else {
            int numLastU = numeratorLength - 1;
            int opLDiff = numLastU - (denominatorLength - 1);
            int quotientLength = opLDiff;
            for (int iu = numLastU; ; iu--)
            {
                if (iu < opLDiff)
                {
                    quotientLength = 1 + quotientLength;
                    break;
                }
                if (denominator[iu - opLDiff] != numerator[iu])
                {
                    if (denominator[iu - opLDiff] < numerator[iu])
                        quotientLength = 1 + quotientLength;
                    break;
                }
            }

            uint denFirst = denominator[denominatorLength - 1];
            uint denSecond = denominator[denominatorLength - 2];
            int leftShiftBit = InternalBasicOperators::countOfZeroBitStart(denFirst);
            int rightShiftBit = 32 - leftShiftBit;
            if (leftShiftBit > 0)
            {
                denFirst = (denFirst << leftShiftBit) | (denSecond >> rightShiftBit);
                denSecond <<= leftShiftBit;
                if (denominatorLength > 2)
                    denSecond |= denominator[denominatorLength - 3] >> rightShiftBit;
            }

            for (int uInd = quotientLength; --uInd >= 0;)
            {
                uint hiNumDig = (uInd + denominatorLength <= numLastU) ? numerator[uInd + denominatorLength] : 0;

                ulong currNum = ((ulong)hiNumDig << 32) | numerator[uInd + denominatorLength - 1];
                uint nextNum = numerator[uInd + denominatorLength - 2];
                if (leftShiftBit > 0)
                {
                    currNum = (currNum << leftShiftBit) | (nextNum >> rightShiftBit);
                    nextNum <<= leftShiftBit;
                    if (uInd + denominatorLength >= 3)
                        nextNum |= numerator[uInd + denominatorLength - 3] >> rightShiftBit;
                }
                ulong rQuot = currNum / denFirst;
                ulong rRem = (uint)(currNum % denFirst);
                if (rQuot > 0xFFFFFFFF)
                {
                    rRem += denFirst * (rQuot - 0xFFFFFFFF);
                    rQuot = 0xFFFFFFFF;
                }
                while (rRem <= 0xFFFFFFFF && rQuot * denSecond > (((ulong)((uint)rRem) << 32) | nextNum))
                {
                    rQuot--;
                    rRem += denFirst;
                }
                if (rQuot > 0)
                {
                    ulong borrow = 0;
                    for (int u = 0; u < denominatorLength; u++)
                    {
                        borrow += denominator[u] * rQuot;
                        uint uSub = (uint)borrow;
                        borrow >>= 32;
                        if (numerator[uInd + u] < uSub)
                            borrow++;
                        numerator[uInd + u] -= uSub;
                    }
                    if (hiNumDig < borrow)
                    {
                        uint uCarry = 0;
                        for (int iu2 = 0; iu2 < denominatorLength; iu2++)
                        {
                            uCarry = InternalBasicOperators::addCarry(&numerator[uInd + iu2], denominator[iu2], uCarry);
                        }
                        rQuot--;
                    }
                    numLastU = uInd + denominatorLength - 1;
                }
            }
            remainderLength = denominatorLength;
            while (numerator[remainderLength - 1] == 0 && remainderLength > 1)
                remainderLength = remainderLength - 1;
        }
    }
    static uint *Mul(uint *left, int leftLength, uint *right, int rightLength, int &resultLength)
    {
        if (leftLength > rightLength)
        {
            int tmp = leftLength;
            leftLength = rightLength;
            rightLength = tmp;
            uint *tmpb = left;
            left = right;
            right = tmpb;
        }

        resultLength = leftLength + rightLength;
        uint *result = new uint[resultLength];

        for(int i = 0; i < resultLength; i++)
            result[i] = 0;

        for (int i = 0; i < leftLength; i++)
        {
            if (left[i] == 0) continue;

            ulong carry = 0;
            for (int j = 0, k = i; j < rightLength; j++, k++)
            {
                ulong val = ((ulong)left[i] * right[j]) + result[k] + carry;
                result[k] = (uint)val;
                carry = (val >> 32);
            }
            result[i + rightLength] = (uint)carry;
        }
        while (result[resultLength - 1] == 0 && resultLength > 1)
            resultLength = resultLength - 1;
        return result;
    }
    static uint *MulSingle(uint *left, int leftLength, uint right, int &resultLength)
    {
        resultLength = leftLength + 1;
        uint *result = new uint[resultLength];

        result[0] = 0;
        ulong carry;
        for (int i = 0; i < leftLength; i++)
        {
            carry = 0;
            ulong val = ((ulong)left[i] * (ulong)right) + (ulong)result[i];
            result[i] = (uint)val;
            carry = (val >> 32);
            result[i + 1] = (uint)carry;
        }

        while (result[resultLength - 1] == 0 && resultLength > 1)
            resultLength = resultLength - 1;
        return result;
    }
    static uint *Sub(uint *left, int leftLength, uint *right, int rightLength, int &resultLength)
    {
        uint *result = new uint[leftLength];
        for(int i = leftLength - rightLength; i < leftLength; i++)
            result[i] = 0;

        int carry = 0;
        int i = 0;
        long diff;
        for ( ; i < rightLength; i++)
        {
            diff = (long)left[i] - (long)right[i] + carry;
            result[i] = (uint)(diff);
            carry = (diff >> 63);
        }
        for ( ; carry && i < leftLength; i++)
        {
            diff = (long)left[i] + carry;
            result[i] = (uint)(diff);
            carry = (diff >> 63);
        }
        for ( ; i < leftLength; i++)
            result[i] = left[i];

        resultLength = leftLength;
        while (result[resultLength - 1] == 0 && resultLength > 1)
            resultLength = resultLength - 1;
        return result;
    }

    static uint *ShiftRight(uint *digits, int digitLength, int shift, int &resultLength)
    {
        if (shift == 0) {
            uint *clone = new uint[digitLength];
            for(int i = 0; i < digitLength; i++)
                clone[i] = digits[i];
            return clone;
        }

        int fullShift = shift >> 5;
        int remShift = shift & 31;

        int predictedLen = (digitLength) - fullShift;
        uint *result = new uint[predictedLen];
        for(int i = 0; i < predictedLen; i++)
            result[i] = digits[fullShift + i];
        if(remShift > 0){
            result[0] = result[0] >> remShift;
            for(int i = 1; i < predictedLen; i++){
                result[i - 1] |= result[i] << (32 - remShift);
                result[i] = result[i] >> remShift;
            }
        }
        if(result[predictedLen - 1] == 0 && predictedLen > 1)
            predictedLen--;
        resultLength = predictedLen;
        return result;
    }
    static uint *ShiftLeft(uint *digits, int digitLength, int shift, int &resultLength)
    {
        if (shift == 0) {
            uint *clone = new uint[digitLength];
            for(int i = 0; i < digitLength; i++)
                clone[i] = digits[i];
            return clone;
        }

        int fullShift = shift >> 5;
        int remShift = shift & 31;
        int needRemShift = remShift > 0;
        resultLength = digitLength + fullShift + needRemShift;
        uint *result = new uint[resultLength];
        result[resultLength - 1] = 0;

        for(int i = 0; i < digitLength; i++)
            result[i + fullShift] = digits[i];
        if(remShift > 0){
            for(int i = resultLength - 1; i > fullShift; i--){
                uint dig = result[i] << remShift;
                dig |= result[i - 1] >> (32 - remShift);
                result[i] = dig;
            }
            result[fullShift] = result[fullShift] << remShift;
        }
        for(int i = 0; i < fullShift; i++)
            result[i] = 0;
        if(result[resultLength - 1] == 0 && resultLength > 1)
            resultLength--;

        return result;
    }
    static uint *And(uint *left, int leftLength, uint *right, int rightLength, int &resultLength)
    {
        int min = leftLength > rightLength ? rightLength : leftLength;

        uint *result = new uint[min];
        for (int i = 0; i < min; i++)
            result[i] = left[i] & right[i];

        resultLength = min;
        while (result[resultLength - 1] == 0 && resultLength > 1)
            resultLength = resultLength - 1;
        return result;
    }
    static uint *Or(uint *left, int leftLength, uint *right, int rightLength, int &resultLength)
    {
        uint *operands[2] { left, right };
        int lengths[2] { leftLength, rightLength };
        int lgtr = leftLength < rightLength;

        int max = lengths[lgtr];
        int min = lengths[!lgtr];
        uint *maxOperand = operands[lgtr];

        uint *result = new uint[max];
        int i = 0;
        for ( ; i < min; i++)
            result[i] = left[i] | right[i];
        for ( ; i < max; i++)
            result[i] = maxOperand[i];
        resultLength = max;
        return result;
    }
    static uint *Xor(uint *left, int leftLength, uint *right, int rightLength, int &resultLength)
    {
        uint *operands[2] { left, right };
        int lengths[2] { leftLength, rightLength };
        int lgtr = leftLength < rightLength;

        int max = lengths[lgtr];
        int min = lengths[!lgtr];
        uint *maxOperand = operands[lgtr];

        uint *result = new uint[max];
        int i = 0;
        for ( ; i < min; i++)
            result[i] = left[i] ^ right[i];
        for ( ; i < max; i++)
            result[i] = maxOperand[i] ^ 0;
        resultLength = max;
        while (result[resultLength - 1] == 0 && resultLength > 1)
            resultLength = resultLength - 1;
        return result;
    }
    static uint *Not(uint *digits, int digitLength, int &resultLength)
    {
        uint *result = new uint[digitLength];
        for(int i = 0; i < digitLength; i++)
            result[i] = ~digits[i];
        resultLength = digitLength;
        while (result[resultLength - 1] == 0 && resultLength > 1)
            resultLength = resultLength - 1;
        return result;
    }

    static int Compare(uint *left, int leftLength, uint *right, int rightLength)
    {
        int c = (int)(leftLength > rightLength);
        c = -(int)(leftLength < rightLength) * ((c + 1) & 1) + c;
        for(int i = leftLength - 1; !c && (i >= 0); i--)
            c = (int)(left[i] > right[i]) - (int)(left[i] < right[i]);
        return c;
    }
    static String16 ToString(uint *digits, int digitLength, int sign)
    {
        if (sign == 0 || digitLength == 0) {
            return "0";
        }
        else if (digitLength == 1 && sign == 1){
            char *str = new char[20];
            sprintf(str, "%d", digits[0]);
            String16 u16str = str;
            delete[] str;
            return u16str;
        }

        const uint kuBase = 1000000000; // 10^9
        int cuMax = digitLength * 10 / 9 + 2;
        uint *rguDst = new uint[cuMax];
        int cuDst = 0;
        for(int i = 0; i < cuMax; i++)
            rguDst[i] = 0;

        for (int iuSrc = digitLength; --iuSrc >= 0;){
            uint uCarry = digits[iuSrc];
            for (int iuDst = 0; iuDst < cuDst; iuDst++){
                ulong uuRes = ((ulong)rguDst[iuDst] << 32) | uCarry;
                rguDst[iuDst] = (uint)(uuRes % kuBase);
                uCarry = (uint)(uuRes / kuBase);
            }
            if (uCarry != 0){
                rguDst[cuDst++] = uCarry % kuBase;
                uCarry /= kuBase;
                if (uCarry != 0)
                    rguDst[cuDst++] = uCarry;
            }
        }
        int cchMax = cuDst * 9;
        int rgchBufSize = cchMax + 2 + (sign == -1);
        int ichDst = cchMax;

        CharArray chars16 = CharArray(rgchBufSize);
        Char16 *rgch = chars16.data();

        for (int iuDst = 0; iuDst < cuDst - 1; iuDst++){
            uint uDig = rguDst[iuDst];
            for (int cch = 9; --cch >= 0; ){
                int ascii = (48 + uDig % 10);
                rgch[--ichDst] = (char)ascii;
                uDig /= 10;
            }
        }
        for (uint uDig = rguDst[cuDst - 1]; uDig != 0; ){
            int ascii = (48 + uDig % 10);
            rgch[--ichDst] = (char)ascii;
            uDig /= 10;
        }
        delete[] rguDst;
        if (sign == -1){
            rgch[--ichDst] = '-';
        }
        return String16(chars16, ichDst, cchMax - ichDst);
    }
    static uint *UnsignedParse(char *value, int charLen, int &digitLength)
    {
        int offset = charLen & 7;
        int base108Len = (charLen >> 3);
        uint lastDigit = 0;

        base108Len++;
        for(int i = 0; i < offset; i++){
            lastDigit *= 10;
            lastDigit += value[i] - 48;
        }
        uint *base108Digits = new uint[base108Len];
        int uiLast = base108Len - 1;
        base108Digits[uiLast] = lastDigit;
        for(int i = uiLast - 1; i >= 0; i--){
            uint curDigit = 0;
            offset += 8;
            for(int j = offset - 8; j < offset; j++){
                curDigit *= 10;
                curDigit += value[j] - 48;
            }
            base108Digits[i] = curDigit;
        }

        const uint cBase = 100000000u;
        uint *digits = new uint[1];
        digits[0] = 0;
        int resultLength = 1;
        uint *tmp = digits;
        digits = InternalBasicOperators::AddSingle(digits, resultLength, base108Digits[base108Len - 1], resultLength);
        delete[] tmp;
        for(int i = base108Len - 2; i >= 0; i--){
            tmp = digits;
            digits = InternalBasicOperators::MulSingle(digits, resultLength, cBase, resultLength);
            delete[] tmp;
            tmp = digits;
            uint base108dig = base108Digits[i];
            digits = InternalBasicOperators::AddSingle(digits, resultLength, base108dig, resultLength);
            delete[] tmp;
        }
        delete[] base108Digits;
        digitLength = resultLength;
        return digits;
    }
    static long UnsignedBitsLength(uint *digits, int digitLength)
    {
        uint uiLast = digits[digitLength - 1];
        return 32 * (long)digitLength - InternalBasicOperators::countOfZeroBitStart(uiLast);
    }

    static uint addCarry(uint *u1, uint u2, uint uCarry)
    {
        ulong uu = (ulong)*u1 + u2 + uCarry;
        *u1 = (uint)uu;
        return (uint)(uu >> 32);
    }
    static int countOfZeroBitStart(uint u)
    {
        int cbit = (u == 0);
        int f = (u & 0xFFFF0000) == 0;
        cbit += f << 4;
        f = ((u << cbit) & 0xFF000000) == 0;
        cbit += f << 3;
        f = ((u << cbit) & 0xF0000000) == 0;
        cbit += f << 2;
        f = ((u << cbit) & 0xC0000000) == 0;
        cbit += f << 1;
        f = ((u << cbit) & 0x80000000) == 0;
        cbit += f;
        return cbit;
    }
};

BigInteger::BigInteger()
{
    this->_sign = 0;
    this->_digits = new uint[1];
    this->_digits[0] = 0;
    this->_digitLength = 1;
}
BigInteger::BigInteger(int value)
{
    this->_sign = (value >> 31);
    this->_sign = this->_sign + (int)(value > 0);
    value *= this->_sign;
    this->_digitLength = 1;
    this->_digits = new uint[1];
    this->_digits[0] = (uint)value;
}
BigInteger::BigInteger(uint value)
{
    this->_sign = value > 0;
    this->_digitLength = 1;
    this->_digits = new uint[1];
    this->_digits[0] = (uint)value;
}
BigInteger::BigInteger(long value)
{
    this->_sign = (value >> 63);
    this->_sign = this->_sign + (int)(value > 0);
    value *= this->_sign;
    int vgtuim = (int)(value > 0xffffffff);
    this->_digitLength = 1 + vgtuim;
    this->_digits = new uint[this->_digitLength];
    this->_digits[vgtuim] = (uint)(value >> 32);
    this->_digits[0] = (uint)value;
}
BigInteger::BigInteger(ulong value)
{
    this->_sign = value > 0;
    int vgtuim = (int)(value > 0xffffffff);
    this->_digitLength = 1 + vgtuim;
    this->_digits = new uint[this->_digitLength];
    this->_digits[vgtuim] = (uint)(value >> 32);
    this->_digits[0] = (uint)value;
}

BigInteger::BigInteger(const BigInteger &big)
{
    this->_digitLength = big._digitLength;
    this->_sign = big._sign;
    this->_digits = new uint[big._digitLength];
    for(int i = 0; i < this->_digitLength; i++)
        this->_digits[i] = big._digits[i];
}

bool BigInteger::isPowerOfTwo() const
{
    int uiLast = this->_digitLength - 1;
    uint uLast = this->_digits[uiLast];

    if ((uLast & (uLast - 1)) != 0)
        return false;

    for(int i = 0; i < uiLast; i++)
        if(this->_digits[i] != 0)
            return false;

    return true;
}

BigInteger &BigInteger::Add(long value)
{
    BigInteger v = value;
    return this->Add(v);
}
BigInteger &BigInteger::Add(ulong value)
{
    BigInteger v = value;
    return this->Add(v);
}
BigInteger &BigInteger::Add(const BigInteger &value)
{
    if(this->_sign == value._sign){
        if(this->_sign == 0){
            delete[] this->_digits;
            this->_digits = new uint[1] { 0 };
            return *this;
        }
        uint *digits = InternalBasicOperators::Add(this->_digits, this->_digitLength, value._digits, value._digitLength, this->_digitLength);
        delete[] this->_digits;
        this->_digits = digits;
        return *this;
    } else {
        int c = InternalBasicOperators::Compare(this->_digits, this->_digitLength, value._digits, value._digitLength);
        uint *digits;
        if(c == 1){
            digits = InternalBasicOperators::Sub(this->_digits, this->_digitLength, value._digits, value._digitLength, this->_digitLength);
            delete[] this->_digits;
            this->_digits = digits;
        } else if(c == -1){
            digits = InternalBasicOperators::Sub(value._digits, value._digitLength, this->_digits, this->_digitLength, this->_digitLength);
            delete[] this->_digits;
            this->_digits = digits;
            this->_sign = value._sign;
        } else {
            delete[] this->_digits;
            this->_digits = new uint[1] { 0 };
            this->_digitLength = 1;
            this->_sign = 0;
        }
        return *this;
    }
}
BigInteger &BigInteger::Sub(long value)
{
    BigInteger v = value;
    return this->Sub(v);
}
BigInteger &BigInteger::Sub(ulong value)
{
    BigInteger v = value;
    return this->Sub(v);
}
BigInteger &BigInteger::Sub(const BigInteger &value)
{
    if(this->_sign == -value._sign){
        if(this->_sign == 0){
            delete[] this->_digits;
            this->_digits = new uint[1] { 0 };
            return *this;
        }
        uint *digits = InternalBasicOperators::Add(this->_digits, this->_digitLength, value._digits, value._digitLength, this->_digitLength);
        delete[] this->_digits;
        this->_digits = digits;
        return *this;
    } else {
        int c = InternalBasicOperators::Compare(this->_digits, this->_digitLength, value._digits, value._digitLength);
        uint *digits;
        if(c == 1){
            digits = InternalBasicOperators::Sub(this->_digits, this->_digitLength, value._digits, value._digitLength, this->_digitLength);
            delete[] this->_digits;
            this->_digits = digits;
        } else if(c == -1){
            digits = InternalBasicOperators::Sub(value._digits, value._digitLength, this->_digits, this->_digitLength, this->_digitLength);
            delete[] this->_digits;
            this->_digits = digits;
            this->_sign = -value._sign;
        } else {
            delete[] this->_digits;
            this->_digits = new uint[1] { 0 };
            this->_digitLength = 1;
            this->_sign = 0;
        }
        return *this;
    }
}
BigInteger &BigInteger::Mul(long value)
{
    BigInteger v = value;
    return this->Mul(v);
}
BigInteger &BigInteger::Mul(ulong value)
{
    BigInteger v = value;
    return this->Mul(v);
}
BigInteger &BigInteger::Mul(const BigInteger &value)
{
    this->_sign = this->_sign * value._sign;
    if(this->_sign == 0){
        delete[] this->_digits;
        this->_digits = new uint[1] { 0 };
        this->_digitLength = 1;
        return *this;
    }
    uint *digits = InternalBasicOperators::Mul(this->_digits, this->_digitLength, value._digits, value._digitLength, this->_digitLength);
    delete[] this->_digits;
    this->_digits = digits;
    return *this;
}
BigInteger &BigInteger::Div(long divisor)
{
    long rem;
    return this->DivRem(divisor, rem);
}
BigInteger &BigInteger::Div(ulong divisor)
{
    ulong rem;
    return this->DivRem(divisor, rem);
}
BigInteger &BigInteger::Div(const BigInteger &divisor)
{
    if(((BigInteger&)divisor).isZero())
        throw DivideByZeroException();
    BigInteger rem;
    return this->DivRem(divisor, rem);
}
BigInteger &BigInteger::Rem(long modulus)
{
    if(modulus == 0)
        throw DivideByZeroException();
    if(this->_sign == 0)
        return *this;
    int modulus_sign = (modulus >> 63);
    modulus_sign = modulus_sign + (int)(modulus > 0);
    modulus *= modulus_sign;
    int vgtuim = (int)(modulus > 0xffffffff);
    int modulus_digitLength = 1 + vgtuim;
    uint *modulus_digits = new uint[modulus_digitLength];
    modulus_digits[vgtuim] = (uint)(modulus >> 32);
    modulus_digits[0] = (uint)modulus;
    this->_sign = this->_sign * modulus_sign;
    if(this->_digitLength >= modulus_digitLength)
        InternalBasicOperators::Rem(this->_digits, this->_digitLength, modulus_digits, modulus_digitLength, this->_digitLength);
    return *this;
}
BigInteger &BigInteger::Rem(ulong modulus)
{
    if(modulus == 0)
        throw DivideByZeroException();
    if(this->_sign == 0)
        return *this;
    int vgtuim = (int)(modulus > 0xffffffff);
    int modulus_digitLength = 1 + vgtuim;
    uint *modulus_digits = new uint[modulus_digitLength];
    modulus_digits[vgtuim] = (uint)(modulus >> 32);
    modulus_digits[0] = (uint)modulus;
    if(this->_digitLength >= modulus_digitLength)
        InternalBasicOperators::Rem(this->_digits, this->_digitLength, modulus_digits, modulus_digitLength, this->_digitLength);
    return *this;
}
BigInteger &BigInteger::Rem(const BigInteger &modulus)
{
    if(((BigInteger&)modulus).isZero())
        throw DivideByZeroException();
    if(this->_sign == 0)
        return *this;
    this->_sign = this->_sign * modulus._sign;
    if(this->_digitLength >= modulus._digitLength)
        InternalBasicOperators::Rem(this->_digits, this->_digitLength, modulus._digits, modulus._digitLength, this->_digitLength);
    return *this;
}
BigInteger &BigInteger::DivRem(long divisor, long &remainder)
{
    BigInteger r, div = divisor;
    this->DivRem(div, r);
    remainder = (long)r;
    return *this;
}
BigInteger &BigInteger::DivRem(ulong divisor, ulong &remainder)
{
    BigInteger r, div = divisor;
    this->DivRem(div, r);
    remainder = (ulong)r;
    remainder += divisor;
    remainder %= divisor;
    return *this;
}
BigInteger &BigInteger::DivRem(const BigInteger &divisor, BigInteger &remainder)
{
    if(divisor._sign == 0)
        throw DivideByZeroException();
    if(this->_sign == 0){
        if(this->_digits != remainder._digits){
            delete[] remainder._digits;
            remainder._digits = new uint[1] { 0 };
            remainder._digitLength = 1;
            remainder._sign = 0;
        }
        return *this;
    } else {
        this->_sign = this->_sign * divisor._sign;
        remainder._sign = this->_sign;
        int c = InternalBasicOperators::Compare(this->_digits, this->_digitLength, divisor._digits, divisor._digitLength);
        if(c == -1){
            if(this->_digits != remainder._digits){
                delete[] remainder._digits;
                remainder._digits = this->_digits;
                remainder._digitLength = this->_digitLength;
                this->_digits = new uint[1] { 0 };
                this->_digitLength = 1;
                this->_sign = 0;
            }
            return *this;
        } else if (c == 0){
            if(this->_digits == remainder._digits){
                delete[] this->_digits;
                this->_digits = new uint[1] { 0 };
                this->_digitLength = 1;
            } else {
                delete[] this->_digits;
                this->_digits = new uint[1] { 1 };
                this->_digitLength = 1;
                delete[] remainder._digits;
                remainder._digits = new uint[1] { 0 };
                remainder._digitLength = 1;
                remainder._sign = 0;
            }
            return *this;
        }else {
            int quotientLength, remainderLength;
            uint *quot = InternalBasicOperators::DivRem(this->_digits, this->_digitLength, divisor._digits, divisor._digitLength, quotientLength, remainderLength);
            if(this->_digits == remainder._digits){
                delete[] quot;
                this->_digitLength = remainderLength;
                return *this;
            } else {
                delete[] remainder._digits;
                remainder._digits = this->_digits;
                remainder._digitLength = remainderLength;
                this->_digits = quot;
                this->_digitLength = quotientLength;
                remainder._sign = (!(remainder._digitLength == 1 && !remainder._digits[0])) * remainder._sign;
            }
            return *this;
        }
    }
}

BigInteger BigInteger::Add(const BigInteger &left, const BigInteger &right)
{
    if(left._sign == right._sign){
        if(left._sign == 0){
            uint *digits = new uint[1] { 0 };
            return BigInteger(digits, 1, 0, true);
        }
        int resultLength;
        uint *digits = InternalBasicOperators::Add(left._digits, left._digitLength, right._digits, right._digitLength, resultLength);
        return BigInteger(digits, resultLength, left._sign, resultLength);
    } else {
        int c = InternalBasicOperators::Compare(left._digits, left._digitLength, right._digits, right._digitLength);
        if(c == 1){
            int resultLength;
            uint *digits = InternalBasicOperators::Sub(left._digits, left._digitLength, right._digits, right._digitLength, resultLength);
            return BigInteger(digits, resultLength, left._sign, true);
        } else if(c == -1){
            int resultLength;
            uint *digits = InternalBasicOperators::Sub(right._digits, right._digitLength, left._digits, left._digitLength, resultLength);
            return BigInteger(digits, resultLength, right._sign, true);
        } else {
            uint *digits = new uint[1] { 0 };
            return BigInteger(digits, 1, 0, true);
        }
    }
}
BigInteger BigInteger::Sub(const BigInteger &left, const BigInteger &right)
{
    if(left._sign == -right._sign){
        if(left._sign == 0){
            return BigInteger(0u);
        }
        int resultLength;
        uint *digits = InternalBasicOperators::Add(left._digits, left._digitLength, right._digits, right._digitLength, resultLength);
        return BigInteger(digits, resultLength, left._sign, true);
    } else {
        int c = InternalBasicOperators::Compare(left._digits, left._digitLength, right._digits, right._digitLength);
        if(c == 1){
            int resultLength;
            uint *digits = InternalBasicOperators::Sub(left._digits, left._digitLength, right._digits, right._digitLength, resultLength);
            return BigInteger(digits, resultLength, left._sign, true);
        } else if(c == -1){
            int resultLength;
            uint *digits = InternalBasicOperators::Sub(right._digits, right._digitLength, left._digits, left._digitLength, resultLength);
            return BigInteger(digits, resultLength, -right._sign, true);
        } else {
            return BigInteger(0u);
        }
    }
}
BigInteger BigInteger::Mul(const BigInteger &left, const BigInteger &right)
{
    int result_sign = left._sign * right._sign;
    if(result_sign == 0)
        return BigInteger(0u);

    int resultLength;
    uint *digits = InternalBasicOperators::Mul(left._digits, left._digitLength, right._digits, right._digitLength, resultLength);
    return BigInteger(digits, resultLength, result_sign, true);
}
BigInteger BigInteger::Div(const BigInteger &dividend, const BigInteger &divisor)
{
    if(divisor._sign == 0)
        throw DivideByZeroException();
    if(dividend._sign == 0){
        return BigInteger(0u);
    } else {
        int c = InternalBasicOperators::Compare(dividend._digits, dividend._digitLength, divisor._digits, divisor._digitLength);
        int result_sign = dividend._sign * divisor._sign;
        if(c == -1)
            return BigInteger(0u);
        else if (c == 0)
            return BigInteger(result_sign);
        else {
            int quotientLength, remainderLength;
            uint *remainder = new uint[dividend._digitLength];
            for(int i = 0; i < dividend._digitLength; i++)
                remainder[i] = dividend._digits[i];
            uint *quot = InternalBasicOperators::DivRem(remainder, dividend._digitLength, divisor._digits, divisor._digitLength, quotientLength, remainderLength);
            delete[] remainder;
            return BigInteger(quot, quotientLength, result_sign, true);
        }
    }
}
BigInteger BigInteger::Rem(const BigInteger &dividend, const BigInteger &divisor)
{
    if(((BigInteger&)divisor).isZero())
        throw DivideByZeroException();
    if(dividend._sign == 0)
        return BigInteger(0u);
    if(dividend._digitLength >= divisor._digitLength){
        uint *remainder = new uint[dividend._digitLength];
        for(int i = 0; i < dividend._digitLength; i++)
            remainder[i] = dividend._digits[i];
        int remainderLength;
        InternalBasicOperators::Rem(remainder, dividend._digitLength, divisor._digits, divisor._digitLength, remainderLength);
        return BigInteger(remainder, remainderLength, dividend._sign * divisor._sign, true);
    } else {
        BigInteger rem = ((BigInteger&)dividend).Clone();
        rem._sign *= divisor._sign;
        return rem;
    }
}
BigInteger BigInteger::DivRem(const BigInteger &dividend, const BigInteger &divisor, BigInteger &remainder)
{
    if(dividend._digits == remainder._digits)
        return ((BigInteger&)dividend).DivRem(divisor, remainder);
    if(divisor._sign == 0)
        throw DivideByZeroException();
    if(dividend._sign == 0){
        return BigInteger(0u);
    } else {
        int result_sign = dividend._sign * divisor._sign;
        remainder._sign = result_sign;
        delete[] remainder._digits;
        remainder._digits = new uint[dividend._digitLength];
        for(int i = 0; i < dividend._digitLength; i++)
            remainder._digits[i] = dividend._digits[i];
        if(dividend._digitLength >= divisor._digitLength) {
            int quotientLength;
            uint *quot = InternalBasicOperators::DivRem(remainder._digits, dividend._digitLength, divisor._digits, divisor._digitLength, quotientLength, remainder._digitLength);
            return BigInteger(quot, quotientLength, result_sign, true);
        } else {
            remainder._digitLength = dividend._digitLength;
            return BigInteger(0u);
        }
    }
}
BigInteger BigInteger::Or(const BigInteger &left, const BigInteger &right)
{
    int resultLength;
    uint *digits = InternalBasicOperators::Or(left._digits, left._digitLength, right._digits, right._digitLength, resultLength);
    return BigInteger(digits, resultLength, (int)(resultLength != 1 || digits[0] != 0), true);
}
BigInteger BigInteger::And(const BigInteger &left, const BigInteger &right)
{
    int resultLength;
    uint *digits = InternalBasicOperators::And(left._digits, left._digitLength, right._digits, right._digitLength, resultLength);
    return BigInteger(digits, resultLength, (int)(resultLength != 1 || digits[0] != 0), true);
}
BigInteger BigInteger::Xor(const BigInteger &left, const BigInteger &right)
{
    int resultLength;
    uint *digits = InternalBasicOperators::Xor(left._digits, left._digitLength, right._digits, right._digitLength, resultLength);
    return BigInteger(digits, resultLength, (int)(resultLength != 1 || digits[0] != 0), true);
}

BigInteger &BigInteger::Shift(int shift)
{
    uint *digits;
    if(shift > 0)
        digits = InternalBasicOperators::ShiftLeft(this->_digits, this->_digitLength, shift, this->_digitLength);
    else
        digits = InternalBasicOperators::ShiftRight(this->_digits, this->_digitLength, -shift, this->_digitLength);
    delete[] this->_digits;
    this->_digits = digits;
    return *this;
}
BigInteger &BigInteger::And(const BigInteger &value)
{
    uint *digits = InternalBasicOperators::And(this->_digits, this->_digitLength, value._digits, value._digitLength, this->_digitLength);
    delete[] this->_digits;
    this->_digits = digits;
    return *this;
}
BigInteger &BigInteger::Or(const BigInteger &value)
{
    uint *digits = InternalBasicOperators::Or(this->_digits, this->_digitLength, value._digits, value._digitLength, this->_digitLength);
    delete[] this->_digits;
    this->_digits = digits;
    return *this;
}
BigInteger &BigInteger::Xor(const BigInteger &value)
{
    uint *digits = InternalBasicOperators::Xor(this->_digits, this->_digitLength, value._digits, value._digitLength, this->_digitLength);
    delete[] this->_digits;
    this->_digits = digits;
    return *this;
}
BigInteger &BigInteger::Not()
{
    uint *digits = InternalBasicOperators::Not(this->_digits, this->_digitLength, this->_digitLength);
    delete[] this->_digits;
    this->_digits = digits;
    return *this;
}
BigInteger &BigInteger::Decrease()
{
    return this->Sub(1l);
}
BigInteger &BigInteger::Increase()
{
    return this->Add(1l);
}
BigInteger &BigInteger::Negate()
{
    this->_sign *= -1;
    return *this;
}
BigInteger &BigInteger::Square()
{
    return this->Mul(*this);
}
BigInteger &BigInteger::Abs()
{
    this->_sign *= this->_sign;
    return *this;
}
BigInteger &BigInteger::Pow(uint exponent)
{
    if (exponent == 1)
        return *this;
    if (exponent == 0){
        delete[] this->_digits;
        this->_digits = new uint[1] { 1 };
        this->_digitLength = 1;
        this->_sign = 1;
    }
    BigInteger value = this->Clone();
    if (!(exponent & 1)){
        delete[] this->_digits;
        this->_digits = new uint[1] { 1 };
        this->_digitLength = 1;
        this->_sign = 1;
    }

    exponent >>= 1;
    while (exponent != 0)
    {
        value.Square();
        if ((exponent & 1) == 1)
            this->Mul(value);
        exponent >>= 1;
    }
    return *this;
}

void BigInteger::Assign(uint value)
{
    this->_digitLength = 1;
    this->_digits[0] = value;
    this->_sign = value > 0;
}

String16 BigInteger::ToString() const
{
    if(this->_digitLength == 1){
        char buffer[50];
        int len = sprintf(&buffer[1], "%u", this->_digits[0]);
        buffer[len + 1] = 0;
        buffer[0] = '-';
        return String16((const char *)&buffer[(this->_sign + 2) >> 1]);
    }else{
        return InternalBasicOperators::ToString(this->_digits, this->_digitLength, this->_sign);
    }
}
BigInteger BigInteger::Clone() const
{
    uint *digits = new uint[this->_digitLength];
    for(int i = 0; i < this->_digitLength; i++)
        digits[i] = this->_digits[i];
    return BigInteger(digits, this->_digitLength, this->_sign, true);
}
BigInteger BigInteger::Parse(const char *chars)
{
    char *value = (char *)chars;
    int sign = 1;
    if(chars[0] == '-'){
        sign = -1;
        value = (char *)&chars[1];
    }
    int count = 0;
    char c = value[0];
    while(c != 0){
        if(c < 48 || 57 < c)
            throw FormatException("Used invalid numeric literal for parsing string.");
        count++;
        c = value[count];
    }

    int zeroTrim = 0;
    c = value[0];
    while(c == 48){
        zeroTrim++;
        c = value[zeroTrim];
    }
    char *start = &value[zeroTrim];
    count -= zeroTrim;
    int digitLength;
    uint *digits = InternalBasicOperators::UnsignedParse(start, count, digitLength);
    if(digitLength == 1 && digits[0] == 0)
        sign = 0;
    return BigInteger(digits, digitLength, sign, true);
}
BigInteger BigInteger::Parse(const String16 &value)
{
    ByteArray chars = Encoding::UTF8.GetBytes(value.charsReference());
    return BigInteger::Parse((const char*)chars.data());
}

int BigInteger::Compare(const BigInteger &left, long right)
{
    int right_sign = (right >> 63);
    right_sign = right_sign + (int)(right > 0);
    right *= right_sign;
    int vgtuim = (int)(right > 0xffffffff);
    int right_digitLength = 1 + vgtuim;
    uint *right_digits = new uint[right_digitLength];
    right_digits[vgtuim] = (uint)(right >> 32);
    right_digits[0] = (uint)right;

    if(left._sign < right_sign)
        return -1;
    if(left._sign > right_sign)
        return 1;
    return InternalBasicOperators::Compare(left._digits, left._digitLength, right_digits, right_digitLength);

}
int BigInteger::Compare(const BigInteger &left, ulong right)
{
    int right_sign = right > 0;
    int vgtuim = (int)(right > 0xffffffff);
    int right_digitLength = 1 + vgtuim;
    uint *right_digits = new uint[right_digitLength];
    right_digits[vgtuim] = (uint)(right >> 32);
    right_digits[0] = (uint)right;

    if(left._sign < right_sign)
        return -1;
    if(left._sign > right_sign)
        return 1;
    return InternalBasicOperators::Compare(left._digits, left._digitLength, right_digits, right_digitLength);
}
int BigInteger::Compare(const BigInteger &left, const BigInteger &right)
{
    if(left._sign > right._sign)
        return 1;
    if(left._sign < right._sign)
        return -1;
    return InternalBasicOperators::Compare(left._digits, left._digitLength, right._digits, right._digitLength);
}

BigInteger &BigInteger::operator=(int value)
{
    this->_sign = (value >> 31);
    this->_sign = this->_sign + (int)(value > 0);
    value *= this->_sign;
    this->_digitLength = 1;
    this->_digits = new uint[1];
    this->_digits[0] = (uint)value;
    return *this;
}
BigInteger &BigInteger::operator=(uint value)
{
    this->_sign = value > 0;
    this->_digitLength = 1;
    this->_digits = new uint[1];
    this->_digits[0] = (uint)value;
    return *this;
}
BigInteger &BigInteger::operator=(long value)
{
    this->_sign = (value >> 63);
    this->_sign = this->_sign + (int)(value > 0);
    value *= this->_sign;
    int vgtuim = (int)(value > 0xffffffff);
    this->_digitLength = 1 + vgtuim;
    this->_digits = new uint[this->_digitLength];
    this->_digits[vgtuim] = (uint)(value >> 32);
    this->_digits[0] = (uint)value;
    return *this;
}
BigInteger &BigInteger::operator=(ulong value)
{
    this->_sign = value > 0;
    int vgtuim = (int)(value > 0xffffffff);
    this->_digitLength = 1 + vgtuim;
    this->_digits = new uint[this->_digitLength];
    this->_digits[vgtuim] = (uint)(value >> 32);
    this->_digits[0] = (uint)value;
    return *this;
}
BigInteger &BigInteger::operator=(const BigInteger &big)
{
    if(this->_digits != big._digits){
        delete[] this->_digits;
        this->_digits = new uint[big._digitLength];
        this->_digitLength = big._digitLength;
        this->_sign = big._sign;
        for(int i = 0; i < this->_digitLength; i++)
            this->_digits[i] = big._digits[i];
    }
    return *this;
}

BigInteger BigInteger::Pow(BigInteger value, uint exponent)
{
    if (exponent == 1)
        return value;
    if (exponent == 0)
        return BigInteger(1u);

    BigInteger res = BigInteger(1u);
    if (exponent & 1)
        res = value;

    exponent >>= 1;
    while (exponent != 0)
    {
        value.Square();
        if ((exponent & 1) == 1)
            res.Mul(value);
        exponent >>= 1;
    }
    return res;
}
BigInteger BigInteger::Factorial(uint value)
{
    if (value == 0 || value == 1)
        return BigInteger(1u);

    uint cbit = (value == 0);
    uint f = (value & 0xFFFF0000) == 0;
    cbit += f << 4;
    f = ((value << cbit) & 0xFF000000) == 0;
    cbit += f << 3;
    f = ((value << cbit) & 0xF0000000) == 0;
    cbit += f << 2;
    f = ((value << cbit) & 0xC0000000) == 0;
    cbit += f << 1;
    f = ((value << cbit) & 0x80000000) == 0;
    cbit += f;

    uint t = (32 - cbit);
    uint *a = new uint[t];
    uint shift = 0;

    for (uint i = 0; i < t; i++){
        if ((value & 1) == 1){
            value = a[i] = value >> 1;
            shift += value;
        }
        else{
            a[i] = (value = value >> 1) - 1;
            shift += value;
        }
    }
    BigInteger inner = BigInteger(1u), T = BigInteger(1u);
    uint abovePi, belowPi;
    for (uint i = 1; i < t; i++){
        abovePi = a[i - 1];
        belowPi = a[i] + 1;
        for (uint j = belowPi; j <= abovePi; j++)
            inner.Mul((j << 1) | 1);
        inner.Pow(i);
        T.Mul(inner);
        inner.Assign(1u);
    }
    delete[] a;
    T.Shift((int)shift);
    return T;
}
BigInteger BigInteger::PollardRhoFactorization(BigInteger &value)
{
    if (value.isZero())
        return BigInteger(0u);
    if (value.isOne())
        return BigInteger(1u);

    BigInteger a = 5u;
    a.DivRem(value, a);
    BigInteger b = 26u;
    b.DivRem(value, b);
    while (true)
    {
        BigInteger c = a < b ? BigInteger::Sub(b, a) : BigInteger::Sub(a, b);
        BigInteger d = BigInteger::GreatestCommonDivisor(c, value);
        if (d.isOne())
        {
            a.Square().Increase().Rem(value);
            b.Square().Increase().Rem(value);
            b.Square().Increase().Rem(value);
            continue;
        }
        else{
            value.Div(d);
            return d;
        }
    }
}
BigInteger BigInteger::GreatestCommonDivisor(const BigInteger &left, const BigInteger &right)
{
    if (((BigInteger&)right).isZero())
        return ((BigInteger&)left).Clone();
    else{
        BigInteger rem = left % right; //BigInteger::Rem(left, right);
        return BigInteger::GreatestCommonDivisor(right, rem);
    }
}
BigInteger BigInteger::LeastCommonMultiple(const BigInteger &left, const BigInteger &right)
{
    BigInteger gcd = BigInteger::GreatestCommonDivisor(left, right);
    BigInteger leftFac = left / gcd;
    BigInteger rightFac = right / gcd;
    gcd.Mul(leftFac).Mul(rightFac);
    return gcd;
}
BigInteger BigInteger::ModPow(BigInteger value, const BigInteger &exponent, const BigInteger &modulus)
{
    if(((BigInteger&)modulus).isNegative())
        throw DomainException("modulus cannot be negative");
    if(value.isZero())
        return BigInteger(0u);
    if(value.isNegative() && ((BigInteger&)exponent).isNegative())
        throw DomainException("value and exponent cannot be negative currently");
    if(((BigInteger&)exponent).isNegative())
        value = BigInteger::ModInverse(value, modulus);

    BigInteger result = BigInteger(1u);
    long bitLength = InternalBasicOperators::UnsignedBitsLength(exponent._digits, exponent._digitLength);
    for (long i = 0; i < bitLength; i++)
    {
        int bit = 0;
        int digitPos = (int)(i >> 5);
        if(digitPos < exponent._digitLength)
            bit = (exponent._digits[digitPos] >> (i & 31)) & 1;
        if (value._digitLength > modulus._digitLength)
            value.DivRem(modulus, value);
        if (bit == 1)
        {
            result.Mul(value);
            if (result._digitLength > modulus._digitLength)
                result.DivRem(modulus, result);
        }
        value.Square();
    }
    result.DivRem(modulus, result);
    return result;
}
BigInteger BigInteger::SquareRoot(const BigInteger &value)
{
    if(((BigInteger &)value).isNegative())
        throw DomainException("value cannot be a negative");
    BigInteger xf = BigInteger(1u);
    BigInteger xl = BigInteger(1u);
    do
    {
        xf = xl;
        xl = value;
        xl.Div(xf).Add(xf).Shift(-1);
    } while (!(xf == xl || xf.Sub(xl).isMinusOne()));
    if(xf.isMinusOne())
        xl.Decrease();
    return xl;
}
BigInteger BigInteger::ModInverse(const BigInteger &value, const BigInteger &modulus)
{
    if(((BigInteger&)value).isOne())
        return BigInteger(1u);
    if(((BigInteger&)value).isNegative() || ((BigInteger&)value).isZero())
        throw DomainException("value must be positive.");
    if(((BigInteger&)modulus).isNegative() || ((BigInteger&)modulus).isZero())
        throw DomainException("Modulus must be positive.");

    BigInteger x1 = BigInteger(0u), x2 = modulus, y1 = BigInteger(1u), y2 = value;

    BigInteger t1, t2, q = BigInteger::DivRem(x2, y2, t2);
    q.Negate();
    t1 = q;

    while (!y2.isOne())
    {
        if (t2._sign == 0)
            return BigInteger(0u);

        x1 = y1; x2 = y2;
        y1 = t1; y2 = t2;
        q = BigInteger::DivRem(x2, y2, t2);
        q.Mul(y1);
        t1 = x1.Sub(q);
    }
    if (y1._sign == -1)
        return (y1.Add(modulus));
    else
        return y1;
}

BigInteger::operator int() const
{
    uint f_digit = this->_digits[0];
    f_digit -= (f_digit > 0x7FFFFFFF) * 0x7FFFFFFF;
    return (int)f_digit * this->_sign;
}
BigInteger::operator uint() const
{
    uint f_digit = this->_digits[0];
    return (uint)(f_digit * this->_sign);
}
BigInteger::operator long() const
{
    if(this->_digitLength > 1){
        ulong dig = ((ulong *)this->_digits)[0];
        dig -= (dig > 0x7FFFFFFFFFFFFFFF) * 0x7FFFFFFFFFFFFFFF;
        return (long)dig * this->_sign;
    } else {
        long f_digit = this->_digits[0];
        return f_digit * this->_sign;
    }
}
BigInteger::operator ulong() const
{
    if(this->_digitLength > 1){
        ulong dig = ((ulong *)this->_digits)[0];
        return (ulong)dig * this->_sign;
    } else {
        ulong f_digit = this->_digits[0];
        return f_digit * this->_sign;
    }
}

BigInteger::BigInteger(uint *digits, int length, int sign, bool internal)
{
    if(internal){
        if(length == 0){
            delete[] digits;
            this->_digitLength = 1;
            this->_digits = new uint[1] { 0 };
            this->_sign = 0;
        } else {
            if(length == 1 && digits[0] == 0)
                this->_sign = 0;
            else
                this->_sign = sign;
            if(sign == 0){
                this->_digitLength = 1;
                this->_digits = new uint[1] { 0 };
                this->_sign = 0;
            } else{
                this->_digits = digits;
                this->_digitLength = length;
            }
        }
    } else {
        if(!length){
            this->_sign = 0;
            this->_digitLength = length;
            this->_digits = new uint[1] { 0 };
        } else {
            while(digits[length - 1] == 0 && length > 1)
                length--;
            if(length == 1 && digits[0] == 0)
                this->_sign = 0;
            else
                this->_sign = sign;
            if(sign == 0){
                this->_digitLength = 1;
                this->_digits = new uint[1] { 0 };
                this->_sign = 0;
            } else {
                this->_digitLength = length;
                this->_digits = new uint[length];
                for(int i = 0; i < length; i++)
                    this->_digits[i] = digits[i];
            }
        }
    }
}

void BigInteger::GetSerializationData(BinaryWriter *writer) const
{
    writer->Write(this->_sign);
    if(this->_sign == 0)
        return;
    ByteArray array = ByteArray((byte *)this->_digits, this->_digitLength * 4);
    writer->Write(array);
}
bool BigInteger::SetSerializationData(BinaryReader *reader)
{
    if(!reader->Read(this->_sign)) return false;
    if(this->_sign == 0){
        this->_digitLength = 1;
        delete[] this->_digits;
        this->_digits = new uint[1] { 0 };
        return true;
    }
    ByteArray array;
    if(!reader->Read(array)) return false;
    uint *digits = (uint *)array.data();
    delete[] this->_digits;
    this->_digitLength = array.length() / 4;
    this->_digits = new uint[this->_digitLength];
    for(int i = 0; i < array.length(); i++)
        this->_digits[i] = digits[i];
    return true;
}

bool BigInteger::Equals(const Object &obj) const
{
    return this->Equals((const BigInteger &)obj);
}

bool BigInteger::Equals(const BigInteger &other) const
{
    if(this->_sign > other._sign)
        return false;
    if(this->_sign < other._sign)
        return false;
    return InternalBasicOperators::Compare(this->_digits, this->_digitLength, other._digits, other._digitLength) == 0;
}
long BigInteger::GetHashCode() const
{
    uint *data = this->_digits;
    long h1 = 5381, h2 = 5381;
    int len = this->_digitLength;
    for(int i = len & 1; i < len; i += 2){
        h1 = ((h1 << 5) + h1) ^ data[i];
        h2 = ((h2 << 5) + h2) ^ ((long)data[i + 1] << 32);
    }
    return h1 + ((h2 + (len & 1) * data[0]) * 1566083941);
}
