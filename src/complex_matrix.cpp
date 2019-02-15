#include "complex_matrix.h"
#include <gsl/gsl_complex_math.h>
#include <gsl/gsl_blas.h>
#include <gsl/gsl_cblas.h>

using namespace GSL;

Complex_Matrix::Complex_Matrix()
 : BaseMatrix(), gsl_mat(nullptr)
{}

Complex_Matrix::Complex_Matrix(Complex_Matrix& m)
 : BaseMatrix(), gsl_mat(m.gsl_mat)
{}

Complex_Matrix::Complex_Matrix(const Complex_Matrix& m)
 : BaseMatrix(), gsl_mat(m.gsl_mat)
{}

Complex_Matrix::Complex_Matrix(Complex_Matrix&& m)
 : BaseMatrix(), gsl_mat(nullptr)
{
     std::swap(gsl_mat, m.gsl_mat);
}

Complex_Matrix::Complex_Matrix(const size_t n1, const size_t n2)
 : BaseMatrix(), gsl_mat(gsl_matrix_complex_calloc(n1, n2), gsl_matrix_complex_free)
 // rows and cols are std::vectors of empty GSL::vectors
 // The GSL::Complex_Vector::~Complex_Vector() destructor will be called automatically
 // when the std::vectors go out of scope, we therefore need to initialize them
 // correctly!
 {
    if(gsl_mat == nullptr){
        throw std::runtime_error("Memory allocation (gsl_matrix_complex_calloc)"
        " failed!");
    }

}

Complex_Matrix::Complex_Matrix(std::initializer_list<std::initializer_list<Complex>> m)
 : Complex_Matrix(m.size(), m.begin()->size())
{
    for(size_t i = 0; i < m.size(); i++){
        if(m.begin()[i].size() != gsl_mat->size2){
            throw std::runtime_error("Matrix has different row lengths!");
        }
        for(size_t j = 0; j < m.begin()[i].size(); j++){
            gsl_matrix_complex_set(gsl_mat.get(), i, j, *(m.begin()[i].begin()[j]).gsl_c);
        }
    }
}

Complex_Matrix::~Complex_Matrix()
{}

// Make this a copy of the Complex_Matrix m
// Copy the data, not just the pointers!
void Complex_Matrix::copy(const Complex_Matrix& m)
{
    if(this->gsl_mat.get() == nullptr){
        throw std::runtime_error("Error in matrix allocation!");
    }
    int stat = gsl_matrix_complex_memcpy(this->gsl_mat.get(), m.gsl_mat.get());
    if(stat){
        std::string error_str =   gsl_strerror(stat);
        throw std::runtime_error("Error in memory copying.\nGSL error: "
        + error_str);
    }
}


Complex_Matrix& Complex_Matrix::operator= (const Complex_Matrix& m)
{
    // If &m and this are the same object, do nothing
    // especially do not deallocate any memory!
    if(this == &m){
        return *this;
    }
    this->gsl_mat = m.gsl_mat;

    return *this;
}
Complex_Matrix& Complex_Matrix::operator= (Complex_Matrix&& m)
{
    std::swap(gsl_mat, m.gsl_mat);

    return *this;
}

Complex_Vector Complex_Matrix::operator[](const size_t index)
{
    Complex_Vector res(gsl_matrix_complex_row(gsl_mat.get(), index).vector);
    return res;
}

Complex_Matrix& Complex_Matrix::operator+= (const Complex_Matrix& b)
{
    int stat = gsl_matrix_complex_add(this->gsl_mat.get(), b.gsl_mat.get());
    if(stat){
		std::string error_str =   gsl_strerror(stat);
		throw std::runtime_error("Error in matrix addition.\nGSL error: "
        + error_str);
	}
    return *this;
}
Complex_Matrix& Complex_Matrix::operator-= (const Complex_Matrix& b)
{
    int stat = gsl_matrix_complex_sub(this->gsl_mat.get(), b.gsl_mat.get());
    if(stat){
		std::string error_str =   gsl_strerror(stat);
		throw std::runtime_error("Error in matrix subtraction.\nGSL error: "
        + error_str);
	}
    return *this;
}

Complex_Matrix& Complex_Matrix::operator*= (const Complex_Matrix& b)
{
    int stat = gsl_blas_zgemm(CblasNoTrans, CblasNoTrans, gsl_complex_rect(1.0,0.0), this->gsl_mat.get(),
        b.gsl_mat.get(), gsl_complex_rect(0.0, 0.0), this->gsl_mat.get());
    if(stat){
		std::string error_str =   gsl_strerror(stat);
		throw std::runtime_error("Error in matrix multiplication.\nGSL error: "
        + error_str);
	}
    return *this;
}

