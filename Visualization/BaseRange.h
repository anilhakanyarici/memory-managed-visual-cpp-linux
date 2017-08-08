#ifndef BASERANGE_H
#define BASERANGE_H

#include "Adjustment.h"
#include "BaseWidget.h"

class BaseRange : public BaseWidget
{
public:
    Adjustment *adjustment() const;
    void adjustment(Adjustment *v) const;
    double fillLevel() const;
    void fillLevel(double v);
    bool flippable() const;
    void flippable(bool v);
    GdkRectangle getRangeRectangle() const;
    bool inverted() const;
    void inverted(bool v);
    GtkSensitivityType lowerStepSensitivity() const;
    void lowerStepSensitivity(GtkSensitivityType v);
    GtkSensitivityType upperStepSensitivity() const;
    void upperStepSensitivity(GtkSensitivityType v);
    bool restrictToFillLevel() const;
    void restrictToFillLevel(bool v);
    int roundDigit() const;
    void roundDigit(int v);
    bool showFillLevel() const;
    void showFillLevel(bool v);
    bool sizeFixed() const;
    void sizeFixed(bool v);
    double value() const;
    void value(double v);

    void SetIncrements(double step, double page);
    void SetRange(double min, double max);

    class Signals : public BaseWidget::Signals
    {
    public:
        static RawSignal AdjustBounds(SignalCallback eventMethod, void *instance = nullptr, void *userData = nullptr); //Callback(BaseRange *, double, EventArgs *)
        static RawSignal ChangeValue(SignalCallback eventMethod, void *instance = nullptr, void *userData = nullptr); //Callback(BaseRange *, GtkScrollType, double, EventArgs *)
        static RawSignal MoveSlider(SignalCallback eventMethod, void *instance = nullptr, void *userData = nullptr); //Callback(BaseRange *, GtkScrollType, EventArgs *)
        static RawSignal ValueChanged(SignalCallback eventMethod, void *instance = nullptr, void *userData = nullptr); //Callback(BaseRange *, EventArgs *)
    };
};

#endif // BASERANGE_H
