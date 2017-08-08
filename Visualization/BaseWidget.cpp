#include <gtk/gtk.h>
#include "BaseWidget.h"
#include "../Char16.h"
#include "../String16.h"
#include "../ByteArray.h"
#include "../StringList.h"
#include "FrameClock.h"
#include "AccelGroup.h"
#include "StyleContext.h"
#include "WidgetPath.h"
#include "UiWindow.h"
#include "Display.h"

Delegate(StaticSignalMethod, void, BaseWidget *, EventArgs *);
Delegate(InstanceSignalMethod, void, void *, BaseWidget *, EventArgs *);
Delegate(StaticSignalMethod_CanActAcc, void, BaseWidget *, uint, EventArgs *);
Delegate(InstanceSignalMethod_CanActAcc, void, void *, BaseWidget *, uint, EventArgs *);
Delegate(StaticSignalMethod_DirCh, void, BaseWidget *, GtkTextDirection, EventArgs *);
Delegate(InstanceSignalMethod_DirCh, void, void *, BaseWidget *, GtkTextDirection, EventArgs *);
Delegate(StaticSignalMethod_DirType, void, BaseWidget *, GtkDirectionType, EventArgs *);
Delegate(InstanceSignalMethod_DirType, void, void *, BaseWidget *, GtkDirectionType, EventArgs *);
Delegate(StaticSignalMethod_bool, void, BaseWidget *, bool, EventArgs *);
Delegate(InstanceSignalMethod_bool, void, void *, BaseWidget *, bool, EventArgs *);
Delegate(StaticSignalMethod_GtkWid, void, BaseWidget *, BaseWidget *, EventArgs *);
Delegate(InstanceSignalMethod_GtkWid, void, void *, BaseWidget *, BaseWidget *, EventArgs *);
Delegate(StaticSignalMethod_Cairo, void, BaseWidget *, CairoGC *, EventArgs *);
Delegate(InstanceSignalMethod_Cairo, void, void *, BaseWidget *, CairoGC *, EventArgs *);
Delegate(StaticSignalMethod_Screen, void, BaseWidget *, Screen *, EventArgs *);
Delegate(InstanceSignalMethod_Screen, void, void *, BaseWidget *, Screen *, EventArgs *);


bool BaseWidget::inDestruction() const { return gtk_widget_in_destruction(GTK_WIDGET(this)); }
FrameClock *BaseWidget::frameClock() const { return (FrameClock *)(gtk_widget_get_frame_clock(GTK_WIDGET(this))); }
int BaseWidget::scaleFactor() const { return gtk_widget_get_scale_factor(GTK_WIDGET(this)); }
bool BaseWidget::isFocus() const { return gtk_widget_is_focus(GTK_WIDGET(this)); }

void BaseWidget::name(const String16 &name)
{
    ByteArray utf8 = name.ToCString();
    const char *cStr = (const char *)utf8.data();
    gtk_widget_set_name(GTK_WIDGET(this), cStr);
}

String16 BaseWidget::name() const { return String16(gtk_widget_get_name(GTK_WIDGET(this))); }
void BaseWidget::sensitive(bool sens) { gtk_widget_set_sensitive(GTK_WIDGET(this), sens); }
bool BaseWidget::sensitive() const { return gtk_widget_get_sensitive(GTK_WIDGET(this)); }
BaseWidget *BaseWidget::parent() const { return (BaseWidget *)gtk_widget_get_parent(GTK_WIDGET(this)); }
void BaseWidget::parent(BaseWidget *parent) { gtk_widget_set_parent(GTK_WIDGET(this), GTK_WIDGET(parent)); }
DWindow *BaseWidget::parentWindow() const { return (DWindow *)gtk_widget_get_parent_window(GTK_WIDGET(this)); }
void BaseWidget::parentWindow(DWindow *parent) { gtk_widget_set_parent_window(GTK_WIDGET(this), GDK_WINDOW(parent)); }
void BaseWidget::events(GdkEventMask events) { gtk_widget_set_events(GTK_WIDGET(this), (int)events); }
GdkEventMask BaseWidget::events() const { return (GdkEventMask)gtk_widget_get_events(GTK_WIDGET(this)); }
BaseWidget *BaseWidget::topLevelParent() const { return (BaseWidget *)gtk_widget_get_toplevel(GTK_WIDGET(this)); }
void BaseWidget::direction(GtkTextDirection direction) { gtk_widget_set_direction(GTK_WIDGET(this), direction); }
GtkTextDirection BaseWidget::direction() const { return gtk_widget_get_direction(GTK_WIDGET(this)); }
void BaseWidget::paintable(bool appPaintable) { gtk_widget_set_app_paintable(GTK_WIDGET(this), appPaintable); }
bool BaseWidget::paintable() const { return gtk_widget_get_app_paintable(GTK_WIDGET(this)); }
void BaseWidget::noShowAll(bool noShowAll) { gtk_widget_set_no_show_all(GTK_WIDGET(this), noShowAll); }
bool BaseWidget::noShowAll() const { return gtk_widget_get_no_show_all(GTK_WIDGET(this)); }

void BaseWidget::tooltipMarkup(const String16 &ttmarkup)
{
    ByteArray utf8 = ttmarkup.ToCString();
    const char *cStr = (const char *)utf8.data();
    gtk_widget_set_tooltip_markup(GTK_WIDGET(this), cStr);
}

String16 BaseWidget::tooltipMarkup() const
{
    gchar * s = gtk_widget_get_tooltip_markup(GTK_WIDGET(this));
    String16 str = String16((const char *)s);
    g_free(s);
    return str;
}

void BaseWidget::tooltipText(const String16 &tttext)
{
    ByteArray utf8 = tttext.ToCString();
    const char *cStr = (const char *)utf8.data();
    gtk_widget_set_tooltip_text(GTK_WIDGET(this), cStr);
}

String16 BaseWidget::tooltipText() const
{
    gchar * s = gtk_widget_get_tooltip_text(GTK_WIDGET(this));
    String16 str = String16((const char *)s);
    g_free(s);
    return str;
}

void BaseWidget::tooltipWindow(UiWindow *w) { gtk_widget_set_tooltip_window(GTK_WIDGET(this), GTK_WINDOW(w)); }
UiWindow *BaseWidget::tooltipWindow() const { return(UiWindow *)gtk_widget_get_tooltip_window(GTK_WIDGET(this)); }
void BaseWidget::hasTooltip(bool has) { gtk_widget_set_has_tooltip(GTK_WIDGET(this), has); }
bool BaseWidget::hasTooltip() const { return gtk_widget_get_has_tooltip(GTK_WIDGET(this)); }
int BaseWidget::getAllocatedWidth() const { return gtk_widget_get_allocated_width(GTK_WIDGET(this)); }
int BaseWidget::getAllocatedHeight() const { return gtk_widget_get_allocated_height(GTK_WIDGET(this)); }
int BaseWidget::getAllocatedBaseline() const { return gtk_widget_get_allocated_baseline(GTK_WIDGET(this)); }
void BaseWidget::allocation(const GtkAllocation *allocation) { gtk_widget_set_allocation(GTK_WIDGET(this), allocation); }

GtkAllocation BaseWidget::allocation() const
{
    GtkAllocation a;
    gtk_widget_get_allocation(GTK_WIDGET(this), &a);
    return a;
}

void BaseWidget::clip(GtkAllocation *clip) { gtk_widget_set_clip(GTK_WIDGET(this), clip); }

GtkAllocation BaseWidget::clip()
{
    GtkAllocation clip;
    gtk_widget_get_clip(GTK_WIDGET(this), &clip);
    return clip;
}

