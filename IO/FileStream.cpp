#include <unistd.h>
#include "FileStream.h"
#include "IOException.h"
#include "../Char16.h"
#include "../Text/Encoder.h"

struct FileStream::_impl{
    FILE *fp = nullptr;
    bool _locked = false;
    String16 _fileName;
    bool _canRead = false;
    bool _canSeek = false;
    bool _canWrite = false;
};

FileStream::FileStream(const String16 &fileName, FileMode mode, bool lock)
{
    long utf8Len = Encoder::UTF8.GetLength(fileName.charsReference(), 0, fileName.length());
    ByteArray utf8c = ByteArray(utf8Len + 1);
    long charsUsed, bytesUsed;
    Encoder::UTF8.Encode(fileName.charsReference(), 0, fileName.length(), utf8c, 0, utf8Len, &charsUsed, &bytesUsed);
    utf8c[utf8Len] = '\0';

    const char* fn = (const char*)utf8c.data();

    this->_pImpl = new FileStream::_impl();

    switch (mode) {
    case FileMode::Append:
        this->_pImpl->fp = fopen(fn, "ab");
        if(this->_pImpl->fp == 0)
            throw FileNotFoundException("File cannot be found.", fileName);
        this->_pImpl->_canWrite = true;
        break;
    case FileMode::AppendOrCreate:
        this->_pImpl->fp = fopen(fn, "a+b");
        if(this->_pImpl->fp == 0)
            throw Exception("???");
        this->_pImpl->_canWrite = true;
        this->_pImpl->_canRead = true;
        break;
    case FileMode::Create:
        this->_pImpl->fp = fopen(fn, "w+b");
        if(this->_pImpl->fp == 0)
            throw Exception("???");
        this->_pImpl->_canWrite = true;
        break;
    case FileMode::Open:
        this->_pImpl->fp = fopen(fn, "rb");
        if(this->_pImpl->fp == 0)
            throw Exception("???");
        this->_pImpl->_canRead = true;
        break;
    case FileMode::OpenOrCreate:
        this->_pImpl->fp = fopen(fn, "r+b");
        if(this->_pImpl->fp == 0)
            this->_pImpl->fp = fopen(fn, "w+b");
        if(this->_pImpl->fp == 0)
            throw Exception("???");
        this->_pImpl->_canRead = true;
        this->_pImpl->_canWrite = true;
        break;
    default:
        throw Exception("What the fuck are you talking about?");
        break;
    }
    this->_pImpl->_fileName = fileName;
    this->_pImpl->_canSeek = ftell(this->_pImpl->fp) != -1;
    if(lock) this->Lock();
}

void FileStream::Clear()
{
    if(!this->_pImpl->_canWrite)
        throw NotSupportedException("Stream was not writable. Supporting file modes are Append, AppendOrCreate, Create and OpenOrCreate.");
    int ftr = ftruncate(fileno(this->_pImpl->fp), 0);
    if(ftr == 30) //EROFS
        throw IOException("The named file resides on a read-only file system.");
    if(ftr == 9 || ftr == 22) //EBADF or EINVAL
        throw IOException("Used bad file pointer.");
    if(ftr == 27) //EFBIG
        throw IOException("File was too large.");
}

const String16 &FileStream::fileName() const
{
    if(this->_pImpl == nullptr)
        throw ObjectClosedException("Object has already closed.", "FileStream");
    return this->_pImpl->_fileName;
}

void FileStream::Lock()
{
    if(this->_pImpl == nullptr)
        throw ObjectClosedException("Object has already closed.", "FileStream");
    if(this->_pImpl->_locked)
        return;
    int rs = ftrylockfile(this->_pImpl->fp);
    if(rs == 9) //EBADF
        throw IOException("Used bad file pointer when locking file.");
    if(rs == 16) //EBUSY
        throw IOException("The file is locked by another thread.");
    this->_pImpl->_locked = true;
}

ByteArray FileStream::ReadToEnd() const
{
    if(this->_pImpl == nullptr)
        throw ObjectClosedException("Object has already closed.", "FileStream");
    if(!this->_pImpl->_canRead)
        throw NotSupportedException("Stream was not readable. Supporting file modes are Open and OpenOrCreate.");
    if(!this->_pImpl->_canSeek)
        throw NotSupportedException("Seeking operations does not supported for FileStream.");
    long len = this->length();
    ByteArray array = ByteArray(this->length());
    int pos = ftell(this->_pImpl->fp);
    fseek(this->_pImpl->fp, 0, 0);
    fread(array.data(), 1, len, this->_pImpl->fp);
    fseek(this->_pImpl->fp, pos, 0);
    return array;
}

void FileStream::Unlock()
{
    if(this->_pImpl == nullptr)
        throw ObjectClosedException("Object has already closed.", "FileStream");
    if(!this->_pImpl->_locked)
        return;
    funlockfile(this->_pImpl->fp);
    this->_pImpl->_locked = false;
}

bool FileStream::canRead() const
{
    return this->_pImpl != 0 && this->_pImpl->_canRead;
}

bool FileStream::canSeek() const
{
    return this->_pImpl != 0 && this->_pImpl->_canSeek;
}

bool FileStream::canWrite() const
{
    return this->_pImpl != 0 && this->_pImpl->_canWrite;
}

