#ifndef CAIROGC_H
#define CAIROGC_H

#include <gtk/gtk.h>
#include "../Array.h"
#include "BaseWidget.h"

class Pixelbuffer;
class UiWindow;
class Color;
class CairoSurface;

class CairoPattern
{
public:
    static CairoPattern *NewFromLinear(double x0, double y0, double x1, double y1) { return (CairoPattern *)cairo_pattern_create_linear(x0, y0, x1, y1); }
    static CairoPattern *NewRadial(double cx0, double cy0, double radius0, double cx1, double cy1, double radius1) { return (CairoPattern *)cairo_pattern_create_radial(cx0, cy0, radius0, cx1, cy1, radius1); }
    static CairoPattern *NewForSurface(CairoSurface *surface) { return (CairoPattern *)cairo_pattern_create_for_surface((cairo_surface_t *)surface); }

    void AddColorStopRGB(double offset, double r, double g, double b) { cairo_pattern_add_color_stop_rgb((cairo_pattern_t *)this, offset, r, g, b); }
    void AddColorStopRGBA(double offset, double r, double g, double b, double a) { cairo_pattern_add_color_stop_rgba((cairo_pattern_t *)this, offset, r, g, b, a); }
    void Destroy();
    cairo_status_t GetColorStopCount(int *count) { return cairo_pattern_get_color_stop_count((cairo_pattern_t *)this, count); }
};

class CairoSurface
{
public:
    static CairoSurface *New(UiWindow *window, cairo_content_t content, int width, int heigth);
    static CairoSurface *New(int width, int height, cairo_format_t imageFormat = CAIRO_FORMAT_ARGB32);
    static CairoSurface *New(const String16 &pngFilePath);

    int width() const;
    int stride() const;
    int height() const;

    Pixelbuffer *ScreenShot(int x, int y, int w, int h);
    void Destroy();
    void GetFallbackResolution(double *xPixelsPerInch, double *yPixelPerInch);
    void SetFallbackResolution(double xPixelsPerInch, double yPixelPerInch);
    void WriteToPng(const String16 &fileName);
};

class CairoGC
{
public:
    static CairoGC *New(CairoSurface *target);
    static CairoGC *New(DWindow *window);

    cairo_antialias_t antialias() const;
    void antialias(cairo_antialias_t a);
    cairo_fill_rule_t fillRule() const;
    void fillRule(cairo_fill_rule_t r);
    double lineWidth() const;
    void lineWidth(double l);
    double miterLimit() const;
    void miterLimit(double l);
    double tolerance() const;
    void tolerance(double l);
    cairo_line_cap_t lineCap() const;
    void lineCap(cairo_line_cap_t cap);
    cairo_line_join_t lineJoin() const;
    void lineJoin(cairo_line_join_t join);
    cairo_operator_t operating() const;
    void operating(cairo_operator_t op);
    DoublePosition getPoint();
    CairoSurface *target() const;

    void Arc(double xc, double yc, double radius, double angle1, double angle2);
    void ArcNegative(double xc, double yc, double radius, double angle1, double angle2);
    void Circle(double xc, double yc, double radius);
    void Clip();
    void ClipExtents(double *x1, double *y1, double *x2, double *y2);
    void ClipPreserve();
    void ClosePath();
    void CopyPage();
    void CurveTo(double x1, double y1, double x2, double y2, double x3, double y3);
    void Destroy();
    void Fill();
    void FillExtents(double *x1, double *y1, double *x2, double *y2);
    void FillPreserve();
    Array<double> GetDash(double *offset);
    cairo_text_extents_t TextExtents(const String16 &text);
    void LineTo(double x, double y);
    void MaskSurface(CairoSurface *surf, double surfaceX, double surfaceY);
    void MoveTo(double x, double y);
    void Paint(double alpha = 1.0);
    void Rectangle(double x, double y, double w, double h);
    void RelativeCurveTo(double dx1, double dy1, double dx2, double dy2, double dx3, double dy3);
    void RelativeLineTo(double dx, double dy);
    void RelativeMoveTo(double dx, double dy);
    void Restore();
    void Rotate(double angle);
    void Save();
    void Scale(double sx, double sy);
    void SetDash(Array<double> dashes, double offset);
    void SelectFont(const String16 &family, cairo_font_slant_t slant, cairo_font_weight_t weight);
    void SelectFontSize(double size);
    void SetSource(Color color);
    void SetSource(CairoPattern *pattern);
    void SetSource(Pixelbuffer *buffer, double x, double y);
    void SetSource(CairoSurface *surf, double x, double y);
    void SetSource(DWindow *window, double x, double y);
    void ShowPage();
    void ShowText(const String16 &text);
    bool ShouldDrawWindow(DWindow *win);
    void Stroke();
    void StrokePreserve();
    void TransformToWindow(BaseWidget *wid, DWindow *win);
    void Translate(double tx, double ty);
};


class CairoRegion
{
public:
};
#endif // CAIROGC_H
