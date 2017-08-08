#include "UiLinkButton.h"

Delegate(StaticSignalMethod, void, VObject *, EventArgs *);
Delegate(InstanceSignalMethod, void, void *, VObject *, EventArgs *);

UiLinkButton *UiLinkButton::New(const String16 &uri)
{
    ByteArray utf8 = uri.ToCString();
    return (UiLinkButton *) gtk_link_button_new((const char *)utf8.data());
}

String16 UiLinkButton::uri() const { return String16((const char *)gtk_link_button_get_uri(GTK_LINK_BUTTON(this))); }

void UiLinkButton::uri(const String16 &uri)
{
    ByteArray utf8 = uri.ToCString();
    gtk_link_button_set_uri(GTK_LINK_BUTTON(this),(const char *)utf8.data());
}

bool UiLinkButton::visited() const { return gtk_link_button_get_visited(GTK_LINK_BUTTON(this)); }

void UiLinkButton::visited(bool v) { gtk_link_button_set_visited(GTK_LINK_BUTTON(this), v); }

RawSignal UiLinkButton::Signals::ActivateLink(SignalCallback eventMethod, void *instance, void *userData)
{
    VSignal *s = new VSignal();
    s->eventMethod = (void *)eventMethod;
    s->userData = userData;
    s->instance = instance;
    s->signalName = "activate-link";
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
