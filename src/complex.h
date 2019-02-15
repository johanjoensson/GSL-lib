#ifndef GSL_COMPLEX_IMPL_H
#define GSL_COMPLEX_IMPL_H

#include "complex_template.h"
#include "complex_template.tpp"

template class GSL::Complex_t<double, gsl_complex>;
template class GSL::Complex_t<long double, gsl_complex_long_double>;
template class GSL::Complex_t<float, gsl_complex_float>;
#endif // GSL_COMPLEX_IMPL_H
