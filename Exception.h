#ifndef EXCEPTION_H
#define EXCEPTION_H

#define Check_Exceptions 1
#include "Text/Encoding.h"

class Exception : public std::exception
{
public:
    Exception();
    Exception(const String16 &message);

    virtual String16 Message() const { return this->_msg; }

    virtual String16 What() const;
    inline String16 ToString() { return this->What(); }

protected:
    String16 _msg;

public:
     const char *what() const  noexcept override final;
};

class FormatException : public Exception
{
public:
    FormatException() : Exception(){}
    FormatException(const String16 &message) : Exception(message){}
};

class ArgumentException : public Exception
{
public:
    ArgumentException() : Exception(){}
    ArgumentException(const String16 &message, const String16 &argName) : Exception(message){ this->_argName = argName; }

    String16 ArgumentName() const { return this->_argName; }

    String16 What() const override;

private:
    String16 _argName;
};

class OutOfRangeException : public Exception
{
public:
    OutOfRangeException() : Exception(){}
    OutOfRangeException(const String16 &message) : Exception(message){}
};
class IndexOutOfRangeException : public OutOfRangeException
{
public:
    IndexOutOfRangeException() : OutOfRangeException() {}
    IndexOutOfRangeException(const String16 &message) : OutOfRangeException(message){}
};
class ArgumentOutOfRangeException : public OutOfRangeException
{
public:
    ArgumentOutOfRangeException() : OutOfRangeException(){}
    ArgumentOutOfRangeException(const String16 &message) : OutOfRangeException(message){ this->_argName = ""; }
    ArgumentOutOfRangeException(const String16 &message, const String16 &argName) : OutOfRangeException(message){ this->_argName = argName; }

    String16 ArgumentName() const { return this->_argName; }

    String16 What() const override;

private:
    String16 _argName;
};

class NotSupportedException : public Exception
{
public:
    NotSupportedException() : Exception(){}
    NotSupportedException(const String16 &message) : Exception(message){}
};

class ArithmeticException : public Exception
{
public:
    ArithmeticException() : Exception(){}
    ArithmeticException(const String16 &message) : Exception(message){}
};
class DivideByZeroException : public ArithmeticException
{
public:
    DivideByZeroException() : ArithmeticException("Attempted to divide by zero.") {}
    DivideByZeroException(const String16 &message) : ArithmeticException(message){}
};
class DomainException : public ArithmeticException
{
public:
    DomainException() : ArithmeticException("Function input was not in the domain."){}
    DomainException(const String16 &message) : ArithmeticException(message){}
};

class LiteralException : public Exception
{
public:
    LiteralException() : Exception(){}
    LiteralException(const String16 &message) : Exception(message){}
};

class InvalidOperationException : public Exception
{
public:
    InvalidOperationException() : Exception(){}
    InvalidOperationException(const String16 &message) : Exception(message){}
};

class ObjectClosedException : public Exception
{
public:
    ObjectClosedException() : Exception(){}
    ObjectClosedException(const String16 &message) : Exception(message){}
    ObjectClosedException(const String16 &message, const String16 &objectName) : Exception(message) { this->_objName = objectName; }

    String16 ObjectName() const { return this->_objName; }

    String16 What() const override;

private:
    String16 _objName;
};

class SystemException : public Exception
{
public:
    SystemException() : Exception(){}
    SystemException(const String16 &message) : Exception(message){}
};
class NotImplementedException : public SystemException
{
public:
    NotImplementedException() : SystemException(){}
    NotImplementedException(const String16 &message) : SystemException(message){}
    NotImplementedException(const String16 &message, const String16 &member) : SystemException(message){ this->_member = member; }

    String16 Member() const { return this->_member; }

    String16 What() const override;

private:
    String16 _member;

};

class ArgumentNullException : public Exception
{
public:
    ArgumentNullException() : Exception(){}
    ArgumentNullException(const String16 &message) : Exception(message){ this->_argName = ""; }
    ArgumentNullException(const String16 &message, const String16 &argName) : Exception(message){ this->_argName = argName; }

    String16 ArgumentName() const { return this->_argName; }

    String16 What() const override;

private:
    String16 _argName;
};

class ThreadStateException : public Exception
{
public:
    ThreadStateException() : Exception() {}
    ThreadStateException(const String16 &message) : Exception(message){}
};
#endif // EXCEPTION_H
