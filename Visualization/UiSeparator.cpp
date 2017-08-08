#include "UiSeparator.h"

UiSeparator *UiSeparator::New(GtkOrientation orientation)
{
    return (UiSeparator *)gtk_separator_new(orientation);
}
