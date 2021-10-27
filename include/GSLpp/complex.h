#ifndef NEW_COMPLEX_GSLPP_LIB_H
#define NEW_COMPLEX_GSLPP_LIB_H

#if defined (__STDC_IEC_559_COMPLEX__) || (__STDC_IEC_60559_COMPLEX__)
// If C11 is supported, use complex as the implementation for gsl_complex
#include <complex.h>
#undef I
#endif

#include <gsl/gsl_complex.h>
#include <gsl/gsl_complex_math.h>
#include <complex>
#include "GSLpp/complex_math.h"
#include "GSLpp/complex_polynomial.h"
namespace GSL{

class Complex {
private:
    gsl_complex gsl_c_m;
public:
    Complex(const Complex&) = default;
    Complex(Complex&&) = default;
    ~Complex() = default;

    Complex& operator=(const Complex&) = default;
    Complex& operator=(Complex&&) = default;

    Complex(const double re = 0, const double im = 0);
    Complex(gsl_complex& z) : gsl_c_m(z) {}
    Complex(gsl_complex&& z) : gsl_c_m(z) {}


    /********************************************************************************************
    * Explicitly rely on the fact that C++ and C complex types have the requirement that          *
    * reinterpret_cast<T(&)[2]>(z)[0] returns the real part of z, and                                            *
    * reinterpret_cast<T(&)[2]>(z)[1] returns the imaginary part                                                 *
    * Not sure if this is a requirement for the GSL reference implementations though...              *
    ********************************************************************************************/
    friend double real(const Complex& z) {return z.real();}
    double real() const {return reinterpret_cast<const double(&)[2]>(*this)[0];}
    void real(double value) {reinterpret_cast<double(&)[2]> (*this)[0] = value;}

    friend double imag(const Complex& z) {return z.imag();}
    double imag() const {return reinterpret_cast<const double(&)[2]>(*this)[1];}
    void imag(double value) {reinterpret_cast<double(&)[2]> (*this)[1] = value;}

    friend double arg(const Complex& z);
    double arg() const {return GSL::arg(*this);}
    friend double abs(const Complex& z);
    double abs() const {return GSL::abs(*this);}
    friend double abs2(const Complex& z);
    double abs2() const {return GSL::abs2(*this);}
    friend double norm(const Complex& z);
    double norm() const {return GSL::norm(*this);}
    friend double logabs(const Complex& z);
    double logabs() const {return GSL::logabs(*this);}

    friend Complex conjugate(const Complex&);
    Complex conjugate() const {return GSL::conjugate(*this);}
    friend Complex conj(const Complex& z) {return GSL::conjugate(z);}
    Complex conj() const {return this->conjugate();}

    friend Complex GSL::negate(const Complex&);
    Complex negate() const {return GSL::negate(*this);}
    friend Complex GSL::inverse(const Complex&);
    Complex inverse() const {return GSL::inverse(*this);}
    friend Complex GSL::recipr(const Complex&);
    Complex recipr() const {return GSL::inverse(*this);}

    friend Complex operator+(const Complex&, const Complex&);
    friend Complex operator-(const Complex&, const Complex&);
    friend Complex operator*(const Complex&, const Complex&);
    friend Complex operator/(const Complex&, const Complex&);
    friend Complex operator+(const Complex&, const double&);
    friend Complex operator-(const Complex&, const double&);
    friend Complex operator*(const Complex&, const double&);
    friend Complex operator/(const Complex&, const double&);

    friend Complex operator-(const Complex& z) {return GSL::negate(z);}

    friend Complex operator+(const double& x, const Complex& z) {return z + x;}
    friend Complex operator-(const double& x, const Complex& z) {return -(z - x);}
    friend Complex operator*(const double& x, const Complex& z) {return z*x;}
    friend Complex operator/(const double& x, const Complex& z) {return GSL::inverse(z/x);}


    Complex& operator+=(const Complex& z) {*this = *this + z; return *this;}
    Complex& operator-=(const Complex& z){*this = *this - z; return *this;}
    Complex& operator*=(const Complex& z){*this = *this * z; return *this;}
    Complex& operator/=(const Complex& z){*this = *this / z; return *this;}

    Complex& operator+=(const double& c) {*this = *this + c; return *this;}
    Complex& operator-=(const double& c){*this = *this - c; return *this;}
    Complex& operator*=(const double& c){*this = *this * c; return *this;}
    Complex& operator/=(const double& c){*this = *this / c; return *this;}


    friend bool operator==(const Complex& a, const Complex& b);
    friend bool operator!=(const Complex& a, const Complex& b);

    friend Complex exp(const Complex& a);
    friend Complex sqrt(const Complex& a);
    friend Complex pow(const Complex& a, const Complex& b);
    friend Complex log(const Complex& a);
    friend Complex pow(const Complex& a, const double& s);
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

    friend Complex PolynomialInternal::evaluate_polynomial(const std::vector<double>& coeffs, const size_t order, const Complex& z);
    friend Complex PolynomialInternal::evaluate_polynomial(const std::vector<Complex>& coeffs, const size_t order, const Complex& z);


    operator gsl_complex&() {return *(&gsl_c_m);}
    operator const gsl_complex&() const {return *(&gsl_c_m);}

    operator std::complex<double>&()
    {
        return *(reinterpret_cast<std::complex<double>*> (this));
    }

    operator const std::complex<double>&() const
    {
        return *(reinterpret_cast<const std::complex<double>*> (this));
    }

    std::string to_string() const
    {
        return  (this->real() == 0 ? "" : std::to_string(this->real())) +
                (this->imag() == 0 ? "" :
                (this->imag() > 0 ? std::string(" + ") :"") +
                (this->imag() < 0 ? std::string(" - ") : "") +
                    std::to_string(std::abs(this->imag())) + std::string("i"));
    }

    friend std::ostream& operator<<(std::ostream& os, const Complex& z)
    {
        return os << z.to_string();
    };


};
}

namespace std{

    inline string to_string(const GSL::Complex& z) {return z.to_string();}

    template<>
    struct hash<GSL::Complex>{
	    size_t operator()(const GSL::Complex& z)
	    {
		    std::hash<double> h;
		    size_t res = 0;
		    res ^= h(z.real()) + 0x9e3779b9 + (res<< 6) + (res>> 2);
		    res ^= h(z.imag()) + 0x9e3779b9 + (res<< 6) + (res>> 2);
		    return res;
	    }
    };
}


#endif // NEW_COMPLEX_GSLPP_LIB_H
