#ifndef UISCALE_H
#define UISCALE_H

#include "BaseRange.h"
#include "Adjustment.h"

class UiScale : public BaseRange
{
public:
    static UiScale *New(GtkOrientation orientation, Adjustment *adj);
    static UiScale *New(GtkOrientation orientation, double min, double max, double step);

    int digits() const;
    void digits(int v);
    bool drawValue() const;
    void drawValue(bool v) const;
    bool hasOrigin() const;
    void hasOrigin(bool v) const;
    GtkPositionType valuePositionType() const;
    void valuePositionType(GtkPositionType v) const;
    Position getLayoutOffset() const;

    void AddMark(double value, GtkPositionType type, const String16 &markup);
    void ClearMarks();

    class Signals : public BaseRange::Signals {};
};

#endif // UISCALE_H
