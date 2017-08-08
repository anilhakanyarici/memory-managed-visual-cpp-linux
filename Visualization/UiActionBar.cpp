#include "UiActionBar.h"


UiActionBar *UiActionBar::New() { return (UiActionBar *)gtk_action_bar_new(); }

BaseWidget *UiActionBar::centerWidget() const { return (BaseWidget *) gtk_action_bar_get_center_widget(GTK_ACTION_BAR(this)); }

void UiActionBar::centerWidget(BaseWidget *child) { gtk_action_bar_set_center_widget(GTK_ACTION_BAR(this), GTK_WIDGET(child)); }

void UiActionBar::PackStart(BaseWidget *child) { gtk_action_bar_pack_start(GTK_ACTION_BAR(this), GTK_WIDGET(child)); }

void UiActionBar::PackEnd(BaseWidget *child) { gtk_action_bar_pack_end(GTK_ACTION_BAR(this), GTK_WIDGET(child)); }
