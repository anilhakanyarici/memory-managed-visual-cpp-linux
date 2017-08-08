#ifndef PANED_H
#define PANED_H

#include "BaseContainer.h"

class Paned : public BaseContainer
{
public:
    static Paned *New(GtkOrientation orientation);

    BaseWidget *child1() const;
    void child1(BaseWidget *widget);
    BaseWidget *child2() const;
    void child2(BaseWidget *widget);
    int position() const;
    void position(int pos);
    bool wideHandle() const;
    void wideHandle(bool p);
    UiWindow *getHandleWindow() const;

    void Pack1(BaseWidget *child, bool resize, bool shrink);
    void Pack2(BaseWidget *child, bool resize, bool shrink);

    class Signals : public BaseContainer::Signals
    {
    public:
        static RawSignal AcceptPosition(SignalCallback eventMethod, void *instance = nullptr, void *userData = nullptr); //Callback(UiPaned *, EventArgs *)
        static RawSignal CancelPosition(SignalCallback eventMethod, void *instance = nullptr, void *userData = nullptr); //Callback(UiPaned *, EventArgs *)
        static RawSignal CycleChildFocus(SignalCallback eventMethod, void *instance = nullptr, void *userData = nullptr); //Callback(UiPaned *, bool, EventArgs *)
        static RawSignal CycleHandleFocus(SignalCallback eventMethod, void *instance = nullptr, void *userData = nullptr); //Callback(UiPaned *, bool, EventArgs *)
        static RawSignal MoveHandle(SignalCallback eventMethod, void *instance = nullptr, void *userData = nullptr); //Callback(UiPaned *, GtkScrollType, EventArgs *)
        static RawSignal ToggleHandleFocus(SignalCallback eventMethod, void *instance = nullptr, void *userData = nullptr); //Callback(UiPaned *, EventArgs *)
    };
};

#endif // PANED_H
