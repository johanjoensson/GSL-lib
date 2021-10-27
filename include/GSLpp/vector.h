#ifndef NEW_VECTOR_GLSPP_LIB_H
#define NEW_VECTOR_GLSPP_LIB_H

#include <gsl/gsl_vector.h>
#include <utility>
#include <memory>
#include <iostream>
#include <string>

namespace GSL{

class Vector{
private:
    std::unique_ptr<gsl_vector, decltype(&gsl_vector_free)> gsl_vec_m;
    Vector(gsl_vector* v);
protected:
    Vector() = default;

public:
    Vector(const Vector&) = default;
    Vector(Vector&& other) = default;
    Vector& operator=(const Vector&) = default;
    Vector& operator=(Vector&& other) = default;
    ~Vector() = default;

    Vector(size_t n);
    Vector(size_t n, double val);

    Vector(std::initializer_list<double> l);

    gsl_vector* gsl_data();
    const gsl_vector* gsl_data() const;

    void copy(const Vector& other);

    void swap(Vector& other);

    void swap_elements(size_t i, size_t j);

    void reverse();

    Vector clone() const;

    size_t size() const;

    void set_all(double val);
    void set_zero();
    void set(size_t i, double val);
    void set_basis(size_t i);
    double get(size_t i) const;

    double& operator[](const size_t i);
    const double& operator[](const size_t i) const;
    double& at(const size_t i);
    const double& at(const size_t i) const;

    Vector& operator+=(const Vector& other);
    Vector& operator-=(const Vector& other);
    Vector& operator*=(const Vector& other);
    Vector& operator/=(const Vector& other);

    Vector& operator+=(double s);
    Vector& operator-=(double s);
    Vector& operator*=(double s);
    Vector& operator/=(double s);

    Vector operator-() const;

    double max() const;
    double min() const;
    std::pair<double, double> minmax() const;

    size_t max_index() const;
    size_t min_index() const;
    std::pair<size_t, size_t> minmax_index() const;

    bool isnull() const;
    bool ispos() const;
    bool isneg() const;
    bool isnonneg() const;

    friend double norm(const Vector& a);
    double norm() const;
    friend double norm2(const Vector& a);
    double norm2() const;
    friend double l1_norm(const Vector& a);
    double l1_norm() const;

    friend double dot(const Vector& a, const Vector& b);
    friend Vector cross(const Vector& a, const Vector& b);

    friend bool operator==(const Vector& a, const Vector& b);
    friend bool operator!=(const Vector& a, const Vector& b);

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

    std::string to_string() const;

};


std::ostream& operator<<(std::ostream& os, const Vector& v);

Vector operator+(const Vector& a, const Vector& b);
Vector operator-(const Vector& a, const Vector& b);
Vector operator*(const Vector& a, const Vector& b);
Vector operator/(const Vector& a, const Vector& b);
Vector operator+(const Vector& a, double s);
Vector operator+(double s, const Vector& a);
Vector operator-(const Vector& a, double s);
Vector operator-(double s, const Vector& a);
Vector operator*(const Vector& a, double s);
Vector operator*(double s, const Vector& a);
Vector operator/(const Vector& a, double s);

Vector zeros(size_t n);
Vector unit(size_t n, size_t i);

double dot(const Vector& a, const Vector& b);
Vector cross(const Vector& a, const Vector& b);


double norm(const Vector& a);
double norm2(const Vector& a);
double l1_norm(const Vector& a);

Vector normalize(const Vector& a);
Vector mirror(const Vector& v, const Vector& a);

bool operator==(const Vector& a, const Vector& b);
bool operator!=(const Vector& a, const Vector& b);

} // namespace GSL

#include "GSLpp/vector_view.h"

namespace std {
void swap(GSL::Vector&a, GSL::Vector& b);

string to_string(const GSL::Vector& v);

} // namespace std

#endif // VECTOR_GSLPP_LIB_H
