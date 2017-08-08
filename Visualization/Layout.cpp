#include "Layout.h"

Layout *Layout::New()
{
    return (Layout *)gtk_layout_new(NULL, NULL);
}

Size Layout::size() const
{
    Size s;
    gtk_layout_get_size(GTK_LAYOUT(this), (guint *)&s.Width, (guint *)&s.Height);
    return s;
}

void Layout::size(Size s) { gtk_layout_set_size(GTK_LAYOUT(this), s.Width, s.Height); }

UiWindow *Layout::getBinWindow() const { return (UiWindow *)gtk_layout_get_bin_window(GTK_LAYOUT(this)); }

void Layout::Put(BaseWidget *widget, Position pos) { gtk_layout_put(GTK_LAYOUT(this), GTK_WIDGET(widget), pos.X, pos.Y); }

void Layout::Put(BaseWidget *widget, int x, int y)
{
    Position p;
    p.X = x;
    p.Y = y;
    this->Put(widget, p);
}

void Layout::Move(BaseWidget *widget, Position pos) { gtk_layout_move(GTK_LAYOUT(this), GTK_WIDGET(widget), pos.X, pos.Y); }

void Layout::Move(BaseWidget *widget, int x, int y)
{
    Position p;
    p.X = x;
    p.Y = y;
    this->Move(widget, p);
}
