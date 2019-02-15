#ifndef GSL_MATRIX_IMPL_H
#define GSL_MATRIX_IMPL_H
#include "matrix_template.h"
#include "complex_template.h"
#include "vector_template.h"
#include "matrix_template.tpp"

template class GSL::Matrix_t<double, gsl_matrix, gsl_vector>;
template class GSL::Matrix_t<long double, gsl_matrix_long_double, gsl_vector_long_double>;
template class GSL::Matrix_t<float, gsl_matrix_float, gsl_vector_float>;
template class GSL::Matrix_t<int, gsl_matrix_int, gsl_vector_int>;
template class GSL::Matrix_t<unsigned int, gsl_matrix_uint, gsl_vector_uint>;
template class GSL::Matrix_t<long, gsl_matrix_long, gsl_vector_long>;
template class GSL::Matrix_t<unsigned long, gsl_matrix_ulong, gsl_vector_ulong>;
template class GSL::Matrix_t<short, gsl_matrix_short, gsl_vector_short>;
template class GSL::Matrix_t<unsigned short, gsl_matrix_ushort, gsl_vector_ushort>;
template class GSL::Matrix_t<char, gsl_matrix_char, gsl_vector_char>;
template class GSL::Matrix_t<unsigned char, gsl_matrix_uchar, gsl_vector_uchar>;
template class GSL::Matrix_t<GSL::Complex, gsl_matrix_complex,
    gsl_vector_complex, std::allocator<gsl_complex>>;
template class GSL::Matrix_t<GSL::Complex_ld, gsl_matrix_complex_long_double,
    gsl_vector_complex_long_double, std::allocator<gsl_complex_long_double>>;
template class GSL::Matrix_t<GSL::Complex_f, gsl_matrix_complex_float,
    gsl_vector_complex_float, std::allocator<gsl_complex_float>>;

#endif // GSL_MATRIX_IMPL_H
