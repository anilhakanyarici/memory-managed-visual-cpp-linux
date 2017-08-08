#ifndef CONTAINER_H
#define CONTAINER_H

#include "BaseWidget.h"
#include "../Array.h"
#include "Adjustment.h"

class BaseContainer : public BaseWidget
{
public:
    uint borderWidth() const;
    void borderWidth(uint width);
    Array<BaseWidget *> childs();
    BaseWidget *focusChild();
    void focusChild(BaseWidget *child);

    void Add(BaseWidget *component);
    void CheckResize();
    WidgetPath *GetChildPath(BaseWidget *child);
    Adjustment *focusVAdjustment() const;
    void focusVAdjustment(Adjustment * a);
    Adjustment *focusHAdjustment() const;
    void focusHAdjustment(Adjustment * a);

    void PropagateDraw(BaseWidget *child, CairoGC *cr);
    void Remove(BaseWidget *component);

    class Signals : public BaseWidget::Signals
    {
    public:
        static RawSignal Add(SignalCallback eventMethod, void *instance = nullptr, void *userData = nullptr); //Callback(BaseContainer *, BaseWidget *, EventArgs *)
        static RawSignal CheckResize(SignalCallback eventMethod, void *instance = nullptr, void *userData = nullptr); //Callback(BaseContainer *, EventArgs *)
        static RawSignal Remove(SignalCallback eventMethod, void *instance = nullptr, void *userData = nullptr); //Callback(BaseContainer *, BaseWidget *, EventArgs *)
        static RawSignal SetFocusChild(SignalCallback eventMethod, void *instance = nullptr, void *userData = nullptr); //Callback(BaseContainer *, BaseWidget *, EventArgs *)
    };

};
#endif // CONTAINER_H
