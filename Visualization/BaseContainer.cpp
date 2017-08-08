#include "BaseContainer.h"
#include "WidgetPath.h"

Delegate(StaticSignalMethod, void, BaseWidget *, EventArgs *);
Delegate(InstanceSignalMethod, void, void *, BaseWidget *, EventArgs *);
Delegate(StaticSignalMethod_GtkWid, void, BaseWidget *, BaseWidget *, EventArgs *);
Delegate(InstanceSignalMethod_GtkWid, void, void *, BaseWidget *, BaseWidget *, EventArgs *);

uint BaseContainer::borderWidth() const { return gtk_container_get_border_width(GTK_CONTAINER(this)); }

void BaseContainer::borderWidth(uint width) { gtk_container_set_border_width(GTK_CONTAINER(this), width); }

Array<BaseWidget *> BaseContainer::childs()
{
    GList *list = gtk_container_get_children(GTK_CONTAINER(this));
    int len = (int)g_list_length(list);
    Array<BaseWidget *> array = Array<BaseWidget *>(len);
    GList *curr = list;
    int i = 0;
    while(curr != NULL){
        array[i] = (BaseWidget *)curr->data;
        curr = curr->next;
        i++;
    }
    g_list_free(list);
    return array;
}

BaseWidget *BaseContainer::focusChild() { return (BaseWidget *)gtk_container_get_focus_child(GTK_CONTAINER(this)); }

void BaseContainer::focusChild(BaseWidget *child) { gtk_container_set_focus_child(GTK_CONTAINER(this), GTK_WIDGET(child)); }

void BaseContainer::Add(BaseWidget *component) { gtk_container_add(GTK_CONTAINER(this), GTK_WIDGET(component)); }

void BaseContainer::CheckResize() { gtk_container_check_resize(GTK_CONTAINER(this)); }

void BaseContainer::Remove(BaseWidget *component) { gtk_container_remove(GTK_CONTAINER(this), GTK_WIDGET(component)); }

WidgetPath *BaseContainer::GetChildPath(BaseWidget *child) { return (WidgetPath*)(gtk_container_get_path_for_child(GTK_CONTAINER(this), GTK_WIDGET(child))); }

Adjustment *BaseContainer::focusVAdjustment() const { return (Adjustment *)gtk_container_get_focus_vadjustment(GTK_CONTAINER(this)); }

void BaseContainer::focusVAdjustment(Adjustment *a) { gtk_container_set_focus_vadjustment(GTK_CONTAINER(this), GTK_ADJUSTMENT(a)); }

Adjustment *BaseContainer::focusHAdjustment() const { return (Adjustment *)gtk_container_get_focus_hadjustment(GTK_CONTAINER(this)); }

void BaseContainer::focusHAdjustment(Adjustment *a) { gtk_container_set_focus_hadjustment(GTK_CONTAINER(this), GTK_ADJUSTMENT(a)); }

void BaseContainer::PropagateDraw(BaseWidget *child, CairoGC *cr)
{
    gtk_container_propagate_draw(GTK_CONTAINER(this), GTK_WIDGET(child), (cairo_t *)cr);
}

RawSignal BaseContainer::Signals::Add(SignalCallback eventMethod, void *instance, void *userData)
{
    VSignal *s = new VSignal();
    s->eventMethod = (void *)eventMethod;
    s->userData = userData;
    s->instance = instance;
    s->signalName = "add";
    void (*gtkmethod) (GtkContainer *, GtkWidget *, gpointer) = [](GtkContainer *sender, GtkWidget *widget, gpointer g) -> void{
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

RawSignal BaseContainer::Signals::CheckResize(SignalCallback eventMethod, void *instance, void *userData)
{
    VSignal *s = new VSignal();
    s->eventMethod = (void *)eventMethod;
    s->userData = userData;
    s->instance = instance;
    s->signalName = "check-resize";
    void (*gtkmethod) (GtkContainer *, gpointer) = [](GtkContainer *sender, gpointer g) -> void{
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

RawSignal BaseContainer::Signals::Remove(SignalCallback eventMethod, void *instance, void *userData)
{
    VSignal *s = new VSignal();
    s->eventMethod = (void *)eventMethod;
    s->userData = userData;
    s->instance = instance;
    s->signalName = "remove";
    void (*gtkmethod) (GtkContainer *, GtkWidget *, gpointer) = [](GtkContainer *sender, GtkWidget *widget, gpointer g) -> void{
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

RawSignal BaseContainer::Signals::SetFocusChild(SignalCallback eventMethod, void *instance, void *userData)
{
    VSignal *s = new VSignal();
    s->eventMethod = (void *)eventMethod;
    s->userData = userData;
    s->instance = instance;
    s->signalName = "set-focus-child";
    void (*gtkmethod) (GtkContainer *, GtkWidget *, gpointer) = [](GtkContainer *sender, GtkWidget *widget, gpointer g) -> void{
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
