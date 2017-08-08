#ifndef ADJUSTMENT_H
#define ADJUSTMENT_H

#include <gtk/gtk.h>
#include "VObject.h"

class Adjustment : public VObject
{
public:
    static Adjustment *New(double value, double lower, double upper, double step_increment, double page_increment, double page_size);

    double value() const;
    void value(double v);
    double lower() const;
    void lower(double v);
    double upper() const;
    void upper(double v);
    double pageIncrement() const;
    void pageIncrement(double v);
    double pageSize() const;
    void pageSize(double v);
    double stepIncrement() const;
    void stepIncrement(double v);
    double getMinimumIncrement() const;

    void ClampPage(double lower, double upper);
    void Configure(double value, double lower, double upper, double step_increment, double page_increment, double page_size);

    class Signals
    {
     public:
        static RawSignal Changed(SignalCallback eventMethod, void *instance = nullptr, void *userData = nullptr); //Callback(Adjustment *, EventArgs *)
        static RawSignal ValueChanged(SignalCallback eventMethod, void *instance = nullptr, void *userData = nullptr); //Callback(Adjustment *, EventArgs *)
    };
};

#endif // ADJUSTMENT_H
