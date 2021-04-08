#ifndef GSLpp_INTERP_H
#define GSLpp_INTERP_H
#include <gsl/gsl_interp.h>
#include <gsl/gsl_spline.h>
#include <vector>
#include <memory>
#include <iostream>

namespace GSL{
    enum Interpolation_type
    {
        Linear,
        Polynomial,
        CSpline,
        CSpline_periodic,
        Akima,
        Akima_periodic,
        Steffen
    };

    class Interpolation
    {
    private:
        // gsl_interp_accel* gsl_interp_accel_m;
        // gsl_spline* gsl_spline_m;
        std::shared_ptr<gsl_interp_accel> gsl_interp_accel_m;
        std::shared_ptr<gsl_spline> gsl_spline_m;
        // std::unique_ptr<gsl_interp_accel, decltype(gsl_interp_accel_free)> gsl_interp_accel_m;
        // std::unique_ptr<gsl_spline, decltype(gsl_spline_free)> gsl_spline_m;
    public:
        // Interpolation();
        Interpolation(const std::vector<double>&, const std::vector<double>&, Interpolation_type);
        ~Interpolation() = default;
        Interpolation(const Interpolation&) = default;
        Interpolation(Interpolation&&) = default;

        Interpolation& operator=(const Interpolation&) = default;
        Interpolation& operator=(Interpolation&&) = default;

        double operator()(const double) const;
        double deriv(const double, const size_t) const;
        double integrate(const double, const double) const;
    };
}

#endif // GSLpp_INTERP_H
