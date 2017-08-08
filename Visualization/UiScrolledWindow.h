#ifndef UISCROLLEDWINDOW_H
#define UISCROLLEDWINDOW_H

#include "BaseBin.h"
#include "Adjustment.h"
#include "BaseRange.h"

class UiScrollbar : public BaseRange
{
public:
    static UiScrollbar *New(GtkOrientation orientation, Adjustment *adj);

    class Signals : public BaseRange::Signals{};
};

class UiScrolledWindow : public BaseBin
{
public:
    static UiScrolledWindow *New(Adjustment *h = NULL, Adjustment *v = NULL);

    UiScrollbar *getHScrollbar() const;
    UiScrollbar *getVScrollbar() const;
    GtkPolicyType getHPolicy() const;
    GtkPolicyType getVPolicy() const;

    GtkCornerType placement() const;
    void placement(GtkCornerType p);
    GtkShadowType shadowType() const;
    void shadowType(GtkShadowType p);
    bool kineticScrolling() const;
    void kineticScrolling(bool p);
    bool captureButtonPress () const;
    void captureButtonPress (bool p);
    bool overlayScrolling() const;
    void overlayScrolling(bool p);
    int minContentWidth() const;
    void minContentWidth(int p);
    int minContentHeight() const;
    void minContentHeight(int p);

    void SetPolicy(GtkPolicyType h, GtkPolicyType v);
    void UnsetPlacement();

    class Signals : public BaseBin::Signals
    {
    public:
        static RawSignal EdgeOvershot(SignalCallback eventMethod, void *instance = nullptr, void *userData = nullptr); //Callback(UiScrolledWindow *, GtkPositionType, EventArgs *)
        static RawSignal EdgeReached(SignalCallback eventMethod, void *instance = nullptr, void *userData = nullptr); //Callback(UiScrolledWindow *, GtkPositionType, EventArgs *)
        static RawSignal MoveFocusOut(SignalCallback eventMethod, void *instance = nullptr, void *userData = nullptr); //Callback(UiScrolledWindow *, GtkDirectionType, EventArgs *)
        static RawSignal ScrollChild(SignalCallback eventMethod, void *instance = nullptr, void *userData = nullptr); //Callback(UiScrolledWindow *, GtkScrollType, bool, EventArgs *)

    };
};
#endif // UISCROLLEDWINDOW_H
