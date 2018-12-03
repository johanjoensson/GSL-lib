#ifndef LINALG_H
#define LINALG_H
#include "vector.h"
#include "matrix.h"
#include "complex_vector.h"
#include "complex_matrix.h"


namespace GSL{

    void hermitian_eigen(Complex_Matrix& eigvecs, Vector& eigvals);

}


#endif // GSL_LINALG_H
