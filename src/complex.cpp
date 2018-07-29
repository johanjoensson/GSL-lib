#include "complex.h"
#include <gsl/gsl_complex_math.h>

using namespace GSL;

Complex::Complex(double& a, double& b)
 : gsl_c(nullptr), re(), im()
{
    this->gsl_c = new gsl_complex;
    *this->gsl_c = gsl_complex_rect(a,b);
    re =  gsl_c->dat[0];
    im = gsl_c->dat[1];
}

Complex::Complex(const double& a, const double& b)
 : gsl_c(nullptr), re(), im()
{
    this->gsl_c = new gsl_complex;
    *this->gsl_c = gsl_complex_rect(a,b);
    re =  gsl_c->dat[0];
    im = gsl_c->dat[1];
}

Complex::Complex(gsl_complex& z)
 : gsl_c(nullptr), re(), im()
{
    this->gsl_c = &z;
    re = gsl_c->dat[0];
    im = gsl_c->dat[1];
}

Complex::Complex(const gsl_complex& z)
 : gsl_c(nullptr), re(), im()
{
    this->gsl_c = new gsl_complex;
    *this->gsl_c = z;
    re = gsl_c->dat[0];
    im = gsl_c->dat[1];
}

Complex::Complex(Complex& z)
 : gsl_c(nullptr), re(), im()
{
    this->gsl_c = new gsl_complex;
    *this->gsl_c = *z.gsl_c;
    this->re = this->gsl_c->dat[0];
    this->im = this->gsl_c->dat[1];
}

Complex::Complex(const Complex& z)
 : gsl_c(nullptr), re(), im()
{
    this->gsl_c = new gsl_complex;
    *this->gsl_c = *z.gsl_c;
    this->re = this->gsl_c->dat[0];
    this->im = this->gsl_c->dat[1];
}

Complex::Complex(Complex&& z)
 : gsl_c(z.gsl_c), re(), im()
{
    std::swap(re, z.re);
    std::swap(im, z.im);
    z.gsl_c = nullptr;
}

Complex::Complex()
    : Complex(0,0)
{
}

Complex::~Complex()
{
    if(gsl_c != nullptr){
        delete gsl_c;
    }
    gsl_c = nullptr;
}

Complex& Complex::operator= (const Complex& z)
{
    if(this == &z){
        return *this;
    }

    if(this->gsl_c == nullptr){
	    this->gsl_c = new gsl_complex;
    }
    *this->gsl_c = *z.gsl_c;
    this->re = this->gsl_c->dat[0];
    this->im = this->gsl_c->dat[1];

    return *this;
}

Complex& Complex::operator= (Complex&& m)
{
    gsl_complex *tmp = m.gsl_c;
    m.gsl_c = this->gsl_c;
    m.re = m.gsl_c->dat[0];
    m.im = m.gsl_c->dat[1];

    this->gsl_c = tmp;
    this->re = this->gsl_c->dat[0];
    this->im = this->gsl_c->dat[1];

    return *this;
}

std::ostream& operator << (std::ostream& os, const Complex& z)
{
    if (z.im > 0){
        if (z.im == 1){
            os << z.re << " + " << "i";
        }else{
            os << z.re << " + " << z.im << "i";
        }
    }else if (z.im < 0){
        if(z.im == -1){
            os << z.re << " - " << "i";
        }else{
            os << z.re << " " << z.im << "i";
        }
    }else{
            os << z.re;
    }
    return os;
}

Complex GSL::operator+(const Complex& a, const Complex& b)
{
    return Complex(gsl_complex_add(*a.gsl_c, *b.gsl_c));
}

Complex GSL::operator+(const Complex& a, const double& s)
{
    return Complex(gsl_complex_add_real(*a.gsl_c, s));
}

Complex GSL::operator+(const double& s, const Complex& a)
{
    return a + s;
}

Complex GSL::operator-(const Complex& a, const Complex& b)
{
    return Complex(gsl_complex_sub(*a.gsl_c, *b.gsl_c));
}

Complex GSL::operator-(const Complex& a, const double& s)
{
    return Complex(gsl_complex_sub_real(*a.gsl_c, s));
}

Complex GSL::operator-(const double& s, const Complex& a)
{
    return -(a - s);
}

Complex GSL::operator-(const Complex& a)
{
    return gsl_complex_negative(*a.gsl_c);
}

Complex GSL::operator*(const Complex& a, const Complex& b)
{
    return Complex(gsl_complex_mul(*a.gsl_c, *b.gsl_c));
}

Complex GSL::operator*(const Complex& a, const double& s)
{
    return Complex(gsl_complex_mul_real(*a.gsl_c, s));
}

Complex GSL::operator*(const double& s, const Complex& a)
{
    return a*s;
}

Complex GSL::operator/(const Complex& a, const Complex& b)
{
    return Complex(gsl_complex_div(*a.gsl_c, *b.gsl_c));
}

Complex GSL::operator/(const Complex& a, const double& s)
{
    return Complex(gsl_complex_div_real(*a.gsl_c, s));
}

Complex GSL::operator/(const double& s, const Complex& a)
{
    return gsl_complex_mul_real(gsl_complex_inverse(*a.gsl_c),s);
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
    return gsl_complex_abs(*gsl_c);
}

double Complex::abs2()
{
    return gsl_complex_abs2(*gsl_c);
}

double Complex::logabs()
{
    return gsl_complex_logabs(*gsl_c);
}

