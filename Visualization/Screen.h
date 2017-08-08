#ifndef SCREEN_H
#define SCREEN_H

#include "VObject.h"
#include "../Array.h"

class Visual;
class DWindow;
class Display;

class Screen : public VObject
{
public:
    static Screen *Default();

    Visual *getSystemVisual() const;
    Visual *getRGBAVisual() const;
    bool isComposited() const;
    double resolution() const;
    void resolution(double dpi);
    DWindow *getRootWindow() const;
    Display *getDisplay() const;

    Array<Visual *> GetVisuals();
    Array<DWindow *> GetToplevelWindows();
    Array<DWindow *> GetWindowStack();

    class Signals
    {
    public:
        static RawSignal CompositedChanged(SignalCallback eventMethod, void *instance = nullptr, void *userData = nullptr); //Callback(Screen *, EventArgs *)
        static RawSignal MonitorsChanged(SignalCallback eventMethod, void *instance = nullptr, void *userData = nullptr); //Callback(Screen *, EventArgs *)
        static RawSignal SizeChanged(SignalCallback eventMethod, void *instance = nullptr, void *userData = nullptr); //Callback(Screen *, EventArgs *)
    };
};
#endif // SCREEN_H
