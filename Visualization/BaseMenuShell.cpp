#include "BaseMenuShell.h"

Delegate(StaticSignalMethod, void, BaseWidget *, EventArgs *);
Delegate(InstanceSignalMethod, void, void *, BaseWidget *, EventArgs *);
Delegate(StaticSignalMethod_bool, void, BaseWidget *, bool, EventArgs *);
Delegate(InstanceSignalMethod_bool, void, void *, BaseWidget *, bool, EventArgs *);
Delegate(StaticSignalMethod_DirType, void, BaseWidget *, GtkDirectionType, EventArgs *);
Delegate(InstanceSignalMethod_DirType, void, void *, BaseWidget *, GtkDirectionType, EventArgs *);
Delegate(StaticSignalMethod_MenuDirType, void, BaseWidget *, GtkMenuDirectionType, EventArgs *);
Delegate(InstanceSignalMethod_MenuDirType, void, void *, BaseWidget *, GtkMenuDirectionType, EventArgs *);
Delegate(StaticSignalMethod_int, void, BaseWidget *, int, EventArgs *);
Delegate(InstanceSignalMethod_int, void, void *, BaseWidget *, int, EventArgs *);
Delegate(StaticSignalMethod_Wid_int, void, BaseWidget *, BaseWidget *, int, EventArgs *);
Delegate(InstanceSignalMethod_Wid_int, void, void *, BaseWidget *, BaseWidget *, int, EventArgs *);

RawSignal BaseMenuShell::Signals::ActivateCurrent(SignalCallback eventMethod, void *instance, void *userData)
{
    VSignal *s = new VSignal();
    s->eventMethod = (void *)eventMethod;
    s->userData = userData;
    s->instance = instance;
    s->signalName = "activate-current";
    void (*gtkmethod) (GtkWidget *, bool, gpointer) = [](GtkWidget *sender, bool forceHide, gpointer g) -> void{
        VSignal *signal = (VSignal *)g;
        EventArgs *eArgs = new EventArgs(nullptr);
        signal->args = eArgs;
        signal->args->EventSignal = signal;
        signal->args->UserData = signal->userData;
        if(signal->instance == nullptr){
            StaticSignalMethod_bool ssm = (StaticSignalMethod_bool)signal->eventMethod;
            ssm((BaseWidget *)sender, forceHide, signal->args);
        } else {
            InstanceSignalMethod_bool ism = (InstanceSignalMethod_bool)signal->eventMethod;
            ism(signal->instance, (BaseWidget *)sender, forceHide, signal->args);
        }
        delete eArgs;
    };
    s->callBack = G_CALLBACK(gtkmethod);
    return s;
}

