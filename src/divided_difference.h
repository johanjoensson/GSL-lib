#ifndef DIVIDED_DIFFERENCE_H
#define DIVIDED_DIFFERENCE_H

#include <gsl/gsl_poly.h>
#include <stdexcept>
#include <vector>

#include "polynomial.h"
#include <memory>

namespace GSL {

    class Divided_Difference_Representation{
    private:
        std::unique_ptr<double[]> dd;
        std::unique_ptr<double[]> x;
        size_t size;
    public:
        Divided_Difference_Representation()
         : dd(nullptr), x(nullptr), size(0)
         {};

        Divided_Difference_Representation(std::vector<double>& x, std::vector<double>& y);

        /* The class F must have an overloaded double operator()(const double)
         * i.e. a function call operator taking a double and returning a double*/
        template<class F>
        Divided_Difference_Representation(F& f, double a, double b, size_t n)
            : dd(new double[n]), x(new double[n]), size(n)
        {
            int stat = 0;
            std::unique_ptr<double[]> y(new double[n]);
            double delta = (b - a)/(n - 1);
            for(size_t i = 0; i < n; i++){
                x[i] = a + delta*i;
                y[i] = f(a + delta*i);
            }
            stat = gsl_poly_dd_init(this->dd.get(), this->x.get(), y.get(), n);
            if(stat){
                throw std::runtime_error("Error in creating divided difference "
                "representation.");
            }
        }

        double operator()(const double x);
        Polynomial<double, double> to_Taylor_series(const double x);

    };
}
#endif // DIVIDED_DIFFERENCE_H
