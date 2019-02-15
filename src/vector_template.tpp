#include "vector_template.h"
#include "complex.h"
#include <gsl/gsl_blas.h>
#include <iostream>

using namespace GSL;

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
inline Vector_t<double, gsl_vector>::Vector_t
(const Vector_t<double, gsl_vector>::size_type n)
 : gsl_vec(gsl_vector_calloc(n), gsl_vector_free)
{
    if(gsl_vec == nullptr){
        throw std::runtime_error("Memory allocation (gsl_vector_calloc)"
        " failed!");
    }
}

template<>
inline Vector_t<long double, gsl_vector_long_double>::Vector_t
(const Vector_t::size_type n)
 : gsl_vec(gsl_vector_long_double_calloc(n), gsl_vector_long_double_free)
{

    if(gsl_vec == nullptr){
        throw std::runtime_error("Memory allocation (gsl_vector_long_double_calloc)"
        " failed!");
    }
}

template<>
inline Vector_t<float, gsl_vector_float>::Vector_t
(const Vector_t::size_type n)
 : gsl_vec(gsl_vector_float_calloc(n), gsl_vector_float_free)
{
    if(gsl_vec == nullptr){
        throw std::runtime_error("Memory allocation (gsl_vector_float_calloc)"
        " failed!");
    }
}

template<>
inline Vector_t<int, gsl_vector_int>::Vector_t
(const Vector_t::size_type n)
 : gsl_vec(gsl_vector_int_calloc(n), gsl_vector_int_free)
{
    if(gsl_vec == nullptr){
        throw std::runtime_error("Memory allocation (gsl_vector_int_calloc)"
        " failed!");
    }
}

template<>
inline Vector_t<unsigned int, gsl_vector_uint>::Vector_t
(const Vector_t::size_type n)
 : gsl_vec(gsl_vector_uint_calloc(n), gsl_vector_uint_free)
{
    if(gsl_vec == nullptr){
        throw std::runtime_error("Memory allocation (gsl_vector_uint_calloc)"
        " failed!");
    }
}

template<>
inline Vector_t<long, gsl_vector_long>::Vector_t
(const Vector_t::size_type n)
 : gsl_vec(gsl_vector_long_calloc(n), gsl_vector_long_free)
{
    if(gsl_vec == nullptr){
        throw std::runtime_error("Memory allocation (gsl_vector_long_calloc)"
        " failed!");
    }
}

template<>
inline Vector_t<unsigned long, gsl_vector_ulong>::Vector_t
(const Vector_t::size_type n)
 : gsl_vec(gsl_vector_ulong_calloc(n), gsl_vector_ulong_free)
{
    if(gsl_vec == nullptr){
        throw std::runtime_error("Memory allocation (gsl_vector_ulong_calloc)"
        " failed!");
    }
}

template<>
inline Vector_t<short, gsl_vector_short>::Vector_t
(const Vector_t::size_type n)
 : gsl_vec(gsl_vector_short_calloc(n), gsl_vector_short_free)
{
    if(gsl_vec == nullptr){
        throw std::runtime_error("Memory allocation (gsl_vector_short_calloc)"
        " failed!");
    }
}

template<>
inline Vector_t<unsigned short, gsl_vector_ushort>::Vector_t
(const Vector_t::size_type n)
 : gsl_vec(gsl_vector_ushort_calloc(n), gsl_vector_ushort_free)
{
    if(gsl_vec == nullptr){
        throw std::runtime_error("Memory allocation (gsl_vector_ushort_calloc)"
        " failed!");
    }
}

template<>
inline Vector_t<char, gsl_vector_char>::Vector_t
(const Vector_t::size_type n)
 : gsl_vec(gsl_vector_char_calloc(n), gsl_vector_char_free)
{
    if(gsl_vec == nullptr){
        throw std::runtime_error("Memory allocation (gsl_vector_char_calloc)"
        " failed!");
    }
}

template<>
inline Vector_t<unsigned char, gsl_vector_uchar>::Vector_t
(const Vector_t::size_type n)
 : gsl_vec(gsl_vector_uchar_calloc(n), gsl_vector_uchar_free)
{
    if(gsl_vec == nullptr){
        throw std::runtime_error("Memory allocation (gsl_vector_uchar_calloc)"
        " failed!");
    }
}

template<>
inline Vector_t<GSL::Complex_t<double, gsl_complex>, gsl_vector_complex, std::allocator<gsl_complex>>::Vector_t
(const Vector_t::size_type n)
 : gsl_vec(gsl_vector_complex_calloc(n), gsl_vector_complex_free)
{
    if(gsl_vec == nullptr){
        throw std::runtime_error("Memory allocation (gsl_vector_complex_calloc)"
        " failed!");
    }
}

template<>
inline Vector_t<GSL::Complex_t<long double, gsl_complex_long_double>, gsl_vector_complex_long_double, std::allocator<gsl_complex_long_double>>::Vector_t
(const Vector_t::size_type n)
 : gsl_vec(gsl_vector_complex_long_double_calloc(n), gsl_vector_complex_long_double_free)
{
    if(gsl_vec == nullptr){
        throw std::runtime_error("Memory allocation (gsl_vector_long_double_calloc)"
        " failed!");
    }
}

template<>
inline Vector_t<GSL::Complex_t<float, gsl_complex_float>, gsl_vector_complex_float, std::allocator<gsl_complex_float>>::Vector_t
(const Vector_t::size_type n)
 : gsl_vec(gsl_vector_complex_float_calloc(n), gsl_vector_complex_float_free)
{
    if(gsl_vec == nullptr){
        throw std::runtime_error("Memory allocation (gsl_vector_float_calloc)"
        " failed!");
    }
}

template<>
inline Vector_t<double, gsl_vector>::Vector_t(std::initializer_list<double> l)
 : gsl_vec(gsl_vector_alloc(l.size()), gsl_vector_free)
{
    auto current = l.begin();
    for(size_t i = 0; i < l.size(); i++){
        gsl_vector_set(gsl_vec.get(), i, *current);
        current++;
    }
}

template<>
inline Vector_t<long double, gsl_vector_long_double>::Vector_t(std::initializer_list<long double> l)
 : gsl_vec(gsl_vector_long_double_alloc(l.size()), gsl_vector_long_double_free)
{
    auto current = l.begin();
    for(size_t i = 0; i < l.size(); i++){
        gsl_vector_long_double_set(gsl_vec.get(), i, *current);
        current++;
    }
}

template<>
inline Vector_t<float, gsl_vector_float>::Vector_t(std::initializer_list<float> l)
 : gsl_vec(gsl_vector_float_alloc(l.size()), gsl_vector_float_free)
{
    auto current = l.begin();
    for(size_t i = 0; i < l.size(); i++){
        gsl_vector_float_set(gsl_vec.get(), i, *current);
        current++;
    }
}

template<>
inline Vector_t<int, gsl_vector_int>::Vector_t(std::initializer_list<int> l)
 : gsl_vec(gsl_vector_int_alloc(l.size()), gsl_vector_int_free)
{
    auto current = l.begin();
    for(size_t i = 0; i < l.size(); i++){
        gsl_vector_int_set(gsl_vec.get(), i, *current);
        current++;
    }
}

template<>
inline Vector_t<unsigned int, gsl_vector_uint>::Vector_t(std::initializer_list<unsigned int> l)
 : gsl_vec(gsl_vector_uint_alloc(l.size()), gsl_vector_uint_free)
{
    auto current = l.begin();
    for(size_t i = 0; i < l.size(); i++){
        gsl_vector_uint_set(gsl_vec.get(), i, *current);
        current++;
    }
}

template<>
inline Vector_t<long, gsl_vector_long>::Vector_t(std::initializer_list<long> l)
 : gsl_vec(gsl_vector_long_alloc(l.size()), gsl_vector_long_free)
{
    auto current = l.begin();
    for(size_t i = 0; i < l.size(); i++){
        gsl_vector_long_set(gsl_vec.get(), i, *current);
        current++;
    }
}

template<>
inline Vector_t<unsigned long, gsl_vector_ulong>::Vector_t(std::initializer_list<unsigned long> l)
 : gsl_vec(gsl_vector_ulong_alloc(l.size()), gsl_vector_ulong_free)
{
    auto current = l.begin();
    for(size_t i = 0; i < l.size(); i++){
        gsl_vector_ulong_set(gsl_vec.get(), i, *current);
        current++;
    }
}

template<>
inline Vector_t<short, gsl_vector_short>::Vector_t(std::initializer_list<short> l)
 : gsl_vec(gsl_vector_short_alloc(l.size()), gsl_vector_short_free)
{
    auto current = l.begin();
    for(size_t i = 0; i < l.size(); i++){
        gsl_vector_short_set(gsl_vec.get(), i, *current);
        current++;
    }
}

template<>
inline Vector_t<unsigned short, gsl_vector_ushort>::Vector_t(std::initializer_list<unsigned short> l)
 : gsl_vec(gsl_vector_ushort_alloc(l.size()), gsl_vector_ushort_free)
{
    auto current = l.begin();
    for(size_t i = 0; i < l.size(); i++){
        gsl_vector_ushort_set(gsl_vec.get(), i, *current);
        current++;
    }
}

template<>
inline Vector_t<char, gsl_vector_char>::Vector_t(std::initializer_list<char> l)
 : gsl_vec(gsl_vector_char_alloc(l.size()), gsl_vector_char_free)
{
    auto current = l.begin();
    for(size_t i = 0; i < l.size(); i++){
        gsl_vector_char_set(gsl_vec.get(), i, *current);
        current++;
    }
}

template<>
inline Vector_t<unsigned char, gsl_vector_uchar>::Vector_t(std::initializer_list<unsigned char> l)
 : gsl_vec(gsl_vector_uchar_alloc(l.size()), gsl_vector_uchar_free)
{
    auto current = l.begin();
    for(size_t i = 0; i < l.size(); i++){
        gsl_vector_uchar_set(gsl_vec.get(), i, *current);
        current++;
    }
}

