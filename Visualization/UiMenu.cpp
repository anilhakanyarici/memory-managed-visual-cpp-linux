#include "UiMenu.h"
#include "UiWindow.h"
#include "AccelGroup.h"
#include "../String16.h"

Delegate(StaticSignalMethod, void, BaseWidget *, EventArgs *);
Delegate(InstanceSignalMethod, void, void *, BaseWidget *, EventArgs *);
Delegate(StaticSignalMethod_int, void, BaseWidget *, int, EventArgs *);
Delegate(InstanceSignalMethod_int, void, void *, BaseWidget *, int, EventArgs *);
Delegate(StaticSignalMethod_intPtr, void, BaseWidget *, int *, EventArgs *);
Delegate(InstanceSignalMethod_intPtr, void, void *, BaseWidget *, int *, EventArgs *);
Delegate(StaticSignalMethod_ScrType, void, BaseWidget *, GtkScrollType, EventArgs *);
Delegate(InstanceSignalMethod_ScrType, void, void *, BaseWidget *, GtkScrollType, EventArgs *);
Delegate(StaticSignalMethod_Rect_Rect_bool_bool, void, BaseWidget *, GdkRectangle *, GdkRectangle *, bool, bool, EventArgs *);
Delegate(InstanceSignalMethod_Rect_Rect_bool_bool, void, void *, BaseWidget *, GdkRectangle *, GdkRectangle *, bool, bool, EventArgs *);

RawSignal UiMenu::Signals::MoveScroll(SignalCallback eventMethod, void *instance, void *userData)
{
    VSignal *s = new VSignal();
    s->eventMethod = (void *)eventMethod;
    s->userData = userData;
    s->instance = instance;
    s->signalName = "move-scroll";
    void (*gtkmethod) (GtkWidget *, GtkScrollType, gpointer) = [](GtkWidget *sender, GtkScrollType scrType, gpointer g) -> void{
        VSignal *signal = (VSignal *)g;
        EventArgs *eArgs = new EventArgs(nullptr);
        signal->args = eArgs;
        signal->args->EventSignal = signal;
        signal->args->UserData = signal->userData;
        if(signal->instance == nullptr){
            StaticSignalMethod_ScrType ssm = (StaticSignalMethod_ScrType)signal->eventMethod;
            ssm((BaseWidget *)sender, scrType, signal->args);
        } else {
            InstanceSignalMethod_ScrType ism = (InstanceSignalMethod_ScrType)signal->eventMethod;
            ism(signal->instance, (BaseWidget *)sender, scrType, signal->args);
        }
        delete eArgs;
    };
    s->callBack = G_CALLBACK(gtkmethod);
    return s;
}

RawSignal UiMenu::Signals::PoppedUp(SignalCallback eventMethod, void *instance, void *userData)
{
    VSignal *s = new VSignal();
    s->eventMethod = (void *)eventMethod;
    s->userData = userData;
    s->instance = instance;
    s->signalName = "popped-up";
    void (*gtkmethod) (GtkWidget *, gpointer, gpointer, bool, bool, gpointer) = [](GtkWidget *sender, gpointer flippedRect, gpointer finalRect, bool flippedX, bool flippedY, gpointer g) -> void{
        VSignal *signal = (VSignal *)g;
        EventArgs *eArgs = new EventArgs(nullptr);
        signal->args = eArgs;
        signal->args->EventSignal = signal;
        signal->args->UserData = signal->userData;
        if(signal->instance == nullptr){
            StaticSignalMethod_Rect_Rect_bool_bool ssm = (StaticSignalMethod_Rect_Rect_bool_bool)signal->eventMethod;
            ssm((BaseWidget *)sender, (GdkRectangle *)flippedRect, (GdkRectangle *)finalRect, flippedX, flippedY, signal->args);
        } else {
            InstanceSignalMethod_Rect_Rect_bool_bool ism = (InstanceSignalMethod_Rect_Rect_bool_bool)signal->eventMethod;
            ism(signal->instance, (BaseWidget *)sender, (GdkRectangle *)flippedRect, (GdkRectangle *)finalRect, flippedX, flippedY, signal->args);
        }
        delete eArgs;
    };
    s->callBack = G_CALLBACK(gtkmethod);
    return s;
}

void UiMenu::ReorderChild(UiMenuItem *child, int position) { gtk_menu_reorder_child(GTK_MENU(this), GTK_WIDGET(child), position); }

void UiMenu::Reposition() { gtk_menu_reposition(GTK_MENU(this)); }

void UiMenu::SetActive(int index) { gtk_menu_set_monitor(GTK_MENU(this), index); }

