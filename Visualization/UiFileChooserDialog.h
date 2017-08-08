#ifndef UIFILECHOOSERDIALOG_H
#define UIFILECHOOSERDIALOG_H

#include "UiDialog.h"

class FileFilter
{
public:
    static FileFilter *New();

    String16 name() const;
    void name(const String16 &v);
    GtkFileFilterFlags needed() const;

    void AddMimeType(const String16 &mimeType);
    void AddPattern(const String16 &pattern);
    void AddImageTypes();

};

class UiFileChooserDialog : public UiDialog
{
public:
    static UiFileChooserDialog *New(const String16 &title, GtkFileChooserAction action, UiWindow *parentWindow = NULL);

    GtkFileChooserAction action() const;
    void action(GtkFileChooserAction a);
    bool canCreateFolder() const;
    void canCreateFolder(bool v);
    String16 currentFolder() const;
    void currentFolder(const String16 &v);
    String16 currentName() const;
    void currentName(const String16 &v);
    BaseWidget *extraWidget() const;
    void extraWidget(BaseWidget *v);
    String16 fileName() const;
    void fileName(const String16 &v);
    bool localOnly() const;
    void localOnly(bool v);
    bool overwriteConfirmation() const;
    void overwriteConfirmation(bool v);
    BaseWidget *previewWidget() const;
    void previewWidget(BaseWidget *v);
    bool previewWidgetActive() const;
    void previewWidgetActive(bool v);
    bool selectMultiple() const;
    void selectMultiple(bool v);
    bool showHidden() const;
    void showHidden(bool v);

    bool usePreviewLabel() const;
    void usePreviewLabel(bool v);

    void AddFilter(FileFilter *filter);
    void RemoveFilter(FileFilter *filter);
    void SelectFileName(const String16 &name);
    void SelectAll();
    void SetFilter(FileFilter *filter);
    void UnselectAll();
    void UnselectFileName(const String16 &name);
    StringList GetFileNames();

    class Signals : public UiDialog::Signals
    {
    public:
        static RawSignal ConfirmOverwrite(SignalCallback eventMethod, void *instance = nullptr, void *userData = nullptr); //Callback(UiFileChooserDialog *, FileChooserConfirmation *, EventArgs *)
        static RawSignal CurrentFolderChanged(SignalCallback eventMethod, void *instance = nullptr, void *userData = nullptr); //Callback(UiFileChooserDialog *, EventArgs *)
        static RawSignal FileActivated(SignalCallback eventMethod, void *instance = nullptr, void *userData = nullptr); //Callback(UiFileChooserDialog *, EventArgs *)
        static RawSignal SelectionChanged(SignalCallback eventMethod, void *instance = nullptr, void *userData = nullptr); //Callback(UiFileChooserDialog *, EventArgs *)
        static RawSignal UpdatePreview(SignalCallback eventMethod, void *instance = nullptr, void *userData = nullptr); //Callback(UiFileChooserDialog *, EventArgs *)
    };
};
class FileChooserConfirmation
{
    friend class UiFileChooserDialog::Signals;
    GtkFileChooserConfirmation _conf;
    FileChooserConfirmation() { this->_conf = GTK_FILE_CHOOSER_CONFIRMATION_ACCEPT_FILENAME; }

public:
    void AcceptFileName() { this->_conf = GTK_FILE_CHOOSER_CONFIRMATION_ACCEPT_FILENAME; }
    void Confirm() { this->_conf = GTK_FILE_CHOOSER_CONFIRMATION_CONFIRM; }
    void SelectAgain() { this->_conf = GTK_FILE_CHOOSER_CONFIRMATION_SELECT_AGAIN; }
};
#endif // UIFILECHOOSERDIALOG_H
