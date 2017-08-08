#include "UiInfoBar.h"

Delegate(StaticSignalMethod, void, BaseWidget *, EventArgs *);
Delegate(InstanceSignalMethod, void, void *, BaseWidget *, EventArgs *);
Delegate(StaticSignalMethod_int, void, BaseWidget *, int, EventArgs *);
Delegate(InstanceSignalMethod_int, void, void *, BaseWidget *, int, EventArgs *);

UiInfoBar *UiInfoBar::New() { return (UiInfoBar *)gtk_info_bar_new(); }

GtkMessageType UiInfoBar::messageType() const { return gtk_info_bar_get_message_type(GTK_INFO_BAR(this)); }

void UiInfoBar::messageType(GtkMessageType t) { gtk_info_bar_set_message_type(GTK_INFO_BAR(this), t); }

bool UiInfoBar::showCloseButton() const { return gtk_info_bar_get_show_close_button(GTK_INFO_BAR(this)); }

void UiInfoBar::showCloseButton(bool t) { gtk_info_bar_set_show_close_button(GTK_INFO_BAR(this), t); }

BaseWidget *UiInfoBar::getActionArea() const { return (BaseWidget *)gtk_info_bar_get_action_area(GTK_INFO_BAR(this)); }

BaseWidget *UiInfoBar::getContentArea() const { return (BaseWidget *)gtk_info_bar_get_content_area(GTK_INFO_BAR(this)); }

void UiInfoBar::AddActionWidget(BaseWidget *child, int responseId) { gtk_info_bar_add_action_widget(GTK_INFO_BAR(this), GTK_WIDGET(child), responseId); }

UiButton *UiInfoBar::AddActionWidget(const String16 &str, int responseId)
{
    ByteArray utf8 = str.ToCString();
    return (UiButton *)gtk_info_bar_add_button(GTK_INFO_BAR(this), (const gchar *)utf8.data(), responseId);
}

void UiInfoBar::SetResponseSensitive(int responseId, bool setting) { gtk_info_bar_set_response_sensitive(GTK_INFO_BAR(this), responseId, setting); }

void UiInfoBar::SetDefaultResponse(int responseId) { gtk_info_bar_set_default_response(GTK_INFO_BAR(this), responseId); }

void UiInfoBar::EmitResponse(int responseId) { gtk_info_bar_response(GTK_INFO_BAR(this), responseId); }

RawSignal UiInfoBar::Signals::Close(SignalCallback eventMethod, void *instance, void *userData)
{
    VSignal *s = new VSignal();
    s->eventMethod = (void *)eventMethod;
    s->userData = userData;
    s->instance = instance;
    s->signalName = "close";
    void (*gtkmethod) (GtkInfoBar *, gpointer) = [](GtkInfoBar *sender, gpointer g) -> void{
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

RawSignal UiInfoBar::Signals::Response(SignalCallback eventMethod, void *instance, void *userData)
{
    VSignal *s = new VSignal();
    s->eventMethod = (void *)eventMethod;
    s->userData = userData;
    s->instance = instance;
    s->signalName = "response";
    void (*gtkmethod) (GtkInfoBar *, int, gpointer) = [](GtkInfoBar *sender, int resp, gpointer g) -> void{
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
