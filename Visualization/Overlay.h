#ifndef OVERLAY_H
#define OVERLAY_H

#include "BaseBin.h"

class Overlay : public BaseBin
{
public:
    static Overlay *New();

    bool GetOverlayPassThrough(BaseWidget *widget) const;
    void SetOverlayPassThrough(BaseWidget *widget, bool s);
    void AddOverlay(BaseWidget *child);
    void ReorderOverlay(BaseWidget *child, int position);

    class Signals : public BaseBin::Signals
    {
    public:
        static RawSignal GetChildPosition(SignalCallback eventMethod, void *instance = nullptr, void *userData = nullptr); //Callback(Overlay *, BaseWidget *, GdkRectangle *, EventArgs *)
    };

};

#endif // OVERLAY_H
