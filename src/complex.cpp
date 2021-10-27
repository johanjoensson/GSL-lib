#include <iostream>
#include "GSLpp/complex.h"

using namespace GSL;

GSL::Complex::Complex(const double re, const double im)
 : gsl_c_m(gsl_complex_rect(re, im))
{}

double GSL::arg(const Complex& z)
{
    return gsl_complex_arg(z.gsl_c_m);
}

double GSL::abs(const Complex& z)
{
    return gsl_complex_abs(z.gsl_c_m);
}

double GSL::abs2(const Complex& z)
{
    return gsl_complex_abs2(z.gsl_c_m);
}

double GSL::norm(const Complex& z)
{
    return abs2(z);
}

double GSL::logabs(const Complex& z)
{
    return gsl_complex_logabs(z.gsl_c_m);
}

Complex GSL::conjugate(const Complex& z)
{
    return gsl_complex_conjugate(z.gsl_c_m);
}

Complex GSL::negate(const Complex& z)
{
    return gsl_complex_negative(z.gsl_c_m);
}

Complex GSL::inverse(const Complex& z)
{
    return gsl_complex_inverse(z.gsl_c_m);
}

Complex GSL::recipr(const Complex& z)
{
    return inverse(z);
}

Complex GSL::operator+(const Complex& a, const Complex& b)
{
    return gsl_complex_add(a.gsl_c_m, b.gsl_c_m);
}
Complex GSL::operator-(const Complex& a, const Complex& b)
{
    return gsl_complex_sub(a.gsl_c_m, b.gsl_c_m);
}
Complex GSL::operator*(const Complex& a, const Complex& b)
{
    return gsl_complex_mul(a.gsl_c_m, b.gsl_c_m);
}
Complex GSL::operator/(const Complex& a, const Complex& b)
{
    return gsl_complex_div(a.gsl_c_m, b.gsl_c_m);
}
Complex GSL::operator+(const Complex& a, const double& x)
{
    return gsl_complex_add_real(a.gsl_c_m, x);
}
Complex GSL::operator-(const Complex& a, const double& x)
{
    return gsl_complex_sub_real(a.gsl_c_m, x);
}
Complex GSL::operator*(const Complex& a, const double& x)
{
    return gsl_complex_mul_real(a.gsl_c_m, x);
}
Complex GSL::operator/(const Complex& a, const double& x)
{
    return gsl_complex_div_real(a.gsl_c_m, x);
}

bool GSL::operator==(const Complex& a, const Complex& b)
{
    return a.real() == b.real() && a.imag() == b.imag();
}

bool GSL::operator!=(const Complex& a, const Complex& b)
{
    return !(a == b);
}

Complex GSL::sqrt(const double& x)
{
    return gsl_complex_sqrt_real(x);
}

Complex GSL::exp(const Complex& z)
{
    return gsl_complex_exp(z.gsl_c_m);
}
Complex GSL::sqrt(const Complex& z)
{
    return gsl_complex_sqrt(z.gsl_c_m);
}
Complex GSL::pow(const Complex& z, const Complex& a)
{
    return gsl_complex_pow(z.gsl_c_m, a.gsl_c_m);
}
Complex GSL::pow(const Complex& z, const double& x)
{
    return gsl_complex_pow_real(z.gsl_c_m, x);
}
Complex GSL::log(const Complex& z)
{
    return gsl_complex_log(z.gsl_c_m);
}
Complex GSL::log10(const Complex& z)
{
    return gsl_complex_log10(z.gsl_c_m);
}
Complex GSL::log_b(const Complex& z, const Complex& b)
{
    return gsl_complex_log_b(z.gsl_c_m, b.gsl_c_m);
}

Complex GSL::sin(const Complex& z)
{
    return gsl_complex_sin(z.gsl_c_m);
}
Complex GSL::cos(const Complex& z)
{
    return gsl_complex_cos(z.gsl_c_m);
}
Complex GSL::tan(const Complex& z)
{
    return gsl_complex_tan(z.gsl_c_m);
}
Complex GSL::sec(const Complex& z)
{
    return gsl_complex_sec(z.gsl_c_m);
}
Complex GSL::csc(const Complex& z)
{
    return gsl_complex_csc(z.gsl_c_m);
}
Complex GSL::cot(const Complex& z)
{
    return gsl_complex_cot(z.gsl_c_m);
}

Complex GSL::arcsin(const Complex& z)
{
    return gsl_complex_arcsin(z.gsl_c_m);
}
Complex GSL::arcsin(const double& x)
{
    return gsl_complex_arcsin_real(x);
}
Complex GSL::arccos(const Complex& z)
{
    return gsl_complex_arccos(z.gsl_c_m);
}
Complex GSL::arccos(const double& x)
{
    return gsl_complex_arccos_real(x);
}
Complex GSL::arctan(const Complex& z)
{
    return gsl_complex_arctan(z.gsl_c_m);
}
Complex GSL::arcsec(const Complex& z)
{
    return gsl_complex_arcsec(z.gsl_c_m);
}
Complex GSL::arcsec(const double& x)
{
    return gsl_complex_arcsec_real(x);
}
Complex GSL::arccsc(const Complex& z)
{
    return gsl_complex_arccsc(z.gsl_c_m);
}
Complex GSL::arccsc(const double& x)
{
    return gsl_complex_arccsc_real(x);
}
Complex GSL::arccot(const Complex& z)
{
    return gsl_complex_arccot(z.gsl_c_m);
}

Complex GSL::sinh(const Complex& z)
{
    return gsl_complex_sinh(z.gsl_c_m);
}
Complex GSL::cosh(const Complex& z)
{
    return gsl_complex_cosh(z.gsl_c_m);
}
Complex GSL::tanh(const Complex& z)
{
    return gsl_complex_tanh(z.gsl_c_m);
}
Complex GSL::sech(const Complex& z)
{
    return gsl_complex_sech(z.gsl_c_m);
}
Complex GSL::csch(const Complex& z)
{
    return gsl_complex_csch(z.gsl_c_m);
}
Complex GSL::coth(const Complex& z)
{
    return gsl_complex_coth(z.gsl_c_m);
}

Complex GSL::arcsinh(const Complex& z)
{
    return gsl_complex_arcsinh(z.gsl_c_m);
}
Complex GSL::arccosh(const Complex& z)
{
    return gsl_complex_arccosh(z.gsl_c_m);
}
Complex GSL::arccosh(const double& x)
{
    return gsl_complex_arccosh_real(x);
}
Complex GSL::arctanh(const Complex& z)
{
    return gsl_complex_arctanh(z.gsl_c_m);
}
Complex GSL::arctanh(const double& x)
{
    return gsl_complex_arctanh_real(x);
}
Complex GSL::arcsech(const Complex& z)
{
    return gsl_complex_arcsech(z.gsl_c_m);
}
Complex GSL::arccsch(const Complex& z)
{
    return gsl_complex_arccsch(z.gsl_c_m);
}
Complex GSL::arccoth(const Complex& z)
{
    return gsl_complex_arccoth(z.gsl_c_m);
}

#if 0
int main()
{
    Complex a(1.0, 2.0), c(2.5, 1.0);

    std::complex<double> b = a;

    b.imag(b.imag() + 1);

    std::cout << a << "\n";
    std::cout << b << "\n";
    std::cout << "arg( " << a << ") = " << arg(a) << "\n";
    std::cout << "a + c = (" << a << ") + (" << c << ") = " << a + c << "\n";
    return 0;
}
#endif
