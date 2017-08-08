#ifndef UIDRAWINGAREA_H
#define UIDRAWINGAREA_H

#include "BaseWidget.h"

class UiDrawingArea : public BaseWidget
{
public:
    static UiDrawingArea *New();

    class Signals : public BaseWidget::Signals{};
};


#endif // UIDRAWINGAREA_H
