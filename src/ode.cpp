#include "GSLpp/ode.h"
#include <gsl/gsl_errno.h>
#include <cmath>
#include <string>
#include <stdexcept>
#include <iostream>
#include <fstream>

namespace{
void print_error_message(std::string function_name, int& gsl_err_code)
{
    throw std::runtime_error("Error in " + function_name + "\nGSL error"
    " message: " + gsl_strerror(gsl_err_code));
}
}


using namespace GSL;
extern "C"  int rhs_function_in_C(double t, const double y[], double dydt[],
    void* solver_pointer)
{
    ODE_solver *solver = static_cast<ODE_solver*>(solver_pointer);

    std::vector<double> yprime{dydt, dydt + solver->dim()};

    solver->rhs_m(t, {y, y + solver->dim()}, yprime);

    for(size_t i = 0; i < solver->dim(); i++){
        dydt[i] = yprime[i];
    }

    return GSL_SUCCESS;
}

extern "C"  int jacobian_in_C(double t, const double y[], double* dfdy,
    double dfdt[], void* solver_pointer)
{
    std::cout << "Jacobian in C" << std::endl;
    ODE_solver *solver = static_cast<ODE_solver*>(solver_pointer);

    std::vector<double> fprime_t{dfdt, dfdt + solver->dim()},
        fprime_y{dfdy, dfdy + solver->dim()*solver->dim()};

    solver->jacobian_m(t, {y, y + solver->dim()}, fprime_t, fprime_y);

    for(size_t i = 0; i < solver->dim(); i++){
        dfdt[i] = fprime_t[i];
        for(size_t j = 0; j < solver->dim(); j++){
            dfdy[i*solver->dim() + j] = fprime_y[i*solver->dim() + j];
        }
    }

    return GSL_SUCCESS;
}


const gsl_odeiv2_step_type* gsl_stepper(ode_stepper stepper)
{
    switch(stepper){
        case Runge_Kutta_2: return gsl_odeiv2_step_rk2;
        break;
        case Runge_Kutta_4: return gsl_odeiv2_step_rk4;
        break;
        case Runge_Kutta_45: return gsl_odeiv2_step_rkf45;
        break;
        case Runge_Kutta_Cash_Karp: return gsl_odeiv2_step_rkck;
        break;
        case Runge_Kutta_Prince_Diamond: return gsl_odeiv2_step_rk8pd;
        break;
        case Runge_Kutta_1_implicit: return gsl_odeiv2_step_rk1imp;
        break;
        case Runge_Kutta_2_implicit: return gsl_odeiv2_step_rk2imp;
        break;
        case Runge_Kutta_4_implicit: return gsl_odeiv2_step_rk4imp;
        break;
        case Burlisch_Stoer_implicit: return gsl_odeiv2_step_bsimp;
        break;
        case Multistep_Adams: return gsl_odeiv2_step_msadams;
        break;
        case Multistep_Backwards_differentiation: return gsl_odeiv2_step_msbdf;
        break;
    }
    return nullptr;
}

ODE_solver::ODE_solver(ode_stepper stepper, size_t dim, const double abs_err, const double rel_err)
 : step_m(gsl_odeiv2_step_alloc(gsl_stepper(stepper), dim), gsl_odeiv2_step_free),
   controller_m(gsl_odeiv2_control_y_new(abs_err, rel_err), gsl_odeiv2_control_free),
   evolver_m(gsl_odeiv2_evolve_alloc(dim), gsl_odeiv2_evolve_free),
   sys_m({rhs_function_in_C, jacobian_in_C, dim, this}), dim_m(dim), rhs_m(), jacobian_m()
{}

void ODE_solver::reset()
{
    gsl_odeiv2_step_reset(this->step_m.get());
    gsl_odeiv2_evolve_reset(this->evolver_m.get());
}

void ODE_solver::apply(double& t, const double t1, double& h, std::vector<double>& y)
{
    int status = gsl_odeiv2_evolve_apply (evolver_m.get(), controller_m.get(),
    step_m.get(), &this->sys_m, &t, t1, &h, &(*y.begin()));

    if(status){
        print_error_message("apply", status);
    }
}


void ODE_solver::apply_fixed_step(double& t, const double h, std::vector<double>& y)
{
    int status = gsl_odeiv2_evolve_apply_fixed_step (evolver_m.get(), controller_m.get(),
    step_m.get(), &this->sys_m, &t, h, &(*y.begin()));

    if(status){
        print_error_message("apply", status);
    }
}
