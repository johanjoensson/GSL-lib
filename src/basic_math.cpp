#include "basic_math.h"
#include <gsl/gsl_math.h>

using namespace GSL;

double GSL::pow_int(const double& x, const int& n)
{
    return gsl_pow_int(x, n);
}
double GSL::pow_uint(const double& x, const unsigned int& n)
{
    return gsl_pow_uint(x, n);
}

double GSL::pow_2(const double& x)
{
    return gsl_pow_2(x);
}
double GSL::pow_3(const double& x)
{
    return gsl_pow_3(x);
}
double GSL::pow_4(const double& x)
{
    return gsl_pow_4(x);
}

double GSL::pow_5(const double& x)
{
    return gsl_pow_5(x);
}

double GSL::pow_6(const double& x)
{
    return gsl_pow_6(x);
}

double GSL::pow_7(const double& x)
{
    return gsl_pow_7(x);
}

double GSL::pow_8(const double& x)
{
    return gsl_pow_8(x);
}

double GSL::pow_9(const double& x)
{
    return gsl_pow_9(x);
}
double GSL::log1p(const double& x)
{
    return gsl_log1p(x);
}
double GSL::expm1(const double& x)
{
    return gsl_expm1(x);
}

double GSL::hypot(const double& x, const double& y)
{
    return gsl_hypot(x, y);
}

double GSL::hypot3(const double& x, const double& y, const double& z)
{
    return gsl_hypot3(x, y, z);
}


double GSL::acosh(const double& x)
{
    return gsl_acosh(x);
}

double GSL::asinh(const double& x)
{
    return gsl_asinh(x);
}

double GSL::atanh(const double& x)
{
    return gsl_atanh(x);
}


double GSL::ldexp(const double& x, const int& e)
{
    return gsl_ldexp(x, e);
}

double GSL::frexp(const double& x, const int& e)
{
    int tmp = e;
    double res = gsl_frexp(x, &tmp);
    return res;
}
