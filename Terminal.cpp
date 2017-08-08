#include "Text/Encoding.h"
#include "Terminal.h"


char *toCStyleString(const Char16 *chars, long length);

StandartStream Terminal::ssio = StandartStream(1);
StandartStream Terminal::sser = StandartStream(0);
TextReader Terminal::sinText = TextReader(&Terminal::ssio);
TextWriter Terminal::soutText = TextWriter(&Terminal::ssio);
TextWriter Terminal::serrText = TextWriter(&Terminal::sser);


void Terminal::Command(const String16 &cmd)
{
    char *c = toCStyleString(cmd.data(), cmd.length());
    system(c);
    delete[] c;
}

TextReader &Terminal::StdInput()
{
    return Terminal::sinText;
}

TextWriter &Terminal::StdError()
{
    return Terminal::serrText;
}
void Terminal::Clear()
{
#ifdef __linux__
    system("clear");
#endif
}
TextWriter &Terminal::StdOutput()
{
    return Terminal::soutText;
}

String16 Terminal::Scan()
{
    String16 line;
    is >> line;
    return line;
}

#define NonBMPSafe 1
char *toCStyleString(const Char16 *chars, long length){
    long len = 0;
    for(int i = 0; i < length; i++){
        ushort unicode = chars[i].unicode();
        int cl = 1 + (unicode > 0x7f) + (unicode > 0x800) + (0xd800 <= unicode && unicode < 0xe000);
        i += (cl >> 2);
#if NonBMPSafe
        len += cl + (cl >> 2);
#else
        len += cl;
#endif
    }
    char *u8chars = new char[len + 1];
    uint unicode = 0;
    for(int i = 0, j = 0; i < length; i++){
        unicode = chars[i].unicode();
        if(0xd800 <= unicode && unicode <= 0xdfff){ //If surrogate
            if(length - i < 2){
                u8chars[j++] = '\\';
                u8chars[j++] = 239;
                u8chars[j++] = 191;
                u8chars[j++] = 189;
#if NonBMPSafe
                u8chars[j++] = '\\';
#endif
                break;
            }else {
                unicode = (unicode - 0xd800) * 0x400 + (chars[++i].unicode() - 0xdc00) + 0x10000;
                if(unicode > 0x10ffff){
                    u8chars[j++] = '\\';
                    u8chars[j++] = 239;
                    u8chars[j++] = 191;
                    u8chars[j++] = 189;
#if NonBMPSafe
                u8chars[j++] = '\\';
#endif
                }else{
                    u8chars[j++] = (byte)(unicode / 262144 + 240);
                    u8chars[j++] = (byte)((unicode % 262144) / 4096 + 128);
                    u8chars[j++] = (byte)((unicode % 4096) / 64 + 128);
                    u8chars[j++] = (byte)(unicode % 64 + 128);
#if NonBMPSafe
                u8chars[j++] = ' ';
#endif
                }
            }
        } else {
            if(unicode < 0x80){
                u8chars[j++] = (byte)unicode;
            } else if(unicode < 0x0800){
                u8chars[j++] = (byte)(unicode / 64 + 192);
                u8chars[j++] = (byte)(unicode % 64 + 128);
            } else { // 0x0800 <= unicode && (unicode < 0xd800 || 0xdfff < unicode)
                u8chars[j++] = (byte)(unicode / 4096 + 224);
                u8chars[j++] = (byte)((unicode % 4096) / 64 + 128);
                u8chars[j++] = (byte)(unicode % 64 + 128);
            }
        }
    }
    u8chars[len] = 0;
    return u8chars;
}
