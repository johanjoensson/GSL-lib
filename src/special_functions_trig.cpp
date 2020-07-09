#include "GSLpp/special_functions_trig.h"
#include <gsl/gsl_sf_trig.h>
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

Result GSL::sin(const double& x)
{
    gsl_sf_result res{0., 0.};
    int stat = gsl_sf_sin_e(x, &res);
    if(stat){
        print_error_message("sin", stat);
    }
    return Result(res);
}
Result GSL::cos(const double& x)
{
    gsl_sf_result res{0., 0.};
    int stat = gsl_sf_cos_e(x, &res);
    if(stat){
        print_error_message("cos", stat);
    }
    return Result(res);
}

Result GSL::hypotenuse(const double& x, const double& y)
{
    gsl_sf_result res{0., 0.};
    int stat = gsl_sf_hypot_e(x, y, &res);
    if(stat){
        print_error_message("hypotenuse", stat);
    }
    return Result(res);
}

Result GSL::sinc(const double& x)
{
    gsl_sf_result res{0., 0.};
    int stat = gsl_sf_sinc_e(x, &res);
    if(stat){
        print_error_message("sinc", stat);
    }
    return Result(res);
}
Result GSL::lnsinh(const double& x)
{
    gsl_sf_result res{0., 0.};
    int stat = gsl_sf_lnsinh_e(x, &res);
    if(stat){
        print_error_message("lnsinh", stat);
    }
    return Result(res);
}
Result GSL::lncosh(const double& x)
{
    gsl_sf_result res{0., 0.};
    int stat = gsl_sf_lncosh_e(x, &res);
    if(stat){
        print_error_message("lncosh", stat);
    }
    return Result(res);
}
