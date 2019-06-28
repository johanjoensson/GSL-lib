#include "special_functions_gamma_beta.h"
#include <gsl/gsl_sf_gamma.h>

using namespace GSL;

Result GSL::gamma(const double x)
{
    gsl_sf_result res{0., 0.};
    gsl_sf_gamma_e(x, &res);

    return res;
}

Result GSL::lngamma(const double x)
{
    gsl_sf_result res{0., 0.};
    gsl_sf_lngamma_e(x, &res);

    return res;
}

Result GSL::gammastar(const double x)
{
    gsl_sf_result res{0., 0.};
    gsl_sf_gammastar_e(x, &res);

    return res;
}

Result GSL::gammainv(const double x)
{
    gsl_sf_result res{0., 0.};
    gsl_sf_gammainv_e(x, &res);

    return res;
}

Result GSL::fact(const unsigned int n)
{
    gsl_sf_result res{0., 0.};
    gsl_sf_fact_e(n, &res);

    return res;
}

Result GSL::doublefact(const unsigned int n)
{
    gsl_sf_result res{0., 0.};
    gsl_sf_doublefact_e(n, &res);

    return res;
}

Result GSL::lnfact(const unsigned int n)
{
    gsl_sf_result res{0., 0.};
    gsl_sf_lnfact_e(n, &res);

    return res;
}

Result GSL::lndoublefact(const unsigned int n)
{
    gsl_sf_result res{0., 0.};
    gsl_sf_lndoublefact_e(n, &res);

    return res;
}

Result GSL::choose(const unsigned int n, const unsigned int m)
{
    gsl_sf_result res{0., 0.};
    gsl_sf_choose_e(n, m, &res);

    return res;
}

Result GSL::lnchoose(const unsigned int n, const unsigned int m)
{
    gsl_sf_result res{0., 0.};
    gsl_sf_lnchoose_e(n, m, &res);

    return res;
}

Result GSL::taylorcoeff(const int n, const double x)
{
    gsl_sf_result res{0., 0.};
    gsl_sf_taylorcoeff_e(n, x, &res);

    return res;
}


Result GSL::poch(const double a, const double x)
{
    gsl_sf_result res{0., 0.};
    gsl_sf_poch_e(a, x, &res);

    return res;
}

Result GSL::lnpoch(const double a, const double x)
{
    gsl_sf_result res{0., 0.};
    gsl_sf_lnpoch_e(a, x, &res);

    return res;
}

Result GSL::pochrel(const double a, const double x)
{
    gsl_sf_result res{0., 0.};
    gsl_sf_pochrel_e(a, x, &res);

    return res;
}


Result GSL::gamma_inc(const double a, const double x)
{
    gsl_sf_result res{0., 0.};
    gsl_sf_gamma_inc_e(a, x, &res);

    return res;
}

Result GSL::gamma_inc_Q(const double a, const double x)
{
    gsl_sf_result res{0., 0.};
    gsl_sf_gamma_inc_Q_e(a, x, &res);

    return res;
}

Result GSL::gamma_inc_P(const double a, const double x)
{
    gsl_sf_result res{0., 0.};
    gsl_sf_gamma_inc_P_e(a, x, &res);

    return res;
}


Result GSL::beta(const double a, const double b)
{
    gsl_sf_result res{0., 0.};
    gsl_sf_beta_e(a, b, &res);

    return res;
}

Result GSL::lnbeta(const double a, const double b)
{
    gsl_sf_result res{0., 0.};
    gsl_sf_lnbeta_e(a, b, &res);

    return res;
}


Result GSL::beta_inc(const double a, const double b, const double x)
{
    gsl_sf_result res{0., 0.};
    gsl_sf_beta_inc_e(a, b, x, &res);

    return res;
}
