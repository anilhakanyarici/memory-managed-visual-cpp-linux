#ifndef FILESTREAM_H
#define FILESTREAM_H
#include <stdio.h>
#include "../String16.h"
#include "ByteStream.h"

enum FileMode { Append, AppendOrCreate, Create, Open, OpenOrCreate };

class FileStream final: public ByteStream
{
    PIMPL
public:
    FileStream(const String16 &fileName, FileMode mode = FileMode::OpenOrCreate, bool lock = false);

    const String16 &fileName() const;

    void Clear();
    void Lock();
    ByteArray ReadToEnd() const;
    void Unlock();

    // ByteStream interface
public:
    bool canRead() const override;
    bool canSeek() const override;
    bool canWrite() const override;
    bool isClosed() const override;
    long length() const override;
    void length(long length) override;
    long position() const override;
    ByteStream &position(long position) override;

    void Close() override;
    long Flush() override;
    long Read(ByteArray &buffer, long offset, long count) override;
    long Seek(long offset, SeekOrigin origin) override;
    long Write(const ByteArray &buffer, long offset, long count) override;
};

#endif // FILESTREAM_H
