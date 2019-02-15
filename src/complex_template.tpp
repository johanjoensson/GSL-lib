#include "complex_template.h"
#include "special_functions.h"
#include <gsl/gsl_complex_math.h>
#include <cmath>

using namespace GSL;


template<>
inline GSL::Complex_t<double, gsl_complex>::Complex_t(const double& a, const double& b)
 : gsl_c(new gsl_complex)
{
    *this->gsl_c = gsl_complex_rect(a,b);
}

template<>
inline GSL::Complex_t<long double, gsl_complex_long_double>::Complex_t(const long double& a, const long double& b)
 : gsl_c(new gsl_complex_long_double)
{
    this->gsl_c->dat[0] = a;
    this->gsl_c->dat[1] = b;
}

template<>
inline GSL::Complex_t<float, gsl_complex_float>::Complex_t(const float& a, const float& b)
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
GSL::Complex_t<T, GSL_COMPLEX>::Complex_t(const GSL_COMPLEX& z)
 : gsl_c(new GSL_COMPLEX)
{
    *gsl_c = z;
}

template<class T, class GSL_COMPLEX>
T& GSL::Complex_t<T, GSL_COMPLEX>::re() const
{
	return this->gsl_c->dat[0];
}

template<class T, class GSL_COMPLEX>
T& GSL::Complex_t<T, GSL_COMPLEX>::im() const
{
	return this->gsl_c->dat[1];
}

template<class T, class GSL_COMPLEX>
GSL::Complex_t<T, GSL_COMPLEX>& GSL::Complex_t<T, GSL_COMPLEX>::operator= (const GSL::Complex_t<T, GSL_COMPLEX>& z)
{
    if(this == &z){
        return *this;
    }
    this->gsl_c = z.gsl_c;

    return *this;
}

template<class T, class GSL_COMPLEX>
GSL::Complex_t<T, GSL_COMPLEX>& GSL::Complex_t<T, GSL_COMPLEX>::operator= (GSL::Complex_t<T, GSL_COMPLEX>&& m)
{
    std::swap(this->gsl_c, m.gsl_c);
    return *this;
}

template<class T, class G>
GSL::Complex_t<T, G> GSL::Complex_t<T, G>::operator+(const GSL::Complex_t<T, G>& b) const
{
    GSL::Complex_t<T, G> res = *this;
    res.re() += b.re();
    res.im() += b.im();
    return res;
}

template<>
inline GSL::Complex GSL::Complex::operator+(const GSL::Complex& b) const
{
    return GSL::Complex(gsl_complex_add(*this->gsl_c.get(), *b.gsl_c.get()));
}

template<class T, class G>
GSL::Complex_t<T, G> GSL::Complex_t<T, G>::operator+(const T& s) const
{
    GSL::Complex_t<T, G> res = *this;
    res.re() += s;
    return res;
}

template<>
inline GSL::Complex GSL::Complex::operator+(const double& s) const
{
    return GSL::Complex(gsl_complex_add_real(*this->gsl_c.get(), s));
}

template<class T, class G>
GSL::Complex_t<T, G> GSL::Complex_t<T, G>::operator-(const GSL::Complex_t<T, G>& b) const
{
    GSL::Complex_t<T, G> res = *this;
    res.re() -= b.re();
    res.im() -= b.im();
    return res;
}

template<>
inline GSL::Complex GSL::Complex::operator-(const GSL::Complex& b) const
{
    return GSL::Complex(gsl_complex_sub(*this->gsl_c.get(), *b.gsl_c.get()));
}

template<class T, class G>
GSL::Complex_t<T, G> GSL::Complex_t<T, G>::operator-(const T& s) const
{
    GSL::Complex_t<T, G> res = *this;
    res.re() -= s;
    return res;
}

template<>
inline GSL::Complex GSL::Complex::operator-(const double& s) const
{
    return GSL::Complex(gsl_complex_sub_real(*this->gsl_c.get(), s));
}

template<class T, class G>
GSL::Complex_t<T, G> GSL::Complex_t<T, G>::operator-() const
{
    GSL::Complex_t<T, G> res = *this;
    res.re() *= -1;
    res.im() *= -1;
    return res;
}

template<>
inline GSL::Complex GSL::Complex::operator-() const
{
    return GSL::Complex(gsl_complex_negative(*this->gsl_c.get()));
}

