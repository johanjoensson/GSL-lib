#ifndef VECTOR_TEMPLATE_GSL_LIB_H
#define VECTOR_TEMPLATE_GSL_LIB_H
#include "complex_template.h"
#include "matrix_template.h"
#include <gsl/gsl_vector.h>
#include <gsl/gsl_matrix.h>
#include <gsl/gsl_complex.h>
#include <iostream>
#include <memory>

/**************************************************************************//**
* A class for using GSL-vectors with a simpler interface than
* the default one.
* Also try to avoid using unnecessary amounts of memory.
*******************************************************************************/
namespace GSL{

    template<class T, class GSL_MAT, class GSL_VEC, class A> class Matrix_t;
    template<class T, class GSL_VEC, class A> class Vector_t;
    template<class T, class GSL_COMPLEX> class Complex_t;

    using Vector = Vector_t<double, gsl_vector, std::allocator<double>>;
    using Vector_ld = Vector_t<long double, gsl_vector_long_double, std::allocator<long double>>;
    using Vector_f = Vector_t<float, gsl_vector_float, std::allocator<float>>;
    using Vector_i = Vector_t<int, gsl_vector_int, std::allocator<int>>;
    using Vector_ui = Vector_t<unsigned int, gsl_vector_uint, std::allocator<unsigned int>>;
    using Vector_l = Vector_t<long, gsl_vector_long, std::allocator<long>>;
    using Vector_ul = Vector_t<unsigned long, gsl_vector_ulong, std::allocator<unsigned long>>;
    using Vector_s = Vector_t<short, gsl_vector_short, std::allocator<short>>;
    using Vector_us = Vector_t<unsigned short, gsl_vector_ushort, std::allocator<unsigned short>>;
    using Vector_c = Vector_t<char, gsl_vector_char, std::allocator<char>>;
    using Vector_uc = Vector_t<unsigned char, gsl_vector_uchar, std::allocator<unsigned char>>;
    using Vector_cx = Vector_t<Complex_t<double, gsl_complex>, gsl_vector_complex, std::allocator<gsl_complex>>;
    using Vector_cxld = Vector_t<Complex_t<long double, gsl_complex_long_double>, gsl_vector_complex_long_double, std::allocator<gsl_complex_long_double>>;
    using Vector_cxf = Vector_t<Complex_t<float, gsl_complex_float>, gsl_vector_complex_float, std::allocator<gsl_complex_float>>;

template<class T, class GSL_VEC, class A = std::allocator<T>>
class Vector_t {
    // Store a reference to the gsl_vector
    std::shared_ptr<GSL_VEC> gsl_vec;
    Vector_t(const GSL_VEC& v);
    Vector_t(const GSL_VEC* v);


    // template<class GSL_MAT>
    // friend class Matrix_t<T, GSL_MAT, GSL_VEC, A>;
    friend class Matrix_t<double, gsl_matrix, gsl_vector, std::allocator<double>>;
    friend class Matrix_t<long double, gsl_matrix_long_double, gsl_vector_long_double, std::allocator<long double>>;
    friend class Matrix_t<T, gsl_matrix_float, gsl_vector_float, A>;
    friend class Matrix_t<T, gsl_matrix_int, gsl_vector_int, A>;
    friend class Matrix_t<T, gsl_matrix_uint, gsl_vector_uint, A>;
    friend class Matrix_t<T, gsl_matrix_long, gsl_vector_long, A>;
    friend class Matrix_t<T, gsl_matrix_ulong, gsl_vector_ulong, A>;
    friend class Matrix_t<T, gsl_matrix_short, gsl_vector_short, A>;
    friend class Matrix_t<T, gsl_matrix_ushort, gsl_vector_ushort, A>;
    friend class Matrix_t<T, gsl_matrix_char, gsl_vector_char, A>;
    friend class Matrix_t<T, gsl_matrix_uchar, gsl_vector_uchar, A>;
    friend class Matrix_t<T, gsl_matrix_complex, gsl_vector_complex, A>;
    friend class Matrix_t<T, gsl_matrix_complex_long_double, gsl_vector_complex_long_double, A>;
    friend class Matrix_t<T, gsl_matrix_complex_float, gsl_vector_complex_float, A>;
public:
    typedef A allocator_type;
    typedef T value_type;
    typedef typename A::reference reference;
    typedef typename A::const_reference const_reference;
    typedef typename A::difference_type difference_type;
    typedef typename A::size_type size_type;

