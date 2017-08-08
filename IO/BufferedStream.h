#ifndef BUFFEREDSTREAM_H
#define BUFFEREDSTREAM_H

#include "ByteStream.h"

class BufferedStream : public ByteStream
{
    PIMPL
public:
    BufferedStream(ByteStream *baseStream, StreamMode mode, long bufferSize = 4096);

    long availableDataLength();
    ByteStream &baseStream() const;

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

#endif // BUFFEREDSTREAM_H
