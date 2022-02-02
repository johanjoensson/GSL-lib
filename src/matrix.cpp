#include "GSLpp/matrix.h"
#include "GSLpp/block.h"
#include <gsl/gsl_blas.h>

using namespace GSL;

/**********************************************************************************************
* MATRIX                                                                                                                                     *
**********************************************************************************************/

Matrix::Matrix(size_t n1, size_t n2)
 : gsl_mat_m(gsl_matrix_alloc(n1, n2), gsl_matrix_free)
{}

Matrix::Matrix(size_t n1, size_t n2, double val)
 : gsl_mat_m(gsl_matrix_alloc(n1, n2), gsl_matrix_free)
{
    gsl_matrix_set_all(this->gsl_mat_m.get(), val);
}

Matrix::Matrix(const std::initializer_list<Vector>& l)
 : Matrix(l.size(), l.begin()->size())
{
    size_t row = 0/*, column = 0*/;
    for(auto it = l.begin(); it != l.end(); it++, row++){
        this->row(row).copy(*it);
        // for(double v : it->cview()){
            // this->set(row, column, v);
            // column++;
        // }
        // column = 0;
    }
}

/*
Matrix::Matrix(const std::initializer_list<std::initializer_list<double>>& l)
 : Matrix(l.size(), l.begin()->size())
{
    size_t row = 0, column = 0;
    for(auto it = l.begin(); it != l.end(); it++){
        for(double v : *it){
            this->set(row, column, v);
            column++;
        }
        column = 0;
        row++;
    }
}
*/
Matrix::Matrix(gsl_matrix* v)
 : gsl_mat_m(v, [](gsl_matrix*){})
{}

gsl_matrix* Matrix::gsl_data()
{
    return this->gsl_mat_m.get();
}

const gsl_matrix* Matrix::gsl_data() const
{
    return this->gsl_mat_m.get();
}

bool GSL::operator==(const Matrix& a, const Matrix& b)
{
    return gsl_matrix_equal(a.gsl_mat_m.get(), b.gsl_mat_m.get());
}

bool GSL::operator!=(const Matrix& a, const Matrix& b)
{
    return !(a==b);
}

Matrix& Matrix::copy(const Matrix& other)
{
    gsl_matrix_memcpy(this->gsl_mat_m.get(), other.gsl_mat_m.get());
    return *this;
}

Matrix& Matrix::transpose_copy(const Matrix& other)
{
    gsl_matrix_transpose_memcpy(this->gsl_mat_m.get(), other.gsl_mat_m.get());
    return *this;
}

Matrix& Matrix::swap(const Matrix& other)
{
    gsl_matrix_swap(this->gsl_mat_m.get(), other.gsl_mat_m.get());
    return *this;
}

Matrix& Matrix::swap_rows(size_t i, size_t j)
{
    gsl_matrix_swap_rows(this->gsl_mat_m.get(), i, j);
    return *this;
}

Matrix& Matrix::swap_columns(size_t i, size_t j)
{
    gsl_matrix_swap_columns(this->gsl_mat_m.get(), i, j);
    return *this;
}

Matrix& Matrix::swap_rowcol(size_t i, size_t j)
{
    gsl_matrix_swap_rowcol(this->gsl_mat_m.get(), i, j);
    return *this;
}

Matrix& Matrix::transpose()
{
    gsl_matrix_transpose(this->gsl_mat_m.get());
    return *this;
}

Matrix& Matrix::T()
{
    this->transpose();
    return *this;
}

Matrix Matrix::clone() const
{
    Matrix res(this->gsl_mat_m->size1, this->gsl_mat_m->size2);
    res.copy(*this);
    return res;
}

size_t Matrix::num_rows() const
{
    return this->gsl_mat_m->size1;
}

size_t Matrix::num_columns() const
{
    return this->gsl_mat_m->size2;
}

std::pair<size_t, size_t> Matrix::dim() const
{
    return {this->num_rows(), this->num_columns()};
}

Matrix& Matrix::set_all(double val)
{
    gsl_matrix_set_all(this->gsl_mat_m.get(), val);
    return *this;
}

Matrix& Matrix::set_zero()
{
    gsl_matrix_set_zero(this->gsl_mat_m.get());
    return *this;
}

Matrix& Matrix::set(size_t i, size_t j, double val)
{
    gsl_matrix_set(this->gsl_mat_m.get(), i, j, val);
    return *this;
}

Matrix& Matrix::set_identity()
{
    gsl_matrix_set_identity(this->gsl_mat_m.get());
    return *this;
}

double Matrix::get(size_t i, size_t j) const
{
    return gsl_matrix_get(this->gsl_mat_m.get(), i, j);
}

double Matrix::max() const
{
    return gsl_matrix_max(this->gsl_mat_m.get());
}

double Matrix::min() const
{
    return gsl_matrix_min(gsl_mat_m.get());
}

std::pair<double, double> Matrix::minmax() const
{
    std::pair<double, double> res;
    gsl_matrix_minmax(this->gsl_mat_m.get(), &res.first, &res.second);
    return res;
}

std::pair<size_t, size_t> Matrix::max_index() const
{
    std::pair<size_t, size_t> res;
    gsl_matrix_max_index(this->gsl_mat_m.get(), &res.first, &res.second);
    return res;
}

std::pair<size_t, size_t> Matrix::min_index() const
{
    std::pair<size_t, size_t> res;
    gsl_matrix_min_index(this->gsl_mat_m.get(), &res.first, &res.second);
    return res;
}

std::pair<std::pair<size_t, size_t>, std::pair<size_t, size_t>> Matrix::minmax_index() const
{
    std::pair<std::pair<size_t, size_t>,  std::pair<size_t, size_t>> res;
    gsl_matrix_minmax_index(this->gsl_mat_m.get(), &res.first.first, &res.first.second, &res.second.first, &res.second.second);
    return res;
}

bool Matrix::isnull() const
{
    return gsl_matrix_isnull(this->gsl_mat_m.get());
}

bool Matrix::ispos() const
{
    return gsl_matrix_ispos(this->gsl_mat_m.get());
}

bool Matrix::isneg() const
{
    return gsl_matrix_isneg(this->gsl_mat_m.get());
}

bool Matrix::isnonneg() const
{
    return gsl_matrix_isnonneg(this->gsl_mat_m.get());
}

Matrix& Matrix::operator+=(const Matrix&  other)
{
    gsl_matrix_add(this->gsl_mat_m.get(), other.gsl_mat_m.get());
    return *this;
}

Matrix& Matrix::operator-=(const Matrix&  other)
{
    gsl_matrix_sub(this->gsl_mat_m.get(), other.gsl_mat_m.get());
    return *this;
}

Matrix& Matrix::operator*=(const Matrix&  other)
{
//    gsl_blas_dgemm(CblasNoTrans /* op(A) */, CblasNoTrans /* op(B) */, 1 /* alpha */,
//                                this->gsl_mat_m.view() /* A */, other.gsl_mat_m.get() /* B */,
//                                0 /* beta */, this->gsl_mat_m.view() /* C */);
    gsl_matrix_mul_elements(this->gsl_mat_m.get(), other.gsl_mat_m.get());
    return *this;
}

Matrix& Matrix::operator/=(const Matrix& other)
{
    gsl_matrix_div_elements(this->gsl_mat_m.get(), other.gsl_mat_m.get());
    return *this;
}

Matrix& Matrix::operator+=(double s)
{
    gsl_matrix_add_constant(this->gsl_mat_m.get(), s);
    return *this;
}

Matrix& Matrix::operator-=(double s)
{
    gsl_matrix_add_constant(this->gsl_mat_m.get(), -s);
    return *this;
}

Matrix& Matrix::operator*=(double s)
{
    gsl_matrix_scale(this->gsl_mat_m.get(), s);
    return *this;
}

Matrix& Matrix::operator/=(double s)
{
    gsl_matrix_scale(this->gsl_mat_m.get(), 1/s);
    return *this;
}

Matrix& Matrix::multiply(const Matrix&  other)
{
    gsl_blas_dgemm(CblasNoTrans /* op(A) */, CblasNoTrans /* op(B) */, 1 /* alpha */,
                                this->gsl_mat_m.get() /* A */, other.gsl_mat_m.get() /* B */,
                                0 /* beta */, this->gsl_mat_m.get() /* C */);
    return *this;
}

Matrix GSL::operator+(const Matrix& a, const Matrix& b)
{
    Matrix res(a.clone());
    res += b;
    return res;
}

Matrix GSL::operator-(const Matrix& a, const Matrix& b)
{
    Matrix res(a.clone());
    res -= b;
    return res;
}

Matrix GSL::operator*(const Matrix& a, const Matrix& b)
{
    Matrix res(a.clone());
    res *= b;
    return res;
}

Matrix GSL::operator/(const Matrix& a, const Matrix& b)
{
    Matrix res(a.clone());
    res /= b;
    return res;
}

Matrix GSL::operator+(const Matrix& a, double s)
{
    Matrix res(a.clone());
    res += s;
    return res;
}

Matrix GSL::operator+(double s, const Matrix& a)
{
    return a + s;
}

Matrix GSL::operator-(const Matrix& a, double s)
{
    Matrix res(a.clone());
    res -= s;
    return res;
}

Matrix GSL::operator-(double s, const Matrix& a)
{
    return -(a - s);
}

Matrix GSL::operator*(const Matrix& a, double s)
{
    Matrix res(a.clone());
    res *= s;
    return res;
}

