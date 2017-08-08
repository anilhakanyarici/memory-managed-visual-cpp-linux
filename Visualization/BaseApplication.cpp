#include "BaseApplication.h"

Delegate(StaticSignalMethod, void, BaseApplication *, EventArgs *);
Delegate(InstanceSignalMethod, void, void *, BaseApplication *, EventArgs *);

String16 BaseApplication::applicationId() const { return String16((const char *)g_application_get_application_id(G_APPLICATION(this))); }
void BaseApplication::applicationId(const String16 &v) { ByteArray utf8 = v.ToCString(); g_application_set_application_id(G_APPLICATION(this), (const gchar *)utf8.data()); }
int BaseApplication::inactivityTimeout() const { return g_application_get_inactivity_timeout(G_APPLICATION(this)); }
void BaseApplication::inactivityTimeout(int v) { g_application_set_inactivity_timeout(G_APPLICATION(this), v); }
GApplicationFlags BaseApplication::flags() const { return g_application_get_flags(G_APPLICATION(this)); }
void BaseApplication::flags(GApplicationFlags v) { g_application_set_flags(G_APPLICATION(this), v); }
String16 BaseApplication::resourcePath() const { return String16((const char *)g_application_get_resource_base_path(G_APPLICATION(this))); }
void BaseApplication::resourcePath(const String16 &v) { ByteArray utf8 = v.ToCString(); g_application_set_resource_base_path(G_APPLICATION(this), (const gchar *)utf8.data()); }
bool BaseApplication::isBusy() const { return g_application_get_is_busy(G_APPLICATION(this)); }
int BaseApplication::isRegistered() const { return g_application_get_is_registered(G_APPLICATION(this)); }
int BaseApplication::isRemote() const { return g_application_get_is_remote(G_APPLICATION(this)); }

void BaseApplication::Activate() { g_application_activate(G_APPLICATION(this)); }

void BaseApplication::AddMainAction(const String16 &longName, char shortName, GOptionFlags flags, GOptionArg arg, const String16 &description, const String16 &argDescription)
{
    ByteArray utf8Name = longName.ToCString();
    ByteArray utf8Desc = description.ToCString();
    ByteArray utf8ArgD = argDescription.ToCString();
    g_application_add_main_option(G_APPLICATION(this), (const char *)utf8Name.data(), shortName, flags, arg, (const char *)utf8Desc.data(), (const char *)utf8ArgD.data());
}

bool BaseApplication::Register(CancellationToken *token)
{
    GError *e;
    bool ret = g_application_register(G_APPLICATION(this), G_CANCELLABLE(token), &e);
    g_error_free(e);
    return ret;
}

void BaseApplication::Hold() { g_application_hold(G_APPLICATION(this)); }
void BaseApplication::MarkBusy() { g_application_mark_busy(G_APPLICATION(this)); }
void BaseApplication::Release() { g_application_release(G_APPLICATION(this)); }
int BaseApplication::Run(int argc, char **argv) { return g_application_run(G_APPLICATION(this), argc, argv); }
void BaseApplication::Quit() { g_application_quit(G_APPLICATION(this)); }
void BaseApplication::UnmarkBusy() { g_application_unmark_busy(G_APPLICATION(this)); }

void BaseApplication::Unref()
{
    g_object_unref(G_APPLICATION(this));
}

Signal BaseApplication::Signals::Activate(SignalCallback eventMethod, void *instance, void *userData)
{
    VSignal *s = new VSignal();
    s->eventMethod = (void *)eventMethod;
    s->userData = userData;
    s->instance = instance;
    s->signalName = "activate";
    void (*gtkmethod) (GApplication *, gpointer) = [](GApplication *sender, gpointer g) -> void{
        VSignal *signal = (VSignal *)g;
        EventArgs *eArgs = new EventArgs(nullptr);
        signal->args = eArgs;
        signal->args->EventSignal = signal;
        signal->args->UserData = signal->userData;
        if(signal->instance == nullptr){
            StaticSignalMethod ssm = (StaticSignalMethod)signal->eventMethod;
            ssm((BaseApplication *)sender, signal->args);
        } else {
            InstanceSignalMethod ism = (InstanceSignalMethod)signal->eventMethod;
            ism(signal->instance, (BaseApplication *)sender, signal->args);
        }
        delete eArgs;
    };
    s->callBack = G_CALLBACK(gtkmethod);
    return s;
}

Signal BaseApplication::Signals::Shutdown(SignalCallback eventMethod, void *instance, void *userData)
{
    VSignal *s = new VSignal();
    s->eventMethod = (void *)eventMethod;
    s->userData = userData;
    s->instance = instance;
    s->signalName = "shutdown";
    void (*gtkmethod) (GApplication *, gpointer) = [](GApplication *sender, gpointer g) -> void{
        VSignal *signal = (VSignal *)g;
        EventArgs *eArgs = new EventArgs(nullptr);
        signal->args = eArgs;
        signal->args->EventSignal = signal;
        signal->args->UserData = signal->userData;
        if(signal->instance == nullptr){
            StaticSignalMethod ssm = (StaticSignalMethod)signal->eventMethod;
            ssm((BaseApplication *)sender, signal->args);
        } else {
            InstanceSignalMethod ism = (InstanceSignalMethod)signal->eventMethod;
            ism(signal->instance, (BaseApplication *)sender, signal->args);
        }
        delete eArgs;
    };
    s->callBack = G_CALLBACK(gtkmethod);
    return s;
}

Signal BaseApplication::Signals::Startup(SignalCallback eventMethod, void *instance, void *userData)
{
    VSignal *s = new VSignal();
    s->eventMethod = (void *)eventMethod;
    s->userData = userData;
    s->instance = instance;
    s->signalName = "startup";
    void (*gtkmethod) (GApplication *, gpointer) = [](GApplication *sender, gpointer g) -> void{
        VSignal *signal = (VSignal *)g;
        EventArgs *eArgs = new EventArgs(nullptr);
        signal->args = eArgs;
        signal->args->EventSignal = signal;
        signal->args->UserData = signal->userData;
        if(signal->instance == nullptr){
            StaticSignalMethod ssm = (StaticSignalMethod)signal->eventMethod;
            ssm((BaseApplication *)sender, signal->args);
        } else {
            InstanceSignalMethod ism = (InstanceSignalMethod)signal->eventMethod;
            ism(signal->instance, (BaseApplication *)sender, signal->args);
        }
        delete eArgs;
    };
    s->callBack = G_CALLBACK(gtkmethod);
    return s;
}