void BaseWidget::canDefault(bool can) { gtk_widget_set_can_default(GTK_WIDGET(this), can); }

bool BaseWidget::canDefault() const { return gtk_widget_get_can_focus(GTK_WIDGET(this)); }

void BaseWidget::canFocus(bool can) { gtk_widget_set_can_focus(GTK_WIDGET(this), can); }

bool BaseWidget::canFocus() const { return gtk_widget_get_can_focus(GTK_WIDGET(this)); }

void BaseWidget::hasWindow(bool has) { gtk_widget_set_has_window(GTK_WIDGET(this), has); }

bool BaseWidget::hasWindow() const { return gtk_widget_get_has_window(GTK_WIDGET(this)); }

long BaseWidget::getWidgetId() const { return (long)GTK_WIDGET(this); }

void BaseWidget::visible(bool visible) { gtk_widget_set_visible(GTK_WIDGET(this), visible); }

Visual *BaseWidget::visual() const { return (Visual *)gtk_widget_get_visual(GTK_WIDGET(this)); }

void BaseWidget::visual(Visual *v) { gtk_widget_set_visual(GTK_WIDGET(this), GDK_VISUAL(v)); }

bool BaseWidget::visible() const { return gtk_widget_is_visible(GTK_WIDGET(this)); }

DWindow *BaseWidget::window() const { return (DWindow *)gtk_widget_get_window(GTK_WIDGET(this)); }

void BaseWidget::window(DWindow *w) { gtk_widget_set_window(GTK_WIDGET(this), GDK_WINDOW(w)); }

void BaseWidget::stateFlags(GtkStateFlags flags) { gtk_widget_set_state_flags(GTK_WIDGET(this), flags, true); }

GtkStateFlags BaseWidget::stateFlags() const { return gtk_widget_get_state_flags(GTK_WIDGET(this)); }

bool BaseWidget::hasDefault() const { return gtk_widget_has_default(GTK_WIDGET(this)); }

bool BaseWidget::hasFocus() const { return gtk_widget_has_focus(GTK_WIDGET(this)); }

bool BaseWidget::hasVisibleFocus() const { return gtk_widget_has_visible_focus(GTK_WIDGET(this)); }

bool BaseWidget::hasGrab() const { return gtk_widget_has_grab(GTK_WIDGET(this)); }

bool BaseWidget::isDrawable() const { return gtk_widget_is_drawable(GTK_WIDGET(this)); }

bool BaseWidget::isTopLevel() const { return gtk_widget_is_toplevel(GTK_WIDGET(this)); }

bool BaseWidget::isNull() const { return GTK_WIDGET(this) == NULL; }

void BaseWidget::receivesDefault(bool rd) { gtk_widget_set_receives_default(GTK_WIDGET(this), rd); }

bool BaseWidget::receivesDefault() const { return gtk_widget_get_receives_default(GTK_WIDGET(this)); }

void BaseWidget::supportedMultidevice(bool smd) { gtk_widget_set_support_multidevice(GTK_WIDGET(this), smd); }

bool BaseWidget::supportedMultidevice() const { return gtk_widget_get_support_multidevice(GTK_WIDGET(this)); }

void BaseWidget::realized(bool realized) { gtk_widget_set_realized(GTK_WIDGET(this), realized); }

bool BaseWidget::realized() const { return gtk_widget_get_realized(GTK_WIDGET(this)); }

void BaseWidget::mapped(bool mapped) { gtk_widget_set_mapped(GTK_WIDGET(this), mapped); }

bool BaseWidget::mapped() const { return gtk_widget_get_mapped(GTK_WIDGET(this)); }

void BaseWidget::opacity(double opacity) { gtk_widget_set_opacity(GTK_WIDGET(this), opacity); }

double BaseWidget::opacity() const { return gtk_widget_get_opacity(GTK_WIDGET(this)); }

StringList BaseWidget::actionPrefixes() const
{
    StringList list = StringList();
    const gchar **prefs = gtk_widget_list_action_prefixes(GTK_WIDGET(this));
    int i = 0;
    const gchar *p = prefs[i];
    while(p != nullptr){
        list.Add((const char *)p);
        i++;
        p = prefs[i];
    }
    return list;
}

WidgetPath *BaseWidget::path() const { return (WidgetPath *)(gtk_widget_get_path(GTK_WIDGET(this))); }

StyleContext *BaseWidget::styleContext() const { return (StyleContext *)(gtk_widget_get_style_context(GTK_WIDGET(this))); }

PreferredHeight BaseWidget::preferredHeight() const
{
    PreferredHeight h;
    gtk_widget_get_preferred_height(GTK_WIDGET(this), &h.Minimum, &h.Natural);
    return h;
}

PreferredWidth BaseWidget::preferredWidth() const
{
    PreferredWidth w;
    gtk_widget_get_preferred_width(GTK_WIDGET(this), &w.Minimum, &w.Natural);
    return w;
}

PreferredHeight BaseWidget::preferredHeight(int width) const
{
    PreferredHeight h;
    gtk_widget_get_preferred_height_for_width(GTK_WIDGET(this), width, &h.Minimum, &h.Natural);
    return h;
}

PreferredWidth BaseWidget::preferredWidth(int height) const
{
    PreferredWidth w;
    gtk_widget_get_preferred_width_for_height(GTK_WIDGET(this), height, &w.Minimum, &w.Natural);
    return w;
}

GtkSizeRequestMode BaseWidget::sizeRequestMode() const { return gtk_widget_get_request_mode(GTK_WIDGET(this)); }

PreferredSize BaseWidget::preferedSize() const
{
    GtkRequisition *min = gtk_requisition_new();
    GtkRequisition *nat = gtk_requisition_new();
    gtk_widget_get_preferred_size(GTK_WIDGET(this), min, nat);
    PreferredSize size;
    size.Minimum.Height = min->height;
    size.Natural.Height = nat->height;
    size.Minimum.Width = min->width;
    size.Natural.Width = nat->width;
    gtk_requisition_free(min);
    gtk_requisition_free(nat);
    return size;
}

void BaseWidget::hAlign(GtkAlign align) { gtk_widget_set_halign(GTK_WIDGET(this), align); }
GtkAlign BaseWidget::hAlign() const { return gtk_widget_get_halign(GTK_WIDGET(this)); }
void BaseWidget::vAlign(GtkAlign align) { gtk_widget_set_valign(GTK_WIDGET(this), align); }
GtkAlign BaseWidget::vAlign() const { return gtk_widget_get_valign(GTK_WIDGET(this)); }
GtkAlign BaseWidget::vAlignWithBaseline() const { return gtk_widget_get_valign_with_baseline(GTK_WIDGET(this)); }
void BaseWidget::marginStart(int margin) { gtk_widget_set_margin_start(GTK_WIDGET(this), margin); }
int BaseWidget::marginStart() const { return gtk_widget_get_margin_start(GTK_WIDGET(this)); }
void BaseWidget::marginEnd(int margin) { gtk_widget_set_margin_end(GTK_WIDGET(this), margin); }
int BaseWidget::marginEnd() const { return gtk_widget_get_margin_end(GTK_WIDGET(this)); }
void BaseWidget::marginTop(int margin) { gtk_widget_set_margin_top(GTK_WIDGET(this), margin); }
int BaseWidget::marginTop() const { return gtk_widget_get_margin_top(GTK_WIDGET(this)); }
void BaseWidget::marginBottom(int margin) { gtk_widget_set_margin_bottom(GTK_WIDGET(this), margin); }
int BaseWidget::marginBottom() const { return gtk_widget_get_margin_bottom(GTK_WIDGET(this)); }
void BaseWidget::hExpand(bool expand) { gtk_widget_set_hexpand(GTK_WIDGET(this), expand); }
bool BaseWidget::hExpand() const { return gtk_widget_get_hexpand(GTK_WIDGET(this)); }
void BaseWidget::hExpandSet(bool expand) { gtk_widget_set_hexpand_set(GTK_WIDGET(this), expand); }
bool BaseWidget::hExpandSet() const { return gtk_widget_get_hexpand_set(GTK_WIDGET(this)); }
void BaseWidget::vExpand(bool expand) { gtk_widget_set_vexpand(GTK_WIDGET(this), expand); }
bool BaseWidget::vExpand() const { return gtk_widget_get_vexpand(GTK_WIDGET(this)); }
void BaseWidget::vExpandSet(bool expand) { gtk_widget_set_vexpand_set(GTK_WIDGET(this), expand); }
bool BaseWidget::vExpandSet() const { return gtk_widget_get_vexpand_set(GTK_WIDGET(this)); }
void BaseWidget::Destroy() { gtk_widget_destroy(GTK_WIDGET(this)); }

