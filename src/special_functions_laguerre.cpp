#include "special_functions_laguerre.h"
#include <gsl/gsl_sf_laguerre.h>

using namespace GSL;

Result GSL::laguerre_1(double a, double x)
{
    gsl_sf_result res;
    gsl_sf_laguerre_1_e(a, x, &res);
    return Result(res);
}

Result GSL::laguerre_2(double a, double x)
{
    gsl_sf_result res;
    gsl_sf_laguerre_2_e(a, x, &res);
    return Result(res);
}

Result GSL::laguerre_3(double a, double x)
{
    gsl_sf_result res;
    gsl_sf_laguerre_3_e(a, x, &res);
    return Result(res);
}

Result GSL::laguerre_n(int n, double a, double x)
{
    gsl_sf_result res;
    gsl_sf_laguerre_n_e(n, a, x, &res);
    return Result(res);
}
