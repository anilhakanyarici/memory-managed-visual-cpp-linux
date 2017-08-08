#include "UiSpinButton.h"

Delegate(StaticSignalMethod, void, BaseWidget *, EventArgs *);
Delegate(InstanceSignalMethod, void, void *, BaseWidget *, EventArgs *);
Delegate(StaticSignalMethod_GtkScrType, void, BaseWidget *, GtkScrollType, EventArgs *);
Delegate(InstanceSignalMethod_GtkScrType, void, void *, BaseWidget *, GtkScrollType, EventArgs *);
Delegate(StaticSignalMethod_Double, void, BaseWidget *, double, EventArgs *);
Delegate(InstanceSignalMethod_Double, void, void *, BaseWidget *, double, EventArgs *);

UiSpinButton *UiSpinButton::New(Adjustment *adj, double climbRate, double precision)
{
    return (UiSpinButton *)gtk_spin_button_new(GTK_ADJUSTMENT(adj), climbRate, precision);
}

UiSpinButton *UiSpinButton::New(double min, double max, double step)
{
    return (UiSpinButton *)gtk_spin_button_new_with_range(min, max, step);
}

Adjustment *UiSpinButton::adjustment() const { return (Adjustment *)(gtk_spin_button_get_adjustment(GTK_SPIN_BUTTON(this))); }

void UiSpinButton::adjustment(Adjustment *v) const { gtk_spin_button_set_adjustment(GTK_SPIN_BUTTON(this), GTK_ADJUSTMENT(v)); }

uint UiSpinButton::precision() const { return gtk_spin_button_get_digits(GTK_SPIN_BUTTON(this)); }

void UiSpinButton::precision(uint p) { gtk_spin_button_set_digits(GTK_SPIN_BUTTON(this), p); }

double UiSpinButton::step() const {
    double step, page;
    gtk_spin_button_get_increments(GTK_SPIN_BUTTON(this), &step, &page);
    return step;
}

void UiSpinButton::step(double s){
    double step, page;
    gtk_spin_button_get_increments(GTK_SPIN_BUTTON(this), &step, &page);
    gtk_spin_button_set_increments(GTK_SPIN_BUTTON(this), s, page);
}

double UiSpinButton::page() const {
    double step, page;
    gtk_spin_button_get_increments(GTK_SPIN_BUTTON(this), &step, &page);
    return page;
}

void UiSpinButton::page(double p){
    double step, page;
    gtk_spin_button_get_increments(GTK_SPIN_BUTTON(this), &step, &page);
    gtk_spin_button_set_increments(GTK_SPIN_BUTTON(this), step, p);
}

double UiSpinButton::minimumValue() const{
    double min, max;
    gtk_spin_button_get_range(GTK_SPIN_BUTTON(this), &min, &max);
    return min;
}

void UiSpinButton::minimumValue(double m){
    double min, max;
    gtk_spin_button_get_range(GTK_SPIN_BUTTON(this), &min, &max);
    gtk_spin_button_set_range(GTK_SPIN_BUTTON(this), m, max);
}

double UiSpinButton::maximumValue() const{
    double min, max;
    gtk_spin_button_get_range(GTK_SPIN_BUTTON(this), &min, &max);
    return max;
}

void UiSpinButton::maximumValue(double m){
    double min, max;
    gtk_spin_button_get_range(GTK_SPIN_BUTTON(this), &min, &max);
    gtk_spin_button_set_range(GTK_SPIN_BUTTON(this), min, m);
}

double UiSpinButton::value() const { return gtk_spin_button_get_value(GTK_SPIN_BUTTON(this)); }
void UiSpinButton::value(double d) { gtk_spin_button_set_value(GTK_SPIN_BUTTON(this), d); }
GtkSpinButtonUpdatePolicy UiSpinButton::updatePolicy() const { return gtk_spin_button_get_update_policy(GTK_SPIN_BUTTON(this)); }
void UiSpinButton::updatePolicy(GtkSpinButtonUpdatePolicy p) { gtk_spin_button_set_update_policy(GTK_SPIN_BUTTON(this), p); }
bool UiSpinButton::isNumeric() const { return gtk_spin_button_get_numeric(GTK_SPIN_BUTTON(this)); }
void UiSpinButton::isNumeric(bool b) { gtk_spin_button_set_numeric(GTK_SPIN_BUTTON(this), b); }
bool UiSpinButton::wrap() const { return gtk_spin_button_get_wrap(GTK_SPIN_BUTTON(this)); }
void UiSpinButton::wrap(bool w){ gtk_spin_button_set_wrap(GTK_SPIN_BUTTON(this), w); }
bool UiSpinButton::snapToTicks() const { return gtk_spin_button_get_snap_to_ticks(GTK_SPIN_BUTTON(this)); }
void UiSpinButton::snapToTicks(bool b) const { return gtk_spin_button_set_snap_to_ticks(GTK_SPIN_BUTTON(this), b); }