Matrix GSL::operator*(double s, const Matrix& a)
{
    return a*s;
}

Matrix GSL::operator/(const Matrix& a, double s)
{
    Matrix res(a.clone());
    res /= s;
    return res;
}

Matrix GSL::operator-(const Matrix& a)
{
    Matrix res(a.num_rows(), a.num_columns(), 0);
    res -= a;
    return res;
}

Vector GSL::multiply(const Matrix& a, const Vector& v)
{
    Vector res(v.size());
    gsl_blas_dgemv(CblasNoTrans /* op(A) */,  1 /* alpha */,
                              a.gsl_data() /* A */, v.gsl_data() /* x */,
                              0 /* beta */, res.gsl_data() /* y */);
    return res;
}

Vector GSL::multiply(const Vector& v, const Matrix& a)
{
    Vector res(v.size());
    gsl_blas_dgemv(CblasTrans /* op(A) */,  1 /* alpha */,
                              a.gsl_data() /* A */, v.gsl_data() /* x */,
                              0 /* beta */, res.gsl_data() /* y */);
    return res;
}

Matrix GSL::outer(const Vector&a, Vector& b)
{
    Matrix res(a.size(), b.size(), 0);
    gsl_blas_dger(1.0, a.gsl_data(), b.gsl_data(), res.gsl_data());
    return res;
}

Matrix::View Matrix::view()
{
    return View(*this, 0, 0, this->num_rows(), this->num_columns());
}

const Matrix::View Matrix::view() const
{
    return View(*this, 0, 0, this->num_rows(), this->num_columns());
}

Matrix::Const_View Matrix::cview() const
{
    return Const_View(*this, 0, 0, this->num_rows(), this->num_columns());
}

Matrix::View Matrix::view(size_t k1, size_t k2, size_t n1, size_t n2)
{
    return View(*this, k1, k2, n1, n2);
}

const Matrix::View Matrix::view(size_t k1, size_t k2, size_t n1, size_t n2) const
{
    return View(*this, k1, k2, n1, n2);
}

Matrix::Const_View Matrix::cview(size_t k1, size_t k2, size_t n1, size_t n2) const
{
    return Const_View(*this, k1, k2, n1, n2);
}


Vector::View Matrix::row(size_t row)
{
    return gsl_matrix_row(this->gsl_mat_m.get(), row);
}

Vector::Const_View Matrix::row(size_t row) const
{
    return gsl_matrix_const_row(this->gsl_mat_m.get(), row);
}

Vector::Const_View Matrix::crow(size_t row) const
{
    return gsl_matrix_const_row(this->gsl_mat_m.get(), row);
}

Vector::View Matrix::column(size_t column)
{
    return gsl_matrix_column(this->gsl_mat_m.get(), column);
}

Vector::Const_View Matrix::column(size_t column) const
{
    return gsl_matrix_const_column(this->gsl_mat_m.get(), column);
}

Vector::Const_View Matrix::ccolumn(size_t column) const
{
    return gsl_matrix_const_column(this->gsl_mat_m.get(), column);
}

Vector::View Matrix::operator[](size_t row)
{
    return gsl_matrix_row(this->gsl_mat_m.get(), row);
}

Vector::Const_View Matrix::operator[](size_t row) const
{
    return gsl_matrix_const_row(this->gsl_mat_m.get(), row);
}

Vector::View Matrix::at(size_t row)
{
    if(!(row < this->gsl_mat_m->size1)){
        throw std::out_of_range("Row index " + std::to_string(row) + " out of range.");
    }
    return (*this)[row];
}

Vector::Const_View Matrix::at(size_t row) const
{
    if(!(row < this->gsl_mat_m->size1)){
        throw std::out_of_range("Row index " + std::to_string(row) + " out of range.");
    }
    return (*this)[row];
}

double& Matrix::operator()(size_t i, size_t j)
{
    return *gsl_matrix_ptr(this->gsl_mat_m.get(), i, j);
}

const double& Matrix::operator()(size_t i, size_t j) const
{
    return *gsl_matrix_const_ptr(this->gsl_mat_m.get(), i, j);
}

double& Matrix::at(size_t row, size_t column)
{
    if(!(row < this->gsl_mat_m->size1) || !(column < this->gsl_mat_m->size2)){
        throw std::out_of_range("(Row, Column) index (" + std::to_string(row) +
            ", " + std::to_string(column) + ") out of range.");
    }
    return (*this)(row, column);
}

const double& Matrix::at(size_t row, size_t column) const
{
    if(!(row < this->gsl_mat_m->size1) || !(column < this->gsl_mat_m->size2)){
        throw std::out_of_range("(Row, Column) index (" + std::to_string(row) +
            ", " + std::to_string(column) + ") out of range.");
    }
    return (*this)(row, column);
}

Vector::View Matrix::subrow(size_t i, size_t offset, size_t n)
{
    return gsl_matrix_subrow(this->gsl_mat_m.get(), i, offset, n);
}
Vector::Const_View Matrix::subrow(size_t i, size_t offset, size_t n) const
{
    return gsl_matrix_const_subrow(this->gsl_mat_m.get(), i, offset, n);
}
Vector::Const_View Matrix::csubrow(size_t i, size_t offset, size_t n) const
{
    return gsl_matrix_const_subrow(this->gsl_mat_m.get(), i, offset, n);
}

Vector::View Matrix::subcolumn(size_t i, size_t offset, size_t n)
{
    return gsl_matrix_subcolumn(this->gsl_mat_m.get(), i, offset, n);
}
Vector::Const_View Matrix::subcolumn(size_t i, size_t offset, size_t n) const
{
    return gsl_matrix_const_subcolumn(this->gsl_mat_m.get(), i, offset, n);
}
Vector::Const_View Matrix::csubcolumn(size_t i, size_t offset, size_t n) const
{
    return gsl_matrix_const_subcolumn(this->gsl_mat_m.get(), i, offset, n);
}

Vector::View Matrix::diagonal()
{
    return gsl_matrix_diagonal(this->gsl_mat_m.get());
}
Vector::Const_View Matrix::diagonal() const
{
    return gsl_matrix_const_diagonal(this->gsl_mat_m.get());
}
Vector::Const_View Matrix::cdiagonal() const
{
    return gsl_matrix_const_diagonal(this->gsl_mat_m.get());
}

Vector::View Matrix::subdiagonal(size_t k)
{
    return gsl_matrix_subdiagonal(this->gsl_mat_m.get(), k);
}
Vector::Const_View Matrix::subdiagonal(size_t k) const
{
    return gsl_matrix_const_subdiagonal(this->gsl_mat_m.get(), k);
}
Vector::Const_View Matrix::csubdiagonal(size_t k) const
{
    return gsl_matrix_const_subdiagonal(this->gsl_mat_m.get(), k);
}

Vector::View Matrix::superdiagonal(size_t k)
{
    return gsl_matrix_superdiagonal(this->gsl_mat_m.get(), k);
}
Vector::Const_View Matrix::superdiagonal(size_t k) const
{
    return gsl_matrix_const_superdiagonal(this->gsl_mat_m.get(), k);
}
Vector::Const_View Matrix::csuperdiagonal(size_t k) const
{
    return gsl_matrix_const_superdiagonal(this->gsl_mat_m.get(), k);
}

std::string Matrix::to_string() const
{
    std::string res = "";
    for(const auto& row : this->cview()){
        res += std::to_string(row) + "\n";
    }
    return res;
}

std::string std::to_string(const GSL::Matrix& m)
{
    return m.to_string();
}


std::ostream& GSL::operator<<(std::ostream& os, const Matrix& m)
{
    os << m.to_string();
    return os;
}

/**********************************************************************************************
**********************************************************************************************/


/**********************************************************************************************
* MATRIX VIEW                                                                                                                            *
**********************************************************************************************/

Matrix::View::View(const Matrix& m)
 : View(m, 0, 0, m.num_rows(), m.num_columns())
{}

Matrix::View::View(const Matrix& m, size_t k1, size_t k2, size_t n1, size_t n2)
 : gsl_mat_view_m(gsl_matrix_submatrix(m.gsl_mat_m.get(), k1, k2, n1, n2))
{}

Matrix::View::View(GSL::Block& b, size_t n1, size_t n2)
 : View(b, 0, n1, n2)
{}

Matrix::View::View(GSL::Block& b, size_t offset, size_t n1, size_t n2)
 : gsl_mat_view_m(gsl_matrix_view_array(b.data() + offset, n1, n2))
{}

Matrix::View::View(GSL::Block& b, size_t offset, size_t n1, size_t n2, size_t tda)
 : gsl_mat_view_m(gsl_matrix_view_array_with_tda(b.data() + offset, n1, n2, tda))
{}

Matrix::View::View(double* data, size_t n1, size_t n2)
 : View(data, 0, n1, n2)
{}

Matrix::View::View(double* data, size_t offset, size_t n1, size_t n2)
 : gsl_mat_view_m(gsl_matrix_view_array(data + offset, n1, n2))
{}

Matrix::View::View(double* data, size_t offset, size_t n1, size_t n2, size_t tda)
 : gsl_mat_view_m(gsl_matrix_view_array_with_tda(data + offset, n1, n2, tda))
{}

Matrix::View::View(Vector& v, size_t n1, size_t n2)
 : gsl_mat_view_m(gsl_matrix_view_vector(v.gsl_data(), n1, n2))
{}

