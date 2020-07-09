#include "GSLpp/vector.h"
#include "GSLpp/complex.h"
#include "GSLpp/matrix.h"
#include <gsl/gsl_blas.h>
#include <iostream>
#include <stdexcept>
#include <functional>

namespace GSL{

template<>
Vector::Vector_t(const std::shared_ptr<GSL_Vec>& v)
 : gsl_vec(v)
{}

template<>
Vector_ld::Vector_t(const std::shared_ptr<GSL_Vec>& v)
 : gsl_vec(v)
{}

template<>
Vector_f::Vector_t(const std::shared_ptr<GSL_Vec>& v)
 : gsl_vec(v)
{}

template<>
Vector_i::Vector_t(const std::shared_ptr<GSL_Vec>& v)
 : gsl_vec(v)
{}

template<>
Vector_ui::Vector_t(const std::shared_ptr<GSL_Vec>& v)
 : gsl_vec(v)
{}

template<>
Vector_l::Vector_t(const std::shared_ptr<GSL_Vec>& v)
 : gsl_vec(v)
{}

template<>
Vector_ul::Vector_t(const std::shared_ptr<GSL_Vec>& v)
 : gsl_vec(v)
{}

template<>
Vector_s::Vector_t(const std::shared_ptr<GSL_Vec>& v)
 : gsl_vec(v)
{}

template<>
Vector_us::Vector_t(const std::shared_ptr<GSL_Vec>& v)
 : gsl_vec(v)
{}

template<>
Vector_c::Vector_t(const std::shared_ptr<GSL_Vec>& v)
 : gsl_vec(v)
{}

template<>
Vector_uc::Vector_t(const std::shared_ptr<GSL_Vec>& v)
 : gsl_vec(v)
{}

template<>
Vector_cx::Vector_t(const std::shared_ptr<GSL_Vec>& v)
 : gsl_vec(v)
{}

template<>
Vector_cxld::Vector_t(const std::shared_ptr<GSL_Vec>& v)
 : gsl_vec(v)
{}


template<>
Vector_cxf::Vector_t(const std::shared_ptr<GSL_Vec>& v)
 : gsl_vec(v)
{}


template<>
Vector::Vector_t
(const Vector::size_type n)
 : gsl_vec(gsl_vector_calloc(n), gsl_vector_free)
{
    if(gsl_vec == nullptr){
        throw std::runtime_error("Memory allocation (gsl_vector_calloc)"
        " failed!");
    }
}

template<>
Vector_ld::Vector_t
(const Vector_t::size_type n)
 : gsl_vec(gsl_vector_long_double_calloc(n), gsl_vector_long_double_free)
{

    if(gsl_vec == nullptr){
        throw std::runtime_error("Memory allocation (gsl_vector_long_double_calloc)"
        " failed!");
    }
}

template<>
Vector_f::Vector_t(const Vector_t::size_type n)
 : gsl_vec(gsl_vector_float_calloc(n), gsl_vector_float_free)
{
    if(gsl_vec == nullptr){
        throw std::runtime_error("Memory allocation (gsl_vector_float_calloc)"
        " failed!");
    }
}

template<>
Vector_i::Vector_t
(const Vector_t::size_type n)
 : gsl_vec(gsl_vector_int_calloc(n), gsl_vector_int_free)
{
    if(gsl_vec == nullptr){
        throw std::runtime_error("Memory allocation (gsl_vector_int_calloc)"
        " failed!");
    }
}

template<>
Vector_ui::Vector_t
(const Vector_t::size_type n)
 : gsl_vec(gsl_vector_uint_calloc(n), gsl_vector_uint_free)
{
    if(gsl_vec == nullptr){
        throw std::runtime_error("Memory allocation (gsl_vector_uint_calloc)"
        " failed!");
    }
}

template<>
Vector_l::Vector_t
(const Vector_t::size_type n)
 : gsl_vec(gsl_vector_long_calloc(n), gsl_vector_long_free)
{
    if(gsl_vec == nullptr){
        throw std::runtime_error("Memory allocation (gsl_vector_long_calloc)"
        " failed!");
    }
}

template<>
Vector_ul::Vector_t
(const Vector_t::size_type n)
 : gsl_vec(gsl_vector_ulong_calloc(n), gsl_vector_ulong_free)
{
    if(gsl_vec == nullptr){
        throw std::runtime_error("Memory allocation (gsl_vector_ulong_calloc)"
        " failed!");
    }
}

template<>
Vector_s::Vector_t
(const Vector_t::size_type n)
 : gsl_vec(gsl_vector_short_calloc(n), gsl_vector_short_free)
{
    if(gsl_vec == nullptr){
        throw std::runtime_error("Memory allocation (gsl_vector_short_calloc)"
        " failed!");
    }
}

template<>
Vector_us::Vector_t
(const Vector_t::size_type n)
 : gsl_vec(gsl_vector_ushort_calloc(n), gsl_vector_ushort_free)
{
    if(gsl_vec == nullptr){
        throw std::runtime_error("Memory allocation (gsl_vector_ushort_calloc)"
        " failed!");
    }
}

template<>
Vector_c::Vector_t
(const Vector_t::size_type n)
 : gsl_vec(gsl_vector_char_calloc(n), gsl_vector_char_free)
{
    if(gsl_vec == nullptr){
        throw std::runtime_error("Memory allocation (gsl_vector_char_calloc)"
        " failed!");
    }
}

template<>
Vector_uc::Vector_t
(const Vector_t::size_type n)
 : gsl_vec(gsl_vector_uchar_calloc(n), gsl_vector_uchar_free)
{
    if(gsl_vec == nullptr){
        throw std::runtime_error("Memory allocation (gsl_vector_uchar_calloc)"
        " failed!");
    }
}

template<>
Vector_cx::Vector_t
(const Vector_t::size_type n)
 : gsl_vec(gsl_vector_complex_calloc(n), gsl_vector_complex_free)
{
    if(gsl_vec == nullptr){
        throw std::runtime_error("Memory allocation (gsl_vector_complex_calloc)"
        " failed!");
    }
}

template<>
Vector_cxld::Vector_t
(const Vector_t::size_type n)
 : gsl_vec(gsl_vector_complex_long_double_calloc(n), gsl_vector_complex_long_double_free)
{
    if(gsl_vec == nullptr){
        throw std::runtime_error("Memory allocation (gsl_vector_long_double_calloc)"
        " failed!");
    }
}

template<>
Vector_cxf::Vector_t
(const Vector_t::size_type n)
 : gsl_vec(gsl_vector_complex_float_calloc(n), gsl_vector_complex_float_free)
{
    if(gsl_vec == nullptr){
        throw std::runtime_error("Memory allocation (gsl_vector_float_calloc)"
        " failed!");
    }
}

template<>
Vector::Vector_t
(const Vector_t::size_type n, const Vector_t::value_type v)
 : gsl_vec(gsl_vector_alloc(n), gsl_vector_free)
{

    if(gsl_vec == nullptr){
        throw std::runtime_error("Memory allocation (gsl_vector_alloc)"
        " failed!");
    }
    gsl_vector_set_all(gsl_vec.get(), v);
}

template<>
Vector_ld::Vector_t
(const Vector_t::size_type n, const Vector_t::value_type v)
 : gsl_vec(gsl_vector_long_double_alloc(n), gsl_vector_long_double_free)
{

    if(gsl_vec == nullptr){
        throw std::runtime_error("Memory allocation (gsl_vector_long_double_alloc)"
        " failed!");
    }
    gsl_vector_long_double_set_all(gsl_vec.get(), v);
}

template<>
Vector_f::Vector_t(const Vector_t::size_type n, const Vector_t::value_type v)
 : gsl_vec(gsl_vector_float_alloc(n), gsl_vector_float_free)
{
    if(gsl_vec == nullptr){
        throw std::runtime_error("Memory allocation (gsl_vector_float_alloc)"
        " failed!");
    }
    gsl_vector_float_set_all(gsl_vec.get(), v);
}

template<>
Vector_i::Vector_t
(const Vector_t::size_type n, const Vector_t::value_type v)
 : gsl_vec(gsl_vector_int_alloc(n), gsl_vector_int_free)
{
    if(gsl_vec == nullptr){
        throw std::runtime_error("Memory allocation (gsl_vector_int_alloc)"
        " failed!");
    }
    gsl_vector_int_set_all(gsl_vec.get(), v);
}

template<>
Vector_ui::Vector_t
(const Vector_t::size_type n, const Vector_t::value_type v)
 : gsl_vec(gsl_vector_uint_alloc(n), gsl_vector_uint_free)
{
    if(gsl_vec == nullptr){
        throw std::runtime_error("Memory allocation (gsl_vector_uint_alloc)"
        " failed!");
    }
    gsl_vector_uint_set_all(gsl_vec.get(), v);
}

template<>
Vector_l::Vector_t
(const Vector_t::size_type n, const Vector_t::value_type v)
 : gsl_vec(gsl_vector_long_alloc(n), gsl_vector_long_free)
{
    if(gsl_vec == nullptr){
        throw std::runtime_error("Memory allocation (gsl_vector_long_alloc)"
        " failed!");
    }
    gsl_vector_long_set_all(gsl_vec.get(), v);
}

template<>
Vector_ul::Vector_t
(const Vector_t::size_type n, const Vector_t::value_type v)
 : gsl_vec(gsl_vector_ulong_alloc(n), gsl_vector_ulong_free)
{
    if(gsl_vec == nullptr){
        throw std::runtime_error("Memory allocation (gsl_vector_ulong_alloc)"
        " failed!");
    }
    gsl_vector_ulong_set_all(gsl_vec.get(), v);
}

template<>
Vector_s::Vector_t
(const Vector_t::size_type n, const Vector_t::value_type v)
 : gsl_vec(gsl_vector_short_alloc(n), gsl_vector_short_free)
{
    if(gsl_vec == nullptr){
        throw std::runtime_error("Memory allocation (gsl_vector_short_alloc)"
        " failed!");
    }
    gsl_vector_short_set_all(gsl_vec.get(), v);
}

template<>
Vector_us::Vector_t
(const Vector_t::size_type n, const Vector_t::value_type v)
 : gsl_vec(gsl_vector_ushort_alloc(n), gsl_vector_ushort_free)
{
    if(gsl_vec == nullptr){
        throw std::runtime_error("Memory allocation (gsl_vector_ushort_alloc)"
        " failed!");
    }
    gsl_vector_ushort_set_all(gsl_vec.get(), v);
}

template<>
Vector_c::Vector_t
(const Vector_t::size_type n, const Vector_t::value_type v)
 : gsl_vec(gsl_vector_char_alloc(n), gsl_vector_char_free)
{
    if(gsl_vec == nullptr){
        throw std::runtime_error("Memory allocation (gsl_vector_char_alloc)"
        " failed!");
    }
    gsl_vector_char_set_all(gsl_vec.get(), v);
}

template<>
Vector_uc::Vector_t
(const Vector_t::size_type n, const Vector_t::value_type v)
 : gsl_vec(gsl_vector_uchar_alloc(n), gsl_vector_uchar_free)
{
    if(gsl_vec == nullptr){
        throw std::runtime_error("Memory allocation (gsl_vector_uchar_alloc)"
        " failed!");
    }
    gsl_vector_uchar_set_all(gsl_vec.get(), v);
}

template<>
Vector_cx::Vector_t
(const Vector_t::size_type n, const Vector_t::value_type v)
 : gsl_vec(gsl_vector_complex_alloc(n), gsl_vector_complex_free)
{
    if(gsl_vec == nullptr){
        throw std::runtime_error("Memory allocation (gsl_vector_complex_alloc)"
        " failed!");
    }
    gsl_vector_complex_set_all(gsl_vec.get(), v);
}

template<>
Vector_cxld::Vector_t
(const Vector_t::size_type n, const Vector_t::value_type v)
 : gsl_vec(gsl_vector_complex_long_double_alloc(n), gsl_vector_complex_long_double_free)
{
    if(gsl_vec == nullptr){
        throw std::runtime_error("Memory allocation (gsl_vector_complex_long_double_alloc)"
        " failed!");
    }
    gsl_vector_complex_long_double_set_all(gsl_vec.get(), v);
}

template<>
Vector_cxf::Vector_t
(const Vector_t::size_type n, const Vector_t::value_type v)
 : gsl_vec(gsl_vector_complex_float_alloc(n), gsl_vector_complex_float_free)
{
    if(gsl_vec == nullptr){
        throw std::runtime_error("Memory allocation (gsl_vector_complex_float_alloc)"
        " failed!");
    }
    gsl_vector_complex_float_set_all(gsl_vec.get(), v);
}

template<>
Vector::Vector_t(std::initializer_list<double> l)
 : gsl_vec(gsl_vector_alloc(l.size()), gsl_vector_free)
{
    auto current = l.begin();
    for(size_t i = 0; i < l.size(); i++){
        gsl_vector_set(gsl_vec.get(), i, *current);
        current++;
    }
}

template<>
Vector_ld::Vector_t(std::initializer_list<long double> l)
 : gsl_vec(gsl_vector_long_double_alloc(l.size()), gsl_vector_long_double_free)
{
    auto current = l.begin();
    for(size_t i = 0; i < l.size(); i++){
        gsl_vector_long_double_set(gsl_vec.get(), i, *current);
        current++;
    }
}

template<>
Vector_f::Vector_t(std::initializer_list<float> l)
 : gsl_vec(gsl_vector_float_alloc(l.size()), gsl_vector_float_free)
{
    auto current = l.begin();
    for(size_t i = 0; i < l.size(); i++){
        gsl_vector_float_set(gsl_vec.get(), i, *current);
        current++;
    }
}

template<>
Vector_i::Vector_t(std::initializer_list<int> l)
 : gsl_vec(gsl_vector_int_alloc(l.size()), gsl_vector_int_free)
{
    auto current = l.begin();
    for(size_t i = 0; i < l.size(); i++){
        gsl_vector_int_set(gsl_vec.get(), i, *current);
        current++;
    }
}

template<>
Vector_ui::Vector_t(std::initializer_list<unsigned int> l)
 : gsl_vec(gsl_vector_uint_alloc(l.size()), gsl_vector_uint_free)
{
    auto current = l.begin();
    for(size_t i = 0; i < l.size(); i++){
        gsl_vector_uint_set(gsl_vec.get(), i, *current);
        current++;
    }
}

template<>
Vector_l::Vector_t(std::initializer_list<long> l)
 : gsl_vec(gsl_vector_long_alloc(l.size()), gsl_vector_long_free)
{
    auto current = l.begin();
    for(size_t i = 0; i < l.size(); i++){
        gsl_vector_long_set(gsl_vec.get(), i, *current);
        current++;
    }
}

template<>
Vector_ul::Vector_t(std::initializer_list<unsigned long> l)
 : gsl_vec(gsl_vector_ulong_alloc(l.size()), gsl_vector_ulong_free)
{
    auto current = l.begin();
    for(size_t i = 0; i < l.size(); i++){
        gsl_vector_ulong_set(gsl_vec.get(), i, *current);
        current++;
    }
}

template<>
Vector_s::Vector_t(std::initializer_list<short> l)
 : gsl_vec(gsl_vector_short_alloc(l.size()), gsl_vector_short_free)
{
    auto current = l.begin();
    for(size_t i = 0; i < l.size(); i++){
        gsl_vector_short_set(gsl_vec.get(), i, *current);
        current++;
    }
}

template<>
Vector_us::Vector_t(std::initializer_list<unsigned short> l)
 : gsl_vec(gsl_vector_ushort_alloc(l.size()), gsl_vector_ushort_free)
{
    auto current = l.begin();
    for(size_t i = 0; i < l.size(); i++){
        gsl_vector_ushort_set(gsl_vec.get(), i, *current);
        current++;
    }
}

template<>
Vector_c::Vector_t(std::initializer_list<char> l)
 : gsl_vec(gsl_vector_char_alloc(l.size()), gsl_vector_char_free)
{
    auto current = l.begin();
    for(size_t i = 0; i < l.size(); i++){
        gsl_vector_char_set(gsl_vec.get(), i, *current);
        current++;
    }
}

template<>
Vector_uc::Vector_t(std::initializer_list<unsigned char> l)
 : gsl_vec(gsl_vector_uchar_alloc(l.size()), gsl_vector_uchar_free)
{
    auto current = l.begin();
    for(size_t i = 0; i < l.size(); i++){
        gsl_vector_uchar_set(gsl_vec.get(), i, *current);
        current++;
    }
}

template<>
Vector_cx::
Vector_t(std::initializer_list<Complex> l)
 : gsl_vec(gsl_vector_complex_alloc(l.size()), gsl_vector_complex_free)
{
    auto current = l.begin();
    for(size_t i = 0; i < l.size(); i++){
        gsl_vector_complex_set(gsl_vec.get(), i, *current->gsl_c);
        current++;
    }
}

template<>
Vector_cxld::
Vector_t(std::initializer_list<Complex_ld> l)
 : gsl_vec(gsl_vector_complex_long_double_alloc(l.size()), gsl_vector_complex_long_double_free)
{
    auto current = l.begin();
    for(size_t i = 0; i < l.size(); i++){
        gsl_vector_complex_long_double_set(gsl_vec.get(), i, *current->gsl_c);
        current++;
    }
}

template<>
Vector_cxf::
Vector_t(std::initializer_list<Complex_f> l)
 : gsl_vec(gsl_vector_complex_float_alloc(l.size()), gsl_vector_complex_float_free)
{
    auto current = l.begin();
    for(size_t i = 0; i < l.size(); i++){
        gsl_vector_complex_float_set(gsl_vec.get(), i, *current->gsl_c.get());
        current++;
    }
}

template<class T, class GSL_VEC, class A>
Vector_t<T, GSL_VEC, A> Vector_t<T, GSL_VEC, A>::copy() const
{
    return *this;
}

template<>
Vector& Vector::copy(const Vector& a)
{
    if(this->gsl_vec.get() == nullptr){
        this->gsl_vec = std::shared_ptr<gsl_vector>(gsl_vector_alloc(a.size()), gsl_vector_free);
        if(this->gsl_vec.get() == nullptr){
            throw std::runtime_error("Error in vector allocation!");
        }
    }
    int stat = gsl_vector_memcpy(this->gsl_vec.get(), a.gsl_vec.get());
    if(stat){
		std::string error_str =   gsl_strerror(stat);
		throw std::runtime_error("Error in memory copying.\nGSL error: "
        + error_str);
	}
    return *this;
}

template<>
Vector_ld& Vector_ld::copy
(const Vector_ld& a)
{
    if(this->gsl_vec.get() == nullptr){
        this->gsl_vec = std::shared_ptr<gsl_vector_long_double>
            (gsl_vector_long_double_alloc(a.size()), gsl_vector_long_double_free);
        if(this->gsl_vec.get() == nullptr){
            throw std::runtime_error("Error in vector allocation!");
        }
    }
    int stat = gsl_vector_long_double_memcpy(this->gsl_vec.get(), a.gsl_vec.get());
    if(stat){
		std::string error_str =   gsl_strerror(stat);
		throw std::runtime_error("Error in memory copying.\nGSL error: "
        + error_str);
	}
    return *this;
}

template<>
Vector_f& Vector_f::copy
(const Vector_f& a)
{
    if(this->gsl_vec.get() == nullptr){
        this->gsl_vec = std::shared_ptr<gsl_vector_float>
            (gsl_vector_float_alloc(a.size()), gsl_vector_float_free);
        if(this->gsl_vec.get() == nullptr){
            throw std::runtime_error("Error in vector allocation!");
        }
    }
    int stat = gsl_vector_float_memcpy(this->gsl_vec.get(), a.gsl_vec.get());
    if(stat){
		std::string error_str =   gsl_strerror(stat);
		throw std::runtime_error("Error in memory copying.\nGSL error: "
        + error_str);
	}
    return *this;
}

template<>
Vector_i& Vector_i::copy
(const Vector_i& a)
{
    if(this->gsl_vec.get() == nullptr){
        this->gsl_vec = std::shared_ptr<gsl_vector_int>
            (gsl_vector_int_alloc(a.size()), gsl_vector_int_free);
        if(this->gsl_vec.get() == nullptr){
            throw std::runtime_error("Error in vector allocation!");
        }
    }
    int stat = gsl_vector_int_memcpy(this->gsl_vec.get(), a.gsl_vec.get());
    if(stat){
		std::string error_str =   gsl_strerror(stat);
		throw std::runtime_error("Error in memory copying.\nGSL error: "
        + error_str);
	}
    return *this;
}

template<>
Vector_ui& Vector_ui::copy
(const Vector_ui& a)
{
    if(this->gsl_vec.get() == nullptr){
        this->gsl_vec = std::shared_ptr<gsl_vector_uint>
            (gsl_vector_uint_alloc(a.size()), gsl_vector_uint_free);
        if(this->gsl_vec.get() == nullptr){
            throw std::runtime_error("Error in vector allocation!");
        }
    }
    int stat = gsl_vector_uint_memcpy(this->gsl_vec.get(), a.gsl_vec.get());
    if(stat){
		std::string error_str =   gsl_strerror(stat);
		throw std::runtime_error("Error in memory copying.\nGSL error: "
        + error_str);
	}
    return *this;
}

template<>
Vector_l& Vector_l::copy
(const Vector_l& a)
{
    if(this->gsl_vec.get() == nullptr){
        this->gsl_vec = std::shared_ptr<gsl_vector_long>
            (gsl_vector_long_alloc(a.size()), gsl_vector_long_free);
        if(this->gsl_vec.get() == nullptr){
            throw std::runtime_error("Error in vector allocation!");
        }
    }
    int stat = gsl_vector_long_memcpy(this->gsl_vec.get(), a.gsl_vec.get());
    if(stat){
		std::string error_str =   gsl_strerror(stat);
		throw std::runtime_error("Error in memory copying.\nGSL error: "
        + error_str);
	}
    return *this;
}

template<>
Vector_ul& Vector_ul::copy
(const Vector_ul& a)
{
    if(this->gsl_vec.get() == nullptr){
        this->gsl_vec = std::shared_ptr<gsl_vector_ulong>
            (gsl_vector_ulong_alloc(a.size()), gsl_vector_ulong_free);
        if(this->gsl_vec.get() == nullptr){
            throw std::runtime_error("Error in vector allocation!");
        }
    }
    int stat = gsl_vector_ulong_memcpy(this->gsl_vec.get(), a.gsl_vec.get());
    if(stat){
		std::string error_str =   gsl_strerror(stat);
		throw std::runtime_error("Error in memory copying.\nGSL error: "
        + error_str);
	}
    return *this;
}

template<>
Vector_s& Vector_s::copy
(const Vector_s& a)
{
    if(this->gsl_vec.get() == nullptr){
        this->gsl_vec = std::shared_ptr<gsl_vector_short>
            (gsl_vector_short_alloc(a.size()), gsl_vector_short_free);
        if(this->gsl_vec.get() == nullptr){
            throw std::runtime_error("Error in vector allocation!");
        }
    }
    int stat = gsl_vector_short_memcpy(this->gsl_vec.get(), a.gsl_vec.get());
    if(stat){
		std::string error_str =   gsl_strerror(stat);
		throw std::runtime_error("Error in memory copying.\nGSL error: "
        + error_str);
	}
    return *this;
}

template<>
Vector_us& Vector_us::copy
(const Vector_us& a)
{
    if(this->gsl_vec.get() == nullptr){
        this->gsl_vec = std::shared_ptr<gsl_vector_ushort>
            (gsl_vector_ushort_alloc(a.size()), gsl_vector_ushort_free);
        if(this->gsl_vec.get() == nullptr){
            throw std::runtime_error("Error in vector allocation!");
        }
    }
    int stat = gsl_vector_ushort_memcpy(this->gsl_vec.get(), a.gsl_vec.get());
    if(stat){
		std::string error_str =   gsl_strerror(stat);
		throw std::runtime_error("Error in memory copying.\nGSL error: "
        + error_str);
	}
    return *this;
}

template<>
Vector_c& Vector_c::copy
(const Vector_c& a)
{
    if(this->gsl_vec.get() == nullptr){
        this->gsl_vec = std::shared_ptr<gsl_vector_char>
            (gsl_vector_char_alloc(a.size()), gsl_vector_char_free);
        if(this->gsl_vec.get() == nullptr){
            throw std::runtime_error("Error in vector allocation!");
        }
    }
    int stat = gsl_vector_char_memcpy(this->gsl_vec.get(), a.gsl_vec.get());
    if(stat){
		std::string error_str =   gsl_strerror(stat);
		throw std::runtime_error("Error in memory copying.\nGSL error: "
        + error_str);
	}
    return *this;
}

template<>
Vector_uc& Vector_uc::copy
(const Vector_uc& a)
{
    if(this->gsl_vec.get() == nullptr){
        this->gsl_vec = std::shared_ptr<gsl_vector_uchar>
            (gsl_vector_uchar_alloc(a.size()), gsl_vector_uchar_free);
        if(this->gsl_vec.get() == nullptr){
            throw std::runtime_error("Error in vector allocation!");
        }
    }
    int stat = gsl_vector_uchar_memcpy(this->gsl_vec.get(), a.gsl_vec.get());
    if(stat){
		std::string error_str =   gsl_strerror(stat);
		throw std::runtime_error("Error in memory copying.\nGSL error: "
        + error_str);
	}
    return *this;
}

template<>
Vector_cx& Vector_cx::copy
(const Vector_cx& a)
{
    if(this->gsl_vec.get() == nullptr){
        this->gsl_vec = std::shared_ptr<gsl_vector_complex>
            (gsl_vector_complex_alloc(a.size()), gsl_vector_complex_free);
        if(this->gsl_vec.get() == nullptr){
            throw std::runtime_error("Error in vector allocation!");
        }
    }
    int stat = gsl_vector_complex_memcpy(this->gsl_vec.get(), a.gsl_vec.get());
    if(stat){
		std::string error_str =   gsl_strerror(stat);
		throw std::runtime_error("Error in memory copying.\nGSL error: "
        + error_str);
	}
    return *this;
}

template<>
Vector_cxld& Vector_cxld::copy
(const Vector_cxld& a)
{
    if(this->gsl_vec.get() == nullptr){
        this->gsl_vec = std::shared_ptr<gsl_vector_complex_long_double>
            (gsl_vector_complex_long_double_alloc(a.size()), gsl_vector_complex_long_double_free);
        if(this->gsl_vec.get() == nullptr){
            throw std::runtime_error("Error in vector allocation!");
        }
    }
    int stat = gsl_vector_complex_long_double_memcpy(this->gsl_vec.get(), a.gsl_vec.get());
    if(stat){
		std::string error_str =   gsl_strerror(stat);
		throw std::runtime_error("Error in memory copying.\nGSL error: "
        + error_str);
	}
    return *this;
}

template<>
Vector_cxf& Vector_cxf::copy
(const Vector_cxf& a)
{
    if(this->gsl_vec.get() == nullptr){
        this->gsl_vec = std::shared_ptr<gsl_vector_complex_float>
            (gsl_vector_complex_float_alloc(a.size()), gsl_vector_complex_float_free);
        if(this->gsl_vec.get() == nullptr){
            throw std::runtime_error("Error in vector allocation!");
        }
    }
    int stat = gsl_vector_complex_float_memcpy(this->gsl_vec.get(), a.gsl_vec.get());
    if(stat){
		std::string error_str =   gsl_strerror(stat);
		throw std::runtime_error("Error in memory copying.\nGSL error: "
        + error_str);
	}
    return *this;
}

template <class T, class V, class A>
T Vector_t<T, V, A>::dot(const Vector_t<T, V, A>& b) const
{
    if(this->size() != b.size()){
        throw std::runtime_error("Error in dot. Dimensions of vectors do not match!\n");
    }
    T res(0);
    for(size_type i = 0; i < this->size(); i++){
        res = static_cast<T>(res + T{(*this)[i]}*T{b[i]});
    }
    return res;
}

template<>
double Vector::dot(const Vector& b) const
{
    if(this->size() != b.size()){
        throw std::runtime_error("Error in dot. Dimensions of vectors do not match!\n");
    }
    double res;
    int stat = gsl_blas_ddot(this->gsl_vec.get(), b.gsl_vec.get(), &res);
    if(stat){
		std::string error_str =   gsl_strerror(stat);
		throw std::runtime_error("Error in vector dot product.\nGSL error: "
        + error_str);
	}
    return res;
}

template<>
float Vector_f::dot(const Vector_f& b) const
{
    if(this->size() != b.size()){
        throw std::runtime_error("Error in dot. Dimensions of vectors do not match!\n");
    }
    float res;
    int stat = gsl_blas_sdot(this->gsl_vec.get(), b.gsl_vec.get(), &res);
    if(stat){
		std::string error_str =   gsl_strerror(stat);
		throw std::runtime_error("Error in vector dot product.\nGSL error: "
        + error_str);
	}
    return res;
}

template<>
Complex Vector_cx::dot(const Vector_cx& b) const
{
    if(this->size() != b.size()){
        throw std::runtime_error("Error in dot. Dimensions of vectors do not match!\n");
    }
    Complex res;
    int stat = gsl_blas_zdotu(this->gsl_vec.get(), b.gsl_vec.get(), res.gsl_c.get());
    if(stat){
		std::string error_str =   gsl_strerror(stat);
		throw std::runtime_error("Error in vector dot product.\nGSL error: "
        + error_str);
	}
    return res;
}

template<>
Complex_f Vector_cxf::dot(const Vector_cxf& b) const
{
    if(this->size() != b.size()){
        throw std::runtime_error("Error in dot. Dimensions of vectors do not match!\n");
    }
    Complex_f res;
    int stat = gsl_blas_cdotu(this->gsl_vec.get(), b.gsl_vec.get(), res.gsl_c.get());
    if(stat){
		std::string error_str =   gsl_strerror(stat);
		throw std::runtime_error("Error in vector dot product.\nGSL error: "
        + error_str);
	}
    return res;
}

template<class T, class G, class A> template<class S>
S Vector_t<T, G, A>::norm() const
{
    return std::sqrt(this->norm2<S>());
}

template<> template<>
double Vector::norm<double>() const
{
    return gsl_blas_dnrm2(this->gsl_vec.get());
}

template<> template<>
float Vector_f::norm<float>() const
{
    return gsl_blas_snrm2(this->gsl_vec.get());
}

template<> template<>
double Vector_cx::norm<double>() const
{
    return gsl_blas_dznrm2(this->gsl_vec.get());
}

template<> template<>
float Vector_cxf::norm<float>() const
{
    return gsl_blas_scnrm2(this->gsl_vec.get());
}

template<> template<>
long double Vector_cxld::norm<long double>() const
{
    Complex_ld tmp;
    long double n{0};
    for(Vector_cxld::size_type i = 0; i < this->gsl_vec->size; i++){
        tmp = (*this)[i];
        n += tmp.re()*tmp.re() + tmp.im()*tmp.im();
    }
    return std::sqrt(n);
}

template<>
Vector& Vector::operator+=(const Vector& b)
{
    int stat = gsl_vector_add(this->gsl_vec.get(), b.gsl_vec.get());
    if(stat){
		std::string error_str =   gsl_strerror(stat);
		throw std::runtime_error("Error in vector addition.\nGSL error: "
        + error_str);
	}
    return *this;
}

template<>
Vector_ld& Vector_ld::operator+=(const Vector_ld& b)
{
    int stat = gsl_vector_long_double_add(this->gsl_vec.get(), b.gsl_vec.get());
    if(stat){
		std::string error_str =   gsl_strerror(stat);
		throw std::runtime_error("Error in vector addition.\nGSL error: "
        + error_str);
	}
    return *this;
}

template<>
Vector_f& Vector_f::operator+=(const Vector_f& b)
{
    int stat = gsl_vector_float_add(this->gsl_vec.get(), b.gsl_vec.get());
    if(stat){
		std::string error_str =   gsl_strerror(stat);
		throw std::runtime_error("Error in vector addition.\nGSL error: "
        + error_str);
	}
    return *this;
}

template<>
Vector_i& Vector_i::operator+=(const Vector_i& b)
{
    int stat = gsl_vector_int_add(this->gsl_vec.get(), b.gsl_vec.get());
    if(stat){
		std::string error_str =   gsl_strerror(stat);
		throw std::runtime_error("Error in vector addition.\nGSL error: "
        + error_str);
	}
    return *this;
}

template<>
Vector_ui& Vector_ui::operator+=(const Vector_ui& b)
{
    int stat = gsl_vector_uint_add(this->gsl_vec.get(), b.gsl_vec.get());
    if(stat){
		std::string error_str =   gsl_strerror(stat);
		throw std::runtime_error("Error in vector addition.\nGSL error: "
        + error_str);
	}
    return *this;
}

template<>
Vector_l& Vector_l::operator+=(const Vector_l& b)
{
    int stat = gsl_vector_long_add(this->gsl_vec.get(), b.gsl_vec.get());
    if(stat){
		std::string error_str =   gsl_strerror(stat);
		throw std::runtime_error("Error in vector addition.\nGSL error: "
        + error_str);
	}
    return *this;
}

template<>
Vector_ul& Vector_ul::operator+=(const Vector_ul& b)
{
    int stat = gsl_vector_ulong_add(this->gsl_vec.get(), b.gsl_vec.get());
    if(stat){
		std::string error_str =   gsl_strerror(stat);
		throw std::runtime_error("Error in vector addition.\nGSL error: "
        + error_str);
	}
    return *this;
}

template<>
Vector_s& Vector_s::operator+=(const Vector_s& b)
{
    int stat = gsl_vector_short_add(this->gsl_vec.get(), b.gsl_vec.get());
    if(stat){
		std::string error_str =   gsl_strerror(stat);
		throw std::runtime_error("Error in vector addition.\nGSL error: "
        + error_str);
	}
    return *this;
}

template<>
Vector_us& Vector_us::operator+=(const Vector_us& b)
{
    int stat = gsl_vector_ushort_add(this->gsl_vec.get(), b.gsl_vec.get());
    if(stat){
		std::string error_str =   gsl_strerror(stat);
		throw std::runtime_error("Error in vector addition.\nGSL error: "
        + error_str);
	}
    return *this;
}


template<>
Vector_c& Vector_c::operator+=(const Vector_c& b)
{
    int stat = gsl_vector_char_add(this->gsl_vec.get(), b.gsl_vec.get());
    if(stat){
		std::string error_str =   gsl_strerror(stat);
		throw std::runtime_error("Error in vector addition.\nGSL error: "
        + error_str);
	}
    return *this;
}

template<>
Vector_uc& Vector_uc::operator+=(const Vector_uc& b)
{
    int stat = gsl_vector_uchar_add(this->gsl_vec.get(), b.gsl_vec.get());
    if(stat){
		std::string error_str =   gsl_strerror(stat);
		throw std::runtime_error("Error in vector addition.\nGSL error: "
        + error_str);
	}
    return *this;
}

template<>
Vector_cx& Vector_cx::operator+=(const Vector_cx& b)
{
    int stat = gsl_vector_complex_add(this->gsl_vec.get(), b.gsl_vec.get());
    if(stat){
		std::string error_str =   gsl_strerror(stat);
		throw std::runtime_error("Error in vector addition.\nGSL error: "
        + error_str);
	}
    return *this;
}

template<>
Vector_cxld& Vector_cxld::operator+=(const Vector_cxld& b)
{
    int stat = gsl_vector_complex_long_double_add(this->gsl_vec.get(), b.gsl_vec.get());
    if(stat){
		std::string error_str =   gsl_strerror(stat);
		throw std::runtime_error("Error in vector addition.\nGSL error: "
        + error_str);
	}
    return *this;
}

template<>
Vector_cxf& Vector_cxf::operator+=(const Vector_cxf& b)
{
    int stat = gsl_vector_complex_float_add(this->gsl_vec.get(), b.gsl_vec.get());
    if(stat){
		std::string error_str =   gsl_strerror(stat);
		throw std::runtime_error("Error in vector addition.\nGSL error: "
        + error_str);
	}
    return *this;
}

template<>
Vector& Vector::operator-=(const Vector& b)
{
    int stat = gsl_vector_sub(this->gsl_vec.get(), b.gsl_vec.get());
    if(stat){
		std::string error_str =   gsl_strerror(stat);
		throw std::runtime_error("Error in vector addition.\nGSL error: "
        + error_str);
	}
    return *this;
}

template<>
Vector_ld& Vector_ld::operator-=(const Vector_ld& b)
{
    int stat = gsl_vector_long_double_sub(this->gsl_vec.get(), b.gsl_vec.get());
    if(stat){
		std::string error_str = gsl_strerror(stat);
		throw std::runtime_error("Error in vector addition.\nGSL error: "
        + error_str);
	}
    return *this;
}

template<>
Vector_f& Vector_f::operator-=(const Vector_f& b)
{
    int stat = gsl_vector_float_sub(this->gsl_vec.get(), b.gsl_vec.get());
    if(stat){
		std::string error_str =   gsl_strerror(stat);
		throw std::runtime_error("Error in vector addition.\nGSL error: "
        + error_str);
	}
    return *this;
}

template<>
Vector_i& Vector_i::operator-=(const Vector_i& b)
{
    int stat = gsl_vector_int_sub(this->gsl_vec.get(), b.gsl_vec.get());
    if(stat){
		std::string error_str =   gsl_strerror(stat);
		throw std::runtime_error("Error in vector addition.\nGSL error: "
        + error_str);
	}
    return *this;
}

template<>
Vector_ui& Vector_ui::operator-=(const Vector_ui& b)
{
    int stat = gsl_vector_uint_sub(this->gsl_vec.get(), b.gsl_vec.get());
    if(stat){
		std::string error_str =   gsl_strerror(stat);
		throw std::runtime_error("Error in vector addition.\nGSL error: "
        + error_str);
	}
    return *this;
}

template<>
Vector_l& Vector_l::operator-=(const Vector_l& b)
{
    int stat = gsl_vector_long_sub(this->gsl_vec.get(), b.gsl_vec.get());
    if(stat){
		std::string error_str =   gsl_strerror(stat);
		throw std::runtime_error("Error in vector addition.\nGSL error: "
        + error_str);
	}
    return *this;
}

template<>
Vector_ul& Vector_ul::operator-=(const Vector_ul& b)
{
    int stat = gsl_vector_ulong_sub(this->gsl_vec.get(), b.gsl_vec.get());
    if(stat){
		std::string error_str =   gsl_strerror(stat);
		throw std::runtime_error("Error in vector addition.\nGSL error: "
        + error_str);
	}
    return *this;
}

template<>
Vector_s& Vector_s::operator-=(const Vector_s& b)
{
    int stat = gsl_vector_short_sub(this->gsl_vec.get(), b.gsl_vec.get());
    if(stat){
		std::string error_str =   gsl_strerror(stat);
		throw std::runtime_error("Error in vector addition.\nGSL error: "
        + error_str);
	}
    return *this;
}

template<>
Vector_us& Vector_us::operator-=(const Vector_us& b)
{
    int stat = gsl_vector_ushort_sub(this->gsl_vec.get(), b.gsl_vec.get());
    if(stat){
		std::string error_str =   gsl_strerror(stat);
		throw std::runtime_error("Error in vector addition.\nGSL error: "
        + error_str);
	}
    return *this;
}


template<>
Vector_c& Vector_c::operator-=(const Vector_c& b)
{
    int stat = gsl_vector_char_sub(this->gsl_vec.get(), b.gsl_vec.get());
    if(stat){
		std::string error_str =   gsl_strerror(stat);
		throw std::runtime_error("Error in vector addition.\nGSL error: "
        + error_str);
	}
    return *this;
}

template<>
Vector_uc& Vector_uc::operator-=(const Vector_uc& b)
{
    int stat = gsl_vector_uchar_sub(this->gsl_vec.get(), b.gsl_vec.get());
    if(stat){
		std::string error_str =   gsl_strerror(stat);
		throw std::runtime_error("Error in vector addition.\nGSL error: "
        + error_str);
	}
    return *this;
}

template<>
Vector_cx& Vector_cx::operator-=(const Vector_cx& b)
{
    int stat = gsl_vector_complex_sub(this->gsl_vec.get(), b.gsl_vec.get());
    if(stat){
		std::string error_str =   gsl_strerror(stat);
		throw std::runtime_error("Error in vector addition.\nGSL error: "
        + error_str);
	}
    return *this;
}

template<>
Vector_cxld& Vector_cxld::operator-=(const Vector_cxld& b)
{
    int stat = gsl_vector_complex_long_double_sub(this->gsl_vec.get(), b.gsl_vec.get());
    if(stat){
		std::string error_str =   gsl_strerror(stat);
		throw std::runtime_error("Error in vector addition.\nGSL error: "
        + error_str);
	}
    return *this;
}

template<>
Vector_cxf& Vector_cxf::operator-=(const Vector_cxf& b)
{
    int stat = gsl_vector_complex_float_sub(this->gsl_vec.get(), b.gsl_vec.get());
    if(stat){
		std::string error_str =   gsl_strerror(stat);
		throw std::runtime_error("Error in vector addition.\nGSL error: "
        + error_str);
	}
    return *this;
}

template<>
Vector& Vector::operator*=(const Vector& b)
{
    int stat = gsl_vector_mul(this->gsl_vec.get(), b.gsl_vec.get());
    if(stat){
		std::string error_str =   gsl_strerror(stat);
		throw std::runtime_error("Error in vector addition.\nGSL error: "
        + error_str);
	}
    return *this;
}

template<>
Vector_ld& Vector_ld::operator*=(const Vector_ld& b)
{
    int stat = gsl_vector_long_double_mul(this->gsl_vec.get(), b.gsl_vec.get());
    if(stat){
		std::string error_str = gsl_strerror(stat);
		throw std::runtime_error("Error in vector addition.\nGSL error: "
        + error_str);
	}
    return *this;
}

template<>
Vector_f& Vector_f::operator*=(const Vector_f& b)
{
    int stat = gsl_vector_float_mul(this->gsl_vec.get(), b.gsl_vec.get());
    if(stat){
		std::string error_str =   gsl_strerror(stat);
		throw std::runtime_error("Error in vector addition.\nGSL error: "
        + error_str);
	}
    return *this;
}

template<>
Vector_i& Vector_i::operator*=(const Vector_i& b)
{
    int stat = gsl_vector_int_mul(this->gsl_vec.get(), b.gsl_vec.get());
    if(stat){
		std::string error_str =   gsl_strerror(stat);
		throw std::runtime_error("Error in vector addition.\nGSL error: "
        + error_str);
	}
    return *this;
}

template<>
Vector_ui& Vector_ui::operator*=(const Vector_ui& b)
{
    int stat = gsl_vector_uint_mul(this->gsl_vec.get(), b.gsl_vec.get());
    if(stat){
		std::string error_str =   gsl_strerror(stat);
		throw std::runtime_error("Error in vector addition.\nGSL error: "
        + error_str);
	}
    return *this;
}

template<>
Vector_l& Vector_l::operator*=(const Vector_l& b)
{
    int stat = gsl_vector_long_mul(this->gsl_vec.get(), b.gsl_vec.get());
    if(stat){
		std::string error_str =   gsl_strerror(stat);
		throw std::runtime_error("Error in vector addition.\nGSL error: "
        + error_str);
	}
    return *this;
}

template<>
Vector_ul& Vector_ul::operator*=(const Vector_ul& b)
{
    int stat = gsl_vector_ulong_mul(this->gsl_vec.get(), b.gsl_vec.get());
    if(stat){
		std::string error_str =   gsl_strerror(stat);
		throw std::runtime_error("Error in vector addition.\nGSL error: "
        + error_str);
	}
    return *this;
}

template<>
Vector_s& Vector_s::operator*=(const Vector_s& b)
{
    int stat = gsl_vector_short_mul(this->gsl_vec.get(), b.gsl_vec.get());
    if(stat){
		std::string error_str =   gsl_strerror(stat);
		throw std::runtime_error("Error in vector addition.\nGSL error: "
        + error_str);
	}
    return *this;
}

template<>
Vector_us& Vector_us::operator*=(const Vector_us& b)
{
    int stat = gsl_vector_ushort_mul(this->gsl_vec.get(), b.gsl_vec.get());
    if(stat){
		std::string error_str =   gsl_strerror(stat);
		throw std::runtime_error("Error in vector addition.\nGSL error: "
        + error_str);
	}
    return *this;
}


template<>
Vector_c& Vector_c::operator*=(const Vector_c& b)
{
    int stat = gsl_vector_char_mul(this->gsl_vec.get(), b.gsl_vec.get());
    if(stat){
		std::string error_str =   gsl_strerror(stat);
		throw std::runtime_error("Error in vector addition.\nGSL error: "
        + error_str);
	}
    return *this;
}

template<>
Vector_uc& Vector_uc::operator*=(const Vector_uc& b)
{
    int stat = gsl_vector_uchar_mul(this->gsl_vec.get(), b.gsl_vec.get());
    if(stat){
		std::string error_str =   gsl_strerror(stat);
		throw std::runtime_error("Error in vector addition.\nGSL error: "
        + error_str);
	}
    return *this;
}

template<>
Vector_cx& Vector_cx::operator*=(const Vector_cx& b)
{
    int stat = gsl_vector_complex_mul(this->gsl_vec.get(), b.gsl_vec.get());
    if(stat){
		std::string error_str =   gsl_strerror(stat);
		throw std::runtime_error("Error in vector addition.\nGSL error: "
        + error_str);
	}
    return *this;
}

template<>
Vector_cxld& Vector_cxld::operator*=(const Vector_cxld& b)
{
    int stat = gsl_vector_complex_long_double_mul(this->gsl_vec.get(), b.gsl_vec.get());
    if(stat){
		std::string error_str =   gsl_strerror(stat);
		throw std::runtime_error("Error in vector addition.\nGSL error: "
        + error_str);
	}
    return *this;
}

template<>
Vector_cxf& Vector_cxf::operator*=(const Vector_cxf& b)
{
    int stat = gsl_vector_complex_float_mul(this->gsl_vec.get(), b.gsl_vec.get());
    if(stat){
		std::string error_str =   gsl_strerror(stat);
		throw std::runtime_error("Error in vector addition.\nGSL error: "
        + error_str);
	}
    return *this;
}

template<>
Vector& Vector::operator/=(const Vector& b)
{
    int stat = gsl_vector_div(this->gsl_vec.get(), b.gsl_vec.get());
    if(stat){
		std::string error_str =   gsl_strerror(stat);
		throw std::runtime_error("Error in vector addition.\nGSL error: "
        + error_str);
	}
    return *this;
}

template<>
Vector_ld& Vector_ld::operator/=(const Vector_ld& b)
{
    int stat = gsl_vector_long_double_div(this->gsl_vec.get(), b.gsl_vec.get());
    if(stat){
		std::string error_str = gsl_strerror(stat);
		throw std::runtime_error("Error in vector addition.\nGSL error: "
        + error_str);
	}
    return *this;
}

template<>
Vector_f& Vector_f::operator/=(const Vector_f& b)
{
    int stat = gsl_vector_float_div(this->gsl_vec.get(), b.gsl_vec.get());
    if(stat){
		std::string error_str =   gsl_strerror(stat);
		throw std::runtime_error("Error in vector addition.\nGSL error: "
        + error_str);
	}
    return *this;
}

template<>
Vector_i& Vector_i::operator/=(const Vector_i& b)
{
    int stat = gsl_vector_int_div(this->gsl_vec.get(), b.gsl_vec.get());
    if(stat){
		std::string error_str =   gsl_strerror(stat);
		throw std::runtime_error("Error in vector addition.\nGSL error: "
        + error_str);
	}
    return *this;
}

template<>
Vector_ui& Vector_ui::operator/=(const Vector_ui& b)
{
    int stat = gsl_vector_uint_div(this->gsl_vec.get(), b.gsl_vec.get());
    if(stat){
		std::string error_str =   gsl_strerror(stat);
		throw std::runtime_error("Error in vector addition.\nGSL error: "
        + error_str);
	}
    return *this;
}

template<>
Vector_l& Vector_l::operator/=(const Vector_l& b)
{
    int stat = gsl_vector_long_div(this->gsl_vec.get(), b.gsl_vec.get());
    if(stat){
		std::string error_str =   gsl_strerror(stat);
		throw std::runtime_error("Error in vector addition.\nGSL error: "
        + error_str);
	}
    return *this;
}

template<>
Vector_ul& Vector_ul::operator/=(const Vector_ul& b)
{
    int stat = gsl_vector_ulong_div(this->gsl_vec.get(), b.gsl_vec.get());
    if(stat){
		std::string error_str =   gsl_strerror(stat);
		throw std::runtime_error("Error in vector addition.\nGSL error: "
        + error_str);
	}
    return *this;
}

template<>
Vector_s& Vector_s::operator/=(const Vector_s& b)
{
    int stat = gsl_vector_short_div(this->gsl_vec.get(), b.gsl_vec.get());
    if(stat){
		std::string error_str =   gsl_strerror(stat);
		throw std::runtime_error("Error in vector addition.\nGSL error: "
        + error_str);
	}
    return *this;
}

template<>
Vector_us& Vector_us::operator/=(const Vector_us& b)
{
    int stat = gsl_vector_ushort_div(this->gsl_vec.get(), b.gsl_vec.get());
    if(stat){
		std::string error_str =   gsl_strerror(stat);
		throw std::runtime_error("Error in vector addition.\nGSL error: "
        + error_str);
	}
    return *this;
}


template<>
Vector_c& Vector_c::operator/=(const Vector_c& b)
{
    int stat = gsl_vector_char_div(this->gsl_vec.get(), b.gsl_vec.get());
    if(stat){
		std::string error_str =   gsl_strerror(stat);
		throw std::runtime_error("Error in vector addition.\nGSL error: "
        + error_str);
	}
    return *this;
}

template<>
Vector_uc& Vector_uc::operator/=(const Vector_uc& b)
{
    int stat = gsl_vector_uchar_div(this->gsl_vec.get(), b.gsl_vec.get());
    if(stat){
		std::string error_str =   gsl_strerror(stat);
		throw std::runtime_error("Error in vector addition.\nGSL error: "
        + error_str);
	}
    return *this;
}

template<>
Vector_cx& Vector_cx::operator/=(const Vector_cx& b)
{
    int stat = gsl_vector_complex_div(this->gsl_vec.get(), b.gsl_vec.get());
    if(stat){
		std::string error_str =   gsl_strerror(stat);
		throw std::runtime_error("Error in vector addition.\nGSL error: "
        + error_str);
	}
    return *this;
}

template<>
Vector_cxld& Vector_cxld::operator/=(const Vector_cxld& b)
{
    int stat = gsl_vector_complex_long_double_div(this->gsl_vec.get(), b.gsl_vec.get());
    if(stat){
		std::string error_str =   gsl_strerror(stat);
		throw std::runtime_error("Error in vector addition.\nGSL error: "
        + error_str);
	}
    return *this;
}

template<>
Vector_cxf& Vector_cxf::operator/=(const Vector_cxf& b)
{
    int stat = gsl_vector_complex_float_div(this->gsl_vec.get(), b.gsl_vec.get());
    if(stat){
		std::string error_str =   gsl_strerror(stat);
		throw std::runtime_error("Error in vector addition.\nGSL error: "
        + error_str);
	}
    return *this;
}

template<>
Vector& Vector::operator*=(const double& b)
{
    int stat = gsl_vector_scale(this->gsl_vec.get(), b);
    if(stat){
		std::string error_str = gsl_strerror(stat);
		throw std::runtime_error("Error in vector addition.\nGSL error: "
        + error_str);
	}
    return *this;
}

template<>
Vector_ld& Vector_ld::operator*=(const long double& b)
{
    int stat = gsl_vector_long_double_scale(this->gsl_vec.get(), static_cast<double>(b));
    if(stat){
		std::string error_str = gsl_strerror(stat);
		throw std::runtime_error("Error in vector addition.\nGSL error: "
        + error_str);
	}
    return *this;
}

template<>
Vector_f& Vector_f::operator*=(const float& b)
{
    int stat = gsl_vector_float_scale(this->gsl_vec.get(), b);
    if(stat){
		std::string error_str = gsl_strerror(stat);
		throw std::runtime_error("Error in vector addition.\nGSL error: "
        + error_str);
	}
    return *this;
}

template<>
Vector_i& Vector_i::operator*=(const int& b)
{
    int stat = gsl_vector_int_scale(this->gsl_vec.get(), b);
    if(stat){
		std::string error_str = gsl_strerror(stat);
		throw std::runtime_error("Error in vector addition.\nGSL error: "
        + error_str);
	}
    return *this;
}

template<>
Vector_ui& Vector_ui::operator*=(const unsigned int& b)
{
    int stat = gsl_vector_uint_scale(this->gsl_vec.get(), b);
    if(stat){
		std::string error_str = gsl_strerror(stat);
		throw std::runtime_error("Error in vector addition.\nGSL error: "
        + error_str);
	}
    return *this;
}

template<>
Vector_l& Vector_l::operator*=(const long& b)
{
    int stat = gsl_vector_long_scale(this->gsl_vec.get(), b);
    if(stat){
		std::string error_str = gsl_strerror(stat);
		throw std::runtime_error("Error in vector addition.\nGSL error: "
        + error_str);
	}
    return *this;
}

template<>
Vector_ul& Vector_ul::operator*=(const unsigned long& b)
{
    int stat = gsl_vector_ulong_scale(this->gsl_vec.get(), b);
    if(stat){
		std::string error_str = gsl_strerror(stat);
		throw std::runtime_error("Error in vector addition.\nGSL error: "
        + error_str);
	}
    return *this;
}

template<>
Vector_s& Vector_s::operator*=(const short& b)
{
    int stat = gsl_vector_short_scale(this->gsl_vec.get(), b);
    if(stat){
		std::string error_str = gsl_strerror(stat);
		throw std::runtime_error("Error in vector addition.\nGSL error: "
        + error_str);
	}
    return *this;
}

template<>
Vector_us& Vector_us::operator*=(const unsigned short& b)
{
    int stat = gsl_vector_ushort_scale(this->gsl_vec.get(), b);
    if(stat){
		std::string error_str = gsl_strerror(stat);
		throw std::runtime_error("Error in vector addition.\nGSL error: "
        + error_str);
	}
    return *this;
}


template<>
Vector_c& Vector_c::operator*=(const char& b)
{
    int stat = gsl_vector_char_scale(this->gsl_vec.get(), b);
    if(stat){
		std::string error_str = gsl_strerror(stat);
		throw std::runtime_error("Error in vector addition.\nGSL error: "
        + error_str);
	}
    return *this;
}

template<>
Vector_uc& Vector_uc::operator*=(const unsigned char& b)
{
    int stat = gsl_vector_uchar_scale(this->gsl_vec.get(), b);
    if(stat){
		std::string error_str = gsl_strerror(stat);
		throw std::runtime_error("Error in vector addition.\nGSL error: "
        + error_str);
	}
    return *this;
}

template<>
Vector_cx& Vector_cx::operator*=(const Complex& b)
{
    int stat = gsl_vector_complex_scale(this->gsl_vec.get(), *b.gsl_c.get());
    if(stat){
		std::string error_str = gsl_strerror(stat);
		throw std::runtime_error("Error in vector addition.\nGSL error: "
        + error_str);
	}
    return *this;
}

template<>
Vector_cxld& Vector_cxld::operator*=(const Complex_ld& b)
{
    int stat = gsl_vector_complex_long_double_scale(this->gsl_vec.get(), *b.gsl_c.get());
    if(stat){
		std::string error_str = gsl_strerror(stat);
		throw std::runtime_error("Error in vector addition.\nGSL error: "
        + error_str);
	}
    return *this;
}

template<>
Vector_cxf& Vector_cxf::operator*=(const Complex_f& b)
{
    int stat = gsl_vector_complex_float_scale(this->gsl_vec.get(), *b.gsl_c.get());
    if(stat){
		std::string error_str = gsl_strerror(stat);
		throw std::runtime_error("Error in vector addition.\nGSL error: "
        + error_str);
	}
    return *this;
}

template<>
Vector& Vector::operator/=(const double& b)
{
    int stat = gsl_vector_scale(this->gsl_vec.get(), 1./b);
    if(stat){
		std::string error_str = gsl_strerror(stat);
		throw std::runtime_error("Error in vector addition.\nGSL error: "
        + error_str);
	}
    return *this;
}

template<>
Vector_ld& Vector_ld::operator/=(const long double& b)
{
    int stat = gsl_vector_long_double_scale(this->gsl_vec.get(), 1./static_cast<double>(b));
    if(stat){
		std::string error_str = gsl_strerror(stat);
		throw std::runtime_error("Error in vector addition.\nGSL error: "
        + error_str);
	}
    return *this;
}

template<>
Vector_f& Vector_f::operator/=(const float& b)
{
    int stat = gsl_vector_float_scale(this->gsl_vec.get(), static_cast<float>(1.)/b);
    if(stat){
		std::string error_str = gsl_strerror(stat);
		throw std::runtime_error("Error in vector addition.\nGSL error: "
        + error_str);
	}
    return *this;
}

template<>
Vector_i& Vector_i::operator/=(const int& b)
{
    Vector_i tmp(this->size());
    gsl_vector_int_set_all(tmp.gsl_vec.get(), b);
    int stat = gsl_vector_int_div(this->gsl_vec.get(), tmp.gsl_vec.get());
    if(stat){
		std::string error_str = gsl_strerror(stat);
		throw std::runtime_error("Error in vector addition.\nGSL error: "
        + error_str);
	}
    return *this;
}

template<>
Vector_ui& Vector_ui::operator/=(const unsigned int& b)
{
    Vector_ui tmp(this->size());
    gsl_vector_uint_set_all(tmp.gsl_vec.get(), b);
    int stat = gsl_vector_uint_div(this->gsl_vec.get(), tmp.gsl_vec.get());
    if(stat){
		std::string error_str =   gsl_strerror(stat);
		throw std::runtime_error("Error in vector addition.\nGSL error: "
        + error_str);
	}
    return *this;
}

template<>
Vector_l& Vector_l::operator/=(const long& b)
{
    Vector_l tmp(this->size());
    gsl_vector_long_set_all(tmp.gsl_vec.get(), b);
    int stat = gsl_vector_long_div(this->gsl_vec.get(), tmp.gsl_vec.get());
    if(stat){
		std::string error_str =   gsl_strerror(stat);
		throw std::runtime_error("Error in vector addition.\nGSL error: "
        + error_str);
	}
    return *this;
}

template<>
Vector_ul& Vector_ul::operator/=(const unsigned long& b)
{
    Vector_ul tmp(this->size());
    gsl_vector_ulong_set_all(tmp.gsl_vec.get(), b);
    int stat = gsl_vector_ulong_div(this->gsl_vec.get(), tmp.gsl_vec.get());
    if(stat){
		std::string error_str =   gsl_strerror(stat);
		throw std::runtime_error("Error in vector addition.\nGSL error: "
        + error_str);
	}
    return *this;
}

template<>
Vector_s& Vector_s::operator/=(const short& b)
{
    Vector_s tmp(this->size());
    gsl_vector_short_set_all(tmp.gsl_vec.get(), b);
    int stat = gsl_vector_short_div(this->gsl_vec.get(), tmp.gsl_vec.get());
    if(stat){
		std::string error_str =   gsl_strerror(stat);
		throw std::runtime_error("Error in vector addition.\nGSL error: "
        + error_str);
	}
    return *this;
}

template<>
Vector_us& Vector_us::operator/=(const unsigned short& b)
{
    Vector_us tmp(this->size());
    gsl_vector_ushort_set_all(tmp.gsl_vec.get(), b);
    int stat = gsl_vector_ushort_div(this->gsl_vec.get(), tmp.gsl_vec.get());
    if(stat){
		std::string error_str =   gsl_strerror(stat);
		throw std::runtime_error("Error in vector addition.\nGSL error: "
        + error_str);
	}
    return *this;
}


template<>
Vector_c& Vector_c::operator/=(const char& b)
{
    Vector_c tmp(this->size());
    gsl_vector_char_set_all(tmp.gsl_vec.get(), b);
    int stat = gsl_vector_char_div(this->gsl_vec.get(), tmp.gsl_vec.get());
    if(stat){
		std::string error_str =   gsl_strerror(stat);
		throw std::runtime_error("Error in vector addition.\nGSL error: "
        + error_str);
	}
    return *this;
}

template<>
Vector_uc& Vector_uc::operator/=(const unsigned char& b)
{
    Vector_uc tmp(this->size());
    gsl_vector_uchar_set_all(tmp.gsl_vec.get(), b);
    int stat = gsl_vector_uchar_div(this->gsl_vec.get(), tmp.gsl_vec.get());
    if(stat){
		std::string error_str =   gsl_strerror(stat);
		throw std::runtime_error("Error in vector addition.\nGSL error: "
        + error_str);
	}
    return *this;
}

template<>
Vector_cx& Vector_cx::operator/=(const Complex& b)
{
    int stat = gsl_vector_complex_scale(this->gsl_vec.get(), *(1./b).gsl_c);
    if(stat){
		std::string error_str =   gsl_strerror(stat);
		throw std::runtime_error("Error in vector addition.\nGSL error: "
        + error_str);
	}
    return *this;
}

template<>
Vector_cxld& Vector_cxld::operator/=(const Complex_ld& b)
{
    int stat = gsl_vector_complex_long_double_scale(this->gsl_vec.get(), *(static_cast<long double>(1.)/b).gsl_c);
    if(stat){
		std::string error_str =   gsl_strerror(stat);
		throw std::runtime_error("Error in vector addition.\nGSL error: "
        + error_str);
	}
    return *this;
}

template<>
Vector_cxf& Vector_cxf::operator/=(const Complex_f& b)
{
    int stat = gsl_vector_complex_float_scale(this->gsl_vec.get(), *(1./b).gsl_c);
    if(stat){
		std::string error_str =   gsl_strerror(stat);
		throw std::runtime_error("Error in vector addition.\nGSL error: "
        + error_str);
	}
    return *this;
}

template<> template<>
Vector Vector::operator*<gsl_matrix>(const Matrix_t<double, gsl_matrix, gsl_vector, std::allocator<double>>& m) const
{
    Vector res(m.size().first);
    int stat = gsl_blas_dgemv(CblasTrans, 1.0, m.gsl_mat.get(),
        this->gsl_vec.get(), 0.0, res.gsl_vec.get());
    if(stat){
		std::string error_str =   gsl_strerror(stat);
		throw std::runtime_error("Error in matrix-vector multiplication.\nGSL error: "
        + error_str);
	}

    return res;
}

template<> template<>
Vector_f Vector_f::operator*<gsl_matrix_float>(const Matrix_t<float, gsl_matrix_float, gsl_vector_float>& m) const
{
    Vector_f res(m.size().first);
    int stat = gsl_blas_sgemv(CblasTrans, 1.0, m.gsl_mat.get(),
        this->gsl_vec.get(), 0.0, res.gsl_vec.get());
    if(stat){
		std::string error_str =   gsl_strerror(stat);
		throw std::runtime_error("Error in matrix-vector multiplication.\nGSL error: "
        + error_str);
	}

    return res;
}

template<> template<>
Vector_cx Vector_cx::operator*<gsl_matrix_complex>(const Matrix_t<Complex, gsl_matrix_complex, gsl_vector_complex, std::allocator<gsl_complex>>& m) const
{
    Vector_cx res(m.size().first);
    int stat = gsl_blas_zgemv(CblasTrans, Complex(1.0), m.gsl_mat.get(),
        this->gsl_vec.get(), Complex(0.0), res.gsl_vec.get());
    if(stat){
		std::string error_str =   gsl_strerror(stat);
		throw std::runtime_error("Error in matrix-vector multiplication.\nGSL error: "
        + error_str);
	}

    return res;
}

template<> template<>
Vector_cxf Vector_cxf::operator*<gsl_matrix_complex_float>(const Matrix_t<Complex_f, gsl_matrix_complex_float, gsl_vector_complex_float, std::allocator<gsl_complex_float>>& m) const
{
    Vector_cxf res(m.size().first);
    int stat = gsl_blas_cgemv(CblasTrans, Complex_f(1.0), m.gsl_mat.get(),
        this->gsl_vec.get(), Complex_f(0.0), res.gsl_vec.get());
    if(stat){
		std::string error_str =   gsl_strerror(stat);
		throw std::runtime_error("Error in matrix-vector multiplication.\nGSL error: "
        + error_str);
	}

    return res;
}


template<>
bool Vector::operator==(const Vector& b) const
{
    if(this->gsl_vec.get() == nullptr && b.gsl_vec.get() == nullptr){
        return true;
    }else if(this->gsl_vec.get() == nullptr || b.gsl_vec.get() == nullptr){
        return false;
    }
    return gsl_vector_equal(this->gsl_vec.get(), b.gsl_vec.get());
}

template<>
bool Vector_ld::operator==(const Vector_ld& b) const
{
    if(this->gsl_vec.get() == nullptr && b.gsl_vec.get() == nullptr){
        return true;
    }else if(this->gsl_vec.get() == nullptr || b.gsl_vec.get() == nullptr){
        return false;
    }
    return gsl_vector_long_double_equal(this->gsl_vec.get(), b.gsl_vec.get());
}

template<>
bool Vector_f::operator==(const Vector_f& b) const
{
    if(this->gsl_vec.get() == nullptr && b.gsl_vec.get() == nullptr){
        return true;
    }else if(this->gsl_vec.get() == nullptr || b.gsl_vec.get() == nullptr){
        return false;
    }
    return gsl_vector_float_equal(this->gsl_vec.get(), b.gsl_vec.get());
}

template<>
bool Vector_i::operator==(const Vector_i& b) const
{
    if(this->gsl_vec.get() == nullptr && b.gsl_vec.get() == nullptr){
        return true;
    }else if(this->gsl_vec.get() == nullptr || b.gsl_vec.get() == nullptr){
        return false;
    }
    return gsl_vector_int_equal(this->gsl_vec.get(), b.gsl_vec.get());
}

template<>
bool Vector_ui::operator==(const Vector_ui& b) const
{
    if(this->gsl_vec.get() == nullptr && b.gsl_vec.get() == nullptr){
        return true;
    }else if(this->gsl_vec.get() == nullptr || b.gsl_vec.get() == nullptr){
        return false;
    }
    return gsl_vector_uint_equal(this->gsl_vec.get(), b.gsl_vec.get());
}

template<>
bool Vector_l::operator==(const Vector_l& b) const
{
    if(this->gsl_vec.get() == nullptr && b.gsl_vec.get() == nullptr){
        return true;
    }else if(this->gsl_vec.get() == nullptr || b.gsl_vec.get() == nullptr){
        return false;
    }
    return gsl_vector_long_equal(this->gsl_vec.get(), b.gsl_vec.get());
}

template<>
bool Vector_ul::operator==(const Vector_ul& b) const
{
    if(this->gsl_vec.get() == nullptr && b.gsl_vec.get() == nullptr){
        return true;
    }else if(this->gsl_vec.get() == nullptr || b.gsl_vec.get() == nullptr){
        return false;
    }
    return gsl_vector_ulong_equal(this->gsl_vec.get(), b.gsl_vec.get());
}

template<>
bool Vector_s::operator==(const Vector_s& b) const
{
    if(this->gsl_vec.get() == nullptr && b.gsl_vec.get() == nullptr){
        return true;
    }else if(this->gsl_vec.get() == nullptr || b.gsl_vec.get() == nullptr){
        return false;
    }
    return gsl_vector_short_equal(this->gsl_vec.get(), b.gsl_vec.get());
}

template<>
bool Vector_us::operator==(const Vector_us& b) const
{
    if(this->gsl_vec.get() == nullptr && b.gsl_vec.get() == nullptr){
        return true;
    }else if(this->gsl_vec.get() == nullptr || b.gsl_vec.get() == nullptr){
        return false;
    }
    return gsl_vector_ushort_equal(this->gsl_vec.get(), b.gsl_vec.get());
}

template<>
bool Vector_c::operator==(const Vector_c& b) const
{
    if(this->gsl_vec.get() == nullptr && b.gsl_vec.get() == nullptr){
        return true;
    }else if(this->gsl_vec.get() == nullptr || b.gsl_vec.get() == nullptr){
        return false;
    }
    return gsl_vector_char_equal(this->gsl_vec.get(), b.gsl_vec.get());
}

template<>
bool Vector_uc::operator==(const Vector_uc& b) const
{
    if(this->gsl_vec.get() == nullptr && b.gsl_vec.get() == nullptr){
        return true;
    }else if(this->gsl_vec.get() == nullptr || b.gsl_vec.get() == nullptr){
        return false;
    }
    return gsl_vector_uchar_equal(this->gsl_vec.get(), b.gsl_vec.get());
}

template<>
bool Vector_cx::operator==(const Vector_cx& b) const
{
    if(this->gsl_vec.get() == nullptr && b.gsl_vec.get() == nullptr){
        return true;
    }else if(this->gsl_vec.get() == nullptr || b.gsl_vec.get() == nullptr){
        return false;
    }
    return gsl_vector_complex_equal(this->gsl_vec.get(), b.gsl_vec.get());
}

template<>
bool Vector_cxld::operator==(const Vector_cxld& b) const
{
    if(this->gsl_vec.get() == nullptr && b.gsl_vec.get() == nullptr){
        return true;
    }else if(this->gsl_vec.get() == nullptr || b.gsl_vec.get() == nullptr){
        return false;
    }
    return gsl_vector_complex_long_double_equal(this->gsl_vec.get(), b.gsl_vec.get());
}

template<>
bool Vector_cxf::operator==(const Vector_cxf& b) const
{
    if(this->gsl_vec.get() == nullptr && b.gsl_vec.get() == nullptr){
        return true;
    }else if(this->gsl_vec.get() == nullptr || b.gsl_vec.get() == nullptr){
        return false;
    }
    return gsl_vector_complex_float_equal(this->gsl_vec.get(), b.gsl_vec.get());
}

template<>
typename Vector::iterator Vector::begin()
{
    if(this->gsl_vec.get() == nullptr){
        throw std::runtime_error("Calling begin() on uninitialized Vector");
    }
    return Vector::iterator(gsl_vector_ptr(gsl_vec.get(), 0), this->gsl_vec->stride);
}

template<>
typename Vector_ld::iterator Vector_ld::begin()
{
    if(this->gsl_vec.get() == nullptr){
        throw std::runtime_error("Calling begin() on uninitialized Vector");
    }
    return iterator(gsl_vector_long_double_ptr(gsl_vec.get(), 0), this->gsl_vec->stride);
}

template<>
typename Vector_f::iterator Vector_f::begin()
{
    if(this->gsl_vec.get() == nullptr){
        throw std::runtime_error("Calling begin() on uninitialized Vector");
    }
    return iterator(gsl_vector_float_ptr(gsl_vec.get(), 0), this->gsl_vec->stride);
}

template<>
typename Vector_i::iterator Vector_i::begin()
{
    if(this->gsl_vec.get() == nullptr){
        throw std::runtime_error("Calling begin() on uninitialized Vector");
    }
    return iterator(gsl_vector_int_ptr(gsl_vec.get(), 0), this->gsl_vec->stride);
}

template<>
typename Vector_ui::iterator Vector_ui::begin()
{
    if(this->gsl_vec.get() == nullptr){
        throw std::runtime_error("Calling begin() on uninitialized Vector");
    }
    return iterator(gsl_vector_uint_ptr(gsl_vec.get(), 0), this->gsl_vec->stride);
}

template<>
typename Vector_l::iterator Vector_l::begin()
{
    if(this->gsl_vec.get() == nullptr){
        throw std::runtime_error("Calling begin() on uninitialized Vector");
    }
    return iterator(gsl_vector_long_ptr(gsl_vec.get(), 0), this->gsl_vec->stride);
}

template<>
typename Vector_ul::iterator Vector_ul::begin()
{
    if(this->gsl_vec.get() == nullptr){
        throw std::runtime_error("Calling begin() on uninitialized Vector");
    }
    return iterator(gsl_vector_ulong_ptr(gsl_vec.get(), 0), this->gsl_vec->stride);
}

template<>
typename Vector_s::iterator Vector_s::begin()
{
    if(this->gsl_vec.get() == nullptr){
        throw std::runtime_error("Calling begin() on uninitialized Vector");
    }
    return iterator(gsl_vector_short_ptr(gsl_vec.get(), 0), this->gsl_vec->stride);
}

template<>
typename Vector_us::iterator Vector_us::begin()
{
    if(this->gsl_vec.get() == nullptr){
        throw std::runtime_error("Calling begin() on uninitialized Vector");
    }
    return iterator(gsl_vector_ushort_ptr(gsl_vec.get(), 0), this->gsl_vec->stride);
}

template<>
typename Vector_c::iterator Vector_c::begin()
{
    if(this->gsl_vec.get() == nullptr){
        throw std::runtime_error("Calling begin() on uninitialized Vector");
    }
    return iterator(gsl_vector_char_ptr(gsl_vec.get(), 0), this->gsl_vec->stride);
}

template<>
typename Vector_uc::iterator Vector_uc::begin()
{
    if(this->gsl_vec.get() == nullptr){
        throw std::runtime_error("Calling begin() on uninitialized Vector");
    }
    return iterator(gsl_vector_uchar_ptr(gsl_vec.get(), 0), this->gsl_vec->stride);
}

template<>
typename Vector_cx::iterator Vector_cx::begin()
{
    if(this->gsl_vec.get() == nullptr){
        throw std::runtime_error("Calling begin() on uninitialized Vector");
    }
    return iterator(gsl_vector_complex_ptr(gsl_vec.get(), 0), this->gsl_vec->stride);
}

template<>
typename Vector_cxld::iterator Vector_cxld::begin()
{
    if(this->gsl_vec.get() == nullptr){
        throw std::runtime_error("Calling begin() on uninitialized Vector");
    }
    return iterator(gsl_vector_complex_long_double_ptr(gsl_vec.get(), 0), this->gsl_vec->stride);
}

template<>
typename Vector_cxf::iterator Vector_cxf::begin()
{
    if(this->gsl_vec.get() == nullptr){
        throw std::runtime_error("Calling begin() on uninitialized Vector");
    }
    return iterator(gsl_vector_complex_float_ptr(gsl_vec.get(), 0), this->gsl_vec->stride);
}

template<>
typename Vector::const_iterator Vector::begin() const
{
    if(this->gsl_vec.get() == nullptr){
        throw std::runtime_error("Calling begin() on uninitialized Vector");
    }
    return const_iterator(gsl_vector_ptr(gsl_vec.get(), 0), this->gsl_vec->stride);
}

template<>
typename Vector_ld::const_iterator Vector_ld::begin() const
{
    if(this->gsl_vec.get() == nullptr){
        throw std::runtime_error("Calling begin() on uninitialized Vector");
    }
    return const_iterator(gsl_vector_long_double_ptr(gsl_vec.get(), 0), this->gsl_vec->stride);
}

template<>
typename Vector_f::const_iterator Vector_f::begin() const
{
    if(this->gsl_vec.get() == nullptr){
        throw std::runtime_error("Calling begin() on uninitialized Vector");
    }
    return const_iterator(gsl_vector_float_ptr(gsl_vec.get(), 0), this->gsl_vec->stride);
}

template<>
typename Vector_i::const_iterator Vector_i::begin() const
{
    if(this->gsl_vec.get() == nullptr){
        throw std::runtime_error("Calling begin() on uninitialized Vector");
    }
    return const_iterator(gsl_vector_int_ptr(gsl_vec.get(), 0), this->gsl_vec->stride);
}

template<>
typename Vector_ui::const_iterator Vector_ui::begin() const
{
    if(this->gsl_vec.get() == nullptr){
        throw std::runtime_error("Calling begin() on uninitialized Vector");
    }
    return const_iterator(gsl_vector_uint_ptr(gsl_vec.get(), 0), this->gsl_vec->stride);
}

template<>
typename Vector_l::const_iterator Vector_l::begin() const
{
    if(this->gsl_vec.get() == nullptr){
        throw std::runtime_error("Calling begin() on uninitialized Vector");
    }
    return const_iterator(gsl_vector_long_ptr(gsl_vec.get(), 0), this->gsl_vec->stride);
}

template<>
typename Vector_ul::const_iterator Vector_ul::begin() const
{
    if(this->gsl_vec.get() == nullptr){
        throw std::runtime_error("Calling begin() on uninitialized Vector");
    }
    return const_iterator(gsl_vector_ulong_ptr(gsl_vec.get(), 0), this->gsl_vec->stride);
}

template<>
typename Vector_s::const_iterator Vector_s::begin() const
{
    if(this->gsl_vec.get() == nullptr){
        throw std::runtime_error("Calling begin() on uninitialized Vector");
    }
    return const_iterator(gsl_vector_short_ptr(gsl_vec.get(), 0), this->gsl_vec->stride);
}

template<>
typename Vector_us::const_iterator Vector_us::begin() const
{
    if(this->gsl_vec.get() == nullptr){
        throw std::runtime_error("Calling begin() on uninitialized Vector");
    }
    return const_iterator(gsl_vector_ushort_ptr(gsl_vec.get(), 0), this->gsl_vec->stride);
}

template<>
typename Vector_c::const_iterator Vector_c::begin() const
{
    if(this->gsl_vec.get() == nullptr){
        throw std::runtime_error("Calling begin() on uninitialized Vector");
    }
    return const_iterator(gsl_vector_char_ptr(gsl_vec.get(), 0), this->gsl_vec->stride);
}

template<>
typename Vector_uc::const_iterator Vector_uc::begin() const
{
    if(this->gsl_vec.get() == nullptr){
        throw std::runtime_error("Calling begin() on uninitialized Vector");
    }
    return const_iterator(gsl_vector_uchar_ptr(gsl_vec.get(), 0), this->gsl_vec->stride);
}

template<>
typename Vector_cx::const_iterator Vector_cx::begin() const
{
    if(this->gsl_vec.get() == nullptr){
        throw std::runtime_error("Calling begin() on uninitialized Vector");
    }
    return const_iterator(gsl_vector_complex_ptr(gsl_vec.get(), 0), this->gsl_vec->stride);
}

template<>
typename Vector_cxld::const_iterator Vector_cxld::begin() const
{
    if(this->gsl_vec.get() == nullptr){
        throw std::runtime_error("Calling begin() on uninitialized Vector");
    }
    return const_iterator(gsl_vector_complex_long_double_ptr(gsl_vec.get(), 0), this->gsl_vec->stride);
}

template<>
typename Vector_cxf::const_iterator Vector_cxf::begin() const
{
    if(this->gsl_vec.get() == nullptr){
        throw std::runtime_error("Calling begin() on uninitialized Vector");
    }
    return const_iterator(gsl_vector_complex_float_ptr(gsl_vec.get(), 0), this->gsl_vec->stride);
}



template<>
typename Vector::const_iterator Vector::cbegin() const
{
    if(this->gsl_vec.get() == nullptr){
        throw std::runtime_error("Calling begin() on uninitialized Vector");
    }
    return const_iterator(gsl_vector_ptr(gsl_vec.get(), 0), this->gsl_vec->stride);
}

template<>
typename Vector_ld::const_iterator Vector_ld::cbegin() const
{
    if(this->gsl_vec.get() == nullptr){
        throw std::runtime_error("Calling begin() on uninitialized Vector");
    }
    return const_iterator(gsl_vector_long_double_ptr(gsl_vec.get(), 0), this->gsl_vec->stride);
}

template<>
typename Vector_f::const_iterator Vector_f::cbegin() const
{
    if(this->gsl_vec.get() == nullptr){
        throw std::runtime_error("Calling begin() on uninitialized Vector");
    }
    return const_iterator(gsl_vector_float_ptr(gsl_vec.get(), 0), this->gsl_vec->stride);
}

template<>
typename Vector_i::const_iterator Vector_i::cbegin() const
{
    if(this->gsl_vec.get() == nullptr){
        throw std::runtime_error("Calling begin() on uninitialized Vector");
    }
    return const_iterator(gsl_vector_int_ptr(gsl_vec.get(), 0), this->gsl_vec->stride);
}

template<>
typename Vector_ui::const_iterator Vector_ui::cbegin() const
{
    if(this->gsl_vec.get() == nullptr){
        throw std::runtime_error("Calling begin() on uninitialized Vector");
    }
    return const_iterator(gsl_vector_uint_ptr(gsl_vec.get(), 0), this->gsl_vec->stride);
}

template<>
typename Vector_l::const_iterator Vector_l::cbegin() const
{
    if(this->gsl_vec.get() == nullptr){
        throw std::runtime_error("Calling begin() on uninitialized Vector");
    }
    return const_iterator(gsl_vector_long_ptr(gsl_vec.get(), 0), this->gsl_vec->stride);
}

template<>
typename Vector_ul::const_iterator Vector_ul::cbegin() const
{
    if(this->gsl_vec.get() == nullptr){
        throw std::runtime_error("Calling begin() on uninitialized Vector");
    }
    return const_iterator(gsl_vector_ulong_ptr(gsl_vec.get(), 0), this->gsl_vec->stride);
}

template<>
typename Vector_s::const_iterator Vector_s::cbegin() const
{
    if(this->gsl_vec.get() == nullptr){
        throw std::runtime_error("Calling begin() on uninitialized Vector");
    }
    return const_iterator(gsl_vector_short_ptr(gsl_vec.get(), 0), this->gsl_vec->stride);
}

template<>
typename Vector_us::const_iterator Vector_us::cbegin() const
{
    if(this->gsl_vec.get() == nullptr){
        throw std::runtime_error("Calling begin() on uninitialized Vector");
    }
    return const_iterator(gsl_vector_ushort_ptr(gsl_vec.get(), 0), this->gsl_vec->stride);
}

template<>
typename Vector_c::const_iterator Vector_c::cbegin() const
{
    if(this->gsl_vec.get() == nullptr){
        throw std::runtime_error("Calling begin() on uninitialized Vector");
    }
    return const_iterator(gsl_vector_char_ptr(gsl_vec.get(), 0), this->gsl_vec->stride);
}

template<>
typename Vector_uc::const_iterator Vector_uc::cbegin() const
{
    if(this->gsl_vec.get() == nullptr){
        throw std::runtime_error("Calling begin() on uninitialized Vector");
    }
    return const_iterator(gsl_vector_uchar_ptr(gsl_vec.get(), 0), this->gsl_vec->stride);
}

template<>
typename Vector_cx::const_iterator Vector_cx::cbegin() const
{
    if(this->gsl_vec.get() == nullptr){
        throw std::runtime_error("Calling begin() on uninitialized Vector");
    }
    return const_iterator(gsl_vector_complex_ptr(gsl_vec.get(), 0), this->gsl_vec->stride);
}

template<>
typename Vector_cxld::const_iterator Vector_cxld::cbegin() const
{
    if(this->gsl_vec.get() == nullptr){
        throw std::runtime_error("Calling begin() on uninitialized Vector");
    }
    return const_iterator(gsl_vector_complex_long_double_ptr(gsl_vec.get(), 0), this->gsl_vec->stride);
}

template<>
typename Vector_cxf::const_iterator Vector_cxf::cbegin() const
{
    if(this->gsl_vec.get() == nullptr){
        throw std::runtime_error("Calling begin() on uninitialized Vector");
    }
    return const_iterator(gsl_vector_complex_float_ptr(gsl_vec.get(), 0), this->gsl_vec->stride);
}

/*
template<>
std::string Vector_cx::to_string() const
{
    std::string res = "(";
    Complex tmp;
    for(Vector_cx::size_type i = 0; i < this->size(); i++){
        tmp = (*this)[i];
        res += tmp.to_string();
        if(i < this->size() - 1){
            res += ",";
        }
        res += " ";
    }
    res += ")";
    return res;
}

template<>
std::string Vector_cxld::to_string() const
{
    std::string res = "(";
    Complex_ld tmp;
    for(Vector_cxld::size_type i = 0; i < this->size(); i++){
        tmp = (*this)[i];
        res += tmp.to_string();
        if(i < this->size() - 1){
            res += ",";
        }
        res += " ";
    }
    res += ")";
    return res;
}

template<>
std::string Vector_cxf::to_string() const
{
    std::string res = "(";
    Complex_f tmp;
    for(Vector_cxf::size_type i = 0; i < this->size(); i++){
        tmp = (*this)[i];
        res += tmp.to_string();
        if(i < this->size() - 1){
            res += ",";
        }
        res += " ";
    }
    res += ")";
    return res;
}
*/


template Vector::Vector_t(const std::shared_ptr<GSL_Vec>&);
template Vector_ld::Vector_t(const std::shared_ptr<GSL_Vec>&);
template Vector_f::Vector_t(const std::shared_ptr<GSL_Vec>&);
template Vector_i::Vector_t(const std::shared_ptr<GSL_Vec>&);
template Vector_ui::Vector_t(const std::shared_ptr<GSL_Vec>&);
template Vector_l::Vector_t(const std::shared_ptr<GSL_Vec>&);
template Vector_ul::Vector_t(const std::shared_ptr<GSL_Vec>&);
template Vector_s::Vector_t(const std::shared_ptr<GSL_Vec>&);
template Vector_us::Vector_t(const std::shared_ptr<GSL_Vec>&);
template Vector_c::Vector_t(const std::shared_ptr<GSL_Vec>&);
template Vector_uc::Vector_t(const std::shared_ptr<GSL_Vec>&);
template Vector_cx::Vector_t(const std::shared_ptr<GSL_Vec>&);
template Vector_cxf::Vector_t(const std::shared_ptr<GSL_Vec>&);
template Vector_cxld::Vector_t(const std::shared_ptr<GSL_Vec>&);

template Vector::Vector_t(const size_type n);
template Vector_ld::Vector_t(const size_type n);
template Vector_f::Vector_t(const size_type n);
template Vector_i::Vector_t(const size_type n);
template Vector_ui::Vector_t(const size_type n);
template Vector_l::Vector_t(const size_type n);
template Vector_ul::Vector_t(const size_type n);
template Vector_s::Vector_t(const size_type n);
template Vector_us::Vector_t(const size_type n);
template Vector_c::Vector_t(const size_type n);
template Vector_uc::Vector_t(const size_type n);
template Vector_cx::Vector_t(const size_type n);
template Vector_cxld::Vector_t(const size_type n);
template Vector_cxf::Vector_t(const size_type n);

template Vector::Vector_t(std::initializer_list<value_type>);
template Vector_ld::Vector_t(std::initializer_list<value_type>);
template Vector_f::Vector_t(std::initializer_list<value_type>);
template Vector_i::Vector_t(std::initializer_list<value_type>);
template Vector_ui::Vector_t(std::initializer_list<value_type>);
template Vector_l::Vector_t(std::initializer_list<value_type>);
template Vector_ul::Vector_t(std::initializer_list<value_type>);
template Vector_s::Vector_t(std::initializer_list<value_type>);
template Vector_us::Vector_t(std::initializer_list<value_type>);
template Vector_c::Vector_t(std::initializer_list<value_type>);
template Vector_uc::Vector_t(std::initializer_list<value_type>);
template Vector_cx::Vector_t(std::initializer_list<value_type>);
template Vector_cxld::Vector_t(std::initializer_list<value_type>);
template Vector_cxf::Vector_t(std::initializer_list<value_type>);

template Vector Vector::copy() const;
template Vector_ld Vector_ld::copy() const;
template Vector_f Vector_f::copy() const;
template Vector_i Vector_i::copy() const;
template Vector_ui Vector_ui::copy() const;
template Vector_l Vector_l::copy() const;
template Vector_ul Vector_ul::copy() const;
template Vector_s Vector_s::copy() const;
template Vector_us Vector_us::copy() const;
template Vector_c Vector_c::copy() const;
template Vector_uc Vector_uc::copy() const;
template Vector_cx Vector_cx::copy() const;
template Vector_cxld Vector_cxld::copy() const;
template Vector_cxf Vector_cxf::copy() const;

template Vector& Vector::copy(const Vector_t& a);
template Vector_ld& Vector_ld::copy(const Vector_t& a);
template Vector_f& Vector_f::copy(const Vector_t& a);
template Vector_i& Vector_i::copy(const Vector_t& a);
template Vector_ui& Vector_ui::copy(const Vector_t& a);
template Vector_l& Vector_l::copy(const Vector_t& a);
template Vector_ul& Vector_ul::copy(const Vector_t& a);
template Vector_s& Vector_s::copy(const Vector_t& a);
template Vector_us& Vector_us::copy(const Vector_t& a);
template Vector_c& Vector_c::copy(const Vector_t& a);
template Vector_uc& Vector_uc::copy(const Vector_t& a);
template Vector_cx& Vector_cx::copy(const Vector_t& a);
template Vector_cxld& Vector_cxld::copy(const Vector_t& a);
template Vector_cxf& Vector_cxf::copy(const Vector_t& a);

template double Vector::norm<double>() const;
template float Vector_f::norm<float>() const;
template double Vector_cx::norm<double>() const;
template float Vector_cxf::norm<float>() const;
template long double Vector_ld::norm<long double>() const;
template double Vector_i::norm<double>() const;
template float Vector_i::norm<float>() const;
template double Vector_ui::norm<double>() const;
template float Vector_ui::norm<float>() const;
template double Vector_l::norm<double>() const;
template long double Vector::norm<long double>() const;
template double Vector_ul::norm<double>() const;
template long double Vector_ul::norm<long double>() const;
template double Vector_s::norm<double>() const;
template float Vector_s::norm<float>() const;
template double Vector_us::norm<double>() const;
template float Vector_us::norm<float>() const;
template double Vector_c::norm<double>() const;
template float Vector_c::norm<float>() const;
template double Vector_uc::norm<double>() const;
template float Vector_uc::norm<float>() const;
template long double Vector_cxld::norm<long double>() const;
template float Vector_f::norm<float>() const;

template Vector::value_type Vector::dot(const Vector_t& b) const;
template Vector_ld::value_type Vector_ld::dot(const Vector_t& b) const;
template Vector_f::value_type Vector_f::dot(const Vector_t& b) const;
template Vector_i::value_type Vector_i::dot(const Vector_t& b) const;
template Vector_ui::value_type Vector_ui::dot(const Vector_t& b) const;
template Vector_l::value_type Vector_l::dot(const Vector_t& b) const;
template Vector_ul::value_type Vector_ul::dot(const Vector_t& b) const;
template Vector_s::value_type Vector_s::dot(const Vector_t& b) const;
template Vector_us::value_type Vector_us::dot(const Vector_t& b) const;
template Vector_c::value_type Vector_c::dot(const Vector_t& b) const;
template Vector_uc::value_type Vector_uc::dot(const Vector_t& b) const;
template Vector_cx::value_type Vector_cx::dot(const Vector_t& b) const;
template Vector_cxld::value_type Vector_cxld::dot(const Vector_t& b) const;
template Vector_cxf::value_type Vector_cxf::dot(const Vector_t& b) const;

template Vector& Vector::operator+= (const Vector_t& b);
template Vector_ld& Vector_ld::operator+= (const Vector_t& b);
template Vector_f& Vector_f::operator+= (const Vector_t& b);
template Vector_i& Vector_i::operator+= (const Vector_t& b);
template Vector_ui& Vector_ui::operator+= (const Vector_t& b);
template Vector_l& Vector_l::operator+= (const Vector_t& b);
template Vector_ul& Vector_ul::operator+= (const Vector_t& b);
template Vector_s& Vector_s::operator+= (const Vector_t& b);
template Vector_us& Vector_us::operator+= (const Vector_t& b);
template Vector_c& Vector_c::operator+= (const Vector_t& b);
template Vector_uc& Vector_uc::operator+= (const Vector_t& b);
template Vector_cx& Vector_cx::operator+= (const Vector_t& b);
template Vector_cxld& Vector_cxld::operator+= (const Vector_t& b);
template Vector_cxf& Vector_cxf::operator+= (const Vector_t& b);

template Vector& Vector::operator-= (const Vector_t& b);
template Vector_ld& Vector_ld::operator-= (const Vector_t& b);
template Vector_f& Vector_f::operator-= (const Vector_t& b);
template Vector_i& Vector_i::operator-= (const Vector_t& b);
template Vector_ui& Vector_ui::operator-= (const Vector_t& b);
template Vector_l& Vector_l::operator-= (const Vector_t& b);
template Vector_ul& Vector_ul::operator-= (const Vector_t& b);
template Vector_s& Vector_s::operator-= (const Vector_t& b);
template Vector_us& Vector_us::operator-= (const Vector_t& b);
template Vector_c& Vector_c::operator-= (const Vector_t& b);
template Vector_uc& Vector_uc::operator-= (const Vector_t& b);
template Vector_cx& Vector_cx::operator-= (const Vector_t& b);
template Vector_cxld& Vector_cxld::operator-= (const Vector_t& b);
template Vector_cxf& Vector_cxf::operator-= (const Vector_t& b);

template Vector& Vector::operator*= (const Vector_t& b);
template Vector_ld& Vector_ld::operator*= (const Vector_t& b);
template Vector_f& Vector_f::operator*= (const Vector_t& b);
template Vector_i& Vector_i::operator*= (const Vector_t& b);
template Vector_ui& Vector_ui::operator*= (const Vector_t& b);
template Vector_l& Vector_l::operator*= (const Vector_t& b);
template Vector_ul& Vector_ul::operator*= (const Vector_t& b);
template Vector_s& Vector_s::operator*= (const Vector_t& b);
template Vector_us& Vector_us::operator*= (const Vector_t& b);
template Vector_c& Vector_c::operator*= (const Vector_t& b);
template Vector_uc& Vector_uc::operator*= (const Vector_t& b);
template Vector_cx& Vector_cx::operator*= (const Vector_t& b);
template Vector_cxld& Vector_cxld::operator*= (const Vector_t& b);
template Vector_cxf& Vector_cxf::operator*= (const Vector_t& b);


template Vector& Vector::operator/= (const Vector_t& b);
template Vector_ld& Vector_ld::operator/= (const Vector_t& b);
template Vector_f& Vector_f::operator/= (const Vector_t& b);
template Vector_i& Vector_i::operator/= (const Vector_t& b);
template Vector_ui& Vector_ui::operator/= (const Vector_t& b);
template Vector_l& Vector_l::operator/= (const Vector_t& b);
template Vector_ul& Vector_ul::operator/= (const Vector_t& b);
template Vector_s& Vector_s::operator/= (const Vector_t& b);
template Vector_us& Vector_us::operator/= (const Vector_t& b);
template Vector_c& Vector_c::operator/= (const Vector_t& b);
template Vector_uc& Vector_uc::operator/= (const Vector_t& b);
template Vector_cx& Vector_cx::operator/= (const Vector_t& b);
template Vector_cxld& Vector_cxld::operator/= (const Vector_t& b);
template Vector_cxf& Vector_cxf::operator/= (const Vector_t& b);

template Vector& Vector::operator*= (const Vector_t::value_type& s);
template Vector_ld& Vector_ld::operator*= (const Vector_t::value_type& s);
template Vector_f& Vector_f::operator*= (const Vector_t::value_type& s);
template Vector_i& Vector_i::operator*= (const Vector_t::value_type& s);
template Vector_ui& Vector_ui::operator*= (const Vector_t::value_type& s);
template Vector_l& Vector_l::operator*= (const Vector_t::value_type& s);
template Vector_ul& Vector_ul::operator*= (const Vector_t::value_type& s);
template Vector_s& Vector_s::operator*= (const Vector_t::value_type& s);
template Vector_us& Vector_us::operator*= (const Vector_t::value_type& s);
template Vector_c& Vector_c::operator*= (const Vector_t::value_type& s);
template Vector_uc& Vector_uc::operator*= (const Vector_t::value_type& s);
template Vector_cx& Vector_cx::operator*= (const Vector_t::value_type& s);
template Vector_cxld& Vector_cxld::operator*= (const Vector_t::value_type& s);
template Vector_cxf& Vector_cxf::operator*= (const Vector_t::value_type& s);

template Vector& Vector::operator/= (const Vector_t::value_type& s);
template Vector_ld& Vector_ld::operator/= (const Vector_t::value_type& s);
template Vector_f& Vector_f::operator/= (const Vector_t::value_type& s);
template Vector_i& Vector_i::operator/= (const Vector_t::value_type& s);
template Vector_ui& Vector_ui::operator/= (const Vector_t::value_type& s);
template Vector_l& Vector_l::operator/= (const Vector_t::value_type& s);
template Vector_ul& Vector_ul::operator/= (const Vector_t::value_type& s);
template Vector_s& Vector_s::operator/= (const Vector_t::value_type& s);
template Vector_us& Vector_us::operator/= (const Vector_t::value_type& s);
template Vector_c& Vector_c::operator/= (const Vector_t::value_type& s);
template Vector_uc& Vector_uc::operator/= (const Vector_t::value_type& s);
template Vector_cx& Vector_cx::operator/= (const Vector_t::value_type& s);
template Vector_cxld& Vector_cxld::operator/= (const Vector_t::value_type& s);
template Vector_cxf& Vector_cxf::operator/= (const Vector_t::value_type& s);

template Vector Vector::operator*<gsl_matrix>(const Matrix_t<double, gsl_matrix, gsl_vector, std::allocator<double>>& m) const;
template Vector_f Vector_f::operator*<gsl_matrix_float>(const Matrix_t<float, gsl_matrix_float, gsl_vector_float, std::allocator<float>>& m) const;
template Vector_cx Vector_cx::operator*<gsl_matrix_complex>(const Matrix_t<Complex_t<double, gsl_complex>, gsl_matrix_complex, gsl_vector_complex, std::allocator<gsl_complex>>& m) const;
template Vector_cxf Vector_cxf::operator*<gsl_matrix_complex_float>(const Matrix_t<Complex_t<float, gsl_complex_float>, gsl_matrix_complex_float, gsl_vector_complex_float, std::allocator<gsl_complex_float>>& m) const;

template bool Vector::operator==(const Vector_t&) const;
template bool Vector_ld::operator==(const Vector_t&) const;
template bool Vector_f::operator==(const Vector_t&) const;
template bool Vector_i::operator==(const Vector_t&) const;
template bool Vector_ui::operator==(const Vector_t&) const;
template bool Vector_l::operator==(const Vector_t&) const;
template bool Vector_ul::operator==(const Vector_t&) const;
template bool Vector_s::operator==(const Vector_t&) const;
template bool Vector_us::operator==(const Vector_t&) const;
template bool Vector_c::operator==(const Vector_t&) const;
template bool Vector_uc::operator==(const Vector_t&) const;
template bool Vector_cx::operator==(const Vector_t&) const;
template bool Vector_cxld::operator==(const Vector_t&) const;
template bool Vector_cxf::operator==(const Vector_t&) const;

template Vector::iterator Vector::begin();
template Vector_ld::iterator Vector_ld::begin();
template Vector_f::iterator Vector_f::begin();
template Vector_i::iterator Vector_i::begin();
template Vector_ui::iterator Vector_ui::begin();
template Vector_l::iterator Vector_l::begin();
template Vector_ul::iterator Vector_ul::begin();
template Vector_s::iterator Vector_s::begin();
template Vector_us::iterator Vector_us::begin();
template Vector_c::iterator Vector_c::begin();
template Vector_uc::iterator Vector_uc::begin();
template Vector_cx::iterator Vector_cx::begin();
template Vector_cxld::iterator Vector_cxld::begin();
template Vector_cxf::iterator Vector_cxf::begin();

template Vector::const_iterator Vector::begin() const;
template Vector_ld::const_iterator Vector_ld::begin() const;
template Vector_f::const_iterator Vector_f::begin() const;
template Vector_i::const_iterator Vector_i::begin() const;
template Vector_ui::const_iterator Vector_ui::begin() const;
template Vector_l::const_iterator Vector_l::begin() const;
template Vector_ul::const_iterator Vector_ul::begin() const;
template Vector_s::const_iterator Vector_s::begin() const;
template Vector_us::const_iterator Vector_us::begin() const;
template Vector_c::const_iterator Vector_c::begin() const;
template Vector_uc::const_iterator Vector_uc::begin() const;
template Vector_cx::const_iterator Vector_cx::begin() const;
template Vector_cxld::const_iterator Vector_cxld::begin() const;
template Vector_cxf::const_iterator Vector_cxf::begin() const;

template Vector::const_iterator Vector::cbegin() const;
template Vector_ld::const_iterator Vector_ld::cbegin() const;
template Vector_f::const_iterator Vector_f::cbegin() const;
template Vector_i::const_iterator Vector_i::cbegin() const;
template Vector_ui::const_iterator Vector_ui::cbegin() const;
template Vector_l::const_iterator Vector_l::cbegin() const;
template Vector_ul::const_iterator Vector_ul::cbegin() const;
template Vector_s::const_iterator Vector_s::cbegin() const;
template Vector_us::const_iterator Vector_us::cbegin() const;
template Vector_c::const_iterator Vector_c::cbegin() const;
template Vector_uc::const_iterator Vector_uc::cbegin() const;
template Vector_cx::const_iterator Vector_cx::cbegin() const;
template Vector_cxld::const_iterator Vector_cxld::cbegin() const;
template Vector_cxf::const_iterator Vector_cxf::cbegin() const;

template class Vector_t<double, gsl_vector, std::allocator<double>>;
template class Vector_t<long double, gsl_vector_long_double, std::allocator<long double>>;
template class Vector_t<float, gsl_vector_float, std::allocator<float>>;
template class Vector_t<int, gsl_vector_int, std::allocator<int>>;
template class Vector_t<unsigned int, gsl_vector_uint, std::allocator<unsigned int>>;
template class Vector_t<long, gsl_vector_long, std::allocator<long>>;
template class Vector_t<unsigned long, gsl_vector_ulong, std::allocator<unsigned long>>;
template class Vector_t<short, gsl_vector_short, std::allocator<short>>;
template class Vector_t<unsigned short, gsl_vector_ushort, std::allocator<unsigned short>>;
template class Vector_t<char, gsl_vector_char, std::allocator<char>>;
template class Vector_t<unsigned char, gsl_vector_uchar, std::allocator<unsigned char>>;
template class Vector_t<Complex_t<double, gsl_complex>, gsl_vector_complex, std::allocator<gsl_complex>>;
template class Vector_t<Complex_t<long double, gsl_complex_long_double>, gsl_vector_complex_long_double, std::allocator<gsl_complex_long_double>>;
template class Vector_t<Complex_t<float, gsl_complex_float>, gsl_vector_complex_float, std::allocator<gsl_complex_float>>;

}
