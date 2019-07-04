#ifndef MATRIX_TEMPLATE_GSL_LIB_H
#define MATRIX_TEMPLATE_GSL_LIB_H
#include "complex_template.h"
#include "vector_template.h"
#include <gsl/gsl_matrix.h>
#include <gsl/gsl_matrix.h>
#include <gsl/gsl_complex.h>
#include <iostream>
#include <memory>
#include <utility>

/**************************************************************************//**
* A class for using GSL-matrices with a simpler interface than
* the default one.
* Also try to avoid using unnecessary amounts of memory.
*******************************************************************************/

namespace GSL{

    template<class T, class GSL_MAT, class GSL_VEC, class A> class Matrix_t;
    template<class T, class GSL_VEC, class A> class Vector_t;
    template<class T, class GSL_COMPLEX> class Complex_t;

    class Permutation;
    template<class T, class GSL_MAT, class GSL_VEC, class A> class Matrix_t;
    using Matrix = Matrix_t<double, gsl_matrix, gsl_vector, std::allocator<double>>;
    using Matrix_ld = Matrix_t<long double, gsl_matrix_long_double, gsl_vector_long_double, std::allocator<long double>>;
    using Matrix_f = Matrix_t<float, gsl_matrix_float, gsl_vector_float, std::allocator<float>>;
    using Matrix_i = Matrix_t<int, gsl_matrix_int, gsl_vector_int, std::allocator<int>>;
    using Matrix_ui = Matrix_t<unsigned int, gsl_matrix_uint, gsl_vector_uint, std::allocator<unsigned int>>;
    using Matrix_l = Matrix_t<long, gsl_matrix_long, gsl_vector_long, std::allocator<long>>;
    using Matrix_ul = Matrix_t<unsigned long, gsl_matrix_ulong, gsl_vector_ulong, std::allocator<unsigned long>>;
    using Matrix_s = Matrix_t<short, gsl_matrix_short, gsl_vector_short, std::allocator<short>>;
    using Matrix_us = Matrix_t<unsigned short, gsl_matrix_ushort, gsl_vector_ushort, std::allocator<unsigned short>>;
    using Matrix_c = Matrix_t<char, gsl_matrix_char, gsl_vector_char, std::allocator<char>>;
    using Matrix_uc = Matrix_t<unsigned char, gsl_matrix_uchar, gsl_vector_uchar, std::allocator<unsigned char>>;
    using Matrix_cx = Matrix_t<GSL::Complex_t<double, gsl_complex>, gsl_matrix_complex, gsl_vector_complex, std::allocator<gsl_complex>>;
    using Matrix_cxld = Matrix_t<GSL::Complex_t<long double, gsl_complex_long_double>, gsl_matrix_complex_long_double,
        gsl_vector_complex_long_double, std::allocator<gsl_complex_long_double>>;
    using Matrix_cxf = Matrix_t<GSL::Complex_t<float, gsl_complex_float>, gsl_matrix_complex_float,
        gsl_vector_complex_float, std::allocator<gsl_complex_float>>;

    Matrix cholesky_decomp(const Matrix&);
    Matrix_cx cholesky_decomp(const Matrix_cx&);

    Matrix lu_inverse(const Matrix& a);
    Matrix_cx lu_inverse(const Matrix_cx& a);
    std::pair<Matrix, Permutation> lu_decomp(const Matrix& a);
    std::pair<Matrix_cx, Permutation> lu_decomp(const Matrix_cx& a);

    std::pair<Matrix_cx, Vector_t<double, gsl_vector, std::allocator<double>>> hermitian_eigen(const Matrix_cx&);

    std::pair<Matrix_cx, Vector_t<double, gsl_vector, std::allocator<double>>> general_hermitian_eigen(const Matrix_cx&,
            const Matrix_cx&);

template<class T, class GSL_MAT, class GSL_VEC, class A = std::allocator<T>>
class Matrix_t {
    // Store a reference to the gsl_matrix
    friend class Vector_t<T, GSL_VEC, A>;
    std::shared_ptr<GSL_MAT> gsl_mat;
    Matrix_t(const GSL_MAT& v);
    Vector_t<T, GSL_VEC, A> v_m;


public:
    typedef A allocator_type;
    typedef T value_type;
    typedef typename A::reference reference;
    typedef typename A::const_reference const_reference;
    typedef typename A::difference_type difference_type;
    typedef typename A::size_type size_type;

    // Create an empty matrix (no data at all)
    explicit Matrix_t();
    // Create a matrix of size n
    Matrix_t(const size_type n1, const size_type n2);
    // Create a new reference to the gsl_matrix inside v
    // Do not allocate anything, only reference stuff!
    Matrix_t(const Matrix_t& v) = default;
    Matrix_t(Matrix_t&& v) = default;
    Matrix_t(std::initializer_list<std::initializer_list<T>>);
    Matrix_t(std::initializer_list<GSL::Vector_t<T, GSL_VEC, A>>);
    ~Matrix_t() = default;

    // operator GSL_MAT() const {return *this->gsl_mat;};
    operator GSL_MAT() const;

    // Actually copy data from the other matrix, don't just reference it
    void copy(const Matrix_t& a);

    Matrix_t& operator= (const Matrix_t& a);
    Matrix_t& operator= (Matrix_t&& a);

    std::pair<size_type, size_type> dim() const;
    std::pair<size_type, size_type> size() const;


    Matrix_t& operator+= (const Matrix_t& b);
    Matrix_t& operator-= (const Matrix_t& b);
    Matrix_t& operator*= (const Matrix_t& b);
    Matrix_t& operator/= (const Matrix_t& b);
    Matrix_t& operator*= (const T& s);
    Matrix_t& operator/= (const T& s);


