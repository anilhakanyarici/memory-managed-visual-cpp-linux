#include "ListBox.h"

Delegate(StaticSignalMethod, void, BaseWidget *, EventArgs *);
Delegate(InstanceSignalMethod, void, void *, BaseWidget *, EventArgs *);
Delegate(StaticSignalMethod_ListBoxRow, void, BaseWidget *, ListBoxRow *, EventArgs *);
Delegate(InstanceSignalMethod_ListBoxRow, void, void *, BaseWidget *, ListBoxRow *, EventArgs *);
Delegate(StaticSignalMethod_MovStep_int, void, BaseWidget *, GtkMovementStep, int, EventArgs *);
Delegate(InstanceSignalMethod_MovStep_int, void, void *, BaseWidget *, GtkMovementStep, int, EventArgs *);

ListBox *ListBox::New()
{
    return (ListBox *)gtk_list_box_new();
}

bool ListBox::activateOnSingleClick() const { return gtk_list_box_get_activate_on_single_click(GTK_LIST_BOX(this)); }
void ListBox::activateOnSingleClick(bool m) { gtk_list_box_set_activate_on_single_click(GTK_LIST_BOX(this), m); }
Adjustment *ListBox::adjustment() const { return (Adjustment *)(gtk_list_box_get_adjustment(GTK_LIST_BOX(this))); }
void ListBox::adjustment(Adjustment *a) { gtk_list_box_set_adjustment(GTK_LIST_BOX(this), GTK_ADJUSTMENT(a)); }
GtkSelectionMode ListBox::mode() const { return gtk_list_box_get_selection_mode(GTK_LIST_BOX(this)); }
void ListBox::mode(GtkSelectionMode m) { gtk_list_box_set_selection_mode(GTK_LIST_BOX(this), m); }

ListBoxRow *ListBox::selectedRow() const
{
    return (ListBoxRow *)gtk_list_box_get_selected_row(GTK_LIST_BOX(this));;
}

void ListBox::selectedRow(ListBoxRow *row) { gtk_list_box_select_row(GTK_LIST_BOX(this), GTK_LIST_BOX_ROW(row)); }
void ListBox::DragHighlightRow(ListBoxRow *row) { gtk_list_box_drag_highlight_row(GTK_LIST_BOX(this), GTK_LIST_BOX_ROW(row)); }
void ListBox::DragUnighlightRow() { gtk_list_box_drag_unhighlight_row(GTK_LIST_BOX(this)); }
void ListBox::InvalidateFilter() { gtk_list_box_invalidate_filter(GTK_LIST_BOX(this)); }
void ListBox::InvalidateHeaders() { gtk_list_box_invalidate_headers(GTK_LIST_BOX(this)); }
void ListBox::InvalidateSort() { gtk_list_box_invalidate_sort(GTK_LIST_BOX(this)); }
void ListBox::Prepend(BaseWidget *child, int position) { gtk_list_box_insert(GTK_LIST_BOX(this), GTK_WIDGET(child), position); }
void ListBox::Prepend(BaseWidget *child) { gtk_list_box_prepend(GTK_LIST_BOX(this), GTK_WIDGET(child)); }

ListBoxRow *ListBox::RowAtIndex(int index)
{
    return (ListBoxRow *)gtk_list_box_get_row_at_index(GTK_LIST_BOX(this), index);
}

ListBoxRow *ListBox::RowAtY(int y)
{
    return (ListBoxRow *)gtk_list_box_get_row_at_y(GTK_LIST_BOX(this), y);
}

void ListBox::SelectAll() { gtk_list_box_select_all(GTK_LIST_BOX(this)); }
void ListBox::SetPlaceholder(BaseWidget *placeholder) { gtk_list_box_set_placeholder(GTK_LIST_BOX(this), GTK_WIDGET(placeholder)); }

