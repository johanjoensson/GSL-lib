#include "complex_matrix.h"
#include <gsl/gsl_complex_math.h>
#include <gsl/gsl_blas.h>
#include <gsl/gsl_cblas.h>

using namespace GSL;

Complex_Matrix::Complex_Matrix()
 : gsl_mat(nullptr), rows(), cols(), count(nullptr)
{
}

Complex_Matrix::Complex_Matrix(Complex_Matrix& m)
 : gsl_mat(m.gsl_mat), rows(m.rows), cols(m.cols), count(m.count)
{
    (*count)++;
}

Complex_Matrix::Complex_Matrix(const Complex_Matrix& m)
 : gsl_mat(m.gsl_mat), rows(m.rows), cols(m.cols), count(m.count)
{
    (*count)++;
}

Complex_Matrix::Complex_Matrix(Complex_Matrix&& m)
 : gsl_mat(m.gsl_mat), rows(), cols(), count(nullptr)
 {
     std::swap(count, m.count);
     std::swap(rows, m.rows);
     std::swap(cols, m.cols);
     m.gsl_mat = nullptr;
}

Complex_Matrix::Complex_Matrix(const size_t n1, const size_t n2)
 : rows(n1), cols(n2)
 // rows and cols are std::vectors of empty GSL::vectors
 // The GSL::Complex_Vector::~Complex_Vector() destructor will be called automatically
 // when the std::vectors go out of scope, we therefore need to initialize them
 // correctly!
 {
    gsl_mat = gsl_matrix_complex_calloc(n1, n2);
    if(gsl_mat == nullptr){
        throw std::runtime_error("Memory allocation (gsl_matrix_complex_calloc)"
        " failed!");
    }
    count = new size_t;
    *count = 1;

    // Copy data from rows and columns into the rows and cols structures
    // Temporary data container to copy from
    gsl_vector_complex_view tmp = gsl_matrix_complex_row(gsl_mat, 0);
    for(size_t i = 0; i < n1; i++){
        // Read row i into tmp
        tmp = gsl_matrix_complex_row(gsl_mat, i);
        // Since rows[i] is an empty GSL::Complex_Vector we need to allocate the
        // gsl_vector_complex
        rows[i].gsl_vec = new gsl_vector_complex;
        *rows[i].gsl_vec = tmp.vector;
        rows[i].count = new int;
        *rows[i].count = 1;
        rows[i].gsl_vec->owner = 0;
	rows[i].matrix = true;
    }
    // Do the same thing we did for the rows for the columns
    for(size_t i = 0; i < n2; i++){
        tmp = gsl_matrix_complex_column(gsl_mat, i);

        cols[i].gsl_vec = new gsl_vector_complex;
        *cols[i].gsl_vec = tmp.vector;
        cols[i].count = new int;
        *cols[i].count = 1;
        cols[i].gsl_vec->owner = 0;
	cols[i].matrix = true;
    }
}

Complex_Matrix::~Complex_Matrix()
{
    // Make sure there is an allocated gsl_vector_complex
    if(count != nullptr){
        // Reduce the number of references to the gsl_vector_complex by one
        *count -= 1;
        rows.clear();
        cols.clear();
        // If there are no more references to the vector, deallocate the memory
        if(*count <= 0){
            delete count;
            count = nullptr;
            if(gsl_mat != nullptr){
                gsl_matrix_complex_free(gsl_mat);
                gsl_mat = nullptr;
            }
        }
    }
}

// Make this a copy of the Complex_Matrix m
// Copy the data, not just the pointers!
void Complex_Matrix::copy(const Complex_Matrix& m)
{
    if(m.count == nullptr){
        throw std::runtime_error("Trying to copy uninitialized Complex_Matrix!\n");
    }
    /* Special cases to consider:
    * This Matrix is not initialized => Initialize it and copy data from m
    * This Matrix shares it's data with other matrices => allocate new
    gsl_matrix_complex and copy the data from a into it (reducing count on the
    old matrix)
    * This Matrix is the only matrix using the data => copy the data
    directly from m
    * m is uninitialized => raise an error
    */
    // This Matrix is uninitialized
    if(this->count == nullptr){
        this->gsl_mat = gsl_matrix_complex_alloc(m.gsl_mat->size1, m.gsl_mat->size2);
        this->count = new size_t;
        *this->count = 1;
        // Other matrices are using the data
    }else if(*this->count > 1){
        *this->count -= 1;
        // Create new data array
        this->gsl_mat = gsl_matrix_complex_alloc(m.gsl_mat->size1, m.gsl_mat->size2);
        this->count = new size_t;
        *this->count = 1;
        // No other matrix is using the data!
        // Make sure the dimesnions of the gsl_matrix_complex es are the same
    }else if(this->gsl_mat->size1 != m.gsl_mat->size1 || this->gsl_mat->size2 != m.gsl_mat->size2){
        gsl_matrix_complex_free(this->gsl_mat);
        this->gsl_mat = gsl_matrix_complex_alloc(m.gsl_mat->size1, m.gsl_mat->size2);
    }
    if(this->gsl_mat == nullptr){
        throw std::runtime_error("Error in matrix allocation!");
    }
    int stat = gsl_matrix_complex_memcpy(this->gsl_mat, m.gsl_mat);
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
    if(this->gsl_mat != nullptr && this->count != nullptr){
        gsl_matrix_complex_free(gsl_mat);
    }
    delete count;

    this->gsl_mat = m.gsl_mat;
    this->count = m.count ;
    ++(*count);

    return *this;
}
Complex_Matrix& Complex_Matrix::operator= (Complex_Matrix&& m)
{
    std::swap(gsl_mat, m.gsl_mat);
    std::swap(count, m.count);
    std::swap(rows, m.rows);
    std::swap(cols, m.cols);

    return *this;
}

