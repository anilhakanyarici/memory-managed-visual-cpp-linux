#include "UiScale.h"
#include "../String16.h"

UiScale *UiScale::New(GtkOrientation orientation, Adjustment *adj)
{
    return (UiScale *)gtk_scale_new(orientation, GTK_ADJUSTMENT(adj));
}

UiScale *UiScale::New(GtkOrientation orientation, double min, double max, double step)
{
    return (UiScale *)gtk_scale_new_with_range(orientation, min, max, step);
}

int UiScale::digits() const { return gtk_scale_get_digits(GTK_SCALE(this)); }

void UiScale::digits(int v) { gtk_scale_set_digits(GTK_SCALE(this), v); }

bool UiScale::drawValue() const { return gtk_scale_get_draw_value(GTK_SCALE(this)); }

void UiScale::drawValue(bool v) const { gtk_scale_set_draw_value(GTK_SCALE(this), v); }

bool UiScale::hasOrigin() const { return gtk_scale_get_has_origin(GTK_SCALE(this)); }

void UiScale::hasOrigin(bool v) const { gtk_scale_set_has_origin(GTK_SCALE(this), v); }

GtkPositionType UiScale::valuePositionType() const { return gtk_scale_get_value_pos(GTK_SCALE(this)); }

void UiScale::valuePositionType(GtkPositionType v) const { gtk_scale_set_value_pos(GTK_SCALE(this), v); }

Position UiScale::getLayoutOffset() const { Position p; gtk_scale_get_layout_offsets(GTK_SCALE(this), &p.X, &p.Y); return p; }

void UiScale::AddMark(double value, GtkPositionType type, const String16 &markup)
{
    ByteArray utf8 = markup.ToCString();
    gtk_scale_add_mark(GTK_SCALE(this), value, type, (const gchar *)utf8.data());
}

void UiScale::ClearMarks() { gtk_scale_clear_marks(GTK_SCALE(this)); }

