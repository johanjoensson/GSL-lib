#include "GSLpp/permutation.h"

using namespace GSL;

Permutation::Permutation()
 : p_m(nullptr)
{}

Permutation::Permutation(size_t N)
 : p_m(gsl_permutation_alloc(N), gsl_permutation_free)
{}
