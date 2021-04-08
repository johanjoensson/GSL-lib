#ifndef COMPLEX_GSLPP_LIB_H
#define COMPLEX_GSLPP_LIB_H
#include <iostream>
#include <memory>
#include <vector>
#include <cmath>
#include <gsl/gsl_complex.h>
#include <gsl/gsl_complex_math.h>
#include <gsl/gsl_vector.h>
#include <gsl/gsl_matrix.h>

/**************************************************************************//***
* A class for using GSL complex numbers with a simpler interface than          *
* the default one.                                                             *
* Also try to avoid using unnecessary amounts of memory.                       *
*******************************************************************************/
namespace GSL{

    template<typename T, typename GSL_COMPLEX> class Complex_t;
    using Complex = Complex_t<double, gsl_complex>;
    using Complex_f = Complex_t<float, gsl_complex_float>;
    using Complex_ld = Complex_t<long double, gsl_complex_long_double>;

    template<class D, class GSL_MAT, class GSL_VEC, class A> class Matrix_t;
    template<class D, class GSL_VEC, class A> class Vector_t;

    namespace PolynomialInternal{
        Complex evaluate_polynomial(const std::vector<double>& coeffs, const size_t order, const Complex& z);
        Complex evaluate_polynomial(const std::vector<Complex>& coeffs, const size_t order, const Complex& z);
    }

// Representation of complex numbers
template<typename T, typename GSL_COMPLEX>
class Complex_t
{
private:

    friend Vector_t<Complex_t<double, gsl_complex>, gsl_vector_complex, std::allocator<gsl_complex>>;
    friend Vector_t<Complex_t<long double, gsl_complex_long_double>, gsl_vector_complex_long_double, std::allocator<gsl_complex_long_double>>;
    friend Vector_t<Complex_t<float, gsl_complex_float>, gsl_vector_complex_float, std::allocator<gsl_complex_float>>;

    friend Matrix_t<GSL::Complex_t<double, gsl_complex>, gsl_matrix_complex, gsl_vector_complex, std::allocator<gsl_complex>>;
    friend Matrix_t<GSL::Complex_t<long double, gsl_complex_long_double>, gsl_matrix_complex_long_double,
        gsl_vector_complex_long_double, std::allocator<gsl_complex_long_double>>;
    friend Matrix_t<GSL::Complex_t<float, gsl_complex_float>, gsl_matrix_complex_float,
        gsl_vector_complex_float, std::allocator<gsl_complex_float>>;
    std::shared_ptr<GSL_COMPLEX> gsl_c;
public:
    Complex_t(const T& a = 0, const T& b = 0);
    Complex_t(const GSL_COMPLEX& z) : Complex_t(){*gsl_c = z;}
    Complex_t(const std::shared_ptr<GSL_COMPLEX>& z);
    Complex_t(const Complex_t& ) = default;
    Complex_t(Complex_t&& ) = default;
    ~Complex_t() = default;

    Complex_t& operator=(const Complex_t& z) = default;
    Complex_t& operator=(Complex_t&& z) = default;

    operator GSL_COMPLEX() const {return *gsl_c;}

    T re() const {return gsl_c->dat[0];}
    T im() const {return gsl_c->dat[1];}
    T& re() {return gsl_c->dat[0];}
    T& im() {return gsl_c->dat[1];}
    T abs() const;
    T abs2() const;
    T logabs() const;
    T arg() const;

    Complex_t conjugate() const;
    Complex_t recipr() const;
    Complex_t negate() const;

    Complex_t operator+(const Complex_t& b) const;
    Complex_t operator-(const Complex_t& b) const;
    Complex_t operator*(const Complex_t& b) const;
    Complex_t operator/(const Complex_t& b) const;

    Complex_t operator+(const T& s) const;
    Complex_t operator-(const T& s) const;
    Complex_t operator*(const T& s) const;
    Complex_t operator/(const T& s) const;

