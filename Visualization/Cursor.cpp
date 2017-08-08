#include "Cursor.h"
#include "CairoGC.h"

Cursor *Cursor::Default(Display *disp) { return (Cursor *)gdk_cursor_new_from_name(GDK_DISPLAY(disp), "default"); }
Cursor *Cursor::Help(Display *disp) { return (Cursor *)gdk_cursor_new_from_name(GDK_DISPLAY(disp), "help"); }
Cursor *Cursor::Pointer(Display *disp) { return (Cursor *)gdk_cursor_new_from_name(GDK_DISPLAY(disp), "pointer"); }
Cursor *Cursor::ContextMenu(Display *disp) { return (Cursor *)gdk_cursor_new_from_name(GDK_DISPLAY(disp), "context-menu"); }
Cursor *Cursor::Progress(Display *disp) { return (Cursor *)gdk_cursor_new_from_name(GDK_DISPLAY(disp), "progress"); }
Cursor *Cursor::Wait(Display *disp) { return (Cursor *)gdk_cursor_new_from_name(GDK_DISPLAY(disp), "wait"); }
Cursor *Cursor::Cell(Display *disp) { return (Cursor *)gdk_cursor_new_from_name(GDK_DISPLAY(disp), "cell"); }
Cursor *Cursor::Crosshair(Display *disp) { return (Cursor *)gdk_cursor_new_from_name(GDK_DISPLAY(disp), "crosshair"); }
Cursor *Cursor::Text(Display *disp) { return (Cursor *)gdk_cursor_new_from_name(GDK_DISPLAY(disp), "text"); }
Cursor *Cursor::VerticalText(Display *disp) { return (Cursor *)gdk_cursor_new_from_name(GDK_DISPLAY(disp), "vertical-text"); }
Cursor *Cursor::Alias(Display *disp) { return (Cursor *)gdk_cursor_new_from_name(GDK_DISPLAY(disp), "alias"); }
Cursor *Cursor::Copy(Display *disp) { return (Cursor *)gdk_cursor_new_from_name(GDK_DISPLAY(disp), "copy"); }
Cursor *Cursor::NoDrop(Display *disp) { return (Cursor *)gdk_cursor_new_from_name(GDK_DISPLAY(disp), "no-drop"); }
Cursor *Cursor::Move(Display *disp) { return (Cursor *)gdk_cursor_new_from_name(GDK_DISPLAY(disp), "move"); }
Cursor *Cursor::NotAllowed(Display *disp) { return (Cursor *)gdk_cursor_new_from_name(GDK_DISPLAY(disp), "not-allowed"); }
Cursor *Cursor::Grab(Display *disp) { return (Cursor *)gdk_cursor_new_from_name(GDK_DISPLAY(disp), "grab"); }
Cursor *Cursor::Grabbing(Display *disp) { return (Cursor *)gdk_cursor_new_from_name(GDK_DISPLAY(disp), "grabbing"); }
Cursor *Cursor::AllScroll(Display *disp) { return (Cursor *)gdk_cursor_new_from_name(GDK_DISPLAY(disp), "all-scroll"); }
Cursor *Cursor::ColumnResize(Display *disp) { return (Cursor *)gdk_cursor_new_from_name(GDK_DISPLAY(disp), "col-resize"); }
Cursor *Cursor::RowResize(Display *disp) { return (Cursor *)gdk_cursor_new_from_name(GDK_DISPLAY(disp), "row-resize"); }
Cursor *Cursor::NResize(Display *disp) { return (Cursor *)gdk_cursor_new_from_name(GDK_DISPLAY(disp), "n-resize"); }
Cursor *Cursor::EResize(Display *disp) { return (Cursor *)gdk_cursor_new_from_name(GDK_DISPLAY(disp), "e-resize"); }
Cursor *Cursor::WResize(Display *disp) { return (Cursor *)gdk_cursor_new_from_name(GDK_DISPLAY(disp), "w-resize"); }
Cursor *Cursor::SResize(Display *disp) { return (Cursor *)gdk_cursor_new_from_name(GDK_DISPLAY(disp), "s-resize"); }
Cursor *Cursor::NEResize(Display *disp) { return (Cursor *)gdk_cursor_new_from_name(GDK_DISPLAY(disp), "ne-resize"); }
Cursor *Cursor::NWResize(Display *disp) { return (Cursor *)gdk_cursor_new_from_name(GDK_DISPLAY(disp), "nw-resize"); }
Cursor *Cursor::SEResize(Display *disp) { return (Cursor *)gdk_cursor_new_from_name(GDK_DISPLAY(disp), "se-resize"); }
Cursor *Cursor::SWResize(Display *disp) { return (Cursor *)gdk_cursor_new_from_name(GDK_DISPLAY(disp), "sw-resize"); }
Cursor *Cursor::EWResize(Display *disp) { return (Cursor *)gdk_cursor_new_from_name(GDK_DISPLAY(disp), "ew-resize"); }
Cursor *Cursor::NSResize(Display *disp) { return (Cursor *)gdk_cursor_new_from_name(GDK_DISPLAY(disp), "ns-resize"); }
Cursor *Cursor::NESWResize(Display *disp) { return (Cursor *)gdk_cursor_new_from_name(GDK_DISPLAY(disp), "nesw-resize"); }
Cursor *Cursor::NWSEResize(Display *disp) { return (Cursor *)gdk_cursor_new_from_name(GDK_DISPLAY(disp), "nwse-resize"); }
Cursor *Cursor::ZoomIn(Display *disp) { return (Cursor *)gdk_cursor_new_from_name(GDK_DISPLAY(disp), "zoom-in"); }
Cursor *Cursor::ZoomOut(Display *disp) { return (Cursor *)gdk_cursor_new_from_name(GDK_DISPLAY(disp), "zoom-out"); }

Display *Cursor::getDisplay() const { return (Display *)gdk_cursor_get_display(GDK_CURSOR(this)); }
Pixelbuffer *Cursor::getImage() const { return (Pixelbuffer *)gdk_cursor_get_image(GDK_CURSOR(this)); }
GdkCursorType Cursor::getType() const { return gdk_cursor_get_cursor_type(GDK_CURSOR(this)); }

CairoSurface *Cursor::GetSurface(double *xHot, double *yHot) const { return (CairoSurface *)gdk_cursor_get_surface(GDK_CURSOR(this), (gdouble *)xHot, (gdouble *)yHot); }
