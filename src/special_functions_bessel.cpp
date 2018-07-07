#include "special_functions_bessel.h"
#include <string>
#include <stdexcept>
#include <gsl/gsl_errno.h>
#include <gsl/gsl_sf_result.h>

using namespace GSL;

void print_error_message(std::string function_name, int& gsl_err_code)
{
    throw std::runtime_error("Error in " + function_name + "\nGSL error"
    " message: " + gsl_strerror(gsl_err_code));
}

std::tuple<double, double> GSL::bessel_J0(double& x)
{
    gsl_sf_result res;
    int stat = gsl_sf_bessel_J0_e(x, &res);
    if(stat){
        print_error_message("Bessel J0", stat);
    }
    return std::make_tuple(res.val, res.err);
}

std::tuple<double, double> GSL::bessel_J1(double& x)
{
    gsl_sf_result res;
    int stat = gsl_sf_bessel_J1_e(x, &res);
    if(stat){
        print_error_message("Bessel J1", stat);
    }
    return std::make_tuple(res.val, res.err);
}

std::tuple<double, double> GSL::bessel_Jn(int& n, double& x)
{
    gsl_sf_result res;
    int stat = gsl_sf_bessel_Jn_e(n, x, &res);
    if(stat){
        print_error_message("Bessel Jn", stat);
    }
    return std::make_tuple(res.val, res.err);
}

std::tuple<double, double> GSL::bessel_Y0(double& x)
{
    gsl_sf_result res;
    int stat = gsl_sf_bessel_Y0_e(x, &res);
    if(stat){
        print_error_message("Bessel Y0", stat);
    }
    return std::make_tuple(res.val, res.err);
}

std::tuple<double, double> GSL::bessel_Y1(double& x)
{
    gsl_sf_result res;
    int stat = gsl_sf_bessel_Y1_e(x, &res);
    if(stat){
        print_error_message("Bessel Y1", stat);
    }
    return std::make_tuple(res.val, res.err);
}

std::tuple<double, double> GSL::bessel_Yn(int& n, double& x)
{
    gsl_sf_result res;
    int stat = gsl_sf_bessel_Yn_e(n, x, &res);
    if(stat){
        print_error_message("Bessel Yn", stat);
    }
    return std::make_tuple(res.val, res.err);
}

std::tuple<double, double> GSL::bessel_I0(double& x)
{
    gsl_sf_result res;
    int stat = gsl_sf_bessel_I0_e(x, &res);
    if(stat){
        print_error_message("Bessel I0", stat);
    }
    return std::make_tuple(res.val, res.err);
}

std::tuple<double, double> GSL::bessel_I1(double& x)
{
    gsl_sf_result res;
    int stat = gsl_sf_bessel_I1_e(x, &res);
    if(stat){
        print_error_message("Bessel I1", stat);
    }
    return std::make_tuple(res.val, res.err);
}

std::tuple<double, double> GSL::bessel_In(int& n, double& x)
{
    gsl_sf_result res;
    int stat = gsl_sf_bessel_In_e(n, x, &res);
    if(stat){
        print_error_message("Bessel In", stat);
    }
    return std::make_tuple(res.val, res.err);
}

std::tuple<double, double> GSL::bessel_I0_scaled(double& x)
{
    gsl_sf_result res;
    int stat = gsl_sf_bessel_I0_scaled_e(x, &res);
    if(stat){
        print_error_message("Scaled Bessel I0", stat);
    }
    return std::make_tuple(res.val, res.err);
}

std::tuple<double, double> GSL::bessel_I1_scaled(double& x)
{
    gsl_sf_result res;
    int stat = gsl_sf_bessel_I1_scaled_e(x, &res);
    if(stat){
        print_error_message("Bessel I1", stat);
    }
    return std::make_tuple(res.val, res.err);
}

std::tuple<double, double> GSL::bessel_In_scaled(int& n, double& x)
{
    gsl_sf_result res;
    int stat = gsl_sf_bessel_In_scaled_e(n, x, &res);
    if(stat){
        print_error_message("Bessel In", stat);
    }
    return std::make_tuple(res.val, res.err);
}

