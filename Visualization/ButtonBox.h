#ifndef BUTTONBOX_H
#define BUTTONBOX_H

#include "Box.h"

class ButtonBox : public Box
{
public:
    GtkButtonBoxStyle layout() const;
    void layout(GtkButtonBoxStyle style);

    static ButtonBox *New(GtkOrientation orientation);

    bool GetChildSecondary(BaseWidget *child);
    bool GetChildNonHomogeneous(BaseWidget *child);
    void SetChildSecondary(BaseWidget *child, bool isSecondary);
    void SetChildNonHomogeneous(BaseWidget *child, bool nonHomogeneous);

    class Signals : public Box::Signals{};
};

#endif // BUTTONBOX_H
