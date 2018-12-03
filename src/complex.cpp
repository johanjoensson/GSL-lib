#include "complex.h"
#include "special_functions.h"
#include <gsl/gsl_complex_math.h>

using namespace GSL;

Complex::Complex(const double& a, const double& b)
 : gsl_c(nullptr), re(), im()
{
    this->gsl_c = std::shared_ptr<gsl_complex>(new gsl_complex);
    *this->gsl_c = gsl_complex_rect(a,b);
    re =  gsl_c->dat[0];
    im = gsl_c->dat[1];
}

void del(gsl_complex*){}
Complex::Complex(gsl_complex* z)
 : gsl_c(z, del), re(), im()
{
    re = gsl_c->dat[0];
    gsl_c->dat[1];
}

Complex::Complex(const gsl_complex& z)
 : gsl_c(nullptr), re(), im()
{
    this->gsl_c = std::shared_ptr<gsl_complex>(new gsl_complex);
    *this->gsl_c = z;
    re = gsl_c->dat[0];
    im = gsl_c->dat[1];
}

Complex::Complex(const Complex& z)
 : gsl_c(nullptr), re(), im()
{
    this->gsl_c = z.gsl_c;
    this->re = this->gsl_c->dat[0];
    this->im = this->gsl_c->dat[1];
}

Complex::Complex(Complex&& z)
 : gsl_c(nullptr), re(), im()
{
    std::swap(gsl_c, z.gsl_c);
    std::swap(re, z.re);
    std::swap(im, z.im);
}

Complex::Complex()
    : Complex(0.0,0.0)
{
}

Complex::~Complex()
{}

Complex& Complex::operator= (const Complex& z)
{
    if(this == &z){
        return *this;
    }
    this->gsl_c = z.gsl_c;
    this->re = this->gsl_c->dat[0];
    this->im = this->gsl_c->dat[1];

    return *this;
}

Complex& Complex::operator= (Complex&& m)
{
    std::swap(this->gsl_c, m.gsl_c);
    std::swap(this->re, m.re);
    std::swap(this->im, m.im);

    return *this;
}

std::ostream& GSL::operator<< (std::ostream& os, const Complex& z)
{
    os << z.to_string();
    return os;
}

Complex GSL::operator+(const Complex& a, const Complex& b)
{
    return Complex(gsl_complex_add(*a.gsl_c.get(), *b.gsl_c.get()));
}

Complex GSL::operator+(const Complex& a, const double& s)
{
    return Complex(gsl_complex_add_real(*a.gsl_c.get(), s));
}

Complex GSL::operator+(const double& s, const Complex& a)
{
    return a + s;
}

Complex GSL::operator-(const Complex& a, const Complex& b)
{
    return Complex(gsl_complex_sub(*a.gsl_c.get(), *b.gsl_c.get()));
}

Complex GSL::operator-(const Complex& a, const double& s)
{
    return Complex(gsl_complex_sub_real(*a.gsl_c.get(), s));
}

Complex GSL::operator-(const double& s, const Complex& a)
{
    return -(a - s);
}

Complex GSL::operator-(const Complex& a)
{
    return gsl_complex_negative(*a.gsl_c.get());
}

Complex GSL::operator*(const Complex& a, const Complex& b)
{
    return Complex(gsl_complex_mul(*a.gsl_c.get(), *b.gsl_c.get()));
}

Complex GSL::operator*(const Complex& a, const double& s)
{
    return Complex(gsl_complex_mul_real(*a.gsl_c.get(), s));
}

Complex GSL::operator*(const double& s, const Complex& a)
{
    return a*s;
}

Complex GSL::operator/(const Complex& a, const Complex& b)
{
    return Complex(gsl_complex_div(*a.gsl_c.get(), *b.gsl_c.get()));
}

Complex GSL::operator/(const Complex& a, const double& s)
{
    return Complex(gsl_complex_div_real(*a.gsl_c.get(), s));
}

Complex GSL::operator/(const double& s, const Complex& a)
{
    return gsl_complex_mul_real(gsl_complex_inverse(*a.gsl_c.get()),s);
}

Complex& Complex::operator+=(const Complex& b)
{
    *this = (*this) + b;
    return *this;
}

Complex& Complex::operator-=(const Complex& b)
{
    *this = (*this) - b;
    return *this;
}

Complex& Complex::operator*=(const Complex& b)
{
    *this = (*this) * b;
    return *this;
}

Complex& Complex::operator/=(const Complex& b)
{
    *this = (*this) / b;
    return *this;
}

Complex& Complex::operator+=(const double& s)
{
    *this = (*this) + s;
    return *this;
}

Complex& Complex::operator-=(const double& s)
{
    *this = (*this) - s;
    return *this;
}

Complex& Complex::operator*=(const double& s)
{
    *this = (*this) * s;
    return *this;
}

Complex& Complex::operator/=(const double& s)
{
    *this = (*this) / s;
    return *this;
}

bool GSL::operator==(const Complex& a, const Complex& b)
{
    return (a.re == b.re) && (a.im == b.im);
}

bool GSL::operator!=(const Complex& a, const Complex& b)
{
    return !(a == b);
}

double Complex::abs()
{
    return gsl_complex_abs(*gsl_c.get());
}

double Complex::abs2()
{
    return gsl_complex_abs2(*gsl_c.get());
}

double Complex::logabs()
{
    return gsl_complex_logabs(*gsl_c.get());
}

double Complex::arg()
{
    return gsl_complex_arg(*gsl_c.get());
}

Complex Complex::conjugate() const
{
    return Complex(gsl_complex_conjugate(*gsl_c.get()));

}

Complex Complex::recipr() const
{
    return Complex(gsl_complex_inverse(*gsl_c.get()));
}