    Complex_t operator+(const GSL_COMPLEX& b) const
    {return Complex_t(this->re() + b.dat[0], this->im() + b.dat[1]);}
    Complex_t operator-(const GSL_COMPLEX& b) const
    {return Complex_t(this->re() - b.dat[0], this->im() - b.dat[1]);}
    Complex_t operator*(const GSL_COMPLEX& b) const
    {return Complex_t(this->re()*b.dat[0] - this->im()*b.dat[1],
                      this->re()*b.dat[1] + this->im()*b.dat[0]);}
    Complex_t operator/(const GSL_COMPLEX& b) const
    {return (*this)*Complex_t(b.dat[0], -b.dat[1])/(b.dat[0]*b.dat[0] + b.dat[1]*b.dat[1]);}

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

    friend Complex_t (operator+)(const GSL_COMPLEX& b, const Complex_t& a)
    {
        return a + b;
    };
    friend Complex_t operator-(const GSL_COMPLEX& b, const Complex_t& a)
    {
        return -(a-b);
    };
    friend Complex_t operator*(const GSL_COMPLEX& b, const Complex_t& a)
    {
        return a*b;
    };

    friend Complex_t operator/(const GSL_COMPLEX& b, const Complex_t& a)
    {
        return a.recipr()*b;
    };

    Complex_t operator-() const { return this->negate();}

    Complex_t operator+=(const Complex_t& b) {*this = *this + b; return *this;}
    Complex_t operator-=(const Complex_t& b) {*this = *this - b; return *this;}
    Complex_t operator*=(const Complex_t& b) {*this = *this * b; return *this;}
    Complex_t operator/=(const Complex_t& b) {*this = *this / b; return *this;}

    Complex_t operator+=(const T& s) {*this = *this + s; return *this;}
    Complex_t operator-=(const T& s) {*this = *this - s; return *this;}
    Complex_t operator*=(const T& s) {*this = *this * s; return *this;}
    Complex_t operator/=(const T& s) {*this = *this / s; return *this;}

    Complex_t operator+=(const GSL_COMPLEX& b) {*this = *this + b; return *this;}
    Complex_t operator-=(const GSL_COMPLEX& b) {*this = *this - b; return *this;}
    Complex_t operator*=(const GSL_COMPLEX& b) {*this = *this * b; return *this;}
    Complex_t operator/=(const GSL_COMPLEX& b) {*this = *this / b; return *this;}

    bool  operator==(const Complex_t& b) const {return this->re() == b.re() && this->im() == b.im();}
    bool  operator!=(const Complex_t& b) const {return !(*this == b);}

    std::string to_string() const
    {
        return  (this->re() == 0 ? "" : std::to_string(this->re())) +
                (this->im() == 0 ? "" :
                (this->im() > 0 ? std::string(" + ") :"") +
                (this->im() < 0 ? std::string(" - ") : "") +
                    std::to_string(std::abs(this->im())) + std::string("i"));
    }

    friend std::ostream& operator<<(std::ostream& os, const Complex_t& z)
    {
        return os << z.to_string();
    };

    friend Complex_t<double, gsl_complex> exp(const Complex_t<double, gsl_complex>& a);
    friend Complex_t<double, gsl_complex> sqrt(const Complex_t<double, gsl_complex>& a);
    friend Complex_t<double, gsl_complex> pow(const Complex_t<double, gsl_complex>& a, const Complex_t<double, gsl_complex>& b);
    friend Complex_t<double, gsl_complex> log(const Complex_t<double, gsl_complex>& a);
    friend Complex_t<double, gsl_complex> pow(const Complex_t<double, gsl_complex>& a, const double& s);
    friend Complex_t<double, gsl_complex> log10(const Complex_t<double, gsl_complex>& a);
    friend Complex_t<double, gsl_complex> log_b(const Complex_t<double, gsl_complex>& a, const Complex_t<double, gsl_complex>& b);

    friend Complex_t<double, gsl_complex> sin(const Complex_t<double, gsl_complex>&a);
    friend Complex_t<double, gsl_complex> cos(const Complex_t<double, gsl_complex>&a);
    friend Complex_t<double, gsl_complex> tan(const Complex_t<double, gsl_complex>&a);
    friend Complex_t<double, gsl_complex> sec(const Complex_t<double, gsl_complex>&a);
    friend Complex_t<double, gsl_complex> csc(const Complex_t<double, gsl_complex>&a);
    friend Complex_t<double, gsl_complex> cot(const Complex_t<double, gsl_complex>&a);

