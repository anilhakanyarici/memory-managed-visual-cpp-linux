#ifndef UISPINBUTTON_H
#define UISPINBUTTON_H

#include "UiEntry.h"
#include "Adjustment.h"

class UiSpinButton : public UiEntry
{
public:
    static UiSpinButton *New(Adjustment *adj, double climbRate, double precision);
    static UiSpinButton *New(double min, double max, double step);

    Adjustment *adjustment() const;
    void adjustment(Adjustment *v) const;
    bool isNumeric() const;
    void isNumeric(bool b);
    double maximumValue() const;
    void maximumValue(double m);
    double minimumValue() const;
    void minimumValue(double m);
    double page() const;
    void page(double p);
    uint precision() const;
    void precision(uint p);
    double step() const;
    void step(double s);
    GtkSpinButtonUpdatePolicy updatePolicy() const;
    void updatePolicy(GtkSpinButtonUpdatePolicy p);
    double value() const;
    void value(double d);
    bool wrap() const;
    void wrap(bool w);
    bool snapToTicks() const;
    void snapToTicks(bool b) const;

    void Configure(Adjustment *adj, double climbRate, double precision);
    void Spin(GtkSpinType direction, double increment);
    void Update();

    class Signals : UiEntry::Signals
    {
    public:
        static RawSignal ChangeValue(SignalCallback eventMethod, void *instance = nullptr, void *userData = nullptr); //Callback(UiSpinButton *, GtkScrollType, EventArgs *)
        static RawSignal Input(SignalCallback eventMethod, void *instance = nullptr, void *userData = nullptr); //Callback(UiSpinButton *, String16, EventArgs *)
        static RawSignal Output(SignalCallback eventMethod, void *instance = nullptr, void *userData = nullptr); //Callback(UiSpinButton *, EventArgs *)
        static RawSignal ValueChanged(SignalCallback eventMethod, void *instance = nullptr, void *userData = nullptr); //Callback(UiSpinButton *, EventArgs *)
        static RawSignal Wrapped(SignalCallback eventMethod, void *instance = nullptr, void *userData = nullptr); //Callback(UiSpinButton *, EventArgs *)
    };
};

#endif // UISPINBUTTON_H
