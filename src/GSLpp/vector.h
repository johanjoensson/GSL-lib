#ifndef VECTOR_GSLPP_LIB_H
#define VECTOR_GSLPP_LIB_H
#include <GSLpp/complex.h>
#include <gsl/gsl_vector.h>
#include <gsl/gsl_matrix.h>
#include <iostream>
#include <memory>
#include <functional>

/**************************************************************************//**
* A class for using GSL-vectors with a simpler interface than
* the default one.
* Also try to avoid using unnecessary amounts of memory.
*******************************************************************************/
namespace GSL{

    template<typename T, typename GSL_COMPLEX> class Complex_t;
    template<class D, class GSL_MAT, class GSL_VEC, class A> class Matrix_t;

    template<class T, class GSL_VEC, class A> class Vector_t;
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
class Vector_t
{
protected:
    // Store a reference to the gsl_vector
    std::shared_ptr<GSL_VEC> gsl_vec;
    Vector_t(const std::shared_ptr<GSL_VEC>& v);
    Vector_t(const GSL_VEC& v);
    Vector_t(const GSL_VEC* v);


    friend class Matrix_t<double, gsl_matrix, gsl_vector, std::allocator<double>>;
    friend class Matrix_t<long double, gsl_matrix_long_double, gsl_vector_long_double, std::allocator<long double>>;
    friend class Matrix_t<float, gsl_matrix_float, gsl_vector_float, std::allocator<float>>;
    friend class Matrix_t<int, gsl_matrix_int, gsl_vector_int, std::allocator<int>>;
    friend class Matrix_t<unsigned int, gsl_matrix_uint, gsl_vector_uint, std::allocator<unsigned int>>;
    friend class Matrix_t<long, gsl_matrix_long, gsl_vector_long, std::allocator<long>>;
    friend class Matrix_t<unsigned long, gsl_matrix_ulong, gsl_vector_ulong, std::allocator<unsigned long>>;
    friend class Matrix_t<short, gsl_matrix_short, gsl_vector_short, std::allocator<short>>;
    friend class Matrix_t<unsigned short, gsl_matrix_ushort, gsl_vector_ushort, std::allocator<unsigned short>>;
    friend class Matrix_t<char, gsl_matrix_char, gsl_vector_char, std::allocator<char>>;
    friend class Matrix_t<unsigned char, gsl_matrix_uchar, gsl_vector_uchar, std::allocator<unsigned char>>;
    friend class Matrix_t<GSL::Complex_t<double, gsl_complex>, gsl_matrix_complex, gsl_vector_complex, std::allocator<gsl_complex>>;
    friend class Matrix_t<GSL::Complex_t<long double, gsl_complex_long_double>, gsl_matrix_complex_long_double, gsl_vector_complex_long_double,  std::allocator<gsl_complex_long_double>>;
    friend class Matrix_t<GSL::Complex_t<float, gsl_complex_float>, gsl_matrix_complex_float, gsl_vector_complex_float, std::allocator<gsl_complex_float>>;
public:
    typedef A allocator_type;
    typedef T value_type;
    typedef GSL_VEC GSL_Vec;
    typedef typename A::pointer pointer;
    typedef typename A::reference reference;
    typedef typename A::const_reference const_reference;
    typedef typename A::difference_type difference_type;
    typedef typename A::size_type size_type;

    // Create an empty vector (no data at all)
    explicit Vector_t() : gsl_vec(nullptr){};
    // Create a vector of size n
    explicit Vector_t(const size_type n);
     explicit Vector_t(const size_type n, const value_type v);

    // Create a new reference to the gsl_vector inside v
    // Do not allocate anything, only reference stuff!
    Vector_t(const Vector_t&) = default;
    Vector_t(Vector_t&&) = default;
    Vector_t(std::initializer_list<T>);
    // Deallocate vector, keeping in mind that several vectors might reference
    // the same gsl_vector.
    ~Vector_t() = default;

    // operator GSL_VEC() const {return *this->gsl_vec;};
    operator GSL_VEC() const {return *this->gsl_vec;}

