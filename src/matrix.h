#ifndef MATRIX_H
#define MATRIX_H
#include "vector.h"
#include <gsl/gsl_matrix.h>
#include <vector>

namespace GSL{class Matrix;}
std::ostream& operator<< (std::ostream& os, const GSL::Matrix& a);

namespace GSL{
    class Matrix{
    private:
        gsl_matrix* gsl_mat;
        std::vector<Vector> rows, cols;
        size_t* count;
    public:
        Matrix();
        Matrix(const size_t n1, const size_t n2);
        Matrix(gsl_matrix m);
        Matrix(Matrix& m);
        Matrix(const Matrix& m);
        Matrix(Matrix&& m);
        ~Matrix();

        void copy(const Matrix& m);
        Matrix& operator= (const Matrix& m);
        Matrix& operator= (Matrix&& m);

        Vector& operator[](const size_t index);

        Matrix& operator+= (const Matrix& b);
        Matrix& operator-= (const Matrix& b);
        Matrix& operator*= (const Matrix& b);
        Matrix& operator/= (const Matrix& b);
        Matrix& operator*= (const double s);
        Matrix& operator/= (const double s);

        // Basic arithmetic operations
        Matrix operator+ (const Matrix& b) const;
        Matrix operator- (const Matrix& b) const;
        // Element wise multiplication and division
        Matrix operator* (const Matrix& b) const;
        Matrix operator/ (const Matrix& b) const;
        // Scaling of matrices
        Matrix operator* (const double& s) const;
        friend Matrix operator*(const double& s, const Matrix& a);
        Matrix operator/ (const double& s) const;

        // Matrix - vector multiplication
        Vector operator* (const Vector& v) const;
        friend Vector operator* (const Vector& v, const Matrix& a);

        Matrix transpose() const;

        friend std::ostream& ::operator<< (std::ostream& os, const Matrix& a);

    };

    Matrix operator*(const double& s, const Matrix& a);
    Vector operator* (const Vector& v, const Matrix& a);
}

#endif // MATRIX_H
