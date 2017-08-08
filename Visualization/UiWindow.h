#ifndef UIWINDOW_H
#define UIWINDOW_H

#include "../String16.h"
#include "AccelGroup.h"
#include "Atom.h"
#include "Display.h"
#include "BaseBin.h"

class Application;

class UiWindow : public BaseBin
{
public:
    static UiWindow *New(const String16 &title = "", GtkWindowType windowType = GtkWindowType::GTK_WINDOW_TOPLEVEL);

    Application *application() const;
    void application(Application *app);
    bool acceptFocus() const;
    void acceptFocus(bool accept);
    BaseWidget *attachedTo() const;
    void attachedTo(BaseWidget *component);
    bool decorated() const;
    void decorated(bool decorated);
    bool deletable() const;
    void deletable(bool deletable);
    Size defaultSize() const;
    void defaultSize(Size size);
    BaseWidget *defaultWidget() const;
    void defaultWidget(BaseWidget * w);
    bool destroyWithParent() const;
    void destroyWithParent(bool set);
    BaseWidget *focus();
    void focus(BaseWidget *focus);
    bool focusOnMap() const;
    void focusOnMap(bool focus);
    bool focusVisible();
    void focusVisible(bool fVis);
    DWindow *gdkWindow() const;
    Size getSize() const;
    Position getPosition() const;
    GtkWindowType getWindowType() const;
    GdkGravity gravity() const;
    void gravity(GdkGravity gravity);
    bool hasTopLevelFocus() const;
    bool hideTitlebarWhenMaximized() const;
    void hideTitlebarWhenMaximized(bool hide);
    String16 iconName() const;
    void iconName(const String16 &name);
    bool isActive() const;
    bool isMaximized() const;
    bool modal() const;
    void modal(bool modal);
    bool resizable() const;
    void resizable(bool resizable);
    String16 role() const;
    void role(const String16 &role);
    Screen *screen() const;
    void screen(Screen *s);
    bool skipPagerHint() const;
    void skipPagerHint(bool skip);
    bool skipTaskbarHint() const;
    void skipTaskbarHint(bool skip);
    String16 title() const;
    void title(const String16 &title);
    BaseWidget *titleBar() const;
    void titleBar(BaseWidget *bar);
    BaseWidget *transientFor() const;
    void transientFor(UiWindow *parent);
    GdkWindowTypeHint typeHint() const;
    void typeHint(GdkWindowTypeHint hint);
    bool urgencyHint() const;
    void urgencyHint(bool hint);


    bool ActivateDefault();
    bool ActivateFocus();
    void AddAccelGroup(AccelGroup *accelGroup);
    void ChangeAtomProperty(Atom property, Atom type, int format, GdkPropMode mode, const ByteArray &data, int elementSize);
    void Close();
    void Deiconify();
    void DeleteAtomProperty(Atom property);
    void FullScreen();
    void FullScreenOnMonitor(Screen *screen, int monitor);
    AtomProperty GetAtomProperty(Atom property, Atom type, ulong offset, ulong length, int pdelete) const;
    void Iconify();
    void Maximize();
    void Move(int x, int y);
    void Move(Position pos);
    void Present(uint timestamp = 0);
    void RemoveAccelGroup(AccelGroup *accelGroup);
    void Resize(int width, int height);
    void SetAttachTo(BaseWidget *component);
    bool SetIcon(const String16 &fileName);
    void SetGeometryHints(BaseWidget *geometryWidget, GdkGeometry *geo, GdkWindowHints geoMask);
    void SetKeepAbove(bool keepAbove);
    void SetKeepBelow(bool keepBelow);
    void SetStartupId(const String16 &id);
    void SetWindowPosition(GtkWindowPosition windPos);
    void Stick();
    void UnFullScreen();
    void UnMaximize();
    void UnStick();

    class Signals : public BaseBin::Signals
    {
    public:
        static RawSignal ActivateDefault(SignalCallback eventMethod, void *instance = nullptr, void *userData = nullptr); //Callback(UiWindow *, EventArgs *)
        static RawSignal ActivateFocus(SignalCallback eventMethod, void *instance = nullptr, void *userData = nullptr); //Callback(UiWindow *, EventArgs *)
        static RawSignal EnableDebugging(SignalCallback eventMethod, void *instance = nullptr, void *userData = nullptr); //Callback(UiWindow *, bool, EventArgs *)
        static RawSignal KeysChanged(SignalCallback eventMethod, void *instance = nullptr, void *userData = nullptr); //Callback(UiWindow *, EventArgs *)
        static RawSignal SetFocus(SignalCallback eventMethod, void *instance = nullptr, void *userData = nullptr); //Callback(UiWindow *, BaseWidget *, EventArgs *)

    };

    static Array<UiWindow *>Toplevels();
};
#endif // UIWINDOW_H
