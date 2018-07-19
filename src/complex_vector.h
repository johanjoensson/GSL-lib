#ifndef Complex_Vector_GSL_LIB_H
#define Complex_Vector_GSL_LIB_H
#include "complex.h"
#include <gsl/gsl_vector.h>
#include <gsl/gsl_complex.h>
#include <iostream>
#include <vector>

namespace GSL{class Complex_Vector;}
std::ostream& operator<< (std::ostream& os, const GSL::Complex_Vector& a);


/**************************************************************************//**
* A class for using GSL-vectors with a simpler interface than
* the default one.
* Also try to avoid using unnecessary amounts of memory.
*******************************************************************************/
namespace GSL{

/*******************************************************************************
* Do not allocate more vectors than are absolutely necessary
*******************************************************************************/
class Complex_Vector{
    // Store a reference to the gsl_vector
    gsl_vector_complex* gsl_vec;
    // "Shortcut" to the data contained in the gsl_vector
    double* data;
    // Store the number of copies of this vector we have in play
    int* count;
public:
    // Create an empty vector (no data at all)
    Complex_Vector();
    // Create a vector of size n
    Complex_Vector(const size_t n);
    // Create a new reference to vector v
    // Do not allocate anything, only add references!
    Complex_Vector(Complex_Vector& v);
    Complex_Vector(const Complex_Vector& v);
    Complex_Vector(Complex_Vector&& v);
    // Deallocate vector, keeping in mind that several vectors might reference
    // the same gsl_vector.
    ~Complex_Vector();

    void copy(const Complex_Vector& a);

    Complex_Vector& operator= (const Complex_Vector& a);
    Complex_Vector& operator= (Complex_Vector&& a);

    void normalize() const;
    double norm() const;

    Complex operator[] (const int index);

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

    friend std::ostream& ::operator<< (std::ostream& os, const Complex_Vector& a);
};

Complex_Vector operator*(const double& s, const Complex_Vector& a);
Complex dot(const Complex_Vector& a, const Complex_Vector& b);
Complex_Vector cross(const Complex_Vector& a, const Complex_Vector& b);

}

#endif //Complex_Vector_GSL_LIB_H
