#include "vector_template.h"
#include "complex.h"
#include <gsl/gsl_blas.h>
#include <iostream>
#include <stdexcept>

namespace GSL{

template<class T, class GSL_VEC, class A>
Vector_t<T, GSL_VEC, A>::Vector_t(const GSL_VEC& v)
: gsl_vec(new GSL_VEC)
{
    *gsl_vec = v;
}

template<class T, class GSL_VEC, class A>
Vector_t<T, GSL_VEC, A>::Vector_t(const GSL_VEC* v)
: gsl_vec(new GSL_VEC)
{
    *gsl_vec = *v;
}

template<>
inline Vector::Vector_t
(const Vector::size_type n)
 : gsl_vec(gsl_vector_calloc(n), gsl_vector_free)
{
    if(gsl_vec == nullptr){
        throw std::runtime_error("Memory allocation (gsl_vector_calloc)"
        " failed!");
    }
}

template<>
inline Vector_ld::Vector_t
(const Vector_t::size_type n)
 : gsl_vec(gsl_vector_long_double_calloc(n), gsl_vector_long_double_free)
{

    if(gsl_vec == nullptr){
        throw std::runtime_error("Memory allocation (gsl_vector_long_double_calloc)"
        " failed!");
    }
}

template<>
inline Vector_f::Vector_t
(const Vector_t::size_type n)
 : gsl_vec(gsl_vector_float_calloc(n), gsl_vector_float_free)
{
    if(gsl_vec == nullptr){
        throw std::runtime_error("Memory allocation (gsl_vector_float_calloc)"
        " failed!");
    }
}

template<>
inline Vector_i::Vector_t
(const Vector_t::size_type n)
 : gsl_vec(gsl_vector_int_calloc(n), gsl_vector_int_free)
{
    if(gsl_vec == nullptr){
        throw std::runtime_error("Memory allocation (gsl_vector_int_calloc)"
        " failed!");
    }
}

template<>
inline Vector_ui::Vector_t
(const Vector_t::size_type n)
 : gsl_vec(gsl_vector_uint_calloc(n), gsl_vector_uint_free)
{
    if(gsl_vec == nullptr){
        throw std::runtime_error("Memory allocation (gsl_vector_uint_calloc)"
        " failed!");
    }
}

template<>
inline Vector_l::Vector_t
(const Vector_t::size_type n)
 : gsl_vec(gsl_vector_long_calloc(n), gsl_vector_long_free)
{
    if(gsl_vec == nullptr){
        throw std::runtime_error("Memory allocation (gsl_vector_long_calloc)"
        " failed!");
    }
}

template<>
inline Vector_ul::Vector_t
(const Vector_t::size_type n)
 : gsl_vec(gsl_vector_ulong_calloc(n), gsl_vector_ulong_free)
{
    if(gsl_vec == nullptr){
        throw std::runtime_error("Memory allocation (gsl_vector_ulong_calloc)"
        " failed!");
    }
}

template<>
inline Vector_s::Vector_t
(const Vector_t::size_type n)
 : gsl_vec(gsl_vector_short_calloc(n), gsl_vector_short_free)
{
    if(gsl_vec == nullptr){
        throw std::runtime_error("Memory allocation (gsl_vector_short_calloc)"
        " failed!");
    }
}

template<>
inline Vector_us::Vector_t
(const Vector_t::size_type n)
 : gsl_vec(gsl_vector_ushort_calloc(n), gsl_vector_ushort_free)
{
    if(gsl_vec == nullptr){
        throw std::runtime_error("Memory allocation (gsl_vector_ushort_calloc)"
        " failed!");
    }
}

template<>
inline Vector_c::Vector_t
(const Vector_t::size_type n)
 : gsl_vec(gsl_vector_char_calloc(n), gsl_vector_char_free)
{
    if(gsl_vec == nullptr){
        throw std::runtime_error("Memory allocation (gsl_vector_char_calloc)"
        " failed!");
    }
}

template<>
inline Vector_uc::Vector_t
(const Vector_t::size_type n)
 : gsl_vec(gsl_vector_uchar_calloc(n), gsl_vector_uchar_free)
{
    if(gsl_vec == nullptr){
        throw std::runtime_error("Memory allocation (gsl_vector_uchar_calloc)"
        " failed!");
    }
}

template<>
inline Vector_cx::Vector_t
(const Vector_t::size_type n)
 : gsl_vec(gsl_vector_complex_calloc(n), gsl_vector_complex_free)
{
    if(gsl_vec == nullptr){
        throw std::runtime_error("Memory allocation (gsl_vector_complex_calloc)"
        " failed!");
    }
}

template<>
inline Vector_cxld::Vector_t
(const Vector_t::size_type n)
 : gsl_vec(gsl_vector_complex_long_double_calloc(n), gsl_vector_complex_long_double_free)
{
    if(gsl_vec == nullptr){
        throw std::runtime_error("Memory allocation (gsl_vector_long_double_calloc)"
        " failed!");
    }
}

template<>
inline Vector_cxf::Vector_t
(const Vector_t::size_type n)
 : gsl_vec(gsl_vector_complex_float_calloc(n), gsl_vector_complex_float_free)
{
    if(gsl_vec == nullptr){
        throw std::runtime_error("Memory allocation (gsl_vector_float_calloc)"
        " failed!");
    }
}

template<>
inline Vector::Vector_t(std::initializer_list<double> l)
 : gsl_vec(gsl_vector_alloc(l.size()), gsl_vector_free)
{
    auto current = l.begin();
    for(size_t i = 0; i < l.size(); i++){
        gsl_vector_set(gsl_vec.get(), i, *current);
        current++;
    }
}

template<>
inline Vector_ld::Vector_t(std::initializer_list<long double> l)
 : gsl_vec(gsl_vector_long_double_alloc(l.size()), gsl_vector_long_double_free)
{
    auto current = l.begin();
    for(size_t i = 0; i < l.size(); i++){
        gsl_vector_long_double_set(gsl_vec.get(), i, *current);
        current++;
    }
}

template<>
inline Vector_f::Vector_t(std::initializer_list<float> l)
 : gsl_vec(gsl_vector_float_alloc(l.size()), gsl_vector_float_free)
{
    auto current = l.begin();
    for(size_t i = 0; i < l.size(); i++){
        gsl_vector_float_set(gsl_vec.get(), i, *current);
        current++;
    }
}

template<>
inline Vector_i::Vector_t(std::initializer_list<int> l)
 : gsl_vec(gsl_vector_int_alloc(l.size()), gsl_vector_int_free)
{
    auto current = l.begin();
    for(size_t i = 0; i < l.size(); i++){
        gsl_vector_int_set(gsl_vec.get(), i, *current);
        current++;
    }
}

template<>
inline Vector_ui::Vector_t(std::initializer_list<unsigned int> l)
 : gsl_vec(gsl_vector_uint_alloc(l.size()), gsl_vector_uint_free)
{
    auto current = l.begin();
    for(size_t i = 0; i < l.size(); i++){
        gsl_vector_uint_set(gsl_vec.get(), i, *current);
        current++;
    }
}

template<>
inline Vector_l::Vector_t(std::initializer_list<long> l)
 : gsl_vec(gsl_vector_long_alloc(l.size()), gsl_vector_long_free)
{
    auto current = l.begin();
    for(size_t i = 0; i < l.size(); i++){
        gsl_vector_long_set(gsl_vec.get(), i, *current);
        current++;
    }
}

template<>
inline Vector_ul::Vector_t(std::initializer_list<unsigned long> l)
 : gsl_vec(gsl_vector_ulong_alloc(l.size()), gsl_vector_ulong_free)
{
    auto current = l.begin();
    for(size_t i = 0; i < l.size(); i++){
        gsl_vector_ulong_set(gsl_vec.get(), i, *current);
        current++;
    }
}

template<>
inline Vector_s::Vector_t(std::initializer_list<short> l)
 : gsl_vec(gsl_vector_short_alloc(l.size()), gsl_vector_short_free)
{
    auto current = l.begin();
    for(size_t i = 0; i < l.size(); i++){
        gsl_vector_short_set(gsl_vec.get(), i, *current);
        current++;
    }
}

template<>
inline Vector_us::Vector_t(std::initializer_list<unsigned short> l)
 : gsl_vec(gsl_vector_ushort_alloc(l.size()), gsl_vector_ushort_free)
{
    auto current = l.begin();
    for(size_t i = 0; i < l.size(); i++){
        gsl_vector_ushort_set(gsl_vec.get(), i, *current);
        current++;
    }
}

template<>
inline Vector_c::Vector_t(std::initializer_list<char> l)
 : gsl_vec(gsl_vector_char_alloc(l.size()), gsl_vector_char_free)
{
    auto current = l.begin();
    for(size_t i = 0; i < l.size(); i++){
        gsl_vector_char_set(gsl_vec.get(), i, *current);
        current++;
    }
}

template<>
inline Vector_uc::Vector_t(std::initializer_list<unsigned char> l)
 : gsl_vec(gsl_vector_uchar_alloc(l.size()), gsl_vector_uchar_free)
{
    auto current = l.begin();
    for(size_t i = 0; i < l.size(); i++){
        gsl_vector_uchar_set(gsl_vec.get(), i, *current);
        current++;
    }
}

template<>
inline Vector_cx::
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
inline Vector_cxld::
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
inline Vector_cxf::
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
Vector_t<T, GSL_VEC, A>::operator GSL_VEC() const
{
    return *this->gsl_vec;
}

template<>
inline void Vector::copy(const Vector& a)
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
}