    // Basic arithmetic operations
    Matrix_t operator+(const Matrix_t& b) const;
    Matrix_t operator-(const Matrix_t& b) const;
    Matrix_t operator*(const Matrix_t& b) const;
    Matrix_t operator/(const Matrix_t& b) const;
    Matrix_t operator*(const T s) const;
    Matrix_t operator/(const T s) const;
    Matrix_t operator-() const;

    friend Matrix_t operator*(const T& s, const Matrix_t& m)
    {
        return m*s;
    };

    std::string to_string() const;
    friend std::ostream& operator<<(std::ostream& os, const Matrix_t& z)
    {
        return os << z.to_string();
    };

    Vector_t<T, GSL_VEC, A> operator*(const Vector_t<T, GSL_VEC, A>& v);

    bool operator==(const Matrix_t&) const;
    bool operator!=(const Matrix_t&) const;

    Matrix_t transpose() const;
    Matrix_t hermitian_transpose() const;

    Matrix_t inverse() const;

    Vector_t<T, GSL_VEC, A>& get_row(const difference_type i);
    Vector_t<T, GSL_VEC, A>& get_col(const difference_type i);

    class iterator {
    public:
        typedef typename A::difference_type difference_type;
        typedef Vector_t<T, GSL_VEC, A> value_type;
        typedef Vector_t<T, GSL_VEC, A>& reference;
        typedef typename A::pointer pointer;
        typedef std::random_access_iterator_tag iterator_category;

        iterator() = default;
        iterator(Matrix_t& mat, const difference_type n = 0);
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
        iterator& operator+=(difference_type);
        iterator operator+(difference_type) const;
        friend iterator operator+(difference_type n, const iterator& it)
        {
            iterator tmp = it;
            tmp += n;
            return tmp;
        };
        iterator& operator-=(difference_type);
        iterator operator-(difference_type) const;
        difference_type operator-(iterator) const;


        reference operator*();
        friend class const_iterator;
    private:
        Matrix_t& mat_m;
        difference_type row_m;
    };

    class const_iterator{
    public:
        typedef typename A::difference_type difference_type;
        typedef const Vector_t<T, GSL_VEC, A> value_type;
        typedef const Vector_t<T, GSL_VEC, A>& reference;
        typedef const Vector_t<T, GSL_VEC, A>* pointer;
        typedef std::random_access_iterator_tag iterator_category;


        const_iterator() = default;
        const_iterator(Matrix_t& mat, const difference_type n = 0);
        const_iterator(const const_iterator&) = default;
        const_iterator(const_iterator&&) = default;
        const_iterator(const iterator&);
        ~const_iterator() = default;

        const_iterator& operator=(const const_iterator&) = default;
        const_iterator& operator=(const_iterator&&) = default;
        bool operator==(const const_iterator&) const;
        bool operator!=(const const_iterator&) const;
        bool operator<(const const_iterator&) const;
        bool operator>(const const_iterator&) const;
        bool operator<=(const const_iterator&) const;
        bool operator>=(const const_iterator&) const;

        const_iterator& operator++();
        const_iterator operator++(int);
        const_iterator& operator--();
        const_iterator operator--(int);
        const_iterator& operator+=(difference_type);
        const_iterator operator+(difference_type) const;
        friend const_iterator operator+(difference_type n, const const_iterator& it)
        {
            const_iterator tmp = it;
            tmp += n;
            return tmp;
        };
        const_iterator& operator-=(difference_type);
        const_iterator operator-(difference_type) const;
        difference_type operator-(const_iterator) const;

        reference operator*()const;
    private:
        Matrix_t& mat_m;
        difference_type row_m;
    };


    typedef std::reverse_iterator<iterator> reverse_iterator;
    typedef std::reverse_iterator<const_iterator> const_reverse_iterator;

    iterator begin();
    const_iterator begin() const;
    const_iterator cbegin() const;
    iterator end();
    const_iterator end() const;
    const_iterator cend() const;
    reverse_iterator rbegin();
    const_reverse_iterator rbegin() const;
    const_reverse_iterator crbegin() const;
    reverse_iterator rend();
    const_reverse_iterator rend() const;
    const_reverse_iterator crend() const;

    Vector_t<T, GSL_VEC, A>& operator[] (const size_type index);
    const Vector_t<T, GSL_VEC, A>& operator[] (const size_type index) const;

    Vector_t<T, GSL_VEC, A>& front();
    const Vector_t<T, GSL_VEC, A>& front() const;
    Vector_t<T, GSL_VEC, A>& back();
    const Vector_t<T, GSL_VEC, A>& back() const;
    Vector_t<T, GSL_VEC, A>& at(size_type);
    const Vector_t<T, GSL_VEC, A>& at(size_type) const;
    reference at(size_type, size_type);
    const_reference at(size_type, size_type) const;

    friend Matrix cholesky_decomp(const Matrix&);

    friend Matrix_cx GSL::cholesky_decomp(const Matrix_cx&);

    friend Matrix GSL::lu_inverse(const Matrix& a);
    friend Matrix_cx GSL::lu_inverse(const Matrix_cx& a);
    friend std::pair<Matrix, Permutation> GSL::lu_decomp(const Matrix& a);
    friend std::pair<Matrix_cx, Permutation> GSL::lu_decomp(const Matrix_cx& a);

    friend std::pair<Matrix_cx, Vector_t<double, gsl_vector, std::allocator<double>>> hermitian_eigen(const Matrix_cx&);

    friend std::pair<Matrix_cx, Vector_t<double, gsl_vector, std::allocator<double>>>general_hermitian_eigen(const Matrix_cx&,
            const Matrix_cx&);
};


}
#endif //MATRIX_TEMPLATE_GSL_LIB_H
