#include "matrix.h"
#include <gsl/gsl_blas.h>
#include <gsl/gsl_cblas.h>

using namespace GSL;

std::ostream& GSL::operator<< (std::ostream& os, const BaseMatrix& a)
{
    return (os << a.to_string());
}

Matrix::Matrix()
 : BaseMatrix(), gsl_mat(nullptr)
{}

Matrix::Matrix(Matrix& m)
 : BaseMatrix(), gsl_mat(m.gsl_mat)
{}

Matrix::Matrix(const Matrix& m)
 : BaseMatrix(), gsl_mat(m.gsl_mat)
{}

Matrix::Matrix(Matrix&& m)
 : BaseMatrix(), gsl_mat(nullptr)
 {
     std::swap(gsl_mat, m.gsl_mat);
}

Matrix::Matrix(const size_t n1, const size_t n2)
 : BaseMatrix(), gsl_mat(gsl_matrix_calloc(n1, n2), gsl_matrix_free)
 // rows and cols are std::vectors of empty GSL::vectors
 // The GSL::Vector::~Vector() destructor will be called automatically
 // when the std::vectors go out of scope, we therefore need to initialize them
 // correctly!
 {
    if(gsl_mat == nullptr){
        throw std::runtime_error("Memory allocation (gsl_matrix_calloc)"
        " failed!");
    }
}

Matrix::Matrix(std::initializer_list<std::initializer_list<double>> m)
 : Matrix(m.size(), m.begin()->size())
{
    for(size_t i = 0; i < m.size(); i++){
        if(m.begin()[i].size() != gsl_mat->size2){
            throw std::runtime_error("Matrix has different row lengths!");
        }
        for(size_t j = 0; j < m.begin()[i].size(); j++){
            gsl_matrix_set(gsl_mat.get(), i, j, m.begin()[i].begin()[j]);
        }
    }
}

Matrix::~Matrix()
{
}

// Make this a copy of the Matrix m
// Copy the data, not just the pointers!
void Matrix::copy(const Matrix& m)
{
    if(this->gsl_mat.get() == nullptr){
        throw std::runtime_error("Error in matrix allocation!");
    }
    int stat = gsl_matrix_memcpy(this->gsl_mat.get(), m.gsl_mat.get());
    if(stat){
        std::string error_str =   gsl_strerror(stat);
        throw std::runtime_error("Error in memory copying.\nGSL error: "
        + error_str);
    }
}


Matrix& Matrix::operator= (const Matrix& m)
{
    // If &m and this are the same object, do nothing
    // especially do not deallocate any memory!
    if(this == &m){
        return *this;
    }

    this->gsl_mat = m.gsl_mat;

    return *this;
}
Matrix& Matrix::operator= (Matrix&& m)
{

    std::swap(gsl_mat, m.gsl_mat);

    return *this;
}

Vector Matrix::operator[](const size_t index)
{
    Vector res(gsl_matrix_row(gsl_mat.get(), index).vector);
    return res;
}

Matrix& Matrix::operator+= (const Matrix& b)
{
    int stat = gsl_matrix_add(this->gsl_mat.get(), b.gsl_mat.get());
    if(stat){
		std::string error_str =   gsl_strerror(stat);
		throw std::runtime_error("Error in matrix addition.\nGSL error: "
        + error_str);
	}
    return *this;
}
Matrix& Matrix::operator-= (const Matrix& b)
{
    int stat = gsl_matrix_sub(this->gsl_mat.get(), b.gsl_mat.get());
    if(stat){
		std::string error_str =   gsl_strerror(stat);
		throw std::runtime_error("Error in matrix subtraction.\nGSL error: "
        + error_str);
	}
    return *this;
}