template<>
inline void Vector_ld::copy
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
}

template<class T, class GSL_VEC, class A>
typename Vector_t<T, GSL_VEC, A>::size_type Vector_t<T, GSL_VEC, A>::size() const
{
    return this->gsl_vec->size;
}

template<>
inline void Vector_f::copy
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
}

template<>
inline void Vector_i::copy
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
}

template<>
inline void Vector_ui::copy
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
}

template<>
inline void Vector_l::copy
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
}

template<>
inline void Vector_ul::copy
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
}

template<>
inline void Vector_s::copy
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
}

template<>
inline void Vector_us::copy
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
}

template<>
inline void Vector_c::copy
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
}

template<>
inline void Vector_uc::copy
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
}

template<>
inline void Vector_cx::copy
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
}

template<>
inline void Vector_cxld::copy
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
}

template<>
inline void Vector_cxf::copy
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
}

template<>
inline Vector& Vector::operator=(const Vector& a)
{
    if( gsl_vec == nullptr || this->gsl_vec->owner != 0){
        this->gsl_vec = a.gsl_vec;
    }else if(this->gsl_vec->owner == 0){
        if(this->gsl_vec == nullptr){
            this->gsl_vec = std::shared_ptr<gsl_vector>(gsl_vector_alloc(a.size()), gsl_vector_free);
        }
        if(a.gsl_vec != nullptr){
            gsl_vector_memcpy(this->gsl_vec.get(), a.gsl_vec.get());
        }
    }else{
        throw std::runtime_error("Unknown owner value " + std::to_string(gsl_vec->owner));
    }
    return *this;
}

template<>
inline Vector_ld& Vector_ld::operator=(const Vector_ld& a)
{
    if(this->gsl_vec == nullptr || this->gsl_vec->owner != 0){
        this->gsl_vec = a.gsl_vec;
    }else if(this->gsl_vec->owner == 0){
        gsl_vector_long_double_memcpy(this->gsl_vec.get(), a.gsl_vec.get());
    }else{
        throw std::runtime_error("Unknown owner value " + std::to_string(gsl_vec->owner));
    }
    return *this;
}

template<>
inline Vector_f& Vector_f::operator=(const Vector_f& a)
{
    if(this->gsl_vec == nullptr || this->gsl_vec->owner != 0){
        this->gsl_vec = a.gsl_vec;
    }else if(this->gsl_vec->owner == 0){
        gsl_vector_float_memcpy(this->gsl_vec.get(), a.gsl_vec.get());
    }else{
        throw std::runtime_error("Unknown owner value " + std::to_string(gsl_vec->owner));
    }
    return *this;
}

template<>
inline Vector_i& Vector_i::operator=(const Vector_i& a)
{
    if(this->gsl_vec == nullptr || this->gsl_vec->owner != 0){
        this->gsl_vec = a.gsl_vec;
    }else if(this->gsl_vec->owner == 0){
        gsl_vector_int_memcpy(this->gsl_vec.get(), a.gsl_vec.get());
    }else{
        throw std::runtime_error("Unknown owner value " + std::to_string(gsl_vec->owner));
    }
    return *this;
}

template<>
inline Vector_ui& Vector_ui::operator=(const Vector_ui& a)
{
    if(this->gsl_vec == nullptr || this->gsl_vec->owner != 0){
        this->gsl_vec = a.gsl_vec;
    }else if(this->gsl_vec->owner == 0){
        gsl_vector_uint_memcpy(this->gsl_vec.get(), a.gsl_vec.get());
    }else{
        throw std::runtime_error("Unknown owner value " + std::to_string(gsl_vec->owner));
    }
    return *this;
}

template<>
inline Vector_l& Vector_l::operator=(const Vector_l& a)
{
    if(this->gsl_vec == nullptr || this->gsl_vec->owner != 0){
        this->gsl_vec = a.gsl_vec;
    }else if(this->gsl_vec->owner == 0){
        gsl_vector_long_memcpy(this->gsl_vec.get(), a.gsl_vec.get());
    }else{
        throw std::runtime_error("Unknown owner value " + std::to_string(gsl_vec->owner));
    }
    return *this;
}

template<>
inline Vector_ul& Vector_ul::operator=(const Vector_ul& a)
{
    if(this->gsl_vec == nullptr || this->gsl_vec->owner != 0){
        this->gsl_vec = a.gsl_vec;
    }else if(this->gsl_vec->owner == 0){
        gsl_vector_ulong_memcpy(this->gsl_vec.get(), a.gsl_vec.get());
    }else{
        throw std::runtime_error("Unknown owner value " + std::to_string(gsl_vec->owner));
    }
    return *this;
}

template<>
inline Vector_s& Vector_s::operator=(const Vector_s& a)
{
    if(this->gsl_vec == nullptr || this->gsl_vec->owner != 0){
        this->gsl_vec = a.gsl_vec;
    }else if(this->gsl_vec->owner == 0){
        gsl_vector_short_memcpy(this->gsl_vec.get(), a.gsl_vec.get());
    }else{
        throw std::runtime_error("Unknown owner value " + std::to_string(gsl_vec->owner));
    }
    return *this;
}

template<>
inline Vector_us& Vector_us::operator=(const Vector_us& a)
{
    if(this->gsl_vec == nullptr || this->gsl_vec->owner != 0){
        this->gsl_vec = a.gsl_vec;
    }else if(this->gsl_vec->owner == 0){
        gsl_vector_ushort_memcpy(this->gsl_vec.get(), a.gsl_vec.get());
    }else{
        throw std::runtime_error("Unknown owner value " + std::to_string(gsl_vec->owner));
    }
    return *this;
}

template<>
inline Vector_c& Vector_c::operator=(const Vector_c& a)
{
    if(this->gsl_vec == nullptr || this->gsl_vec->owner != 0){
        this->gsl_vec = a.gsl_vec;
    }else if(this->gsl_vec->owner == 0){
        gsl_vector_char_memcpy(this->gsl_vec.get(), a.gsl_vec.get());
    }else{
        throw std::runtime_error("Unknown owner value " + std::to_string(gsl_vec->owner));
    }
    return *this;
}

template<>
inline Vector_uc& Vector_uc::operator=(const Vector_uc& a)
{
    if(this->gsl_vec == nullptr || this->gsl_vec->owner != 0){
        this->gsl_vec = a.gsl_vec;
    }else if(this->gsl_vec->owner == 0){
        gsl_vector_uchar_memcpy(this->gsl_vec.get(), a.gsl_vec.get());
    }else{
        throw std::runtime_error("Unknown owner value " + std::to_string(gsl_vec->owner));
    }
    return *this;
}

template<>
inline Vector_cx& Vector_cx::operator=(const Vector_cx& a)
{
    if(this->gsl_vec == nullptr || this->gsl_vec->owner != 0){
        this->gsl_vec = a.gsl_vec;
    }else if(this->gsl_vec->owner == 0){
        gsl_vector_complex_memcpy(this->gsl_vec.get(), a.gsl_vec.get());
    }else{
        throw std::runtime_error("Unknown owner value " + std::to_string(gsl_vec->owner));
    }
    return *this;
}

template<>
inline Vector_cxld& Vector_cxld::operator=(const Vector_cxld& a)
{
    if(this->gsl_vec == nullptr || this->gsl_vec->owner != 0){
        this->gsl_vec = a.gsl_vec;
    }else if(this->gsl_vec->owner == 0){
        gsl_vector_complex_long_double_memcpy(this->gsl_vec.get(), a.gsl_vec.get());
    }else{
        throw std::runtime_error("Unknown owner value " + std::to_string(gsl_vec->owner));
    }
    return *this;
}

template<>
inline Vector_cxf& Vector_cxf::operator=(const Vector_cxf& a)
{
    if(this->gsl_vec == nullptr || this->gsl_vec->owner != 0){
        this->gsl_vec = a.gsl_vec;
    }else if(this->gsl_vec->owner == 0){
        gsl_vector_complex_float_memcpy(this->gsl_vec.get(), a.gsl_vec.get());
    }else{
        throw std::runtime_error("Unknown owner value " + std::to_string(gsl_vec->owner));
    }
    return *this;
}

template<>
inline Vector& Vector::operator=(Vector&& a)
{
    if(this->gsl_vec == nullptr || this->gsl_vec->owner != 0){
        std::swap(this->gsl_vec, a.gsl_vec);
    }else if(this->gsl_vec->owner == 0){
        if(a.gsl_vec != nullptr){
            gsl_vector_memcpy(this->gsl_vec.get(), a.gsl_vec.get());
        }
    }
    return *this;
}

template<>
inline Vector_ld& Vector_ld::operator=(Vector_ld&& a)
{
    if(this->gsl_vec == nullptr || this->gsl_vec->owner != 0){
        std::swap(this->gsl_vec, a.gsl_vec);
    }else if(this->gsl_vec->owner == 0){
        gsl_vector_long_double_memcpy(this->gsl_vec.get(), a.gsl_vec.get());
    }
    return *this;
}

template<>
inline Vector_f& Vector_f::operator=(Vector_f&& a)
{
    if(this->gsl_vec == nullptr || this->gsl_vec->owner != 0){
        std::swap(this->gsl_vec, a.gsl_vec);
    }else if(this->gsl_vec->owner == 0){
        gsl_vector_float_memcpy(this->gsl_vec.get(), a.gsl_vec.get());
    }
    return *this;
}

