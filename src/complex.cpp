#include "complex.h"

using namespace GSL;

Complex::Complex(double a, double b)
{
    gsl_c = gsl_complex_rect(a,b);
    re = gsl_c.dat[0];
    im = gsl_c.dat[1];
}

Complex::Complex(gsl_complex z)
    : Complex(GSL_REAL(z), GSL_IMAG(z))
{
}

Complex::Complex()
    : Complex(0,0)
{
}

std::ostream& operator << (std::ostream& os, const Complex& z)
{
    if (z.im > 0){
        if (z.im == 1){
            os << z.re << " + " << "i";
        }else{
            os << z.re << " + " << z.im << "i";
        }
    }else{
        if(z.im == -1){
            os << z.re << " - " << "i";
        }else{
            os << z.re << " " << z.im << "i";
        }
    }
    return os;
}

Complex operator+(const Complex& a, const Complex& b)
{
    return Complex(gsl_complex_add(a.gsl_c, b.gsl_c));
}

Complex operator+(const Complex& a, const double& s)
{
    return Complex(gsl_complex_add_real(a.gsl_c, s));
}

Complex operator+(const double& s, const Complex& a)
{
    return a + s;
}

Complex operator-(const Complex& a, const Complex& b)
{
    return Complex(gsl_complex_sub(a.gsl_c, b.gsl_c));
}

Complex operator-(const Complex& a, const double& s)
{
    return Complex(gsl_complex_sub_real(a.gsl_c, s));
}

Complex operator-(const double& s, const Complex& a)
{
    return -(a - s);
}

Complex operator-(const Complex& a)
{
    return gsl_complex_negative(a.gsl_c);
}

Complex operator*(const Complex& a, const Complex& b)
{
    return Complex(gsl_complex_mul(a.gsl_c, b.gsl_c));
}

Complex operator*(const Complex& a, const double& s)
{
    return Complex(gsl_complex_mul_real(a.gsl_c, s));
}

Complex operator*(const double& s, const Complex& a)
{
    return a*s;
}

Complex operator/(const Complex& a, const Complex& b)
{
    return Complex(gsl_complex_div(a.gsl_c, b.gsl_c));
}

Complex operator/(const Complex& a, const double& s)
{
    return Complex(gsl_complex_div_real(a.gsl_c, s));
}