Complex_Vector& Complex_Matrix::operator[](const size_t index)
{
    return rows[index];
}

Complex_Matrix& Complex_Matrix::operator+= (const Complex_Matrix& b)
{
    int stat = gsl_matrix_complex_add(this->gsl_mat, b.gsl_mat);
    if(stat){
		std::string error_str =   gsl_strerror(stat);
		throw std::runtime_error("Error in matrix addition.\nGSL error: "
        + error_str);
	}
    return *this;
}
Complex_Matrix& Complex_Matrix::operator-= (const Complex_Matrix& b)
{
    int stat = gsl_matrix_complex_sub(this->gsl_mat, b.gsl_mat);
    if(stat){
		std::string error_str =   gsl_strerror(stat);
		throw std::runtime_error("Error in matrix subtraction.\nGSL error: "
        + error_str);
	}
    return *this;
}

Complex_Matrix& Complex_Matrix::operator*= (const Complex_Matrix& b)
{
    int stat = gsl_blas_zgemm(CblasNoTrans, CblasNoTrans, gsl_complex_rect(1.0,0.0), this->gsl_mat,
        b.gsl_mat, gsl_complex_rect(0.0, 0.0), this->gsl_mat);
    if(stat){
		std::string error_str =   gsl_strerror(stat);
		throw std::runtime_error("Error in matrix multiplication.\nGSL error: "
        + error_str);
	}
    return *this;
}

Complex_Matrix& Complex_Matrix::operator/= (const Complex_Matrix& b)
{
    int stat = gsl_matrix_complex_div_elements(this->gsl_mat, b.gsl_mat);
    if(stat){
		std::string error_str =   gsl_strerror(stat);
		throw std::runtime_error("Error in matrix element-wise division.\nGSL error: "
        + error_str);
	}
    return *this;
}
Complex_Matrix& Complex_Matrix::operator*= (const double s)
{
    int stat = gsl_matrix_complex_scale(this->gsl_mat, gsl_complex_rect(s, 0.0));
    if(stat){
		std::string error_str =   gsl_strerror(stat);
		throw std::runtime_error("Error in matrix scaling.\nGSL error: "
        + error_str);
	}
    return *this;
}

Complex_Matrix& Complex_Matrix::operator/= (const double s)
{
    int stat = gsl_matrix_complex_scale(this->gsl_mat, gsl_complex_rect(1./s, 0.0));
    if(stat){
		std::string error_str =   gsl_strerror(stat);
		throw std::runtime_error("Error in matrix scaling.\nGSL error: "
        + error_str);
	}
    return *this;
}


