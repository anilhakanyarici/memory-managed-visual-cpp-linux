#include "Exception.h"

Exception::Exception()
{
    this->_msg = "";
}

Exception::Exception(const String16 &message)
{
    this->_msg = message;
}

String16 Exception::What() const
{
    return this->_msg;
}

const char *Exception::what() const noexcept
{
    ByteArray utf8 = Encoding::UTF8.GetBytes(this->What().ToArray());
    char *cStyle = new char[utf8.length() + 1];
    cStyle[utf8.length()] = '\0';
    for(int i = 0; i < utf8.length(); i++)
        cStyle[i] = (char)utf8[i];
    return cStyle;
}

String16 ArgumentException::What() const
{
    StringList a = StringList();
    a.Add(this->_msg);
    a.Add(this->ArgumentName());
    return String16::Format("%s \n\tArgument Name: %s", a);
}

String16 ArgumentOutOfRangeException::What() const
{
    StringList a = StringList();
    a.Add(this->_msg);
    a.Add(this->ArgumentName());
    return String16::Format("%s \n\tArgument Name: %s", a);
}

String16 ObjectClosedException::What() const
{
    StringList a = StringList();
    a.Add(this->_msg);
    a.Add(this->ObjectName());
    return String16::Format("%s \n\tObject Name: %s", a);
}

String16 NotImplementedException::What() const
{
    StringList a = StringList();
    a.Add(this->_msg);
    a.Add(this->Member());
    return String16::Format("%s \n\tMember : %s", a);
}

String16 ArgumentNullException::What() const
{
    StringList a = StringList();
    a.Add(this->_msg);
    a.Add(this->ArgumentName());
    return String16::Format("%s \n\tArgument Name: %s", a);
}
