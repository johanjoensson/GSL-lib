#include "GSLpp/complex.h"
#include "GSLpp/special_functions.h"
#include <gsl/gsl_complex_math.h>
#include <cmath>

namespace GSL{

template<class T, class GSL_COMPLEX>
Complex_t<T, GSL_COMPLEX>::Complex_t(const std::shared_ptr<GSL_COMPLEX>& z)
 : gsl_c(z)
{}

template<>
Complex_t<double, gsl_complex>::Complex_t(const double& a, const double& b)
 : gsl_c(new gsl_complex)
{
    *this->gsl_c = gsl_complex_rect(a,b);
}

template<class T, class GSL_COMPLEX>
T Complex_t<T, GSL_COMPLEX>::abs() const
{return std::sqrt(this->abs2());}

template<class T, class GSL_COMPLEX>
T Complex_t<T, GSL_COMPLEX>::abs2() const
{return this->re()*this->re() + this->im()*this->im();}

template<class T, class GSL_COMPLEX>
T Complex_t<T, GSL_COMPLEX>::logabs() const
{return std::log(this->abs2())/2;}

template<class T, class GSL_COMPLEX>
T Complex_t<T, GSL_COMPLEX>::arg() const
{
    T res = 0;
    if(this->im() != 0){
        res = 2*std::atan((this->abs() - this->re())/this->im());
    }else if(this->re() > 0){
        res = 0;
    }else if(this->re() < 0){
        res = static_cast<T>(M_PI);
    }else{
        res = static_cast<T>(NAN);
    }
    return res;
}

template<class T, class GSL_COMPLEX>
Complex_t<T, GSL_COMPLEX> Complex_t<T, GSL_COMPLEX>::conjugate() const
{return {this->re(), -this->im()};}

template<class T, class GSL_COMPLEX>
Complex_t<T, GSL_COMPLEX> Complex_t<T, GSL_COMPLEX>::recipr() const
{return this->conjugate()/this->abs2();}

template<class T, class GSL_COMPLEX>
Complex_t<T, GSL_COMPLEX> Complex_t<T, GSL_COMPLEX>::negate() const
{return {-this->re(), -this->im()};}

template<class T, class GSL_COMPLEX>
Complex_t<T, GSL_COMPLEX> Complex_t<T, GSL_COMPLEX>::operator+(const Complex_t& b) const
    {return {this->re() + b.re(), this->im() + b.im()};}

template<class T, class GSL_COMPLEX>
Complex_t<T, GSL_COMPLEX> Complex_t<T, GSL_COMPLEX>::operator-(const Complex_t& b) const
    {return {this->re() - b.re(), this->im() - b.im()};}

template<class T, class GSL_COMPLEX>
Complex_t<T, GSL_COMPLEX> Complex_t<T, GSL_COMPLEX>::operator*(const Complex_t& b) const
    {return {this->re()*b.re() - this->im()*b.im(), this->re()*b.im() + this->im()*b.re()};}

template<class T, class GSL_COMPLEX>
Complex_t<T, GSL_COMPLEX> Complex_t<T, GSL_COMPLEX>::operator/(const Complex_t& b) const
    {return (*this)*b.conjugate()/b.abs2();}

template<class T, class GSL_COMPLEX>
Complex_t<T, GSL_COMPLEX> Complex_t<T, GSL_COMPLEX>::operator+(const T& s) const
{ return {this->re() + s, this->im()};}

template<class T, class GSL_COMPLEX>
Complex_t<T, GSL_COMPLEX> Complex_t<T, GSL_COMPLEX>::operator-(const T& s) const
{ return {this->re() - s, this->im()};}

template<class T, class GSL_COMPLEX>
Complex_t<T, GSL_COMPLEX> Complex_t<T, GSL_COMPLEX>::operator*(const T& s) const
{ return {this->re() * s, this->im() * s};}

template<class T, class GSL_COMPLEX>
Complex_t<T, GSL_COMPLEX> Complex_t<T, GSL_COMPLEX>::operator/(const T& s) const
{ return {this->re() / s, this->im() / s};}

template<>
Complex_t<long double, gsl_complex_long_double>::Complex_t(const long double& a, const long double& b)
 : gsl_c(new gsl_complex_long_double)
{
    this->gsl_c->dat[0] = a;
    this->gsl_c->dat[1] = b;
}

template<>
Complex_t<float, gsl_complex_float>::Complex_t(const float& a, const float& b)
 : gsl_c(new gsl_complex_float)
{
    this->gsl_c->dat[0] = a;
    this->gsl_c->dat[1] = b;
}

template<>
Complex_t<double, gsl_complex> Complex_t<double, gsl_complex>::operator+(const Complex_t<double, gsl_complex>& b) const
{
    return Complex_t<double, gsl_complex>(gsl_complex_add(*this->gsl_c.get(), *b.gsl_c.get()));
}

template<>
Complex_t<double, gsl_complex> Complex_t<double, gsl_complex>::operator+(const double& s) const
{
    return Complex_t<double, gsl_complex>(gsl_complex_add_real(*this->gsl_c.get(), s));
}

template<>
Complex_t<double, gsl_complex> Complex_t<double, gsl_complex>::operator-(const Complex_t<double, gsl_complex>& b) const
{
    return Complex_t<double, gsl_complex>(gsl_complex_sub(*this->gsl_c.get(), *b.gsl_c.get()));
}

template<>
 Complex_t<double, gsl_complex> Complex_t<double, gsl_complex>::operator-(const double& s) const
{
    return Complex_t<double, gsl_complex>(gsl_complex_sub_real(*this->gsl_c.get(), s));
}

template<>
Complex_t<double, gsl_complex> Complex_t<double, gsl_complex>::operator-() const
{
    return Complex_t<double, gsl_complex>(gsl_complex_negative(*this->gsl_c.get()));
}

template<>
Complex_t<double, gsl_complex> Complex_t<double, gsl_complex>::operator*(const Complex_t<double, gsl_complex>& b) const
{
    return Complex_t<double, gsl_complex>(gsl_complex_mul(*this->gsl_c.get(), *b.gsl_c.get()));
}

template<>
Complex_t<double, gsl_complex> Complex_t<double, gsl_complex>::operator*(const double& s) const
{
    return Complex_t<double, gsl_complex>(gsl_complex_mul_real(*this->gsl_c.get(), s));
}

template<>
Complex_t<double, gsl_complex> Complex_t<double, gsl_complex>::operator/(const Complex_t<double, gsl_complex>& b) const
{
    return Complex_t<double, gsl_complex>(gsl_complex_div(*this->gsl_c.get(), *b.gsl_c.get()));
}

template<>
Complex_t<double, gsl_complex> Complex_t<double, gsl_complex>::operator/(const double& s) const
{
    return Complex_t<double, gsl_complex>(gsl_complex_div_real(*this->gsl_c.get(), s));
}

template<>
double Complex_t<double, gsl_complex>::abs() const
{
    return gsl_complex_abs(*this->gsl_c.get());
}

template<>
double Complex_t<double, gsl_complex>::abs2() const
{
    return gsl_complex_abs2(*this->gsl_c.get());
}

template<>
double Complex_t<double, gsl_complex>::logabs() const
{
    return gsl_complex_logabs(*this->gsl_c.get());
}

template<>
double Complex_t<double, gsl_complex>::arg() const
{
    return gsl_complex_arg(*this->gsl_c.get());
}

template<>
Complex_t<double, gsl_complex> Complex_t<double, gsl_complex>::conjugate() const
{
    return Complex_t<double, gsl_complex>(gsl_complex_conjugate(*gsl_c.get()));
}

template<>
Complex_t<double, gsl_complex> Complex_t<double, gsl_complex>::recipr() const
{
    return Complex_t<double, gsl_complex>(gsl_complex_inverse(*gsl_c.get()));
}

template<>
Complex_t<double, gsl_complex> Complex_t<double, gsl_complex>::negate() const
{
    return Complex_t<double, gsl_complex>(gsl_complex_negative(*gsl_c.get()));
}

Complex_t<double, gsl_complex> sqrt(const double& s)
{
    return Complex_t<double, gsl_complex>(gsl_complex_sqrt_real(s));
}

Complex_t<double, gsl_complex> sqrt(const Complex_t<double, gsl_complex>& a)
{
    return Complex_t<double, gsl_complex>(gsl_complex_sqrt(*a.gsl_c.get()));
}

Complex_t<double, gsl_complex> pow(const Complex_t<double, gsl_complex>& a, const Complex_t<double, gsl_complex>& b)
{
    return Complex_t<double, gsl_complex>(gsl_complex_pow(*a.gsl_c.get(), *b.gsl_c.get()));
}

Complex_t<double, gsl_complex> pow(const Complex_t<double, gsl_complex>& a, const double& s)
{
    return Complex_t<double, gsl_complex>(gsl_complex_pow_real(*a.gsl_c.get(), s));
}

Complex_t<double, gsl_complex> exp(const Complex_t<double, gsl_complex>& a)
{
    return Complex_t<double, gsl_complex>(gsl_complex_exp(*a.gsl_c.get()));
}

Complex_t<double, gsl_complex> log(const Complex_t<double, gsl_complex>& a)
{
    return Complex_t<double, gsl_complex>(gsl_complex_log(*a.gsl_c.get()));
}

Complex_t<double, gsl_complex> log10(const Complex_t<double, gsl_complex>& a)
{
    return Complex_t<double, gsl_complex>(gsl_complex_log10(*a.gsl_c.get()));
}

Complex_t<double, gsl_complex> log_b(const Complex_t<double, gsl_complex>& a, const Complex_t<double, gsl_complex>& b)
{
    return Complex_t<double, gsl_complex>(gsl_complex_log_b(*a.gsl_c.get(), *b.gsl_c.get()));
}

Complex_t<double, gsl_complex> sin(const Complex_t<double, gsl_complex>& a)
{
    return Complex_t<double, gsl_complex>(gsl_complex_sin(*a.gsl_c.get()));
}

Complex_t<double, gsl_complex> cos(const Complex_t<double, gsl_complex>& a)
{
    return Complex_t<double, gsl_complex>(gsl_complex_cos(*a.gsl_c.get()));
}

Complex_t<double, gsl_complex> tan(const Complex_t<double, gsl_complex>& a)
{
    return Complex_t<double, gsl_complex>(gsl_complex_tan(*a.gsl_c.get()));
}

Complex_t<double, gsl_complex> sec(const Complex_t<double, gsl_complex>& a)
{
    return Complex_t<double, gsl_complex>(gsl_complex_sec(*a.gsl_c.get()));
}

Complex_t<double, gsl_complex> csc(const Complex_t<double, gsl_complex>& a)
{
    return Complex_t<double, gsl_complex>(gsl_complex_csc(*a.gsl_c.get()));
}

Complex_t<double, gsl_complex> cot(const Complex_t<double, gsl_complex>& a)
{
    return Complex_t<double, gsl_complex>(gsl_complex_cot(*a.gsl_c.get()));
}

Complex_t<double, gsl_complex> arcsin(const Complex_t<double, gsl_complex>& a)
{
    return Complex_t<double, gsl_complex>(gsl_complex_arcsin(*a.gsl_c.get()));
}

Complex_t<double, gsl_complex> arcsin(const double& s)
{
    return Complex_t<double, gsl_complex>(gsl_complex_arcsin_real(s));
}

Complex_t<double, gsl_complex> arccos(const Complex_t<double, gsl_complex>& a)
{
    return Complex_t<double, gsl_complex>(gsl_complex_arccos(*a.gsl_c.get()));
}

Complex_t<double, gsl_complex> arccos(const double& s)
{
    return Complex_t<double, gsl_complex>(gsl_complex_arccos_real(s));
}

Complex_t<double, gsl_complex> arctan(const Complex_t<double, gsl_complex>& a)
{
    return Complex_t<double, gsl_complex>(gsl_complex_arctan(*a.gsl_c.get()));
}

Complex_t<double, gsl_complex> arcsec(const Complex_t<double, gsl_complex>& a)
{
    return Complex_t<double, gsl_complex>(gsl_complex_arcsec(*a.gsl_c.get()));
}

Complex_t<double, gsl_complex> arcsec(const double& s)
{
    return Complex_t<double, gsl_complex>(gsl_complex_arcsec_real(s));
}

Complex_t<double, gsl_complex> arccsc(const Complex_t<double, gsl_complex>& a)
{
    return Complex_t<double, gsl_complex>(gsl_complex_arccsc(*a.gsl_c.get()));
}

Complex_t<double, gsl_complex> arccsc(const double& s)
{
    return Complex_t<double, gsl_complex>(gsl_complex_arccsc_real(s));
}

Complex_t<double, gsl_complex> arccot(const Complex_t<double, gsl_complex>& a)
{
    return Complex_t<double, gsl_complex>(gsl_complex_arccot(*a.gsl_c.get()));
}

Complex_t<double, gsl_complex> sinh(const Complex_t<double, gsl_complex>& a)
{
    return Complex_t<double, gsl_complex>(gsl_complex_sinh(*a.gsl_c.get()));
}

Complex_t<double, gsl_complex> cosh(const Complex_t<double, gsl_complex>& a)
{
    return Complex_t<double, gsl_complex>(gsl_complex_cosh(*a.gsl_c.get()));
}

Complex_t<double, gsl_complex> tanh(const Complex_t<double, gsl_complex>& a)
{
    return Complex_t<double, gsl_complex>(gsl_complex_tanh(*a.gsl_c.get()));
}

Complex_t<double, gsl_complex> sech(const Complex_t<double, gsl_complex>& a)
{
    return Complex_t<double, gsl_complex>(gsl_complex_sech(*a.gsl_c.get()));
}

Complex_t<double, gsl_complex> csch(const Complex_t<double, gsl_complex>& a)
{
    return Complex_t<double, gsl_complex>(gsl_complex_csch(*a.gsl_c.get()));
}

Complex_t<double, gsl_complex> coth(const Complex_t<double, gsl_complex>& a)
{
    return Complex_t<double, gsl_complex>(gsl_complex_coth(*a.gsl_c.get()));
}

Complex_t<double, gsl_complex> arcsinh(const Complex_t<double, gsl_complex>& a)
{
    return Complex_t<double, gsl_complex>(gsl_complex_arcsinh(*a.gsl_c.get()));
}

Complex_t<double, gsl_complex> arccosh(const Complex_t<double, gsl_complex>& a)
{
    return Complex_t<double, gsl_complex>(gsl_complex_arccosh(*a.gsl_c.get()));
}

Complex_t<double, gsl_complex> arccosh(const double& s)
{
    return Complex_t<double, gsl_complex>(gsl_complex_arccosh_real(s));
}

Complex_t<double, gsl_complex> arctanh(const Complex_t<double, gsl_complex>& a)
{
    return Complex_t<double, gsl_complex>(gsl_complex_arctanh(*a.gsl_c.get()));
}

Complex_t<double, gsl_complex> arctanh(const double& s)
{
    return Complex_t<double, gsl_complex>(gsl_complex_arctanh_real(s));
}

Complex_t<double, gsl_complex> arcsech(const Complex_t<double, gsl_complex>& a)
{
    return Complex_t<double, gsl_complex>(gsl_complex_arcsech(*a.gsl_c.get()));
}

Complex_t<double, gsl_complex> arccsch(const Complex_t<double, gsl_complex>& a)
{
    return Complex_t<double, gsl_complex>(gsl_complex_arccsch(*a.gsl_c.get()));
}

Complex_t<double, gsl_complex> arccoth(const Complex_t<double, gsl_complex>& a)
{
    return Complex_t<double, gsl_complex>(gsl_complex_arccoth(*a.gsl_c.get()));
}

bool operator==( const gsl_complex&a, const gsl_complex&b)
{
    return a.dat[0] == b.dat[0] && a.dat[1] == b.dat[1];
}

bool operator==( const gsl_complex_float&a, const gsl_complex_float&b)
{
    return a.dat[0] == b.dat[0] && a.dat[1] == b.dat[1];
}

bool operator==( const gsl_complex_long_double&a, const gsl_complex_long_double&b)
{
    return a.dat[0] == b.dat[0] && a.dat[1] == b.dat[1];
}

gsl_complex operator*(const gsl_complex& a, const gsl_complex&b)
{
    return gsl_complex_mul(a, b);
}
gsl_complex operator+(const gsl_complex& a, const gsl_complex&b)
{
    return gsl_complex_add(a, b);
}

gsl_complex operator-(const gsl_complex& a, const gsl_complex&b)
{
    return gsl_complex_sub(a, b);
}

gsl_complex_long_double operator+(const gsl_complex_long_double& a, const gsl_complex_long_double&b)
{
    gsl_complex_long_double res;
    res.dat[0] = a.dat[0] + b.dat[0];
    res.dat[1] = a.dat[1] + b.dat[1];
    return res;
}

gsl_complex_long_double operator-(const gsl_complex_long_double& a, const gsl_complex_long_double&b)
{
    gsl_complex_long_double res;
    res.dat[0] = a.dat[0] - b.dat[0];
    res.dat[1] = a.dat[1] - b.dat[1];
    return res;
}

gsl_complex_long_double operator*(const gsl_complex_long_double& a, const gsl_complex_long_double&b)
{
    gsl_complex_long_double res;
    res.dat[0] = a.dat[0]*b.dat[0] - a.dat[1]*b.dat[1];
    res.dat[1] = a.dat[1]*b.dat[0] + a.dat[0]*b.dat[1];
    return res;
}

gsl_complex_float operator+(const gsl_complex_float& a, const gsl_complex_float&b)
{
    gsl_complex_float res;
    res.dat[0] = a.dat[0] + b.dat[0];
    res.dat[1] = a.dat[1] + b.dat[1];
    return res;
}

gsl_complex_float operator-(const gsl_complex_float& a, const gsl_complex_float&b)
{
    gsl_complex_float res;
    res.dat[0] = a.dat[0] - b.dat[0];
    res.dat[1] = a.dat[1] - b.dat[1];
    return res;
}

gsl_complex_float operator*(const gsl_complex_float& a, const gsl_complex_float&b)
{
    gsl_complex_float res;
    res.dat[0] = a.dat[0]*b.dat[0] - a.dat[1]*b.dat[1];
    res.dat[1] = a.dat[1]*b.dat[0] + a.dat[0]*b.dat[1];
    return res;
}

template Complex_t<double, gsl_complex>::Complex_t(const gsl_complex& a);
template Complex_t<float, gsl_complex_float>::Complex_t(const gsl_complex_float& a);
template Complex_t<long double, gsl_complex_long_double>::Complex_t(const gsl_complex_long_double& a);

template float Complex_t<float, gsl_complex_float>::abs() const;
template long double Complex_t<long double, gsl_complex_long_double>::abs() const;
template float Complex_t<float, gsl_complex_float>::abs2() const;
template long double Complex_t<long double, gsl_complex_long_double>::abs2() const;
template float Complex_t<float, gsl_complex_float>::logabs() const;
template long double Complex_t<long double, gsl_complex_long_double>::logabs() const;

template float Complex_t<float, gsl_complex_float>::arg() const;
template long double Complex_t<long double, gsl_complex_long_double>::arg() const;

template Complex_t<float, gsl_complex_float> Complex_t<float, gsl_complex_float>::conjugate() const;
template Complex_t<long double, gsl_complex_long_double> Complex_t<long double, gsl_complex_long_double>::conjugate() const;

template Complex_t<float, gsl_complex_float> Complex_t<float, gsl_complex_float>::recipr() const;
template Complex_t<long double, gsl_complex_long_double> Complex_t<long double, gsl_complex_long_double>::recipr() const;

template Complex_t<float, gsl_complex_float> Complex_t<float, gsl_complex_float>::negate() const;
template Complex_t<long double, gsl_complex_long_double> Complex_t<long double, gsl_complex_long_double>::negate() const;

template Complex_t<float, gsl_complex_float> Complex_t<float, gsl_complex_float>::operator+(const Complex_t& b) const;
template Complex_t<long double, gsl_complex_long_double> Complex_t<long double, gsl_complex_long_double>::operator+(const Complex_t& b) const;
template Complex_t<float, gsl_complex_float> Complex_t<float, gsl_complex_float>::operator-(const Complex_t& b) const;
template Complex_t<long double, gsl_complex_long_double> Complex_t<long double, gsl_complex_long_double>::operator-(const Complex_t& b) const;
template Complex_t<float, gsl_complex_float> Complex_t<float, gsl_complex_float>::operator*(const Complex_t& b) const;
template Complex_t<long double, gsl_complex_long_double> Complex_t<long double, gsl_complex_long_double>::operator*(const Complex_t& b) const;
template Complex_t<float, gsl_complex_float> Complex_t<float, gsl_complex_float>::operator/(const Complex_t& b) const;
template Complex_t<long double, gsl_complex_long_double> Complex_t<long double, gsl_complex_long_double>::operator/(const Complex_t& b) const;

template Complex_t<float, gsl_complex_float> Complex_t<float, gsl_complex_float>::operator+(const float& s) const;
template Complex_t<long double, gsl_complex_long_double> Complex_t<long double, gsl_complex_long_double>::operator+(const long double& s) const;
template Complex_t<float, gsl_complex_float> Complex_t<float, gsl_complex_float>::operator-(const float& s) const;
template Complex_t<long double, gsl_complex_long_double> Complex_t<long double, gsl_complex_long_double>::operator-(const long double& s) const;
template Complex_t<float, gsl_complex_float> Complex_t<float, gsl_complex_float>::operator*(const float& s) const;
template Complex_t<long double, gsl_complex_long_double> Complex_t<long double, gsl_complex_long_double>::operator*(const long double& s) const;
template Complex_t<float, gsl_complex_float> Complex_t<float, gsl_complex_float>::operator/(const float& s) const;
template Complex_t<long double, gsl_complex_long_double> Complex_t<long double, gsl_complex_long_double>::operator/(const long double& s) const;

template Complex_t<float, gsl_complex_float> Complex_t<float, gsl_complex_float>::operator+(const gsl_complex_float& s) const;
template Complex_t<long double, gsl_complex_long_double> Complex_t<long double, gsl_complex_long_double>::operator+(const gsl_complex_long_double& s) const;
template Complex_t<float, gsl_complex_float> Complex_t<float, gsl_complex_float>::operator-(const gsl_complex_float& s) const;
template Complex_t<long double, gsl_complex_long_double> Complex_t<long double, gsl_complex_long_double>::operator-(const gsl_complex_long_double& s) const;
template Complex_t<float, gsl_complex_float> Complex_t<float, gsl_complex_float>::operator*(const gsl_complex_float& s) const;
template Complex_t<long double, gsl_complex_long_double> Complex_t<long double, gsl_complex_long_double>::operator*(const gsl_complex_long_double& s) const;
template Complex_t<float, gsl_complex_float> Complex_t<float, gsl_complex_float>::operator/(const gsl_complex_float& s) const;
template Complex_t<long double, gsl_complex_long_double> Complex_t<long double, gsl_complex_long_double>::operator/(const gsl_complex_long_double& s) const;
}
