#ifndef COLOR_H
#define COLOR_H

#include "VObject.h"

class Color
{
public:
    GdkRGBA handler;
    Color(const String16 &colorString);
    Color(double r, double g, double b, double a);

    double alpha() const;
    void alpha(double alpha);
    double red() const;
    void red(double red);
    double green() const;
    void green(double green);
    double blue() const;
    void blue(double blue);

    uint Hash() const;

    inline static Color AliceBlue(double alpha = 1.0) { return Color(0.94, 0.97, 1.0, alpha); }
    inline static Color AntiqueWhite(double alpha = 1.0) { return Color(0.98, 0.92, 0.84, alpha); }
    inline static Color Aqua(double alpha = 1.0) { return Color(0, 1.0, 1.0, alpha); }
    inline static Color Aquamarine(double alpha = 1.0) { return Color(0.5, 1.0, 0.83, alpha); }
    inline static Color Azure(double alpha = 1.0) { return Color(0.94, 1.0, 1.0, alpha); }
    inline static Color Beige(double alpha = 1.0) { return Color(0.96, 0.96, 0.86, alpha); }
    inline static Color Bisque(double alpha = 1.0) { return Color(1.0, 0.89, 0.83, alpha); }
    inline static Color Black(double alpha = 1.0) { return Color(0, 0, 0, alpha); }
    inline static Color BlancehAlmond(double alpha = 1.0) { return Color(1.0, 0.92, 0.80, alpha); }
    inline static Color Blue(double alpha = 1.0) { return Color(0, 0, 1.0, alpha); }
    inline static Color BlueViolet(double alpha = 1.0) { return Color(0.54, 0.17, 0.89, alpha); }
    inline static Color Brown(double alpha = 1.0) { return Color(0.65, 0.16, 0.16, alpha); }
    inline static Color BurlyWood(double alpha = 1.0) { return Color(0.87, 0.72, 0.53, alpha); }
    inline static Color CadetBlue(double alpha = 1.0) { return Color(0.37, 0.62, 0.63, alpha); }
    inline static Color Chartreuse(double alpha = 1.0) { return Color(0.50, 1.0, 0, alpha); }
    inline static Color Chocolate(double alpha = 1.0) { return Color(0.82, 0.41, 0.12, alpha); }
    inline static Color Coral(double alpha = 1.0) { return Color(1.0, 0.5, 0.31, alpha); }
    inline static Color CornFlower(double alpha = 1.0) { return Color(0.39, 0.58, 0.93, alpha); }
    inline static Color Cornsilk(double alpha = 1.0) { return Color(1.0, 0.97, 0.86, alpha); }
    inline static Color Crimson(double alpha = 1.0) { return Color(0.86, 0.8, 0.24, alpha); }
    inline static Color Cyan(double alpha = 1.0) { return Color(0.0, 1.0, 1.0, alpha); }
    inline static Color DarkBlue(double alpha = 1.0) { return Color(0.0, 0.0, 0.55, alpha); }
    inline static Color DarkCyan(double alpha = 1.0) { return Color(0.0, 0.55, 0.55, alpha); }
    inline static Color DarkGoldenrod(double alpha = 1.0) { return Color(0.72, 0.53, 0.4, alpha); }
    inline static Color DarkGray(double alpha = 1.0) { return Color(0.66, 0.66, 0.66, alpha); }
    inline static Color DarkGreen(double alpha = 1.0) { return Color(0.0, 0.39, 0.0, alpha); }
    inline static Color DarkKhaki(double alpha = 1.0) { return Color(0.74, 0.72, 0.42, alpha); }
    inline static Color DarkMagenta(double alpha = 1.0) { return Color(0.55, 0.0, 0.55, alpha); }
    inline static Color DarkOliveGreen(double alpha = 1.0) { return Color(0.33, 0.42, 0.18, alpha); }
    inline static Color DarkOrange(double alpha = 1.0) { return Color(1.0, 0.55, 0.0, alpha); }
    inline static Color DarkOrchid(double alpha = 1.0) { return Color(0.60, 0.20, 0.80, alpha); }
    inline static Color DarkRed(double alpha = 1.0) { return Color(0.55, 0.0, 0.0, alpha); }
    inline static Color DarkSalmon(double alpha = 1.0) { return Color(0.91, 0.59, 0.48, alpha); }
    inline static Color DarkSeaGreen(double alpha = 1.0) { return Color(0.56, 0.74, 0.56, alpha); }
    inline static Color DarkSlateBlue(double alpha = 1.0) { return Color(0.28, 0.24, 0.55, alpha); }
    inline static Color DarkSlateGray(double alpha = 1.0) { return Color(0.28, 0.31, 0.31, alpha); }
    inline static Color DarkTurquoise(double alpha = 1.0) { return Color(0.0, 0.81, 0.82, alpha); }
    inline static Color DarkViolet(double alpha = 1.0) { return Color(0.58, 0.0, 0.83, alpha); }
    inline static Color DeepPink(double alpha = 1.0) { return Color(1.0, 0.8, 0.58, alpha); }
    inline static Color DeepSkyBlue(double alpha = 1.0) { return Color(0.0, 0.75, 1.0, alpha); }
    inline static Color DimGray(double alpha = 1.0) { return Color(0.41, 0.41, 0.41, alpha); }
    inline static Color DodgerBlue(double alpha = 1.0) { return Color(0.12, 0.56, 1.0, alpha); }
    inline static Color FireBrick(double alpha = 1.0) { return Color(0.70, 0.13, 0.13, alpha); }
    inline static Color FloralWhite(double alpha = 1.0) { return Color(1.0, 0.98, 0.94, alpha); }
    inline static Color ForestGreen(double alpha = 1.0) { return Color(0.13, 0.55, 0.13, alpha); }
    inline static Color Fuchsia(double alpha = 1.0) { return Color(1.0, 0.0, 1.0, alpha); }
    inline static Color Gainsboro(double alpha = 1.0) { return Color(0.86, 0.86, 0.86, alpha); }
    inline static Color GhostWhite(double alpha = 1.0) { return Color(0.97, 0.97, 1.0, alpha); }
    inline static Color Gold(double alpha = 1.0) { return Color(1.0, 0.84, 0.0, alpha); }
    inline static Color Goldenrod(double alpha = 1.0) { return Color(0.85, 0.65, 0.13, alpha); }
    inline static Color Gray(double alpha = 1.0) { return Color(0.75, 0.75, 0.75, alpha); }
    inline static Color Green(double alpha = 1.0) { return Color(0.0, 1.0, 0.0, alpha); }
    inline static Color GreenYellow(double alpha = 1.0) { return Color(0.68, 1.0, 0.18, alpha); }
    inline static Color Honeydew(double alpha = 1.0) { return Color(0.94, 1.0, 0.95, alpha); }
    inline static Color HotPink(double alpha = 1.0) { return Color(1.0, 0.41, 0.71, alpha); }
    inline static Color IndianRed(double alpha = 1.0) { return Color(0.80, 0.36, 0.36, alpha); }
    inline static Color Indigo(double alpha = 1.0) { return Color(0.29, 0.0, 0.51, alpha); }
    inline static Color Ivory(double alpha = 1.0) { return Color(1.0, 1.0, 0.94, alpha); }
    inline static Color Khaki(double alpha = 1.0) { return Color(0.94, 0.90, 0.55, alpha); }
    inline static Color Lavender(double alpha = 1.0) { return Color(0.90, 0.90, 0.98, alpha); }
    inline static Color LavenderBlush(double alpha = 1.0) { return Color(1.0, 0.94, 0.96, alpha); }
    inline static Color LawnGreen(double alpha = 1.0) { return Color(0.49, 0.99, 0.0, alpha); }
    inline static Color LemonChiffon(double alpha = 1.0) { return Color(1.0, 0.98, 0.80, alpha); }
    inline static Color LightBlue(double alpha = 1.0) { return Color(0.68, 0.85, 0.90, alpha); }
    inline static Color LightCoral(double alpha = 1.0) { return Color(0.94, 0.50, 0.50, alpha); }
    inline static Color LightCyan(double alpha = 1.0) { return Color(0.88, 1.0, 1.0, alpha); }
    inline static Color LightGoldenrod(double alpha = 1.0) { return Color(0.98, 0.98, 0.82, alpha); }
    inline static Color LightGray(double alpha = 1.0) { return Color(0.83, 0.83, 0.83, alpha); }
    inline static Color LightGreen(double alpha = 1.0) { return Color(0.56, 0.93, 0.56, alpha); }
    inline static Color LightPink(double alpha = 1.0) { return Color(1.0, 0.71, 0.76, alpha); }
    inline static Color LightSalmon(double alpha = 1.0) { return Color(1.0, 0.63, 0.48, alpha); }
    inline static Color LightSeaGreen(double alpha = 1.0) { return Color(0.13, 0.70, 0.67, alpha); }
    inline static Color LightSkyBlue(double alpha = 1.0) { return Color(0.53, 0.81, 0.98, alpha); }
    inline static Color LightSlateGray(double alpha = 1.0) { return Color(0.47, 0.53, 0.60, alpha); }
    inline static Color LightSteelBlue(double alpha = 1.0) { return Color(0.69, 0.77, 0.87, alpha); }
    inline static Color LightYellow(double alpha = 1.0) { return Color(1.0, 1.0, 0.88, alpha); }
    inline static Color Lime(double alpha = 1.0) { return Color(0.0, 1.0, 0.0, alpha); }
    inline static Color LimeGreen(double alpha = 1.0) { return Color(0.20, 0.80, 0.20, alpha); }
    inline static Color Linen(double alpha = 1.0) { return Color(0.98, 0.94, 0.90, alpha); }
    inline static Color Magenta(double alpha = 1.0) { return Color(1.0, 0.0, 1.0, alpha); }
    inline static Color Maroon(double alpha = 1.0) { return Color(0.69, 0.19, 0.38, alpha); }
    inline static Color MediumAquamarine(double alpha = 1.0) { return Color(0.40, 0.80, 0.67, alpha); }
    inline static Color MediumBlue(double alpha = 1.0) { return Color(0.0, 0.0, 0.80, alpha); }
    inline static Color MediumOrchid(double alpha = 1.0) { return Color(0.73, 0.33, 0.83, alpha); }
    inline static Color MediumPurple(double alpha = 1.0) { return Color(0.58, 0.44, 0.86, alpha); }
    inline static Color MediumSeaGreen(double alpha = 1.0) { return Color(0.24, 0.70, 0.44, alpha); }
    inline static Color MediumSlateBlue(double alpha = 1.0) { return Color(0.48, 0.41, 0.93, alpha); }
    inline static Color MediumSpringGreen(double alpha = 1.0) { return Color(0.0, 0.98, 0.60, alpha); }
    inline static Color MediumTurquoise(double alpha = 1.0) { return Color(0.28, 0.82, 0.80, alpha); }
    inline static Color MediumVioletRed(double alpha = 1.0) { return Color(0.78, 0.08, 0.52, alpha); }
    inline static Color MidnightBlue(double alpha = 1.0) { return Color(0.10, 0.10, 0.44, alpha); }
    inline static Color MintCream(double alpha = 1.0) { return Color(0.96, 1.0, 0.98, alpha); }
    inline static Color MistyRose(double alpha = 1.0) { return Color(1.0, 0.89, 0.88, alpha); }
    inline static Color Mocassin(double alpha = 1.0) { return Color(1.0, 0.89, 0.71, alpha); }
    inline static Color NavajoWhite(double alpha = 1.0) { return Color(1.0, 0.87, 0.68, alpha); }
    inline static Color NavyBlue(double alpha = 1.0) { return Color(0.0, 0.0, 0.50, alpha); }
    inline static Color OldLace(double alpha = 1.0) { return Color(0.99, 0.96, 0.90, alpha); }
    inline static Color Olive(double alpha = 1.0) { return Color(0.50, 0.50, 0.0, alpha); }
    inline static Color OliveDrab(double alpha = 1.0) { return Color(0.42, 0.56, 0.14, alpha); }
    inline static Color Orange(double alpha = 1.0) { return Color(1.0, 0.65, 0.0, alpha); }
    inline static Color OrangeRed(double alpha = 1.0) { return Color(1.0, 0.27, 0.0, alpha); }
    inline static Color Orchid(double alpha = 1.0) { return Color(0.85, 0.44, 0.84, alpha); }
    inline static Color PaleGoldenrod(double alpha = 1.0) { return Color(0.93, 0.91, 0.67, alpha); }
    inline static Color PaleGreen(double alpha = 1.0) { return Color(0.60, 0.98, 0.60, alpha); }
    inline static Color PaleTurquoise(double alpha = 1.0) { return Color(0.69, 0.93, 0.93, alpha); }
    inline static Color PaleVioletRed(double alpha = 1.0) { return Color(0.86, 0.44, 0.58, alpha); }
    inline static Color PapayeWhip(double alpha = 1.0) { return Color(1.0, 0.94, 0.84, alpha); }
    inline static Color PeachPuff(double alpha = 1.0) { return Color(1.0, 0.85, 0.73, alpha); }
    inline static Color Peru(double alpha = 1.0) { return Color(0.80, 0.52, 0.25, alpha); }
    inline static Color Pink(double alpha = 1.0) { return Color(1.0, 0.75, 0.80, alpha); }
    inline static Color Plum(double alpha = 1.0) { return Color(0.87, 0.63, 0.87, alpha); }
    inline static Color PowderBlue(double alpha = 1.0) { return Color(0.69, 0.88, 0.90, alpha); }
    inline static Color Purple(double alpha = 1.0) { return Color(0.63, 0.13, 0.94, alpha); }
    inline static Color RebeccaPurple(double alpha = 1.0) { return Color(0.40, 0.20, 0.60, alpha); }
    inline static Color Red(double alpha = 1.0) { return Color(1.0, 0.0, 0.0, alpha); }
    inline static Color RosyBrown(double alpha = 1.0) { return Color(0.74, 0.56, 0.56, alpha); }
    inline static Color RoyalBlue(double alpha = 1.0) { return Color(0.25, 0.41, 0.88, alpha); }
    inline static Color SaddleBrown(double alpha = 1.0) { return Color(0.55, 0.27, 0.07, alpha); }
    inline static Color Salmon(double alpha = 1.0) { return Color(0.98, 0.50, 0.45, alpha); }
    inline static Color SandyBrown(double alpha = 1.0) { return Color(0.96, 0.64, 0.38, alpha); }
    inline static Color SeaGreen(double alpha = 1.0) { return Color(0.18, 0.55, 0.34, alpha); }
    inline static Color Seashell(double alpha = 1.0) { return Color(1.0, 0.96, 0.93, alpha); }
    inline static Color Sienna(double alpha = 1.0) { return Color(0.63, 0.32, 0.18, alpha); }
    inline static Color Silver(double alpha = 1.0) { return Color(0.75, 0.75, 0.75, alpha); }
    inline static Color SkyBlue(double alpha = 1.0) { return Color(0.53, 0.81, 0.92, alpha); }
    inline static Color SlateBlue(double alpha = 1.0) { return Color(0.42, 0.35, 0.80, alpha); }
    inline static Color SlateGray(double alpha = 1.0) { return Color(0.44, 0.50, 0.56, alpha); }
    inline static Color Snow(double alpha = 1.0) { return Color(1.0, 0.98, 0.98, alpha); }
    inline static Color SpringGreen(double alpha = 1.0) { return Color(0.0, 1.0, 0.50, alpha); }
    inline static Color SteelBlue(double alpha = 1.0) { return Color(0.27, 0.51, 0.71, alpha); }
    inline static Color Tan(double alpha = 1.0) { return Color(0.82, 0.71, 0.55, alpha); }
    inline static Color Teal(double alpha = 1.0) { return Color(0.0, 0.50, 0.50, alpha); }
    inline static Color Thistle(double alpha = 1.0) { return Color(0.85, 0.75, 0.85, alpha); }
    inline static Color Tomato(double alpha = 1.0) { return Color(1.0, 0.39, 0.28, alpha); }
    inline static Color Turquoise(double alpha = 1.0) { return Color(0.25, 0.88, 0.82, alpha); }
    inline static Color Violet(double alpha = 1.0) { return Color(0.93, 0.51, 0.93, alpha); }
    inline static Color WebGray(double alpha = 1.0) { return Color(0.50, 0.50, 0.50, alpha); }
    inline static Color WebGreen(double alpha = 1.0) { return Color(0.0, 0.5, 0.0, alpha); }
    inline static Color WebMaroon(double alpha = 1.0) { return Color(0.5, 0.0, 0.0, alpha); }
    inline static Color WebPurple(double alpha = 1.0) { return Color(0.50, 0.0, 0.50, alpha); }
    inline static Color Wheat(double alpha = 1.0) { return Color(0.96, 0.87, 0.70, alpha); }
    inline static Color White(double alpha = 1.0) { return Color(1.0, 1.0, 1.0, alpha); }
    inline static Color WhiteSmoke(double alpha = 1.0) { return Color(0.96, 0.96, 0.96, alpha); }
    inline static Color Yellow(double alpha = 1.0) { return Color(1.0, 1.0, 0.0, alpha); }
    inline static Color YellowGreen(double alpha = 1.0) { return Color(0.60, 0.80, 0.20, alpha); }
};

#endif // COLOR_H