template<>
inline Vector_t<Complex, gsl_vector_complex, std::allocator<gsl_complex>>::
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
inline Vector_t<Complex_ld, gsl_vector_complex_long_double, std::allocator<gsl_complex_long_double>>::
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
inline Vector_t<Complex_f, gsl_vector_complex_float, std::allocator<gsl_complex_float>>::
Vector_t(std::initializer_list<Complex_f> l)
 : gsl_vec(gsl_vector_complex_float_alloc(l.size()), gsl_vector_complex_float_free)
{
    auto current = l.begin();
    for(size_t i = 0; i < l.size(); i++){
        gsl_vector_complex_float_set(gsl_vec.get(), i, *current->gsl_c.get());
        current++;
    }
}

template<>
inline void Vector_t<double, gsl_vector>::copy(const Vector_t<double, gsl_vector>& a)
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
inline void Vector_t<long double, gsl_vector_long_double>::copy
(const Vector_t<long double, gsl_vector_long_double>& a)
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
inline void Vector_t<float, gsl_vector_float>::copy
(const Vector_t<float, gsl_vector_float>& a)
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
inline void Vector_t<int, gsl_vector_int>::copy
(const Vector_t<int, gsl_vector_int>& a)
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
inline void Vector_t<unsigned int, gsl_vector_uint>::copy
(const Vector_t<unsigned int, gsl_vector_uint>& a)
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
inline void Vector_t<long, gsl_vector_long>::copy
(const Vector_t<long, gsl_vector_long>& a)
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
inline void Vector_t<unsigned long, gsl_vector_ulong>::copy
(const Vector_t<unsigned long, gsl_vector_ulong>& a)
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
inline void Vector_t<short, gsl_vector_short>::copy
(const Vector_t<short, gsl_vector_short>& a)
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
inline void Vector_t<unsigned short, gsl_vector_ushort>::copy
(const Vector_t<unsigned short, gsl_vector_ushort>& a)
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
inline void Vector_t<char, gsl_vector_char>::copy
(const Vector_t<char, gsl_vector_char>& a)
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
inline void Vector_t<unsigned char, gsl_vector_uchar>::copy
(const Vector_t<unsigned char, gsl_vector_uchar>& a)
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
inline void Vector_t<GSL::Complex_t<double, gsl_complex>, gsl_vector_complex, std::allocator<gsl_complex>>::copy
(const Vector_t<GSL::Complex_t<double, gsl_complex>, gsl_vector_complex, std::allocator<gsl_complex>>& a)
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
inline void Vector_t<GSL::Complex_t<long double, gsl_complex_long_double>, gsl_vector_complex_long_double, std::allocator<gsl_complex_long_double>>::copy
(const Vector_t<GSL::Complex_t<long double, gsl_complex_long_double>, gsl_vector_complex_long_double, std::allocator<gsl_complex_long_double>>& a)
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
inline void Vector_t<GSL::Complex_t<float, gsl_complex_float>, gsl_vector_complex_float, std::allocator<gsl_complex_float>>::copy
(const Vector_t<GSL::Complex_t<float, gsl_complex_float>, gsl_vector_complex_float, std::allocator<gsl_complex_float>>& a)
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
inline Vector_t<double, gsl_vector>& Vector_t<double, gsl_vector>::operator=(const Vector_t<double, gsl_vector>& a)
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
inline Vector_t<long double, gsl_vector_long_double>& Vector_t<long double, gsl_vector_long_double>::operator=(const Vector_t<long double, gsl_vector_long_double>& a)
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
inline Vector_t<float, gsl_vector_float>& Vector_t<float, gsl_vector_float>::operator=(const Vector_t<float, gsl_vector_float>& a)
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
inline Vector_t<int, gsl_vector_int>& Vector_t<int, gsl_vector_int>::operator=(const Vector_t<int, gsl_vector_int>& a)
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
inline Vector_t<unsigned int, gsl_vector_uint>& Vector_t<unsigned int, gsl_vector_uint>::operator=(const Vector_t<unsigned int, gsl_vector_uint>& a)
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
inline Vector_t<long, gsl_vector_long>& Vector_t<long, gsl_vector_long>::operator=(const Vector_t<long, gsl_vector_long>& a)
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
inline Vector_t<unsigned long, gsl_vector_ulong>& Vector_t<unsigned long, gsl_vector_ulong>::operator=(const Vector_t<unsigned long, gsl_vector_ulong>& a)
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
inline Vector_t<short, gsl_vector_short>& Vector_t<short, gsl_vector_short>::operator=(const Vector_t<short, gsl_vector_short>& a)
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
inline Vector_t<unsigned short, gsl_vector_ushort>& Vector_t<unsigned short, gsl_vector_ushort>::operator=(const Vector_t<unsigned short, gsl_vector_ushort>& a)
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
inline Vector_t<char, gsl_vector_char>& Vector_t<char, gsl_vector_char>::operator=(const Vector_t<char, gsl_vector_char>& a)
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
inline Vector_t<unsigned char, gsl_vector_uchar>& Vector_t<unsigned char, gsl_vector_uchar>::operator=(const Vector_t<unsigned char, gsl_vector_uchar>& a)
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
inline Vector_t<Complex_t<double, gsl_complex>, gsl_vector_complex, std::allocator<gsl_complex>>& Vector_t<Complex_t<double, gsl_complex>, gsl_vector_complex, std::allocator<gsl_complex>>::operator=(const Vector_t<Complex_t<double, gsl_complex>, gsl_vector_complex, std::allocator<gsl_complex>>& a)
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
inline Vector_t<Complex_t<long double, gsl_complex_long_double>, gsl_vector_complex_long_double, std::allocator<gsl_complex_long_double>>& Vector_t<Complex_t<long double, gsl_complex_long_double>, gsl_vector_complex_long_double, std::allocator<gsl_complex_long_double>>::operator=(const Vector_t<Complex_t<long double, gsl_complex_long_double>, gsl_vector_complex_long_double, std::allocator<gsl_complex_long_double>>& a)
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
inline Vector_t<Complex_t<float, gsl_complex_float>, gsl_vector_complex_float, std::allocator<gsl_complex_float>>& Vector_t<Complex_t<float, gsl_complex_float>, gsl_vector_complex_float, std::allocator<gsl_complex_float>>::operator=(const Vector_t<Complex_t<float, gsl_complex_float>, gsl_vector_complex_float, std::allocator<gsl_complex_float>>& a)
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
inline Vector_t<double, gsl_vector>& Vector_t<double, gsl_vector>::operator=(Vector_t<double, gsl_vector>&& a)
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
inline Vector_t<long double, gsl_vector_long_double>& Vector_t<long double, gsl_vector_long_double>::operator=(Vector_t<long double, gsl_vector_long_double>&& a)
{
    if(this->gsl_vec == nullptr || this->gsl_vec->owner != 0){
        std::swap(this->gsl_vec, a.gsl_vec);
    }else if(this->gsl_vec->owner == 0){
        gsl_vector_long_double_memcpy(this->gsl_vec.get(), a.gsl_vec.get());
    }
    return *this;
}

template<>
inline Vector_t<float, gsl_vector_float>& Vector_t<float, gsl_vector_float>::operator=(Vector_t<float, gsl_vector_float>&& a)
{
    if(this->gsl_vec == nullptr || this->gsl_vec->owner != 0){
        std::swap(this->gsl_vec, a.gsl_vec);
    }else if(this->gsl_vec->owner == 0){
        gsl_vector_float_memcpy(this->gsl_vec.get(), a.gsl_vec.get());
    }
    return *this;
}

template<>
inline Vector_t<int, gsl_vector_int>& Vector_t<int, gsl_vector_int>::operator=(Vector_t<int, gsl_vector_int>&& a)
{
    if(this->gsl_vec == nullptr || this->gsl_vec->owner != 0){
        std::swap(this->gsl_vec, a.gsl_vec);
    }else if(this->gsl_vec->owner == 0){
        gsl_vector_int_memcpy(this->gsl_vec.get(), a.gsl_vec.get());
    }
    return *this;
}

template<>
inline Vector_t<unsigned int, gsl_vector_uint>& Vector_t<unsigned int, gsl_vector_uint>::operator=(Vector_t<unsigned int, gsl_vector_uint>&& a)
{
    if(this->gsl_vec == nullptr || this->gsl_vec->owner != 0){
        std::swap(this->gsl_vec, a.gsl_vec);
    }else if(this->gsl_vec->owner == 0){
        gsl_vector_uint_memcpy(this->gsl_vec.get(), a.gsl_vec.get());
    }
    return *this;
}

template<>
inline Vector_t<long, gsl_vector_long>& Vector_t<long, gsl_vector_long>::operator=(Vector_t<long, gsl_vector_long>&& a)
{
    if(this->gsl_vec == nullptr || this->gsl_vec->owner != 0){
        std::swap(this->gsl_vec, a.gsl_vec);
    }else if(this->gsl_vec->owner == 0){
        gsl_vector_long_memcpy(this->gsl_vec.get(), a.gsl_vec.get());
    }
    return *this;
}

template<>
inline Vector_t<unsigned long, gsl_vector_ulong>& Vector_t<unsigned long, gsl_vector_ulong>::operator=(Vector_t<unsigned long, gsl_vector_ulong>&& a)
{
    if(this->gsl_vec == nullptr || this->gsl_vec->owner != 0){
        std::swap(this->gsl_vec, a.gsl_vec);
    }else if(this->gsl_vec->owner == 0){
        gsl_vector_ulong_memcpy(this->gsl_vec.get(), a.gsl_vec.get());
    }
    return *this;
}

template<>
inline Vector_t<short, gsl_vector_short>& Vector_t<short, gsl_vector_short>::operator=(Vector_t<short, gsl_vector_short>&& a)
{
    if(this->gsl_vec == nullptr || this->gsl_vec->owner != 0){
        std::swap(this->gsl_vec, a.gsl_vec);
    }else if(this->gsl_vec->owner == 0){
        gsl_vector_short_memcpy(this->gsl_vec.get(), a.gsl_vec.get());
    }
    return *this;
}

template<>
inline Vector_t<unsigned short, gsl_vector_ushort>& Vector_t<unsigned short, gsl_vector_ushort>::operator=(Vector_t<unsigned short, gsl_vector_ushort>&& a)
{
    if(this->gsl_vec == nullptr || this->gsl_vec->owner != 0){
        std::swap(this->gsl_vec, a.gsl_vec);
    }else if(this->gsl_vec->owner == 0){
        gsl_vector_ushort_memcpy(this->gsl_vec.get(), a.gsl_vec.get());
    }
    return *this;
}

