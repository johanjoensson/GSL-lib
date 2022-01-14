#ifndef NEW_TRIANGULAR_MATRIX_GLSPP_LIB_H
#define NEW_TRIANGULAR_MATRIX_GLSPP_LIB_H

#include "GSLpp/matrix.h"

namespace GSL {

class Triangular_Matrix : public Matrix{
protected:
    Triangular_Matrix() = default;
public:
    Triangular_Matrix(const Triangular_Matrix&) = default;
    Triangular_Matrix(Triangular_Matrix&&) = default;

    Triangular_Matrix& operator=(const Triangular_Matrix&) = default;
    Triangular_Matrix& operator=(Triangular_Matrix&&) = default;
};

}
#endif // NEW_TRIANGULAR_MATRIX_GLSPP_LIB_H
