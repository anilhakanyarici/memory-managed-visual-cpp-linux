#include "UiRadioButton.h"

Delegate(StaticSignalMethod, void, VObject *, EventArgs *);
Delegate(InstanceSignalMethod, void, void *, VObject *, EventArgs *);

UiRadioButton *UiRadioButton::New() { return (UiRadioButton *)gtk_radio_button_new(NULL); }

UiRadioButton *UiRadioButton::New(Array<UiRadioButton *> group)
{
    GSList *slist = g_slist_alloc();
    for(int i = 0; i < group.length(); i++)
        slist = g_slist_append(slist, GTK_WIDGET(group[i]));
    GtkWidget *rad = gtk_radio_button_new(slist);
    g_slist_free(slist);
    return (UiRadioButton *)rad;
}

UiRadioButton *UiRadioButton::New(UiRadioButton *groupMember)
{
    return (UiRadioButton *)gtk_radio_button_new_from_widget(GTK_RADIO_BUTTON(groupMember));
}

UiRadioButton *UiRadioButton::New(const String16 &label, bool mnemonic)
{
    ByteArray utf8 = label.ToCString();
    if(mnemonic)
        return (UiRadioButton *)gtk_radio_button_new_with_mnemonic(NULL, (const char *)utf8.data());
    else
        return (UiRadioButton *)gtk_radio_button_new_with_label(NULL, (const char *)utf8.data());
}

UiRadioButton *UiRadioButton::New(Array<UiRadioButton *> group, const String16 &label, bool mnemonic)
{
    GSList *slist = g_slist_alloc();
    for(int i = 0; i < group.length(); i++)
        slist = g_slist_append(slist, GTK_WIDGET(group[i]));
    ByteArray utf8 = label.ToCString();
    GtkWidget *rad;
    if(mnemonic)
        rad = gtk_radio_button_new_with_mnemonic(slist, (const char *)utf8.data());
    else
        rad = gtk_radio_button_new_with_label(slist, (const char *)utf8.data());
    g_slist_free(slist);
    return (UiRadioButton *)rad;
}

Array<UiRadioButton *> UiRadioButton::group() const
{
    GSList* list = gtk_radio_button_get_group(GTK_RADIO_BUTTON(this));
    guint len = g_slist_length(list);
    Array<UiRadioButton *> buttons = Array<UiRadioButton *>(len);

    GSList *curr = list;
    int i = 0;
    while(curr != NULL){
        buttons[i] = (UiRadioButton *)curr->data;
        curr = curr->next;
        i++;
    }
    g_slist_free(list);
    return buttons;
}

void UiRadioButton::group(Array<UiRadioButton *> group)
{
    GSList *slist = g_slist_alloc();
    for(int i = 0; i < group.length(); i++)
        slist = g_slist_append(slist, GTK_WIDGET(group[i]));
    gtk_radio_button_set_group(GTK_RADIO_BUTTON(this), slist);
    g_slist_free(slist);
}

void UiRadioButton::Join(UiRadioButton *groupSource)
{
    gtk_radio_button_join_group(GTK_RADIO_BUTTON(this), GTK_RADIO_BUTTON(groupSource));
}

RawSignal UiRadioButton::Signals::GroupChanged(SignalCallback eventMethod, void *instance, void *userData)
{
    VSignal *s = new VSignal();
    s->eventMethod = (void *)eventMethod;
    s->userData = userData;
    s->instance = instance;
    s->signalName = "group-changed";
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
