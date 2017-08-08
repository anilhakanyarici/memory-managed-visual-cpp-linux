#include "IOException.h"

String16 FileNotFoundException::What() const
{
    StringList a = StringList();
    a.Add(this->_msg);
    a.Add(this->FileName());
    return String16::Format("%s \n\tFile Name: %s", a);
}

String16 EndOfFileException::What() const
{
    StringList a = StringList();
    a.Add(this->_msg);
    a.Add(this->FileName());
    return String16::Format("%s \n\tFile Name: %s", a);
}
