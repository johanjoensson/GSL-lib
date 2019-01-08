#ifndef Complex_Vector_GSL_LIB_H
#define Complex_Vector_GSL_LIB_H
#include "complex.h"
#include "vector.h"
#include <gsl/gsl_vector.h>
#include <gsl/gsl_complex.h>
#include <iostream>
#include <vector>
#include <memory>

namespace GSL{class Complex_Vector; class Complex_Matrix;}


/**************************************************************************//**
* A class for using GSL-vectors with a simpler interface than
* the default one.
* Also try to avoid using unnecessary amounts of memory.
*******************************************************************************/
namespace GSL{

/*******************************************************************************
* Do not allocate more vectors than are absolutely necessary
*******************************************************************************/
class Complex_Vector : public BaseVector{
    // Store a reference to the gsl_vector
    std::shared_ptr<gsl_vector_complex> gsl_vec;

    // Store the number of copies of this vector we have in play
public:
    // Create an empty vector (no data at all)
    Complex_Vector() : BaseVector(), gsl_vec(nullptr){};
    // Create a vector of size n
    Complex_Vector(const size_t n);
    // Create a new reference to vector v
    // Do not allocate anything, only add references!
    Complex_Vector(const Complex_Vector& v);
    Complex_Vector(Complex_Vector&& v);
    Complex_Vector(const gsl_vector_complex& v);
    Complex_Vector(std::initializer_list<Complex>);
    // Deallocate vector, keeping in mind that several vectors might reference
    // the same gsl_vector.
    ~Complex_Vector();

    void copy(const Complex_Vector& a);

    Complex_Vector& operator= (const Complex_Vector& a);
    Complex_Vector& operator= (Complex_Vector&& a);

    void normalize() const;
    double norm() const;

    Complex operator[] (const size_t index);

    // Define dot and cross products of vectors
    friend Complex dot(const Complex_Vector& a, const Complex_Vector& b);
    friend Complex_Vector cross(const Complex_Vector& a, const Complex_Vector& b);

    Complex_Vector& operator+= (const Complex_Vector& b);
    Complex_Vector& operator-= (const Complex_Vector& b);
    Complex_Vector& operator*= (const Complex_Vector& b);
    Complex_Vector& operator/= (const Complex_Vector& b);
    Complex_Vector& operator*= (const double s);
    Complex_Vector& operator/= (const double s);


    // Basic arithmetic operations
    Complex_Vector operator+ (const Complex_Vector& b) const;
    Complex_Vector operator- (const Complex_Vector& b) const;
    // Element wise multiplication and division
    Complex_Vector operator* (const Complex_Vector& b) const;
    Complex_Vector operator/ (const Complex_Vector& b) const;
    // Scaling of vectors
    Complex_Vector operator* (const double& s) const;
    friend Complex_Vector operator*(const double& s, const Complex_Vector& a);
    Complex_Vector operator/ (const double& s) const;

    friend class Complex_Matrix;
    friend Complex_Vector operator* (const Complex_Vector& v, const Complex_Matrix& a);

    friend Complex_Vector operator- (const Complex_Vector& a);


    void set(size_t i, const Complex& z);
    Complex get(size_t i);

    friend bool (operator==)(const Complex_Vector&, const Complex_Vector&);
    friend bool (operator!=)(const Complex_Vector&, const Complex_Vector&);

    std::string to_string() const;

};

Complex_Vector operator*(const double& s, const Complex_Vector& a);
Complex dot(const Complex_Vector& a, const Complex_Vector& b);
Complex_Vector cross(const Complex_Vector& a, const Complex_Vector& b);
Complex_Vector operator- (const Complex_Vector& a);

bool operator==(const Complex_Vector&, const Complex_Vector&);
bool operator!=(const Complex_Vector&, const Complex_Vector&);

}

#endif //Complex_Vector_GSL_LIB_H