Array<ListBoxRow *> ListBox::SelectedRows()
{
    GList * list = gtk_list_box_get_selected_rows(GTK_LIST_BOX(this));
    int len = g_list_length(list);
    Array<ListBoxRow *> array = Array<ListBoxRow *>(len);

    GList *curr = list;
    int i = 0;
    while(curr != NULL){
        array[i] = (ListBoxRow *)curr->data;
        curr = curr->next;
        i++;
    }
    g_list_free(list);
    return array;
}

void ListBox::UnselectAll() { gtk_list_box_unselect_all(GTK_LIST_BOX(this)); }
void ListBox::UnselectRow(ListBoxRow *row) { gtk_list_box_unselect_row(GTK_LIST_BOX(this), GTK_LIST_BOX_ROW(row)); }

ListBoxRow *ListBoxRow::New() { return (ListBoxRow *)gtk_list_box_row_new(); }

int ListBoxRow::activatable() const { return gtk_list_box_row_get_activatable(GTK_LIST_BOX_ROW(this)); }
void ListBoxRow::activatable(bool a) { gtk_list_box_row_set_activatable(GTK_LIST_BOX_ROW(this), a); }
int ListBoxRow::getIndex() const { return gtk_list_box_row_get_index(GTK_LIST_BOX_ROW(this)); }
BaseWidget *ListBoxRow::header() const { return (BaseWidget *)gtk_list_box_row_get_header(GTK_LIST_BOX_ROW(this)); }
void ListBoxRow::header(BaseWidget *w) { gtk_list_box_row_set_header(GTK_LIST_BOX_ROW(this), GTK_WIDGET(w)); }
bool ListBoxRow::isSelected() const { return gtk_list_box_row_is_selected(GTK_LIST_BOX_ROW(this)); }
int ListBoxRow::selectable() const { return gtk_list_box_row_get_selectable(GTK_LIST_BOX_ROW(this)); }
void ListBoxRow::selectable(bool a) { gtk_list_box_row_set_selectable(GTK_LIST_BOX_ROW(this), a); }

void ListBoxRow::MarkChanged() { gtk_list_box_row_changed(GTK_LIST_BOX_ROW(this)); }

