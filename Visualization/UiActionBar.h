#ifndef UIACTIONBAR_H
#define UIACTIONBAR_H

#include "BaseBin.h"

class UiActionBar : public BaseBin
{
public:
    static UiActionBar *New();

    BaseWidget *centerWidget() const;
    void centerWidget(BaseWidget *child);

    void PackStart(BaseWidget *child);
    void PackEnd(BaseWidget *child);

    class Signals : public BaseBin::Signals{};
};
#endif // UIACTIONBAR_H