UiMenu *UiMenu::New()
{
    return (UiMenu *)gtk_menu_new();
}

AccelGroup *UiMenu::accelGroup() const { return (AccelGroup *)(gtk_menu_get_accel_group(GTK_MENU(this))); }

void UiMenu::accelGroup(AccelGroup *acc) { gtk_menu_set_accel_group(GTK_MENU(this), GTK_ACCEL_GROUP(acc)); }

BaseWidget *UiMenu::getActive() const { return (BaseWidget *)gtk_menu_get_active(GTK_MENU(this)); }

int UiMenu::monitor() const { return gtk_menu_get_monitor(GTK_MENU(this)); }

void UiMenu::monitor(int m) { gtk_menu_set_monitor(GTK_MENU(this), m); }

bool UiMenu::reserveToggleSize() const { return gtk_menu_get_reserve_toggle_size(GTK_MENU(this)); }

void UiMenu::reserveToggleSize(bool m) { gtk_menu_set_reserve_toggle_size(GTK_MENU(this), m); }

void UiMenu::Attach(UiMenuItem *child, uint left, uint right, uint top, uint bottom) { gtk_menu_attach(GTK_MENU(this), GTK_WIDGET(child), left, right, top, bottom); }

void UiMenu::Popdown() { gtk_menu_popdown(GTK_MENU(this)); }