    size_type size() const {return this->gsl_vec->size;}
    size_type dim() const {return this->gsl_vec->size;}
    // Actually copy data from the other vector, don't just reference it
    Vector_t copy() const;
    Vector_t& copy(const Vector_t& a);

    Vector_t& operator= (Vector_t&& a) = default;
    Vector_t& operator= (const Vector_t& a) = default;

    template<class S=double> S norm() const;
    T norm2() const {return this->dot(*this);}

    template <class S=double>
    Vector_t& normalize() {return *this /= static_cast<value_type>(this->norm<S>());}


    // Define dot and cross products of vectors
    T dot(const Vector_t& b) const;
    Vector_t cross(const Vector_t& b) const
    {
        if(this->size() != 3 || b.size() != 3){
            throw std::runtime_error("Vector is not 3D in cross product.");
        }
        Vector_t res(3);
        res[0] = static_cast<T>((*this)[1]*b[2] - (*this)[2]*b[1]);
        res[1] = static_cast<T>((*this)[2]*b[0] - (*this)[0]*b[2]);
        res[2] = static_cast<T>((*this)[0]*b[1] - (*this)[1]*b[0]);

        return res;
    }

    template<class S = double>
    Vector_t mirror(const Vector_t& b) const
    {
        auto n = b/b.norm<S>();
        return *this - 2*this->dot(n)*n;
    }

    Vector_t& operator+= (const Vector_t& b);
    Vector_t& operator-= (const Vector_t& b);
    Vector_t& operator*= (const Vector_t& b);
    Vector_t& operator/= (const Vector_t& b);
    Vector_t& operator*= (const T& s);
    Vector_t& operator/= (const T& s);


    // Basic arithmetic operations
    Vector_t operator+(const Vector_t& b) const {Vector_t tmp; tmp.copy(*this); return tmp += b;}
    Vector_t operator-(const Vector_t& b) const {Vector_t tmp; tmp.copy(*this); return tmp -= b;}
    Vector_t operator*(const Vector_t& b) const {Vector_t tmp; tmp.copy(*this); return tmp *= b;}
    Vector_t operator/(const Vector_t& b) const {Vector_t tmp; tmp.copy(*this); return tmp /= b;}
    Vector_t operator*(const T s) const {Vector_t tmp; tmp.copy(*this); return tmp *= s;}
    Vector_t operator/(const T s) const {Vector_t tmp; tmp.copy(*this); return tmp /= s;}
    Vector_t operator-() const {Vector_t tmp(this->size(), 0); return tmp -= *this;}

    friend Vector_t operator*(const T& s, const Vector_t& v)
    {
        return v*s;
    };

    std::string to_string() const
    {
        std::string res("(");
        for(auto elem : *this){
            res += std::to_string(elem) + ", ";
        }
        res += ")";
        return res;
    }
    friend std::ostream& operator<<(std::ostream& os, const Vector_t& z)
    {
        return os << z.to_string();
    };

    template<class GSL_MAT>
    Vector_t operator*(const Matrix_t<T, GSL_MAT, GSL_VEC, A>& m) const;

    bool operator==(const Vector_t&) const;
    bool operator!=(const Vector_t& b) const {return !(*this == b);}


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
        bool operator==(const iterator& b) const {return this->data_m == b.data_m;}
        bool operator!=(const iterator& b) const {return !(this->data_m == b.data_m);}
        bool operator<(const iterator& b) const {return this->data_m < b.data_m;}
        bool operator>(const iterator& b) const {return this->data_m > b.data_m;}
        bool operator<=(const iterator& b) const {return !(this->data_m > b.data_m);}
        bool operator>=(const iterator& b) const {return !(this->data_m < b.data_m);}

