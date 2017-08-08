#include "Display.h"
#include "EventArgs.h"
#include "../String16.h"
#include "DWindow.h"
#include "Device.h"

Delegate(StaticSignalMethod, void, VObject *, EventArgs *);
Delegate(InstanceSignalMethod, void, void *, VObject *, EventArgs *);
Delegate(StaticSignalMethod_bool, void, VObject *, bool, EventArgs *);
Delegate(InstanceSignalMethod_bool, void, void *, VObject *, bool, EventArgs *);

Display *Display::Open(const String16 &name)
{
    ByteArray utf8 = name.ToCString();
    return (Display *)gdk_display_open((const gchar *)utf8.data());
}
Display *Display::Default()
{
    return (Display *)gdk_display_get_default();
}

String16 Display::name() const { return String16((const char *)gdk_display_get_name(GDK_DISPLAY(this))); }
Screen *Display::defaultScreen() const { return (Screen *)gdk_display_get_default_screen(GDK_DISPLAY(this)); }
bool Display::isClosed() const { return gdk_display_is_closed(GDK_DISPLAY(this)); }
bool Display::hasPending() const { return gdk_display_has_pending(GDK_DISPLAY(this)); }
bool Display::supportsCursorColor() const { return gdk_display_supports_cursor_color(GDK_DISPLAY(this)); }
bool Display::supportsCursorAlpha() const { return gdk_display_supports_cursor_alpha(GDK_DISPLAY(this)); }
uint Display::cursorSize() const { return gdk_display_get_default_cursor_size(GDK_DISPLAY(this)); }
Size Display::maximalCursorSize() const { Size s; gdk_display_get_maximal_cursor_size(GDK_DISPLAY(this), (guint *)&s.Width, (guint *)&s.Height); return s; }
bool Display::supportsSelectionNotification() const { return gdk_display_supports_selection_notification(GDK_DISPLAY(this)); }
bool Display::supportsClipboardPersistence() const { return gdk_display_supports_clipboard_persistence(GDK_DISPLAY(this)); }
bool Display::supportsShapes() const { return gdk_display_supports_shapes(GDK_DISPLAY(this)); }
bool Display::supportsInputShapes() const { return gdk_display_supports_input_shapes(GDK_DISPLAY(this)); }

void Display::Beep() { gdk_display_beep(GDK_DISPLAY(this)); }
void Display::Close() { gdk_display_close(GDK_DISPLAY(this)); }
void Display::Flush() { gdk_display_flush(GDK_DISPLAY(this)); }
bool Display::RequestSelectionNotification(Atom selection) { return gdk_display_request_selection_notification(GDK_DISPLAY(this), selection._atom); }
bool Display::IsGrabbed(Device *dev) { return gdk_display_device_is_grabbed(GDK_DISPLAY(this), GDK_DEVICE(dev)); }
void Display::SetDoubleClickDistance(uint msec) { gdk_display_set_double_click_distance(GDK_DISPLAY(this), msec); }
void Display::SetDoubleClickTime(uint msec) { gdk_display_set_double_click_time(GDK_DISPLAY(this), msec); }
void Display::Sync() { gdk_display_sync(GDK_DISPLAY(this)); }

RawSignal Display::Signals::Closed(SignalCallback eventMethod, void *instance, void *userData)
{
    VSignal *s = new VSignal();
    s->eventMethod = (void *)eventMethod;
    s->userData = userData;
    s->instance = instance;
    s->signalName = "closed";
    void (*gtkmethod) (GdkDisplay *, bool, gpointer) = [](GdkDisplay *sender, bool isError, gpointer g) -> void{
        VSignal *signal = (VSignal *)g;
        EventArgs *eArgs = new EventArgs(nullptr);

        signal->args = eArgs;
        signal->args->EventSignal = signal;
        signal->args->UserData = signal->userData;
        if(signal->instance == nullptr){
            StaticSignalMethod_bool ssm = (StaticSignalMethod_bool)signal->eventMethod;
            ssm((Display *)sender, isError, signal->args);
        } else {
            InstanceSignalMethod_bool ism = (InstanceSignalMethod_bool)signal->eventMethod;
            ism(signal->instance, (Display *)sender, isError, signal->args);
        }
        delete eArgs;
    };
    s->callBack = G_CALLBACK(gtkmethod);
    return s;
}

RawSignal Display::Signals::Opened(SignalCallback eventMethod, void *instance, void *userData)
{
    VSignal *s = new VSignal();
    s->eventMethod = (void *)eventMethod;
    s->userData = userData;
    s->instance = instance;
    s->signalName = "opened";
    void (*gtkmethod) (GdkDisplay *, gpointer) = [](GdkDisplay *sender, gpointer g) -> void{
        VSignal *signal = (VSignal *)g;
        EventArgs *eArgs = new EventArgs(nullptr);

        signal->args = eArgs;
        signal->args->EventSignal = signal;
        signal->args->UserData = signal->userData;
        if(signal->instance == nullptr){
            StaticSignalMethod ssm = (StaticSignalMethod)signal->eventMethod;
            ssm((Display *)sender, signal->args);
        } else {
            InstanceSignalMethod ism = (InstanceSignalMethod)signal->eventMethod;
            ism(signal->instance, (Display *)sender, signal->args);
        }
        delete eArgs;
    };
    s->callBack = G_CALLBACK(gtkmethod);
    return s;
}


Cursor *Cursor::New(Display *disp, Pixelbuffer *pixbuf, int x, int y) { return (Cursor *)gdk_cursor_new_from_pixbuf(GDK_DISPLAY(disp), GDK_PIXBUF(pixbuf), x, y); }
Cursor *Cursor::New(Display *disp, CairoSurface *surface, double x, double y) { return (Cursor *)gdk_cursor_new_from_surface(GDK_DISPLAY(disp), (cairo_surface_t *)(surface), x, y); }
Cursor *Cursor::New(Display *disp, GdkCursorType type) { return (Cursor *) gdk_cursor_new_for_display(GDK_DISPLAY(disp), type); }

Cursor *Cursor::New(Display *disp, const String16 &name)
{
    ByteArray utf8 = name.ToCString();
    return (Cursor *)gdk_cursor_new_from_name(GDK_DISPLAY(disp), (const gchar *)utf8.data());
}

