#include "GSLpp/special_functions_coupling.h"
#include <gsl/gsl_sf_coupling.h>
#include <string>
#include <stdexcept>
#include <gsl/gsl_errno.h>

using namespace GSL;

namespace{
void print_error_message(std::string function_name, int& gsl_err_code)
{
    throw std::runtime_error("Error in " + function_name + "\nGSL error"
    " message: " + gsl_strerror(gsl_err_code));
}
}

Result GSL::wigner_3j(const int& ja, const int& jb, const int& jc,
    const int& ma, const int& mb, const int& mc)
{
    gsl_sf_result res{0., 0.};

    int stat = gsl_sf_coupling_3j_e(2*ja, 2*jb, 2*jc, 2*ma, 2*mb, 2*mc, &res);

    if(stat){
        print_error_message("Wigner 3j", stat);
    }
    return Result(res);
}
Result GSL::wigner_6j(const int& ja, const int& jb, const int& jc,
    const int& jd, const int& je, const int& jf)
{
    gsl_sf_result res{0., 0.};
    int stat = gsl_sf_coupling_6j_e(2*ja, 2*jb, 2*jc, 2*jd, 2*je, 2*jf, &res);

    if(stat){
        print_error_message("Wigner 6j", stat);
    }
    return Result(res);
}

Result GSL::wigner_9j(const int& ja, const int& jb, const int& jc,
    const int& jd, const int& je, const int& jf,
    const int& jg, const int& jh, const int& ji)
{
    gsl_sf_result res{0., 0.};
    int stat = gsl_sf_coupling_9j_e(2*ja, 2*jb, 2*jc, 2*jd, 2*je, 2*jf, 2*jg,
        2*jh, 2*ji, &res);

    if(stat){
        print_error_message("Wigner 9j", stat);
    }
    return Result(res);
}