        iterator& operator++() {this->data_m += stride; return *this;}
        iterator operator++(int) {auto tmp = *this; this->data_m += stride; return tmp;}
        iterator& operator--() {this->data_m -= stride; return *this;}
        iterator operator--(int) {auto tmp = *this; this->data_m -= stride; return tmp;}
        iterator& operator+=(difference_type n) {this->data_m += n*static_cast<difference_type>(stride); return *this;}
        iterator operator+(difference_type n) const {auto tmp = *this; return tmp += n;}
        friend iterator operator+(difference_type n, const iterator& it) {return it + n;}
        iterator& operator-=(difference_type n) {this->data_m -= n*static_cast<difference_type>(stride); return *this;}
        iterator operator-(difference_type n) const {auto tmp = *this; return tmp -= n;}
        difference_type operator-(iterator it) const {return (this->data_m - it.data_m)/static_cast<difference_type>(stride);}

        reference operator*() const {return *this->data_m;}
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
        bool operator==(const const_iterator& b) const {return this->data_m == b.data_m;}
        bool operator!=(const const_iterator& b) const {return !(this->data_m == b.data_m);}
        bool operator<(const const_iterator& b) const {return this->data_m < b.data_m;}
        bool operator>(const const_iterator& b) const {return this->data_m > b.data_m;}
        bool operator<=(const const_iterator& b) const {return !(this->data_m > b.data_m);}
        bool operator>=(const const_iterator& b) const {return !(this->data_m < b.data_m);}

        const_iterator& operator++() {this->data_m += stride; return *this;}
        const_iterator operator++(int) {auto tmp = *this; this->data_m += stride; return tmp;}
        const_iterator& operator--() {this->data_m -= stride; return *this;}
        const_iterator operator--(int) {auto tmp = *this; this->data_m -= stride; return tmp;}
        const_iterator& operator+=(difference_type n) {this->data_m += n*static_cast<difference_type>(stride); return *this;}
        const_iterator operator+(difference_type n) const {auto tmp = *this; return tmp += n;}
        friend const_iterator operator+(difference_type n, const const_iterator& it) {return it + n;}
        const_iterator& operator-=(difference_type n) {this->data_m -= n*static_cast<difference_type>(stride); return *this;}
        const_iterator operator-(difference_type n) const {auto tmp = *this; return tmp -= n;}
        difference_type operator-(const_iterator it) const {return (this->data_m - it.data_m)/static_cast<difference_type>(stride);}

        reference operator*() const {return *this->data_m;}
    private:
        size_type stride;
        pointer data_m;
    };


    typedef std::reverse_iterator<iterator> reverse_iterator;
    typedef std::reverse_iterator<const_iterator> const_reverse_iterator;

    iterator begin();
    const_iterator begin() const;
    const_iterator cbegin() const;
    iterator end() {return this->begin() += static_cast<difference_type>(this->size());}
    const_iterator end() const {return this->begin() += static_cast<difference_type>(this->size());}
    const_iterator cend() const {return this->cbegin() += static_cast<difference_type>(this->size());}
    reverse_iterator rbegin() {return reverse_iterator(this->end());}
    const_reverse_iterator rbegin() const {return const_reverse_iterator(this->end());}
    const_reverse_iterator crbegin() const {return const_reverse_iterator(this->cend());}
    reverse_iterator rend() {return reverse_iterator(this->begin());}
    const_reverse_iterator rend() const {return const_reverse_iterator(this->begin());}
    const_reverse_iterator crend() const {return const_reverse_iterator(this->cbegin());}

    reference operator[] (const size_type index) {return *(this->begin() + static_cast<difference_type>(index));}
    const_reference operator[] (const size_type index) const {return *(this->begin() + static_cast<difference_type>(index));}

    reference front() {return *this->begin();}
    const_reference front() const {return *this->cbegin();}
    reference back() {return *(--this->end());}
    const_reference back() const {return *(--this->cend());}
    reference at(const size_type index)
    {
        if(index >= this->size()){
            throw std::runtime_error("index out of range.\n");
        }
        return (*this)[index];
    }
    const_reference at(const size_type index) const
    {
        if(index >= this->size()){
            throw std::runtime_error("index out of range.\n");
        }
        return (*this)[index];
    }

    template<class iter>
    void assign(iter start, iter end)
    {
        size_type n_elem = static_cast<size_type>(end - start);
        if(n_elem != this->size()){
            *this = Vector_t(n_elem);
        }
        auto current = this->begin();
        for(iter elem = start; elem != end; elem++, current++){
            *current = *elem;
        }
    }

