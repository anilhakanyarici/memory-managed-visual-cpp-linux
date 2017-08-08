#ifndef CURSOR_H
#define CURSOR_H

#include "Display.h"

class Cursor
{
public:
    static Cursor *New(Display *disp, Pixelbuffer *pixbuf, int x, int y);
    static Cursor *New(Display *disp, CairoSurface *surface, double x, double y);
    static Cursor *New(Display *disp, const String16 &name);
    static Cursor *New(Display *disp, GdkCursorType type);

    static Cursor *Default(Display *disp = Display::Default());
    static Cursor *Help(Display *disp = Display::Default());
    static Cursor *Pointer(Display *disp = Display::Default());
    static Cursor *ContextMenu(Display *disp = Display::Default());
    static Cursor *Progress(Display *disp = Display::Default());
    static Cursor *Wait(Display *disp = Display::Default());
    static Cursor *Cell(Display *disp = Display::Default());
    static Cursor *Crosshair(Display *disp = Display::Default());
    static Cursor *Text(Display *disp = Display::Default());
    static Cursor *VerticalText(Display *disp = Display::Default());
    static Cursor *Alias(Display *disp = Display::Default());
    static Cursor *Copy(Display *disp = Display::Default());
    static Cursor *NoDrop(Display *disp = Display::Default());
    static Cursor *Move(Display *disp = Display::Default());
    static Cursor *NotAllowed(Display *disp = Display::Default());
    static Cursor *Grab(Display *disp = Display::Default());
    static Cursor *Grabbing(Display *disp = Display::Default());
    static Cursor *AllScroll(Display *disp = Display::Default());
    static Cursor *ColumnResize(Display *disp = Display::Default());
    static Cursor *RowResize(Display *disp = Display::Default());
    static Cursor *NResize(Display *disp = Display::Default());
    static Cursor *EResize(Display *disp = Display::Default());
    static Cursor *WResize(Display *disp = Display::Default());
    static Cursor *SResize(Display *disp = Display::Default());
    static Cursor *NEResize(Display *disp = Display::Default());
    static Cursor *NWResize(Display *disp = Display::Default());
    static Cursor *SEResize(Display *disp = Display::Default());
    static Cursor *SWResize(Display *disp = Display::Default());
    static Cursor *EWResize(Display *disp = Display::Default());
    static Cursor *NSResize(Display *disp = Display::Default());
    static Cursor *NESWResize(Display *disp = Display::Default());
    static Cursor *NWSEResize(Display *disp = Display::Default());
    static Cursor *ZoomIn(Display *disp = Display::Default());
    static Cursor *ZoomOut(Display *disp = Display::Default());

    Display *getDisplay() const;
    Pixelbuffer *getImage() const;
    GdkCursorType getType() const;

    CairoSurface *GetSurface(double *xHot, double *yHot) const;
};


#endif // CURSOR_H
