#ifndef MATRIX_GSLPP_LIB_H
#define MATRIX_GSLPP_LIB_H
#include <GSLpp/complex.h>
#include <GSLpp/vector.h>
#include <gsl/gsl_matrix.h>
#include <memory>
#include <iostream>

namespace GSL{

    template<typename T, typename GSL_COMPLEX> class Complex_t;
    template<class T, class GSL_VEC, class A> class Vector_t;

    enum class SORTING;

    template<class D, class GSL_MAT, class GSL_VEC, class A> class Matrix_t;
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

    class Permutation;
    Matrix cholesky_decomp(const Matrix&);
    Matrix_cx cholesky_decomp(const Matrix_cx&);

    Matrix lu_inverse(const Matrix& a);
    double lu_det(const Matrix& a);
    Matrix_cx lu_inverse(const Matrix_cx& a);
    GSL::Complex_t<double, gsl_complex> lu_det(const Matrix_cx& a);
    std::tuple<Matrix, Permutation, int> lu_decomp(const Matrix& a);
    std::tuple<Matrix_cx, Permutation, int> lu_decomp(const Matrix_cx& a);

    std::pair<Matrix_cx, Vector_t<double, gsl_vector, std::allocator<double>>> hermitian_eigen(const Matrix_cx&);

    std::pair<Matrix_cx, Vector_t<double, gsl_vector, std::allocator<double>>> general_hermitian_eigen(const Matrix_cx&,
            const Matrix_cx&);

/**************************************************************************//**
* A class for using GSL-matrices with a simpler interface than
* the default one.
* Also try to avoid using unnecessary amounts of memory.
*******************************************************************************/
template<class D, class GSL_MAT, class GSL_VEC, class A = std::allocator<D>>
class Matrix_t
{
protected:
    // Store a reference to the gsl_matrix
    friend class Vector_t<D, GSL_VEC, A>;
    std::shared_ptr<GSL_MAT> gsl_mat;
    Matrix_t(GSL_MAT m) : gsl_mat(std::make_shared<GSL_MAT>(m)){}


public:
    typedef GSL_MAT GSL_Mat;
    typedef GSL::Vector_t<D, GSL_VEC, A> V;
    typedef A allocator_type;
    typedef D value_type;
    typedef typename V::View Row;
    typedef typename V::View Column;
    typedef typename A::reference reference;
    typedef typename A::pointer pointer;
    typedef typename A::const_reference const_reference;
    typedef typename A::difference_type difference_type;
    typedef typename A::size_type size_type;

    // Create an empty matrix (no data at all)
    explicit Matrix_t() : gsl_mat(){}
    // Create a matrix of size n
    explicit Matrix_t(const size_type n1, const size_type n2);
    // Create a new reference to the gsl_matrix inside v
    // Do not allocate anything, only reference stuff!
    Matrix_t(const Matrix_t& v) = default;
    Matrix_t(Matrix_t&& v) = default;
    Matrix_t(std::initializer_list<V>);

    ~Matrix_t() = default;

    // operator GSL_MAT() const {return *this->gsl_mat;};
    operator GSL_MAT() const {return *this->gsl_mat;}

    // Actually copy data from the other matrix, don't just reference it
    Matrix_t& copy(const Matrix_t& a);
    Matrix_t& copy(Matrix_t&& a){std::swap(this->gsl_mat, a.gsl_mat); return *this;}



    Matrix_t& operator= (const Matrix_t& a) = default;
    Matrix_t& operator= (Matrix_t&& a) = default;

    std::pair<size_type, size_type> dim() const
    {
        if(gsl_mat.get() != nullptr){
            return std::pair<Matrix_t::size_type, Matrix_t::size_type>(gsl_mat->size1, gsl_mat->size2);
        }else{
            throw std::runtime_error("Taking size/dimension of uninitialized Matrix!\n");
        }
    }
    std::pair<size_type, size_type> size() const {return this->dim();}


    Matrix_t& operator+= (const Matrix_t& b);
    Matrix_t& operator-= (const Matrix_t& b);
    Matrix_t& operator*= (const Matrix_t& b);
    Matrix_t& operator/= (const Matrix_t& b);
    Matrix_t& operator*= (const D& s);
    Matrix_t& operator/= (const D& s);


