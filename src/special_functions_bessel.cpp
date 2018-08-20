#include "special_functions_bessel.h"
#include <gsl/gsl_sf.h>
#include <gsl/gsl_sf_bessel.h>
#include <string>
#include <stdexcept>
#include <gsl/gsl_errno.h>

namespace{
void print_error_message(std::string function_name, const int& gsl_err_code)
{
    throw std::runtime_error("Error in " + function_name + "\nGSL error"
    " message: " + gsl_strerror(gsl_err_code));
}
}

using namespace GSL;

Result GSL::bessel_J0(const double& x)
{
    gsl_sf_result res{0., 0.};
    int stat = gsl_sf_bessel_J0_e(x, &res);
    if(stat){
        print_error_message("Bessel J0", stat);
    }
    return Result(res);
}

Result GSL::bessel_J1(const double& x)
{
    gsl_sf_result res{0., 0.};
    int stat = gsl_sf_bessel_J1_e(x, &res);
    if(stat){
        print_error_message("Bessel J1", stat);
    }
    return Result(res);
}

Result GSL::bessel_Jn(const int& n, const double& x)
{
    gsl_sf_result res{0., 0.};
    int stat = gsl_sf_bessel_Jn_e(n, x, &res);
    if(stat){
        print_error_message("Bessel Jn", stat);
    }
    return Result(res);
}

Result GSL::bessel_Y0(const double& x)
{
    gsl_sf_result res{0., 0.};
    int stat = gsl_sf_bessel_Y0_e(x, &res);
    if(stat){
        print_error_message("Bessel Y0", stat);
    }
    return Result(res);
}

Result GSL::bessel_Y1(const double& x)
{
    gsl_sf_result res{0., 0.};
    int stat = gsl_sf_bessel_Y1_e(x, &res);
    if(stat){
        print_error_message("Bessel Y1", stat);
    }
    return Result(res);
}

Result GSL::bessel_Yn(const int& n, const double& x)
{
    gsl_sf_result res{0., 0.};
    int stat = gsl_sf_bessel_Yn_e(n, x, &res);
    if(stat){
        print_error_message("Bessel Yn", stat);
    }
    return Result(res);
}

Result GSL::bessel_I0(const double& x)
{
    gsl_sf_result res{0., 0.};
    int stat = gsl_sf_bessel_I0_e(x, &res);
    if(stat){
        print_error_message("Bessel I0", stat);
    }
    return Result(res);
}

Result GSL::bessel_I1(const double& x)
{
    gsl_sf_result res{0., 0.};
    int stat = gsl_sf_bessel_I1_e(x, &res);
    if(stat){
        print_error_message("Bessel I1", stat);
    }
    return Result(res);
}

Result GSL::bessel_In(const int& n, const double& x)
{
    gsl_sf_result res{0., 0.};
    int stat = gsl_sf_bessel_In_e(n, x, &res);
    if(stat){
        print_error_message("Bessel In", stat);
    }
    return Result(res);
}

Result GSL::bessel_I0_scaled(const double& x)
{
    gsl_sf_result res{0., 0.};
    int stat = gsl_sf_bessel_I0_scaled_e(x, &res);
    if(stat){
        print_error_message("Scaled Bessel I0", stat);
    }
    return Result(res);
}

Result GSL::bessel_I1_scaled(const double& x)
{
    gsl_sf_result res{0., 0.};
    int stat = gsl_sf_bessel_I1_scaled_e(x, &res);
    if(stat){
        print_error_message("Bessel I1", stat);
    }
    return Result(res);
}

Result GSL::bessel_In_scaled(const int& n, const double& x)
{
    gsl_sf_result res{0., 0.};
    int stat = gsl_sf_bessel_In_scaled_e(n, x, &res);
    if(stat){
        print_error_message("Bessel In", stat);
    }
    return Result(res);
}

Result GSL::bessel_K0(const double& x)
{
    gsl_sf_result res{0., 0.};
    int stat = gsl_sf_bessel_K0_e(x, &res);
    if(stat){
        print_error_message("Bessel K0", stat);
    }
    return Result(res);
}

Result GSL::bessel_K1(const double& x)
{
    gsl_sf_result res{0., 0.};
    int stat = gsl_sf_bessel_K1_e(x, &res);
    if(stat){
        print_error_message("Bessel K1", stat);
    }
    return Result(res);
}

Result GSL::bessel_Kn(const int& n, const double& x)
{
    gsl_sf_result res{0., 0.};
    int stat = gsl_sf_bessel_Kn_e(n, x, &res);
    if(stat){
        print_error_message("Bessel Kn", stat);
    }
    return Result(res);
}

Result GSL::bessel_K0_scaled(const double& x)
{
    gsl_sf_result res{0., 0.};
    int stat = gsl_sf_bessel_K0_scaled_e(x, &res);
    if(stat){
        print_error_message("Scaled Bessel K0", stat);
    }
    return Result(res);
}

Result GSL::bessel_K1_scaled(const double& x)
{
    gsl_sf_result res{0., 0.};
    int stat = gsl_sf_bessel_K1_scaled_e(x, &res);
    if(stat){
        print_error_message("Scaled Bessel K1", stat);
    }
    return Result(res);
}

Result GSL::bessel_Kn_scaled(const int& n, const double& x)
{
    gsl_sf_result res{0., 0.};
    int stat = gsl_sf_bessel_Kn_scaled_e(n, x, &res);
    if(stat){
        print_error_message("Scaled Bessel Kn", stat);
    }
    return Result(res);
}

