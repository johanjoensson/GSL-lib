#ifndef LINALG_H
#define LINALG_H

#include <GSLpp/vector.h>
#include <GSLpp/matrix.h>

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

    std::pair<Matrix_cx, Vector> hermitian_eigen(const Matrix_cx& A);
    std::pair<Matrix_cx, Vector> sort_hermitian_eigen(
        const Vector& evals, const Matrix_cx& evecs, SORTING sorting = SORTING::VALUE_ASCENDING);

    std::pair<Matrix_cx, Vector> general_hermitian_eigen(
        const Matrix_cx& A, const Matrix_cx& B);
    std::pair<Matrix_cx, Vector> sort_general_hermitian_eigen(
        const Vector& evals, const Matrix_cx& evecs, SORTING sorting = SORTING::VALUE_ASCENDING);

}


#endif // GSL_LINALG_H
