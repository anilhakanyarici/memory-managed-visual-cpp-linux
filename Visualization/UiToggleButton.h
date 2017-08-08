#ifndef UITOGGLEBUTTON_H
#define UITOGGLEBUTTON_H

#include "UiButton.h"

class UiToggleButton : public UiButton
{
public:
    static UiToggleButton *New();
    static UiToggleButton *New(const String16 &label, bool mnemonic = false);

    bool active() const;
    void active(bool a);
    bool inconsistent() const;
    void inconsistent(bool a);
    bool mode() const;
    void mode(bool drawIndicator);

    void EmitToggled();

    class Signals : public UiButton::Signals
    {
    public:
        static RawSignal Toggled(SignalCallback eventMethod, void *instance = nullptr, void *userData = nullptr); //Callback(UiToggleButton *, EventArgs *)
    };
};

#endif // UITOGGLEBUTTON_H
