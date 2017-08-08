#ifndef UISWITCH_H
#define UISWITCH_H

#include "BaseWidget.h"

class UiSwitch : public BaseWidget
{
public:
    static UiSwitch *New();

    bool active() const;
    void active(bool a);
    bool state() const;
    void state(bool a);

    class Signals : public BaseWidget::Signals
    {
    public:
        static RawSignal Activate(SignalCallback eventMethod, void *instance = nullptr, void *userData = nullptr); //Callback(BaseWidget *, EventArgs *)
        static RawSignal StateSet(SignalCallback eventMethod, void *instance = nullptr, void *userData = nullptr); //Callback(BaseWidget *, bool, EventArgs *)
    };
};
#endif // UISWITCH_H
