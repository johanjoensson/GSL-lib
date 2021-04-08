#ifndef SPECIAL_FUNCTIONS_BESSEL_H
#define SPECIAL_FUNCTIONS_BESSEL_H
#include <GSLpp/special_functions_results.h>

namespace GSL{
    Result bessel_J0(const double&);
    Result bessel_J1(const double&);
    Result bessel_Jn(const int&, const double&);

    Result bessel_Y0(const double&);
    Result bessel_Y1(const double&);
    Result bessel_Yn(const int&, const double&);

    Result bessel_I0(const double&);
    Result bessel_I1(const double&);
    Result bessel_In(const int&, const double&);

    Result bessel_I0_scaled(const double&);
    Result bessel_I1_scaled(const double&);
    Result bessel_In_scaled(const int&, const double&);

    Result bessel_K0(const double&);
    Result bessel_K1(const double&);
    Result bessel_Kn(const int&, const double&);

    Result bessel_K0_scaled(const double&);
    Result bessel_K1_scaled(const double&);
    Result bessel_Kn_scaled(const int&, const double&);

    Result bessel_j0(const double&);
    Result bessel_j1(const double&);
    Result bessel_jn(const int&, const double&);

    Result bessel_y0(const double&);
    Result bessel_y1(const double&);
    Result bessel_yn(const int&, const double&);

    Result bessel_i0_scaled(const double&);
    Result bessel_i1_scaled(const double&);
    Result bessel_in_scaled(const int&, const double&);

    Result bessel_k0_scaled(const double&);
    Result bessel_k1_scaled(const double&);
    Result bessel_kn_scaled(const int&, const double&);


    Result bessel_Jnu(const double&, const double&);
    Result bessel_Ynu(const double&, const double&);
    Result bessel_Inu(const double&, const double&);
    Result bessel_Knu(const double&, const double&);

    Result bessel_J0_zeros(unsigned const int&);
    Result bessel_J1_zeros(unsigned const int&);
    Result bessel_Jnu_zeros(const double&, unsigned const int&);

}
#endif // SPECIAL_FUNCTIONS_BESSEL_H
