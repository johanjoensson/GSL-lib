#include "GSLpp/matrix.h"
#include "GSLpp/complex.h"
#include "GSLpp/vector.h"
#include <gsl/gsl_blas.h>
#include <gsl/gsl_complex_math.h>
#include <iostream>
#include <stdexcept>

namespace GSL{

template<>
Matrix::Matrix_t(const std::shared_ptr<GSL_Mat>& m)
 : gsl_mat(m)
{}

template<>
Matrix_ld::Matrix_t(const std::shared_ptr<GSL_Mat>& m)
 : gsl_mat(m)
{}

template<>
Matrix_f::Matrix_t(const std::shared_ptr<GSL_Mat>& m)
 : gsl_mat(m)
{}

template<>
Matrix_i::Matrix_t(const std::shared_ptr<GSL_Mat>& m)
 : gsl_mat(m)
{}

template<>
Matrix_ui::Matrix_t(const std::shared_ptr<GSL_Mat>& m)
 : gsl_mat(m)
{}

template<>
Matrix_l::Matrix_t(const std::shared_ptr<GSL_Mat>& m)
 : gsl_mat(m)
{}

template<>
Matrix_ul::Matrix_t(const std::shared_ptr<GSL_Mat>& m)
 : gsl_mat(m)
{}

template<>
Matrix_s::Matrix_t(const std::shared_ptr<GSL_Mat>& m)
 : gsl_mat(m)
{}

template<>
Matrix_us::Matrix_t(const std::shared_ptr<GSL_Mat>& m)
 : gsl_mat(m)
{}

template<>
Matrix_c::Matrix_t(const std::shared_ptr<GSL_Mat>& m)
 : gsl_mat(m)
{}

template<>
Matrix_uc::Matrix_t(const std::shared_ptr<GSL_Mat>& m)
 : gsl_mat(m)
{}

template<>
Matrix_cx::Matrix_t(const std::shared_ptr<GSL_Mat>& m)
 : gsl_mat(m)
{}

template<>
Matrix_cxld::Matrix_t(const std::shared_ptr<GSL_Mat>& m)
 : gsl_mat(m)
{}

template<>
Matrix_cxf::Matrix_t(const std::shared_ptr<GSL_Mat>& m)
 : gsl_mat(m)
{}

template<>
Matrix::Matrix_t(const Matrix_t::size_type n1, const Matrix_t::size_type n2)
: gsl_mat(gsl_matrix_calloc(n1, n2), gsl_matrix_free)
{
    if(gsl_mat == nullptr){
        throw std::runtime_error("Memory allocation (gsl_matrix_calloc)"
        " failed!");
    }
}

template<>
Matrix_ld::
Matrix_t(const Matrix_t::size_type n1, const Matrix_t::size_type n2)
: gsl_mat(gsl_matrix_long_double_calloc(n1, n2), gsl_matrix_long_double_free)
{

    if(gsl_mat == nullptr){
        throw std::runtime_error("Memory allocation (gsl_matrix_long_double_calloc)"
        " failed!");
    }
}

template<>
Matrix_f::
Matrix_t(const Matrix_t::size_type n1, const Matrix_t::size_type n2)
: gsl_mat(gsl_matrix_float_calloc(n1, n2), gsl_matrix_float_free)
{
    if(gsl_mat == nullptr){
        throw std::runtime_error("Memory allocation (gsl_matrix_float_calloc)"
        " failed!");
    }
}

template<>
Matrix_i::
Matrix_t(const Matrix_t::size_type n1, const Matrix_t::size_type n2)
: gsl_mat(gsl_matrix_int_calloc(n1, n2), gsl_matrix_int_free)
{
    if(gsl_mat == nullptr){
        throw std::runtime_error("Memory allocation (gsl_matrix_int_calloc)"
        " failed!");
    }
}

template<>
Matrix_ui::
Matrix_t(const Matrix_t::size_type n1, const Matrix_t::size_type n2)
: gsl_mat(gsl_matrix_uint_calloc(n1, n2), gsl_matrix_uint_free)
{
    if(gsl_mat == nullptr){
        throw std::runtime_error("Memory allocation (gsl_matrix_uint_calloc)"
        " failed!");
    }
}

template<>
Matrix_l::
Matrix_t(const Matrix_t::size_type n1, const Matrix_t::size_type n2)
: gsl_mat(gsl_matrix_long_calloc(n1, n2), gsl_matrix_long_free)
{
    if(gsl_mat == nullptr){
        throw std::runtime_error("Memory allocation (gsl_matrix_long_calloc)"
        " failed!");
    }
}

template<>
Matrix_ul::
Matrix_t(const Matrix_t::size_type n1, const Matrix_t::size_type n2)
: gsl_mat(gsl_matrix_ulong_calloc(n1, n2), gsl_matrix_ulong_free)
{
    if(gsl_mat == nullptr){
        throw std::runtime_error("Memory allocation (gsl_matrix_ulong_calloc)"
        " failed!");
    }
}

template<>
Matrix_s::
Matrix_t(const Matrix_t::size_type n1, const Matrix_t::size_type n2)
: gsl_mat(gsl_matrix_short_calloc(n1, n2), gsl_matrix_short_free)
{
    if(gsl_mat == nullptr){
        throw std::runtime_error("Memory allocation (gsl_matrix_short_calloc)"
        " failed!");
    }
}

template<>
Matrix_us::
Matrix_t(const Matrix_t::size_type n1, const Matrix_t::size_type n2)
: gsl_mat(gsl_matrix_ushort_calloc(n1, n2), gsl_matrix_ushort_free)
{
    if(gsl_mat == nullptr){
        throw std::runtime_error("Memory allocation (gsl_matrix_ushort_calloc)"
        " failed!");
    }
}

template<>
Matrix_c::
Matrix_t(const Matrix_t::size_type n1, const Matrix_t::size_type n2)
: gsl_mat(gsl_matrix_char_calloc(n1, n2), gsl_matrix_char_free)
{
    if(gsl_mat == nullptr){
        throw std::runtime_error("Memory allocation (gsl_matrix_char_calloc)"
        " failed!");
    }
}

template<>
Matrix_uc::
Matrix_t(const Matrix_t::size_type n1, const Matrix_t::size_type n2)
: gsl_mat(gsl_matrix_uchar_calloc(n1, n2), gsl_matrix_uchar_free)
{
    if(gsl_mat == nullptr){
        throw std::runtime_error("Memory allocation (gsl_matrix_uchar_calloc)"
        " failed!");
    }
}

template<>
Matrix_cx::
Matrix_t(const Matrix_t::size_type n1, const Matrix_t::size_type n2)
: gsl_mat(gsl_matrix_complex_calloc(n1, n2), gsl_matrix_complex_free)
{
    if(gsl_mat == nullptr){
        throw std::runtime_error("Memory allocation (gsl_matrix_complex_calloc)"
        " failed!");
    }
}

template<>
Matrix_cxld::
Matrix_t(const Matrix_t::size_type n1, const Matrix_t::size_type n2)
: gsl_mat(gsl_matrix_complex_long_double_calloc(n1, n2), gsl_matrix_complex_long_double_free)
{
    if(gsl_mat == nullptr){
        throw std::runtime_error("Memory allocation (gsl_matrix_long_double_calloc)"
        " failed!");
    }
}

template<>
Matrix_cxf::Matrix_t
(const Matrix_t::size_type n1, const Matrix_t::size_type n2)
: gsl_mat(gsl_matrix_complex_float_calloc(n1, n2), gsl_matrix_complex_float_free)
{
    if(gsl_mat == nullptr){
        throw std::runtime_error("Memory allocation (gsl_matrix_float_calloc)"
        " failed!");
    }
}

template<class D, class GSL_MATRIX, class GSL_VECTOR, class A>
Matrix_t<D, GSL_MATRIX, GSL_VECTOR, A>::
Matrix_t(std::initializer_list<V> l)
: Matrix_t(l.size(), l.begin()->size())
{
    auto row_it = l.begin();
    for(auto& row : *this){
	row = *row_it;
	row_it++;
    }
}

template<>
Matrix::Matrix_t(std::initializer_list<V> l)
: Matrix_t(l.size(), l.begin()->size())
{
     auto row_it = l.begin();
     for(size_t i = 0; i < l.size(); i++){
         gsl_matrix_set_row(this->gsl_mat.get(), i, row_it->gsl_vec.get());
         row_it++;
     }
}

template<>
Matrix_ld::Matrix_t(std::initializer_list<V> l)
: Matrix_t(l.size(), l.begin()->size())
{
     auto row_it = l.begin();
     for(size_t i = 0; i < l.size(); i++){
         gsl_matrix_long_double_set_row(this->gsl_mat.get(), i, row_it->gsl_vec.get());
         row_it++;
     }
}

template<>
Matrix_f::Matrix_t(std::initializer_list<V> l)
: Matrix_t(l.size(), l.begin()->size())
{
     auto row_it = l.begin();
     for(size_t i = 0; i < l.size(); i++){
         gsl_matrix_float_set_row(this->gsl_mat.get(), i, row_it->gsl_vec.get());
         row_it++;
     }
}

template<>
Matrix_i::Matrix_t(std::initializer_list<V> l)
: Matrix_t(l.size(), l.begin()->size())
{
     auto row_it = l.begin();
     for(size_t i = 0; i < l.size(); i++){
         gsl_matrix_int_set_row(this->gsl_mat.get(), i, row_it->gsl_vec.get());
         row_it++;
     }
}

template<>
Matrix_ui::Matrix_t(std::initializer_list<V> l)
: Matrix_t(l.size(), l.begin()->size())
{
     auto row_it = l.begin();
     for(size_t i = 0; i < l.size(); i++){
         gsl_matrix_uint_set_row(this->gsl_mat.get(), i, row_it->gsl_vec.get());
         row_it++;
     }
}

template<>
Matrix_l::Matrix_t(std::initializer_list<V> l)
: Matrix_t(l.size(), l.begin()->size())
{
     auto row_it = l.begin();
     for(size_t i = 0; i < l.size(); i++){
         gsl_matrix_long_set_row(this->gsl_mat.get(), i, row_it->gsl_vec.get());
         row_it++;
     }
}

template<>
Matrix_ul::Matrix_t(std::initializer_list<V> l)
: Matrix_t(l.size(), l.begin()->size())
{
     auto row_it = l.begin();
     for(size_t i = 0; i < l.size(); i++){
         gsl_matrix_ulong_set_row(this->gsl_mat.get(), i, row_it->gsl_vec.get());
         row_it++;
     }
}

template<>
Matrix_s::Matrix_t(std::initializer_list<V> l)
: Matrix_t(l.size(), l.begin()->size())
{
     auto row_it = l.begin();
     for(size_t i = 0; i < l.size(); i++){
         gsl_matrix_short_set_row(this->gsl_mat.get(), i, row_it->gsl_vec.get());
         row_it++;
     }
}

template<>
Matrix_us::Matrix_t(std::initializer_list<V> l)
: Matrix_t(l.size(), l.begin()->size())
{
     auto row_it = l.begin();
     for(size_t i = 0; i < l.size(); i++){
         gsl_matrix_ushort_set_row(this->gsl_mat.get(), i, row_it->gsl_vec.get());
         row_it++;
     }
}

template<>
Matrix_c::Matrix_t(std::initializer_list<V> l)
: Matrix_t(l.size(), l.begin()->size())
{
     auto row_it = l.begin();
     for(size_t i = 0; i < l.size(); i++){
         gsl_matrix_char_set_row(this->gsl_mat.get(), i, row_it->gsl_vec.get());
         row_it++;
     }
}

template<>
Matrix_uc::Matrix_t(std::initializer_list<V> l)
: Matrix_t(l.size(), l.begin()->size())
{
     auto row_it = l.begin();
     for(size_t i = 0; i < l.size(); i++){
         gsl_matrix_uchar_set_row(this->gsl_mat.get(), i, row_it->gsl_vec.get());
         row_it++;
     }
}

template<>
Matrix_cx::Matrix_t(std::initializer_list<V> l)
: Matrix_t(l.size(), l.begin()->size())
{
     auto row_it = l.begin();
     for(size_t i = 0; i < l.size(); i++){
         gsl_matrix_complex_set_row(this->gsl_mat.get(), i, row_it->gsl_vec.get());
         row_it++;
     }
}

template<>
Matrix_cxld::Matrix_t(std::initializer_list<V> l)
: Matrix_t(l.size(), l.begin()->size())
{
     auto row_it = l.begin();
     for(size_t i = 0; i < l.size(); i++){
         gsl_matrix_complex_long_double_set_row(this->gsl_mat.get(), i, row_it->gsl_vec.get());
         row_it++;
     }
}

template<>
Matrix_cxf::Matrix_t(std::initializer_list<V> l)
: Matrix_t(l.size(), l.begin()->size())
{
     auto row_it = l.begin();
     for(size_t i = 0; i < l.size(); i++){
         gsl_matrix_complex_float_set_row(this->gsl_mat.get(), i, row_it->gsl_vec.get());
         row_it++;
     }
}

template<>
Matrix& Matrix::copy(const Matrix& a)
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
    return *this;
}

