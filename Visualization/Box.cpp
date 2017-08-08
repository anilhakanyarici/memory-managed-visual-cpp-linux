#include "Box.h"

Box *Box::New(GtkOrientation orientation, int spacing)
{
    return (Box *)gtk_box_new(orientation, spacing);
}

bool Box::homogeneous() const { return gtk_box_get_homogeneous(GTK_BOX(this)); }
void Box::homogeneous(bool h) { gtk_box_set_homogeneous(GTK_BOX(this), h); }
int Box::spacing() const { return gtk_box_get_spacing(GTK_BOX(this)); }
void Box::spacing(int h) { gtk_box_set_spacing(GTK_BOX(this), h); }
GtkBaselinePosition Box::baselinePosition() const { return gtk_box_get_baseline_position(GTK_BOX(this)); }
void Box::baselinePosition(GtkBaselinePosition h) { gtk_box_set_baseline_position(GTK_BOX(this), h); }
BaseWidget *Box::centerWidget() const { return (BaseWidget *)gtk_box_get_center_widget(GTK_BOX(this)); }
void Box::centerWidget(BaseWidget *w) { gtk_box_set_center_widget(GTK_BOX(this), GTK_WIDGET(w)); }

void Box::End(BaseWidget *widget, bool expand, bool fill, uint padding) { gtk_box_pack_end(GTK_BOX(this), GTK_WIDGET(widget), expand, fill, padding); }
void Box::Start(BaseWidget *widget, bool expand, bool fill, uint padding) { gtk_box_pack_start(GTK_BOX(this), GTK_WIDGET(widget), expand, fill, padding); }
void Box::ReorderChild(BaseWidget *widget, int position) { gtk_box_reorder_child(GTK_BOX(this), GTK_WIDGET(widget), position); }
void Box::QueryChildPacking(BaseWidget *widget, bool *expand, bool *fill, uint *padding, GtkPackType *packType) { gtk_box_query_child_packing(GTK_BOX(this), GTK_WIDGET(widget), (gboolean *)expand, (gboolean *)fill, padding, packType); }
void Box::SetChildPacking(BaseWidget *widget, bool expand, bool fill, uint padding, GtkPackType packType) { gtk_box_set_child_packing(GTK_BOX(this), GTK_WIDGET(widget), expand, fill, padding, packType); }
