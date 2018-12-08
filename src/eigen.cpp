#include "eigen.h"
#include <gsl/gsl_eigen.h>

#include <memory>
#include <functional>
#include <stdexcept>

using namespace GSL;

void GSL::hermitian_eigen(Complex_Matrix& eigvecs, Vector& eigvals)
{
    size_t N = eigvecs.gsl_mat.get()->size1;
    std::unique_ptr<gsl_eigen_hermv_workspace,
        std::function<void(gsl_eigen_hermv_workspace*)>>
            w(gsl_eigen_hermv_alloc(N),
                gsl_eigen_hermv_free);
    Complex_Matrix tmp_mat(N, N);
    int status = gsl_eigen_hermv(eigvecs.gsl_mat.get(), eigvals.gsl_vec.get(),
        tmp_mat.gsl_mat.get(), w.get());

    if(status){
        std::string error_str =   gsl_strerror(status);
        throw std::runtime_error("Error in solving Hermitian eigenproblem.\nGSL error: "
        + error_str);
    }

    eigvecs.copy(tmp_mat);
}

void GSL::general_hermitian_eigen(const Complex_Matrix&A, const Complex_Matrix&B, Complex_Matrix& eigvecs, Vector& eigvals)
{
    size_t N = A.gsl_mat.get()->size1;
    Complex_Matrix a(N,N), b(N,N);
    a.copy(A);
    b.copy(B);
    std::unique_ptr<gsl_eigen_genhermv_workspace,
        std::function<void(gsl_eigen_genhermv_workspace*)>>
            w(gsl_eigen_genhermv_alloc(N),
                gsl_eigen_genhermv_free);
    Complex_Matrix tmp_mat(N, N);
    int status = gsl_eigen_genhermv(a.gsl_mat.get(), b.gsl_mat.get(), eigvals.gsl_vec.get(),
        tmp_mat.gsl_mat.get(), w.get());
    if(status){
        std::string error_str =   gsl_strerror(status);
        throw std::runtime_error("Error in solving Hermitian eigenproblem.\nGSL error: "
        + error_str);
    }

    eigvecs.copy(tmp_mat);
}