template<>
inline Vector_i& Vector_i::operator=(Vector_i&& a)
{
    if(this->gsl_vec == nullptr || this->gsl_vec->owner != 0){
        std::swap(this->gsl_vec, a.gsl_vec);
    }else if(this->gsl_vec->owner == 0){
        gsl_vector_int_memcpy(this->gsl_vec.get(), a.gsl_vec.get());
    }
    return *this;
}

template<>
inline Vector_ui& Vector_ui::operator=(Vector_ui&& a)
{
    if(this->gsl_vec == nullptr || this->gsl_vec->owner != 0){
        std::swap(this->gsl_vec, a.gsl_vec);
    }else if(this->gsl_vec->owner == 0){
        gsl_vector_uint_memcpy(this->gsl_vec.get(), a.gsl_vec.get());
    }
    return *this;
}

template<>
inline Vector_l& Vector_l::operator=(Vector_l&& a)
{
    if(this->gsl_vec == nullptr || this->gsl_vec->owner != 0){
        std::swap(this->gsl_vec, a.gsl_vec);
    }else if(this->gsl_vec->owner == 0){
        gsl_vector_long_memcpy(this->gsl_vec.get(), a.gsl_vec.get());
    }
    return *this;
}

template<>
inline Vector_ul& Vector_ul::operator=(Vector_ul&& a)
{
    if(this->gsl_vec == nullptr || this->gsl_vec->owner != 0){
        std::swap(this->gsl_vec, a.gsl_vec);
    }else if(this->gsl_vec->owner == 0){
        gsl_vector_ulong_memcpy(this->gsl_vec.get(), a.gsl_vec.get());
    }
    return *this;
}

template<>
inline Vector_s & Vector_s::operator=(Vector_s&& a)
{
    if(this->gsl_vec == nullptr || this->gsl_vec->owner != 0){
        std::swap(this->gsl_vec, a.gsl_vec);
    }else if(this->gsl_vec->owner == 0){
        gsl_vector_short_memcpy(this->gsl_vec.get(), a.gsl_vec.get());
    }
    return *this;
}

template<>
inline Vector_us& Vector_us::operator=(Vector_us&& a)
{
    if(this->gsl_vec == nullptr || this->gsl_vec->owner != 0){
        std::swap(this->gsl_vec, a.gsl_vec);
    }else if(this->gsl_vec->owner == 0){
        gsl_vector_ushort_memcpy(this->gsl_vec.get(), a.gsl_vec.get());
    }
    return *this;
}

template<>
inline Vector_c& Vector_c::operator=(Vector_c&& a)
{
    if(this->gsl_vec == nullptr || this->gsl_vec->owner != 0){
        std::swap(this->gsl_vec, a.gsl_vec);
    }else if(this->gsl_vec->owner == 0){
        gsl_vector_char_memcpy(this->gsl_vec.get(), a.gsl_vec.get());
    }
    return *this;
}

template<>
inline Vector_uc& Vector_uc::operator=(Vector_uc&& a)
{
    if(this->gsl_vec == nullptr || this->gsl_vec->owner != 0){
        std::swap(this->gsl_vec, a.gsl_vec);
    }else if(this->gsl_vec->owner == 0){
        gsl_vector_uchar_memcpy(this->gsl_vec.get(), a.gsl_vec.get());
    }
    return *this;
}

template<>
inline Vector_cx& Vector_cx::operator=(Vector_cx&& a)
{
    if(this->gsl_vec == nullptr || this->gsl_vec->owner != 0){
        std::swap(this->gsl_vec, a.gsl_vec);
    }else if(this->gsl_vec->owner == 0){
        gsl_vector_complex_memcpy(this->gsl_vec.get(), a.gsl_vec.get());
    }
    return *this;
}

template<>
inline Vector_cxld& Vector_cxld::operator=(Vector_cxld&& a)
{
    if(this->gsl_vec == nullptr || this->gsl_vec->owner != 0){
        std::swap(this->gsl_vec, a.gsl_vec);
    }else if(this->gsl_vec->owner == 0){
        gsl_vector_complex_long_double_memcpy(this->gsl_vec.get(), a.gsl_vec.get());
    }
    return *this;
}

template<>
inline Vector_cxf& Vector_cxf::operator=(Vector_cxf&& a)
{
    if(this->gsl_vec == nullptr || this->gsl_vec->owner != 0){
        std::swap(this->gsl_vec, a.gsl_vec);
    }else if(this->gsl_vec->owner == 0){
        gsl_vector_complex_float_memcpy(this->gsl_vec.get(), a.gsl_vec.get());
    }
    return *this;
}

template<class T, class G, class A>
typename Vector_t<T, G, A>::size_type Vector_t<T, G, A>::dim() const{
    if(gsl_vec.get() != nullptr){
        return gsl_vec->size;
    }else{
        throw std::runtime_error("Taking size/dimension of uninitialized Vector!\n");
    }
}

template<class T, class G, class A>
inline typename Vector_t<T, G, A>::reference Vector_t<T, G, A>::
    operator[] (const typename Vector_t<T, G, A>::size_type index)
{
    return *(this->begin() + index);
}

template<class T, class G, class A>
inline typename Vector_t<T, G, A>::const_reference Vector_t<T, G, A>::
    operator[] (const typename Vector_t<T, G, A>::size_type index) const
{
    return *(this->begin() + index);
}

template<>
inline typename Vector_cx::const_reference Vector_cx::operator[]
    (const typename Vector_cx::size_type index) const
{
    return *gsl_vector_complex_ptr(this->gsl_vec.get(), index);
}

template<>
inline typename Vector_cxld::const_reference
Vector_cxld::operator[]
    (const typename Vector_cxld::size_type index) const
{
    return *gsl_vector_complex_long_double_ptr(this->gsl_vec.get(), index);
}

template<>
inline typename Vector_cxf::const_reference
Vector_cxf::operator[]
    (const typename Vector_cxf::size_type index) const
{
    return *gsl_vector_complex_float_ptr(this->gsl_vec.get(), index);
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
inline double Vector::dot(const Vector& b) const
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
inline float Vector_f::dot(const Vector_f& b) const
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
inline Complex Vector_cx::dot(const Vector_cx& b) const
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
inline Complex_ld Vector_cxld::dot(const Vector_cxld& b) const
{
    if(this->size() != b.size()){
        throw std::runtime_error("Error in dot. Dimensions of vectors do not match!\n");
    }
    Complex_ld res(static_cast<long double>(0.));
    for(Vector_cxld::size_type i = 0; i < this->size(); i++){
        res.re() += (*this)[i].dat[0]*b[i].dat[0] - (*this)[i].dat[1]*b[i].dat[1];
        res.im() += (*this)[i].dat[1]*b[i].dat[0] + (*this)[i].dat[0]*b[i].dat[0];
    }
    return res;
}

template<>
inline Complex_f Vector_cxf::dot(const Vector_cxf& b) const
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
    return std::sqrt(this->dot(*this));
}

template<> template<>
inline double Vector::norm<double>() const
{
    return gsl_blas_dnrm2(this->gsl_vec.get());
}

template<> template<>
inline float Vector_f::norm<float>() const
{
    return gsl_blas_snrm2(this->gsl_vec.get());
}

template<> template<>
inline double Vector_cx::norm<double>() const
{
    return gsl_blas_dznrm2(this->gsl_vec.get());
}

template<> template<>
inline float Vector_cxf::norm<float>() const
{
    return gsl_blas_scnrm2(this->gsl_vec.get());
}

template<> template<>
inline long double Vector_cxld::norm<long double>() const
{
    Complex_ld tmp;
    long double n{0};
    for(Vector_cxld::size_type i = 0; i < this->gsl_vec->size; i++){
        tmp = (*this)[i];
        n += tmp.re()*tmp.re() + tmp.im()*tmp.im();
    }
    return std::sqrt(n);
}

template <class T, class V, class A> template<class S>
void Vector_t<T, V, A>::normalize()
{
    *this /= static_cast<T>(this->norm<S>());
}

template<class T, class GSL_VEC, class A>
Vector_t<T, GSL_VEC, A> Vector_t<T, GSL_VEC, A>::cross(const Vector_t<T, GSL_VEC, A>& b) const
{
    if(this->size() != b.size()){
        throw std::runtime_error("Error in cross product!\nCross product "
        "(vector product) only defined for vectors of equal length!");
    } else if(this->size() != 3 || b.size() !=3){
        throw std::runtime_error("Error in cross product!\nCross product "
        "(vector product) only defined for vectors of length 3!");
    }
    T r1, r2, r3;
    r1 = static_cast<T>(T((*this)[1])*T(b[2]) - T((*this)[2])*T(b[1]));
    r2 = static_cast<T>(T((*this)[2])*T(b[0]) - T((*this)[0])*T(b[2]));
    r3 = static_cast<T>(T((*this)[0])*T(b[1]) - T((*this)[1])*T(b[0]));

    return Vector_t({r1, r2, r3});
}

