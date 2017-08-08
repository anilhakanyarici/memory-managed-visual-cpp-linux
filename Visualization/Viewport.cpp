#include "Viewport.h"


Viewport *Viewport::New()
{
    return (Viewport *)gtk_viewport_new(NULL, NULL);
}

GtkShadowType Viewport::shadowType() const { return gtk_viewport_get_shadow_type(GTK_VIEWPORT(this)); }

void Viewport::shadowType(GtkShadowType w) { gtk_viewport_set_shadow_type(GTK_VIEWPORT(this), w); }

UiWindow *Viewport::binWindow() const { return (UiWindow *)gtk_viewport_get_bin_window(GTK_VIEWPORT(this)); }

UiWindow *Viewport::viewWindow() const { return (UiWindow *)gtk_viewport_get_view_window(GTK_VIEWPORT(this)); }