Complex_Matrix Complex_Matrix::operator+ (const Complex_Matrix& b) const
{
    Complex_Matrix res(this->gsl_mat->size1, this->gsl_mat->size2);
    int stat = gsl_matrix_complex_memcpy(res.gsl_mat,this->gsl_mat);
    if(stat){
		std::string error_str = gsl_strerror(stat);
		throw std::runtime_error("Error in memory copying.\nGSL error: "
        + error_str);
	}
    stat = gsl_matrix_complex_add(res.gsl_mat, b.gsl_mat);
    if(stat){
		std::string error_str =   gsl_strerror(stat);
		throw std::runtime_error("Error in matrix addition.\nGSL error: "
        + error_str);
	}

    return res;
}
Complex_Matrix Complex_Matrix::operator- (const Complex_Matrix& b) const
{
    Complex_Matrix res(this->gsl_mat->size1, this->gsl_mat->size2);
    int stat = gsl_matrix_complex_memcpy(res.gsl_mat,this->gsl_mat);
    if(stat){
		std::string error_str = gsl_strerror(stat);
		throw std::runtime_error("Error in memory copying.\nGSL error: "
        + error_str);
	}
    stat = gsl_matrix_complex_sub(res.gsl_mat, b.gsl_mat);
    if(stat){
		std::string error_str =   gsl_strerror(stat);
		throw std::runtime_error("Error in matrix subtraction.\nGSL error: "
        + error_str);
	}

    return res;
}
Complex_Matrix Complex_Matrix::operator* (const Complex_Matrix& b) const
{
    Complex_Matrix res(this->gsl_mat->size1, b.gsl_mat->size2);
    int stat = gsl_blas_zgemm(CblasNoTrans, CblasNoTrans, gsl_complex_rect(1.0, 0.0), this->gsl_mat,
        b.gsl_mat, gsl_complex_rect(0.0, 0.0), res.gsl_mat);
    if(stat){
		std::string error_str =   gsl_strerror(stat);
		throw std::runtime_error("Error in matrix multiplication.\nGSL error: "
        + error_str);
	}

    return res;
}
Complex_Matrix Complex_Matrix::operator/ (const Complex_Matrix& b) const
{
    Complex_Matrix res(this->gsl_mat->size1, this->gsl_mat->size2);
    int stat = gsl_matrix_complex_memcpy(res.gsl_mat,this->gsl_mat);
    if(stat){
		std::string error_str = gsl_strerror(stat);
		throw std::runtime_error("Error in memory copying.\nGSL error: "
        + error_str);
	}
    stat = gsl_matrix_complex_div_elements(res.gsl_mat, b.gsl_mat);
    if(stat){
		std::string error_str =   gsl_strerror(stat);
		throw std::runtime_error("Error in matrix element-wise division.\nGSL error: "
        + error_str);
	}

    return res;
}
Complex_Matrix Complex_Matrix::operator* (const double& s) const
{
    Complex_Matrix res(this->gsl_mat->size1, this->gsl_mat->size2);
    int stat = gsl_matrix_complex_memcpy(res.gsl_mat,this->gsl_mat);
    if(stat){
		std::string error_str = gsl_strerror(stat);
		throw std::runtime_error("Error in memory copying.\nGSL error: "
        + error_str);
	}
    stat = gsl_matrix_complex_scale(res.gsl_mat, gsl_complex_rect(s, 0.0));
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
    Complex_Vector res(this->gsl_mat->size1);
    int stat = gsl_blas_zgemv(CblasNoTrans, gsl_complex_rect(1.0, 0.0), this->gsl_mat,
        v.gsl_vec, gsl_complex_rect(0.0,0.0), res.gsl_vec);
    if(stat){
		std::string error_str =   gsl_strerror(stat);
		throw std::runtime_error("Error in matrix-vector multiplication.\nGSL error: "
        + error_str);
	}

    return res;
}

Complex_Vector GSL::operator* (const Complex_Vector& v, const Complex_Matrix& a)
{
    Complex_Vector res(a.gsl_mat->size2);
    int stat = gsl_blas_zgemv(CblasTrans, gsl_complex_rect(1.0, 0.0), a.gsl_mat,
        v.gsl_vec, gsl_complex_rect(0.0, 0.0), res.gsl_vec);
    if(stat){
		std::string error_str =   gsl_strerror(stat);
		throw std::runtime_error("Error in matrix-vector multiplication.\nGSL error: "
        + error_str);
	}

    return res;
}

Complex_Matrix Complex_Matrix::transpose() const
{
    Complex_Matrix res(this->gsl_mat->size2, this->gsl_mat->size1);

    gsl_matrix_complex_transpose_memcpy(res.gsl_mat, this->gsl_mat);

    return res;
}


bool GSL::operator== (const Complex_Matrix& u, const Complex_Matrix& v)
{
    return gsl_matrix_complex_equal(u.gsl_mat, v.gsl_mat);
}

bool GSL::operator!= (const Complex_Matrix& u, const Complex_Matrix& v)
{
    return !(u == v);
}

void Complex_Matrix::set_row(const size_t& index, const Complex_Vector& r)
{
    this->rows[index] = r;
}

std::ostream& operator<<(std::ostream& os, const Complex_Matrix& m)
{
    size_t size_1 = m.gsl_mat->size1;
    size_t size_2 = m.gsl_mat->size2;
    Complex tmp;

    os << "[";
    for(size_t i = 0; i < size_1; i++){
        if(i > 0){
            os << ", ";
        }
        os << "( ";
        for(size_t j = 0; j < size_2; j++){
            tmp = Complex(gsl_matrix_complex_get(m.gsl_mat, i, j));

            os << tmp;
            if(j < size_2 -1){
                os << ",";
            }
            os << " ";
        }
        os << ")";
    }
    os << "]";
    return os;
}