template<>
inline Vector& Vector::operator+=(const Vector& b)
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
inline Vector_ld& Vector_ld::operator+=(const Vector_ld& b)
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
inline Vector_f& Vector_f::operator+=(const Vector_f& b)
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
inline Vector_i& Vector_i::operator+=(const Vector_i& b)
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
inline Vector_ui& Vector_ui::operator+=(const Vector_ui& b)
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
inline Vector_l& Vector_l::operator+=(const Vector_l& b)
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
inline Vector_ul& Vector_ul::operator+=(const Vector_ul& b)
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
inline Vector_s& Vector_s::operator+=(const Vector_s& b)
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
inline Vector_us& Vector_us::operator+=(const Vector_us& b)
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
inline Vector_c& Vector_c::operator+=(const Vector_c& b)
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
inline Vector_uc& Vector_uc::operator+=(const Vector_uc& b)
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
inline Vector_cx& Vector_cx::operator+=(const Vector_cx& b)
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
inline Vector_cxld& Vector_cxld::operator+=(const Vector_cxld& b)
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
inline Vector_cxf& Vector_cxf::operator+=(const Vector_cxf& b)
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
inline Vector& Vector::operator-=(const Vector& b)
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
inline Vector_ld& Vector_ld::operator-=(const Vector_ld& b)
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
inline Vector_f& Vector_f::operator-=(const Vector_f& b)
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
inline Vector_i& Vector_i::operator-=(const Vector_i& b)
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
inline Vector_ui& Vector_ui::operator-=(const Vector_ui& b)
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
inline Vector_l& Vector_l::operator-=(const Vector_l& b)
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
inline Vector_ul& Vector_ul::operator-=(const Vector_ul& b)
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
inline Vector_s& Vector_s::operator-=(const Vector_s& b)
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
inline Vector_us& Vector_us::operator-=(const Vector_us& b)
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
inline Vector_c& Vector_c::operator-=(const Vector_c& b)
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
inline Vector_uc& Vector_uc::operator-=(const Vector_uc& b)
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
inline Vector_cx& Vector_cx::operator-=(const Vector_cx& b)
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
inline Vector_cxld& Vector_cxld::operator-=(const Vector_cxld& b)
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
inline Vector_cxf& Vector_cxf::operator-=(const Vector_cxf& b)
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
inline Vector& Vector::operator*=(const Vector& b)
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
inline Vector_ld& Vector_ld::operator*=(const Vector_ld& b)
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
inline Vector_f& Vector_f::operator*=(const Vector_f& b)
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
inline Vector_i& Vector_i::operator*=(const Vector_i& b)
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
inline Vector_ui& Vector_ui::operator*=(const Vector_ui& b)
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
inline Vector_l& Vector_l::operator*=(const Vector_l& b)
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
inline Vector_ul& Vector_ul::operator*=(const Vector_ul& b)
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
inline Vector_s& Vector_s::operator*=(const Vector_s& b)
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
inline Vector_us& Vector_us::operator*=(const Vector_us& b)
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
inline Vector_c& Vector_c::operator*=(const Vector_c& b)
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
inline Vector_uc& Vector_uc::operator*=(const Vector_uc& b)
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
inline Vector_cx& Vector_cx::operator*=(const Vector_cx& b)
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
inline Vector_cxld& Vector_cxld::operator*=(const Vector_cxld& b)
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
inline Vector_cxf& Vector_cxf::operator*=(const Vector_cxf& b)
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
inline Vector& Vector::operator/=(const Vector& b)
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
inline Vector_ld& Vector_ld::operator/=(const Vector_ld& b)
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
inline Vector_f& Vector_f::operator/=(const Vector_f& b)
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
inline Vector_i& Vector_i::operator/=(const Vector_i& b)
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
inline Vector_ui& Vector_ui::operator/=(const Vector_ui& b)
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
inline Vector_l& Vector_l::operator/=(const Vector_l& b)
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
inline Vector_ul& Vector_ul::operator/=(const Vector_ul& b)
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
inline Vector_s& Vector_s::operator/=(const Vector_s& b)
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
inline Vector_us& Vector_us::operator/=(const Vector_us& b)
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
inline Vector_c& Vector_c::operator/=(const Vector_c& b)
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
inline Vector_uc& Vector_uc::operator/=(const Vector_uc& b)
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
inline Vector_cx& Vector_cx::operator/=(const Vector_cx& b)
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
inline Vector_cxld& Vector_cxld::operator/=(const Vector_cxld& b)
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
inline Vector_cxf& Vector_cxf::operator/=(const Vector_cxf& b)
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
inline Vector& Vector::operator*=(const double& b)
{
    int stat = gsl_vector_scale(this->gsl_vec.get(), b);
    if(stat){
		std::string error_str =   gsl_strerror(stat);
		throw std::runtime_error("Error in vector addition.\nGSL error: "
        + error_str);
	}
    return *this;
}

template<>
inline Vector_ld& Vector_ld::operator*=(const long double& b)
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
inline Vector_f& Vector_f::operator*=(const float& b)
{
    int stat = gsl_vector_float_scale(this->gsl_vec.get(), static_cast<double>(b));
    if(stat){
		std::string error_str =   gsl_strerror(stat);
		throw std::runtime_error("Error in vector addition.\nGSL error: "
        + error_str);
	}
    return *this;
}

template<>
inline Vector_i& Vector_i::operator*=(const int& b)
{
    int stat = gsl_vector_int_scale(this->gsl_vec.get(), b);
    if(stat){
		std::string error_str =   gsl_strerror(stat);
		throw std::runtime_error("Error in vector addition.\nGSL error: "
        + error_str);
	}
    return *this;
}

template<>
inline Vector_ui& Vector_ui::operator*=(const unsigned int& b)
{
    int stat = gsl_vector_uint_scale(this->gsl_vec.get(), b);
    if(stat){
		std::string error_str =   gsl_strerror(stat);
		throw std::runtime_error("Error in vector addition.\nGSL error: "
        + error_str);
	}
    return *this;
}

template<>
inline Vector_l& Vector_l::operator*=(const long& b)
{
    int stat = gsl_vector_long_scale(this->gsl_vec.get(), static_cast<double>(b));
    if(stat){
		std::string error_str =   gsl_strerror(stat);
		throw std::runtime_error("Error in vector addition.\nGSL error: "
        + error_str);
	}
    return *this;
}

template<>
inline Vector_ul& Vector_ul::operator*=(const unsigned long& b)
{
    int stat = gsl_vector_ulong_scale(this->gsl_vec.get(), static_cast<double>(b));
    if(stat){
		std::string error_str =   gsl_strerror(stat);
		throw std::runtime_error("Error in vector addition.\nGSL error: "
        + error_str);
	}
    return *this;
}

template<>
inline Vector_s& Vector_s::operator*=(const short& b)
{
    int stat = gsl_vector_short_scale(this->gsl_vec.get(), b);
    if(stat){
		std::string error_str =   gsl_strerror(stat);
		throw std::runtime_error("Error in vector addition.\nGSL error: "
        + error_str);
	}
    return *this;
}

template<>
inline Vector_us& Vector_us::operator*=(const unsigned short& b)
{
    int stat = gsl_vector_ushort_scale(this->gsl_vec.get(), b);
    if(stat){
		std::string error_str =   gsl_strerror(stat);
		throw std::runtime_error("Error in vector addition.\nGSL error: "
        + error_str);
	}
    return *this;
}


template<>
inline Vector_c& Vector_c::operator*=(const char& b)
{
    int stat = gsl_vector_char_scale(this->gsl_vec.get(), b);
    if(stat){
		std::string error_str =   gsl_strerror(stat);
		throw std::runtime_error("Error in vector addition.\nGSL error: "
        + error_str);
	}
    return *this;
}

template<>
inline Vector_uc& Vector_uc::operator*=(const unsigned char& b)
{
    int stat = gsl_vector_uchar_scale(this->gsl_vec.get(), b);
    if(stat){
		std::string error_str =   gsl_strerror(stat);
		throw std::runtime_error("Error in vector addition.\nGSL error: "
        + error_str);
	}
    return *this;
}

template<>
inline Vector_cx& Vector_cx::operator*=(const Complex& b)
{
    int stat = gsl_vector_complex_scale(this->gsl_vec.get(), *b.gsl_c.get());
    if(stat){
		std::string error_str =   gsl_strerror(stat);
		throw std::runtime_error("Error in vector addition.\nGSL error: "
        + error_str);
	}
    return *this;
}

template<>
inline Vector_cxld& Vector_cxld::operator*=(const Complex_ld& b)
{
    int stat = gsl_vector_complex_long_double_scale(this->gsl_vec.get(), *b.gsl_c.get());
    if(stat){
		std::string error_str =   gsl_strerror(stat);
		throw std::runtime_error("Error in vector addition.\nGSL error: "
        + error_str);
	}
    return *this;
}

template<>
inline Vector_cxf& Vector_cxf::operator*=(const Complex_f& b)
{
    int stat = gsl_vector_complex_float_scale(this->gsl_vec.get(), *b.gsl_c.get());
    if(stat){
		std::string error_str =   gsl_strerror(stat);
		throw std::runtime_error("Error in vector addition.\nGSL error: "
        + error_str);
	}
    return *this;
}

template<>
inline Vector& Vector::operator/=(const double& b)
{
    int stat = gsl_vector_scale(this->gsl_vec.get(), 1./b);
    if(stat){
		std::string error_str =   gsl_strerror(stat);
		throw std::runtime_error("Error in vector addition.\nGSL error: "
        + error_str);
	}
    return *this;
}

template<>
inline Vector_ld& Vector_ld::operator/=(const long double& b)
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
inline Vector_f& Vector_f::operator/=(const float& b)
{
    int stat = gsl_vector_float_scale(this->gsl_vec.get(), 1./static_cast<double>(b));
    if(stat){
		std::string error_str =   gsl_strerror(stat);
		throw std::runtime_error("Error in vector addition.\nGSL error: "
        + error_str);
	}
    return *this;
}

