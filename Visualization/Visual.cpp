#include "Visual.h"
#include "Screen.h"

int Visual::getDepth() const { return gdk_visual_get_depth(GDK_VISUAL(this)); }
int Visual::getType() const { return gdk_visual_get_visual_type(GDK_VISUAL(this)); }
Screen *Visual::screen() const { return (Screen *)gdk_visual_get_screen(GDK_VISUAL(this)); }

void Visual::BluePixelDetails(uint *mask, int *shift, int *precision) { gdk_visual_get_blue_pixel_details(GDK_VISUAL(this), (guint32 *)mask, (gint *)shift, (gint *)precision); }
void Visual::GreenPixelDetails(uint *mask, int *shift, int *precision) { gdk_visual_get_green_pixel_details(GDK_VISUAL(this), (guint32 *)mask, (gint *)shift, (gint *)precision); }
void Visual::RedPixelDetails(uint *mask, int *shift, int *precision) { gdk_visual_get_red_pixel_details(GDK_VISUAL(this), (guint32 *)mask, (gint *)shift, (gint *)precision); }
