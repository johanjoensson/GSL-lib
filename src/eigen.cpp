#include "eigen.h"
#include <gsl/gsl_eigen.h>

#include <memory>
#include <functional>
#include <stdexcept>

using namespace GSL;

std::pair<Matrix_cx, Vector> GSL::hermitian_eigen(const Matrix_cx& A)
{
    size_t N = A.gsl_mat->size1;
    Matrix_cx a(N,N);
    std::unique_ptr<gsl_eigen_hermv_workspace,
        std::function<void(gsl_eigen_hermv_workspace*)>>
            w(gsl_eigen_hermv_alloc(N),
                gsl_eigen_hermv_free);
    Matrix_cx eigvecs(N, N);
    Vector eigvals(N);
    a.copy(A);
    int status = gsl_eigen_hermv(a.gsl_mat.get(), eigvals.gsl_vec.get(),
        eigvecs.gsl_mat.get(), w.get());

    if(status){
        std::string error_str =   gsl_strerror(status);
        throw std::runtime_error("Error in solving Hermitian eigenproblem.\nGSL error: "
        + error_str + "\n");
    }

    return std::pair<Matrix_cx, Vector>(eigvecs, eigvals);
}

std::pair<Matrix_cx, Vector> GSL::general_hermitian_eigen(
    const Matrix_cx&A, const Matrix_cx&B)
{
    size_t N = A.gsl_mat.get()->size1;
    Matrix_cx a(N,N), b(N,N);
    GSL::Vector eigvals(N);
    Matrix_cx eigvecs(N, N);
    a.copy(A);
    b.copy(B);

    std::unique_ptr<gsl_eigen_genhermv_workspace,
        std::function<void(gsl_eigen_genhermv_workspace*)>>
            w(gsl_eigen_genhermv_alloc(N),
                gsl_eigen_genhermv_free);
    int status = gsl_eigen_genhermv(a.gsl_mat.get(), b.gsl_mat.get(), eigvals.gsl_vec.get(),
        eigvecs.gsl_mat.get(), w.get());
    if(status){
        std::string error_str =   gsl_strerror(status);
        throw std::runtime_error("Error in solving general Hermitian eigenproblem.\nGSL error: "
        + error_str + "\n");
    }

    return std::pair<Matrix_cx, Vector>(eigvecs, eigvals);
}
