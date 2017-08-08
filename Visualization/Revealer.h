#ifndef REVEALER_H
#define REVEALER_H

#include "BaseBin.h"

class Revealer : public BaseBin
{
public:
    static Revealer *New();

    bool revealChild() const;
    void revealChild(bool c);
    uint transitionDuration() const;
    void transitionDuration(uint c);
    bool isRevealed() const;
};

#endif // REVEALER_H
