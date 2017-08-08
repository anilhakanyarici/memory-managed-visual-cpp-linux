#ifndef VIEWPORT_H
#define VIEWPORT_H

#include "BaseBin.h"

class Viewport : public BaseBin
{
public:
    static Viewport *New();

    GtkShadowType shadowType() const;
    void shadowType(GtkShadowType w);
    UiWindow *binWindow() const;
    UiWindow *viewWindow() const;

    class Signals : public BaseBin::Signals{};
};

#endif // VIEWPORT_H
