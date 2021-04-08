#ifndef SPECIAL_FUNCTIONS_LEGENDRE_H
#define SPECIAL_FUNCTIONS_LEGENDRE_H

#include <GSLpp/special_functions_results.h>

namespace GSL{

Result legendre_P1(const double& x);
Result legendre_P2(const double& x);
Result legendre_P3(const double& x);
Result legendre_Pl(const int& l, const double& x);

Result legendre_Q0(const double& x);
Result legendre_Q1(const double& x);
Result legendre_Ql(const int& l, const double& x);

Result legendre_Plm(const int l, const int m, const double& x);
Result legendre_sphPlm(const int l, const int m, const double& x);
}
#endif // SPECIAL_FUNCTIONS_LEGENDRE_H
