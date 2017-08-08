#ifndef LAYOUT_H
#define LAYOUT_H

#include "Adjustment.h"
#include "BaseContainer.h"

class Layout : public BaseContainer
{
protected:
    Layout(GtkLayout *layout);
public:
    static Layout *New();

    Size size() const;
    void size(Size s);
    UiWindow *getBinWindow() const;

    void Move(BaseWidget *widget, Position pos);
    void Move(BaseWidget *widget, int x, int y);
    void Put(BaseWidget *widget, Position pos);
    void Put(BaseWidget *widget, int x, int y);
};

#endif // LAYOUT_H
