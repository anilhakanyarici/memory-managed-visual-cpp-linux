#ifndef FIXED_H
#define FIXED_H

#include "BaseContainer.h"

class Fixed : public BaseContainer
{
public:
    static Fixed *New();

    void Put(BaseWidget *widget, Position pos);
    void Put(BaseWidget *widget, int x, int y);
    void Move(BaseWidget *widget, Position pos);
    void Move(BaseWidget *widget, int x, int y);
};

#endif // FIXED_H