template<>
inline Vector_i& Vector_i::operator/=(const int& b)
{
    int stat = gsl_vector_int_scale(this->gsl_vec.get(), 1./b);
    if(stat){
		std::string error_str =   gsl_strerror(stat);
		throw std::runtime_error("Error in vector addition.\nGSL error: "
        + error_str);
	}
    return *this;
}

template<>
inline Vector_ui& Vector_ui::operator/=(const unsigned int& b)
{
    int stat = gsl_vector_uint_scale(this->gsl_vec.get(), 1./b);
    if(stat){
		std::string error_str =   gsl_strerror(stat);
		throw std::runtime_error("Error in vector addition.\nGSL error: "
        + error_str);
	}
    return *this;
}

template<>
inline Vector_l& Vector_l::operator/=(const long& b)
{
    int stat = gsl_vector_long_scale(this->gsl_vec.get(), 1./static_cast<double>(b));
    if(stat){
		std::string error_str =   gsl_strerror(stat);
		throw std::runtime_error("Error in vector addition.\nGSL error: "
        + error_str);
	}
    return *this;
}

template<>
inline Vector_ul& Vector_ul::operator/=(const unsigned long& b)
{
    int stat = gsl_vector_ulong_scale(this->gsl_vec.get(), 1./static_cast<double>(b));
    if(stat){
		std::string error_str =   gsl_strerror(stat);
		throw std::runtime_error("Error in vector addition.\nGSL error: "
        + error_str);
	}
    return *this;
}

template<>
inline Vector_s& Vector_s::operator/=(const short& b)
{
    int stat = gsl_vector_short_scale(this->gsl_vec.get(), 1./b);
    if(stat){
		std::string error_str =   gsl_strerror(stat);
		throw std::runtime_error("Error in vector addition.\nGSL error: "
        + error_str);
	}
    return *this;
}

template<>
inline Vector_us& Vector_us::operator/=(const unsigned short& b)
{
    int stat = gsl_vector_ushort_scale(this->gsl_vec.get(), 1./b);
    if(stat){
		std::string error_str =   gsl_strerror(stat);
		throw std::runtime_error("Error in vector addition.\nGSL error: "
        + error_str);
	}
    return *this;
}


template<>
inline Vector_c& Vector_c::operator/=(const char& b)
{
    int stat = gsl_vector_char_scale(this->gsl_vec.get(), 1./b);
    if(stat){
		std::string error_str =   gsl_strerror(stat);
		throw std::runtime_error("Error in vector addition.\nGSL error: "
        + error_str);
	}
    return *this;
}

template<>
inline Vector_uc& Vector_uc::operator/=(const unsigned char& b)
{
    int stat = gsl_vector_uchar_scale(this->gsl_vec.get(), 1./b);
    if(stat){
		std::string error_str =   gsl_strerror(stat);
		throw std::runtime_error("Error in vector addition.\nGSL error: "
        + error_str);
	}
    return *this;
}

template<>
inline Vector_cx& Vector_cx::operator/=(const Complex& b)
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
inline Vector_cxld& Vector_cxld::operator/=(const Complex_ld& b)
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
inline Vector_cxf& Vector_cxf::operator/=(const Complex_f& b)
{
    int stat = gsl_vector_complex_float_scale(this->gsl_vec.get(), *(1./b).gsl_c);
    if(stat){
		std::string error_str =   gsl_strerror(stat);
		throw std::runtime_error("Error in vector addition.\nGSL error: "
        + error_str);
	}
    return *this;
}

template<class T, class G, class A>
Vector_t<T, G, A> Vector_t<T, G, A>::operator+(const Vector_t<T, G, A>& b) const
{
    Vector_t<T, G, A>tmp(this->size());
    tmp.copy(*this);
    return tmp += b;
}

template<class T, class G, class A>
Vector_t<T, G, A> Vector_t<T, G, A>::operator-(const Vector_t<T, G, A>& b) const
{
    Vector_t<T, G, A>tmp(this->size());
    tmp.copy(*this);
    return tmp -= b;
}

template<class T, class G, class A>
Vector_t<T, G, A> Vector_t<T, G, A>::operator*(const Vector_t<T, G, A>& b) const
{
    Vector_t<T, G, A>tmp(this->size());
    tmp.copy(*this);
    return tmp *= b;
}

template<class T, class G, class A>
Vector_t<T, G, A> Vector_t<T, G, A>::operator/(const Vector_t<T, G, A>& b) const
{
    Vector_t<T, G, A>tmp(this->size());
    tmp.copy(*this);
    return tmp /= b;
}

template<class T, class G, class A>
Vector_t<T, G, A> Vector_t<T, G, A>::operator*(const T s) const
{
    Vector_t<T, G, A>tmp(this->size());
    tmp.copy(*this);
    return tmp *= s;
}

template<class T, class G, class A>
Vector_t<T, G, A> Vector_t<T, G, A>::operator/(const T s) const
{
    Vector_t<T, G, A>tmp(this->size());
    tmp.copy(*this);
    return tmp /= s;
}

template<class T, class G, class A>
Vector_t<T, G, A> Vector_t<T, G, A>::operator-() const
{
    Vector_t<T, G, A> tmp(this->size());
    return tmp - *this;
}


template<> template<>
inline Vector Vector::operator*<gsl_matrix>(const Matrix_t<double, gsl_matrix, gsl_vector, std::allocator<double>>& m)
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
inline Vector_f Vector_f::operator*<gsl_matrix_float>(const Matrix_t<float, gsl_matrix_float, gsl_vector_float>& m)
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
inline Vector_cx Vector_cx::operator*<gsl_matrix_complex>(const Matrix_t<Complex, gsl_matrix_complex, gsl_vector_complex, std::allocator<gsl_complex>>& m)
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
inline Vector_cxf Vector_cxf::operator*<gsl_matrix_complex_float>(const Matrix_t<Complex_f, gsl_matrix_complex_float, gsl_vector_complex_float, std::allocator<gsl_complex_float>>& m)
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
inline bool Vector::operator==(const Vector& b) const
{
    if(this->gsl_vec.get() == nullptr && b.gsl_vec.get() == nullptr){
        return true;
    }else if(this->gsl_vec.get() == nullptr || b.gsl_vec.get() == nullptr){
        return false;
    }
    return gsl_vector_equal(this->gsl_vec.get(), b.gsl_vec.get());
}

template<>
inline bool Vector_ld::operator==(const Vector_ld& b) const
{
    if(this->gsl_vec.get() == nullptr && b.gsl_vec.get() == nullptr){
        return true;
    }else if(this->gsl_vec.get() == nullptr || b.gsl_vec.get() == nullptr){
        return false;
    }
    return gsl_vector_long_double_equal(this->gsl_vec.get(), b.gsl_vec.get());
}

template<>
inline bool Vector_f::operator==(const Vector_f& b) const
{
    if(this->gsl_vec.get() == nullptr && b.gsl_vec.get() == nullptr){
        return true;
    }else if(this->gsl_vec.get() == nullptr || b.gsl_vec.get() == nullptr){
        return false;
    }
    return gsl_vector_float_equal(this->gsl_vec.get(), b.gsl_vec.get());
}

template<>
inline bool Vector_i::operator==(const Vector_i& b) const
{
    if(this->gsl_vec.get() == nullptr && b.gsl_vec.get() == nullptr){
        return true;
    }else if(this->gsl_vec.get() == nullptr || b.gsl_vec.get() == nullptr){
        return false;
    }
    return gsl_vector_int_equal(this->gsl_vec.get(), b.gsl_vec.get());
}

template<>
inline bool Vector_ui::operator==(const Vector_ui& b) const
{
    if(this->gsl_vec.get() == nullptr && b.gsl_vec.get() == nullptr){
        return true;
    }else if(this->gsl_vec.get() == nullptr || b.gsl_vec.get() == nullptr){
        return false;
    }
    return gsl_vector_uint_equal(this->gsl_vec.get(), b.gsl_vec.get());
}

template<>
inline bool Vector_l::operator==(const Vector_l& b) const
{
    if(this->gsl_vec.get() == nullptr && b.gsl_vec.get() == nullptr){
        return true;
    }else if(this->gsl_vec.get() == nullptr || b.gsl_vec.get() == nullptr){
        return false;
    }
    return gsl_vector_long_equal(this->gsl_vec.get(), b.gsl_vec.get());
}

template<>
inline bool Vector_ul::operator==(const Vector_ul& b) const
{
    if(this->gsl_vec.get() == nullptr && b.gsl_vec.get() == nullptr){
        return true;
    }else if(this->gsl_vec.get() == nullptr || b.gsl_vec.get() == nullptr){
        return false;
    }
    return gsl_vector_ulong_equal(this->gsl_vec.get(), b.gsl_vec.get());
}

template<>
inline bool Vector_s::operator==(const Vector_s& b) const
{
    if(this->gsl_vec.get() == nullptr && b.gsl_vec.get() == nullptr){
        return true;
    }else if(this->gsl_vec.get() == nullptr || b.gsl_vec.get() == nullptr){
        return false;
    }
    return gsl_vector_short_equal(this->gsl_vec.get(), b.gsl_vec.get());
}

template<>
inline bool Vector_us::operator==(const Vector_us& b) const
{
    if(this->gsl_vec.get() == nullptr && b.gsl_vec.get() == nullptr){
        return true;
    }else if(this->gsl_vec.get() == nullptr || b.gsl_vec.get() == nullptr){
        return false;
    }
    return gsl_vector_ushort_equal(this->gsl_vec.get(), b.gsl_vec.get());
}

