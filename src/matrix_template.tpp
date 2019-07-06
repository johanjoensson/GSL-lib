#include "matrix_template.h"
#include "complex.h"
#include "vector.h"
#include <gsl/gsl_blas.h>
#include <iostream>
#include <stdexcept>

namespace GSL{

template<class T, class GSL_MAT, class GSL_VEC, class A>
inline Matrix_t<T, GSL_MAT, GSL_VEC, A>::Matrix_t()
 : gsl_mat(nullptr), v_m()
{}

template<>
inline Matrix::Matrix_t(const Matrix_t::size_type n1, const Matrix_t::size_type n2)
 : gsl_mat(gsl_matrix_calloc(n1, n2), gsl_matrix_free), v_m()
{
    if(gsl_mat == nullptr){
        throw std::runtime_error("Memory allocation (gsl_matrix_calloc)"
        " failed!");
    }
}

template<>
inline Matrix_ld::
Matrix_t(const Matrix_t::size_type n1, const Matrix_t::size_type n2)
 : gsl_mat(gsl_matrix_long_double_calloc(n1, n2), gsl_matrix_long_double_free), v_m()
{

    if(gsl_mat == nullptr){
        throw std::runtime_error("Memory allocation (gsl_matrix_long_double_calloc)"
        " failed!");
    }
}

template<>
inline Matrix_f::
Matrix_t(const Matrix_t::size_type n1, const Matrix_t::size_type n2)
 : gsl_mat(gsl_matrix_float_calloc(n1, n2), gsl_matrix_float_free), v_m()
{
    if(gsl_mat == nullptr){
        throw std::runtime_error("Memory allocation (gsl_matrix_float_calloc)"
        " failed!");
    }
}

template<>
inline Matrix_i::
Matrix_t(const Matrix_t::size_type n1, const Matrix_t::size_type n2)
 : gsl_mat(gsl_matrix_int_calloc(n1, n2), gsl_matrix_int_free), v_m()
{
    if(gsl_mat == nullptr){
        throw std::runtime_error("Memory allocation (gsl_matrix_int_calloc)"
        " failed!");
    }
}

template<>
inline Matrix_ui::
Matrix_t(const Matrix_t::size_type n1, const Matrix_t::size_type n2)
 : gsl_mat(gsl_matrix_uint_calloc(n1, n2), gsl_matrix_uint_free), v_m()
{
    if(gsl_mat == nullptr){
        throw std::runtime_error("Memory allocation (gsl_matrix_uint_calloc)"
        " failed!");
    }
}

template<>
inline Matrix_l::
Matrix_t(const Matrix_t::size_type n1, const Matrix_t::size_type n2)
 : gsl_mat(gsl_matrix_long_calloc(n1, n2), gsl_matrix_long_free), v_m()
{
    if(gsl_mat == nullptr){
        throw std::runtime_error("Memory allocation (gsl_matrix_long_calloc)"
        " failed!");
    }
}

template<>
inline Matrix_ul::
Matrix_t(const Matrix_t::size_type n1, const Matrix_t::size_type n2)
 : gsl_mat(gsl_matrix_ulong_calloc(n1, n2), gsl_matrix_ulong_free), v_m()
{
    if(gsl_mat == nullptr){
        throw std::runtime_error("Memory allocation (gsl_matrix_ulong_calloc)"
        " failed!");
    }
}

template<>
inline Matrix_s::
Matrix_t(const Matrix_t::size_type n1, const Matrix_t::size_type n2)
 : gsl_mat(gsl_matrix_short_calloc(n1, n2), gsl_matrix_short_free), v_m()
{
    if(gsl_mat == nullptr){
        throw std::runtime_error("Memory allocation (gsl_matrix_short_calloc)"
        " failed!");
    }
}

template<>
inline Matrix_us::
Matrix_t(const Matrix_t::size_type n1, const Matrix_t::size_type n2)
 : gsl_mat(gsl_matrix_ushort_calloc(n1, n2), gsl_matrix_ushort_free), v_m()
{
    if(gsl_mat == nullptr){
        throw std::runtime_error("Memory allocation (gsl_matrix_ushort_calloc)"
        " failed!");
    }
}

template<>
inline Matrix_c::
Matrix_t(const Matrix_t::size_type n1, const Matrix_t::size_type n2)
 : gsl_mat(gsl_matrix_char_calloc(n1, n2), gsl_matrix_char_free), v_m()
{
    if(gsl_mat == nullptr){
        throw std::runtime_error("Memory allocation (gsl_matrix_char_calloc)"
        " failed!");
    }
}

template<>
inline Matrix_uc::
Matrix_t(const Matrix_t::size_type n1, const Matrix_t::size_type n2)
 : gsl_mat(gsl_matrix_uchar_calloc(n1, n2), gsl_matrix_uchar_free), v_m()
{
    if(gsl_mat == nullptr){
        throw std::runtime_error("Memory allocation (gsl_matrix_uchar_calloc)"
        " failed!");
    }
}

template<>
inline Matrix_cx::
Matrix_t(const Matrix_t::size_type n1, const Matrix_t::size_type n2)
 : gsl_mat(gsl_matrix_complex_calloc(n1, n2), gsl_matrix_complex_free), v_m()
{
    if(gsl_mat == nullptr){
        throw std::runtime_error("Memory allocation (gsl_matrix_complex_calloc)"
        " failed!");
    }
}

template<>
inline Matrix_cxld::
Matrix_t(const Matrix_t::size_type n1, const Matrix_t::size_type n2)
 : gsl_mat(gsl_matrix_complex_long_double_calloc(n1, n2), gsl_matrix_complex_long_double_free), v_m()
{
    if(gsl_mat == nullptr){
        throw std::runtime_error("Memory allocation (gsl_matrix_long_double_calloc)"
        " failed!");
    }
}

template<>
inline Matrix_cxf::Matrix_t
(const Matrix_t::size_type n1, const Matrix_t::size_type n2)
 : gsl_mat(gsl_matrix_complex_float_calloc(n1, n2), gsl_matrix_complex_float_free), v_m()
{
    if(gsl_mat == nullptr){
        throw std::runtime_error("Memory allocation (gsl_matrix_float_calloc)"
        " failed!");
    }
}

template<class T, class GSL_MATRIX, class GSL_VECTOR, class A>
inline Matrix_t<T, GSL_MATRIX, GSL_VECTOR, A>::
Matrix_t(std::initializer_list<GSL::Vector_t<T, GSL_VECTOR, A>> l)
 : Matrix_t(l.size(), l.begin()->size())
{
    auto row_it = l.begin();
    for(auto& row : *this){
	row = *row_it;
	row_it++;
    }
}

template<class T, class GSL_MAT, class GSL_VEC, class A>
Matrix_t<T, GSL_MAT, GSL_VEC, A>::operator GSL_MAT() const
{
    return *this->gsl_mat;
}

template<>
inline void Matrix::copy(const Matrix& a)
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
inline void Matrix_ld::copy
(const Matrix_ld& a)
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
inline void Matrix_f::copy
(const Matrix_f& a)
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
inline void Matrix_i::copy
(const Matrix_i& a)
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
inline void Matrix_ui::copy
(const Matrix_ui& a)
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
inline void Matrix_l::copy
(const Matrix_l& a)
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
inline void Matrix_ul::copy
(const Matrix_ul& a)
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
inline void Matrix_s::copy
(const Matrix_s& a)
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
inline void Matrix_us::copy
(const Matrix_us& a)
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
inline void Matrix_c::copy
(const Matrix_c& a)
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
inline void Matrix_uc::copy
(const Matrix_uc& a)
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
inline void Matrix_cx::copy
(const Matrix_cx& a)
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
inline void Matrix_cxld::copy
(const Matrix_cxld& a)
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
inline void Matrix_cxf::copy
(const Matrix_cxf& a)
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
    return *this;
}

