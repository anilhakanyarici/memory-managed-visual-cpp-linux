#include "EventArgs.h"
#include "UiWindow.h"
#include "../Char16.h"

EventArgs::EventArgs(GdkEvent *any)
{
    this->_gtkEvent = any;
}

bool EventArgs::isExplicit() const { return (bool)this->_gtkEvent->any.send_event; }

GdkEventType EventArgs::type() const
{
    return this->_gtkEvent->type;
}

UiWindow *EventArgs::window() const
{
    return (UiWindow *)this->_gtkEvent->any.window;
}

ButtonEventArgs::ButtonEventArgs(GdkEvent *buttonEvent) : EventArgs(buttonEvent){}
bool ButtonEventArgs::isSinglePress() const { return this->type() == GDK_BUTTON_PRESS; }
bool ButtonEventArgs::isDoublePress() const { return this->type() == GDK_2BUTTON_PRESS; }
bool ButtonEventArgs::isTriplePress() const { return this->type() == GDK_3BUTTON_PRESS; }
bool ButtonEventArgs::isRelease() const { return this->type() == GDK_BUTTON_RELEASE; }
uint ButtonEventArgs::time() const { return (uint)this->_gtkEvent->button.time; }

DoublePosition ButtonEventArgs::pointerPosition() const
{
    DoublePosition pos;
    pos.X = this->_gtkEvent->button.x;
    pos.Y = this->_gtkEvent->button.y;
    return pos;
}

double *ButtonEventArgs::axes() const { return (double *)this->_gtkEvent->button.axes; }
GdkModifierType ButtonEventArgs::state() const { return (GdkModifierType)this->_gtkEvent->button.state; }
uint ButtonEventArgs::button() const { return this->_gtkEvent->button.button; }

DoublePosition ButtonEventArgs::pointerPositionOnRoot() const
{
    DoublePosition pos;
    pos.X = this->_gtkEvent->button.x_root;
    pos.Y = this->_gtkEvent->button.y_root;
    return pos;
}

TouchEventArgs::TouchEventArgs(GdkEvent *touchEvent) : EventArgs(touchEvent){}

bool TouchEventArgs::isBegin() const { return this->type() == GDK_TOUCH_BEGIN; }
bool TouchEventArgs::isUpdate() const { return this->type() == GDK_TOUCH_UPDATE; }
bool TouchEventArgs::isEnd() const { return this->type() == GDK_TOUCH_END; }
bool TouchEventArgs::isCancel() const { return this->type() == GDK_TOUCH_CANCEL; }
uint TouchEventArgs::time() const { return (uint)this->_gtkEvent->touch.time; }

DoublePosition TouchEventArgs::pointerPosition() const
{
    DoublePosition pos;
    pos.X = this->_gtkEvent->touch.x;
    pos.Y = this->_gtkEvent->touch.y;
    return pos;
}

double *TouchEventArgs::axes() const { return (double *)this->_gtkEvent->touch.axes; }
GdkModifierType TouchEventArgs::state() const { return (GdkModifierType)this->_gtkEvent->touch.state; }
bool TouchEventArgs::emulatingPointer() const { return this->_gtkEvent->touch.emulating_pointer; }

DoublePosition TouchEventArgs::pointerPositionOnRoot() const
{
    DoublePosition pos;
    pos.X = this->_gtkEvent->touch.x_root;
    pos.Y = this->_gtkEvent->touch.y_root;
    return pos;
}

KeyEventArgs::KeyEventArgs(GdkEvent *keyEvent) : EventArgs(keyEvent){}

uint KeyEventArgs::time() const { return (uint)this->_gtkEvent->key.time; }
GdkModifierType KeyEventArgs::state() const { return (GdkModifierType)this->_gtkEvent->key.state; }
uint KeyEventArgs::key() const { return (uint)this->_gtkEvent->key.keyval; }
byte KeyEventArgs::group() const { return (byte)this->_gtkEvent->key.group; }
ushort KeyEventArgs::hardwareKeycode() const { return (ushort)this->_gtkEvent->key.hardware_keycode; }
uint KeyEventArgs::isModifier() const { return (uint)this->_gtkEvent->key.is_modifier; }
ScrollEventArgs::ScrollEventArgs(GdkEvent *scrollEvent) : EventArgs(scrollEvent){}
uint ScrollEventArgs::time() const { return (uint)this->_gtkEvent->scroll.time; }

