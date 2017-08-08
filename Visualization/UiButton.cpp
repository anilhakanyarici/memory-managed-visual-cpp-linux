#include "UiButton.h"

Delegate(StaticSignalMethod, void, BaseWidget *, EventArgs *);
Delegate(InstanceSignalMethod, void, void *, BaseWidget *, EventArgs *);

RawSignal UiButton::Signals::Activate(SignalCallback eventMethod, void *instance, void *userData)
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

RawSignal UiButton::Signals::Clicked(SignalCallback eventMethod, void *instance, void *userData)
{
    VSignal *s = new VSignal();
    s->eventMethod = (void *)eventMethod;
    s->userData = userData;
    s->instance = instance;
    s->signalName = "clicked";
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

UiButton *UiButton::New()
{
     GtkWidget *button = gtk_button_new();
     return (UiButton *)button;
}

UiButton *UiButton::New(const String16 &label)
{
    GtkWidget *button = gtk_button_new();
    ByteArray utf8 = label.ToCString();
    gtk_button_set_label(GTK_BUTTON(button), (const char *)utf8.data());
    return (UiButton *)button;
}

String16 UiButton::label() const { return String16((const char *)gtk_button_get_label(GTK_BUTTON(this))); }

void UiButton::label(const String16 &label)
{
    ByteArray utf8 = label.ToCString();
    gtk_button_set_label(GTK_BUTTON(this), (const char *)utf8.data());
}

bool UiButton::alwaysShowImage() const { return gtk_button_get_always_show_image(GTK_BUTTON(this)); }

void UiButton::alwaysShowImage(bool v) { gtk_button_set_always_show_image(GTK_BUTTON(this), v); }

bool UiButton::useUnderline() const { return gtk_button_get_use_underline(GTK_BUTTON(this)); }

void UiButton::useUnderline(bool v) { gtk_button_set_use_underline(GTK_BUTTON(this), v); }

UiImage *UiButton::image() const { return (UiImage *)gtk_button_get_image(GTK_BUTTON(this)); }

void UiButton::image(UiImage *v) { gtk_button_set_image(GTK_BUTTON(this), GTK_WIDGET(v)); }

GtkPositionType UiButton::imagePosition() const { return gtk_button_get_image_position(GTK_BUTTON(this)); }

void UiButton::imagePosition(GtkPositionType v) { gtk_button_set_image_position(GTK_BUTTON(this), v); }

void UiButton::Click(){ gtk_button_clicked(GTK_BUTTON(this)); }

