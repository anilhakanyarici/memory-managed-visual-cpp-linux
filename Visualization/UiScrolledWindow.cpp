#include "UiScrolledWindow.h"

Delegate(StaticSignalMethod_GtkPosType, void, BaseWidget *, GtkPositionType, EventArgs *);
Delegate(InstanceSignalMethod_GtkPosType, void, void *, BaseWidget *, GtkPositionType, EventArgs *);
Delegate(StaticSignalMethod_GtkDirType, void, BaseWidget *, GtkDirectionType, EventArgs *);
Delegate(InstanceSignalMethod_GtkDirType, void, void *, BaseWidget *, GtkDirectionType, EventArgs *);
Delegate(StaticSignalMethod_GtkScrType_bool, void, BaseWidget *, GtkScrollType, bool, EventArgs *);
Delegate(InstanceSignalMethod_GtkScrType_bool, void, void *, BaseWidget *, GtkScrollType, bool, EventArgs *);

UiScrollbar *UiScrollbar::New(GtkOrientation orientation, Adjustment *adj)
{
    return (UiScrollbar *)gtk_scrollbar_new(orientation, GTK_ADJUSTMENT(adj));
}

UiScrolledWindow *UiScrolledWindow::New(Adjustment *h, Adjustment *v)
{
    return (UiScrolledWindow *)gtk_scrolled_window_new(GTK_ADJUSTMENT(h), GTK_ADJUSTMENT(v));
}

UiScrollbar *UiScrolledWindow::getHScrollbar() const { return (UiScrollbar *)gtk_scrolled_window_get_hscrollbar(GTK_SCROLLED_WINDOW(this)); }
UiScrollbar *UiScrolledWindow::getVScrollbar() const { return (UiScrollbar *)gtk_scrolled_window_get_vscrollbar(GTK_SCROLLED_WINDOW(this)); }

GtkPolicyType UiScrolledWindow::getHPolicy() const
{
    GtkPolicyType h, v;
    gtk_scrolled_window_get_policy(GTK_SCROLLED_WINDOW(this), &h, &v);
    return h;
}

GtkPolicyType UiScrolledWindow::getVPolicy() const
{
    GtkPolicyType h, v;
    gtk_scrolled_window_get_policy(GTK_SCROLLED_WINDOW(this), &h, &v);
    return v;
}

GtkCornerType UiScrolledWindow::placement() const { return gtk_scrolled_window_get_placement(GTK_SCROLLED_WINDOW(this)); }
void UiScrolledWindow::placement(GtkCornerType p) { gtk_scrolled_window_set_placement(GTK_SCROLLED_WINDOW(this), p); }
GtkShadowType UiScrolledWindow::shadowType() const { return gtk_scrolled_window_get_shadow_type(GTK_SCROLLED_WINDOW(this)); }

void UiScrolledWindow::shadowType(GtkShadowType p) { gtk_scrolled_window_set_shadow_type(GTK_SCROLLED_WINDOW(this), p); }
bool UiScrolledWindow::kineticScrolling() const { return gtk_scrolled_window_get_kinetic_scrolling(GTK_SCROLLED_WINDOW(this)); }
void UiScrolledWindow::kineticScrolling(bool p) { gtk_scrolled_window_set_kinetic_scrolling(GTK_SCROLLED_WINDOW(this), p); }
bool UiScrolledWindow::captureButtonPress() const { return gtk_scrolled_window_get_capture_button_press(GTK_SCROLLED_WINDOW(this)); }
void UiScrolledWindow::captureButtonPress(bool p) { gtk_scrolled_window_set_capture_button_press(GTK_SCROLLED_WINDOW(this), p); }
bool UiScrolledWindow::overlayScrolling() const { return gtk_scrolled_window_get_overlay_scrolling(GTK_SCROLLED_WINDOW(this)); }
void UiScrolledWindow::overlayScrolling(bool p) { gtk_scrolled_window_set_overlay_scrolling(GTK_SCROLLED_WINDOW(this), p); }
int UiScrolledWindow::minContentWidth() const { return gtk_scrolled_window_get_min_content_width(GTK_SCROLLED_WINDOW(this)); }
void UiScrolledWindow::minContentWidth(int p) { gtk_scrolled_window_set_min_content_width(GTK_SCROLLED_WINDOW(this), p); }
int UiScrolledWindow::minContentHeight() const { return gtk_scrolled_window_get_min_content_height(GTK_SCROLLED_WINDOW(this)); }
void UiScrolledWindow::minContentHeight(int p) { gtk_scrolled_window_set_min_content_height(GTK_SCROLLED_WINDOW(this), p); }

void UiScrolledWindow::SetPolicy(GtkPolicyType h, GtkPolicyType v)
{
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(this), h, v);
}
void UiScrolledWindow::UnsetPlacement() { gtk_scrolled_window_unset_placement(GTK_SCROLLED_WINDOW(this)); }

