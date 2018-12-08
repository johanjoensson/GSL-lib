#ifndef VECTOR_GSL_LIB_H
#define VECTOR_GSL_LIB_H
#include <gsl/gsl_vector.h>
#include <iostream>
#include <memory>

namespace GSL{class Vector; class Matrix; class Complex_Matrix; class BaseMatrix;}


/**************************************************************************//**
* A class for using GSL-vectors with a simpler interface than
* the default one.
* Also try to avoid using unnecessary amounts of memory.
*******************************************************************************/
namespace GSL{

// Abstract base class representing all types of vectors.
class BaseVector{
protected:
    // Special care has to be taken if this vector is part of a matrix
    // e.g., this vector is a row or column in a matrix
public:

    virtual ~BaseVector(){};
//    virtual void copy(const BaseVector& v);
    virtual double norm() const = 0;
    virtual void normalize() const = 0;

    friend std::ostream& operator<< (std::ostream& os, const BaseVector& a);
    virtual std::string to_string() const = 0;

    friend class BaseMatrix;
};
std::ostream& operator<< (std::ostream& os, const GSL::BaseVector& a);

// Class representing vectors of real numbers
class Vector : public BaseVector{
    // Store a reference to the gsl_vector
//    gsl_vector* gsl_vec;
    std::shared_ptr<gsl_vector> gsl_vec;
    Vector(gsl_vector& v);
    Vector(const gsl_vector& v);
public:
    // Create an empty vector (no data at all)
    Vector();
    // Create a vector of size n
    Vector(const size_t n);
    // Create a new reference to the gsl_vector inside v
    // Do not allocate anything, only reference stuff!
    Vector(Vector& v);
    Vector(const Vector& v);
    Vector(Vector&& v);
    Vector(std::initializer_list<double>);
    // Deallocate vector, keeping in mind that several vectors might reference
    // the same gsl_vector.
    ~Vector();

    // Actually copy data from the other vector, don't just reference it
    void copy(const Vector& a);

    Vector& operator= (const Vector& a);
    Vector& operator= (Vector&& a);

    void normalize() const;
    double norm() const;

    double& operator[] (const size_t index);

    // Define dot and cross products of vectors
    friend double dot(const Vector& a, const Vector& b);
    friend Vector cross(const Vector& a, const Vector& b);

    Vector& operator+= (const Vector& b);
    Vector& operator-= (const Vector& b);
    Vector& operator*= (const Vector& b);
    Vector& operator/= (const Vector& b);
    Vector& operator*= (const double s);
    Vector& operator/= (const double s);


    // Basic arithmetic operations
    friend Vector operator+(Vector a, const Vector& b);
    friend Vector operator-(Vector a, const Vector& b);
    friend Vector operator*(Vector a, const Vector& b);
    friend Vector operator/(Vector a, const Vector& b);
    friend Vector operator*(Vector a, const double s);
    friend Vector operator/(Vector a, const double s);
    friend Vector operator- (const Vector& a);

    std::string to_string() const;

    friend class Matrix;
    friend Vector operator* (const Vector& v, const Matrix& a);

    friend bool (operator==)(const Vector&, const Vector&);
    friend bool (operator!=)(const Vector&, const Vector&);

    friend void hermitian_eigen(Complex_Matrix& eigves, Vector& eigvals);
    friend void general_hermitian_eigen(const Complex_Matrix& A, const Complex_Matrix& B, Complex_Matrix& eigvecs, Vector& eigvals);
};


Vector operator+(Vector a, const Vector& b);
Vector operator-(Vector a, const Vector& b);
Vector operator*(Vector a, const Vector& b);
Vector operator/(Vector a, const Vector& b);
Vector operator*(Vector a, const double s);
Vector operator/(Vector a, const double s);
Vector operator*(const double s, Vector a);
double dot(const Vector& a, const Vector& b);
Vector cross(const Vector& a, const Vector& b);
Vector operator- (const Vector& a);

bool operator==(const Vector&, const Vector&);
bool operator!=(const Vector&, const Vector&);

}

#endif //VECTOR_GSL_LIB_H
