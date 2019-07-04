#ifndef SPECIAL_FUNCTIONS_HERMITE_H
#define SPECIAL_FUNCTIONS_HERMITE_H

#include <vector>
#include "special_functions_results.h"


namespace GSL{

Result hermite_prob(const int n, const double x);
Result hermite_prob_series(const int nmax, const double x, const std::vector<double>& a);

Result hermite_phys(const int n, const double x);
Result hermite_phys_series(const int nmax, const double x, const std::vector<double>& a);

}

#endif // SPECIAL_FUNCTIONS_HERMITE_H
