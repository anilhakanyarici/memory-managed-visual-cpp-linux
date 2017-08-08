#include "UiWindow.h"
#include "../ByteArray.h"

Delegate(StaticSignalMethod, void, BaseWidget *, EventArgs *);
Delegate(InstanceSignalMethod, void, void *, BaseWidget *, EventArgs *);
Delegate(StaticSignalMethod_GtkWid, void, BaseWidget *, BaseWidget *, EventArgs *);
Delegate(InstanceSignalMethod_GtkWid, void, void *, BaseWidget *, BaseWidget *, EventArgs *);
Delegate(StaticSignalMethod_bool, void, BaseWidget *, bool, EventArgs *);
Delegate(InstanceSignalMethod_bool, void, void *, BaseWidget *, bool, EventArgs *);

UiWindow *UiWindow::New(const String16 &title, GtkWindowType windowType)
{
    ByteArray utf8 = title.ToCString();
    const char *cStr = (const char *)utf8.data();
    GtkWidget *win = gtk_window_new(windowType);
    gtk_window_set_title(GTK_WINDOW(win), cStr);
    return (UiWindow *)win;
}

Application *UiWindow::application() const { return(Application *)gtk_window_get_application(GTK_WINDOW(this)); }
void UiWindow::application(Application *app) { gtk_window_set_application(GTK_WINDOW(this), GTK_APPLICATION(app)); }
bool UiWindow::acceptFocus() const { return gtk_window_get_accept_focus(GTK_WINDOW(this)); }
void UiWindow::acceptFocus(bool accept) { gtk_window_set_accept_focus(GTK_WINDOW(this), accept); }
BaseWidget *UiWindow::attachedTo() const { return (BaseWidget *)gtk_window_get_attached_to(GTK_WINDOW(this)); }
void UiWindow::attachedTo(BaseWidget *component) { gtk_window_set_attached_to(GTK_WINDOW(this), GTK_WIDGET(component)); }
bool UiWindow::decorated() const { return gtk_window_get_decorated(GTK_WINDOW(this)); }
void UiWindow::decorated(bool decorated) { gtk_window_set_decorated(GTK_WINDOW(this), decorated); }
bool UiWindow::deletable() const { return gtk_window_get_deletable(GTK_WINDOW(this)); }
void UiWindow::deletable(bool deletable) { gtk_window_set_deletable(GTK_WINDOW(this), deletable); }

Size UiWindow::defaultSize() const
{
    Size s;
    gtk_window_get_default_size(GTK_WINDOW(this), &s.Width, &s.Height);
    return s;
}

void UiWindow::defaultSize(Size size) { gtk_window_set_default_size(GTK_WINDOW(this), size.Width, size.Height); }

BaseWidget *UiWindow::defaultWidget() const { return (BaseWidget *)gtk_window_get_default_widget(GTK_WINDOW(this)); }

void UiWindow::defaultWidget(BaseWidget *w) { gtk_window_set_default(GTK_WINDOW(this), GTK_WIDGET(w)); }
bool UiWindow::destroyWithParent() const { return gtk_window_get_destroy_with_parent(GTK_WINDOW(this)); }
void UiWindow::destroyWithParent(bool set) { gtk_window_set_destroy_with_parent(GTK_WINDOW(this), set); }
BaseWidget *UiWindow::focus() { return (BaseWidget *)gtk_window_get_focus(GTK_WINDOW(this)); }
void UiWindow::focus(BaseWidget *focus) { gtk_window_set_focus(GTK_WINDOW(this), GTK_WIDGET(focus)); }
bool UiWindow::focusOnMap() const { return gtk_window_get_focus_on_map(GTK_WINDOW(this)); }
void UiWindow::focusOnMap(bool focus) { gtk_window_set_focus_on_map(GTK_WINDOW(this), focus); }
bool UiWindow::focusVisible() { return gtk_window_get_focus_visible(GTK_WINDOW(this)); }
void UiWindow::focusVisible(bool fVis) { gtk_window_set_focus_visible(GTK_WINDOW(this), fVis); }

DWindow *UiWindow::gdkWindow() const { return (DWindow *)this; }

Size UiWindow::getSize() const
{
    Size s;
    gtk_window_get_size(GTK_WINDOW(this), &s.Width, &s.Height);
    return s;
}