RawSignal UiScrolledWindow::Signals::EdgeOvershot(SignalCallback eventMethod, void *instance, void *userData)
{
    VSignal *s = new VSignal();
    s->eventMethod = (void *)eventMethod;
    s->userData = userData;
    s->instance = instance;
    s->signalName = "edge-overshot";
    void (*gtkmethod) (GtkWidget *, GtkPositionType, gpointer) = [](GtkWidget *sender, GtkPositionType type, gpointer g) -> void{
        VSignal *signal = (VSignal *)g;
        EventArgs *eArgs = new EventArgs(nullptr);

        signal->args = eArgs;
        signal->args->EventSignal = signal;
        signal->args->UserData = signal->userData;
        if(signal->instance == nullptr){
            StaticSignalMethod_GtkPosType ssm = (StaticSignalMethod_GtkPosType)signal->eventMethod;
            ssm((BaseWidget *)sender, type, signal->args);
        } else {
            InstanceSignalMethod_GtkPosType ism = (InstanceSignalMethod_GtkPosType)signal->eventMethod;
            ism(signal->instance, (BaseWidget *)sender, type, signal->args);
        }
        delete eArgs;
    };
    s->callBack = G_CALLBACK(gtkmethod);
    return s;
}

RawSignal UiScrolledWindow::Signals::EdgeReached(SignalCallback eventMethod, void *instance, void *userData)
{
    VSignal *s = new VSignal();
    s->eventMethod = (void *)eventMethod;
    s->userData = userData;
    s->instance = instance;
    s->signalName = "edge-reached";
    void (*gtkmethod) (GtkWidget *, GtkPositionType, gpointer) = [](GtkWidget *sender, GtkPositionType type, gpointer g) -> void{
        VSignal *signal = (VSignal *)g;
        EventArgs *eArgs = new EventArgs(nullptr);

        signal->args = eArgs;
        signal->args->EventSignal = signal;
        signal->args->UserData = signal->userData;
        if(signal->instance == nullptr){
            StaticSignalMethod_GtkPosType ssm = (StaticSignalMethod_GtkPosType)signal->eventMethod;
            ssm((BaseWidget *)sender, type, signal->args);
        } else {
            InstanceSignalMethod_GtkPosType ism = (InstanceSignalMethod_GtkPosType)signal->eventMethod;
            ism(signal->instance, (BaseWidget *)sender, type, signal->args);
        }
        delete eArgs;
    };
    s->callBack = G_CALLBACK(gtkmethod);
    return s;
}

RawSignal UiScrolledWindow::Signals::MoveFocusOut(SignalCallback eventMethod, void *instance, void *userData)
{
    VSignal *s = new VSignal();
    s->eventMethod = (void *)eventMethod;
    s->userData = userData;
    s->instance = instance;
    s->signalName = "move-focus-out";
    void (*gtkmethod) (GtkWidget *, GtkDirectionType, gpointer) = [](GtkWidget *sender, GtkDirectionType type, gpointer g) -> void{
        VSignal *signal = (VSignal *)g;
        EventArgs *eArgs = new EventArgs(nullptr);

        signal->args = eArgs;
        signal->args->EventSignal = signal;
        signal->args->UserData = signal->userData;
        if(signal->instance == nullptr){
            StaticSignalMethod_GtkDirType ssm = (StaticSignalMethod_GtkDirType)signal->eventMethod;
            ssm((BaseWidget *)sender, type, signal->args);
        } else {
            InstanceSignalMethod_GtkDirType ism = (InstanceSignalMethod_GtkDirType)signal->eventMethod;
            ism(signal->instance, (BaseWidget *)sender, type, signal->args);
        }
        delete eArgs;
    };
    s->callBack = G_CALLBACK(gtkmethod);
    return s;
}

RawSignal UiScrolledWindow::Signals::ScrollChild(SignalCallback eventMethod, void *instance, void *userData)
{
    VSignal *s = new VSignal();
    s->eventMethod = (void *)eventMethod;
    s->userData = userData;
    s->instance = instance;
    s->signalName = "scroll-child";
    bool (*gtkmethod) (GtkWidget *, GtkScrollType, bool, gpointer) = [](GtkWidget *sender, GtkScrollType type, bool horizontal, gpointer g) -> bool{
        VSignal *signal = (VSignal *)g;
        EventArgs *eArgs = new EventArgs(nullptr);
        eArgs->CanStopHandlers = true;
        signal->args = eArgs;
        signal->args->EventSignal = signal;
        signal->args->UserData = signal->userData;
        if(signal->instance == nullptr){
            StaticSignalMethod_GtkScrType_bool ssm = (StaticSignalMethod_GtkScrType_bool)signal->eventMethod;
            ssm((BaseWidget *)sender, type, horizontal, signal->args);
        } else {
            InstanceSignalMethod_GtkScrType_bool ism = (InstanceSignalMethod_GtkScrType_bool)signal->eventMethod;
            ism(signal->instance, (BaseWidget *)sender, type, horizontal, signal->args);
        }
        bool stopHandlers = eArgs->StopOtherHandlers;
        delete eArgs;
        return stopHandlers;
    };
    s->callBack = G_CALLBACK(gtkmethod);
    return s;
}