    friend Complex_t<double, gsl_complex> arcsin(const Complex_t<double, gsl_complex>& a);
    friend Complex_t<double, gsl_complex> arccos(const Complex_t<double, gsl_complex>& a);
    friend Complex_t<double, gsl_complex> arctan(const Complex_t<double, gsl_complex>& a);
    friend Complex_t<double, gsl_complex> arcsec(const Complex_t<double, gsl_complex>& a);
    friend Complex_t<double, gsl_complex> arccsc(const Complex_t<double, gsl_complex>& a);
    friend Complex_t<double, gsl_complex> arccot(const Complex_t<double, gsl_complex>& a);

    friend Complex_t<double, gsl_complex> sinh(const Complex_t<double, gsl_complex>& a);
    friend Complex_t<double, gsl_complex> cosh(const Complex_t<double, gsl_complex>& a);
    friend Complex_t<double, gsl_complex> tanh(const Complex_t<double, gsl_complex>& a);
    friend Complex_t<double, gsl_complex> sech(const Complex_t<double, gsl_complex>& a);
    friend Complex_t<double, gsl_complex> csch(const Complex_t<double, gsl_complex>& a);
    friend Complex_t<double, gsl_complex> coth(const Complex_t<double, gsl_complex>& a);

    friend Complex_t<double, gsl_complex> arcsinh(const Complex_t<double, gsl_complex>& a);
    friend Complex_t<double, gsl_complex> arccosh(const Complex_t<double, gsl_complex>& a);
    friend Complex_t<double, gsl_complex> arctanh(const Complex_t<double, gsl_complex>& a);
    friend Complex_t<double, gsl_complex> arcsech(const Complex_t<double, gsl_complex>& a);
    friend Complex_t<double, gsl_complex> arccsch(const Complex_t<double, gsl_complex>& a);
    friend Complex_t<double, gsl_complex> arccoth(const Complex_t<double, gsl_complex>& a);
    friend Complex_t<double, gsl_complex> PolynomialInternal::evaluate_polynomial(const std::vector<double>& coeffs, const size_t order, const Complex_t<double, gsl_complex>& z);
    friend Complex_t<double, gsl_complex> PolynomialInternal::evaluate_polynomial(const std::vector<Complex_t<double, gsl_complex>>& coeffs, const size_t order, const Complex_t<double, gsl_complex>& z);

};


    Complex_t<double, gsl_complex> sqrt(const double& a);
    Complex_t<double, gsl_complex> exp(const Complex_t<double, gsl_complex>& a);
    Complex_t<double, gsl_complex> sqrt(const Complex_t<double, gsl_complex>& a);
    Complex_t<double, gsl_complex> pow(const Complex_t<double, gsl_complex>& a, const Complex_t<double, gsl_complex>& b);
    Complex_t<double, gsl_complex> pow(const Complex_t<double, gsl_complex>& a, const double& s);
    Complex_t<double, gsl_complex> log(const Complex_t<double, gsl_complex>& a);
    Complex_t<double, gsl_complex> log10(const Complex_t<double, gsl_complex>& a);
    Complex_t<double, gsl_complex> log_b(const Complex_t<double, gsl_complex>& a, const Complex_t<double, gsl_complex>& b);

    Complex_t<double, gsl_complex> sin(const Complex_t<double, gsl_complex>&a);
    Complex_t<double, gsl_complex> cos(const Complex_t<double, gsl_complex>&a);
    Complex_t<double, gsl_complex> tan(const Complex_t<double, gsl_complex>&a);
    Complex_t<double, gsl_complex> sec(const Complex_t<double, gsl_complex>&a);
    Complex_t<double, gsl_complex> csc(const Complex_t<double, gsl_complex>&a);
    Complex_t<double, gsl_complex> cot(const Complex_t<double, gsl_complex>&a);

    Complex_t<double, gsl_complex> arcsin(const Complex_t<double, gsl_complex>& a);
    Complex_t<double, gsl_complex> arcsin(const double& a);
    Complex_t<double, gsl_complex> arccos(const Complex_t<double, gsl_complex>& a);
    Complex_t<double, gsl_complex> arccos(const double& a);
    Complex_t<double, gsl_complex> arctan(const Complex_t<double, gsl_complex>& a);
    Complex_t<double, gsl_complex> arcsec(const Complex_t<double, gsl_complex>& a);
    Complex_t<double, gsl_complex> arcsec(const double& a);
    Complex_t<double, gsl_complex> arccsc(const Complex_t<double, gsl_complex>& a);
    Complex_t<double, gsl_complex> arccsc(const double& a);
    Complex_t<double, gsl_complex> arccot(const Complex_t<double, gsl_complex>& a);

