#include "UiHeaderBar.h"

UiHeaderBar *UiHeaderBar::New(const String16 &title)
{
    ByteArray utf8 = title.ToCString();
    GtkWidget *hb = gtk_header_bar_new();
    gtk_header_bar_set_title(GTK_HEADER_BAR(hb), (const char *)utf8.data());
    return (UiHeaderBar *)hb;
}

BaseWidget *UiHeaderBar::customTitle() const { return (BaseWidget *)gtk_header_bar_get_custom_title(GTK_HEADER_BAR(this)); }
void UiHeaderBar::customTitle(BaseWidget *widget) { gtk_header_bar_set_custom_title(GTK_HEADER_BAR(this), GTK_WIDGET(widget)); }
bool UiHeaderBar::hasSubtitle() const { return gtk_header_bar_get_has_subtitle(GTK_HEADER_BAR(this)); }
void UiHeaderBar::hasSubtitle(bool hs) { return gtk_header_bar_set_has_subtitle(GTK_HEADER_BAR(this), hs); }
bool UiHeaderBar::showCloseButton() const { return gtk_header_bar_get_show_close_button(GTK_HEADER_BAR(this)); }
void UiHeaderBar::showCloseButton(bool hs) { return gtk_header_bar_set_show_close_button(GTK_HEADER_BAR(this), hs); }
String16 UiHeaderBar::subtitle() const { return String16((const char *)gtk_header_bar_get_subtitle(GTK_HEADER_BAR(this))); }

void UiHeaderBar::subtitle(const String16 &title) const
{
    ByteArray utf8 = title.ToCString();
    gtk_header_bar_set_subtitle(GTK_HEADER_BAR(this), (const char *)utf8.data());
}
String16 UiHeaderBar::title() const { return String16((const char *)gtk_header_bar_get_title(GTK_HEADER_BAR(this))); }

void UiHeaderBar::title(const String16 &title) const
{
    ByteArray utf8 = title.ToCString();
    gtk_header_bar_set_title(GTK_HEADER_BAR(this), (const char *)utf8.data());
}

void UiHeaderBar::PackEnd(BaseWidget *widget) { gtk_header_bar_pack_end(GTK_HEADER_BAR(this), GTK_WIDGET(widget)); }
void UiHeaderBar::PackStart(BaseWidget *widget) { gtk_header_bar_pack_start(GTK_HEADER_BAR(this), GTK_WIDGET(widget)); }