DoublePosition ScrollEventArgs::pointerPosition() const
{
    DoublePosition pos;
    pos.X = this->_gtkEvent->scroll.x;
    pos.Y = this->_gtkEvent->scroll.y;
    return pos;
}

GdkModifierType ScrollEventArgs::state() const { return (GdkModifierType)this->_gtkEvent->scroll.state;  }
GdkScrollDirection ScrollEventArgs::direction() const { return (GdkScrollDirection)this->_gtkEvent->scroll.direction;  }

DoublePosition ScrollEventArgs::pointerPositionOnRoot() const
{
    DoublePosition pos;
    pos.X = this->_gtkEvent->scroll.x_root;
    pos.Y = this->_gtkEvent->scroll.y_root;
    return pos;
}

DoublePosition ScrollEventArgs::delta() const
{
    if(this->direction() == GDK_SCROLL_SMOOTH){
        DoublePosition pos;
        pos.X = this->_gtkEvent->scroll.delta_x;
        pos.Y = this->_gtkEvent->scroll.delta_y;
        return pos;
    } else {
        DoublePosition pos;
        pos.X = 0.0;
        pos.Y = 0.0;
        return pos;
    }
}

MotionEventArgs::MotionEventArgs(GdkEvent *motionEvent) : EventArgs(motionEvent) {}
uint MotionEventArgs::time() const { return (uint)this->_gtkEvent->motion.time; }

DoublePosition MotionEventArgs::pointerPosition() const
{
    DoublePosition pos;
    pos.X = this->_gtkEvent->motion.x;
    pos.Y = this->_gtkEvent->motion.y;
    return pos;
}

double *MotionEventArgs::axes() const { return (double *)this->_gtkEvent->motion.axes; }
GdkModifierType MotionEventArgs::state() const { return (GdkModifierType)this->_gtkEvent->motion.state; }

DoublePosition MotionEventArgs::pointerPositionOnRoot() const
{
    DoublePosition pos;
    pos.X = this->_gtkEvent->motion.x_root;
    pos.Y = this->_gtkEvent->motion.y_root;
    return pos;
}

ExposeEventArgs::ExposeEventArgs(GdkEvent *exposeEvent) : EventArgs(exposeEvent) {}
GdkRectangle ExposeEventArgs::area() const { return this->_gtkEvent->expose.area; }

int ExposeEventArgs::count() const { return this->_gtkEvent->expose.count; }
bool ExposeEventArgs::isExpose() { return this->type() == GDK_EXPOSE; }
bool ExposeEventArgs::isDamage() { return this->type() == GDK_DAMAGE; }
CrossingEventArgs::CrossingEventArgs(GdkEvent *crossingEvent) : EventArgs(crossingEvent) {}
uint CrossingEventArgs::time() const { return (uint)this->_gtkEvent->crossing.time; }

DoublePosition CrossingEventArgs::pointerPosition() const
{
    DoublePosition pos;
    pos.X = this->_gtkEvent->crossing.x;
    pos.Y = this->_gtkEvent->crossing.y;
    return pos;
}

DoublePosition CrossingEventArgs::pointerPositionOnRoot() const
{
    DoublePosition pos;
    pos.X = this->_gtkEvent->crossing.x_root;
    pos.Y = this->_gtkEvent->crossing.y_root;
    return pos;
}

UiWindow *CrossingEventArgs::subWindow() const
{
    return (UiWindow *)this->_gtkEvent->crossing.subwindow;
}

GdkCrossingMode CrossingEventArgs::mode() const { return this->_gtkEvent->crossing.mode; }
GdkNotifyType CrossingEventArgs::detail() const { return this->_gtkEvent->crossing.detail; }
bool CrossingEventArgs::focus() const { return this->_gtkEvent->crossing.focus; }
GdkModifierType CrossingEventArgs::state() const { return (GdkModifierType)this->_gtkEvent->crossing.state; }
ConfigureEventArgs::ConfigureEventArgs(GdkEvent *configureEvent) : EventArgs(configureEvent) {}

Position ConfigureEventArgs::windowPosition() const
{
    Position pos;
    pos.X = this->_gtkEvent->configure.x;
    pos.Y = this->_gtkEvent->configure.y;
    return pos;
}

Size ConfigureEventArgs::newSize() const
{
    Size s;
    s.Height = this->_gtkEvent->configure.height;
    s.Width = this->_gtkEvent->configure.width;
    return s;
}

