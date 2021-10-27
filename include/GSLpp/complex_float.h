#include <gsl/gsl_complex.h>
#include <gsl/gsl_complex_math.h>
#include <complex>

namespace GSL{

class Complex_float {
private:
    gsl_complex_float gsl_c_m;
public:
    Complex_float(const Complex_float&) = default;
    Complex_float(Complex_float&&) = default;
    ~Complex_float() = default;

    Complex_float& operator=(const Complex_float&) = default;
    Complex_float& operator=(Complex_float&&) = default;
    explicit Complex_float(const float re = float(), const float im = float());
    Complex_float(gsl_complex_float z) : gsl_c_m(z) {}


    friend float real(const Complex_float& z) {return z.real();}
    float real() const {return reinterpret_cast<const float(&)[2]>(*this)[0];}
    void real(float value) {reinterpret_cast<float(&)[2]> (*this)[0] = value;}

    friend float imag(const Complex_float& z) {return z.imag();}
    float imag() const {return reinterpret_cast<const float(&)[2]>(*this)[1];}
    void imag(float value) {reinterpret_cast<float(&)[2]> (*this)[1] = value;}

    operator gsl_complex_float&() {return *(&gsl_c_m);}

    operator std::complex<float>&()
    {
        return *(reinterpret_cast<std::complex<float>*> (this));
    }

    operator const std::complex<float>&() const
    {
        return *(reinterpret_cast<const std::complex<float>*> (this));
    }

    friend bool operator==(const Complex_float& a, const Complex_float& b);
    friend bool operator!=(const Complex_float& a, const Complex_float& b);


    std::string to_string() const
    {
        return  (this->real() == 0 ? "" : std::to_string(this->real())) +
                (this->imag() == 0 ? "" :
                (this->imag() > 0 ? std::string(" + ") :"") +
                (this->imag() < 0 ? std::string(" - ") : "") +
                    std::to_string(std::abs(this->imag())) + std::string("i"));
    }

    friend std::ostream& operator<<(std::ostream& os, const Complex_float& z)
    {
        return os << z.to_string();
    };

};

bool operator==(const Complex_float& a, const Complex_float& b);
bool operator!=(const Complex_float& a, const Complex_float& b);


}
