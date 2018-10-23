#include "matrix.h"
#include <gsl/gsl_blas.h>
#include <gsl/gsl_cblas.h>

using namespace GSL;

BaseMatrix::~BaseMatrix()
{
    if(count != nullptr){
        if(*count == 0){
            delete count;
        }
    }
}

BaseMatrix::BaseMatrix()
 : count(nullptr)
{}

BaseMatrix::BaseMatrix(const BaseMatrix &m)
 : count(m.count)
{
    if(count != nullptr){
        (*count)++;
    }
}

BaseMatrix::BaseMatrix(BaseMatrix &m)
 : count(m.count)
{}

BaseMatrix::BaseMatrix(BaseMatrix &&m)
 : BaseMatrix()
{
    std::swap(this->count, m.count);
}
std::ostream& GSL::operator<< (std::ostream& os, const BaseMatrix& a)
{
    return (os << a.to_string());
}

Matrix::Matrix()
 : BaseMatrix(), gsl_mat(nullptr), rows(), cols()
{}

Matrix::Matrix(Matrix& m)
 : BaseMatrix(m), gsl_mat(m.gsl_mat), rows(m.rows), cols(m.cols)
{}

Matrix::Matrix(const Matrix& m)
 : BaseMatrix(m), gsl_mat(m.gsl_mat), rows(m.rows), cols(m.cols)
{}

Matrix::Matrix(Matrix&& m)
 : BaseMatrix(m), gsl_mat(nullptr), rows(), cols()
 {
     std::swap(rows, m.rows);
     std::swap(cols, m.cols);
     std::swap(gsl_mat, m.gsl_mat);
}

Matrix::Matrix(const size_t n1, const size_t n2)
 : BaseMatrix(), rows(n1), cols(n2)
 // rows and cols are std::vectors of empty GSL::vectors
 // The GSL::Vector::~Vector() destructor will be called automatically
 // when the std::vectors go out of scope, we therefore need to initialize them
 // correctly!
 {
    gsl_mat = gsl_matrix_calloc(n1, n2);
    if(gsl_mat == nullptr){
        throw std::runtime_error("Memory allocation (gsl_matrix_calloc)"
        " failed!");
    }
    count = new size_t;
    *count = 1;

    // Copy data from rows and columns into the rows and cols structures
    // Temporary data container to copy from
    gsl_vector_view tmp = gsl_matrix_row(gsl_mat, 0);
    for(size_t i = 0; i < n1; i++){
        // Read row i into tmp
        tmp = gsl_matrix_row(gsl_mat, i);
        // Since rows[i] is an empty GSL::Vector we need to allocate the
        // gsl_vector
        rows[i].gsl_vec = new gsl_vector;
        *rows[i].gsl_vec = tmp.vector;
        rows[i].count = new int;
        *rows[i].count = 1;
        rows[i].gsl_vec->owner = 0;
	rows[i].matrix = true;

    }
    // Do the same thing we did for the rows for the columns
    for(size_t i = 0; i < n2; i++){
        tmp = gsl_matrix_column(gsl_mat, i);

        cols[i].gsl_vec = new gsl_vector;
        *cols[i].gsl_vec = tmp.vector;
        cols[i].count = new int;
        *cols[i].count = 1;
        cols[i].gsl_vec->owner = 0;
	cols[i].matrix = true;
    }
}

Matrix::~Matrix()
{
    // Make sure there is an allocated gsl_vector
    if(count != nullptr){
        // Reduce the number of references to the gsl_vector_complex by one
        *count -= 1;
        rows.clear();
        cols.clear();
        // If there are no more references to the vector, deallocate the memory
        if(*count <= 0){
            if(gsl_mat != nullptr){
                gsl_matrix_free(gsl_mat);
                gsl_mat = nullptr;
            }
        }
    }
}

