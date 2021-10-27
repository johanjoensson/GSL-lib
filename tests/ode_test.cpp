#include "GSLpp/ode.h"
#include <vector>
#include <gtest/gtest.h>
#include <fstream>

/*******************************************************************************
* van der Pol oscillator from the gsl documentation                            *
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


    GSL::ODE_solver solver(GSL::Runge_Kutta_Prince_Dormand, 2);

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

/*******************************************************************************
* Dirac equation for central field potential                                   *
*******************************************************************************/
TEST(ODETest, TestDirac)
{
    const int Z = 1;
    const int kappa = 1;
    const double c = 2*137.035999174;
    const double E = -1/4. - 0.000004109;
    auto V = [=](const double r){ return -2*Z/r;};
    auto Vp = [=](const double r){return 2*Z/(r*r);};

    auto func = [=](double r, const std::vector<double>& y, std::vector<double>& f)
    {
        f[0] = -kappa/r*y[0] + 1/c*(E - V(r) + c*c)*y[1];
        f[1] = -1/c*(E - V(r))*y[0] + kappa/r*y[1];
    };

    auto jac = [=](double r, const std::vector<double>& y, std::vector<double>& dfdy, std::vector<double>& dfdt)
    {
        dfdy[0] = -kappa/r;
        dfdy[1] = -1/c*(E - V(r) + c*c);
        dfdy[2] = 1/c*(E - V(r));
        dfdy[3] = kappa/r;

        dfdt[0] = kappa/(r*r)*y[0] + 1/c*Vp(r)*y[1];
        dfdt[1] = -1/c*Vp(r)*y[0] - kappa/(r*r)*y[1];
    };

    GSL::ODE_solver solver(GSL::Runge_Kutta_Prince_Dormand, 2, 1e-12, 0);

    solver.set_rhs(func);
    solver.set_jacobian(jac);

    const double r_end = 40, midpoint = 30;
    double h = 1e-6, r = h;
    std::vector<double> y{r, r/c};
    std::vector<double> g, f, r_v;

    std::ofstream os;
    os.open("radDirac_test.dat", std::fstream::out);
    os << "# r     V(r)     g(r)     f(r)\n";

    while(r < midpoint){
        solver.apply(r, midpoint, h, y);
        os << r << " " << y[0] << " " << y[1] << "\n";
    }
    std::cout << "Resetting solver!" << std::endl;
    solver.reset();
    double scale_g = y[0], scale_f = y[1];
    r = r_end, h = -1e-6;
    y[0] = 1e-6, y[1] = -1e-8;
    while(r > midpoint){
        solver.apply(r, midpoint, h, y);
        g.push_back(y[0]);
        f.push_back(y[1]);
        r_v.push_back(r);
    }

    scale_g /= y[0];
    scale_f /= y[1];

    std::cout << "g.size() = " << g.size() << "\n";;
    for(size_t i = g.size() - 1; i > 0 ; i--){
        os << r_v[i] << " " << g[i]*scale_g << " " << f[i]*scale_f << "\n";
    }
    os << r_v[0] << " " << g[0]*scale_g << " " << f[0]*scale_f << "\n";
    os.close();

}
