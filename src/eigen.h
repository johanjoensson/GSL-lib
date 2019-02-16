#ifndef LINALG_H
#define LINALG_H

#include "vector.h"
#include "matrix.h"

namespace GSL{

    enum Matrix_symmetry{
        SYMMETRIC,
        ANTISYMMETRIC,

    };

    std::pair<Matrix_cx, Vector> hermitian_eigen(const Matrix_cx& A);
    std::pair<Matrix_cx, Vector> general_hermitian_eigen(
        const Matrix_cx& A, const Matrix_cx& B);
}


#endif // GSL_LINALG_H
