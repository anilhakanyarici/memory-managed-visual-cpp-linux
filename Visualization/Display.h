#ifndef DISPLAY_H
#define DISPLAY_H

#include "VObject.h"
#include "../Array.h"
#include "Atom.h"

class Screen;
class Display;
class Pixelbuffer;
class CairoSurface;
class DWindow;
class Device;

class Display : public VObject
{
public:
    static Display *Open(const String16 &name);
    static Display *Default();

    String16 name() const;
    Screen *defaultScreen() const;
    bool isClosed() const;
    bool hasPending() const;
    bool supportsCursorColor() const;
    bool supportsCursorAlpha() const;
    uint cursorSize() const;
    Size maximalCursorSize() const;
    bool supportsSelectionNotification() const;
    bool supportsClipboardPersistence() const;
    bool supportsShapes() const;
    bool supportsInputShapes() const;

    void Beep();
    void Close();
    void Flush();
    bool RequestSelectionNotification(Atom selection);
    bool IsGrabbed(Device * dev);
    void SetDoubleClickDistance(uint msec);
    void SetDoubleClickTime(uint msec);
    void Sync();

    class Signals
    {
    public:
        static RawSignal Closed(SignalCallback eventMethod, void *instance = nullptr, void *userData = nullptr); //Callback(Display *, bool, EventArgs *)
        static RawSignal Opened(SignalCallback eventMethod, void *instance = nullptr, void *userData = nullptr); //Callback(Display *, EventArgs *)
    };
};

#endif // DISPLAY_H
