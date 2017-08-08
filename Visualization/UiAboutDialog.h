#ifndef UIABOUTDIALOG_H
#define UIABOUTDIALOG_H

#include "UiDialog.h"

class UiAboutDialog : public UiDialog
{
public:
    static UiAboutDialog *New();

    bool wrapLicense() const;
    void wrapLicense(bool v);
    GtkLicense licenseType() const;
    void licenseType(GtkLicense v);
    String16 programName() const;
    void programName(const String16 &v);
    String16 version() const;
    void version(const String16 &v);
    String16 copyright() const;
    void copyright(const String16 &v);
    String16 comments() const;
    void comments(const String16 &v);
    String16 license() const;
    void license(const String16 &v);
    String16 website() const;
    void website(const String16 &v);
    String16 websiteLabel() const;
    void websiteLabel(const String16 &v);
    String16 translatorCredits() const;
    void translatorCredits(const String16 &v);

    void SetLogo(UiImage *image);

    class Signals : public UiDialog::Signals
    {
    public:
        static RawSignal ActivateLink(SignalCallback eventMethod, void *instance = nullptr, void *userData = nullptr); //Callback(UiAboutDialog *, String16, EventArgs *)
    };
};

#endif // UIABOUTDIALOG_H
