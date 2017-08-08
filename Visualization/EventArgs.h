#ifndef EVENTARGS_H
#define EVENTARGS_H

#include <gtk/gtk.h>
#include "VObject.h"
#include "Atom.h"

class UiWindow;
class Position;
class DoublePosition;
class CairoRegion;
class Size;
class Device;

class EventArgs
{
protected:
    GdkEvent *_gtkEvent;
public:
    EventArgs(GdkEvent *any);

    void *UserData;
    Signal EventSignal;
    bool CanStopHandlers = false;
    bool StopOtherHandlers = false;

    bool isExplicit() const;
    GdkEventType type() const;
    UiWindow *window() const;
};

//Describes a key press or key release event.
class KeyEventArgs : public EventArgs
{
public:
    KeyEventArgs(GdkEvent *keyEvent);

    uint time() const;
    GdkModifierType state() const;
    uint key() const;
    byte group() const;
    ushort hardwareKeycode() const;
    uint isModifier() const;

};

//Used for button press and button release events.
class ButtonEventArgs : public EventArgs
{
public:
    ButtonEventArgs(GdkEvent *buttonEvent);

    bool isSinglePress() const;
    bool isDoublePress() const;
    bool isTriplePress() const;
    bool isRelease() const;

    uint time() const;
    DoublePosition pointerPosition() const;
    double *axes() const;
    GdkModifierType state() const;
    uint button() const;
    DoublePosition pointerPositionOnRoot() const;
};

//Used for touch events.
class TouchEventArgs : public EventArgs
{
public:
    TouchEventArgs(GdkEvent *touchEvent);

    bool isBegin() const;
    bool isUpdate() const;
    bool isEnd() const;
    bool isCancel() const;

    uint time() const;
    DoublePosition pointerPosition() const;
    double *axes() const;
    GdkModifierType state() const;
    bool emulatingPointer() const;
    DoublePosition pointerPositionOnRoot() const;
};

//Generated from button presses for the buttons 4 to 7. Wheel mice are usually configured to generate button press events for buttons 4 and 5 when the wheel is turned.
class ScrollEventArgs : public EventArgs
{
public:
    ScrollEventArgs(GdkEvent *scrollEvent);

    uint time() const;
    DoublePosition pointerPosition() const;
    GdkModifierType state() const;
    GdkScrollDirection direction() const;
    DoublePosition pointerPositionOnRoot() const;
    DoublePosition delta() const;
};

//Generated when the pointer moves.
class MotionEventArgs : public EventArgs
{
public:
    MotionEventArgs(GdkEvent *motionEvent);

    uint time() const;
    DoublePosition pointerPosition() const;
    double *axes() const;
    GdkModifierType state() const;
    DoublePosition pointerPositionOnRoot() const;
};

//Generated when all or part of a window becomes visible and needs to be redrawn.
class ExposeEventArgs : public EventArgs
{
public:
    ExposeEventArgs(GdkEvent *exposeEvent);

    GdkRectangle area() const;
    int count() const;
    bool isExpose();
    bool isDamage();
};

//Generated when the pointer enters or leaves a window.
class CrossingEventArgs : public EventArgs
{
public:
    CrossingEventArgs(GdkEvent *crossingEvent);

    uint time() const;
    DoublePosition pointerPosition() const;
    DoublePosition pointerPositionOnRoot() const;
    UiWindow *subWindow() const;
    GdkCrossingMode mode() const;
    GdkNotifyType detail() const;
    bool focus() const;
    GdkModifierType state() const;
};

//Describes a change of keyboard focus.
class FocusChangedEventArgs : public EventArgs
{
public:
    FocusChangedEventArgs(GdkEvent *focusEvent);

    bool in() const;
};

//Generated when a window size or position has changed.
class ConfigureEventArgs : public EventArgs
{
public:
    ConfigureEventArgs(GdkEvent *configureEvent);

    Position windowPosition() const;
    Size newSize() const;
};

//Describes a property change on a window.
class PropertyEventArgs : public EventArgs
{
public:
    PropertyEventArgs(GdkEvent *propertyEvent);

    Atom atom() const;
    uint time() const;
    bool isDeleted() const;
};

//Generated when a selection is requested or ownership of a selection is taken over by another client application.
class SelectionEventArgs : public EventArgs
{
public:
    SelectionEventArgs(GdkEvent *selectionEvent);

    Atom selection() const;
    Atom target() const;
    Atom property() const;
    uint time() const;
    UiWindow *requestor() const;
};

//Generated when the state of a toplevel window changes.
class WindowStateEventArgs : public EventArgs
{
public:
    WindowStateEventArgs(GdkEvent *windowStateEvent);

    GdkWindowState changedMask() const;
    GdkWindowState newState() const;
};

//Generated when a setting is modified.
class SettingEventArgs : public EventArgs
{
public:
    SettingEventArgs(GdkEvent *settingEvent);

    GdkSettingAction action() const;
    bool isNew() const;
    bool isChanged() const;
    bool isDeleted() const;
    String16 name() const;
};

//Generated when the owner of a selection changes. On X11, this information is only available if the X server supports the XFIXES extension.
class OwnerChangeEventArgs : public EventArgs
{
public:
    OwnerChangeEventArgs(GdkEvent *ownerChangeEvent);

    UiWindow *newOwner() const;
    GdkOwnerChange reason() const;
    Atom selection() const;
    uint time() const;
    uint selectionTime() const;
};

//Generated when a pointer or keyboard grab is broken.
class GrabBrokenEventArgs : public EventArgs
{
public:
    GrabBrokenEventArgs(GdkEvent *grabBrokenEvent);

    bool isKeyboard() const;
    bool isImplicit() const;
    UiWindow *grabWindow() const;
};

class ProximityEventArgs : public EventArgs
{
public:
    ProximityEventArgs(GdkEvent *proxEvent);
    uint time() const;
    Device *device() const;
};

#endif // EVENTARGS_H
