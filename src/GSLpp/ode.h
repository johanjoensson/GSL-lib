#include <vector>
#include <functional>
#include <gsl/gsl_odeiv2.h>
#include <memory>


namespace GSL{
    enum ode_stepper{
        Runge_Kutta_2,
        Runge_Kutta_4,
        Runge_Kutta_45,
        Runge_Kutta_Cash_Karp,
        Runge_Kutta_Prince_Diamond,
        Runge_Kutta_1_implicit,
        Runge_Kutta_2_implicit,
        Runge_Kutta_4_implicit,
        Burlisch_Stoer_implicit,
        Multistep_Adams,
        Multistep_Backwards_differentiation
    };

    class ODE_solver{
    private:
        std::unique_ptr<gsl_odeiv2_step, std::function<void(gsl_odeiv2_step*)>> step_m;
        std::unique_ptr<gsl_odeiv2_control, std::function<void(gsl_odeiv2_control*)>> controller_m;
        std::unique_ptr<gsl_odeiv2_evolve, std::function<void(gsl_odeiv2_evolve*)>> evolver_m;
        gsl_odeiv2_system sys_m;
        size_t dim_m;
    public:
        std::function<
            void(double, const std::vector<double>&, std::vector<double>&)> rhs_m;
        std::function<
            void(double, const std::vector<double>&, std::vector<double>&,
                std::vector<double>&)> jacobian_m;
        ODE_solver(ode_stepper stepper, size_t dim, const double abs_err = 1e-6, const double rel_err = 0);
        size_t dim() const {return dim_m;}
        void set_rhs(std::function<void(double, const std::vector<double>&, std::vector<double>&)> rhs)
        {
            rhs_m = rhs;
        }

        void set_jacobian(std::function<void(double, const std::vector<double>&, std::vector<double>&, std::vector<double>&)> jacobian)
        {
            jacobian_m = jacobian;
        }

        void init_system();

        void apply(double& t, const double t1, double& h, std::vector<double>& y);
    };
}
