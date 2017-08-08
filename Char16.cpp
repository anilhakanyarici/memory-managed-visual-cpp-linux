#include <ctype.h>
#include "Char16.h"
#include "String16.h"
#include "Exception.h"

std::locale Char16::_locale = std::locale("");

Char16::Char16()
{
    this->_u = 0;
}

Char16::Char16(int u)
{
    byte* i = (byte*)&u;
    uint unicode;
    if(i[3] > 239) throw LiteralException("Too many characters for character literal."); //unicode = (i[3] - 240) * 262144 + (i[2] - 128) * 4096 + (i[1] - 128) * 64 + (i[0] - 128);
    else if(i[2] > 223) unicode = (i[2] - 224) * 4096 + (i[1] - 128) * 64 + (i[0] - 128);
    else if(i[1] > 191) unicode = (i[1] - 192) * 64 + (i[0] - 128);
    else unicode = (ushort)u;
    this->_u = unicode;
    //if(0xDFFF >= unicode && unicode >= 0xD800) = than u is one of UTF-16 surrogate characters.
}
Char16::Char16(ushort u)
{
    this->_u = u;
}
Char16::Char16(char c)
{
    if((ushort)c > 127) //throw LiteralException("There are too many bytes for supported utf8 character literal.");
        this->_u = 63;
    else this->_u = c;
}

Char16 &Char16::operator =(int u)
{
    byte* i = (byte*)&u;
    uint unicode;
    if(i[3] > 239) throw LiteralException("Too many characters for character literal.");
    else if(i[2] > 223) unicode = (i[2] - 224) * 4096 + (i[1] - 128) * 64 + (i[0] - 128);
    else if(i[1] > 191) unicode = (i[1] - 192) * 64 + (i[0] - 128);
    else unicode = (ushort)u;
    this->_u = (ushort)unicode;
    return *this;
}
Char16 &Char16::operator =(ushort u)
{
    this->_u = u;
    return *this;
}
Char16 &Char16::operator =(char c)
{
    if((ushort)c > 127) //throw LiteralException("There are too many bytes for supported utf8 character literal.");
        this->_u = 63;
    else this->_u = c;
    return *this;
}
bool Char16::operator ==(Char16 xc)
{
    return this->_u == xc._u;
}

bool Char16::operator ==(int c)
{
    byte* i = (byte*)&c;
    uint unicode;
    if(i[3] > 239) return false;
    else if(i[2] > 223) unicode = (i[2] - 224) * 4096 + (i[1] - 128) * 64 + (i[0] - 128);
    else if(i[1] > 191) unicode = (i[1] - 192) * 64 + (i[0] - 128);
    else unicode = c;
    return this->_u == unicode;
}

bool Char16::Equals(const Object &obj) const
{
    Char other = (const Char &)obj;
    return other == *this;
}

String16 Char16::HexString()
{
    ushort unicode = this->unicode();
    char c[10];
    int len = sprintf(c, "U+%.4x", unicode);
    c[len] = 0;
    return String16((const char *)c);
}

bool Char16::isCJK() const
{
    bool radicalsSupplement = 0x2e80 <= this->_u && this->_u < 0x2f00;
    bool symbolsPunctuation = 0x3000 <= this->_u && this->_u < 0x3040;
    bool strokes = 0x31c0 <= this->_u && this->_u < 0x31f0;
    bool compability = 0x3300 <= this->_u && this->_u < 0x3400;
    bool unifiedIdeographsExtA = 0x3400 <= this->_u && this->_u < 0x4dc0;
    bool unifiedIdeographs = 0x4e00 <= this->_u && this->_u < 0xa000;
    bool compabilityIdeographs = 0xf900 <= this->_u && this->_u < 0xfb00;
    bool compabilityForms = 0xfe30 <= this->_u && this->_u < 0xfe50;
    return radicalsSupplement || symbolsPunctuation || strokes || compability || unifiedIdeographsExtA || unifiedIdeographs || compabilityIdeographs || compabilityForms;
}
bool Char16::operator ==(char c)
{
    Char16 xc = Char16(c);
    return this->_u == xc._u;
}

bool Char16::isDigit() const
{
    return 47 < this->_u && this->_u < 58;
}

bool Char16::isLowSurrogate() const
{
    return ((this->_u & 0xfffffc00) == 0xdc00);
}

bool Char16::isHighSurrogate() const
{
    return ((this->_u & 0xfffffc00) == 0xd800);
}
bool Char16::isSurrogate() const
{
    return 0xd800 <= this->_u && this->_u < 0xE000;
}

ushort Char16::unicode() const
{
    return this->_u;
}

String16 Char16::ToString() const
{
    return String16(*this);
}
Char16 Char16::ToUpper()
{
    ushort code = std::toupper((wchar_t)this->_u, Char16::_locale);
    return Char16(code);
}
Char16 Char16::ToLower()
{
    ushort code = std::tolower((wchar_t)this->_u, Char16::_locale);
    return Char16(code);
}

Char16::operator ushort()
{
    return this->_u;
}

