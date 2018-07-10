#ifndef SPECIAL_FUNCTIONS_BESSEL_H
#define SPECIAL_FUNCTIONS_BESSEL_H
#include "special_functions_results.h"

namespace GSL{
    Result bessel_J0(double&);
    Result bessel_J1(double&);
    Result bessel_Jn(int&, double&);

    Result bessel_Y0(double&);
    Result bessel_Y1(double&);
    Result bessel_Yn(int&, double&);

    Result bessel_I0(double&);
    Result bessel_I1(double&);
    Result bessel_In(int&, double&);

    Result bessel_I0_scaled(double&);
    Result bessel_I1_scaled(double&);
    Result bessel_In_scaled(int&, double&);

    Result bessel_K0(double&);
    Result bessel_K1(double&);
    Result bessel_Kn(int&, double&);

    Result bessel_K0_scaled(double&);
    Result bessel_K1_scaled(double&);
    Result bessel_Kn_scaled(int&, double&);

    Result bessel_j0(double&);
    Result bessel_j1(double&);
    Result bessel_jn(int&, double&);

    Result bessel_y0(double&);
    Result bessel_y1(double&);
    Result bessel_yn(int&, double&);

    Result bessel_i0_scaled(double&);
    Result bessel_i1_scaled(double&);
    Result bessel_in_scaled(int&, double&);

    Result bessel_k0_scaled(double&);
    Result bessel_k1_scaled(double&);
    Result bessel_kn_scaled(int&, double&);


    Result bessel_Jnu(double&, double&);
    Result bessel_Ynu(double&, double&);
    Result bessel_Inu(double&, double&);
    Result bessel_Knu(double&, double&);

    Result bessel_J0_zeros(unsigned int&);
    Result bessel_J1_zeros(unsigned int&);
    Result bessel_Jnu_zeros(double&, unsigned int&);

}
#endif // SPECIAL_FUNCTIONS_BESSEL_H
