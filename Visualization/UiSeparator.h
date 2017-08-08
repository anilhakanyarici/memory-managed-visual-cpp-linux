#ifndef UISEPARATOR_H
#define UISEPARATOR_H

#include "BaseWidget.h"

class UiSeparator : public BaseWidget
{
public:
    static UiSeparator *New(GtkOrientation orientation);

    class Signals : public BaseWidget::Signals{};
};

#endif // UISEPARATOR_H
