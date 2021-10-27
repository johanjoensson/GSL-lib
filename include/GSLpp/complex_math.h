#ifndef NEW_COMPLEX_MATH_GSLPP_LIB_H
#define NEW_COMPLEX_MATH_GSLPP_LIB_H

namespace GSL {

class Complex;

Complex operator+(const Complex&, const Complex&);
Complex operator-(const Complex&, const Complex&);
Complex operator*(const Complex&, const Complex&);
Complex operator/(const Complex&, const Complex&);
Complex operator+(const Complex&, const double&);
Complex operator-(const Complex&, const double&);
Complex operator*(const Complex&, const double&);
Complex operator/(const Complex&, const double&);

bool operator==(const Complex& a, const Complex& b);
bool operator!=(const Complex& a, const Complex& b);

double arg(const Complex&);
double abs(const Complex&);
double abs2(const Complex&);
double norm(const Complex&);
double logabs(const Complex&);

Complex conjugate(const Complex&);
Complex conj(const Complex&);
Complex negate(const Complex&);
Complex inverse(const Complex&);
Complex recipr(const Complex&);

Complex sqrt(const double& a);
Complex exp(const Complex& a);
Complex sqrt(const Complex& a);
Complex pow(const Complex& a, const Complex& b);
Complex pow(const Complex& a, const double& s);
Complex log(const Complex& a);
Complex log10(const Complex& a);
Complex log_b(const Complex& a, const Complex& b);

Complex sin(const Complex&a);
Complex cos(const Complex&a);
Complex tan(const Complex&a);
Complex sec(const Complex&a);
Complex csc(const Complex&a);
Complex cot(const Complex&a);

Complex arcsin(const Complex& a);
Complex arcsin(const double& a);
Complex arccos(const Complex& a);
Complex arccos(const double& a);
Complex arctan(const Complex& a);
Complex arcsec(const Complex& a);
Complex arcsec(const double& a);
Complex arccsc(const Complex& a);
Complex arccsc(const double& a);
Complex arccot(const Complex& a);

Complex sinh(const Complex& a);
Complex cosh(const Complex& a);
Complex tanh(const Complex& a);
Complex sech(const Complex& a);
Complex csch(const Complex& a);
Complex coth(const Complex& a);

Complex arcsinh(const Complex& a);
Complex arccosh(const Complex& a);
Complex arccosh(const double& a);
Complex arctanh(const Complex& a);
Complex arctanh(const double& a);
Complex arcsech(const Complex& a);
Complex arccsch(const Complex& a);
Complex arccoth(const Complex& a);

}

#endif // NEW_COMPLEX_MATH_GSLPP_LIB_H
