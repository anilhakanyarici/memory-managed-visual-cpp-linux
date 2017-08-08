#include "Application.h"

Delegate(StaticSignalMethod_UiWin, void, BaseApplication *, UiWindow *, EventArgs *);
Delegate(InstanceSignalMethod_UiWin, void, void *, BaseApplication *, UiWindow *, EventArgs *);

Application *Application::New(const String16 &id, GApplicationFlags flags)
{
    ByteArray utf8Name = id.ToCString();
    return (Application *) gtk_application_new((const gchar *)utf8Name.data(), flags);
}

UiWindow *Application::getActiveWindow() const
{
    UiWindow *win = (UiWindow *)gtk_application_get_active_window(GTK_APPLICATION(this));
    return win;
}

void Application::AddWindow(UiWindow *window)
{
    gtk_application_add_window(GTK_APPLICATION(this), GTK_WINDOW(window));
}

void Application::RemoveWindow(UiWindow *window)
{
    gtk_application_remove_window(GTK_APPLICATION(this), GTK_WINDOW(window));
}

uint Application::Inhibit(UiWindow *window, GtkApplicationInhibitFlags flags, const String16 &reason)
{
    ByteArray utf8 = reason.ToCString();
    return gtk_application_inhibit(GTK_APPLICATION(this), GTK_WINDOW(window), flags, (const char *)utf8.data());
}

void Application::Uninhibit(uint cookie)
{
    gtk_application_uninhibit(GTK_APPLICATION(this), cookie);
}

bool Application::IsInhibited(GtkApplicationInhibitFlags flags)
{
    return gtk_application_is_inhibited(GTK_APPLICATION(this), flags);
}

Array<UiWindow *> Application::getWindows()
{
    GList* list = gtk_application_get_windows(GTK_APPLICATION(this));
    guint len = g_list_length(list);
    Array<UiWindow *> windows = Array<UiWindow *>(len);

    GList *curr = list;
    int i = 0;
    while(curr != NULL){
        windows[i] = (UiWindow *)curr->data;
        curr = curr->next;
        i++;
    }
    g_list_free(list);
    return windows;
}

Signal Application::Signals::WindowAdded(SignalCallback eventMethod, void *instance, void *userData)
{
    VSignal *s = new VSignal();
    s->eventMethod = (void *)eventMethod;
    s->userData = userData;
    s->instance = instance;
    s->signalName = "window-added";
    void (*gtkmethod) (GtkApplication *, GtkWindow *, gpointer) = [](GtkApplication *sender, GtkWindow *win, gpointer g) -> void{
        VSignal *signal = (VSignal *)g;
        EventArgs *eArgs = new EventArgs(nullptr);
        signal->args = eArgs;
        signal->args->EventSignal = signal;
        signal->args->UserData = signal->userData;
        UiWindow *window = (UiWindow *)win;
        if(signal->instance == nullptr){
            StaticSignalMethod_UiWin ssm = (StaticSignalMethod_UiWin)signal->eventMethod;
            ssm((BaseApplication *)sender, window, signal->args);
        } else {
            InstanceSignalMethod_UiWin ism = (InstanceSignalMethod_UiWin)signal->eventMethod;
            ism(signal->instance, (BaseApplication *)sender, window, signal->args);
        }
        delete eArgs;
    };
    s->callBack = G_CALLBACK(gtkmethod);
    return s;
}

Signal Application::Signals::WindowRemoved(SignalCallback eventMethod, void *instance, void *userData)
{
    VSignal *s = new VSignal();
    s->eventMethod = (void *)eventMethod;
    s->userData = userData;
    s->instance = instance;
    s->signalName = "window-removed";
    void (*gtkmethod) (GtkApplication *, GtkWindow *, gpointer) = [](GtkApplication *sender, GtkWindow *win, gpointer g) -> void{
        VSignal *signal = (VSignal *)g;
        EventArgs *eArgs = new EventArgs(nullptr);
        signal->args = eArgs;
        signal->args->EventSignal = signal;
        signal->args->UserData = signal->userData;
        UiWindow *window = (UiWindow *)win;
        if(signal->instance == nullptr){
            StaticSignalMethod_UiWin ssm = (StaticSignalMethod_UiWin)signal->eventMethod;
            ssm((BaseApplication *)sender, window, signal->args);
        } else {
            InstanceSignalMethod_UiWin ism = (InstanceSignalMethod_UiWin)signal->eventMethod;
            ism(signal->instance, (BaseApplication *)sender, window, signal->args);
        }
        delete eArgs;
    };
    s->callBack = G_CALLBACK(gtkmethod);
    return s;
}