    Complex_t<double, gsl_complex> sinh(const Complex_t<double, gsl_complex>& a);
    Complex_t<double, gsl_complex> cosh(const Complex_t<double, gsl_complex>& a);
    Complex_t<double, gsl_complex> tanh(const Complex_t<double, gsl_complex>& a);
    Complex_t<double, gsl_complex> sech(const Complex_t<double, gsl_complex>& a);
    Complex_t<double, gsl_complex> csch(const Complex_t<double, gsl_complex>& a);
    Complex_t<double, gsl_complex> coth(const Complex_t<double, gsl_complex>& a);

    Complex_t<double, gsl_complex> arcsinh(const Complex_t<double, gsl_complex>& a);
    Complex_t<double, gsl_complex> arccosh(const Complex_t<double, gsl_complex>& a);
    Complex_t<double, gsl_complex> arccosh(const double& a);
    Complex_t<double, gsl_complex> arctanh(const Complex_t<double, gsl_complex>& a);
    Complex_t<double, gsl_complex> arctanh(const double& a);
    Complex_t<double, gsl_complex> arcsech(const Complex_t<double, gsl_complex>& a);
    Complex_t<double, gsl_complex> arccsch(const Complex_t<double, gsl_complex>& a);
    Complex_t<double, gsl_complex> arccoth(const Complex_t<double, gsl_complex>& a);

    bool operator==( const gsl_complex&, const gsl_complex&);
    inline bool operator!=( const gsl_complex&a, const gsl_complex&b){ return !(a == b);}
    bool operator==( const gsl_complex_float&, const gsl_complex_float&);
    inline bool operator!=( const gsl_complex_float&a, const gsl_complex_float&b){ return !(a == b);}
    bool operator==( const gsl_complex_long_double&, const gsl_complex_long_double&);
    inline bool operator!=( const gsl_complex_long_double&a, const gsl_complex_long_double&b){ return !(a == b);}

    gsl_complex operator*(const gsl_complex& a, const gsl_complex&b);
    gsl_complex operator+(const gsl_complex& a, const gsl_complex&b);
    gsl_complex operator-(const gsl_complex& a, const gsl_complex&b);

    gsl_complex_long_double operator+(const gsl_complex_long_double& a, const gsl_complex_long_double&b);
    gsl_complex_long_double operator-(const gsl_complex_long_double& a, const gsl_complex_long_double&b);
    gsl_complex_long_double operator*(const gsl_complex_long_double& a, const gsl_complex_long_double&b);
    gsl_complex_float operator+(const gsl_complex_float& a, const gsl_complex_float&b);
    gsl_complex_float operator-(const gsl_complex_float& a, const gsl_complex_float&b);
    gsl_complex_float operator*(const gsl_complex_float& a, const gsl_complex_float&b);
}

namespace std{
    inline string to_string(const GSL::Complex_t<double, gsl_complex>& c) {return c.to_string();}
    inline string to_string(const GSL::Complex_t<long double, gsl_complex_long_double>& c) {return c.to_string();}
    inline string to_string(const GSL::Complex_t<float, gsl_complex_float>& c) {return c.to_string();}
    template<class T, class GSL_COMPLEX>
    T abs(const GSL::Complex_t<T, GSL_COMPLEX>& c)
    {
        return c.abs();
    }


    template<class T, class GSL_COMPLEX>
    struct hash<GSL::Complex_t<T, GSL_COMPLEX>>{
	    size_t operator()(const GSL::Complex_t<T, GSL_COMPLEX>& c)
	    {
		    std::hash<T> h;
		    size_t res = 0;
		    res ^= h(c.re()) + 0x9e3779b9 + (res<< 6) + (res>> 2);
		    res ^= h(c.im()) + 0x9e3779b9 + (res<< 6) + (res>> 2);
		    return res;
	    }
    };
}

#endif //COMPLEX_GSLPP_LIB_H
