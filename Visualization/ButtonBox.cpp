#include "ButtonBox.h"

GtkButtonBoxStyle ButtonBox::layout() const { return gtk_button_box_get_layout(GTK_BUTTON_BOX(this)); }
void ButtonBox::layout(GtkButtonBoxStyle style) { gtk_button_box_set_layout(GTK_BUTTON_BOX(this), style); }

ButtonBox *ButtonBox::New(GtkOrientation orientation) { return (ButtonBox *)gtk_button_box_new(orientation); }

bool ButtonBox::GetChildSecondary(BaseWidget *child) { return gtk_button_box_get_child_secondary(GTK_BUTTON_BOX(this), GTK_WIDGET(child)); }
bool ButtonBox::GetChildNonHomogeneous(BaseWidget *child) { return gtk_button_box_get_child_non_homogeneous(GTK_BUTTON_BOX(this), GTK_WIDGET(child)); }
void ButtonBox::SetChildSecondary(BaseWidget *child, bool isSecondary) { gtk_button_box_set_child_secondary(GTK_BUTTON_BOX(this), GTK_WIDGET(child), isSecondary); }
void ButtonBox::SetChildNonHomogeneous(BaseWidget *child, bool nonHomogeneous) { gtk_button_box_set_child_non_homogeneous(GTK_BUTTON_BOX(this), GTK_WIDGET(child), nonHomogeneous); }
