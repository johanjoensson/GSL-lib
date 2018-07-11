#ifndef SPECIAL_FUNCTIONS_ERF_H
#define SPECIAL_FUNCTIONS_ERF_H
#include "special_functions_results.h"

namespace GSL{

Result erf(const double& x);
Result erfc(const double& x);
Result log_erfc(const double& x);

Result erf_Z(const double& x);
Result erf_Q(const double& x);
Result hazard(const double& x);
}
#endif // SPECIAL_FUNCTIONS_ERF_H