Matrix& Matrix::operator*= (const Matrix& b)
{
    int stat = gsl_blas_dgemm(CblasNoTrans, CblasNoTrans, 1.0, this->gsl_mat.get(),
        b.gsl_mat.get(), 0.0, this->gsl_mat.get());
    if(stat){
		std::string error_str =   gsl_strerror(stat);
		throw std::runtime_error("Error in matrix multiplication.\nGSL error: "
        + error_str);
	}
    return *this;
}

Matrix& Matrix::operator/= (const Matrix& b)
{
    int stat = gsl_matrix_div_elements(this->gsl_mat.get(), b.gsl_mat.get());
    if(stat){
		std::string error_str =   gsl_strerror(stat);
		throw std::runtime_error("Error in matrix element-wise division.\nGSL error: "
        + error_str);
	}
    return *this;
}
Matrix& Matrix::operator*= (const double s)
{
    int stat = gsl_matrix_scale(this->gsl_mat.get(), s);
    if(stat){
		std::string error_str =   gsl_strerror(stat);
		throw std::runtime_error("Error in matrix scaling.\nGSL error: "
        + error_str);
	}
    return *this;
}

Matrix& Matrix::operator/= (const double s)
{
    int stat = gsl_matrix_scale(this->gsl_mat.get(), 1./s);
    if(stat){
		std::string error_str =   gsl_strerror(stat);
		throw std::runtime_error("Error in matrix scaling.\nGSL error: "
        + error_str);
	}
    return *this;
}


Matrix Matrix::operator+ (const Matrix& b) const
{
    Matrix res(this->gsl_mat.get()->size1, this->gsl_mat.get()->size2);
    int stat = gsl_matrix_memcpy(res.gsl_mat.get(),this->gsl_mat.get());
    if(stat){
		std::string error_str = gsl_strerror(stat);
		throw std::runtime_error("Error in memory copying.\nGSL error: "
        + error_str);
	}
    stat = gsl_matrix_add(res.gsl_mat.get(), b.gsl_mat.get());
    if(stat){
		std::string error_str =   gsl_strerror(stat);
		throw std::runtime_error("Error in matrix addition.\nGSL error: "
        + error_str);
	}

    return res;
}
Matrix Matrix::operator- (const Matrix& b) const
{
    Matrix res(this->gsl_mat.get()->size1, this->gsl_mat.get()->size2);
    int stat = gsl_matrix_memcpy(res.gsl_mat.get(), this->gsl_mat.get());
    if(stat){
		std::string error_str = gsl_strerror(stat);
		throw std::runtime_error("Error in memory copying.\nGSL error: "
        + error_str);
	}
    stat = gsl_matrix_sub(res.gsl_mat.get(), b.gsl_mat.get());
    if(stat){
		std::string error_str =   gsl_strerror(stat);
		throw std::runtime_error("Error in matrix subtraction.\nGSL error: "
        + error_str);
	}

    return res;
}
Matrix Matrix::operator* (const Matrix& b) const
{
    Matrix res(this->gsl_mat.get()->size1, b.gsl_mat.get()->size2);
    int stat = gsl_blas_dgemm(CblasNoTrans, CblasNoTrans, 1.0, this->gsl_mat.get(),
        b.gsl_mat.get(), 0.0, res.gsl_mat.get());
    if(stat){
		std::string error_str =   gsl_strerror(stat);
		throw std::runtime_error("Error in matrix multiplication.\nGSL error: "
        + error_str);
	}

    return res;
}
Matrix Matrix::operator/ (const Matrix& b) const
{
    Matrix res(this->gsl_mat.get()->size1, this->gsl_mat.get()->size2);
    int stat = gsl_matrix_memcpy(res.gsl_mat.get(),this->gsl_mat.get());
    if(stat){
		std::string error_str = gsl_strerror(stat);
		throw std::runtime_error("Error in memory copying.\nGSL error: "
        + error_str);
	}
    stat = gsl_matrix_div_elements(res.gsl_mat.get(), b.gsl_mat.get());
    if(stat){
		std::string error_str =   gsl_strerror(stat);
		throw std::runtime_error("Error in matrix element-wise division.\nGSL error: "
        + error_str);
	}

    return res;
}
Matrix Matrix::operator* (const double& s) const
{
    Matrix res(this->gsl_mat.get()->size1, this->gsl_mat.get()->size2);
    int stat = gsl_matrix_memcpy(res.gsl_mat.get(),this->gsl_mat.get());
    if(stat){
		std::string error_str = gsl_strerror(stat);
		throw std::runtime_error("Error in memory copying.\nGSL error: "
        + error_str);
	}
    stat = gsl_matrix_scale(res.gsl_mat.get(), s);
    if(stat){
		std::string error_str =   gsl_strerror(stat);
		throw std::runtime_error("Error in matrix scaling.\nGSL error: "
        + error_str);
	}

    return res;
}
Matrix GSL::operator*(const double& s, const Matrix& a)
{
    return a*s;
}
Matrix Matrix::operator/ (const double& s) const
{
    return 1./s*(*this);
}

