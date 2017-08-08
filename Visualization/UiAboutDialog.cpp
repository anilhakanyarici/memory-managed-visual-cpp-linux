#include "UiAboutDialog.h"

Delegate(StaticSignalMethod_Str, void, VObject *, String16, EventArgs *);
Delegate(InstanceSignalMethod_Str, void, void *, VObject *, String16, EventArgs *);

UiAboutDialog *UiAboutDialog::New()
{
    return (UiAboutDialog *)gtk_about_dialog_new();
}

bool UiAboutDialog::wrapLicense() const { return gtk_about_dialog_get_wrap_license(GTK_ABOUT_DIALOG(this)); }
void UiAboutDialog::wrapLicense(bool v) { gtk_about_dialog_set_wrap_license(GTK_ABOUT_DIALOG(this), v); }
GtkLicense UiAboutDialog::licenseType() const { return gtk_about_dialog_get_license_type(GTK_ABOUT_DIALOG(this)); }
void UiAboutDialog::licenseType(GtkLicense v) { gtk_about_dialog_set_license_type(GTK_ABOUT_DIALOG(this), v); }
String16 UiAboutDialog::programName() const { return String16(gtk_about_dialog_get_program_name(GTK_ABOUT_DIALOG(this))); }

void UiAboutDialog::programName(const String16 &v)
{
    ByteArray utf8 = v.ToCString();
    gtk_about_dialog_set_program_name(GTK_ABOUT_DIALOG(this), (const gchar *)utf8.data());
}

String16 UiAboutDialog::version() const { return String16(gtk_about_dialog_get_version(GTK_ABOUT_DIALOG(this))); }

void UiAboutDialog::version(const String16 &v)
{
    ByteArray utf8 = v.ToCString();
    gtk_about_dialog_set_version(GTK_ABOUT_DIALOG(this), (const gchar *)utf8.data());
}

String16 UiAboutDialog::copyright() const { return String16(gtk_about_dialog_get_copyright(GTK_ABOUT_DIALOG(this))); }

void UiAboutDialog::copyright(const String16 &v)
{
    ByteArray utf8 = v.ToCString();
    gtk_about_dialog_set_copyright(GTK_ABOUT_DIALOG(this), (const gchar *)utf8.data());
}

String16 UiAboutDialog::comments() const { return String16(gtk_about_dialog_get_comments(GTK_ABOUT_DIALOG(this))); }

void UiAboutDialog::comments(const String16 &v)
{
    ByteArray utf8 = v.ToCString();
    gtk_about_dialog_set_comments(GTK_ABOUT_DIALOG(this), (const gchar *)utf8.data());
}

String16 UiAboutDialog::license() const { return String16(gtk_about_dialog_get_license(GTK_ABOUT_DIALOG(this))); }

void UiAboutDialog::license(const String16 &v)
{
    ByteArray utf8 = v.ToCString();
    gtk_about_dialog_set_license(GTK_ABOUT_DIALOG(this), (const gchar *)utf8.data());
}

String16 UiAboutDialog::website() const { return String16(gtk_about_dialog_get_website(GTK_ABOUT_DIALOG(this))); }

void UiAboutDialog::website(const String16 &v)
{
    ByteArray utf8 = v.ToCString();
    gtk_about_dialog_set_website(GTK_ABOUT_DIALOG(this), (const gchar *)utf8.data());
}

String16 UiAboutDialog::websiteLabel() const { return String16(gtk_about_dialog_get_website_label(GTK_ABOUT_DIALOG(this))); }

void UiAboutDialog::websiteLabel(const String16 &v)
{
    ByteArray utf8 = v.ToCString();
    gtk_about_dialog_set_website_label(GTK_ABOUT_DIALOG(this), (const gchar *)utf8.data());
}

String16 UiAboutDialog::translatorCredits() const { return String16(gtk_about_dialog_get_translator_credits(GTK_ABOUT_DIALOG(this))); }

void UiAboutDialog::translatorCredits(const String16 &v)
{
    ByteArray utf8 = v.ToCString();
    gtk_about_dialog_set_translator_credits(GTK_ABOUT_DIALOG(this), (const gchar *)utf8.data());
}

void UiAboutDialog::SetLogo(UiImage *image)
{
    Pixelbuffer *pixbuf = Pixelbuffer::New(image);
    gtk_about_dialog_set_logo(GTK_ABOUT_DIALOG(this), GDK_PIXBUF(pixbuf));
}

RawSignal UiAboutDialog::Signals::ActivateLink(SignalCallback eventMethod, void *instance, void *userData)
{
    VSignal *s = new VSignal();
    s->eventMethod = (void *)eventMethod;
    s->userData = userData;
    s->instance = instance;
    s->signalName = "close";
    bool (*gtkmethod) (GtkWidget *, gchar *, gpointer) = [](GtkWidget *sender, gchar *uri, gpointer g) -> bool{
        VSignal *signal = (VSignal *)g;
        EventArgs *eArgs = new EventArgs(nullptr);

        String16 str = String16((const char *)uri);

        signal->args = eArgs;
        signal->args->EventSignal = signal;
        signal->args->UserData = signal->userData;
        if(signal->instance == nullptr){
            StaticSignalMethod_Str ssm = (StaticSignalMethod_Str)signal->eventMethod;
            ssm((BaseWidget *)sender, str, signal->args);
        } else {
            InstanceSignalMethod_Str ism = (InstanceSignalMethod_Str)signal->eventMethod;
            ism(signal->instance, (BaseWidget *)sender, str, signal->args);
        }
        delete eArgs;
        return true;
    };
    s->callBack = G_CALLBACK(gtkmethod);
    return s;
}
