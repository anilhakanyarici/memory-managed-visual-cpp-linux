#ifndef IOEXCEPTION_H
#define IOEXCEPTION_H
#include "../Exception.h"

class IOException : public Exception
{
public:
    IOException() : Exception(){}
    IOException(const String16 &message) : Exception(message){}
};

class EndOfStreamException : IOException
{
    EndOfStreamException() : IOException() {}
    EndOfStreamException(const String16 &message) : IOException(message){}
};

class FileNotFoundException : public IOException
{
public:

    FileNotFoundException() : IOException(){}
    FileNotFoundException(const String16 &message) : IOException(message){}
    FileNotFoundException(const String16 &message, const String16 &fileName) : IOException(message){ this->_fileName = fileName; }

    String16 FileName() const { return this->_fileName; }

    String16 What() const override;

private:
    String16 _fileName;
};

class EndOfFileException : public IOException
{
public:
    EndOfFileException() : IOException(){}
    EndOfFileException(const String16 &message) : IOException(message){}
    EndOfFileException(const String16 &message, const String16 &fileName) : IOException(message){ this->_fileName = fileName; }

    String16 FileName() const { return this->_fileName; }

    String16 What() const override;

private:
    String16 _fileName;

};
#endif // IOEXCEPTION_H
