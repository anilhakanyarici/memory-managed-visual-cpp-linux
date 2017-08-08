#include "StyleContext.h"
#include "../String16.h"
#include "UiImage.h"

Delegate(StaticSignalMethod, void, StyleContext *, EventArgs *);
Delegate(InstanceSignalMethod, void, void *, StyleContext *, EventArgs *);

StyleContext *StyleContext::New()
{
    return (StyleContext *)gtk_style_context_new();
}

GtkJunctionSides StyleContext::junctionSides() const { return gtk_style_context_get_junction_sides(GTK_STYLE_CONTEXT(this)); }
void StyleContext::junctionSides(GtkJunctionSides side) { gtk_style_context_set_junction_sides(GTK_STYLE_CONTEXT(this), side); }
StyleContext *StyleContext::parent() const { return (StyleContext *)gtk_style_context_get_parent(GTK_STYLE_CONTEXT(this)); }
void StyleContext::parent(StyleContext *sc) { gtk_style_context_set_parent(GTK_STYLE_CONTEXT(this), GTK_STYLE_CONTEXT(sc)); }
GtkStateFlags StyleContext::state() const { return gtk_style_context_get_state(GTK_STYLE_CONTEXT(this)); }
void StyleContext::state(GtkStateFlags flag) { gtk_style_context_set_state(GTK_STYLE_CONTEXT(this), flag); }
int StyleContext::scale() const { return gtk_style_context_get_scale(GTK_STYLE_CONTEXT(this)); }
void StyleContext::scale(int sc) { gtk_style_context_set_scale(GTK_STYLE_CONTEXT(this), sc); }
FrameClock *StyleContext::frameClock() const { return (FrameClock *)(gtk_style_context_get_frame_clock(GTK_STYLE_CONTEXT(this))); }

Color StyleContext::GetColor(GtkStateFlags flag)
{
    Color c = Color(1,1,1,1);
    gtk_style_context_get_color(GTK_STYLE_CONTEXT(this), flag, &c.handler);
    return c;
}

GtkBorder StyleContext::GetBorder(GtkStateFlags flag)
{
    GtkBorder c = GtkBorder();
    gtk_style_context_get_border(GTK_STYLE_CONTEXT(this), flag, &c);
    return c;
}

GtkBorder StyleContext::GetPadding(GtkStateFlags flag)
{
    GtkBorder c = GtkBorder();
    gtk_style_context_get_border(GTK_STYLE_CONTEXT(this), flag, &c);
    return c;
}

void StyleContext::RenderArrow(CairoGC *cairo, double angle, double x, double y, double size) { gtk_render_arrow(GTK_STYLE_CONTEXT(this), (cairo_t *)(cairo), angle, x, y, size); }
void StyleContext::RenderBackground(CairoGC *cairo, double x, double y, double width, double height) { gtk_render_background(GTK_STYLE_CONTEXT(this), (cairo_t *)(cairo), x, y, width, height); }
void StyleContext::RenderCheck(CairoGC *cairo, double x, double y, double width, double height) { gtk_render_check(GTK_STYLE_CONTEXT(this), (cairo_t *)(cairo), x, y, width, height); }
void StyleContext::RenderExpander(CairoGC *cairo, double x, double y, double width, double height) { gtk_render_expander(GTK_STYLE_CONTEXT(this), (cairo_t *)(cairo), x, y, width, height); }
void StyleContext::RenderExtension(CairoGC *cairo, double x, double y, double width, double height, GtkPositionType gapSide) { gtk_render_extension(GTK_STYLE_CONTEXT(this), (cairo_t *)(cairo), x, y, width, height, gapSide); }
void StyleContext::RenderFocus(CairoGC *cairo, double x, double y, double width, double height) { gtk_render_focus(GTK_STYLE_CONTEXT(this), (cairo_t *)(cairo), x, y, width, height); }
void StyleContext::RenderFrame(CairoGC *cairo, double x, double y, double width, double height) { gtk_render_frame(GTK_STYLE_CONTEXT(this), (cairo_t *)(cairo), x, y, width, height); }
void StyleContext::RenderFrameGap(CairoGC *cairo, double x, double y, double width, double height, GtkPositionType gapSide, double xy0Gap, double xy1Gap) { gtk_render_frame_gap(GTK_STYLE_CONTEXT(this), (cairo_t *)(cairo), x, y, width, height, gapSide, xy0Gap, xy1Gap); }
void StyleContext::RenderHandle(CairoGC *cairo, double x, double y, double width, double height) { gtk_render_handle(GTK_STYLE_CONTEXT(this), (cairo_t *)(cairo), x, y, width, height); }
void StyleContext::RenderLine(CairoGC *cairo, double x0, double y0, double x1, double y1) { gtk_render_handle(GTK_STYLE_CONTEXT(this), (cairo_t *)(cairo), x0, y0, x1, y1); }
void StyleContext::RenderOption(CairoGC *cairo, double x, double y, double width, double height) { gtk_render_option(GTK_STYLE_CONTEXT(this), (cairo_t *)(cairo), x, y, width, height); }
void StyleContext::RenderSlider(CairoGC *cairo, double x, double y, double width, double height, GtkOrientation orientation) { gtk_render_slider(GTK_STYLE_CONTEXT(this), (cairo_t *)(cairo), x, y, width, height, orientation); }
void StyleContext::RenderActivity(CairoGC *cairo, double x, double y, double width, double height) { gtk_render_activity(GTK_STYLE_CONTEXT(this), (cairo_t *)(cairo), x, y, width, height); }
void StyleContext::RenderIcon(CairoGC *cairo, Pixelbuffer *buffer, double x, double y) { gtk_render_icon(GTK_STYLE_CONTEXT(this), (cairo_t *)(cairo), GDK_PIXBUF(buffer), x, y); }

void StyleContext::RenderIconSurface(CairoGC *cairo, CairoSurface *surf, double x, double y)
{
    gtk_render_icon_surface(GTK_STYLE_CONTEXT(this), (cairo_t *)(cairo), (cairo_surface_t *)surf, x, y);
}

RawSignal StyleContext::Signals::Changed(SignalCallback eventMethod, void *instance, void *userData)
{
    VSignal *s = new VSignal();
    s->eventMethod = (void *)eventMethod;
    s->userData = userData;
    s->instance = instance;
    s->signalName = "changed";
    void (*gtkmethod) (GtkStyleContext *, gpointer) = [](GtkStyleContext *sender, gpointer g) -> void{
        VSignal *signal = (VSignal *)g;
        EventArgs *eArgs = new EventArgs(nullptr);
        signal->args = eArgs;
        signal->args->EventSignal = signal;
        signal->args->UserData = signal->userData;
        if(signal->instance == nullptr){
            StaticSignalMethod ssm = (StaticSignalMethod)signal->eventMethod;
            ssm((StyleContext *)sender, signal->args);
        } else {
            InstanceSignalMethod ism = (InstanceSignalMethod)signal->eventMethod;
            ism(signal->instance, (StyleContext *)sender, signal->args);
        }
        delete eArgs;
    };
    s->callBack = G_CALLBACK(gtkmethod);
    return s;
}