PropertyEventArgs::PropertyEventArgs(GdkEvent *propertyEvent) : EventArgs(propertyEvent){}
Atom PropertyEventArgs::atom() const { return Atom(this->_gtkEvent->property.atom); }
uint PropertyEventArgs::time() const { return (uint)this->_gtkEvent->property.time; }
bool PropertyEventArgs::isDeleted() const { return this->_gtkEvent->property.state == GDK_PROPERTY_DELETE; }
FocusChangedEventArgs::FocusChangedEventArgs(GdkEvent *focusEvent) : EventArgs(focusEvent) {}
bool FocusChangedEventArgs::in() const { return (bool)this->_gtkEvent->focus_change.in; }
SelectionEventArgs::SelectionEventArgs(GdkEvent *selectionEvent) : EventArgs(selectionEvent){}
Atom SelectionEventArgs::selection() const { return Atom(this->_gtkEvent->selection.selection); }
Atom SelectionEventArgs::target() const { return Atom(this->_gtkEvent->selection.target); }
Atom SelectionEventArgs::property() const { return Atom(this->_gtkEvent->selection.property); }
uint SelectionEventArgs::time() const { return (uint)this->_gtkEvent->selection.time; }

UiWindow *SelectionEventArgs::requestor() const
{
    if(this->_gtkEvent->selection.requestor == NULL)
        return nullptr;
    return (UiWindow *)this->_gtkEvent->selection.requestor;
}

WindowStateEventArgs::WindowStateEventArgs(GdkEvent *windowStateEvent) : EventArgs(windowStateEvent){}
GdkWindowState WindowStateEventArgs::changedMask() const { return this->_gtkEvent->window_state.changed_mask; }
GdkWindowState WindowStateEventArgs::newState() const { return this->_gtkEvent->window_state.new_window_state; }
SettingEventArgs::SettingEventArgs(GdkEvent *settingEvent) : EventArgs(settingEvent) {}
GdkSettingAction SettingEventArgs::action() const { return this->_gtkEvent->setting.action; }
bool SettingEventArgs::isNew() const { return this->action() == GDK_SETTING_ACTION_NEW; }
bool SettingEventArgs::isChanged() const { return this->action() == GDK_SETTING_ACTION_CHANGED;  }
bool SettingEventArgs::isDeleted() const { return this->action() == GDK_SETTING_ACTION_DELETED;  }
String16 SettingEventArgs::name() const { return String16(this->_gtkEvent->setting.name); }
OwnerChangeEventArgs::OwnerChangeEventArgs(GdkEvent *ownerChangeEvent) : EventArgs(ownerChangeEvent) {}

UiWindow *OwnerChangeEventArgs::newOwner() const
{
    if(this->_gtkEvent->owner_change.owner == NULL)
        return nullptr;
    return (UiWindow *)this->_gtkEvent->owner_change.owner;
}

GdkOwnerChange OwnerChangeEventArgs::reason() const { return this->_gtkEvent->owner_change.reason; }
Atom OwnerChangeEventArgs::selection() const { return Atom(this->_gtkEvent->owner_change.selection); }
uint OwnerChangeEventArgs::time() const { return (uint)this->_gtkEvent->owner_change.time; }
uint OwnerChangeEventArgs::selectionTime() const { return (uint)this->_gtkEvent->owner_change.selection_time; }
GrabBrokenEventArgs::GrabBrokenEventArgs(GdkEvent *grabBrokenEvent) : EventArgs(grabBrokenEvent) {}
bool GrabBrokenEventArgs::isKeyboard() const { return this->_gtkEvent->grab_broken.keyboard; }
bool GrabBrokenEventArgs::isImplicit() const { return this->_gtkEvent->grab_broken.implicit; }

UiWindow *GrabBrokenEventArgs::grabWindow() const
{
    if(this->_gtkEvent->grab_broken.grab_window == NULL)
        return nullptr;
    return (UiWindow *)this->_gtkEvent->grab_broken.grab_window;
}

ProximityEventArgs::ProximityEventArgs(GdkEvent *proxEvent) : EventArgs(proxEvent) {}
uint ProximityEventArgs::time() const { return (uint)this->_gtkEvent->proximity.time; }
Device *ProximityEventArgs::device() const { return (Device *)this->_gtkEvent->proximity.device; }