    // Basic arithmetic operations
    Matrix_t operator+(const Matrix_t& b) const {return (Matrix_t().copy(*this) += b);}
    Matrix_t operator-(const Matrix_t& b) const {return (Matrix_t().copy(*this) -= b);}
    Matrix_t operator*(const Matrix_t& b) const {return (Matrix_t().copy(*this) *= b);}
    Matrix_t operator/(const Matrix_t& b) const {return (Matrix_t().copy(*this) /= b);}
    Matrix_t operator*(const D s) const {return (Matrix_t().copy(*this) *= s);}
    Matrix_t operator/(const D s) const {return (Matrix_t().copy(*this) /= s);}
    Matrix_t operator-() const {return (Matrix_t(this->size().first, this->size().second) - *this);}

    friend Matrix_t operator*(const D& s, const Matrix_t& m)
    {
        return m*s;
    };

    std::string to_string() const
    {
        std::string res("[");
        for(const auto& row : *this){
            res += "(";
            for(const auto elem : row){
                res += std::to_string(elem) + ", ";
            }
            res += "), ";
        }
        res += "]";
        return res;
    }

    friend std::ostream& operator<<(std::ostream& os, const Matrix_t& mat)
    {
        return os << mat.to_string();
    };

    Vector_t<D, GSL_VEC, A> operator*(const Vector_t<D, GSL_VEC, A>& v);

    bool operator==(const Matrix_t&) const;
    bool operator!=(const Matrix_t& b) const{return !(*this == b);}

    Matrix_t transpose() const;
    Matrix_t T() const { return this->transpose();}
    Matrix_t hermitian_transpose() const;
    Matrix_t dagger() const { return this->hermitian_transpose();}
    Matrix_t H() const { return this->hermitian_transpose();}

    Matrix_t inverse() const;
    D det() const;

    Row get_row(const size_type i);
    Column get_col(const size_type i);
    const Row get_row(const size_type i) const;
    const Column get_col(const size_type i) const;

    Row diagonal();
    const Row diagonal() const;
    Row diagonal(long int k)
    {
        if(k < 0){
            return this->subdiagonal(static_cast<size_t>(-k));
        }else{
            return this->subdiagonal(static_cast<size_t>(k));
        }
    }
    const Row diagonal(int k) const
    {
        if(k < 0){
            return this->subdiagonal(static_cast<size_t>(-k));
        }else{
            return this->subdiagonal(static_cast<size_t>(k));
        }
    }

    Row subdiagonal(size_t k);
    const Row subdiagonal(size_t k) const;
    Row superdiagonal(size_t k);
    const Row superdiagonal(size_t k) const;

    class iterator {
    public:
        typedef typename A::difference_type difference_type;
        typedef Row value_type;
        typedef Row reference;
        typedef GSL_VEC* pointer;
        typedef std::random_access_iterator_tag iterator_category;

        iterator() = default;
        iterator(const Matrix_t& mat, const pointer p)
         : mat_m(mat), vector_ptr(p){}
        iterator(const iterator& it) = default;
        iterator(iterator&& it) = default;
        ~iterator() = default;

        iterator& operator=(const iterator&) = default;
        iterator& operator=(iterator&&) = default;
        bool operator==(const iterator& b) const {return (this->mat_m == b.mat_m) && (this->vector_ptr->data == b.vector_ptr->data);}
        bool operator!=(const iterator& b) const {return !(*this == b);}
        bool operator<(const iterator& b) const {return (this->vector_ptr->data < b.vector_ptr->data);}
        bool operator>(const iterator& b) const {return (this->vector_ptr->data > b.vector_ptr->data);}
        bool operator<=(const iterator& b) const {return !(this->vector_ptr->data > b.vector_ptr->data);}
        bool operator>=(const iterator& b) const {return !(this->vector_ptr->data < b.vector_ptr->data);}

        iterator& operator++(){*this = iterator(mat_m, ); return *this;}
        iterator operator++(int){iterator tmp = *this; this->vector_ptr->data += ; return tmp;}

        iterator& operator--(){--this->row_m; return *this;}
        iterator operator--(int){iterator tmp = *this; this->; return tmp;}
        iterator& operator+=(difference_type n){this->row_m += n; return *this;}

