#ifndef UISPINNER_H
#define UISPINNER_H

#include "BaseWidget.h"

class UiSpinner : public BaseWidget
{
public:
    static UiSpinner *New();

    void Start();
    void Stop();

    class Signals : public BaseWidget::Signals{};
};

#endif // UISPINNER_H
