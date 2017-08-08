#ifndef TERMINAL_H
#define TERMINAL_H

#include <string>
#include "Defs.h"
#include "String16.h"
#include "Convert.h"
#include "IO/TextReader.h"
#include "IO/TextWriter.h"
#include "IO/StandartStream.h"

#define tpl(x) Terminal::PrintLine(x)
#define tp(x) Terminal::Print(x)
#define scan Terminal::Scan()
#define is Terminal::StdInput()
#define os Terminal::StdOutput()
#define es Terminal::StdError()

class Terminal
{
public:
    static void Clear();
    static void Command(const String16 &cmd);
    static inline void Error(const String16 &err) { es < err; }
    static inline void ErrorLine(const String16 &err) { es << err; }
    static TextWriter &StdError();
    static TextWriter &StdOutput();
    static TextReader &StdInput();
    static inline void Print(bool value) { os < Convert::ToString(value); }
    static inline void Print(byte value) { os < Convert::ToString(value); }
    static inline void Print(char value) { os < Convert::ToString(value); }
    static inline void Print(int value) { os < Convert::ToString(value); }
    static inline void Print(uint value) { os < Convert::ToString(value); }
    static inline void Print(long value) { os < Convert::ToString(value); }
    static inline void Print(ulong value) { os < Convert::ToString(value); }
    static inline void Print(double value) { os < Convert::ToString(value); }
    static inline void Print(float value) { os < Convert::ToString(value); }
    static inline void Print(void* value) { os < Convert::ToString(value); }
    static inline void Print(const IStringable &value) { os < value.ToString(); }
    static inline void Print(const String16 &value) { os < value; }
    static inline void Print(const char *value) { fprintf(stdout, "%s", value); }
    static inline void Print(const String16 &format, const StringList &args) { os < String16::Format(format, args); }
    static inline void PrintLine(bool value) { os << Convert::ToString(value); }
    static inline void PrintLine(byte value) { os << Convert::ToString(value); }
    static inline void PrintLine(char value) { os << Convert::ToString(value); }
    static inline void PrintLine(int value) { os << Convert::ToString(value); }
    static inline void PrintLine(uint value) { os << Convert::ToString(value); }
    static inline void PrintLine(long value) { os << Convert::ToString(value); }
    static inline void PrintLine(ulong value) { os << Convert::ToString(value); }
    static inline void PrintLine(double value) { os << Convert::ToString(value); }
    static inline void PrintLine(float value) { os << Convert::ToString(value); }
    static inline void PrintLine(void* value) { os << Convert::ToString(value); }
    static inline void PrintLine(const IStringable &value) { os << value.ToString(); }
    static inline void PrintLine(const String16 &value) { os << value; }
    static inline void PrintLine(const char *value) { fprintf(stdout, "%s\n", value); }
    static inline void PrintLine(const String16 &format, const StringList &args) { os << String16::Format(format, args); }
    static inline String16 Scan();

private:
    static StandartStream ssio;
    static StandartStream sser;
    static  TextReader sinText;
    static  TextWriter soutText;
    static  TextWriter serrText;
};

#endif // TERMINAL_H
