#include "UiFileChooserDialog.h"

Delegate(StaticSignalMethod, void, BaseWidget *, EventArgs *);
Delegate(InstanceSignalMethod, void, void *, BaseWidget *, EventArgs *);
Delegate(StaticSignalMethod_fcc, void, BaseWidget *, FileChooserConfirmation *, EventArgs *);
Delegate(InstanceSignalMethod_fcc, void, void *, BaseWidget *, FileChooserConfirmation *, EventArgs *);

FileFilter *FileFilter::New()
{
    return (FileFilter *)gtk_file_filter_new();
}

String16 FileFilter::name() const
{
    const gchar *np = gtk_file_filter_get_name(GTK_FILE_FILTER(this));
    return String16((const char *)np);
}

void FileFilter::name(const String16 &v)
{
    ByteArray utf8 = v.ToCString();
    gtk_file_filter_set_name((GTK_FILE_FILTER(this)), (const char *)utf8.data());
}

GtkFileFilterFlags FileFilter::needed() const { return gtk_file_filter_get_needed(GTK_FILE_FILTER(this)); }

void FileFilter::AddMimeType(const String16 &mimeType)
{
    ByteArray utf8 = mimeType.ToCString();
    gtk_file_filter_add_mime_type(GTK_FILE_FILTER(this), (const gchar *)utf8.data());
}

void FileFilter::AddPattern(const String16 &pattern)
{
    ByteArray utf8 = pattern.ToCString();
    gtk_file_filter_add_pattern(GTK_FILE_FILTER(this), (const gchar *)utf8.data());
}

void FileFilter::AddImageTypes()
{
    gtk_file_filter_add_pixbuf_formats(GTK_FILE_FILTER(this));
}

UiFileChooserDialog *UiFileChooserDialog::New(const String16 &title, GtkFileChooserAction action, UiWindow *parentWindow)
{
    ByteArray utf8 = title.ToCString();
    if(action == GTK_FILE_CHOOSER_ACTION_OPEN || action == GTK_FILE_CHOOSER_ACTION_SELECT_FOLDER)
        return (UiFileChooserDialog *)gtk_file_chooser_dialog_new((const char *)utf8.data(), GTK_WINDOW(parentWindow), action, "_Cancel", GTK_RESPONSE_CANCEL, "_Open", GTK_RESPONSE_ACCEPT, NULL);
    else
        return (UiFileChooserDialog *)gtk_file_chooser_dialog_new((const char *)utf8.data(), GTK_WINDOW(parentWindow), action, "_Cancel", GTK_RESPONSE_CANCEL, "_Save", GTK_RESPONSE_ACCEPT, NULL);
}

GtkFileChooserAction UiFileChooserDialog::action() const { return gtk_file_chooser_get_action(GTK_FILE_CHOOSER(this)); }
void UiFileChooserDialog::action(GtkFileChooserAction a) { gtk_file_chooser_set_action(GTK_FILE_CHOOSER(this), a); }
bool UiFileChooserDialog::canCreateFolder() const { return gtk_file_chooser_get_create_folders(GTK_FILE_CHOOSER(this)); }
void UiFileChooserDialog::canCreateFolder(bool v) { gtk_file_chooser_set_create_folders(GTK_FILE_CHOOSER(this), v); }

String16 UiFileChooserDialog::currentFolder() const
{
    gchar *np = gtk_file_chooser_get_current_folder(GTK_FILE_CHOOSER(this));
    String16 str = String16((const char *)np);
    g_free(np);
    return str;
}

void UiFileChooserDialog::currentFolder(const String16 &v)
{
    ByteArray utf8 = v.ToCString();
    gtk_file_chooser_set_current_folder(GTK_FILE_CHOOSER(this), (const char *)utf8.data());
}

String16 UiFileChooserDialog::currentName() const
{
    gchar *np = gtk_file_chooser_get_current_name(GTK_FILE_CHOOSER(this));
    String16 str = String16((const char *)np);
    g_free(np);
    return str;
}

