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
public:

    virtual ~BaseVector(){};
    BaseVector(){};
    BaseVector(const BaseVector& v) = default;
    BaseVector(BaseVector&& v) = default;

    BaseVector& operator=(const BaseVector&){ return *this;};
    BaseVector& operator=(BaseVector&&){ return *this;};
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
    Vector(const gsl_vector& v);
public:
    // Create an empty vector (no data at all)
    Vector();
    // Create a vector of size n
    Vector(const size_t n);
    // Create a new reference to the gsl_vector inside v
    // Do not allocate anything, only reference stuff!
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
    size_t dim() const;

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

    friend std::pair<Complex_Matrix, Vector> hermitian_eigen(
        const Complex_Matrix& A);
    friend std::pair<Complex_Matrix, Vector> general_hermitian_eigen(
        const Complex_Matrix& A, const Complex_Matrix& B);

    typedef std::allocator<double> allocator_type;
    typedef typename std::allocator<double>::value_type value_type;
    typedef typename std::allocator<double>::reference reference;
    typedef typename std::allocator<double>::const_reference const_reference;
    typedef typename std::allocator<double>::difference_type difference_type;
    typedef typename std::allocator<double>::size_type size_type;

    class const_iterator;
    class iterator {
    public:
        typedef typename std::allocator<double>::difference_type difference_type;
        typedef typename std::allocator<double>::value_type value_type;
        typedef typename std::allocator<double>::reference reference;
        typedef typename std::allocator<double>::pointer pointer;
        typedef std::random_access_iterator_tag iterator_category;
        iterator() = default;
        iterator(double* d) : data_m(d){};
        iterator(const iterator& it) = default;
        iterator(iterator&& it) = default;
        ~iterator() = default;

        iterator& operator=(const iterator&) = default;
        iterator& operator=(iterator&&) = default;
        bool operator==(const iterator&) const;
        bool operator!=(const iterator&) const;
        bool operator<(const iterator&) const;
        bool operator>(const iterator&) const;
        bool operator<=(const iterator&) const;
        bool operator>=(const iterator&) const;

        iterator& operator++();
        iterator operator++(int);
        iterator& operator--();
        iterator operator--(int);
        iterator& operator+=(size_type);
        iterator operator+(size_type) const;
        friend iterator operator+(size_type, const iterator&);
        iterator& operator-=(size_type);
        iterator operator-(size_type) const;
        difference_type operator-(iterator) const;

        reference operator*() const;
        friend class const_iterator;
    private:
        double* data_m;
    };

    class const_iterator{
    public:
        typedef typename std::allocator<double>::difference_type difference_type;
        typedef typename std::allocator<double>::value_type value_type;
        typedef typename std::allocator<double>::reference reference;
        typedef typename std::allocator<double>::pointer pointer;
        typedef std::random_access_iterator_tag iterator_category;


        const_iterator() = default;
        const_iterator(double* d) : data_m(d){};
        const_iterator(const const_iterator&) = default;
        const_iterator(const_iterator&&) = default;
        const_iterator(const iterator&);
        ~const_iterator() = default;

        const_iterator& operator=(const const_iterator&) = default;
        const_iterator& operator=(const_iterator&&) = default;
        bool operator==(const const_iterator&) const;
        bool operator!=(const const_iterator&) const;
        bool operator<(const const_iterator&) const; //optional
        bool operator>(const const_iterator&) const; //optional
        bool operator<=(const const_iterator&) const; //optional
        bool operator>=(const const_iterator&) const; //optional

        const_iterator& operator++();
        const_iterator operator++(int); //optional
        const_iterator& operator--(); //optional
        const_iterator operator--(int); //optional
        const_iterator& operator+=(size_type); //optional
        const_iterator operator+(size_type) const; //optional
        friend const_iterator operator+(size_type, const const_iterator&); //optional
        const_iterator& operator-=(size_type); //optional
        const_iterator operator-(size_type) const; //optional
        difference_type operator-(const_iterator) const; //optional

        const reference operator*() const;
    private:
        double* data_m;
    };

    typedef std::reverse_iterator<iterator> reverse_iterator;
    typedef std::reverse_iterator<const_iterator> const_reverse_iterator;

    iterator begin();
    const_iterator begin() const;
    const_iterator cbegin() const;
    iterator end();
    const_iterator end() const;
    const_iterator cend() const;
    reverse_iterator rbegin(); //optional
    const_reverse_iterator rbegin() const; //optional
    const_reverse_iterator crbegin() const; //optional
    reverse_iterator rend(); //optional
    const_reverse_iterator rend() const; //optional
    const_reverse_iterator crend() const; //optional

    reference front(); //optional
    const_reference front() const; //optional
    reference back(); //optional
    const_reference back() const; //optional
    template<class ...Args>
    void emplace_front(Args&&...); //optional
    template<class ...Args>
    void emplace_back(Args&&...); //optional
    void push_front(const double&); //optional
    void push_front(double&&); //optional
    void push_back(const double&); //optional
    void push_back(double&&); //optional
    void pop_front(); //optional
    void pop_back(); //optional
    const_reference operator[](size_type) const; //optional
    reference at(size_type); //optional
    const_reference at(size_type) const; //optional

    template<class ...Args>
    iterator emplace(const_iterator, Args&&...); //optional
    iterator insert(const_iterator, const double&); //optional
    iterator insert(const_iterator, double&&); //optional
    iterator insert(const_iterator, size_type, double&); //optional
    template<class iter>
    iterator insert(const_iterator, iter, iter); //optional
    iterator insert(const_iterator, std::initializer_list<double>); //optional
    iterator erase(const_iterator); //optional
    iterator erase(const_iterator, const_iterator); //optional
    void clear(); //optional
    template<class iter>
    void assign(iter, iter); //optional
    void assign(std::initializer_list<double>); //optional
    void assign(size_type, const double&); //optional
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

Vector::iterator operator+(std::allocator<double>::size_type, const Vector::iterator&);
Vector::const_iterator operator+(std::allocator<double>::size_type, const Vector::const_iterator&);
}

#endif //VECTOR_GSL_LIB_H
