#ifndef DWINDOW_H
#define DWINDOW_H

#include "VObject.h"
#include "Display.h"
#include "FrameClock.h"
#include "Cursor.h"

class CairoRegion;
class CairoGC;
class Visual;

class DrawingContext{};

class DWindow : public VObject
{
public:
    static DWindow *New(const String16 &title, int x, int y, int width, int height, DWindow *parent = NULL, GdkWindowWindowClass wclass = GDK_INPUT_OUTPUT, GdkWindowType type = GDK_WINDOW_TOPLEVEL, Cursor *cursor = Cursor::Default(), bool overrideRedirect = true, GdkWindowTypeHint hint = GDK_WINDOW_TYPE_HINT_NORMAL, GdkWindowAttributesType attrMask = (GdkWindowAttributesType)511);
    static DWindow *DefaultRootWindow();

    GdkWindowType type() const;
    Display *display() const;
    Screen *screen() const;
    Visual *visual() const;
    Cursor *cursor() const;
    void cursor(Cursor *c);
    bool isDestroyed() const;
    bool isVisible() const;
    bool isViewable() const;
    bool isInputOnly() const;
    bool isShaped() const;
    GdkWindowState state() const;
    GdkFullscreenMode fullscreenMode() const;
    void fullscreenMode(GdkFullscreenMode mode);
    bool passThrough() const;
    void passThrough(bool b);
    bool hasNative() const;
    int scaleFactor() const;
    CairoRegion *getClipRegion() const;
    CairoRegion *getVisibleRegion() const;
    CairoRegion *getUpdateArea() const;
    FrameClock *frameClock() const;
    bool acceptFocus() const;
    void acceptFocus(bool b);
    bool focusOnMap() const;
    void focusOnMap(bool b);
    bool width() const;
    bool height() const;
    bool modalHint() const;
    void modalHint(bool m);
    GdkWindowTypeHint typeHint() const;
    void typeHint(GdkWindowTypeHint m);
    Position position() const;
    Position rootOrigin() const;
    GdkRectangle getFrameExtents() const;
    DWindow *parent() const;
    DWindow *toplevel() const;
    GdkEventMask events() const;
    void events(GdkEventMask m);
    DWindow *group() const;
    void group(DWindow * m);
    GdkWMDecoration decoration() const;
    void decoration(GdkWMDecoration m);
    void wmFunctions(GdkWMFunction m);
    bool supportMultidevice() const;
    void supportMultidevice(bool b);
    CairoSurface *surface() const;
    DWindow *embedder() const;
    void embedder(DWindow * m);
    DWindow *effectiveParent() const;
    DWindow *effectiveToplevel() const;

    void Destroy();
    void Show();
    void ShowUnraised();
    void Hide();
    void Withdraw();
    void Iconify();
    void Deiconify();
    void Stick();
    void Unstick();
    void Maximize();
    void Unmaximize();
    void Fullscreen();
    void FullscreenOnMonitor(int monitor);
    void Unfullscreen();
    void SetKeepAbove(bool keep);
    void SetKeepBelow(bool keep);
    void SetOpacity(double o);
    void Move(int x, int y);
    void Resize(int width, int height);
    void Scroll(int dx, int dy);
    void MoveRegion(CairoRegion *region, int dx, int dy);
    bool EnsureNative();
    void Reparent(DWindow *parent, int x, int y);
    void Raise();
    void Lower();
    void Restack(DWindow *sibling, bool above);
    void Focus(uint timestamp);
    void Beep();
    void SetOpaqueRegion(CairoRegion *region);
    void MarkPaintFromClip(CairoGC *gc);
    void InvalidateRectangle(GdkRectangle *rect, bool invalidateChild);
    void InvalidateRegion(CairoRegion *reg, bool invalidateChild);
    void FreezeUpdates();
    void ThawUpdates();
    void SetStartupId(const String16 &id);
    void SetOverrideRedirect(bool m);
    void CombineRegion(CairoRegion *region, int offsetX, int offsetY);
    void InputShapeCombineRegion(CairoRegion *region, int offsetX, int offsetY);
    void SetChildShapes();
    void MergeChildShapes();
    void SetChildInputShapes();
    void MergeChildInputShapes();
    void SetTitle(const String16 &title);
    void GetGeometry(int *x, int *y, int *w, int *h);
    void SetShadowWidth(int left, int right, int top, int bottom);
    void SkipTaskbarHint(bool m);
    void SkipPagerHint(bool m);
    void SkipUrgencyHint(bool m);
    int GetOrigin(int *x, int *y);
    void GetRootCoords(int x, int y, int *rootX, int *rootY);
    void TransientFor(DWindow *parent);
    void CoordsFromParent(double parentX, double parentY, double *x, double *y);
    void CoordsToParent(double x, double y, double *parentX, double *parentY);
    Pixelbuffer *ScreenShot(int x, int y, int w, int h);
};

#endif // DWINDOW_H