Matrix::View::View(Vector& v, size_t n1, size_t n2, size_t tda)
 : gsl_mat_view_m(gsl_matrix_view_vector_with_tda(v.gsl_data(), n1, n2, tda))
{}

Matrix::View::operator Matrix()
{
    return Matrix(&this->gsl_mat_view_m.matrix);
}

Matrix::View::operator const Matrix() const
{
    return Matrix(const_cast<gsl_matrix*>(&this->gsl_mat_view_m.matrix));
}

gsl_matrix* Matrix::View::gsl_data()
{
    return &this->gsl_mat_view_m.matrix;
}

const gsl_matrix* Matrix::View::gsl_data() const
{
    return &this->gsl_mat_view_m.matrix;
}

Matrix Matrix::View::clone() const
{
    Matrix res(this->gsl_mat_view_m.matrix.size1, this->gsl_mat_view_m.matrix.size2);
    res.copy(*this);
    return res;
}


Matrix::View Matrix::View::view()
{
    return View(*this, 0, 0, this->num_rows(), this->num_columns());
}

Matrix::Const_View Matrix::View::view() const
{
    return Const_View(*this, 0, 0, this->num_rows(), this->num_columns());
}

Matrix::Const_View Matrix::View::cview() const
{
    return Const_View(*this, 0, 0, this->num_rows(), this->num_columns());
}

Matrix::View Matrix::View::view(size_t k1, size_t k2, size_t n1, size_t n2)
{
    return View(*this, k1, k2, n1, n2);
}

Matrix::Const_View Matrix::View::view(size_t k1, size_t k2, size_t n1, size_t n2) const
{
    return Const_View(*this, k1, k2, n1, n2);
}

Matrix::Const_View Matrix::View::cview(size_t k1, size_t k2, size_t n1, size_t n2) const
{
    return Const_View(*this, k1, k2, n1, n2);
}

size_t Matrix::View::num_rows() const
{
    return this->gsl_mat_view_m.matrix.size1;
}

size_t Matrix::View::num_columns() const
{
    return this->gsl_mat_view_m.matrix.size2;
}

std::pair<size_t, size_t> Matrix::View::dim() const
{
    return {this->gsl_mat_view_m.matrix.size1, this->gsl_mat_view_m.matrix.size2};
}

size_t Matrix::View::tda() const
{
    return this->gsl_mat_view_m.matrix.tda;
}

Matrix::View& Matrix::View::operator+=(const Matrix& other)
{
    gsl_matrix_add(&this->gsl_mat_view_m.matrix, other.gsl_mat_m.get());
    return *this;

}

Matrix::View& Matrix::View::operator-=(const Matrix& other)
{
    gsl_matrix_sub(&this->gsl_mat_view_m.matrix, other.gsl_mat_m.get());
    return *this;
}

Matrix::View& Matrix::View::operator*=(const Matrix& other)
{
    gsl_matrix_mul_elements(&this->gsl_mat_view_m.matrix, other.gsl_mat_m.get());
    return *this;
}

Matrix::View& Matrix::View::operator/=(const Matrix& other)
{
    gsl_matrix_div_elements(&this->gsl_mat_view_m.matrix, other.gsl_mat_m.get());
    return *this;
}

Matrix::View& Matrix::View::operator+=(double s)
{
    gsl_matrix_add_constant(&this->gsl_mat_view_m.matrix, s);
    return *this;
}

Matrix::View& Matrix::View::operator-=(double s)
{
    gsl_matrix_add_constant(&this->gsl_mat_view_m.matrix, -s);
    return *this;
}

Matrix::View& Matrix::View::operator*=(double s)
{
    gsl_matrix_scale(&this->gsl_mat_view_m.matrix, s);
    return *this;
}

Matrix::View& Matrix::View::operator/=(double s)
{
    gsl_matrix_scale(&this->gsl_mat_view_m.matrix, 1/s);
    return *this;
}

Matrix::View& Matrix::View::multiply(const Matrix& other)
{
    gsl_blas_dgemm(CblasNoTrans /* op(A) */, CblasNoTrans /* op(B) */, 1 /* alpha */,
                                &this->gsl_mat_view_m.matrix /* A */, other.gsl_mat_m.get() /* B */,
                                0 /* beta */, &this->gsl_mat_view_m.matrix /* C */);
    return *this;
}

Vector::View Matrix::View::row(size_t row)
{
    return gsl_matrix_row(&this->gsl_mat_view_m.matrix, row);
}

Vector::Const_View Matrix::View::row(size_t row) const
{
    return gsl_matrix_const_row(&this->gsl_mat_view_m.matrix, row);
}

Vector::Const_View Matrix::View::crow(size_t row) const
{
    return gsl_matrix_const_row(&this->gsl_mat_view_m.matrix, row);
}

Vector::View Matrix::View::column(size_t column)
{
    return gsl_matrix_column(&this->gsl_mat_view_m.matrix, column);
}

Vector::Const_View Matrix::View::column(size_t column) const
{
    return gsl_matrix_const_column(&this->gsl_mat_view_m.matrix, column);
}

Vector::Const_View Matrix::View::ccolumn(size_t column) const
{
    return gsl_matrix_const_column(&this->gsl_mat_view_m.matrix, column);
}


Vector::View Matrix::View::subrow(size_t i, size_t offset, size_t n)
{
    return gsl_matrix_subrow(&this->gsl_mat_view_m.matrix, i,  offset, n);
}

Vector::Const_View Matrix::View::subrow(size_t i, size_t offset, size_t n) const
{
    return gsl_matrix_const_subrow(&this->gsl_mat_view_m.matrix, i, offset, n);
}

Vector::Const_View Matrix::View::csubrow(size_t i, size_t offset, size_t n) const
{
    return gsl_matrix_const_subrow(&this->gsl_mat_view_m.matrix, i, offset, n);
}

Vector::View Matrix::View::subcolumn(size_t i, size_t offset, size_t n)
{
    return gsl_matrix_subcolumn(&this->gsl_mat_view_m.matrix, i, offset, n);
}

Vector::Const_View Matrix::View::subcolumn(size_t i, size_t offset, size_t n) const
{
    return gsl_matrix_const_subcolumn(&this->gsl_mat_view_m.matrix, i, offset, n);
}

Vector::Const_View Matrix::View::csubcolumn(size_t i, size_t offset, size_t n) const
{
    return gsl_matrix_const_subcolumn(&this->gsl_mat_view_m.matrix, i, offset, n);
}

Vector::View Matrix::View::diagonal()
{
    return gsl_matrix_diagonal(&this->gsl_mat_view_m.matrix);
}

Vector::Const_View Matrix::View::diagonal() const
{
    return gsl_matrix_const_diagonal(&this->gsl_mat_view_m.matrix);
}

Vector::Const_View Matrix::View::cdiagonal() const
{
    return gsl_matrix_const_diagonal(&this->gsl_mat_view_m.matrix);
}

Vector::View Matrix::View::subdiagonal(size_t k)
{
    return gsl_matrix_subdiagonal(&this->gsl_mat_view_m.matrix, k);
}

Vector::Const_View Matrix::View::subdiagonal(size_t k) const
{
    return gsl_matrix_const_subdiagonal(&this->gsl_mat_view_m.matrix, k);
}

Vector::Const_View Matrix::View::csubdiagonal(size_t k) const
{
    return gsl_matrix_const_subdiagonal(&this->gsl_mat_view_m.matrix, k);
}

Vector::View Matrix::View::superdiagonal(size_t k)
{
    return gsl_matrix_superdiagonal(&this->gsl_mat_view_m.matrix, k);
}

Vector::Const_View Matrix::View::superdiagonal(size_t k) const
{
    return gsl_matrix_const_superdiagonal(&this->gsl_mat_view_m.matrix, k);
}

Vector::Const_View Matrix::View::csuperdiagonal(size_t k) const
{
    return gsl_matrix_const_superdiagonal(&this->gsl_mat_view_m.matrix, k);
}

Vector::View Matrix::View::operator[](size_t row)
{
    return gsl_matrix_row(&this->gsl_mat_view_m.matrix, row);
}

Vector::Const_View Matrix::View::operator[](size_t row) const
{
    return gsl_matrix_const_row(&this->gsl_mat_view_m.matrix, row);
}

Vector::View Matrix::View::at(size_t row)
{
    if(!(row < this->gsl_mat_view_m.matrix.size1)){
        throw std::out_of_range("Row index " + std::to_string(row) + " out of range.");
    }
    return (*this)[row];
}

Vector::Const_View Matrix::View::at(size_t row) const
{
    if(!(row < this->gsl_mat_view_m.matrix.size1)){
        throw std::out_of_range("Row index " + std::to_string(row) + " out of range.");
    }
    return (*this)[row];
}

double& Matrix::View::operator()(size_t i, size_t j)
{
    return *gsl_matrix_ptr(&this->gsl_mat_view_m.matrix, i, j);
}

const double& Matrix::View::operator()(size_t i, size_t j) const
{
    return *gsl_matrix_const_ptr(&this->gsl_mat_view_m.matrix, i, j);
}

double& Matrix::View::at(size_t row, size_t column)
{
    if(!(row < this->gsl_mat_view_m.matrix.size1) || !(column < this->gsl_mat_view_m.matrix.size2)){
        throw std::out_of_range("(Row, Column) index (" + std::to_string(row) +
            ", " + std::to_string(column) + ") out of range.");
    }
    return (*this)(row, column);
}