std::tuple<double, double> GSL::bessel_K0(double& x)
{
    gsl_sf_result res;
    int stat = gsl_sf_bessel_K0_e(x, &res);
    if(stat){
        print_error_message("Bessel K0", stat);
    }
    return std::make_tuple(res.val, res.err);
}

std::tuple<double, double> GSL::bessel_K1(double& x)
{
    gsl_sf_result res;
    int stat = gsl_sf_bessel_K1_e(x, &res);
    if(stat){
        print_error_message("Bessel K1", stat);
    }
    return std::make_tuple(res.val, res.err);
}

std::tuple<double, double> GSL::bessel_Kn(int& n, double& x)
{
    gsl_sf_result res;
    int stat = gsl_sf_bessel_Kn_e(n, x, &res);
    if(stat){
        print_error_message("Bessel Kn", stat);
    }
    return std::make_tuple(res.val, res.err);
}

std::tuple<double, double> GSL::bessel_K0_scaled(double& x)
{
    gsl_sf_result res;
    int stat = gsl_sf_bessel_K0_scaled_e(x, &res);
    if(stat){
        print_error_message("Scaled Bessel K0", stat);
    }
    return std::make_tuple(res.val, res.err);
}

std::tuple<double, double> GSL::bessel_K1_scaled(double& x)
{
    gsl_sf_result res;
    int stat = gsl_sf_bessel_K1_scaled_e(x, &res);
    if(stat){
        print_error_message("Scaled Bessel K1", stat);
    }
    return std::make_tuple(res.val, res.err);
}

std::tuple<double, double> GSL::bessel_Kn_scaled(int& n, double& x)
{
    gsl_sf_result res;
    int stat = gsl_sf_bessel_Kn_scaled_e(n, x, &res);
    if(stat){
        print_error_message("Scaled Bessel Kn", stat);
    }
    return std::make_tuple(res.val, res.err);
}

std::tuple<double, double> GSL::bessel_j0(double& x)
{
    gsl_sf_result res;
    int stat = gsl_sf_bessel_j0_e(x, &res);
    if(stat){
        print_error_message("Bessel j0", stat);
    }
    return std::make_tuple(res.val, res.err);
}

std::tuple<double, double> GSL::bessel_j1(double& x)
{
    gsl_sf_result res;
    int stat = gsl_sf_bessel_j1_e(x, &res);
    if(stat){
        print_error_message("Bessel j1", stat);
    }
    return std::make_tuple(res.val, res.err);
}

std::tuple<double, double> GSL::bessel_jn(int& n, double& x)
{
    gsl_sf_result res;
    int stat = gsl_sf_bessel_jl_e(n, x, &res);
    if(stat){
        print_error_message("Bessel jn", stat);
    }
    return std::make_tuple(res.val, res.err);
}

std::tuple<double, double> GSL::bessel_y0(double& x)
{
    gsl_sf_result res;
    int stat = gsl_sf_bessel_y0_e(x, &res);
    if(stat){
        print_error_message("Bessel y0", stat);
    }
    return std::make_tuple(res.val, res.err);
}

std::tuple<double, double> GSL::bessel_y1(double& x)
{
    gsl_sf_result res;
    int stat = gsl_sf_bessel_y1_e(x, &res);
    if(stat){
        print_error_message("Bessel y1", stat);
    }
    return std::make_tuple(res.val, res.err);
}

std::tuple<double, double> GSL::bessel_yn(int& n, double& x)
{
    gsl_sf_result res;
    int stat = gsl_sf_bessel_yl_e(n, x, &res);
    if(stat){
        print_error_message("Bessel yn", stat);
    }
    return std::make_tuple(res.val, res.err);
}

std::tuple<double, double> GSL::bessel_i0_scaled(double& x)
{
    gsl_sf_result res;
    int stat = gsl_sf_bessel_i0_scaled_e(x, &res);
    if(stat){
        print_error_message("Scaled Bessel i0", stat);
    }
    return std::make_tuple(res.val, res.err);
}

