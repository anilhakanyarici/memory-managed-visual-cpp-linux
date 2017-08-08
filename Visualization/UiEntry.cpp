#include "UiEntry.h"

Delegate(StaticSignalMethod, void, BaseWidget *, EventArgs *);
Delegate(InstanceSignalMethod, void, void *, BaseWidget *, EventArgs *);
Delegate(StaticSignalMethod_GtkWid, void, BaseWidget *, BaseWidget *, EventArgs *);
Delegate(InstanceSignalMethod_GtkWid, void, void *, BaseWidget *, BaseWidget *, EventArgs *);
Delegate(StaticSignalMethod_GtkDel_Int, void, BaseWidget *, GtkDeleteType, int, EventArgs *);
Delegate(InstanceSignalMethod_GtkDel_Int, void, void *, BaseWidget *, GtkDeleteType, int, EventArgs *);
Delegate(StaticSignalMethod_Str, void, BaseWidget *, String16, EventArgs *);
Delegate(InstanceSignalMethod_Str, void, void *, BaseWidget *, String16, EventArgs *);
Delegate(StaticSignalMethod_MovStep_Int_bool, void, BaseWidget *, GtkMovementStep, int, bool, EventArgs *);
Delegate(InstanceSignalMethod_MovStep_Int_bool, void, void *, BaseWidget *, GtkMovementStep, int, bool, EventArgs *);


EntryBuffer *EntryBuffer::New(const String16 &initialString)
{
    ByteArray utf8 = initialString.ToCString();
    return (EntryBuffer *)gtk_entry_buffer_new((const gchar *)utf8.data(), utf8.length() - 1);
}

String16 EntryBuffer::text() const { return String16((const char *)gtk_entry_buffer_get_text(GTK_ENTRY_BUFFER(this))); }

void EntryBuffer::text(const String16 &text)
{
    ByteArray utf8 = text.ToCString();
    gtk_entry_buffer_set_text(GTK_ENTRY_BUFFER(this), (const gchar *)utf8.data(), utf8.length() - 1);
}

uint EntryBuffer::length() const { return gtk_entry_buffer_get_length(GTK_ENTRY_BUFFER(this)); }
uint EntryBuffer::maxLength() const { return gtk_entry_buffer_get_max_length(GTK_ENTRY_BUFFER(this)); }
void EntryBuffer::maxLength(uint maxLength) { return gtk_entry_buffer_set_max_length(GTK_ENTRY_BUFFER(this), maxLength); }

UiEntry *UiEntry::New()
{
    return (UiEntry *)gtk_entry_new();
}

UiEntry *UiEntry::New(const String16 &text)
{
    GtkWidget *e = gtk_entry_new();
    ByteArray utf8 = text.ToCString();
    gtk_entry_set_text(GTK_ENTRY(e), (const char *)utf8.data());
    return (UiEntry *)e;
}

UiEntry *UiEntry::New(EntryBuffer *buffer)
{
    return (UiEntry *)gtk_entry_new_with_buffer(GTK_ENTRY_BUFFER(buffer));
}

EntryBuffer *UiEntry::buffer() const { return (EntryBuffer *)(gtk_entry_get_buffer(GTK_ENTRY(this))); }
void UiEntry::buffer(EntryBuffer *buffer) { gtk_entry_set_buffer(GTK_ENTRY(this), GTK_ENTRY_BUFFER(buffer)); }
String16 UiEntry::text() const{ return String16((const char *)gtk_entry_get_text(GTK_ENTRY(this))); }

void UiEntry::text(const String16 &text)
{
    ByteArray utf8 = text.ToCString();
    gtk_entry_set_text(GTK_ENTRY(this), (const gchar *)utf8.data());
}

ushort UiEntry::getLength() const { return (ushort)gtk_entry_get_text_length(GTK_ENTRY(this)); }

GdkRectangle UiEntry::getTextArea() const
{
    GdkRectangle r;
    gtk_entry_get_text_area(GTK_ENTRY(this), &r);
    return r;
}

