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
Complex exp(Complex& a);
Complex sqrt(Complex& a);
Complex sqrt(double& s);
Complex pow(Complex& a, Complex& b);
Complex pow(Complex& a, double& s);
Complex log(Complex& a);
Complex log10(Complex& a);
Complex log_b(Complex& a, Complex& b);

// Trigonometric functions
Complex sin(Complex&a);
Complex cos(Complex&a);
Complex tan(Complex&a);
Complex sec(Complex&a);
Complex csc(Complex&a);
Complex cot(Complex&a);

// Inverse trigonometric functions
Complex arcsin(Complex& a);
Complex arcsin(double& s);
Complex arccons(Complex& a);
Complex arccos(double& s);
Complex arctan(Complex& a);
Complex arcsec(Complex& a);
Complex arcsec(double& s);
Complex arccsc(Complex& a);
Complex arccsc(double& s);
Complex arccot(Complex& a);

// Hyperbolic functions
Complex sinh(Complex& a);
Complex cosh(Complex& a);
Complex tanh(Complex& a);
Complex sech(Complex& a);
Complex csch(Complex& a);
Complex coth(Complex& a);

// Inverse hyperbolic functions
Complex arcsinh(Complex& a);
Complex arccosh(Complex& a);
Complex arccosh(double& s);
Complex arctanh(Complex& a);
Complex arctanh(double& s);
Complex arcsech(Complex& a);
Complex arccsch(Complex& a);
Complex arccoth(Complex& a);

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

    friend Complex exp(Complex& a);
    friend Complex sqrt(Complex& a);
    friend Complex pow(Complex& a, Complex& b);
    friend Complex pow(Complex& a, double& s);
    friend Complex log(Complex& a);
    friend Complex log10(Complex& a);
    friend Complex log_b(Complex& a, Complex& b);

    friend Complex sin(Complex&a);
    friend Complex cos(Complex&a);
    friend Complex tan(Complex&a);
    friend Complex sec(Complex&a);
    friend Complex csc(Complex&a);
    friend Complex cot(Complex&a);

    friend Complex arcsin(Complex& a);
    friend Complex arccons(Complex& a);
    friend Complex arctan(Complex& a);
    friend Complex arcsec(Complex& a);
    friend Complex arccsc(Complex& a);
    friend Complex arccot(Complex& a);

    friend Complex sinh(Complex& a);
    friend Complex cosh(Complex& a);
    friend Complex tanh(Complex& a);
    friend Complex sech(Complex& a);
    friend Complex csch(Complex& a);
    friend Complex coth(Complex& a);

    friend Complex arcsinh(Complex& a);
    friend Complex arccosh(Complex& a);
    friend Complex arctanh(Complex& a);
    friend Complex arcsech(Complex& a);
    friend Complex arccsch(Complex& a);
    friend Complex arccoth(Complex& a);

};
}

std::ostream& operator << (std::ostream&, const GSL::Complex&);

#endif //COMPLEX_GSL_LIB_H
