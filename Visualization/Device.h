#ifndef DEVICE_H
#define DEVICE_H

#include "VObject.h"
#include "../String16.h"
#include "../Array.h"

class Display;
class Screen;
class DWindow;

class Device : public VObject
{
public:
    String16 name() const;
    String16 vendorId() const;
    String16 productId() const;
    GdkInputSource source() const;
    GdkInputMode mode() const;
    void mode(GdkInputMode m);
    Device *associatedDevice() const;
    GdkDeviceType deviceType() const;
    Display *display() const;
    bool hasCursor() const;
    bool axesCount() const;
    bool keysCount() const;
    DWindow *lastEventWindow() const;

    void Warp(Screen *scr, int x, int y);
    Array<Device *>GetSlaveDevices() const;

    class Signals
    {
    public:
        static RawSignal Changed(SignalCallback eventMethod, void *instance = nullptr, void *userData = nullptr); //Callback(Device *, EventArgs *)
    };
};

#endif // DEVICE_H