void UiSpinButton::Configure(Adjustment *adj, double climbRate, double precision) { gtk_spin_button_configure(GTK_SPIN_BUTTON(this), GTK_ADJUSTMENT(adj), climbRate, precision); }
void UiSpinButton::Spin(GtkSpinType direction, double increment) { gtk_spin_button_spin(GTK_SPIN_BUTTON(this), direction, increment); }
void UiSpinButton::Update() { gtk_spin_button_update(GTK_SPIN_BUTTON(this)); }

RawSignal UiSpinButton::Signals::ChangeValue(SignalCallback eventMethod, void *instance, void *userData)
{
    VSignal *s = new VSignal();
    s->eventMethod = (void *)eventMethod;
    s->userData = userData;
    s->instance = instance;
    s->signalName = "change-value";
    void (*gtkmethod) (GtkWidget *, GtkScrollType, gpointer) = [](GtkWidget *sender, GtkScrollType scr, gpointer g) -> void{
        VSignal *signal = (VSignal *)g;
        EventArgs *eArgs = new EventArgs(nullptr);
        signal->args = eArgs;
        signal->args->EventSignal = signal;
        signal->args->UserData = signal->userData;
        if(signal->instance == nullptr){
            StaticSignalMethod_GtkScrType ssm = (StaticSignalMethod_GtkScrType)signal->eventMethod;
            ssm((BaseWidget *)sender, scr, signal->args);
        } else {
            InstanceSignalMethod_GtkScrType ism = (InstanceSignalMethod_GtkScrType)signal->eventMethod;
            ism(signal->instance, (BaseWidget *)sender, scr, signal->args);
        }
        delete eArgs;
    };
    s->callBack = G_CALLBACK(gtkmethod);
    return s;
}

RawSignal UiSpinButton::Signals::Input(SignalCallback eventMethod, void *instance, void *userData)
{
    VSignal *s = new VSignal();
    s->eventMethod = (void *)eventMethod;
    s->userData = userData;
    s->instance = instance;
    s->signalName = "input";
    void (*gtkmethod) (GtkWidget *, gpointer, gpointer) = [](GtkWidget *sender, gpointer new_val, gpointer g) -> void{
        VSignal *signal = (VSignal *)g;
        EventArgs *eArgs = new EventArgs(nullptr);
        signal->args = eArgs;
        signal->args->EventSignal = signal;
        signal->args->UserData = signal->userData;

        if(signal->instance == nullptr){
            StaticSignalMethod_Double ssm = (StaticSignalMethod_Double)signal->eventMethod;
            ssm((BaseWidget *)sender, *((double *)new_val), signal->args);
        } else {
            InstanceSignalMethod_Double ism = (InstanceSignalMethod_Double)signal->eventMethod;
            ism(signal->instance, (BaseWidget *)sender, *((double *)new_val), signal->args);
        }
        delete eArgs;
    };
    s->callBack = G_CALLBACK(gtkmethod);
    return s;
}

RawSignal UiSpinButton::Signals::Output(SignalCallback eventMethod, void *instance, void *userData)
{
    VSignal *s = new VSignal();
    s->eventMethod = (void *)eventMethod;
    s->userData = userData;
    s->instance = instance;
    s->signalName = "output";
    bool (*gtkmethod) (GtkWidget *, gpointer) = [](GtkWidget *sender, gpointer g) -> bool{
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
        return true;
    };
    s->callBack = G_CALLBACK(gtkmethod);
    return s;
}

RawSignal UiSpinButton::Signals::ValueChanged(SignalCallback eventMethod, void *instance, void *userData)
{
    VSignal *s = new VSignal();
    s->eventMethod = (void *)eventMethod;
    s->userData = userData;
    s->instance = instance;
    s->signalName = "value-changed";
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

RawSignal UiSpinButton::Signals::Wrapped(SignalCallback eventMethod, void *instance, void *userData)
{
    VSignal *s = new VSignal();
    s->eventMethod = (void *)eventMethod;
    s->userData = userData;
    s->instance = instance;
    s->signalName = "wrapped";
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