template<>
inline bool Vector_c::operator==(const Vector_c& b) const
{
    if(this->gsl_vec.get() == nullptr && b.gsl_vec.get() == nullptr){
        return true;
    }else if(this->gsl_vec.get() == nullptr || b.gsl_vec.get() == nullptr){
        return false;
    }
    return gsl_vector_char_equal(this->gsl_vec.get(), b.gsl_vec.get());
}

template<>
inline bool Vector_uc::operator==(const Vector_uc& b) const
{
    if(this->gsl_vec.get() == nullptr && b.gsl_vec.get() == nullptr){
        return true;
    }else if(this->gsl_vec.get() == nullptr || b.gsl_vec.get() == nullptr){
        return false;
    }
    return gsl_vector_uchar_equal(this->gsl_vec.get(), b.gsl_vec.get());
}

template<>
inline bool Vector_cx::operator==(const Vector_cx& b) const
{
    if(this->gsl_vec.get() == nullptr && b.gsl_vec.get() == nullptr){
        return true;
    }else if(this->gsl_vec.get() == nullptr || b.gsl_vec.get() == nullptr){
        return false;
    }
    return gsl_vector_complex_equal(this->gsl_vec.get(), b.gsl_vec.get());
}

template<>
inline bool Vector_cxld::operator==(const Vector_cxld& b) const
{
    if(this->gsl_vec.get() == nullptr && b.gsl_vec.get() == nullptr){
        return true;
    }else if(this->gsl_vec.get() == nullptr || b.gsl_vec.get() == nullptr){
        return false;
    }
    return gsl_vector_complex_long_double_equal(this->gsl_vec.get(), b.gsl_vec.get());
}

template<>
inline bool Vector_cxf::operator==(const Vector_cxf& b) const
{
    if(this->gsl_vec.get() == nullptr && b.gsl_vec.get() == nullptr){
        return true;
    }else if(this->gsl_vec.get() == nullptr || b.gsl_vec.get() == nullptr){
        return false;
    }
    return gsl_vector_complex_float_equal(this->gsl_vec.get(), b.gsl_vec.get());
}

template<class T, class G, class A>
bool Vector_t<T, G, A>::operator!=(const Vector_t<T, G, A>& b) const
{
    return !(*this == b);
}


template<class T, class G, class A>
bool Vector_t<T, G, A>::iterator::operator==(const Vector_t<T, G, A>::iterator& b) const
{
    return (this->data_m == b.data_m) && (this->stride == b.stride);
}

template<class T, class G, class A>
bool Vector_t<T, G, A>::iterator::operator!=(const Vector_t<T, G, A>::iterator& b) const
{
    return !(*this == b);
}

template<class T, class G, class A>
bool Vector_t<T, G, A>::iterator::operator<(const Vector_t<T, G, A>::iterator& b) const
{
    return (this->data_m < b.data_m);
}

template<class T, class G, class A>
bool Vector_t<T, G, A>::iterator::operator>(const Vector_t<T, G, A>::iterator& b) const
{
    return (this->data_m > b.data_m);
}

template<class T, class G, class A>
bool Vector_t<T, G, A>::iterator::operator<=(const Vector_t<T, G, A>::iterator& b) const
{
    return !(this->data_m > b.data_m);
}

template<class T, class G, class A>
bool Vector_t<T, G, A>::iterator::operator>=(const Vector_t<T, G, A>::iterator& b) const
{
    return !(this->data_m < b.data_m);
}

template<class T, class G, class A>
typename Vector_t<T, G, A>::iterator& Vector_t<T, G, A>::iterator::operator++()
{
    this->data_m += this->stride;
    return *this;
}

template<class T, class G, class A>
typename Vector_t<T, G, A>::iterator Vector_t<T, G, A>::iterator::operator++(int)
{
    Vector_t<T, G, A>::iterator tmp = *this;
    ++(*this);
    return tmp;
}

template<class T, class G, class A>
typename Vector_t<T, G, A>::iterator& Vector_t<T, G, A>::iterator::operator--()
{
    this->data_m -= this->stride;
    return *this;
}

template<class T, class G, class A>
typename Vector_t<T, G, A>::iterator Vector_t<T, G, A>::iterator::operator--(int)
{
    Vector_t<T, G, A>::iterator tmp = *this;
    --(*this);
    return tmp;
}

template<class T, class G, class A>
typename Vector_t<T, G, A>::iterator& Vector_t<T, G, A>::iterator::
    operator+=(Vector_t<T, G, A>::size_type n)
{
    this->data_m += n*this->stride;
    return *this;
}

template<class T, class G, class A>
typename Vector_t<T, G, A>::iterator Vector_t<T, G, A>::iterator::
    operator+(Vector_t<T, G, A>::size_type n) const
{
    Vector_t<T, G, A>::iterator tmp = *this;
    tmp += n;
    return tmp;
}

template<class T, class G, class A>
typename Vector_t<T, G, A>::iterator& Vector_t<T, G, A>::iterator::
    operator-=(Vector_t<T, G, A>::size_type n)
{
    this->data_m -= n*this->stride;
    return *this;
}

template<class T, class G, class A>
typename Vector_t<T, G, A>::iterator Vector_t<T, G, A>::iterator::
    operator-(Vector_t<T, G, A>::size_type n) const
{
    Vector_t<T, G, A>::iterator tmp = *this;
    tmp -= n;
    return tmp;
}

template<class T, class G, class A>
typename Vector_t<T, G, A>::iterator::difference_type Vector_t<T, G, A>::iterator::
    operator-(iterator b) const
{
    return this->data_m - b.data_m;
}

template<class T, class G, class A>
typename Vector_t<T, G, A>::iterator::reference Vector_t<T, G, A>::iterator::
    operator*() const
{
    return *this->data_m;
}

template<class T, class G, class A>
bool Vector_t<T, G, A>::const_iterator::operator==(const Vector_t<T, G, A>::const_iterator& b) const
{
    return (this->data_m == b.data_m) && (this->stride == b.stride);
}

template<class T, class G, class A>
bool Vector_t<T, G, A>::const_iterator::operator!=(const Vector_t<T, G, A>::const_iterator& b) const
{
    return !(*this == b);
}

template<class T, class G, class A>
bool Vector_t<T, G, A>::const_iterator::operator<(const Vector_t<T, G, A>::const_iterator& b) const
{
    return (this->data_m < b.data_m);
}

template<class T, class G, class A>
bool Vector_t<T, G, A>::const_iterator::operator>(const Vector_t<T, G, A>::const_iterator& b) const
{
    return (this->data_m > b.data_m);
}

template<class T, class G, class A>
bool Vector_t<T, G, A>::const_iterator::operator<=(const Vector_t<T, G, A>::const_iterator& b) const
{
    return !(this->data_m > b.data_m);
}

template<class T, class G, class A>
bool Vector_t<T, G, A>::const_iterator::operator>=(const Vector_t<T, G, A>::const_iterator& b) const
{
    return !(this->data_m < b.data_m);
}

template<class T, class G, class A>
typename Vector_t<T, G, A>::const_iterator& Vector_t<T, G, A>::const_iterator::operator++()
{
    this->data_m += this->stride;
    return *this;
}

template<class T, class G, class A>
typename Vector_t<T, G, A>::const_iterator Vector_t<T, G, A>::const_iterator::operator++(int)
{
    Vector_t<T, G, A>::const_iterator tmp = *this;
    ++(*this);
    return tmp;
}

template<class T, class G, class A>
typename Vector_t<T, G, A>::const_iterator& Vector_t<T, G, A>::const_iterator::operator--()
{
    this->data_m -= this->stride;
    return *this;
}

template<class T, class G, class A>
typename Vector_t<T, G, A>::const_iterator Vector_t<T, G, A>::const_iterator::operator--(int)
{
    Vector_t<T, G, A>::const_iterator tmp = *this;
    --(*this);
    return tmp;
}

template<class T, class G, class A>
typename Vector_t<T, G, A>::const_iterator& Vector_t<T, G, A>::const_iterator::
    operator+=(Vector_t<T, G, A>::size_type n)
{
    this->data_m += n*this->stride;
    return *this;
}

template<class T, class G, class A>
typename Vector_t<T, G, A>::const_iterator Vector_t<T, G, A>::const_iterator::
    operator+(Vector_t<T, G, A>::size_type n) const
{
    Vector_t<T, G, A>::const_iterator tmp = *this;
    tmp += n;
    return tmp;
}

template<class T, class G, class A>
typename Vector_t<T, G, A>::const_iterator& Vector_t<T, G, A>::const_iterator::
    operator-=(Vector_t<T, G, A>::size_type n)
{
    this->data_m -= n*this->stride;
    return *this;
}

template<class T, class G, class A>
typename Vector_t<T, G, A>::const_iterator Vector_t<T, G, A>::const_iterator::
    operator-(Vector_t<T, G, A>::size_type n) const
{
    Vector_t<T, G, A>::const_iterator tmp = *this;
    tmp -= n;
    return tmp;
}

template<class T, class G, class A>
typename Vector_t<T, G, A>::const_iterator::difference_type Vector_t<T, G, A>::const_iterator::
    operator-(const_iterator b) const
{
    return this->data_m - b.data_m;
}

