#ifndef UIRADIOBUTTON_H
#define UIRADIOBUTTON_H

#include "UiCheckButton.h"

class UiRadioButton : public UiCheckButton
{
    static UiRadioButton *New();
    static UiRadioButton *New(Array<UiRadioButton *> group);
    static UiRadioButton *New(UiRadioButton *groupMember);
    static UiRadioButton *New(const String16 &label, bool mnemonic = false);
    static UiRadioButton *New(Array<UiRadioButton *> group, const String16 &label, bool mnemonic = false);

    Array<UiRadioButton *> group() const;
    void group(Array<UiRadioButton *> group);

    void Join(UiRadioButton *groupSource);

    class Signals : public UiCheckButton::Signals
    {
    public:
        static RawSignal GroupChanged(SignalCallback eventMethod, void *instance = nullptr, void *userData = nullptr); //Callback(UiRadioButton *, EventArgs *)
    };
};

#endif // UIRADIOBUTTON_H
