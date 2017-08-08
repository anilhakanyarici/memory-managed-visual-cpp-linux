#ifndef UILINKBUTTON_H
#define UILINKBUTTON_H

#include "UiButton.h"

class UiLinkButton : public UiButton
{
public:
    static UiLinkButton *New(const String16 &uri);

    String16 uri() const;
    void uri(const String16 &uri);
    bool visited() const;
    void visited(bool v);

    class Signals : public UiButton::Signals
    {
    public:
        static RawSignal ActivateLink(SignalCallback eventMethod, void *instance = nullptr, void *userData = nullptr); //Callback(UiLinkButton *, EventArgs *)
    };
};

#endif // UILINKBUTTON_H
