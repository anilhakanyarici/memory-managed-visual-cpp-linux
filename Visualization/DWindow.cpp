#include "DWindow.h"
#include "../String16.h"
#include "Visual.h"

DWindow *DWindow::New(const String16 &title, int x, int y, int width, int height, DWindow *parent, GdkWindowWindowClass wclass, GdkWindowType type, Cursor *cursor, bool overrideRedirect, GdkWindowTypeHint hint, GdkWindowAttributesType attrMask)
{
    GdkWindowAttr attrs;
    ByteArray utf8 = title.ToCString();
    attrs.title = (gchar *)title.data();
    attrs.x = x;
    attrs.y = y;
    attrs.width = width;
    attrs.height = height;
    attrs.wclass = wclass;
    attrs.window_type = type;
    attrs.cursor = (GdkCursor *)cursor;
    attrs.override_redirect = overrideRedirect;
    attrs.type_hint = hint;
    return (DWindow *)gdk_window_new(GDK_WINDOW(parent), &attrs, (gint)attrMask);
}

DWindow *DWindow::DefaultRootWindow() { return (DWindow *)gdk_get_default_root_window(); }

GdkWindowType DWindow::type() const { return gdk_window_get_window_type(GDK_WINDOW(this)); }
Display *DWindow::display() const { return (Display *)gdk_window_get_display(GDK_WINDOW(this)); }
Screen *DWindow::screen() const { return (Screen *)gdk_window_get_screen(GDK_WINDOW(this)); }
Visual *DWindow::visual() const { return (Visual *)gdk_window_get_visual(GDK_WINDOW(this)); }
Cursor *DWindow::cursor() const { return (Cursor *)gdk_window_get_cursor(GDK_WINDOW(this)); }
void DWindow::cursor(Cursor *c) { gdk_window_set_cursor(GDK_WINDOW(this), GDK_CURSOR(c)); }
bool DWindow::isDestroyed() const { return gdk_window_is_destroyed(GDK_WINDOW(this)); }
bool DWindow::isVisible() const { return gdk_window_is_visible(GDK_WINDOW(this)); }
bool DWindow::isViewable() const { return gdk_window_is_viewable(GDK_WINDOW(this)); }
bool DWindow::isInputOnly() const { return gdk_window_is_input_only(GDK_WINDOW(this)); }
bool DWindow::isShaped() const { return gdk_window_is_shaped(GDK_WINDOW(this)); }
GdkWindowState DWindow::state() const { return gdk_window_get_state(GDK_WINDOW(this)); }
GdkFullscreenMode DWindow::fullscreenMode() const { return gdk_window_get_fullscreen_mode(GDK_WINDOW(this)); }
void DWindow::fullscreenMode(GdkFullscreenMode mode) { gdk_window_set_fullscreen_mode(GDK_WINDOW(this), mode); }
bool DWindow::passThrough() const { return gdk_window_get_pass_through(GDK_WINDOW(this)); }
void DWindow::passThrough(bool b) { gdk_window_set_pass_through(GDK_WINDOW(this), b); }
bool DWindow::hasNative() const { return gdk_window_has_native(GDK_WINDOW(this)); }
int DWindow::scaleFactor() const { return gdk_window_get_scale_factor(GDK_WINDOW(this)); }
CairoRegion *DWindow::getClipRegion() const { return (CairoRegion *)gdk_window_get_clip_region(GDK_WINDOW(this)); }
CairoRegion *DWindow::getVisibleRegion() const { return (CairoRegion *)gdk_window_get_visible_region(GDK_WINDOW(this)); }
CairoRegion *DWindow::getUpdateArea() const { return (CairoRegion *)gdk_window_get_update_area(GDK_WINDOW(this)); }
FrameClock *DWindow::frameClock() const { return (FrameClock *)gdk_window_get_frame_clock(GDK_WINDOW(this)); }
bool DWindow::acceptFocus() const { return gdk_window_get_accept_focus(GDK_WINDOW(this)); }
void DWindow::acceptFocus(bool b) { gdk_window_set_accept_focus(GDK_WINDOW(this), b); }
bool DWindow::focusOnMap() const { return gdk_window_get_focus_on_map(GDK_WINDOW(this)); }
void DWindow::focusOnMap(bool b) { gdk_window_set_focus_on_map(GDK_WINDOW(this), b); }
bool DWindow::width() const { return gdk_window_get_width(GDK_WINDOW(this)); }
bool DWindow::height() const { return gdk_window_get_height(GDK_WINDOW(this)); }
bool DWindow::modalHint() const { return gdk_window_get_modal_hint(GDK_WINDOW(this)); }
void DWindow::modalHint(bool m) { gdk_window_set_modal_hint(GDK_WINDOW(this), m); }
GdkWindowTypeHint DWindow::typeHint() const { return gdk_window_get_type_hint(GDK_WINDOW(this)); }
void DWindow::typeHint(GdkWindowTypeHint m) { gdk_window_set_type_hint(GDK_WINDOW(this), m); }
Position DWindow::position() const { Position p; gdk_window_get_position(GDK_WINDOW(this), &p.X, &p.Y); return p; }
Position DWindow::rootOrigin() const { Position p; gdk_window_get_root_origin(GDK_WINDOW(this), &p.X, &p.Y); return p; }
GdkRectangle DWindow::getFrameExtents() const { GdkRectangle p; gdk_window_get_frame_extents(GDK_WINDOW(this), &p); return p; }
DWindow *DWindow::parent() const { return (DWindow *)gdk_window_get_parent(GDK_WINDOW(this)); }
DWindow *DWindow::toplevel() const { return (DWindow *)gdk_window_get_toplevel(GDK_WINDOW(this)); }
GdkEventMask DWindow::events() const { return gdk_window_get_events(GDK_WINDOW(this)); }
void DWindow::events(GdkEventMask m) { gdk_window_set_events(GDK_WINDOW(this), m); }
DWindow *DWindow::group() const { return (DWindow *)gdk_window_get_group(GDK_WINDOW(this)); }
void DWindow::group(DWindow *m) { gdk_window_set_group(GDK_WINDOW(this), GDK_WINDOW(m)); }
GdkWMDecoration DWindow::decoration() const { GdkWMDecoration d; gdk_window_get_decorations(GDK_WINDOW(this), &d); return d; }
void DWindow::decoration(GdkWMDecoration m) { gdk_window_set_decorations(GDK_WINDOW(this), m); }
void DWindow::wmFunctions(GdkWMFunction m) { gdk_window_set_functions(GDK_WINDOW(this), m); }
bool DWindow::supportMultidevice() const { return gdk_window_get_support_multidevice(GDK_WINDOW(this)); }
void DWindow::supportMultidevice(bool b) { gdk_window_set_support_multidevice(GDK_WINDOW(this), b); }
CairoSurface *DWindow::surface() const { return (CairoSurface *)gdk_offscreen_window_get_surface(GDK_WINDOW(this)); }
DWindow *DWindow::embedder() const { return (DWindow *)gdk_offscreen_window_get_embedder(GDK_WINDOW(this)); }
void DWindow::embedder(DWindow *m) { gdk_offscreen_window_set_embedder(GDK_WINDOW(this), GDK_WINDOW(m)); }
DWindow *DWindow::effectiveParent() const { return (DWindow *)gdk_window_get_effective_parent(GDK_WINDOW(this)); }
DWindow *DWindow::effectiveToplevel() const { return (DWindow *)gdk_window_get_effective_toplevel(GDK_WINDOW(this)); }

