#include "GSLpp/special_functions_legendre.h"
#include <gsl/gsl_sf.h>
#include <gsl/gsl_sf_legendre.h>
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

Result GSL::legendre_P1(const double& x)
{
    gsl_sf_result res{0., 0.};
    int stat = gsl_sf_legendre_P1_e(x, &res);
    if(stat){
        print_error_message("Legendre P1", stat);
    }
    return Result(res);
}

Result GSL::legendre_P2(const double& x)
{
    gsl_sf_result res{0., 0.};
    int stat = gsl_sf_legendre_P2_e(x, &res);
    if(stat){
        print_error_message("Legendre P2", stat);
    }
    return Result(res);
}

Result GSL::legendre_P3(const double& x)
{
    gsl_sf_result res{0., 0.};
    int stat = gsl_sf_legendre_P3_e(x, &res);
    if(stat){
        print_error_message("Legendre P3", stat);
    }
    return Result(res);
}

Result GSL::legendre_Pl(const int& l, const double& x)
{
    gsl_sf_result res{0., 0.};
    int stat = gsl_sf_legendre_Pl_e(l, x, &res);
    if(stat){
        print_error_message("Legendre Pl", stat);
    }
    return Result(res);
}


Result GSL::legendre_Q0(const double& x)
{
    gsl_sf_result res{0., 0.};
    int stat = gsl_sf_legendre_Q0_e(x, &res);
    if(stat){
        print_error_message("Legendre Q0", stat);
    }
    return Result(res);
}

Result GSL::legendre_Q1(const double& x)
{
    gsl_sf_result res{0., 0.};
    int stat = gsl_sf_legendre_Q1_e(x, &res);
    if(stat){
        print_error_message("Legendre Q1", stat);
    }
    return Result(res);
}

Result GSL::legendre_Ql(const int& l, const double& x)
{
    gsl_sf_result res{0., 0.};
    int stat = gsl_sf_legendre_Ql_e(l, x, &res);
    if(stat){
        print_error_message("Legendre Ql", stat);
    }
    return Result(res);
}

Result GSL::legendre_Plm(const int l, const int m, const double& x)
{
    gsl_sf_result res{0., 0.};
    int stat = gsl_sf_legendre_Plm_e(l, m, x, &res);
    if(stat){
        print_error_message("Associated Legendre Plm", stat);
    }
    return Result(res);
}

Result GSL::legendre_sphPlm(const int l, const int m, const double& x)
{
    gsl_sf_result res{0., 0.};
    int stat = gsl_sf_legendre_sphPlm_e(l, m, x, &res);
    if(stat){
        print_error_message("Normalized associated (spherical harmonics) Legendre Plm", stat);
    }
    return Result(res);
}