bool FileStream::isClosed() const { return this->_pImpl == nullptr; }

long FileStream::length() const
{
    if(this->_pImpl == nullptr)
        throw ObjectClosedException("Object has already closed.", "FileStream");
    if(!this->_pImpl->_canSeek)
        throw NotSupportedException("Seeking operations does not supported for FileStream.");

    long pos = ftell(this->_pImpl->fp);
    fseek(this->_pImpl->fp, 0, 2); //SEEK_END
    long len = ftell(this->_pImpl->fp);
    fseek(this->_pImpl->fp, pos, 0); //SEEK_SET
    return len;
}

void FileStream::length(long length)
{
    if(this->_pImpl == nullptr)
        throw ObjectClosedException("Object has already closed.", "FileStream");
    if(length < 0)
        throw ArgumentOutOfRangeException("File length cannot be less than zero.");
    if(!this->_pImpl->_canWrite)
        throw NotSupportedException("Stream was not writable. Supporting file modes are Append, AppendOrCreate, Create and OpenOrCreate.");
    int ftr = ftruncate(fileno(this->_pImpl->fp), length);
    if(ftr == 30) //EROFS
        throw IOException("The named file resides on a read-only file system.");
    if(ftr == 9 || ftr == 22) //EBADF or EINVAL
        throw IOException("Used bad file pointer.");
    if(ftr == 27) //EFBIG
        throw IOException("File was too large.");
}

long FileStream::position() const
{
    if(this->_pImpl == nullptr)
        throw ObjectClosedException("Object has already closed.", "FileStream");
    if(!this->_pImpl->_canSeek)
        throw NotSupportedException("Seeking operations does not supported for FileStream.");
    return ftell(this->_pImpl->fp);
}

ByteStream &FileStream::position(long position)
{
    if(this->_pImpl == nullptr)
        throw ObjectClosedException("Object has already closed.", "FileStream");
    if(!this->_pImpl->_canSeek)
        throw NotSupportedException("Seeking operations does not supported for FileStream.");
    if(position < 0)
        throw ArgumentOutOfRangeException("Position cannot be less than zero.", "position");
    if(position > this->length())
        throw ArgumentOutOfRangeException("Position cannot be greater than stream length.", "position");
    fseek(this->_pImpl->fp, position, 0); //SEEK_SET
    return *this;
}

void FileStream::Close()
{
    if(this->_pImpl == nullptr)
        return;
    if(this->canWrite())
        this->Flush();
    if(this->_pImpl->_locked)
        funlockfile(this->_pImpl->fp);
    fclose(this->_pImpl->fp);
    delete this->_pImpl;
    this->_pImpl = nullptr;
}

long FileStream::Flush()
{
    if(this->_pImpl == nullptr)
        throw ObjectClosedException("Object has already closed.", "FileStream");
    return -1;
}

long FileStream::Read(ByteArray &buffer, long offset, long count)
{
    if(this->_pImpl == nullptr)
        throw ObjectClosedException("Object has already closed.", "FileStream");
    if(!this->_pImpl->_canRead)
        throw NotSupportedException("Stream was not readable. Supporting file modes are Open and OpenOrCreate.");
    if(offset < 0)
        throw ArgumentOutOfRangeException("Offset cannot be less than zero.", "offset");
    if(offset > buffer.length())
        throw ArgumentOutOfRangeException("Offset cannot be greater than buffer length.", "offset");
    if(count < 0)
        throw ArgumentOutOfRangeException("Count cannot be less than zero.");
    long readable = this->length() - this->position();
    if(readable < count)
        count = readable;
    if(count == 0)
        return 0;
    if(offset + count > buffer.length())
        buffer.Resize(offset + count);
    byte *offPtr = buffer.data() + offset;
    return fread(offPtr, 1, count, this->_pImpl->fp);
}

long FileStream::Seek(long offset, SeekOrigin origin)
{
    if(this->_pImpl == nullptr)
        throw ObjectClosedException("Object has already closed.", "FileStream");
    if(!this->_pImpl->_canSeek)
        throw NotSupportedException("Seeking operations does not supported for FileStream.");
    switch (origin) {
    case SeekOrigin::Begin:
        this->position(offset);
        break;
    case SeekOrigin::Current:
        this->position(this->position() + offset);
        break;
    case SeekOrigin::End:
        this->position(this->length() - offset);
    default:
        break;
    }
    return this->position();
}

long FileStream::Write(const ByteArray &buffer, long offset, long count)
{
    if(this->_pImpl == nullptr)
        throw ObjectClosedException("Object has already closed.", "FileStream");
    if(!this->_pImpl->_canWrite)
        throw NotSupportedException("Stream was not writable. Supporting file modes are Append, AppendOrCreate, Create and OpenOrCreate.");
    if(offset < 0)
        throw ArgumentOutOfRangeException("Offset cannot be less than zero.", "offset");
    if(offset + count > buffer.length())
        throw OutOfRangeException("Block boundries was out of range of source block.");
    if(count < 0)
        throw ArgumentOutOfRangeException("Count cannot be less than zero.");
    byte *offPtr = buffer.data() + offset;
    return fwrite(offPtr, 1, count, this->_pImpl->fp);
}
