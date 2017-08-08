#include "UiToggleButton.h"

Delegate(StaticSignalMethod, void, VObject *, EventArgs *);
Delegate(InstanceSignalMethod, void, void *, VObject *, EventArgs *);

RawSignal UiToggleButton::Signals::Toggled(SignalCallback eventMethod, void *instance, void *userData)
{
    VSignal *s = new VSignal();
    s->eventMethod = (void *)eventMethod;
    s->userData = userData;
    s->instance = instance;
    s->signalName = "toggled";
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

UiToggleButton *UiToggleButton::New() { return (UiToggleButton *)gtk_toggle_button_new(); }

UiToggleButton *UiToggleButton::New(const String16 &label, bool mnemonic)
{
    ByteArray utf8 = label.ToCString();
    if(mnemonic)
        return (UiToggleButton *)gtk_toggle_button_new_with_mnemonic((const char *)utf8.data());
    else
        return (UiToggleButton *)gtk_toggle_button_new_with_label((const char *)utf8.data());
}

bool UiToggleButton::active() const { return gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(this)); }
void UiToggleButton::active(bool a) { gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(this), a); }
bool UiToggleButton::inconsistent() const { return gtk_toggle_button_get_inconsistent(GTK_TOGGLE_BUTTON(this)); }
void UiToggleButton::inconsistent(bool a) { gtk_toggle_button_set_inconsistent(GTK_TOGGLE_BUTTON(this), a); }
bool UiToggleButton::mode() const { return gtk_toggle_button_get_mode(GTK_TOGGLE_BUTTON(this)); }
void UiToggleButton::mode(bool drawIndicator) { gtk_toggle_button_set_mode(GTK_TOGGLE_BUTTON(this), drawIndicator); }

void UiToggleButton::EmitToggled() { gtk_toggle_button_toggled(GTK_TOGGLE_BUTTON(this)); }