template<>
Matrix_ld& Matrix_ld::copy
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
    return *this;
}

template<>
Matrix_f& Matrix_f::copy
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
    return *this;
}

template<>
Matrix_i& Matrix_i::copy
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
    return *this;
}

template<>
Matrix_ui& Matrix_ui::copy
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
    return *this;
}

template<>
Matrix_l& Matrix_l::copy
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
    return *this;
}

template<>
Matrix_ul& Matrix_ul::copy
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
    return *this;
}

template<>
Matrix_s& Matrix_s::copy
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
    return *this;
}

template<>
Matrix_us& Matrix_us::copy
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
    return *this;
}

template<>
Matrix_c& Matrix_c::copy
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
    return *this;
}

template<>
Matrix_uc& Matrix_uc::copy
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
    return *this;
}

template<>
Matrix_cx& Matrix_cx::copy
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
    return *this;
}

template<>
Matrix_cxld& Matrix_cxld::copy
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
    return *this;
}

template<>
Matrix_cxf& Matrix_cxf::copy
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
    return *this;
}

template<>
Matrix& Matrix::operator+=(const Matrix& b)
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
Matrix_ld& Matrix_ld::operator+=(const Matrix_ld& b)
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
Matrix_f& Matrix_f::operator+=(const Matrix_f& b)
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
Matrix_i& Matrix_i::operator+=(const Matrix_i& b)
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
Matrix_ui& Matrix_ui::operator+=(const Matrix_ui& b)
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
Matrix_l& Matrix_l::operator+=(const Matrix_l& b)
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
Matrix_ul& Matrix_ul::operator+=(const Matrix_ul& b)
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
Matrix_s& Matrix_s::operator+=(const Matrix_s& b)
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
Matrix_us& Matrix_us::operator+=(const Matrix_us& b)
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
Matrix_c& Matrix_c::operator+=(const Matrix_c& b)
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
Matrix_uc& Matrix_uc::operator+=(const Matrix_uc& b)
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
Matrix_cx& Matrix_cx::operator+=(const Matrix_cx& b)
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
Matrix_cxld& Matrix_cxld::operator+=(const Matrix_cxld& b)
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
Matrix_cxf& Matrix_cxf::operator+=(const Matrix_cxf& b)
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
Matrix& Matrix::operator-=(const Matrix& b)
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
Matrix_ld& Matrix_ld::operator-=(const Matrix_ld& b)
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
Matrix_f& Matrix_f::operator-=(const Matrix_f& b)
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
Matrix_i& Matrix_i::operator-=(const Matrix_i& b)
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
Matrix_ui& Matrix_ui::operator-=(const Matrix_ui& b)
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
Matrix_l& Matrix_l::operator-=(const Matrix_l& b)
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
Matrix_ul& Matrix_ul::operator-=(const Matrix_ul& b)
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
Matrix_s& Matrix_s::operator-=(const Matrix_s& b)
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
Matrix_us& Matrix_us::operator-=(const Matrix_us& b)
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
Matrix_c& Matrix_c::operator-=(const Matrix_c& b)
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
Matrix_uc& Matrix_uc::operator-=(const Matrix_uc& b)
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
Matrix_cx& Matrix_cx::operator-=(const Matrix_cx& b)
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
Matrix_cxld& Matrix_cxld::operator-=(const Matrix_cxld& b)
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
Matrix_cxf& Matrix_cxf::operator-=(const Matrix_cxf& b)
{
    int stat = gsl_matrix_complex_float_sub(this->gsl_mat.get(), b.gsl_mat.get());
    if(stat){
		std::string error_str =   gsl_strerror(stat);
		throw std::runtime_error("Error in matrix addition.\nGSL error: "
        + error_str);
	}
    return *this;
}

template<class D, class M, class V, class A>
Matrix_t<D, M, V, A>& Matrix_t<D, M, V, A>::operator*=(const Matrix_t& b)
{
    Matrix_t tmp(this->size().first, b.size().second);
    for(Matrix_t::size_type i = 0; i < this->size().first; i++){
        for(Matrix_t::size_type j = 0; j < b.size().second; j++){
            for(Matrix_t::size_type k = 0; k < this->size().second; k++){
                tmp(i, j) = static_cast<typename A::value_type> (tmp(i, j) +
                (*this)(i, k) * static_cast<value_type>(b(k, j)));
            }
        }
    }
    *this = tmp;
    return *this;
}

template<>
Matrix& Matrix::operator*=(const Matrix& b)
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
Matrix_f& Matrix_f::operator*=(const Matrix_f& b)
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
Matrix_cx& Matrix_cx::operator*=(const Matrix_cx& b)
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
Matrix_cxf& Matrix_cxf::operator*=(const Matrix_cxf& b)
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

/*
template<>
Matrix_cxld& Matrix_cxld::operator*=(const Matrix_cxld& b)
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
                c1 = (*this)[i][k];
                c2 = b[k][j];
                tmp[i][j] = tmp[i][j] + c1*c2;
            }
        }
    }
    *this = tmp;
    return *this;
}
*/
template<>
Matrix& Matrix::operator/=(const Matrix& b)
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
Matrix_ld& Matrix_ld::operator/=(const Matrix_ld& b)
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
Matrix_f& Matrix_f::operator/=(const Matrix_f& b)
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
Matrix_i& Matrix_i::operator/=(const Matrix_i& b)
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
Matrix_ui& Matrix_ui::operator/=(const Matrix_ui& b)
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
Matrix_l& Matrix_l::operator/=(const Matrix_l& b)
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
Matrix_ul& Matrix_ul::operator/=(const Matrix_ul& b)
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
Matrix_s& Matrix_s::operator/=(const Matrix_s& b)
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
Matrix_us& Matrix_us::operator/=(const Matrix_us& b)
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
Matrix_c& Matrix_c::operator/=(const Matrix_c& b)
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
Matrix_uc& Matrix_uc::operator/=(const Matrix_uc& b)
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
Matrix_cx& Matrix_cx::operator/=(const Matrix_cx& b)
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
Matrix_cxld& Matrix_cxld::operator/=(const Matrix_cxld& b)
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
Matrix_cxf& Matrix_cxf::operator/=(const Matrix_cxf& b)
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
Matrix& Matrix::operator*=(const double& b)
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
Matrix_ld& Matrix_ld::operator*=(const long double& b)
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
Matrix_f& Matrix_f::operator*=(const float& b)
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
Matrix_i& Matrix_i::operator*=(const int& b)
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
Matrix_ui& Matrix_ui::operator*=(const unsigned int& b)
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
Matrix_l& Matrix_l::operator*=(const long& b)
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
Matrix_ul& Matrix_ul::operator*=(const unsigned long& b)
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
Matrix_s& Matrix_s::operator*=(const short& b)
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
Matrix_us& Matrix_us::operator*=(const unsigned short& b)
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
Matrix_c& Matrix_c::operator*=(const char& b)
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
Matrix_uc& Matrix_uc::operator*=(const unsigned char& b)
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
Matrix_cx& Matrix_cx::operator*=(const Complex& b)
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
Matrix_cxld& Matrix_cxld::operator*=(const Complex_ld& b)
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
Matrix_cxf& Matrix_cxf::operator*=(const Complex_f& b)
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
Matrix& Matrix::operator/=(const double& b)
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
Matrix_ld& Matrix_ld::operator/=(const long double& b)
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
Matrix_f& Matrix_f::operator/=(const float& b)
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
Matrix_i& Matrix_i::operator/=(const int& b)
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
Matrix_ui& Matrix_ui::operator/=(const unsigned int& b)
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
Matrix_l& Matrix_l::operator/=(const long& b)
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
Matrix_ul& Matrix_ul::operator/=(const unsigned long& b)
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
Matrix_s& Matrix_s::operator/=(const short& b)
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
Matrix_us& Matrix_us::operator/=(const unsigned short& b)
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
Matrix_c& Matrix_c::operator/=(const char& b)
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
Matrix_uc& Matrix_uc::operator/=(const unsigned char& b)
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
Matrix_cx& Matrix_cx::operator/=(const Complex& b)
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
Matrix_cxld& Matrix_cxld::operator/=(const Complex_ld& b)
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
Matrix_cxf& Matrix_cxf::operator/=(const Complex_f& b)
{
    int stat = gsl_matrix_complex_float_scale(this->gsl_mat.get(), *(1./b).gsl_c);
    if(stat){
		std::string error_str =   gsl_strerror(stat);
		throw std::runtime_error("Error in matrix addition.\nGSL error: "
        + error_str);
	}
    return *this;
}

