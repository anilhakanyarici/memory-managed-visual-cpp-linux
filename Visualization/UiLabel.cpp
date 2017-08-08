#include "UiLabel.h"
Delegate(StaticSignalMethod, void, BaseWidget *, EventArgs *);
Delegate(InstanceSignalMethod, void, void *, BaseWidget *, EventArgs *);
Delegate(StaticSignalMethod_MovStep_int_bool, void, BaseWidget *, GtkMovementStep, int, bool, EventArgs *);
Delegate(InstanceSignalMethod_MovStep_int_bool, void, void *, BaseWidget *, GtkMovementStep, int, bool, EventArgs *);

UiLabel *UiLabel::New(const String16 &text)
{
    ByteArray utf8 = text.ToCString();
    return (UiLabel *)gtk_label_new((const char *)utf8.data());
}

PangoEllipsizeMode UiLabel::ellipsize() const{ return gtk_label_get_ellipsize(GTK_LABEL(this)); }
void UiLabel::ellipsize(PangoEllipsizeMode j) { gtk_label_set_ellipsize(GTK_LABEL(this), j); }
GtkJustification UiLabel::justify() const{ return gtk_label_get_justify(GTK_LABEL(this)); }
void UiLabel::justify(GtkJustification j) { gtk_label_set_justify(GTK_LABEL(this), j); }
float UiLabel::xAlign() const{ return gtk_label_get_xalign(GTK_LABEL(this)); }
void UiLabel::xAlign(float v) { gtk_label_set_xalign(GTK_LABEL(this), v); }
float UiLabel::yAlign() const{ return gtk_label_get_yalign(GTK_LABEL(this)); }
void UiLabel::yAlign(float v) { gtk_label_set_yalign(GTK_LABEL(this), v); }
int UiLabel::widthChars() const{ return gtk_label_get_width_chars(GTK_LABEL(this)); }
void UiLabel::widthChars(int v) { gtk_label_set_width_chars(GTK_LABEL(this), v); }
int UiLabel::maxWidthChars() const{ return gtk_label_get_max_width_chars(GTK_LABEL(this)); }
void UiLabel::maxWidthChars(int v) { gtk_label_set_max_width_chars(GTK_LABEL(this), v); }
bool UiLabel::lineWrap() const{ return gtk_label_get_line_wrap(GTK_LABEL(this)); }
void UiLabel::lineWrap(bool v) { gtk_label_set_line_wrap(GTK_LABEL(this), v); }
PangoWrapMode UiLabel::lineWrapMode() const{ return gtk_label_get_line_wrap_mode(GTK_LABEL(this)); }
void UiLabel::lineWrapMode(PangoWrapMode j) { gtk_label_set_line_wrap_mode(GTK_LABEL(this), j); }
int UiLabel::lineCount() const{ return gtk_label_get_lines(GTK_LABEL(this)); }
void UiLabel::lineCount(int v) { gtk_label_set_lines(GTK_LABEL(this), v); }
bool UiLabel::useMarkup() const{ return gtk_label_get_use_markup(GTK_LABEL(this)); }
void UiLabel::useMarkup(bool v) { gtk_label_set_use_markup(GTK_LABEL(this), v); }
bool UiLabel::useUnderline() const{ return gtk_label_get_use_underline(GTK_LABEL(this)); }
void UiLabel::useUnderline(bool v) { gtk_label_set_use_underline(GTK_LABEL(this), v); }
bool UiLabel::singleLineMode() const{ return gtk_label_get_single_line_mode(GTK_LABEL(this)); }
void UiLabel::singleLineMode(bool v) { gtk_label_set_single_line_mode(GTK_LABEL(this), v); }

float UiLabel::angle() const{ return gtk_label_get_angle(GTK_LABEL(this)); }
void UiLabel::angle(float v) { gtk_label_set_angle(GTK_LABEL(this), v); }

Position UiLabel::getLayoutOffset() const
{
    Position p;
    gtk_label_get_layout_offsets(GTK_LABEL(this), &p.X, &p.Y);
    return p;
}

bool UiLabel::selectable() const{ return gtk_label_get_selectable(GTK_LABEL(this)); }
void UiLabel::selectable(bool v) { gtk_label_set_selectable(GTK_LABEL(this), v); }

String16 UiLabel::text() const
{
    return String16(gtk_label_get_text(GTK_LABEL(this)));
}

void UiLabel::text(const String16 &text)
{
    ByteArray utf8 = text.ToCString();
    gtk_label_set_text(GTK_LABEL(this), (const char *)utf8.data());
}

String16 UiLabel::label() const
{
    return String16(gtk_label_get_label(GTK_LABEL(this)));
}

void UiLabel::label(const String16 &text)
{
    ByteArray utf8 = text.ToCString();
    gtk_label_set_label(GTK_LABEL(this), (const char *)utf8.data());
}

void UiLabel::SetMarkup(const String16 &markup)
{
    ByteArray array = markup.ToCString();
    gtk_label_set_markup(GTK_LABEL(this), (const gchar *)array.data());
}

void UiLabel::SetMarkupWithMNemonic(const String16 &markup)
{
    ByteArray array = markup.ToCString();
    gtk_label_set_markup_with_mnemonic(GTK_LABEL(this), (const gchar *)array.data());
}

void UiLabel::SetPattern(const String16 &pattern)
{
    ByteArray array = pattern.ToCString();
    gtk_label_set_pattern(GTK_LABEL(this), (const gchar *)array.data());
}

RawSignal UiLabel::Signals::CopyClipboard(SignalCallback eventMethod, void *instance, void *userData)
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

RawSignal UiLabel::Signals::MoveCursor(SignalCallback eventMethod, void *instance, void *userData)
{
    VSignal *s = new VSignal();
    s->eventMethod = (void *)eventMethod;
    s->userData = userData;
    s->instance = instance;
    s->signalName = "move-cursor";
    void (*gtkmethod) (GtkWidget *, GtkMovementStep, int, bool, gpointer) = [](GtkWidget *sender, GtkMovementStep step, int count, bool extSel, gpointer g) -> void{
        VSignal *signal = (VSignal *)g;
        EventArgs *eArgs = new EventArgs(nullptr);
        signal->args = eArgs;
        signal->args->EventSignal = signal;
        signal->args->UserData = signal->userData;
        if(signal->instance == nullptr){
            StaticSignalMethod_MovStep_int_bool ssm = (StaticSignalMethod_MovStep_int_bool)signal->eventMethod;
            ssm((BaseWidget *)sender, step, count, extSel, signal->args);
        } else {
            InstanceSignalMethod_MovStep_int_bool ism = (InstanceSignalMethod_MovStep_int_bool)signal->eventMethod;
            ism(signal->instance, (BaseWidget *)sender, step, count, extSel, signal->args);
        }
        delete eArgs;
    };
    s->callBack = G_CALLBACK(gtkmethod);
    return s;
}
