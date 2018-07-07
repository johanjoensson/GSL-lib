#ifndef COMPLEX_GSL_LIB_H
#define COMPLEX_GSL_LIB_H

#include <gsl/gsl_complex.h>
#include <gsl/gsl_complex_math.h>
#include <iostream>

/**************************************************************************//**
* A class for using GSL complex numbers with a simpler interface than
* the default one.
* Also try to avoid using unnecessary amounts of memory.
*******************************************************************************/
namespace GSL{class Complex;}
// Basic arithmetic operations
// 2 Complex numbers
GSL::Complex operator+(const GSL::Complex&, const GSL::Complex&);
GSL::Complex operator-(const GSL::Complex&, const GSL::Complex&);
GSL::Complex operator*(const GSL::Complex&, const GSL::Complex&);
GSL::Complex operator/(const GSL::Complex&, const GSL::Complex&);

// 1 Complex number and one floating point number
GSL::Complex operator+(const GSL::Complex&, const double&);
GSL::Complex operator-(const GSL::Complex&, const double&);
GSL::Complex operator*(const GSL::Complex&, const double&);
GSL::Complex operator/(const GSL::Complex&, const double&);

GSL::Complex operator+(const double&, const GSL::Complex&);
GSL::Complex operator-(const double&, const GSL::Complex&);
GSL::Complex operator*(const double&, const GSL::Complex&);
GSL::Complex operator/(const double&, const GSL::Complex&);

//Negate complex numbers
GSL::Complex operator-(const GSL::Complex&);

// Equality
bool operator==(const GSL::Complex&, const GSL::Complex&);
bool operator!=(const GSL::Complex&, const GSL::Complex&);

namespace GSL{

// Elementary mathematics functions
Complex exp(const Complex& a);
Complex sqrt(const Complex& a);
Complex sqrt(const double& s);
Complex pow(const Complex& a, const Complex& b);
Complex pow(const Complex& a, const double& s);
Complex log(const Complex& a);
Complex log10(const Complex& a);
Complex log_b(const Complex& a, const Complex& b);

// Trigonometric functions
Complex sin(const Complex&a);
Complex cos(const Complex&a);
Complex tan(const Complex&a);
Complex sec(const Complex&a);
Complex csc(const Complex&a);
Complex cot(const Complex&a);

// Inverse trigonometric functions
Complex arcsin(const Complex& a);
Complex arcsin(const double& s);
Complex arccos(const Complex& a);
Complex arccos(const double& s);
Complex arctan(const Complex& a);
Complex arcsec(const Complex& a);
Complex arcsec(const double& s);
Complex arccsc(const Complex& a);
Complex arccsc(const double& s);
Complex arccot(const Complex& a);

// Hyperbolic functions
Complex sinh(const Complex& a);
Complex cosh(const Complex& a);
Complex tanh(const Complex& a);
Complex sech(const Complex& a);
Complex csch(const Complex& a);
Complex coth(const Complex& a);

// Inverse hyperbolic functions
Complex arcsinh(const Complex& a);
Complex arccosh(const Complex& a);
Complex arccosh(const double& s);
Complex arctanh(const Complex& a);
Complex arctanh(const double& s);
Complex arcsech(const Complex& a);
Complex arccsch(const Complex& a);
Complex arccoth(const Complex& a);

// Representation of complex numbers
class Complex
{
    gsl_complex gsl_c;

public:
    double re, im;
    Complex();
    Complex(double a, double b);
    Complex(gsl_complex z);
    double abs();
    double arg();
    double abs2();
    double logabs();
    Complex conjugate() const;
    Complex recipr() const;
    Complex negate() const;

    friend Complex (::operator+)(const Complex& a, const Complex& b);
    friend Complex (::operator-)(const Complex& a, const Complex& b);
    friend Complex (::operator*)(const Complex& a, const Complex&);
    friend Complex (::operator/)(const Complex& a, const Complex&);

    friend Complex (::operator+)(const Complex& a, const double& s);
    friend Complex (::operator-)(const Complex& a, const double& s);
    friend Complex (::operator*)(const Complex& a, const double& s);
    friend Complex (::operator/)(const Complex& a, const double& s);

    friend Complex (::operator+)(const double& s, const Complex& a);
    friend Complex (::operator-)(const double& s, const Complex& a);
    friend Complex (::operator*)(const double& s, const Complex& a);
    friend Complex (::operator/)(const double& s, const Complex& a);

    friend Complex (::operator-)(const Complex& a);

    Complex& (operator+=)(const Complex& b);
    Complex& (operator-=)(const Complex& b);
    Complex& (operator*=)(const Complex& b);
    Complex& (operator/=)(const Complex& b);

    Complex& (operator+=)(const double& s);
    Complex& (operator-=)(const double& s);
    Complex& (operator*=)(const double& s);
    Complex& (operator/=)(const double& s);

    friend bool (::operator==)(const Complex&, const Complex&);
    friend bool (::operator!=)(const Complex&, const Complex&);

    friend Complex exp(const Complex& a);
    friend Complex sqrt(const Complex& a);
    friend Complex pow(const Complex& a, const Complex& b);
    friend Complex pow(const Complex& a, const double& s);
    friend Complex log(const Complex& a);
    friend Complex log10(const Complex& a);
    friend Complex log_b(const Complex& a, const Complex& b);

    friend Complex sin(const Complex&a);
    friend Complex cos(const Complex&a);
    friend Complex tan(const Complex&a);
    friend Complex sec(const Complex&a);
    friend Complex csc(const Complex&a);
    friend Complex cot(const Complex&a);

    friend Complex arcsin(const Complex& a);
    friend Complex arccos(const Complex& a);
    friend Complex arctan(const Complex& a);
    friend Complex arcsec(const Complex& a);
    friend Complex arccsc(const Complex& a);
    friend Complex arccot(const Complex& a);

    friend Complex sinh(const Complex& a);
    friend Complex cosh(const Complex& a);
    friend Complex tanh(const Complex& a);
    friend Complex sech(const Complex& a);
    friend Complex csch(const Complex& a);
    friend Complex coth(const Complex& a);

    friend Complex arcsinh(const Complex& a);
    friend Complex arccosh(const Complex& a);
    friend Complex arctanh(const Complex& a);
    friend Complex arcsech(const Complex& a);
    friend Complex arccsch(const Complex& a);
    friend Complex arccoth(const Complex& a);

};
}

std::ostream& operator << (std::ostream&, const GSL::Complex&);

#endif //COMPLEX_GSL_LIB_H
