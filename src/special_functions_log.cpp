#include "special_functions_log.h"
#include <gsl/gsl_sf.h>
#include <gsl/gsl_sf_exp.h>
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
Result GSL::log(const double& x)
{
    gsl_sf_result res{0., 0.};
    int stat = gsl_sf_log_e(x, &res);
    if(stat){
        print_error_message("logarithm", stat);
    }
    return Result(res);
}
Result GSL::log_abs(const double& x)
{
    gsl_sf_result res{0., 0.};
    int stat = gsl_sf_log_abs_e(x, &res);
    if(stat){
        print_error_message("logarithm of absolute value of x", stat);
    }
    return Result(res);
}

Result GSL::log_1plusx(const double& x)
{
    gsl_sf_result res{0., 0.};
    int stat = gsl_sf_log_1plusx_e(x, &res);
    if(stat){
        print_error_message("logarithm of 1 plus x", stat);
    }
    return Result(res);
}

Result GSL::log_1plusx_mx(const double& x)
{
    gsl_sf_result res{0., 0.};
    int stat = gsl_sf_log_1plusx_mx_e(x, &res);
    if(stat){
        print_error_message("logarithm 1 plus x minus x", stat);
    }
    return Result(res);
}
