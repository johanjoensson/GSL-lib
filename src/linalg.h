#ifndef GSL_LINALG_H
#define GSL_LINALG_H
#include "vector.h"
#include "matrix.h"
#include "complex_vector.h"
#include "complex_matrix.h"
#include "permutation.h"


namespace GSL{

    Complex_Matrix cholesky_decomp(const Complex_Matrix& a);
    Complex_Matrix lu_inverse(const Complex_Matrix& a);
    std::pair<Complex_Matrix, Permutation&> lu_decomp(const Complex_Matrix& a);
    Matrix cholesky_decomp(const Matrix& a);
    Matrix triangular_inverse(const Matrix& a);

}


#endif // GSL_LINALG_H