bool BaseWidget::Draw(CairoGC *gc)
{
    if(!this->isDrawable())
        return false;
    gtk_widget_draw(GTK_WIDGET(this), (cairo_t *)gc);
    return true;
}

bool BaseWidget::EmitMNemonicActivate(bool groupCycling) { return gtk_widget_mnemonic_activate(GTK_WIDGET(this), groupCycling); }
void BaseWidget::Unparent() { gtk_widget_unparent(GTK_WIDGET(this)); }
void BaseWidget::Show() { gtk_widget_show(GTK_WIDGET(this)); }
void BaseWidget::Hide() { gtk_widget_hide(GTK_WIDGET(this)); }
void BaseWidget::ShowAll() { gtk_widget_show_all(GTK_WIDGET(this)); }
void BaseWidget::Map() { gtk_widget_map(GTK_WIDGET(this)); }
void BaseWidget::Unmap() { gtk_widget_unmap(GTK_WIDGET(this)); }
void BaseWidget::Realize() { gtk_widget_realize(GTK_WIDGET(this)); }
void BaseWidget::RegisterWindow(DWindow *window) { gtk_widget_register_window(GTK_WIDGET(this), GDK_WINDOW(window)); }
void BaseWidget::Unrealize() { gtk_widget_unrealize(GTK_WIDGET(this)); }
void BaseWidget::UnregisterWindow(DWindow *window) { gtk_widget_unregister_window(GTK_WIDGET(this), GDK_WINDOW(window)); }
void BaseWidget::QueueDraw() { gtk_widget_queue_draw(GTK_WIDGET(this)); }
void BaseWidget::QueueResize() { gtk_widget_queue_resize(GTK_WIDGET(this)); }
void BaseWidget::QueueResizeNoReDraw() { gtk_widget_queue_resize_no_redraw(GTK_WIDGET(this)); }

void BaseWidget::AddAccelerator(const String16 &signal, AccelGroup *accelGroup, uint key, GdkModifierType mod, GtkAccelFlags flags)
{
    ByteArray utf8 = signal.ToCString();
    const char *cStr = (const char *)utf8.data();
    gtk_widget_add_accelerator(GTK_WIDGET(this), cStr, GTK_ACCEL_GROUP(accelGroup), key, mod, flags);
}

bool BaseWidget::RemoveAccelerator(AccelGroup *accelGroup, uint key, GdkModifierType mod) { return gtk_widget_remove_accelerator(GTK_WIDGET(this), GTK_ACCEL_GROUP(accelGroup), key, mod); }

void BaseWidget::SetAccelGroupPath(const String16 &path, AccelGroup *accelGroup)
{
    ByteArray utf8 = path.ToCString();
    const char *cStr = (const char *)utf8.data();
    gtk_widget_set_accel_path(GTK_WIDGET(this), cStr, GTK_ACCEL_GROUP(accelGroup));
}

bool BaseWidget::CanActivateAccelerator(uint signalId){ return gtk_widget_can_activate_accel(GTK_WIDGET(this), signalId); }
bool BaseWidget::Activate() { return gtk_widget_activate(GTK_WIDGET(this)); }
bool BaseWidget::Intersect(GdkRectangle &area, GdkRectangle &intersection) { return gtk_widget_intersect(GTK_WIDGET(this), &area, &intersection); }
void BaseWidget::GrabFocus() { gtk_widget_grab_focus(GTK_WIDGET(this)); }
void BaseWidget::GrabDefault() { gtk_widget_grab_default(GTK_WIDGET(this)); }
void BaseWidget::AddEvent(GdkEventMask event) { gtk_widget_add_events(GTK_WIDGET(this), (int)event); }
void BaseWidget::AddMNemonicLabel(BaseWidget *label) { gtk_widget_add_mnemonic_label(GTK_WIDGET(this), GTK_WIDGET(label)); }
void BaseWidget::RemoveMNemonicLabel(BaseWidget *label) { gtk_widget_remove_mnemonic_label(GTK_WIDGET(this), GTK_WIDGET(label)); }
BaseWidget *BaseWidget::GetAncestor(GType firstAncestorType) { return (BaseWidget *)gtk_widget_get_ancestor(GTK_WIDGET(this), firstAncestorType); }
bool BaseWidget::IsAncestor(BaseWidget *ancestor) { return gtk_widget_is_ancestor(GTK_WIDGET(this), GTK_WIDGET(ancestor)); }

bool BaseWidget::IsShadowed(Device *dev) { return gtk_widget_device_is_shadowed(GTK_WIDGET(this), GDK_DEVICE(dev)); }
bool BaseWidget::TranslateCoordinates(Position srcPos, BaseWidget *destination, Position *destPos) { return gtk_widget_translate_coordinates(GTK_WIDGET(this), GTK_WIDGET(destination), srcPos.X, srcPos.Y, &destPos->X, &destPos->Y); }
bool BaseWidget::HideOnDelete() { return gtk_widget_hide_on_delete(GTK_WIDGET(this)); }
void BaseWidget::ResetStyle() { gtk_widget_reset_style(GTK_WIDGET(this)); }
void BaseWidget::QueueDrawArea(int x, int y, int width, int height) { gtk_widget_queue_draw_area(GTK_WIDGET(this), x, y, width, height); }
void BaseWidget::SetRedrawOnAllocate(bool redraw) { gtk_widget_set_redraw_on_allocate(GTK_WIDGET(this), redraw); }
bool BaseWidget::ChildFocus(GtkDirectionType dirType) { return gtk_widget_child_focus(GTK_WIDGET(this), dirType); }

void BaseWidget::ChildNotify(const String16 &childProperty)
{
    ByteArray utf8 = childProperty.ToCString();
    const char *cStr = (const char *)utf8.data();
    gtk_widget_child_notify(GTK_WIDGET(this), cStr);
}

void BaseWidget::FreezeChildNotify() { gtk_widget_freeze_child_notify(GTK_WIDGET(this)); }