RawSignal UiMenuItem::Signals::Activate(SignalCallback eventMethod, void *instance, void *userData)
{
    VSignal *s = new VSignal();
    s->eventMethod = (void *)eventMethod;
    s->userData = userData;
    s->instance = instance;
    s->signalName = "activate-item";
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

RawSignal UiMenuItem::Signals::Select(SignalCallback eventMethod, void *instance, void *userData)
{
    VSignal *s = new VSignal();
    s->eventMethod = (void *)eventMethod;
    s->userData = userData;
    s->instance = instance;
    s->signalName = "select";
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

RawSignal UiMenuItem::Signals::Deselect(SignalCallback eventMethod, void *instance, void *userData)
{
    VSignal *s = new VSignal();
    s->eventMethod = (void *)eventMethod;
    s->userData = userData;
    s->instance = instance;
    s->signalName = "deselect";
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

RawSignal UiMenuItem::Signals::ToggleSizeAllocate(SignalCallback eventMethod, void *instance, void *userData)
{
    VSignal *s = new VSignal();
    s->eventMethod = (void *)eventMethod;
    s->userData = userData;
    s->instance = instance;
    s->signalName = "toggle-size-allocate";
    void (*gtkmethod) (GtkWidget *, int, gpointer) = [](GtkWidget *sender, int arg, gpointer g) -> void{
        VSignal *signal = (VSignal *)g;
        EventArgs *eArgs = new EventArgs(nullptr);

        signal->args = eArgs;
        signal->args->EventSignal = signal;
        signal->args->UserData = signal->userData;
        if(signal->instance == nullptr){
            StaticSignalMethod_int ssm = (StaticSignalMethod_int)signal->eventMethod;
            ssm((BaseWidget *)sender, arg, signal->args);
        } else {
            InstanceSignalMethod_int ism = (InstanceSignalMethod_int)signal->eventMethod;
            ism(signal->instance, (BaseWidget *)sender, arg, signal->args);
        }
        delete eArgs;
    };
    s->callBack = G_CALLBACK(gtkmethod);
    return s;
}

RawSignal UiMenuItem::Signals::ToggleSizeRequest(SignalCallback eventMethod, void *instance, void *userData)
{
    VSignal *s = new VSignal();
    s->eventMethod = (void *)eventMethod;
    s->userData = userData;
    s->instance = instance;
    s->signalName = "toggle-size-request";
    void (*gtkmethod) (GtkWidget *, int *, gpointer) = [](GtkWidget *sender, int *requisition, gpointer g) -> void{
        VSignal *signal = (VSignal *)g;
        EventArgs *eArgs = new EventArgs(nullptr);

        signal->args = eArgs;
        signal->args->EventSignal = signal;
        signal->args->UserData = signal->userData;
        if(signal->instance == nullptr){
            StaticSignalMethod_intPtr ssm = (StaticSignalMethod_intPtr)signal->eventMethod;
            ssm((BaseWidget *)sender, requisition, signal->args);
        } else {
            InstanceSignalMethod_intPtr ism = (InstanceSignalMethod_intPtr)signal->eventMethod;
            ism(signal->instance, (BaseWidget *)sender, requisition, signal->args);
        }
        delete eArgs;
    };
    s->callBack = G_CALLBACK(gtkmethod);
    return s;
}

UiMenuBar *UiMenuBar::New()
{
    return (UiMenuBar *)gtk_menu_new();
}

GtkPackDirection UiMenuBar::childPackDirection() const { return gtk_menu_bar_get_child_pack_direction(GTK_MENU_BAR(this)); }

void UiMenuBar::childPackDirection(GtkPackDirection m) { gtk_menu_bar_set_child_pack_direction(GTK_MENU_BAR(this), m); }

GtkPackDirection UiMenuBar::packDirection() const { return gtk_menu_bar_get_pack_direction(GTK_MENU_BAR(this)); }

void UiMenuBar::packDirection(GtkPackDirection m) { gtk_menu_bar_set_pack_direction(GTK_MENU_BAR(this), m); }

UiMenuItem *UiMenuItem::New(const String16 &label)
{
    GtkWidget *menuItem = gtk_menu_item_new();
    ByteArray utf8 = label.ToCString();
    gtk_menu_item_set_label(GTK_MENU_ITEM(menuItem), (const gchar *)utf8.data());
    return (UiMenuItem *)menuItem;
}

String16 UiMenuItem::label() const { return String16((const char *)gtk_menu_item_get_label(GTK_MENU_ITEM(this))); }

void UiMenuItem::label(const String16 &label)
{
    ByteArray utf8 = label.ToCString();
    gtk_menu_item_set_label(GTK_MENU_ITEM(this), (const gchar *)utf8.data());
}

bool UiMenuItem::useUnderline() const { return gtk_menu_item_get_use_underline(GTK_MENU_ITEM(this)); }

void UiMenuItem::useUnderline(bool u) { gtk_menu_item_set_use_underline(GTK_MENU_ITEM(this), u); }

bool UiMenuItem::reserveIndicator() const { return gtk_menu_item_get_reserve_indicator(GTK_MENU_ITEM(this)); }

void UiMenuItem::reserveIndicator(bool u) { gtk_menu_item_set_reserve_indicator(GTK_MENU_ITEM(this), u); }

UiMenuItem *UiMenuItem::submenu() const { return (UiMenuItem *)gtk_menu_item_get_submenu(GTK_MENU_ITEM(this)); }

void UiMenuItem::submenu(UiMenuItem *item) { gtk_menu_item_set_submenu(GTK_MENU_ITEM(this), GTK_WIDGET(item)); }

void UiMenuItem::Activate() { gtk_menu_item_activate(GTK_MENU_ITEM(this)); }

void UiMenuItem::Deselect() { gtk_menu_item_deselect(GTK_MENU_ITEM(this)); }

void UiMenuItem::Select() { gtk_menu_item_select(GTK_MENU_ITEM(this)); }

void UiMenuItem::ToggleSizeAllocate(int t) { gtk_menu_item_toggle_size_allocate(GTK_MENU_ITEM(this), t); }

void UiMenuItem::ToggleSizeRequest(int *requisition) { gtk_menu_item_toggle_size_request(GTK_MENU_ITEM(this), (gint *)requisition); }

RawSignal UiCheckMenuItem::Signals::Toggled(SignalCallback eventMethod, void *instance, void *userData)
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

UiCheckMenuItem *UiCheckMenuItem::New(const String16 &label)
{
    ByteArray utf8 = label.ToCString();
    return (UiCheckMenuItem *) gtk_check_menu_item_new_with_label((const char *)utf8.data());
}

bool UiCheckMenuItem::active() const { return gtk_check_menu_item_get_active(GTK_CHECK_MENU_ITEM(this)); }

void UiCheckMenuItem::active(bool u) { gtk_check_menu_item_set_active(GTK_CHECK_MENU_ITEM(this), u); }

bool UiCheckMenuItem::inconsistent() const { return gtk_check_menu_item_get_inconsistent(GTK_CHECK_MENU_ITEM(this)); }

void UiCheckMenuItem::inconsistent(bool u) { gtk_check_menu_item_set_inconsistent(GTK_CHECK_MENU_ITEM(this), u); }

bool UiCheckMenuItem::drawAsRadio() const { return gtk_check_menu_item_get_draw_as_radio(GTK_CHECK_MENU_ITEM(this)); }

void UiCheckMenuItem::drawAsRadio(bool u) { gtk_check_menu_item_set_draw_as_radio(GTK_CHECK_MENU_ITEM(this), u); }

void UiCheckMenuItem::Toggled() { gtk_check_menu_item_toggled(GTK_CHECK_MENU_ITEM(this)); }

UiSeparatorMenuItem *UiSeparatorMenuItem::New()
{
    return (UiSeparatorMenuItem *)gtk_separator_menu_item_new();
}