const double& Matrix::View::at(size_t row, size_t column) const
{
    if(!(row < this->gsl_mat_view_m.matrix.size1) || !(column < this->gsl_mat_view_m.matrix.size2)){
        throw std::out_of_range("(Row, Column) index (" + std::to_string(row) +
            ", " + std::to_string(column) + ") out of range.");
    }
    return (*this)(row, column);
}

Matrix::View& Matrix::View::swap(Matrix::View& mv)
{
    gsl_matrix_swap(&this->gsl_mat_view_m.matrix, &mv.gsl_mat_view_m.matrix);
    return *this;
}

Matrix::View& Matrix::View::swap(Matrix::View&& mv)
{
    gsl_matrix_swap(&this->gsl_mat_view_m.matrix, &mv.gsl_mat_view_m.matrix);
    return *this;
}

Matrix::View& Matrix::View::swap(Matrix& m)
{
    gsl_matrix_swap(&this->gsl_mat_view_m.matrix, m.gsl_mat_m.get());
    return *this;
}

Matrix::View& Matrix::View::swap(Matrix&& m)
{
    gsl_matrix_swap(&this->gsl_mat_view_m.matrix, m.gsl_mat_m.get());
    return *this;
}

Matrix::View& Matrix::View::copy(const Matrix::View& mv)
{
    gsl_matrix_memcpy(&this->gsl_mat_view_m.matrix, &mv.gsl_mat_view_m.matrix);
    return *this;
}

Matrix::View& Matrix::View::copy(Matrix::View&& mv)
{
    gsl_matrix_swap(&this->gsl_mat_view_m.matrix, &mv.gsl_mat_view_m.matrix);
    return *this;
}

Matrix::View& Matrix::View::copy(const Matrix& m)
{
    gsl_matrix_memcpy(&this->gsl_mat_view_m.matrix, m.gsl_mat_m.get());
    return *this;
}

Matrix::View& Matrix::View::copy(Matrix&& m)
{
    gsl_matrix_swap(&this->gsl_mat_view_m.matrix, m.gsl_mat_m.get());
    return *this;
}

Matrix::View& Matrix::View::transpose_copy(const Matrix& other)
{
    gsl_matrix_transpose_memcpy(&this->gsl_mat_view_m.matrix, other.gsl_mat_m.get());
    return *this;
}

Matrix::View& Matrix::View::swap_rows(size_t i, size_t j)
{
    gsl_matrix_swap_rows(&this->gsl_mat_view_m.matrix, i, j);
    return *this;
}

Matrix::View& Matrix::View::swap_columns(size_t i, size_t j)
{
    gsl_matrix_swap_columns(&this->gsl_mat_view_m.matrix, i, j);
    return *this;
}

Matrix::View& Matrix::View::swap_rowcol(size_t i, size_t j)
{
    gsl_matrix_swap_rowcol(&this->gsl_mat_view_m.matrix, i, j);
    return *this;
}

Matrix::View& Matrix::View::transpose()
{
    gsl_matrix_transpose(&this->gsl_mat_view_m.matrix);
    return *this;
}

Matrix::View& Matrix::View::T()
{
    return this->transpose();
}

Matrix::View& Matrix::View::set_all(double val)
{
    gsl_matrix_set_all(&this->gsl_mat_view_m.matrix, val);
    return *this;
}

Matrix::View& Matrix::View::set_zero()
{
    gsl_matrix_set_zero(&this->gsl_mat_view_m.matrix);
    return *this;
}

Matrix::View& Matrix::View::set(size_t i, size_t j, double val)
{
    gsl_matrix_set(&this->gsl_mat_view_m.matrix, i, j, val);
    return *this;
}

Matrix::View& Matrix::View::set_identity()
{
    gsl_matrix_set_identity(&this->gsl_mat_view_m.matrix);
    return *this;
}

double Matrix::View::get(size_t i, size_t j) const
{
    return gsl_matrix_get(&this->gsl_mat_view_m.matrix, i, j);
}

double Matrix::View::max() const
{
    return gsl_matrix_max(&this->gsl_mat_view_m.matrix);
}

double Matrix::View::min() const
{
    return gsl_matrix_min(&this->gsl_mat_view_m.matrix);
}

std::pair<double, double> Matrix::View::minmax() const
{
    std::pair<double, double> res;
    gsl_matrix_minmax(&this->gsl_mat_view_m.matrix, &res.first, &res.second);
    return res;
}

std::pair<size_t, size_t> Matrix::View::max_index() const
{
    std::pair<size_t, size_t> res;
    gsl_matrix_max_index(&this->gsl_mat_view_m.matrix, &res.first, &res.second);
    return res;
}

std::pair<size_t, size_t> Matrix::View::min_index() const
{
    std::pair<size_t, size_t> res;
    gsl_matrix_min_index(&this->gsl_mat_view_m.matrix, &res.first, &res.second);
    return res;
}

std::pair<std::pair<size_t, size_t>, std::pair<size_t, size_t>> Matrix::View::minmax_index() const
{
    std::pair<std::pair<size_t, size_t>, std::pair<size_t, size_t>> res;
    gsl_matrix_minmax_index(&this->gsl_mat_view_m.matrix, &res.first.first, &res.first.second, &res.second.first, &res.second.second);
    return res;
}

bool Matrix::View::isnull() const
{
    return gsl_matrix_isnull(&this->gsl_mat_view_m.matrix);
}

bool Matrix::View::ispos() const
{
    return gsl_matrix_ispos(&this->gsl_mat_view_m.matrix);
}

bool Matrix::View::isneg() const
{
    return gsl_matrix_isneg(&this->gsl_mat_view_m.matrix);
}

bool Matrix::View::isnonneg() const
{
    return gsl_matrix_isnonneg(&this->gsl_mat_view_m.matrix);
}

Matrix::View& Matrix::View::operator=(const Matrix& m)
{
    return this->copy(m);
}

Matrix::View& Matrix::View::operator=(Matrix&& m)
{
    return this->swap(m);
}

Matrix::View::iterator Matrix::View::begin() noexcept
{
        return this->rows_begin();
}

Matrix::View::const_iterator Matrix::View::begin() const noexcept
{
        return this->rows_begin();
}

Matrix::View::const_iterator Matrix::View::cbegin() const noexcept
{
        return this->rows_cbegin();
}

Matrix::View::iterator Matrix::View::end() noexcept
{
        return this->rows_end();
}

Matrix::View::const_iterator Matrix::View::end() const noexcept
{
        return this->rows_end();
}

Matrix::View::const_iterator Matrix::View::cend() const noexcept
{
        return this->rows_cend();
}

Matrix::View::reverse_iterator Matrix::View::rbegin() noexcept
{
        return rows_rbegin();
}

Matrix::View::const_reverse_iterator Matrix::View::rbegin() const noexcept
{
        return rows_rbegin();
}

Matrix::View::const_reverse_iterator Matrix::View::crbegin() const noexcept
{
        return rows_crbegin();
}

Matrix::View::reverse_iterator Matrix::View::rend() noexcept
{
        return this->rows_rend();
}

Matrix::View::const_reverse_iterator Matrix::View::rend() const noexcept
{
        return this->rows_rend();
}

Matrix::View::const_reverse_iterator Matrix::View::crend() const noexcept
{
        return this->rows_crend();
}

Matrix::View::iterator Matrix::View::rows_begin() noexcept
{
    return Row_Iterator(this, 0);
}

Matrix::View::const_iterator Matrix::View::rows_begin() const noexcept
{
    return Const_Row_Iterator(this, 0);
}

Matrix::View::const_iterator Matrix::View::rows_cbegin() const noexcept
{
    return Const_Row_Iterator(this, 0);
}

Matrix::View::iterator Matrix::View::rows_end() noexcept
{
    return Row_Iterator(this, this->gsl_mat_view_m.matrix.size1);
}

Matrix::View::const_iterator Matrix::View::rows_end() const noexcept
{
    return Const_Row_Iterator(this, this->gsl_mat_view_m.matrix.size1);
}

Matrix::View::const_iterator Matrix::View::rows_cend() const noexcept
{
    return Const_Row_Iterator(this, this->gsl_mat_view_m.matrix.size1);
}

Matrix::View::reverse_iterator Matrix::View::rows_rbegin() noexcept
{
    return std::reverse_iterator<iterator>(this->end());
}

Matrix::View::const_reverse_iterator Matrix::View::rows_rbegin() const noexcept
{
    return std::reverse_iterator<const_iterator>(this->end());
}

Matrix::View::const_reverse_iterator Matrix::View::rows_crbegin() const noexcept
{
    return std::reverse_iterator<const_iterator>(this->cend());
}

Matrix::View::reverse_iterator Matrix::View::rows_rend() noexcept
{
    return std::reverse_iterator<iterator>(this->begin());
}

Matrix::View::const_reverse_iterator Matrix::View::rows_rend() const noexcept
{
    return std::reverse_iterator<const_iterator>(this->begin());
}

Matrix::View::const_reverse_iterator Matrix::View::rows_crend() const noexcept
{
    return std::reverse_iterator<const_iterator>(this->cbegin());
}

Matrix::View::value_type Matrix::View::rows_front()
{
    return *this->begin();
}

Matrix::View::const_value_type Matrix::View::rows_front() const
{
    return *this->begin();
}

Matrix::View::value_type Matrix::View::rows_back()
{
        return *(--this->end());
}

Matrix::View::const_value_type Matrix::View::rows_back() const
{
    return *(--this->end());
}


