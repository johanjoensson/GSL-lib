#include "ode.h"
#include <gsl/gsl_errno.h>
#include <cmath>


using namespace GSL;
extern "C"  int rhs_function_in_C(double t, const double y[], double dydt[],
    void* solver_pointer)
{
    ODE_solver *solver = static_cast<ODE_solver*>(solver_pointer);
    std::vector<double> yprime{dydt, dydt + solver->dim()};
    solver->rhs(t, {y, y + solver->dim()}, yprime);
    for(size_t i = 0; i < solver->dim(); i++){
        dydt[i] = yprime[i];
    }
    return GSL_SUCCESS;
}

extern "C"  int jacobian_in_C(double t, const double y[], double* dfdy,
    double dfdt[], void* solver_pointer)
{
    ODE_solver *solver = static_cast<ODE_solver*>(solver_pointer);
    std::vector<double> fprime_t{dfdt, dfdt + solver->dim()},
        fprime_y{dfdy, dfdy + solver->dim()*solver->dim()};
    solver->jacobian(t, {y, y + solver->dim()}, fprime_t, fprime_y);
    for(size_t i = 0; i < solver->dim(); i++){
        dfdt[i] = fprime_t[i];
    }
    for(size_t i = 0; i < solver->dim()*solver->dim(); i++){
        dfdy[i] = fprime_y[i];
    }

    for(size_t i = 0; i < solver->dim(); i++){
        dfdt[i] = fprime_t[i];
        for(size_t j = 0; j < solver->dim(); j++){
            dfdy[i*solver->dim() + j] = fprime_y[i*solver->dim() + j];
        }
    }
    return GSL_SUCCESS;
}


std::unique_ptr<gsl_odeiv2_step_type> gsl_stepper(ode_stepper stepper)
{
    std::unique_ptr<gsl_odeiv2_step_type> res(new gsl_odeiv2_step_type);
    switch(stepper){
        case Runge_Kutta_2: *res = *gsl_odeiv2_step_rk2;
        break;
        case Runge_Kutta_4: *res = *gsl_odeiv2_step_rk4;
        break;
        case Runge_Kutta_45: *res = *gsl_odeiv2_step_rkf45;
        break;
        case Runge_Kutta_Cash_Karp: *res = *gsl_odeiv2_step_rkck;
        break;
        case Runge_Kutta_Prince_Diamond: *res = *gsl_odeiv2_step_rk8pd;
        break;
        case Runge_Kutta_1_implicit: *res = *gsl_odeiv2_step_rk1imp;
        break;
        case Runge_Kutta_2_implicit: *res = *gsl_odeiv2_step_rk2imp;
        break;
        case Runge_Kutta_4_implicit: *res = *gsl_odeiv2_step_rk4imp;
        break;
        case Burlisch_Stoer_implicit: *res = *gsl_odeiv2_step_bsimp;
        break;
        case Multistep_Adams: *res = *gsl_odeiv2_step_msadams;
        break;
        case Multistep_Backwards_differentiation: *res = *gsl_odeiv2_step_msbdf;
        break;
    }
    return res;
}

ODE_solver::ODE_solver(ode_stepper stepper, size_t dim)
 : step_m(gsl_odeiv2_step_alloc(gsl_stepper(stepper).get(), dim), gsl_odeiv2_step_free), dim_m(dim), rhs(), jacobian()
{}