template<class T, class G, class A>
typename Vector_t<T, G, A>::const_iterator::reference Vector_t<T, G, A>::const_iterator::
    operator*() const
{
    return *this->data_m;
}

template<>
inline typename Vector::iterator Vector::begin()
{
    if(this->gsl_vec.get() == nullptr){
        throw std::runtime_error("Calling begin() on uninitialized Vector");
    }
    return Vector::iterator(gsl_vector_ptr(gsl_vec.get(), 0), this->gsl_vec->stride);
}

template<>
inline typename Vector_ld::iterator Vector_ld::begin()
{
    if(this->gsl_vec.get() == nullptr){
        throw std::runtime_error("Calling begin() on uninitialized Vector");
    }
    return iterator(gsl_vector_long_double_ptr(gsl_vec.get(), 0), this->gsl_vec->stride);
}

template<>
inline typename Vector_f::iterator Vector_f::begin()
{
    if(this->gsl_vec.get() == nullptr){
        throw std::runtime_error("Calling begin() on uninitialized Vector");
    }
    return iterator(gsl_vector_float_ptr(gsl_vec.get(), 0), this->gsl_vec->stride);
}

template<>
inline typename Vector_i::iterator Vector_i::begin()
{
    if(this->gsl_vec.get() == nullptr){
        throw std::runtime_error("Calling begin() on uninitialized Vector");
    }
    return iterator(gsl_vector_int_ptr(gsl_vec.get(), 0), this->gsl_vec->stride);
}

template<>
inline typename Vector_ui::iterator Vector_ui::begin()
{
    if(this->gsl_vec.get() == nullptr){
        throw std::runtime_error("Calling begin() on uninitialized Vector");
    }
    return iterator(gsl_vector_uint_ptr(gsl_vec.get(), 0), this->gsl_vec->stride);
}

template<>
inline typename Vector_l::iterator Vector_l::begin()
{
    if(this->gsl_vec.get() == nullptr){
        throw std::runtime_error("Calling begin() on uninitialized Vector");
    }
    return iterator(gsl_vector_long_ptr(gsl_vec.get(), 0), this->gsl_vec->stride);
}

template<>
inline typename Vector_ul::iterator Vector_ul::begin()
{
    if(this->gsl_vec.get() == nullptr){
        throw std::runtime_error("Calling begin() on uninitialized Vector");
    }
    return iterator(gsl_vector_ulong_ptr(gsl_vec.get(), 0), this->gsl_vec->stride);
}

template<>
inline typename Vector_s::iterator Vector_s::begin()
{
    if(this->gsl_vec.get() == nullptr){
        throw std::runtime_error("Calling begin() on uninitialized Vector");
    }
    return iterator(gsl_vector_short_ptr(gsl_vec.get(), 0), this->gsl_vec->stride);
}

template<>
inline typename Vector_us::iterator Vector_us::begin()
{
    if(this->gsl_vec.get() == nullptr){
        throw std::runtime_error("Calling begin() on uninitialized Vector");
    }
    return iterator(gsl_vector_ushort_ptr(gsl_vec.get(), 0), this->gsl_vec->stride);
}

template<>
inline typename Vector_c::iterator Vector_c::begin()
{
    if(this->gsl_vec.get() == nullptr){
        throw std::runtime_error("Calling begin() on uninitialized Vector");
    }
    return iterator(gsl_vector_char_ptr(gsl_vec.get(), 0), this->gsl_vec->stride);
}

template<>
inline typename Vector_uc::iterator Vector_uc::begin()
{
    if(this->gsl_vec.get() == nullptr){
        throw std::runtime_error("Calling begin() on uninitialized Vector");
    }
    return iterator(gsl_vector_uchar_ptr(gsl_vec.get(), 0), this->gsl_vec->stride);
}

template<>
inline typename Vector_cx::iterator Vector_cx::begin()
{
    if(this->gsl_vec.get() == nullptr){
        throw std::runtime_error("Calling begin() on uninitialized Vector");
    }
    return iterator(gsl_vector_complex_ptr(gsl_vec.get(), 0), this->gsl_vec->stride);
}

template<>
inline typename Vector_cxld::iterator Vector_cxld::begin()
{
    if(this->gsl_vec.get() == nullptr){
        throw std::runtime_error("Calling begin() on uninitialized Vector");
    }
    return iterator(gsl_vector_complex_long_double_ptr(gsl_vec.get(), 0), this->gsl_vec->stride);
}

template<>
inline typename Vector_cxf::iterator Vector_cxf::begin()
{
    if(this->gsl_vec.get() == nullptr){
        throw std::runtime_error("Calling begin() on uninitialized Vector");
    }
    return iterator(gsl_vector_complex_float_ptr(gsl_vec.get(), 0), this->gsl_vec->stride);
}

template<>
inline typename Vector::const_iterator Vector::begin() const
{
    if(this->gsl_vec.get() == nullptr){
        throw std::runtime_error("Calling begin() on uninitialized Vector");
    }
    return const_iterator(gsl_vector_ptr(gsl_vec.get(), 0), this->gsl_vec->stride);
}

template<>
inline typename Vector_ld::const_iterator Vector_ld::begin() const
{
    if(this->gsl_vec.get() == nullptr){
        throw std::runtime_error("Calling begin() on uninitialized Vector");
    }
    return const_iterator(gsl_vector_long_double_ptr(gsl_vec.get(), 0), this->gsl_vec->stride);
}

template<>
inline typename Vector_f::const_iterator Vector_f::begin() const
{
    if(this->gsl_vec.get() == nullptr){
        throw std::runtime_error("Calling begin() on uninitialized Vector");
    }
    return const_iterator(gsl_vector_float_ptr(gsl_vec.get(), 0), this->gsl_vec->stride);
}

template<>
inline typename Vector_i::const_iterator Vector_i::begin() const
{
    if(this->gsl_vec.get() == nullptr){
        throw std::runtime_error("Calling begin() on uninitialized Vector");
    }
    return const_iterator(gsl_vector_int_ptr(gsl_vec.get(), 0), this->gsl_vec->stride);
}

template<>
inline typename Vector_ui::const_iterator Vector_ui::begin() const
{
    if(this->gsl_vec.get() == nullptr){
        throw std::runtime_error("Calling begin() on uninitialized Vector");
    }
    return const_iterator(gsl_vector_uint_ptr(gsl_vec.get(), 0), this->gsl_vec->stride);
}

template<>
inline typename Vector_l::const_iterator Vector_l::begin() const
{
    if(this->gsl_vec.get() == nullptr){
        throw std::runtime_error("Calling begin() on uninitialized Vector");
    }
    return const_iterator(gsl_vector_long_ptr(gsl_vec.get(), 0), this->gsl_vec->stride);
}

template<>
inline typename Vector_ul::const_iterator Vector_ul::begin() const
{
    if(this->gsl_vec.get() == nullptr){
        throw std::runtime_error("Calling begin() on uninitialized Vector");
    }
    return const_iterator(gsl_vector_ulong_ptr(gsl_vec.get(), 0), this->gsl_vec->stride);
}

template<>
inline typename Vector_s::const_iterator Vector_s::begin() const
{
    if(this->gsl_vec.get() == nullptr){
        throw std::runtime_error("Calling begin() on uninitialized Vector");
    }
    return const_iterator(gsl_vector_short_ptr(gsl_vec.get(), 0), this->gsl_vec->stride);
}

template<>
inline typename Vector_us::const_iterator Vector_us::begin() const
{
    if(this->gsl_vec.get() == nullptr){
        throw std::runtime_error("Calling begin() on uninitialized Vector");
    }
    return const_iterator(gsl_vector_ushort_ptr(gsl_vec.get(), 0), this->gsl_vec->stride);
}

template<>
inline typename Vector_c::const_iterator Vector_c::begin() const
{
    if(this->gsl_vec.get() == nullptr){
        throw std::runtime_error("Calling begin() on uninitialized Vector");
    }
    return const_iterator(gsl_vector_char_ptr(gsl_vec.get(), 0), this->gsl_vec->stride);
}

template<>
inline typename Vector_uc::const_iterator Vector_uc::begin() const
{
    if(this->gsl_vec.get() == nullptr){
        throw std::runtime_error("Calling begin() on uninitialized Vector");
    }
    return const_iterator(gsl_vector_uchar_ptr(gsl_vec.get(), 0), this->gsl_vec->stride);
}

template<>
inline typename Vector_cx::const_iterator Vector_cx::begin() const
{
    if(this->gsl_vec.get() == nullptr){
        throw std::runtime_error("Calling begin() on uninitialized Vector");
    }
    return const_iterator(gsl_vector_complex_ptr(gsl_vec.get(), 0), this->gsl_vec->stride);
}

template<>
inline typename Vector_cxld::const_iterator Vector_cxld::begin() const
{
    if(this->gsl_vec.get() == nullptr){
        throw std::runtime_error("Calling begin() on uninitialized Vector");
    }
    return const_iterator(gsl_vector_complex_long_double_ptr(gsl_vec.get(), 0), this->gsl_vec->stride);
}

template<>
inline typename Vector_cxf::const_iterator Vector_cxf::begin() const
{
    if(this->gsl_vec.get() == nullptr){
        throw std::runtime_error("Calling begin() on uninitialized Vector");
    }
    return const_iterator(gsl_vector_complex_float_ptr(gsl_vec.get(), 0), this->gsl_vec->stride);
}



