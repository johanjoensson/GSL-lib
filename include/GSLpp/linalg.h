#ifndef GSL_LINALG_H
#define GSL_LINALG_H
#include <GSLpp/vector.h>
#include <GSLpp/matrix.h>
#include <GSLpp/permutation.h>


namespace GSL{

    Matrix_cx cholesky_decomp(const Matrix_cx& a);
    Matrix lu_inverse(const Matrix& a);
    Matrix_cx lu_inverse(const Matrix_cx& a);
    std::tuple<Matrix, Permutation, int> lu_decomp(const Matrix& a);
    std::tuple<Matrix_cx, Permutation, int> lu_decomp(const Matrix_cx& a);
    Matrix cholesky_decomp(const Matrix& a);
    Matrix triangular_inverse(const Matrix& a);

    GSL::Complex lu_det(const Matrix_cx&);
    double lu_det(const Matrix&);

}


#endif // GSL_LINALG_H
