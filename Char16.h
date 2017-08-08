#ifndef CHAR16_H
#define CHAR16_H

#include <locale>
#include "Defs.h"
#include "Object.h"

struct Char16 : public Object
{
public:
    Char16();
    Char16(int u); //For the Char16 c = 'anyChar' (>= 0x80) assignment.
    Char16(ushort u);
    Char16(char c);
    Char16(wchar_t c);

    Char16 &operator =(int u);
    Char16 &operator =(ushort u);
    Char16 &operator =(char c);
    Char16 &operator =(wchar_t c);
    bool operator ==(Char16 xc);
    bool operator ==(char c);
    bool operator ==(wchar_t c);
    bool operator ==(int c);

    bool isCJK() const;
    bool isDigit() const;
    bool isLowSurrogate() const;
    bool isHighSurrogate() const;
    bool isSurrogate() const;
    ushort unicode() const;

    bool Equals(const Object &obj) const override;
    String16 HexString();
    String16 ToString() const override;
    Char16 ToUpper();
    Char16 ToLower();

    operator ushort();

private:
    ushort _u = 0;
    static std::locale _locale;
};
#endif // CHAR16_H
