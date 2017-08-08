#ifndef BASEWIDGET_H
#define BASEWIDGET_H

#include <gtk/gtk.h>
#include <map>

#include "../Defs.h"
#include "EventArgs.h"
#include "VObject.h"
#include "../Array.h"

class StringList;
struct Position;
struct Size;
struct PreferredHeight;
struct PreferredWidth;
struct PreferredSize;
class FrameClock;
class AccelGroup;
class StyleContext;
class ActionGroup;
class WidgetPath;
class BaseWidget;
class UiWindow;
class CairoGC;
class Visual;
class DWindow;


class BaseWidget : public VObject
{
public:
    StringList actionPrefixes() const;
    GtkAllocation allocation() const;
    void allocation(const GtkAllocation *allocation);
    bool canDefault() const;
    void canDefault(bool can);
    bool canFocus() const;
    void canFocus(bool can);
    GtkAllocation clip();
    void clip(GtkAllocation *clip);
    GtkTextDirection direction() const;
    void direction(GtkTextDirection direction);
    GdkEventMask events() const;
    void events(GdkEventMask events);
    FrameClock *frameClock() const;
    int getAllocatedBaseline() const;
    int getAllocatedHeight() const;
    int getAllocatedWidth() const;
    long getWidgetId() const;
    bool hasDefault() const;
    bool hasFocus() const;
    bool hasGrab() const;
    bool hasTooltip() const;
    void hasTooltip(bool has);
    bool hasVisibleFocus() const;
    void hasWindow(bool has);
    bool hasWindow() const;
    bool inDestruction() const;
    bool isDrawable() const;
    bool isFocus() const;
    bool isTopLevel() const;
    bool isNull() const;
    bool mapped() const;
    void mapped(bool mapped);
    String16 name() const;
    void name(const String16 &name);
    bool noShowAll() const;
    void noShowAll(bool noShowAll);
    double opacity() const;
    void opacity(double opacity);
    bool paintable() const;
    void paintable(bool appPaintable);
    BaseWidget *parent() const;
    void parent(BaseWidget *parent);
    DWindow *parentWindow() const;
    void parentWindow(DWindow *parent);
    WidgetPath *path() const;
    PreferredHeight preferredHeight() const;
    PreferredHeight preferredHeight(int width) const;
    PreferredWidth preferredWidth() const;
    PreferredWidth preferredWidth(int height) const;
    PreferredSize preferedSize() const;
    bool realized() const;
    void realized(bool realized);
    bool receivesDefault() const;
    void receivesDefault(bool rd);
    int scaleFactor() const;
    bool sensitive() const;
    void sensitive(bool sens);
    GtkSizeRequestMode sizeRequestMode() const;
    void stateFlags(GtkStateFlags flags);
    GtkStateFlags stateFlags() const;
    StyleContext *styleContext() const;
    bool supportedMultidevice() const;
    void supportedMultidevice(bool smd);
    String16 tooltipMarkup() const;
    void tooltipMarkup(const String16 &ttmarkup);
    String16 tooltipText() const;
    void tooltipText(const String16 &tttext);
    UiWindow *tooltipWindow() const;
    void tooltipWindow(UiWindow *w);
    BaseWidget *topLevelParent() const;
    bool visible() const;
    void visible(bool visible);
    Visual *visual() const;
    void visual(Visual *v);
    DWindow *window() const;
    void window(DWindow *w);

    GtkAlign hAlign() const;
    void hAlign(GtkAlign align);
    bool hExpand() const;
    void hExpand(bool expand);
    bool hExpandSet() const;
    void hExpandSet(bool expand);
    int marginBottom() const;
    void marginBottom(int margin);
    int marginEnd() const;
    void marginEnd(int margin);
    int marginStart() const;
    void marginStart(int margin);
    int marginTop() const;
    void marginTop(int margin);
    GtkAlign vAlign() const;
    void vAlign(GtkAlign align);
    GtkAlign vAlignWithBaseline() const;
    bool vExpand() const;
    void vExpand(bool expand);
    bool vExpandSet() const;
    void vExpandSet(bool expand);

