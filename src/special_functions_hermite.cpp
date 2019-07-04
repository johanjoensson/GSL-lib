#include "special_functions_hermite.h"
#include <gsl/gsl_sf_hermite.h>

using namespace GSL;

Result GSL::hermite_prob(const int n, const double x)
{
    gsl_sf_result res;
    gsl_sf_hermite_prob_e(n, x, &res);
    return Result(res);
}

Result GSL::hermite_prob_series(const int n, const double x, const std::vector<double>& a)
{
    gsl_sf_result res;
    gsl_sf_hermite_prob_series_e(n, x, &*a.cbegin(), &res);
    return Result(res);
}

Result GSL::hermite_phys(const int n, const double x)
{
    gsl_sf_result res;
    gsl_sf_hermite_phys_e(n, x, &res);
    return Result(res);
}

Result GSL::hermite_phys_series(const int n, const double x, const std::vector<double>& a)
{
    gsl_sf_result res;
    gsl_sf_hermite_phys_series_e(n, x, &*a.cbegin(), &res);
    return Result(res);
}
