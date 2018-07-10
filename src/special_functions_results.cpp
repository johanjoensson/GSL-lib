#include "special_functions_results.h"
#include <gsl/gsl_sf_elementary.h>
#include <cmath>


using namespace GSL;

Result::Result()
{}

Result::Result(gsl_sf_result res)
 : gsl_res(res), val(res.val), err(res.err)
{
}

Result GSL::operator+(const Result& a, const Result& b)
{
    gsl_sf_result res;
    res.val = a.val + b.val;
    res.err = std::sqrt(a.err*a.err + b.err*b.err);
    return Result(res);
}

Result GSL::operator+(const Result& a, const double& b)
{
    gsl_sf_result res;
    res.val = a.val + b;
    res.err = a.err*a.err ;
    return Result(res);
}

Result GSL::operator+(const double& a, const Result& b)
{
    gsl_sf_result res;
    res.val = a + b.val;
    res.err = b.err*b.err;
    return Result(res);
}

Result GSL::operator-(const Result& a, const Result& b)
{
    gsl_sf_result res;
    res.val = a.val - b.val;
    res.err = std::sqrt(a.err*a.err + b.err*b.err);
    return Result(res);
}

Result GSL::operator-(const Result& a, const double& b)
{
    gsl_sf_result res;
    res.val = a.val - b;
    res.err = a.err*a.err ;
    return Result(res);
}

Result GSL::operator-(const double& a, const Result& b)
{
    gsl_sf_result res;
    res.val = a - b.val;
    res.err = b.err*b.err;
    return Result(res);
}

Result GSL::operator*(const Result& a, const Result& b)
{
    Result res;
    gsl_sf_multiply_err_e(a.val, a.err, b.val, b.err, &res.gsl_res);
    return res;
}

Result GSL::operator*(const Result& a, const double& b)
{
    Result res;
    gsl_sf_multiply_err_e(a.val, a.err, b, 0, &res.gsl_res);
    return res;
}

Result GSL::operator*(const double& a, const Result& b)
{
    Result res;
    gsl_sf_multiply_err_e(a, 0, b.val, b.err, &res.gsl_res);
    return res;
}

Result GSL::operator/(const Result& a, const Result& b)
{
    Result res;
    gsl_sf_multiply_err_e(a.val, a.err, 1./b.val, b.err, &res.gsl_res);
    return res;
}

Result GSL::operator/(const Result& a, const double& b)
{
    Result res;
    gsl_sf_multiply_err_e(a.val, a.err, 1./b, b, &res.gsl_res);
    return res;
}

Result GSL::operator/(const double& a, const Result& b)
{
    Result res;
    gsl_sf_multiply_err_e(a, 0, 1./b.val, b.err, &res.gsl_res);
    return res;
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
