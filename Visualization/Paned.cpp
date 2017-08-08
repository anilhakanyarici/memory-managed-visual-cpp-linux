#include "Paned.h"

Delegate(StaticSignalMethod, void, BaseWidget *, EventArgs *);
Delegate(InstanceSignalMethod, void, void *, BaseWidget *, EventArgs *);
Delegate(StaticSignalMethod_bool, void, BaseWidget *, bool, EventArgs *);
Delegate(InstanceSignalMethod_bool, void, void *, BaseWidget *, bool, EventArgs *);
Delegate(StaticSignalMethod_ScrType, void, BaseWidget *, GtkScrollType, EventArgs *);
Delegate(InstanceSignalMethod_ScrType, void, void *, BaseWidget *, GtkScrollType, EventArgs *);

Paned *Paned::New(GtkOrientation orientation)
{
    return (Paned *)gtk_paned_new(orientation);
}

BaseWidget *Paned::child1() const { return (BaseWidget *)gtk_paned_get_child1(GTK_PANED(this)); }
void Paned::child1(BaseWidget *widget) { gtk_paned_add1(GTK_PANED(this), GTK_WIDGET(widget)); }
BaseWidget *Paned::child2() const { return (BaseWidget *)gtk_paned_get_child2(GTK_PANED(this)); }
void Paned::child2(BaseWidget *widget) { gtk_paned_add2(GTK_PANED(this), GTK_WIDGET(widget)); }
int Paned::position() const { return gtk_paned_get_position(GTK_PANED(this)); }
void Paned::position(int pos) { gtk_paned_set_position(GTK_PANED(this), pos); }
bool Paned::wideHandle() const { return gtk_paned_get_wide_handle(GTK_PANED(this)); }
void Paned::wideHandle(bool p) { gtk_paned_set_wide_handle(GTK_PANED(this), p); }
UiWindow *Paned::getHandleWindow() const { return (UiWindow *)gtk_paned_get_handle_window(GTK_PANED(this)); }

void Paned::Pack1(BaseWidget *child, bool resize, bool shrink) { gtk_paned_pack1(GTK_PANED(this), GTK_WIDGET(child), resize, shrink); }
void Paned::Pack2(BaseWidget *child, bool resize, bool shrink) { gtk_paned_pack2(GTK_PANED(this), GTK_WIDGET(child), resize, shrink); }

RawSignal Paned::Signals::AcceptPosition(SignalCallback eventMethod, void *instance, void *userData)
{
    VSignal *s = new VSignal();
    s->eventMethod = (void *)eventMethod;
    s->userData = userData;
    s->instance = instance;
    s->signalName = "accept-position";
    bool (*gtkmethod) (GtkWidget *, gpointer) = [](GtkWidget *sender, gpointer g) -> bool{
        VSignal *signal = (VSignal *)g;
        EventArgs *eArgs = new EventArgs(nullptr);
        eArgs->CanStopHandlers = true;
        signal->args = eArgs;
        signal->args->EventSignal = signal;
        signal->args->UserData = signal->userData;
        if(signal->instance == nullptr){
            StaticSignalMethod ssm = (StaticSignalMethod)signal->eventMethod;
            ssm((BaseWidget *)sender, signal->args);
        } else {
            InstanceSignalMethod ism = (InstanceSignalMethod)signal->eventMethod;
            ism(signal->instance, (BaseWidget *)sender, signal->args);
        }
        bool stopHandlers = eArgs->StopOtherHandlers;
        delete eArgs;
        return stopHandlers;
    };
    s->callBack = G_CALLBACK(gtkmethod);
    return s;
}

RawSignal Paned::Signals::CancelPosition(SignalCallback eventMethod, void *instance, void *userData)
{
    VSignal *s = new VSignal();
    s->eventMethod = (void *)eventMethod;
    s->userData = userData;
    s->instance = instance;
    s->signalName = "cancel-position";
    bool (*gtkmethod) (GtkWidget *, gpointer) = [](GtkWidget *sender, gpointer g) -> bool{
        VSignal *signal = (VSignal *)g;
        EventArgs *eArgs = new EventArgs(nullptr);
        eArgs->CanStopHandlers = true;
        signal->args = eArgs;
        signal->args->EventSignal = signal;
        signal->args->UserData = signal->userData;
        if(signal->instance == nullptr){
            StaticSignalMethod ssm = (StaticSignalMethod)signal->eventMethod;
            ssm((BaseWidget *)sender, signal->args);
        } else {
            InstanceSignalMethod ism = (InstanceSignalMethod)signal->eventMethod;
            ism(signal->instance, (BaseWidget *)sender, signal->args);
        }
        bool stopHandlers = eArgs->StopOtherHandlers;
        delete eArgs;
        return stopHandlers;
    };
    s->callBack = G_CALLBACK(gtkmethod);
    return s;
}

