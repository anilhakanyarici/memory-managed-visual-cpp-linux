#include "UiFrame.h"
#include "../String16.h"

UiFrame *UiFrame::New(const String16 &label)
{
    ByteArray utf8 = label.ToCString();
    return (UiFrame *)gtk_frame_new((const gchar *)utf8.data());
}

String16 UiFrame::label() const { return String16(gtk_frame_get_label(GTK_FRAME(this))); }

void UiFrame::label(const String16 &label)
{
    ByteArray utf8 = label.ToCString();
    gtk_frame_set_label(GTK_FRAME(this), (const gchar *)utf8.data());
}

BaseWidget *UiFrame::labelWidget() const { return (BaseWidget *)gtk_frame_get_label_widget(GTK_FRAME(this)); }

void UiFrame::labelWidget(BaseWidget *w) { gtk_frame_set_label_widget(GTK_FRAME(this), GTK_WIDGET(w)); }

DoublePosition UiFrame::labelAlign() const
{
    DoublePosition dp;
    float x, y;
    gtk_frame_get_label_align(GTK_FRAME(this), &x, &y);
    dp.X = x; dp.Y = y;
    return dp;
}

void UiFrame::labelAlign(DoublePosition align) { gtk_frame_set_label_align(GTK_FRAME(this), align.X, align.Y); }

GtkShadowType UiFrame::shadowType() const { return gtk_frame_get_shadow_type(GTK_FRAME(this)); }

void UiFrame::shadowType(GtkShadowType w) { gtk_frame_set_shadow_type(GTK_FRAME(this), w); }
