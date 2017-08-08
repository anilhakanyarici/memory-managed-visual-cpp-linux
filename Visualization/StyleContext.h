#ifndef STYLECONTEXT_H
#define STYLECONTEXT_H

#include <gtk/gtk.h>
#include "FrameClock.h"
#include "CairoGC.h"
#include "Color.h"

class StyleContext
{
public:
    static StyleContext *New();

    GtkJunctionSides junctionSides() const;
    void junctionSides(GtkJunctionSides side);
    StyleContext *parent() const;
    void parent(StyleContext *sc);
    GtkStateFlags state() const;
    void state(GtkStateFlags flag);
    int scale() const;
    void scale(int sc);
    FrameClock *frameClock() const;

    Color GetColor(GtkStateFlags flag);
    GtkBorder GetBorder(GtkStateFlags flag);
    GtkBorder GetPadding(GtkStateFlags flag);
    void RenderArrow(CairoGC *cairo, double angle, double x, double y, double size);
    void RenderBackground(CairoGC *cairo, double x, double y, double width, double height);
    void RenderCheck(CairoGC *cairo, double x, double y, double width, double height);
    void RenderExpander(CairoGC *cairo, double x, double y, double width, double height);
    void RenderExtension(CairoGC *cairo, double x, double y, double width, double height, GtkPositionType gapSide);
    void RenderFocus(CairoGC *cairo, double x, double y, double width, double height);
    void RenderFrame(CairoGC *cairo, double x, double y, double width, double height);
    void RenderFrameGap(CairoGC *cairo, double x, double y, double width, double height, GtkPositionType gapSide, double xy0Gap, double xy1Gap);
    void RenderHandle(CairoGC *cairo, double x, double y, double width, double height);
    void RenderLine(CairoGC *cairo, double x0, double y0, double x1, double y1);
    void RenderOption(CairoGC *cairo, double x, double y, double width, double height);
    void RenderSlider(CairoGC *cairo, double x, double y, double width, double height, GtkOrientation orientation);
    void RenderActivity(CairoGC *cairo, double x, double y, double width, double height);
    void RenderIcon(CairoGC *cairo, Pixelbuffer *buffer, double x, double y);
    void RenderIconSurface(CairoGC *cairo, CairoSurface *surf, double x, double y);

    class Signals
    {
        static RawSignal Changed(SignalCallback eventMethod, void *instance = nullptr, void *userData = nullptr); //Callback(StyleContext *, EventArgs *)
    };
};

#endif // STYLECONTEXT_H
