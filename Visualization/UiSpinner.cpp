#include "UiSpinner.h"

UiSpinner *UiSpinner::New()
{
    return (UiSpinner *)gtk_spinner_new();
}

void UiSpinner::Start() { gtk_spinner_start(GTK_SPINNER(this)); }
void UiSpinner::Stop() { gtk_spinner_stop(GTK_SPINNER(this)); }