RawSignal BaseMenuShell::Signals::Cancel(SignalCallback eventMethod, void *instance, void *userData)
{
    VSignal *s = new VSignal();
    s->eventMethod = (void *)eventMethod;
    s->userData = userData;
    s->instance = instance;
    s->signalName = "cancel";
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

RawSignal BaseMenuShell::Signals::CycleFocus(SignalCallback eventMethod, void *instance, void *userData)
{
    VSignal *s = new VSignal();
    s->eventMethod = (void *)eventMethod;
    s->userData = userData;
    s->instance = instance;
    s->signalName = "cycle-focus";
    void (*gtkmethod) (GtkWidget *, GtkDirectionType, gpointer) = [](GtkWidget *sender, GtkDirectionType direction, gpointer g) -> void{
        VSignal *signal = (VSignal *)g;
        EventArgs *eArgs = new EventArgs(nullptr);
        signal->args = eArgs;
        signal->args->EventSignal = signal;
        signal->args->UserData = signal->userData;
        if(signal->instance == nullptr){
            StaticSignalMethod_DirType ssm = (StaticSignalMethod_DirType)signal->eventMethod;
            ssm((BaseWidget *)sender, direction, signal->args);
        } else {
            InstanceSignalMethod_DirType ism = (InstanceSignalMethod_DirType)signal->eventMethod;
            ism(signal->instance, (BaseWidget *)sender, direction, signal->args);
        }
        delete eArgs;
    };
    s->callBack = G_CALLBACK(gtkmethod);
    return s;
}

RawSignal BaseMenuShell::Signals::Deactivate(SignalCallback eventMethod, void *instance, void *userData)
{
    VSignal *s = new VSignal();
    s->eventMethod = (void *)eventMethod;
    s->userData = userData;
    s->instance = instance;
    s->signalName = "deactivate";
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

RawSignal BaseMenuShell::Signals::Insert(SignalCallback eventMethod, void *instance, void *userData)
{
    VSignal *s = new VSignal();
    s->eventMethod = (void *)eventMethod;
    s->userData = userData;
    s->instance = instance;
    s->signalName = "insert";
    void (*gtkmethod) (GtkWidget *, GtkWidget *, int, gpointer) = [](GtkWidget *sender, GtkWidget *child, int pos, gpointer g) -> void{
        VSignal *signal = (VSignal *)g;
        EventArgs *eArgs = new EventArgs(nullptr);
        BaseWidget *w = (BaseWidget *)child;
        signal->args = eArgs;
        signal->args->EventSignal = signal;
        signal->args->UserData = signal->userData;
        if(signal->instance == nullptr){
            StaticSignalMethod_Wid_int ssm = (StaticSignalMethod_Wid_int)signal->eventMethod;
            ssm((BaseWidget *)sender, w, pos, signal->args);
        } else {
            InstanceSignalMethod_Wid_int ism = (InstanceSignalMethod_Wid_int)signal->eventMethod;
            ism(signal->instance, (BaseWidget *)sender, w, pos, signal->args);
        }
        delete eArgs;
    };
    s->callBack = G_CALLBACK(gtkmethod);
    return s;
}

RawSignal BaseMenuShell::Signals::MoveCurrent(SignalCallback eventMethod, void *instance, void *userData)
{
    VSignal *s = new VSignal();
    s->eventMethod = (void *)eventMethod;
    s->userData = userData;
    s->instance = instance;
    s->signalName = "move-current";
    void (*gtkmethod) (GtkWidget *, GtkMenuDirectionType, gpointer) = [](GtkWidget *sender, GtkMenuDirectionType direction, gpointer g) -> void{
        VSignal *signal = (VSignal *)g;
        EventArgs *eArgs = new EventArgs(nullptr);
        signal->args = eArgs;
        signal->args->EventSignal = signal;
        signal->args->UserData = signal->userData;
        if(signal->instance == nullptr){
            StaticSignalMethod_MenuDirType ssm = (StaticSignalMethod_MenuDirType)signal->eventMethod;
            ssm((BaseWidget *)sender, direction, signal->args);
        } else {
            InstanceSignalMethod_MenuDirType ism = (InstanceSignalMethod_MenuDirType)signal->eventMethod;
            ism(signal->instance, (BaseWidget *)sender, direction, signal->args);
        }
        delete eArgs;
    };
    s->callBack = G_CALLBACK(gtkmethod);
    return s;
}

RawSignal BaseMenuShell::Signals::MoveSelected(SignalCallback eventMethod, void *instance, void *userData)
{
    VSignal *s = new VSignal();
    s->eventMethod = (void *)eventMethod;
    s->userData = userData;
    s->instance = instance;
    s->signalName = "move-selected";
    void (*gtkmethod) (GtkWidget *, int, gpointer) = [](GtkWidget *sender, int distance, gpointer g) -> void{
        VSignal *signal = (VSignal *)g;
        EventArgs *eArgs = new EventArgs(nullptr);
        signal->args = eArgs;
        signal->args->EventSignal = signal;
        signal->args->UserData = signal->userData;
        if(signal->instance == nullptr){
            StaticSignalMethod_int ssm = (StaticSignalMethod_int)signal->eventMethod;
            ssm((BaseWidget *)sender, distance, signal->args);
        } else {
            InstanceSignalMethod_int ism = (InstanceSignalMethod_int)signal->eventMethod;
            ism(signal->instance, (BaseWidget *)sender, distance, signal->args);
        }
        delete eArgs;
    };
    s->callBack = G_CALLBACK(gtkmethod);
    return s;
}

RawSignal BaseMenuShell::Signals::SelectionDone(SignalCallback eventMethod, void *instance, void *userData)
{
    VSignal *s = new VSignal();
    s->eventMethod = (void *)eventMethod;
    s->userData = userData;
    s->instance = instance;
    s->signalName = "selection-done";
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

bool BaseMenuShell::takeFocus() const { return gtk_menu_shell_get_take_focus(GTK_MENU_SHELL(this)); }

void BaseMenuShell::takeFocus(bool tf) { gtk_menu_shell_set_take_focus(GTK_MENU_SHELL(this), tf); }

BaseWidget *BaseMenuShell::getSelectedItem() const { return (BaseWidget *)gtk_menu_shell_get_selected_item(GTK_MENU_SHELL(this)); }

BaseWidget *BaseMenuShell::getParentShell() const { return (BaseWidget *)gtk_menu_shell_get_parent_shell(GTK_MENU_SHELL(this)); }

void BaseMenuShell::ActivateItem(BaseWidget *menuItem, bool forceDeactive) { gtk_menu_shell_activate_item(GTK_MENU_SHELL(this), GTK_WIDGET(menuItem), forceDeactive); }

void BaseMenuShell::Append(BaseWidget *child) { gtk_menu_shell_append(GTK_MENU_SHELL(this), GTK_WIDGET(child)); }

void BaseMenuShell::Cancel() { gtk_menu_shell_cancel(GTK_MENU_SHELL(this)); }

void BaseMenuShell::Deactivate() { gtk_menu_shell_deactivate(GTK_MENU_SHELL(this)); }

void BaseMenuShell::Deselect() { gtk_menu_shell_deselect(GTK_MENU_SHELL(this)); }

void BaseMenuShell::Insert(BaseWidget *child, int position) { gtk_menu_shell_insert(GTK_MENU_SHELL(this), GTK_WIDGET(child), position); }

void BaseMenuShell::Prepend(BaseWidget *child) { gtk_menu_shell_prepend(GTK_MENU_SHELL(this), GTK_WIDGET(child)); }

void BaseMenuShell::SelectFirst(bool searchSensitive) { gtk_menu_shell_select_first(GTK_MENU_SHELL(this), searchSensitive); }

void BaseMenuShell::SelectItem(BaseWidget *menuItem) { gtk_menu_shell_select_item(GTK_MENU_SHELL(this), GTK_WIDGET(menuItem)); }
