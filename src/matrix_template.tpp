#include "matrix_template.h"
#include "complex.h"
#include "vector.h"
#include <gsl/gsl_blas.h>
#include <iostream>

namespace GSL{

template<class T, class GSL_MAT, class GSL_VEC, class A>
inline Matrix_t<T, GSL_MAT, GSL_VEC, A>::Matrix_t()
 : gsl_mat(nullptr), v_m()
{}

template<>
inline Matrix_t<double, gsl_matrix, gsl_vector>::Matrix_t(const Matrix_t::size_type n1, const Matrix_t::size_type n2)
 : gsl_mat(gsl_matrix_calloc(n1, n2), gsl_matrix_free), v_m()
{
    if(gsl_mat == nullptr){
        throw std::runtime_error("Memory allocation (gsl_matrix_calloc)"
        " failed!");
    }
}

template<>
inline Matrix_t<long double, gsl_matrix_long_double, gsl_vector_long_double>::
Matrix_t(const Matrix_t::size_type n1, const Matrix_t::size_type n2)
 : gsl_mat(gsl_matrix_long_double_calloc(n1, n2), gsl_matrix_long_double_free), v_m()
{

    if(gsl_mat == nullptr){
        throw std::runtime_error("Memory allocation (gsl_matrix_long_double_calloc)"
        " failed!");
    }
}

template<>
inline Matrix_t<float, gsl_matrix_float, gsl_vector_float>::
Matrix_t(const Matrix_t::size_type n1, const Matrix_t::size_type n2)
 : gsl_mat(gsl_matrix_float_calloc(n1, n2), gsl_matrix_float_free), v_m()
{
    if(gsl_mat == nullptr){
        throw std::runtime_error("Memory allocation (gsl_matrix_float_calloc)"
        " failed!");
    }
}

template<>
inline Matrix_t<int, gsl_matrix_int, gsl_vector_int>::
Matrix_t(const Matrix_t::size_type n1, const Matrix_t::size_type n2)
 : gsl_mat(gsl_matrix_int_calloc(n1, n2), gsl_matrix_int_free), v_m()
{
    if(gsl_mat == nullptr){
        throw std::runtime_error("Memory allocation (gsl_matrix_int_calloc)"
        " failed!");
    }
}

template<>
inline Matrix_t<unsigned int, gsl_matrix_uint, gsl_vector_uint>::
Matrix_t(const Matrix_t::size_type n1, const Matrix_t::size_type n2)
 : gsl_mat(gsl_matrix_uint_calloc(n1, n2), gsl_matrix_uint_free), v_m()
{
    if(gsl_mat == nullptr){
        throw std::runtime_error("Memory allocation (gsl_matrix_uint_calloc)"
        " failed!");
    }
}

template<>
inline Matrix_t<long, gsl_matrix_long, gsl_vector_long>::
Matrix_t(const Matrix_t::size_type n1, const Matrix_t::size_type n2)
 : gsl_mat(gsl_matrix_long_calloc(n1, n2), gsl_matrix_long_free), v_m()
{
    if(gsl_mat == nullptr){
        throw std::runtime_error("Memory allocation (gsl_matrix_long_calloc)"
        " failed!");
    }
}

template<>
inline Matrix_t<unsigned long, gsl_matrix_ulong, gsl_vector_ulong>::
Matrix_t(const Matrix_t::size_type n1, const Matrix_t::size_type n2)
 : gsl_mat(gsl_matrix_ulong_calloc(n1, n2), gsl_matrix_ulong_free), v_m()
{
    if(gsl_mat == nullptr){
        throw std::runtime_error("Memory allocation (gsl_matrix_ulong_calloc)"
        " failed!");
    }
}

template<>
inline Matrix_t<short, gsl_matrix_short, gsl_vector_short>::
Matrix_t(const Matrix_t::size_type n1, const Matrix_t::size_type n2)
 : gsl_mat(gsl_matrix_short_calloc(n1, n2), gsl_matrix_short_free), v_m()
{
    if(gsl_mat == nullptr){
        throw std::runtime_error("Memory allocation (gsl_matrix_short_calloc)"
        " failed!");
    }
}

template<>
inline Matrix_t<unsigned short, gsl_matrix_ushort, gsl_vector_ushort>::
Matrix_t(const Matrix_t::size_type n1, const Matrix_t::size_type n2)
 : gsl_mat(gsl_matrix_ushort_calloc(n1, n2), gsl_matrix_ushort_free), v_m()
{
    if(gsl_mat == nullptr){
        throw std::runtime_error("Memory allocation (gsl_matrix_ushort_calloc)"
        " failed!");
    }
}

template<>
inline Matrix_t<char, gsl_matrix_char, gsl_vector_char>::
Matrix_t(const Matrix_t::size_type n1, const Matrix_t::size_type n2)
 : gsl_mat(gsl_matrix_char_calloc(n1, n2), gsl_matrix_char_free), v_m()
{
    if(gsl_mat == nullptr){
        throw std::runtime_error("Memory allocation (gsl_matrix_char_calloc)"
        " failed!");
    }
}

template<>
inline Matrix_t<unsigned char, gsl_matrix_uchar, gsl_vector_uchar>::
Matrix_t(const Matrix_t::size_type n1, const Matrix_t::size_type n2)
 : gsl_mat(gsl_matrix_uchar_calloc(n1, n2), gsl_matrix_uchar_free), v_m()
{
    if(gsl_mat == nullptr){
        throw std::runtime_error("Memory allocation (gsl_matrix_uchar_calloc)"
        " failed!");
    }
}

template<>
inline Matrix_t<Complex, gsl_matrix_complex,
    gsl_vector_complex, std::allocator<gsl_complex>>::
Matrix_t(const Matrix_t::size_type n1, const Matrix_t::size_type n2)
 : gsl_mat(gsl_matrix_complex_calloc(n1, n2), gsl_matrix_complex_free), v_m()
{
    if(gsl_mat == nullptr){
        throw std::runtime_error("Memory allocation (gsl_matrix_complex_calloc)"
        " failed!");
    }
}

template<>
inline Matrix_t<Complex_ld, gsl_matrix_complex_long_double,
    gsl_vector_complex_long_double, std::allocator<gsl_complex_long_double>>::
Matrix_t(const Matrix_t::size_type n1, const Matrix_t::size_type n2)
 : gsl_mat(gsl_matrix_complex_long_double_calloc(n1, n2), gsl_matrix_complex_long_double_free), v_m()
{
    if(gsl_mat == nullptr){
        throw std::runtime_error("Memory allocation (gsl_matrix_long_double_calloc)"
        " failed!");
    }
}

template<>
inline Matrix_t<Complex_f, gsl_matrix_complex_float,
    gsl_vector_complex_float, std::allocator<gsl_complex_float>>::Matrix_t
(const Matrix_t::size_type n1, const Matrix_t::size_type n2)
 : gsl_mat(gsl_matrix_complex_float_calloc(n1, n2), gsl_matrix_complex_float_free), v_m()
{
    if(gsl_mat == nullptr){
        throw std::runtime_error("Memory allocation (gsl_matrix_float_calloc)"
        " failed!");
    }
}

template<>
inline Matrix_t<double, gsl_matrix, gsl_vector>::
Matrix_t(std::initializer_list<std::initializer_list<double>> l)
 : gsl_mat(gsl_matrix_alloc(l.size(), l.begin()->size()), gsl_matrix_free), v_m()
{
    auto row = l.begin();
    auto column = (*row).begin();
    for(size_t i = 0; i < l.size(); i++){
        if((*row).size() != gsl_mat->size2){
            throw std::runtime_error("Matrix has different row lengths!");
        }
        column = (*row).begin();
        for(size_t j = 0; j < l.begin()->size(); j++){
            gsl_matrix_set(gsl_mat.get(), i, j, *column);
            column++;
        }
        row++;
    }
}

template<>
inline Matrix_t<long double, gsl_matrix_long_double, gsl_vector_long_double>::
Matrix_t(std::initializer_list<std::initializer_list<long double>> l)
 : gsl_mat(gsl_matrix_long_double_alloc(l.size(), l.begin()->size()), gsl_matrix_long_double_free), v_m()
{
    auto row = l.begin();
    auto column = (*row).begin();
    for(size_t i = 0; i < l.size(); i++){
        if((*row).size() != gsl_mat->size2){
            throw std::runtime_error("Matrix has different row lengths!");
        }
        column = (*row).begin();
        for(size_t j = 0; j < l.begin()->size(); j++){
            gsl_matrix_long_double_set(gsl_mat.get(), i, j, *column);
            column++;
        }
        row++;
    }
}

template<>
inline Matrix_t<float, gsl_matrix_float, gsl_vector_float>::
Matrix_t(std::initializer_list<std::initializer_list<float>> l)
 : gsl_mat(gsl_matrix_float_alloc(l.size(), l.begin()->size()), gsl_matrix_float_free), v_m()
{
    auto row = l.begin();
    auto column = (*row).begin();
    for(size_t i = 0; i < l.size(); i++){
        if((*row).size() != gsl_mat->size2){
            throw std::runtime_error("Matrix has different row lengths!");
        }
        column = (*row).begin();
        for(size_t j = 0; j < l.begin()->size(); j++){
            gsl_matrix_float_set(gsl_mat.get(), i, j, *column);
            column++;
        }
        row++;
    }
}

template<>
inline Matrix_t<int, gsl_matrix_int, gsl_vector_int>::
Matrix_t(std::initializer_list<std::initializer_list<int>> l)
 : gsl_mat(gsl_matrix_int_alloc(l.size(), l.begin()->size()), gsl_matrix_int_free), v_m()
{
    auto row = l.begin();
    auto column = (*row).begin();
    for(size_t i = 0; i < l.size(); i++){
        if((*row).size() != gsl_mat->size2){
            throw std::runtime_error("matrix has different row lengths!");
        }
        column = (*row).begin();
        for(size_t j = 0; j < l.begin()->size(); j++){
            gsl_matrix_int_set(gsl_mat.get(), i, j, *column);
            column++;
        }
        row++;
    }
}

template<>
inline Matrix_t<uint, gsl_matrix_uint, gsl_vector_uint>::
Matrix_t(std::initializer_list<std::initializer_list<uint>> l)
 : gsl_mat(gsl_matrix_uint_alloc(l.size(), l.begin()->size()), gsl_matrix_uint_free), v_m()
{
    auto row = l.begin();
    auto column = (*row).begin();
    for(size_t i = 0; i < l.size(); i++){
        if((*row).size() != gsl_mat->size2){
            throw std::runtime_error("matrix has different row lengths!");
        }
        column = (*row).begin();
        for(size_t j = 0; j < l.begin()->size(); j++){
            gsl_matrix_uint_set(gsl_mat.get(), i, j, *column);
            column++;
        }
        row++;
    }
}

template<>
inline Matrix_t<long, gsl_matrix_long, gsl_vector_long>::
Matrix_t(std::initializer_list<std::initializer_list<long>> l)
 : gsl_mat(gsl_matrix_long_alloc(l.size(), l.begin()->size()), gsl_matrix_long_free), v_m()
{
    auto row = l.begin();
    auto column = (*row).begin();
    for(size_t i = 0; i < l.size(); i++){
        if((*row).size() != gsl_mat->size2){
            throw std::runtime_error("matrix has different row lengths!");
        }
        column = (*row).begin();
        for(size_t j = 0; j < l.begin()->size(); j++){
            gsl_matrix_long_set(gsl_mat.get(), i, j, *column);
            column++;
        }
        row++;
    }
}

template<>
inline Matrix_t<unsigned long, gsl_matrix_ulong, gsl_vector_ulong>::
Matrix_t(std::initializer_list<std::initializer_list<unsigned long>> l)
 : gsl_mat(gsl_matrix_ulong_alloc(l.size(), l.begin()->size()), gsl_matrix_ulong_free), v_m()
{
    auto row = l.begin();
    auto column = (*row).begin();
    for(size_t i = 0; i < l.size(); i++){
        if((*row).size() != gsl_mat->size2){
            throw std::runtime_error("matrix has different row lengths!");
        }
        column = (*row).begin();
        for(size_t j = 0; j < l.begin()->size(); j++){
            gsl_matrix_ulong_set(gsl_mat.get(), i, j, *column);
            column++;
        }
        row++;
    }
}

template<>
inline Matrix_t<short, gsl_matrix_short, gsl_vector_short>::
Matrix_t(std::initializer_list<std::initializer_list<short>> l)
 : gsl_mat(gsl_matrix_short_alloc(l.size(), l.begin()->size()), gsl_matrix_short_free), v_m()
{
    auto row = l.begin();
    auto column = (*row).begin();
    for(size_t i = 0; i < l.size(); i++){
        if((*row).size() != gsl_mat->size2){
            throw std::runtime_error("matrix has different row lengths!");
        }
        column = (*row).begin();
        for(size_t j = 0; j < l.begin()->size(); j++){
            gsl_matrix_short_set(gsl_mat.get(), i, j, *column);
            column++;
        }
        row++;
    }
}


template<>
inline Matrix_t<unsigned short, gsl_matrix_ushort, gsl_vector_ushort>::
Matrix_t(std::initializer_list<std::initializer_list<unsigned short>> l)
 : gsl_mat(gsl_matrix_ushort_alloc(l.size(), l.begin()->size()), gsl_matrix_ushort_free), v_m()
{
    auto row = l.begin();
    auto column = (*row).begin();
    for(size_t i = 0; i < l.size(); i++){
        if((*row).size() != gsl_mat->size2){
            throw std::runtime_error("matrix has different row lengths!");
        }
        column = (*row).begin();
        for(size_t j = 0; j < l.begin()->size(); j++){
            gsl_matrix_ushort_set(gsl_mat.get(), i, j, *column);
            column++;
        }
        row++;
    }
}

template<>
inline Matrix_t<char, gsl_matrix_char, gsl_vector_char>::
Matrix_t(std::initializer_list<std::initializer_list<char>> l)
 : gsl_mat(gsl_matrix_char_alloc(l.size(), l.begin()->size()), gsl_matrix_char_free), v_m()
{
    auto row = l.begin();
    auto column = (*row).begin();
    for(size_t i = 0; i < l.size(); i++){
        if((*row).size() != gsl_mat->size2){
            throw std::runtime_error("matrix has different row lengths!");
        }
        column = (*row).begin();
        for(size_t j = 0; j < l.begin()->size(); j++){
            gsl_matrix_char_set(gsl_mat.get(), i, j, *column);
            column++;
        }
        row++;
    }
}

template<>
inline Matrix_t<unsigned char, gsl_matrix_uchar, gsl_vector_uchar>::
Matrix_t(std::initializer_list<std::initializer_list<unsigned char>> l)
 : gsl_mat(gsl_matrix_uchar_alloc(l.size(), l.begin()->size()), gsl_matrix_uchar_free), v_m()
{
    auto row = l.begin();
    auto column = (*row).begin();
    for(size_t i = 0; i < l.size(); i++){
        if((*row).size() != gsl_mat->size2){
            throw std::runtime_error("matrix has different row lengths!");
        }
        column = (*row).begin();
        for(size_t j = 0; j < l.begin()->size(); j++){
            gsl_matrix_uchar_set(gsl_mat.get(), i, j, *column);
            column++;
        }
        row++;
    }
}

template<>
inline Matrix_t<Complex, gsl_matrix_complex, gsl_vector_complex, std::allocator<gsl_complex>>::
Matrix_t(std::initializer_list<std::initializer_list<Complex>> l)
 : gsl_mat(gsl_matrix_complex_alloc(l.size(), l.begin()->size()), gsl_matrix_complex_free), v_m()
{
    auto row = l.begin();
    auto column = (*row).begin();
    for(size_t i = 0; i < l.size(); i++){
        if((*row).size() != gsl_mat->size2){
            throw std::runtime_error("matrix has different row lengths!");
        }
        column = (*row).begin();
        for(size_t j = 0; j < l.begin()->size(); j++){
            gsl_matrix_complex_set(gsl_mat.get(), i, j, *column);
            column++;
        }
        row++;
    }
}

template<>
inline Matrix_t<Complex_ld, gsl_matrix_complex_long_double,
    gsl_vector_complex_long_double, std::allocator<gsl_complex_long_double>>::
Matrix_t(std::initializer_list<std::initializer_list<Complex_ld>> l)
 : gsl_mat(gsl_matrix_complex_long_double_alloc(l.size(), l.begin()->size()), gsl_matrix_complex_long_double_free), v_m()
{
    auto row = l.begin();
    auto column = (*row).begin();
    for(size_t i = 0; i < l.size(); i++){
        if((*row).size() != gsl_mat->size2){
            throw std::runtime_error("matrix has different row lengths!");
        }
        column = (*row).begin();
        for(size_t j = 0; j < l.begin()->size(); j++){
            gsl_matrix_complex_long_double_set(gsl_mat.get(), i, j, *column);
            column++;
        }
        row++;
    }
}

template<>
inline Matrix_t<Complex_f, gsl_matrix_complex_float,
    gsl_vector_complex_float, std::allocator<gsl_complex_float>>::
Matrix_t(std::initializer_list<std::initializer_list<Complex_f>> l)
 : gsl_mat(gsl_matrix_complex_float_alloc(l.size(), l.begin()->size()), gsl_matrix_complex_float_free), v_m()
{
    auto row = l.begin();
    auto column = (*row).begin();
    for(size_t i = 0; i < l.size(); i++){
        if((*row).size() != gsl_mat->size2){
            throw std::runtime_error("matrix has different row lengths!");
        }
        column = (*row).begin();
        for(size_t j = 0; j < l.begin()->size(); j++){
            gsl_matrix_complex_float_set(gsl_mat.get(), i, j, *column);
            column++;
        }
        row++;
    }
}

template<>
inline void Matrix_t<double, gsl_matrix, gsl_vector>::copy(const Matrix_t<double, gsl_matrix, gsl_vector>& a)
{
    if(this->gsl_mat.get() == nullptr){
        this->gsl_mat = std::shared_ptr<gsl_matrix>(gsl_matrix_alloc(a.size().first, a.size().second), gsl_matrix_free);
        if(this->gsl_mat.get() == nullptr){
            throw std::runtime_error("Error in matrix allocation!");
        }
    }
    int stat = gsl_matrix_memcpy(this->gsl_mat.get(), a.gsl_mat.get());
    if(stat){
		std::string error_str =   gsl_strerror(stat);
		throw std::runtime_error("Error in memory copying.\nGSL error: "
        + error_str);
	}
}

template<>
inline void Matrix_t<long double, gsl_matrix_long_double, gsl_vector_long_double>::copy
(const Matrix_t<long double, gsl_matrix_long_double, gsl_vector_long_double>& a)
{
    if(this->gsl_mat.get() == nullptr){
        this->gsl_mat = std::shared_ptr<gsl_matrix_long_double>
            (gsl_matrix_long_double_alloc(a.size().first, a.size().second), gsl_matrix_long_double_free);
        if(this->gsl_mat.get() == nullptr){
            throw std::runtime_error("Error in matrix allocation!");
        }
    }
    int stat = gsl_matrix_long_double_memcpy(this->gsl_mat.get(), a.gsl_mat.get());
    if(stat){
		std::string error_str =   gsl_strerror(stat);
		throw std::runtime_error("Error in memory copying.\nGSL error: "
        + error_str);
	}
}

template<>
inline void Matrix_t<float, gsl_matrix_float, gsl_vector_float>::copy
(const Matrix_t<float, gsl_matrix_float, gsl_vector_float>& a)
{
    if(this->gsl_mat.get() == nullptr){
        this->gsl_mat = std::shared_ptr<gsl_matrix_float>
            (gsl_matrix_float_alloc(a.size().first, a.size().second), gsl_matrix_float_free);
        if(this->gsl_mat.get() == nullptr){
            throw std::runtime_error("Error in matrix allocation!");
        }
    }
    int stat = gsl_matrix_float_memcpy(this->gsl_mat.get(), a.gsl_mat.get());
    if(stat){
		std::string error_str =   gsl_strerror(stat);
		throw std::runtime_error("Error in memory copying.\nGSL error: "
        + error_str);
	}
}

template<>
inline void Matrix_t<int, gsl_matrix_int, gsl_vector_int>::copy
(const Matrix_t<int, gsl_matrix_int, gsl_vector_int>& a)
{
    if(this->gsl_mat.get() == nullptr){
        this->gsl_mat = std::shared_ptr<gsl_matrix_int>
            (gsl_matrix_int_alloc(a.size().first, a.size().second), gsl_matrix_int_free);
        if(this->gsl_mat.get() == nullptr){
            throw std::runtime_error("Error in matrix allocation!");
        }
    }
    int stat = gsl_matrix_int_memcpy(this->gsl_mat.get(), a.gsl_mat.get());
    if(stat){
		std::string error_str =   gsl_strerror(stat);
		throw std::runtime_error("Error in memory copying.\nGSL error: "
        + error_str);
	}
}

template<>
inline void Matrix_t<unsigned int, gsl_matrix_uint, gsl_vector_uint>::copy
(const Matrix_t<unsigned int, gsl_matrix_uint, gsl_vector_uint>& a)
{
    if(this->gsl_mat.get() == nullptr){
        this->gsl_mat = std::shared_ptr<gsl_matrix_uint>
            (gsl_matrix_uint_alloc(a.size().first, a.size().second), gsl_matrix_uint_free);
        if(this->gsl_mat.get() == nullptr){
            throw std::runtime_error("Error in matrix allocation!");
        }
    }
    int stat = gsl_matrix_uint_memcpy(this->gsl_mat.get(), a.gsl_mat.get());
    if(stat){
		std::string error_str =   gsl_strerror(stat);
		throw std::runtime_error("Error in memory copying.\nGSL error: "
        + error_str);
	}
}

template<>
inline void Matrix_t<long , gsl_matrix_long, gsl_vector_long>::copy
(const Matrix_t<long , gsl_matrix_long, gsl_vector_long>& a)
{
    if(this->gsl_mat.get() == nullptr){
        this->gsl_mat = std::shared_ptr<gsl_matrix_long>
            (gsl_matrix_long_alloc(a.size().first, a.size().second), gsl_matrix_long_free);
        if(this->gsl_mat.get() == nullptr){
            throw std::runtime_error("Error in matrix allocation!");
        }
    }
    int stat = gsl_matrix_long_memcpy(this->gsl_mat.get(), a.gsl_mat.get());
    if(stat){
		std::string error_str =   gsl_strerror(stat);
		throw std::runtime_error("Error in memory copying.\nGSL error: "
        + error_str);
	}
}

template<>
inline void Matrix_t<unsigned long, gsl_matrix_ulong, gsl_vector_ulong>::copy
(const Matrix_t<unsigned long, gsl_matrix_ulong, gsl_vector_ulong>& a)
{
    if(this->gsl_mat.get() == nullptr){
        this->gsl_mat = std::shared_ptr<gsl_matrix_ulong>
            (gsl_matrix_ulong_alloc(a.size().first, a.size().second), gsl_matrix_ulong_free);
        if(this->gsl_mat.get() == nullptr){
            throw std::runtime_error("Error in matrix allocation!");
        }
    }
    int stat = gsl_matrix_ulong_memcpy(this->gsl_mat.get(), a.gsl_mat.get());
    if(stat){
		std::string error_str =   gsl_strerror(stat);
		throw std::runtime_error("Error in memory copying.\nGSL error: "
        + error_str);
	}
}

template<>
inline void Matrix_t<short, gsl_matrix_short, gsl_vector_short>::copy
(const Matrix_t<short, gsl_matrix_short, gsl_vector_short>& a)
{
    if(this->gsl_mat.get() == nullptr){
        this->gsl_mat = std::shared_ptr<gsl_matrix_short>
            (gsl_matrix_short_alloc(a.size().first, a.size().second), gsl_matrix_short_free);
        if(this->gsl_mat.get() == nullptr){
            throw std::runtime_error("Error in matrix allocation!");
        }
    }
    int stat = gsl_matrix_short_memcpy(this->gsl_mat.get(), a.gsl_mat.get());
    if(stat){
		std::string error_str =   gsl_strerror(stat);
		throw std::runtime_error("Error in memory copying.\nGSL error: "
        + error_str);
	}
}

template<>
inline void Matrix_t<unsigned short, gsl_matrix_ushort, gsl_vector_ushort>::copy
(const Matrix_t<unsigned short, gsl_matrix_ushort, gsl_vector_ushort>& a)
{
    if(this->gsl_mat.get() == nullptr){
        this->gsl_mat = std::shared_ptr<gsl_matrix_ushort>
            (gsl_matrix_ushort_alloc(a.size().first, a.size().second), gsl_matrix_ushort_free);
        if(this->gsl_mat.get() == nullptr){
            throw std::runtime_error("Error in matrix allocation!");
        }
    }
    int stat = gsl_matrix_ushort_memcpy(this->gsl_mat.get(), a.gsl_mat.get());
    if(stat){
		std::string error_str =   gsl_strerror(stat);
		throw std::runtime_error("Error in memory copying.\nGSL error: "
        + error_str);
	}
}

template<>
inline void Matrix_t<char, gsl_matrix_char, gsl_vector_char>::copy
(const Matrix_t<char, gsl_matrix_char, gsl_vector_char>& a)
{
    if(this->gsl_mat.get() == nullptr){
        this->gsl_mat = std::shared_ptr<gsl_matrix_char>
            (gsl_matrix_char_alloc(a.size().first, a.size().second), gsl_matrix_char_free);
        if(this->gsl_mat.get() == nullptr){
            throw std::runtime_error("Error in matrix allocation!");
        }
    }
    int stat = gsl_matrix_char_memcpy(this->gsl_mat.get(), a.gsl_mat.get());
    if(stat){
		std::string error_str =   gsl_strerror(stat);
		throw std::runtime_error("Error in memory copying.\nGSL error: "
        + error_str);
	}
}

template<>
inline void Matrix_t<unsigned char, gsl_matrix_uchar, gsl_vector_uchar>::copy
(const Matrix_t<unsigned char, gsl_matrix_uchar, gsl_vector_uchar>& a)
{
    if(this->gsl_mat.get() == nullptr){
        this->gsl_mat = std::shared_ptr<gsl_matrix_uchar>
            (gsl_matrix_uchar_alloc(a.size().first, a.size().second), gsl_matrix_uchar_free);
        if(this->gsl_mat.get() == nullptr){
            throw std::runtime_error("Error in matrix allocation!");
        }
    }
    int stat = gsl_matrix_uchar_memcpy(this->gsl_mat.get(), a.gsl_mat.get());
    if(stat){
		std::string error_str =   gsl_strerror(stat);
		throw std::runtime_error("Error in memory copying.\nGSL error: "
        + error_str);
	}
}

template<>
inline void Matrix_t<Complex_t<double, gsl_complex>, gsl_matrix_complex, gsl_vector_complex, std::allocator<gsl_complex>>::copy
(const Matrix_t<Complex_t<double, gsl_complex>, gsl_matrix_complex, gsl_vector_complex, std::allocator<gsl_complex>>& a)
{
    if(this->gsl_mat.get() == nullptr){
        this->gsl_mat = std::shared_ptr<gsl_matrix_complex>
            (gsl_matrix_complex_alloc(a.size().first, a.size().second), gsl_matrix_complex_free);
        if(this->gsl_mat.get() == nullptr){
            throw std::runtime_error("Error in matrix allocation!");
        }
    }
    int stat = gsl_matrix_complex_memcpy(this->gsl_mat.get(), a.gsl_mat.get());
    if(stat){
		std::string error_str =   gsl_strerror(stat);
		throw std::runtime_error("Error in memory copying.\nGSL error: "
        + error_str);
	}
}

template<>
inline void Matrix_t<Complex_t<long double, gsl_complex_long_double>, gsl_matrix_complex_long_double, gsl_vector_complex_long_double, std::allocator<gsl_complex_long_double>>::copy
(const Matrix_t<Complex_t<long double, gsl_complex_long_double>, gsl_matrix_complex_long_double, gsl_vector_complex_long_double, std::allocator<gsl_complex_long_double>>& a)
{
    if(this->gsl_mat.get() == nullptr){
        this->gsl_mat = std::shared_ptr<gsl_matrix_complex_long_double>
            (gsl_matrix_complex_long_double_alloc(a.size().first, a.size().second), gsl_matrix_complex_long_double_free);
        if(this->gsl_mat.get() == nullptr){
            throw std::runtime_error("Error in matrix allocation!");
        }
    }
    int stat = gsl_matrix_complex_long_double_memcpy(this->gsl_mat.get(), a.gsl_mat.get());
    if(stat){
		std::string error_str =   gsl_strerror(stat);
		throw std::runtime_error("Error in memory copying.\nGSL error: "
        + error_str);
	}
}

template<>
inline void Matrix_t<Complex_t<float, gsl_complex_float>, gsl_matrix_complex_float, gsl_vector_complex_float, std::allocator<gsl_complex_float>>::copy
(const Matrix_t<Complex_t<float, gsl_complex_float>, gsl_matrix_complex_float, gsl_vector_complex_float, std::allocator<gsl_complex_float>>& a)
{
    if(this->gsl_mat.get() == nullptr){
        this->gsl_mat = std::shared_ptr<gsl_matrix_complex_float>
            (gsl_matrix_complex_float_alloc(a.size().first, a.size().second), gsl_matrix_complex_float_free);
        if(this->gsl_mat.get() == nullptr){
            throw std::runtime_error("Error in matrix allocation!");
        }
    }
    int stat = gsl_matrix_complex_float_memcpy(this->gsl_mat.get(), a.gsl_mat.get());
    if(stat){
		std::string error_str =   gsl_strerror(stat);
		throw std::runtime_error("Error in memory copying.\nGSL error: "
        + error_str);
	}
}

template<class T, class G, class V, class A>
inline Matrix_t<T, G, V, A>& Matrix_t<T, G, V, A>::operator=(const Matrix_t<T, G, V, A>& a)
{
    this->gsl_mat = a.gsl_mat;
    // this->v_m = a.v_m;
    return *this;
}

/*
template<>
inline Matrix_t<long double, gsl_matrix_long_double, gsl_vector_long_double>& Matrix_t<long double, gsl_matrix_long_double, gsl_vector_long_double>::operator=(const Matrix_t<long double, gsl_matrix_long_double, gsl_vector_long_double>& a)
{
    if(this->gsl_mat == nullptr || this->gsl_mat->owner == 1){
        this->gsl_mat = a.gsl_mat;
    }else if(this->gsl_mat->owner == 0){
        gsl_matrix_long_double_memcpy(this->gsl_mat.get(), a.gsl_mat.get());
    }else{
        throw std::runtime_error("Unknown owner value " + std::to_string(gsl_mat->owner));
    }
    return *this;
}

template<>
inline Matrix_t<float, gsl_matrix_float, gsl_vector_float>& Matrix_t<float, gsl_matrix_float, gsl_vector_float>::operator=(const Matrix_t<float, gsl_matrix_float, gsl_vector_float>& a)
{
    if(this->gsl_mat == nullptr || this->gsl_mat->owner == 1){
        this->gsl_mat = a.gsl_mat;
    }else if(this->gsl_mat->owner == 0){
        gsl_matrix_float_memcpy(this->gsl_mat.get(), a.gsl_mat.get());
    }else{
        throw std::runtime_error("Unknown owner value " + std::to_string(gsl_mat->owner));
    }
    return *this;
}

template<>
inline Matrix_t<int, gsl_matrix_int, gsl_vector_int>& Matrix_t<int, gsl_matrix_int, gsl_vector_int>::operator=(const Matrix_t<int, gsl_matrix_int, gsl_vector_int>& a)
{
    if(this->gsl_mat == nullptr || this->gsl_mat->owner == 1){
        this->gsl_mat = a.gsl_mat;
    }else if(this->gsl_mat->owner == 0){
        gsl_matrix_int_memcpy(this->gsl_mat.get(), a.gsl_mat.get());
    }else{
        throw std::runtime_error("Unknown owner value " + std::to_string(gsl_mat->owner));
    }
    return *this;
}

template<>
inline Matrix_t<unsigned int, gsl_matrix_uint, gsl_vector_uint>& Matrix_t<unsigned int, gsl_matrix_uint, gsl_vector_uint>::operator=(const Matrix_t<unsigned int, gsl_matrix_uint, gsl_vector_uint>& a)
{
    if(this->gsl_mat == nullptr || this->gsl_mat->owner == 1){
        this->gsl_mat = a.gsl_mat;
    }else if(this->gsl_mat->owner == 0){
        gsl_matrix_uint_memcpy(this->gsl_mat.get(), a.gsl_mat.get());
    }else{
        throw std::runtime_error("Unknown owner value " + std::to_string(gsl_mat->owner));
    }
    return *this;
}

template<>
inline Matrix_t<long, gsl_matrix_long, gsl_vector_long>& Matrix_t<long, gsl_matrix_long, gsl_vector_long>::operator=(const Matrix_t<long, gsl_matrix_long, gsl_vector_long>& a)
{
    if(this->gsl_mat == nullptr || this->gsl_mat->owner == 1){
        this->gsl_mat = a.gsl_mat;
    }else if(this->gsl_mat->owner == 0){
        gsl_matrix_long_memcpy(this->gsl_mat.get(), a.gsl_mat.get());
    }else{
        throw std::runtime_error("Unknown owner value " + std::to_string(gsl_mat->owner));
    }
    return *this;
}

template<>
inline Matrix_t<unsigned long, gsl_matrix_ulong, gsl_vector_ulong>& Matrix_t<unsigned long, gsl_matrix_ulong, gsl_vector_ulong>::operator=(const Matrix_t<unsigned long, gsl_matrix_ulong, gsl_vector_ulong>& a)
{
    if(this->gsl_mat == nullptr || this->gsl_mat->owner == 1){
        this->gsl_mat = a.gsl_mat;
    }else if(this->gsl_mat->owner == 0){
        gsl_matrix_ulong_memcpy(this->gsl_mat.get(), a.gsl_mat.get());
    }else{
        throw std::runtime_error("Unknown owner value " + std::to_string(gsl_mat->owner));
    }
    return *this;
}

template<>
inline Matrix_t<short, gsl_matrix_short, gsl_vector_short>& Matrix_t<short, gsl_matrix_short, gsl_vector_short>::operator=(const Matrix_t<short, gsl_matrix_short, gsl_vector_short>& a)
{
    if(this->gsl_mat == nullptr || this->gsl_mat->owner == 1){
        this->gsl_mat = a.gsl_mat;
    }else if(this->gsl_mat->owner == 0){
        gsl_matrix_short_memcpy(this->gsl_mat.get(), a.gsl_mat.get());
    }else{
        throw std::runtime_error("Unknown owner value " + std::to_string(gsl_mat->owner));
    }
    return *this;
}

template<>
inline Matrix_t<unsigned short, gsl_matrix_ushort, gsl_vector_ushort>& Matrix_t<unsigned short, gsl_matrix_ushort, gsl_vector_ushort>::operator=(const Matrix_t<unsigned short, gsl_matrix_ushort, gsl_vector_ushort>& a)
{
    if(this->gsl_mat == nullptr || this->gsl_mat->owner == 1){
        this->gsl_mat = a.gsl_mat;
    }else if(this->gsl_mat->owner == 0){
        gsl_matrix_ushort_memcpy(this->gsl_mat.get(), a.gsl_mat.get());
    }else{
        throw std::runtime_error("Unknown owner value " + std::to_string(gsl_mat->owner));
    }
    return *this;
}

template<>
inline Matrix_t<char, gsl_matrix_char, gsl_vector_char>& Matrix_t<char, gsl_matrix_char, gsl_vector_char>::operator=(const Matrix_t<char, gsl_matrix_char, gsl_vector_char>& a)
{
    if(this->gsl_mat == nullptr || this->gsl_mat->owner == 1){
        this->gsl_mat = a.gsl_mat;
    }else if(this->gsl_mat->owner == 0){
        gsl_matrix_char_memcpy(this->gsl_mat.get(), a.gsl_mat.get());
    }else{
        throw std::runtime_error("Unknown owner value " + std::to_string(gsl_mat->owner));
    }
    return *this;
}

template<>
inline Matrix_t<unsigned char, gsl_matrix_uchar, gsl_vector_uchar>& Matrix_t<unsigned char, gsl_matrix_uchar, gsl_vector_uchar>::operator=(const Matrix_t<unsigned char, gsl_matrix_uchar, gsl_vector_uchar>& a)
{
    if(this->gsl_mat == nullptr || this->gsl_mat->owner == 1){
        this->gsl_mat = a.gsl_mat;
    }else if(this->gsl_mat->owner == 0){
        gsl_matrix_uchar_memcpy(this->gsl_mat.get(), a.gsl_mat.get());
    }else{
        throw std::runtime_error("Unknown owner value " + std::to_string(gsl_mat->owner));
    }
    return *this;
}

template<>
inline Matrix_t<Complex_t<double, gsl_complex>, gsl_matrix_complex, gsl_vector_complex, std::allocator<gsl_complex>>& Matrix_t<Complex_t<double, gsl_complex>, gsl_matrix_complex, gsl_vector_complex, std::allocator<gsl_complex>>::operator=(const Matrix_t<Complex_t<double, gsl_complex>, gsl_matrix_complex, gsl_vector_complex, std::allocator<gsl_complex>>& a)
{
    if(this->gsl_mat == nullptr || this->gsl_mat->owner == 1){
        this->gsl_mat = a.gsl_mat;
    }else if(this->gsl_mat->owner == 0){
        gsl_matrix_complex_memcpy(this->gsl_mat.get(), a.gsl_mat.get());
    }else{
        throw std::runtime_error("Unknown owner value " + std::to_string(gsl_mat->owner));
    }
    return *this;
}

template<>
inline Matrix_t<Complex_t<long double, gsl_complex_long_double>, gsl_matrix_complex_long_double, gsl_vector_complex_long_double, std::allocator<gsl_complex_long_double>>& Matrix_t<Complex_t<long double, gsl_complex_long_double>, gsl_matrix_complex_long_double, gsl_vector_complex_long_double, std::allocator<gsl_complex_long_double>>::operator=(const Matrix_t<Complex_t<long double, gsl_complex_long_double>, gsl_matrix_complex_long_double, gsl_vector_complex_long_double, std::allocator<gsl_complex_long_double>>& a)
{
    if(this->gsl_mat == nullptr || this->gsl_mat->owner == 1){
        this->gsl_mat = a.gsl_mat;
    }else if(this->gsl_mat->owner == 0){
        gsl_matrix_complex_long_double_memcpy(this->gsl_mat.get(), a.gsl_mat.get());
    }else{
        throw std::runtime_error("Unknown owner value " + std::to_string(gsl_mat->owner));
    }
    return *this;
}

template<>
inline Matrix_t<Complex_t<float, gsl_complex_float>, gsl_matrix_complex_float, gsl_vector_complex_float, std::allocator<gsl_complex_float>>& Matrix_t<Complex_t<float, gsl_complex_float>, gsl_matrix_complex_float, gsl_vector_complex_float, std::allocator<gsl_complex_float>>::operator=(const Matrix_t<Complex_t<float, gsl_complex_float>, gsl_matrix_complex_float, gsl_vector_complex_float, std::allocator<gsl_complex_float>>& a)
{
    if(this->gsl_mat == nullptr || this->gsl_mat->owner == 1){
        this->gsl_mat = a.gsl_mat;
    }else if(this->gsl_mat->owner == 0){
        gsl_matrix_complex_float_memcpy(this->gsl_mat.get(), a.gsl_mat.get());
    }else{
        throw std::runtime_error("Unknown owner value " + std::to_string(gsl_mat->owner));
    }
    return *this;
}
*/

template<class T, class G, class V, class A>
inline Matrix_t<T, G, V, A>& Matrix_t<T, G, V, A>::operator=(Matrix_t<T, G, V, A>&& a)
{
    std::swap(this->gsl_mat, a.gsl_mat);
    // std::swap(this->v_m, a.v_m);
    return *this;
}

/*
template<>
inline Matrix_t<long double, gsl_matrix_long_double, gsl_vector_long_double>& Matrix_t<long double, gsl_matrix_long_double, gsl_vector_long_double>::operator=(Matrix_t<long double, gsl_matrix_long_double, gsl_vector_long_double>&& a)
{
    if(this->gsl_mat == nullptr || this->gsl_mat->owner == 1){
        std::swap(this->gsl_mat, a.gsl_mat);
    }else if(this->gsl_mat->owner == 0){
        gsl_matrix_long_double_memcpy(this->gsl_mat.get(), a.gsl_mat.get());
    }
    return *this;
}

template<>
inline Matrix_t<float, gsl_matrix_float, gsl_vector_float>& Matrix_t<float, gsl_matrix_float, gsl_vector_float>::operator=(Matrix_t<float, gsl_matrix_float, gsl_vector_float>&& a)
{
    if(this->gsl_mat == nullptr || this->gsl_mat->owner == 1){
        std::swap(this->gsl_mat, a.gsl_mat);
    }else if(this->gsl_mat->owner == 0){
        gsl_matrix_float_memcpy(this->gsl_mat.get(), a.gsl_mat.get());
    }
    return *this;
}

template<>
inline Matrix_t<int, gsl_matrix_int, gsl_vector_int>& Matrix_t<int, gsl_matrix_int, gsl_vector_int>::operator=(Matrix_t<int, gsl_matrix_int, gsl_vector_int>&& a)
{
    if(this->gsl_mat == nullptr || this->gsl_mat->owner == 1){
        std::swap(this->gsl_mat, a.gsl_mat);
    }else if(this->gsl_mat->owner == 0){
        gsl_matrix_int_memcpy(this->gsl_mat.get(), a.gsl_mat.get());
    }
    return *this;
}

template<>
inline Matrix_t<unsigned int, gsl_matrix_uint, gsl_vector_uint>& Matrix_t<unsigned int, gsl_matrix_uint, gsl_vector_uint>::operator=(Matrix_t<unsigned int, gsl_matrix_uint, gsl_vector_uint>&& a)
{
    if(this->gsl_mat == nullptr || this->gsl_mat->owner == 1){
        std::swap(this->gsl_mat, a.gsl_mat);
    }else if(this->gsl_mat->owner == 0){
        gsl_matrix_uint_memcpy(this->gsl_mat.get(), a.gsl_mat.get());
    }
    return *this;
}

template<>
inline Matrix_t<long, gsl_matrix_long, gsl_vector_long>& Matrix_t<long, gsl_matrix_long, gsl_vector_long>::operator=(Matrix_t<long, gsl_matrix_long, gsl_vector_long>&& a)
{
    if(this->gsl_mat == nullptr || this->gsl_mat->owner == 1){
        std::swap(this->gsl_mat, a.gsl_mat);
    }else if(this->gsl_mat->owner == 0){
        gsl_matrix_long_memcpy(this->gsl_mat.get(), a.gsl_mat.get());
    }
    return *this;
}

template<>
inline Matrix_t<unsigned long, gsl_matrix_ulong, gsl_vector_ulong>& Matrix_t<unsigned long, gsl_matrix_ulong, gsl_vector_ulong>::operator=(Matrix_t<unsigned long, gsl_matrix_ulong, gsl_vector_ulong>&& a)
{
    if(this->gsl_mat == nullptr || this->gsl_mat->owner == 1){
        std::swap(this->gsl_mat, a.gsl_mat);
    }else if(this->gsl_mat->owner == 0){
        gsl_matrix_ulong_memcpy(this->gsl_mat.get(), a.gsl_mat.get());
    }
    return *this;
}

template<>
inline Matrix_t<short, gsl_matrix_short, gsl_vector_short>& Matrix_t<short, gsl_matrix_short, gsl_vector_short>::operator=(Matrix_t<short, gsl_matrix_short, gsl_vector_short>&& a)
{
    if(this->gsl_mat == nullptr || this->gsl_mat->owner == 1){
        std::swap(this->gsl_mat, a.gsl_mat);
    }else if(this->gsl_mat->owner == 0){
        gsl_matrix_short_memcpy(this->gsl_mat.get(), a.gsl_mat.get());
    }
    return *this;
}

template<>
inline Matrix_t<unsigned short, gsl_matrix_ushort, gsl_vector_ushort>& Matrix_t<unsigned short, gsl_matrix_ushort, gsl_vector_ushort>::operator=(Matrix_t<unsigned short, gsl_matrix_ushort, gsl_vector_ushort>&& a)
{
    if(this->gsl_mat == nullptr || this->gsl_mat->owner == 1){
        std::swap(this->gsl_mat, a.gsl_mat);
    }else if(this->gsl_mat->owner == 0){
        gsl_matrix_ushort_memcpy(this->gsl_mat.get(), a.gsl_mat.get());
    }
    return *this;
}

template<>
inline Matrix_t<char, gsl_matrix_char, gsl_vector_char>& Matrix_t<char, gsl_matrix_char, gsl_vector_char>::operator=(Matrix_t<char, gsl_matrix_char, gsl_vector_char>&& a)
{
    if(this->gsl_mat == nullptr || this->gsl_mat->owner == 1){
        std::swap(this->gsl_mat, a.gsl_mat);
    }else if(this->gsl_mat->owner == 0){
        gsl_matrix_char_memcpy(this->gsl_mat.get(), a.gsl_mat.get());
    }
    return *this;
}

template<>
inline Matrix_t<unsigned char, gsl_matrix_uchar, gsl_vector_uchar>& Matrix_t<unsigned char, gsl_matrix_uchar, gsl_vector_uchar>::operator=(Matrix_t<unsigned char, gsl_matrix_uchar, gsl_vector_uchar>&& a)
{
    if(this->gsl_mat == nullptr || this->gsl_mat->owner == 1){
        std::swap(this->gsl_mat, a.gsl_mat);
    }else if(this->gsl_mat->owner == 0){
        gsl_matrix_uchar_memcpy(this->gsl_mat.get(), a.gsl_mat.get());
    }
    return *this;
}

template<>
inline Matrix_t<Complex_t<double, gsl_complex>, gsl_matrix_complex, gsl_vector_complex, std::allocator<gsl_complex>>& Matrix_t<Complex_t<double, gsl_complex>, gsl_matrix_complex, gsl_vector_complex, std::allocator<gsl_complex>>::operator=(Matrix_t<Complex_t<double, gsl_complex>, gsl_matrix_complex, gsl_vector_complex, std::allocator<gsl_complex>>&& a)
{
    if(this->gsl_mat == nullptr || this->gsl_mat->owner == 1){
        std::swap(this->gsl_mat, a.gsl_mat);
    }else if(this->gsl_mat->owner == 0){
        gsl_matrix_complex_memcpy(this->gsl_mat.get(), a.gsl_mat.get());
    }
    return *this;
}

template<>
inline Matrix_t<Complex_t<long double, gsl_complex_long_double>, gsl_matrix_complex_long_double, gsl_vector_complex_long_double, std::allocator<gsl_complex_long_double>>& Matrix_t<Complex_t<long double, gsl_complex_long_double>, gsl_matrix_complex_long_double, gsl_vector_complex_long_double, std::allocator<gsl_complex_long_double>>::operator=(Matrix_t<Complex_t<long double, gsl_complex_long_double>, gsl_matrix_complex_long_double, gsl_vector_complex_long_double, std::allocator<gsl_complex_long_double>>&& a)
{
    if(this->gsl_mat == nullptr || this->gsl_mat->owner == 1){
        std::swap(this->gsl_mat, a.gsl_mat);
    }else if(this->gsl_mat->owner == 0){
        gsl_matrix_complex_long_double_memcpy(this->gsl_mat.get(), a.gsl_mat.get());
    }
    return *this;
}

template<>
inline Matrix_t<Complex_t<float, gsl_complex_float>, gsl_matrix_complex_float, gsl_vector_complex_float, std::allocator<gsl_complex_float>>& Matrix_t<Complex_t<float, gsl_complex_float>, gsl_matrix_complex_float, gsl_vector_complex_float, std::allocator<gsl_complex_float>>::operator=(Matrix_t<Complex_t<float, gsl_complex_float>, gsl_matrix_complex_float, gsl_vector_complex_float, std::allocator<gsl_complex_float>>&& a)
{
    if(this->gsl_mat == nullptr || this->gsl_mat->owner == 1){
        std::swap(this->gsl_mat, a.gsl_mat);
    }else if(this->gsl_mat->owner == 0){
        gsl_matrix_complex_float_memcpy(this->gsl_mat.get(), a.gsl_mat.get());
    }
    return *this;
}
*/
template<class T, class M, class V, class A>
std::pair<typename Matrix_t<T, M, V, A>::size_type, typename Matrix_t<T, M, V, A>::size_type>
 Matrix_t<T, M, V, A>::dim() const
{
    if(gsl_mat.get() != nullptr){
        return std::pair<Matrix_t<T, M, V, A>::size_type, Matrix_t<T, M, V, A>::size_type>(gsl_mat->size1, gsl_mat->size2);
    }else{
        throw std::runtime_error("Taking size/dimension of uninitialized Matrix!\n");
    }
}

template<class T, class M, class V, class A>
std::pair<typename Matrix_t<T, M, V, A>::size_type, typename Matrix_t<T, M, V, A>::size_type>
 Matrix_t<T, M, V, A>::size() const
 {
     return this->dim();
 }
template<>
inline Matrix_t<double, gsl_matrix, gsl_vector>& Matrix_t<double, gsl_matrix, gsl_vector>::operator+=(const Matrix_t<double, gsl_matrix, gsl_vector>& b)
{
    int stat = gsl_matrix_add(this->gsl_mat.get(), b.gsl_mat.get());
    if(stat){
		std::string error_str =   gsl_strerror(stat);
		throw std::runtime_error("Error in matrix addition.\nGSL error: "
        + error_str);
	}
    return *this;
}

template<>
inline Matrix_t<long double, gsl_matrix_long_double, gsl_vector_long_double>& Matrix_t<long double, gsl_matrix_long_double, gsl_vector_long_double>::operator+=(const Matrix_t<long double, gsl_matrix_long_double, gsl_vector_long_double>& b)
{
    int stat = gsl_matrix_long_double_add(this->gsl_mat.get(), b.gsl_mat.get());
    if(stat){
		std::string error_str =   gsl_strerror(stat);
		throw std::runtime_error("Error in matrix addition.\nGSL error: "
        + error_str);
	}
    return *this;
}

template<>
inline Matrix_t<float, gsl_matrix_float, gsl_vector_float>& Matrix_t<float, gsl_matrix_float, gsl_vector_float>::operator+=(const Matrix_t<float, gsl_matrix_float, gsl_vector_float>& b)
{
    int stat = gsl_matrix_float_add(this->gsl_mat.get(), b.gsl_mat.get());
    if(stat){
		std::string error_str =   gsl_strerror(stat);
		throw std::runtime_error("Error in matrix addition.\nGSL error: "
        + error_str);
	}
    return *this;
}

template<>
inline Matrix_t<int, gsl_matrix_int, gsl_vector_int>& Matrix_t<int, gsl_matrix_int, gsl_vector_int>::operator+=(const Matrix_t<int, gsl_matrix_int, gsl_vector_int>& b)
{
    int stat = gsl_matrix_int_add(this->gsl_mat.get(), b.gsl_mat.get());
    if(stat){
		std::string error_str =   gsl_strerror(stat);
		throw std::runtime_error("Error in matrix addition.\nGSL error: "
        + error_str);
	}
    return *this;
}

template<>
inline Matrix_t<unsigned int, gsl_matrix_uint, gsl_vector_uint>& Matrix_t<unsigned int, gsl_matrix_uint, gsl_vector_uint>::operator+=(const Matrix_t<unsigned int, gsl_matrix_uint, gsl_vector_uint>& b)
{
    int stat = gsl_matrix_uint_add(this->gsl_mat.get(), b.gsl_mat.get());
    if(stat){
		std::string error_str =   gsl_strerror(stat);
		throw std::runtime_error("Error in matrix addition.\nGSL error: "
        + error_str);
	}
    return *this;
}

template<>
inline Matrix_t<long, gsl_matrix_long, gsl_vector_long>& Matrix_t<long, gsl_matrix_long, gsl_vector_long>::operator+=(const Matrix_t<long, gsl_matrix_long, gsl_vector_long>& b)
{
    int stat = gsl_matrix_long_add(this->gsl_mat.get(), b.gsl_mat.get());
    if(stat){
		std::string error_str =   gsl_strerror(stat);
		throw std::runtime_error("Error in matrix addition.\nGSL error: "
        + error_str);
	}
    return *this;
}

template<>
inline Matrix_t<unsigned long, gsl_matrix_ulong, gsl_vector_ulong>& Matrix_t<unsigned long, gsl_matrix_ulong, gsl_vector_ulong>::operator+=(const Matrix_t<unsigned long, gsl_matrix_ulong, gsl_vector_ulong>& b)
{
    int stat = gsl_matrix_ulong_add(this->gsl_mat.get(), b.gsl_mat.get());
    if(stat){
		std::string error_str =   gsl_strerror(stat);
		throw std::runtime_error("Error in matrix addition.\nGSL error: "
        + error_str);
	}
    return *this;
}

template<>
inline Matrix_t<short, gsl_matrix_short, gsl_vector_short>& Matrix_t<short, gsl_matrix_short, gsl_vector_short>::operator+=(const Matrix_t<short, gsl_matrix_short, gsl_vector_short>& b)
{
    int stat = gsl_matrix_short_add(this->gsl_mat.get(), b.gsl_mat.get());
    if(stat){
		std::string error_str =   gsl_strerror(stat);
		throw std::runtime_error("Error in matrix addition.\nGSL error: "
        + error_str);
	}
    return *this;
}

template<>
inline Matrix_t<unsigned short, gsl_matrix_ushort, gsl_vector_ushort>& Matrix_t<unsigned short, gsl_matrix_ushort, gsl_vector_ushort>::operator+=(const Matrix_t<unsigned short, gsl_matrix_ushort, gsl_vector_ushort>& b)
{
    int stat = gsl_matrix_ushort_add(this->gsl_mat.get(), b.gsl_mat.get());
    if(stat){
		std::string error_str =   gsl_strerror(stat);
		throw std::runtime_error("Error in matrix addition.\nGSL error: "
        + error_str);
	}
    return *this;
}


template<>
inline Matrix_t<char, gsl_matrix_char, gsl_vector_char>& Matrix_t<char, gsl_matrix_char, gsl_vector_char>::operator+=(const Matrix_t<char, gsl_matrix_char, gsl_vector_char>& b)
{
    int stat = gsl_matrix_char_add(this->gsl_mat.get(), b.gsl_mat.get());
    if(stat){
		std::string error_str =   gsl_strerror(stat);
		throw std::runtime_error("Error in matrix addition.\nGSL error: "
        + error_str);
	}
    return *this;
}

template<>
inline Matrix_t<unsigned char, gsl_matrix_uchar, gsl_vector_uchar>& Matrix_t<unsigned char, gsl_matrix_uchar, gsl_vector_uchar>::operator+=(const Matrix_t<unsigned char, gsl_matrix_uchar, gsl_vector_uchar>& b)
{
    int stat = gsl_matrix_uchar_add(this->gsl_mat.get(), b.gsl_mat.get());
    if(stat){
		std::string error_str =   gsl_strerror(stat);
		throw std::runtime_error("Error in matrix addition.\nGSL error: "
        + error_str);
	}
    return *this;
}

template<>
inline Matrix_t<Complex_t<double, gsl_complex>, gsl_matrix_complex, gsl_vector_complex, std::allocator<gsl_complex>>& Matrix_t<Complex_t<double, gsl_complex>, gsl_matrix_complex, gsl_vector_complex, std::allocator<gsl_complex>>::operator+=(const Matrix_t<Complex_t<double, gsl_complex>, gsl_matrix_complex, gsl_vector_complex, std::allocator<gsl_complex>>& b)
{
    int stat = gsl_matrix_complex_add(this->gsl_mat.get(), b.gsl_mat.get());
    if(stat){
		std::string error_str =   gsl_strerror(stat);
		throw std::runtime_error("Error in matrix addition.\nGSL error: "
        + error_str);
	}
    return *this;
}

template<>
inline Matrix_t<Complex_t<long double, gsl_complex_long_double>, gsl_matrix_complex_long_double, gsl_vector_complex_long_double, std::allocator<gsl_complex_long_double>>& Matrix_t<Complex_t<long double, gsl_complex_long_double>, gsl_matrix_complex_long_double, gsl_vector_complex_long_double, std::allocator<gsl_complex_long_double>>::operator+=(const Matrix_t<Complex_t<long double, gsl_complex_long_double>, gsl_matrix_complex_long_double, gsl_vector_complex_long_double, std::allocator<gsl_complex_long_double>>& b)
{
    int stat = gsl_matrix_complex_long_double_add(this->gsl_mat.get(), b.gsl_mat.get());
    if(stat){
		std::string error_str =   gsl_strerror(stat);
		throw std::runtime_error("Error in matrix addition.\nGSL error: "
        + error_str);
	}
    return *this;
}

template<>
inline Matrix_t<Complex_t<float, gsl_complex_float>, gsl_matrix_complex_float, gsl_vector_complex_float, std::allocator<gsl_complex_float>>& Matrix_t<Complex_t<float, gsl_complex_float>, gsl_matrix_complex_float, gsl_vector_complex_float, std::allocator<gsl_complex_float>>::operator+=(const Matrix_t<Complex_t<float, gsl_complex_float>, gsl_matrix_complex_float, gsl_vector_complex_float, std::allocator<gsl_complex_float>>& b)
{
    int stat = gsl_matrix_complex_float_add(this->gsl_mat.get(), b.gsl_mat.get());
    if(stat){
		std::string error_str =   gsl_strerror(stat);
		throw std::runtime_error("Error in matrix addition.\nGSL error: "
        + error_str);
	}
    return *this;
}

template<>
inline Matrix_t<double, gsl_matrix, gsl_vector>& Matrix_t<double, gsl_matrix, gsl_vector>::operator-=(const Matrix_t<double, gsl_matrix, gsl_vector>& b)
{
    int stat = gsl_matrix_sub(this->gsl_mat.get(), b.gsl_mat.get());
    if(stat){
		std::string error_str =   gsl_strerror(stat);
		throw std::runtime_error("Error in matrix addition.\nGSL error: "
        + error_str);
	}
    return *this;
}

template<>
inline Matrix_t<long double, gsl_matrix_long_double, gsl_vector_long_double>& Matrix_t<long double, gsl_matrix_long_double, gsl_vector_long_double>::operator-=(const Matrix_t<long double, gsl_matrix_long_double, gsl_vector_long_double>& b)
{
    int stat = gsl_matrix_long_double_sub(this->gsl_mat.get(), b.gsl_mat.get());
    if(stat){
		std::string error_str = gsl_strerror(stat);
		throw std::runtime_error("Error in matrix addition.\nGSL error: "
        + error_str);
	}
    return *this;
}

template<>
inline Matrix_t<float, gsl_matrix_float, gsl_vector_float>& Matrix_t<float, gsl_matrix_float, gsl_vector_float>::operator-=(const Matrix_t<float, gsl_matrix_float, gsl_vector_float>& b)
{
    int stat = gsl_matrix_float_sub(this->gsl_mat.get(), b.gsl_mat.get());
    if(stat){
		std::string error_str =   gsl_strerror(stat);
		throw std::runtime_error("Error in matrix addition.\nGSL error: "
        + error_str);
	}
    return *this;
}

template<>
inline Matrix_t<int, gsl_matrix_int, gsl_vector_int>& Matrix_t<int, gsl_matrix_int, gsl_vector_int>::operator-=(const Matrix_t<int, gsl_matrix_int, gsl_vector_int>& b)
{
    int stat = gsl_matrix_int_sub(this->gsl_mat.get(), b.gsl_mat.get());
    if(stat){
		std::string error_str =   gsl_strerror(stat);
		throw std::runtime_error("Error in matrix addition.\nGSL error: "
        + error_str);
	}
    return *this;
}

template<>
inline Matrix_t<unsigned int, gsl_matrix_uint, gsl_vector_uint>& Matrix_t<unsigned int, gsl_matrix_uint, gsl_vector_uint>::operator-=(const Matrix_t<unsigned int, gsl_matrix_uint, gsl_vector_uint>& b)
{
    int stat = gsl_matrix_uint_sub(this->gsl_mat.get(), b.gsl_mat.get());
    if(stat){
		std::string error_str =   gsl_strerror(stat);
		throw std::runtime_error("Error in matrix addition.\nGSL error: "
        + error_str);
	}
    return *this;
}

template<>
inline Matrix_t<long, gsl_matrix_long, gsl_vector_long>& Matrix_t<long, gsl_matrix_long, gsl_vector_long>::operator-=(const Matrix_t<long, gsl_matrix_long, gsl_vector_long>& b)
{
    int stat = gsl_matrix_long_sub(this->gsl_mat.get(), b.gsl_mat.get());
    if(stat){
		std::string error_str =   gsl_strerror(stat);
		throw std::runtime_error("Error in matrix addition.\nGSL error: "
        + error_str);
	}
    return *this;
}

template<>
inline Matrix_t<unsigned long, gsl_matrix_ulong, gsl_vector_ulong>& Matrix_t<unsigned long, gsl_matrix_ulong, gsl_vector_ulong>::operator-=(const Matrix_t<unsigned long, gsl_matrix_ulong, gsl_vector_ulong>& b)
{
    int stat = gsl_matrix_ulong_sub(this->gsl_mat.get(), b.gsl_mat.get());
    if(stat){
		std::string error_str =   gsl_strerror(stat);
		throw std::runtime_error("Error in matrix addition.\nGSL error: "
        + error_str);
	}
    return *this;
}

template<>
inline Matrix_t<short, gsl_matrix_short, gsl_vector_short>& Matrix_t<short, gsl_matrix_short, gsl_vector_short>::operator-=(const Matrix_t<short, gsl_matrix_short, gsl_vector_short>& b)
{
    int stat = gsl_matrix_short_sub(this->gsl_mat.get(), b.gsl_mat.get());
    if(stat){
		std::string error_str =   gsl_strerror(stat);
		throw std::runtime_error("Error in matrix addition.\nGSL error: "
        + error_str);
	}
    return *this;
}

template<>
inline Matrix_t<unsigned short, gsl_matrix_ushort, gsl_vector_ushort>& Matrix_t<unsigned short, gsl_matrix_ushort, gsl_vector_ushort>::operator-=(const Matrix_t<unsigned short, gsl_matrix_ushort, gsl_vector_ushort>& b)
{
    int stat = gsl_matrix_ushort_sub(this->gsl_mat.get(), b.gsl_mat.get());
    if(stat){
		std::string error_str =   gsl_strerror(stat);
		throw std::runtime_error("Error in matrix addition.\nGSL error: "
        + error_str);
	}
    return *this;
}


template<>
inline Matrix_t<char, gsl_matrix_char, gsl_vector_char>& Matrix_t<char, gsl_matrix_char, gsl_vector_char>::operator-=(const Matrix_t<char, gsl_matrix_char, gsl_vector_char>& b)
{
    int stat = gsl_matrix_char_sub(this->gsl_mat.get(), b.gsl_mat.get());
    if(stat){
		std::string error_str =   gsl_strerror(stat);
		throw std::runtime_error("Error in matrix addition.\nGSL error: "
        + error_str);
	}
    return *this;
}

template<>
inline Matrix_t<unsigned char, gsl_matrix_uchar, gsl_vector_uchar>& Matrix_t<unsigned char, gsl_matrix_uchar, gsl_vector_uchar>::operator-=(const Matrix_t<unsigned char, gsl_matrix_uchar, gsl_vector_uchar>& b)
{
    int stat = gsl_matrix_uchar_sub(this->gsl_mat.get(), b.gsl_mat.get());
    if(stat){
		std::string error_str =   gsl_strerror(stat);
		throw std::runtime_error("Error in matrix addition.\nGSL error: "
        + error_str);
	}
    return *this;
}

template<>
inline Matrix_t<Complex_t<double, gsl_complex>, gsl_matrix_complex, gsl_vector_complex, std::allocator<gsl_complex>>& Matrix_t<Complex_t<double, gsl_complex>, gsl_matrix_complex, gsl_vector_complex, std::allocator<gsl_complex>>::operator-=(const Matrix_t<Complex_t<double, gsl_complex>, gsl_matrix_complex, gsl_vector_complex, std::allocator<gsl_complex>>& b)
{
    int stat = gsl_matrix_complex_sub(this->gsl_mat.get(), b.gsl_mat.get());
    if(stat){
		std::string error_str =   gsl_strerror(stat);
		throw std::runtime_error("Error in matrix addition.\nGSL error: "
        + error_str);
	}
    return *this;
}

template<>
inline Matrix_t<Complex_t<long double, gsl_complex_long_double>, gsl_matrix_complex_long_double, gsl_vector_complex_long_double, std::allocator<gsl_complex_long_double>>& Matrix_t<Complex_t<long double, gsl_complex_long_double>, gsl_matrix_complex_long_double, gsl_vector_complex_long_double, std::allocator<gsl_complex_long_double>>::operator-=(const Matrix_t<Complex_t<long double, gsl_complex_long_double>, gsl_matrix_complex_long_double, gsl_vector_complex_long_double, std::allocator<gsl_complex_long_double>>& b)
{
    int stat = gsl_matrix_complex_long_double_sub(this->gsl_mat.get(), b.gsl_mat.get());
    if(stat){
		std::string error_str =   gsl_strerror(stat);
		throw std::runtime_error("Error in matrix addition.\nGSL error: "
        + error_str);
	}
    return *this;
}

template<>
inline Matrix_t<Complex_t<float, gsl_complex_float>, gsl_matrix_complex_float, gsl_vector_complex_float, std::allocator<gsl_complex_float>>& Matrix_t<Complex_t<float, gsl_complex_float>, gsl_matrix_complex_float, gsl_vector_complex_float, std::allocator<gsl_complex_float>>::operator-=(const Matrix_t<Complex_t<float, gsl_complex_float>, gsl_matrix_complex_float, gsl_vector_complex_float, std::allocator<gsl_complex_float>>& b)
{
    int stat = gsl_matrix_complex_float_sub(this->gsl_mat.get(), b.gsl_mat.get());
    if(stat){
		std::string error_str =   gsl_strerror(stat);
		throw std::runtime_error("Error in matrix addition.\nGSL error: "
        + error_str);
	}
    return *this;
}

template<class T, class M, class V, class A>
Matrix_t<T, M, V, A>& Matrix_t<T, M, V, A>::operator*=(const Matrix_t<T, M, V, A>& b)
{
    Matrix_t<T, M, V, A> tmp(this->size().first, this->size().second);
    for(Matrix_t<T, M, V, A>::size_type i = 0; i < this->size().second; i++){
        for(Matrix_t<T, M, V, A>::size_type j = 0; i < b.size().first; j++){
            for(Matrix_t<T, M, V, A>::size_type k = 0; i < this->size().second; k++){
                tmp[i][j] = static_cast<T>( tmp[i][j] + (*this)[i][k]*b[k][j] );
            }
        }
    }
    this->copy(tmp);
    return *this;
}

template<>
inline Matrix_t<double, gsl_matrix, gsl_vector>& Matrix_t<double, gsl_matrix, gsl_vector>::operator*=(const Matrix_t<double, gsl_matrix, gsl_vector>& b)
{
    int stat = gsl_blas_dgemm(CblasNoTrans, CblasNoTrans, 1.0, this->gsl_mat.get(),
        b.gsl_mat.get(), 0.0, this->gsl_mat.get());
    if(stat){
		std::string error_str =   gsl_strerror(stat);
		throw std::runtime_error("Error in matrix multiplication.\nGSL error: "
        + error_str);
	}
    return *this;
}

template<>
inline Matrix_t<float, gsl_matrix_float, gsl_vector_float>& Matrix_t<float, gsl_matrix_float, gsl_vector_float>::operator*=(const Matrix_t<float, gsl_matrix_float, gsl_vector_float>& b)
{
    int stat = gsl_blas_sgemm(CblasNoTrans, CblasNoTrans, 1.0, this->gsl_mat.get(),
        b.gsl_mat.get(), 0.0, this->gsl_mat.get());
    if(stat){
		std::string error_str =   gsl_strerror(stat);
		throw std::runtime_error("Error in matrix addition.\nGSL error: "
        + error_str);
	}
    return *this;
}

template<>
inline Matrix_t<Complex_t<double, gsl_complex>, gsl_matrix_complex, gsl_vector_complex, std::allocator<gsl_complex>>& Matrix_t<Complex_t<double, gsl_complex>, gsl_matrix_complex, gsl_vector_complex, std::allocator<gsl_complex>>::operator*=(const Matrix_t<Complex_t<double, gsl_complex>, gsl_matrix_complex, gsl_vector_complex, std::allocator<gsl_complex>>& b)
{
    int stat = gsl_blas_zgemm(CblasNoTrans, CblasNoTrans, Complex(1.0), this->gsl_mat.get(),
        b.gsl_mat.get(), Complex(0.0), this->gsl_mat.get());
    if(stat){
		std::string error_str =   gsl_strerror(stat);
		throw std::runtime_error("Error in matrix addition.\nGSL error: "
        + error_str);
	}
    return *this;
}

template<>
inline Matrix_t<Complex_t<float, gsl_complex_float>, gsl_matrix_complex_float, gsl_vector_complex_float, std::allocator<gsl_complex_float>>& Matrix_t<Complex_t<float, gsl_complex_float>, gsl_matrix_complex_float, gsl_vector_complex_float, std::allocator<gsl_complex_float>>::operator*=(const Matrix_t<Complex_t<float, gsl_complex_float>, gsl_matrix_complex_float, gsl_vector_complex_float, std::allocator<gsl_complex_float>>& b)
{
    int stat = gsl_blas_cgemm(CblasNoTrans, CblasNoTrans, Complex_f(1.0), this->gsl_mat.get(),
        b.gsl_mat.get(), Complex_f(0.0), this->gsl_mat.get());
    if(stat){
		std::string error_str =   gsl_strerror(stat);
		throw std::runtime_error("Error in matrix addition.\nGSL error: "
        + error_str);
	}
    return *this;
}

template<>
inline Matrix_t<Complex_t<long double, gsl_complex_long_double>, gsl_matrix_complex_long_double, gsl_vector_complex_long_double, std::allocator<gsl_complex_long_double>>& Matrix_t<Complex_t<long double, gsl_complex_long_double>, gsl_matrix_complex_long_double, gsl_vector_complex_long_double, std::allocator<gsl_complex_long_double>>::operator*=(const Matrix_t<Complex_t<long double, gsl_complex_long_double>, gsl_matrix_complex_long_double, gsl_vector_complex_long_double, std::allocator<gsl_complex_long_double>>& b)
{
    Complex_ld c1(0), c2(0);
    Matrix_t<Complex_t<long double, gsl_complex_long_double>, gsl_matrix_complex_long_double, gsl_vector_complex_long_double, std::allocator<gsl_complex_long_double>> tmp(this->size().first, this->size().second);
    for(Matrix_t<Complex_t<long double, gsl_complex_long_double>, gsl_matrix_complex_long_double, gsl_vector_complex_long_double, std::allocator<gsl_complex_long_double>>::size_type i = 0; i < this->size().second; i++){
        for(Matrix_t<Complex_t<long double, gsl_complex_long_double>, gsl_matrix_complex_long_double, gsl_vector_complex_long_double, std::allocator<gsl_complex_long_double>>::size_type j = 0; i < b.size().first; j++){
            for(Matrix_t<Complex_t<long double, gsl_complex_long_double>, gsl_matrix_complex_long_double, gsl_vector_complex_long_double, std::allocator<gsl_complex_long_double>>::size_type k = 0; i < this->size().second; k++){
                c1 = Complex_ld((*this)[i][k]);
                c2 = Complex_ld((*this)[k][j]);
                tmp[i][j] = Complex_ld(tmp[i][j]) + c1*c2;
            }
        }
    }
    this->copy(tmp);
    return *this;
}
template<>
inline Matrix_t<double, gsl_matrix, gsl_vector>& Matrix_t<double, gsl_matrix, gsl_vector>::operator/=(const Matrix_t<double, gsl_matrix, gsl_vector>& b)
{
    int stat = gsl_matrix_div_elements(this->gsl_mat.get(), b.gsl_mat.get());
    if(stat){
		std::string error_str =   gsl_strerror(stat);
		throw std::runtime_error("Error in matrix addition.\nGSL error: "
        + error_str);
	}
    return *this;
}

template<>
inline Matrix_t<long double, gsl_matrix_long_double, gsl_vector_long_double>& Matrix_t<long double, gsl_matrix_long_double, gsl_vector_long_double>::operator/=(const Matrix_t<long double, gsl_matrix_long_double, gsl_vector_long_double>& b)
{
    int stat = gsl_matrix_long_double_div_elements(this->gsl_mat.get(), b.gsl_mat.get());
    if(stat){
		std::string error_str = gsl_strerror(stat);
		throw std::runtime_error("Error in matrix addition.\nGSL error: "
        + error_str);
	}
    return *this;
}

template<>
inline Matrix_t<float, gsl_matrix_float, gsl_vector_float>& Matrix_t<float, gsl_matrix_float, gsl_vector_float>::operator/=(const Matrix_t<float, gsl_matrix_float, gsl_vector_float>& b)
{
    int stat = gsl_matrix_float_div_elements(this->gsl_mat.get(), b.gsl_mat.get());
    if(stat){
		std::string error_str =   gsl_strerror(stat);
		throw std::runtime_error("Error in matrix addition.\nGSL error: "
        + error_str);
	}
    return *this;
}

template<>
inline Matrix_t<int, gsl_matrix_int, gsl_vector_int>& Matrix_t<int, gsl_matrix_int, gsl_vector_int>::operator/=(const Matrix_t<int, gsl_matrix_int, gsl_vector_int>& b)
{
    int stat = gsl_matrix_int_div_elements(this->gsl_mat.get(), b.gsl_mat.get());
    if(stat){
		std::string error_str =   gsl_strerror(stat);
		throw std::runtime_error("Error in matrix addition.\nGSL error: "
        + error_str);
	}
    return *this;
}

template<>
inline Matrix_t<unsigned int, gsl_matrix_uint, gsl_vector_uint>& Matrix_t<unsigned int, gsl_matrix_uint, gsl_vector_uint>::operator/=(const Matrix_t<unsigned int, gsl_matrix_uint, gsl_vector_uint>& b)
{
    int stat = gsl_matrix_uint_div_elements(this->gsl_mat.get(), b.gsl_mat.get());
    if(stat){
		std::string error_str =   gsl_strerror(stat);
		throw std::runtime_error("Error in matrix addition.\nGSL error: "
        + error_str);
	}
    return *this;
}

template<>
inline Matrix_t<long, gsl_matrix_long, gsl_vector_long>& Matrix_t<long, gsl_matrix_long, gsl_vector_long>::operator/=(const Matrix_t<long, gsl_matrix_long, gsl_vector_long>& b)
{
    int stat = gsl_matrix_long_div_elements(this->gsl_mat.get(), b.gsl_mat.get());
    if(stat){
		std::string error_str =   gsl_strerror(stat);
		throw std::runtime_error("Error in matrix addition.\nGSL error: "
        + error_str);
	}
    return *this;
}

template<>
inline Matrix_t<unsigned long, gsl_matrix_ulong, gsl_vector_ulong>& Matrix_t<unsigned long, gsl_matrix_ulong, gsl_vector_ulong>::operator/=(const Matrix_t<unsigned long, gsl_matrix_ulong, gsl_vector_ulong>& b)
{
    int stat = gsl_matrix_ulong_div_elements(this->gsl_mat.get(), b.gsl_mat.get());
    if(stat){
		std::string error_str =   gsl_strerror(stat);
		throw std::runtime_error("Error in matrix addition.\nGSL error: "
        + error_str);
	}
    return *this;
}

template<>
inline Matrix_t<short, gsl_matrix_short, gsl_vector_short>& Matrix_t<short, gsl_matrix_short, gsl_vector_short>::operator/=(const Matrix_t<short, gsl_matrix_short, gsl_vector_short>& b)
{
    int stat = gsl_matrix_short_div_elements(this->gsl_mat.get(), b.gsl_mat.get());
    if(stat){
		std::string error_str =   gsl_strerror(stat);
		throw std::runtime_error("Error in matrix addition.\nGSL error: "
        + error_str);
	}
    return *this;
}

template<>
inline Matrix_t<unsigned short, gsl_matrix_ushort, gsl_vector_ushort>& Matrix_t<unsigned short, gsl_matrix_ushort, gsl_vector_ushort>::operator/=(const Matrix_t<unsigned short, gsl_matrix_ushort, gsl_vector_ushort>& b)
{
    int stat = gsl_matrix_ushort_div_elements(this->gsl_mat.get(), b.gsl_mat.get());
    if(stat){
		std::string error_str =   gsl_strerror(stat);
		throw std::runtime_error("Error in matrix addition.\nGSL error: "
        + error_str);
	}
    return *this;
}


template<>
inline Matrix_t<char, gsl_matrix_char, gsl_vector_char>& Matrix_t<char, gsl_matrix_char, gsl_vector_char>::operator/=(const Matrix_t<char, gsl_matrix_char, gsl_vector_char>& b)
{
    int stat = gsl_matrix_char_div_elements(this->gsl_mat.get(), b.gsl_mat.get());
    if(stat){
		std::string error_str =   gsl_strerror(stat);
		throw std::runtime_error("Error in matrix addition.\nGSL error: "
        + error_str);
	}
    return *this;
}

template<>
inline Matrix_t<unsigned char, gsl_matrix_uchar, gsl_vector_uchar>& Matrix_t<unsigned char, gsl_matrix_uchar, gsl_vector_uchar>::operator/=(const Matrix_t<unsigned char, gsl_matrix_uchar, gsl_vector_uchar>& b)
{
    int stat = gsl_matrix_uchar_div_elements(this->gsl_mat.get(), b.gsl_mat.get());
    if(stat){
		std::string error_str =   gsl_strerror(stat);
		throw std::runtime_error("Error in matrix addition.\nGSL error: "
        + error_str);
	}
    return *this;
}

template<>
inline Matrix_t<Complex_t<double, gsl_complex>, gsl_matrix_complex, gsl_vector_complex, std::allocator<gsl_complex>>& Matrix_t<Complex_t<double, gsl_complex>, gsl_matrix_complex, gsl_vector_complex, std::allocator<gsl_complex>>::operator/=(const Matrix_t<Complex_t<double, gsl_complex>, gsl_matrix_complex, gsl_vector_complex, std::allocator<gsl_complex>>& b)
{
    int stat = gsl_matrix_complex_div_elements(this->gsl_mat.get(), b.gsl_mat.get());
    if(stat){
		std::string error_str =   gsl_strerror(stat);
		throw std::runtime_error("Error in matrix addition.\nGSL error: "
        + error_str);
	}
    return *this;
}

template<>
inline Matrix_t<Complex_t<long double, gsl_complex_long_double>, gsl_matrix_complex_long_double, gsl_vector_complex_long_double, std::allocator<gsl_complex_long_double>>& Matrix_t<Complex_t<long double, gsl_complex_long_double>, gsl_matrix_complex_long_double, gsl_vector_complex_long_double, std::allocator<gsl_complex_long_double>>::operator/=(const Matrix_t<Complex_t<long double, gsl_complex_long_double>, gsl_matrix_complex_long_double, gsl_vector_complex_long_double, std::allocator<gsl_complex_long_double>>& b)
{
    int stat = gsl_matrix_complex_long_double_div_elements(this->gsl_mat.get(), b.gsl_mat.get());
    if(stat){
		std::string error_str =   gsl_strerror(stat);
		throw std::runtime_error("Error in matrix addition.\nGSL error: "
        + error_str);
	}
    return *this;
}

template<>
inline Matrix_t<Complex_t<float, gsl_complex_float>, gsl_matrix_complex_float, gsl_vector_complex_float, std::allocator<gsl_complex_float>>& Matrix_t<Complex_t<float, gsl_complex_float>, gsl_matrix_complex_float, gsl_vector_complex_float, std::allocator<gsl_complex_float>>::operator/=(const Matrix_t<Complex_t<float, gsl_complex_float>, gsl_matrix_complex_float, gsl_vector_complex_float, std::allocator<gsl_complex_float>>& b)
{
    int stat = gsl_matrix_complex_float_div_elements(this->gsl_mat.get(), b.gsl_mat.get());
    if(stat){
		std::string error_str =   gsl_strerror(stat);
		throw std::runtime_error("Error in matrix addition.\nGSL error: "
        + error_str);
	}
    return *this;
}

template<>
inline Matrix_t<double, gsl_matrix, gsl_vector>& Matrix_t<double, gsl_matrix, gsl_vector>::operator*=(const double& b)
{
    int stat = gsl_matrix_scale(this->gsl_mat.get(), b);
    if(stat){
		std::string error_str =   gsl_strerror(stat);
		throw std::runtime_error("Error in matrix addition.\nGSL error: "
        + error_str);
	}
    return *this;
}

template<>
inline Matrix_t<long double, gsl_matrix_long_double, gsl_vector_long_double>& Matrix_t<long double, gsl_matrix_long_double, gsl_vector_long_double>::operator*=(const long double& b)
{
    int stat = gsl_matrix_long_double_scale(this->gsl_mat.get(), static_cast<double>(b));
    if(stat){
		std::string error_str = gsl_strerror(stat);
		throw std::runtime_error("Error in matrix addition.\nGSL error: "
        + error_str);
	}
    return *this;
}

template<>
inline Matrix_t<float, gsl_matrix_float, gsl_vector_float>& Matrix_t<float, gsl_matrix_float, gsl_vector_float>::operator*=(const float& b)
{
    int stat = gsl_matrix_float_scale(this->gsl_mat.get(), static_cast<double>(b));
    if(stat){
		std::string error_str =   gsl_strerror(stat);
		throw std::runtime_error("Error in matrix addition.\nGSL error: "
        + error_str);
	}
    return *this;
}

template<>
inline Matrix_t<int, gsl_matrix_int, gsl_vector_int>& Matrix_t<int, gsl_matrix_int, gsl_vector_int>::operator*=(const int& b)
{
    int stat = gsl_matrix_int_scale(this->gsl_mat.get(), b);
    if(stat){
		std::string error_str =   gsl_strerror(stat);
		throw std::runtime_error("Error in matrix addition.\nGSL error: "
        + error_str);
	}
    return *this;
}

template<>
inline Matrix_t<unsigned int, gsl_matrix_uint, gsl_vector_uint>& Matrix_t<unsigned int, gsl_matrix_uint, gsl_vector_uint>::operator*=(const unsigned int& b)
{
    int stat = gsl_matrix_uint_scale(this->gsl_mat.get(), b);
    if(stat){
		std::string error_str =   gsl_strerror(stat);
		throw std::runtime_error("Error in matrix addition.\nGSL error: "
        + error_str);
	}
    return *this;
}

template<>
inline Matrix_t<long, gsl_matrix_long, gsl_vector_long>& Matrix_t<long, gsl_matrix_long, gsl_vector_long>::operator*=(const long& b)
{
    int stat = gsl_matrix_long_scale(this->gsl_mat.get(), static_cast<double>(b));
    if(stat){
		std::string error_str =   gsl_strerror(stat);
		throw std::runtime_error("Error in matrix addition.\nGSL error: "
        + error_str);
	}
    return *this;
}

template<>
inline Matrix_t<unsigned long, gsl_matrix_ulong, gsl_vector_ulong>& Matrix_t<unsigned long, gsl_matrix_ulong, gsl_vector_ulong>::operator*=(const unsigned long& b)
{
    int stat = gsl_matrix_ulong_scale(this->gsl_mat.get(), static_cast<double>(b));
    if(stat){
		std::string error_str =   gsl_strerror(stat);
		throw std::runtime_error("Error in matrix addition.\nGSL error: "
        + error_str);
	}
    return *this;
}

template<>
inline Matrix_t<short, gsl_matrix_short, gsl_vector_short>& Matrix_t<short, gsl_matrix_short, gsl_vector_short>::operator*=(const short& b)
{
    int stat = gsl_matrix_short_scale(this->gsl_mat.get(), b);
    if(stat){
		std::string error_str =   gsl_strerror(stat);
		throw std::runtime_error("Error in matrix addition.\nGSL error: "
        + error_str);
	}
    return *this;
}

template<>
inline Matrix_t<unsigned short, gsl_matrix_ushort, gsl_vector_ushort>& Matrix_t<unsigned short, gsl_matrix_ushort, gsl_vector_ushort>::operator*=(const unsigned short& b)
{
    int stat = gsl_matrix_ushort_scale(this->gsl_mat.get(), b);
    if(stat){
		std::string error_str =   gsl_strerror(stat);
		throw std::runtime_error("Error in matrix addition.\nGSL error: "
        + error_str);
	}
    return *this;
}


template<>
inline Matrix_t<char, gsl_matrix_char, gsl_vector_char>& Matrix_t<char, gsl_matrix_char, gsl_vector_char>::operator*=(const char& b)
{
    int stat = gsl_matrix_char_scale(this->gsl_mat.get(), b);
    if(stat){
		std::string error_str =   gsl_strerror(stat);
		throw std::runtime_error("Error in matrix addition.\nGSL error: "
        + error_str);
	}
    return *this;
}

template<>
inline Matrix_t<unsigned char, gsl_matrix_uchar, gsl_vector_uchar>& Matrix_t<unsigned char, gsl_matrix_uchar, gsl_vector_uchar>::operator*=(const unsigned char& b)
{
    int stat = gsl_matrix_uchar_scale(this->gsl_mat.get(), b);
    if(stat){
		std::string error_str =   gsl_strerror(stat);
		throw std::runtime_error("Error in matrix addition.\nGSL error: "
        + error_str);
	}
    return *this;
}

template<>
inline Matrix_t<Complex_t<double, gsl_complex>, gsl_matrix_complex, gsl_vector_complex, std::allocator<gsl_complex>>& Matrix_t<Complex_t<double, gsl_complex>, gsl_matrix_complex, gsl_vector_complex, std::allocator<gsl_complex>>::operator*=(const Complex& b)
{
    int stat = gsl_matrix_complex_scale(this->gsl_mat.get(), *b.gsl_c.get());
    if(stat){
		std::string error_str =   gsl_strerror(stat);
		throw std::runtime_error("Error in matrix addition.\nGSL error: "
        + error_str);
	}
    return *this;
}

template<>
inline Matrix_t<Complex_t<long double, gsl_complex_long_double>, gsl_matrix_complex_long_double, gsl_vector_complex_long_double, std::allocator<gsl_complex_long_double>>& Matrix_t<Complex_t<long double, gsl_complex_long_double>, gsl_matrix_complex_long_double, gsl_vector_complex_long_double, std::allocator<gsl_complex_long_double>>::operator*=(const Complex_ld& b)
{
    int stat = gsl_matrix_complex_long_double_scale(this->gsl_mat.get(), *b.gsl_c.get());
    if(stat){
		std::string error_str =   gsl_strerror(stat);
		throw std::runtime_error("Error in matrix addition.\nGSL error: "
        + error_str);
	}
    return *this;
}

template<>
inline Matrix_t<Complex_t<float, gsl_complex_float>, gsl_matrix_complex_float, gsl_vector_complex_float, std::allocator<gsl_complex_float>>& Matrix_t<Complex_t<float, gsl_complex_float>, gsl_matrix_complex_float, gsl_vector_complex_float, std::allocator<gsl_complex_float>>::operator*=(const Complex_f& b)
{
    int stat = gsl_matrix_complex_float_scale(this->gsl_mat.get(), *b.gsl_c.get());
    if(stat){
		std::string error_str =   gsl_strerror(stat);
		throw std::runtime_error("Error in matrix addition.\nGSL error: "
        + error_str);
	}
    return *this;
}

template<>
inline Matrix_t<double, gsl_matrix, gsl_vector>& Matrix_t<double, gsl_matrix, gsl_vector>::operator/=(const double& b)
{
    int stat = gsl_matrix_scale(this->gsl_mat.get(), 1./b);
    if(stat){
		std::string error_str =   gsl_strerror(stat);
		throw std::runtime_error("Error in matrix addition.\nGSL error: "
        + error_str);
	}
    return *this;
}

template<>
inline Matrix_t<long double, gsl_matrix_long_double, gsl_vector_long_double>& Matrix_t<long double, gsl_matrix_long_double, gsl_vector_long_double>::operator/=(const long double& b)
{
    int stat = gsl_matrix_long_double_scale(this->gsl_mat.get(), static_cast<double>(1/b));
    if(stat){
		std::string error_str = gsl_strerror(stat);
		throw std::runtime_error("Error in matrix addition.\nGSL error: "
        + error_str);
	}
    return *this;
}

template<>
inline Matrix_t<float, gsl_matrix_float, gsl_vector_float>& Matrix_t<float, gsl_matrix_float, gsl_vector_float>::operator/=(const float& b)
{
    int stat = gsl_matrix_float_scale(this->gsl_mat.get(), 1./static_cast<double>(b));
    if(stat){
		std::string error_str =   gsl_strerror(stat);
		throw std::runtime_error("Error in matrix addition.\nGSL error: "
        + error_str);
	}
    return *this;
}

template<>
inline Matrix_t<int, gsl_matrix_int, gsl_vector_int>& Matrix_t<int, gsl_matrix_int, gsl_vector_int>::operator/=(const int& b)
{
    int stat = gsl_matrix_int_scale(this->gsl_mat.get(), 1./b);
    if(stat){
		std::string error_str =   gsl_strerror(stat);
		throw std::runtime_error("Error in matrix addition.\nGSL error: "
        + error_str);
	}
    return *this;
}

template<>
inline Matrix_t<unsigned int, gsl_matrix_uint, gsl_vector_uint>& Matrix_t<unsigned int, gsl_matrix_uint, gsl_vector_uint>::operator/=(const unsigned int& b)
{
    int stat = gsl_matrix_uint_scale(this->gsl_mat.get(), 1./b);
    if(stat){
		std::string error_str =   gsl_strerror(stat);
		throw std::runtime_error("Error in matrix addition.\nGSL error: "
        + error_str);
	}
    return *this;
}

template<>
inline Matrix_t<long, gsl_matrix_long, gsl_vector_long>& Matrix_t<long, gsl_matrix_long, gsl_vector_long>::operator/=(const long& b)
{
    int stat = gsl_matrix_long_scale(this->gsl_mat.get(), 1./static_cast<double>(b));
    if(stat){
		std::string error_str =   gsl_strerror(stat);
		throw std::runtime_error("Error in matrix addition.\nGSL error: "
        + error_str);
	}
    return *this;
}

template<>
inline Matrix_t<unsigned long, gsl_matrix_ulong, gsl_vector_ulong>& Matrix_t<unsigned long, gsl_matrix_ulong, gsl_vector_ulong>::operator/=(const unsigned long& b)
{
    int stat = gsl_matrix_ulong_scale(this->gsl_mat.get(), 1./static_cast<double>(b));
    if(stat){
		std::string error_str =   gsl_strerror(stat);
		throw std::runtime_error("Error in matrix addition.\nGSL error: "
        + error_str);
	}
    return *this;
}

template<>
inline Matrix_t<short, gsl_matrix_short, gsl_vector_short>& Matrix_t<short, gsl_matrix_short, gsl_vector_short>::operator/=(const short& b)
{
    int stat = gsl_matrix_short_scale(this->gsl_mat.get(), 1./b);
    if(stat){
		std::string error_str =   gsl_strerror(stat);
		throw std::runtime_error("Error in matrix addition.\nGSL error: "
        + error_str);
	}
    return *this;
}

template<>
inline Matrix_t<unsigned short, gsl_matrix_ushort, gsl_vector_ushort>& Matrix_t<unsigned short, gsl_matrix_ushort, gsl_vector_ushort>::operator/=(const unsigned short& b)
{
    int stat = gsl_matrix_ushort_scale(this->gsl_mat.get(), 1./b);
    if(stat){
		std::string error_str =   gsl_strerror(stat);
		throw std::runtime_error("Error in matrix addition.\nGSL error: "
        + error_str);
	}
    return *this;
}


template<>
inline Matrix_t<char, gsl_matrix_char, gsl_vector_char>& Matrix_t<char, gsl_matrix_char, gsl_vector_char>::operator/=(const char& b)
{
    int stat = gsl_matrix_char_scale(this->gsl_mat.get(), 1./b);
    if(stat){
		std::string error_str =   gsl_strerror(stat);
		throw std::runtime_error("Error in matrix addition.\nGSL error: "
        + error_str);
	}
    return *this;
}

template<>
inline Matrix_t<unsigned char, gsl_matrix_uchar, gsl_vector_uchar>& Matrix_t<unsigned char, gsl_matrix_uchar, gsl_vector_uchar>::operator/=(const unsigned char& b)
{
    int stat = gsl_matrix_uchar_scale(this->gsl_mat.get(), 1./b);
    if(stat){
		std::string error_str =   gsl_strerror(stat);
		throw std::runtime_error("Error in matrix addition.\nGSL error: "
        + error_str);
	}
    return *this;
}

template<>
inline Matrix_t<Complex_t<double, gsl_complex>, gsl_matrix_complex, gsl_vector_complex, std::allocator<gsl_complex>>& Matrix_t<Complex_t<double, gsl_complex>, gsl_matrix_complex, gsl_vector_complex, std::allocator<gsl_complex>>::operator/=(const Complex& b)
{
    int stat = gsl_matrix_complex_scale(this->gsl_mat.get(), *(1./b).gsl_c);
    if(stat){
		std::string error_str =   gsl_strerror(stat);
		throw std::runtime_error("Error in matrix addition.\nGSL error: "
        + error_str);
	}
    return *this;
}

template<>
inline Matrix_t<Complex_t<long double, gsl_complex_long_double>, gsl_matrix_complex_long_double, gsl_vector_complex_long_double, std::allocator<gsl_complex_long_double>>& Matrix_t<Complex_t<long double, gsl_complex_long_double>, gsl_matrix_complex_long_double, gsl_vector_complex_long_double, std::allocator<gsl_complex_long_double>>::operator/=(const Complex_ld& b)
{
    int stat = gsl_matrix_complex_long_double_scale(this->gsl_mat.get(), *(1/b).gsl_c);
    if(stat){
		std::string error_str =   gsl_strerror(stat);
		throw std::runtime_error("Error in matrix addition.\nGSL error: "
        + error_str);
	}
    return *this;
}

template<>
inline Matrix_t<Complex_t<float, gsl_complex_float>, gsl_matrix_complex_float, gsl_vector_complex_float, std::allocator<gsl_complex_float>>& Matrix_t<Complex_t<float, gsl_complex_float>, gsl_matrix_complex_float, gsl_vector_complex_float, std::allocator<gsl_complex_float>>::operator/=(const Complex_f& b)
{
    int stat = gsl_matrix_complex_float_scale(this->gsl_mat.get(), *(1./b).gsl_c);
    if(stat){
		std::string error_str =   gsl_strerror(stat);
		throw std::runtime_error("Error in matrix addition.\nGSL error: "
        + error_str);
	}
    return *this;
}

template<class T, class M, class V, class A>
Matrix_t<T, M, V, A> Matrix_t<T, M, V, A>::operator+(const Matrix_t<T, M, V, A>& b) const
{
    Matrix_t<T, M , V, A>tmp(this->size().first, this->size().second);
    tmp.copy(*this);
    return tmp += b;
}

template<class T, class M, class V, class A>
Matrix_t<T, M, V, A> Matrix_t<T, M, V, A>::operator-(const Matrix_t<T, M, V, A>& b) const
{
    Matrix_t<T, M , V, A>tmp(this->size().first, this->size().second);
    tmp.copy(*this);
    return tmp -= b;
}

template<class T, class M, class V, class A>
Matrix_t<T, M, V, A> Matrix_t<T, M, V, A>::operator*(const Matrix_t<T, M, V, A>& b) const
{
    Matrix_t<T, M , V, A>tmp(this->size().first, this->size().second);
    tmp.copy(*this);
    return tmp *= b;
}

template<>
inline Vector_t<double, gsl_vector> Matrix_t<double, gsl_matrix, gsl_vector>::operator*(const Vector_t<double, gsl_vector>& v)
{
    Vector_t<double, gsl_vector> res(this->size().second);
    int stat = gsl_blas_dgemv(CblasNoTrans, 1.0, this->gsl_mat.get(),
        v.gsl_vec.get(), 0.0, res.gsl_vec.get());
    if(stat){
		std::string error_str =   gsl_strerror(stat);
		throw std::runtime_error("Error in matrix-vector multiplication.\nGSL error: "
        + error_str);
	}

    return res;
}

template<>
inline Vector_t<float, gsl_vector_float> Matrix_t<float, gsl_matrix_float, gsl_vector_float>::operator*(const Vector_t<float, gsl_vector_float>& v)
{
    Vector_t<float, gsl_vector_float> res(this->size().second);
    int stat = gsl_blas_sgemv(CblasNoTrans, 1.0, this->gsl_mat.get(),
        v.gsl_vec.get(), 0.0, res.gsl_vec.get());
    if(stat){
		std::string error_str =   gsl_strerror(stat);
		throw std::runtime_error("Error in matrix-vector multiplication.\nGSL error: "
        + error_str);
	}

    return res;
}

template<>
inline Vector_t<Complex_t<double, gsl_complex>, gsl_vector_complex, std::allocator<gsl_complex>> Matrix_t<Complex_t<double, gsl_complex>, gsl_matrix_complex, gsl_vector_complex, std::allocator<gsl_complex>>::operator*(const Vector_t<Complex_t<double, gsl_complex>, gsl_vector_complex, std::allocator<gsl_complex>>& v)
{
    Vector_t<Complex_t<double, gsl_complex>, gsl_vector_complex, std::allocator<gsl_complex>> res(this->size().second);
    int stat = gsl_blas_zgemv(CblasNoTrans, Complex(1.0), this->gsl_mat.get(),
        v.gsl_vec.get(), Complex(0.0), res.gsl_vec.get());
    if(stat){
		std::string error_str =   gsl_strerror(stat);
		throw std::runtime_error("Error in matrix-vector multiplication.\nGSL error: "
        + error_str);
	}

    return res;
}

template<>
inline Vector_t<Complex_t<float, gsl_complex_float>, gsl_vector_complex_float, std::allocator<gsl_complex_float>> Matrix_t<Complex_t<float, gsl_complex_float>, gsl_matrix_complex_float, gsl_vector_complex_float, std::allocator<gsl_complex_float>>::operator*(const Vector_t<Complex_t<float, gsl_complex_float>, gsl_vector_complex_float, std::allocator<gsl_complex_float>>& v)
{
    Vector_t<Complex_t<float, gsl_complex_float>, gsl_vector_complex_float, std::allocator<gsl_complex_float>> res(this->size().second);
    int stat = gsl_blas_cgemv(CblasNoTrans, Complex_t<float, gsl_complex_float>(1.0), this->gsl_mat.get(),
        v.gsl_vec.get(), Complex_t<float, gsl_complex_float>(0.0), res.gsl_vec.get());
    if(stat){
		std::string error_str =   gsl_strerror(stat);
		throw std::runtime_error("Error in matrix-vector multiplication.\nGSL error: "
        + error_str);
	}

    return res;
}

template<class T, class M, class V, class A>
Matrix_t<T, M, V, A> Matrix_t<T, M, V, A>::operator/(const Matrix_t<T, M, V, A>& b) const
{
    Matrix_t<T, M , V, A>tmp(this->size().first, this->size().second);
    tmp.copy(*this);
    return tmp /= b;
}

template<class T, class M, class V, class A>
Matrix_t<T, M, V, A> Matrix_t<T, M, V, A>::operator*(const T s) const
{
    Matrix_t<T, M , V, A>tmp(this->size().first, this->size().second);
    tmp.copy(*this);
    return tmp *= s;
}

template<class T, class M, class V, class A>
Matrix_t<T, M, V, A> Matrix_t<T, M, V, A>::operator/(const T s) const
{
    Matrix_t<T, M , V, A>tmp(this->size().first, this->size().second);
    tmp.copy(*this);
    return tmp /= s;
}

template<class T, class M, class V, class A>
Matrix_t<T, M, V, A> Matrix_t<T, M, V, A>::operator-() const
{
    Matrix_t<T, M , V, A>tmp(this->size().first, this->size().second);
    return tmp - *this;
}

template<>
inline bool Matrix_t<double, gsl_matrix, gsl_vector>::operator==(const Matrix_t<double, gsl_matrix, gsl_vector>& b) const
{
    if(this->gsl_mat.get() == nullptr && b.gsl_mat.get() == nullptr){
        return true;
    }else if(this->gsl_mat.get() == nullptr || b.gsl_mat.get() == nullptr){
        return false;
    }
    return gsl_matrix_equal(this->gsl_mat.get(), b.gsl_mat.get());
}

template<>
inline bool Matrix_t<long double, gsl_matrix_long_double, gsl_vector_long_double>::operator==(const Matrix_t<long double, gsl_matrix_long_double, gsl_vector_long_double>& b) const
{
    if(this->gsl_mat.get() == nullptr && b.gsl_mat.get() == nullptr){
        return true;
    }else if(this->gsl_mat.get() == nullptr || b.gsl_mat.get() == nullptr){
        return false;
    }
    return gsl_matrix_long_double_equal(this->gsl_mat.get(), b.gsl_mat.get());
}

template<>
inline bool Matrix_t<float, gsl_matrix_float, gsl_vector_float>::operator==(const Matrix_t<float, gsl_matrix_float, gsl_vector_float>& b) const
{
    if(this->gsl_mat.get() == nullptr && b.gsl_mat.get() == nullptr){
        return true;
    }else if(this->gsl_mat.get() == nullptr || b.gsl_mat.get() == nullptr){
        return false;
    }
    return gsl_matrix_float_equal(this->gsl_mat.get(), b.gsl_mat.get());
}

template<>
inline bool Matrix_t<int, gsl_matrix_int, gsl_vector_int>::operator==(const Matrix_t<int, gsl_matrix_int, gsl_vector_int>& b) const
{
    if(this->gsl_mat.get() == nullptr && b.gsl_mat.get() == nullptr){
        return true;
    }else if(this->gsl_mat.get() == nullptr || b.gsl_mat.get() == nullptr){
        return false;
    }
    return gsl_matrix_int_equal(this->gsl_mat.get(), b.gsl_mat.get());
}

template<>
inline bool Matrix_t<unsigned int, gsl_matrix_uint, gsl_vector_uint>::operator==(const Matrix_t<unsigned int, gsl_matrix_uint, gsl_vector_uint>& b) const
{
    if(this->gsl_mat.get() == nullptr && b.gsl_mat.get() == nullptr){
        return true;
    }else if(this->gsl_mat.get() == nullptr || b.gsl_mat.get() == nullptr){
        return false;
    }
    return gsl_matrix_uint_equal(this->gsl_mat.get(), b.gsl_mat.get());
}

template<>
inline bool Matrix_t<long, gsl_matrix_long, gsl_vector_long>::operator==(const Matrix_t<long, gsl_matrix_long, gsl_vector_long>& b) const
{
    if(this->gsl_mat.get() == nullptr && b.gsl_mat.get() == nullptr){
        return true;
    }else if(this->gsl_mat.get() == nullptr || b.gsl_mat.get() == nullptr){
        return false;
    }
    return gsl_matrix_long_equal(this->gsl_mat.get(), b.gsl_mat.get());
}

template<>
inline bool Matrix_t<unsigned long, gsl_matrix_ulong, gsl_vector_ulong>::operator==(const Matrix_t<unsigned long, gsl_matrix_ulong, gsl_vector_ulong>& b) const
{
    if(this->gsl_mat.get() == nullptr && b.gsl_mat.get() == nullptr){
        return true;
    }else if(this->gsl_mat.get() == nullptr || b.gsl_mat.get() == nullptr){
        return false;
    }
    return gsl_matrix_ulong_equal(this->gsl_mat.get(), b.gsl_mat.get());
}

template<>
inline bool Matrix_t<short, gsl_matrix_short, gsl_vector_short>::operator==(const Matrix_t<short, gsl_matrix_short, gsl_vector_short>& b) const
{
    if(this->gsl_mat.get() == nullptr && b.gsl_mat.get() == nullptr){
        return true;
    }else if(this->gsl_mat.get() == nullptr || b.gsl_mat.get() == nullptr){
        return false;
    }
    return gsl_matrix_short_equal(this->gsl_mat.get(), b.gsl_mat.get());
}

template<>
inline bool Matrix_t<unsigned short, gsl_matrix_ushort, gsl_vector_ushort>::operator==(const Matrix_t<unsigned short, gsl_matrix_ushort, gsl_vector_ushort>& b) const
{
    if(this->gsl_mat.get() == nullptr && b.gsl_mat.get() == nullptr){
        return true;
    }else if(this->gsl_mat.get() == nullptr || b.gsl_mat.get() == nullptr){
        return false;
    }
    return gsl_matrix_ushort_equal(this->gsl_mat.get(), b.gsl_mat.get());
}

template<>
inline bool Matrix_t<char, gsl_matrix_char, gsl_vector_char>::operator==(const Matrix_t<char, gsl_matrix_char, gsl_vector_char>& b) const
{
    if(this->gsl_mat.get() == nullptr && b.gsl_mat.get() == nullptr){
        return true;
    }else if(this->gsl_mat.get() == nullptr || b.gsl_mat.get() == nullptr){
        return false;
    }
    return gsl_matrix_char_equal(this->gsl_mat.get(), b.gsl_mat.get());
}

template<>
inline bool Matrix_t<unsigned char, gsl_matrix_uchar, gsl_vector_uchar>::operator==(const Matrix_t<unsigned char, gsl_matrix_uchar, gsl_vector_uchar>& b) const
{
    if(this->gsl_mat.get() == nullptr && b.gsl_mat.get() == nullptr){
        return true;
    }else if(this->gsl_mat.get() == nullptr || b.gsl_mat.get() == nullptr){
        return false;
    }
    return gsl_matrix_uchar_equal(this->gsl_mat.get(), b.gsl_mat.get());
}

template<>
inline bool Matrix_t<Complex_t<double, gsl_complex>, gsl_matrix_complex, gsl_vector_complex, std::allocator<gsl_complex>>::operator==(const Matrix_t<Complex_t<double, gsl_complex>, gsl_matrix_complex, gsl_vector_complex, std::allocator<gsl_complex>>& b) const
{
    if(this->gsl_mat.get() == nullptr && b.gsl_mat.get() == nullptr){
        return true;
    }else if(this->gsl_mat.get() == nullptr || b.gsl_mat.get() == nullptr){
        return false;
    }
    return gsl_matrix_complex_equal(this->gsl_mat.get(), b.gsl_mat.get());
}

template<>
inline bool Matrix_t<Complex_t<long double, gsl_complex_long_double>, gsl_matrix_complex_long_double, gsl_vector_complex_long_double, std::allocator<gsl_complex_long_double>>::operator==(const Matrix_t<Complex_t<long double, gsl_complex_long_double>, gsl_matrix_complex_long_double, gsl_vector_complex_long_double, std::allocator<gsl_complex_long_double>>& b) const
{
    if(this->gsl_mat.get() == nullptr && b.gsl_mat.get() == nullptr){
        return true;
    }else if(this->gsl_mat.get() == nullptr || b.gsl_mat.get() == nullptr){
        return false;
    }
    return gsl_matrix_complex_long_double_equal(this->gsl_mat.get(), b.gsl_mat.get());
}

template<>
inline bool Matrix_t<Complex_t<float, gsl_complex_float>, gsl_matrix_complex_float, gsl_vector_complex_float, std::allocator<gsl_complex_float>>::operator==(const Matrix_t<Complex_t<float, gsl_complex_float>, gsl_matrix_complex_float, gsl_vector_complex_float, std::allocator<gsl_complex_float>>& b) const
{
    if(this->gsl_mat.get() == nullptr && b.gsl_mat.get() == nullptr){
        return true;
    }else if(this->gsl_mat.get() == nullptr || b.gsl_mat.get() == nullptr){
        return false;
    }
    return gsl_matrix_complex_float_equal(this->gsl_mat.get(), b.gsl_mat.get());
}

template<class T, class M, class V, class A>
bool Matrix_t<T, M, V, A>::operator!=(const Matrix_t<T, M, V, A>& b) const
{
    return !(*this == b);
}

template<class T, class M, class V, class A>
Matrix_t<T, M, V, A> Matrix_t<T, M, V, A>::transpose() const
{
    Matrix_t<T, M, V, A> res(this->size().second, this->size().first);
    for(Matrix_t<T, M, V, A>::size_type i = 0; i < this->size().second; i++){
        for(Matrix_t<T, M, V, A>::size_type j = 0; j < this->size().first; j++){
            res[i][j] = (*this)[j][i];
        }
    }
    return res;
}


template<>
inline Vector_t<double, gsl_vector>& Matrix_t<double, gsl_matrix, gsl_vector>::get_row(const Matrix_t<double, gsl_matrix, gsl_vector>::difference_type i)
{
    if(i < 0 || static_cast<Matrix_t<double, gsl_matrix, gsl_vector>::size_type>(i) >= this->size().first){
        throw(std::runtime_error("Error, dereferencing an iterator that is"
        "out of bounds!\n"));
    }
    gsl_vector tmp = gsl_matrix_row(this->gsl_mat.get(), static_cast<Matrix_t<double, gsl_matrix, gsl_vector>::size_type>(i)).vector;
    v_m.gsl_vec = std::shared_ptr<gsl_vector>(new gsl_vector);
    *v_m.gsl_vec.get() = tmp;
    return v_m;
}

template<>
inline Vector_t<long double, gsl_vector_long_double>& Matrix_t<long double, gsl_matrix_long_double, gsl_vector_long_double>::get_row(const Matrix_t<long double, gsl_matrix_long_double, gsl_vector_long_double>::difference_type i)
{
    if(i < 0 || static_cast<Matrix_t<long double, gsl_matrix_long_double, gsl_vector_long_double>::size_type>(i) >= this->size().first){
        throw(std::runtime_error("Error, dereferencing an iterator that is"
        "out of bounds!\n"));
    }
    gsl_vector_long_double tmp = gsl_matrix_long_double_row(this->gsl_mat.get(), static_cast<Matrix_t<long double, gsl_matrix_long_double, gsl_vector_long_double>::size_type>(i)).vector;
    v_m.gsl_vec = std::shared_ptr<gsl_vector_long_double>(new gsl_vector_long_double);
    *v_m.gsl_vec.get() = tmp;
    return v_m;
}

template<>
inline Vector_t<float, gsl_vector_float>& Matrix_t<float, gsl_matrix_float, gsl_vector_float>::get_row(const Matrix_t<float, gsl_matrix_float, gsl_vector_float>::difference_type i)
{
    if(i < 0 || static_cast<Matrix_t<float, gsl_matrix_float, gsl_vector_float>::size_type>(i) >= this->size().first){
        throw(std::runtime_error("Error, dereferencing an iterator that is"
        "out of bounds!\n"));
    }
    gsl_vector_float tmp = gsl_matrix_float_row(this->gsl_mat.get(), static_cast<Matrix_t<float, gsl_matrix_float, gsl_vector_float>::size_type>(i)).vector;
    v_m.gsl_vec = std::shared_ptr<gsl_vector_float>(new gsl_vector_float);
    *v_m.gsl_vec.get() = tmp;
    return v_m;
}

template<>
inline Vector_t<int, gsl_vector_int>& Matrix_t<int, gsl_matrix_int, gsl_vector_int>::get_row(const Matrix_t<int, gsl_matrix_int, gsl_vector_int>::difference_type i)
{
    if(i < 0 || static_cast<Matrix_t<int, gsl_matrix_int, gsl_vector_int>::size_type>(i) >= this->size().first){
        throw(std::runtime_error("Error, dereferencing an iterator that is"
        "out of bounds!\n"));
    }
    gsl_vector_int tmp = gsl_matrix_int_row(this->gsl_mat.get(), static_cast<Matrix_t<int, gsl_matrix_int, gsl_vector_int>::size_type>(i)).vector;
    v_m.gsl_vec = std::shared_ptr<gsl_vector_int>(new gsl_vector_int);
    *v_m.gsl_vec.get() = tmp;
    return v_m;
}

template<>
inline Vector_t<unsigned int, gsl_vector_uint>& Matrix_t<unsigned int, gsl_matrix_uint, gsl_vector_uint>::get_row(const Matrix_t<unsigned int, gsl_matrix_uint, gsl_vector_uint>::difference_type i)
{
    if(i < 0 || static_cast<Matrix_t<unsigned int, gsl_matrix_uint, gsl_vector_uint>::size_type>(i) >= this->size().first){
        throw(std::runtime_error("Error, dereferencing an iterator that is"
        "out of bounds!\n"));
    }
    gsl_vector_uint tmp = gsl_matrix_uint_row(this->gsl_mat.get(), static_cast<Matrix_t<unsigned int, gsl_matrix_uint, gsl_vector_uint>::size_type>(i)).vector;
    v_m.gsl_vec = std::shared_ptr<gsl_vector_uint>(new gsl_vector_uint);
    *v_m.gsl_vec.get() = tmp;
    return v_m;
}

template<>
inline Vector_t<long, gsl_vector_long>& Matrix_t<long, gsl_matrix_long, gsl_vector_long>::get_row(const Matrix_t<long, gsl_matrix_long, gsl_vector_long>::difference_type i)
{
    if(i < 0 || static_cast<Matrix_t<long, gsl_matrix_long, gsl_vector_long>::size_type>(i) >= this->size().first){
        throw(std::runtime_error("Error, dereferencing an iterator that is"
        "out of bounds!\n"));
    }
    gsl_vector_long tmp = gsl_matrix_long_row(this->gsl_mat.get(), static_cast<Matrix_t<long, gsl_matrix_long, gsl_vector_long>::size_type>(i)).vector;
    v_m.gsl_vec = std::shared_ptr<gsl_vector_long>(new gsl_vector_long);
    *v_m.gsl_vec.get() = tmp;
    return v_m;
}

template<>
inline Vector_t<unsigned long, gsl_vector_ulong>& Matrix_t<unsigned long, gsl_matrix_ulong, gsl_vector_ulong>::get_row(const Matrix_t<unsigned long, gsl_matrix_ulong, gsl_vector_ulong>::difference_type i)
{
    if(i < 0 || static_cast<Matrix_t<unsigned long, gsl_matrix_ulong, gsl_vector_ulong>::size_type>(i) >= this->size().first){
        throw(std::runtime_error("Error, dereferencing an iterator that is"
        "out of bounds!\n"));
    }
    gsl_vector_ulong tmp = gsl_matrix_ulong_row(this->gsl_mat.get(), static_cast<Matrix_t<unsigned long, gsl_matrix_ulong, gsl_vector_ulong>::size_type>(i)).vector;
    v_m.gsl_vec = std::shared_ptr<gsl_vector_ulong>(new gsl_vector_ulong);
    *v_m.gsl_vec.get() = tmp;
    return v_m;
}

template<>
inline Vector_t<short, gsl_vector_short>& Matrix_t<short, gsl_matrix_short, gsl_vector_short>::get_row(const Matrix_t<short, gsl_matrix_short, gsl_vector_short>::difference_type i)
{
    if(i < 0 || static_cast<Matrix_t<short, gsl_matrix_short, gsl_vector_short>::size_type>(i) >= this->size().first){
        throw(std::runtime_error("Error, dereferencing an iterator that is"
        "out of bounds!\n"));
    }
    gsl_vector_short tmp = gsl_matrix_short_row(this->gsl_mat.get(), static_cast<Matrix_t<short, gsl_matrix_short, gsl_vector_short>::size_type>(i)).vector;
    v_m.gsl_vec = std::shared_ptr<gsl_vector_short>(new gsl_vector_short);
    *v_m.gsl_vec.get() = tmp;
    return v_m;
}

template<>
inline Vector_t<unsigned short, gsl_vector_ushort>& Matrix_t<unsigned short, gsl_matrix_ushort, gsl_vector_ushort>::get_row(const Matrix_t<unsigned short, gsl_matrix_ushort, gsl_vector_ushort>::difference_type i)
{
    if(i < 0 || static_cast<Matrix_t<unsigned short, gsl_matrix_ushort, gsl_vector_ushort>::size_type>(i) >= this->size().first){
        throw(std::runtime_error("Error, dereferencing an iterator that is"
        "out of bounds!\n"));
    }
    gsl_vector_ushort tmp = gsl_matrix_ushort_row(this->gsl_mat.get(), static_cast<Matrix_t<ushort, gsl_matrix_ushort, gsl_vector_ushort>::size_type>(i)).vector;
    v_m.gsl_vec = std::shared_ptr<gsl_vector_ushort>(new gsl_vector_ushort);
    *v_m.gsl_vec.get() = tmp;
    return v_m;
}

template<>
inline Vector_t<char, gsl_vector_char>& Matrix_t<char, gsl_matrix_char, gsl_vector_char>::get_row(const Matrix_t<char, gsl_matrix_char, gsl_vector_char>::difference_type i)
{
    if(i < 0 || static_cast<Matrix_t<char, gsl_matrix_char, gsl_vector_char>::size_type>(i) >= this->size().first){
        throw(std::runtime_error("Error, dereferencing an iterator that is"
        "out of bounds!\n"));
    }
    gsl_vector_char tmp = gsl_matrix_char_row(this->gsl_mat.get(), static_cast<Matrix_t<char, gsl_matrix_char, gsl_vector_char>::size_type>(i)).vector;
    v_m.gsl_vec = std::shared_ptr<gsl_vector_char>(new gsl_vector_char);
    *v_m.gsl_vec.get() = tmp;
    return v_m;
}

template<>
inline Vector_t<unsigned char, gsl_vector_uchar>& Matrix_t<unsigned char, gsl_matrix_uchar, gsl_vector_uchar>::get_row(const Matrix_t<unsigned char, gsl_matrix_uchar, gsl_vector_uchar>::difference_type i)
{
    if(i < 0 || static_cast<Matrix_t<unsigned char, gsl_matrix_uchar, gsl_vector_uchar>::size_type>(i) >= this->size().first){
        throw(std::runtime_error("Error, dereferencing an iterator that is"
        "out of bounds!\n"));
    }
    gsl_vector_uchar tmp = gsl_matrix_uchar_row(this->gsl_mat.get(), static_cast<Matrix_t<unsigned char, gsl_matrix_uchar, gsl_vector_uchar>::size_type>(i)).vector;
    v_m.gsl_vec = std::shared_ptr<gsl_vector_uchar>(new gsl_vector_uchar);
    *v_m.gsl_vec.get() = tmp;
    return v_m;
}

template<>
inline Vector_t<Complex_t<double, gsl_complex>, gsl_vector_complex, std::allocator<gsl_complex>>& Matrix_t<Complex_t<double, gsl_complex>, gsl_matrix_complex, gsl_vector_complex, std::allocator<gsl_complex>>::get_row(const Matrix_t<Complex_t<double, gsl_complex>, gsl_matrix_complex, gsl_vector_complex, std::allocator<gsl_complex>>::difference_type i)
{
    if(i < 0 || static_cast<Matrix_t<Complex_t<double, gsl_complex>, gsl_matrix_complex, gsl_vector_complex, std::allocator<gsl_complex>>::size_type>(i) >= this->size().first){
        throw(std::runtime_error("Error, dereferencing an iterator that is"
        "out of bounds!\n"));
    }
    gsl_vector_complex tmp = gsl_matrix_complex_row(this->gsl_mat.get(), static_cast<Matrix_t<Complex_t<double, gsl_complex>, gsl_matrix_complex, gsl_vector_complex, std::allocator<gsl_complex>>::size_type>(i)).vector;
    v_m.gsl_vec = std::shared_ptr<gsl_vector_complex>(new gsl_vector_complex);
    *v_m.gsl_vec.get() = tmp;
    return v_m;
}

template<>
inline Vector_t<Complex_t<long double, gsl_complex_long_double>, gsl_vector_complex_long_double, std::allocator<gsl_complex_long_double>>& Matrix_t<Complex_t<long double, gsl_complex_long_double>, gsl_matrix_complex_long_double, gsl_vector_complex_long_double, std::allocator<gsl_complex_long_double>>::get_row(const Matrix_t<Complex_t<long double, gsl_complex_long_double>, gsl_matrix_complex_long_double, gsl_vector_complex_long_double, std::allocator<gsl_complex_long_double>>::difference_type i)
{
    if(i < 0 || static_cast<Matrix_t<Complex_t<long double, gsl_complex_long_double>, gsl_matrix_complex_long_double, gsl_vector_complex_long_double, std::allocator<gsl_complex_long_double>>::size_type>(i) >= this->size().first){
        throw(std::runtime_error("Error, dereferencing an iterator that is"
        "out of bounds!\n"));
    }
    gsl_vector_complex_long_double tmp = gsl_matrix_complex_long_double_row(this->gsl_mat.get(), static_cast<Matrix_t<Complex_t<long double, gsl_complex_long_double>, gsl_matrix_complex_long_double, gsl_vector_complex_long_double, std::allocator<gsl_complex_long_double>>::size_type>(i)).vector;
    v_m.gsl_vec = std::shared_ptr<gsl_vector_complex_long_double>(new gsl_vector_complex_long_double);
    *v_m.gsl_vec.get() = tmp;
    return v_m;
}

template<>
inline Vector_t<Complex_t<float, gsl_complex_float>, gsl_vector_complex_float, std::allocator<gsl_complex_float>>& Matrix_t<Complex_t<float, gsl_complex_float>, gsl_matrix_complex_float, gsl_vector_complex_float, std::allocator<gsl_complex_float>>::get_row(const Matrix_t<Complex_t<float, gsl_complex_float>, gsl_matrix_complex_float, gsl_vector_complex_float, std::allocator<gsl_complex_float>>::difference_type i)
{
    if(i < 0 || static_cast<Matrix_t<Complex_t<float, gsl_complex_float>, gsl_matrix_complex_float, gsl_vector_complex_float, std::allocator<gsl_complex_float>>::size_type>(i) >= this->size().first){
        throw(std::runtime_error("Error, dereferencing an iterator that is"
        "out of bounds!\n"));
    }
    gsl_vector_complex_float tmp = gsl_matrix_complex_float_row(this->gsl_mat.get(), static_cast<Matrix_t<Complex_t<float, gsl_complex_float>, gsl_matrix_complex_float, gsl_vector_complex_float, std::allocator<gsl_complex_float>>::size_type>(i)).vector;
    v_m.gsl_vec = std::shared_ptr<gsl_vector_complex_float>(new gsl_vector_complex_float);
    *v_m.gsl_vec.get() = tmp;
    return v_m;
}


template<class T, class M, class V, class A>
Matrix_t<T, M, V, A>::iterator::iterator(Matrix_t<T, M, V, A>& mat, Matrix_t<T, M, V, A>::difference_type n)
 : mat_m(mat), row_m(n)
{
}

template<class T, class M, class V, class A>
bool Matrix_t<T, M, V, A>::iterator::operator==(const Matrix_t<T, M, V, A>::iterator& b) const
{
    return (this->mat_m == b.mat_m) && (this->row_m == b.row_m);
}

template<class T, class M, class V, class A>
bool Matrix_t<T, M, V, A>::iterator::operator!=(const Matrix_t<T, M, V, A>::iterator& b) const
{
    return !(*this == b);
}

template<class T, class M, class V, class A>
bool Matrix_t<T, M, V, A>::iterator::operator<(const Matrix_t<T, M, V, A>::iterator& b) const
{
    return (this->row_m < b.row_m);
}

template<class T, class M, class V, class A>
bool Matrix_t<T, M, V, A>::iterator::operator>(const Matrix_t<T, M, V, A>::iterator& b) const
{
    return (this->row_m > b.row_m);
}

template<class T, class M, class V, class A>
bool Matrix_t<T, M, V, A>::iterator::operator<=(const Matrix_t<T, M, V, A>::iterator& b) const
{
    return !(this->row_m > b.row_m);
}

template<class T, class M, class V, class A>
bool Matrix_t<T, M, V, A>::iterator::operator>=(const Matrix_t<T, M, V, A>::iterator& b) const
{
    return !(this->row_m < b.row_m);
}

template<class T, class M, class V, class A>
typename Matrix_t<T, M, V, A>::iterator& Matrix_t<T, M, V, A>::iterator::operator++()
{
    this->row_m++;
    return *this;
}

template<class T, class M, class V, class A>
typename Matrix_t<T, M, V, A>::iterator Matrix_t<T, M, V, A>::iterator::operator++(int)
{
    Matrix_t<T, M, V, A>::iterator tmp = *this;
    ++(*this);
    return tmp;
}

template<class T, class M, class V, class A>
typename Matrix_t<T, M, V, A>::iterator& Matrix_t<T, M, V, A>::iterator::operator--()
{
    this->row_m--;
    return *this;
}

template<class T, class M, class V, class A>
typename Matrix_t<T, M, V, A>::iterator Matrix_t<T, M, V, A>::iterator::operator--(int)
{
    Matrix_t<T, M, V, A>::iterator tmp = *this;
    --(*this);
    return tmp;
}

template<class T, class M, class V, class A>
typename Matrix_t<T, M, V, A>::iterator& Matrix_t<T, M, V, A>::iterator::
    operator+=(Matrix_t<T, M, V, A>::difference_type n)
{
    this->row_m += n;
    return *this;
}

template<class T, class M, class V, class A>
typename Matrix_t<T, M, V, A>::iterator Matrix_t<T, M, V, A>::iterator::
    operator+(Matrix_t<T, M, V, A>::difference_type n) const
{
    Matrix_t<T, M, V, A>::iterator tmp = *this;
    tmp += n;
    return tmp;
}

template<class T, class M, class V, class A>
typename Matrix_t<T, M, V, A>::iterator& Matrix_t<T, M, V, A>::iterator::
    operator-=(Matrix_t<T, M, V, A>::difference_type n)
{
    this->row_m -= n;
    return *this;
}

template<class T, class M, class V, class A>
typename Matrix_t<T, M, V, A>::iterator Matrix_t<T, M, V, A>::iterator::
    operator-(Matrix_t<T, M, V, A>::difference_type n) const
{
    Matrix_t<T, M, V, A>::iterator tmp = *this;
    tmp -= n;
    return tmp;
}

template<class T, class M, class V, class A>
typename Matrix_t<T, M, V, A>::iterator::difference_type Matrix_t<T, M, V, A>::iterator::
    operator-(iterator b) const
{
    return this->row_m - b.row_m;
}

template<class T, class M, class V, class A>
typename Matrix_t<T, M, V, A>::iterator::reference Matrix_t<T, M, V, A>::iterator::
    operator*()
{
    if(static_cast<Matrix_t<T, M, V, A>::size_type>(this->row_m) >= this->mat_m.size().first
        || this->row_m < 0){
        throw(std::runtime_error("Error, dereferencing an iterator that is"
        "out of bounds!\n"));
    }
    return this->mat_m.get_row(this->row_m);
}


template<class T, class M, class V, class A>
Matrix_t<T, M, V, A>::const_iterator::
const_iterator(Matrix_t<T, M, V, A>& mat, const Matrix_t<T, M, V, A>::difference_type n)
 : mat_m(mat), row_m(n)
{}

template<class T, class M, class V, class A>
bool Matrix_t<T, M, V, A>::const_iterator::operator==(const Matrix_t<T, M, V, A>::const_iterator& b) const
{
    return (this->mat_m == b.mat_m) && (this->row_m == b.row_m);
}

template<class T, class M, class V, class A>
bool Matrix_t<T, M, V, A>::const_iterator::operator!=(const Matrix_t<T, M, V, A>::const_iterator& b) const
{
    return !(*this == b);
}

template<class T, class M, class V, class A>
bool Matrix_t<T, M, V, A>::const_iterator::operator<(const Matrix_t<T, M, V, A>::const_iterator& b) const
{
    return (this->row_m < b.row_m);
}

template<class T, class M, class V, class A>
bool Matrix_t<T, M, V, A>::const_iterator::operator>(const Matrix_t<T, M, V, A>::const_iterator& b) const
{
    return (this->row_m > b.row_m);
}

template<class T, class M, class V, class A>
bool Matrix_t<T, M, V, A>::const_iterator::operator<=(const Matrix_t<T, M, V, A>::const_iterator& b) const
{
    return !(this->row_m > b.row_m);
}

template<class T, class M, class V, class A>
bool Matrix_t<T, M, V, A>::const_iterator::operator>=(const Matrix_t<T, M, V, A>::const_iterator& b) const
{
    return !(this->row_m < b.row_m);
}

template<class T, class M, class V, class A>
typename Matrix_t<T, M, V, A>::const_iterator& Matrix_t<T, M, V, A>::const_iterator::operator++()
{
    this->row_m++;
    return *this;
}

template<class T, class M, class V, class A>
typename Matrix_t<T, M, V, A>::const_iterator Matrix_t<T, M, V, A>::const_iterator::operator++(int)
{
    Matrix_t<T, M, V, A>::const_iterator tmp = *this;
    ++(*this);
    return tmp;
}

template<class T, class M, class V, class A>
typename Matrix_t<T, M, V, A>::const_iterator& Matrix_t<T, M, V, A>::const_iterator::operator--()
{
    this->row_m--;
    return *this;
}

template<class T, class M, class V, class A>
typename Matrix_t<T, M, V, A>::const_iterator Matrix_t<T, M, V, A>::const_iterator::operator--(int)
{
    Matrix_t<T, M, V, A>::const_iterator tmp = *this;
    --(*this);
    return tmp;
}

template<class T, class M, class V, class A>
typename Matrix_t<T, M, V, A>::const_iterator& Matrix_t<T, M, V, A>::const_iterator::
    operator+=(Matrix_t<T, M, V, A>::difference_type n)
{
    this->row_m += n;
    return *this;
}

template<class T, class M, class V, class A>
typename Matrix_t<T, M, V, A>::const_iterator Matrix_t<T, M, V, A>::const_iterator::
    operator+(Matrix_t<T, M, V, A>::difference_type n) const
{
    Matrix_t<T, M, V, A>::const_iterator tmp = *this;
    tmp += n;
    return tmp;
}

template<class T, class M, class V, class A>
typename Matrix_t<T, M, V, A>::const_iterator& Matrix_t<T, M, V, A>::const_iterator::
    operator-=(Matrix_t<T, M, V, A>::difference_type n)
{
    this->row_m -= n;
    return *this;
}

template<class T, class M, class V, class A>
typename Matrix_t<T, M, V, A>::const_iterator Matrix_t<T, M, V, A>::const_iterator::
    operator-(Matrix_t<T, M, V, A>::difference_type n) const
{
    Matrix_t<T, M, V, A>::const_iterator tmp = *this;
    tmp -= n;
    return tmp;
}

template<class T, class M, class V, class A>
typename Matrix_t<T, M, V, A>::const_iterator::difference_type Matrix_t<T, M, V, A>::const_iterator::
    operator-(const_iterator b) const
{
    return this->row_m - b.row_m;
}

template<class T, class M, class V, class A>
typename Matrix_t<T, M, V, A>::const_iterator::reference Matrix_t<T, M, V, A>::const_iterator::
    operator*() const
{
    if(static_cast<Matrix_t<T, M, V, A>::size_type>(this->row_m) >= this->mat_m.size().first
        || this->row_m < 0){
        throw(std::runtime_error("Error, dereferencing an iterator that is"
        "out of bounds!\n"));
    }
    return mat_m[static_cast<Matrix_t<T, M, V, A>::size_type>(this->row_m)];
}


template<class T, class M, class V, class A>
typename Matrix_t<T, M, V, A>::iterator Matrix_t<T, M, V, A>::begin()
{
    if(this->gsl_mat.get() == nullptr){
        throw std::runtime_error("Calling begin() on uninitialized Matrix");
    }
    return Matrix_t<T, M, V, A>::iterator(*this, 0);
}


template<class T, class M, class V, class A>
typename Matrix_t<T, M, V, A>::const_iterator Matrix_t<T ,M, V, A>::begin() const
{
    if(this->gsl_mat.get() == nullptr){
        throw std::runtime_error("Calling begin() on uninitialized Matrix");
    }
    return Matrix_t<T, M, V, A>::const_iterator(const_cast<Matrix_t<T, M, V, A>&>(*this), 0);
}


template<class T, class M, class V, class A>
typename Matrix_t<T, M, V, A>::const_iterator Matrix_t<T, M, V, A>::cbegin() const
{
    if(this->gsl_mat.get() == nullptr){
        throw std::runtime_error("Calling begin() on uninitialized Matrix");
    }
    return Matrix_t<T, M, V, A>::const_iterator(const_cast<Matrix_t<T, M, V, A>&>(*this), 0);
}

template<class T, class M, class V, class A>
typename Matrix_t<T, M, V, A>::iterator Matrix_t<T, M, V, A>::end()
{
    return this->begin() +
        static_cast<Matrix_t<T, M, V, A>::difference_type>(this->size().first);
}

template<class T, class M, class V, class A>
typename Matrix_t<T, M, V, A>::const_iterator Matrix_t<T, M, V, A>::end() const
{
    return this->begin() +
        static_cast<Matrix_t<T, M, V, A>::difference_type>(this->size().first);
}

template<class T, class M, class V, class A>
typename Matrix_t<T, M, V, A>::const_iterator Matrix_t<T, M, V, A>::cend() const
{
    return this->cbegin() +
        static_cast<Matrix_t<T, M, V, A>::difference_type>(this->size().first);
}

template<class T, class M, class V, class A>
typename Matrix_t<T, M, V, A>::reverse_iterator Matrix_t<T, M, V, A>::rbegin()
{
    return Matrix_t<T, M, V, A>::reverse_iterator(--(this->end()));
}

template<class T, class M, class V, class A>
typename Matrix_t<T, M, V, A>::const_reverse_iterator Matrix_t<T, M, V, A>::rbegin() const
{
    return Matrix_t<T, M, V, A>::const_reverse_iterator(--(this->end()));
}

template<class T, class M, class V, class A>
typename Matrix_t<T, M, V, A>::const_reverse_iterator Matrix_t<T, M, V, A>::crbegin() const
{
    return Matrix_t<T, M, V, A>::const_reverse_iterator(--(this->end()));
}

template<class T, class M, class V, class A>
typename Matrix_t<T, M, V, A>::reverse_iterator Matrix_t<T, M, V, A>::rend()
{
    return Matrix_t<T, M, V, A>::reverse_iterator(--(this->begin()));
}

template<class T, class M, class V, class A>
typename Matrix_t<T, M, V, A>::const_reverse_iterator Matrix_t<T, M, V, A>::rend() const
{
    return Matrix_t<T, M, V, A>::const_reverse_iterator(--(this->begin()));
}

template<class T, class M, class V, class A>
typename Matrix_t<T, M, V, A>::const_reverse_iterator Matrix_t<T, M, V, A>::crend() const
{
    return Matrix_t<T, M, V, A>::const_reverse_iterator(--(this->cbegin()));
}

template<class T, class M, class V, class A>
Vector_t<T, V, A>& Matrix_t<T, M, V, A>::
//V& Matrix_t<T, M, V, A>::
    operator[] (const typename Matrix_t<T, M, V, A>::size_type index)
{
    return *(this->begin() + static_cast<Matrix_t<T, M, V, A>::difference_type>(index));
    //return this->get_row(static_cast<Matrix_t<T, M, V, A>::difference_type>(index));
}

template<class T, class M, class V, class A>
const Vector_t<T, V, A>& Matrix_t<T, M, V, A>::
//const V& Matrix_t<T, M, V, A>::
    operator[] (const typename Matrix_t<T, M, V, A>::size_type index) const
{
    return *(this->cbegin() +
        static_cast<Matrix_t<T, M, V, A>::difference_type>(index));
    //return this->get_row(static_cast<Matrix_t<T, M, V, A>::difference_type>(index));
}


template<class T, class M, class V, class A>
Vector_t<T, V, A>& Matrix_t<T, M, V, A>::
    front()
{
    return *this->begin();
}

template<class T, class M, class V, class A>
const Vector_t<T, V, A>& Matrix_t<T, M, V, A>::
    front() const
{
    return *this->cbegin();
}


template<class T, class M, class V, class A>
Vector_t<T, V, A>& Matrix_t<T, M, V, A>::
    back()
{
    return *(--this->end());
}

template<class T, class M, class V, class A>
const Vector_t<T, V, A>& Matrix_t<T, M, V, A>::
    back() const
{
    return *(--this->cend());
}

template<class T, class M, class V, class A>
Vector_t<T, V, A>& Matrix_t<T, M, V, A>::
    at(const typename Matrix_t<T, M, V, A>::size_type index)
{
    return (*this)[index];
}

template<class T, class M, class V, class A>
const Vector_t<T, V, A>& Matrix_t<T, M, V, A>::
    at(const typename Matrix_t<T, M, V, A>::size_type index) const
{
    return (*this)[index];
}

template<class T, class M, class V, class A>
std::string Matrix_t<T, M, V, A>::to_string() const
{
    std::string res = "[";
    size_t i = 0, j = 0;
    for(auto& row : *this){
        if(i > 0 && i < this->size().first){
            res += ", ";
        }
        res += "( ";
        j = 0;
        for(auto& el : row){
            res += std::to_string(el);
            if(j < this->size().second - 1){
                res += ",";
            }
            res += " ";
            j++;
        }
        res += ")";
        i++;
    }
    res += "]";
    return res;
}

template<>
inline std::string Matrix_t<Complex_t<double, gsl_complex>, gsl_matrix_complex, gsl_vector_complex, std::allocator<gsl_complex>>::to_string() const
{
    std::string res = "[";
    size_t i = 0, j = 0;
    for(auto& row : *this){
        if(i > 0 && i < this->size().first){
            res += ", ";
        }
        res += "( ";
        j = 0;
        for(auto& el : row){
            res += Complex_t<double, gsl_complex>(el).to_string();
            if(j < this->size().second - 1){
                res += ",";
            }
            res += " ";
            j++;
        }
        res += ")";
        i++;
    }
    res += "]";

    return res;
}

template<>
inline std::string Matrix_t<Complex_t<long double, gsl_complex_long_double>, gsl_matrix_complex_long_double, gsl_vector_complex_long_double, std::allocator<gsl_complex_long_double>>::to_string() const
{
    std::string res = "[";
    size_t i = 0, j = 0;
    for(auto& row : *this){
        if(i > 0 && i < this->size().first){
            res += ", ";
        }
        res += "( ";
        j = 0;
        for(auto& el : row){
            res += Complex_t<long double, gsl_complex_long_double>(el).to_string();
            if(j < this->size().second - 1){
                res += ",";
            }
            res += " ";
            j++;
        }
        res += ")";
        i++;
    }
    res += "]";

    return res;
}

template<>
inline std::string Matrix_t<Complex_t<float, gsl_complex_float>, gsl_matrix_complex_float, gsl_vector_complex_float, std::allocator<gsl_complex_float>>::to_string() const
{
    std::string res = "[";
    size_t i = 0, j = 0;
    for(auto& row : *this){
        if(i > 0 && i < this->size().first){
            res += ", ";
        }
        res += "( ";
        j = 0;
        for(auto& el : row){
            res += Complex_t<float, gsl_complex_float>(el).to_string();
            if(j < this->size().second - 1){
                res += ",";
            }
            res += " ";
            j++;
        }
        res += ")";
        i++;
    }
    res += "]";

    return res;
}
}