template<class T, class G>
GSL::Complex_t<T, G> GSL::Complex_t<T, G>::operator*(const GSL::Complex_t<T, G>& b) const
{
    GSL::Complex_t<T, G> res = *this;
    res.re() = res.re()*b.re() - res.im()*b.im();
    res.im() = res.re()*b.im() + res.im()*b.re();
    return res;
}

template<>
inline GSL::Complex GSL::Complex::operator*(const GSL::Complex& b) const
{
    return GSL::Complex(gsl_complex_mul(*this->gsl_c.get(), *b.gsl_c.get()));
}

template<class T, class G>
GSL::Complex_t<T, G> GSL::Complex_t<T, G>::operator*(const T& s) const
{
    GSL::Complex_t<T, G> res = *this;
    res.re() *= s;
    res.im() *= s;
    return res;
}

template<>
inline GSL::Complex GSL::Complex::operator*(const double& s) const
{
    return GSL::Complex(gsl_complex_mul_real(*this->gsl_c.get(), s));
}

template<class T, class G>
GSL::Complex_t<T, G> GSL::Complex_t<T, G>::operator/(const GSL::Complex_t<T, G>& b) const
{
    GSL::Complex_t<T, G> res = *this;
    res *= b.conjugate()/b.abs2();
    return res;
}

template<>
inline GSL::Complex GSL::Complex::operator/(const GSL::Complex& b) const
{
    return GSL::Complex(gsl_complex_div(*this->gsl_c.get(), *b.gsl_c.get()));
}

template<class T, class G>
GSL::Complex_t<T, G> GSL::Complex_t<T, G>::operator/(const T& s) const
{
    GSL::Complex_t<T, G> res = *this;
    res.re() /= s;
    res.im() /= s;
    return res;
}

template<>
inline GSL::Complex GSL::Complex::operator/(const double& s) const
{
    return GSL::Complex(gsl_complex_div_real(*this->gsl_c.get(), s));
}

template<class T, class GSL_COMPLEX>
GSL::Complex_t<T, GSL_COMPLEX>& GSL::Complex_t<T, GSL_COMPLEX>::operator+=(const GSL::Complex_t<T, GSL_COMPLEX>& b)
{
    *this = (*this) + b;
    return *this;
}

template<class T, class GSL_COMPLEX>
GSL::Complex_t<T, GSL_COMPLEX>& GSL::Complex_t<T, GSL_COMPLEX>::operator-=(const GSL::Complex_t<T, GSL_COMPLEX>& b)
{
    *this = (*this) - b;
    return *this;
}

template<class T, class GSL_COMPLEX>
GSL::Complex_t<T, GSL_COMPLEX>& GSL::Complex_t<T, GSL_COMPLEX>::operator*=(const GSL::Complex_t<T, GSL_COMPLEX>& b)
{
    *this = (*this) * b;
    return *this;
}

template<class T, class GSL_COMPLEX>
GSL::Complex_t<T, GSL_COMPLEX>& GSL::Complex_t<T, GSL_COMPLEX>::operator/=(const GSL::Complex_t<T, GSL_COMPLEX>& b)
{
    *this = (*this) / b;
    return *this;
}

template<class T, class GSL_COMPLEX>
GSL::Complex_t<T, GSL_COMPLEX>& GSL::Complex_t<T, GSL_COMPLEX>::operator+=(const T& s)
{
    *this = (*this) + s;
    return *this;
}

template<class T, class GSL_COMPLEX>
GSL::Complex_t<T, GSL_COMPLEX>& GSL::Complex_t<T, GSL_COMPLEX>::operator-=(const T& s)
{
    *this = (*this) - s;
    return *this;
}

template<class T, class GSL_COMPLEX>
GSL::Complex_t<T, GSL_COMPLEX>& GSL::Complex_t<T, GSL_COMPLEX>::operator*=(const T& s)
{
    *this = (*this) * s;
    return *this;
}

template<class T, class GSL_COMPLEX>
GSL::Complex_t<T, GSL_COMPLEX>& GSL::Complex_t<T, GSL_COMPLEX>::operator/=(const T& s)
{
    *this = (*this) / s;
    return *this;
}

template<class T, class GSL_COMPLEX>
bool GSL::Complex_t<T, GSL_COMPLEX>::operator==(const GSL::Complex_t<T, GSL_COMPLEX>& b) const
{
    return (this->re() == b.re()) && (this->im() == b.im());
}

