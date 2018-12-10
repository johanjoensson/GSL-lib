#ifndef COMPLEX_MATRIX_H
#define COMPLEX_MATRIX_H
#include "complex_vector.h"
#include "matrix.h"
#include "permutation.h"
#include <gsl/gsl_matrix.h>
#include <vector>

namespace GSL{class Complex_Matrix;}

namespace GSL{
    class Complex_Matrix : public BaseMatrix{
    private:
        std::shared_ptr<gsl_matrix_complex> gsl_mat;
    public:
        Complex_Matrix();
        Complex_Matrix(const size_t n1, const size_t n2);
        Complex_Matrix(gsl_matrix_complex m);
        Complex_Matrix(Complex_Matrix& m);
        Complex_Matrix(const Complex_Matrix& m);
        Complex_Matrix(Complex_Matrix&& m);
        Complex_Matrix(std::initializer_list<std::initializer_list<Complex>>);
        ~Complex_Matrix();

        void copy(const Complex_Matrix& m);
        Complex_Matrix& operator= (const Complex_Matrix& m);
        Complex_Matrix& operator= (Complex_Matrix&& m);

        Complex_Vector operator[](const size_t index);

        Complex_Matrix& operator+= (const Complex_Matrix& b);
        Complex_Matrix& operator-= (const Complex_Matrix& b);
        Complex_Matrix& operator*= (const Complex_Matrix& b);
        Complex_Matrix& operator/= (const Complex_Matrix& b);
        Complex_Matrix& operator*= (const double s);
        Complex_Matrix& operator/= (const double s);

        // Basic arithmetic operations
        Complex_Matrix operator+ (const Complex_Matrix& b) const;
        Complex_Matrix operator- (const Complex_Matrix& b) const;
        // Element wise multiplication and division
        Complex_Matrix operator* (const Complex_Matrix& b) const;
        Complex_Matrix operator/ (const Complex_Matrix& b) const;
        // Scaling of matrices
        Complex_Matrix operator* (const double& s) const;
        friend Complex_Matrix operator*(const double& s, const Complex_Matrix& a);
        Complex_Matrix operator/ (const double& s) const;

        // Complex_Matrix - vector multiplication
        Complex_Vector operator* (const Complex_Vector& v) const;
        friend Complex_Vector operator* (const Complex_Vector& v, const Complex_Matrix& a);

        Complex_Matrix transpose() const;
        Complex_Matrix hermitian_transpose() const;

        friend bool operator== (const Complex_Matrix& u, const Complex_Matrix& v);
        friend bool operator!= (const Complex_Matrix& u, const Complex_Matrix& v);

        std::string to_string() const;

        void set_row(const size_t& index, const Complex_Vector& r);
        void set_col(const size_t& index, const Complex_Vector& r);
        Complex_Vector diag();
        Complex_Vector get_col(const size_t i);

        friend Complex_Matrix cholesky_decomp(const Complex_Matrix& a);
        friend Complex_Matrix lu_inverse(const Complex_Matrix& a);
        friend std::pair<Complex_Matrix, Permutation&> lu_decomp(
            const Complex_Matrix& a);

        friend std::pair<Complex_Matrix, Vector> hermitian_eigen(
            const Complex_Matrix& A);
        friend std::pair<Complex_Matrix, Vector> general_hermitian_eigen(
            const Complex_Matrix& A, const Complex_Matrix& B);
    };

    Complex_Matrix operator*(const double& s, const Complex_Matrix& a);
    Complex_Vector operator* (const Complex_Vector& v, const Complex_Matrix& a);

    bool operator== (const Complex_Matrix& u, const Complex_Matrix& v);
    bool operator!= (const Complex_Matrix& u, const Complex_Matrix& v);
}

#endif // MATRIX_H
