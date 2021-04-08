#include "GSLpp/interp.h"
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

const gsl_interp_type* gsl_interp_type_translate(Interpolation_type type)
{
    switch(type){
        case Linear : return gsl_interp_linear;
            break;
        case Polynomial : return gsl_interp_polynomial;
            break;
        case CSpline : return gsl_interp_cspline;
            break;
        case CSpline_periodic : return gsl_interp_cspline_periodic;
            break;
        case Akima : return gsl_interp_akima;
            break;
        case Akima_periodic : return gsl_interp_akima_periodic;
            break;
        case Steffen : return gsl_interp_steffen;
            break;
    }
    return nullptr;
}

Interpolation::Interpolation(const std::vector<double>& xa, const std::vector<double>& ya, Interpolation_type type)
 // : gsl_interp_accel_m(gsl_interp_accel_alloc()), gsl_spline_m(gsl_spline_alloc(gsl_interp_type_translate(type), xa.size()))
 : gsl_interp_accel_m(gsl_interp_accel_alloc(), gsl_interp_accel_free), gsl_spline_m(gsl_spline_alloc(gsl_interp_type_translate(type), xa.size()), gsl_spline_free)

{
    if(xa.size() != ya.size()){
        throw std::runtime_error("length of x-input vector not equal to length of y-input vector!");
    }
    // gsl_interp_type interp_type = gsl_interp_type_trans(type);
    // gsl_spline_m = std::shared_ptr<gsl_spline>(gsl_spline_alloc(&interp_type, size), gsl_spline_free);
    gsl_spline_init(gsl_spline_m.get(), &(*xa.cbegin()), &(*ya.cbegin() ), xa.size());
}

// Interpolation::~Interpolation()
// {
    // gsl_interp_accel_free(gsl_interp_accel_m);
    // gsl_spline_free(gsl_spline_m);
// }

double Interpolation::operator()(const double x) const
{
    double res;
    int stat;
    stat = gsl_spline_eval_e(gsl_spline_m.get(), x, gsl_interp_accel_m.get(), &res);
    if(stat){
        print_error_message("Interpolation operator()", stat);
    }
    return res;
}

double Interpolation::deriv(const double x, const size_t n = 1) const
{
    double res;
    int stat;
    if(n == 1){
        stat = gsl_spline_eval_deriv_e(gsl_spline_m.get(), x, gsl_interp_accel_m.get(), &res);
    }else if(n == 2){
        stat = gsl_spline_eval_deriv2_e(gsl_spline_m.get(), x, gsl_interp_accel_m.get(), &res);
    }else{
        throw std::runtime_error("Can only get first or second derivatives of interpolated functions!");
    }
    if(stat){
        print_error_message("Interpolation deriv()", stat);
    }
    return res;
}

double Interpolation::integrate(const double a, const double b) const
{
    double res;
    int stat;
    stat = gsl_spline_eval_integ_e(gsl_spline_m.get(), a, b, gsl_interp_accel_m.get(), &res);
    if(stat){
        print_error_message("Interpolation integrate()", stat);
    }
    return res;
}