template<>
Matrix::V Matrix::operator*(const V& v)
{
    V res(this->size().second);
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
Matrix_f::V Matrix_f::operator*(const V& v)
{
    V res(this->size().second);
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
Matrix_cx::V Matrix_cx::operator*(const V& v)
{
    V res(this->size().second);
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
Matrix_cxf::V Matrix_cxf::operator*(const V& v)
{
    V res(this->size().second);
    int stat = gsl_blas_cgemv(CblasNoTrans, Complex_f(1.0), this->gsl_mat.get(),
        v.gsl_vec.get(), Complex_f(0.0), res.gsl_vec.get());
    if(stat){
		std::string error_str =   gsl_strerror(stat);
		throw std::runtime_error("Error in matrix-vector multiplication.\nGSL error: "
        + error_str);
	}

    return res;
}

template<>
bool Matrix::operator==(const Matrix& b) const
{
    if(this->gsl_mat.get() == nullptr && b.gsl_mat.get() == nullptr){
        return true;
    }else if(this->gsl_mat.get() == nullptr || b.gsl_mat.get() == nullptr){
        return false;
    }
    return gsl_matrix_equal(this->gsl_mat.get(), b.gsl_mat.get());
}

template<>
bool Matrix_ld::operator==(const Matrix_ld& b) const
{
    if(this->gsl_mat.get() == nullptr && b.gsl_mat.get() == nullptr){
        return true;
    }else if(this->gsl_mat.get() == nullptr || b.gsl_mat.get() == nullptr){
        return false;
    }
    return gsl_matrix_long_double_equal(this->gsl_mat.get(), b.gsl_mat.get());
}

template<>
bool Matrix_f::operator==(const Matrix_f& b) const
{
    if(this->gsl_mat.get() == nullptr && b.gsl_mat.get() == nullptr){
        return true;
    }else if(this->gsl_mat.get() == nullptr || b.gsl_mat.get() == nullptr){
        return false;
    }
    return gsl_matrix_float_equal(this->gsl_mat.get(), b.gsl_mat.get());
}

template<>
bool Matrix_i::operator==(const Matrix_i& b) const
{
    if(this->gsl_mat.get() == nullptr && b.gsl_mat.get() == nullptr){
        return true;
    }else if(this->gsl_mat.get() == nullptr || b.gsl_mat.get() == nullptr){
        return false;
    }
    return gsl_matrix_int_equal(this->gsl_mat.get(), b.gsl_mat.get());
}

template<>
bool Matrix_ui::operator==(const Matrix_ui& b) const
{
    if(this->gsl_mat.get() == nullptr && b.gsl_mat.get() == nullptr){
        return true;
    }else if(this->gsl_mat.get() == nullptr || b.gsl_mat.get() == nullptr){
        return false;
    }
    return gsl_matrix_uint_equal(this->gsl_mat.get(), b.gsl_mat.get());
}

template<>
bool Matrix_l::operator==(const Matrix_l& b) const
{
    if(this->gsl_mat.get() == nullptr && b.gsl_mat.get() == nullptr){
        return true;
    }else if(this->gsl_mat.get() == nullptr || b.gsl_mat.get() == nullptr){
        return false;
    }
    return gsl_matrix_long_equal(this->gsl_mat.get(), b.gsl_mat.get());
}

template<>
bool Matrix_ul::operator==(const Matrix_ul& b) const
{
    if(this->gsl_mat.get() == nullptr && b.gsl_mat.get() == nullptr){
        return true;
    }else if(this->gsl_mat.get() == nullptr || b.gsl_mat.get() == nullptr){
        return false;
    }
    return gsl_matrix_ulong_equal(this->gsl_mat.get(), b.gsl_mat.get());
}

template<>
bool Matrix_s::operator==(const Matrix_s& b) const
{
    if(this->gsl_mat.get() == nullptr && b.gsl_mat.get() == nullptr){
        return true;
    }else if(this->gsl_mat.get() == nullptr || b.gsl_mat.get() == nullptr){
        return false;
    }
    return gsl_matrix_short_equal(this->gsl_mat.get(), b.gsl_mat.get());
}

template<>
bool Matrix_us::operator==(const Matrix_us& b) const
{
    if(this->gsl_mat.get() == nullptr && b.gsl_mat.get() == nullptr){
        return true;
    }else if(this->gsl_mat.get() == nullptr || b.gsl_mat.get() == nullptr){
        return false;
    }
    return gsl_matrix_ushort_equal(this->gsl_mat.get(), b.gsl_mat.get());
}

template<>
bool Matrix_c::operator==(const Matrix_c& b) const
{
    if(this->gsl_mat.get() == nullptr && b.gsl_mat.get() == nullptr){
        return true;
    }else if(this->gsl_mat.get() == nullptr || b.gsl_mat.get() == nullptr){
        return false;
    }
    return gsl_matrix_char_equal(this->gsl_mat.get(), b.gsl_mat.get());
}

template<>
bool Matrix_uc::operator==(const Matrix_uc& b) const
{
    if(this->gsl_mat.get() == nullptr && b.gsl_mat.get() == nullptr){
        return true;
    }else if(this->gsl_mat.get() == nullptr || b.gsl_mat.get() == nullptr){
        return false;
    }
    return gsl_matrix_uchar_equal(this->gsl_mat.get(), b.gsl_mat.get());
}

template<>
bool Matrix_cx::operator==(const Matrix_cx& b) const
{
    if(this->gsl_mat.get() == nullptr && b.gsl_mat.get() == nullptr){
        return true;
    }else if(this->gsl_mat.get() == nullptr || b.gsl_mat.get() == nullptr){
        return false;
    }
    return gsl_matrix_complex_equal(this->gsl_mat.get(), b.gsl_mat.get());
}

template<>
bool Matrix_cxld::operator==(const Matrix_cxld& b) const
{
    if(this->gsl_mat.get() == nullptr && b.gsl_mat.get() == nullptr){
        return true;
    }else if(this->gsl_mat.get() == nullptr || b.gsl_mat.get() == nullptr){
        return false;
    }
    return gsl_matrix_complex_long_double_equal(this->gsl_mat.get(), b.gsl_mat.get());
}

template<>
bool Matrix_cxf::operator==(const Matrix_cxf& b) const
{
    if(this->gsl_mat.get() == nullptr && b.gsl_mat.get() == nullptr){
        return true;
    }else if(this->gsl_mat.get() == nullptr || b.gsl_mat.get() == nullptr){
        return false;
    }
    return gsl_matrix_complex_float_equal(this->gsl_mat.get(), b.gsl_mat.get());
}

template<class D, class M, class V, class A>
Matrix_t<D, M, V, A> Matrix_t<D, M, V, A>::transpose() const
{
    Matrix_t res(this->size().second, this->size().first);
    for(Matrix_t::size_type i = 0; i < this->size().second; i++){
        for(Matrix_t::size_type j = 0; j < this->size().first; j++){
            res[i][j] = (*this)[j][i];
        }
    }
    return res;
}

template<>
Matrix Matrix::transpose() const
{
    Matrix res(this->size().second, this->size().first);
    gsl_matrix_transpose_memcpy(res.gsl_mat.get(), this->gsl_mat.get());
    return res;
}

template<>
Matrix_ld Matrix_ld::transpose() const
{
    Matrix_ld res(this->size().second, this->size().first);
    gsl_matrix_long_double_transpose_memcpy(res.gsl_mat.get(), this->gsl_mat.get());
    return res;
}

template<>
Matrix_f Matrix_f::transpose() const
{
    Matrix_f res(this->size().second, this->size().first);
    gsl_matrix_float_transpose_memcpy(res.gsl_mat.get(), this->gsl_mat.get());
    return res;
}

template<>
Matrix_i Matrix_i::transpose() const
{
    Matrix_i res(this->size().second, this->size().first);
    gsl_matrix_int_transpose_memcpy(res.gsl_mat.get(), this->gsl_mat.get());
    return res;
}

template<>
Matrix_ui Matrix_ui::transpose() const
{
    Matrix_ui res(this->size().second, this->size().first);
    gsl_matrix_uint_transpose_memcpy(res.gsl_mat.get(), this->gsl_mat.get());
    return res;
}

template<>
Matrix_l Matrix_l::transpose() const
{
    Matrix_l res(this->size().second, this->size().first);
    gsl_matrix_long_transpose_memcpy(res.gsl_mat.get(), this->gsl_mat.get());
    return res;
}

template<>
Matrix_ul Matrix_ul::transpose() const
{
    Matrix_ul res(this->size().second, this->size().first);
    gsl_matrix_ulong_transpose_memcpy(res.gsl_mat.get(), this->gsl_mat.get());
    return res;
}

template<>
Matrix_s Matrix_s::transpose() const
{
    Matrix_s res(this->size().second, this->size().first);
    gsl_matrix_short_transpose_memcpy(res.gsl_mat.get(), this->gsl_mat.get());
    return res;
}

template<>
Matrix_us Matrix_us::transpose() const
{
    Matrix_us res(this->size().second, this->size().first);
    gsl_matrix_ushort_transpose_memcpy(res.gsl_mat.get(), this->gsl_mat.get());
    return res;
}

template<>
Matrix_c Matrix_c::transpose() const
{
    Matrix_c res(this->size().second, this->size().first);
    gsl_matrix_char_transpose_memcpy(res.gsl_mat.get(), this->gsl_mat.get());
    return res;
}

template<>
Matrix_uc Matrix_uc::transpose() const
{
    Matrix_uc res(this->size().second, this->size().first);
    gsl_matrix_uchar_transpose_memcpy(res.gsl_mat.get(), this->gsl_mat.get());
    return res;
}

template<>
Matrix_cx Matrix_cx::transpose() const
{
    Matrix_cx res(this->size().second, this->size().first);
    gsl_matrix_complex_transpose_memcpy(res.gsl_mat.get(), this->gsl_mat.get());
    return res;
}

template<>
Matrix_cxld Matrix_cxld::transpose() const
{
    Matrix_cxld res(this->size().second, this->size().first);
    gsl_matrix_complex_long_double_transpose_memcpy(res.gsl_mat.get(), this->gsl_mat.get());
    return res;
}

template<>
Matrix_cxf Matrix_cxf::transpose() const
{
    Matrix_cxf res(this->size().second, this->size().first);
    gsl_matrix_complex_float_transpose_memcpy(res.gsl_mat.get(), this->gsl_mat.get());
    return res;
}

template<class D, class M, class V, class A>
Matrix_t<D, M, V, A> Matrix_t<D, M, V, A>::hermitian_transpose() const
{
    return this->transpose();
}

template<>
Matrix_cx Matrix_cx::hermitian_transpose() const
{
    Matrix_cx res = this->transpose();
    for(Matrix_cx::size_type
            i = 0; i < this->size().second; i++){
        for(Matrix_cx::size_type
                j = 0; j < this->size().first; j++){
                    res[i][j] = gsl_complex_conjugate(res[i][j]);
        }
    }
    return res;
}

template<>
Matrix_cxld
Matrix_cxld::
hermitian_transpose() const
{
    Matrix_cxld res = this->transpose();
    for(Matrix_cxld::size_type
            i = 0; i < this->size().second; i++){
        for(Matrix_cxld::size_type
                j = 0; j < this->size().first; j++){
                    res[i][j] = GSL::Complex_ld(res[i][j]).conjugate();
        }
    }
    return res;
}

template<>
Matrix_cxf
Matrix_cxf::
hermitian_transpose() const
{
    Matrix_cxf res = this->transpose();
    for(Matrix_cxf::size_type
            i = 0; i < this->size().second; i++){
        for(Matrix_cxf::size_type
                j = 0; j < this->size().first; j++){
                    res[i][j] = GSL::Complex_f(res[i][j]).conjugate();
        }
    }
    return res;
}

template<>
Matrix Matrix::inverse() const
{
    return GSL::lu_inverse(*this);
}

template<>
Matrix_cx Matrix_cx::inverse() const
{
    return GSL::lu_inverse(*this);
}

template<>
double Matrix::det() const
{
   return GSL::lu_det(*this);
}

template<>
GSL::Complex Matrix_cx::det() const
{
   return GSL::lu_det(*this);
}

template<>
Matrix::Row Matrix::get_row(const Matrix::size_type i)
{
    return std::make_shared<GSL_Vec>(gsl_matrix_row(this->gsl_mat.get(), i).vector);
}


template<>
Matrix_ld::Row Matrix_ld::get_row(const Matrix_ld::size_type i)
{
    return std::make_shared<GSL_Vec>(gsl_matrix_long_double_row(this->gsl_mat.get(), i).vector);
}

template<>
Matrix_f::Row Matrix_f::get_row(const Matrix_f::size_type i)
{
    return std::make_shared<GSL_Vec>(gsl_matrix_float_row(this->gsl_mat.get(), i).vector);
}

template<>
Matrix_i::Row Matrix_i::get_row(const Matrix_i::size_type i)
{
    return std::make_shared<GSL_Vec>(gsl_matrix_int_row(this->gsl_mat.get(), i).vector);
}

template<>
Matrix_ui::Row Matrix_ui::get_row(const Matrix_ui::size_type i)
{
    return std::make_shared<GSL_Vec>(gsl_matrix_uint_row(this->gsl_mat.get(), i).vector);
}

template<>
Matrix_l::Row Matrix_l::get_row(const Matrix_l::size_type i)
{
    return std::make_shared<GSL_Vec>(gsl_matrix_long_row(this->gsl_mat.get(), i).vector);
}

template<>
Matrix_ul::Row Matrix_ul::get_row(const Matrix_ul::size_type i)
{
    return std::make_shared<GSL_Vec>(gsl_matrix_ulong_row(this->gsl_mat.get(), i).vector);
}

template<>
Matrix_s::Row Matrix_s::get_row(const Matrix_s::size_type i)
{
    return std::make_shared<GSL_Vec>(gsl_matrix_short_row(this->gsl_mat.get(), i).vector);
}

template<>
Matrix_us::Row Matrix_us::get_row(const Matrix_us::size_type i)
{
    return std::make_shared<GSL_Vec>(gsl_matrix_ushort_row(this->gsl_mat.get(), i).vector);
}

template<>
Matrix_c::Row Matrix_c::get_row(const Matrix_c::size_type i)
{
    return std::make_shared<GSL_Vec>(gsl_matrix_char_row(this->gsl_mat.get(), i).vector);
}

template<>
Matrix_uc::Row Matrix_uc::get_row(const Matrix_uc::size_type i)
{
    return std::make_shared<GSL_Vec>(gsl_matrix_uchar_row(this->gsl_mat.get(), i).vector);
}

template<>
Matrix_cx::Row Matrix_cx::get_row(const Matrix_cx::size_type i)
{
    return std::make_shared<GSL_Vec>(gsl_matrix_complex_row(this->gsl_mat.get(), i).vector);
}

template<>
Matrix_cxld::Row Matrix_cxld::get_row(const Matrix_cxld::size_type i)
{
    return std::make_shared<GSL_Vec>(gsl_matrix_complex_long_double_row(this->gsl_mat.get(), i).vector);
}

template<>
Matrix_cxf::Row Matrix_cxf::get_row(const Matrix_cxf::size_type i)
{
    return std::make_shared<GSL_Vec>(gsl_matrix_complex_float_row(this->gsl_mat.get(), i).vector);
}

template<>
const Matrix::Row Matrix::get_row(const Matrix::size_type i) const
{
    return std::make_shared<GSL_Vec>(gsl_matrix_const_row(this->gsl_mat.get(), i).vector);
}


template<>
const Matrix_ld::Row Matrix_ld::get_row(const Matrix_ld::size_type i) const
{
    return std::make_shared<GSL_Vec>(gsl_matrix_long_double_const_row(this->gsl_mat.get(), i).vector);
}

template<>
const Matrix_f::Row Matrix_f::get_row(const Matrix_f::size_type i) const
{
    return std::make_shared<GSL_Vec>(gsl_matrix_float_const_row(this->gsl_mat.get(), i).vector);
}

template<>
const Matrix_i::Row Matrix_i::get_row(const Matrix_i::size_type i) const
{
    return std::make_shared<GSL_Vec>(gsl_matrix_int_const_row(this->gsl_mat.get(), i).vector);
}

template<>
const Matrix_ui::Row Matrix_ui::get_row(const Matrix_ui::size_type i) const
{
    return std::make_shared<GSL_Vec>(gsl_matrix_uint_const_row(this->gsl_mat.get(), i).vector);
}

template<>
const Matrix_l::Row Matrix_l::get_row(const Matrix_l::size_type i) const
{
    return std::make_shared<GSL_Vec>(gsl_matrix_long_const_row(this->gsl_mat.get(), i).vector);
}

template<>
const Matrix_ul::Row Matrix_ul::get_row(const Matrix_ul::size_type i) const
{
    return std::make_shared<GSL_Vec>(gsl_matrix_ulong_const_row(this->gsl_mat.get(), i).vector);
}

template<>
const Matrix_s::Row Matrix_s::get_row(const Matrix_s::size_type i) const
{
    return std::make_shared<GSL_Vec>(gsl_matrix_short_const_row(this->gsl_mat.get(), i).vector);
}

template<>
const Matrix_us::Row Matrix_us::get_row(const Matrix_us::size_type i) const
{
    return std::make_shared<GSL_Vec>(gsl_matrix_ushort_const_row(this->gsl_mat.get(), i).vector);
}

template<>
const Matrix_c::Row Matrix_c::get_row(const Matrix_c::size_type i) const
{
    return std::make_shared<GSL_Vec>(gsl_matrix_char_const_row(this->gsl_mat.get(), i).vector);
}

template<>
const Matrix_uc::Row Matrix_uc::get_row(const Matrix_uc::size_type i) const
{
    return std::make_shared<GSL_Vec>(gsl_matrix_uchar_const_row(this->gsl_mat.get(), i).vector);
}

template<>
const Matrix_cx::Row Matrix_cx::get_row(const Matrix_cx::size_type i) const
{
    return std::make_shared<GSL_Vec>(gsl_matrix_complex_const_row(this->gsl_mat.get(), i).vector);
}

template<>
const Matrix_cxld::Row Matrix_cxld::get_row(const Matrix_cxld::size_type i) const
{
    return std::make_shared<GSL_Vec>(gsl_matrix_complex_long_double_const_row(this->gsl_mat.get(), i).vector);
}

template<>
const Matrix_cxf::Row Matrix_cxf::get_row(const Matrix_cxf::size_type i) const
{
    return std::make_shared<GSL_Vec>(gsl_matrix_complex_float_const_row(this->gsl_mat.get(), i).vector);
}

template<>
Matrix::Column Matrix::get_col(const Matrix::size_type i)
{
    return std::make_shared<GSL_Vec>(gsl_matrix_column(this->gsl_mat.get(), i).vector);
}

template<>
Matrix_ld::Column Matrix_ld::get_col(const Matrix_ld::size_type i)
{
    return std::make_shared<GSL_Vec>(gsl_matrix_long_double_column(this->gsl_mat.get(), i).vector);
}

template<>
Matrix_f::Column Matrix_f::get_col(const Matrix_f::size_type i)
{
    return std::make_shared<GSL_Vec>(gsl_matrix_float_column(this->gsl_mat.get(), i).vector);
}

template<>
Matrix_i::Column Matrix_i::get_col(const Matrix_i::size_type i)
{
    return std::make_shared<GSL_Vec>(gsl_matrix_int_column(this->gsl_mat.get(), i).vector);
}

template<>
Matrix_ui::Column Matrix_ui::get_col(const Matrix_ui::size_type i)
{
    return std::make_shared<GSL_Vec>(gsl_matrix_uint_column(this->gsl_mat.get(), i).vector);
}

template<>
Matrix_l::Column Matrix_l::get_col(const Matrix_l::size_type i)
{
    return std::make_shared<GSL_Vec>(gsl_matrix_long_column(this->gsl_mat.get(), i).vector);
}

template<>
Matrix_ul::Column Matrix_ul::get_col(const Matrix_ul::size_type i)
{
    return std::make_shared<GSL_Vec>(gsl_matrix_ulong_column(this->gsl_mat.get(), i).vector);
}

template<>
Matrix_s::Column Matrix_s::get_col(const Matrix_s::size_type i)
{
    return std::make_shared<GSL_Vec>(gsl_matrix_short_column(this->gsl_mat.get(), i).vector);
}

template<>
Matrix_us::Column Matrix_us::get_col(const Matrix_us::size_type i)
{
    return std::make_shared<GSL_Vec>(gsl_matrix_ushort_column(this->gsl_mat.get(), i).vector);
}

template<>
Matrix_c::Column Matrix_c::get_col(const Matrix_c::size_type i)
{
    return std::make_shared<GSL_Vec>(gsl_matrix_char_column(this->gsl_mat.get(), i).vector);
}

template<>
Matrix_uc::Column Matrix_uc::get_col(const Matrix_uc::size_type i)
{
    return std::make_shared<GSL_Vec>(gsl_matrix_uchar_column(this->gsl_mat.get(), i).vector);
}

template<>
Matrix_cx::Column Matrix_cx::get_col(const Matrix_cx::size_type i)
{
    return std::make_shared<GSL_Vec>(gsl_matrix_complex_column(this->gsl_mat.get(), i).vector);
}

template<>
Matrix_cxld::Column Matrix_cxld::get_col(const Matrix_cxld::size_type i)
{
    return std::make_shared<GSL_Vec>(gsl_matrix_complex_long_double_column(this->gsl_mat.get(), i).vector);
}

template<>
Matrix_cxf::Column Matrix_cxf::get_col(const Matrix_t::size_type i)
{
    return std::make_shared<GSL_Vec>(gsl_matrix_complex_float_column(this->gsl_mat.get(), i).vector);
}

template<>
const Matrix::Column Matrix::get_col(const Matrix::size_type i) const
{
    return std::make_shared<GSL_Vec>(gsl_matrix_const_column(this->gsl_mat.get(), i).vector);
}

template<>
const Matrix_ld::Column Matrix_ld::get_col(const Matrix_ld::size_type i) const
{
    return std::make_shared<GSL_Vec>(gsl_matrix_long_double_const_column(this->gsl_mat.get(), i).vector);
}

template<>
const Matrix_f::Column Matrix_f::get_col(const Matrix_f::size_type i) const
{
    return std::make_shared<GSL_Vec>(gsl_matrix_float_const_column(this->gsl_mat.get(), i).vector);
}

template<>
const Matrix_i::Column Matrix_i::get_col(const Matrix_i::size_type i) const
{
    return std::make_shared<GSL_Vec>(gsl_matrix_int_const_column(this->gsl_mat.get(), i).vector);
}

template<>
const Matrix_ui::Column Matrix_ui::get_col(const Matrix_ui::size_type i) const
{
    return std::make_shared<GSL_Vec>(gsl_matrix_uint_const_column(this->gsl_mat.get(), i).vector);
}

template<>
const Matrix_l::Column Matrix_l::get_col(const Matrix_l::size_type i) const
{
    return std::make_shared<GSL_Vec>(gsl_matrix_long_const_column(this->gsl_mat.get(), i).vector);
}

template<>
const Matrix_ul::Column Matrix_ul::get_col(const Matrix_ul::size_type i) const
{
    return std::make_shared<GSL_Vec>(gsl_matrix_ulong_const_column(this->gsl_mat.get(), i).vector);
}

template<>
const Matrix_s::Column Matrix_s::get_col(const Matrix_s::size_type i) const
{
    return std::make_shared<GSL_Vec>(gsl_matrix_short_const_column(this->gsl_mat.get(), i).vector);
}

template<>
const Matrix_us::Column Matrix_us::get_col(const Matrix_us::size_type i) const
{
    return std::make_shared<GSL_Vec>(gsl_matrix_ushort_const_column(this->gsl_mat.get(), i).vector);
}

template<>
const Matrix_c::Column Matrix_c::get_col(const Matrix_c::size_type i) const
{
    return std::make_shared<GSL_Vec>(gsl_matrix_char_const_column(this->gsl_mat.get(), i).vector);
}

template<>
const Matrix_uc::Column Matrix_uc::get_col(const Matrix_uc::size_type i) const
{
    return std::make_shared<GSL_Vec>(gsl_matrix_uchar_const_column(this->gsl_mat.get(), i).vector);
}

template<>
const Matrix_cx::Column Matrix_cx::get_col(const Matrix_cx::size_type i) const
{
    return std::make_shared<GSL_Vec>(gsl_matrix_complex_const_column(this->gsl_mat.get(), i).vector);
}

template<>
const Matrix_cxld::Column Matrix_cxld::get_col(const Matrix_cxld::size_type i) const
{
    return std::make_shared<GSL_Vec>(gsl_matrix_complex_long_double_const_column(this->gsl_mat.get(), i).vector);
}

template<>
const Matrix_cxf::Column Matrix_cxf::get_col(const Matrix_t::size_type i) const
{
    return std::make_shared<GSL_Vec>(gsl_matrix_complex_float_const_column(this->gsl_mat.get(), i).vector);
}

template<>
typename Matrix::reference Matrix::
    operator() (const typename Matrix_t::size_type row, const typename Matrix_t::size_type column)
{
	return *gsl_matrix_ptr(this->gsl_mat.get(), row, column);
}

template<>
typename Matrix_ld::reference Matrix_ld::
    operator() (const typename Matrix_t::size_type row, const typename Matrix_t::size_type column)
{
	return *gsl_matrix_long_double_ptr(this->gsl_mat.get(), row, column);
}

template<>
typename Matrix_f::reference Matrix_f::
    operator() (const typename Matrix_t::size_type row, const typename Matrix_t::size_type column)
{
	return *gsl_matrix_float_ptr(this->gsl_mat.get(), row, column);
}

template<>
typename Matrix_i::reference Matrix_i::
    operator() (const typename Matrix_t::size_type row, const typename Matrix_t::size_type column)
{
	return *gsl_matrix_int_ptr(this->gsl_mat.get(), row, column);
}

template<>
typename Matrix_ui::reference Matrix_ui::
    operator() (const typename Matrix_t::size_type row, const typename Matrix_t::size_type column)
{
	return *gsl_matrix_uint_ptr(this->gsl_mat.get(), row, column);
}

template<>
typename Matrix_l::reference Matrix_l::
    operator() (const typename Matrix_t::size_type row, const typename Matrix_t::size_type column)
{
	return *gsl_matrix_long_ptr(this->gsl_mat.get(), row, column);
}

template<>
typename Matrix_ul::reference Matrix_ul::
    operator() (const typename Matrix_t::size_type row, const typename Matrix_t::size_type column)
{
	return *gsl_matrix_ulong_ptr(this->gsl_mat.get(), row, column);
}

template<>
typename Matrix_s::reference Matrix_s::
    operator() (const typename Matrix_t::size_type row, const typename Matrix_t::size_type column)
{
	return *gsl_matrix_short_ptr(this->gsl_mat.get(), row, column);
}

template<>
typename Matrix_us::reference Matrix_us::
    operator() (const typename Matrix_t::size_type row, const typename Matrix_t::size_type column)
{
	return *gsl_matrix_ushort_ptr(this->gsl_mat.get(), row, column);
}

template<>
typename Matrix_c::reference Matrix_c::
    operator() (const typename Matrix_t::size_type row, const typename Matrix_t::size_type column)
{
	return *gsl_matrix_char_ptr(this->gsl_mat.get(), row, column);
}

template<>
typename Matrix_uc::reference Matrix_uc::
    operator() (const typename Matrix_t::size_type row, const typename Matrix_t::size_type column)
{
	return *gsl_matrix_uchar_ptr(this->gsl_mat.get(), row, column);
}

template<>
typename Matrix_cx::reference Matrix_cx::
    operator() (const typename Matrix_t::size_type row, const typename Matrix_t::size_type column)
{
	return *gsl_matrix_complex_ptr(this->gsl_mat.get(), row, column);
}

template<>
typename Matrix_cxld::reference Matrix_cxld::
    operator() (const typename Matrix_t::size_type row, const typename Matrix_t::size_type column)
{
	return *gsl_matrix_complex_long_double_ptr(this->gsl_mat.get(), row, column);
}

template<>
typename Matrix_cxf::reference Matrix_cxf::
    operator() (const typename Matrix_t::size_type row, const typename Matrix_t::size_type column)
{
	return *gsl_matrix_complex_float_ptr(this->gsl_mat.get(), row, column);
}

template<class D, class M, class V, class A>
typename Matrix_t<D, M, V, A>::const_reference Matrix_t<D, M, V, A>::
    operator() (const typename Matrix_t::size_type row, const typename Matrix_t::size_type column) const
{
	return (*this)[row][column];
}

template<>
typename Matrix::const_reference Matrix::
    operator() (const typename Matrix::size_type row, const typename Matrix::size_type column) const
{
	return *gsl_matrix_const_ptr(this->gsl_mat.get(), row, column);
}

template<>
typename Matrix_ld::const_reference Matrix_ld::
    operator() (const typename Matrix_ld::size_type row, const typename Matrix_ld::size_type column) const
{
	return *gsl_matrix_long_double_const_ptr(this->gsl_mat.get(), row, column);
}

template<>
typename Matrix_f::const_reference Matrix_f::
    operator() (const typename Matrix_f::size_type row, const typename Matrix_f::size_type column) const
{
	return *gsl_matrix_float_const_ptr(this->gsl_mat.get(), row, column);
}

template<>
typename Matrix_i::const_reference Matrix_i::
    operator() (const typename Matrix_i::size_type row, const typename Matrix_i::size_type column) const
{
	return *gsl_matrix_int_const_ptr(this->gsl_mat.get(), row, column);
}

template<>
typename Matrix_ui::const_reference Matrix_ui::
    operator() (const typename Matrix_ui::size_type row, const typename Matrix_ui::size_type column) const
{
	return *gsl_matrix_uint_const_ptr(this->gsl_mat.get(), row, column);
}

template<>
typename Matrix_l::const_reference Matrix_l::
    operator() (const typename Matrix_l::size_type row, const typename Matrix_l::size_type column) const
{
	return *gsl_matrix_long_const_ptr(this->gsl_mat.get(), row, column);
}

template<>
typename Matrix_ul::const_reference Matrix_ul::
    operator() (const typename Matrix_ul::size_type row, const typename Matrix_ul::size_type column) const
{
	return *gsl_matrix_ulong_const_ptr(this->gsl_mat.get(), row, column);
}

template<>
typename Matrix_s::const_reference Matrix_s::
    operator() (const typename Matrix_s::size_type row, const typename Matrix_s::size_type column) const
{
	return *gsl_matrix_short_const_ptr(this->gsl_mat.get(), row, column);
}

template<>
typename Matrix_us::const_reference Matrix_us::
    operator() (const typename Matrix_us::size_type row, const typename Matrix_us::size_type column) const
{
	return *gsl_matrix_ushort_const_ptr(this->gsl_mat.get(), row, column);
}

template<>
typename Matrix_c::const_reference Matrix_c::
    operator() (const typename Matrix_c::size_type row, const typename Matrix_c::size_type column) const
{
	return *gsl_matrix_char_const_ptr(this->gsl_mat.get(), row, column);
}

template<>
typename Matrix_uc::const_reference Matrix_uc::
    operator() (const typename Matrix_uc::size_type row, const typename Matrix_uc::size_type column) const
{
	return *gsl_matrix_uchar_const_ptr(this->gsl_mat.get(), row, column);
}

template<>
typename Matrix_cx::const_reference Matrix_cx::
    operator() (const typename Matrix_cx::size_type row, const typename Matrix_cx::size_type column) const
{
	return *gsl_matrix_complex_const_ptr(this->gsl_mat.get(), row, column);
}

template<>
typename Matrix_cxld::const_reference Matrix_cxld::
    operator() (const typename Matrix_cxld::size_type row, const typename Matrix_cxld::size_type column) const
{
	return *gsl_matrix_complex_long_double_const_ptr(this->gsl_mat.get(), row, column);
}

template<>
typename Matrix_cxf::const_reference Matrix_cxf::
    operator() (const typename Matrix_cxf::size_type row, const typename Matrix_cxf::size_type column) const
{
	return *gsl_matrix_complex_float_const_ptr(this->gsl_mat.get(), row, column);
}

/*
template<class D, class M, class V, class A>
std::string Matrix_t<D, M, V, A>::to_string() const
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
std::string Matrix_cx::to_string() const
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
std::string Matrix_cxld::to_string() const
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
std::string Matrix_cxf::to_string() const
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
*/

template Matrix::Matrix_t(const std::shared_ptr<Matrix_t::GSL_Mat>& m);
template Matrix_ld::Matrix_t(const std::shared_ptr<Matrix_t::GSL_Mat>& m);
template Matrix_f::Matrix_t(const std::shared_ptr<Matrix_t::GSL_Mat>& m);
template Matrix_i::Matrix_t(const std::shared_ptr<Matrix_t::GSL_Mat>& m);
template Matrix_ui::Matrix_t(const std::shared_ptr<Matrix_t::GSL_Mat>& m);
template Matrix_l::Matrix_t(const std::shared_ptr<Matrix_t::GSL_Mat>& m);
template Matrix_ul::Matrix_t(const std::shared_ptr<Matrix_t::GSL_Mat>& m);
template Matrix_s::Matrix_t(const std::shared_ptr<Matrix_t::GSL_Mat>& m);
template Matrix_us::Matrix_t(const std::shared_ptr<Matrix_t::GSL_Mat>& m);
template Matrix_c::Matrix_t(const std::shared_ptr<Matrix_t::GSL_Mat>& m);
template Matrix_uc::Matrix_t(const std::shared_ptr<Matrix_t::GSL_Mat>& m);
template Matrix_cx::Matrix_t(const std::shared_ptr<Matrix_t::GSL_Mat>& m);
template Matrix_cxld::Matrix_t(const std::shared_ptr<Matrix_t::GSL_Mat>& m);
template Matrix_cxf::Matrix_t(const std::shared_ptr<Matrix_t::GSL_Mat>& m);

template Matrix::Matrix_t(const Matrix_t::size_type n1, const Matrix_t::size_type n2);
template Matrix_ld::Matrix_t(const Matrix_t::size_type n1, const Matrix_t::size_type n2);
template Matrix_f::Matrix_t(const Matrix_t::size_type n1, const Matrix_t::size_type n2);
template Matrix_i::Matrix_t(const Matrix_t::size_type n1, const Matrix_t::size_type n2);
template Matrix_ui::Matrix_t(const Matrix_t::size_type n1, const Matrix_t::size_type n2);
template Matrix_l::Matrix_t(const Matrix_t::size_type n1, const Matrix_t::size_type n2);
template Matrix_ul::Matrix_t(const Matrix_t::size_type n1, const Matrix_t::size_type n2);
template Matrix_s::Matrix_t(const Matrix_t::size_type n1, const Matrix_t::size_type n2);
template Matrix_us::Matrix_t(const Matrix_t::size_type n1, const Matrix_t::size_type n2);
template Matrix_c::Matrix_t(const Matrix_t::size_type n1, const Matrix_t::size_type n2);
template Matrix_uc::Matrix_t(const Matrix_t::size_type n1, const Matrix_t::size_type n2);
template Matrix_cx::Matrix_t(const Matrix_t::size_type n1, const Matrix_t::size_type n2);
template Matrix_cxld::Matrix_t(const Matrix_t::size_type n1, const Matrix_t::size_type n2);
template Matrix_cxf::Matrix_t(const Matrix_t::size_type n1, const Matrix_t::size_type n2);

template Matrix::Matrix_t(std::initializer_list<V> l);
template Matrix_ld::Matrix_t(std::initializer_list<V> l);
template Matrix_f::Matrix_t(std::initializer_list<V> l);
template Matrix_i::Matrix_t(std::initializer_list<V> l);
template Matrix_ui::Matrix_t(std::initializer_list<V> l);
template Matrix_l::Matrix_t(std::initializer_list<V> l);
template Matrix_ul::Matrix_t(std::initializer_list<V> l);
template Matrix_s::Matrix_t(std::initializer_list<V> l);
template Matrix_us::Matrix_t(std::initializer_list<V> l);
template Matrix_c::Matrix_t(std::initializer_list<V> l);
template Matrix_uc::Matrix_t(std::initializer_list<V> l);
template Matrix_cx::Matrix_t(std::initializer_list<V> l);
template Matrix_cxld::Matrix_t(std::initializer_list<V> l);
template Matrix_cxf::Matrix_t(std::initializer_list<V> l);

template Matrix& Matrix::copy(const Matrix_t& a);
template Matrix_ld& Matrix_ld::copy(const Matrix_t& a);
template Matrix_f& Matrix_f::copy(const Matrix_t& a);
template Matrix_i& Matrix_i::copy(const Matrix_t& a);
template Matrix_ui& Matrix_ui::copy(const Matrix_t& a);
template Matrix_l& Matrix_l::copy(const Matrix_t& a);
template Matrix_ul& Matrix_ul::copy(const Matrix_t& a);
template Matrix_s& Matrix_s::copy(const Matrix_t& a);
template Matrix_us& Matrix_us::copy(const Matrix_t& a);
template Matrix_c& Matrix_c::copy(const Matrix_t& a);
template Matrix_uc& Matrix_uc::copy(const Matrix_t& a);
template Matrix_cx& Matrix_cx::copy(const Matrix_t& a);
template Matrix_cxld& Matrix_cxld::copy(const Matrix_t& a);
template Matrix_cxf& Matrix_cxf::copy(const Matrix_t& a);

template Matrix& Matrix::operator+=(const Matrix_t& b);
template Matrix_ld& Matrix_ld::operator+=(const Matrix_t& b);
template Matrix_f& Matrix_f::operator+=(const Matrix_t& b);
template Matrix_i& Matrix_i::operator+=(const Matrix_t& b);
template Matrix_ui& Matrix_ui::operator+=(const Matrix_t& b);
template Matrix_l& Matrix_l::operator+=(const Matrix_t& b);
template Matrix_ul& Matrix_ul::operator+=(const Matrix_t& b);
template Matrix_s& Matrix_s::operator+=(const Matrix_t& b);
template Matrix_us& Matrix_us::operator+=(const Matrix_t& b);
template Matrix_c& Matrix_c::operator+=(const Matrix_t& b);
template Matrix_uc& Matrix_uc::operator+=(const Matrix_t& b);
template Matrix_cx& Matrix_cx::operator+=(const Matrix_t& b);
template Matrix_cxld& Matrix_cxld::operator+=(const Matrix_t& b);
template Matrix_cxf& Matrix_cxf::operator+=(const Matrix_t& b);

template Matrix& Matrix::operator-=(const Matrix_t& b);
template Matrix_ld& Matrix_ld::operator-=(const Matrix_t& b);
template Matrix_f& Matrix_f::operator-=(const Matrix_t& b);
template Matrix_i& Matrix_i::operator-=(const Matrix_t& b);
template Matrix_ui& Matrix_ui::operator-=(const Matrix_t& b);
template Matrix_l& Matrix_l::operator-=(const Matrix_t& b);
template Matrix_ul& Matrix_ul::operator-=(const Matrix_t& b);
template Matrix_s& Matrix_s::operator-=(const Matrix_t& b);
template Matrix_us& Matrix_us::operator-=(const Matrix_t& b);
template Matrix_c& Matrix_c::operator-=(const Matrix_t& b);
template Matrix_uc& Matrix_uc::operator-=(const Matrix_t& b);
template Matrix_cx& Matrix_cx::operator-=(const Matrix_t& b);
template Matrix_cxld& Matrix_cxld::operator-=(const Matrix_t& b);
template Matrix_cxf& Matrix_cxf::operator-=(const Matrix_t& b);

template Matrix& Matrix::operator*=(const Matrix_t& b);
template Matrix_ld& Matrix_ld::operator*=(const Matrix_t& b);
template Matrix_f& Matrix_f::operator*=(const Matrix_t& b);
template Matrix_i& Matrix_i::operator*=(const Matrix_t& b);
template Matrix_ui& Matrix_ui::operator*=(const Matrix_t& b);
template Matrix_l& Matrix_l::operator*=(const Matrix_t& b);
template Matrix_ul& Matrix_ul::operator*=(const Matrix_t& b);
template Matrix_s& Matrix_s::operator*=(const Matrix_t& b);
template Matrix_us& Matrix_us::operator*=(const Matrix_t& b);
template Matrix_c& Matrix_c::operator*=(const Matrix_t& b);
template Matrix_uc& Matrix_uc::operator*=(const Matrix_t& b);
template Matrix_cx& Matrix_cx::operator*=(const Matrix_t& b);
template Matrix_cxld& Matrix_cxld::operator*=(const Matrix_t& b);
template Matrix_cxf& Matrix_cxf::operator*=(const Matrix_t& b);

template Matrix& Matrix::operator/=(const Matrix_t& b);
template Matrix_ld& Matrix_ld::operator/=(const Matrix_t& b);
template Matrix_f& Matrix_f::operator/=(const Matrix_t& b);
template Matrix_i& Matrix_i::operator/=(const Matrix_t& b);
template Matrix_ui& Matrix_ui::operator/=(const Matrix_t& b);
template Matrix_l& Matrix_l::operator/=(const Matrix_t& b);
template Matrix_ul& Matrix_ul::operator/=(const Matrix_t& b);
template Matrix_s& Matrix_s::operator/=(const Matrix_t& b);
template Matrix_us& Matrix_us::operator/=(const Matrix_t& b);
template Matrix_c& Matrix_c::operator/=(const Matrix_t& b);
template Matrix_uc& Matrix_uc::operator/=(const Matrix_t& b);
template Matrix_cx& Matrix_cx::operator/=(const Matrix_t& b);
template Matrix_cxld& Matrix_cxld::operator/=(const Matrix_t& b);
template Matrix_cxf& Matrix_cxf::operator/=(const Matrix_t& b);

template Matrix& Matrix::operator*=(const value_type& b);
template Matrix_ld& Matrix_ld::operator*=(const value_type& b);
template Matrix_f& Matrix_f::operator*=(const value_type& b);
template Matrix_i& Matrix_i::operator*=(const value_type& b);
template Matrix_ui& Matrix_ui::operator*=(const value_type& b);
template Matrix_l& Matrix_l::operator*=(const value_type& b);
template Matrix_ul& Matrix_ul::operator*=(const value_type& b);
template Matrix_s& Matrix_s::operator*=(const value_type& b);
template Matrix_us& Matrix_us::operator*=(const value_type& b);
template Matrix_c& Matrix_c::operator*=(const value_type& b);
template Matrix_uc& Matrix_uc::operator*=(const value_type& b);
template Matrix_cx& Matrix_cx::operator*=(const value_type& b);
template Matrix_cxld& Matrix_cxld::operator*=(const value_type& b);
template Matrix_cxf& Matrix_cxf::operator*=(const value_type& b);

template Matrix& Matrix::operator/=(const value_type& b);
template Matrix_ld& Matrix_ld::operator/=(const value_type& b);
template Matrix_f& Matrix_f::operator/=(const value_type& b);
template Matrix_i& Matrix_i::operator/=(const value_type& b);
template Matrix_ui& Matrix_ui::operator/=(const value_type& b);
template Matrix_l& Matrix_l::operator/=(const value_type& b);
template Matrix_ul& Matrix_ul::operator/=(const value_type& b);
template Matrix_s& Matrix_s::operator/=(const value_type& b);
template Matrix_us& Matrix_us::operator/=(const value_type& b);
template Matrix_c& Matrix_c::operator/=(const value_type& b);
template Matrix_uc& Matrix_uc::operator/=(const value_type& b);
template Matrix_cx& Matrix_cx::operator/=(const value_type& b);
template Matrix_cxld& Matrix_cxld::operator/=(const value_type& b);
template Matrix_cxf& Matrix_cxf::operator/=(const value_type& b);

template Matrix::V Matrix::operator*(const V& v);
template Matrix_f::V Matrix_f::operator*(const V& v);
template Matrix_cx::V Matrix_cx::operator*(const V& v);
template Matrix_cxld::V Matrix_cxld::operator*(const V& v);

template bool Matrix::operator==(const Matrix_t& b) const;
template bool Matrix_ld::operator==(const Matrix_t& b) const;
template bool Matrix_f::operator==(const Matrix_t& b) const;
template bool Matrix_i::operator==(const Matrix_t& b) const;
template bool Matrix_ui::operator==(const Matrix_t& b) const;
template bool Matrix_l::operator==(const Matrix_t& b) const;
template bool Matrix_ul::operator==(const Matrix_t& b) const;
template bool Matrix_s::operator==(const Matrix_t& b) const;
template bool Matrix_us::operator==(const Matrix_t& b) const;
template bool Matrix_c::operator==(const Matrix_t& b) const;
template bool Matrix_uc::operator==(const Matrix_t& b) const;
template bool Matrix_cx::operator==(const Matrix_t& b) const;
template bool Matrix_cxld::operator==(const Matrix_t& b) const;
template bool Matrix_cxf::operator==(const Matrix_t& b) const;

template Matrix Matrix::transpose() const;
template Matrix_ld Matrix_ld::transpose() const;
template Matrix_f Matrix_f::transpose() const;
template Matrix_i Matrix_i::transpose() const;
template Matrix_ui Matrix_ui::transpose() const;
template Matrix_l Matrix_l::transpose() const;
template Matrix_ul Matrix_ul::transpose() const;
template Matrix_s Matrix_s::transpose() const;
template Matrix_us Matrix_us::transpose() const;
template Matrix_c Matrix_c::transpose() const;
template Matrix_uc Matrix_uc::transpose() const;
template Matrix_cx Matrix_cx::transpose() const;
template Matrix_cxld Matrix_cxld::transpose() const;
template Matrix_cxf Matrix_cxf::transpose() const;

template Matrix Matrix::hermitian_transpose() const;
template Matrix_ld Matrix_ld::hermitian_transpose() const;
template Matrix_f Matrix_f::hermitian_transpose() const;
template Matrix_i Matrix_i::hermitian_transpose() const;
template Matrix_ui Matrix_ui::hermitian_transpose() const;
template Matrix_l Matrix_l::hermitian_transpose() const;
template Matrix_ul Matrix_ul::hermitian_transpose() const;
template Matrix_s Matrix_s::hermitian_transpose() const;
template Matrix_us Matrix_us::hermitian_transpose() const;
template Matrix_c Matrix_c::hermitian_transpose() const;
template Matrix_uc Matrix_uc::hermitian_transpose() const;
template Matrix_cx Matrix_cx::hermitian_transpose() const;
template Matrix_cxld Matrix_cxld::hermitian_transpose() const;
template Matrix_cxf Matrix_cxf::hermitian_transpose() const;

template Matrix Matrix::inverse() const;
template Matrix_cx Matrix_cx::inverse() const;

template Matrix::value_type Matrix::det() const;
template Matrix_cx::value_type Matrix_cx::det() const;

template const Matrix::Row Matrix::get_row(const Matrix_t::size_type i) const;
template const Matrix_ld::Row Matrix_ld::get_row(const Matrix_t::size_type i) const;
template const Matrix_f::Row Matrix_f::get_row(const Matrix_t::size_type i) const;
template const Matrix_i::Row Matrix_i::get_row(const Matrix_t::size_type i) const;
template const Matrix_ui::Row Matrix_ui::get_row(const Matrix_t::size_type i) const;
template const Matrix_l::Row Matrix_l::get_row(const Matrix_t::size_type i) const;
template const Matrix_ul::Row Matrix_ul::get_row(const Matrix_t::size_type i) const;
template const Matrix_s::Row Matrix_s::get_row(const Matrix_t::size_type i) const;
template const Matrix_us::Row Matrix_us::get_row(const Matrix_t::size_type i) const;
template const Matrix_c::Row Matrix_c::get_row(const Matrix_t::size_type i) const;
template const Matrix_uc::Row Matrix_uc::get_row(const Matrix_t::size_type i) const;
template const Matrix_cx::Row Matrix_cx::get_row(const Matrix_t::size_type i) const;
template const Matrix_cxld::Row Matrix_cxld::get_row(const Matrix_t::size_type i) const;
template const Matrix_cxf::Row Matrix_cxf::get_row(const Matrix_t::size_type i) const;

template Matrix::Row Matrix::get_row(const Matrix_t::size_type i);
template Matrix_ld::Row Matrix_ld::get_row(const Matrix_t::size_type i);
template Matrix_f::Row Matrix_f::get_row(const Matrix_t::size_type i);
template Matrix_i::Row Matrix_i::get_row(const Matrix_t::size_type i);
template Matrix_ui::Row Matrix_ui::get_row(const Matrix_t::size_type i);
template Matrix_l::Row Matrix_l::get_row(const Matrix_t::size_type i);
template Matrix_ul::Row Matrix_ul::get_row(const Matrix_t::size_type i);
template Matrix_s::Row Matrix_s::get_row(const Matrix_t::size_type i);
template Matrix_us::Row Matrix_us::get_row(const Matrix_t::size_type i);
template Matrix_c::Row Matrix_c::get_row(const Matrix_t::size_type i);
template Matrix_uc::Row Matrix_uc::get_row(const Matrix_t::size_type i);
template Matrix_cx::Row Matrix_cx::get_row(const Matrix_t::size_type i);
template Matrix_cxld::Row Matrix_cxld::get_row(const Matrix_t::size_type i);
template Matrix_cxf::Row Matrix_cxf::get_row(const Matrix_t::size_type i);

template const Matrix::Column Matrix::get_col(const Matrix_t::size_type i) const;
template const Matrix_ld::Column Matrix_ld::get_col(const Matrix_t::size_type i) const;
template const Matrix_f::Column Matrix_f::get_col(const Matrix_t::size_type i) const;
template const Matrix_i::Column Matrix_i::get_col(const Matrix_t::size_type i) const;
template const Matrix_ui::Column Matrix_ui::get_col(const Matrix_t::size_type i) const;
template const Matrix_l::Column Matrix_l::get_col(const Matrix_t::size_type i) const;
template const Matrix_ul::Column Matrix_ul::get_col(const Matrix_t::size_type i) const;
template const Matrix_s::Column Matrix_s::get_col(const Matrix_t::size_type i) const;
template const Matrix_us::Column Matrix_us::get_col(const Matrix_t::size_type i) const;
template const Matrix_c::Column Matrix_c::get_col(const Matrix_t::size_type i) const;
template const Matrix_uc::Column Matrix_uc::get_col(const Matrix_t::size_type i) const;
template const Matrix_cx::Column Matrix_cx::get_col(const Matrix_t::size_type i) const;
template const Matrix_cxld::Column Matrix_cxld::get_col(const Matrix_t::size_type i) const;
template const Matrix_cxf::Column Matrix_cxf::get_col(const Matrix_t::size_type i) const;

template Matrix::Column Matrix::get_col(const Matrix_t::size_type i);
template Matrix_ld::Column Matrix_ld::get_col(const Matrix_t::size_type i);
template Matrix_f::Column Matrix_f::get_col(const Matrix_t::size_type i);
template Matrix_i::Column Matrix_i::get_col(const Matrix_t::size_type i);
template Matrix_ui::Column Matrix_ui::get_col(const Matrix_t::size_type i);
template Matrix_l::Column Matrix_l::get_col(const Matrix_t::size_type i);
template Matrix_ul::Column Matrix_ul::get_col(const Matrix_t::size_type i);
template Matrix_s::Column Matrix_s::get_col(const Matrix_t::size_type i);
template Matrix_us::Column Matrix_us::get_col(const Matrix_t::size_type i);
template Matrix_c::Column Matrix_c::get_col(const Matrix_t::size_type i);
template Matrix_uc::Column Matrix_uc::get_col(const Matrix_t::size_type i);
template Matrix_cx::Column Matrix_cx::get_col(const Matrix_t::size_type i);
template Matrix_cxld::Column Matrix_cxld::get_col(const Matrix_t::size_type i);
template Matrix_cxf::Column Matrix_cxf::get_col(const Matrix_t::size_type i);

template Matrix::reference Matrix::operator() (const typename Matrix_t::size_type row, const typename Matrix_t::size_type column);
template Matrix_ld::reference Matrix_ld::operator() (const typename Matrix_t::size_type row, const typename Matrix_t::size_type column);
template Matrix_f::reference Matrix_f::operator() (const typename Matrix_t::size_type row, const typename Matrix_t::size_type column);
template Matrix_i::reference Matrix_i::operator() (const typename Matrix_t::size_type row, const typename Matrix_t::size_type column);
template Matrix_ui::reference Matrix_ui::operator() (const typename Matrix_t::size_type row, const typename Matrix_t::size_type column);
template Matrix_l::reference Matrix_l::operator() (const typename Matrix_t::size_type row, const typename Matrix_t::size_type column);
template Matrix_ul::reference Matrix_ul::operator() (const typename Matrix_t::size_type row, const typename Matrix_t::size_type column);
template Matrix_s::reference Matrix_s::operator() (const typename Matrix_t::size_type row, const typename Matrix_t::size_type column);
template Matrix_us::reference Matrix_us::operator() (const typename Matrix_t::size_type row, const typename Matrix_t::size_type column);
template Matrix_c::reference Matrix_c::operator() (const typename Matrix_t::size_type row, const typename Matrix_t::size_type column);
template Matrix_uc::reference Matrix_uc::operator() (const typename Matrix_t::size_type row, const typename Matrix_t::size_type column);
template Matrix_cx::reference Matrix_cx::operator() (const typename Matrix_t::size_type row, const typename Matrix_t::size_type column);
template Matrix_cxld::reference Matrix_cxld::operator() (const typename Matrix_t::size_type row, const typename Matrix_t::size_type column);
template Matrix_cxf::reference Matrix_cxf::operator() (const typename Matrix_t::size_type row, const typename Matrix_t::size_type column);

template Matrix::const_reference Matrix::operator()(const typename Matrix_t::size_type row, const typename Matrix_t::size_type column) const;
template Matrix_ld::const_reference Matrix_ld::operator()(const typename Matrix_t::size_type row, const typename Matrix_t::size_type column) const;
template Matrix_f::const_reference Matrix_f::operator()(const typename Matrix_t::size_type row, const typename Matrix_t::size_type column) const;
template Matrix_i::const_reference Matrix_i::operator()(const typename Matrix_t::size_type row, const typename Matrix_t::size_type column) const;
template Matrix_ui::const_reference Matrix_ui::operator()(const typename Matrix_t::size_type row, const typename Matrix_t::size_type column) const;
template Matrix_l::const_reference Matrix_l::operator()(const typename Matrix_t::size_type row, const typename Matrix_t::size_type column) const;
template Matrix_ul::const_reference Matrix_ul::operator()(const typename Matrix_t::size_type row, const typename Matrix_t::size_type column) const;
template Matrix_s::const_reference Matrix_s::operator()(const typename Matrix_t::size_type row, const typename Matrix_t::size_type column) const;
template Matrix_us::const_reference Matrix_us::operator()(const typename Matrix_t::size_type row, const typename Matrix_t::size_type column) const;
template Matrix_c::const_reference Matrix_c::operator()(const typename Matrix_t::size_type row, const typename Matrix_t::size_type column) const;
template Matrix_uc::const_reference Matrix_uc::operator()(const typename Matrix_t::size_type row, const typename Matrix_t::size_type column) const;
template Matrix_cx::const_reference Matrix_cx::operator()(const typename Matrix_t::size_type row, const typename Matrix_t::size_type column) const;
template Matrix_cxld::const_reference Matrix_cxld::operator()(const typename Matrix_t::size_type row, const typename Matrix_t::size_type column) const;
template Matrix_cxf::const_reference Matrix_cxf::operator()(const typename Matrix_t::size_type row, const typename Matrix_t::size_type column) const;

template class Matrix_t<double, gsl_matrix, gsl_vector>;
template class Matrix_t<long double, gsl_matrix_long_double, gsl_vector_long_double>;
template class Matrix_t<float, gsl_matrix_float, gsl_vector_float>;
template class Matrix_t<int, gsl_matrix_int, gsl_vector_int>;
template class Matrix_t<unsigned int, gsl_matrix_uint, gsl_vector_uint>;
template class Matrix_t<long, gsl_matrix_long, gsl_vector_long>;
template class Matrix_t<unsigned long, gsl_matrix_ulong, gsl_vector_ulong>;
template class Matrix_t<short, gsl_matrix_short, gsl_vector_short>;
template class Matrix_t<unsigned short, gsl_matrix_ushort, gsl_vector_ushort>;
template class Matrix_t<char, gsl_matrix_char, gsl_vector_char>;
template class Matrix_t<unsigned char, gsl_matrix_uchar, gsl_vector_uchar>;
template class Matrix_t<GSL::Complex, gsl_matrix_complex,
    gsl_vector_complex, std::allocator<gsl_complex>>;
template class Matrix_t<GSL::Complex_ld, gsl_matrix_complex_long_double,
    gsl_vector_complex_long_double, std::allocator<gsl_complex_long_double>>;
template class Matrix_t<GSL::Complex_f, gsl_matrix_complex_float,
    gsl_vector_complex_float, std::allocator<gsl_complex_float>>;

}
