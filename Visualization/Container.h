#ifndef CONTAINER_H
#define CONTAINER_H

#include "BaseWidget.h"
#include "../Array.h"

class BaseContainer : public BaseWidget
{
protected:
    BaseContainer(GtkBaseContainer *widget) : BaseWidget(GTK_WIDGET(widget)) {}
public:
    uint borderWidth() const;
    void borderWidth(uint width);
    Array<BaseWidget *> childs();
    BaseWidget *focusChild();
    void focusChild(BaseWidget *child);

    void Add(BaseWidget *component);
    void CheckResize();
    WidgetPath GetChildPath(BaseWidget *child);
    void PropagateDraw(BaseWidget *child, GtkCairo *cr);
    void Remove(BaseWidget *component);

    class Signals : public BaseWidget::Signals
    {
    public:
        static Signal Add(SignalCallback eventMethod, void *instance = nullptr, void *userData = nullptr); //Callback(BaseContainer *, BaseWidget *, EventArgs *)
        static Signal CheckResize(SignalCallback eventMethod, void *instance = nullptr, void *userData = nullptr); //Callback(BaseContainer *, EventArgs *)
        static Signal Remove(SignalCallback eventMethod, void *instance = nullptr, void *userData = nullptr); //Callback(BaseContainer *, BaseWidget *, EventArgs *)
        static Signal SetFocusChild(SignalCallback eventMethod, void *instance = nullptr, void *userData = nullptr); //Callback(BaseContainer *, BaseWidget *, EventArgs *)
    };

};
class Bin : public BaseContainer
{
protected:
    Bin(GtkBin *widget) : BaseContainer(GTK_CONTAINER(widget)) {}
public:
    BaseWidget *binChild();

    class Signals : public BaseContainer::Signals{};
};
#endif // CONTAINER_H