template<class T, class G, class V, class A>
inline Matrix_t<T, G, V, A>& Matrix_t<T, G, V, A>::operator=(Matrix_t<T, G, V, A>&& a)
{
    std::swap(this->gsl_mat, a.gsl_mat);
    return *this;
}

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
inline Matrix& Matrix::operator+=(const Matrix& b)
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
inline Matrix_ld& Matrix_ld::operator+=(const Matrix_ld& b)
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
inline Matrix_f& Matrix_f::operator+=(const Matrix_f& b)
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
inline Matrix_i& Matrix_i::operator+=(const Matrix_i& b)
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
inline Matrix_ui& Matrix_ui::operator+=(const Matrix_ui& b)
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
inline Matrix_l& Matrix_l::operator+=(const Matrix_l& b)
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
inline Matrix_ul& Matrix_ul::operator+=(const Matrix_ul& b)
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
inline Matrix_s& Matrix_s::operator+=(const Matrix_s& b)
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
inline Matrix_us& Matrix_us::operator+=(const Matrix_us& b)
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
inline Matrix_c& Matrix_c::operator+=(const Matrix_c& b)
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
inline Matrix_uc& Matrix_uc::operator+=(const Matrix_uc& b)
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
inline Matrix_cx& Matrix_cx::operator+=(const Matrix_cx& b)
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
inline Matrix_cxld& Matrix_cxld::operator+=(const Matrix_cxld& b)
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
inline Matrix_cxf& Matrix_cxf::operator+=(const Matrix_cxf& b)
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
inline Matrix& Matrix::operator-=(const Matrix& b)
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
inline Matrix_ld& Matrix_ld::operator-=(const Matrix_ld& b)
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
inline Matrix_f& Matrix_f::operator-=(const Matrix_f& b)
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
inline Matrix_i& Matrix_i::operator-=(const Matrix_i& b)
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
inline Matrix_ui& Matrix_ui::operator-=(const Matrix_ui& b)
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
inline Matrix_l& Matrix_l::operator-=(const Matrix_l& b)
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
inline Matrix_ul& Matrix_ul::operator-=(const Matrix_ul& b)
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
inline Matrix_s& Matrix_s::operator-=(const Matrix_s& b)
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
inline Matrix_us& Matrix_us::operator-=(const Matrix_us& b)
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
inline Matrix_c& Matrix_c::operator-=(const Matrix_c& b)
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
inline Matrix_uc& Matrix_uc::operator-=(const Matrix_uc& b)
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
inline Matrix_cx& Matrix_cx::operator-=(const Matrix_cx& b)
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
inline Matrix_cxld& Matrix_cxld::operator-=(const Matrix_cxld& b)
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
inline Matrix_cxf& Matrix_cxf::operator-=(const Matrix_cxf& b)
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
    Matrix_t<T, M, V, A> tmp(this->size().first, b.size().second);
    for(Matrix_t<T, M, V, A>::size_type i = 0; i < this->size().first; i++){
        for(Matrix_t<T, M, V, A>::size_type j = 0; j < b.size().second; j++){
            for(Matrix_t<T, M, V, A>::size_type k = 0; k < this->size().second; k++){
                tmp[i][j] = static_cast<T>( tmp[i][j] + (*this)[i][k]*b[k][j] );
            }
        }
    }
    *this = tmp;
    return *this;
}

template<>
inline Matrix& Matrix::operator*=(const Matrix& b)
{
    Matrix tmp(this->gsl_mat->size1, b.gsl_mat->size2);
    int stat = gsl_blas_dgemm(CblasNoTrans, CblasNoTrans, 1.0, this->gsl_mat.get(),
        b.gsl_mat.get(), 0.0, tmp.gsl_mat.get());
    if(stat){
		std::string error_str =   gsl_strerror(stat);
		throw std::runtime_error("Error in matrix multiplication.\nGSL error: "
        + error_str);
	}
    *this = tmp;
    return *this;
}

template<>
inline Matrix_f& Matrix_f::operator*=(const Matrix_f& b)
{
    Matrix_f tmp(this->gsl_mat->size1, b.gsl_mat->size2);
    int stat = gsl_blas_sgemm(CblasNoTrans, CblasNoTrans, 1.0, this->gsl_mat.get(),
        b.gsl_mat.get(), 0.0, tmp.gsl_mat.get());
    if(stat){
		std::string error_str =   gsl_strerror(stat);
		throw std::runtime_error("Error in matrix addition.\nGSL error: "
        + error_str);
	}
    *this = tmp;
    return *this;
}

template<>
inline Matrix_cx& Matrix_cx::operator*=(const Matrix_cx& b)
{
    Matrix_cx tmp(this->gsl_mat->size1, b.gsl_mat->size2);
    int stat = gsl_blas_zgemm(CblasNoTrans, CblasNoTrans, Complex(1.0), this->gsl_mat.get(),
        b.gsl_mat.get(), Complex(0.0), tmp.gsl_mat.get());
    if(stat){
		std::string error_str =   gsl_strerror(stat);
		throw std::runtime_error("Error in matrix addition.\nGSL error: "
        + error_str);
	}
    *this = tmp;
    return *this;
}