double Complex::arg()
{
    return gsl_complex_arg(*gsl_c);
}

Complex Complex::conjugate() const
{
    return Complex(gsl_complex_conjugate(*gsl_c));

}

Complex Complex::recipr() const
{
    return Complex(gsl_complex_inverse(*gsl_c));
}

Complex Complex::negate() const
{
    return Complex(gsl_complex_negative(*gsl_c));
}

Complex GSL::sqrt(const Complex& a)
{
    return Complex(gsl_complex_sqrt(*a.gsl_c));
}

Complex GSL::sqrt(const double& s)
{
    return Complex(gsl_complex_sqrt_real(s));
}

Complex GSL::pow(const Complex& a, const Complex& b)
{
    return Complex(gsl_complex_pow(*a.gsl_c, *b.gsl_c));
}

Complex GSL::pow(const Complex& a, const double& s)
{
    return Complex(gsl_complex_pow_real(*a.gsl_c, s));
}

Complex GSL::exp(const Complex& a)
{
    return Complex(gsl_complex_exp(*a.gsl_c));
}

Complex GSL::log(const Complex& a)
{
    return Complex(gsl_complex_log(*a.gsl_c));
}

Complex GSL::log10(const Complex& a)
{
    return Complex(gsl_complex_log10(*a.gsl_c));
}

Complex GSL::log_b(const Complex& a, const Complex& b)
{
    return Complex(gsl_complex_log_b(*a.gsl_c, *b.gsl_c));
}

Complex GSL::sin(const Complex& a)
{
    return Complex(gsl_complex_sin(*a.gsl_c));
}

Complex GSL::cos(const Complex& a)
{
    return Complex(gsl_complex_cos(*a.gsl_c));
}

Complex GSL::tan(const Complex& a)
{
    return Complex(gsl_complex_tan(*a.gsl_c));
}

Complex GSL::sec(const Complex& a)
{
    return Complex(gsl_complex_sec(*a.gsl_c));
}

Complex GSL::csc(const Complex& a)
{
    return Complex(gsl_complex_csc(*a.gsl_c));
}

Complex GSL::cot(const Complex& a)
{
    return Complex(gsl_complex_cot(*a.gsl_c));
}

Complex GSL::arcsin(const Complex& a)
{
    return Complex(gsl_complex_arcsin(*a.gsl_c));
}
Complex GSL::arcsin(const double& s)
{
    return Complex(gsl_complex_arcsin_real(s));
}
Complex GSL::arccos(const Complex& a)
{
    return Complex(gsl_complex_arccos(*a.gsl_c));
}
Complex GSL::arccos(const double& s)
{
    return Complex(gsl_complex_arccos_real(s));
}
Complex GSL::arctan(const Complex& a)
{
    return Complex(gsl_complex_arctan(*a.gsl_c));
}
Complex GSL::arcsec(const Complex& a)
{
    return Complex(gsl_complex_arcsec(*a.gsl_c));
}
Complex GSL::arcsec(const double& s)
{
    return Complex(gsl_complex_arcsec_real(s));
}
Complex GSL::arccsc(const Complex& a)
{
    return Complex(gsl_complex_arccsc(*a.gsl_c));
}
Complex GSL::arccsc(const double& s)
{
    return Complex(gsl_complex_arccsc_real(s));
}
Complex GSL::arccot(const Complex& a)
{
    return Complex(gsl_complex_arccot(*a.gsl_c));
}

Complex GSL::sinh(const Complex& a)
{
    return Complex(gsl_complex_sinh(*a.gsl_c));
}
Complex GSL::cosh(const Complex& a)
{
    return Complex(gsl_complex_cosh(*a.gsl_c));
}
Complex GSL::tanh(const Complex& a)
{
    return Complex(gsl_complex_tanh(*a.gsl_c));
}
Complex GSL::sech(const Complex& a)
{
    return Complex(gsl_complex_sech(*a.gsl_c));
}
Complex GSL::csch(const Complex& a)
{
    return Complex(gsl_complex_csch(*a.gsl_c));
}
Complex GSL::coth(const Complex& a)
{
    return Complex(gsl_complex_coth(*a.gsl_c));
}

Complex GSL::arcsinh(const Complex& a)
{
    return Complex(gsl_complex_arcsinh(*a.gsl_c));
}
Complex GSL::arccosh(const Complex& a)
{
    return Complex(gsl_complex_arccosh(*a.gsl_c));
}

Complex GSL::arccosh(const double& s)
{
    return Complex(gsl_complex_arccosh_real(s));
}
Complex GSL::arctanh(const Complex& a)
{
    return Complex(gsl_complex_arctanh(*a.gsl_c));
}

Complex GSL::arctanh(const double& s)
{
    return Complex(gsl_complex_arctanh_real(s));
}

Complex GSL::arcsech(const Complex& a)
{
    return Complex(gsl_complex_arcsech(*a.gsl_c));
}

Complex GSL::arccsch(const Complex& a)
{
    return Complex(gsl_complex_arccsch(*a.gsl_c));
}

Complex GSL::arccoth(const Complex& a)
{
    return Complex(gsl_complex_arccoth(*a.gsl_c));
}

/*
int main()
{
    Complex u(1.2,0);
    Complex v(1,1.5);
    Complex c(v);
    c += (v + u) / (v - u) * c ;
    std::cout << ((c.recipr() + c.recipr()).abs() == (2/c).arg()) << std::endl;
    return 0;
}
*/