void DWindow::Destroy() { gdk_window_destroy(GDK_WINDOW(this)); }
void DWindow::Show() { gdk_window_show(GDK_WINDOW(this)); }
void DWindow::ShowUnraised() { gdk_window_show_unraised(GDK_WINDOW(this)); }
void DWindow::Hide() { gdk_window_hide(GDK_WINDOW(this)); }
void DWindow::Withdraw() { gdk_window_withdraw(GDK_WINDOW(this)); }
void DWindow::Iconify() { gdk_window_iconify(GDK_WINDOW(this)); }
void DWindow::Deiconify() { gdk_window_deiconify(GDK_WINDOW(this)); }
void DWindow::Stick() { gdk_window_stick(GDK_WINDOW(this)); }
void DWindow::Unstick() { gdk_window_unstick(GDK_WINDOW(this)); }
void DWindow::Maximize() { gdk_window_maximize(GDK_WINDOW(this)); }
void DWindow::Unmaximize() { gdk_window_unmaximize(GDK_WINDOW(this)); }
void DWindow::Fullscreen() { gdk_window_fullscreen(GDK_WINDOW(this)); }
void DWindow::FullscreenOnMonitor(int monitor) { gdk_window_fullscreen_on_monitor(GDK_WINDOW(this), monitor); }
void DWindow::Unfullscreen() { gdk_window_unfullscreen(GDK_WINDOW(this)); }
void DWindow::SetKeepAbove(bool keep) { gdk_window_set_keep_above(GDK_WINDOW(this), keep); }
void DWindow::SetKeepBelow(bool keep) { gdk_window_set_keep_below(GDK_WINDOW(this), keep); }
void DWindow::SetOpacity(double o) { gdk_window_set_opacity(GDK_WINDOW(this), o); }
void DWindow::Move(int x, int y) { gdk_window_move(GDK_WINDOW(this), x, y); }
void DWindow::Resize(int width, int height) { gdk_window_resize(GDK_WINDOW(this), width, height); }
void DWindow::Scroll(int dx, int dy) { gdk_window_scroll(GDK_WINDOW(this), dx, dy); }
void DWindow::MoveRegion(CairoRegion *region, int dx, int dy) { gdk_window_move_region(GDK_WINDOW(this), (cairo_region_t *)region, dx, dy); }
bool DWindow::EnsureNative() { return gdk_window_ensure_native(GDK_WINDOW(this)); }
void DWindow::Reparent(DWindow *parent, int x, int y) { gdk_window_reparent(GDK_WINDOW(this), GDK_WINDOW(parent), x, y); }
void DWindow::Raise() { gdk_window_raise(GDK_WINDOW(this)); }
void DWindow::Lower() { gdk_window_lower(GDK_WINDOW(this)); }
void DWindow::Restack(DWindow *sibling, bool above) { gdk_window_restack(GDK_WINDOW(this), GDK_WINDOW(sibling), above); }
void DWindow::Focus(uint timestamp) { gdk_window_focus(GDK_WINDOW(this), timestamp); }
void DWindow::Beep() { gdk_window_beep(GDK_WINDOW(this)); }
void DWindow::SetOpaqueRegion(CairoRegion *region) { gdk_window_set_opaque_region(GDK_WINDOW(this), (cairo_region_t *)region); }
void DWindow::MarkPaintFromClip(CairoGC *gc) { gdk_window_mark_paint_from_clip(GDK_WINDOW(this), (cairo_t *)gc); }
void DWindow::InvalidateRectangle(GdkRectangle *rect, bool invalidateChild) { gdk_window_invalidate_rect(GDK_WINDOW(this), rect, invalidateChild); }
void DWindow::InvalidateRegion(CairoRegion *reg, bool invalidateChild) { gdk_window_invalidate_region(GDK_WINDOW(this), (cairo_region_t *)reg, invalidateChild); }
void DWindow::FreezeUpdates() { gdk_window_freeze_updates(GDK_WINDOW(this)); }
void DWindow::ThawUpdates() { gdk_window_thaw_updates(GDK_WINDOW(this)); }