template<>
inline Matrix_cxf& Matrix_cxf::operator*=(const Matrix_cxf& b)
{
    Matrix_cxf tmp(this->gsl_mat->size1, b.gsl_mat->size2);
    int stat = gsl_blas_cgemm(CblasNoTrans, CblasNoTrans, Complex_f(1.0), this->gsl_mat.get(),
        b.gsl_mat.get(), Complex_f(0.0), tmp.gsl_mat.get());
    if(stat){
		std::string error_str =   gsl_strerror(stat);
		throw std::runtime_error("Error in matrix addition.\nGSL error: "
        + error_str);
	}
    *this = tmp;
    return *this;
}

template<>
inline Matrix_cxld& Matrix_cxld::operator*=(const Matrix_cxld& b)
{
    Complex_ld c1(0), c2(0);
    Matrix_cxld::size_type rows, columns, c;
    rows = this->size().first;
    columns = b.size().second;
    c = this->size().second;
    Matrix_cxld tmp(this->size().first, b.size().second);
    for(Matrix_cxld::size_type i = 0; i < rows; i++){
        for(Matrix_cxld::size_type j = 0; j < columns; j++){
            for(Matrix_cxld::size_type k = 0; k < c; k++){
                c1 = Complex_ld((*this)[i][k]);
                c2 = Complex_ld(b[k][j]);
                tmp[i][j] = Complex_ld(tmp[i][j]) + c1*c2;
            }
        }
    }
    *this = tmp;
    return *this;
}
template<>
inline Matrix& Matrix::operator/=(const Matrix& b)
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
inline Matrix_ld& Matrix_ld::operator/=(const Matrix_ld& b)
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
inline Matrix_f& Matrix_f::operator/=(const Matrix_f& b)
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
inline Matrix_i& Matrix_i::operator/=(const Matrix_i& b)
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
inline Matrix_ui& Matrix_ui::operator/=(const Matrix_ui& b)
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
inline Matrix_l& Matrix_l::operator/=(const Matrix_l& b)
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
inline Matrix_ul& Matrix_ul::operator/=(const Matrix_ul& b)
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
inline Matrix_s& Matrix_s::operator/=(const Matrix_s& b)
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
inline Matrix_us& Matrix_us::operator/=(const Matrix_us& b)
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
inline Matrix_c& Matrix_c::operator/=(const Matrix_c& b)
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
inline Matrix_uc& Matrix_uc::operator/=(const Matrix_uc& b)
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
inline Matrix_cx& Matrix_cx::operator/=(const Matrix_cx& b)
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
inline Matrix_cxld& Matrix_cxld::operator/=(const Matrix_cxld& b)
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
inline Matrix_cxf& Matrix_cxf::operator/=(const Matrix_cxf& b)
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
inline Matrix& Matrix::operator*=(const double& b)
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
inline Matrix_ld& Matrix_ld::operator*=(const long double& b)
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
inline Matrix_f& Matrix_f::operator*=(const float& b)
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
inline Matrix_i& Matrix_i::operator*=(const int& b)
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
inline Matrix_ui& Matrix_ui::operator*=(const unsigned int& b)
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
inline Matrix_l& Matrix_l::operator*=(const long& b)
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
inline Matrix_ul& Matrix_ul::operator*=(const unsigned long& b)
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
inline Matrix_s& Matrix_s::operator*=(const short& b)
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
inline Matrix_us& Matrix_us::operator*=(const unsigned short& b)
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
inline Matrix_c& Matrix_c::operator*=(const char& b)
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
inline Matrix_uc& Matrix_uc::operator*=(const unsigned char& b)
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
inline Matrix_cx& Matrix_cx::operator*=(const Complex& b)
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
inline Matrix_cxld& Matrix_cxld::operator*=(const Complex_ld& b)
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
inline Matrix_cxf& Matrix_cxf::operator*=(const Complex_f& b)
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
inline Matrix& Matrix::operator/=(const double& b)
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
inline Matrix_ld& Matrix_ld::operator/=(const long double& b)
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
inline Matrix_f& Matrix_f::operator/=(const float& b)
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
inline Matrix_i& Matrix_i::operator/=(const int& b)
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
inline Matrix_ui& Matrix_ui::operator/=(const unsigned int& b)
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
inline Matrix_l& Matrix_l::operator/=(const long& b)
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
inline Matrix_ul& Matrix_ul::operator/=(const unsigned long& b)
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
inline Matrix_s& Matrix_s::operator/=(const short& b)
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
inline Matrix_us& Matrix_us::operator/=(const unsigned short& b)
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
inline Matrix_c& Matrix_c::operator/=(const char& b)
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
inline Matrix_uc& Matrix_uc::operator/=(const unsigned char& b)
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
inline Matrix_cx& Matrix_cx::operator/=(const Complex& b)
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
inline Matrix_cxld& Matrix_cxld::operator/=(const Complex_ld& b)
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
inline Matrix_cxf& Matrix_cxf::operator/=(const Complex_f& b)
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
inline Vector Matrix::operator*(const Vector& v)
{
    Vector res(this->size().second);
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
inline Vector_f Matrix_f::operator*(const Vector_f& v)
{
    Vector_f res(this->size().second);
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
inline Vector_cx Matrix_cx::operator*(const Vector_cx& v)
{
    Vector_cx res(this->size().second);
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
inline Vector_cxf Matrix_cxf::operator*(const Vector_cxf& v)
{
    Vector_cxf res(this->size().second);
    int stat = gsl_blas_cgemv(CblasNoTrans, Complex_f(1.0), this->gsl_mat.get(),
        v.gsl_vec.get(), Complex_f(0.0), res.gsl_vec.get());
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
inline bool Matrix::operator==(const Matrix& b) const
{
    if(this->gsl_mat.get() == nullptr && b.gsl_mat.get() == nullptr){
        return true;
    }else if(this->gsl_mat.get() == nullptr || b.gsl_mat.get() == nullptr){
        return false;
    }
    return gsl_matrix_equal(this->gsl_mat.get(), b.gsl_mat.get());
}

template<>
inline bool Matrix_ld::operator==(const Matrix_ld& b) const
{
    if(this->gsl_mat.get() == nullptr && b.gsl_mat.get() == nullptr){
        return true;
    }else if(this->gsl_mat.get() == nullptr || b.gsl_mat.get() == nullptr){
        return false;
    }
    return gsl_matrix_long_double_equal(this->gsl_mat.get(), b.gsl_mat.get());
}

template<>
inline bool Matrix_f::operator==(const Matrix_f& b) const
{
    if(this->gsl_mat.get() == nullptr && b.gsl_mat.get() == nullptr){
        return true;
    }else if(this->gsl_mat.get() == nullptr || b.gsl_mat.get() == nullptr){
        return false;
    }
    return gsl_matrix_float_equal(this->gsl_mat.get(), b.gsl_mat.get());
}

template<>
inline bool Matrix_i::operator==(const Matrix_i& b) const
{
    if(this->gsl_mat.get() == nullptr && b.gsl_mat.get() == nullptr){
        return true;
    }else if(this->gsl_mat.get() == nullptr || b.gsl_mat.get() == nullptr){
        return false;
    }
    return gsl_matrix_int_equal(this->gsl_mat.get(), b.gsl_mat.get());
}

template<>
inline bool Matrix_ui::operator==(const Matrix_ui& b) const
{
    if(this->gsl_mat.get() == nullptr && b.gsl_mat.get() == nullptr){
        return true;
    }else if(this->gsl_mat.get() == nullptr || b.gsl_mat.get() == nullptr){
        return false;
    }
    return gsl_matrix_uint_equal(this->gsl_mat.get(), b.gsl_mat.get());
}

template<>
inline bool Matrix_l::operator==(const Matrix_l& b) const
{
    if(this->gsl_mat.get() == nullptr && b.gsl_mat.get() == nullptr){
        return true;
    }else if(this->gsl_mat.get() == nullptr || b.gsl_mat.get() == nullptr){
        return false;
    }
    return gsl_matrix_long_equal(this->gsl_mat.get(), b.gsl_mat.get());
}

template<>
inline bool Matrix_ul::operator==(const Matrix_ul& b) const
{
    if(this->gsl_mat.get() == nullptr && b.gsl_mat.get() == nullptr){
        return true;
    }else if(this->gsl_mat.get() == nullptr || b.gsl_mat.get() == nullptr){
        return false;
    }
    return gsl_matrix_ulong_equal(this->gsl_mat.get(), b.gsl_mat.get());
}

template<>
inline bool Matrix_s::operator==(const Matrix_s& b) const
{
    if(this->gsl_mat.get() == nullptr && b.gsl_mat.get() == nullptr){
        return true;
    }else if(this->gsl_mat.get() == nullptr || b.gsl_mat.get() == nullptr){
        return false;
    }
    return gsl_matrix_short_equal(this->gsl_mat.get(), b.gsl_mat.get());
}

template<>
inline bool Matrix_us::operator==(const Matrix_us& b) const
{
    if(this->gsl_mat.get() == nullptr && b.gsl_mat.get() == nullptr){
        return true;
    }else if(this->gsl_mat.get() == nullptr || b.gsl_mat.get() == nullptr){
        return false;
    }
    return gsl_matrix_ushort_equal(this->gsl_mat.get(), b.gsl_mat.get());
}

template<>
inline bool Matrix_c::operator==(const Matrix_c& b) const
{
    if(this->gsl_mat.get() == nullptr && b.gsl_mat.get() == nullptr){
        return true;
    }else if(this->gsl_mat.get() == nullptr || b.gsl_mat.get() == nullptr){
        return false;
    }
    return gsl_matrix_char_equal(this->gsl_mat.get(), b.gsl_mat.get());
}

template<>
inline bool Matrix_uc::operator==(const Matrix_uc& b) const
{
    if(this->gsl_mat.get() == nullptr && b.gsl_mat.get() == nullptr){
        return true;
    }else if(this->gsl_mat.get() == nullptr || b.gsl_mat.get() == nullptr){
        return false;
    }
    return gsl_matrix_uchar_equal(this->gsl_mat.get(), b.gsl_mat.get());
}

template<>
inline bool Matrix_cx::operator==(const Matrix_cx& b) const
{
    if(this->gsl_mat.get() == nullptr && b.gsl_mat.get() == nullptr){
        return true;
    }else if(this->gsl_mat.get() == nullptr || b.gsl_mat.get() == nullptr){
        return false;
    }
    return gsl_matrix_complex_equal(this->gsl_mat.get(), b.gsl_mat.get());
}

template<>
inline bool Matrix_cxld::operator==(const Matrix_cxld& b) const
{
    if(this->gsl_mat.get() == nullptr && b.gsl_mat.get() == nullptr){
        return true;
    }else if(this->gsl_mat.get() == nullptr || b.gsl_mat.get() == nullptr){
        return false;
    }
    return gsl_matrix_complex_long_double_equal(this->gsl_mat.get(), b.gsl_mat.get());
}

template<>
inline bool Matrix_cxf::operator==(const Matrix_cxf& b) const
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

template<class T, class M, class V, class A>
Matrix_t<T, M, V, A> Matrix_t<T, M, V, A>::hermitian_transpose() const
{
    return this->transpose();
}

template<>
inline Matrix_cx
Matrix_cx::
hermitian_transpose() const
{
    Matrix_cx
        res(this->size().second, this->size().first);
    for(Matrix_cx::size_type
            i = 0; i < this->size().second; i++){
        for(Matrix_cx::size_type
                j = 0; j < this->size().first; j++){
                    res[i][j] = Complex((*this)[j][i]).conjugate();
        }
    }
    return res;
}

template<>
inline Matrix_cxld
Matrix_cxld::
hermitian_transpose() const
{
    Matrix_cxld
        res(this->size().second, this->size().first);
    for(Matrix_cxld::size_type
            i = 0; i < this->size().second; i++){
        for(Matrix_cxld::size_type
                j = 0; j < this->size().first; j++){
                    res[i][j] = Complex_ld((*this)[j][i]).conjugate();
        }
    }
    return res;
}

template<>
inline Matrix_cxf
Matrix_cxf::
hermitian_transpose() const
{
    Matrix_cxf
        res(this->size().second, this->size().first);
    for(Matrix_cx::size_type
            i = 0; i < this->size().second; i++){
        for(Matrix_cx::size_type
                j = 0; j < this->size().first; j++){
                    res[i][j] = Complex_f((*this)[j][i]).conjugate();
        }
    }
    return res;
}

template<>
inline Matrix Matrix::inverse() const
{
    return GSL::lu_inverse(*this);
}

template<>
inline Matrix_cx Matrix_cx::inverse() const
{
    return GSL::lu_inverse(*this);
}

template<>
inline Vector& Matrix::get_row(const Matrix::difference_type i)
{
    if(i < 0 || static_cast<Matrix::size_type>(i) >= this->size().first){
        throw(std::runtime_error("Error, dereferencing an iterator that is"
        "out of bounds!\n"));
    }
    gsl_vector tmp = gsl_matrix_row(this->gsl_mat.get(), static_cast<Matrix::size_type>(i)).vector;
    v_m.gsl_vec = std::shared_ptr<gsl_vector>(new gsl_vector);
    *v_m.gsl_vec.get() = tmp;
    return v_m;
}

template<>
inline Vector_ld& Matrix_ld::get_row(const Matrix_ld::difference_type i)
{
    if(i < 0 || static_cast<Matrix_ld::size_type>(i) >= this->size().first){
        throw(std::runtime_error("Error, dereferencing an iterator that is"
        "out of bounds!\n"));
    }
    gsl_vector_long_double tmp = gsl_matrix_long_double_row(this->gsl_mat.get(), static_cast<Matrix_ld::size_type>(i)).vector;
    v_m.gsl_vec = std::shared_ptr<gsl_vector_long_double>(new gsl_vector_long_double);
    *v_m.gsl_vec.get() = tmp;
    return v_m;
}

template<>
inline Vector_f& Matrix_f::get_row(const Matrix_f::difference_type i)
{
    if(i < 0 || static_cast<Matrix_f::size_type>(i) >= this->size().first){
        throw(std::runtime_error("Error, dereferencing an iterator that is"
        "out of bounds!\n"));
    }
    gsl_vector_float tmp = gsl_matrix_float_row(this->gsl_mat.get(), static_cast<Matrix_f::size_type>(i)).vector;
    v_m.gsl_vec = std::shared_ptr<gsl_vector_float>(new gsl_vector_float);
    *v_m.gsl_vec.get() = tmp;
    return v_m;
}

template<>
inline Vector_i& Matrix_i::get_row(const Matrix_i::difference_type i)
{
    if(i < 0 || static_cast<Matrix_i::size_type>(i) >= this->size().first){
        throw(std::runtime_error("Error, dereferencing an iterator that is"
        "out of bounds!\n"));
    }
    gsl_vector_int tmp = gsl_matrix_int_row(this->gsl_mat.get(), static_cast<Matrix_i::size_type>(i)).vector;
    v_m.gsl_vec = std::shared_ptr<gsl_vector_int>(new gsl_vector_int);
    *v_m.gsl_vec.get() = tmp;
    return v_m;
}

template<>
inline Vector_ui& Matrix_ui::get_row(const Matrix_ui::difference_type i)
{
    if(i < 0 || static_cast<Matrix_ui::size_type>(i) >= this->size().first){
        throw(std::runtime_error("Error, dereferencing an iterator that is"
        "out of bounds!\n"));
    }
    gsl_vector_uint tmp = gsl_matrix_uint_row(this->gsl_mat.get(), static_cast<Matrix_ui::size_type>(i)).vector;
    v_m.gsl_vec = std::shared_ptr<gsl_vector_uint>(new gsl_vector_uint);
    *v_m.gsl_vec.get() = tmp;
    return v_m;
}

template<>
inline Vector_l& Matrix_l::get_row(const Matrix_l::difference_type i)
{
    if(i < 0 || static_cast<Matrix_l::size_type>(i) >= this->size().first){
        throw(std::runtime_error("Error, dereferencing an iterator that is"
        "out of bounds!\n"));
    }
    gsl_vector_long tmp = gsl_matrix_long_row(this->gsl_mat.get(), static_cast<Matrix_l::size_type>(i)).vector;
    v_m.gsl_vec = std::shared_ptr<gsl_vector_long>(new gsl_vector_long);
    *v_m.gsl_vec.get() = tmp;
    return v_m;
}

template<>
inline Vector_ul& Matrix_ul::get_row(const Matrix_ul::difference_type i)
{
    if(i < 0 || static_cast<Matrix_ul::size_type>(i) >= this->size().first){
        throw(std::runtime_error("Error, dereferencing an iterator that is"
        "out of bounds!\n"));
    }
    gsl_vector_ulong tmp = gsl_matrix_ulong_row(this->gsl_mat.get(), static_cast<Matrix_ul::size_type>(i)).vector;
    v_m.gsl_vec = std::shared_ptr<gsl_vector_ulong>(new gsl_vector_ulong);
    *v_m.gsl_vec.get() = tmp;
    return v_m;
}

template<>
inline Vector_s& Matrix_s::get_row(const Matrix_s::difference_type i)
{
    if(i < 0 || static_cast<Matrix_s::size_type>(i) >= this->size().first){
        throw(std::runtime_error("Error, dereferencing an iterator that is"
        "out of bounds!\n"));
    }
    gsl_vector_short tmp = gsl_matrix_short_row(this->gsl_mat.get(), static_cast<Matrix_s::size_type>(i)).vector;
    v_m.gsl_vec = std::shared_ptr<gsl_vector_short>(new gsl_vector_short);
    *v_m.gsl_vec.get() = tmp;
    return v_m;
}

template<>
inline Vector_us& Matrix_us::get_row(const Matrix_us::difference_type i)
{
    if(i < 0 || static_cast<Matrix_us::size_type>(i) >= this->size().first){
        throw(std::runtime_error("Error, dereferencing an iterator that is"
        "out of bounds!\n"));
    }
    gsl_vector_ushort tmp = gsl_matrix_ushort_row(this->gsl_mat.get(), static_cast<Matrix_us::size_type>(i)).vector;
    v_m.gsl_vec = std::shared_ptr<gsl_vector_ushort>(new gsl_vector_ushort);
    *v_m.gsl_vec.get() = tmp;
    return v_m;
}

template<>
inline Vector_c& Matrix_c::get_row(const Matrix_c::difference_type i)
{
    if(i < 0 || static_cast<Matrix_c::size_type>(i) >= this->size().first){
        throw(std::runtime_error("Error, dereferencing an iterator that is"
        "out of bounds!\n"));
    }
    gsl_vector_char tmp = gsl_matrix_char_row(this->gsl_mat.get(), static_cast<Matrix_c::size_type>(i)).vector;
    v_m.gsl_vec = std::shared_ptr<gsl_vector_char>(new gsl_vector_char);
    *v_m.gsl_vec.get() = tmp;
    return v_m;
}

template<>
inline Vector_uc& Matrix_uc::get_row(const Matrix_uc::difference_type i)
{
    if(i < 0 || static_cast<Matrix_uc::size_type>(i) >= this->size().first){
        throw(std::runtime_error("Error, dereferencing an iterator that is"
        "out of bounds!\n"));
    }
    gsl_vector_uchar tmp = gsl_matrix_uchar_row(this->gsl_mat.get(), static_cast<Matrix_uc::size_type>(i)).vector;
    v_m.gsl_vec = std::shared_ptr<gsl_vector_uchar>(new gsl_vector_uchar);
    *v_m.gsl_vec.get() = tmp;
    return v_m;
}

template<>
inline Vector_cx& Matrix_cx::get_row(const Matrix_cx::difference_type i)
{
    if(i < 0 || static_cast<Matrix_cx::size_type>(i) >= this->size().first){
        throw(std::runtime_error("Error, dereferencing an iterator that is"
        "out of bounds!\n"));
    }
    gsl_vector_complex tmp = gsl_matrix_complex_row(this->gsl_mat.get(), static_cast<Matrix_cx::size_type>(i)).vector;
    v_m.gsl_vec = std::shared_ptr<gsl_vector_complex>(new gsl_vector_complex);
    *v_m.gsl_vec.get() = tmp;
    return v_m;
}

template<>
inline Vector_cxld& Matrix_cxld::get_row(const Matrix_cxld::difference_type i)
{
    if(i < 0 || static_cast<Matrix_cxld::size_type>(i) >= this->size().first){
        throw(std::runtime_error("Error, dereferencing an iterator that is"
        "out of bounds!\n"));
    }
    gsl_vector_complex_long_double tmp = gsl_matrix_complex_long_double_row(this->gsl_mat.get(), static_cast<Matrix_cxld::size_type>(i)).vector;
    v_m.gsl_vec = std::shared_ptr<gsl_vector_complex_long_double>(new gsl_vector_complex_long_double);
    *v_m.gsl_vec.get() = tmp;
    return v_m;
}

template<>
inline Vector_cxf& Matrix_cxf::get_row(const Matrix_cxf::difference_type i)
{
    if(i < 0 || static_cast<Matrix_cxf::size_type>(i) >= this->size().first){
        throw(std::runtime_error("Error, dereferencing an iterator that is"
        "out of bounds!\n"));
    }
    gsl_vector_complex_float tmp = gsl_matrix_complex_float_row(this->gsl_mat.get(), static_cast<Matrix_cxf::size_type>(i)).vector;
    v_m.gsl_vec = std::shared_ptr<gsl_vector_complex_float>(new gsl_vector_complex_float);
    *v_m.gsl_vec.get() = tmp;
    return v_m;
}

template<>
inline Vector& Matrix::get_col(const Matrix::difference_type i)
{
    if(i < 0 || static_cast<Matrix::size_type>(i) >= this->size().second){
        throw(std::runtime_error("Error, dereferencing an iterator that is"
        "out of bounds!\n"));
    }
    gsl_vector tmp = gsl_matrix_column(this->gsl_mat.get(), static_cast<Matrix::size_type>(i)).vector;
    v_m.gsl_vec = std::shared_ptr<gsl_vector>(new gsl_vector);
    *v_m.gsl_vec.get() = tmp;
    return v_m;
}

template<>
inline Vector_ld& Matrix_ld::get_col(const Matrix_ld::difference_type i)
{
    if(i < 0 || static_cast<Matrix_ld::size_type>(i) >= this->size().second){
        throw(std::runtime_error("Error, dereferencing an iterator that is"
        "out of bounds!\n"));
    }
    gsl_vector_long_double tmp = gsl_matrix_long_double_column(this->gsl_mat.get(), static_cast<Matrix_ld::size_type>(i)).vector;
    v_m.gsl_vec = std::shared_ptr<gsl_vector_long_double>(new gsl_vector_long_double);
    *v_m.gsl_vec.get() = tmp;
    return v_m;
}

template<>
inline Vector_f& Matrix_f::get_col(const Matrix_f::difference_type i)
{
    if(i < 0 || static_cast<Matrix_f::size_type>(i) >= this->size().second){
        throw(std::runtime_error("Error, dereferencing an iterator that is"
        "out of bounds!\n"));
    }
    gsl_vector_float tmp = gsl_matrix_float_column(this->gsl_mat.get(), static_cast<Matrix_f::size_type>(i)).vector;
    v_m.gsl_vec = std::shared_ptr<gsl_vector_float>(new gsl_vector_float);
    *v_m.gsl_vec.get() = tmp;
    return v_m;
}

template<>
inline Vector_i& Matrix_i::get_col(const Matrix_i::difference_type i)
{
    if(i < 0 || static_cast<Matrix_i::size_type>(i) >= this->size().second){
        throw(std::runtime_error("Error, dereferencing an iterator that is"
        "out of bounds!\n"));
    }
    gsl_vector_int tmp = gsl_matrix_int_column(this->gsl_mat.get(), static_cast<Matrix_i::size_type>(i)).vector;
    v_m.gsl_vec = std::shared_ptr<gsl_vector_int>(new gsl_vector_int);
    *v_m.gsl_vec.get() = tmp;
    return v_m;
}

template<>
inline Vector_ui& Matrix_ui::get_col(const Matrix_ui::difference_type i)
{
    if(i < 0 || static_cast<Matrix_ui::size_type>(i) >= this->size().second){
        throw(std::runtime_error("Error, dereferencing an iterator that is"
        "out of bounds!\n"));
    }
    gsl_vector_uint tmp = gsl_matrix_uint_column(this->gsl_mat.get(), static_cast<Matrix_ui::size_type>(i)).vector;
    v_m.gsl_vec = std::shared_ptr<gsl_vector_uint>(new gsl_vector_uint);
    *v_m.gsl_vec.get() = tmp;
    return v_m;
}

template<>
inline Vector_l& Matrix_l::get_col(const Matrix_l::difference_type i)
{
    if(i < 0 || static_cast<Matrix_l::size_type>(i) >= this->size().second){
        throw(std::runtime_error("Error, dereferencing an iterator that is"
        "out of bounds!\n"));
    }
    gsl_vector_long tmp = gsl_matrix_long_column(this->gsl_mat.get(), static_cast<Matrix_l::size_type>(i)).vector;
    v_m.gsl_vec = std::shared_ptr<gsl_vector_long>(new gsl_vector_long);
    *v_m.gsl_vec.get() = tmp;
    return v_m;
}

template<>
inline Vector_ul& Matrix_ul::get_col(const Matrix_ul::difference_type i)
{
    if(i < 0 || static_cast<Matrix_ul::size_type>(i) >= this->size().second){
        throw(std::runtime_error("Error, dereferencing an iterator that is"
        "out of bounds!\n"));
    }
    gsl_vector_ulong tmp = gsl_matrix_ulong_column(this->gsl_mat.get(), static_cast<Matrix_ul::size_type>(i)).vector;
    v_m.gsl_vec = std::shared_ptr<gsl_vector_ulong>(new gsl_vector_ulong);
    *v_m.gsl_vec.get() = tmp;
    return v_m;
}

template<>
inline Vector_s& Matrix_s::get_col(const Matrix_s::difference_type i)
{
    if(i < 0 || static_cast<Matrix_s::size_type>(i) >= this->size().second){
        throw(std::runtime_error("Error, dereferencing an iterator that is"
        "out of bounds!\n"));
    }
    gsl_vector_short tmp = gsl_matrix_short_column(this->gsl_mat.get(), static_cast<Matrix_s::size_type>(i)).vector;
    v_m.gsl_vec = std::shared_ptr<gsl_vector_short>(new gsl_vector_short);
    *v_m.gsl_vec.get() = tmp;
    return v_m;
}

template<>
inline Vector_us& Matrix_us::get_col(const Matrix_us::difference_type i)
{
    if(i < 0 || static_cast<Matrix_us::size_type>(i) >= this->size().second){
        throw(std::runtime_error("Error, dereferencing an iterator that is"
        "out of bounds!\n"));
    }
    gsl_vector_ushort tmp = gsl_matrix_ushort_column(this->gsl_mat.get(), static_cast<Matrix_us::size_type>(i)).vector;
    v_m.gsl_vec = std::shared_ptr<gsl_vector_ushort>(new gsl_vector_ushort);
    *v_m.gsl_vec.get() = tmp;
    return v_m;
}

template<>
inline Vector_c& Matrix_c::get_col(const Matrix_c::difference_type i)
{
    if(i < 0 || static_cast<Matrix_c::size_type>(i) >= this->size().second){
        throw(std::runtime_error("Error, dereferencing an iterator that is"
        "out of bounds!\n"));
    }
    gsl_vector_char tmp = gsl_matrix_char_column(this->gsl_mat.get(), static_cast<Matrix_c::size_type>(i)).vector;
    v_m.gsl_vec = std::shared_ptr<gsl_vector_char>(new gsl_vector_char);
    *v_m.gsl_vec.get() = tmp;
    return v_m;
}

template<>
inline Vector_uc& Matrix_uc::get_col(const Matrix_uc::difference_type i)
{
    if(i < 0 || static_cast<Matrix_uc::size_type>(i) >= this->size().second){
        throw(std::runtime_error("Error, dereferencing an iterator that is"
        "out of bounds!\n"));
    }
    gsl_vector_uchar tmp = gsl_matrix_uchar_column(this->gsl_mat.get(), static_cast<Matrix_uc::size_type>(i)).vector;
    v_m.gsl_vec = std::shared_ptr<gsl_vector_uchar>(new gsl_vector_uchar);
    *v_m.gsl_vec.get() = tmp;
    return v_m;
}

template<>
inline Vector_cx& Matrix_cx::get_col(const Matrix_cx::difference_type i)
{
    if(i < 0 || static_cast<Matrix_cx::size_type>(i) >= this->size().second){
        throw(std::runtime_error("Error, dereferencing an iterator that is"
        "out of bounds!\n"));
    }
    gsl_vector_complex tmp = gsl_matrix_complex_column(this->gsl_mat.get(), static_cast<Matrix_cx::size_type>(i)).vector;
    v_m.gsl_vec = std::shared_ptr<gsl_vector_complex>(new gsl_vector_complex);
    *v_m.gsl_vec.get() = tmp;
    return v_m;
}

template<>
inline Vector_cxld& Matrix_cxld::get_col(const Matrix_cxld::difference_type i)
{
    if(i < 0 || static_cast<Matrix_cxld::size_type>(i) >= this->size().second){
        throw(std::runtime_error("Error, dereferencing an iterator that is"
        "out of bounds!\n"));
    }
    gsl_vector_complex_long_double tmp = gsl_matrix_complex_long_double_column(this->gsl_mat.get(), static_cast<Matrix_cxld::size_type>(i)).vector;
    v_m.gsl_vec = std::shared_ptr<gsl_vector_complex_long_double>(new gsl_vector_complex_long_double);
    *v_m.gsl_vec.get() = tmp;
    return v_m;
}

template<>
inline Vector_cxf& Matrix_cxf::get_col(const Matrix_cxf::difference_type i)
{
    if(i < 0 || static_cast<Matrix_cxf::size_type>(i) >= this->size().second){
        throw(std::runtime_error("Error, dereferencing an iterator that is"
        "out of bounds!\n"));
    }
    gsl_vector_complex_float tmp = gsl_matrix_complex_float_column(this->gsl_mat.get(), static_cast<Matrix_cxf::size_type>(i)).vector;
    v_m.gsl_vec = std::shared_ptr<gsl_vector_complex_float>(new gsl_vector_complex_float);
    *v_m.gsl_vec.get() = tmp;
    return v_m;
}


template<class T, class M, class V, class A>
Matrix_t<T, M, V, A>::iterator::iterator(Matrix_t<T, M, V, A>& mat, Matrix_t<T, M, V, A>::difference_type n)
 : mat_m(mat), row_m(n)
{}

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
    return Matrix_t<T, M, V, A>::reverse_iterator(this->end());
}

template<class T, class M, class V, class A>
typename Matrix_t<T, M, V, A>::const_reverse_iterator Matrix_t<T, M, V, A>::rbegin() const
{
    return Matrix_t<T, M, V, A>::const_reverse_iterator(this->end());
}

template<class T, class M, class V, class A>
typename Matrix_t<T, M, V, A>::const_reverse_iterator Matrix_t<T, M, V, A>::crbegin() const
{
    return Matrix_t<T, M, V, A>::const_reverse_iterator(this->end());
}

template<class T, class M, class V, class A>
typename Matrix_t<T, M, V, A>::reverse_iterator Matrix_t<T, M, V, A>::rend()
{
    return Matrix_t<T, M, V, A>::reverse_iterator(this->begin());
}

template<class T, class M, class V, class A>
typename Matrix_t<T, M, V, A>::const_reverse_iterator Matrix_t<T, M, V, A>::rend() const
{
    return Matrix_t<T, M, V, A>::const_reverse_iterator(this->begin());
}

template<class T, class M, class V, class A>
typename Matrix_t<T, M, V, A>::const_reverse_iterator Matrix_t<T, M, V, A>::crend() const
{
    return Matrix_t<T, M, V, A>::const_reverse_iterator(this->cbegin());
}

template<class T, class M, class V, class A>
Vector_t<T, V, A>& Matrix_t<T, M, V, A>::
    operator[] (const typename Matrix_t<T, M, V, A>::size_type index)
{
    return *(this->begin() + static_cast<Matrix_t<T, M, V, A>::difference_type>(index));
}

template<class T, class M, class V, class A>
const Vector_t<T, V, A>& Matrix_t<T, M, V, A>::
    operator[] (const typename Matrix_t<T, M, V, A>::size_type index) const
{
    return *(this->cbegin() +
        static_cast<Matrix_t<T, M, V, A>::difference_type>(index));
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
    if(index >= this->gsl_mat->size1){
        throw std::out_of_range("Row index " + std::to_string(index) + " out of range.");
    }
    return (*this)[index];
}

template<class T, class M, class V, class A>
const Vector_t<T, V, A>& Matrix_t<T, M, V, A>::
    at(const typename Matrix_t<T, M, V, A>::size_type index) const
{
    if(index >= this->gsl_mat->size1){
        throw std::out_of_range("Row index " + std::to_string(index) + " out of range.");
    }
    return (*this)[index];
}

template<class T, class M, class V, class A>
typename Matrix_t<T, M, V, A>::reference Matrix_t<T, M, V, A>::
    at(const typename Matrix_t<T, M, V, A>::size_type i, const typename Matrix_t<T, M, V, A>::size_type j)
{
    if(i >= this->gsl_mat->size1 || j >= this->gsl_mat->size2){
        throw std::out_of_range("Element at (" + std::to_string(i) + ", " + std::to_string(j) + ") out of range.");
    }
    return this->gsl_mat->data[i*this->gsl_mat->tda + j];
}

template<class T, class M, class V, class A>
typename Matrix_t<T, M, V, A>::const_reference Matrix_t<T, M, V, A>::
    at(const typename Matrix_t<T, M, V, A>::size_type i, const typename Matrix_t<T, M, V, A>::size_type j) const
{
    if(i >= this->gsl_mat->size1 || j >= this->gsl_mat->size2){
        throw std::out_of_range("Element at (" + std::to_string(i) + ", " + std::to_string(j) + ") out of range.");
    }
    return this->gsl_mat->data[i*this->gsl_mat->tda + j];
}

template<>
inline typename Matrix_cx::reference Matrix_cx::at(const Matrix_cx::size_type i, const Matrix_cx::size_type j)
{
    if(i >= this->gsl_mat->size1 || j >= this->gsl_mat->size2){
        throw std::out_of_range("Element at (" + std::to_string(i) + ", " + std::to_string(j) + ") out of range.");
    }
    return *gsl_matrix_complex_ptr(this->gsl_mat.get(), i, j);
}

template<>
inline typename Matrix_cx::const_reference Matrix_cx::at(const Matrix_cx::size_type i, const Matrix_cx::size_type j) const
{
    if(i >= this->gsl_mat->size1 || j >= this->gsl_mat->size2){
        throw std::out_of_range("Element at (" + std::to_string(i) + ", " + std::to_string(j) + ") out of range.");
    }
    return *gsl_matrix_complex_ptr(this->gsl_mat.get(), i, j);
}

template<>
inline typename Matrix_cxf::reference Matrix_cxf::at(const Matrix_cxf::size_type i, const Matrix_cxf::size_type j)
{
    if(i >= this->gsl_mat->size1 || j >= this->gsl_mat->size2){
        throw std::out_of_range("Element at (" + std::to_string(i) + ", " + std::to_string(j) + ") out of range.");
    }
    return *gsl_matrix_complex_float_ptr(this->gsl_mat.get(), i, j);
}

template<>
inline typename Matrix_cxf::const_reference Matrix_cxf::at(const Matrix_cxf::size_type i, const Matrix_cxf::size_type j) const
{
    if(i >= this->gsl_mat->size1 || j >= this->gsl_mat->size2){
        throw std::out_of_range("Element at (" + std::to_string(i) + ", " + std::to_string(j) + ") out of range.");
    }
    return *gsl_matrix_complex_float_ptr(this->gsl_mat.get(), i, j);
}

template<>
inline typename Matrix_cxld::reference Matrix_cxld::at(const Matrix_cxld::size_type i, const Matrix_cxld::size_type j)
{
    if(i >= this->gsl_mat->size1 || j >= this->gsl_mat->size2){
        throw std::out_of_range("Element at (" + std::to_string(i) + ", " + std::to_string(j) + ") out of range.");
    }
    return *gsl_matrix_complex_long_double_ptr(this->gsl_mat.get(), i, j);
}

template<>
inline typename Matrix_cxld::const_reference Matrix_cxld::at(const Matrix_cxld::size_type i, const Matrix_cxld::size_type j) const
{
    if(i >= this->gsl_mat->size1 || j >= this->gsl_mat->size2){
        throw std::out_of_range("Element at (" + std::to_string(i) + ", " + std::to_string(j) + ") out of range.");
    }
    return *gsl_matrix_complex_long_double_ptr(this->gsl_mat.get(), i, j);
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
inline std::string Matrix_cx::to_string() const
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
inline std::string Matrix_cxld::to_string() const
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
inline std::string Matrix_cxf::to_string() const
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
            res += Complex_f(el).to_string();
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
