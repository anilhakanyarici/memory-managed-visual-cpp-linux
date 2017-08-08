#include "FlowBox.h"

Delegate(StaticSignalMethod, void, BaseWidget *, EventArgs *);
Delegate(InstanceSignalMethod, void, void *, BaseWidget *, EventArgs *);
Delegate(StaticSignalMethod_fbc, void, BaseWidget *, FlowBoxChild *, EventArgs *);
Delegate(InstanceSignalMethod_fbc, void, void *, BaseWidget *, FlowBoxChild *, EventArgs *);
Delegate(StaticSignalMethod_movStep_int, void, BaseWidget *, GtkMovementStep, int, EventArgs *);
Delegate(InstanceSignalMethod_movStep_int, void, void *, BaseWidget *, GtkMovementStep, int, EventArgs *);

FlowBox *FlowBox::New() { return (FlowBox *)gtk_flow_box_new(); }

bool FlowBox::activateOnSingleClick() const { return gtk_flow_box_get_activate_on_single_click(GTK_FLOW_BOX(this)); }
void FlowBox::activateOnSingleClick(bool h) { gtk_flow_box_set_activate_on_single_click(GTK_FLOW_BOX(this), h); }
bool FlowBox::homogenius() const { return gtk_flow_box_get_homogeneous(GTK_FLOW_BOX(this)); }
void FlowBox::homogenius(bool h) { gtk_flow_box_set_homogeneous(GTK_FLOW_BOX(this), h); }
uint FlowBox::rowSpacing() const { return gtk_flow_box_get_row_spacing(GTK_FLOW_BOX(this)); }
void FlowBox::rowSpacing(uint h) { gtk_flow_box_set_row_spacing(GTK_FLOW_BOX(this), h); }
GtkSelectionMode FlowBox::selectionMode() const { return gtk_flow_box_get_selection_mode(GTK_FLOW_BOX(this)); }
void FlowBox::selectionMode(GtkSelectionMode h) { gtk_flow_box_set_selection_mode(GTK_FLOW_BOX(this), h); }
uint FlowBox::columnSpacing() const { return gtk_flow_box_get_column_spacing(GTK_FLOW_BOX(this)); }
void FlowBox::columnSpacing(uint h) { gtk_flow_box_set_column_spacing(GTK_FLOW_BOX(this), h); }
uint FlowBox::minChildPerLine() const { return gtk_flow_box_get_min_children_per_line(GTK_FLOW_BOX(this)); }
void FlowBox::minChildPerLine(uint h) { gtk_flow_box_set_min_children_per_line(GTK_FLOW_BOX(this), h); }
uint FlowBox::maxChildPerLine() const { return gtk_flow_box_get_max_children_per_line(GTK_FLOW_BOX(this)); }
void FlowBox::maxChildPerLine(uint h) { gtk_flow_box_set_max_children_per_line(GTK_FLOW_BOX(this), h); }

void FlowBox::Insert(BaseWidget *child, int position) { gtk_flow_box_insert(GTK_FLOW_BOX(this), GTK_WIDGET(child), position); }
FlowBoxChild *FlowBox::GetChildAtIndex(int index) { return (FlowBoxChild *)gtk_flow_box_get_child_at_index(GTK_FLOW_BOX(this), index); }

Array<FlowBoxChild *> FlowBox::SelectedChildrens()
{
    GList* list = gtk_flow_box_get_selected_children(GTK_FLOW_BOX(this));
    guint len = g_list_length(list);
    Array<FlowBoxChild *> array = Array<FlowBoxChild *>(len);

    GList *curr = list;
    int i = 0;
    while(curr != NULL){
        array[i] = (FlowBoxChild *)curr->data;
        curr = curr->next;
        i++;
    }
    g_list_free(list);
    return array;
}

void FlowBox::SetHAdjustment(Adjustment *h) { gtk_flow_box_set_hadjustment(GTK_FLOW_BOX(this), GTK_ADJUSTMENT(h)); }
void FlowBox::SetVAdjustment(Adjustment *v) { gtk_flow_box_set_vadjustment(GTK_FLOW_BOX(this), GTK_ADJUSTMENT(v)); }
void FlowBox::Select(FlowBoxChild *child) { gtk_flow_box_select_child(GTK_FLOW_BOX(this), GTK_FLOW_BOX_CHILD(child)); }
void FlowBox::Unselect(FlowBoxChild *child) { gtk_flow_box_unselect_child(GTK_FLOW_BOX(this), GTK_FLOW_BOX_CHILD(child)); }
void FlowBox::SelectAll() { gtk_flow_box_select_all(GTK_FLOW_BOX(this)); }
void FlowBox::UnselectAll() { gtk_flow_box_unselect_all(GTK_FLOW_BOX(this)); }

