#include <iostream>
#include "GSLpp/complex_float.h"

using namespace GSL;

GSL::Complex_float::Complex_float(const float re, const float im)
 : gsl_c_m()
{
    this->real(re);
    this->imag(im);
}

bool GSL::operator==(const Complex_float& a, const Complex_float& b)
{
    return a.real() == b.real() && a.imag() == b.imag();
}

bool GSL::operator!=(const Complex_float& a, const Complex_float& b)
{
    return !(a == b);
}
