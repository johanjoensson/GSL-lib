#include "special_functions_erf.h"
#include <gsl/gsl_sf_erf.h>
#include <string>
#include <stdexcept>
#include <gsl/gsl_errno.h>

namespace{
void print_error_message(std::string function_name, int& gsl_err_code)
{
    throw std::runtime_error("Error in " + function_name + "\nGSL error"
    " message: " + gsl_strerror(gsl_err_code));
}
}

using namespace GSL;

Result GSL::erf(const double& x)
{
    gsl_sf_result res{0., 0.};
    int stat = gsl_sf_erf_e(x, &res);
    if(stat){
        print_error_message("error function", stat);
    }
    return Result(res);
}

Result GSL::erfc(const double& x)
{
    gsl_sf_result res{0., 0.};
    int stat = gsl_sf_erfc_e(x, &res);
    if(stat){
        print_error_message("complementary error function", stat);
    }
    return Result(res);
}

Result GSL::log_erfc(const double& x)
{
    gsl_sf_result res{0., 0.};
    int stat = gsl_sf_log_erfc_e(x, &res);
    if(stat){
        print_error_message("logarithm of complementary error function", stat);
    }
    return Result(res);
}


Result GSL::erf_Z(const double& x)
{
    gsl_sf_result res{0., 0.};
    int stat = gsl_sf_erf_Z_e(x, &res);
    if(stat){
        print_error_message("Gaussian probability density Z", stat);
    }
    return Result(res);
}

Result GSL::erf_Q(const double& x)
{
    gsl_sf_result res{0., 0.};
    int stat = gsl_sf_erf_Q_e(x, &res);
    if(stat){
        print_error_message("upper tail of Gaussian probability density Q", stat);
    }
    return Result(res);
}

Result GSL::hazard(const double& x)
{
    gsl_sf_result res{0., 0.};
    int stat = gsl_sf_hazard_e(x, &res);
    if(stat){
        print_error_message("Hazard function for normal distribution Z/Q", stat);
    }
    return Result(res);
}
