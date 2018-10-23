#ifndef MATRIX_H
#define MATRIX_H
#include "vector.h"
#include <gsl/gsl_matrix.h>
#include <vector>

namespace GSL{class Matrix;}

namespace GSL{
    class BaseMatrix{
    protected:
        size_t *count;

        BaseMatrix();
        BaseMatrix(BaseMatrix &m);
        BaseMatrix(const BaseMatrix &m);
        BaseMatrix(BaseMatrix &&m);
        ~BaseMatrix();

        BaseMatrix& operator=(const BaseMatrix &m) = delete;
        BaseMatrix& operator=(BaseMatrix &&m) = delete;

        virtual void copy(const BaseMatrix &m) = delete;

        virtual std::string to_string() const = 0;

        friend std::ostream& operator<<(std::ostream &os, const BaseMatrix &m);

        void set_row(const size_t &i, const BaseVector &v) = delete;
        void set_col(const size_t &i, const BaseVector &v) = delete;

    };
    std::ostream& operator<<(std::ostream &os, const BaseMatrix &m);

    class Matrix : public BaseMatrix{
    private:
        gsl_matrix* gsl_mat;
        std::vector<Vector> rows, cols;
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
        Matrix hermitian_conj() const;

        void set_row(const size_t &i, const Vector &v);
        void set_col(const size_t &i, const Vector &v);

        friend bool operator== (const Matrix& u, const Matrix& v);
        friend bool operator!= (const Matrix& u, const Matrix& v);

        std::string to_string() const;

    };

    Matrix operator*(const double& s, const Matrix& a);
    Vector operator* (const Vector& v, const Matrix& a);
    bool operator== (const Matrix& u, const Matrix& v);
    bool operator!= (const Matrix& u, const Matrix& v);
}

#endif // MATRIX_H
