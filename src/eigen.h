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
    void hermitian_eigen(Complex_Matrix& eigvecs, Vector& eigvals);
    void general_hermitian_eigen(const Complex_Matrix& A, const Complex_Matrix& B, Complex_Matrix& eigvecs, Vector& eigvals);

}


#endif // GSL_LINALG_H
