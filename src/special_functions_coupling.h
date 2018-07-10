#ifndef SPECIAL_FUNCTIONS_COUPLING_H
#define SPECIAL_FUNCTIONS_COUPLING_H
#include "special_functions_results.h"
#include <stdexcept>
#include <gsl/gsl_errno.h>

namespace GSL{
    Result wigner_3j(const int&, const int&, const int&, const int&, const int&,
        const int&);
    Result wigner_6j(const int&, const int&, const int&, const int&, const int&,
        const int&);
    Result wigner_9j(const int&, const int&, const int&, const int&, const int&,
        const int&, const int&, const int&, const int&);
}

#endif // SPECIAL_FUNCTIONS_COUPLING_H