Matrix::View::Column_Iterator Matrix::View::columns_begin() noexcept
{
    return Column_Iterator(this, 0);
}

Matrix::View::Const_Column_Iterator Matrix::View::columns_begin() const noexcept
{
    return Const_Column_Iterator(this, 0);
}

Matrix::View::Const_Column_Iterator Matrix::View::columns_cbegin() const noexcept
{
    return Const_Column_Iterator(this, 0);
}

Matrix::View::Column_Iterator Matrix::View::columns_end() noexcept
{
    return Column_Iterator(this, this->gsl_mat_view_m.matrix.size2);
}

Matrix::View::Const_Column_Iterator Matrix::View::columns_end() const noexcept
{
    return Const_Column_Iterator(this, this->gsl_mat_view_m.matrix.size2);
}

Matrix::View::Const_Column_Iterator Matrix::View::columns_cend() const noexcept
{
    return Const_Column_Iterator(this, this->gsl_mat_view_m.matrix.size2);
}

std::reverse_iterator<Matrix::View::Column_Iterator> Matrix::View::columns_rbegin() noexcept
{
    return std::reverse_iterator<Column_Iterator>(this->columns_end());
}

std::reverse_iterator<Matrix::View::Const_Column_Iterator> Matrix::View::columns_rbegin() const noexcept
{
    return std::reverse_iterator<Const_Column_Iterator>(this->columns_end());
}

std::reverse_iterator<Matrix::View::Const_Column_Iterator> Matrix::View::columns_crbegin() const noexcept
{
    return std::reverse_iterator<Const_Column_Iterator>(this->columns_cend());
}

std::reverse_iterator<Matrix::View::Column_Iterator> Matrix::View::columns_rend() noexcept
{
    return std::reverse_iterator<Column_Iterator>(this->columns_begin());
}

std::reverse_iterator<Matrix::View::Const_Column_Iterator> Matrix::View::columns_rend() const noexcept
{
    return std::reverse_iterator<Const_Column_Iterator>(this->columns_begin());
}

std::reverse_iterator<Matrix::View::Const_Column_Iterator> Matrix::View::columns_crend() const noexcept
{
    return std::reverse_iterator<Const_Column_Iterator>(this->columns_cbegin());
}

Matrix::View::value_type Matrix::View::columns_front()
{
    return *this->columns_begin();
}

Matrix::View::const_value_type Matrix::View::columns_front() const
{
    return *this->columns_begin();
}

Matrix::View::value_type Matrix::View::columns_back()
{
        return *(--this->columns_end());
}

Matrix::View::const_value_type Matrix::View::columns_back() const
{
    return *(--this->columns_end());
}


Matrix::View::diagonal_iterator Matrix::View::diagonals_begin() noexcept
{
    return diagonal_iterator(this, 0);
}

Matrix::View::const_diagonal_iterator Matrix::View::diagonals_begin() const noexcept
{
    return const_diagonal_iterator(this, 0);
}

Matrix::View::const_diagonal_iterator Matrix::View::diagonals_cbegin() const noexcept
{
    return const_diagonal_iterator(this, 0);
}

Matrix::View::diagonal_iterator Matrix::View::diagonals_end() noexcept
{
    return diagonal_iterator(this, this->gsl_mat_view_m.matrix.size1 + this->gsl_mat_view_m.matrix.size2);
}

Matrix::View::const_diagonal_iterator Matrix::View::diagonals_end() const noexcept
{
    return const_diagonal_iterator(this, this->gsl_mat_view_m.matrix.size1 + this->gsl_mat_view_m.matrix.size2);
}

Matrix::View::const_diagonal_iterator Matrix::View::diagonals_cend() const noexcept
{
    return const_diagonal_iterator(this, this->gsl_mat_view_m.matrix.size1 + this->gsl_mat_view_m.matrix.size2);
}

std::reverse_iterator<Matrix::View::Diagonal_Iterator> Matrix::View::diagonals_rbegin() noexcept
{
    return std::reverse_iterator<Diagonal_Iterator>(this->diagonals_end());
}

Matrix::View::const_reverse_diagonal_iterator Matrix::View::diagonals_rbegin() const noexcept
{
    return const_reverse_diagonal_iterator(this->diagonals_end());
}

Matrix::View::const_reverse_diagonal_iterator Matrix::View::diagonals_crbegin() const noexcept
{
    return const_reverse_diagonal_iterator(this->diagonals_cend());
}

Matrix::View::reverse_diagonal_iterator Matrix::View::diagonals_rend() noexcept
{
    return reverse_diagonal_iterator(this->diagonals_begin());
}

Matrix::View::const_reverse_diagonal_iterator Matrix::View::diagonals_rend() const noexcept
{
    return const_reverse_diagonal_iterator(this->diagonals_begin());
}

Matrix::View::const_reverse_diagonal_iterator Matrix::View::diagonals_crend() const noexcept
{
    return const_reverse_diagonal_iterator(this->diagonals_cbegin());
}

Matrix::View::value_type Matrix::View::diagonals_front()
{
    return *this->diagonals_begin();
}

Matrix::View::const_value_type Matrix::View::diagonals_front() const
{
    return *this->diagonals_begin();
}

Matrix::View::value_type Matrix::View::diagonals_back()
{
        return *(--this->diagonals_end());
}

Matrix::View::const_value_type Matrix::View::diagonals_back() const
{
    return *(--this->diagonals_end());
}


/**********************************************************************************************
* MATRIX ITERATOR                                                                                                                    *
**********************************************************************************************/

Matrix::View::Iterator::Iterator()
 : m_m(), vector_view_m(nullptr, 0), index_m()
{}

Matrix::View::Iterator::Iterator(const Matrix::View* m, size_t i)
 : m_m(m->gsl_mat_view_m), vector_view_m(nullptr, 0), index_m(i)
{}

Matrix::View::Const_Iterator::Const_Iterator()
 : m_m(), vector_view_m(nullptr, 0), index_m()
{}

Matrix::View::Const_Iterator::Const_Iterator(const Matrix::View* m, size_t i)
 : m_m(m->gsl_mat_view_m), vector_view_m(nullptr, 0), index_m(i)
{}

Matrix::View::Row_Iterator::reference Matrix::View::Row_Iterator::operator*()
{
    std::cout << "Index = " << index_m << std::endl;
    std::cout << "matrix size = (" << this->m_m.matrix.size1 << ", " << this->m_m.matrix.size2 << ")" << std::endl;
    return gsl_matrix_row(&this->m_m.matrix, this->index_m);
}

Matrix::View::Row_Iterator::pointer Matrix::View::Row_Iterator::operator->()
{
    this->vector_view_m = **this;
    return &this->vector_view_m;
}

Matrix::View::Column_Iterator::reference Matrix::View::Column_Iterator::operator*()
{
    return gsl_matrix_column(&this->m_m.matrix, this->index_m);
}

Matrix::View::Column_Iterator::pointer Matrix::View::Column_Iterator::operator->()
{
    this->vector_view_m = **this;
    return &this->vector_view_m;
}

Matrix::View::Diagonal_Iterator::reference Matrix::View::Diagonal_Iterator::operator*()
{
    size_t max_dim = std::max(this->m_m.matrix.size1, this->m_m.matrix.size2) ;
    if(this->index_m < max_dim){
        return gsl_matrix_subdiagonal(&this->m_m.matrix, max_dim - this->index_m - 1);
    }else{
        return gsl_matrix_superdiagonal(&this->m_m.matrix, this->index_m % max_dim);
    }
}

Matrix::View::Diagonal_Iterator::pointer Matrix::View::Diagonal_Iterator::operator->()
{
    size_t max_dim = std::max(this->m_m.matrix.size1, this->m_m.matrix.size2) ;
    if(this->index_m < max_dim){
        this->vector_view_m = gsl_matrix_subdiagonal(&this->m_m.matrix, max_dim - this->index_m - 1);
    }else{
        this->vector_view_m = gsl_matrix_superdiagonal(&this->m_m.matrix, this->index_m % max_dim);
    }
    return &this->vector_view_m;
}

bool Matrix::View::Iterator::operator==(const Iterator& other)
{
    return this->index_m == other.index_m;
}

bool Matrix::View::Iterator::operator!=(const Iterator& other)
{
    return !(*this == other);
}

bool Matrix::View::Iterator::operator<=(const Iterator& other)
{
    return this->index_m <= other.index_m;
}

bool Matrix::View::Iterator::operator>=(const Iterator& other)
{
    return this->index_m >= other.index_m;
}

bool Matrix::View::Iterator::operator<(const Iterator& other)
{
    return !(*this >= other);
}

bool Matrix::View::Iterator::operator>(const Iterator& other)
{
    return !(*this <= other);
}

/**********************************************************************************************
**********************************************************************************************/


/**********************************************************************************************
* MATRIX VIEW CONST ITERATOR                                                                                               *
**********************************************************************************************/

Matrix::View::Const_Row_Iterator::const_reference Matrix::View::Const_Row_Iterator::operator*()
{
    return gsl_matrix_const_row(&this->m_m.matrix, this->index_m);
}

Matrix::View::Const_Row_Iterator::pointer
  Matrix::View::Const_Row_Iterator::operator->()
{
    this->vector_view_m = gsl_matrix_row(&this->m_m.matrix, this->index_m);
    return reinterpret_cast<Vector::Const_View*>(&vector_view_m);
}

