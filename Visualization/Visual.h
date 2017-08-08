#ifndef VISUAL_H
#define VISUAL_H

#include "VObject.h"

class Screen;

class Visual : public VObject
{
public:
    int getDepth() const;
    int getType() const;
    Screen *screen() const;

    void BluePixelDetails(uint *mask, int *shift, int *precision);
    void GreenPixelDetails(uint *mask, int *shift, int *precision);
    void RedPixelDetails(uint *mask, int *shift, int *precision);
};

#endif // VISUAL_H
