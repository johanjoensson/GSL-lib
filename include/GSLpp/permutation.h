#ifndef GSLpp_PERMUTATION_H
#define GSLpp_PERMUTATION_H
#include <memory>
#include <functional>
#include <gsl/gsl_permutation.h>


namespace GSL {
    class Permutation{
    public:
//        std::unique_ptr<gsl_permutation, std::function<void(gsl_permutation*)>> p_m;
        std::shared_ptr<gsl_permutation> p_m;

        Permutation();
        Permutation(size_t N);
    };
}
#endif // GSLpp_PERMUTATION_H