    bool Activate();
    void AddAccelerator(const String16 &signal, AccelGroup *accelGroup, uint key, GdkModifierType mod, GtkAccelFlags flags);
    BaseWidget *GetAncestor(GType firstAncestorType);
    void AddEvent(GdkEventMask event);
    void AddMNemonicLabel(BaseWidget *label);
    bool CanActivateAccelerator(uint signalId);
    bool ChildFocus(GtkDirectionType dirType);
    void ChildNotify(const String16 &childProperty);
    bool ComputeExpand(GtkOrientation orientation);
    void Destroy();
    bool Draw(CairoGC *gc);
    bool EmitMNemonicActivate(bool groupCycling);
    void ErrorBell();
    void FreezeChildNotify();
    ActionGroup GetActionGroup(const String16 &prefix);
    Array<BaseWidget *> GetMNemonicLabels();
    GdkModifierType GetModifierMask(GdkModifierIntent intent);
    void GrabDefault();
    void GrabFocus();
    void Hide();
    bool HideOnDelete();
    void InsertActionGroup(const String16 &name, ActionGroup *group);
    bool Intersect(GdkRectangle &area, GdkRectangle &intersection);
    bool IsAncestor(BaseWidget *ancestor);
    bool IsShadowed(Device *dev);
    bool KeyNavigationFailed(GtkDirectionType dirType);
    void Map();
    void QueueComputeExpand();
    void QueueDraw();
    void QueueDrawArea(int x, int y, int width, int height);
    void QueueResize();
    void QueueResizeNoReDraw();
    void Realize();
    void RegisterWindow(DWindow *window);
    bool RemoveAccelerator(AccelGroup *accelGroup, uint key, GdkModifierType mod);
    void RemoveMNemonicLabel(BaseWidget *label);
    void ResetStyle();
    void SetAccelGroupPath(const String16 &path, AccelGroup *accelGroup);
    void SetRedrawOnAllocate(bool redraw);
    void SetSizeRequest(int width, int height);
    void ShapeCombineRegion(CairoRegion *region);
    void Show();
    void ShowAll();
    void ThawChildNotify();
    bool TranslateCoordinates(Position srcPos, BaseWidget *destination, Position *destPos);
    void TriggerTooltipQuery();
    void Unmap();
    void Unparent();
    void Unrealize();
    void UnregisterWindow(DWindow *window);

    static GtkTextDirection defaultDirection();