bool UiEntry::visibility() const { return gtk_entry_get_visibility(GTK_ENTRY(this)); }
void UiEntry::visibility(bool v) { gtk_entry_set_visibility(GTK_ENTRY(this), v); }
int UiEntry::maxLength() const { return gtk_entry_get_max_length(GTK_ENTRY(this)); }
void UiEntry::maxLength(int maxLength) { gtk_entry_set_max_length(GTK_ENTRY(this), maxLength); }
bool UiEntry::activatesDefault() const { return gtk_entry_get_activates_default(GTK_ENTRY(this)); }
void UiEntry::activatesDefault(bool a) { gtk_entry_set_activates_default(GTK_ENTRY(this), a); }
bool UiEntry::hasFrame() const { return gtk_entry_get_has_frame(GTK_ENTRY(this)); }
void UiEntry::hasFrame(bool h) { gtk_entry_set_has_frame(GTK_ENTRY(this), h); }
int UiEntry::widthChars() const { return gtk_entry_get_width_chars(GTK_ENTRY(this)); }
void UiEntry::widthChars(int w) { gtk_entry_set_width_chars(GTK_ENTRY(this), w); }
int UiEntry::maxWidthChars() const { return gtk_entry_get_max_width_chars(GTK_ENTRY(this)); }
void UiEntry::maxWidthChars(int w) { gtk_entry_set_max_width_chars(GTK_ENTRY(this), w); }
float UiEntry::alignment() const { return gtk_entry_get_alignment(GTK_ENTRY(this)); }
void UiEntry::alignment(float a) { gtk_entry_set_alignment(GTK_ENTRY(this), a); }
bool UiEntry::overwrite() const { return gtk_entry_get_overwrite_mode(GTK_ENTRY(this)); }
void UiEntry::overwrite(bool o) { gtk_entry_set_overwrite_mode(GTK_ENTRY(this), o); }
double UiEntry::progressFraction() const { return gtk_entry_get_progress_fraction(GTK_ENTRY(this)); }
void UiEntry::progressFraction(double a) { gtk_entry_set_progress_fraction(GTK_ENTRY(this), a); }
double UiEntry::pulseStep() const { return gtk_entry_get_progress_pulse_step(GTK_ENTRY(this)); }
void UiEntry::pulseStep(double a) { gtk_entry_set_progress_pulse_step(GTK_ENTRY(this), a); }
GtkInputPurpose UiEntry::inputPurpose() const { return gtk_entry_get_input_purpose(GTK_ENTRY(this)); }
void UiEntry::inputPurpose(GtkInputPurpose a) { gtk_entry_set_input_purpose(GTK_ENTRY(this), a); }
GtkInputHints UiEntry::inputHints() const { return gtk_entry_get_input_hints(GTK_ENTRY(this)); }
void UiEntry::inputHints(GtkInputHints a) { gtk_entry_set_input_hints(GTK_ENTRY(this), a); }
void UiEntry::Pulse() { gtk_entry_progress_pulse(GTK_ENTRY(this)); }
void UiEntry::GrabFocusWithoutSelection() { gtk_entry_grab_focus_without_selecting(GTK_ENTRY(this)); }

RawSignal UiEntry::Signals::Activate(SignalCallback eventMethod, void *instance, void *userData)
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