    // Create an empty vector (no data at all)
    explicit Vector_t() : gsl_vec(nullptr){};
    // Create a vector of size n
    explicit Vector_t(const size_type n);
    // Create a new reference to the gsl_vector inside v
    // Do not allocate anything, only reference stuff!
    Vector_t(const Vector_t&) = default;
    Vector_t(Vector_t&&) = default;
    Vector_t(std::initializer_list<T>);
    // Deallocate vector, keeping in mind that several vectors might reference
    // the same gsl_vector.
    ~Vector_t() = default;

    // operator GSL_VEC() const {return *this->gsl_vec;};
    operator GSL_VEC() const;

    size_type size() const;
    size_type dim() const;
    // Actually copy data from the other vector, don't just reference it
    void copy(const Vector_t& a);

    Vector_t& operator= (Vector_t&& a);
    Vector_t& operator= (const Vector_t& a);

    template<class S> S norm() const;
    template <class S>
    void normalize();


    // Define dot and cross products of vectors
    T dot(const Vector_t& b) const;
    Vector_t cross(const Vector_t& b) const;

    Vector_t& operator+= (const Vector_t& b);
    Vector_t& operator-= (const Vector_t& b);
    Vector_t& operator*= (const Vector_t& b);
    Vector_t& operator/= (const Vector_t& b);
    Vector_t& operator*= (const T& s);
    Vector_t& operator/= (const T& s);


    // Basic arithmetic operations
    Vector_t operator+(const Vector_t& b) const;
    Vector_t operator-(const Vector_t& b) const;
    Vector_t operator*(const Vector_t& b) const;
    Vector_t operator/(const Vector_t& b) const;
    Vector_t operator*(const T s) const;
    Vector_t operator/(const T s) const;
    Vector_t operator-() const;

    friend Vector_t operator*(const T& s, const Vector_t& v)
    {
        return v*s;
    };

    std::string to_string() const;
    friend std::ostream& operator<<(std::ostream& os, const Vector_t& z)
    {
        return os << z.to_string();
    };

    template<class GSL_MAT>
    Vector_t operator*(const Matrix_t<T, GSL_MAT, GSL_VEC, A>& m);

    bool operator==(const Vector_t&) const;
    bool operator!=(const Vector_t&) const;


    friend std::pair<Matrix_t<Complex_t<double, gsl_complex>, gsl_matrix_complex, gsl_vector_complex, std::allocator<gsl_complex>>, Vector>
        hermitian_eigen(const Matrix_t<Complex_t<double, gsl_complex>, gsl_matrix_complex, gsl_vector_complex, std::allocator<gsl_complex>>&);
    friend std::pair<Matrix_t<Complex_t<double, gsl_complex>, gsl_matrix_complex, gsl_vector_complex, std::allocator<gsl_complex>>, Vector>
        general_hermitian_eigen(const Matrix_t<Complex_t<double, gsl_complex>, gsl_matrix_complex, gsl_vector_complex, std::allocator<gsl_complex>>&,
            const Matrix_t<Complex_t<double, gsl_complex>, gsl_matrix_complex, gsl_vector_complex, std::allocator<gsl_complex>>&);


