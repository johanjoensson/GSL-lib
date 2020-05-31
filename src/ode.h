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
        size_t dim_m;
    public:
        std::function<
            void(double, const std::vector<double>&, std::vector<double>&)> rhs;
        std::function<
            void(double, const std::vector<double>&, std::vector<double>&,
                std::vector<double>&)> jacobian;
        ODE_solver(ode_stepper stepper, size_t dim);
        size_t dim() const {return dim_m;}
        void set_rhs(std::function<void(double, const std::vector<double>&, std::vector<double>&)>);
        void set_jacobian(std::function<void(double, const std::vector<double>&, std::vector<double>&, std::vector<double>&)>);
    };
}
