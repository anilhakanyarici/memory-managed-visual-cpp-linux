#include "UiDialog.h"

Delegate(StaticSignalMethod, void, BaseWidget *, EventArgs *);
Delegate(InstanceSignalMethod, void, void *, BaseWidget *, EventArgs *);
Delegate(StaticSignalMethod_int, void, BaseWidget *, int, EventArgs *);
Delegate(InstanceSignalMethod_int, void, void *, BaseWidget *, int, EventArgs *);
Delegate(StaticSignalMethod_Str, void, BaseWidget *, String16, EventArgs *);
Delegate(InstanceSignalMethod_Str, void, void *, BaseWidget *, String16, EventArgs *);

UiDialog *UiDialog::New()
{
    return (UiDialog *)gtk_dialog_new();
}

void UiDialog::AddActionWidget(BaseWidget *child, int responseId) { gtk_dialog_add_action_widget(GTK_DIALOG(this), GTK_WIDGET(child), (int)responseId); }
void UiDialog::DialogResponse(int responseId) { gtk_dialog_response(GTK_DIALOG(this), (int)responseId); }

UiButton *UiDialog::AddButton(const String16 &buttonText, int responseId)
{
    ByteArray utf8 = buttonText.ToCString();
    GtkButton *button = GTK_BUTTON(gtk_dialog_add_button(GTK_DIALOG(this), (const char *)utf8.data(), (int)responseId));
    return (UiButton *)button;
}

int UiDialog::Run() { return (int)gtk_dialog_run(GTK_DIALOG(this)); }
void UiDialog::SetDefaultResponse(int responseId) { gtk_dialog_set_default_response(GTK_DIALOG(this), (int)responseId); }

RawSignal UiDialog::Signals::Close(SignalCallback eventMethod, void *instance, void *userData)
{
    VSignal *s = new VSignal();
    s->eventMethod = (void *)eventMethod;
    s->userData = userData;
    s->instance = instance;
    s->signalName = "close";
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

RawSignal UiDialog::Signals::Response(SignalCallback eventMethod, void *instance, void *userData)
{
    VSignal *s = new VSignal();
    s->eventMethod = (void *)eventMethod;
    s->userData = userData;
    s->instance = instance;
    s->signalName = "close";
    void (*gtkmethod) (GtkWidget *, int, gpointer) = [](GtkWidget *sender, int resp, gpointer g) -> void{
        VSignal *signal = (VSignal *)g;
        EventArgs *eArgs = new EventArgs(nullptr);

        signal->args = eArgs;
        signal->args->EventSignal = signal;
        signal->args->UserData = signal->userData;
        if(signal->instance == nullptr){
            StaticSignalMethod_int ssm = (StaticSignalMethod_int)signal->eventMethod;
            ssm((BaseWidget *)sender, resp, signal->args);
        } else {
            InstanceSignalMethod_int ism = (InstanceSignalMethod_int)signal->eventMethod;
            ism(signal->instance, (BaseWidget *)sender, resp, signal->args);
        }
        delete eArgs;
    };
    s->callBack = G_CALLBACK(gtkmethod);
    return s;
}