RawSignal Paned::Signals::CycleChildFocus(SignalCallback eventMethod, void *instance, void *userData)
{
    VSignal *s = new VSignal();
    s->eventMethod = (void *)eventMethod;
    s->userData = userData;
    s->instance = instance;
    s->signalName = "cycle-child-focus";
    bool (*gtkmethod) (GtkWidget *, bool, gpointer) = [](GtkWidget *sender, bool reversed, gpointer g) -> bool{
        VSignal *signal = (VSignal *)g;
        EventArgs *eArgs = new EventArgs(nullptr);
        eArgs->CanStopHandlers = true;
        signal->args = eArgs;
        signal->args->EventSignal = signal;
        signal->args->UserData = signal->userData;
        if(signal->instance == nullptr){
            StaticSignalMethod_bool ssm = (StaticSignalMethod_bool)signal->eventMethod;
            ssm((BaseWidget *)sender, reversed, signal->args);
        } else {
            InstanceSignalMethod_bool ism = (InstanceSignalMethod_bool)signal->eventMethod;
            ism(signal->instance, (BaseWidget *)sender, reversed, signal->args);
        }
        bool stopHandlers = eArgs->StopOtherHandlers;
        delete eArgs;
        return stopHandlers;
    };
    s->callBack = G_CALLBACK(gtkmethod);
    return s;
}

RawSignal Paned::Signals::CycleHandleFocus(SignalCallback eventMethod, void *instance, void *userData)
{
    VSignal *s = new VSignal();
    s->eventMethod = (void *)eventMethod;
    s->userData = userData;
    s->instance = instance;
    s->signalName = "cycle-handle-focus";
    bool (*gtkmethod) (GtkWidget *, bool, gpointer) = [](GtkWidget *sender, bool reversed, gpointer g) -> bool{
        VSignal *signal = (VSignal *)g;
        EventArgs *eArgs = new EventArgs(nullptr);
        eArgs->CanStopHandlers = true;
        signal->args = eArgs;
        signal->args->EventSignal = signal;
        signal->args->UserData = signal->userData;
        if(signal->instance == nullptr){
            StaticSignalMethod_bool ssm = (StaticSignalMethod_bool)signal->eventMethod;
            ssm((BaseWidget *)sender, reversed, signal->args);
        } else {
            InstanceSignalMethod_bool ism = (InstanceSignalMethod_bool)signal->eventMethod;
            ism(signal->instance, (BaseWidget *)sender, reversed, signal->args);
        }
        bool stopHandlers = eArgs->StopOtherHandlers;
        delete eArgs;
        return stopHandlers;
    };
    s->callBack = G_CALLBACK(gtkmethod);
    return s;
}

RawSignal Paned::Signals::MoveHandle(SignalCallback eventMethod, void *instance, void *userData)
{
    VSignal *s = new VSignal();
    s->eventMethod = (void *)eventMethod;
    s->userData = userData;
    s->instance = instance;
    s->signalName = "move-handle";
    bool (*gtkmethod) (GtkWidget *, GtkScrollType, gpointer) = [](GtkWidget *sender, GtkScrollType type, gpointer g) -> bool{
        VSignal *signal = (VSignal *)g;
        EventArgs *eArgs = new EventArgs(nullptr);
        eArgs->CanStopHandlers = true;
        signal->args = eArgs;
        signal->args->EventSignal = signal;
        signal->args->UserData = signal->userData;
        if(signal->instance == nullptr){
            StaticSignalMethod_ScrType ssm = (StaticSignalMethod_ScrType)signal->eventMethod;
            ssm((BaseWidget *)sender, type, signal->args);
        } else {
            InstanceSignalMethod_ScrType ism = (InstanceSignalMethod_ScrType)signal->eventMethod;
            ism(signal->instance, (BaseWidget *)sender, type, signal->args);
        }
        bool stopHandlers = eArgs->StopOtherHandlers;
        delete eArgs;
        return stopHandlers;
    };
    s->callBack = G_CALLBACK(gtkmethod);
    return s;
}

RawSignal Paned::Signals::ToggleHandleFocus(SignalCallback eventMethod, void *instance, void *userData)
{
    VSignal *s = new VSignal();
    s->eventMethod = (void *)eventMethod;
    s->userData = userData;
    s->instance = instance;
    s->signalName = "toggle-handle-focus";
    bool (*gtkmethod) (GtkWidget *, gpointer) = [](GtkWidget *sender, gpointer g) -> bool{
        VSignal *signal = (VSignal *)g;
        EventArgs *eArgs = new EventArgs(nullptr);
        eArgs->CanStopHandlers = true;
        signal->args = eArgs;
        signal->args->EventSignal = signal;
        signal->args->UserData = signal->userData;
        if(signal->instance == nullptr){
            StaticSignalMethod ssm = (StaticSignalMethod)signal->eventMethod;
            ssm((BaseWidget *)sender, signal->args);
        } else {
            InstanceSignalMethod ism = (InstanceSignalMethod)signal->eventMethod;
            ism(signal->instance, (BaseWidget *)sender, signal->args);
        }
        bool stopHandlers = eArgs->StopOtherHandlers;
        delete eArgs;
        return stopHandlers;
    };
    s->callBack = G_CALLBACK(gtkmethod);
    return s;
}