// Make this a copy of the Matrix m
// Copy the data, not just the pointers!
void Matrix::copy(const Matrix& m)
{
    if(m.count == nullptr){
        throw std::runtime_error("Trying to copy uninitialized Matrix!\n");
    }
    /* Special cases to consider:
    * This Matrix is not initialized => Initialize it and copy data from m
    * This Matrix shares it's data with other matrices => allocate new
    gsl_matrix and copy the data from a into it (reducing count on the
    old matrix)
    * This Matrix is the only matrix using the data => copy the data
    directly from m
    * m is uninitialized => raise an error
    */
    // This Matrix is uninitialized
    if(this->count == nullptr){
        this->gsl_mat = gsl_matrix_alloc(m.gsl_mat->size1, m.gsl_mat->size2);
        this->count = new size_t;
        *this->count = 1;
        // Other matrices are using the data
    }else if(*this->count > 1){
        *this->count -= 1;
        // Create new data array
        this->gsl_mat = gsl_matrix_alloc(m.gsl_mat->size1, m.gsl_mat->size2);
        this->count = new size_t;
        *this->count = 1;
        // No other matrix is using the data!
        // Make sure the dimesnions of the gsl_matrix es are the same
    }else if(this->gsl_mat->size1 != m.gsl_mat->size1 || this->gsl_mat->size2 != m.gsl_mat->size2){
        gsl_matrix_free(this->gsl_mat);
        this->gsl_mat = gsl_matrix_alloc(m.gsl_mat->size1, m.gsl_mat->size2);
    }
    if(this->gsl_mat == nullptr){
        throw std::runtime_error("Error in matrix allocation!");
    }
    int stat = gsl_matrix_memcpy(this->gsl_mat, m.gsl_mat);
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
    if(this->count != nullptr){
	    (*count)--;
	    if(*count == 0){
		    if(gsl_mat->size1 != 0 && gsl_mat->size2 != 0){
		    	    gsl_matrix_free(gsl_mat);
		    }else{
			    delete gsl_mat;
		    }
		    delete count;
		    gsl_mat = nullptr;
		    count = nullptr;
	    }
    }

    this->gsl_mat = m.gsl_mat;
    this->count = m.count ;
    ++(*count);

    return *this;
}
Matrix& Matrix::operator= (Matrix&& m)
{

    std::swap(gsl_mat, m.gsl_mat);
    std::swap(count, m.count);

    std::swap(rows, m.rows);
    std::swap(cols, m.cols);

    return *this;
}

Vector& Matrix::operator[](const size_t index)
{
    return rows[index];
}

Matrix& Matrix::operator+= (const Matrix& b)
{
    int stat = gsl_matrix_add(this->gsl_mat, b.gsl_mat);
    if(stat){
		std::string error_str =   gsl_strerror(stat);
		throw std::runtime_error("Error in matrix addition.\nGSL error: "
        + error_str);
	}
    return *this;
}
Matrix& Matrix::operator-= (const Matrix& b)
{
    int stat = gsl_matrix_sub(this->gsl_mat, b.gsl_mat);
    if(stat){
		std::string error_str =   gsl_strerror(stat);
		throw std::runtime_error("Error in matrix subtraction.\nGSL error: "
        + error_str);
	}
    return *this;
}

Matrix& Matrix::operator*= (const Matrix& b)
{
    int stat = gsl_blas_dgemm(CblasNoTrans, CblasNoTrans, 1.0, this->gsl_mat,
        b.gsl_mat, 0.0, this->gsl_mat);
    if(stat){
		std::string error_str =   gsl_strerror(stat);
		throw std::runtime_error("Error in matrix multiplication.\nGSL error: "
        + error_str);
	}
    return *this;
}

Matrix& Matrix::operator/= (const Matrix& b)
{
    int stat = gsl_matrix_div_elements(this->gsl_mat, b.gsl_mat);
    if(stat){
		std::string error_str =   gsl_strerror(stat);
		throw std::runtime_error("Error in matrix element-wise division.\nGSL error: "
        + error_str);
	}
    return *this;
}
Matrix& Matrix::operator*= (const double s)
{
    int stat = gsl_matrix_scale(this->gsl_mat, s);
    if(stat){
		std::string error_str =   gsl_strerror(stat);
		throw std::runtime_error("Error in matrix scaling.\nGSL error: "
        + error_str);
	}
    return *this;
}

Matrix& Matrix::operator/= (const double s)
{
    int stat = gsl_matrix_scale(this->gsl_mat, 1./s);
    if(stat){
		std::string error_str =   gsl_strerror(stat);
		throw std::runtime_error("Error in matrix scaling.\nGSL error: "
        + error_str);
	}
    return *this;
}