        iterator operator+(difference_type n) const{iterator tmp = *this; return tmp += n;}
        friend iterator operator+(difference_type n, const iterator& it){return it + n;}
        iterator& operator-=(difference_type n){this->row_m -= n;return *this;}
        iterator operator-(difference_type n) const { iterator tmp = *this; return tmp -= n;}
        difference_type operator-(iterator b) const
        {
            if(this->mat_m != b.mat_m){
                throw std::runtime_error("Iterators point to different matrices.");
            }
            return this->row_m - b.row_m;
        }


        value_type operator*(){return *vector_ptr;}
        friend class const_iterator;
    private:
        const Matrix_t& mat_m;
        int step_m;
        pointer vector_ptr;
    };

    class const_iterator{
    public:
        typedef typename A::difference_type difference_type;
        typedef const Row value_type;
        typedef const Row& reference;
        typedef const GSL_VEC* pointer;
        typedef std::random_access_iterator_tag iterator_category;


        const_iterator() = default;
        const_iterator(const Matrix_t& mat, const difference_type n = 0)
         : mat_m(mat), row_m(n){}
        const_iterator(const const_iterator&) = default;
        const_iterator(const_iterator&&) = default;
        const_iterator(const iterator&);
        ~const_iterator() = default;

        const_iterator& operator=(const const_iterator&) = default;
        const_iterator& operator=(const_iterator&&) = default;
        bool operator==(const const_iterator& b) const {return (this->mat_m == b.mat_m) && (this->row_m == b.row_m);}
        bool operator!=(const const_iterator& b) const {return !(*this == b);}
        bool operator<(const const_iterator& b) const {return (this->row_m < b.row_m);}
        bool operator>(const const_iterator& b) const {return (this->row_m > b.row_m);}
        bool operator<=(const const_iterator& b) const {return !(this->row_m > b.row_m);}
        bool operator>=(const const_iterator& b) const {return !(this->row_m < b.row_m);}

        const_iterator& operator++() {++this->row_m;return *this;}
        const_iterator operator++(int) {auto tmp = *this; ++this->row_m; return tmp;}
        const_iterator& operator--() {--this->row_m; return *this;}
        const_iterator operator--(int) {auto tmp = *this; --this->row_m; return tmp;}
        const_iterator& operator+=(difference_type n) {this->row_m += n; return *this;}
        const_iterator operator+(difference_type n) const {const_iterator tmp = *this; return tmp += n;}
        friend const_iterator operator+(difference_type n, const const_iterator& it)
        {
            const_iterator tmp = it;
            tmp += n;
            return tmp;
        };
        const_iterator& operator-=(difference_type n) {this->row_m -= n;return *this;}
        const_iterator operator-(difference_type n) const {const_iterator tmp = *this; return tmp -= n;}
        difference_type operator-(const_iterator it) const
        {
            if(this->mat_m != it.mat_m){
                throw std::runtime_error("Iterators point to different matrices.");
            }
            return this->row_m - it.row_m;
        }

        value_type& operator*() const
        {
            return *vector_ptr;
        }

    private:
        const Matrix_t& mat_m;
        int step_m;
        pointer vector_ptr;
    };


    typedef std::reverse_iterator<iterator> reverse_iterator;
    typedef std::reverse_iterator<const_iterator> const_reverse_iterator;

    iterator begin() {return iterator{*this, 0};}
    const_iterator begin() const {return const_iterator{*this, 0};}
    const_iterator cbegin() const {return const_iterator{*this, 0};}
    iterator end(){return iterator{*this, static_cast<difference_type>(this->size().first)};}
    const_iterator end() const {return const_iterator{*this, static_cast<difference_type>(this->size().first)};}
    const_iterator cend() const {return const_iterator{*this, static_cast<difference_type>(this->size().first)};}
    reverse_iterator rbegin(){return reverse_iterator{this->end()};}
    const_reverse_iterator rbegin() const{return const_reverse_iterator{this->end()};}
    const_reverse_iterator crbegin() const {return const_reverse_iterator{this->cend()};}
    reverse_iterator rend() {return reverse_iterator{this->begin()};}
    const_reverse_iterator rend() const {return const_reverse_iterator{this->begin()};}
    const_reverse_iterator crend() const {return const_reverse_iterator{this->cbegin()};}