    void assign(std::initializer_list<value_type> l)
    {
        size_type n_elem = l.size();
        if(n_elem != this->size()){
            *this = Vector_t(n_elem);
        }
        auto current = this->begin();
        for(auto elem = l.begin(); elem != l.end(); elem++, current++){
            *current = *elem;
        }
    }

    void assign(size_type n_elem, const_reference val)
    {
        if(n_elem != this->size()){
            *this = Vector_t(n_elem);
        }
        auto current = this->begin();
        for(size_type i = 0; i < n_elem; current++, i++){
            *current = val;
        }
    }


    pointer data() { return reinterpret_cast<pointer>(gsl_vec->data);}
    size_t stride() { return gsl_vec->stride;}

    class View;

};

template<class D, class GSL_VEC, class A>
class Vector_t<D, GSL_VEC, A>::View : public Vector_t
{
    friend class Matrix_t<double, gsl_matrix, gsl_vector, std::allocator<double>>;
    friend class Matrix_t<long double, gsl_matrix_long_double, gsl_vector_long_double, std::allocator<long double>>;
    friend class Matrix_t<float, gsl_matrix_float, gsl_vector_float, std::allocator<float>>;
    friend class Matrix_t<int, gsl_matrix_int, gsl_vector_int, std::allocator<int>>;
    friend class Matrix_t<unsigned int, gsl_matrix_uint, gsl_vector_uint, std::allocator<unsigned int>>;
    friend class Matrix_t<long, gsl_matrix_long, gsl_vector_long, std::allocator<long>>;
    friend class Matrix_t<unsigned long, gsl_matrix_ulong, gsl_vector_ulong, std::allocator<unsigned long>>;
    friend class Matrix_t<short, gsl_matrix_short, gsl_vector_short, std::allocator<short>>;
    friend class Matrix_t<unsigned short, gsl_matrix_ushort, gsl_vector_ushort, std::allocator<unsigned short>>;
    friend class Matrix_t<char, gsl_matrix_char, gsl_vector_char, std::allocator<char>>;
    friend class Matrix_t<unsigned char, gsl_matrix_uchar, gsl_vector_uchar, std::allocator<unsigned char>>;
    friend class Matrix_t<GSL::Complex_t<double, gsl_complex>, gsl_matrix_complex, gsl_vector_complex, std::allocator<gsl_complex>>;
    friend class Matrix_t<GSL::Complex_t<long double, gsl_complex_long_double>, gsl_matrix_complex_long_double, gsl_vector_complex_long_double,  std::allocator<gsl_complex_long_double>>;
    friend class Matrix_t<GSL::Complex_t<float, gsl_complex_float>, gsl_matrix_complex_float, gsl_vector_complex_float, std::allocator<gsl_complex_float>>;
    View(const GSL_VEC& v) : Vector_t()
    {
        gsl_vec = std::make_shared<GSL_VEC>(v);
        gsl_vec->owner = 0;
    }

public:
   View() = default;
   View(const View&) = default;
   View(View&&) = default;

   View& operator=(const View&) = default;
   View& operator=(View&&) = default;
   View& operator=(const Vector_t& v)
   {
       this->copy(v);
       return *this;
   }

   ~View() = default;
};

template<class T, class GSL_VEC, class A>
struct Vector_hasher_t{
	size_t operator()(const GSL::Vector_t<T, GSL_VEC, A> &v) const
	{
		size_t res = 0;
		std::hash<T> h;
		for(auto a : v){
			res ^= h(a) + 0x9e3779b9 + (res<< 6) + (res>> 2);
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

namespace std{
    template<class T, class GSL_VEC, class A>
    struct hash<GSL::Vector_t<T, GSL_VEC, A>>{
        size_t operator()(const GSL::Vector_t<T, GSL_VEC, A> &v) const
        {
            GSL::Vector_hasher_t<T, GSL_VEC, A> h;
            return h(v);
        }
    };
}
#endif //VECTOR_GSLPP_LIB_H
