#ifndef NEW_VECTOR_COMPLEX_GLSPP_LIB_H
#define NEW_VECTOR_COMPLEX_GLSPP_LIB_H

#include <gsl/gsl_vector.h>
#include <utility>
#include <memory>
#include <iostream>
#include <string>

#include "GSLpp/complex.h"
#include "GSLpp/vector.h"

namespace GSL{

class Vector_Complex{
private:
    std::unique_ptr<gsl_vector_complex, decltype(&gsl_vector_complex_free)> gsl_vec_m;
    Vector_Complex(gsl_vector_complex* v);
protected:
    Vector_Complex() = default;

public:
    Vector_Complex(const Vector_Complex&) = default;
    Vector_Complex(Vector_Complex&& other) = default;
    Vector_Complex& operator=(const Vector_Complex&) = default;
    Vector_Complex& operator=(Vector_Complex&& other) = default;
    ~Vector_Complex() = default;

    Vector_Complex(size_t n);
    Vector_Complex(size_t n, Complex val);

    Vector_Complex(std::initializer_list<Complex> l);

    gsl_vector_complex* gsl_data();
    const gsl_vector_complex* gsl_data() const;

    void copy(const Vector_Complex& other);

    void swap(Vector_Complex& other);

    void swap_elements(size_t i, size_t j);

    void reverse();

    Vector_Complex clone() const;

    size_t size() const;

    void set_all(Complex val);
    void set_zero();
    void set(size_t i, Complex val);
    void set_basis(size_t i);
    Complex get(size_t i) const;

    Complex& operator[](const size_t i);
    const Complex& operator[](const size_t i) const;
    Complex& at(const size_t i);
    const Complex& at(const size_t i) const;

    Vector_Complex& conjugate();
    Vector_Complex& conj(){return this->conjugate();}

    Vector_Complex& operator+=(const Vector_Complex& other);
    Vector_Complex& operator-=(const Vector_Complex& other);
    Vector_Complex& operator*=(const Vector_Complex& other);
    Vector_Complex& operator/=(const Vector_Complex& other);

    Vector_Complex& operator+=(const Vector& other);
    Vector_Complex& operator-=(const Vector& other);
    Vector_Complex& operator*=(const Vector& other);
    Vector_Complex& operator/=(const Vector& other);

    Vector_Complex& operator+=(Complex s);
    Vector_Complex& operator-=(Complex s);
    Vector_Complex& operator*=(Complex s);
    Vector_Complex& operator/=(Complex s);

    Vector_Complex operator-() const;

/*
    double max() const;
    double min() const;
    std::pair<double, double> minmax() const;

    size_t max_index() const;
    size_t min_index() const;
    std::pair<size_t, size_t> minmax_index() const;
*/

    bool isnull() const;
    bool ispos() const;
    bool isneg() const;
    bool isnonneg() const;

    friend double norm(const Vector_Complex& a);
    double norm() const;
    friend double norm2(const Vector_Complex& a);
    double norm2() const;
    friend double l1_norm(const Vector_Complex& a);
    double l1_norm() const;

    friend Complex dot(const Vector_Complex& a, const Vector_Complex& b)
    {
        return dotc(a, b);
    }
    friend Complex dotc(const Vector_Complex& a, const Vector_Complex& b);
    friend Complex dotu(const Vector_Complex& a, const Vector_Complex& b);

    friend Vector_Complex cross(const Vector_Complex& a, const Vector_Complex& b);

    friend bool operator==(const Vector_Complex& a, const Vector_Complex& b);
    friend bool operator!=(const Vector_Complex& a, const Vector_Complex& b);

    class View;
    class Const_View;

    View view();

    const View view() const;

    View view(const size_t offset, const size_t size);

    const View view(const size_t offset, const size_t size) const;

    View view(const size_t offset, const size_t stride, const size_t size);

    const View view(const size_t offset, const size_t stride, const size_t size) const;

    Const_View cview() const;

    Const_View cview(const size_t offset, const size_t size) const;

    Const_View cview(const size_t offset, const size_t stride, const size_t size) const;

    Vector::View real();
    Vector::Const_View real() const;

    Vector::View imag();
    Vector::Const_View imag() const;

    std::string to_string() const;

    friend std::ostream& operator<<(std::ostream& os, const Vector_Complex& v);
};


std::ostream& operator<<(std::ostream& os, const Vector_Complex& v);

Vector_Complex operator+(const Vector_Complex& a, const Vector_Complex& b);
Vector_Complex operator-(const Vector_Complex& a, const Vector_Complex& b);
Vector_Complex operator*(const Vector_Complex& a, const Vector_Complex& b);
Vector_Complex operator/(const Vector_Complex& a, const Vector_Complex& b);

Vector_Complex operator+(const Vector_Complex& a, const Vector& b);
Vector_Complex operator+(const Vector& a, const Vector_Complex& b);
Vector_Complex operator-(const Vector_Complex& a, const Vector& b);
Vector_Complex operator-(const Vector& a, const Vector_Complex& b);
Vector_Complex operator*(const Vector_Complex& a, const Vector& b);
Vector_Complex operator*(const Vector& a, const Vector_Complex& b);
Vector_Complex operator/(const Vector_Complex& a, const Vector& b);
Vector_Complex operator/(const Vector& a, const Vector_Complex& b);

Vector_Complex operator+(const Vector_Complex& a, Complex s);
Vector_Complex operator+(Complex s, const Vector_Complex& a);
Vector_Complex operator-(const Vector_Complex& a, Complex s);
Vector_Complex operator-(Complex s, const Vector_Complex& a);
Vector_Complex operator*(const Vector_Complex& a, Complex s);
Vector_Complex operator*(Complex s, const Vector_Complex& a);
Vector_Complex operator/(const Vector_Complex& a, Complex s);


Vector_Complex zeros_complex(size_t n);
Vector_Complex unit_complex(size_t n, size_t i);


Complex dotc(const Vector_Complex& a, const Vector_Complex& b);
Complex dotu(const Vector_Complex& a, const Vector_Complex& b);
Vector_Complex cross(const Vector_Complex& a, const Vector_Complex& b);

double norm(const Vector_Complex& a);
double norm2(const Vector_Complex& a);
double l1_norm(const Vector_Complex& a);

Vector_Complex normalize(const Vector_Complex& a);
Vector_Complex mirror(const Vector_Complex& v, const Vector_Complex& a);

bool operator==(const Vector_Complex& a, const Vector_Complex& b);
bool operator!=(const Vector_Complex& a, const Vector_Complex& b);

} // namespace GSL

#include "GSLpp/vector_complex_view.h"

namespace std {
void swap(GSL::Vector_Complex&a, GSL::Vector_Complex& b);

string to_string(const GSL::Vector_Complex& v);

} // namespace std

#endif // VECTOR_GSLPP_LIB_H