    Row operator[] (const size_type index) {return get_row(index);}
    const Row operator[] (const size_type index) const {return get_row(index);}

    Row operator() (const size_type row) {return (*this)[row];}
    const Row operator() (const size_type row) const {return (*this)[row];}
    reference operator() (const size_type row, const size_type column);
    const_reference operator() (const size_type row, const size_type column) const;

    Row front(){return *this->begin();}
    const Row front() const {return *this->cbegin();}
    Row back() {return *(--this->end());}
    const Row back() const {return *(--this->end());}

    Row at(const size_type row)
    {
        if(row >= this->size().first){
            throw std::runtime_error("Row index out of range.");
        }
        return (*this)[row];
    }
    const Row at(const size_type row) const
    {
        if(row >= this->size().first){
            throw std::runtime_error("Row index out of range.");
        }
        return (*this)[row];
    }
    reference at(const size_type row, const size_type column)
    {
        if(row >= this->size().first){
            throw std::runtime_error("Row index out of range.");
        }
        if(column >= this->size().second){
            throw std::runtime_error("column index out of range.");
        }
        return (*this)[row][column];
    }
    const_reference at(const size_type row, const size_type column) const
    {
        if(row >= this->size().first){
            throw std::runtime_error("Row index out of range.");
        }
        if(column >= this->size().second){
            throw std::runtime_error("column index out of range.");
        }
        return (*this)[row][column];
    }

    pointer data() { return reinterpret_cast<pointer>(gsl_mat->data);}
    size_t tda() { return gsl_mat->tda;}


    friend Matrix cholesky_decomp(const Matrix&);
    friend Matrix_cx GSL::cholesky_decomp(const Matrix_cx&);

    friend Matrix GSL::lu_inverse(const Matrix& a);
    friend Matrix_cx GSL::lu_inverse(const Matrix_cx& a);
    friend std::tuple<Matrix, Permutation, int> GSL::lu_decomp(const Matrix& a);
    friend std::tuple<Matrix_cx, Permutation, int> GSL::lu_decomp(const Matrix_cx& a);
    friend double GSL::lu_det(const Matrix& a);
    friend GSL::Complex_t<double, gsl_complex> GSL::lu_det(const Matrix_cx& a);

    friend std::pair<Matrix_cx, Vector_t<double, gsl_vector, std::allocator<double>>> hermitian_eigen(const Matrix_cx&);

    friend std::pair<Matrix_cx, Vector_t<double, gsl_vector, std::allocator<double>>>general_hermitian_eigen(const Matrix_cx&,
            const Matrix_cx&);

    friend std::pair<Matrix_cx, Vector_t<double, gsl_vector, std::allocator<double>>> sort_hermitian_eigen(
        const Vector_t<double, gsl_vector, std::allocator<double>>& evals, const Matrix_cx& evecs, SORTING sorting);
    friend std::pair<Matrix_cx, Vector_t<double, gsl_vector, std::allocator<double>>> sort_general_hermitian_eigen(
        const Vector_t<double, gsl_vector, std::allocator<double>>& evals, const Matrix_cx& evecs, SORTING sorting);



    class View;

    View view();
    View view(size_t i, size_t j, size_t rows, size_t columns);
    const View view() const;
    const View view(size_t i, size_t j, size_t rows, size_t columns) const;

};


template<class D, class GSL_MAT, class GSL_VEC, class A>
class Matrix_t<D, GSL_MAT, GSL_VEC, A>::View : public Matrix_t
{
private:
    friend Matrix_t;
    View(GSL_MAT m) : Matrix_t(m)
    {
        gsl_mat->owner = 0;
    }

public:
    explicit View() = default;
    View(const View&) = default;
    View(View&&) = default;

    explicit View(Matrix_t);
    explicit View(pointer data, size_type rows, size_type columns);
    explicit View(pointer data, size_type rows, size_type columns, size_type tda);


    View& operator=(const View&) = default;
    View& operator=(View&&) = default;

    View& operator=(Matrix_t m){this->copy(m); return *this;}
};


}
#endif // MATRIX_GSLPP_LIB_H