void DWindow::SetStartupId(const String16 &id)
{
    ByteArray utf8 = id.ToCString();
    const char *cStr = (const char *)utf8.data();
    gdk_window_set_startup_id(GDK_WINDOW(this), cStr);
}

void DWindow::SetOverrideRedirect(bool m) { gdk_window_set_override_redirect(GDK_WINDOW(this), m); }
void DWindow::CombineRegion(CairoRegion *region, int offsetX, int offsetY) { gdk_window_shape_combine_region(GDK_WINDOW(this), (cairo_region_t *)region, offsetX, offsetY); }
void DWindow::InputShapeCombineRegion(CairoRegion *region, int offsetX, int offsetY) { gdk_window_input_shape_combine_region(GDK_WINDOW(this), (cairo_region_t *)region, offsetX, offsetY); }
void DWindow::SetChildShapes() { gdk_window_set_child_shapes(GDK_WINDOW(this)); }
void DWindow::MergeChildShapes() { gdk_window_merge_child_shapes(GDK_WINDOW(this)); }
void DWindow::SetChildInputShapes() { gdk_window_set_child_input_shapes(GDK_WINDOW(this)); }
void DWindow::MergeChildInputShapes() { gdk_window_merge_child_input_shapes(GDK_WINDOW(this)); }
void DWindow::SetTitle(const String16 &title) { ByteArray utf8 = title.ToCString(); gdk_window_set_title(GDK_WINDOW(this), (const gchar *)utf8.data()); }
void DWindow::GetGeometry(int *x, int *y, int *w, int *h) { gdk_window_get_geometry(GDK_WINDOW(this), (gint *)x, (gint *)y, (gint *)w, (gint *)h); }
void DWindow::SetShadowWidth(int left, int right, int top, int bottom) { gdk_window_set_shadow_width(GDK_WINDOW(this), left, right, top, bottom); }
void DWindow::SkipTaskbarHint(bool m) { gdk_window_set_skip_taskbar_hint(GDK_WINDOW(this), m); }
void DWindow::SkipPagerHint(bool m) { gdk_window_set_skip_pager_hint(GDK_WINDOW(this), m); }
void DWindow::SkipUrgencyHint(bool m) { gdk_window_set_urgency_hint(GDK_WINDOW(this), m); }
int DWindow::GetOrigin(int *x, int *y) { return gdk_window_get_origin(GDK_WINDOW(this), (gint *)x, (gint *)y); }
void DWindow::GetRootCoords(int x, int y, int *rootX, int *rootY) { gdk_window_get_root_coords(GDK_WINDOW(this), x, y, (gint *)rootX, (gint *)rootY); }
void DWindow::TransientFor(DWindow *parent) { gdk_window_set_transient_for(GDK_WINDOW(this), GDK_WINDOW(parent)); }
void DWindow::CoordsFromParent(double parentX, double parentY, double *x, double *y) { gdk_window_coords_from_parent(GDK_WINDOW(this), parentX, parentY, (gdouble *)x, (gdouble *)y); }
void DWindow::CoordsToParent(double x, double y, double *parentX, double *parentY) { gdk_window_coords_to_parent(GDK_WINDOW(this), x, y, (gdouble *)parentX, (gdouble *)parentY); }

Pixelbuffer *DWindow::ScreenShot(int x, int y, int w, int h) { return (Pixelbuffer *)gdk_pixbuf_get_from_window(GDK_WINDOW(this), x, y, w, h); }
