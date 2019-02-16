#ifndef GSL_VECTOR_IMPL_H
#define GSL_VECTOR_IMPL_H

#include "vector_template.h"
#include "matrix_template.h"
#include "complex_template.h"
#include "vector_template.tpp"

template class GSL::Vector_t<double, gsl_vector>;
template class GSL::Vector_t<long double, gsl_vector_long_double>;
template class GSL::Vector_t<float, gsl_vector_float>;
template class GSL::Vector_t<int, gsl_vector_int>;
template class GSL::Vector_t<unsigned int, gsl_vector_uint>;
template class GSL::Vector_t<long, gsl_vector_long>;
template class GSL::Vector_t<unsigned long, gsl_vector_ulong>;
template class GSL::Vector_t<short, gsl_vector_short>;
template class GSL::Vector_t<unsigned short, gsl_vector_ushort>;
template class GSL::Vector_t<char, gsl_vector_char>;
template class GSL::Vector_t<unsigned char, gsl_vector_uchar>;
template class GSL::Vector_t<GSL::Complex_t<double, gsl_complex>, gsl_vector_complex, std::allocator<gsl_complex>>;
template class GSL::Vector_t<GSL::Complex_t<long double, gsl_complex_long_double>, gsl_vector_complex_long_double, std::allocator<gsl_complex_long_double>>;
template class GSL::Vector_t<GSL::Complex_t<float, gsl_complex_float>, gsl_vector_complex_float, std::allocator<gsl_complex_float>>;

#endif // GSL_VECTOR_IMPL_H
