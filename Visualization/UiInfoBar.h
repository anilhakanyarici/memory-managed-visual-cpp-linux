#ifndef UIINFOBAR_H
#define UIINFOBAR_H

#include "Box.h"
#include "UiButton.h"

class UiInfoBar : public Box
{
public:
    static UiInfoBar *New();

    GtkMessageType messageType() const;
    void messageType(GtkMessageType t);
    bool showCloseButton() const;
    void showCloseButton(bool t);
    BaseWidget *getActionArea() const;
    BaseWidget *getContentArea() const;

    void AddActionWidget(BaseWidget *child, int responseId);
    UiButton *AddActionWidget(const String16 &str, int responseId);
    void SetResponseSensitive(int responseId, bool setting);
    void SetDefaultResponse(int responseId);
    void EmitResponse(int responseId);

    class Signals : public Box::Signals
    {
    public:
        static RawSignal Close(SignalCallback eventMethod, void *instance = nullptr, void *userData = nullptr); //Callback(UiInfoBar *, EventArgs *)
        static RawSignal Response(SignalCallback eventMethod, void *instance = nullptr, void *userData = nullptr); //Callback(UiInfoBar *, int *, EventArgs *)
    };
};

#endif // UIINFOBAR_H
