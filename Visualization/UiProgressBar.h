#ifndef UIPROGRESSBAR_H
#define UIPROGRESSBAR_H

#include "BaseWidget.h"

class UiProgressBar : public BaseWidget
{
public:
    static UiProgressBar *New();

    double fraction() const;
    void fraction(double frc);
    bool inverted() const;
    void inverted(bool inv);
    bool showText() const;
    void showText(bool sht);
    String16 text() const;
    void text(const String16 &text);
    PangoEllipsizeMode ellipsize() const;
    void ellipsize(PangoEllipsizeMode pem);
    double pulseStep() const;
    void pulseStep(double pls);

    void Pulse();
};

#endif // UIPROGRESSBAR_H
