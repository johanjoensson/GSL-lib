#include "GSLpp/divided_difference.h"
#include <cstring>

using namespace GSL;

Divided_Difference_Representation::Divided_Difference_Representation(
    std::vector<double>& xp, std::vector<double>& y)
    : dd(new double[xp.size()]), x(new double[xp.size()]), size(xp.size())
    {
        memcpy(this->x.get(), &xp[0], size*sizeof(double));
        gsl_poly_dd_init(this->dd.get(), this->x.get(), &y[0], size);
    }

double Divided_Difference_Representation::operator()(const double xp)
{
    return gsl_poly_dd_eval(this->dd.get(), this->x.get(), this->size, xp);
}

Polynomial<double, double> Divided_Difference_Representation::to_Taylor_series(const double xp)
{
    std::unique_ptr<double[]> w(new double[this->size]);
    std::unique_ptr<double[]> c(new double[this->size]);
    std::vector<double> res(this->size, 0);

    gsl_poly_dd_taylor(c.get(), xp, this->dd.get(), this->x.get(), this->size, w.get());

    for(size_t i = 0; i < this->size; i++){
        res[i] = c[i];
    }
    return res;
}
