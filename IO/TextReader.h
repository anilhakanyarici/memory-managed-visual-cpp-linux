#ifndef TEXTREADER_H
#define TEXTREADER_H

#include "CharStream.h"
#include "ByteStream.h"
#include "../Text/Encoding.h"

class TruncateReader;
class TextReader final
{
    PIMPL
public:
    TextReader(CharStream *baseStream);

    bool endOfStream() const;
    CharStream &baseStream() const;

    Char16 Peek();
    long ReadBlock(CharArray &buffer, long offset, long count);
    String16 ReadBlock(long count);
    long ReadChar(CharArray &buffer, long offset);
    Char16 ReadChar();
    long ReadLine(CharArray &buffer, long offset);
    String16 ReadLine();
    long ReadToSpace(CharArray &buffer, long offset);
    String16 ReadToSpace();
    long ReadTo(CharArray &buffer, long offset, Char16 ch);
    String16 ReadTo(Char16 ch);
    long ReadTo(CharArray &buffer, long offset, const String16 &endText);
    String16 ReadTo(const String16 &endText);
    long ReadToEnd(CharArray &buffer, long offset);
    String16 ReadToEnd();

    bool operator >(String16 &str);
    bool operator >>(String16 &str);
    bool operator >>=(String16 &str);
    TruncateReader operator %(const char *endText);
    TruncateReader operator %(const String16 &endText);

    TextReader(const TextReader &reader);
    TextReader &operator =(const TextReader &reader);
    ~TextReader();

};
class TruncateReader
{
    friend class TextReader;
private:
    TruncateReader(TextReader *reader, const String16 &endText);

    TruncateReader (const TruncateReader &tr);
    TruncateReader &operator =(const TruncateReader &tr);

    String16 _endText;
    TextReader *_reader;

public:
    bool operator >(String16 &str);
};
#endif // TEXTREADER_H
