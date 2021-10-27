#ifndef GSL_LINALG_H
#define GSL_LINALG_H
#include <GSLpp/vector.h>
#include <GSLpp/vector_complex.h>
#include <GSLpp/matrix.h>
#include <GSLpp/matrix_complex.h>
#include <GSLpp/permutation.h>


namespace GSL{

    Matrix_Complex cholesky_decomp(const Matrix_Complex& a);
    Matrix lu_inverse(const Matrix& a);
    Matrix_Complex lu_inverse(const Matrix_Complex& a);
    std::tuple<Matrix, Permutation, int> lu_decomp(const Matrix& a);
    std::tuple<Matrix_Complex, Permutation, int> lu_decomp(const Matrix_Complex& a);
    Matrix cholesky_decomp(const Matrix& a);
    Matrix triangular_inverse(const Matrix& a);

    Complex lu_det(const Matrix_Complex&);
    double lu_det(const Matrix&);

}


#endif // GSL_LINALG_H