Matrix::View::Const_Column_Iterator::const_reference Matrix::View::Const_Column_Iterator::operator*()
{
    return gsl_matrix_const_column(&this->m_m.matrix, this->index_m);
}

Matrix::View::Const_Column_Iterator::pointer
  Matrix::View::Const_Column_Iterator::operator->()
{
    this->vector_view_m = gsl_matrix_column(&this->m_m.matrix, this->index_m);
    return reinterpret_cast<Vector::Const_View*>(&vector_view_m);
}

Matrix::View::Const_Diagonal_Iterator::const_reference Matrix::View::Const_Diagonal_Iterator::operator*()
{
    size_t max_dim =
        std::max(this->m_m.matrix.size1, this->m_m.matrix.size2) ;
    if(this->index_m < max_dim){
        return gsl_matrix_const_subdiagonal(
                &this->m_m.matrix
                , max_dim - this->index_m - 1);
    }else{
        return
            gsl_matrix_const_superdiagonal(
                &this->m_m.matrix
                , this->index_m % max_dim);
    }
}

Matrix::View::Const_Diagonal_Iterator::pointer
  Matrix::View::Const_Diagonal_Iterator::operator->()
{
    size_t max_dim =
        std::max(this->m_m.matrix.size1, this->m_m.matrix.size2) ;
    if(this->index_m < max_dim){
        this->vector_view_m =
            gsl_matrix_subdiagonal(
                &this->m_m.matrix
                , max_dim - this->index_m - 1);
    }else{
        this->vector_view_m =
            gsl_matrix_superdiagonal(
                &this->m_m.matrix
                , this->index_m % max_dim);
    }
    return reinterpret_cast<Vector::Const_View*>(&vector_view_m);
}

bool Matrix::View::Const_Iterator::operator==(const Const_Iterator& other)
{
    return this->index_m == other.index_m;
}

bool Matrix::View::Const_Iterator::operator!=(const Const_Iterator& other)
{
    return !(*this == other);
}

bool Matrix::View::Const_Iterator::operator<=(const Const_Iterator& other)
{
    return this->index_m <= other.index_m;
}

bool Matrix::View::Const_Iterator::operator>=(const Const_Iterator& other)
{
    return this->index_m >= other.index_m;
}

bool Matrix::View::Const_Iterator::operator<(const Const_Iterator& other)
{
    return !(*this >= other);
}

bool Matrix::View::Const_Iterator::operator>(const Const_Iterator& other)
{
    return !(*this <= other);
}

/**********************************************************************************************
**********************************************************************************************/


/**********************************************************************************************
* MATRIX VIEW ROW ITERATOR                                                                                                   *
**********************************************************************************************/

Matrix::View::Row_Iterator::Row_Iterator()
 : Matrix::View::Iterator()
{}

Matrix::View::Row_Iterator::Row_Iterator(const Matrix::View* m, size_t i)
 : Matrix::View::Iterator(m, i)
{}

/**********************************************************************************************
**********************************************************************************************/

/**********************************************************************************************
* MATRIX VIEW CONST_ROW ITERATOR                                                                                      *
**********************************************************************************************/

Matrix::View::Const_Row_Iterator::Const_Row_Iterator()
 : Matrix::View::Const_Iterator()
{}

Matrix::View::Const_Row_Iterator::Const_Row_Iterator(const Matrix::View* m, size_t i)
 : Matrix::View::Const_Iterator(m, i)
{}


/**********************************************************************************************
**********************************************************************************************/

/**********************************************************************************************
* MATRIX VIEW COLUMN ITERATOR                                                                                             *
**********************************************************************************************/

Matrix::View::Column_Iterator::Column_Iterator()
 : Matrix::View::Iterator()
{}

Matrix::View::Column_Iterator::Column_Iterator(const Matrix::View* m, size_t i)
 : Matrix::View::Iterator(m, i)
{}

/**********************************************************************************************
**********************************************************************************************/

/**********************************************************************************************
* MATRIX VIEW CONST_COLUMN ITERATOR                                                                                *
**********************************************************************************************/

Matrix::View::Const_Column_Iterator::Const_Column_Iterator()
 : Matrix::View::Const_Iterator()
{}

Matrix::View::Const_Column_Iterator::Const_Column_Iterator(const Matrix::View* m, size_t i)
 : Matrix::View::Const_Iterator(m, i)
{}

/**********************************************************************************************
**********************************************************************************************/


/**********************************************************************************************
* MATRIX VIEW DIAGONAL ITERATOR                                                                                          *
**********************************************************************************************/

Matrix::View::Diagonal_Iterator::Diagonal_Iterator()
 : Matrix::View::Iterator()
{}

Matrix::View::Diagonal_Iterator::Diagonal_Iterator(const Matrix::View* m, size_t i)
 : Matrix::View::Iterator(m, i)
{}

/**********************************************************************************************
**********************************************************************************************/


/**********************************************************************************************
* MATRIX VIEW CONST DIAGONAL ITERATOR                                                                              *
**********************************************************************************************/

Matrix::View::Const_Diagonal_Iterator::Const_Diagonal_Iterator()
 : Matrix::View::Const_Iterator()
{}

Matrix::View::Const_Diagonal_Iterator::Const_Diagonal_Iterator(const Matrix::View* m, size_t i)
 : Matrix::View::Const_Iterator(m, i)
{}

/**********************************************************************************************
**********************************************************************************************/


/**********************************************************************************************
* MATRIX CONST VIEW                                                                                                                *
**********************************************************************************************/

Matrix::Const_View::Const_View(const Matrix& m, size_t k1, size_t k2, size_t n1, size_t n2)
 : gsl_mat_view_m(gsl_matrix_const_submatrix(m.gsl_mat_m.get(), k1, k2, n1, n2))
{}

Matrix::Const_View::Const_View(const GSL::Block& b, size_t n1, size_t n2)
 : Const_View(b, 0, n1, n2)
{}

Matrix::Const_View::Const_View(const GSL::Block& b, size_t offset, size_t n1, size_t n2)
 : gsl_mat_view_m(gsl_matrix_const_view_array(b.data() + offset, n1, n2))
{}

Matrix::Const_View::Const_View(const GSL::Block& b, size_t offset, size_t n1, size_t n2, size_t tda)
 : gsl_mat_view_m(gsl_matrix_const_view_array_with_tda(b.data() + offset, n1, n2, tda))
{}

Matrix::Const_View::Const_View(const double* data, size_t n1, size_t n2)
 : Const_View(data, 0, n1, n2)
{}

Matrix::Const_View::Const_View(const double* data, size_t offset, size_t n1, size_t n2)
 : gsl_mat_view_m(gsl_matrix_const_view_array(data + offset, n1, n2))
{}

Matrix::Const_View::Const_View(const double* data, size_t offset, size_t n1, size_t n2, size_t tda)
 : gsl_mat_view_m(gsl_matrix_const_view_array_with_tda(data + offset, n1, n2, tda))
{}

Matrix::Const_View::Const_View(const Vector& v, size_t n1, size_t n2)
 : gsl_mat_view_m(gsl_matrix_const_view_vector(v.gsl_data(), n1, n2))
{}

Matrix::Const_View::Const_View(const Vector& v, size_t n1, size_t n2, size_t tda)
 : gsl_mat_view_m(gsl_matrix_const_view_vector_with_tda(v.gsl_data(), n1, n2, tda))
{}

size_t Matrix::Const_View::num_rows() const
{
    return this->gsl_mat_view_m.matrix.size1;
}

size_t Matrix::Const_View::num_columns() const
{
    return this->gsl_mat_view_m.matrix.size2;
}

std::pair<size_t, size_t> Matrix::Const_View::dim() const
{
    return {this->gsl_mat_view_m.matrix.size1, this->gsl_mat_view_m.matrix.size2};
}

size_t Matrix::Const_View::tda() const
{
    return this->gsl_mat_view_m.matrix.tda;
}

double Matrix::Const_View::get(size_t i, size_t j)
{
    return gsl_matrix_get(&this->gsl_mat_view_m.matrix, i, j);
}

double Matrix::Const_View::max() const
{
    return gsl_matrix_max(&this->gsl_mat_view_m.matrix);
}

double Matrix::Const_View::min() const
{
    return gsl_matrix_min(&this->gsl_mat_view_m.matrix);
}

std::pair<double, double> Matrix::Const_View::minmax() const
{
    std::pair<double, double> res;
    gsl_matrix_minmax(&this->gsl_mat_view_m.matrix, &res.first, &res.second);
    return res;
}

std::pair<size_t, size_t> Matrix::Const_View::max_index() const
{
    std::pair<size_t, size_t> res;
    gsl_matrix_max_index(&this->gsl_mat_view_m.matrix, &res.first, &res.second);
    return res;
}

std::pair<size_t, size_t> Matrix::Const_View::min_index() const
{
    std::pair<size_t, size_t> res;
    gsl_matrix_min_index(&this->gsl_mat_view_m.matrix, &res.first, &res.second);
    return res;
}

std::pair<std::pair<size_t, size_t>, std::pair<size_t, size_t>> Matrix::Const_View::minmax_index() const
{
    std::pair<std::pair<size_t, size_t>, std::pair<size_t, size_t>> res;
    gsl_matrix_minmax_index(&this->gsl_mat_view_m.matrix, &res.first.first, &res.first.second, &res.second.first, &res.second.second);
    return res;
}

bool Matrix::Const_View::isnull() const
{
    return gsl_matrix_isnull(&this->gsl_mat_view_m.matrix);
}

