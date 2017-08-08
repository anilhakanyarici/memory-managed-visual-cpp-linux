#ifndef EVENTBOX_H
#define EVENTBOX_H

#include "BaseBin.h"

class EventBox : public BaseBin
{
public:
    static EventBox *New();

    bool aboveChild() const;
    void aboveChild(bool u);
    bool visibleWindow() const;
    void visibleWindow(bool u);

    class Signals : public BaseBin::Signals{};
};


#endif // EVENTBOX_H