RawSignal UiEntry::Signals::Backspace(SignalCallback eventMethod, void *instance, void *userData)
{
    VSignal *s = new VSignal();
    s->eventMethod = (void *)eventMethod;
    s->userData = userData;
    s->instance = instance;
    s->signalName = "backspace";
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

RawSignal UiEntry::Signals::CopyClipboard(SignalCallback eventMethod, void *instance, void *userData)
{
    VSignal *s = new VSignal();
    s->eventMethod = (void *)eventMethod;
    s->userData = userData;
    s->instance = instance;
    s->signalName = "copy-clipboard";
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

RawSignal UiEntry::Signals::CutClipboard(SignalCallback eventMethod, void *instance, void *userData)
{
    VSignal *s = new VSignal();
    s->eventMethod = (void *)eventMethod;
    s->userData = userData;
    s->instance = instance;
    s->signalName = "cut-clipboard";
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

RawSignal UiEntry::Signals::DeleteFromCursor(SignalCallback eventMethod, void *instance, void *userData)
{
    VSignal *s = new VSignal();
    s->eventMethod = (void *)eventMethod;
    s->userData = userData;
    s->instance = instance;
    s->signalName = "delete-from-cursor";
    void (*gtkmethod) (GtkWidget *, GtkDeleteType, int, gpointer) = [](GtkWidget *sender, GtkDeleteType type, int count, gpointer g) -> void{
        VSignal *signal = (VSignal *)g;
        EventArgs *eArgs = new EventArgs(nullptr);
        signal->args = eArgs;
        signal->args->EventSignal = signal;
        signal->args->UserData = signal->userData;
        if(signal->instance == nullptr){
            StaticSignalMethod_GtkDel_Int ssm = (StaticSignalMethod_GtkDel_Int)signal->eventMethod;
            ssm((BaseWidget *)sender, type, count, signal->args);
        } else {
            InstanceSignalMethod_GtkDel_Int ism = (InstanceSignalMethod_GtkDel_Int)signal->eventMethod;
            ism(signal->instance, (BaseWidget *)sender, type, count, signal->args);
        }
        delete eArgs;
    };
    s->callBack = G_CALLBACK(gtkmethod);
    return s;
}

RawSignal UiEntry::Signals::InsertAtCursor(SignalCallback eventMethod, void *instance, void *userData)
{
    VSignal *s = new VSignal();
    s->eventMethod = (void *)eventMethod;
    s->userData = userData;
    s->instance = instance;
    s->signalName = "insert-at-cursor";
    void (*gtkmethod) (GtkWidget *, gchar *, gpointer) = [](GtkWidget *sender, gchar * str, gpointer g) -> void{
        VSignal *signal = (VSignal *)g;
        EventArgs *eArgs = new EventArgs(nullptr);
        signal->args = eArgs;
        signal->args->EventSignal = signal;
        signal->args->UserData = signal->userData;

        if(signal->instance == nullptr){
            StaticSignalMethod_Str ssm = (StaticSignalMethod_Str)signal->eventMethod;
            ssm((BaseWidget *)sender, String16(str), signal->args);
        } else {
            InstanceSignalMethod_Str ism = (InstanceSignalMethod_Str)signal->eventMethod;
            ism(signal->instance, (BaseWidget *)sender, String16(str), signal->args);
        }
        delete eArgs;
    };
    s->callBack = G_CALLBACK(gtkmethod);
    return s;
}

RawSignal UiEntry::Signals::PasteClipboard(SignalCallback eventMethod, void *instance, void *userData)
{
    VSignal *s = new VSignal();
    s->eventMethod = (void *)eventMethod;
    s->userData = userData;
    s->instance = instance;
    s->signalName = "paste-clipboard";
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

RawSignal UiEntry::Signals::PopulatePopup(SignalCallback eventMethod, void *instance, void *userData)
{
    VSignal *s = new VSignal();
    s->eventMethod = (void *)eventMethod;
    s->userData = userData;
    s->instance = instance;
    s->signalName = "populate-popup";
    void (*gtkmethod) (GtkWidget *, GtkWidget *, gpointer) = [](GtkWidget *sender, GtkWidget *w, gpointer g) -> void{
        VSignal *signal = (VSignal *)g;
        BaseWidget * comp = (BaseWidget *)w;
        EventArgs *eArgs = new EventArgs(nullptr);
        signal->args = eArgs;
        signal->args->EventSignal = signal;
        signal->args->UserData = signal->userData;
        if(signal->instance == nullptr){
            StaticSignalMethod_GtkWid ssm = (StaticSignalMethod_GtkWid)signal->eventMethod;
            ssm((BaseWidget *)sender, comp, signal->args);
        } else {
            InstanceSignalMethod_GtkWid ism = (InstanceSignalMethod_GtkWid)signal->eventMethod;
            ism(signal->instance, (BaseWidget *)sender, comp, signal->args);
        }
        delete eArgs;
    };
    s->callBack = G_CALLBACK(gtkmethod);
    return s;
}

RawSignal UiEntry::Signals::PreEditChanged(SignalCallback eventMethod, void *instance, void *userData)
{
    VSignal *s = new VSignal();
    s->eventMethod = (void *)eventMethod;
    s->userData = userData;
    s->instance = instance;
    s->signalName = "preedit-changed";
    void (*gtkmethod) (GtkWidget *, gchar *, gpointer) = [](GtkWidget *sender, gchar * str, gpointer g) -> void{
        VSignal *signal = (VSignal *)g;
        EventArgs *eArgs = new EventArgs(nullptr);
        signal->args = eArgs;
        signal->args->EventSignal = signal;
        signal->args->UserData = signal->userData;

        if(signal->instance == nullptr){
            StaticSignalMethod_Str ssm = (StaticSignalMethod_Str)signal->eventMethod;
            ssm((BaseWidget *)sender, String16(str), signal->args);
        } else {
            InstanceSignalMethod_Str ism = (InstanceSignalMethod_Str)signal->eventMethod;
            ism(signal->instance, (BaseWidget *)sender, String16(str), signal->args);
        }
        delete eArgs;
    };
    s->callBack = G_CALLBACK(gtkmethod);
    return s;
}

RawSignal UiEntry::Signals::ToggleOverwrite(SignalCallback eventMethod, void *instance, void *userData)
{
    VSignal *s = new VSignal();
    s->eventMethod = (void *)eventMethod;
    s->userData = userData;
    s->instance = instance;
    s->signalName = "toggle-overwrite";
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

RawSignal UiSearchEntry::Signals::NextMatch(SignalCallback eventMethod, void *instance, void *userData)
{
    VSignal *s = new VSignal();
    s->eventMethod = (void *)eventMethod;
    s->userData = userData;
    s->instance = instance;
    s->signalName = "next-match";
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

RawSignal UiSearchEntry::Signals::PreviousMatch(SignalCallback eventMethod, void *instance, void *userData)
{
    VSignal *s = new VSignal();
    s->eventMethod = (void *)eventMethod;
    s->userData = userData;
    s->instance = instance;
    s->signalName = "previous-match";
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

RawSignal UiSearchEntry::Signals::SearchChanged(SignalCallback eventMethod, void *instance, void *userData)
{
    VSignal *s = new VSignal();
    s->eventMethod = (void *)eventMethod;
    s->userData = userData;
    s->instance = instance;
    s->signalName = "search-changed";
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

RawSignal UiSearchEntry::Signals::StopSearch(SignalCallback eventMethod, void *instance, void *userData)
{
    VSignal *s = new VSignal();
    s->eventMethod = (void *)eventMethod;
    s->userData = userData;
    s->instance = instance;
    s->signalName = "stop-search";
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

UiSearchEntry *UiSearchEntry::New()
{
    return (UiSearchEntry *)gtk_search_entry_new();
}
