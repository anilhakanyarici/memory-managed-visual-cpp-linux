#include "UiLevelBar.h"

Delegate(StaticSignalMethod_Str, void, BaseWidget *, String16, EventArgs *);
Delegate(InstanceSignalMethod_Str, void, void *, BaseWidget *, String16, EventArgs *);

UiLevelBar *UiLevelBar::New(double min, double max)
{
    return (UiLevelBar *)gtk_level_bar_new_for_interval(min, max);
}

GtkLevelBarMode UiLevelBar::mode() const { return gtk_level_bar_get_mode(GTK_LEVEL_BAR(this)); }
void UiLevelBar::mode(GtkLevelBarMode m) { gtk_level_bar_set_mode(GTK_LEVEL_BAR(this), m); }
double UiLevelBar::value() const { return gtk_level_bar_get_value(GTK_LEVEL_BAR(this)); }
void UiLevelBar::value(double v) { gtk_level_bar_set_value(GTK_LEVEL_BAR(this), v); }
double UiLevelBar::minValue() const { return gtk_level_bar_get_min_value(GTK_LEVEL_BAR(this)); }
void UiLevelBar::minValue(double v) { gtk_level_bar_set_min_value(GTK_LEVEL_BAR(this), v); }
double UiLevelBar::maxValue() const { return gtk_level_bar_get_max_value(GTK_LEVEL_BAR(this)); }
void UiLevelBar::maxValue(double v) { gtk_level_bar_set_max_value(GTK_LEVEL_BAR(this), v); }
bool UiLevelBar::inverted() const { return gtk_level_bar_get_inverted(GTK_LEVEL_BAR(this)); }
void UiLevelBar::inverted(bool v) { gtk_level_bar_set_inverted(GTK_LEVEL_BAR(this), v); }

void UiLevelBar::AddOffsetValue(const String16 &name, double value)
{
    ByteArray utf8 = name.ToCString();
    gtk_level_bar_add_offset_value(GTK_LEVEL_BAR(this), (const char *)utf8.data(), value);
}

void UiLevelBar::RemoveOffsetValue(const String16 &name)
{
    ByteArray utf8 = name.ToCString();
    gtk_level_bar_remove_offset_value(GTK_LEVEL_BAR(this), (const char *)utf8.data());
}

double UiLevelBar::GetOffsetValue(const String16 &name)
{
    ByteArray utf8 = name.ToCString();
    double val;
    if(gtk_level_bar_get_offset_value(GTK_LEVEL_BAR(this), (const char *)utf8.data(), &val))
        return val;
    return DOUBLE_NAN;
}

RawSignal UiLevelBar::Signals::OffsetChanged(SignalCallback eventMethod, void *instance, void *userData)
{
    VSignal *s = new VSignal();
    s->eventMethod = (void *)eventMethod;
    s->userData = userData;
    s->instance = instance;
    s->signalName = "offset-changed";
    void (*gtkmethod) (GtkWidget *, gchar *, gpointer) = [](GtkWidget *sender, gchar *namePtr, gpointer g) -> void{
        VSignal *signal = (VSignal *)g;
        EventArgs *eArgs = new EventArgs(nullptr);
        signal->args = eArgs;
        signal->args->EventSignal = signal;
        signal->args->UserData = signal->userData;
        if(signal->instance == nullptr){
            StaticSignalMethod_Str ssm = (StaticSignalMethod_Str)signal->eventMethod;
            ssm((BaseWidget *)sender, String16(namePtr), signal->args);
        } else {
            InstanceSignalMethod_Str ism = (InstanceSignalMethod_Str)signal->eventMethod;
            ism(signal->instance, (BaseWidget *)sender, String16(namePtr), signal->args);
        }
        delete eArgs;
    };
    s->callBack = G_CALLBACK(gtkmethod);
    return s;
}
