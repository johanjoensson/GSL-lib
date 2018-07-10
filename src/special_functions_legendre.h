#ifndef SPECIAL_FUNCTIONS_LEGENDRE_H
#define SPECIAL_FUNCTIONS_LEGENDRE_H

#include "special_functions_results.h"

namespace GSL{

Result legendre_P1(double& x);
Result legendre_P2(double& x);
Result legendre_P3(double& x);
Result legendre_Pl(int& l, double& x);

Result legendre_Q0(double& x);
Result legendre_Q1(double& x);
Result legendre_Ql(int& l, double& x);

Result legendre_Plm(int l, int m, double& x);
Result legendre_sphPlm(int l, int m, double& x);
}
#endif // SPECIAL_FUNCTIONS_LEGENDRE_H
