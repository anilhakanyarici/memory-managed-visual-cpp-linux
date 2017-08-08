#include "CairoGC.h"
#include "UiWindow.h"
#include "UiImage.h"
#include "StyleContext.h"

void CairoGC::SetSource(Color color)
{
    cairo_set_source_rgba((cairo_t *)(this), color.red(), color.green(), color.blue(), color.alpha());
}

void CairoGC::SetSource(CairoPattern *pattern)
{
    cairo_set_source((cairo_t*)this, (cairo_pattern_t *)pattern);
}

void CairoGC::SetSource(Pixelbuffer *buffer, double x, double y)
{
    gdk_cairo_set_source_pixbuf((cairo_t *)(this), GDK_PIXBUF(buffer), x, y);
}

void CairoGC::SetSource(DWindow *window, double x, double y)
{
    gdk_cairo_set_source_window((cairo_t *)(this), GDK_WINDOW(window), x, y);
}

void CairoGC::ShowPage() { cairo_show_page((cairo_t *)(this)); }

void CairoGC::ShowText(const String16 &text)
{
    ByteArray utf8 = text.ToCString();
    cairo_show_text((cairo_t *)this, (const char *)utf8.data());
}

bool CairoGC::ShouldDrawWindow(DWindow *win) { return gtk_cairo_should_draw_window((cairo_t *)this, GDK_WINDOW(win)); }
void CairoGC::Stroke() { cairo_stroke((cairo_t *)(this)); }
void CairoGC::StrokePreserve() { cairo_stroke_preserve((cairo_t *)(this)); }
void CairoGC::TransformToWindow(BaseWidget *wid, DWindow *win) { gtk_cairo_transform_to_window((cairo_t *)this, GTK_WIDGET(wid), GDK_WINDOW(win)); }
void CairoGC::Translate(double tx, double ty) { cairo_translate((cairo_t *)(this), tx, ty); }

void CairoGC::SetSource(CairoSurface *surf, double x, double y)
{
    cairo_set_source_surface((cairo_t *)(this), (cairo_surface_t *)surf, x, y);
}

void CairoGC::Fill()
{
    cairo_fill((cairo_t *)(this));
}

void CairoGC::FillExtents(double *x1, double *y1, double *x2, double *y2) { cairo_fill_extents((cairo_t *)(this), x1, y1, x2, y2); }
void CairoGC::FillPreserve() { cairo_fill_preserve((cairo_t *)(this)); }

Array<double> CairoGC::GetDash(double *offset)
{
    int dl = cairo_get_dash_count((cairo_t *)(this));
    double *data = new double[dl];
    cairo_get_dash((cairo_t *)(this), data, offset);
    Array<double> d = Array<double>(data, dl);
    delete data;
    return d;
}

cairo_text_extents_t CairoGC::TextExtents(const String16 &text)
{
    cairo_text_extents_t e;
    ByteArray utf8 = text.ToCString();
    cairo_text_extents((cairo_t *)this, (const char *)utf8.data(), &e);
    return e;
}

void CairoGC::LineTo(double x, double y) { cairo_line_to((cairo_t *)(this), x, y); }
void CairoGC::MaskSurface(CairoSurface *surf, double surfaceX, double surfaceY) { cairo_mask_surface((cairo_t *)(this), (cairo_surface_t *)surf, surfaceX, surfaceY); }
void CairoGC::MoveTo(double x, double y) { cairo_move_to((cairo_t *)(this), x, y); }

void CairoGC::SetDash(Array<double> dashes, double offset)
{
    cairo_set_dash((cairo_t *)(this), dashes.data(), dashes.length(), offset);
}

CairoGC *CairoGC::New(CairoSurface *target)
{
    return (CairoGC *)cairo_create((cairo_surface_t *)target);
}

CairoGC *CairoGC::New(DWindow *window) { return (CairoGC *)gdk_cairo_create(GDK_WINDOW(window)); }

cairo_antialias_t CairoGC::antialias() const { return cairo_get_antialias((cairo_t *)(this)); }
void CairoGC::antialias(cairo_antialias_t a) { cairo_set_antialias((cairo_t *)(this), a); }
cairo_fill_rule_t CairoGC::fillRule() const { return cairo_get_fill_rule((cairo_t *)(this)); }
void CairoGC::fillRule(cairo_fill_rule_t r) { cairo_set_fill_rule((cairo_t *)(this), r); }
double CairoGC::lineWidth() const { return cairo_get_line_width((cairo_t *)(this)); }
void CairoGC::lineWidth(double l) { cairo_set_line_width((cairo_t *)(this), l); }
double CairoGC::miterLimit() const { return cairo_get_miter_limit((cairo_t *)(this)); }
void CairoGC::miterLimit(double l) { cairo_set_miter_limit((cairo_t *)(this), l); }
double CairoGC::tolerance() const { return cairo_get_tolerance((cairo_t *)(this)); }
void CairoGC::tolerance(double l) { cairo_set_tolerance((cairo_t *)(this), l); }
cairo_line_cap_t CairoGC::lineCap() const { return cairo_get_line_cap((cairo_t *)(this)); }
void CairoGC::lineCap(cairo_line_cap_t cap) { cairo_set_line_cap((cairo_t *)(this), cap); }
cairo_line_join_t CairoGC::lineJoin() const { return cairo_get_line_join((cairo_t *)(this)); }
void CairoGC::lineJoin(cairo_line_join_t join) { cairo_set_line_join((cairo_t *)(this), join); }
cairo_operator_t CairoGC::operating() const { return cairo_get_operator((cairo_t *)(this)); }
void CairoGC::operating(cairo_operator_t op) { cairo_set_operator((cairo_t *)(this), op); }
DoublePosition CairoGC::getPoint() { DoublePosition p; cairo_get_current_point((cairo_t *)(this), &p.X, &p.Y); return p; }

