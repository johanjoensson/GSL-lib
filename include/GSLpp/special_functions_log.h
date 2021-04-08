#ifndef SPECIAL_FUNCTIONS_LOG_H
#define SPECIAL_FUNCTIONS_LOG_H
#include <GSLpp/special_functions_results.h>

namespace GSL{
    Result log(const double& x);
    Result log_abs(const double& x);
    Result log_1plusx(const double& x);
    Result log_1plusx_mx(const double& x);
}
#endif // SPECIAL_FUNCTIONS_LOG_H
