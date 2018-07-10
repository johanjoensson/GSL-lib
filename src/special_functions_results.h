#ifndef SPECIAL_FUNCTIONS_RESULTS_H
#define SPECIAL_FUNCTIONS_RESULTS_H

#include <gsl/gsl_sf_result.h>

namespace GSL{

    /************************************************************************//*
    * Class for simplifying error propagation
    ***************************************************************************/
    class Result{
        gsl_sf_result gsl_res;
    public:
        Result();
        Result(gsl_sf_result res);
        double val;
        double err;

        // Arithmetic operators that  handle (maximum-)error propagation
        friend Result operator+(const Result&, const Result&);
        friend Result operator+(const Result&, const double&);
        friend Result operator+(const double&, const Result&);
        friend Result operator-(const Result&, const Result&);
        friend Result operator-(const Result&, const double&);
        friend Result operator-(const double&, const Result&);
        friend Result operator*(const Result&, const Result&);
        friend Result operator*(const Result&, const double&);
        friend Result operator*(const double&, const Result&);
        friend Result operator/(const Result&, const Result&);
        friend Result operator/(const Result&, const double&);
        friend Result operator/(const double&, const Result&);

        Result& operator+=(const Result&);
        Result& operator+=(const double&);
        Result& operator-=(const Result&);
        Result& operator-=(const double&);
        Result& operator*=(const Result&);
        Result& operator*=(const double&);
        Result& operator/=(const Result&);
        Result& operator/=(const double&);
    };

    Result operator+(const Result&, const Result&);
    Result operator+(const Result&, const double&);
    Result operator+(const double&, const Result&);
    Result operator-(const Result&, const Result&);
    Result operator-(const Result&, const double&);
    Result operator-(const double&, const Result&);
    Result operator*(const Result&, const Result&);
    Result operator*(const Result&, const double&);
    Result operator*(const double&, const Result&);
    Result operator/(const Result&, const Result&);
    Result operator/(const Result&, const double&);
    Result operator/(const double&, const Result&);
}

#endif // SPECIAL_FUNCTIONS_RESULTS_H
