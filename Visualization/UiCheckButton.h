#ifndef UICHECKBUTTON_H
#define UICHECKBUTTON_H

#include "UiToggleButton.h"

class UiCheckButton : public UiToggleButton
{
public:
    static UiCheckButton *New();
    static UiCheckButton *New(const String16 &label, bool mnemonic = false);

    class Signals : public UiToggleButton::Signals{};
};
#endif // UICHECKBUTTON_H