template<>
inline typename Vector::const_iterator Vector::cbegin() const
{
    if(this->gsl_vec.get() == nullptr){
        throw std::runtime_error("Calling begin() on uninitialized Vector");
    }
    return const_iterator(gsl_vector_ptr(gsl_vec.get(), 0), this->gsl_vec->stride);
}

template<>
inline typename Vector_ld::const_iterator Vector_ld::cbegin() const
{
    if(this->gsl_vec.get() == nullptr){
        throw std::runtime_error("Calling begin() on uninitialized Vector");
    }
    return const_iterator(gsl_vector_long_double_ptr(gsl_vec.get(), 0), this->gsl_vec->stride);
}

template<>
inline typename Vector_f::const_iterator Vector_f::cbegin() const
{
    if(this->gsl_vec.get() == nullptr){
        throw std::runtime_error("Calling begin() on uninitialized Vector");
    }
    return const_iterator(gsl_vector_float_ptr(gsl_vec.get(), 0), this->gsl_vec->stride);
}

template<>
inline typename Vector_i::const_iterator Vector_i::cbegin() const
{
    if(this->gsl_vec.get() == nullptr){
        throw std::runtime_error("Calling begin() on uninitialized Vector");
    }
    return const_iterator(gsl_vector_int_ptr(gsl_vec.get(), 0), this->gsl_vec->stride);
}

template<>
inline typename Vector_ui::const_iterator Vector_ui::cbegin() const
{
    if(this->gsl_vec.get() == nullptr){
        throw std::runtime_error("Calling begin() on uninitialized Vector");
    }
    return const_iterator(gsl_vector_uint_ptr(gsl_vec.get(), 0), this->gsl_vec->stride);
}

template<>
inline typename Vector_l::const_iterator Vector_l::cbegin() const
{
    if(this->gsl_vec.get() == nullptr){
        throw std::runtime_error("Calling begin() on uninitialized Vector");
    }
    return const_iterator(gsl_vector_long_ptr(gsl_vec.get(), 0), this->gsl_vec->stride);
}

template<>
inline typename Vector_ul::const_iterator Vector_ul::cbegin() const
{
    if(this->gsl_vec.get() == nullptr){
        throw std::runtime_error("Calling begin() on uninitialized Vector");
    }
    return const_iterator(gsl_vector_ulong_ptr(gsl_vec.get(), 0), this->gsl_vec->stride);
}

template<>
inline typename Vector_s::const_iterator Vector_s::cbegin() const
{
    if(this->gsl_vec.get() == nullptr){
        throw std::runtime_error("Calling begin() on uninitialized Vector");
    }
    return const_iterator(gsl_vector_short_ptr(gsl_vec.get(), 0), this->gsl_vec->stride);
}

template<>
inline typename Vector_us::const_iterator Vector_us::cbegin() const
{
    if(this->gsl_vec.get() == nullptr){
        throw std::runtime_error("Calling begin() on uninitialized Vector");
    }
    return const_iterator(gsl_vector_ushort_ptr(gsl_vec.get(), 0), this->gsl_vec->stride);
}

template<>
inline typename Vector_c::const_iterator Vector_c::cbegin() const
{
    if(this->gsl_vec.get() == nullptr){
        throw std::runtime_error("Calling begin() on uninitialized Vector");
    }
    return const_iterator(gsl_vector_char_ptr(gsl_vec.get(), 0), this->gsl_vec->stride);
}

template<>
inline typename Vector_uc::const_iterator Vector_uc::cbegin() const
{
    if(this->gsl_vec.get() == nullptr){
        throw std::runtime_error("Calling begin() on uninitialized Vector");
    }
    return const_iterator(gsl_vector_uchar_ptr(gsl_vec.get(), 0), this->gsl_vec->stride);
}

template<>
inline typename Vector_cx::const_iterator Vector_cx::cbegin() const
{
    if(this->gsl_vec.get() == nullptr){
        throw std::runtime_error("Calling begin() on uninitialized Vector");
    }
    return const_iterator(gsl_vector_complex_ptr(gsl_vec.get(), 0), this->gsl_vec->stride);
}

template<>
inline typename Vector_cxld::const_iterator Vector_cxld::cbegin() const
{
    if(this->gsl_vec.get() == nullptr){
        throw std::runtime_error("Calling begin() on uninitialized Vector");
    }
    return const_iterator(gsl_vector_complex_long_double_ptr(gsl_vec.get(), 0), this->gsl_vec->stride);
}

template<>
inline typename Vector_cxf::const_iterator Vector_cxf::cbegin() const
{
    if(this->gsl_vec.get() == nullptr){
        throw std::runtime_error("Calling begin() on uninitialized Vector");
    }
    return const_iterator(gsl_vector_complex_float_ptr(gsl_vec.get(), 0), this->gsl_vec->stride);
}

template<class T, class G, class A>
typename Vector_t<T, G, A>::iterator Vector_t<T, G, A>::end()
{
    return this->begin() + this->gsl_vec->size;
}

template<class T, class G, class A>
typename Vector_t<T, G, A>::const_iterator Vector_t<T, G, A>::end() const
{
    return this->begin() + this->gsl_vec->size;
}

template<class T, class G, class A>
typename Vector_t<T, G, A>::const_iterator Vector_t<T, G, A>::cend() const
{
    return this->cbegin() + this->gsl_vec->size;
}

template<class T, class G, class A>
typename Vector_t<T, G, A>::reverse_iterator Vector_t<T, G, A>::rbegin()
{
    return Vector_t<T, G, A>::reverse_iterator(this->end());
}

template<class T, class G, class A>
typename Vector_t<T, G, A>::const_reverse_iterator Vector_t<T, G, A>::rbegin() const
{
    return Vector_t<T, G, A>::const_reverse_iterator(this->end());
}

template<class T, class G, class A>
typename Vector_t<T, G, A>::const_reverse_iterator Vector_t<T, G, A>::crbegin() const
{
    return Vector_t<T, G, A>::const_reverse_iterator(this->end());
}

template<class T, class G, class A>
typename Vector_t<T, G, A>::reverse_iterator Vector_t<T, G, A>::rend()
{
    return Vector_t<T, G, A>::reverse_iterator(this->begin());
}

template<class T, class G, class A>
typename Vector_t<T, G, A>::const_reverse_iterator Vector_t<T, G, A>::rend() const
{
    return Vector_t<T, G, A>::const_reverse_iterator(this->begin());
}

template<class T, class G, class A>
typename Vector_t<T, G, A>::const_reverse_iterator Vector_t<T, G, A>::crend() const
{
    return Vector_t<T, G, A>::const_reverse_iterator(this->cbegin());

}
template<class T, class G, class A>
typename Vector_t<T, G, A>::reference Vector_t<T, G, A>::
    front()
{
    return *this->begin();
}

template<class T, class G, class A>
typename Vector_t<T, G, A>::const_reference Vector_t<T, G, A>::
    front() const
{
    return *this->cbegin();
}

template<class T, class G, class A>
typename Vector_t<T, G, A>::reference Vector_t<T, G, A>::
    back()
{
    return *(--this->end());
}

template<class T, class G, class A>
typename Vector_t<T, G, A>::const_reference Vector_t<T, G, A>::
    back() const
{
    return *(--this->cend());
}

template<class T, class G, class A>
inline typename Vector_t<T, G, A>::reference Vector_t<T, G, A>::
    at(const typename Vector_t<T, G, A>::size_type index)
{
    if(index >= this->gsl_vec->size){
        throw std::out_of_range("Vector index " + std::to_string(index) + " out of range.");
    }
    return (*this)[index];
}

template<class T, class G, class A>
inline typename Vector_t<T, G, A>::const_reference Vector_t<T, G, A>::
    at(const typename Vector_t<T, G, A>::size_type index) const
{
    if(index >= this->gsl_vec->size){
        throw std::out_of_range("Vector index " + std::to_string(index) + " out of range.");
    }
    return (*this)[index];
}

template<class T, class G, class A> template<class iter>
void Vector_t<T, G, A>::assign(iter start_it, iter end_it)
{
    if(end_it - start_it < 0){
        throw(std::runtime_error("Error in assign! End point comes before starting point\n"));
    }
    size_t diff = static_cast<size_t>(end_it - start_it);
    if(diff != this->gsl_vec->size){
        *this = GSL::Vector_t<T, G, A>(diff);
    }
    auto current = this->begin();
    iter counter = start_it;
    while(counter != end_it){
        *current = *counter;
        current++;
        counter++;
    }
}

template<class T, class G, class A>
void Vector_t<T, G, A>::
assign(std::initializer_list<Vector_t<T, G, A>::value_type> l)
{
    this->assign(l.begin(), l.end());
}

template<class T, class G, class A>
void Vector_t<T, G, A>::assign(Vector_t<T, G, A>::size_type n,
Vector_t<T ,G, A>::const_reference val)
{
    if(this->gsl_vec->size != n){
        *this = GSL::Vector_t<T, G, A>(n);
    }
    for(auto it = this->begin(); it != this->begin() + n; it++){
        *it = val;
    }
}

template<class T, class G, class A>
std::string Vector_t<T, G, A>::to_string() const
{
    std::string res = "(";
    size_t i = 0;
    for(auto it : *this){
        res += std::to_string(it);
        if(i < this->size() - 1){
            res += ",";
        }
        res += " ";
        i++;
    }
    res += ")";
    return res;
}

template<>
inline std::string Vector_cx::to_string() const
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
inline std::string Vector_cxld::to_string() const
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
inline std::string Vector_cxf::to_string() const
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
}
