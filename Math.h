#ifndef MATH_H
#define MATH_H
#include <math.h>
#include "Defs.h"

class Math
{
public:
    static inline double Asin(double x) { return asin(x); }
    static inline double Acos(double x) { return acos(x); }
    static inline double Atan(double x) { return atan(x); }
    static inline double Acot(double x) { return atan(1 / x); }

    static inline double Sin(double x) { return sin(x); }
    static inline double Cos(double x) { return cos(x); }
    static inline double Tan(double x) { return tan(x); }
    static inline double Cot(double x) { return 1 / tan(x); }

    static inline double Sinh(double x) { return sinh(x); }
    static inline double Cosh(double x) { return cosh(x); }
    static inline double Tanh(double x) { return tanh(x); }
    static inline double Coth(double x) { return 1 / tanh(x); }

    static inline double Exp(double x) { return exp(x); }
    static inline double Log(double x) { return log(x); }
    static inline double Log10(double x) { return log10(x); }

    static inline double Ceil(double x) { return ceil(x); }
    static inline double Floor(double x) { return floor(x); }
    static inline double Abs(double x) { return fabs(x); }
    static int Signum(double x) { return (x > 0) - (x < 0); }
    static double Round(double x) { return (int)(x + (int)((x - (int)x) >= 0.5)); }

    static inline double Sqrt(double x) { return sqrt(x); }
    static inline double Pow(double x, double y) { return pow(x, y); }

    static inline double PI() { return 3.14159265358979323846; }
    static inline double E() { return 2.7182818284590452354; }
    static inline double Log2() { return 0.69314718055994530942; }
    static inline double Log10() { return 2.30258509299404568402; }
};

#endif // MATH_H