Position UiWindow::getPosition() const
{
    Position p;
    gtk_window_get_position(GTK_WINDOW(this), &p.X, &p.Y);
    return p;
}

GtkWindowType UiWindow::getWindowType() const { return gtk_window_get_window_type(GTK_WINDOW(this)); }
GdkGravity UiWindow::gravity() const { return gtk_window_get_gravity(GTK_WINDOW(this)); }
void UiWindow::gravity(GdkGravity gravity) { gtk_window_set_gravity(GTK_WINDOW(this), gravity); }
bool UiWindow::hasTopLevelFocus() const { return gtk_window_has_toplevel_focus(GTK_WINDOW(this)); }
bool UiWindow::hideTitlebarWhenMaximized() const { return gtk_window_get_hide_titlebar_when_maximized(GTK_WINDOW(this)); }
void UiWindow::hideTitlebarWhenMaximized(bool hide) { gtk_window_set_hide_titlebar_when_maximized(GTK_WINDOW(this), hide); }

String16 UiWindow::iconName() const
{
    return String16((const char *)gtk_window_get_icon_name(GTK_WINDOW(this)));
}

void UiWindow::iconName(const String16 &name)
{
    ByteArray utf8 = name.ToCString();
    const char *cStr = (const char *)utf8.data();
    gtk_window_set_icon_name(GTK_WINDOW(this), cStr);
}

bool UiWindow::isActive() const { return gtk_window_is_active(GTK_WINDOW(this)); }
bool UiWindow::isMaximized() const { return gtk_window_is_maximized(GTK_WINDOW(this)); }
bool UiWindow::modal() const { return gtk_window_get_modal(GTK_WINDOW(this)); }
void UiWindow::modal(bool modal) { gtk_window_set_modal(GTK_WINDOW(this), modal); }
bool UiWindow::resizable() const { return gtk_window_get_resizable(GTK_WINDOW(this)); }
void UiWindow::resizable(bool resizable) { gtk_window_set_resizable(GTK_WINDOW(this), resizable); }

String16 UiWindow::role() const
{
    return String16((const char *)gtk_window_get_role(GTK_WINDOW(this)));
}

void UiWindow::role(const String16 &role)
{
    ByteArray utf8 = role.ToCString();
    const char *cStr = (const char *)utf8.data();
    gtk_window_set_role(GTK_WINDOW(this), cStr);
}

Screen *UiWindow::screen() const { return (Screen *)gtk_window_get_screen(GTK_WINDOW(this)); }

void UiWindow::screen(Screen *s) { gtk_window_set_screen(GTK_WINDOW(this), GDK_SCREEN(s)); }

bool UiWindow::skipPagerHint() const { return gtk_window_get_skip_taskbar_hint(GTK_WINDOW(this)); }
void UiWindow::skipPagerHint(bool skip) { gtk_window_set_skip_taskbar_hint(GTK_WINDOW(this), skip); }
bool UiWindow::skipTaskbarHint() const { return gtk_window_get_skip_taskbar_hint(GTK_WINDOW(this)); }
void UiWindow::skipTaskbarHint(bool skip) { gtk_window_set_skip_taskbar_hint(GTK_WINDOW(this), skip); }

String16 UiWindow::title() const
{
    return String16((const char *)gtk_window_get_title(GTK_WINDOW(this)));
}

void UiWindow::title(const String16 &title)
{
    ByteArray utf8 = title.ToCString();
    const char *cStr = (const char *)utf8.data();
    gtk_window_set_title(GTK_WINDOW(this), cStr);
}

BaseWidget *UiWindow::titleBar() const { return (BaseWidget *)gtk_window_get_titlebar(GTK_WINDOW(this)); }
void UiWindow::titleBar(BaseWidget *bar) { gtk_window_set_titlebar(GTK_WINDOW(this), GTK_WIDGET(bar)); }
BaseWidget *UiWindow::transientFor() const { return (BaseWidget *)gtk_window_get_transient_for(GTK_WINDOW(this)); }
void UiWindow::transientFor(UiWindow *parent) { gtk_window_set_transient_for(GTK_WINDOW(this), GTK_WINDOW(parent)); }
GdkWindowTypeHint UiWindow::typeHint() const { return gtk_window_get_type_hint(GTK_WINDOW(this)); }
void UiWindow::typeHint(GdkWindowTypeHint hint) { gtk_window_set_type_hint(GTK_WINDOW(this), hint); }
bool UiWindow::urgencyHint() const { return gtk_window_get_urgency_hint(GTK_WINDOW(this)); }
void UiWindow::urgencyHint(bool hint) { gtk_window_set_urgency_hint(GTK_WINDOW(this), hint); }

