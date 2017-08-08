#ifndef STACKSWITCHER_H
#define STACKSWITCHER_H

#include "Stack.h"
#include "Box.h"

class StackSwitcher : public Box
{
public:
    static StackSwitcher *New();

    Stack *stack() const;
    void stack(Stack *s);

    class Signals : public Box::Signals{};
};


#endif // STACKSWITCHER_H