Array<BaseWidget *> BaseWidget::GetMNemonicLabels()
{
    GList* list = gtk_widget_list_mnemonic_labels(GTK_WIDGET(this));
    guint len = g_list_length(list);
    Array<BaseWidget *> labels = Array<BaseWidget *>(len);

    GList *curr = list;
    int i = 0;
    while(curr != NULL){
        labels[i] = (BaseWidget *)curr->data;
        curr = curr->next;
        i++;
    }
    g_list_free(list);
    return labels;
}
void BaseWidget::SetSizeRequest(int width, int height) { gtk_widget_set_size_request(GTK_WIDGET(this), width, height); }
void BaseWidget::ThawChildNotify() { gtk_widget_thaw_child_notify(GTK_WIDGET(this)); }
void BaseWidget::ErrorBell(){ gtk_widget_error_bell(GTK_WIDGET(this)); }
bool BaseWidget::KeyNavigationFailed(GtkDirectionType dirType) { return gtk_widget_keynav_failed(GTK_WIDGET(this), dirType); }
void BaseWidget::TriggerTooltipQuery() { gtk_widget_trigger_tooltip_query(GTK_WIDGET(this)); }
GdkModifierType BaseWidget::GetModifierMask(GdkModifierIntent intent) { return gtk_widget_get_modifier_mask(GTK_WIDGET(this), intent); }
void BaseWidget::QueueComputeExpand() { gtk_widget_queue_compute_expand(GTK_WIDGET(this)); }
bool BaseWidget::ComputeExpand(GtkOrientation orientation) { return gtk_widget_compute_expand(GTK_WIDGET(this), orientation); }
GtkTextDirection BaseWidget::defaultDirection() { return gtk_widget_get_default_direction(); }

