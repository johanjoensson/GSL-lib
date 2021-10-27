#ifndef NEW_MATRIX_GLSPP_LIB_H
#define NEW_MATRIX_GLSPP_LIB_H

#include <gsl/gsl_matrix.h>
#include <utility>
#include <memory>
#include <iostream>
#include <string>

#include "GSLpp/vector.h"

namespace GSL{

    class Matrix {
    protected:
        std::unique_ptr<gsl_matrix, decltype(&gsl_matrix_free)> gsl_mat_m;

        Matrix() = default;
        Matrix(gsl_matrix* v);

    public:
        Matrix(const Matrix&) = default;
        Matrix(Matrix&&) = default;
        Matrix& operator=(const Matrix&) = default;
        Matrix& operator=(Matrix&&) = default;
        virtual ~Matrix() = default;

        Matrix(size_t n1, size_t n2);
        Matrix(size_t n1, size_t n2, double val);

        Matrix(std::initializer_list<Vector> l);
        Matrix(std::initializer_list<std::initializer_list<double>> l);

        gsl_matrix* gsl_data();
        const gsl_matrix* gsl_data() const;

        friend bool operator==(const Matrix& a, const Matrix& b);
        friend bool operator!=(const Matrix& a, const Matrix& b);

        Matrix& copy(const Matrix& other);
        Matrix& transpose_copy(const Matrix& other);
        Matrix& swap(const Matrix& other);

        Matrix& swap_rows(size_t i, size_t j);
        Matrix& swap_columns(size_t i, size_t j);
        Matrix& swap_rowcol(size_t i, size_t j);

        Matrix& transpose();
        Matrix& T();

        Matrix clone() const;

        size_t num_rows() const;
        size_t num_columns() const;
        std::pair<size_t, size_t> dim() const;

        Matrix& set_all(double val);
        Matrix& set_zero();
        Matrix& set(size_t i, size_t j, double val);
        Matrix& set_identity();
        double get(size_t i, size_t j) const;

        double max() const;
        double min() const;
        std::pair<double, double> minmax() const;

        std::pair<size_t, size_t> max_index() const;
        std::pair<size_t, size_t> min_index() const;
        std::pair<std::pair<size_t, size_t>, std::pair<size_t, size_t>> minmax_index() const;

        bool isnull() const;
        bool ispos() const;
        bool isneg() const;
        bool isnonneg() const;

        Matrix& operator+=(const Matrix& other);
        Matrix& operator-=(const Matrix& other);
        Matrix& operator*=(const Matrix& other);
        Matrix& operator/=(const Matrix& other);

        Matrix& operator+=(double s);
        Matrix& operator-=(double s);
        Matrix& operator*=(double s);
        Matrix& operator/=(double s);

        Matrix& multiply(const Matrix& other);

        class View;
        class Const_View;

        View view();
        const View view() const;
        Const_View cview() const;

        View view(size_t k1, size_t k2, size_t n1, size_t n2);
        const View view(size_t k1, size_t k2, size_t n1, size_t n2) const;
        Const_View cview(size_t k1, size_t k2, size_t n1, size_t n2) const;

        Vector::View row(size_t row);
        Vector::Const_View row(size_t row) const;
        Vector::Const_View crow(size_t row) const;

        Vector::View column(size_t column);
        Vector::Const_View column(size_t column) const;
        Vector::Const_View ccolumn(size_t column) const;

        Vector::View subrow(size_t i, size_t offset, size_t n);
        Vector::Const_View subrow(size_t i, size_t offset, size_t n) const;
        Vector::Const_View csubrow(size_t i, size_t offset, size_t n) const;
        Vector::View subcolumn(size_t i, size_t offset, size_t n);
        Vector::Const_View subcolumn(size_t i, size_t offset, size_t n) const;
        Vector::Const_View csubcolumn(size_t i, size_t offset, size_t n) const;
        Vector::View diagonal();
        Vector::Const_View diagonal() const;
        Vector::Const_View cdiagonal() const;
        Vector::View subdiagonal(size_t k);
        Vector::Const_View subdiagonal(size_t k) const;
        Vector::Const_View csubdiagonal(size_t k) const;
        Vector::View superdiagonal(size_t k);
        Vector::Const_View superdiagonal(size_t k) const;
        Vector::Const_View csuperdiagonal(size_t k) const;


        Vector::View operator[](size_t row);
        Vector::Const_View operator[](size_t row) const;

        Vector::View at(size_t row);
        Vector::Const_View at(size_t row) const;

        double& operator()(size_t i, size_t j);
        const double& operator()(size_t i, size_t j) const;

        double& at(size_t i, size_t j);
        const double& at(size_t i, size_t j) const;

        std::string to_string() const;

    };

    Matrix operator+(const Matrix& a, const Matrix& b);
    Matrix operator-(const Matrix& a, const Matrix& b);
    Matrix operator*(const Matrix& a, const Matrix& b);
    Matrix operator/(const Matrix& a, const Matrix& b);
    Matrix operator+(const Matrix& a, double s);
    Matrix operator+(double s, const Matrix& a);
    Matrix operator-(const Matrix& a, double s);
    Matrix operator-(double s, const Matrix& a);
    Matrix operator*(const Matrix& a, double s);
    Matrix operator*(double s, const Matrix& a);
    Matrix operator/(const Matrix& a, double s);

    Matrix operator-(const Matrix& a);

    Matrix multiply(const Matrix& a, Matrix& b);
    Vector multiply(const Matrix& a, const Vector& v);
    Vector multiply(const Vector& v, const Matrix& a);

    Matrix zeros(size_t n1, size_t n2);
    Matrix identity(size_t n1, size_t n2);
    Matrix outer(const Vector&a, Vector& b);

    bool operator==(const Matrix& a, const Matrix& b);
    bool operator!=(const Matrix& a, const Matrix& b);

    std::ostream& operator<<(std::ostream& os, const Matrix& m);
}

namespace std{
    string to_string(const GSL::Matrix& m);
}

#include "GSLpp/matrix_view.h"

#endif // NEW_MATRIX_GLSPP_LIB_H
