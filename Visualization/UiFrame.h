#ifndef UIFRAME_H
#define UIFRAME_H

#include "BaseBin.h"

class UiFrame : public BaseBin
{
public:
    static UiFrame *New(const String16 &label);

    String16 label() const;
    void label(const String16 &label);

    BaseWidget *labelWidget() const;
    void labelWidget(BaseWidget *w);
    DoublePosition labelAlign() const;
    void labelAlign(DoublePosition align);

    GtkShadowType shadowType() const;
    void shadowType(GtkShadowType w);

    class Signals : public BaseBin::Signals{};
};


#endif // UIFRAME_H