template<class T, class GSL_COMPLEX>
bool GSL::Complex_t<T, GSL_COMPLEX>::operator!=(const GSL::Complex_t<T, GSL_COMPLEX>& b) const
{
    return !(*this == b);
}

template<class T, class G>
T GSL::Complex_t<T, G>::abs() const
{
    return std::sqrt(this->abs2());
}

template<>
inline double GSL::Complex::abs() const
{
    return gsl_complex_abs(*this->gsl_c.get());
}

template<class T, class G>
T GSL::Complex_t<T, G>::abs2() const
{
    return this->re()*this->re() + this->im()*this->im();
}

template<>
inline double GSL::Complex::abs2() const
{
    return gsl_complex_abs2(*this->gsl_c.get());
}

template<class T, class G>
T GSL::Complex_t<T, G>::logabs() const
{
    return std::log(this->abs());
}

template<>
inline double GSL::Complex::logabs() const
{
    return gsl_complex_logabs(*this->gsl_c.get());
}

template<class T, class G>
T GSL::Complex_t<T, G>::arg() const
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
inline double GSL::Complex::arg() const
{
    return gsl_complex_arg(*this->gsl_c.get());
}

template<class T, class G>
GSL::Complex_t<T, G> GSL::Complex_t<T, G>::conjugate() const
{
    GSL::Complex_t<T, G> tmp = *this;
    tmp.im() *= -1;
    return tmp;
}

template<>
inline GSL::Complex GSL::Complex::conjugate() const
{
    return GSL::Complex(gsl_complex_conjugate(*gsl_c.get()));
}

template<class T, class G>
GSL::Complex_t<T, G> GSL::Complex_t<T, G>::recipr() const
{
    GSL::Complex_t<T, G> tmp = this->conjugate();
    tmp /= tmp.abs2();
    return tmp;
}

template<>
inline GSL::Complex GSL::Complex::recipr() const
{
    return GSL::Complex(gsl_complex_inverse(*gsl_c.get()));
}

inline GSL::Complex GSL::sqrt(const double& s)
{
    return GSL::Complex(gsl_complex_sqrt_real(s));
}

template<class T, class G>
GSL::Complex_t<T, G> GSL::Complex_t<T, G>::negate() const
{
    GSL::Complex_t<T, G> tmp = *this;
    this->re() *= -1;
    this->im() *= -1;
    return tmp;
}

template<>
inline GSL::Complex GSL::Complex::negate() const
{
    return GSL::Complex(gsl_complex_negative(*gsl_c.get()));
}

inline GSL::Complex GSL::sqrt(const GSL::Complex& a)
{
    return GSL::Complex(gsl_complex_sqrt(*a.gsl_c.get()));
}

inline GSL::Complex GSL::pow(const GSL::Complex& a, const GSL::Complex& b)
{
    return GSL::Complex(gsl_complex_pow(*a.gsl_c.get(), *b.gsl_c.get()));
}

inline GSL::Complex GSL::pow(const GSL::Complex& a, const double& s)
{
    return GSL::Complex(gsl_complex_pow_real(*a.gsl_c.get(), s));
}

inline GSL::Complex GSL::exp(const GSL::Complex& a)
{
    return GSL::Complex(gsl_complex_exp(*a.gsl_c.get()));
}

inline GSL::Complex GSL::log(const GSL::Complex& a)
{
    return GSL::Complex(gsl_complex_log(*a.gsl_c.get()));
}

inline GSL::Complex GSL::log10(const GSL::Complex& a)
{
    return GSL::Complex(gsl_complex_log10(*a.gsl_c.get()));
}

inline GSL::Complex GSL::log_b(const GSL::Complex& a, const GSL::Complex& b)
{
    return GSL::Complex(gsl_complex_log_b(*a.gsl_c.get(), *b.gsl_c.get()));
}

inline GSL::Complex GSL::sin(const GSL::Complex& a)
{
    return GSL::Complex(gsl_complex_sin(*a.gsl_c.get()));
}

inline GSL::Complex GSL::cos(const GSL::Complex& a)
{
    return GSL::Complex(gsl_complex_cos(*a.gsl_c.get()));
}

inline GSL::Complex GSL::tan(const GSL::Complex& a)
{
    return GSL::Complex(gsl_complex_tan(*a.gsl_c.get()));
}

inline GSL::Complex GSL::sec(const GSL::Complex& a)
{
    return GSL::Complex(gsl_complex_sec(*a.gsl_c.get()));
}

