#ifndef GSL_SPECIAL_FUNCTIONS_GAMMA_BETA
#define GSL_SPECIAL_FUNCTIONS_GAMMA_BETA
#include "special_functions_results.h"

namespace GSL{
    Result gamma(const double x);
    Result lngamma(const double x);
    Result gammastar(const double x);
    Result gammainv(const double x);

    Result fact(const unsigned int n);
    Result doublefact(const unsigned int n);
    Result lnfact(const unsigned int n);
    Result lndoublefact(const unsigned int n);

    Result choose(const unsigned int n, const unsigned int m);
    Result lnchoose(const unsigned int n, const unsigned int m);
    Result taylorcoeff(const int n, const double x);

    Result poch(const double a, const double x);
    Result lnpoch(const double a, const double x);
    Result pochrel(const double a, const double x);

    Result gamma_inc(const double a, const double x);
    Result gamma_inc_Q(const double a, const double x);
    Result gamma_inc_P(const double a, const double x);

    Result beta(const double a, const double b);
    Result lnbeta(const double a, const double b);

    Result beta_inc(const double a, const double b, const double x);
}

#endif //GSL_SPECIAL_FUNCTIONS_GAMMA_BETA
