#include "Fixed.h"

Fixed *Fixed::New()
{
    return (Fixed *)gtk_fixed_new();
}

void Fixed::Put(BaseWidget *widget, Position pos) { gtk_fixed_put(GTK_FIXED(this), GTK_WIDGET(widget), pos.X, pos.Y); }

void Fixed::Put(BaseWidget *widget, int x, int y)
{
    Position p;
    p.X = x;
    p.Y = y;
    this->Put(widget, p);
}
void Fixed::Move(BaseWidget *widget, Position pos) { gtk_fixed_move(GTK_FIXED(this), GTK_WIDGET(widget), pos.X, pos.Y); }

void Fixed::Move(BaseWidget *widget, int x, int y)
{
    Position p;
    p.X = x;
    p.Y = y;
    this->Move(widget, p);
}