RawSignal ListBoxRow::Signals::Activate(SignalCallback eventMethod, void *instance, void *userData)
{
    VSignal *s = new VSignal();
    s->eventMethod = (void *)eventMethod;
    s->userData = userData;
    s->instance = instance;
    s->signalName = "activate";
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

RawSignal ListBox::Signals::ActivateCursorRow(SignalCallback eventMethod, void *instance, void *userData)
{
    VSignal *s = new VSignal();
    s->eventMethod = (void *)eventMethod;
    s->userData = userData;
    s->instance = instance;
    s->signalName = "activate-cursor-row";
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

RawSignal ListBox::Signals::MoveCursor(SignalCallback eventMethod, void *instance, void *userData)
{
    VSignal *s = new VSignal();
    s->eventMethod = (void *)eventMethod;
    s->userData = userData;
    s->instance = instance;
    s->signalName = "move-cursor";
    void (*gtkmethod) (GtkWidget *, GtkMovementStep, int, gpointer) = [](GtkWidget *sender, GtkMovementStep step, int arg, gpointer g) -> void{
        VSignal *signal = (VSignal *)g;
        EventArgs *eArgs = new EventArgs(nullptr);
        signal->args = eArgs;
        signal->args->EventSignal = signal;
        signal->args->UserData = signal->userData;
        if(signal->instance == nullptr){
            StaticSignalMethod_MovStep_int ssm = (StaticSignalMethod_MovStep_int)signal->eventMethod;
            ssm((BaseWidget *)sender, step, arg, signal->args);
        } else {
            InstanceSignalMethod_MovStep_int ism = (InstanceSignalMethod_MovStep_int)signal->eventMethod;
            ism(signal->instance, (BaseWidget *)sender, step, arg, signal->args);
        }
        delete eArgs;
    };
    s->callBack = G_CALLBACK(gtkmethod);
    return s;
}

RawSignal ListBox::Signals::RowActivated(SignalCallback eventMethod, void *instance, void *userData)
{
    VSignal *s = new VSignal();
    s->eventMethod = (void *)eventMethod;
    s->userData = userData;
    s->instance = instance;
    s->signalName = "row-activated";
    void (*gtkmethod) (GtkWidget *, GtkListBoxRow *, gpointer) = [](GtkWidget *sender, GtkListBoxRow *row, gpointer g) -> void{
        VSignal *signal = (VSignal *)g;
        EventArgs *eArgs = new EventArgs(nullptr);
        signal->args = eArgs;
        signal->args->EventSignal = signal;
        signal->args->UserData = signal->userData;
        ListBoxRow *lbr = (ListBoxRow *)(row);
        if(signal->instance == nullptr){
            StaticSignalMethod_ListBoxRow ssm = (StaticSignalMethod_ListBoxRow)signal->eventMethod;
            ssm((BaseWidget *)sender, lbr, signal->args);
        } else {
            InstanceSignalMethod_ListBoxRow ism = (InstanceSignalMethod_ListBoxRow)signal->eventMethod;
            ism(signal->instance, (BaseWidget *)sender, lbr, signal->args);
        }
        delete eArgs;
    };
    s->callBack = G_CALLBACK(gtkmethod);
    return s;
}

RawSignal ListBox::Signals::RowSelected(SignalCallback eventMethod, void *instance, void *userData)
{
    VSignal *s = new VSignal();
    s->eventMethod = (void *)eventMethod;
    s->userData = userData;
    s->instance = instance;
    s->signalName = "row-selected";
    void (*gtkmethod) (GtkWidget *, GtkListBoxRow *, gpointer) = [](GtkWidget *sender, GtkListBoxRow *row, gpointer g) -> void{
        VSignal *signal = (VSignal *)g;
        EventArgs *eArgs = new EventArgs(nullptr);
        signal->args = eArgs;
        signal->args->EventSignal = signal;
        signal->args->UserData = signal->userData;
        ListBoxRow *lbr = (ListBoxRow *)row;
        if(signal->instance == nullptr){
            StaticSignalMethod_ListBoxRow ssm = (StaticSignalMethod_ListBoxRow)signal->eventMethod;
            ssm((BaseWidget *)sender, lbr, signal->args);
        } else {
            InstanceSignalMethod_ListBoxRow ism = (InstanceSignalMethod_ListBoxRow)signal->eventMethod;
            ism(signal->instance, (BaseWidget *)sender, lbr, signal->args);
        }
        delete eArgs;
    };
    s->callBack = G_CALLBACK(gtkmethod);
    return s;
}

RawSignal ListBox::Signals::SelectAll(SignalCallback eventMethod, void *instance, void *userData)
{
    VSignal *s = new VSignal();
    s->eventMethod = (void *)eventMethod;
    s->userData = userData;
    s->instance = instance;
    s->signalName = "select-all";
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

RawSignal ListBox::Signals::SelectedRowChanged(SignalCallback eventMethod, void *instance, void *userData)
{
    VSignal *s = new VSignal();
    s->eventMethod = (void *)eventMethod;
    s->userData = userData;
    s->instance = instance;
    s->signalName = "selected-rows-changed";
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

RawSignal ListBox::Signals::ToggleCursorRow(SignalCallback eventMethod, void *instance, void *userData)
{
    VSignal *s = new VSignal();
    s->eventMethod = (void *)eventMethod;
    s->userData = userData;
    s->instance = instance;
    s->signalName = "toggle-cursor-row";
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

RawSignal ListBox::Signals::UnselectAll(SignalCallback eventMethod, void *instance, void *userData)
{
    VSignal *s = new VSignal();
    s->eventMethod = (void *)eventMethod;
    s->userData = userData;
    s->instance = instance;
    s->signalName = "unselect-all";
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
