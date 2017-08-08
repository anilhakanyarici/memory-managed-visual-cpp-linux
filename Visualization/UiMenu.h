#ifndef UIMENU_H
#define UIMENU_H

#include "BaseMenuShell.h"
#include "BaseBin.h"

class UiMenuItem;

class UiMenu : public BaseMenuShell
{
public:
    static UiMenu *New();

    AccelGroup *accelGroup() const;
    void accelGroup(AccelGroup *acc);
    BaseWidget *getActive() const;

    int monitor() const;
    void monitor(int m);
    bool reserveToggleSize() const;
    void reserveToggleSize(bool m);

    void Attach(UiMenuItem *child, uint left, uint right, uint top, uint bottom);
    void Popdown();
    void ReorderChild(UiMenuItem *child, int position);
    void Reposition();
    void SetActive(int index);

    class Signals : public BaseMenuShell
    {
    public:
        static RawSignal MoveScroll(SignalCallback eventMethod, void *instance = nullptr, void *userData = nullptr); //Callback(UiMenu *, GtkScrollType, EventArgs *)
        static RawSignal PoppedUp(SignalCallback eventMethod, void *instance = nullptr, void *userData = nullptr); //Callback(UiMenu *, GdkRectangle *, GdkRectangle *, bool, bool, EventArgs *)
    };
};

class UiMenuBar : public BaseMenuShell
{
public:
    static UiMenuBar *New();

    GtkPackDirection childPackDirection() const;
    void childPackDirection(GtkPackDirection m);
    GtkPackDirection packDirection() const;
    void packDirection(GtkPackDirection m);

    class Signals : public BaseMenuShell::Signals{};
};

class UiMenuItem : public BaseBin
{
public:
    static UiMenuItem *New(const String16 &label);

    String16 label() const;
    void label(const String16 &label);
    bool useUnderline() const;
    void useUnderline(bool u);
    bool reserveIndicator() const;
    void reserveIndicator(bool u);
    UiMenuItem *submenu() const;
    void submenu(UiMenuItem *item);

    void Activate();
    void Deselect();
    void Select();
    void ToggleSizeAllocate(int t);
    void ToggleSizeRequest(int *requisition);

    class Signals : public BaseBin::Signals
    {
    public:
        static RawSignal Activate(SignalCallback eventMethod, void *instance = nullptr, void *userData = nullptr); //Callback(UiMenuItem *, EventArgs *)
        static RawSignal Select(SignalCallback eventMethod, void *instance = nullptr, void *userData = nullptr); //Callback(UiMenuItem *, EventArgs *)
        static RawSignal Deselect(SignalCallback eventMethod, void *instance = nullptr, void *userData = nullptr); //Callback(UiMenuItem *, EventArgs *)
        static RawSignal ToggleSizeAllocate(SignalCallback eventMethod, void *instance = nullptr, void *userData = nullptr); //Callback(UiMenuItem *, int, EventArgs *)
        static RawSignal ToggleSizeRequest(SignalCallback eventMethod, void *instance = nullptr, void *userData = nullptr); //Callback(UiMenuItem *, int *, EventArgs *)
    };
};

class UiCheckMenuItem : public UiMenuItem
{
public:
    static UiCheckMenuItem *New(const String16 &label);

    bool active() const;
    void active(bool u);
    bool inconsistent() const;
    void inconsistent(bool u);
    bool drawAsRadio() const;
    void drawAsRadio(bool u);

    void Toggled();

    class Signals : public UiMenuItem::Signals
    {
        static RawSignal Toggled(SignalCallback eventMethod, void *instance = nullptr, void *userData = nullptr); //Callback(UiCheckMenuItem *, EventArgs *)
    };
};
class UiSeparatorMenuItem : public UiMenuItem
{
public:
    static UiSeparatorMenuItem *New();

    class Signals : public UiMenuItem{};
};
#endif // UIMENU_H