template<>
inline Vector_t<char, gsl_vector_char>& Vector_t<char, gsl_vector_char>::operator=(Vector_t<char, gsl_vector_char>&& a)
{
    if(this->gsl_vec == nullptr || this->gsl_vec->owner != 0){
        std::swap(this->gsl_vec, a.gsl_vec);
    }else if(this->gsl_vec->owner == 0){
        gsl_vector_char_memcpy(this->gsl_vec.get(), a.gsl_vec.get());
    }
    return *this;
}

template<>
inline Vector_t<unsigned char, gsl_vector_uchar>& Vector_t<unsigned char, gsl_vector_uchar>::operator=(Vector_t<unsigned char, gsl_vector_uchar>&& a)
{
    if(this->gsl_vec == nullptr || this->gsl_vec->owner != 0){
        std::swap(this->gsl_vec, a.gsl_vec);
    }else if(this->gsl_vec->owner == 0){
        gsl_vector_uchar_memcpy(this->gsl_vec.get(), a.gsl_vec.get());
    }
    return *this;
}

template<>
inline Vector_t<Complex_t<double, gsl_complex>, gsl_vector_complex, std::allocator<gsl_complex>>& Vector_t<Complex_t<double, gsl_complex>, gsl_vector_complex, std::allocator<gsl_complex>>::operator=(Vector_t<Complex_t<double, gsl_complex>, gsl_vector_complex, std::allocator<gsl_complex>>&& a)
{
    if(this->gsl_vec == nullptr || this->gsl_vec->owner != 0){
        std::swap(this->gsl_vec, a.gsl_vec);
    }else if(this->gsl_vec->owner == 0){
        gsl_vector_complex_memcpy(this->gsl_vec.get(), a.gsl_vec.get());
    }
    return *this;
}

template<>
inline Vector_t<Complex_t<long double, gsl_complex_long_double>, gsl_vector_complex_long_double, std::allocator<gsl_complex_long_double>>& Vector_t<Complex_t<long double, gsl_complex_long_double>, gsl_vector_complex_long_double, std::allocator<gsl_complex_long_double>>::operator=(Vector_t<Complex_t<long double, gsl_complex_long_double>, gsl_vector_complex_long_double, std::allocator<gsl_complex_long_double>>&& a)
{
    if(this->gsl_vec == nullptr || this->gsl_vec->owner != 0){
        std::swap(this->gsl_vec, a.gsl_vec);
    }else if(this->gsl_vec->owner == 0){
        gsl_vector_complex_long_double_memcpy(this->gsl_vec.get(), a.gsl_vec.get());
    }
    return *this;
}

template<>
inline Vector_t<Complex_t<float, gsl_complex_float>, gsl_vector_complex_float, std::allocator<gsl_complex_float>>& Vector_t<Complex_t<float, gsl_complex_float>, gsl_vector_complex_float, std::allocator<gsl_complex_float>>::operator=(Vector_t<Complex_t<float, gsl_complex_float>, gsl_vector_complex_float, std::allocator<gsl_complex_float>>&& a)
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

template<class T, class G, class A> template<class S>
S Vector_t<T, G, A>::norm() const
{
    return this->dot(*this);
}

template<> template<>
inline double Vector_t<double, gsl_vector>::norm<double>() const
{
    return gsl_blas_dnrm2(this->gsl_vec.get());
}

template<> template<>
inline float Vector_t<float, gsl_vector_float>::norm<float>() const
{
    return gsl_blas_snrm2(this->gsl_vec.get());
}

template<> template<>
inline double Vector_t<Complex_t<double, gsl_complex>, gsl_vector_complex, std::allocator<gsl_complex>>::norm<double>() const
{
    return gsl_blas_dznrm2(this->gsl_vec.get());
}

template<> template<>
inline float Vector_t<Complex_t<float, gsl_complex_float>, gsl_vector_complex_float, std::allocator<gsl_complex_float>>::norm<float>() const
{
    return gsl_blas_scnrm2(this->gsl_vec.get());
}

template <class T, class V, class A> template<class S>
void Vector_t<T, V, A>::normalize()
{
    *this /= this->norm<S>();
}

template<>
inline typename Vector_t<
    Complex_t<double, gsl_complex>,
    gsl_vector_complex, std::allocator<gsl_complex>>::const_reference Vector_t<
    Complex_t<double, gsl_complex>,
    gsl_vector_complex, std::allocator<gsl_complex>>::operator[]
    (const typename Vector_t<
        Complex_t<double, gsl_complex>,
        gsl_vector_complex, std::allocator<gsl_complex>>::size_type index) const
{
    return *gsl_vector_complex_ptr(this->gsl_vec.get(), index);
}

template<>
inline typename Vector_t<
    Complex_t<long double, gsl_complex_long_double>,
    gsl_vector_complex_long_double, std::allocator<gsl_complex_long_double>>::const_reference
Vector_t<
    Complex_t<long double, gsl_complex_long_double>,
    gsl_vector_complex_long_double, std::allocator<gsl_complex_long_double>>::operator[]
    (const typename Vector_t<
        Complex_t<long double, gsl_complex_long_double>,
        gsl_vector_complex_long_double, std::allocator<gsl_complex_long_double>>::size_type index) const
{
    return *gsl_vector_complex_long_double_ptr(this->gsl_vec.get(), index);
}

template<>
inline typename Vector_t<
    Complex_t<float, gsl_complex_float>,
    gsl_vector_complex_float, std::allocator<gsl_complex_float>>::const_reference
Vector_t<
    Complex_t<float, gsl_complex_float>,
    gsl_vector_complex_float, std::allocator<gsl_complex_float>>::operator[]
    (const typename Vector_t<
        Complex_t<float, gsl_complex_float>,
        gsl_vector_complex_float, std::allocator<gsl_complex_float>>::size_type index) const
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
        res = static_cast<T>(res + (*this)[i]*b[i]);
    }
    return res;
}

template<>
inline double Vector_t<double, gsl_vector>::dot(const Vector_t<double, gsl_vector>& b) const
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
inline float Vector_t<float, gsl_vector_float>::dot(const Vector_t<float, gsl_vector_float>& b) const
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
inline GSL::Complex_t<double, gsl_complex> Vector_t<Complex_t<double, gsl_complex>, gsl_vector_complex, std::allocator<gsl_complex>>::dot(const Vector_t<Complex_t<double, gsl_complex>, gsl_vector_complex, std::allocator<gsl_complex>>& b) const
{
    if(this->size() != b.size()){
        throw std::runtime_error("Error in dot. Dimensions of vectors do not match!\n");
    }
    GSL::Complex_t<double, gsl_complex> res;
    int stat = gsl_blas_zdotu(this->gsl_vec.get(), b.gsl_vec.get(), res.gsl_c.get());
    if(stat){
		std::string error_str =   gsl_strerror(stat);
		throw std::runtime_error("Error in vector dot product.\nGSL error: "
        + error_str);
	}
    return res;
}

template<>
inline GSL::Complex_t<long double, gsl_complex_long_double> Vector_t<Complex_t<long double, gsl_complex_long_double>, gsl_vector_complex_long_double, std::allocator<gsl_complex_long_double>>::dot(const Vector_t<Complex_t<long double, gsl_complex_long_double>, gsl_vector_complex_long_double, std::allocator<gsl_complex_long_double>>& b) const
{
    if(this->size() != b.size()){
        throw std::runtime_error("Error in dot. Dimensions of vectors do not match!\n");
    }
    GSL::Complex_t<long double, gsl_complex_long_double> res(static_cast<long double>(0.));
    for(Vector_t<Complex_t<long double, gsl_complex_long_double>, gsl_vector_complex_long_double, std::allocator<gsl_complex_long_double>>::size_type i = 0; i < this->size(); i++){
        res.re() += (*this)[i].dat[0]*b[i].dat[0] - (*this)[i].dat[1]*b[i].dat[1];
        res.im() += (*this)[i].dat[1]*b[i].dat[0] + (*this)[i].dat[0]*b[i].dat[0];
    }
    return res;
}

