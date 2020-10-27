#include "GSLpp/ode.h"
#include <vector>
#include <gtest/gtest.h>
#include <fstream>

/*******************************************************************************
* van det Pol oscillator from the gsl documentation                            *
*******************************************************************************/
TEST(ODETest, TestVdPolOscillator)
{

    const double mu = 10;
    auto func = [mu](double, const std::vector<double>& y, std::vector<double>& f)
    {
        f[0] = y[1];
        f[1] = -y[0] - mu*y[1]*(y[0]*y[0] - 1);
    };
    auto jac = [mu](double, const std::vector<double>& y, std::vector<double>& dfdy, std::vector<double>& dfdt)
    {
        dfdy[0] = 0.0;
        dfdy[1] = 1.0;
        dfdy[2] = -2.0*mu*y[0]*y[1] - 1.0;
        dfdy[3] = -mu*(y[0]*y[0] - 1.0);

        dfdt[0] = 0;
        dfdt[1] = 0;
    };


    GSL::ODE_solver solver(GSL::Runge_Kutta_Prince_Diamond, 2);

    solver.set_rhs(func);
    solver.set_jacobian(jac);

    const double t_end = 100;
    double t = 0, h = 1e-6;
    std::vector<double> y{1.0, 0.0};

    std::ofstream os;
    os.open("vdPolOscillator_test.dat", std::fstream::out);
    while(t < t_end){
        solver.apply(t, t_end, h, y);
        os << t << " " << y[0] << " " << y[1] << "\n";
    }
    os.close();
}
