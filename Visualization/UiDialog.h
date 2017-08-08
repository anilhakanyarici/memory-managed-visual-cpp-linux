#ifndef UIDIALOG_H
#define UIDIALOG_H

#include "UiWindow.h"
#include "UiButton.h"

class UiDialog : public UiWindow
{
public:
    static UiDialog *New();

    void AddActionWidget(BaseWidget *child, int responseId);
    void DialogResponse(int responseId);
    UiButton *AddButton(const String16& buttonText, int responseId);//Return value must be delete!
    int Run();
    void SetDefaultResponse(int responseId);

    class Signals : public UiWindow::Signals
    {
        static RawSignal Close(SignalCallback eventMethod, void *instance = nullptr, void *userData = nullptr); //Callback(UiDialog *, EventArgs *)
        static RawSignal Response(SignalCallback eventMethod, void *instance = nullptr, void *userData = nullptr); //Callback(UiDialog *, int, EventArgs *)
    };
};

#endif // UIDIALOG_H