bool UiWindow::ActivateDefault() { return gtk_window_activate_default(GTK_WINDOW(this)); }
bool UiWindow::ActivateFocus() { return gtk_window_activate_focus(GTK_WINDOW(this)); }
void UiWindow::AddAccelGroup(AccelGroup *accelGroup) { gtk_window_add_accel_group(GTK_WINDOW(this), GTK_ACCEL_GROUP(accelGroup)); }
void UiWindow::ChangeAtomProperty(Atom property, Atom type, int format, GdkPropMode mode, const ByteArray &data, int elementSize)
{
    gdk_property_change(GDK_WINDOW(this), property._atom, type._atom, format, mode, (const guchar*)data.data(), elementSize);
}

void UiWindow::Close() { gtk_window_close(GTK_WINDOW(this)); }
void UiWindow::Deiconify() { gtk_window_deiconify(GTK_WINDOW(this)); }
void UiWindow::DeleteAtomProperty(Atom property)
{
    gdk_property_delete(GDK_WINDOW(this), property._atom);
}

void UiWindow::FullScreen() { gtk_window_fullscreen(GTK_WINDOW(this)); }

void UiWindow::FullScreenOnMonitor(Screen *screen, int monitor) { gtk_window_fullscreen_on_monitor(GTK_WINDOW(this), GDK_SCREEN(screen), monitor); }

AtomProperty UiWindow::GetAtomProperty(Atom property, Atom type, ulong offset, ulong length, int pdelete) const
{
    guchar *data;
    AtomProperty p;
    GdkAtom atom;
    p.IsExist = gdk_property_get(GDK_WINDOW(this), property._atom, type._atom, offset, length, pdelete, &atom, &p.ActualFormat, &p.ActualLength, &data);
    p.ActualPropertyType = Atom(atom);
    p.Data = ByteArray((byte *)data, p.ActualLength);
    g_free(data);
    return p;
}

void UiWindow::Iconify() { gtk_window_iconify(GTK_WINDOW(this)); }
void UiWindow::Maximize() { gtk_window_maximize(GTK_WINDOW(this)); }
void UiWindow::Move(int x, int y) { gtk_window_move(GTK_WINDOW(this), x, y); }
void UiWindow::Move(Position pos) { this->Move(pos.X, pos.Y); }

void UiWindow::Present(uint timestamp)
{
    if(timestamp == 0)
        gtk_window_present(GTK_WINDOW(this));
    else
        gtk_window_present_with_time(GTK_WINDOW(this), timestamp);
}

void UiWindow::RemoveAccelGroup(AccelGroup *accelGroup) { gtk_window_remove_accel_group(GTK_WINDOW(this), GTK_ACCEL_GROUP(accelGroup)); }
void UiWindow::Resize(int width, int height) { gtk_window_resize(GTK_WINDOW(this), width, height); }
void UiWindow::SetAttachTo(BaseWidget *component) { gtk_window_set_attached_to(GTK_WINDOW(this), GTK_WIDGET(component)); }
bool UiWindow::SetIcon(const String16 &fileName)
{
    ByteArray utf8 = fileName.ToCString();
    const char *cStr = (const char *)utf8.data();
    GError *error;
    return gtk_window_set_icon_from_file(GTK_WINDOW(this), cStr, &error);
}

void UiWindow::SetGeometryHints(BaseWidget *geometryWidget, GdkGeometry *geo, GdkWindowHints geoMask) { gtk_window_set_geometry_hints(GTK_WINDOW(this), GTK_WIDGET(geometryWidget), geo, geoMask); }
void UiWindow::SetKeepAbove(bool keepAbove) { gtk_window_set_keep_above(GTK_WINDOW(this), keepAbove); }
void UiWindow::SetKeepBelow(bool keepBelow) { gtk_window_set_keep_below(GTK_WINDOW(this), keepBelow); }

