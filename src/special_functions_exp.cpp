#include "special_functions_exp.h"
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

Result GSL::exp(const double& x)
{
    gsl_sf_result res{0., 0.};
    int stat = gsl_sf_exp_e(x, &res);
    if(stat == GSL_EUNDRFLW){
        res.val = 0.;
        res.err = 0.;
    }else if(stat){
        print_error_message("exponential", stat);
    }
    return Result(res);
}

Result GSL::exp_mult(const double& x, const double& y)
{
    gsl_sf_result res{0., 0.};
    int stat = gsl_sf_exp_mult_e(x, y, &res);
    if(stat == GSL_EUNDRFLW){
        res.val = 0.;
        res.err = 0.;
    }else if(stat){
        print_error_message("exponential and mult", stat);
    }
    return Result(res);
}