Complex_Matrix& Complex_Matrix::operator/= (const Complex_Matrix& b)
{
    int stat = gsl_matrix_complex_div_elements(this->gsl_mat.get(), b.gsl_mat.get());
    if(stat){
		std::string error_str =   gsl_strerror(stat);
		throw std::runtime_error("Error in matrix element-wise division.\nGSL error: "
        + error_str);
	}
    return *this;
}
Complex_Matrix& Complex_Matrix::operator*= (const double s)
{
    int stat = gsl_matrix_complex_scale(this->gsl_mat.get(), gsl_complex_rect(s, 0.0));
    if(stat){
		std::string error_str =   gsl_strerror(stat);
		throw std::runtime_error("Error in matrix scaling.\nGSL error: "
        + error_str);
	}
    return *this;
}

Complex_Matrix& Complex_Matrix::operator/= (const double s)
{
    int stat = gsl_matrix_complex_scale(this->gsl_mat.get(), gsl_complex_rect(1./s, 0.0));
    if(stat){
		std::string error_str =   gsl_strerror(stat);
		throw std::runtime_error("Error in matrix scaling.\nGSL error: "
        + error_str);
	}
    return *this;
}


Complex_Matrix Complex_Matrix::operator+ (const Complex_Matrix& b) const
{
    Complex_Matrix res(this->gsl_mat.get()->size1, this->gsl_mat.get()->size2);
    int stat = gsl_matrix_complex_memcpy(res.gsl_mat.get(),this->gsl_mat.get());
    if(stat){
		std::string error_str = gsl_strerror(stat);
		throw std::runtime_error("Error in memory copying.\nGSL error: "
        + error_str);
	}
    stat = gsl_matrix_complex_add(res.gsl_mat.get(), b.gsl_mat.get());
    if(stat){
		std::string error_str =   gsl_strerror(stat);
		throw std::runtime_error("Error in matrix addition.\nGSL error: "
        + error_str);
	}

    return res;
}
Complex_Matrix Complex_Matrix::operator- (const Complex_Matrix& b) const
{
    Complex_Matrix res(this->gsl_mat.get()->size1, this->gsl_mat.get()->size2);
    int stat = gsl_matrix_complex_memcpy(res.gsl_mat.get(),this->gsl_mat.get());
    if(stat){
		std::string error_str = gsl_strerror(stat);
		throw std::runtime_error("Error in memory copying.\nGSL error: "
        + error_str);
	}
    stat = gsl_matrix_complex_sub(res.gsl_mat.get(), b.gsl_mat.get());
    if(stat){
		std::string error_str =   gsl_strerror(stat);
		throw std::runtime_error("Error in matrix subtraction.\nGSL error: "
        + error_str);
	}

    return res;
}
Complex_Matrix Complex_Matrix::operator* (const Complex_Matrix& b) const
{
    Complex_Matrix res(this->gsl_mat.get()->size1, b.gsl_mat.get()->size2);
    int stat = gsl_blas_zgemm(CblasNoTrans, CblasNoTrans, gsl_complex_rect(1.0, 0.0), this->gsl_mat.get(),
        b.gsl_mat.get(), gsl_complex_rect(0.0, 0.0), res.gsl_mat.get());
    if(stat){
		std::string error_str =   gsl_strerror(stat);
		throw std::runtime_error("Error in matrix multiplication.\nGSL error: "
        + error_str);
	}

    return res;
}
Complex_Matrix Complex_Matrix::operator/ (const Complex_Matrix& b) const
{
    Complex_Matrix res(this->gsl_mat.get()->size1, this->gsl_mat.get()->size2);
    int stat = gsl_matrix_complex_memcpy(res.gsl_mat.get(),this->gsl_mat.get());
    if(stat){
		std::string error_str = gsl_strerror(stat);
		throw std::runtime_error("Error in memory copying.\nGSL error: "
        + error_str);
	}
    stat = gsl_matrix_complex_div_elements(res.gsl_mat.get(), b.gsl_mat.get());
    if(stat){
		std::string error_str =   gsl_strerror(stat);
		throw std::runtime_error("Error in matrix element-wise division.\nGSL error: "
        + error_str);
	}

    return res;
}
Complex_Matrix Complex_Matrix::operator* (const double& s) const
{
    Complex_Matrix res(this->gsl_mat.get()->size1, this->gsl_mat.get()->size2);
    int stat = gsl_matrix_complex_memcpy(res.gsl_mat.get(),this->gsl_mat.get());
    if(stat){
		std::string error_str = gsl_strerror(stat);
		throw std::runtime_error("Error in memory copying.\nGSL error: "
        + error_str);
	}
    stat = gsl_matrix_complex_scale(res.gsl_mat.get(), gsl_complex_rect(s, 0.0));
    if(stat){
		std::string error_str =   gsl_strerror(stat);
		throw std::runtime_error("Error in matrix scaling.\nGSL error: "
        + error_str);
	}

    return res;
}
Complex_Matrix GSL::operator*(const double& s, const Complex_Matrix& a)
{
    return a*s;
}
Complex_Matrix Complex_Matrix::operator/ (const double& s) const
{
    return (*this)*1./s;
}