Complex Complex::negate() const
{
    return Complex(gsl_complex_negative(*gsl_c.get()));
}

Complex GSL::sqrt(const Complex& a)
{
    return Complex(gsl_complex_sqrt(*a.gsl_c.get()));
}

Complex GSL::sqrt(const double& s)
{
    return Complex(gsl_complex_sqrt_real(s));
}

Complex GSL::pow(const Complex& a, const Complex& b)
{
    return Complex(gsl_complex_pow(*a.gsl_c.get(), *b.gsl_c.get()));
}

Complex GSL::pow(const Complex& a, const double& s)
{
    return Complex(gsl_complex_pow_real(*a.gsl_c.get(), s));
}

Complex GSL::exp(const Complex& a)
{
    return Complex(gsl_complex_exp(*a.gsl_c.get()));
}

Complex GSL::log(const Complex& a)
{
    return Complex(gsl_complex_log(*a.gsl_c.get()));
}

Complex GSL::log10(const Complex& a)
{
    return Complex(gsl_complex_log10(*a.gsl_c.get()));
}

Complex GSL::log_b(const Complex& a, const Complex& b)
{
    return Complex(gsl_complex_log_b(*a.gsl_c.get(), *b.gsl_c.get()));
}

Complex GSL::sin(const Complex& a)
{
    return Complex(gsl_complex_sin(*a.gsl_c.get()));
}

Complex GSL::cos(const Complex& a)
{
    return Complex(gsl_complex_cos(*a.gsl_c.get()));
}

Complex GSL::tan(const Complex& a)
{
    return Complex(gsl_complex_tan(*a.gsl_c.get()));
}

Complex GSL::sec(const Complex& a)
{
    return Complex(gsl_complex_sec(*a.gsl_c.get()));
}

Complex GSL::csc(const Complex& a)
{
    return Complex(gsl_complex_csc(*a.gsl_c.get()));
}

Complex GSL::cot(const Complex& a)
{
    return Complex(gsl_complex_cot(*a.gsl_c.get()));
}

Complex GSL::arcsin(const Complex& a)
{
    return Complex(gsl_complex_arcsin(*a.gsl_c.get()));
}
Complex GSL::arcsin(const double& s)
{
    return Complex(gsl_complex_arcsin_real(s));
}
Complex GSL::arccos(const Complex& a)
{
    return Complex(gsl_complex_arccos(*a.gsl_c.get()));
}
Complex GSL::arccos(const double& s)
{
    return Complex(gsl_complex_arccos_real(s));
}
Complex GSL::arctan(const Complex& a)
{
    return Complex(gsl_complex_arctan(*a.gsl_c.get()));
}
Complex GSL::arcsec(const Complex& a)
{
    return Complex(gsl_complex_arcsec(*a.gsl_c.get()));
}
Complex GSL::arcsec(const double& s)
{
    return Complex(gsl_complex_arcsec_real(s));
}
Complex GSL::arccsc(const Complex& a)
{
    return Complex(gsl_complex_arccsc(*a.gsl_c.get()));
}
Complex GSL::arccsc(const double& s)
{
    return Complex(gsl_complex_arccsc_real(s));
}
Complex GSL::arccot(const Complex& a)
{
    return Complex(gsl_complex_arccot(*a.gsl_c.get()));
}

Complex GSL::sinh(const Complex& a)
{
    return Complex(gsl_complex_sinh(*a.gsl_c.get()));
}
Complex GSL::cosh(const Complex& a)
{
    return Complex(gsl_complex_cosh(*a.gsl_c.get()));
}
Complex GSL::tanh(const Complex& a)
{
    return Complex(gsl_complex_tanh(*a.gsl_c.get()));
}
Complex GSL::sech(const Complex& a)
{
    return Complex(gsl_complex_sech(*a.gsl_c.get()));
}
Complex GSL::csch(const Complex& a)
{
    return Complex(gsl_complex_csch(*a.gsl_c.get()));
}
Complex GSL::coth(const Complex& a)
{
    return Complex(gsl_complex_coth(*a.gsl_c.get()));
}

Complex GSL::arcsinh(const Complex& a)
{
    return Complex(gsl_complex_arcsinh(*a.gsl_c.get()));
}
Complex GSL::arccosh(const Complex& a)
{
    return Complex(gsl_complex_arccosh(*a.gsl_c.get()));
}

Complex GSL::arccosh(const double& s)
{
    return Complex(gsl_complex_arccosh_real(s));
}
Complex GSL::arctanh(const Complex& a)
{
    return Complex(gsl_complex_arctanh(*a.gsl_c.get()));
}

Complex GSL::arctanh(const double& s)
{
    return Complex(gsl_complex_arctanh_real(s));
}

Complex GSL::arcsech(const Complex& a)
{
    return Complex(gsl_complex_arcsech(*a.gsl_c.get()));
}

Complex GSL::arccsch(const Complex& a)
{
    return Complex(gsl_complex_arccsch(*a.gsl_c.get()));
}

Complex GSL::arccoth(const Complex& a)
{
    return Complex(gsl_complex_arccoth(*a.gsl_c.get()));
}

double abs(GSL::Complex z)
{
    return z.abs();
}

std::string Complex::to_string() const
{
    std::string res = "";
    std::string real = std::to_string(this->re);
    std::string imag = std::to_string(this->im);
    if (this->im > 0){
        if (this->im == 1){
            res = real + " + i";
        }else{
            res = real + " + " + imag + "i";
        }
    }else if (this->im < 0){
        if(this->im == -1){
            res = real + " - i";
        }else{
            res = real + " " + imag + "i";
        }
    }else{
            res = real;
    }
    return res;
}
