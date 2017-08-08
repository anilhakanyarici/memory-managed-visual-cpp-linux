#include "UiProgressBar.h"
#include "../String16.h"

UiProgressBar *UiProgressBar::New()
{
    return (UiProgressBar *)gtk_progress_bar_new();
}

double UiProgressBar::fraction() const { return gtk_progress_bar_get_fraction(GTK_PROGRESS_BAR(this)); }
void UiProgressBar::fraction(double frc) { gtk_progress_bar_set_fraction(GTK_PROGRESS_BAR(this), frc); }
bool UiProgressBar::inverted() const { return gtk_progress_bar_get_inverted(GTK_PROGRESS_BAR(this)); }
void UiProgressBar::inverted(bool inv) { gtk_progress_bar_set_inverted(GTK_PROGRESS_BAR(this), inv); }
bool UiProgressBar::showText() const { return gtk_progress_bar_get_show_text(GTK_PROGRESS_BAR(this)); }
void UiProgressBar::showText(bool sht) { gtk_progress_bar_set_show_text(GTK_PROGRESS_BAR(this), sht); }
String16 UiProgressBar::text() const { return String16(gtk_progress_bar_get_text(GTK_PROGRESS_BAR(this))); }

void UiProgressBar::text(const String16 &text)
{
    ByteArray utf8 = text.ToCString();
    gtk_progress_bar_set_text(GTK_PROGRESS_BAR(this), (const char *)utf8.data());
}

PangoEllipsizeMode UiProgressBar::ellipsize() const { return gtk_progress_bar_get_ellipsize(GTK_PROGRESS_BAR(this)); }
void UiProgressBar::ellipsize(PangoEllipsizeMode pem) { gtk_progress_bar_set_ellipsize(GTK_PROGRESS_BAR(this), pem); }
double UiProgressBar::pulseStep() const { return gtk_progress_bar_get_pulse_step(GTK_PROGRESS_BAR(this)); }
void UiProgressBar::pulseStep(double pls) { gtk_progress_bar_set_pulse_step(GTK_PROGRESS_BAR(this), pls); }
void UiProgressBar::Pulse() { gtk_progress_bar_pulse(GTK_PROGRESS_BAR(this)); }
