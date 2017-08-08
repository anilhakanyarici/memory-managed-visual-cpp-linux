#include "BaseRange.h"

Delegate(StaticSignalMethod, void, BaseWidget *, EventArgs *);
Delegate(InstanceSignalMethod, void, void *, BaseWidget *, EventArgs *);
Delegate(StaticSignalMethod_Double, void, BaseWidget *, double, EventArgs *);
Delegate(InstanceSignalMethod_Double, void, void *, BaseWidget *, double, EventArgs *);
Delegate(StaticSignalMethod_ScrType, void, BaseWidget *, GtkScrollType, EventArgs *);
Delegate(InstanceSignalMethod_ScrType, void, void *, BaseWidget *, GtkScrollType, EventArgs *);
Delegate(StaticSignalMethod_ScrType_Double, void, BaseWidget *, GtkScrollType, double, EventArgs *);
Delegate(InstanceSignalMethod_ScrType_Double, void, void *, BaseWidget *, GtkScrollType, double, EventArgs *);

Adjustment *BaseRange::adjustment() const { return (Adjustment *)(gtk_range_get_adjustment(GTK_RANGE(this))); }
void BaseRange::adjustment(Adjustment *v) const { gtk_range_set_adjustment(GTK_RANGE(this), GTK_ADJUSTMENT(v)); }
double BaseRange::fillLevel() const { return gtk_range_get_fill_level(GTK_RANGE(this)); }
void BaseRange::fillLevel(double v) { gtk_range_set_fill_level(GTK_RANGE(this), v); }
bool BaseRange::flippable() const { return gtk_range_get_flippable(GTK_RANGE(this)); }
void BaseRange::flippable(bool v) { gtk_range_set_flippable(GTK_RANGE(this), v); }

GdkRectangle BaseRange::getRangeRectangle() const {
    GdkRectangle r;
    gtk_range_get_range_rect(GTK_RANGE(this), &r);
    return r;
}

bool BaseRange::inverted() const { return gtk_range_get_inverted(GTK_RANGE(this)); }
void BaseRange::inverted(bool v) { gtk_range_set_inverted(GTK_RANGE(this), v); }
GtkSensitivityType BaseRange::lowerStepSensitivity() const { return gtk_range_get_lower_stepper_sensitivity(GTK_RANGE(this)); }
void BaseRange::lowerStepSensitivity(GtkSensitivityType v) { gtk_range_set_lower_stepper_sensitivity(GTK_RANGE(this), v); }
GtkSensitivityType BaseRange::upperStepSensitivity() const { return gtk_range_get_upper_stepper_sensitivity(GTK_RANGE(this)); }
void BaseRange::upperStepSensitivity(GtkSensitivityType v) { gtk_range_set_upper_stepper_sensitivity(GTK_RANGE(this), v); }
bool BaseRange::restrictToFillLevel() const { return gtk_range_get_restrict_to_fill_level(GTK_RANGE(this)); }
void BaseRange::restrictToFillLevel(bool v) { gtk_range_set_restrict_to_fill_level(GTK_RANGE(this), v); }
int BaseRange::roundDigit() const { return gtk_range_get_round_digits(GTK_RANGE(this)); }
void BaseRange::roundDigit(int v) { gtk_range_set_round_digits(GTK_RANGE(this), v); }
bool BaseRange::showFillLevel() const { return gtk_range_get_show_fill_level(GTK_RANGE(this)); }
void BaseRange::showFillLevel(bool v) { gtk_range_set_show_fill_level(GTK_RANGE(this), v); }
bool BaseRange::sizeFixed() const { return gtk_range_get_slider_size_fixed(GTK_RANGE(this)); }
void BaseRange::sizeFixed(bool v) { gtk_range_set_slider_size_fixed(GTK_RANGE(this), v); }
double BaseRange::value() const { return gtk_range_get_value(GTK_RANGE(this)); }
void BaseRange::value(double v) { gtk_range_set_value(GTK_RANGE(this), v); }

void BaseRange::SetIncrements(double step, double page) { gtk_range_set_increments(GTK_RANGE(this), step, page); }

void BaseRange::SetRange(double min, double max) { gtk_range_set_range(GTK_RANGE(this), min, max); }

RawSignal BaseRange::Signals::AdjustBounds(SignalCallback eventMethod, void *instance, void *userData)
{
    VSignal *s = new VSignal();
    s->eventMethod = (void *)eventMethod;
    s->userData = userData;
    s->instance = instance;
    s->signalName = "adjust-bounds";
    void (*gtkmethod) (GtkWidget *, double, gpointer) = [](GtkWidget *sender, double dir, gpointer g) -> void{
        VSignal *signal = (VSignal *)g;
        EventArgs *eArgs = new EventArgs(nullptr);
        signal->args = eArgs;
        signal->args->EventSignal = signal;
        signal->args->UserData = signal->userData;
        if(signal->instance == nullptr){
            StaticSignalMethod_Double ssm = (StaticSignalMethod_Double)signal->eventMethod;
            ssm((BaseWidget *)sender, dir, signal->args);
        } else {
            InstanceSignalMethod_Double ism = (InstanceSignalMethod_Double)signal->eventMethod;
            ism(signal->instance, (BaseWidget *)sender, dir, signal->args);
        }
        delete eArgs;
    };
    s->callBack = G_CALLBACK(gtkmethod);
    return s;
}

RawSignal BaseRange::Signals::ChangeValue(SignalCallback eventMethod, void *instance, void *userData)
{
    VSignal *s = new VSignal();
    s->eventMethod = (void *)eventMethod;
    s->userData = userData;
    s->instance = instance;
    s->signalName = "change-value";
    bool (*gtkmethod) (GtkWidget *, GtkScrollType, double, gpointer) = [](GtkWidget *sender, GtkScrollType type, double dir, gpointer g) -> bool{
        VSignal *signal = (VSignal *)g;
        EventArgs *eArgs = new EventArgs(nullptr);
        eArgs->CanStopHandlers = true;
        signal->args = eArgs;
        signal->args->EventSignal = signal;
        signal->args->UserData = signal->userData;
        if(signal->instance == nullptr){
            StaticSignalMethod_ScrType_Double ssm = (StaticSignalMethod_ScrType_Double)signal->eventMethod;
            ssm((BaseWidget *)sender, type, dir, signal->args);
        } else {
            InstanceSignalMethod_ScrType_Double ism = (InstanceSignalMethod_ScrType_Double)signal->eventMethod;
            ism(signal->instance, (BaseWidget *)sender, type, dir, signal->args);
        }
        bool stopHandler = eArgs->StopOtherHandlers;
        delete eArgs;
        return stopHandler;
    };
    s->callBack = G_CALLBACK(gtkmethod);
    return s;
}

RawSignal BaseRange::Signals::MoveSlider(SignalCallback eventMethod, void *instance, void *userData)
{
    VSignal *s = new VSignal();
    s->eventMethod = (void *)eventMethod;
    s->userData = userData;
    s->instance = instance;
    s->signalName = "move-slider";
    void (*gtkmethod) (GtkWidget *, GtkScrollType, gpointer) = [](GtkWidget *sender, GtkScrollType type, gpointer g) -> void{
        VSignal *signal = (VSignal *)g;
        EventArgs *eArgs = new EventArgs(nullptr);
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
        delete eArgs;
    };
    s->callBack = G_CALLBACK(gtkmethod);
    return s;
}

RawSignal BaseRange::Signals::ValueChanged(SignalCallback eventMethod, void *instance, void *userData)
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