void UiWindow::SetStartupId(const String16 &id)
{
    ByteArray utf8 = id.ToCString();
    const char *cStr = (const char *)utf8.data();
    gtk_window_set_startup_id(GTK_WINDOW(this), cStr);
}

void UiWindow::SetWindowPosition(GtkWindowPosition windPos) { gtk_window_set_position(GTK_WINDOW(this), windPos); }
void UiWindow::Stick() { gtk_window_stick(GTK_WINDOW(this)); }
void UiWindow::UnFullScreen() { gtk_window_unfullscreen(GTK_WINDOW(this)); }
void UiWindow::UnMaximize() { gtk_window_maximize(GTK_WINDOW(this)); }
void UiWindow::UnStick() { gtk_window_unstick(GTK_WINDOW(this)); }

Array<UiWindow *> UiWindow::Toplevels()
{
    GList* list = gtk_window_list_toplevels();
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

RawSignal UiWindow::Signals::ActivateDefault(SignalCallback eventMethod, void *instance, void *userData)
{
    VSignal *s = new VSignal();
    s->eventMethod = (void *)eventMethod;
    s->userData = userData;
    s->instance = instance;
    s->signalName = "activate-default";
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

RawSignal UiWindow::Signals::ActivateFocus(SignalCallback eventMethod, void *instance, void *userData)
{
    VSignal *s = new VSignal();
    s->eventMethod = (void *)eventMethod;
    s->userData = userData;
    s->instance = instance;
    s->signalName = "activate-focus";
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

RawSignal UiWindow::Signals::EnableDebugging(SignalCallback eventMethod, void *instance, void *userData)
{
    VSignal *s = new VSignal();
    s->eventMethod = (void *)eventMethod;
    s->userData = userData;
    s->instance = instance;
    s->signalName = "enable-debugging";
    void (*gtkmethod) (GtkWidget *, bool, gpointer) = [](GtkWidget *sender, bool grabbed, gpointer g) -> void{
        VSignal *signal = (VSignal *)g;
        EventArgs *eArgs = new EventArgs(nullptr);
        signal->args = eArgs;
        signal->args->EventSignal = signal;
        signal->args->UserData = signal->userData;
        if(signal->instance == nullptr){
            StaticSignalMethod_bool ssm = (StaticSignalMethod_bool)signal->eventMethod;
            ssm((BaseWidget *)sender, grabbed, signal->args);
        } else {
            InstanceSignalMethod_bool ism = (InstanceSignalMethod_bool)signal->eventMethod;
            ism(signal->instance, (BaseWidget *)sender, grabbed, signal->args);
        }
        delete eArgs;
    };
    s->callBack = G_CALLBACK(gtkmethod);
    return s;
}

RawSignal UiWindow::Signals::KeysChanged(SignalCallback eventMethod, void *instance, void *userData)
{
    VSignal *s = new VSignal();
    s->eventMethod = (void *)eventMethod;
    s->userData = userData;
    s->instance = instance;
    s->signalName = "keys-changed";
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

RawSignal UiWindow::Signals::SetFocus(SignalCallback eventMethod, void *instance, void *userData)
{
    VSignal *s = new VSignal();
    s->eventMethod = (void *)eventMethod;
    s->userData = userData;
    s->instance = instance;
    s->signalName = "set-focus";
    void (*gtkmethod) (GtkWidget *, GtkWidget *, gpointer) = [](GtkWidget *sender, GtkWidget *widget, gpointer g) -> void{
        VSignal *signal = (VSignal *)g;
        EventArgs *eArgs = new EventArgs(nullptr);
        signal->args = eArgs;
        signal->args->EventSignal = signal;
        signal->args->UserData = signal->userData;
        if(signal->instance == nullptr){
            StaticSignalMethod_GtkWid ssm = (StaticSignalMethod_GtkWid)signal->eventMethod;
            ssm((BaseWidget *)sender, (BaseWidget *)widget, signal->args);
        } else {
            InstanceSignalMethod_GtkWid ism = (InstanceSignalMethod_GtkWid)signal->eventMethod;
            ism(signal->instance, (BaseWidget *)sender, (BaseWidget *)widget, signal->args);
        }
        delete eArgs;
    };
    s->callBack = G_CALLBACK(gtkmethod);
    return s;
}