    class const_iterator;
    class iterator {
    public:
        typedef typename A::difference_type difference_type;
        typedef typename A::value_type value_type;
        typedef typename A::reference reference;
        typedef typename A::pointer pointer;
        typedef std::random_access_iterator_tag iterator_category;
        iterator() = default;
        iterator(pointer d, size_type s = 1) : stride(s), data_m(d){};
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
        friend iterator operator+(size_type n, const iterator& it)
        {
            iterator tmp = it;
            tmp += n;
            return tmp;
        };
        iterator& operator-=(size_type);
        iterator operator-(size_type) const;
        difference_type operator-(iterator) const;

        reference operator*() const;
        friend class const_iterator;
    private:
        size_type stride;
        pointer data_m;
    };

    class const_iterator{
    public:
        typedef typename A::difference_type difference_type;
        typedef const typename A::value_type value_type;
        typedef typename A::const_reference reference;
        typedef typename A::const_pointer pointer;
        typedef std::random_access_iterator_tag iterator_category;


        const_iterator() = default;
        const_iterator(pointer d, size_type s = 1) : stride(s), data_m(d){};
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
        const_iterator& operator+=(size_type);
        const_iterator operator+(size_type) const;
        friend const_iterator operator+(size_type n, const const_iterator& it)
        {
            const_iterator tmp = it;
            tmp += n;
            return tmp;
        };
        const_iterator& operator-=(size_type);
        const_iterator operator-(size_type) const;
        difference_type operator-(const_iterator) const;

        reference operator*() const;
    private:
        size_type stride;
        pointer data_m;
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

    reference operator[] (const size_type index);
    const_reference operator[] (const size_type index) const;

    reference front();
    const_reference front() const;
    reference back();
    const_reference back() const;
    reference at(size_type);
    const_reference at(size_type) const;

    template<class iter>
    void assign(iter, iter);
    void assign(std::initializer_list<value_type>);
    void assign(size_type, const_reference);
};

template<class T, class GSL_VEC, class A>
struct Vector_hasher_t{
	size_t operator()(const GSL::Vector_t<T, GSL_VEC, A> &v) const
	{
		size_t res = v.size();
		for(size_t i = 0; i < v.size(); i++){
			res += std::hash<T>()(v[i]) ^ std::hash<size_t>()(i);
		}
		return res;
	}
};

using Vector_hasher = Vector_hasher_t<double, gsl_vector, std::allocator<double>>;
using Vector_f_hasher = Vector_hasher_t<float, gsl_vector_float, std::allocator<float>>;
using Vector_ld_hasher = Vector_hasher_t<long double, gsl_vector_long_double, std::allocator<long double>>;
using Vector_s_hasher = Vector_hasher_t<short, gsl_vector_short, std::allocator<short>>;
using Vector_us_hasher = Vector_hasher_t<unsigned short, gsl_vector_ushort, std::allocator<unsigned short>>;
using Vector_c_hasher = Vector_hasher_t<char, gsl_vector_char, std::allocator<char>>;
using Vector_uc_hasher = Vector_hasher_t<unsigned char, gsl_vector_uchar, std::allocator<unsigned char>>;
using Vector_i_hasher = Vector_hasher_t<int, gsl_vector_int, std::allocator<int>>;
using Vector_ui_hasher = Vector_hasher_t<unsigned int, gsl_vector_uint, std::allocator<unsigned int>>;
using Vector_l_hasher = Vector_hasher_t<long, gsl_vector_long, std::allocator<long>>;
using Vector_ul_hasher = Vector_hasher_t<unsigned long, gsl_vector_ulong, std::allocator<unsigned long>>;
using Vector_cx_hasher = Vector_hasher_t<GSL::Complex_t<double, gsl_complex>, gsl_vector_complex, std::allocator<gsl_complex>>;
using Vector_cxf_hasher = Vector_hasher_t<GSL::Complex_t<float, gsl_complex_float>, gsl_vector_complex_float, std::allocator<gsl_complex_float>>;
using Vector_cxld_hasher = Vector_hasher_t<GSL::Complex_t<long double, gsl_complex_long_double>, gsl_vector_long_double, std::allocator<gsl_complex_long_double>>;

}
#endif //VECTOR_TEMPLATE_GSL_LIB_H
