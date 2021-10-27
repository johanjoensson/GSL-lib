#include <gsl/gsl_linalg.h>
#include <gsl/gsl_permutation.h>
#include <memory>
#include <functional>
#include "GSLpp/linalg.h"

using namespace GSL;

GSL::Matrix_Complex GSL::cholesky_decomp(const GSL::Matrix_Complex& a)
{
    size_t N = a.num_rows();
    Matrix_Complex tmp(N, N);
    tmp.copy(a);
    int status = gsl_linalg_complex_cholesky_decomp(tmp.gsl_data());
    if(status){
        std::string error_str =   gsl_strerror(status);
        throw std::runtime_error("Error in complex Cholesky decomposition.\nGSL error: "
        + error_str);
    }

    for(size_t i = 0; i < N; i++){
        for(size_t j = i+1; j < N; j++){
            tmp[i][j] = GSL::Complex(0., 0.);
        }
    }

    return tmp;
}

std::tuple<GSL::Matrix, GSL::Permutation, int> GSL::lu_decomp(const GSL::Matrix& a)
{
    size_t N = a.num_rows();
    GSL::Matrix tmp(N, N);
    tmp.copy(a);
    GSL::Permutation p(N);
    int i = 0;
    int status = gsl_linalg_LU_decomp(tmp.gsl_data(), p.p_m.get(), &i);
    if(status){
        std::string error_str =   gsl_strerror(status);
        throw std::runtime_error("Error in real LU decomposition.\nGSL error: "
        + error_str);
    }

    return std::tuple<GSL::Matrix, GSL::Permutation, int>(std::move(tmp), p, i);
}

std::tuple<GSL::Matrix_Complex, GSL::Permutation, int> GSL::lu_decomp(const GSL::Matrix_Complex& a)
{
    size_t N = a.num_rows();
    GSL::Matrix_Complex tmp(N, N);
    tmp.copy(a);
    GSL::Permutation p(N);
    int i = 0;
    int status = gsl_linalg_complex_LU_decomp(tmp.gsl_data(), p.p_m.get(), &i);
    if(status){
        std::string error_str =   gsl_strerror(status);
        throw std::runtime_error("Error in complex LU decomposition.\nGSL error: "
        + error_str);
    }

    return std::tuple<GSL::Matrix_Complex, GSL::Permutation, int>(std::move(tmp), p, i);
}

GSL::Matrix GSL::lu_inverse(const GSL::Matrix& a)
{
    size_t N = a.num_rows();
    GSL::Matrix tmp(N, N), res(N, N);
    tmp.copy(a);
    std::tuple<GSL::Matrix, GSL::Permutation, int> lu = GSL::lu_decomp(tmp);
    int status = gsl_linalg_LU_invert(std::get<0>(lu).gsl_data(), std::get<1>(lu).p_m.get(), res.gsl_data());
    if(status){
        std::string error_str =   gsl_strerror(status);
        throw std::runtime_error("Error in LU inversion.\nGSL error: "
        + error_str);
    }
    return res;
}

double GSL::lu_det(const GSL::Matrix& a)
{
    size_t N = a.num_rows();
    GSL::Matrix tmp(N, N), res(N, N);
    tmp.copy(a);
    std::tuple<GSL::Matrix, GSL::Permutation, int> lu = GSL::lu_decomp(tmp);
    return gsl_linalg_LU_det(std::get<0>(lu).gsl_data(), std::get<2>(lu));
}

GSL::Matrix_Complex GSL::lu_inverse(const GSL::Matrix_Complex& a)
{
    size_t N = a.num_rows();
    GSL::Matrix_Complex tmp(N, N), res(N, N);
    tmp.copy(a);
    std::tuple<GSL::Matrix_Complex, GSL::Permutation, int> lu = GSL::lu_decomp(tmp);
    int status = gsl_linalg_complex_LU_invert(std::get<0>(lu).gsl_data(), std::get<1>(lu).p_m.get(), res.gsl_data());
    if(status){
        std::string error_str =   gsl_strerror(status);
        throw std::runtime_error("Error in complex LU inversion.\nGSL error: "
        + error_str);
    }
    return res;
}

GSL::Complex GSL::lu_det(const GSL::Matrix_Complex& a)
{
    size_t N = a.num_rows();
    GSL::Matrix_Complex tmp(N, N), res(N, N);
    tmp.copy(a);
    std::tuple<GSL::Matrix_Complex, GSL::Permutation, int> lu = GSL::lu_decomp(tmp);
    return  gsl_linalg_complex_LU_det(std::get<0>(lu).gsl_data(), std::get<2>(lu));
}

GSL::Matrix GSL::cholesky_decomp(const GSL::Matrix& a)
{
    size_t N = a.num_rows();
    GSL::Matrix tmp(N, N);
    tmp.copy(a);
    int status = gsl_linalg_cholesky_decomp(tmp.gsl_data());
    if(status){
        std::string error_str =   gsl_strerror(status);
        throw std::runtime_error("Error in complex Cholesky decomposition.\nGSL error: "
        + error_str);
    }

    for(size_t i = 0; i < N; i++){
        for(size_t j = i+1; j < N; j++){
            tmp[i][j] = 0.;
        }
    }
    return tmp;
}
