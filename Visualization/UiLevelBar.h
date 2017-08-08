#ifndef UILEVELBAR_H
#define UILEVELBAR_H

#include "BaseWidget.h"
#include "../String16.h"

class UiLevelBar : public BaseWidget
{
public:
    static UiLevelBar *New(double min, double max);

    GtkLevelBarMode mode() const;
    void mode(GtkLevelBarMode m);
    double value() const;
    void value(double v);
    double minValue() const;
    void minValue(double v);
    double maxValue() const;
    void maxValue(double v);
    bool inverted() const;
    void inverted(bool v);

    void AddOffsetValue(const String16 &name, double value);
    void RemoveOffsetValue(const String16 &name);
    double GetOffsetValue(const String16 &name);

    class Signals : public BaseWidget::Signals
    {
    public:
        static RawSignal OffsetChanged(SignalCallback eventMethod, void *instance = nullptr, void *userData = nullptr); //Callback(UiLevelBar *, String16, EventArgs *)
    };
};

#endif // UILEVELBAR_H