void UiFileChooserDialog::currentName(const String16 &v)
{
    ByteArray utf8 = v.ToCString();
    gtk_file_chooser_set_current_name(GTK_FILE_CHOOSER(this), (const char *)utf8.data());
}

BaseWidget *UiFileChooserDialog::extraWidget() const { return (BaseWidget *)gtk_file_chooser_get_extra_widget(GTK_FILE_CHOOSER(this)); }

void UiFileChooserDialog::extraWidget(BaseWidget *v) { gtk_file_chooser_set_extra_widget(GTK_FILE_CHOOSER(this), GTK_WIDGET(v)); }

String16 UiFileChooserDialog::fileName() const
{
    gchar *np = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(this));
    String16 str = String16((const char *)np);
    g_free(np);
    return str;
}

void UiFileChooserDialog::fileName(const String16 &v)
{
    ByteArray utf8 = v.ToCString();
    gtk_file_chooser_set_filename(GTK_FILE_CHOOSER(this), (const char *)utf8.data());
}

bool UiFileChooserDialog::localOnly() const { return gtk_file_chooser_get_local_only(GTK_FILE_CHOOSER(this)); }
void UiFileChooserDialog::localOnly(bool v) { gtk_file_chooser_set_local_only(GTK_FILE_CHOOSER(this), v); }
bool UiFileChooserDialog::overwriteConfirmation() const { return gtk_file_chooser_get_do_overwrite_confirmation(GTK_FILE_CHOOSER(this)); }
void UiFileChooserDialog::overwriteConfirmation(bool v) { gtk_file_chooser_set_do_overwrite_confirmation(GTK_FILE_CHOOSER(this), v); }
BaseWidget *UiFileChooserDialog::previewWidget() const { return (BaseWidget *)gtk_file_chooser_get_preview_widget(GTK_FILE_CHOOSER(this)); }
void UiFileChooserDialog::previewWidget(BaseWidget *v) { gtk_file_chooser_set_preview_widget(GTK_FILE_CHOOSER(this), GTK_WIDGET(v)); }
bool UiFileChooserDialog::previewWidgetActive() const { return gtk_file_chooser_get_preview_widget_active(GTK_FILE_CHOOSER(this)); }
void UiFileChooserDialog::previewWidgetActive(bool v) { gtk_file_chooser_set_preview_widget_active(GTK_FILE_CHOOSER(this), v); }
bool UiFileChooserDialog::selectMultiple() const { return gtk_file_chooser_get_select_multiple(GTK_FILE_CHOOSER(this)); }
void UiFileChooserDialog::selectMultiple(bool v) { gtk_file_chooser_set_select_multiple(GTK_FILE_CHOOSER(this), v); }
bool UiFileChooserDialog::showHidden() const { return gtk_file_chooser_get_show_hidden(GTK_FILE_CHOOSER(this)); }
void UiFileChooserDialog::showHidden(bool v) { gtk_file_chooser_set_show_hidden(GTK_FILE_CHOOSER(this), v); }
bool UiFileChooserDialog::usePreviewLabel() const { return gtk_file_chooser_get_use_preview_label(GTK_FILE_CHOOSER(this)); }
void UiFileChooserDialog::usePreviewLabel(bool v) { gtk_file_chooser_set_use_preview_label(GTK_FILE_CHOOSER(this), v); }

void UiFileChooserDialog::AddFilter(FileFilter *filter){ gtk_file_chooser_add_filter(GTK_FILE_CHOOSER(this), GTK_FILE_FILTER(filter)); }
void UiFileChooserDialog::RemoveFilter(FileFilter *filter){ gtk_file_chooser_remove_filter(GTK_FILE_CHOOSER(this), GTK_FILE_FILTER(filter)); }

