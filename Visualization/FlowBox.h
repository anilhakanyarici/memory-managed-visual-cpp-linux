#ifndef FLOWBOX_H
#define FLOWBOX_H

#include "Adjustment.h"
#include "BaseBin.h"
#include "../Array.h"

class FlowBoxChild;

class FlowBox : public BaseContainer
{
public:
    static FlowBox *New();

    bool activateOnSingleClick() const;
    void activateOnSingleClick(bool h);
    bool homogenius() const;
    void homogenius(bool h);
    uint rowSpacing() const;
    void rowSpacing(uint h);
    GtkSelectionMode selectionMode() const;
    void selectionMode(GtkSelectionMode h);
    uint columnSpacing() const;
    void columnSpacing(uint h);
    uint minChildPerLine() const;
    void minChildPerLine(uint h);
    uint maxChildPerLine() const;
    void maxChildPerLine(uint h);

    void Insert(BaseWidget *child, int position);
    FlowBoxChild *GetChildAtIndex(int index);
    Array<FlowBoxChild *>SelectedChildrens();
    void SetHAdjustment(Adjustment *h);
    void SetVAdjustment(Adjustment *v);
    void Select(FlowBoxChild *child);
    void Unselect(FlowBoxChild *child);
    void SelectAll();
    void UnselectAll();

    class Signals : public BaseContainer::Signals
    {
    public:
        static RawSignal ActivateCursorChild(SignalCallback eventMethod, void *instance = nullptr, void *userData = nullptr); //Callback(FlowBox *, EventArgs *)
        static RawSignal ChildActivated(SignalCallback eventMethod, void *instance = nullptr, void *userData = nullptr); //Callback(FlowBox *, FlowBoxChild *, EventArgs *)
        static RawSignal MoveCursor(SignalCallback eventMethod, void *instance = nullptr, void *userData = nullptr); //Callback(FlowBox *, GtkMovementStep, int, EventArgs *)
        static RawSignal SelectAll(SignalCallback eventMethod, void *instance = nullptr, void *userData = nullptr); //Callback(FlowBox *, EventArgs *)
        static RawSignal SelectedChildrenChanged(SignalCallback eventMethod, void *instance = nullptr, void *userData = nullptr); //Callback(FlowBox *, EventArgs *)
        static RawSignal ToggleCursorChanged(SignalCallback eventMethod, void *instance = nullptr, void *userData = nullptr); //Callback(FlowBox *, EventArgs *)
        static RawSignal UnselectAll(SignalCallback eventMethod, void *instance = nullptr, void *userData = nullptr); //Callback(FlowBox *, EventArgs *)
    };
};

class FlowBoxChild : public BaseBin
{
public:
    static FlowBoxChild *New();

    int index() const;
    int isSelected() const;

    void MarkChanged();

    class Signals : public BaseBin::Signals
    {
    public:
        static RawSignal Activate(SignalCallback eventMethod, void *instance = nullptr, void *userData = nullptr); //Callback(FlowBoxChild *, EventArgs *)
    };
};

#endif // FLOWBOX_H
