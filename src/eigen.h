#ifndef LINALG_H
#define LINALG_H

#include "vector.h"
#include "matrix.h"
#include "complex_vector.h"
#include "complex_matrix.h"


namespace GSL{

    enum Matrix_symmetry{
        SYMMETRIC,
        ANTISYMMETRIC,

    };

    std::pair<Complex_Matrix, Vector> hermitian_eigen(const Complex_Matrix& A);
    std::pair<Complex_Matrix, Vector> general_hermitian_eigen(
        const Complex_Matrix& A, const Complex_Matrix& B);
}


#endif // GSL_LINALG_H
