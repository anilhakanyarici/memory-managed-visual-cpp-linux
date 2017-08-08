#ifndef STANDARTSTREAM_H
#define STANDARTSTREAM_H

#include "CharStream.h"
#include "../Char16.h"

class Terminal;
class StandartStream final : public CharStream
{
    friend class Terminal;
private:
    StandartStream(int iotype);
    Char16 surrogate;
    int iotype; //1 is stdinput and stdoutput, 0 is stderror.

    // CharStream interface
public:
    bool canRead() const override { return this->iotype; }
    inline bool canSeek() const override { return false; }
    inline bool canWrite() const override { return true; }
    inline bool isClosed() const override { return false; }
    long length() const override;
    void length(long length) override;
    long position() const override;
    CharStream &position(long position) override;

    void Close() override {}
    long Flush() override { return -1; }
    long Read(CharArray &buffer, long offset, long count = 0) override;
    long ReadLine(CharArray &buffer, long offset) override;
    long Seek(long offset, SeekOrigin origin) override;
    long Write(const CharArray &buffer, long offset, long count) override;
    long WriteLine(const CharArray &buffer, long offset, long count) override;
};

#endif // STANDARTSTREAM_H
