#include "Adjustment.h"
#include "EventArgs.h"

Delegate(StaticSignalMethod, void, Adjustment *, EventArgs *);
Delegate(InstanceSignalMethod, void, void *, Adjustment *, EventArgs *);

double Adjustment::value() const { return gtk_adjustment_get_value(GTK_ADJUSTMENT(this)); }
void Adjustment::value(double v) { gtk_adjustment_set_value(GTK_ADJUSTMENT(this), v); }
double Adjustment::lower() const { return gtk_adjustment_get_lower(GTK_ADJUSTMENT(this)); }
void Adjustment::lower(double v) { gtk_adjustment_set_lower(GTK_ADJUSTMENT(this), v); }
double Adjustment::upper() const { return gtk_adjustment_get_upper(GTK_ADJUSTMENT(this)); }
void Adjustment::upper(double v) { gtk_adjustment_set_upper(GTK_ADJUSTMENT(this), v); }
double Adjustment::pageIncrement() const { return gtk_adjustment_get_page_increment(GTK_ADJUSTMENT(this)); }
void Adjustment::pageIncrement(double v) { gtk_adjustment_set_page_increment(GTK_ADJUSTMENT(this), v); }
double Adjustment::pageSize() const { return gtk_adjustment_get_page_size(GTK_ADJUSTMENT(this)); }
void Adjustment::pageSize(double v) { gtk_adjustment_set_page_size(GTK_ADJUSTMENT(this), v); }
double Adjustment::stepIncrement() const { return gtk_adjustment_get_step_increment(GTK_ADJUSTMENT(this)); }
void Adjustment::stepIncrement(double v) { gtk_adjustment_set_step_increment(GTK_ADJUSTMENT(this), v); }
double Adjustment::getMinimumIncrement() const { return gtk_adjustment_get_minimum_increment(GTK_ADJUSTMENT(this)); }

void Adjustment::ClampPage(double lower, double upper){ gtk_adjustment_clamp_page(GTK_ADJUSTMENT(this), lower, upper); }
void Adjustment::Configure(double value, double lower, double upper, double step_increment, double page_increment, double page_size) { gtk_adjustment_configure(GTK_ADJUSTMENT(this), value, lower, upper, step_increment, page_increment, page_size); }

Adjustment *Adjustment::New(double value, double lower, double upper, double step_increment, double page_increment, double page_size)
{
    return (Adjustment *)gtk_adjustment_new(value, lower, upper, step_increment, page_increment, page_size);
}

RawSignal Adjustment::Signals::Changed(SignalCallback eventMethod, void *instance, void *userData)
{
    VSignal *s = new VSignal();
    s->eventMethod = (void *)eventMethod;
    s->userData = userData;
    s->instance = instance;
    s->signalName = "changed";
    void (*gtkmethod) (Adjustment *, gpointer) = [](Adjustment *sender, gpointer g) -> void{
        VSignal *signal = (VSignal *)g;
        EventArgs *eArgs = new EventArgs(nullptr);
        signal->args = eArgs;
        signal->args->EventSignal = signal;
        signal->args->UserData = signal->userData;
        if(signal->instance == nullptr){
            StaticSignalMethod ssm = (StaticSignalMethod)signal->eventMethod;
            ssm((Adjustment *)sender, signal->args);
        } else {
            InstanceSignalMethod ism = (InstanceSignalMethod)signal->eventMethod;
            ism(signal->instance, (Adjustment *)sender, signal->args);
        }
        delete eArgs;
    };
    s->callBack = G_CALLBACK(gtkmethod);
    return s;
}

RawSignal Adjustment::Signals::ValueChanged(SignalCallback eventMethod, void *instance, void *userData)
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
            ssm((Adjustment *)sender, signal->args);
        } else {
            InstanceSignalMethod ism = (InstanceSignalMethod)signal->eventMethod;
            ism(signal->instance, (Adjustment *)sender, signal->args);
        }
        delete eArgs;
    };
    s->callBack = G_CALLBACK(gtkmethod);
    return s;
}
