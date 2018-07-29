#ifndef COMPLEX_MATRIX_H
#define COMPLEX_MATRIX_H
#include "complex_vector.h"
#include <gsl/gsl_matrix.h>
#include <vector>

namespace GSL{class Complex_Matrix;}
std::ostream& operator<< (std::ostream& os, const GSL::Complex_Matrix& a);

namespace GSL{
    class Complex_Matrix{
    private:
        gsl_matrix_complex* gsl_mat;
        std::vector<Complex_Vector> rows, cols;
        size_t* count;
    public:
        Complex_Matrix();
        Complex_Matrix(const size_t n1, const size_t n2);
        Complex_Matrix(gsl_matrix_complex m);
        Complex_Matrix(Complex_Matrix& m);
        Complex_Matrix(const Complex_Matrix& m);
        Complex_Matrix(Complex_Matrix&& m);
        ~Complex_Matrix();

        void copy(const Complex_Matrix& m);
        Complex_Matrix& operator= (const Complex_Matrix& m);
        Complex_Matrix& operator= (Complex_Matrix&& m);

        Complex_Vector& operator[](const size_t index);

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

        friend bool operator== (const Complex_Matrix& u, const Complex_Matrix& v);
        friend bool operator!= (const Complex_Matrix& u, const Complex_Matrix& v);

        friend std::ostream& ::operator<< (std::ostream& os, const Complex_Matrix& a);

    };

    Complex_Matrix operator*(const double& s, const Complex_Matrix& a);
    Complex_Vector operator* (const Complex_Vector& v, const Complex_Matrix& a);

    bool operator== (const Complex_Matrix& u, const Complex_Matrix& v);
    bool operator!= (const Complex_Matrix& u, const Complex_Matrix& v);
}

#endif // MATRIX_H
