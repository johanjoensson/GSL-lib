#ifndef SPECIAL_FUNCTIONS_RESULTS_H
#define SPECIAL_FUNCTIONS_RESULTS_H

#include <gsl/gsl_sf_result.h>
#include <iostream>

namespace GSL{

    /************************************************************************//*
    * Class for simplifying error propagation
    ***************************************************************************/
    class Result{
        gsl_sf_result gsl_res;
    public:
        Result();
        Result(const double a, const double b);
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
        friend bool operator==(const Result& a, const Result& b);
        friend bool operator!=(const Result& a, const Result& b);
        friend std::ostream& operator<<(std::ostream&, const Result&);

        friend Result sin(const Result&);
        friend Result cos(const Result&);

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
    bool operator==(const Result& a, const Result& b);
    bool operator!=(const Result& a, const Result& b);

    Result sin(const Result&);
    Result cos(const Result&);

    std::ostream& operator<<(std::ostream&, const Result&);

    Result exp(const Result& x);
}

#endif // SPECIAL_FUNCTIONS_RESULTS_H
