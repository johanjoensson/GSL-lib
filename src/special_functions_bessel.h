#ifndef SPECIAL_FUNCTIONS_BESSEL_H
#define SPECIAL_FUNCTIONS_BESSEL_H
#include <gsl/gsl_sf.h>
#include <gsl/gsl_sf_bessel.h>
#include <tuple>

namespace GSL{
    std::tuple<double, double> bessel_J0(double&);
    std::tuple<double, double> bessel_J1(double&);
    std::tuple<double, double> bessel_Jn(int&, double&);

    std::tuple<double, double> bessel_Y0(double&);
    std::tuple<double, double> bessel_Y1(double&);
    std::tuple<double, double> bessel_Yn(int&, double&);

    std::tuple<double, double> bessel_I0(double&);
    std::tuple<double, double> bessel_I1(double&);
    std::tuple<double, double> bessel_In(int&, double&);

    std::tuple<double, double> bessel_I0_scaled(double&);
    std::tuple<double, double> bessel_I1_scaled(double&);
    std::tuple<double, double> bessel_In_scaled(int&, double&);

    std::tuple<double, double> bessel_K0(double&);
    std::tuple<double, double> bessel_K1(double&);
    std::tuple<double, double> bessel_Kn(int&, double&);

    std::tuple<double, double> bessel_K0_scaled(double&);
    std::tuple<double, double> bessel_K1_scaled(double&);
    std::tuple<double, double> bessel_Kn_scaled(int&, double&);

    std::tuple<double, double> bessel_j0(double&);
    std::tuple<double, double> bessel_j1(double&);
    std::tuple<double, double> bessel_jn(int&, double&);

    std::tuple<double, double> bessel_y0(double&);
    std::tuple<double, double> bessel_y1(double&);
    std::tuple<double, double> bessel_yn(int&, double&);

    std::tuple<double, double> bessel_i0_scaled(double&);
    std::tuple<double, double> bessel_i1_scaled(double&);
    std::tuple<double, double> bessel_in_scaled(int&, double&);

    std::tuple<double, double> bessel_k0_scaled(double&);
    std::tuple<double, double> bessel_k1_scaled(double&);
    std::tuple<double, double> bessel_kn_scaled(int&, double&);


    std::tuple<double, double> bessel_Jnu(double&, double&);
    std::tuple<double, double> bessel_Ynu(double&, double&);
    std::tuple<double, double> bessel_Inu(double&, double&);
    std::tuple<double, double> bessel_Knu(double&, double&);

    std::tuple<double, double> bessel_J0_zeros(unsigned int&);
    std::tuple<double, double> bessel_J1_zeros(unsigned int&);
    std::tuple<double, double> bessel_Jnu_zeros(double&, unsigned int&);

}
#endif // SPECIAL_FUNCTIONS_BESSEL_H
