#include "complex_template.h"
#include "special_functions.h"
#include <gsl/gsl_complex_math.h>
#include <cmath>

namespace GSL{


template<>
inline Complex_t<double, gsl_complex>::Complex_t(const double& a, const double& b)
 : gsl_c(new gsl_complex)
{
    *this->gsl_c = gsl_complex_rect(a,b);
}

template<>
inline Complex_t<long double, gsl_complex_long_double>::Complex_t(const long double& a, const long double& b)
 : gsl_c(new gsl_complex_long_double)
{
    this->gsl_c->dat[0] = a;
    this->gsl_c->dat[1] = b;
}

template<>
inline Complex_t<float, gsl_complex_float>::Complex_t(const float& a, const float& b)
 : gsl_c(new gsl_complex_float)
{
    this->gsl_c->dat[0] = a;
    this->gsl_c->dat[1] = b;
}

template<class T>
void no_op(T*);
template<>
inline void no_op<gsl_complex>(gsl_complex*){}
template<>
inline void no_op<gsl_complex_long_double>(gsl_complex_long_double*){}
template<>
inline void no_op<gsl_complex_float>(gsl_complex_float*){}
template<class T, class GSL_COMPLEX>
Complex_t<T, GSL_COMPLEX>::Complex_t(const GSL_COMPLEX& z)
 : gsl_c(new GSL_COMPLEX)
{
    *gsl_c = z;
}

template<class T, class GSL_COMPLEX>
T& Complex_t<T, GSL_COMPLEX>::re() const
{
	return this->gsl_c->dat[0];
}

template<class T, class GSL_COMPLEX>
T& Complex_t<T, GSL_COMPLEX>::im() const
{
	return this->gsl_c->dat[1];
}

template<class T, class GSL_COMPLEX>
Complex_t<T, GSL_COMPLEX>& Complex_t<T, GSL_COMPLEX>::operator= (const Complex_t<T, GSL_COMPLEX>& z)
{
    if(this == &z){
        return *this;
    }
    this->gsl_c = z.gsl_c;

    return *this;
}

template<class T, class GSL_COMPLEX>
Complex_t<T, GSL_COMPLEX>& Complex_t<T, GSL_COMPLEX>::operator= (Complex_t<T, GSL_COMPLEX>&& m)
{
    std::swap(this->gsl_c, m.gsl_c);
    return *this;
}

template<class T, class G>
Complex_t<T, G> Complex_t<T, G>::operator+(const Complex_t<T, G>& b) const
{
    Complex_t<T, G> res = *this;
    res.re() += b.re();
    res.im() += b.im();
    return res;
}

template<>
inline Complex Complex::operator+(const Complex& b) const
{
    return Complex(gsl_complex_add(*this->gsl_c.get(), *b.gsl_c.get()));
}

template<class T, class G>
Complex_t<T, G> Complex_t<T, G>::operator+(const T& s) const
{
    Complex_t<T, G> res = *this;
    res.re() += s;
    return res;
}

template<>
inline Complex Complex::operator+(const double& s) const
{
    return Complex(gsl_complex_add_real(*this->gsl_c.get(), s));
}

template<class T, class G>
Complex_t<T, G> Complex_t<T, G>::operator-(const Complex_t<T, G>& b) const
{
    Complex_t<T, G> res = *this;
    res.re() -= b.re();
    res.im() -= b.im();
    return res;
}

template<>
inline Complex Complex::operator-(const Complex& b) const
{
    return Complex(gsl_complex_sub(*this->gsl_c.get(), *b.gsl_c.get()));
}

template<class T, class G>
Complex_t<T, G> Complex_t<T, G>::operator-(const T& s) const
{
    Complex_t<T, G> res = *this;
    res.re() -= s;
    return res;
}

template<>
inline Complex Complex::operator-(const double& s) const
{
    return Complex(gsl_complex_sub_real(*this->gsl_c.get(), s));
}

template<class T, class G>
Complex_t<T, G> Complex_t<T, G>::operator-() const
{
    Complex_t<T, G> res = *this;
    res.re() *= -1;
    res.im() *= -1;
    return res;
}

template<>
inline Complex Complex::operator-() const
{
    return Complex(gsl_complex_negative(*this->gsl_c.get()));
}

template<class T, class G>
Complex_t<T, G> Complex_t<T, G>::operator*(const Complex_t<T, G>& b) const
{
    Complex_t<T, G> res = *this;
    res.re() = res.re()*b.re() - res.im()*b.im();
    res.im() = res.re()*b.im() + res.im()*b.re();
    return res;
}

template<>
inline Complex Complex::operator*(const Complex& b) const
{
    return Complex(gsl_complex_mul(*this->gsl_c.get(), *b.gsl_c.get()));
}

template<class T, class G>
Complex_t<T, G> Complex_t<T, G>::operator*(const T& s) const
{
    Complex_t<T, G> res = *this;
    res.re() *= s;
    res.im() *= s;
    return res;
}

template<>
inline Complex Complex::operator*(const double& s) const
{
    return Complex(gsl_complex_mul_real(*this->gsl_c.get(), s));
}

template<class T, class G>
Complex_t<T, G> Complex_t<T, G>::operator/(const Complex_t<T, G>& b) const
{
    Complex_t<T, G> res = *this;
    res *= b.conjugate()/b.abs2();
    return res;
}

template<>
inline Complex Complex::operator/(const Complex& b) const
{
    return Complex(gsl_complex_div(*this->gsl_c.get(), *b.gsl_c.get()));
}

template<class T, class G>
Complex_t<T, G> Complex_t<T, G>::operator/(const T& s) const
{
    Complex_t<T, G> res = *this;
    res.re() /= s;
    res.im() /= s;
    return res;
}

template<>
inline Complex Complex::operator/(const double& s) const
{
    return Complex(gsl_complex_div_real(*this->gsl_c.get(), s));
}

template<class T, class GSL_COMPLEX>
Complex_t<T, GSL_COMPLEX>& Complex_t<T, GSL_COMPLEX>::operator+=(const Complex_t<T, GSL_COMPLEX>& b)
{
    *this = (*this) + b;
    return *this;
}

template<class T, class GSL_COMPLEX>
Complex_t<T, GSL_COMPLEX>& Complex_t<T, GSL_COMPLEX>::operator-=(const Complex_t<T, GSL_COMPLEX>& b)
{
    *this = (*this) - b;
    return *this;
}

template<class T, class GSL_COMPLEX>
Complex_t<T, GSL_COMPLEX>& Complex_t<T, GSL_COMPLEX>::operator*=(const Complex_t<T, GSL_COMPLEX>& b)
{
    *this = (*this) * b;
    return *this;
}

template<class T, class GSL_COMPLEX>
Complex_t<T, GSL_COMPLEX>& Complex_t<T, GSL_COMPLEX>::operator/=(const Complex_t<T, GSL_COMPLEX>& b)
{
    *this = (*this) / b;
    return *this;
}

template<class T, class GSL_COMPLEX>
Complex_t<T, GSL_COMPLEX>& Complex_t<T, GSL_COMPLEX>::operator+=(const T& s)
{
    *this = (*this) + s;
    return *this;
}

template<class T, class GSL_COMPLEX>
Complex_t<T, GSL_COMPLEX>& Complex_t<T, GSL_COMPLEX>::operator-=(const T& s)
{
    *this = (*this) - s;
    return *this;
}

template<class T, class GSL_COMPLEX>
Complex_t<T, GSL_COMPLEX>& Complex_t<T, GSL_COMPLEX>::operator*=(const T& s)
{
    *this = (*this) * s;
    return *this;
}

template<class T, class GSL_COMPLEX>
Complex_t<T, GSL_COMPLEX>& Complex_t<T, GSL_COMPLEX>::operator/=(const T& s)
{
    *this = (*this) / s;
    return *this;
}

template<class T, class GSL_COMPLEX>
bool Complex_t<T, GSL_COMPLEX>::operator==(const Complex_t<T, GSL_COMPLEX>& b) const
{
    return (this->re() == b.re()) && (this->im() == b.im());
}

template<class T, class GSL_COMPLEX>
bool Complex_t<T, GSL_COMPLEX>::operator!=(const Complex_t<T, GSL_COMPLEX>& b) const
{
    return !(*this == b);
}

template<class T, class G>
T Complex_t<T, G>::abs() const
{
    return std::sqrt(this->abs2());
}

template<>
inline double Complex::abs() const
{
    return gsl_complex_abs(*this->gsl_c.get());
}

template<class T, class G>
T Complex_t<T, G>::abs2() const
{
    return this->re()*this->re() + this->im()*this->im();
}

template<>
inline double Complex::abs2() const
{
    return gsl_complex_abs2(*this->gsl_c.get());
}

template<class T, class G>
T Complex_t<T, G>::logabs() const
{
    return std::log(this->abs());
}

template<>
inline double Complex::logabs() const
{
    return gsl_complex_logabs(*this->gsl_c.get());
}

template<class T, class G>
T Complex_t<T, G>::arg() const
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

template<>
inline double Complex::arg() const
{
    return gsl_complex_arg(*this->gsl_c.get());
}

template<class T, class G>
Complex_t<T, G> Complex_t<T, G>::conjugate() const
{
    Complex_t<T, G> tmp = *this;
    tmp.im() *= -1;
    return tmp;
}

template<>
inline Complex Complex::conjugate() const
{
    return Complex(gsl_complex_conjugate(*gsl_c.get()));
}

template<class T, class G>
Complex_t<T, G> Complex_t<T, G>::recipr() const
{
    Complex_t<T, G> tmp = this->conjugate();
    tmp /= tmp.abs2();
    return tmp;
}

template<>
inline Complex Complex::recipr() const
{
    return Complex(gsl_complex_inverse(*gsl_c.get()));
}

inline Complex sqrt(const double& s)
{
    return Complex(gsl_complex_sqrt_real(s));
}

template<class T, class G>
Complex_t<T, G> Complex_t<T, G>::negate() const
{
    Complex_t<T, G> tmp = *this;
    this->re() *= -1;
    this->im() *= -1;
    return tmp;
}

template<>
inline Complex Complex::negate() const
{
    return Complex(gsl_complex_negative(*gsl_c.get()));
}

inline Complex sqrt(const Complex& a)
{
    return Complex(gsl_complex_sqrt(*a.gsl_c.get()));
}

inline Complex pow(const Complex& a, const Complex& b)
{
    return Complex(gsl_complex_pow(*a.gsl_c.get(), *b.gsl_c.get()));
}

inline Complex pow(const Complex& a, const double& s)
{
    return Complex(gsl_complex_pow_real(*a.gsl_c.get(), s));
}

inline Complex exp(const Complex& a)
{
    return Complex(gsl_complex_exp(*a.gsl_c.get()));
}

inline Complex log(const Complex& a)
{
    return Complex(gsl_complex_log(*a.gsl_c.get()));
}

inline Complex log10(const Complex& a)
{
    return Complex(gsl_complex_log10(*a.gsl_c.get()));
}

inline Complex log_b(const Complex& a, const Complex& b)
{
    return Complex(gsl_complex_log_b(*a.gsl_c.get(), *b.gsl_c.get()));
}

inline Complex sin(const Complex& a)
{
    return Complex(gsl_complex_sin(*a.gsl_c.get()));
}

inline Complex cos(const Complex& a)
{
    return Complex(gsl_complex_cos(*a.gsl_c.get()));
}

inline Complex tan(const Complex& a)
{
    return Complex(gsl_complex_tan(*a.gsl_c.get()));
}

inline Complex sec(const Complex& a)
{
    return Complex(gsl_complex_sec(*a.gsl_c.get()));
}

inline Complex csc(const Complex& a)
{
    return Complex(gsl_complex_csc(*a.gsl_c.get()));
}

inline Complex cot(const Complex& a)
{
    return Complex(gsl_complex_cot(*a.gsl_c.get()));
}

inline Complex arcsin(const Complex& a)
{
    return Complex(gsl_complex_arcsin(*a.gsl_c.get()));
}

inline Complex arcsin(const double& s)
{
    return Complex(gsl_complex_arcsin_real(s));
}

inline Complex arccos(const Complex& a)
{
    return Complex(gsl_complex_arccos(*a.gsl_c.get()));
}

inline Complex arccos(const double& s)
{
    return Complex(gsl_complex_arccos_real(s));
}

inline Complex arctan(const Complex& a)
{
    return Complex(gsl_complex_arctan(*a.gsl_c.get()));
}

inline Complex arcsec(const Complex& a)
{
    return Complex(gsl_complex_arcsec(*a.gsl_c.get()));
}

inline Complex arcsec(const double& s)
{
    return Complex(gsl_complex_arcsec_real(s));
}

inline Complex arccsc(const Complex& a)
{
    return Complex(gsl_complex_arccsc(*a.gsl_c.get()));
}

inline Complex arccsc(const double& s)
{
    return Complex(gsl_complex_arccsc_real(s));
}

inline Complex arccot(const Complex& a)
{
    return Complex(gsl_complex_arccot(*a.gsl_c.get()));
}

inline Complex sinh(const Complex& a)
{
    return Complex(gsl_complex_sinh(*a.gsl_c.get()));
}

inline Complex cosh(const Complex& a)
{
    return Complex(gsl_complex_cosh(*a.gsl_c.get()));
}

inline Complex tanh(const Complex& a)
{
    return Complex(gsl_complex_tanh(*a.gsl_c.get()));
}

inline Complex sech(const Complex& a)
{
    return Complex(gsl_complex_sech(*a.gsl_c.get()));
}

inline Complex csch(const Complex& a)
{
    return Complex(gsl_complex_csch(*a.gsl_c.get()));
}

inline Complex coth(const Complex& a)
{
    return Complex(gsl_complex_coth(*a.gsl_c.get()));
}

inline Complex arcsinh(const Complex& a)
{
    return Complex(gsl_complex_arcsinh(*a.gsl_c.get()));
}

inline Complex arccosh(const Complex& a)
{
    return Complex(gsl_complex_arccosh(*a.gsl_c.get()));
}

inline Complex arccosh(const double& s)
{
    return Complex(gsl_complex_arccosh_real(s));
}

inline Complex arctanh(const Complex& a)
{
    return Complex(gsl_complex_arctanh(*a.gsl_c.get()));
}

inline Complex arctanh(const double& s)
{
    return Complex(gsl_complex_arctanh_real(s));
}

inline Complex arcsech(const Complex& a)
{
    return Complex(gsl_complex_arcsech(*a.gsl_c.get()));
}

inline Complex arccsch(const Complex& a)
{
    return Complex(gsl_complex_arccsch(*a.gsl_c.get()));
}

inline Complex arccoth(const Complex& a)
{
    return Complex(gsl_complex_arccoth(*a.gsl_c.get()));
}

template<class T, class GSL_COMPLEX>
std::string Complex_t<T, GSL_COMPLEX>::to_string() const
{
    std::string res = "";
    std::string real = std::to_string(this->re());
    std::string imag = std::to_string(this->im());
    if (this->im() > 0){
        if (this->im() == 1){
            res = real + " + i";
        }else{
            res = real + " + " + imag + "i";
        }
    }else if (this->im() < 0){
        if(this->im() == -1){
            res = real + " - i";
        }else{
            res = real + " " + imag + "i";
        }
    }else{
            res = real;
    }
    return res;
}
}