bool Matrix::Const_View::ispos() const
{
    return gsl_matrix_ispos(&this->gsl_mat_view_m.matrix);
}

bool Matrix::Const_View::isneg() const
{
    return gsl_matrix_isneg(&this->gsl_mat_view_m.matrix);
}

bool Matrix::Const_View::isnonneg() const
{
    return gsl_matrix_isnonneg(&this->gsl_mat_view_m.matrix);
}

Matrix::Const_View Matrix::Const_View::view() const
{
    return Const_View(*this, 0, 0, this->num_rows(), this->num_columns());
}

Matrix::Const_View Matrix::Const_View::cview() const
{
    return Const_View(*this, 0, 0, this->num_rows(), this->num_columns());
}

Matrix::Const_View Matrix::Const_View::view(size_t k1, size_t k2, size_t n1, size_t n2) const
{
    return Const_View(*this, k1, k2, n1, n2);
}

Matrix::Const_View Matrix::Const_View::cview(size_t k1, size_t k2, size_t n1, size_t n2) const
{
    return Const_View(*this, k1, k2, n1, n2);
}

Vector::Const_View Matrix::Const_View::row(size_t row) const
{
    return gsl_matrix_const_row(&this->gsl_mat_view_m.matrix, row);
}

Vector::Const_View Matrix::Const_View::crow(size_t row) const
{
    return gsl_matrix_const_row(&this->gsl_mat_view_m.matrix, row);
}


Vector::Const_View Matrix::Const_View::column(size_t column) const
{
    return gsl_matrix_const_column(&this->gsl_mat_view_m.matrix, column);
}

Vector::Const_View Matrix::Const_View::ccolumn(size_t column) const
{
    return gsl_matrix_const_column(&this->gsl_mat_view_m.matrix, column);
}


Vector::Const_View Matrix::Const_View::subrow(size_t i, size_t offset, size_t n) const
{
    return gsl_matrix_const_subrow(&this->gsl_mat_view_m.matrix, i, offset, n);
}

Vector::Const_View Matrix::Const_View::csubrow(size_t i, size_t offset, size_t n) const
{
    return gsl_matrix_const_subrow(&this->gsl_mat_view_m.matrix, i, offset, n);
}

Vector::Const_View Matrix::Const_View::subcolumn(size_t i, size_t offset, size_t n) const
{
    return gsl_matrix_const_subcolumn(&this->gsl_mat_view_m.matrix, i, offset, n);
}

Vector::Const_View Matrix::Const_View::csubcolumn(size_t i, size_t offset, size_t n) const
{
    return gsl_matrix_const_subcolumn(&this->gsl_mat_view_m.matrix, i, offset, n);
}

Vector::Const_View Matrix::Const_View::diagonal() const
{
    return gsl_matrix_const_diagonal(&this->gsl_mat_view_m.matrix);
}

Vector::Const_View Matrix::Const_View::cdiagonal() const
{
    return gsl_matrix_const_diagonal(&this->gsl_mat_view_m.matrix);
}

Vector::Const_View Matrix::Const_View::subdiagonal(size_t k) const
{
    return gsl_matrix_const_subdiagonal(&this->gsl_mat_view_m.matrix, k);
}

Vector::Const_View Matrix::Const_View::csubdiagonal(size_t k) const
{
    return gsl_matrix_const_subdiagonal(&this->gsl_mat_view_m.matrix, k);
}

Vector::Const_View Matrix::Const_View::superdiagonal(size_t k) const
{
    return gsl_matrix_const_superdiagonal(&this->gsl_mat_view_m.matrix, k);
}

Vector::Const_View Matrix::Const_View::csuperdiagonal(size_t k) const
{
    return gsl_matrix_const_superdiagonal(&this->gsl_mat_view_m.matrix, k);
}

Vector::Const_View Matrix::Const_View::operator[](size_t row) const
{
    return gsl_matrix_const_row(&this->gsl_mat_view_m.matrix, row);
}

Vector::Const_View Matrix::Const_View::at(size_t row) const
{
    if(!(row < this->gsl_mat_view_m.matrix.size1)){
        throw std::out_of_range("(Row, Column) index (" + std::to_string(row) +
            ", " + std::to_string(row) + ") out of range.");
    }
    return gsl_matrix_const_row(&this->gsl_mat_view_m.matrix, row);
}

const double& Matrix::Const_View::operator()(size_t i, size_t j) const
{
    return *gsl_matrix_const_ptr(&this->gsl_mat_view_m.matrix, i, j);
}

const double& Matrix::Const_View::at(size_t row, size_t column) const
{
    if(!(row < this->gsl_mat_view_m.matrix.size1) || !(column < this->gsl_mat_view_m.matrix.size2)){
        throw std::out_of_range("(Row, Column) index (" + std::to_string(row) +
            ", " + std::to_string(column) + ") out of range.");
    }
    return (*this)(row, column);
}

Matrix::Const_View::operator const Matrix() const
{
    return Matrix(const_cast<gsl_matrix*>(&this->gsl_mat_view_m.matrix));
}

const gsl_matrix* Matrix::Const_View::gsl_data() const
{
    return &this->gsl_mat_view_m.matrix;
}

Matrix Matrix::Const_View::clone() const
{
    Matrix res(this->gsl_mat_view_m.matrix.size1, this->gsl_mat_view_m.matrix.size2);
    res.copy(*this);
    return res;
}



Matrix::Const_View::const_row_iterator Matrix::Const_View::rows_begin() const noexcept
{
    return const_row_iterator(this, 0);
}

Matrix::Const_View::const_row_iterator Matrix::Const_View::rows_cbegin() const noexcept
{
    return const_row_iterator(this, 0);
}

Matrix::Const_View::const_row_iterator Matrix::Const_View::rows_end() const noexcept
{
    return const_row_iterator(this, this->gsl_mat_view_m.matrix.size1);
}

Matrix::Const_View::const_row_iterator Matrix::Const_View::rows_cend() const noexcept
{
    return const_row_iterator(this, this->gsl_mat_view_m.matrix.size1);
}

Matrix::Const_View::const_reverse_row_iterator Matrix::Const_View::rows_rbegin() const noexcept
{
    return const_reverse_row_iterator(this->rows_end());
}

Matrix::Const_View::const_reverse_row_iterator Matrix::Const_View::rows_crbegin() const noexcept
{
    return const_reverse_row_iterator(this->rows_cend());
}

Matrix::Const_View::const_reverse_row_iterator Matrix::Const_View::rows_rend() const noexcept
{
    return const_reverse_row_iterator(this->rows_begin());
}

Matrix::Const_View::const_reverse_row_iterator Matrix::Const_View::rows_crend() const noexcept
{
    return const_reverse_row_iterator(this->rows_cbegin());
}

Matrix::Const_View::const_value_type Matrix::Const_View::rows_front() const
{
    return *this->rows_begin();
}

Matrix::Const_View::const_value_type Matrix::Const_View::rows_back() const
{
    return *(--this->rows_end());
}


Matrix::Const_View::const_column_iterator Matrix::Const_View::columns_begin() const noexcept
{
    return const_column_iterator(this, 0);
}

Matrix::Const_View::const_column_iterator Matrix::Const_View::columns_cbegin() const noexcept
{
    return const_column_iterator(this, 0);
}

Matrix::Const_View::const_column_iterator Matrix::Const_View::columns_end() const noexcept
{
    return const_column_iterator(this, this->gsl_mat_view_m.matrix.size2);
}

Matrix::Const_View::const_column_iterator Matrix::Const_View::columns_cend() const noexcept
{
    return const_column_iterator(this, this->gsl_mat_view_m.matrix.size2);
}

Matrix::Const_View::const_reverse_column_iterator Matrix::Const_View::columns_rbegin() const noexcept
{
    return const_reverse_column_iterator(this->columns_end());
}

Matrix::Const_View::const_reverse_column_iterator Matrix::Const_View::columns_crbegin() const noexcept
{
    return const_reverse_column_iterator(this->columns_cend());
}

Matrix::Const_View::const_reverse_column_iterator Matrix::Const_View::columns_rend() const noexcept
{
    return const_reverse_column_iterator(this->columns_begin());
}

Matrix::Const_View::const_reverse_column_iterator Matrix::Const_View::columns_crend() const noexcept
{
    return const_reverse_column_iterator(this->columns_cbegin());
}

Matrix::Const_View::const_value_type Matrix::Const_View::columns_front() const
{
    return *this->columns_begin();
}

Matrix::Const_View::const_value_type Matrix::Const_View::columns_back() const
{
    return *(--this->columns_end());
}

Matrix::Const_View::const_diagonal_iterator Matrix::Const_View::diagonals_begin() const noexcept
{
    return const_diagonal_iterator(this, 0);
}

Matrix::Const_View::const_diagonal_iterator Matrix::Const_View::diagonals_cbegin() const noexcept
{
    return const_diagonal_iterator(this, 0);
}

Matrix::Const_View::const_diagonal_iterator Matrix::Const_View::diagonals_end() const noexcept
{
    return const_diagonal_iterator(this, this->gsl_mat_view_m.matrix.size1 + this->gsl_mat_view_m.matrix.size2);
}

Matrix::Const_View::const_diagonal_iterator Matrix::Const_View::diagonals_cend() const noexcept
{
    return const_diagonal_iterator(this, this->gsl_mat_view_m.matrix.size1 + this->gsl_mat_view_m.matrix.size2);
}