Vector Matrix::operator* (const Vector& v) const
{
    Vector res(this->gsl_mat.get()->size1);
    int stat = gsl_blas_dgemv(CblasNoTrans, 1.0, this->gsl_mat.get(),
        v.gsl_vec.get(), 0.0, res.gsl_vec.get());
    if(stat){
		std::string error_str =   gsl_strerror(stat);
		throw std::runtime_error("Error in matrix-vector multiplication.\nGSL error: "
        + error_str);
	}

    return res;
}

Vector GSL::operator* (const Vector& v, const Matrix& a)
{
    Vector res(a.gsl_mat.get()->size2);
    int stat = gsl_blas_dgemv(CblasTrans, 1.0, a.gsl_mat.get(),
        v.gsl_vec.get(), 0.0, res.gsl_vec.get());
    if(stat){
		std::string error_str =   gsl_strerror(stat);
		throw std::runtime_error("Error in matrix-vector multiplication.\nGSL error: "
        + error_str);
	}

    return res;
}

Matrix Matrix::transpose() const
{
    Matrix res(this->gsl_mat.get()->size2, this->gsl_mat.get()->size1);

    gsl_matrix_transpose_memcpy(res.gsl_mat.get(), this->gsl_mat.get());

    return res;
}
Matrix Matrix::hermitian_conj() const
{
    return this->transpose();
}

bool GSL::operator== (const Matrix& u, const Matrix& v)
{
    return gsl_matrix_equal(u.gsl_mat.get(), v.gsl_mat.get());
}

bool GSL::operator!= (const Matrix& u, const Matrix& v)
{
    return !(u == v);
}

void Matrix::set_row(const size_t &i, const Vector &v)
{
    gsl_vector row = gsl_matrix_row(gsl_mat.get(), i).vector;
    gsl_vector_memcpy(&row, v.gsl_vec.get());
}

void Matrix::set_col(const size_t &i, const Vector &v)
{
    gsl_vector col = gsl_matrix_column(gsl_mat.get(), i).vector;
    gsl_vector_memcpy(&col, v.gsl_vec.get());
}

Vector Matrix::diag()
{
    Vector res(gsl_matrix_diagonal(this->gsl_mat.get()).vector);
    return res;
}

std::string Matrix::to_string() const
{
    size_t size_1 = this->gsl_mat.get()->size1;
    size_t size_2 = this->gsl_mat.get()->size2;
    double tmp;

    std::string res = "";

    res = "[";
    for(size_t i = 0; i < size_1; i++){
        if(i > 0){
            res += ", ";
        }
        res += "( ";
        for(size_t j = 0; j < size_2; j++){
            tmp = gsl_matrix_get(this->gsl_mat.get(), i, j);
            res += std::to_string(tmp);
            if(i < size_2 - 1){
                res += ",";
            }
            res += " ";
        }
        res += ")";
    }
    res += "]";
    return res;
}