RawSignal FlowBox::Signals::ActivateCursorChild(SignalCallback eventMethod, void *instance, void *userData)
{
    VSignal *s = new VSignal();
    s->eventMethod = (void *)eventMethod;
    s->userData = userData;
    s->instance = instance;
    s->signalName = "activate-cursor-child";
    void (*gtkmethod) (GtkFlowBox *, gpointer) = [](GtkFlowBox *sender, gpointer g) -> void{
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

RawSignal FlowBox::Signals::ChildActivated(SignalCallback eventMethod, void *instance, void *userData)
{
    VSignal *s = new VSignal();
    s->eventMethod = (void *)eventMethod;
    s->userData = userData;
    s->instance = instance;
    s->signalName = "child-activated";
    void (*gtkmethod) (GtkFlowBox *, GtkFlowBoxChild *, gpointer) = [](GtkFlowBox *sender, GtkFlowBoxChild *child, gpointer g) -> void{
        VSignal *signal = (VSignal *)g;
        EventArgs *eArgs = new EventArgs(nullptr);
        signal->args = eArgs;
        signal->args->EventSignal = signal;
        signal->args->UserData = signal->userData;
        if(signal->instance == nullptr){
            StaticSignalMethod_fbc ssm = (StaticSignalMethod_fbc)signal->eventMethod;
            ssm((BaseWidget *)sender, (FlowBoxChild *)child, signal->args);
        } else {
            InstanceSignalMethod_fbc ism = (InstanceSignalMethod_fbc)signal->eventMethod;
            ism(signal->instance, (BaseWidget *)sender, (FlowBoxChild *)child, signal->args);
        }
        delete eArgs;
    };
    s->callBack = G_CALLBACK(gtkmethod);
    return s;
}

RawSignal FlowBox::Signals::MoveCursor(SignalCallback eventMethod, void *instance, void *userData)
{
    VSignal *s = new VSignal();
    s->eventMethod = (void *)eventMethod;
    s->userData = userData;
    s->instance = instance;
    s->signalName = "move-cursor";
    bool (*gtkmethod) (GtkFlowBox *, GtkMovementStep, int, gpointer) = [](GtkFlowBox *sender, GtkMovementStep step, int count, gpointer g) -> bool{
        VSignal *signal = (VSignal *)g;
        EventArgs *eArgs = new EventArgs(nullptr);
        signal->args = eArgs;
        eArgs->CanStopHandlers = true;
        signal->args->EventSignal = signal;
        signal->args->UserData = signal->userData;
        if(signal->instance == nullptr){
            StaticSignalMethod_movStep_int ssm = (StaticSignalMethod_movStep_int)signal->eventMethod;
            ssm((BaseWidget *)sender, step, count, signal->args);
        } else {
            InstanceSignalMethod_movStep_int ism = (InstanceSignalMethod_movStep_int)signal->eventMethod;
            ism(signal->instance, (BaseWidget *)sender, step, count, signal->args);
        }
        bool stopHandlers = eArgs->StopOtherHandlers;
        delete eArgs;
        return stopHandlers;
    };
    s->callBack = G_CALLBACK(gtkmethod);
    return s;
}

RawSignal FlowBox::Signals::SelectAll(SignalCallback eventMethod, void *instance, void *userData)
{
    VSignal *s = new VSignal();
    s->eventMethod = (void *)eventMethod;
    s->userData = userData;
    s->instance = instance;
    s->signalName = "select-all";
    void (*gtkmethod) (GtkFlowBox *, gpointer) = [](GtkFlowBox *sender, gpointer g) -> void{
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

RawSignal FlowBox::Signals::SelectedChildrenChanged(SignalCallback eventMethod, void *instance, void *userData)
{
    VSignal *s = new VSignal();
    s->eventMethod = (void *)eventMethod;
    s->userData = userData;
    s->instance = instance;
    s->signalName = "selected-children-changed";
    void (*gtkmethod) (GtkFlowBox *, gpointer) = [](GtkFlowBox *sender, gpointer g) -> void{
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

RawSignal FlowBox::Signals::ToggleCursorChanged(SignalCallback eventMethod, void *instance, void *userData)
{
    VSignal *s = new VSignal();
    s->eventMethod = (void *)eventMethod;
    s->userData = userData;
    s->instance = instance;
    s->signalName = "toggle-cursor-child";
    void (*gtkmethod) (GtkFlowBox *, gpointer) = [](GtkFlowBox *sender, gpointer g) -> void{
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

RawSignal FlowBox::Signals::UnselectAll(SignalCallback eventMethod, void *instance, void *userData)
{
    VSignal *s = new VSignal();
    s->eventMethod = (void *)eventMethod;
    s->userData = userData;
    s->instance = instance;
    s->signalName = "unselect-all";
    void (*gtkmethod) (GtkFlowBox *, gpointer) = [](GtkFlowBox *sender, gpointer g) -> void{
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

RawSignal FlowBoxChild::Signals::Activate(SignalCallback eventMethod, void *instance, void *userData)
{
    VSignal *s = new VSignal();
    s->eventMethod = (void *)eventMethod;
    s->userData = userData;
    s->instance = instance;
    s->signalName = "activate";
    void (*gtkmethod) (GtkFlowBoxChild *, gpointer) = [](GtkFlowBoxChild *sender, gpointer g) -> void{
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

FlowBoxChild *FlowBoxChild::New() { return (FlowBoxChild *)gtk_flow_box_child_new(); }

int FlowBoxChild::index() const { return gtk_flow_box_child_get_index(GTK_FLOW_BOX_CHILD(this)); }

int FlowBoxChild::isSelected() const { return gtk_flow_box_child_is_selected(GTK_FLOW_BOX_CHILD(this)); }

void FlowBoxChild::MarkChanged() { gtk_flow_box_child_changed(GTK_FLOW_BOX_CHILD(this)); }
