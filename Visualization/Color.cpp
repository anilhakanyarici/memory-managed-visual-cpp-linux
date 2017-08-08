#include "Color.h"
#include "../String16.h"
#include "../ByteArray.h"

Color::Color(const String16 &colorString)
{
    ByteArray utf8 = colorString.ToCString();
    gdk_rgba_parse(&this->handler, (const gchar *)utf8.data());
}

Color::Color(double r, double g, double b, double a)
{
    this->handler.red = r;
    this->handler.green = g;
    this->handler.blue = b;
    this->handler.alpha = a;
}

double Color::alpha() const { return this->handler.alpha; }
void Color::alpha(double alpha) { this->handler.alpha = alpha; }
double Color::red() const { return this->handler.red; }
void Color::red(double red) { this->handler.red = red; }
double Color::green() const { return this->handler.green; }
void Color::green(double green) { this->handler.green = green; }
double Color::blue() const { return this->handler.blue; }
void Color::blue(double blue) { this->handler.blue = blue; }

uint Color::Hash() const { return gdk_rgba_hash(&this->handler); }


