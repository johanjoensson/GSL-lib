#ifndef VECTOR_GSL_LIB_H
#define VECTOR_GSL_LIB_H
#include <gsl/gsl_vector.h>
#include <iostream>

namespace GSL{class Vector; class Matrix;}
std::ostream& operator<< (std::ostream& os, const GSL::Vector& a);


/**************************************************************************//**
* A class for using GSL-vectors with a simpler interface than
* the default one.
* Also try to avoid using unnecessary amounts of memory.
*******************************************************************************/
namespace GSL{

/*******************************************************************************
* Do not allocate more vectors than are absolutely necessary
*******************************************************************************/
class Vector{
    // Store a reference to the gsl_vector
    gsl_vector* gsl_vec;
    // Store the number of copies of this vector we have in play
    int* count;
    Vector(gsl_vector& v);
    Vector(const gsl_vector& v);
    bool matrix = false;
public:
    // Create an empty vector (no data at all)
    Vector();
    // Create a vector of size n
    Vector(const size_t n);
    // Create a new reference to the gsl_vector inside v
    // Do not allocate anything, only add references!
    Vector(Vector& v);
    Vector(const Vector& v);
    Vector(Vector&& v);
    // Deallocate vector, keeping in mind that several vectors might reference
    // the same gsl_vector.
    ~Vector();

    void copy(const Vector& a);

    Vector& operator= (const Vector& a);
    Vector& operator= (Vector&& a);

    void normalize() const;
    double norm() const;

    double& operator[] (const int index);

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
    Vector operator+ (const Vector& b) const;
    Vector operator- (const Vector& b) const;
    // Element wise multiplication and division
    Vector operator* (const Vector& b) const;
    Vector operator/ (const Vector& b) const;
    // Scaling of vectors
    Vector operator* (const double& s) const;
    friend Vector operator*(const double& s, const Vector& a);
    Vector operator/ (const double& s) const;

    friend Vector operator- (const Vector& a);

    friend std::ostream& ::operator<< (std::ostream& os, const Vector& a);

    friend class Matrix;
    friend Vector operator* (const Vector& v, const Matrix& a);

    friend bool (operator==)(const Vector&, const Vector&);
    friend bool (operator!=)(const Vector&, const Vector&);

};

Vector operator*(const double& s, const Vector& a);
double dot(const Vector& a, const Vector& b);
Vector cross(const Vector& a, const Vector& b);
Vector operator- (const Vector& a);

bool (operator==)(const Vector&, const Vector&);
bool (operator!=)(const Vector&, const Vector&);

}

#endif //VECTOR_GSL_LIB_H