void UiFileChooserDialog::SelectFileName(const String16 &name)
{
    ByteArray utf8 = name.ToCString();
    gtk_file_chooser_select_filename(GTK_FILE_CHOOSER(this), (const char *)utf8.data());
}

void UiFileChooserDialog::SelectAll() {  gtk_file_chooser_select_all(GTK_FILE_CHOOSER(this)); }
void UiFileChooserDialog::SetFilter(FileFilter *filter) { gtk_file_chooser_set_filter(GTK_FILE_CHOOSER(this), GTK_FILE_FILTER(filter)); }
void UiFileChooserDialog::UnselectAll() {  gtk_file_chooser_unselect_all(GTK_FILE_CHOOSER(this)); }

void UiFileChooserDialog::UnselectFileName(const String16 &name)
{
    ByteArray utf8 = name.ToCString();
    gtk_file_chooser_unselect_filename(GTK_FILE_CHOOSER(this), (const char *)utf8.data());
}

StringList UiFileChooserDialog::GetFileNames()
{
    GSList* list = gtk_file_chooser_get_filenames(GTK_FILE_CHOOSER(this));
    StringList strList = StringList();

    GSList *curr = list;
    int i = 0;
    while(curr != NULL){
        String16 e = String16((const char *)curr->data);
        strList.Add(e);
        curr = curr->next;
        i++;
    }
    g_slist_free(list);
    return strList;
}

RawSignal UiFileChooserDialog::Signals::ConfirmOverwrite(SignalCallback eventMethod, void *instance, void *userData)
{
    VSignal *s = new VSignal();
    s->eventMethod = (void *)eventMethod;
    s->userData = userData;
    s->instance = instance;
    s->signalName = "confirm-overwrite";
    GtkFileChooserConfirmation (*gtkmethod) (GtkWidget *, gpointer) = [](GtkWidget *sender, gpointer g) -> GtkFileChooserConfirmation{
        VSignal *signal = (VSignal *)g;
        EventArgs *eArgs = new EventArgs(nullptr);
        FileChooserConfirmation conf = FileChooserConfirmation();
        signal->args = eArgs;
        signal->args->EventSignal = signal;
        signal->args->UserData = signal->userData;
        if(signal->instance == nullptr){
            StaticSignalMethod_fcc ssm = (StaticSignalMethod_fcc)signal->eventMethod;
            ssm((BaseWidget *)sender, &conf, signal->args);
        } else {
            InstanceSignalMethod_fcc ism = (InstanceSignalMethod_fcc)signal->eventMethod;
            ism(signal->instance, (BaseWidget *)sender, &conf, signal->args);
        }
        delete eArgs;
        return conf._conf;
    };
    s->callBack = G_CALLBACK(gtkmethod);
    return s;
}

RawSignal UiFileChooserDialog::Signals::CurrentFolderChanged(SignalCallback eventMethod, void *instance, void *userData)
{
    VSignal *s = new VSignal();
    s->eventMethod = (void *)eventMethod;
    s->userData = userData;
    s->instance = instance;
    s->signalName = "current-folder-changed";
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

RawSignal UiFileChooserDialog::Signals::FileActivated(SignalCallback eventMethod, void *instance, void *userData)
{
    VSignal *s = new VSignal();
    s->eventMethod = (void *)eventMethod;
    s->userData = userData;
    s->instance = instance;
    s->signalName = "file-activated";
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

RawSignal UiFileChooserDialog::Signals::SelectionChanged(SignalCallback eventMethod, void *instance, void *userData)
{
    VSignal *s = new VSignal();
    s->eventMethod = (void *)eventMethod;
    s->userData = userData;
    s->instance = instance;
    s->signalName = "selection-changed";
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

RawSignal UiFileChooserDialog::Signals::UpdatePreview(SignalCallback eventMethod, void *instance, void *userData)
{
    VSignal *s = new VSignal();
    s->eventMethod = (void *)eventMethod;
    s->userData = userData;
    s->instance = instance;
    s->signalName = "update-preview";
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