template<>
inline GSL::Complex_t<float, gsl_complex_float> Vector_t<Complex_t<float, gsl_complex_float>, gsl_vector_complex_float, std::allocator<gsl_complex_float>>::dot(const Vector_t<Complex_t<float, gsl_complex_float>, gsl_vector_complex_float, std::allocator<gsl_complex_float>>& b) const
{
    if(this->size() != b.size()){
        throw std::runtime_error("Error in dot. Dimensions of vectors do not match!\n");
    }
    GSL::Complex_t<float, gsl_complex_float> res;
    int stat = gsl_blas_cdotu(this->gsl_vec.get(), b.gsl_vec.get(), res.gsl_c.get());
    if(stat){
		std::string error_str =   gsl_strerror(stat);
		throw std::runtime_error("Error in vector dot product.\nGSL error: "
        + error_str);
	}
    return res;
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
inline GSL::Vector_t<double, gsl_vector>& Vector_t<double, gsl_vector>::operator+=(const Vector_t<double, gsl_vector>& b)
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
inline GSL::Vector_t<long double, gsl_vector_long_double>& Vector_t<long double, gsl_vector_long_double>::operator+=(const Vector_t<long double, gsl_vector_long_double>& b)
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
inline GSL::Vector_t<float, gsl_vector_float>& Vector_t<float, gsl_vector_float>::operator+=(const Vector_t<float, gsl_vector_float>& b)
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
inline GSL::Vector_t<int, gsl_vector_int>& Vector_t<int, gsl_vector_int>::operator+=(const Vector_t<int, gsl_vector_int>& b)
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
inline GSL::Vector_t<unsigned int, gsl_vector_uint>& Vector_t<unsigned int, gsl_vector_uint>::operator+=(const Vector_t<unsigned int, gsl_vector_uint>& b)
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
inline GSL::Vector_t<long, gsl_vector_long>& Vector_t<long, gsl_vector_long>::operator+=(const Vector_t<long, gsl_vector_long>& b)
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
inline GSL::Vector_t<unsigned long, gsl_vector_ulong>& Vector_t<unsigned long, gsl_vector_ulong>::operator+=(const Vector_t<unsigned long, gsl_vector_ulong>& b)
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
inline GSL::Vector_t<short, gsl_vector_short>& Vector_t<short, gsl_vector_short>::operator+=(const Vector_t<short, gsl_vector_short>& b)
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
inline GSL::Vector_t<unsigned short, gsl_vector_ushort>& Vector_t<unsigned short, gsl_vector_ushort>::operator+=(const Vector_t<unsigned short, gsl_vector_ushort>& b)
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
inline GSL::Vector_t<char, gsl_vector_char>& Vector_t<char, gsl_vector_char>::operator+=(const Vector_t<char, gsl_vector_char>& b)
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
inline GSL::Vector_t<unsigned char, gsl_vector_uchar>& Vector_t<unsigned char, gsl_vector_uchar>::operator+=(const Vector_t<unsigned char, gsl_vector_uchar>& b)
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
inline GSL::Vector_t<Complex_t<double, gsl_complex>, gsl_vector_complex, std::allocator<gsl_complex>>& Vector_t<Complex_t<double, gsl_complex>, gsl_vector_complex, std::allocator<gsl_complex>>::operator+=(const Vector_t<Complex_t<double, gsl_complex>, gsl_vector_complex, std::allocator<gsl_complex>>& b)
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
inline GSL::Vector_t<Complex_t<long double, gsl_complex_long_double>, gsl_vector_complex_long_double, std::allocator<gsl_complex_long_double>>& Vector_t<Complex_t<long double, gsl_complex_long_double>, gsl_vector_complex_long_double, std::allocator<gsl_complex_long_double>>::operator+=(const Vector_t<Complex_t<long double, gsl_complex_long_double>, gsl_vector_complex_long_double, std::allocator<gsl_complex_long_double>>& b)
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
inline GSL::Vector_t<Complex_t<float, gsl_complex_float>, gsl_vector_complex_float, std::allocator<gsl_complex_float>>& Vector_t<Complex_t<float, gsl_complex_float>, gsl_vector_complex_float, std::allocator<gsl_complex_float>>::operator+=(const Vector_t<Complex_t<float, gsl_complex_float>, gsl_vector_complex_float, std::allocator<gsl_complex_float>>& b)
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
inline GSL::Vector_t<double, gsl_vector>& Vector_t<double, gsl_vector>::operator-=(const Vector_t<double, gsl_vector>& b)
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
inline GSL::Vector_t<long double, gsl_vector_long_double>& Vector_t<long double, gsl_vector_long_double>::operator-=(const Vector_t<long double, gsl_vector_long_double>& b)
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
inline GSL::Vector_t<float, gsl_vector_float>& Vector_t<float, gsl_vector_float>::operator-=(const Vector_t<float, gsl_vector_float>& b)
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
inline GSL::Vector_t<int, gsl_vector_int>& Vector_t<int, gsl_vector_int>::operator-=(const Vector_t<int, gsl_vector_int>& b)
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
inline GSL::Vector_t<unsigned int, gsl_vector_uint>& Vector_t<unsigned int, gsl_vector_uint>::operator-=(const Vector_t<unsigned int, gsl_vector_uint>& b)
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
inline GSL::Vector_t<long, gsl_vector_long>& Vector_t<long, gsl_vector_long>::operator-=(const Vector_t<long, gsl_vector_long>& b)
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
inline GSL::Vector_t<unsigned long, gsl_vector_ulong>& Vector_t<unsigned long, gsl_vector_ulong>::operator-=(const Vector_t<unsigned long, gsl_vector_ulong>& b)
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
inline GSL::Vector_t<short, gsl_vector_short>& Vector_t<short, gsl_vector_short>::operator-=(const Vector_t<short, gsl_vector_short>& b)
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
inline GSL::Vector_t<unsigned short, gsl_vector_ushort>& Vector_t<unsigned short, gsl_vector_ushort>::operator-=(const Vector_t<unsigned short, gsl_vector_ushort>& b)
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
inline GSL::Vector_t<char, gsl_vector_char>& Vector_t<char, gsl_vector_char>::operator-=(const Vector_t<char, gsl_vector_char>& b)
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
inline GSL::Vector_t<unsigned char, gsl_vector_uchar>& Vector_t<unsigned char, gsl_vector_uchar>::operator-=(const Vector_t<unsigned char, gsl_vector_uchar>& b)
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
inline GSL::Vector_t<Complex_t<double, gsl_complex>, gsl_vector_complex, std::allocator<gsl_complex>>& Vector_t<Complex_t<double, gsl_complex>, gsl_vector_complex, std::allocator<gsl_complex>>::operator-=(const Vector_t<Complex_t<double, gsl_complex>, gsl_vector_complex, std::allocator<gsl_complex>>& b)
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
inline GSL::Vector_t<Complex_t<long double, gsl_complex_long_double>, gsl_vector_complex_long_double, std::allocator<gsl_complex_long_double>>& Vector_t<Complex_t<long double, gsl_complex_long_double>, gsl_vector_complex_long_double, std::allocator<gsl_complex_long_double>>::operator-=(const Vector_t<Complex_t<long double, gsl_complex_long_double>, gsl_vector_complex_long_double, std::allocator<gsl_complex_long_double>>& b)
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
inline GSL::Vector_t<Complex_t<float, gsl_complex_float>, gsl_vector_complex_float, std::allocator<gsl_complex_float>>& Vector_t<Complex_t<float, gsl_complex_float>, gsl_vector_complex_float, std::allocator<gsl_complex_float>>::operator-=(const Vector_t<Complex_t<float, gsl_complex_float>, gsl_vector_complex_float, std::allocator<gsl_complex_float>>& b)
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
inline GSL::Vector_t<double, gsl_vector>& Vector_t<double, gsl_vector>::operator*=(const Vector_t<double, gsl_vector>& b)
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
inline GSL::Vector_t<long double, gsl_vector_long_double>& Vector_t<long double, gsl_vector_long_double>::operator*=(const Vector_t<long double, gsl_vector_long_double>& b)
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
inline GSL::Vector_t<float, gsl_vector_float>& Vector_t<float, gsl_vector_float>::operator*=(const Vector_t<float, gsl_vector_float>& b)
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
inline GSL::Vector_t<int, gsl_vector_int>& Vector_t<int, gsl_vector_int>::operator*=(const Vector_t<int, gsl_vector_int>& b)
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
inline GSL::Vector_t<unsigned int, gsl_vector_uint>& Vector_t<unsigned int, gsl_vector_uint>::operator*=(const Vector_t<unsigned int, gsl_vector_uint>& b)
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
inline GSL::Vector_t<long, gsl_vector_long>& Vector_t<long, gsl_vector_long>::operator*=(const Vector_t<long, gsl_vector_long>& b)
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
inline GSL::Vector_t<unsigned long, gsl_vector_ulong>& Vector_t<unsigned long, gsl_vector_ulong>::operator*=(const Vector_t<unsigned long, gsl_vector_ulong>& b)
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
inline GSL::Vector_t<short, gsl_vector_short>& Vector_t<short, gsl_vector_short>::operator*=(const Vector_t<short, gsl_vector_short>& b)
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
inline GSL::Vector_t<unsigned short, gsl_vector_ushort>& Vector_t<unsigned short, gsl_vector_ushort>::operator*=(const Vector_t<unsigned short, gsl_vector_ushort>& b)
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
inline GSL::Vector_t<char, gsl_vector_char>& Vector_t<char, gsl_vector_char>::operator*=(const Vector_t<char, gsl_vector_char>& b)
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
inline GSL::Vector_t<unsigned char, gsl_vector_uchar>& Vector_t<unsigned char, gsl_vector_uchar>::operator*=(const Vector_t<unsigned char, gsl_vector_uchar>& b)
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
inline GSL::Vector_t<Complex_t<double, gsl_complex>, gsl_vector_complex, std::allocator<gsl_complex>>& Vector_t<Complex_t<double, gsl_complex>, gsl_vector_complex, std::allocator<gsl_complex>>::operator*=(const Vector_t<Complex_t<double, gsl_complex>, gsl_vector_complex, std::allocator<gsl_complex>>& b)
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
inline GSL::Vector_t<Complex_t<long double, gsl_complex_long_double>, gsl_vector_complex_long_double, std::allocator<gsl_complex_long_double>>& Vector_t<Complex_t<long double, gsl_complex_long_double>, gsl_vector_complex_long_double, std::allocator<gsl_complex_long_double>>::operator*=(const Vector_t<Complex_t<long double, gsl_complex_long_double>, gsl_vector_complex_long_double, std::allocator<gsl_complex_long_double>>& b)
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
inline GSL::Vector_t<Complex_t<float, gsl_complex_float>, gsl_vector_complex_float, std::allocator<gsl_complex_float>>& Vector_t<Complex_t<float, gsl_complex_float>, gsl_vector_complex_float, std::allocator<gsl_complex_float>>::operator*=(const Vector_t<Complex_t<float, gsl_complex_float>, gsl_vector_complex_float, std::allocator<gsl_complex_float>>& b)
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
inline GSL::Vector_t<double, gsl_vector>& Vector_t<double, gsl_vector>::operator/=(const Vector_t<double, gsl_vector>& b)
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
inline GSL::Vector_t<long double, gsl_vector_long_double>& Vector_t<long double, gsl_vector_long_double>::operator/=(const Vector_t<long double, gsl_vector_long_double>& b)
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
inline GSL::Vector_t<float, gsl_vector_float>& Vector_t<float, gsl_vector_float>::operator/=(const Vector_t<float, gsl_vector_float>& b)
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
inline GSL::Vector_t<int, gsl_vector_int>& Vector_t<int, gsl_vector_int>::operator/=(const Vector_t<int, gsl_vector_int>& b)
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
inline GSL::Vector_t<unsigned int, gsl_vector_uint>& Vector_t<unsigned int, gsl_vector_uint>::operator/=(const Vector_t<unsigned int, gsl_vector_uint>& b)
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
inline GSL::Vector_t<long, gsl_vector_long>& Vector_t<long, gsl_vector_long>::operator/=(const Vector_t<long, gsl_vector_long>& b)
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
inline GSL::Vector_t<unsigned long, gsl_vector_ulong>& Vector_t<unsigned long, gsl_vector_ulong>::operator/=(const Vector_t<unsigned long, gsl_vector_ulong>& b)
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
inline GSL::Vector_t<short, gsl_vector_short>& Vector_t<short, gsl_vector_short>::operator/=(const Vector_t<short, gsl_vector_short>& b)
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
inline GSL::Vector_t<unsigned short, gsl_vector_ushort>& Vector_t<unsigned short, gsl_vector_ushort>::operator/=(const Vector_t<unsigned short, gsl_vector_ushort>& b)
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
inline GSL::Vector_t<char, gsl_vector_char>& Vector_t<char, gsl_vector_char>::operator/=(const Vector_t<char, gsl_vector_char>& b)
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
inline GSL::Vector_t<unsigned char, gsl_vector_uchar>& Vector_t<unsigned char, gsl_vector_uchar>::operator/=(const Vector_t<unsigned char, gsl_vector_uchar>& b)
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
inline GSL::Vector_t<Complex_t<double, gsl_complex>, gsl_vector_complex, std::allocator<gsl_complex>>& Vector_t<Complex_t<double, gsl_complex>, gsl_vector_complex, std::allocator<gsl_complex>>::operator/=(const Vector_t<Complex_t<double, gsl_complex>, gsl_vector_complex, std::allocator<gsl_complex>>& b)
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
inline GSL::Vector_t<Complex_t<long double, gsl_complex_long_double>, gsl_vector_complex_long_double, std::allocator<gsl_complex_long_double>>& Vector_t<Complex_t<long double, gsl_complex_long_double>, gsl_vector_complex_long_double, std::allocator<gsl_complex_long_double>>::operator/=(const Vector_t<Complex_t<long double, gsl_complex_long_double>, gsl_vector_complex_long_double, std::allocator<gsl_complex_long_double>>& b)
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
inline GSL::Vector_t<Complex_t<float, gsl_complex_float>, gsl_vector_complex_float, std::allocator<gsl_complex_float>>& Vector_t<Complex_t<float, gsl_complex_float>, gsl_vector_complex_float, std::allocator<gsl_complex_float>>::operator/=(const Vector_t<Complex_t<float, gsl_complex_float>, gsl_vector_complex_float, std::allocator<gsl_complex_float>>& b)
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
inline GSL::Vector_t<double, gsl_vector>& Vector_t<double, gsl_vector>::operator*=(const double& b)
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
inline GSL::Vector_t<long double, gsl_vector_long_double>& Vector_t<long double, gsl_vector_long_double>::operator*=(const long double& b)
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
inline GSL::Vector_t<float, gsl_vector_float>& Vector_t<float, gsl_vector_float>::operator*=(const float& b)
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
inline GSL::Vector_t<int, gsl_vector_int>& Vector_t<int, gsl_vector_int>::operator*=(const int& b)
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
inline GSL::Vector_t<unsigned int, gsl_vector_uint>& Vector_t<unsigned int, gsl_vector_uint>::operator*=(const unsigned int& b)
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
inline GSL::Vector_t<long, gsl_vector_long>& Vector_t<long, gsl_vector_long>::operator*=(const long& b)
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
inline GSL::Vector_t<unsigned long, gsl_vector_ulong>& Vector_t<unsigned long, gsl_vector_ulong>::operator*=(const unsigned long& b)
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
inline GSL::Vector_t<short, gsl_vector_short>& Vector_t<short, gsl_vector_short>::operator*=(const short& b)
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
inline GSL::Vector_t<unsigned short, gsl_vector_ushort>& Vector_t<unsigned short, gsl_vector_ushort>::operator*=(const unsigned short& b)
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
inline GSL::Vector_t<char, gsl_vector_char>& Vector_t<char, gsl_vector_char>::operator*=(const char& b)
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
inline GSL::Vector_t<unsigned char, gsl_vector_uchar>& Vector_t<unsigned char, gsl_vector_uchar>::operator*=(const unsigned char& b)
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
inline GSL::Vector_t<Complex_t<double, gsl_complex>, gsl_vector_complex, std::allocator<gsl_complex>>& Vector_t<Complex_t<double, gsl_complex>, gsl_vector_complex, std::allocator<gsl_complex>>::operator*=(const Complex_t<double, gsl_complex>& b)
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
inline GSL::Vector_t<Complex_t<long double, gsl_complex_long_double>, gsl_vector_complex_long_double, std::allocator<gsl_complex_long_double>>& Vector_t<Complex_t<long double, gsl_complex_long_double>, gsl_vector_complex_long_double, std::allocator<gsl_complex_long_double>>::operator*=(const Complex_t<long double, gsl_complex_long_double>& b)
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
inline GSL::Vector_t<Complex_t<float, gsl_complex_float>, gsl_vector_complex_float, std::allocator<gsl_complex_float>>& Vector_t<Complex_t<float, gsl_complex_float>, gsl_vector_complex_float, std::allocator<gsl_complex_float>>::operator*=(const Complex_t<float, gsl_complex_float>& b)
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
inline GSL::Vector_t<double, gsl_vector>& Vector_t<double, gsl_vector>::operator/=(const double& b)
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
inline GSL::Vector_t<long double, gsl_vector_long_double>& Vector_t<long double, gsl_vector_long_double>::operator/=(const long double& b)
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
inline GSL::Vector_t<float, gsl_vector_float>& Vector_t<float, gsl_vector_float>::operator/=(const float& b)
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
inline GSL::Vector_t<int, gsl_vector_int>& Vector_t<int, gsl_vector_int>::operator/=(const int& b)
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
inline GSL::Vector_t<unsigned int, gsl_vector_uint>& Vector_t<unsigned int, gsl_vector_uint>::operator/=(const unsigned int& b)
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
inline GSL::Vector_t<long, gsl_vector_long>& Vector_t<long, gsl_vector_long>::operator/=(const long& b)
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
inline GSL::Vector_t<unsigned long, gsl_vector_ulong>& Vector_t<unsigned long, gsl_vector_ulong>::operator/=(const unsigned long& b)
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
inline GSL::Vector_t<short, gsl_vector_short>& Vector_t<short, gsl_vector_short>::operator/=(const short& b)
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
inline GSL::Vector_t<unsigned short, gsl_vector_ushort>& Vector_t<unsigned short, gsl_vector_ushort>::operator/=(const unsigned short& b)
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
inline GSL::Vector_t<char, gsl_vector_char>& Vector_t<char, gsl_vector_char>::operator/=(const char& b)
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
inline GSL::Vector_t<unsigned char, gsl_vector_uchar>& Vector_t<unsigned char, gsl_vector_uchar>::operator/=(const unsigned char& b)
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
inline GSL::Vector_t<Complex_t<double, gsl_complex>, gsl_vector_complex, std::allocator<gsl_complex>>& Vector_t<Complex_t<double, gsl_complex>, gsl_vector_complex, std::allocator<gsl_complex>>::operator/=(const Complex_t<double, gsl_complex>& b)
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
inline GSL::Vector_t<Complex_t<long double, gsl_complex_long_double>, gsl_vector_complex_long_double, std::allocator<gsl_complex_long_double>>& Vector_t<Complex_t<long double, gsl_complex_long_double>, gsl_vector_complex_long_double, std::allocator<gsl_complex_long_double>>::operator/=(const Complex_t<long double, gsl_complex_long_double>& b)
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
inline GSL::Vector_t<Complex_t<float, gsl_complex_float>, gsl_vector_complex_float, std::allocator<gsl_complex_float>>& Vector_t<Complex_t<float, gsl_complex_float>, gsl_vector_complex_float, std::allocator<gsl_complex_float>>::operator/=(const Complex_t<float, gsl_complex_float>& b)
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
inline Vector_t<double, gsl_vector> Vector_t<double, gsl_vector>::operator*<gsl_matrix>(const Matrix_t<double, gsl_matrix, gsl_vector, std::allocator<double>>& m)
{
    Vector_t<double, gsl_vector> res(m.size().first);
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
inline Vector_t<float, gsl_vector_float> Vector_t<float, gsl_vector_float>::operator*<gsl_matrix_float>(const Matrix_t<float, gsl_matrix_float, gsl_vector_float>& m)
{
    Vector_t<float, gsl_vector_float> res(m.size().first);
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
inline Vector_t<Complex_t<double, gsl_complex>, gsl_vector_complex, std::allocator<gsl_complex>> Vector_t<Complex_t<double, gsl_complex>, gsl_vector_complex, std::allocator<gsl_complex>>::operator*<gsl_matrix_complex>(const Matrix_t<Complex_t<double, gsl_complex>, gsl_matrix_complex, gsl_vector_complex, std::allocator<gsl_complex>>& m)
{
    Vector_t<Complex_t<double, gsl_complex>, gsl_vector_complex, std::allocator<gsl_complex>> res(m.size().first);
    int stat = gsl_blas_zgemv(CblasTrans, Complex_t<double, gsl_complex>(1.0), m.gsl_mat.get(),
        this->gsl_vec.get(), Complex_t<double, gsl_complex>(0.0), res.gsl_vec.get());
    if(stat){
		std::string error_str =   gsl_strerror(stat);
		throw std::runtime_error("Error in matrix-vector multiplication.\nGSL error: "
        + error_str);
	}

    return res;
}

template<> template<>
inline Vector_t<Complex_t<float, gsl_complex_float>, gsl_vector_complex_float, std::allocator<gsl_complex_float>> Vector_t<Complex_t<float, gsl_complex_float>, gsl_vector_complex_float, std::allocator<gsl_complex_float>>::operator*<gsl_matrix_complex_float>(const Matrix_t<Complex_t<float, gsl_complex_float>, gsl_matrix_complex_float, gsl_vector_complex_float, std::allocator<gsl_complex_float>>& m)
{
    Vector_t<Complex_t<float, gsl_complex_float>, gsl_vector_complex_float, std::allocator<gsl_complex_float>> res(m.size().first);
    int stat = gsl_blas_cgemv(CblasTrans, Complex_t<float, gsl_complex_float>(1.0), m.gsl_mat.get(),
        this->gsl_vec.get(), Complex_t<float, gsl_complex_float>(0.0), res.gsl_vec.get());
    if(stat){
		std::string error_str =   gsl_strerror(stat);
		throw std::runtime_error("Error in matrix-vector multiplication.\nGSL error: "
        + error_str);
	}

    return res;
}


template<>
inline bool Vector_t<double, gsl_vector>::operator==(const Vector_t<double, gsl_vector>& b) const
{
    if(this->gsl_vec.get() == nullptr && b.gsl_vec.get() == nullptr){
        return true;
    }else if(this->gsl_vec.get() == nullptr || b.gsl_vec.get() == nullptr){
        return false;
    }
    return gsl_vector_equal(this->gsl_vec.get(), b.gsl_vec.get());
}

template<>
inline bool Vector_t<long double, gsl_vector_long_double>::operator==(const Vector_t<long double, gsl_vector_long_double>& b) const
{
    if(this->gsl_vec.get() == nullptr && b.gsl_vec.get() == nullptr){
        return true;
    }else if(this->gsl_vec.get() == nullptr || b.gsl_vec.get() == nullptr){
        return false;
    }
    return gsl_vector_long_double_equal(this->gsl_vec.get(), b.gsl_vec.get());
}

template<>
inline bool Vector_t<float, gsl_vector_float>::operator==(const Vector_t<float, gsl_vector_float>& b) const
{
    if(this->gsl_vec.get() == nullptr && b.gsl_vec.get() == nullptr){
        return true;
    }else if(this->gsl_vec.get() == nullptr || b.gsl_vec.get() == nullptr){
        return false;
    }
    return gsl_vector_float_equal(this->gsl_vec.get(), b.gsl_vec.get());
}

template<>
inline bool Vector_t<int, gsl_vector_int>::operator==(const Vector_t<int, gsl_vector_int>& b) const
{
    if(this->gsl_vec.get() == nullptr && b.gsl_vec.get() == nullptr){
        return true;
    }else if(this->gsl_vec.get() == nullptr || b.gsl_vec.get() == nullptr){
        return false;
    }
    return gsl_vector_int_equal(this->gsl_vec.get(), b.gsl_vec.get());
}

template<>
inline bool Vector_t<unsigned int, gsl_vector_uint>::operator==(const Vector_t<unsigned int, gsl_vector_uint>& b) const
{
    if(this->gsl_vec.get() == nullptr && b.gsl_vec.get() == nullptr){
        return true;
    }else if(this->gsl_vec.get() == nullptr || b.gsl_vec.get() == nullptr){
        return false;
    }
    return gsl_vector_uint_equal(this->gsl_vec.get(), b.gsl_vec.get());
}

template<>
inline bool Vector_t<long, gsl_vector_long>::operator==(const Vector_t<long, gsl_vector_long>& b) const
{
    if(this->gsl_vec.get() == nullptr && b.gsl_vec.get() == nullptr){
        return true;
    }else if(this->gsl_vec.get() == nullptr || b.gsl_vec.get() == nullptr){
        return false;
    }
    return gsl_vector_long_equal(this->gsl_vec.get(), b.gsl_vec.get());
}

template<>
inline bool Vector_t<unsigned long, gsl_vector_ulong>::operator==(const Vector_t<unsigned long, gsl_vector_ulong>& b) const
{
    if(this->gsl_vec.get() == nullptr && b.gsl_vec.get() == nullptr){
        return true;
    }else if(this->gsl_vec.get() == nullptr || b.gsl_vec.get() == nullptr){
        return false;
    }
    return gsl_vector_ulong_equal(this->gsl_vec.get(), b.gsl_vec.get());
}

template<>
inline bool Vector_t<short, gsl_vector_short>::operator==(const Vector_t<short, gsl_vector_short>& b) const
{
    if(this->gsl_vec.get() == nullptr && b.gsl_vec.get() == nullptr){
        return true;
    }else if(this->gsl_vec.get() == nullptr || b.gsl_vec.get() == nullptr){
        return false;
    }
    return gsl_vector_short_equal(this->gsl_vec.get(), b.gsl_vec.get());
}

template<>
inline bool Vector_t<unsigned short, gsl_vector_ushort>::operator==(const Vector_t<unsigned short, gsl_vector_ushort>& b) const
{
    if(this->gsl_vec.get() == nullptr && b.gsl_vec.get() == nullptr){
        return true;
    }else if(this->gsl_vec.get() == nullptr || b.gsl_vec.get() == nullptr){
        return false;
    }
    return gsl_vector_ushort_equal(this->gsl_vec.get(), b.gsl_vec.get());
}

template<>
inline bool Vector_t<char, gsl_vector_char>::operator==(const Vector_t<char, gsl_vector_char>& b) const
{
    if(this->gsl_vec.get() == nullptr && b.gsl_vec.get() == nullptr){
        return true;
    }else if(this->gsl_vec.get() == nullptr || b.gsl_vec.get() == nullptr){
        return false;
    }
    return gsl_vector_char_equal(this->gsl_vec.get(), b.gsl_vec.get());
}

template<>
inline bool Vector_t<unsigned char, gsl_vector_uchar>::operator==(const Vector_t<unsigned char, gsl_vector_uchar>& b) const
{
    if(this->gsl_vec.get() == nullptr && b.gsl_vec.get() == nullptr){
        return true;
    }else if(this->gsl_vec.get() == nullptr || b.gsl_vec.get() == nullptr){
        return false;
    }
    return gsl_vector_uchar_equal(this->gsl_vec.get(), b.gsl_vec.get());
}

template<>
inline bool Vector_t<Complex_t<double, gsl_complex>, gsl_vector_complex, std::allocator<gsl_complex>>::operator==(const Vector_t<Complex_t<double, gsl_complex>, gsl_vector_complex, std::allocator<gsl_complex>>& b) const
{
    if(this->gsl_vec.get() == nullptr && b.gsl_vec.get() == nullptr){
        return true;
    }else if(this->gsl_vec.get() == nullptr || b.gsl_vec.get() == nullptr){
        return false;
    }
    return gsl_vector_complex_equal(this->gsl_vec.get(), b.gsl_vec.get());
}

template<>
inline bool Vector_t<Complex_t<long double, gsl_complex_long_double>, gsl_vector_complex_long_double, std::allocator<gsl_complex_long_double>>::operator==(const Vector_t<Complex_t<long double, gsl_complex_long_double>, gsl_vector_complex_long_double, std::allocator<gsl_complex_long_double>>& b) const
{
    if(this->gsl_vec.get() == nullptr && b.gsl_vec.get() == nullptr){
        return true;
    }else if(this->gsl_vec.get() == nullptr || b.gsl_vec.get() == nullptr){
        return false;
    }
    return gsl_vector_complex_long_double_equal(this->gsl_vec.get(), b.gsl_vec.get());
}

template<>
inline bool Vector_t<Complex_t<float, gsl_complex_float>, gsl_vector_complex_float, std::allocator<gsl_complex_float>>::operator==(const Vector_t<Complex_t<float, gsl_complex_float>, gsl_vector_complex_float, std::allocator<gsl_complex_float>>& b) const
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
inline typename Vector_t<double, gsl_vector>::iterator Vector_t<double, gsl_vector>::begin()
{
    if(this->gsl_vec.get() == nullptr){
        throw std::runtime_error("Calling begin() on uninitialized Vector");
    }
    return Vector_t<double, gsl_vector>::iterator(gsl_vector_ptr(gsl_vec.get(), 0), this->gsl_vec->stride);
}

template<>
inline typename Vector_t<long double, gsl_vector_long_double>::iterator Vector_t<long double, gsl_vector_long_double>::begin()
{
    if(this->gsl_vec.get() == nullptr){
        throw std::runtime_error("Calling begin() on uninitialized Vector");
    }
    return iterator(gsl_vector_long_double_ptr(gsl_vec.get(), 0), this->gsl_vec->stride);
}

template<>
inline typename Vector_t<float, gsl_vector_float>::iterator Vector_t<float, gsl_vector_float>::begin()
{
    if(this->gsl_vec.get() == nullptr){
        throw std::runtime_error("Calling begin() on uninitialized Vector");
    }
    return iterator(gsl_vector_float_ptr(gsl_vec.get(), 0), this->gsl_vec->stride);
}

template<>
inline typename Vector_t<int, gsl_vector_int>::iterator Vector_t<int, gsl_vector_int>::begin()
{
    if(this->gsl_vec.get() == nullptr){
        throw std::runtime_error("Calling begin() on uninitialized Vector");
    }
    return iterator(gsl_vector_int_ptr(gsl_vec.get(), 0), this->gsl_vec->stride);
}

template<>
inline typename Vector_t<unsigned int, gsl_vector_uint>::iterator Vector_t<unsigned int, gsl_vector_uint>::begin()
{
    if(this->gsl_vec.get() == nullptr){
        throw std::runtime_error("Calling begin() on uninitialized Vector");
    }
    return iterator(gsl_vector_uint_ptr(gsl_vec.get(), 0), this->gsl_vec->stride);
}

template<>
inline typename Vector_t<long, gsl_vector_long>::iterator Vector_t<long, gsl_vector_long>::begin()
{
    if(this->gsl_vec.get() == nullptr){
        throw std::runtime_error("Calling begin() on uninitialized Vector");
    }
    return iterator(gsl_vector_long_ptr(gsl_vec.get(), 0), this->gsl_vec->stride);
}

template<>
inline typename Vector_t<unsigned long, gsl_vector_ulong>::iterator Vector_t<unsigned long, gsl_vector_ulong>::begin()
{
    if(this->gsl_vec.get() == nullptr){
        throw std::runtime_error("Calling begin() on uninitialized Vector");
    }
    return iterator(gsl_vector_ulong_ptr(gsl_vec.get(), 0), this->gsl_vec->stride);
}

template<>
inline typename Vector_t<short, gsl_vector_short>::iterator Vector_t<short, gsl_vector_short>::begin()
{
    if(this->gsl_vec.get() == nullptr){
        throw std::runtime_error("Calling begin() on uninitialized Vector");
    }
    return iterator(gsl_vector_short_ptr(gsl_vec.get(), 0), this->gsl_vec->stride);
}

template<>
inline typename Vector_t<unsigned short, gsl_vector_ushort>::iterator Vector_t<unsigned short, gsl_vector_ushort>::begin()
{
    if(this->gsl_vec.get() == nullptr){
        throw std::runtime_error("Calling begin() on uninitialized Vector");
    }
    return iterator(gsl_vector_ushort_ptr(gsl_vec.get(), 0), this->gsl_vec->stride);
}

template<>
inline typename Vector_t<char, gsl_vector_char>::iterator Vector_t<char, gsl_vector_char>::begin()
{
    if(this->gsl_vec.get() == nullptr){
        throw std::runtime_error("Calling begin() on uninitialized Vector");
    }
    return iterator(gsl_vector_char_ptr(gsl_vec.get(), 0), this->gsl_vec->stride);
}

template<>
inline typename Vector_t<unsigned char, gsl_vector_uchar>::iterator Vector_t<unsigned char, gsl_vector_uchar>::begin()
{
    if(this->gsl_vec.get() == nullptr){
        throw std::runtime_error("Calling begin() on uninitialized Vector");
    }
    return iterator(gsl_vector_uchar_ptr(gsl_vec.get(), 0), this->gsl_vec->stride);
}

template<>
inline typename Vector_t<Complex_t<double, gsl_complex>, gsl_vector_complex, std::allocator<gsl_complex>>::iterator Vector_t<Complex_t<double, gsl_complex>, gsl_vector_complex, std::allocator<gsl_complex>>::begin()
{
    if(this->gsl_vec.get() == nullptr){
        throw std::runtime_error("Calling begin() on uninitialized Vector");
    }
    return iterator(gsl_vector_complex_ptr(gsl_vec.get(), 0), this->gsl_vec->stride);
}

template<>
inline typename Vector_t<Complex_t<long double, gsl_complex_long_double>, gsl_vector_complex_long_double, std::allocator<gsl_complex_long_double>>::iterator Vector_t<Complex_t<long double, gsl_complex_long_double>, gsl_vector_complex_long_double, std::allocator<gsl_complex_long_double>>::begin()
{
    if(this->gsl_vec.get() == nullptr){
        throw std::runtime_error("Calling begin() on uninitialized Vector");
    }
    return iterator(gsl_vector_complex_long_double_ptr(gsl_vec.get(), 0), this->gsl_vec->stride);
}

template<>
inline typename Vector_t<Complex_t<float, gsl_complex_float>, gsl_vector_complex_float, std::allocator<gsl_complex_float>>::iterator Vector_t<Complex_t<float, gsl_complex_float>, gsl_vector_complex_float, std::allocator<gsl_complex_float>>::begin()
{
    if(this->gsl_vec.get() == nullptr){
        throw std::runtime_error("Calling begin() on uninitialized Vector");
    }
    return iterator(gsl_vector_complex_float_ptr(gsl_vec.get(), 0), this->gsl_vec->stride);
}

template<>
inline typename Vector_t<double, gsl_vector>::const_iterator Vector_t<double, gsl_vector>::begin() const
{
    if(this->gsl_vec.get() == nullptr){
        throw std::runtime_error("Calling begin() on uninitialized Vector");
    }
    return const_iterator(gsl_vector_ptr(gsl_vec.get(), 0), this->gsl_vec->stride);
}

template<>
inline typename Vector_t<long double, gsl_vector_long_double>::const_iterator Vector_t<long double, gsl_vector_long_double>::begin() const
{
    if(this->gsl_vec.get() == nullptr){
        throw std::runtime_error("Calling begin() on uninitialized Vector");
    }
    return const_iterator(gsl_vector_long_double_ptr(gsl_vec.get(), 0), this->gsl_vec->stride);
}

template<>
inline typename Vector_t<float, gsl_vector_float>::const_iterator Vector_t<float, gsl_vector_float>::begin() const
{
    if(this->gsl_vec.get() == nullptr){
        throw std::runtime_error("Calling begin() on uninitialized Vector");
    }
    return const_iterator(gsl_vector_float_ptr(gsl_vec.get(), 0), this->gsl_vec->stride);
}

template<>
inline typename Vector_t<int, gsl_vector_int>::const_iterator Vector_t<int, gsl_vector_int>::begin() const
{
    if(this->gsl_vec.get() == nullptr){
        throw std::runtime_error("Calling begin() on uninitialized Vector");
    }
    return const_iterator(gsl_vector_int_ptr(gsl_vec.get(), 0), this->gsl_vec->stride);
}

template<>
inline typename Vector_t<unsigned int, gsl_vector_uint>::const_iterator Vector_t<unsigned int, gsl_vector_uint>::begin() const
{
    if(this->gsl_vec.get() == nullptr){
        throw std::runtime_error("Calling begin() on uninitialized Vector");
    }
    return const_iterator(gsl_vector_uint_ptr(gsl_vec.get(), 0), this->gsl_vec->stride);
}

template<>
inline typename Vector_t<long, gsl_vector_long>::const_iterator Vector_t<long, gsl_vector_long>::begin() const
{
    if(this->gsl_vec.get() == nullptr){
        throw std::runtime_error("Calling begin() on uninitialized Vector");
    }
    return const_iterator(gsl_vector_long_ptr(gsl_vec.get(), 0), this->gsl_vec->stride);
}

template<>
inline typename Vector_t<unsigned long, gsl_vector_ulong>::const_iterator Vector_t<unsigned long, gsl_vector_ulong>::begin() const
{
    if(this->gsl_vec.get() == nullptr){
        throw std::runtime_error("Calling begin() on uninitialized Vector");
    }
    return const_iterator(gsl_vector_ulong_ptr(gsl_vec.get(), 0), this->gsl_vec->stride);
}

template<>
inline typename Vector_t<short, gsl_vector_short>::const_iterator Vector_t<short, gsl_vector_short>::begin() const
{
    if(this->gsl_vec.get() == nullptr){
        throw std::runtime_error("Calling begin() on uninitialized Vector");
    }
    return const_iterator(gsl_vector_short_ptr(gsl_vec.get(), 0), this->gsl_vec->stride);
}

template<>
inline typename Vector_t<unsigned short, gsl_vector_ushort>::const_iterator Vector_t<unsigned short, gsl_vector_ushort>::begin() const
{
    if(this->gsl_vec.get() == nullptr){
        throw std::runtime_error("Calling begin() on uninitialized Vector");
    }
    return const_iterator(gsl_vector_ushort_ptr(gsl_vec.get(), 0), this->gsl_vec->stride);
}

template<>
inline typename Vector_t<char, gsl_vector_char>::const_iterator Vector_t<char, gsl_vector_char>::begin() const
{
    if(this->gsl_vec.get() == nullptr){
        throw std::runtime_error("Calling begin() on uninitialized Vector");
    }
    return const_iterator(gsl_vector_char_ptr(gsl_vec.get(), 0), this->gsl_vec->stride);
}

template<>
inline typename Vector_t<unsigned char, gsl_vector_uchar>::const_iterator Vector_t<unsigned char, gsl_vector_uchar>::begin() const
{
    if(this->gsl_vec.get() == nullptr){
        throw std::runtime_error("Calling begin() on uninitialized Vector");
    }
    return const_iterator(gsl_vector_uchar_ptr(gsl_vec.get(), 0), this->gsl_vec->stride);
}

template<>
inline typename Vector_t<Complex_t<double, gsl_complex>, gsl_vector_complex, std::allocator<gsl_complex>>::const_iterator Vector_t<Complex_t<double, gsl_complex>, gsl_vector_complex, std::allocator<gsl_complex>>::begin() const
{
    if(this->gsl_vec.get() == nullptr){
        throw std::runtime_error("Calling begin() on uninitialized Vector");
    }
    return const_iterator(gsl_vector_complex_ptr(gsl_vec.get(), 0), this->gsl_vec->stride);
}

template<>
inline typename Vector_t<Complex_t<long double, gsl_complex_long_double>, gsl_vector_complex_long_double, std::allocator<gsl_complex_long_double>>::const_iterator Vector_t<Complex_t<long double, gsl_complex_long_double>, gsl_vector_complex_long_double, std::allocator<gsl_complex_long_double>>::begin() const
{
    if(this->gsl_vec.get() == nullptr){
        throw std::runtime_error("Calling begin() on uninitialized Vector");
    }
    return const_iterator(gsl_vector_complex_long_double_ptr(gsl_vec.get(), 0), this->gsl_vec->stride);
}

template<>
inline typename Vector_t<Complex_t<float, gsl_complex_float>, gsl_vector_complex_float, std::allocator<gsl_complex_float>>::const_iterator Vector_t<Complex_t<float, gsl_complex_float>, gsl_vector_complex_float, std::allocator<gsl_complex_float>>::begin() const
{
    if(this->gsl_vec.get() == nullptr){
        throw std::runtime_error("Calling begin() on uninitialized Vector");
    }
    return const_iterator(gsl_vector_complex_float_ptr(gsl_vec.get(), 0), this->gsl_vec->stride);
}



template<>
inline typename Vector_t<double, gsl_vector>::const_iterator Vector_t<double, gsl_vector>::cbegin() const
{
    if(this->gsl_vec.get() == nullptr){
        throw std::runtime_error("Calling begin() on uninitialized Vector");
    }
    return const_iterator(gsl_vector_ptr(gsl_vec.get(), 0), this->gsl_vec->stride);
}

template<>
inline typename Vector_t<long double, gsl_vector_long_double>::const_iterator Vector_t<long double, gsl_vector_long_double>::cbegin() const
{
    if(this->gsl_vec.get() == nullptr){
        throw std::runtime_error("Calling begin() on uninitialized Vector");
    }
    return const_iterator(gsl_vector_long_double_ptr(gsl_vec.get(), 0), this->gsl_vec->stride);
}

template<>
inline typename Vector_t<float, gsl_vector_float>::const_iterator Vector_t<float, gsl_vector_float>::cbegin() const
{
    if(this->gsl_vec.get() == nullptr){
        throw std::runtime_error("Calling begin() on uninitialized Vector");
    }
    return const_iterator(gsl_vector_float_ptr(gsl_vec.get(), 0), this->gsl_vec->stride);
}

template<>
inline typename Vector_t<int, gsl_vector_int>::const_iterator Vector_t<int, gsl_vector_int>::cbegin() const
{
    if(this->gsl_vec.get() == nullptr){
        throw std::runtime_error("Calling begin() on uninitialized Vector");
    }
    return const_iterator(gsl_vector_int_ptr(gsl_vec.get(), 0), this->gsl_vec->stride);
}

template<>
inline typename Vector_t<unsigned int, gsl_vector_uint>::const_iterator Vector_t<unsigned int, gsl_vector_uint>::cbegin() const
{
    if(this->gsl_vec.get() == nullptr){
        throw std::runtime_error("Calling begin() on uninitialized Vector");
    }
    return const_iterator(gsl_vector_uint_ptr(gsl_vec.get(), 0), this->gsl_vec->stride);
}

template<>
inline typename Vector_t<long, gsl_vector_long>::const_iterator Vector_t<long, gsl_vector_long>::cbegin() const
{
    if(this->gsl_vec.get() == nullptr){
        throw std::runtime_error("Calling begin() on uninitialized Vector");
    }
    return const_iterator(gsl_vector_long_ptr(gsl_vec.get(), 0), this->gsl_vec->stride);
}

template<>
inline typename Vector_t<unsigned long, gsl_vector_ulong>::const_iterator Vector_t<unsigned long, gsl_vector_ulong>::cbegin() const
{
    if(this->gsl_vec.get() == nullptr){
        throw std::runtime_error("Calling begin() on uninitialized Vector");
    }
    return const_iterator(gsl_vector_ulong_ptr(gsl_vec.get(), 0), this->gsl_vec->stride);
}

template<>
inline typename Vector_t<short, gsl_vector_short>::const_iterator Vector_t<short, gsl_vector_short>::cbegin() const
{
    if(this->gsl_vec.get() == nullptr){
        throw std::runtime_error("Calling begin() on uninitialized Vector");
    }
    return const_iterator(gsl_vector_short_ptr(gsl_vec.get(), 0), this->gsl_vec->stride);
}

template<>
inline typename Vector_t<unsigned short, gsl_vector_ushort>::const_iterator Vector_t<unsigned short, gsl_vector_ushort>::cbegin() const
{
    if(this->gsl_vec.get() == nullptr){
        throw std::runtime_error("Calling begin() on uninitialized Vector");
    }
    return const_iterator(gsl_vector_ushort_ptr(gsl_vec.get(), 0), this->gsl_vec->stride);
}

template<>
inline typename Vector_t<char, gsl_vector_char>::const_iterator Vector_t<char, gsl_vector_char>::cbegin() const
{
    if(this->gsl_vec.get() == nullptr){
        throw std::runtime_error("Calling begin() on uninitialized Vector");
    }
    return const_iterator(gsl_vector_char_ptr(gsl_vec.get(), 0), this->gsl_vec->stride);
}

template<>
inline typename Vector_t<unsigned char, gsl_vector_uchar>::const_iterator Vector_t<unsigned char, gsl_vector_uchar>::cbegin() const
{
    if(this->gsl_vec.get() == nullptr){
        throw std::runtime_error("Calling begin() on uninitialized Vector");
    }
    return const_iterator(gsl_vector_uchar_ptr(gsl_vec.get(), 0), this->gsl_vec->stride);
}

template<>
inline typename Vector_t<Complex_t<double, gsl_complex>, gsl_vector_complex, std::allocator<gsl_complex>>::const_iterator Vector_t<Complex_t<double, gsl_complex>, gsl_vector_complex, std::allocator<gsl_complex>>::cbegin() const
{
    if(this->gsl_vec.get() == nullptr){
        throw std::runtime_error("Calling begin() on uninitialized Vector");
    }
    return const_iterator(gsl_vector_complex_ptr(gsl_vec.get(), 0), this->gsl_vec->stride);
}

template<>
inline typename Vector_t<Complex_t<long double, gsl_complex_long_double>, gsl_vector_complex_long_double, std::allocator<gsl_complex_long_double>>::const_iterator Vector_t<Complex_t<long double, gsl_complex_long_double>, gsl_vector_complex_long_double, std::allocator<gsl_complex_long_double>>::cbegin() const
{
    if(this->gsl_vec.get() == nullptr){
        throw std::runtime_error("Calling begin() on uninitialized Vector");
    }
    return const_iterator(gsl_vector_complex_long_double_ptr(gsl_vec.get(), 0), this->gsl_vec->stride);
}

template<>
inline typename Vector_t<Complex_t<float, gsl_complex_float>, gsl_vector_complex_float, std::allocator<gsl_complex_float>>::const_iterator Vector_t<Complex_t<float, gsl_complex_float>, gsl_vector_complex_float, std::allocator<gsl_complex_float>>::cbegin() const
{
    if(this->gsl_vec.get() == nullptr){
        throw std::runtime_error("Calling begin() on uninitialized Vector");
    }
    return const_iterator(gsl_vector_complex_float_ptr(gsl_vec.get(), 0), this->gsl_vec->stride);
}

template<class T, class G, class A>
typename Vector_t<T, G, A>::iterator Vector_t<T, G, A>::end()
{
    return this->begin() + this->gsl_vec->stride * this->gsl_vec->size;
}

template<class T, class G, class A>
typename Vector_t<T, G, A>::const_iterator Vector_t<T, G, A>::end() const
{
    return this->begin() + this->gsl_vec->stride * this->gsl_vec->size;
}

template<class T, class G, class A>
typename Vector_t<T, G, A>::const_iterator Vector_t<T, G, A>::cend() const
{
    return this->cbegin() + this->gsl_vec->stride * this->gsl_vec->size;
}

template<class T, class G, class A>
typename Vector_t<T, G, A>::reverse_iterator Vector_t<T, G, A>::rbegin()
{
    return Vector_t<T, G, A>::reverse_iterator(--(this->end()));
}

template<class T, class G, class A>
typename Vector_t<T, G, A>::const_reverse_iterator Vector_t<T, G, A>::rbegin() const
{
    return Vector_t<T, G, A>::const_reverse_iterator(--(this->end()));
}

template<class T, class G, class A>
typename Vector_t<T, G, A>::const_reverse_iterator Vector_t<T, G, A>::crbegin() const
{
    return Vector_t<T, G, A>::const_reverse_iterator(--(this->end()));
}

template<class T, class G, class A>
typename Vector_t<T, G, A>::reverse_iterator Vector_t<T, G, A>::rend()
{
    return Vector_t<T, G, A>::reverse_iterator(--(this->begin()));
}

template<class T, class G, class A>
typename Vector_t<T, G, A>::const_reverse_iterator Vector_t<T, G, A>::rend() const
{
    return Vector_t<T, G, A>::const_reverse_iterator(--(this->begin()));
}

template<class T, class G, class A>
typename Vector_t<T, G, A>::const_reverse_iterator Vector_t<T, G, A>::crend() const
{
    return Vector_t<T, G, A>::const_reverse_iterator(--(this->cbegin()));
}

template<class T, class G, class A>
typename Vector_t<T, G, A>::reference Vector_t<T, G, A>::
    operator[] (const typename Vector_t<T, G, A>::size_type index)
{
    return *(this->begin() + index);
}

template<>
inline typename Vector_t<
    Complex_t<double, gsl_complex>,
    gsl_vector_complex, std::allocator<gsl_complex>>::reference
Vector_t<
    Complex_t<double, gsl_complex>,
    gsl_vector_complex, std::allocator<gsl_complex>>::operator[]
    (const typename Vector_t<
        Complex_t<double, gsl_complex>,
        gsl_vector_complex, std::allocator<gsl_complex>>::size_type index)
{
    return *gsl_vector_complex_ptr(this->gsl_vec.get(), index);
}

template<>
inline typename Vector_t<
    Complex_t<long double, gsl_complex_long_double>,
    gsl_vector_complex_long_double, std::allocator<gsl_complex_long_double>>::reference
Vector_t<
    Complex_t<long double, gsl_complex_long_double>,
    gsl_vector_complex_long_double, std::allocator<gsl_complex_long_double>>::operator[]
    (const typename Vector_t<
        Complex_t<long double, gsl_complex_long_double>,
        gsl_vector_complex_long_double, std::allocator<gsl_complex_long_double>>::size_type index)
{
    return *gsl_vector_complex_long_double_ptr(this->gsl_vec.get(), index);
}

template<>
inline typename Vector_t<
    Complex_t<float, gsl_complex_float>,
    gsl_vector_complex_float, std::allocator<gsl_complex_float>>::reference
Vector_t<
    Complex_t<float, gsl_complex_float>,
    gsl_vector_complex_float, std::allocator<gsl_complex_float>>::operator[]
    (const typename Vector_t<
        Complex_t<float, gsl_complex_float>,
        gsl_vector_complex_float, std::allocator<gsl_complex_float>>::size_type index)
{
    return *gsl_vector_complex_float_ptr(this->gsl_vec.get(), index);
}

template<class T, class G, class A>
typename Vector_t<T, G, A>::const_reference Vector_t<T, G, A>::
    operator[] (const typename Vector_t<T, G, A>::size_type index) const
{
    return *(this->gsl_vec->data + index);
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
typename Vector_t<T, G, A>::reference Vector_t<T, G, A>::
    at(const typename Vector_t<T, G, A>::size_type index)
{
    return (*this)[index];
}

template<class T, class G, class A>
typename Vector_t<T, G, A>::const_reference Vector_t<T, G, A>::
    at(const typename Vector_t<T, G, A>::size_type index) const
{
    return (*this)[index];
}

template<class T, class G, class A> template<class iter>
void Vector_t<T, G, A>::assign(iter start, iter end)
{
    if(end - start < 0){
        throw(std::runtime_error("Error in assign! End point comes before starting point\n"));
    }else if(static_cast<Vector_t<T, G, A>::size_type>(end - start) > this->size() ){
        throw(std::runtime_error("Attemptingto assign too many values! Vector too short\n"));
    }

    auto current = this->begin();
    iter counter = start;
    while(counter != end){
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
inline std::string Vector_t<Complex_t<double, gsl_complex>, gsl_vector_complex, std::allocator<gsl_complex>>::to_string() const
{
    std::string res = "(";
    GSL::Complex_t<double, gsl_complex> tmp;
    for(Vector_t<Complex_t<double, gsl_complex>, gsl_vector_complex, std::allocator<gsl_complex>>::size_type i = 0; i < this->size(); i++){
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
inline std::string Vector_t<Complex_t<long double, gsl_complex_long_double>, gsl_vector_complex_long_double, std::allocator<gsl_complex_long_double>>::to_string() const
{
    std::string res = "(";
    GSL::Complex_t<long double, gsl_complex_long_double> tmp;
    for(Vector_t<Complex_t<long double, gsl_complex_long_double>, gsl_vector_complex_long_double, std::allocator<gsl_complex_long_double>>::size_type i = 0; i < this->size(); i++){
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
inline std::string Vector_t<Complex_t<float, gsl_complex_float>, gsl_vector_complex_float, std::allocator<gsl_complex_float>>::to_string() const
{
    std::string res = "(";
    GSL::Complex_t<float, gsl_complex_float> tmp;
    for(Vector_t<Complex_t<float, gsl_complex_float>, gsl_vector_complex_float, std::allocator<gsl_complex_float>>::size_type i = 0; i < this->size(); i++){
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
