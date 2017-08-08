#include "UiStatusbar.h"
#include "../String16.h"

Delegate(StaticSignalMethod_uint_str, void, BaseWidget *, uint, String16, EventArgs *);
Delegate(InstanceSignalMethod_uint_str, void, void *, BaseWidget *, uint, String16, EventArgs *);

RawSignal UiStatusbar::Signals::TextPopped(SignalCallback eventMethod, void *instance, void *userData)
{
    VSignal *s = new VSignal();
    s->eventMethod = (void *)eventMethod;
    s->userData = userData;
    s->instance = instance;
    s->signalName = "text-popped";
    void (*gtkmethod) (GtkContainer *, uint, gchar *, gpointer) = [](GtkContainer *sender, uint id, gchar *text, gpointer g) -> void{
        VSignal *signal = (VSignal *)g;
        EventArgs *eArgs = new EventArgs(nullptr);
        signal->args = eArgs;
        signal->args->EventSignal = signal;
        signal->args->UserData = signal->userData;
        if(signal->instance == nullptr){
            StaticSignalMethod_uint_str ssm = (StaticSignalMethod_uint_str)signal->eventMethod;
            ssm((BaseWidget *)sender, id, String16(text), signal->args);
        } else {
            InstanceSignalMethod_uint_str ism = (InstanceSignalMethod_uint_str)signal->eventMethod;
            ism(signal->instance, (BaseWidget *)sender, id, String16(text), signal->args);
        }
        delete eArgs;
    };
    s->callBack = G_CALLBACK(gtkmethod);
    return s;
}

RawSignal UiStatusbar::Signals::TextPushed(SignalCallback eventMethod, void *instance, void *userData)
{
    VSignal *s = new VSignal();
    s->eventMethod = (void *)eventMethod;
    s->userData = userData;
    s->instance = instance;
    s->signalName = "text-pushed";
    void (*gtkmethod) (GtkContainer *, uint, gchar *, gpointer) = [](GtkContainer *sender, uint id, gchar *text, gpointer g) -> void{
        VSignal *signal = (VSignal *)g;
        EventArgs *eArgs = new EventArgs(nullptr);
        signal->args = eArgs;
        signal->args->EventSignal = signal;
        signal->args->UserData = signal->userData;
        if(signal->instance == nullptr){
            StaticSignalMethod_uint_str ssm = (StaticSignalMethod_uint_str)signal->eventMethod;
            ssm((BaseWidget *)sender, id, String16(text), signal->args);
        } else {
            InstanceSignalMethod_uint_str ism = (InstanceSignalMethod_uint_str)signal->eventMethod;
            ism(signal->instance, (BaseWidget *)sender, id, String16(text), signal->args);
        }
        delete eArgs;
    };
    s->callBack = G_CALLBACK(gtkmethod);
    return s;
}

UiStatusbar *UiStatusbar::New() { return (UiStatusbar *)gtk_statusbar_new(); }

Box *UiStatusbar::getMessageArea() const { return (Box *)gtk_statusbar_get_message_area(GTK_STATUSBAR(this)); }

uint UiStatusbar::ContextId(const String16 &description)
{
    ByteArray utf8 = description.ToCString();
    return gtk_statusbar_get_context_id(GTK_STATUSBAR(this), (const gchar *)utf8.data());
}

uint UiStatusbar::Push(uint contextId, const String16 &text)
{
    ByteArray utf8 = text.ToCString();
    return gtk_statusbar_push(GTK_STATUSBAR(this), contextId, (const gchar *)utf8.data());
}

void UiStatusbar::Pop(uint contextId)
{
    return gtk_statusbar_pop(GTK_STATUSBAR(this), contextId);
}

void UiStatusbar::Remove(uint contextId, uint messageId)
{
    return gtk_statusbar_remove(GTK_STATUSBAR(this), contextId, messageId);
}

void UiStatusbar::RemoveAll(uint contextId)
{
    return gtk_statusbar_remove_all(GTK_STATUSBAR(this), contextId);
}
