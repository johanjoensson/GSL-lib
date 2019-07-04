#ifndef GSL_LINALG_H
#define GSL_LINALG_H
#include "vector.h"
#include "matrix.h"
#include "permutation.h"


namespace GSL{

    Matrix_cx cholesky_decomp(const Matrix_cx& a);
    Matrix lu_inverse(const Matrix& a);
    Matrix_cx lu_inverse(const Matrix_cx& a);
    std::pair<Matrix, Permutation> lu_decomp(const Matrix& a);
    std::pair<Matrix_cx, Permutation> lu_decomp(const Matrix_cx& a);
    Matrix cholesky_decomp(const Matrix& a);
    Matrix triangular_inverse(const Matrix& a);

}


#endif // GSL_LINALG_H
