#include "UiDrawingArea.h"

UiDrawingArea *UiDrawingArea::New()
{
    return (UiDrawingArea *)gtk_drawing_area_new();
}
