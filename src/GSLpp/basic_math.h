#ifndef BASIC_MATH_H
#define BASIC_MATH_H
#include <gsl/gsl_math.h>

namespace GSL{

double pow_int(const double& x, const int& n);
double pow_uint(const double& x, const unsigned int& n);

double pow_2(const double& x);
double pow_3(const double& x);
double pow_4(const double& x);
double pow_5(const double& x);
double pow_6(const double& x);
double pow_7(const double& x);
double pow_8(const double& x);
double pow_9(const double& x);

double log1p(const double& x);
double expm1(const double& x);
double hypot(const double& x, const double& y);
double hypot3(const double& x, const double& y, const double& z);

double acosh(const double& x);
double asinh(const double& x);
double atanh(const double& x);

double ldexp(const double& x, const int& e);
double frexp(const double& x, const int& e);
}

#endif // BASIC_MATH_H
