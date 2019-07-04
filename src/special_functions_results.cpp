#include "special_functions_results.h"
#include "special_functions.h"
#include <gsl/gsl_sf_elementary.h>
#include <gsl/gsl_sf_trig.h>
#include <cmath>

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

Result::Result()
 : gsl_res(), val(0), err(0)
{
    gsl_res = {0., 0.};
}

Result::Result(const double a, const double b)
 : gsl_res(), val(a), err(b)
{
	gsl_res = {a, b};
}

Result::Result(gsl_sf_result res)
 : gsl_res(res), val(res.val), err(res.err)
{
}

Result GSL::operator+(const Result& a, const Result& b)
{
    gsl_sf_result res{0., 0.};
    res.val = a.val + b.val;
    res.err = std::sqrt(a.err*a.err + b.err*b.err);
    return Result(res);
}

Result GSL::operator+(const Result& a, const double& b)
{
    gsl_sf_result res{0., 0.};
    res.val = a.val + b;
    res.err = a.err ;
    return Result(res);
}

Result GSL::operator+(const double& a, const Result& b)
{
    gsl_sf_result res{0., 0.};
    res.val = a + b.val;
    res.err = b.err;
    return Result(res);
}

Result GSL::operator-(const Result& a, const Result& b)
{
    gsl_sf_result res{0., 0.};
    res.val = a.val - b.val;
    res.err = std::sqrt(a.err*a.err + b.err*b.err);
    return Result(res);
}

Result GSL::operator-(const Result& a, const double& b)
{
    gsl_sf_result res{0., 0.};
    res.val = a.val - b;
    res.err = a.err;
    return Result(res);
}

Result GSL::operator-(const double& a, const Result& b)
{
    gsl_sf_result res{0., 0.};
    res.val = a - b.val;
    res.err = b.err;
    return Result(res);
}

Result GSL::operator*(const Result& a, const Result& b)
{
    gsl_sf_result res{0., 0.};
    int stat = gsl_sf_multiply_err_e(a.val, a.err, b.val, b.err, &res);
    if(stat == GSL_EUNDRFLW){
	    res.val = 0.;
        res.err = 0;
    }else if(stat){
        print_error_message("multiplication", stat);
    }
    return Result(res);
}

Result GSL::operator*(const Result& a, const double& b)
{
    gsl_sf_result res{0., 0.};
    int stat = gsl_sf_multiply_err_e(a.val, a.err, b, 0., &res);
    if(stat == GSL_EUNDRFLW){
	    res.val = 0.;
        res.err = 0;
    }else if(stat){
        print_error_message("multiplication", stat);
    }
    return Result(res);
}

Result GSL::operator*(const double& a, const Result& b)
{
    gsl_sf_result res{0., 0.};
    int stat = gsl_sf_multiply_err_e(a, 0., b.val, 0, &res);
    if(stat == GSL_EUNDRFLW){
	    res.val = 0.;
        res.err = 0;
    }else if(stat){
        print_error_message("multiplication", stat);
    }
    return Result(res);
}

Result GSL::operator/(const Result& a, const Result& b)
{
    gsl_sf_result res{0., 0.};
    int stat = gsl_sf_multiply_err_e(a.val, a.err, 1./b.val, b.err, &res);
    if(stat == GSL_EUNDRFLW){
	    res.val = 0.;
        res.err = 0;
    }else if(stat){
        print_error_message("division", stat);
    }
    return Result(res);
}

Result GSL::operator/(const Result& a, const double& b)
{
    gsl_sf_result res{0., 0.};
    int stat = gsl_sf_multiply_err_e(a.val, a.err, 1./b, 0., &res);
    if(stat == GSL_EUNDRFLW){
	    res.val = 0.;
        res.err = 0;
    }else if(stat){
        print_error_message("mdivision", stat);
    }
    return Result(res);
}

Result GSL::operator/(const double& a, const Result& b)
{
    gsl_sf_result res{0., 0.};
    int stat = gsl_sf_multiply_err_e(a, 0, 1./b.val, 0., &res);
    if(stat == GSL_EUNDRFLW){
	    res.val = 0.;
        res.err = 0;
    }else if(stat){
        print_error_message("division", stat);
    }
    return Result(res);
}

Result& Result::operator+=(const Result& a)
{
    *this = *this + a;
    return *this;
}
Result& Result::operator+=(const double& a)
{
    *this = *this + a;
    return *this;
}

Result& Result::operator-=(const Result& a)
{
    *this = *this - a;
    return *this;
}

Result& Result::operator-=(const double& a)
{
    *this = *this - a;
    return *this;
}

Result& Result::operator*=(const Result& a)
{
    *this = *this * a;
    return *this;
}

Result& Result::operator*=(const double& a)
{
    *this = *this * a;
    return *this;
}

Result& Result::operator/=(const Result& a)
{
    *this = *this / a;
    return *this;
}

Result& Result::operator/=(const double& a)
{
    *this = *this / a;
    return *this;
}

Result GSL::exp(const Result& x)
{
    gsl_sf_result res{0., 0.};
    Result tmp = exp(x.val);

    res.val = tmp.val;
    res.err = std::sqrt(tmp.err*tmp.err + res.val*x.err*res.val*x.err);

    return Result(res);
}

Result GSL::sin(const Result& x)
{
    gsl_sf_result res{0., 0.};
    int stat = gsl_sf_sin_err_e(x.val, x.err, &res);
    if(stat){
        print_error_message("sin", stat);
    }
    return Result(res);
}
Result GSL::cos(const Result& x)
{
    gsl_sf_result res{0., 0.};
    int stat = gsl_sf_cos_err_e(x.val, x.err, &res);
    if(stat){
        print_error_message("cos", stat);
    }
    return Result(res);
}


std::ostream& GSL::operator<<(std::ostream& os, const Result& R)
{
    os << R.val << " \u00b1 " << R.err;
    return os;
}

bool GSL::operator==(const Result& a, const Result& b)
{
    return (a.val == b.val) && (std::abs(a.err - b.err) < 1E-16);
}

bool GSL::operator!=(const Result& a, const Result& b)
{
    return !(a == b);
}
