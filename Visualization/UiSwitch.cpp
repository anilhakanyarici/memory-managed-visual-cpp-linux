#include "UiSwitch.h"

Delegate(StaticSignalMethod, void, BaseWidget *, EventArgs *);
Delegate(InstanceSignalMethod, void, void *, BaseWidget *, EventArgs *);
Delegate(StaticSignalMethod_bool, void, BaseWidget *, bool, EventArgs *);
Delegate(InstanceSignalMethod_bool, void, void *, BaseWidget *, bool, EventArgs *);

RawSignal UiSwitch::Signals::Activate(SignalCallback eventMethod, void *instance, void *userData)
{
    VSignal *s = new VSignal();
    s->eventMethod = (void *)eventMethod;
    s->userData = userData;
    s->instance = instance;
    s->signalName = "activate";
    void (*gtkmethod) (GtkWidget *, gpointer) = [](GtkWidget *sender, gpointer g) -> void{
        VSignal *signal = (VSignal *)g;
        EventArgs *eArgs = new EventArgs(nullptr);
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
        delete eArgs;
    };
    s->callBack = G_CALLBACK(gtkmethod);
    return s;
}

RawSignal UiSwitch::Signals::StateSet(SignalCallback eventMethod, void *instance, void *userData)
{
    VSignal *s = new VSignal();
    s->eventMethod = (void *)eventMethod;
    s->userData = userData;
    s->instance = instance;
    s->signalName = "state-set";
    bool (*gtkmethod) (GtkWidget *, bool, gpointer) = [](GtkWidget *sender, bool grabbed, gpointer g) -> bool{
        VSignal *signal = (VSignal *)g;
        EventArgs *eArgs = new EventArgs(nullptr);
        eArgs->CanStopHandlers = true;
        signal->args = eArgs;
        signal->args->EventSignal = signal;
        signal->args->UserData = signal->userData;
        if(signal->instance == nullptr){
            StaticSignalMethod_bool ssm = (StaticSignalMethod_bool)signal->eventMethod;
            ssm((BaseWidget *)sender, grabbed, signal->args);
        } else {
            InstanceSignalMethod_bool ism = (InstanceSignalMethod_bool)signal->eventMethod;
            ism(signal->instance, (BaseWidget *)sender, grabbed, signal->args);
        }
        bool stopHandlers = eArgs->StopOtherHandlers;
        delete eArgs;
        return stopHandlers;
    };
    s->callBack = G_CALLBACK(gtkmethod);
    return s;
}

UiSwitch *UiSwitch::New()
{
    return (UiSwitch *)gtk_switch_new();
}

bool UiSwitch::active() const { return gtk_switch_get_active(GTK_SWITCH(this)); }
void UiSwitch::active(bool a) { gtk_switch_set_active(GTK_SWITCH(this), a); }
bool UiSwitch::state() const { return gtk_switch_get_state(GTK_SWITCH(this)); }
void UiSwitch::state(bool a) { gtk_switch_set_state(GTK_SWITCH(this), a); }