Complex_Vector Complex_Matrix::operator* (const Complex_Vector& v) const
{
    Complex_Vector res(this->gsl_mat.get()->size1);
    int stat = gsl_blas_zgemv(CblasNoTrans, gsl_complex_rect(1.0, 0.0), this->gsl_mat.get(),
        v.gsl_vec.get(), gsl_complex_rect(0.0,0.0), res.gsl_vec.get());
    if(stat){
		std::string error_str =   gsl_strerror(stat);
		throw std::runtime_error("Error in matrix-vector multiplication.\nGSL error: "
        + error_str);
	}

    return res;
}

Complex_Vector GSL::operator* (const Complex_Vector& v, const Complex_Matrix& a)
{
    Complex_Vector res(a.gsl_mat.get()->size2);
    int stat = gsl_blas_zgemv(CblasTrans, gsl_complex_rect(1.0, 0.0), a.gsl_mat.get(),
        v.gsl_vec.get(), gsl_complex_rect(0.0, 0.0), res.gsl_vec.get());
    if(stat){
		std::string error_str =   gsl_strerror(stat);
		throw std::runtime_error("Error in matrix-vector multiplication.\nGSL error: "
        + error_str);
	}

    return res;
}

Complex_Matrix Complex_Matrix::transpose() const
{
    Complex_Matrix res(this->gsl_mat.get()->size2, this->gsl_mat.get()->size1);

    gsl_matrix_complex_transpose_memcpy(res.gsl_mat.get(), this->gsl_mat.get());

    return res;
}

Complex_Matrix Complex_Matrix::hermitian_transpose() const
{
    Complex_Matrix tmp = this->transpose();
    for(size_t i = 0; i < this->gsl_mat->size1; i++){
        for(size_t j = 0; j < this->gsl_mat->size1; j++){
            tmp[i][j] = tmp[i][j].conjugate();
        }
    }
    return tmp;
}

bool GSL::operator== (const Complex_Matrix& u, const Complex_Matrix& v)
{
    return gsl_matrix_complex_equal(u.gsl_mat.get(), v.gsl_mat.get());
}

bool GSL::operator!= (const Complex_Matrix& u, const Complex_Matrix& v)
{
    return !(u == v);
}

void Complex_Matrix::set_row(const size_t &i, const Complex_Vector &v)
{
    gsl_vector_complex row = gsl_matrix_complex_row(gsl_mat.get(), i).vector;
    gsl_vector_complex_memcpy(&row, v.gsl_vec.get());
}

void Complex_Matrix::set_col(const size_t &i, const Complex_Vector &v)
{
    gsl_vector_complex col = gsl_matrix_complex_column(gsl_mat.get(), i).vector;
    gsl_vector_complex_memcpy(&col, v.gsl_vec.get());
}

Complex_Vector Complex_Matrix::diag()
{
    Complex_Vector res(gsl_matrix_complex_diagonal(this->gsl_mat.get()).vector);
    return res;
}

Complex_Vector Complex_Matrix::get_col(const size_t i)
{
    return Complex_Vector(gsl_matrix_complex_column(this->gsl_mat.get(), i).vector);
}

std::string Complex_Matrix::to_string() const
{
    size_t size_1 = this->gsl_mat.get()->size1;
    size_t size_2 = this->gsl_mat.get()->size2;
    Complex tmp;

    std::string res = "[";
    for(size_t i = 0; i < size_1; i++){
        if(i > 0 && i < size_1){
            res += ", ";
        }
        res += "( ";
        for(size_t j = 0; j < size_2; j++){
            tmp = Complex(gsl_matrix_complex_get(this->gsl_mat.get(), i, j));

            res += tmp.to_string();
            if(j < size_2 -1){
                res += ",";
            }
            res += " ";
        }
        res += ")";
    }
    res += "]";
    return res;
}
