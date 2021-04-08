#ifndef SPECIAL_FUNCTIONS_LAGUERRE_H
#define SPECIAL_FUNCTIONS_LAGUERRE_H

#include <GSLpp/special_functions_results.h>

namespace GSL{
Result laguerre_1(double a, double x);
Result laguerre_2(double a, double x);
Result laguerre_3(double a, double x);
Result laguerre_n(int n, double a, double x);
}

#endif // SPECIAL_FUNCTIONS_LAGUERRE_H
