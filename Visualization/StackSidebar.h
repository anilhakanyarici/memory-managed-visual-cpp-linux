#ifndef STACKSIDEBAR_H
#define STACKSIDEBAR_H

#include "BaseBin.h"
#include "Stack.h"

class StackSidebar : public BaseBin
{
public:
    static StackSidebar *New();

    Stack *stack() const;
    void stack(Stack *s);

    class Signals : public BaseBin::Signals{};
};


#endif // STACKSIDEBAR_H
