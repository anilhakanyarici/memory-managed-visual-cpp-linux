#ifndef ATOM_H
#define ATOM_H

#include <gtk/gtk.h>
#include "../ByteArray.h"

class String16;
struct AtomProperty;

class Atom
{
    friend class UiWindow;
    friend class AtomProperty;
    friend class Display;
    GdkAtom _atom;

    Atom();
public:
    Atom(GdkAtom atom);
    Atom(const String16 &atomName, bool ifOnlyExist);

    String16 target(const String16 &str);
    String16 name() const;

};

struct AtomProperty
{
    bool IsExist;
    Atom ActualPropertyType;
    int ActualFormat;
    int ActualLength;
    ByteArray Data;
};
#endif // ATOM_H
