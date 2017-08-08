#include "Screen.h"
#include "Display.h"
#include "Visual.h"
#include "DWindow.h"

Delegate(StaticSignalMethod, void, VObject *, EventArgs *);
Delegate(InstanceSignalMethod, void, void *, VObject *, EventArgs *);

RawSignal Screen::Signals::CompositedChanged(SignalCallback eventMethod, void *instance, void *userData)
{
    VSignal *s = new VSignal();
    s->eventMethod = (void *)eventMethod;
    s->userData = userData;
    s->instance = instance;
    s->signalName = "composited-changed";
    void (*gtkmethod) (GdkScreen *, gpointer) = [](GdkScreen *sender, gpointer g) -> void{
        VSignal *signal = (VSignal *)g;
        EventArgs *eArgs = new EventArgs(nullptr);

        signal->args = eArgs;
        signal->args->EventSignal = signal;
        signal->args->UserData = signal->userData;
        if(signal->instance == nullptr){
            StaticSignalMethod ssm = (StaticSignalMethod)signal->eventMethod;
            ssm((Screen *)sender, signal->args);
        } else {
            InstanceSignalMethod ism = (InstanceSignalMethod)signal->eventMethod;
            ism(signal->instance, (Screen *)sender, signal->args);
        }
        delete eArgs;
    };
    s->callBack = G_CALLBACK(gtkmethod);
    return s;
}

RawSignal Screen::Signals::MonitorsChanged(SignalCallback eventMethod, void *instance, void *userData)
{
    VSignal *s = new VSignal();
    s->eventMethod = (void *)eventMethod;
    s->userData = userData;
    s->instance = instance;
    s->signalName = "monitors-changed";
    void (*gtkmethod) (GdkScreen *, gpointer) = [](GdkScreen *sender, gpointer g) -> void{
        VSignal *signal = (VSignal *)g;
        EventArgs *eArgs = new EventArgs(nullptr);

        signal->args = eArgs;
        signal->args->EventSignal = signal;
        signal->args->UserData = signal->userData;
        if(signal->instance == nullptr){
            StaticSignalMethod ssm = (StaticSignalMethod)signal->eventMethod;
            ssm((Screen *)sender, signal->args);
        } else {
            InstanceSignalMethod ism = (InstanceSignalMethod)signal->eventMethod;
            ism(signal->instance, (Screen *)sender, signal->args);
        }
        delete eArgs;
    };
    s->callBack = G_CALLBACK(gtkmethod);
    return s;
}

RawSignal Screen::Signals::SizeChanged(SignalCallback eventMethod, void *instance, void *userData)
{
    VSignal *s = new VSignal();
    s->eventMethod = (void *)eventMethod;
    s->userData = userData;
    s->instance = instance;
    s->signalName = "size-changed";
    void (*gtkmethod) (GdkScreen *, gpointer) = [](GdkScreen *sender, gpointer g) -> void{
        VSignal *signal = (VSignal *)g;
        EventArgs *eArgs = new EventArgs(nullptr);

        signal->args = eArgs;
        signal->args->EventSignal = signal;
        signal->args->UserData = signal->userData;
        if(signal->instance == nullptr){
            StaticSignalMethod ssm = (StaticSignalMethod)signal->eventMethod;
            ssm((Screen *)sender, signal->args);
        } else {
            InstanceSignalMethod ism = (InstanceSignalMethod)signal->eventMethod;
            ism(signal->instance, (Screen *)sender, signal->args);
        }
        delete eArgs;
    };
    s->callBack = G_CALLBACK(gtkmethod);
    return s;
}

Screen *Screen::Default() { return (Screen *)gdk_screen_get_default(); }

Visual *Screen::getSystemVisual() const { return (Visual *)gdk_screen_get_system_visual(GDK_SCREEN(this)); }
Visual *Screen::getRGBAVisual() const { return (Visual *)gdk_screen_get_rgba_visual(GDK_SCREEN(this)); }
bool Screen::isComposited() const { return gdk_screen_is_composited(GDK_SCREEN(this)); }
double Screen::resolution() const { return gdk_screen_get_resolution(GDK_SCREEN(this)); }
void Screen::resolution(double dpi) { gdk_screen_set_resolution(GDK_SCREEN(this), dpi); }
DWindow *Screen::getRootWindow() const { return (DWindow *)gdk_screen_get_root_window(GDK_SCREEN(this)); }
Display *Screen::getDisplay() const { return (Display *)gdk_screen_get_display(GDK_SCREEN(this)); }

Array<Visual *> Screen::GetVisuals()
{
    GList* list = gdk_screen_list_visuals(GDK_SCREEN(this));
    guint len = g_list_length(list);
    Array<Visual *> visuals = Array<Visual *>(len);

    GList *curr = list;
    int i = 0;
    while(curr != NULL){
        visuals[i] = (Visual *)curr->data;
        curr = curr->next;
        i++;
    }
    g_list_free(list);
    return visuals;
}

Array<DWindow *> Screen::GetToplevelWindows()
{
    GList* list = gdk_screen_get_toplevel_windows(GDK_SCREEN(this));
    guint len = g_list_length(list);
    Array<DWindow *> windows = Array<DWindow *>(len);

    GList *curr = list;
    int i = 0;
    while(curr != NULL){
        windows[i] = (DWindow *)curr->data;
        curr = curr->next;
        i++;
    }
    g_list_free(list);
    return windows;
}

Array<DWindow *> Screen::GetWindowStack()
{
    GList* list = gdk_screen_get_window_stack(GDK_SCREEN(this));
    guint len = g_list_length(list);
    Array<DWindow *> windows = Array<DWindow *>(len);

    GList *curr = list;
    int i = 0;
    while(curr != NULL){
        windows[i] = (DWindow *)curr->data;
        curr = curr->next;
        i++;
    }
    g_list_free(list);
    return windows;
}
