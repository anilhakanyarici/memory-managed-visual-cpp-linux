#ifndef STRINGSTREAM_H
#define STRINGSTREAM_H

#include "CharStream.h"

class StringStream final: public CharStream, IStringable
{
    PIMPL
public:
    StringStream();
    StringStream(const CharArray &buffer);

    const CharArray &getBuffer() const;

    void Clear();
    CharArray ToArray() const;
    String16 ToString() const override;

    // CharStream interface
public:
    inline bool canRead() const override { return true; }
    inline bool canSeek() const override { return true; }
    inline bool canWrite() const override { return true; }
    bool isClosed() const override;
    long length() const override;
    void length(long length) override;
    long position() const override;
    CharStream &position(long position) override;

    void Close() override;
    long Flush() override;
    long Read(CharArray &buffer, long offset, long count) override;
    long ReadLine(CharArray &buffer, long offset) override;
    long Seek(long offset, SeekOrigin origin) override;
    long Write(const CharArray &buffer, long offset, long count) override;
    long WriteLine(const CharArray &buffer, long offset, long count) override;

};

#endif // STRINGSTREAM_H
