#include "GSLpp/eigen.h"
#include <gsl/gsl_eigen.h>

#include <memory>
#include <functional>
#include <stdexcept>

using namespace GSL;

gsl_eigen_sort_t gsl_sort(SORTING sorting)
{
    switch(sorting){
        case SORTING::VALUE_ASCENDING:
            return GSL_EIGEN_SORT_VAL_ASC;
        case SORTING::VALUE_DESCENDING:
            return GSL_EIGEN_SORT_VAL_DESC;
        case SORTING::ABSOLUTE_VALUE_ASCENDING:
            return GSL_EIGEN_SORT_ABS_ASC;
        case SORTING::ABSOLUTE_VALUE_DESCENDING:
            return GSL_EIGEN_SORT_ABS_DESC;
        default:
            throw std::runtime_error("Unknown SORTING supplied!");
    }
    return GSL_EIGEN_SORT_VAL_ASC;
}

std::pair<Matrix_Complex, Vector> GSL::hermitian_eigen(const Matrix_Complex& A)
{
    size_t N = A.num_rows();
    Matrix_Complex a(N,N);
    std::unique_ptr<gsl_eigen_hermv_workspace,
        std::function<void(gsl_eigen_hermv_workspace*)>>
            w(gsl_eigen_hermv_alloc(N),
                gsl_eigen_hermv_free);
    Matrix_Complex eigvecs(N, N);
    Vector eigvals(N);
    a.copy(A);
    int status = gsl_eigen_hermv(a.gsl_data(), eigvals.gsl_data(),
        eigvecs.gsl_data(), w.get());

    if(status){
        std::string error_str =   gsl_strerror(status);
        throw std::runtime_error("Error in solving Hermitian eigenproblem.\nGSL error: "
        + error_str + "\n");
    }

    return std::pair<Matrix_Complex, Vector> (std::move(eigvecs), std::move(eigvals));
}

std::pair<Matrix_Complex, Vector> GSL::sort_hermitian_eigen(const Vector& evals, const Matrix_Complex& evecs, SORTING sorting)
{
    Matrix_Complex A(evecs.num_rows(), evecs.num_columns());
    Vector v(evals.size());
    A.copy(evecs);
    v.copy(evals);
    int status = gsl_eigen_hermv_sort(v.gsl_data(), A.gsl_data(), gsl_sort(sorting));
    if(status){
        std::string error_str =   gsl_strerror(status);
        throw std::runtime_error("Error in sorting Hermitian eigenvalues and eigenvectors.\nGSL error: "
        + error_str + "\n");
    }

    return std::pair<Matrix_Complex, Vector> (std::move(A), std::move(v));
}

std::pair<Matrix_Complex, Vector> GSL::general_hermitian_eigen(
    const Matrix_Complex& A, const Matrix_Complex&B)
{
    size_t N = A.num_rows();
    Matrix_Complex a(N,N), b(N,N);
    Vector eigvals(N);
    Matrix_Complex eigvecs(N, N);
    a.copy(A);
    b.copy(B);

    std::unique_ptr<gsl_eigen_genhermv_workspace,
        std::function<void(gsl_eigen_genhermv_workspace*)>>
            w(gsl_eigen_genhermv_alloc(N),
                gsl_eigen_genhermv_free);
    int status = gsl_eigen_genhermv(a.gsl_data(), b.gsl_data(), eigvals.gsl_data(),
        eigvecs.gsl_data(), w.get());
    if(status){
        std::string error_str =   gsl_strerror(status);
        throw std::runtime_error("Error in solving general Hermitian eigenproblem.\nGSL error: "
        + error_str + "\n");
    }

    return std::pair<Matrix_Complex, Vector> (std::move(eigvecs), std::move(eigvals));
}

std::pair<Matrix_Complex, Vector> GSL::sort_general_hermitian_eigen(const Vector& evals, const Matrix_Complex& evecs, SORTING sorting)
{
    Matrix_Complex A(evecs.num_rows(), evecs.num_columns());
    Vector v(evals.size());
    A.copy(evecs);
    v.copy(evals);
    int status = gsl_eigen_genhermv_sort(v.gsl_data(), A.gsl_data(), gsl_sort(sorting));
    if(status){
        std::string error_str =   gsl_strerror(status);
        throw std::runtime_error("Error in sorting generalHermitian eigenvalues and eigenvectors.\nGSL error: "
        + error_str + "\n");
    }

    return std::pair<Matrix_Complex, Vector> (std::move(A), std::move(v));
}
