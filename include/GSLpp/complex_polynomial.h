#ifndef NEW_COMPLEX_POLYNOMIAL_GSLPP_LIB_H
#define NEW_COMPLEX_POLYNOMIAL_GSLPP_LIB_H

#include <vector>
namespace GSL{
class Complex;

namespace PolynomialInternal{
    Complex evaluate_polynomial(const std::vector<double>& coeffs, const size_t order, const Complex& z);
    Complex evaluate_polynomial(const std::vector<Complex>& coeffs, const size_t order, const Complex& z);
}
}

#endif // NEW_COMPLEX_POLYNOMIAL_GSLPP_LIB_H
