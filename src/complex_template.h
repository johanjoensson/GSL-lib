#ifndef COMPLEX_GSL_LIB_H
#define COMPLEX_GSL_LIB_H
#include "vector_template.h"
#include "matrix_template.h"
#include <gsl/gsl_complex.h>
#include <gsl/gsl_vector.h>
#include <gsl/gsl_matrix.h>
#include <iostream>
#include <memory>
#include <vector>

/**************************************************************************//***
* A class for using GSL complex numbers with a simpler interface than          *
* the default one.                                                             *
* Also try to avoid using unnecessary amounts of memory.                       *
*******************************************************************************/
namespace GSL{

    class Permutation;
    template<class T, class GSL_COMPLEX> class Complex_t;

    using Complex =  Complex_t<double, gsl_complex>;
    using Complex_ld = Complex_t<long double, gsl_complex_long_double>;
    using Complex_f = Complex_t<float, gsl_complex_float>;

    namespace PolynomialInternal{
        Complex evaluate_polynomial(const std::vector<double>& coeffs, const size_t order, const Complex& z);
        Complex evaluate_polynomial(const std::vector<Complex>& coeffs, const size_t order, const Complex& z);
    }

// Representation of complex numbers
template<typename T, typename GSL_COMPLEX>
class Complex_t
{
private:
    friend class Vector_t<Complex, gsl_vector_complex, std::allocator<gsl_complex>>;
    friend class Vector_t<Complex_ld, gsl_vector_complex_long_double, std::allocator<gsl_complex_long_double>>;
    friend class Vector_t<Complex_f, gsl_vector_complex_float, std::allocator<gsl_complex_float>>;

    // template<class GSL_VEC>
    // friend class Vector_t<Complex_t, GSL_VEC, std::allocator<GSL_COMPLEX>>;

    friend class Matrix_t<Complex, gsl_matrix_complex,
        gsl_vector_complex, std::allocator<gsl_complex>>;
    friend class Matrix_t<Complex_ld, gsl_matrix_complex_long_double,
        gsl_vector_complex_long_double, std::allocator<gsl_complex_long_double>>;
    friend class Matrix_t<Complex_f, gsl_matrix_complex_float,
        gsl_vector_complex_float, std::allocator<gsl_complex_float>>;
    // template<class GSL_VEC, class GSL_MAT>
    // friend class Matrix_t<Complex_t, GSL_VEC, GSL_MAT, std::allocator<GSL_COMPLEX>>;

    std::shared_ptr<GSL_COMPLEX> gsl_c;
public:
    Complex_t(const T& a = 0, const T& b = 0);
    Complex_t(const GSL_COMPLEX& z);
    Complex_t(const Complex_t& ) = default;
    Complex_t(Complex_t&& ) = default;
    ~Complex_t() = default;

    Complex_t& operator=(const Complex_t& z);
    Complex_t& operator=(Complex_t&& z);

    operator GSL_COMPLEX() const { return *this->gsl_c;};

    T& re() const;
    T& im() const;
    T abs() const;
    T arg() const;
    T abs2() const;
    T logabs() const;
    Complex_t conjugate() const;
    Complex_t recipr() const;
    Complex_t negate() const;

    Complex_t operator+(const Complex_t& b) const;
    Complex_t operator-(const Complex_t& b) const;
    Complex_t operator*(const Complex_t&) const;
    Complex_t operator/(const Complex_t&) const;

    Complex_t operator+(const T& s) const;
    Complex_t operator-(const T& s) const;
    Complex_t operator*(const T& s) const;
    Complex_t operator/(const T& s) const;

    friend Complex_t (operator+)(const T& s, const Complex_t& a)
    {
        return a + s;
    };
    friend Complex_t operator-(const T& s, const Complex_t& a)
    {
        return -(a-s);
    };
    friend Complex_t operator*(const T& s, const Complex_t& a)
    {
        return a*s;
    };

    friend Complex_t operator/(const T& s, const Complex_t& a)
    {
        return a.recipr()*s;
    };

    Complex_t operator-() const;

    Complex_t& operator+=(const Complex_t& b);
    Complex_t& operator-=(const Complex_t& b);
    Complex_t& operator*=(const Complex_t& b);
    Complex_t& operator/=(const Complex_t& b);

    Complex_t& operator+=(const T& s);
    Complex_t& operator-=(const T& s);
    Complex_t& operator*=(const T& s);
    Complex_t& operator/=(const T& s);

    bool operator==(const Complex_t&) const;
    bool operator!=(const Complex_t&) const;

    std::string to_string() const;
    friend std::ostream& operator<<(std::ostream& os, const Complex_t& z)
    {
        return os << z.to_string();
    };

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
    friend Complex PolynomialInternal::evaluate_polynomial(const std::vector<double>& coeffs, const size_t order, const Complex& z);
    friend Complex PolynomialInternal::evaluate_polynomial(const std::vector<Complex>& coeffs, const size_t order, const Complex& z);
};

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

#endif //COMPLEX_GSL_LIB_H
