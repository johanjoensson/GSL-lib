#include <gsl/gsl_complex.h>
#include <gsl/gsl_complex_math.h>
#include <complex>

namespace GSL{

class Complex_long_double {
private:
    gsl_complex_long_double gsl_c_m;
public:
    Complex_long_double(const Complex_long_double&) = default;
    Complex_long_double(Complex_long_double&&) = default;
    ~Complex_long_double() = default;

    Complex_long_double& operator=(const Complex_long_double&) = default;
    Complex_long_double& operator=(Complex_long_double&&) = default;
    explicit Complex_long_double(const long double re = 0, const long double im = 0);
    Complex_long_double(gsl_complex_long_double z) : gsl_c_m(z) {}


    friend long double real(const Complex_long_double& z) {return z.real();}
    long double real() const {return reinterpret_cast<const long double(&)[2]>(*this)[0];}
    void real(long double value) {reinterpret_cast<long double(&)[2]> (*this)[0] = value;}

    friend long double imag(const Complex_long_double& z) {return z.imag();}
    long double imag() const {return reinterpret_cast<const long double(&)[2]>(*this)[1];}
    void imag(long double value) {reinterpret_cast<long double(&)[2]> (*this)[1] = value;}

    operator gsl_complex_long_double&() {return *(&gsl_c_m);}

    operator std::complex<long double>&()
    {
        return *(reinterpret_cast<std::complex<long double>*> (this));
    }

    operator const std::complex<long double>&() const
    {
        return *(reinterpret_cast<const std::complex<long double>*> (this));
    }

    friend bool operator==(const Complex_long_double& a, const Complex_long_double& b);
    friend bool operator!=(const Complex_long_double& a, const Complex_long_double& b);


    std::string to_string() const
    {
        return  (this->real() == 0 ? "" : std::to_string(this->real())) +
                (this->imag() == 0 ? "" :
                (this->imag() > 0 ? std::string(" + ") :"") +
                (this->imag() < 0 ? std::string(" - ") : "") +
                    std::to_string(std::abs(this->imag())) + std::string("i"));
    }

    friend std::ostream& operator<<(std::ostream& os, const Complex_long_double& z)
    {
        return os << z.to_string();
    };

};

bool operator==(const Complex_long_double& a, const Complex_long_double& b);
bool operator!=(const Complex_long_double& a, const Complex_long_double& b);

}
