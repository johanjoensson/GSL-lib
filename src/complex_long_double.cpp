#include <iostream>
#include "GSLpp/complex_long_double.h"

using namespace GSL;

GSL::Complex_long_double::Complex_long_double(const long double re, const long double im)
 : gsl_c_m()
{
    this->real(re);
    this->imag(im);
}

bool GSL::operator==(const Complex_long_double& a, const Complex_long_double& b)
{
    return a.real() == b.real() && a.imag() == b.imag();
}

bool GSL::operator!=(const Complex_long_double& a, const Complex_long_double& b)
{
    return !(a == b);
}