std::tuple<double, double> GSL::bessel_i1_scaled(double& x)
{
    gsl_sf_result res;
    int stat = gsl_sf_bessel_i1_scaled_e(x, &res);
    if(stat){
        print_error_message("Bessel i1", stat);
    }
    return std::make_tuple(res.val, res.err);
}

std::tuple<double, double> GSL::bessel_in_scaled(int& n, double& x)
{
    gsl_sf_result res;
    int stat = gsl_sf_bessel_il_scaled_e(n, x, &res);
    if(stat){
        print_error_message("Bessel in", stat);
    }
    return std::make_tuple(res.val, res.err);
}

std::tuple<double, double> GSL::bessel_k0_scaled(double& x)
{
    gsl_sf_result res;
    int stat = gsl_sf_bessel_k0_scaled_e(x, &res);
    if(stat){
        print_error_message("Scaled Bessel k0", stat);
    }
    return std::make_tuple(res.val, res.err);
}

std::tuple<double, double> GSL::bessel_k1_scaled(double& x)
{
    gsl_sf_result res;
    int stat = gsl_sf_bessel_k1_scaled_e(x, &res);
    if(stat){
        print_error_message("Scaled Bessel k1", stat);
    }
    return std::make_tuple(res.val, res.err);
}

std::tuple<double, double> GSL::bessel_kn_scaled(int& n, double& x)
{
    gsl_sf_result res;
    int stat = gsl_sf_bessel_kl_scaled_e(n, x, &res);
    if(stat){
        print_error_message("Scaled Bessel kn", stat);
    }
    return std::make_tuple(res.val, res.err);
}

std::tuple<double, double> GSL::bessel_Jnu(double& nu , double& x)
{
    gsl_sf_result res;
    int stat = gsl_sf_bessel_Jnu_e(nu, x, &res);
    if(stat){
        print_error_message("Bessel Jnu", stat);
    }
    return std::make_tuple(res.val, res.err);
}
std::tuple<double, double> GSL::bessel_Ynu(double& nu, double& x)
{
    gsl_sf_result res;
    int stat = gsl_sf_bessel_Ynu_e(nu, x, &res);
    if(stat){
        print_error_message("Bessel Ynu", stat);
    }
    return std::make_tuple(res.val, res.err);
}

std::tuple<double, double> GSL::bessel_Inu(double& nu, double& x)
{
    gsl_sf_result res;
    int stat = gsl_sf_bessel_Inu_e(nu, x, &res);
    if(stat){
        print_error_message("Bessel Inu", stat);
    }
    return std::make_tuple(res.val, res.err);
}

std::tuple<double, double> GSL::bessel_Knu(double& nu, double& x)
{
    gsl_sf_result res;
    int stat = gsl_sf_bessel_Knu_e(nu, x, &res);
    if(stat){
        print_error_message("Bessel Knu", stat);
    }
    return std::make_tuple(res.val, res.err);
}


std::tuple<double, double> GSL::bessel_J0_zeros(unsigned int& n)
{
    gsl_sf_result res;
    int stat = gsl_sf_bessel_zero_J0_e(n, &res);
    if(stat){
        print_error_message("Bessel zeros J0", stat);
    }
    return std::make_tuple(res.val, res.err);
}
std::tuple<double, double> GSL::bessel_J1_zeros(unsigned int& n)
{
    gsl_sf_result res;
    int stat = gsl_sf_bessel_zero_J1_e(n, &res);
    if(stat){
        print_error_message("Bessel zeros J1", stat);
    }
    return std::make_tuple(res.val, res.err);
}

std::tuple<double, double> GSL::bessel_Jnu_zeros(double& nu, unsigned int& n)
{
    gsl_sf_result res;
    int stat = gsl_sf_bessel_zero_Jnu_e(nu, n, &res);
    if(stat){
        print_error_message("Bessel zeros Jnu", stat);
    }
    return std::make_tuple(res.val, res.err);
}
