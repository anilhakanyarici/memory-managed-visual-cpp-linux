#ifndef MEMORYSTREAM_H
#define MEMORYSTREAM_H

#include "ByteStream.h"

class MemoryStream final : public ByteStream
{
    PIMPL
public:
    MemoryStream();
    MemoryStream(const ByteArray &buffer);

    const ByteArray &getBuffer() const;

    void Clear();
    ByteArray ToArray() const;

    // ByteStream interface
public:
    inline bool canRead() const override { return true; }
    inline bool canSeek() const override { return true; }
    inline bool canWrite() const override { return true; }
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

#endif // MEMORYSTREAM_H