    class Signals
    {
    public:
        static RawSignal AcceleratorClosuresChanged(SignalCallback eventMethod, void *instance = nullptr, void *userData = nullptr); //Callback(BaseWidget *, EventArgs *)
        static RawSignal ButtonPressEvent(SignalCallback eventMethod, void *instance = nullptr, void *userData = nullptr); //Callback(BaseWidget *, ButtonEventArgs *)
        static RawSignal ButtonReleaseEvent(SignalCallback eventMethod, void *instance = nullptr, void *userData = nullptr); //Callback(BaseWidget *, ButtonEventArgs *)
        static RawSignal CanActivateAccelerator(SignalCallback eventMethod, void *instance = nullptr, void *userData = nullptr); //Callback(BaseWidget *, uint, EventArgs *)
        static RawSignal ConfigureEvent(SignalCallback eventMethod, void *instance = nullptr, void *userData = nullptr); //Callback(BaseWidget *, ConfigureEventArgs *)
        static RawSignal DamageEvent(SignalCallback eventMethod, void *instance = nullptr, void *userData = nullptr); //Callback(BaseWidget *, ExposeEventArgs *)
        static RawSignal DeleteEvent(SignalCallback eventMethod, void *instance = nullptr, void *userData = nullptr); //Callback(BaseWidget *, EventArgs *)
        static RawSignal Destroy(SignalCallback eventMethod, void *instance = nullptr, void *userData = nullptr); //Callback(BaseWidget *, EventArgs *)
        static RawSignal DestroyEvent(SignalCallback eventMethod, void *instance = nullptr, void *userData = nullptr); //Callback(BaseWidget *, EventArgs *)
        static RawSignal DirectionChanged(SignalCallback eventMethod, void *instance = nullptr, void *userData = nullptr); //Callback(BaseWidget *, GtkTextDirection, EventArgs *)
        static RawSignal Draw(SignalCallback eventMethod, void *instance = nullptr, void *userData = nullptr); //Callback(BaseWidget *, CairoGC *, EventArgs *)
        static RawSignal Focus(SignalCallback eventMethod, void *instance = nullptr, void *userData = nullptr); //Callback(BaseWidget *, GtkDirectionType, EventArgs *)
        static RawSignal FocusInEvent(SignalCallback eventMethod, void *instance = nullptr, void *userData = nullptr); //Callback(BaseWidget *, FocusChangedEventArgs *)
        static RawSignal FocusOutEvent(SignalCallback eventMethod, void *instance = nullptr, void *userData = nullptr); //Callback(BaseWidget *, FocusChangedEventArgs *)
        static RawSignal GrabBrokenEvent(SignalCallback eventMethod, void *instance = nullptr, void *userData = nullptr); //Callback(BaseWidget *, GrabBrokenEventArgs *)
        static RawSignal GrabFocus(SignalCallback eventMethod, void *instance = nullptr, void *userData = nullptr); //Callback(BaseWidget *, EventArgs *)
        static RawSignal GrabNotify(SignalCallback eventMethod, void *instance = nullptr, void *userData = nullptr); //Callback(BaseWidget *, bool, EventArgs *)
        static RawSignal Hide(SignalCallback eventMethod, void *instance = nullptr, void *userData = nullptr); //Callback(BaseWidget *, EventArgs *)
        static RawSignal HierarchyChanged(SignalCallback eventMethod, void *instance = nullptr, void *userData = nullptr); //Callback(BaseWidget *, BaseWidget *, EventArgs *)
        static RawSignal KeyPressEvent(SignalCallback eventMethod, void *instance = nullptr, void *userData = nullptr); //Callback(BaseWidget *, KeyEventArgs *)
        static RawSignal KeyReleaseEvent(SignalCallback eventMethod, void *instance = nullptr, void *userData = nullptr); //Callback(BaseWidget *, KeyEventArgs *)
        static RawSignal KeyNavigationFailed(SignalCallback eventMethod, void *instance = nullptr, void *userData = nullptr); //Callback(BaseWidget *, GtkDirectionType, EventArgs *)
        static RawSignal PointerLeaveNotify(SignalCallback eventMethod, void *instance = nullptr, void *userData = nullptr); //Callback(BaseWidget *, CrossingEventArgs *)
        static RawSignal Map(SignalCallback eventMethod, void *instance = nullptr, void *userData = nullptr); //Callback(BaseWidget *, EventArgs *)
        static RawSignal MapEvent(SignalCallback eventMethod, void *instance = nullptr, void *userData = nullptr); //Callback(BaseWidget *, EventArgs *)
        static RawSignal MNemonicActivate(SignalCallback eventMethod, void *instance = nullptr, void *userData = nullptr); //Callback(BaseWidget *, bool, EventArgs *)
        static RawSignal MotionNotify(SignalCallback eventMethod, void *instance = nullptr, void *userData = nullptr); //Callback(BaseWidget *, MotionEventArgs *)
        static RawSignal MoveFocus(SignalCallback eventMethod, void *instance = nullptr, void *userData = nullptr); //Callback(BaseWidget *, GtkDirectionType, EventArgs *)
        static RawSignal PointerEnterNotify(SignalCallback eventMethod, void *instance = nullptr, void *userData = nullptr); //Callback(BaseWidget *, CrossingEventArgs *)
        static RawSignal ParentSet(SignalCallback eventMethod, void *instance = nullptr, void *userData = nullptr); //Callback(BaseWidget *, BaseWidget *, EventArgs *)
        static RawSignal PopupMenu(SignalCallback eventMethod, void *instance = nullptr, void *userData = nullptr); //Callback(BaseWidget *, EventArgs *)
        static RawSignal PropertyNotifyEvent(SignalCallback eventMethod, void *instance = nullptr, void *userData = nullptr); //Callback(BaseWidget *, PropertyEventArgs *)
        static RawSignal ProximityInEvent(SignalCallback eventMethod, void *instance = nullptr, void *userData = nullptr); //Callback(BaseWidget *, ProximityEventArgs *)
        static RawSignal ProximityOutEvent(SignalCallback eventMethod, void *instance = nullptr, void *userData = nullptr); //Callback(BaseWidget *, ProximityEventArgs *)
        static RawSignal Realize(SignalCallback eventMethod, void *instance = nullptr, void *userData = nullptr); //Callback(BaseWidget *, EventArgs *)
        static RawSignal ScrollEvent(SignalCallback eventMethod, void *instance = nullptr, void *userData = nullptr); //Callback(BaseWidget *, ScrollEventArgs *)
        static RawSignal ScreenChanged(SignalCallback eventMethod, void *instance = nullptr, void *userData = nullptr); //Callback(BaseWidget *, Screen *, ScrollEventArgs *)
        static RawSignal SelectionClearEvent(SignalCallback eventMethod, void *instance = nullptr, void *userData = nullptr); //Callback(BaseWidget *, SelectionEventArgs *)
        static RawSignal SelectionNotifyEvent(SignalCallback eventMethod, void *instance = nullptr, void *userData = nullptr); //Callback(BaseWidget *, SelectionEventArgs *)
        static RawSignal SelectionRequestEvent(SignalCallback eventMethod, void *instance = nullptr, void *userData = nullptr); //Callback(BaseWidget *, SelectionEventArgs *)
        static RawSignal Show(SignalCallback eventMethod, void *instance = nullptr, void *userData = nullptr); //Callback(BaseWidget *, EventArgs *)
        static RawSignal StyleUpdated(SignalCallback eventMethod, void *instance = nullptr, void *userData = nullptr); //Callback(BaseWidget *, EventArgs *)
        static RawSignal TouchEvent(SignalCallback eventMethod, void *instance = nullptr, void *userData = nullptr); //Callback(BaseWidget *, TouchEventArgs *)
        static RawSignal Unmap(SignalCallback eventMethod, void *instance = nullptr, void *userData = nullptr); //Callback(BaseWidget *, EventArgs *)
        static RawSignal UnmapEvent(SignalCallback eventMethod, void *instance = nullptr, void *userData = nullptr); //Callback(BaseWidget *, EventArgs *)
        static RawSignal UnRealize(SignalCallback eventMethod, void *instance = nullptr, void *userData = nullptr); //Callback(BaseWidget *, EventArgs *)
        static RawSignal WindowStateEvent(SignalCallback eventMethod, void *instance = nullptr, void *userData = nullptr); //Callback(BaseWidget *, WindowStateEventArgs *)
    };
};
#endif // BASEWIDGET_H