Complex operator/(const double& s, const Complex& a)
{
    return gsl_complex_mul_real(gsl_complex_inverse(a.gsl_c),s);
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

bool operator==(const Complex& a, const Complex& b)
{
    return (a.re == b.re) && (a.im == b.im);
}

bool operator!=(const Complex& a, const Complex& b)
{
    return !(a == b);
}

double Complex::abs()
{
    return gsl_complex_abs(gsl_c);
}

double Complex::abs2()
{
    return gsl_complex_abs2(gsl_c);
}

double Complex::logabs()
{
    return gsl_complex_logabs(gsl_c);
}

double Complex::arg()
{
    return gsl_complex_arg(gsl_c);
}

Complex Complex::conjugate() const
{
    return Complex(gsl_complex_conjugate(gsl_c));

}

Complex Complex::recipr() const
{
    return Complex(gsl_complex_inverse(gsl_c));
}

Complex Complex::negate() const
{
    return Complex(gsl_complex_negative(gsl_c));
}

Complex GSL::sqrt(Complex& a)
{
    return Complex(gsl_complex_sqrt(a.gsl_c));
}

Complex GSL::sqrt(double& s)
{
    return Complex(gsl_complex_sqrt_real(s));
}

Complex GSL::pow(Complex& a, Complex& b)
{
    return Complex(gsl_complex_pow(a.gsl_c, b.gsl_c));
}

Complex GSL::pow(Complex& a, double& s)
{
    return Complex(gsl_complex_pow_real(a.gsl_c, s));
}

Complex GSL::log(Complex& a)
{
    return Complex(gsl_complex_log(a.gsl_c));
}

Complex GSL::log10(Complex& a)
{
    return Complex(gsl_complex_log10(a.gsl_c));
}

Complex GSL::log_b(Complex& a, Complex& b)
{
    return Complex(gsl_complex_log_b(a.gsl_c, b.gsl_c));
}

Complex GSL::sin(Complex& a)
{
    return Complex(gsl_complex_sin(a.gsl_c));
}

Complex GSL::cos(Complex& a)
{
    return Complex(gsl_complex_cos(a.gsl_c));
}

Complex GSL::tan(Complex& a)
{
    return Complex(gsl_complex_tan(a.gsl_c));
}

Complex GSL::sec(Complex& a)
{
    return Complex(gsl_complex_sec(a.gsl_c));
}

Complex GSL::csc(Complex& a)
{
    return Complex(gsl_complex_csc(a.gsl_c));
}

Complex GSL::cot(Complex& a)
{
    return Complex(gsl_complex_cot(a.gsl_c));
}

Complex GSL::arcsin(Complex& a)
{
    return Complex(gsl_complex_arcsin(a.gsl_c));
}
Complex GSL::arcsin(double& s)
{
    return Complex(gsl_complex_arcsin_real(s));
}
Complex GSL::arccons(Complex& a)
{
    return Complex(gsl_complex_arccos(a.gsl_c));
}
Complex GSL::arccos(double& s)
{
    return Complex(gsl_complex_arccos_real(s));
}
Complex GSL::arctan(Complex& a)
{
    return Complex(gsl_complex_arctan(a.gsl_c));
}
Complex GSL::arcsec(Complex& a)
{
    return Complex(gsl_complex_arcsec(a.gsl_c));
}
Complex GSL::arcsec(double& s)
{
    return Complex(gsl_complex_arcsec_real(s));
}
Complex GSL::arccsc(Complex& a)
{
    return Complex(gsl_complex_arccsc(a.gsl_c));
}
Complex GSL::arccsc(double& s)
{
    return Complex(gsl_complex_arccsc_real(s));
}
Complex GSL::arccot(Complex& a)
{
    return Complex(gsl_complex_arccot(a.gsl_c));
}

Complex GSL::sinh(Complex& a)
{
    return Complex(gsl_complex_sinh(a.gsl_c));
}
Complex GSL::cosh(Complex& a)
{
    return Complex(gsl_complex_cosh(a.gsl_c));
}
Complex GSL::tanh(Complex& a)
{
    return Complex(gsl_complex_tanh(a.gsl_c));
}
Complex GSL::sech(Complex& a)
{
    return Complex(gsl_complex_sech(a.gsl_c));
}
Complex GSL::csch(Complex& a)
{
    return Complex(gsl_complex_csch(a.gsl_c));
}
Complex GSL::coth(Complex& a)
{
    return Complex(gsl_complex_coth(a.gsl_c));
}

Complex GSL::arcsinh(Complex& a)
{
    return Complex(gsl_complex_arcsinh(a.gsl_c));
}
Complex GSL::arccosh(Complex& a)
{
    return Complex(gsl_complex_arccosh(a.gsl_c));
}

Complex GSL::arccosh(double& s)
{
    return Complex(gsl_complex_arccosh_real(s));
}
Complex GSL::arctanh(Complex& a)
{
    return Complex(gsl_complex_arctanh(a.gsl_c));
}

Complex GSL::arctanh(double& s)
{
    return Complex(gsl_complex_arctanh_real(s));
}

Complex GSL::arcsech(Complex& a)
{
    return Complex(gsl_complex_arcsech(a.gsl_c));
}

Complex GSL::arccsch(Complex& a)
{
    return Complex(gsl_complex_arccsch(a.gsl_c));
}

Complex GSL::arccoth(Complex& a)
{
    return Complex(gsl_complex_arccoth(a.gsl_c));
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
