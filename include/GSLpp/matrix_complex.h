#ifndef NEW_MATRIX_COMPLEX_GLSPP_LIB_H
#define NEW_MATRIX_COMPLEX_GLSPP_LIB_H

#include <gsl/gsl_matrix.h>
#include <utility>
#include <memory>
#include <iostream>
#include <string>

#include "GSLpp/vector_complex.h"
#include "GSLpp/complex.h"

namespace GSL{

    class Matrix_Complex {
    protected:
        std::unique_ptr<gsl_matrix_complex, decltype(&gsl_matrix_complex_free)> gsl_mat_m;

        Matrix_Complex() = delete;
        Matrix_Complex(gsl_matrix_complex* v);

    public:
        Matrix_Complex(const Matrix_Complex&) = delete;
        Matrix_Complex(Matrix_Complex&&) = default;
        Matrix_Complex& operator=(const Matrix_Complex&) = delete;
        Matrix_Complex& operator=(Matrix_Complex&&) = default;
        virtual ~Matrix_Complex() = default;

        Matrix_Complex(size_t n1, size_t n2);
        Matrix_Complex(size_t n1, size_t n2, Complex val);

        Matrix_Complex(std::initializer_list<Vector_Complex> l);
        // Matrix_Complex(std::initializer_list<std::initializer_list<Complex>> l);

        gsl_matrix_complex* gsl_data();
        const gsl_matrix_complex* gsl_data() const;

        friend bool operator==(const Matrix_Complex& a, const Matrix_Complex& b);
        friend bool operator!=(const Matrix_Complex& a, const Matrix_Complex& b);

        Matrix_Complex& copy(const Matrix_Complex& other);
        Matrix_Complex& transpose_copy(const Matrix_Complex& other);
        Matrix_Complex& swap(const Matrix_Complex& other);

        Matrix_Complex& swap_rows(size_t i, size_t j);
        Matrix_Complex& swap_columns(size_t i, size_t j);
        Matrix_Complex& swap_rowcol(size_t i, size_t j);

        Matrix_Complex& transpose();
        Matrix_Complex& T();

        Matrix_Complex& hermitian_transpose();
        Matrix_Complex& H();

        Matrix_Complex clone() const;

        size_t num_rows() const;
        size_t num_columns() const;
        std::pair<size_t, size_t> dim() const;

        Matrix_Complex& set_all(Complex val);
        Matrix_Complex& set_zero();
        Matrix_Complex& set(size_t i, size_t j, Complex val);
        Matrix_Complex& set_identity();
        Complex get(size_t i, size_t j) const;

        bool isnull() const;
        bool ispos() const;
        bool isneg() const;
        bool isnonneg() const;

        Matrix_Complex& operator+=(const Matrix_Complex& other);
        Matrix_Complex& operator-=(const Matrix_Complex& other);
        Matrix_Complex& operator*=(const Matrix_Complex& other);
        Matrix_Complex& operator/=(const Matrix_Complex& other);

        Matrix_Complex& operator+=(Complex s);
        Matrix_Complex& operator-=(Complex s);
        Matrix_Complex& operator*=(Complex s);
        Matrix_Complex& operator/=(Complex s);

        Matrix_Complex& multiply(const Matrix_Complex& other);

        class View;
        class Const_View;

        View view();
        const View view() const;
        Const_View cview() const;

        View view(size_t k1, size_t k2, size_t n1, size_t n2);
        const View view(size_t k1, size_t k2, size_t n1, size_t n2) const;
        Const_View cview(size_t k1, size_t k2, size_t n1, size_t n2) const;

        Vector_Complex::View row(size_t row);
        Vector_Complex::Const_View row(size_t row) const;
        Vector_Complex::Const_View crow(size_t row) const;

        Vector_Complex::View column(size_t column);
        Vector_Complex::Const_View column(size_t column) const;
        Vector_Complex::Const_View ccolumn(size_t column) const;

        Vector_Complex::View subrow(size_t i, size_t offset, size_t n);
        Vector_Complex::Const_View subrow(size_t i, size_t offset, size_t n) const;
        Vector_Complex::Const_View csubrow(size_t i, size_t offset, size_t n) const;
        Vector_Complex::View subcolumn(size_t i, size_t offset, size_t n);
        Vector_Complex::Const_View subcolumn(size_t i, size_t offset, size_t n) const;
        Vector_Complex::Const_View csubcolumn(size_t i, size_t offset, size_t n) const;
        Vector_Complex::View diagonal();
        Vector_Complex::Const_View diagonal() const;
        Vector_Complex::Const_View cdiagonal() const;
        Vector_Complex::View subdiagonal(size_t k);
        Vector_Complex::Const_View subdiagonal(size_t k) const;
        Vector_Complex::Const_View csubdiagonal(size_t k) const;
        Vector_Complex::View superdiagonal(size_t k);
        Vector_Complex::Const_View superdiagonal(size_t k) const;
        Vector_Complex::Const_View csuperdiagonal(size_t k) const;


        Vector_Complex::View operator[](size_t row);
        Vector_Complex::Const_View operator[](size_t row) const;

        Vector_Complex::View at(size_t row);
        Vector_Complex::Const_View at(size_t row) const;

        Complex& operator()(size_t i, size_t j);
        const Complex& operator()(size_t i, size_t j) const;

        Complex& at(size_t i, size_t j);
        const Complex& at(size_t i, size_t j) const;

        std::string to_string() const;
    };

    Matrix_Complex operator+(const Matrix_Complex& a, const Matrix_Complex& b);
    Matrix_Complex operator-(const Matrix_Complex& a, const Matrix_Complex& b);
    Matrix_Complex operator*(const Matrix_Complex& a, const Matrix_Complex& b);
    Matrix_Complex operator/(const Matrix_Complex& a, const Matrix_Complex& b);
    Matrix_Complex operator+(const Matrix_Complex& a, Complex s);
    Matrix_Complex operator+(Complex s, const Matrix_Complex& a);
    Matrix_Complex operator-(const Matrix_Complex& a, Complex s);
    Matrix_Complex operator-(Complex s, const Matrix_Complex& a);
    Matrix_Complex operator*(const Matrix_Complex& a, Complex s);
    Matrix_Complex operator*(Complex s, const Matrix_Complex& a);
    Matrix_Complex operator/(const Matrix_Complex& a, Complex s);

    Matrix_Complex operator-(const Matrix_Complex& a);

    Matrix_Complex multiply(const Matrix_Complex& a, Matrix_Complex& b);
    Vector_Complex multiply(const Matrix_Complex& a, const Vector_Complex& v);
    Vector_Complex multiply(const Vector_Complex& v, const Matrix_Complex& a);

    Matrix_Complex outer(const Vector_Complex&a, Vector_Complex& b);

    bool operator==(const Matrix_Complex& a, const Matrix_Complex& b);
    bool operator!=(const Matrix_Complex& a, const Matrix_Complex& b);

    std::ostream& operator<<(std::ostream& os, const Matrix_Complex& m);

}

namespace std {
    string to_string(const GSL::Matrix_Complex& m);
}

#include "GSLpp/matrix_complex_view.h"

#endif // NEW_MATRIX_COMPLEX_GLSPP_LIB_H
