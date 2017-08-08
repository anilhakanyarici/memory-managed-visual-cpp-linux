#include "Atom.h"
#include "../String16.h"
#include "../ByteArray.h"
#include "UiWindow.h"

Atom::Atom()
{

}

Atom::Atom(GdkAtom atom)
{
    this->_atom = atom;
}

Atom::Atom(const String16 &atomName, bool ifOnlyExist)
{
    ByteArray utf8 = atomName.ToCString();
    this->_atom = gdk_atom_intern((const char *)utf8.data(), ifOnlyExist);
}

String16 Atom::target(const String16 &str)
{
    ByteArray utf8 = str.ToCString();
    return String16((const char *)gdk_utf8_to_string_target((const char *)utf8.data()));
}

String16 Atom::name() const { return String16((const char *)gdk_atom_name(this->_atom)); }

