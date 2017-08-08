#ifndef BASEMENUSHELL_H
#define BASEMENUSHELL_H

#include "BaseContainer.h"

class BaseMenuShell : public BaseContainer
{
public:
    bool takeFocus() const;
    void takeFocus(bool tf);
    BaseWidget *getSelectedItem() const;
    BaseWidget *getParentShell() const;

    void ActivateItem(BaseWidget *menuItem, bool forceDeactive);
    void Append(BaseWidget *child);
    void Cancel();
    void Deactivate();
    void Deselect();
    void Insert(BaseWidget *child, int position);
    void Prepend(BaseWidget *child);
    void SelectFirst(bool searchSensitive);
    void SelectItem(BaseWidget *menuItem);

    class Signals : public BaseContainer::Signals
    {
    public:
        static RawSignal ActivateCurrent(SignalCallback eventMethod, void *instance = nullptr, void *userData = nullptr); //Callback(BaseMenuShell *, bool, EventArgs *)
        static RawSignal Cancel(SignalCallback eventMethod, void *instance = nullptr, void *userData = nullptr); //Callback(BaseMenuShell *, EventArgs *)
        static RawSignal CycleFocus(SignalCallback eventMethod, void *instance = nullptr, void *userData = nullptr); //Callback(BaseMenuShell *, GtkDirectionType, EventArgs *)
        static RawSignal Deactivate(SignalCallback eventMethod, void *instance = nullptr, void *userData = nullptr); //Callback(BaseMenuShell *, EventArgs *)
        static RawSignal Insert(SignalCallback eventMethod, void *instance = nullptr, void *userData = nullptr); //Callback(BaseMenuShell *, BaseWidget *, int, EventArgs *)
        static RawSignal MoveCurrent(SignalCallback eventMethod, void *instance = nullptr, void *userData = nullptr); //Callback(BaseMenuShell *, GtkMenuDirectionType, EventArgs *)
        static RawSignal MoveSelected(SignalCallback eventMethod, void *instance = nullptr, void *userData = nullptr); //Callback(BaseMenuShell *, int, EventArgs *)
        static RawSignal SelectionDone(SignalCallback eventMethod, void *instance = nullptr, void *userData = nullptr); //Callback(BaseMenuShell *, EventArgs *)
    };
};

#endif // BASEMENUSHELL_H