CairoSurface *CairoGC::target() const { return (CairoSurface *)cairo_get_target((cairo_t *)this); }

void CairoGC::Arc(double xc, double yc, double radius, double angle1, double angle2)
{
    cairo_arc((cairo_t *)(this), xc, yc, radius, angle1, angle2);
}

void CairoGC::ArcNegative(double xc, double yc, double radius, double angle1, double angle2)
{
    cairo_arc_negative((cairo_t *)(this), xc, yc, radius, angle1, angle2);
}

void CairoGC::Circle(double xc, double yc, double radius){this->Arc(xc, yc, radius, 0, 6.28318531);}
void CairoGC::Clip() { cairo_clip((cairo_t *)(this)); }
void CairoGC::ClipExtents(double *x1, double *y1, double *x2, double *y2) { cairo_clip_extents((cairo_t *)(this), x1, y1, x2, y2); }
void CairoGC::ClipPreserve() { cairo_clip_preserve((cairo_t *)(this)); }
void CairoGC::ClosePath() { cairo_close_path((cairo_t *)(this)); }
void CairoGC::CopyPage() { cairo_copy_page((cairo_t *)(this)); }

void CairoGC::CurveTo(double x1, double y1, double x2, double y2, double x3, double y3)
{
    cairo_curve_to((cairo_t *)(this), x1, y1, x2, y2, x3, y3);
}

void CairoGC::Destroy() { cairo_destroy((cairo_t *)(this)); }

void CairoGC::Rectangle(double x, double y, double w, double h)
{
    cairo_rectangle((cairo_t *)(this), x, y, w, h);
}

void CairoGC::RelativeCurveTo(double dx1, double dy1, double dx2, double dy2, double dx3, double dy3) { cairo_rel_curve_to((cairo_t *)(this), dx1, dy1, dx2, dy2, dx3, dy3); }
void CairoGC::RelativeLineTo(double dx, double dy) { cairo_rel_line_to((cairo_t *)(this), dx, dy); }
void CairoGC::RelativeMoveTo(double dx, double dy) { cairo_rel_move_to((cairo_t *)(this), dx, dy); }
void CairoGC::Restore() { cairo_restore((cairo_t *)(this)); }
void CairoGC::Rotate(double angle) { cairo_rotate((cairo_t *)(this), angle); }
void CairoGC::Save() { cairo_save((cairo_t *)(this)); }
void CairoGC::Scale(double sx, double sy) { cairo_scale((cairo_t *)(this), sx, sy); }

void CairoGC::SelectFont(const String16 &family, cairo_font_slant_t slant, cairo_font_weight_t weight)
{
    ByteArray utf8 = family.ToCString();
    cairo_select_font_face((cairo_t *)this, (const char *)utf8.data(), slant, weight);
}

void CairoGC::SelectFontSize(double size) { cairo_set_font_size((cairo_t *)this, size); }

void CairoGC::Paint(double alpha)
{
    if(alpha == 1.0)
        cairo_paint((cairo_t *)(this));
    else
        cairo_paint_with_alpha((cairo_t *)(this), alpha);
}

CairoSurface *CairoSurface::New(UiWindow *window, cairo_content_t content, int width, int heigth)
{
    return (CairoSurface *)gdk_window_create_similar_surface(GDK_WINDOW(window), content, width, heigth);
}

CairoSurface *CairoSurface::New(int width, int height, cairo_format_t imageFormat)
{
    return (CairoSurface *)cairo_image_surface_create(imageFormat, width, height);
}

CairoSurface *CairoSurface::New(const String16 &pngFilePath)
{
    ByteArray utf8 = pngFilePath.ToCString();
    return (CairoSurface *)cairo_image_surface_create_from_png((const char *)utf8.data());
}

int CairoSurface::width() const { return cairo_image_surface_get_width((cairo_surface_t *)this); }
int CairoSurface::stride() const { return cairo_image_surface_get_stride((cairo_surface_t *)this); }
int CairoSurface::height() const { return cairo_image_surface_get_height((cairo_surface_t *)this); }

Pixelbuffer *CairoSurface::ScreenShot(int x, int y, int w, int h) { return (Pixelbuffer *)gdk_pixbuf_get_from_surface((cairo_surface_t *)(this), x, y, w, h); }
void CairoSurface::Destroy(){ cairo_surface_destroy((cairo_surface_t *)(this)); }
void CairoSurface::GetFallbackResolution(double *xPixelsPerInch, double *yPixelPerInch) { cairo_surface_get_fallback_resolution((cairo_surface_t *)(this), xPixelsPerInch, yPixelPerInch); }
void CairoSurface::SetFallbackResolution(double xPixelsPerInch, double yPixelPerInch) { cairo_surface_set_fallback_resolution((cairo_surface_t *)(this), xPixelsPerInch, yPixelPerInch); }

void CairoSurface::WriteToPng(const String16 &fileName)
{
    ByteArray a = fileName.ToCString();
    cairo_surface_write_to_png((cairo_surface_t *)this, (const char *)a.data());
}

void CairoPattern::Destroy() { cairo_pattern_destroy((cairo_pattern_t *)this); }