RawSignal BaseWidget::Signals::AcceleratorClosuresChanged(SignalCallback eventMethod, void *instance, void *userData)
{
    VSignal *s = new VSignal();
    s->eventMethod = (void *)eventMethod;
    s->userData = userData;
    s->instance = instance;
    s->signalName = "accel-closures-changed";
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

RawSignal BaseWidget::Signals::ButtonPressEvent(SignalCallback eventMethod, void *instance, void *userData)
{
    VSignal *s = new VSignal();
    s->eventMethod = (void *)eventMethod;
    s->userData = userData;
    s->instance = instance;
    s->signalName = "button-press-event";
    bool (*gtkmethod) (GtkWidget *, GdkEvent *, gpointer) = [](GtkWidget *sender, GdkEvent *e, gpointer g) -> bool{
        VSignal *signal = (VSignal *)g;
        ButtonEventArgs *eArgs = new ButtonEventArgs(e);
        eArgs->CanStopHandlers = true;
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
        bool stopHandler = eArgs->StopOtherHandlers;
        delete eArgs;
        return stopHandler;
    };
    s->callBack = G_CALLBACK(gtkmethod);
    return s;
}

RawSignal BaseWidget::Signals::ButtonReleaseEvent(SignalCallback eventMethod, void *instance, void *userData)
{
    VSignal *s = new VSignal();
    s->eventMethod = (void *)eventMethod;
    s->userData = userData;
    s->instance = instance;
    s->signalName = "button-release-event";
    bool (*gtkmethod) (GtkWidget *, GdkEvent *, gpointer) = [](GtkWidget *sender, GdkEvent *e, gpointer g) -> bool{
        VSignal *signal = (VSignal *)g;
        ButtonEventArgs *eArgs = new ButtonEventArgs(e);
        eArgs->CanStopHandlers = true;
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
        bool stopHandler = eArgs->StopOtherHandlers;
        delete eArgs;
        return stopHandler;
    };
    s->callBack = G_CALLBACK(gtkmethod);
    return s;
}

RawSignal BaseWidget::Signals::CanActivateAccelerator(SignalCallback eventMethod, void *instance, void *userData)
{
    VSignal *s = new VSignal();
    s->eventMethod = (void *)eventMethod;
    s->userData = userData;
    s->instance = instance;
    s->signalName = "can-activate-accel";
    bool (*gtkmethod) (GtkWidget *, guint, gpointer) = [](GtkWidget *sender, guint accSignalId, gpointer g) -> bool{
        VSignal *signal = (VSignal *)g;
        EventArgs *eArgs = new EventArgs(nullptr);
        eArgs->CanStopHandlers = true;
        signal->args = eArgs;
        signal->args->EventSignal = signal;
        signal->args->UserData = signal->userData;
        if(signal->instance == nullptr){
            StaticSignalMethod_CanActAcc ssm = (StaticSignalMethod_CanActAcc)signal->eventMethod;
            ssm((BaseWidget *)sender, accSignalId, signal->args);
        } else {
            InstanceSignalMethod_CanActAcc ism = (InstanceSignalMethod_CanActAcc)signal->eventMethod;
            ism(signal->instance, (BaseWidget *)sender, accSignalId, signal->args);
        }
        bool stopHandler = eArgs->StopOtherHandlers;
        delete eArgs;
        return stopHandler;
    };
    s->callBack = G_CALLBACK(gtkmethod);
    return s;
}

RawSignal BaseWidget::Signals::ConfigureEvent(SignalCallback eventMethod, void *instance, void *userData)
{
    VSignal *s = new VSignal();
    s->eventMethod = (void *)eventMethod;
    s->userData = userData;
    s->instance = instance;
    s->signalName = "configure-event";
    bool (*gtkmethod) (GtkWidget *, GdkEvent *, gpointer) = [](GtkWidget *sender, GdkEvent *e, gpointer g) -> bool{
        VSignal *signal = (VSignal *)g;
        ConfigureEventArgs *eArgs = new ConfigureEventArgs(e);
        eArgs->CanStopHandlers = true;
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
        bool stopHandler = eArgs->StopOtherHandlers;
        delete eArgs;
        return stopHandler;
    };
    s->callBack = G_CALLBACK(gtkmethod);
    return s;
}

RawSignal BaseWidget::Signals::DamageEvent(SignalCallback eventMethod, void *instance, void *userData)
{
    VSignal *s = new VSignal();
    s->eventMethod = (void *)eventMethod;
    s->userData = userData;
    s->instance = instance;
    s->signalName = "damage-event";
    bool (*gtkmethod) (GtkWidget *, GdkEvent *, gpointer) = [](GtkWidget *sender, GdkEvent *e, gpointer g) -> bool{
        VSignal *signal = (VSignal *)g;
        ExposeEventArgs *eArgs = new ExposeEventArgs(e);
        eArgs->CanStopHandlers = true;
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
        bool stopHandler = eArgs->StopOtherHandlers;
        delete eArgs;
        return stopHandler;
    };
    s->callBack = G_CALLBACK(gtkmethod);
    return s;
}

RawSignal BaseWidget::Signals::DeleteEvent(SignalCallback eventMethod, void *instance, void *userData)
{
    VSignal *s = new VSignal();
    s->eventMethod = (void *)eventMethod;
    s->userData = userData;
    s->instance = instance;
    s->signalName = "delete-event";
    bool (*gtkmethod) (GtkWidget *, GdkEvent *, gpointer) = [](GtkWidget *sender, GdkEvent *e, gpointer g) -> bool{
        VSignal *signal = (VSignal *)g;
        EventArgs *eArgs = new EventArgs(e);
        eArgs->CanStopHandlers = true;
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
        bool stopHandler = eArgs->StopOtherHandlers;
        delete eArgs;
        return stopHandler;
    };
    s->callBack = G_CALLBACK(gtkmethod);
    return s;
}

RawSignal BaseWidget::Signals::Destroy(SignalCallback eventMethod, void *instance, void *userData)
{
    VSignal *s = new VSignal();
    s->eventMethod = (void *)eventMethod;
    s->userData = userData;
    s->instance = instance;
    s->signalName = "destroy";
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

RawSignal BaseWidget::Signals::DestroyEvent(SignalCallback eventMethod, void *instance, void *userData)
{
    VSignal *s = new VSignal();
    s->eventMethod = (void *)eventMethod;
    s->userData = userData;
    s->instance = instance;
    s->signalName = "destroy-event";
    bool (*gtkmethod) (GtkWidget *, GdkEvent *, gpointer) = [](GtkWidget *sender, GdkEvent *e, gpointer g) -> bool{
        VSignal *signal = (VSignal *)g;
        EventArgs *eArgs = new EventArgs(e);
        eArgs->CanStopHandlers = true;
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
        bool stopHandler = eArgs->StopOtherHandlers;
        delete eArgs;
        return stopHandler;
    };
    s->callBack = G_CALLBACK(gtkmethod);
    return s;
}

RawSignal BaseWidget::Signals::DirectionChanged(SignalCallback eventMethod, void *instance, void *userData)
{
    VSignal *s = new VSignal();
    s->eventMethod = (void *)eventMethod;
    s->userData = userData;
    s->instance = instance;
    s->signalName = "direction-changed";
    void (*gtkmethod) (GtkWidget *, GtkTextDirection, gpointer) = [](GtkWidget *sender, GtkTextDirection dir, gpointer g) -> void{
        VSignal *signal = (VSignal *)g;
        EventArgs *eArgs = new EventArgs(nullptr);
        signal->args = eArgs;
        signal->args->EventSignal = signal;
        signal->args->UserData = signal->userData;
        if(signal->instance == nullptr){
            StaticSignalMethod_DirCh ssm = (StaticSignalMethod_DirCh)signal->eventMethod;
            ssm((BaseWidget *)sender, dir, signal->args);
        } else {
            InstanceSignalMethod_DirCh ism = (InstanceSignalMethod_DirCh)signal->eventMethod;
            ism(signal->instance, (BaseWidget *)sender, dir, signal->args);
        }
        delete eArgs;
    };
    s->callBack = G_CALLBACK(gtkmethod);
    return s;
}

RawSignal BaseWidget::Signals::Draw(SignalCallback eventMethod, void *instance, void *userData)
{
    VSignal *s = new VSignal();
    s->eventMethod = (void *)eventMethod;
    s->userData = userData;
    s->instance = instance;
    s->signalName = "draw";
    bool (*gtkmethod) (GtkWidget *, cairo_t *, gpointer) = [](GtkWidget *sender, cairo_t * gc, gpointer g) -> bool{
        VSignal *signal = (VSignal *)g;
        EventArgs *eArgs = new EventArgs(nullptr);
        signal->args = eArgs;
        eArgs->CanStopHandlers = true;
        signal->args->EventSignal = signal;
        signal->args->UserData = signal->userData;
        CairoGC *cairo = (CairoGC *)(gc);
        if(signal->instance == nullptr){
            StaticSignalMethod_Cairo ssm = (StaticSignalMethod_Cairo)signal->eventMethod;
            ssm((BaseWidget *)sender, cairo, signal->args);
        } else {
            InstanceSignalMethod_Cairo ism = (InstanceSignalMethod_Cairo)signal->eventMethod;
            ism(signal->instance, (BaseWidget *)sender, cairo, signal->args);
        }
        bool stopHandlers = eArgs->StopOtherHandlers;
        delete eArgs;
        return stopHandlers;
    };
    s->callBack = G_CALLBACK(gtkmethod);
    return s;
}

RawSignal BaseWidget::Signals::PointerEnterNotify(SignalCallback eventMethod, void *instance, void *userData)
{
    VSignal *s = new VSignal();
    s->eventMethod = (void *)eventMethod;
    s->userData = userData;
    s->instance = instance;
    s->signalName = "enter-notify-event";
    bool (*gtkmethod) (GtkWidget *, GdkEvent *, gpointer) = [](GtkWidget *sender, GdkEvent *e, gpointer g) -> bool{
        VSignal *signal = (VSignal *)g;
        CrossingEventArgs *eArgs = new CrossingEventArgs(e);
        eArgs->CanStopHandlers = true;
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
        bool stopHandler = eArgs->StopOtherHandlers;
        delete eArgs;
        return stopHandler;
    };
    s->callBack = G_CALLBACK(gtkmethod);
    return s;
}

RawSignal BaseWidget::Signals::Focus(SignalCallback eventMethod, void *instance, void *userData)
{
    VSignal *s = new VSignal();
    s->eventMethod = (void *)eventMethod;
    s->userData = userData;
    s->instance = instance;
    s->signalName = "focus";
    bool (*gtkmethod) (GtkWidget *, GtkDirectionType, gpointer) = [](GtkWidget *sender, GtkDirectionType dir, gpointer g) -> bool{
        VSignal *signal = (VSignal *)g;
        EventArgs *eArgs = new EventArgs(nullptr);
        eArgs->CanStopHandlers = true;
        signal->args = eArgs;
        signal->args->EventSignal = signal;
        signal->args->UserData = signal->userData;
        if(signal->instance == nullptr){
            StaticSignalMethod_DirType ssm = (StaticSignalMethod_DirType)signal->eventMethod;
            ssm((BaseWidget *)sender, dir, signal->args);
        } else {
            InstanceSignalMethod_DirType ism = (InstanceSignalMethod_DirType)signal->eventMethod;
            ism(signal->instance, (BaseWidget *)sender, dir, signal->args);
        }
        bool stopHandler = eArgs->StopOtherHandlers;
        delete eArgs;
        return stopHandler;
    };
    s->callBack = G_CALLBACK(gtkmethod);
    return s;
}

RawSignal BaseWidget::Signals::FocusInEvent(SignalCallback eventMethod, void *instance, void *userData)
{
    VSignal *s = new VSignal();
    s->eventMethod = (void *)eventMethod;
    s->userData = userData;
    s->instance = instance;
    s->signalName = "focus-in-event";
    bool (*gtkmethod) (GtkWidget *, GdkEvent *, gpointer) = [](GtkWidget *sender, GdkEvent *e, gpointer g) -> bool{
        VSignal *signal = (VSignal *)g;
        FocusChangedEventArgs *eArgs = new FocusChangedEventArgs(e);
        eArgs->CanStopHandlers = true;
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
        bool stopHandler = eArgs->StopOtherHandlers;
        delete eArgs;
        return stopHandler;
    };
    s->callBack = G_CALLBACK(gtkmethod);
    return s;
}

RawSignal BaseWidget::Signals::FocusOutEvent(SignalCallback eventMethod, void *instance, void *userData)
{
    VSignal *s = new VSignal();
    s->eventMethod = (void *)eventMethod;
    s->userData = userData;
    s->instance = instance;
    s->signalName = "focus-out-event";
    bool (*gtkmethod) (GtkWidget *, GdkEvent *, gpointer) = [](GtkWidget *sender, GdkEvent *e, gpointer g) -> bool{
        VSignal *signal = (VSignal *)g;
        FocusChangedEventArgs *eArgs = new FocusChangedEventArgs(e);
        eArgs->CanStopHandlers = true;
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
        bool stopHandler = eArgs->StopOtherHandlers;
        delete eArgs;
        return stopHandler;
    };
    s->callBack = G_CALLBACK(gtkmethod);
    return s;
}

RawSignal BaseWidget::Signals::GrabBrokenEvent(SignalCallback eventMethod, void *instance, void *userData)
{
    VSignal *s = new VSignal();
    s->eventMethod = (void *)eventMethod;
    s->userData = userData;
    s->instance = instance;
    s->signalName = "grab-broken-event";
    bool (*gtkmethod) (GtkWidget *, GdkEvent *, gpointer) = [](GtkWidget *sender, GdkEvent *e, gpointer g) -> bool{
        VSignal *signal = (VSignal *)g;
        GrabBrokenEventArgs *eArgs = new GrabBrokenEventArgs(e);
        eArgs->CanStopHandlers = true;
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
        bool stopHandler = eArgs->StopOtherHandlers;
        delete eArgs;
        return stopHandler;
    };
    s->callBack = G_CALLBACK(gtkmethod);
    return s;
}

RawSignal BaseWidget::Signals::GrabFocus(SignalCallback eventMethod, void *instance, void *userData)
{
    VSignal *s = new VSignal();
    s->eventMethod = (void *)eventMethod;
    s->userData = userData;
    s->instance = instance;
    s->signalName = "grab-focus";
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

RawSignal BaseWidget::Signals::GrabNotify(SignalCallback eventMethod, void *instance, void *userData)
{
    VSignal *s = new VSignal();
    s->eventMethod = (void *)eventMethod;
    s->userData = userData;
    s->instance = instance;
    s->signalName = "grab-notify";
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

RawSignal BaseWidget::Signals::Hide(SignalCallback eventMethod, void *instance, void *userData)
{
    VSignal *s = new VSignal();
    s->eventMethod = (void *)eventMethod;
    s->userData = userData;
    s->instance = instance;
    s->signalName = "hide";
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

RawSignal BaseWidget::Signals::HierarchyChanged(SignalCallback eventMethod, void *instance, void *userData)
{
    VSignal *s = new VSignal();
    s->eventMethod = (void *)eventMethod;
    s->userData = userData;
    s->instance = instance;
    s->signalName = "hierarchy-changed";
    void (*gtkmethod) (GtkWidget *, GtkWidget *, gpointer) = [](GtkWidget *sender, GtkWidget *oldParent, gpointer g) -> void{
        VSignal *signal = (VSignal *)g;
        EventArgs *eArgs = new EventArgs(nullptr);

        signal->args = eArgs;
        signal->args->EventSignal = signal;
        signal->args->UserData = signal->userData;
        if(signal->instance == nullptr){
            StaticSignalMethod_GtkWid ssm = (StaticSignalMethod_GtkWid)signal->eventMethod;
            ssm((BaseWidget *)sender, (BaseWidget *)oldParent, signal->args);
        } else {
            InstanceSignalMethod_GtkWid ism = (InstanceSignalMethod_GtkWid)signal->eventMethod;
            ism(signal->instance, (BaseWidget *)sender, (BaseWidget *)oldParent, signal->args);
        }
        delete eArgs;
    };
    s->callBack = G_CALLBACK(gtkmethod);
    return s;
}

RawSignal BaseWidget::Signals::KeyPressEvent(SignalCallback eventMethod, void *instance, void *userData)
{
    VSignal *s = new VSignal();
    s->eventMethod = (void *)eventMethod;
    s->userData = userData;
    s->instance = instance;
    s->signalName = "key-press-event";
    bool (*gtkmethod) (GtkWidget *, GdkEvent *, gpointer) = [](GtkWidget *sender, GdkEvent *e, gpointer g) -> bool{
        VSignal *signal = (VSignal *)g;
        KeyEventArgs *eArgs = new KeyEventArgs(e);
        eArgs->CanStopHandlers = true;
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
        bool stopHandler = eArgs->StopOtherHandlers;
        delete eArgs;
        return stopHandler;
    };
    s->callBack = G_CALLBACK(gtkmethod);
    return s;
}

RawSignal BaseWidget::Signals::KeyReleaseEvent(SignalCallback eventMethod, void *instance, void *userData)
{
    VSignal *s = new VSignal();
    s->eventMethod = (void *)eventMethod;
    s->userData = userData;
    s->instance = instance;
    s->signalName = "key-release-event";
    bool (*gtkmethod) (GtkWidget *, GdkEvent *, gpointer) = [](GtkWidget *sender, GdkEvent *e, gpointer g) -> bool{
        VSignal *signal = (VSignal *)g;
        KeyEventArgs *eArgs = new KeyEventArgs(e);
        eArgs->CanStopHandlers = true;
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
        bool stopHandler = eArgs->StopOtherHandlers;
        delete eArgs;
        return stopHandler;
    };
    s->callBack = G_CALLBACK(gtkmethod);
    return s;
}

RawSignal BaseWidget::Signals::KeyNavigationFailed(SignalCallback eventMethod, void *instance, void *userData)
{
    VSignal *s = new VSignal();
    s->eventMethod = (void *)eventMethod;
    s->userData = userData;
    s->instance = instance;
    s->signalName = "keynav-failed";
    bool (*gtkmethod) (GtkWidget *, GtkDirectionType, gpointer) = [](GtkWidget *sender, GtkDirectionType dir, gpointer g) -> bool{
        VSignal *signal = (VSignal *)g;
        EventArgs *eArgs = new EventArgs(nullptr);
        eArgs->CanStopHandlers = true;
        signal->args = eArgs;
        signal->args->EventSignal = signal;
        signal->args->UserData = signal->userData;
        if(signal->instance == nullptr){
            StaticSignalMethod_DirType ssm = (StaticSignalMethod_DirType)signal->eventMethod;
            ssm((BaseWidget *)sender, dir, signal->args);
        } else {
            InstanceSignalMethod_DirType ism = (InstanceSignalMethod_DirType)signal->eventMethod;
            ism(signal->instance, (BaseWidget *)sender, dir, signal->args);
        }
        bool stopHandler = eArgs->StopOtherHandlers;
        delete eArgs;
        return stopHandler;
    };
    s->callBack = G_CALLBACK(gtkmethod);
    return s;
}

RawSignal BaseWidget::Signals::PointerLeaveNotify(SignalCallback eventMethod, void *instance, void *userData)
{
    VSignal *s = new VSignal();
    s->eventMethod = (void *)eventMethod;
    s->userData = userData;
    s->instance = instance;
    s->signalName = "leave-notify-event";
    bool (*gtkmethod) (GtkWidget *, GdkEvent *, gpointer) = [](GtkWidget *sender, GdkEvent *e, gpointer g) -> bool{
        VSignal *signal = (VSignal *)g;
        CrossingEventArgs *eArgs = new CrossingEventArgs(e);
        eArgs->CanStopHandlers = true;
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
        bool stopHandler = eArgs->StopOtherHandlers;
        delete eArgs;
        return stopHandler;
    };
    s->callBack = G_CALLBACK(gtkmethod);
    return s;
}

RawSignal BaseWidget::Signals::Map(SignalCallback eventMethod, void *instance, void *userData)
{
    VSignal *s = new VSignal();
    s->eventMethod = (void *)eventMethod;
    s->userData = userData;
    s->instance = instance;
    s->signalName = "map";
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

RawSignal BaseWidget::Signals::MapEvent(SignalCallback eventMethod, void *instance, void *userData)
{
    VSignal *s = new VSignal();
    s->eventMethod = (void *)eventMethod;
    s->userData = userData;
    s->instance = instance;
    s->signalName = "map-event";
    bool (*gtkmethod) (GtkWidget *, GdkEvent *, gpointer) = [](GtkWidget *sender, GdkEvent *e, gpointer g) -> bool{
        VSignal *signal = (VSignal *)g;
        EventArgs *eArgs = new EventArgs(e);
        eArgs->CanStopHandlers = true;
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
        bool stopHandler = eArgs->StopOtherHandlers;
        delete eArgs;
        return stopHandler;
    };
    s->callBack = G_CALLBACK(gtkmethod);
    return s;
}

RawSignal BaseWidget::Signals::MNemonicActivate(SignalCallback eventMethod, void *instance, void *userData)
{
    VSignal *s = new VSignal();
    s->eventMethod = (void *)eventMethod;
    s->userData = userData;
    s->instance = instance;
    s->signalName = "mnemonic-activate";
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

RawSignal BaseWidget::Signals::MotionNotify(SignalCallback eventMethod, void *instance, void *userData)
{
    VSignal *s = new VSignal();
    s->eventMethod = (void *)eventMethod;
    s->userData = userData;
    s->instance = instance;
    s->signalName = "motion-notify-event";
    bool (*gtkmethod) (GtkWidget *, GdkEvent *, gpointer) = [](GtkWidget *sender, GdkEvent *e, gpointer g) -> bool{
        VSignal *signal = (VSignal *)g;
        MotionEventArgs *eArgs = new MotionEventArgs(e);
        eArgs->CanStopHandlers = true;
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
        bool stopHandler = eArgs->StopOtherHandlers;
        delete eArgs;
        return stopHandler;
    };
    s->callBack = G_CALLBACK(gtkmethod);
    return s;
}

RawSignal BaseWidget::Signals::MoveFocus(SignalCallback eventMethod, void *instance, void *userData)
{
    VSignal *s = new VSignal();
    s->eventMethod = (void *)eventMethod;
    s->userData = userData;
    s->instance = instance;
    s->signalName = "move-focus";
    void (*gtkmethod) (GtkWidget *, GtkDirectionType, gpointer) = [](GtkWidget *sender, GtkDirectionType dir, gpointer g) -> void{
        VSignal *signal = (VSignal *)g;
        EventArgs *eArgs = new EventArgs(nullptr);
        signal->args = eArgs;
        signal->args->EventSignal = signal;
        signal->args->UserData = signal->userData;
        if(signal->instance == nullptr){
            StaticSignalMethod_DirType ssm = (StaticSignalMethod_DirType)signal->eventMethod;
            ssm((BaseWidget *)sender, dir, signal->args);
        } else {
            InstanceSignalMethod_DirType ism = (InstanceSignalMethod_DirType)signal->eventMethod;
            ism(signal->instance, (BaseWidget *)sender, dir, signal->args);
        }
        delete eArgs;
    };
    s->callBack = G_CALLBACK(gtkmethod);
    return s;
}

RawSignal BaseWidget::Signals::ParentSet(SignalCallback eventMethod, void *instance, void *userData)
{
    VSignal *s = new VSignal();
    s->eventMethod = (void *)eventMethod;
    s->userData = userData;
    s->instance = instance;
    s->signalName = "parent-set";
    void (*gtkmethod) (GtkWidget *, GtkWidget *, gpointer) = [](GtkWidget *sender, GtkWidget *oldParent, gpointer g) -> void{
        VSignal *signal = (VSignal *)g;
        EventArgs *eArgs = new EventArgs(nullptr);

        signal->args = eArgs;
        signal->args->EventSignal = signal;
        signal->args->UserData = signal->userData;
        if(signal->instance == nullptr){
            StaticSignalMethod_GtkWid ssm = (StaticSignalMethod_GtkWid)signal->eventMethod;
            ssm((BaseWidget *)sender, (BaseWidget *)oldParent, signal->args);
        } else {
            InstanceSignalMethod_GtkWid ism = (InstanceSignalMethod_GtkWid)signal->eventMethod;
            ism(signal->instance, (BaseWidget *)sender, (BaseWidget *)oldParent, signal->args);
        }
        delete eArgs;
    };
    s->callBack = G_CALLBACK(gtkmethod);
    return s;
}

RawSignal BaseWidget::Signals::PopupMenu(SignalCallback eventMethod, void *instance, void *userData)
{
    VSignal *s = new VSignal();
    s->eventMethod = (void *)eventMethod;
    s->userData = userData;
    s->instance = instance;
    s->signalName = "popup-menu";
    bool (*gtkmethod) (GtkWidget *, gpointer) = [](GtkWidget *sender, gpointer g) -> bool{
        VSignal *signal = (VSignal *)g;
        EventArgs *eArgs = new EventArgs(nullptr);
        eArgs->CanStopHandlers = true;
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
        bool stopHandler = eArgs->StopOtherHandlers;
        delete eArgs;
        return stopHandler;
    };
    s->callBack = G_CALLBACK(gtkmethod);
    return s;
}

RawSignal BaseWidget::Signals::PropertyNotifyEvent(SignalCallback eventMethod, void *instance, void *userData)
{
    VSignal *s = new VSignal();
    s->eventMethod = (void *)eventMethod;
    s->userData = userData;
    s->instance = instance;
    s->signalName = "property-notify-event";
    bool (*gtkmethod) (GtkWidget *, GdkEvent *, gpointer) = [](GtkWidget *sender, GdkEvent *e, gpointer g) -> bool{
        VSignal *signal = (VSignal *)g;
        PropertyEventArgs *eArgs = new PropertyEventArgs(e);
        eArgs->CanStopHandlers = true;
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
        bool stopHandler = eArgs->StopOtherHandlers;
        delete eArgs;
        return stopHandler;
    };
    s->callBack = G_CALLBACK(gtkmethod);
    return s;
}

RawSignal BaseWidget::Signals::ProximityInEvent(SignalCallback eventMethod, void *instance, void *userData)
{
    VSignal *s = new VSignal();
    s->eventMethod = (void *)eventMethod;
    s->userData = userData;
    s->instance = instance;
    s->signalName = "proximity-in-event";
    bool (*gtkmethod) (GtkWidget *, GdkEvent *, gpointer) = [](GtkWidget *sender, GdkEvent *e, gpointer g) -> bool{
        VSignal *signal = (VSignal *)g;
        ProximityEventArgs *eArgs = new ProximityEventArgs(e);
        eArgs->CanStopHandlers = true;
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
        bool stopHandler = eArgs->StopOtherHandlers;
        delete eArgs;
        return stopHandler;
    };
    s->callBack = G_CALLBACK(gtkmethod);
    return s;
}

RawSignal BaseWidget::Signals::ProximityOutEvent(SignalCallback eventMethod, void *instance, void *userData)
{
    VSignal *s = new VSignal();
    s->eventMethod = (void *)eventMethod;
    s->userData = userData;
    s->instance = instance;
    s->signalName = "proximity-out-event";
    bool (*gtkmethod) (GtkWidget *, GdkEvent *, gpointer) = [](GtkWidget *sender, GdkEvent *e, gpointer g) -> bool{
        VSignal *signal = (VSignal *)g;
        ProximityEventArgs *eArgs = new ProximityEventArgs(e);
        eArgs->CanStopHandlers = true;
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
        bool stopHandler = eArgs->StopOtherHandlers;
        delete eArgs;
        return stopHandler;
    };
    s->callBack = G_CALLBACK(gtkmethod);
    return s;
}

RawSignal BaseWidget::Signals::Realize(SignalCallback eventMethod, void *instance, void *userData)
{
    VSignal *s = new VSignal();
    s->eventMethod = (void *)eventMethod;
    s->userData = userData;
    s->instance = instance;
    s->signalName = "realize";
    void (*gtkmethod) (GtkWidget *, gpointer) = [](GtkWidget *sender, gpointer g) -> void{
        VSignal *signal = (VSignal *)g;
        EventArgs *eArgs = new EventArgs(nullptr);
        eArgs->CanStopHandlers = true;
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

RawSignal BaseWidget::Signals::ScrollEvent(SignalCallback eventMethod, void *instance, void *userData)
{
    VSignal *s = new VSignal();
    s->eventMethod = (void *)eventMethod;
    s->userData = userData;
    s->instance = instance;
    s->signalName = "scroll-event";
    bool (*gtkmethod) (GtkWidget *, GdkEvent *, gpointer) = [](GtkWidget *sender, GdkEvent *e, gpointer g) -> bool{
        VSignal *signal = (VSignal *)g;
        ScrollEventArgs *eArgs = new ScrollEventArgs(e);
        eArgs->CanStopHandlers = true;
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
        bool stopHandler = eArgs->StopOtherHandlers;
        delete eArgs;
        return stopHandler;
    };
    s->callBack = G_CALLBACK(gtkmethod);
    return s;
}

RawSignal BaseWidget::Signals::ScreenChanged(SignalCallback eventMethod, void *instance, void *userData)
{
    VSignal *s = new VSignal();
    s->eventMethod = (void *)eventMethod;
    s->userData = userData;
    s->instance = instance;
    s->signalName = "screen-changed";
    void (*gtkmethod) (GtkWidget *, GdkScreen *, gpointer) = [](GtkWidget *sender, GdkScreen *prevScreen, gpointer g) -> void{
        VSignal *signal = (VSignal *)g;
        EventArgs *eArgs = new EventArgs(nullptr);
        signal->args = eArgs;
        signal->args->EventSignal = signal;
        signal->args->UserData = signal->userData;
        if(signal->instance == nullptr){
            StaticSignalMethod_Screen ssm = (StaticSignalMethod_Screen)signal->eventMethod;
            ssm((BaseWidget *)sender, (Screen *)prevScreen, signal->args);
        } else {
            InstanceSignalMethod_Screen ism = (InstanceSignalMethod_Screen)signal->eventMethod;
            ism(signal->instance, (BaseWidget *)sender, (Screen *)prevScreen, signal->args);
        }
        delete eArgs;
    };
    s->callBack = G_CALLBACK(gtkmethod);
    return s;
}

RawSignal BaseWidget::Signals::SelectionClearEvent(SignalCallback eventMethod, void *instance, void *userData)
{
    VSignal *s = new VSignal();
    s->eventMethod = (void *)eventMethod;
    s->userData = userData;
    s->instance = instance;
    s->signalName = "selection-clear-event";
    bool (*gtkmethod) (GtkWidget *, GdkEvent *, gpointer) = [](GtkWidget *sender, GdkEvent *e, gpointer g) -> bool{
        VSignal *signal = (VSignal *)g;
        SelectionEventArgs *eArgs = new SelectionEventArgs(e);
        eArgs->CanStopHandlers = true;
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
        bool stopHandler = eArgs->StopOtherHandlers;
        delete eArgs;
        return stopHandler;
    };
    s->callBack = G_CALLBACK(gtkmethod);
    return s;
}

RawSignal BaseWidget::Signals::SelectionNotifyEvent(SignalCallback eventMethod, void *instance, void *userData)
{
    VSignal *s = new VSignal();
    s->eventMethod = (void *)eventMethod;
    s->userData = userData;
    s->instance = instance;
    s->signalName = "selection-notify-event";
    bool (*gtkmethod) (GtkWidget *, GdkEvent *, gpointer) = [](GtkWidget *sender, GdkEvent *e, gpointer g) -> bool{
        VSignal *signal = (VSignal *)g;
        SelectionEventArgs *eArgs = new SelectionEventArgs(e);
        eArgs->CanStopHandlers = true;
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
        bool stopHandler = eArgs->StopOtherHandlers;
        delete eArgs;
        return stopHandler;
    };
    s->callBack = G_CALLBACK(gtkmethod);
    return s;
}

RawSignal BaseWidget::Signals::SelectionRequestEvent(SignalCallback eventMethod, void *instance, void *userData)
{
    VSignal *s = new VSignal();
    s->eventMethod = (void *)eventMethod;
    s->userData = userData;
    s->instance = instance;
    s->signalName = "selection-request-event";
    bool (*gtkmethod) (GtkWidget *, GdkEvent *, gpointer) = [](GtkWidget *sender, GdkEvent *e, gpointer g) -> bool{
        VSignal *signal = (VSignal *)g;
        SelectionEventArgs *eArgs = new SelectionEventArgs(e);
        eArgs->CanStopHandlers = true;
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
        bool stopHandler = eArgs->StopOtherHandlers;
        delete eArgs;
        return stopHandler;
    };
    s->callBack = G_CALLBACK(gtkmethod);
    return s;
}

RawSignal BaseWidget::Signals::Show(SignalCallback eventMethod, void *instance, void *userData)
{
    VSignal *s = new VSignal();
    s->eventMethod = (void *)eventMethod;
    s->userData = userData;
    s->instance = instance;
    s->signalName = "show";
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

RawSignal BaseWidget::Signals::StyleUpdated(SignalCallback eventMethod, void *instance, void *userData)
{
    VSignal *s = new VSignal();
    s->eventMethod = (void *)eventMethod;
    s->userData = userData;
    s->instance = instance;
    s->signalName = "style-updated";
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

RawSignal BaseWidget::Signals::TouchEvent(SignalCallback eventMethod, void *instance, void *userData)
{
    VSignal *s = new VSignal();
    s->eventMethod = (void *)eventMethod;
    s->userData = userData;
    s->instance = instance;
    s->signalName = "touch-event";
    bool (*gtkmethod) (GtkWidget *, GdkEvent *, gpointer) = [](GtkWidget *sender, GdkEvent *e, gpointer g) -> bool{
        VSignal *signal = (VSignal *)g;
        TouchEventArgs *eArgs = new TouchEventArgs(e);
        eArgs->CanStopHandlers = true;
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
        bool stopHandler = eArgs->StopOtherHandlers;
        delete eArgs;
        return stopHandler;
    };
    s->callBack = G_CALLBACK(gtkmethod);
    return s;
}

RawSignal BaseWidget::Signals::Unmap(SignalCallback eventMethod, void *instance, void *userData)
{
    VSignal *s = new VSignal();
    s->eventMethod = (void *)eventMethod;
    s->userData = userData;
    s->instance = instance;
    s->signalName = "unmap";
    void (*gtkmethod) (GtkWidget *, gpointer) = [](GtkWidget *sender, gpointer g) -> void{
        VSignal *signal = (VSignal *)g;
        EventArgs *eArgs = new EventArgs(nullptr);
        eArgs->CanStopHandlers = true;
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

RawSignal BaseWidget::Signals::UnmapEvent(SignalCallback eventMethod, void *instance, void *userData)
{
    VSignal *s = new VSignal();
    s->eventMethod = (void *)eventMethod;
    s->userData = userData;
    s->instance = instance;
    s->signalName = "unmap-event";
    bool (*gtkmethod) (GtkWidget *, GdkEvent *, gpointer) = [](GtkWidget *sender, GdkEvent *e, gpointer g) -> bool{
        VSignal *signal = (VSignal *)g;
        EventArgs *eArgs = new EventArgs(e);
        eArgs->CanStopHandlers = true;
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
        bool stopHandler = eArgs->StopOtherHandlers;
        delete eArgs;
        return stopHandler;
    };
    s->callBack = G_CALLBACK(gtkmethod);
    return s;
}

RawSignal BaseWidget::Signals::UnRealize(SignalCallback eventMethod, void *instance, void *userData)
{
    VSignal *s = new VSignal();
    s->eventMethod = (void *)eventMethod;
    s->userData = userData;
    s->instance = instance;
    s->signalName = "unrealize";
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

RawSignal BaseWidget::Signals::WindowStateEvent(SignalCallback eventMethod, void *instance, void *userData)
{
    VSignal *s = new VSignal();
    s->eventMethod = (void *)eventMethod;
    s->userData = userData;
    s->instance = instance;
    s->signalName = "window-state-event";
    bool (*gtkmethod) (GtkWidget *, GdkEvent *, gpointer) = [](GtkWidget *sender, GdkEvent *e, gpointer g) -> bool{
        VSignal *signal = (VSignal *)g;
        WindowStateEventArgs *eArgs = new WindowStateEventArgs(e);
        eArgs->CanStopHandlers = true;
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
        bool stopHandler = eArgs->StopOtherHandlers;
        delete eArgs;
        return stopHandler;
    };
    s->callBack = G_CALLBACK(gtkmethod);
    return s;
}
