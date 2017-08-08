#ifndef BASEBIN_H
#define BASEBIN_H

#include "BaseContainer.h"

class BaseBin : public BaseContainer
{
public:
    BaseWidget *binChild();

    class Signals : public BaseContainer::Signals{};
};

#endif // BASEBIN_H