inline GSL::Complex GSL::csc(const GSL::Complex& a)
{
    return GSL::Complex(gsl_complex_csc(*a.gsl_c.get()));
}

inline GSL::Complex GSL::cot(const GSL::Complex& a)
{
    return GSL::Complex(gsl_complex_cot(*a.gsl_c.get()));
}

inline GSL::Complex GSL::arcsin(const GSL::Complex& a)
{
    return GSL::Complex(gsl_complex_arcsin(*a.gsl_c.get()));
}

inline GSL::Complex GSL::arcsin(const double& s)
{
    return GSL::Complex(gsl_complex_arcsin_real(s));
}

inline GSL::Complex GSL::arccos(const GSL::Complex& a)
{
    return GSL::Complex(gsl_complex_arccos(*a.gsl_c.get()));
}

inline GSL::Complex GSL::arccos(const double& s)
{
    return GSL::Complex(gsl_complex_arccos_real(s));
}

inline GSL::Complex GSL::arctan(const GSL::Complex& a)
{
    return GSL::Complex(gsl_complex_arctan(*a.gsl_c.get()));
}

inline GSL::Complex GSL::arcsec(const GSL::Complex& a)
{
    return GSL::Complex(gsl_complex_arcsec(*a.gsl_c.get()));
}

inline GSL::Complex GSL::arcsec(const double& s)
{
    return GSL::Complex(gsl_complex_arcsec_real(s));
}

inline GSL::Complex GSL::arccsc(const GSL::Complex& a)
{
    return GSL::Complex(gsl_complex_arccsc(*a.gsl_c.get()));
}

inline GSL::Complex GSL::arccsc(const double& s)
{
    return GSL::Complex(gsl_complex_arccsc_real(s));
}

inline GSL::Complex GSL::arccot(const GSL::Complex& a)
{
    return GSL::Complex(gsl_complex_arccot(*a.gsl_c.get()));
}

inline GSL::Complex GSL::sinh(const GSL::Complex& a)
{
    return GSL::Complex(gsl_complex_sinh(*a.gsl_c.get()));
}

inline GSL::Complex GSL::cosh(const GSL::Complex& a)
{
    return GSL::Complex(gsl_complex_cosh(*a.gsl_c.get()));
}

inline GSL::Complex GSL::tanh(const GSL::Complex& a)
{
    return GSL::Complex(gsl_complex_tanh(*a.gsl_c.get()));
}

inline GSL::Complex GSL::sech(const GSL::Complex& a)
{
    return GSL::Complex(gsl_complex_sech(*a.gsl_c.get()));
}

inline GSL::Complex GSL::csch(const GSL::Complex& a)
{
    return GSL::Complex(gsl_complex_csch(*a.gsl_c.get()));
}

inline GSL::Complex GSL::coth(const GSL::Complex& a)
{
    return GSL::Complex(gsl_complex_coth(*a.gsl_c.get()));
}

inline GSL::Complex GSL::arcsinh(const GSL::Complex& a)
{
    return GSL::Complex(gsl_complex_arcsinh(*a.gsl_c.get()));
}

inline GSL::Complex GSL::arccosh(const GSL::Complex& a)
{
    return GSL::Complex(gsl_complex_arccosh(*a.gsl_c.get()));
}

inline GSL::Complex GSL::arccosh(const double& s)
{
    return GSL::Complex(gsl_complex_arccosh_real(s));
}

inline GSL::Complex GSL::arctanh(const GSL::Complex& a)
{
    return GSL::Complex(gsl_complex_arctanh(*a.gsl_c.get()));
}

inline GSL::Complex GSL::arctanh(const double& s)
{
    return GSL::Complex(gsl_complex_arctanh_real(s));
}

inline GSL::Complex GSL::arcsech(const GSL::Complex& a)
{
    return GSL::Complex(gsl_complex_arcsech(*a.gsl_c.get()));
}

inline GSL::Complex GSL::arccsch(const GSL::Complex& a)
{
    return GSL::Complex(gsl_complex_arccsch(*a.gsl_c.get()));
}

inline GSL::Complex GSL::arccoth(const GSL::Complex& a)
{
    return GSL::Complex(gsl_complex_arccoth(*a.gsl_c.get()));
}

template<class T, class GSL_COMPLEX>
std::string GSL::Complex_t<T, GSL_COMPLEX>::to_string() const
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
