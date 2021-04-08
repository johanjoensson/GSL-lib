#ifndef SPECIAL_FUNCTIONS_TRIG_H
#define SPECIAL_FUNCTIONS_TRIG_H
#include <GSLpp/special_functions_results.h>

namespace GSL{

    Result sin(const double& x);
    Result cos(const double& x);
    Result hypotenuse(const double& x, const double& y);
    Result sinc(const double& x);

    Result lnsinh(const double& x);
    Result lncosh(const double& x);
}

#endif // SPECIAL_FUNCTIONS_TRIG_H