Matrix::Const_View::const_reverse_diagonal_iterator Matrix::Const_View::diagonals_rbegin() const noexcept
{
    return const_reverse_diagonal_iterator(this->diagonals_end());
}

Matrix::Const_View::const_reverse_diagonal_iterator Matrix::Const_View::diagonals_crbegin() const noexcept
{
    return const_reverse_diagonal_iterator(this->diagonals_cend());
}

Matrix::Const_View::const_reverse_diagonal_iterator Matrix::Const_View::diagonals_rend() const noexcept
{
    return const_reverse_diagonal_iterator(this->diagonals_begin());
}

Matrix::Const_View::const_reverse_diagonal_iterator Matrix::Const_View::diagonals_crend() const noexcept
{
    return const_reverse_diagonal_iterator(this->diagonals_cbegin());
}

Matrix::Const_View::const_value_type Matrix::Const_View::diagonals_front() const
{
    return *this->diagonals_begin();
}

Matrix::Const_View::const_value_type Matrix::Const_View::diagonals_back() const
{
    return *(--this->diagonals_end());
}

/**********************************************************************************************
**********************************************************************************************/


/**********************************************************************************************
* MATRIX CONST VIEW CONST ITERATOR                                                                                    *
**********************************************************************************************/

Matrix::Const_View::Const_Iterator::Const_Iterator()
 : m_m(), vector_view_m(nullptr, 0), index_m()
{}

Matrix::Const_View::Const_Iterator::Const_Iterator(const Matrix::Const_View* m, size_t i)
 : m_m(m->gsl_mat_view_m), vector_view_m(nullptr, 0), index_m(i)
{}

Matrix::Const_View::Const_Row_Iterator::const_reference Matrix::Const_View::Const_Row_Iterator::operator*()
{
    return gsl_matrix_const_row(&this->m_m.matrix, this->index_m);
}

Matrix::Const_View::Const_Row_Iterator::pointer
  Matrix::Const_View::Const_Row_Iterator::operator->()
{
    this->vector_view_m = gsl_matrix_row(const_cast<gsl_matrix*>(&this->m_m.matrix), this->index_m);
    return reinterpret_cast<Vector::Const_View*>(&vector_view_m);
}

Matrix::Const_View::Const_Column_Iterator::const_reference Matrix::Const_View::Const_Column_Iterator::operator*()
{
    return gsl_matrix_const_column(const_cast<gsl_matrix*>(&this->m_m.matrix), this->index_m);
}

Matrix::Const_View::Const_Column_Iterator::pointer
  Matrix::Const_View::Const_Column_Iterator::operator->()
{
    this->vector_view_m = gsl_matrix_column(const_cast<gsl_matrix*>(&this->m_m.matrix), this->index_m);
    return reinterpret_cast<Vector::Const_View*>(&vector_view_m);
}

Matrix::Const_View::Const_Diagonal_Iterator::const_reference Matrix::Const_View::Const_Diagonal_Iterator::operator*()
{
    size_t max_dim =
        std::max(this->m_m.matrix.size1, this->m_m.matrix.size2) ;
    if(this->index_m < max_dim){
        return
            gsl_matrix_const_subdiagonal(
                &this->m_m.matrix
                , max_dim - this->index_m - 1);
    }else{
        return
            gsl_matrix_const_superdiagonal(
                &this->m_m.matrix
                , this->index_m % max_dim);
    }
}

Matrix::Const_View::Const_Diagonal_Iterator::pointer
  Matrix::Const_View::Const_Diagonal_Iterator::operator->()
{
    size_t max_dim =
        std::max(this->m_m.matrix.size1, this->m_m.matrix.size2) ;
    if(this->index_m < max_dim){
        this->vector_view_m =
            gsl_matrix_subdiagonal(
                const_cast<gsl_matrix*>(&this->m_m.matrix)
                , max_dim - this->index_m - 1);
    }else{
        this->vector_view_m =
            gsl_matrix_superdiagonal(
                const_cast<gsl_matrix*>(&this->m_m.matrix)
                , this->index_m % max_dim);
    }
    return reinterpret_cast<Vector::Const_View*>(&vector_view_m);
}

bool Matrix::Const_View::Const_Iterator::operator==(const Const_Iterator& other)
{
    return this->index_m == other.index_m;
}

bool Matrix::Const_View::Const_Iterator::operator!=(const Const_Iterator& other)
{
    return !(*this == other);
}

bool Matrix::Const_View::Const_Iterator::operator<=(const Const_Iterator& other)
{
    return this->index_m <= other.index_m;
}

bool Matrix::Const_View::Const_Iterator::operator>=(const Const_Iterator& other)
{
    return this->index_m >= other.index_m;
}

bool Matrix::Const_View::Const_Iterator::operator<(const Const_Iterator& other)
{
    return !(*this >= other);
}

bool Matrix::Const_View::Const_Iterator::operator>(const Const_Iterator& other)
{
    return !(*this <= other);
}

/**********************************************************************************************
**********************************************************************************************/


/**********************************************************************************************
* MATRIX CONST VIEW  CONST ROW ITERATOR                                                                          *
**********************************************************************************************/

Matrix::Const_View::Const_Row_Iterator::Const_Row_Iterator()
 : Matrix::Const_View::Const_Iterator()
{}

Matrix::Const_View::Const_Row_Iterator::Const_Row_Iterator(const Matrix::Const_View* m, size_t i)
 : Matrix::Const_View::Const_Iterator(m, i)
{}

/**********************************************************************************************
**********************************************************************************************/


/**********************************************************************************************
* MATRIX CONST VIEW  CONST COLUMN ITERATOR                                                                    *
**********************************************************************************************/

Matrix::Const_View::Const_Column_Iterator::Const_Column_Iterator()
 : Matrix::Const_View::Const_Iterator()
{}

Matrix::Const_View::Const_Column_Iterator::Const_Column_Iterator(const Matrix::Const_View* m, size_t i)
 : Matrix::Const_View::Const_Iterator(m, i)
{}

/**********************************************************************************************
**********************************************************************************************/


/**********************************************************************************************
* MATRIX CONST VIEW  CONST DIAGONAL ITERATOR                                                                 *
**********************************************************************************************/

Matrix::Const_View::Const_Diagonal_Iterator::Const_Diagonal_Iterator()
 : Matrix::Const_View::Const_Iterator()
{}

Matrix::Const_View::Const_Diagonal_Iterator::Const_Diagonal_Iterator(const Matrix::Const_View* m, size_t i)
 : Matrix::Const_View::Const_Iterator(m, i)
{}

Matrix::Const_View::const_iterator Matrix::Const_View::begin() const noexcept
{
        return this->rows_begin();
}

Matrix::Const_View::const_iterator Matrix::Const_View::cbegin() const noexcept
{
        return this->rows_cbegin();
}

Matrix::Const_View::const_iterator Matrix::Const_View::end() const noexcept
{
        return this->rows_end();
}

Matrix::Const_View::const_iterator Matrix::Const_View::cend() const noexcept
{
        return this->rows_cend();
}

Matrix::Const_View::const_reverse_iterator Matrix::Const_View::rbegin() const noexcept
{
        return rows_rbegin();
}

Matrix::Const_View::const_reverse_iterator Matrix::Const_View::crbegin() const noexcept
{
        return rows_crbegin();
}

Matrix::Const_View::const_reverse_iterator Matrix::Const_View::rend() const noexcept
{
        return this->rows_rend();
}

Matrix::Const_View::const_reverse_iterator Matrix::Const_View::crend() const noexcept
{
        return this->rows_crend();
}
/**********************************************************************************************
**********************************************************************************************/

#if 0
 int main()
{
    Block b(16);

    Matrix m(2, 2, 0);
    m(0, 0) = 0;
    m(0, 1) = 5;
    m(1, 1) = 2;
    /********************************************************************************************
    *  m = [ 0  5 ]                                                                                                                          *
    *         [ 0  1 ]                                                                                                                           *
    ********************************************************************************************/
    Vector v(4, 4);
    /********************************************************************************************
    * v = [ 4 4 4 4 ]                                                                                                                       *
    ********************************************************************************************/
    Matrix::View bv(b, 4, 4);
    /********************************************************************************************
    * bv =  [ * * * * ]                                                                                                                       *
    *          [ * * * * ]                                                                                                                       *
    *          [ * * * * ]                                                                                                                       *
    *          [ * * * * ]                                                                                                                       *
    ********************************************************************************************/

    *m.view().diagonals_begin() = v.view(0,1) * 2;
    m.view().columns_back() = v.view(2, 2) + 3;
    /********************************************************************************************
    *  m = [ 0  7 ]                                                                                                                          *
    *         [ 8  7 ]                                                                                                                           *
    ********************************************************************************************/

    for(const auto& row :  m.cview()){
        std::cout << row << "\n";
    }
    std::cout << "\n";
    /********************************************************************************************
    * (0.000000  7.000000  )                                                                                                         *
    * (8.000000  7.000000  )                                                                                                         *
    ********************************************************************************************/


    double i = 1;
    for(auto row :  bv.view(1, 1, 3, 3)){
        row = Vector(3, i++);
        std::cout << row << "\n";
    }
    std::cout << "\n";
    /********************************************************************************************
    * (1.000000  1.000000  1.000000  )                                                                                        *
    * (2.000000  2.000000  2.000000  )                                                                                        *
    * (3.000000  3.000000  3.000000  )                                                                                        *
    ********************************************************************************************/


    return 0;
}
#endif
