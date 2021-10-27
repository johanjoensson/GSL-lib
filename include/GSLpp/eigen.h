#ifndef LINALG_H
#define LINALG_H

#include <GSLpp/vector.h>
#include <GSLpp/vector_complex.h>

#include <GSLpp/matrix.h>
#include <GSLpp/matrix_complex.h>

namespace GSL{

    enum class Matrix_symmetry{
        SYMMETRIC,
        ANTISYMMETRIC,
    };

    enum class SORTING{
        VALUE_ASCENDING,
        VALUE_DESCENDING,
        ABSOLUTE_VALUE_ASCENDING,
        ABSOLUTE_VALUE_DESCENDING
    };

    std::pair<Matrix_Complex, Vector> hermitian_eigen(const Matrix_Complex& A);
    std::pair<Matrix_Complex, Vector> sort_hermitian_eigen(
        const Vector& evals, const Matrix_Complex& evecs, SORTING sorting = SORTING::VALUE_ASCENDING);

    std::pair<Matrix_Complex, Vector> general_hermitian_eigen(
        const Matrix_Complex& A, const Matrix_Complex& B);
    std::pair<Matrix_Complex, Vector> sort_general_hermitian_eigen(
        const Vector& evals, const Matrix_Complex& evecs, SORTING sorting = SORTING::VALUE_ASCENDING);

}


#endif // GSL_LINALG_H
