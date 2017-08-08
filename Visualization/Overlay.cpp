#include "Overlay.h"

Delegate(StaticSignalMethod_GtkWid_rect, void, BaseWidget *, BaseWidget *, GdkRectangle *, EventArgs *);
Delegate(InstanceSignalMethod_GtkWid_rect, void, void *, BaseWidget *, BaseWidget *, GdkRectangle *, EventArgs *);

Overlay *Overlay::New() { return (Overlay *)gtk_overlay_new(); }

bool Overlay::GetOverlayPassThrough(BaseWidget *widget) const { return gtk_overlay_get_overlay_pass_through(GTK_OVERLAY(this), GTK_WIDGET(widget)); }

void Overlay::SetOverlayPassThrough(BaseWidget *widget, bool s) { gtk_overlay_set_overlay_pass_through(GTK_OVERLAY(this), GTK_WIDGET(widget), s); }

void Overlay::AddOverlay(BaseWidget *child) { gtk_overlay_add_overlay(GTK_OVERLAY(this), GTK_WIDGET(child)); }

void Overlay::ReorderOverlay(BaseWidget *child, int position) { gtk_overlay_reorder_overlay(GTK_OVERLAY(this), GTK_WIDGET(child), position); }

RawSignal Overlay::Signals::GetChildPosition(SignalCallback eventMethod, void *instance, void *userData)
{
    VSignal *s = new VSignal();
    s->eventMethod = (void *)eventMethod;
    s->userData = userData;
    s->instance = instance;
    s->signalName = "get-child-position";
    bool (*gtkmethod) (GtkWidget *, GtkWidget *, GdkRectangle *, gpointer) = [](GtkWidget *sender, GtkWidget *widget, GdkRectangle *rect, gpointer g) -> bool{
        VSignal *signal = (VSignal *)g;
        EventArgs *eArgs = new EventArgs(nullptr);
        signal->args = eArgs;
        eArgs->CanStopHandlers = true;
        signal->args->EventSignal = signal;
        signal->args->UserData = signal->userData;
        if(signal->instance == nullptr){
            StaticSignalMethod_GtkWid_rect ssm = (StaticSignalMethod_GtkWid_rect)signal->eventMethod;
            ssm((BaseWidget *)sender, (BaseWidget *)widget, rect, signal->args);
        } else {
            InstanceSignalMethod_GtkWid_rect ism = (InstanceSignalMethod_GtkWid_rect)signal->eventMethod;
            ism(signal->instance, (BaseWidget *)sender, (BaseWidget *)widget, rect, signal->args);
        }
        bool stopHandlers = eArgs->StopOtherHandlers;
        delete eArgs;
        return stopHandlers;
    };
    s->callBack = G_CALLBACK(gtkmethod);
    return s;
}
