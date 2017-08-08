#ifndef VOBJECT_H
#define VOBJECT_H

#include <gtk/gtk.h>
#include "../Defs.h"

typedef void *RawSignal;
typedef void *Signal;

class EventArgs;

struct VSignal
{
    void *eventMethod = nullptr;
    void *instance = nullptr;
    GCallback callBack;
    const char* signalName;
    EventArgs *args = nullptr;
    void *userData = nullptr;
    ulong id;
};

class VObject
{
public:
    Signal Connect(RawSignal s);
    bool Disconnect(Signal s);
};

struct DoublePosition { double X, Y; };
struct Position { int X, Y; };
struct Size { int Width, Height; };
struct PreferredHeight { int Minimum; int Natural; };
struct PreferredWidth { int Minimum; int Natural; };
struct PreferredSize { Size Minimum; Size Natural; };

#endif // VOBJECT_H