Result GSL::bessel_j0(const double& x)
{
    gsl_sf_result res{0., 0.};
    int stat = gsl_sf_bessel_j0_e(x, &res);
    if(stat){
        print_error_message("Bessel j0", stat);
    }
    return Result(res);
}

Result GSL::bessel_j1(const double& x)
{
    gsl_sf_result res{0., 0.};
    int stat = gsl_sf_bessel_j1_e(x, &res);
    if(stat){
        print_error_message("Bessel j1", stat);
    }
    return Result(res);
}

Result GSL::bessel_jn(const int& n, const double& x)
{
    gsl_sf_result res{0., 0.};
    int stat = gsl_sf_bessel_jl_e(n, x, &res);
    if(stat){
        print_error_message("Bessel jn", stat);
    }
    return Result(res);
}

Result GSL::bessel_y0(const double& x)
{
    gsl_sf_result res{0., 0.};
    int stat = gsl_sf_bessel_y0_e(x, &res);
    if(stat){
        print_error_message("Bessel y0", stat);
    }
    return Result(res);
}

Result GSL::bessel_y1(const double& x)
{
    gsl_sf_result res{0., 0.};
    int stat = gsl_sf_bessel_y1_e(x, &res);
    if(stat){
        print_error_message("Bessel y1", stat);
    }
    return Result(res);
}

Result GSL::bessel_yn(const int& n, const double& x)
{
    gsl_sf_result res{0., 0.};
    int stat = gsl_sf_bessel_yl_e(n, x, &res);
    if(stat){
        print_error_message("Bessel yn", stat);
    }
    return Result(res);
}

Result GSL::bessel_i0_scaled(const double& x)
{
    gsl_sf_result res{0., 0.};
    int stat = gsl_sf_bessel_i0_scaled_e(x, &res);
    if(stat){
        print_error_message("Scaled Bessel i0", stat);
    }
    return Result(res);
}

Result GSL::bessel_i1_scaled(const double& x)
{
    gsl_sf_result res{0., 0.};
    int stat = gsl_sf_bessel_i1_scaled_e(x, &res);
    if(stat){
        print_error_message("Bessel i1", stat);
    }
    return Result(res);
}

Result GSL::bessel_in_scaled(const int& n, const double& x)
{
    gsl_sf_result res{0., 0.};
    int stat = gsl_sf_bessel_il_scaled_e(n, x, &res);
    if(stat){
        print_error_message("Bessel in", stat);
    }
    return Result(res);
}

Result GSL::bessel_k0_scaled(const double& x)
{
    gsl_sf_result res{0., 0.};
    int stat = gsl_sf_bessel_k0_scaled_e(x, &res);
    if(stat){
        print_error_message("Scaled Bessel k0", stat);
    }
    return Result(res);
}

Result GSL::bessel_k1_scaled(const double& x)
{
    gsl_sf_result res{0., 0.};
    int stat = gsl_sf_bessel_k1_scaled_e(x, &res);
    if(stat){
        print_error_message("Scaled Bessel k1", stat);
    }
    return Result(res);
}

Result GSL::bessel_kn_scaled(const int& n, const double& x)
{
    gsl_sf_result res{0., 0.};
    int stat = gsl_sf_bessel_kl_scaled_e(n, x, &res);
    if(stat){
        print_error_message("Scaled Bessel kn", stat);
    }
    return Result(res);
}

Result GSL::bessel_Jnu(const double& nu , const double& x)
{
    gsl_sf_result res{0., 0.};
    int stat = gsl_sf_bessel_Jnu_e(nu, x, &res);
    if(stat){
        print_error_message("Bessel Jnu", stat);
    }
    return Result(res);
}
Result GSL::bessel_Ynu(const double& nu, const double& x)
{
    gsl_sf_result res{0., 0.};
    int stat = gsl_sf_bessel_Ynu_e(nu, x, &res);
    if(stat){
        print_error_message("Bessel Ynu", stat);
    }
    return Result(res);
}

Result GSL::bessel_Inu(const double& nu, const double& x)
{
    gsl_sf_result res{0., 0.};
    int stat = gsl_sf_bessel_Inu_e(nu, x, &res);
    if(stat){
        print_error_message("Bessel Inu", stat);
    }
    return Result(res);
}

Result GSL::bessel_Knu(const double& nu, const double& x)
{
    gsl_sf_result res{0., 0.};
    int stat = gsl_sf_bessel_Knu_e(nu, x, &res);
    if(stat){
        print_error_message("Bessel Knu", stat);
    }
    return Result(res);
}


Result GSL::bessel_J0_zeros(unsigned const int& n)
{
    gsl_sf_result res{0., 0.};
    int stat = gsl_sf_bessel_zero_J0_e(n, &res);
    if(stat){
        print_error_message("Bessel zeros J0", stat);
    }
    return Result(res);
}
Result GSL::bessel_J1_zeros(unsigned const int& n)
{
    gsl_sf_result res{0., 0.};
    int stat = gsl_sf_bessel_zero_J1_e(n, &res);
    if(stat){
        print_error_message("Bessel zeros J1", stat);
    }
    return Result(res);
}

Result GSL::bessel_Jnu_zeros(const double& nu, unsigned const int& n)
{
    gsl_sf_result res{0., 0.};
    int stat = gsl_sf_bessel_zero_Jnu_e(nu, n, &res);
    if(stat){
        print_error_message("Bessel zeros Jnu", stat);
    }
    return Result(res);
}