Matrix Matrix::operator+ (const Matrix& b) const
{
    Matrix res(this->gsl_mat->size1, this->gsl_mat->size2);
    int stat = gsl_matrix_memcpy(res.gsl_mat,this->gsl_mat);
    if(stat){
		std::string error_str = gsl_strerror(stat);
		throw std::runtime_error("Error in memory copying.\nGSL error: "
        + error_str);
	}
    stat = gsl_matrix_add(res.gsl_mat, b.gsl_mat);
    if(stat){
		std::string error_str =   gsl_strerror(stat);
		throw std::runtime_error("Error in matrix addition.\nGSL error: "
        + error_str);
	}

    return res;
}
Matrix Matrix::operator- (const Matrix& b) const
{
    Matrix res(this->gsl_mat->size1, this->gsl_mat->size2);
    int stat = gsl_matrix_memcpy(res.gsl_mat,this->gsl_mat);
    if(stat){
		std::string error_str = gsl_strerror(stat);
		throw std::runtime_error("Error in memory copying.\nGSL error: "
        + error_str);
	}
    stat = gsl_matrix_sub(res.gsl_mat, b.gsl_mat);
    if(stat){
		std::string error_str =   gsl_strerror(stat);
		throw std::runtime_error("Error in matrix subtraction.\nGSL error: "
        + error_str);
	}

    return res;
}
Matrix Matrix::operator* (const Matrix& b) const
{
    Matrix res(this->gsl_mat->size1, b.gsl_mat->size2);
    int stat = gsl_blas_dgemm(CblasNoTrans, CblasNoTrans, 1.0, this->gsl_mat,
        b.gsl_mat, 0.0, res.gsl_mat);
    if(stat){
		std::string error_str =   gsl_strerror(stat);
		throw std::runtime_error("Error in matrix multiplication.\nGSL error: "
        + error_str);
	}

    return res;
}
Matrix Matrix::operator/ (const Matrix& b) const
{
    Matrix res(this->gsl_mat->size1, this->gsl_mat->size2);
    int stat = gsl_matrix_memcpy(res.gsl_mat,this->gsl_mat);
    if(stat){
		std::string error_str = gsl_strerror(stat);
		throw std::runtime_error("Error in memory copying.\nGSL error: "
        + error_str);
	}
    stat = gsl_matrix_div_elements(res.gsl_mat, b.gsl_mat);
    if(stat){
		std::string error_str =   gsl_strerror(stat);
		throw std::runtime_error("Error in matrix element-wise division.\nGSL error: "
        + error_str);
	}

    return res;
}
Matrix Matrix::operator* (const double& s) const
{
    Matrix res(this->gsl_mat->size1, this->gsl_mat->size2);
    int stat = gsl_matrix_memcpy(res.gsl_mat,this->gsl_mat);
    if(stat){
		std::string error_str = gsl_strerror(stat);
		throw std::runtime_error("Error in memory copying.\nGSL error: "
        + error_str);
	}
    stat = gsl_matrix_scale(res.gsl_mat, s);
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
    /*
    Matrix res(this->gsl_mat->size1, this->gsl_mat->size2);
    int stat = gsl_matrix_memcpy(res.gsl_mat,this->gsl_mat);
    if(stat){
		std::string error_str = gsl_strerror(stat);
		throw std::runtime_error("Error in memory copying.\nGSL error: "
        + error_str);
	}
    stat = gsl_matrix_scale(res.gsl_mat, 1./s);
    if(stat){
		std::string error_str =   gsl_strerror(stat);
		throw std::runtime_error("Error in matrix scaling.\nGSL error: "
        + error_str);
	}

    return res;
    */
    return 1./s*(*this);
}

Vector Matrix::operator* (const Vector& v) const
{
    Vector res(this->gsl_mat->size1);
    int stat = gsl_blas_dgemv(CblasNoTrans, 1.0, this->gsl_mat,
        v.gsl_vec, 0.0, res.gsl_vec);
    if(stat){
		std::string error_str =   gsl_strerror(stat);
		throw std::runtime_error("Error in matrix-vector multiplication.\nGSL error: "
        + error_str);
	}

    return res;
}

Vector GSL::operator* (const Vector& v, const Matrix& a)
{
    Vector res(a.gsl_mat->size2);
    int stat = gsl_blas_dgemv(CblasTrans, 1.0, a.gsl_mat,
        v.gsl_vec, 0.0, res.gsl_vec);
    if(stat){
		std::string error_str =   gsl_strerror(stat);
		throw std::runtime_error("Error in matrix-vector multiplication.\nGSL error: "
        + error_str);
	}

    return res;
}

Matrix Matrix::transpose() const
{
    Matrix res(this->gsl_mat->size2, this->gsl_mat->size1);

    gsl_matrix_transpose_memcpy(res.gsl_mat, this->gsl_mat);

    return res;
}
Matrix Matrix::hermitian_conj() const
{
    return this->transpose();
}

bool GSL::operator== (const Matrix& u, const Matrix& v)
{
    return gsl_matrix_equal(u.gsl_mat, v.gsl_mat);
}

bool GSL::operator!= (const Matrix& u, const Matrix& v)
{
    return !(u == v);
}

void Matrix::set_row(const size_t &i, const Vector &v)
{
    this->rows[i] = v;
}

void Matrix::set_col(const size_t &i, const Vector &v)
{
    this->cols[i] = v;
}

std::string Matrix::to_string() const
{
    size_t size_1 = this->gsl_mat->size1;
    size_t size_2 = this->gsl_mat->size2;
    double tmp;

    std::string res = "";

    res = "[";
    for(size_t i = 0; i < size_1; i++){
        if(i > 0){
            res += ", ";
        }
        res += "( ";
        for(size_t j = 0; j < size_2; j++){
            tmp = gsl_matrix_get(this->gsl_mat, i, j);
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
