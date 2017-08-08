#ifndef LISTBOX_H
#define LISTBOX_H

#include "BaseBin.h"
#include "Adjustment.h"

class ListBoxRow : public BaseBin
{
public:
    static ListBoxRow *New();

    int activatable() const;
    void activatable(bool a);
    int getIndex() const;
    BaseWidget *header() const;
    void header(BaseWidget *w);
    bool isSelected() const;
    int selectable() const;
    void selectable(bool a);

    void MarkChanged();

    class Signals : public BaseBin::Signals
    {
    public:
        static Signal Activate(SignalCallback eventMethod, void *instance = nullptr, void *userData = nullptr); //Callback(ListBoxRow *, EventArgs *)
    };
};

class ListBox : public BaseContainer
{
public:
    static ListBox *New();

    bool activateOnSingleClick() const;
    void activateOnSingleClick(bool m);
    Adjustment *adjustment() const;
    void adjustment(Adjustment *a);
    GtkSelectionMode mode() const;
    void mode(GtkSelectionMode m);
    ListBoxRow *selectedRow() const;
    void selectedRow(ListBoxRow *row);

    void DragHighlightRow(ListBoxRow *row);
    void DragUnighlightRow();
    void InvalidateFilter();
    void InvalidateHeaders();
    void InvalidateSort();
    void Prepend(BaseWidget *child, int position);
    void Prepend(BaseWidget *child);
    ListBoxRow *RowAtIndex(int index);
    ListBoxRow *RowAtY(int y);
    void SelectAll();
    void SetPlaceholder(BaseWidget *placeholder);
    Array<ListBoxRow *> SelectedRows();
    void UnselectAll();
    void UnselectRow(ListBoxRow *row);

    class Signals : public BaseContainer::Signals
    {
        static RawSignal ActivateCursorRow(SignalCallback eventMethod, void *instance = nullptr, void *userData = nullptr); //Callback(ListBox *, EventArgs *)
        static RawSignal MoveCursor(SignalCallback eventMethod, void *instance = nullptr, void *userData = nullptr); //Callback(ListBox *, GtkMovementRow, int, EventArgs *)
        static RawSignal RowActivated(SignalCallback eventMethod, void *instance = nullptr, void *userData = nullptr); //Callback(ListBox *, ListBoxRow *, EventArgs *)
        static RawSignal RowSelected(SignalCallback eventMethod, void *instance = nullptr, void *userData = nullptr); //Callback(ListBox *, ListBoxRow *, EventArgs *)
        static RawSignal SelectAll(SignalCallback eventMethod, void *instance = nullptr, void *userData = nullptr); //Callback(ListBox *, EventArgs *)
        static RawSignal SelectedRowChanged(SignalCallback eventMethod, void *instance = nullptr, void *userData = nullptr); //Callback(ListBox *, EventArgs *)
        static RawSignal ToggleCursorRow(SignalCallback eventMethod, void *instance = nullptr, void *userData = nullptr); //Callback(ListBox *, EventArgs *)
        static RawSignal UnselectAll(SignalCallback eventMethod, void *instance = nullptr, void *userData = nullptr); //Callback(ListBox *, EventArgs *)
    };
};

#endif // LISTBOX_H
