#include "GSLpp/matrix_complex.h"
#include "GSLpp/block.h"
#include <gsl/gsl_blas.h>

using namespace GSL;

/**********************************************************************************************
* MATRIX                                                                                                                                     *
**********************************************************************************************/

Matrix_Complex::Matrix_Complex(size_t n1, size_t n2)
 : gsl_mat_m(gsl_matrix_complex_alloc(n1, n2), gsl_matrix_complex_free)
{}

Matrix_Complex::Matrix_Complex(size_t n1, size_t n2, Complex val)
 : gsl_mat_m(gsl_matrix_complex_alloc(n1, n2), gsl_matrix_complex_free)
{
    gsl_matrix_complex_set_all(this->gsl_mat_m.get(), val);
}

Matrix_Complex::Matrix_Complex(std::initializer_list<Vector_Complex> l)
 : Matrix_Complex(l.size(), l.begin()->size())
{
    size_t row = 0, column = 0;
    for(auto it = l.begin(); it != l.end(); it++){
        for(const Complex& c : it->cview()){
            this->set(row, column, c);
            column++;
        }
        column = 0;
        row++;
    }
}

/*
Matrix_Complex::Matrix_Complex(std::initializer_list<std::initializer_list<Complex>> l)
 : Matrix_Complex(l.size(), l.begin()->size())
{
    size_t row = 0, column = 0;
    for(auto it = l.begin(); it != l.end(); it++){
        for(const Complex& c : *it){
            this->set(row, column, c);
            column++;
        }
        column = 0;
        row++;
    }
}
*/

Matrix_Complex::Matrix_Complex(gsl_matrix_complex* v)
 : gsl_mat_m(v, [](gsl_matrix_complex*){})
{}

gsl_matrix_complex* Matrix_Complex::gsl_data()
{
    return this->gsl_mat_m.get();
}

const gsl_matrix_complex* Matrix_Complex::gsl_data() const
{
    return this->gsl_mat_m.get();
}

bool GSL::operator==(const Matrix_Complex& a, const Matrix_Complex& b)
{
    return gsl_matrix_complex_equal(a.gsl_mat_m.get(), b.gsl_mat_m.get());
}

bool GSL::operator!=(const Matrix_Complex& a, const Matrix_Complex& b)
{
    return !(a==b);
}

Matrix_Complex& Matrix_Complex::copy(const Matrix_Complex& other)
{
    gsl_matrix_complex_memcpy(this->gsl_mat_m.get(), other.gsl_mat_m.get());
    return *this;
}

Matrix_Complex& Matrix_Complex::transpose_copy(const Matrix_Complex& other)
{
    gsl_matrix_complex_transpose_memcpy(this->gsl_mat_m.get(), other.gsl_mat_m.get());
    return *this;
}

Matrix_Complex& Matrix_Complex::swap(const Matrix_Complex& other)
{
    gsl_matrix_complex_swap(this->gsl_mat_m.get(), other.gsl_mat_m.get());
    return *this;
}

Matrix_Complex& Matrix_Complex::swap_rows(size_t i, size_t j)
{
    gsl_matrix_complex_swap_rows(this->gsl_mat_m.get(), i, j);
    return *this;
}

Matrix_Complex& Matrix_Complex::swap_columns(size_t i, size_t j)
{
    gsl_matrix_complex_swap_columns(this->gsl_mat_m.get(), i, j);
    return *this;
}

Matrix_Complex& Matrix_Complex::swap_rowcol(size_t i, size_t j)
{
    gsl_matrix_complex_swap_rowcol(this->gsl_mat_m.get(), i, j);
    return *this;
}

Matrix_Complex& Matrix_Complex::transpose()
{
    gsl_matrix_complex_transpose(this->gsl_mat_m.get());
    return *this;
}

Matrix_Complex& Matrix_Complex::T()
{
    return this->transpose();
}

Matrix_Complex& Matrix_Complex::hermitian_transpose()
{
    // gsl_matrix_complex_transpose(this->gsl_mat_m.get());
    for(size_t row = 0; row < this->num_rows(); row++){
        for(size_t column = row; column < this->num_columns(); column++){
            Complex tmp = (*this)(row,column);
            (*this)(row,column) = (*this)(column,row).conjugate();
            (*this)(column,row) = tmp.conjugate();
        }
    }

    return *this;
}

Matrix_Complex& Matrix_Complex::H()
{
    return this->transpose();
}


Matrix_Complex Matrix_Complex::clone() const
{
    Matrix_Complex res(this->gsl_mat_m->size1, this->gsl_mat_m->size2);
    res.copy(*this);
    return res;
}

size_t Matrix_Complex::num_rows() const
{
    return this->gsl_mat_m->size1;
}

size_t Matrix_Complex::num_columns() const
{
    return this->gsl_mat_m->size2;
}

std::pair<size_t, size_t> Matrix_Complex::dim() const
{
    return {this->num_rows(), this->num_columns()};
}

Matrix_Complex& Matrix_Complex::set_all(Complex val)
{
    gsl_matrix_complex_set_all(this->gsl_mat_m.get(), val);
    return *this;
}

Matrix_Complex& Matrix_Complex::set_zero()
{
    gsl_matrix_complex_set_zero(this->gsl_mat_m.get());
    return *this;
}

Matrix_Complex& Matrix_Complex::set(size_t i, size_t j, Complex val)
{
    gsl_matrix_complex_set(this->gsl_mat_m.get(), i, j, val);
    return *this;
}

Matrix_Complex& Matrix_Complex::set_identity()
{
    gsl_matrix_complex_set_identity(this->gsl_mat_m.get());
    return *this;
}

Complex Matrix_Complex::get(size_t i, size_t j) const
{
    return gsl_matrix_complex_get(this->gsl_mat_m.get(), i, j);
}

bool Matrix_Complex::isnull() const
{
    return gsl_matrix_complex_isnull(this->gsl_mat_m.get());
}

bool Matrix_Complex::ispos() const
{
    return gsl_matrix_complex_ispos(this->gsl_mat_m.get());
}

bool Matrix_Complex::isneg() const
{
    return gsl_matrix_complex_isneg(this->gsl_mat_m.get());
}

bool Matrix_Complex::isnonneg() const
{
    return gsl_matrix_complex_isnonneg(this->gsl_mat_m.get());
}

Matrix_Complex& Matrix_Complex::operator+=(const Matrix_Complex&  other)
{
    gsl_matrix_complex_add(this->gsl_mat_m.get(), other.gsl_mat_m.get());
    return *this;
}

Matrix_Complex& Matrix_Complex::operator-=(const Matrix_Complex&  other)
{
    gsl_matrix_complex_sub(this->gsl_mat_m.get(), other.gsl_mat_m.get());
    return *this;
}

Matrix_Complex& Matrix_Complex::operator*=(const Matrix_Complex&  other)
{
//    gsl_blas_dgemm(CblasNoTrans /* op(A) */, CblasNoTrans /* op(B) */, 1 /* alpha */,
//                                this->gsl_mat_m.view() /* A */, other.gsl_mat_m.get() /* B */,
//                                0 /* beta */, this->gsl_mat_m.view() /* C */);
    gsl_matrix_complex_mul_elements(this->gsl_mat_m.get(), other.gsl_mat_m.get());
    return *this;
}

Matrix_Complex& Matrix_Complex::operator/=(const Matrix_Complex& other)
{
    gsl_matrix_complex_div_elements(this->gsl_mat_m.get(), other.gsl_mat_m.get());
    return *this;
}

Matrix_Complex& Matrix_Complex::operator+=(Complex s)
{
    gsl_matrix_complex_add_constant(this->gsl_mat_m.get(), s);
    return *this;
}

Matrix_Complex& Matrix_Complex::operator-=(Complex s)
{
    gsl_matrix_complex_add_constant(this->gsl_mat_m.get(), -s);
    return *this;
}

Matrix_Complex& Matrix_Complex::operator*=(Complex s)
{
    gsl_matrix_complex_scale(this->gsl_mat_m.get(), s);
    return *this;
}

Matrix_Complex& Matrix_Complex::operator/=(Complex s)
{
    gsl_matrix_complex_scale(this->gsl_mat_m.get(), 1/s);
    return *this;
}

Matrix_Complex& Matrix_Complex::multiply(const Matrix_Complex&  other)
{
    gsl_blas_zgemm(CblasNoTrans /* op(A) */, CblasNoTrans /* op(B) */, gsl_complex_rect(1, 0) /* alpha */,
                                this->gsl_mat_m.get() /* A */, other.gsl_mat_m.get() /* B */,
                                gsl_complex_rect(0, 0) /* beta */, this->gsl_mat_m.get() /* C */);
    return *this;
}

Matrix_Complex GSL::operator+(const Matrix_Complex& a, const Matrix_Complex& b)
{
    Matrix_Complex res(a.clone());
    res += b;
    return res;
}

Matrix_Complex GSL::operator-(const Matrix_Complex& a, const Matrix_Complex& b)
{
    Matrix_Complex res(a.clone());
    res -= b;
    return res;
}

Matrix_Complex GSL::operator*(const Matrix_Complex& a, const Matrix_Complex& b)
{
    Matrix_Complex res(a.clone());
    res *= b;
    return res;
}

Matrix_Complex GSL::operator/(const Matrix_Complex& a, const Matrix_Complex& b)
{
    Matrix_Complex res(a.clone());
    res /= b;
    return res;
}

Matrix_Complex GSL::operator+(const Matrix_Complex& a, Complex s)
{
    Matrix_Complex res(a.clone());
    res += s;
    return res;
}

Matrix_Complex GSL::operator+(Complex s, const Matrix_Complex& a)
{
    return a + s;
}

Matrix_Complex GSL::operator-(const Matrix_Complex& a, Complex s)
{
    Matrix_Complex res(a.clone());
    res -= s;
    return res;
}

Matrix_Complex GSL::operator-(Complex s, const Matrix_Complex& a)
{
    return -(a - s);
}

Matrix_Complex GSL::operator*(const Matrix_Complex& a, Complex s)
{
    Matrix_Complex res(a.clone());
    res *= s;
    return res;
}

Matrix_Complex GSL::operator*(Complex s, const Matrix_Complex& a)
{
    return a*s;
}

Matrix_Complex GSL::operator/(const Matrix_Complex& a, Complex s)
{
    Matrix_Complex res(a.clone());
    res /= s;
    return res;
}

Matrix_Complex GSL::operator-(const Matrix_Complex& a)
{
    Matrix_Complex res(a.num_rows(), a.num_columns(), Complex(0));
    res -= a;
    return res;
}

Vector_Complex GSL::multiply(const Matrix_Complex& a, const Vector_Complex& v)
{
    Vector_Complex res(v.size());
    gsl_blas_zgemv(CblasNoTrans /* op(A) */,  gsl_complex_rect(1, 0) /* alpha */,
                              a.gsl_data() /* A */, v.gsl_data() /* x */,
                              gsl_complex_rect(0, 0) /* beta */, res.gsl_data() /* y */);
    return res;
}

Vector_Complex GSL::multiply(const Vector_Complex& v, const Matrix_Complex& a)
{
    Vector_Complex res(v.size());
    gsl_blas_zgemv(CblasTrans /* op(A) */, gsl_complex_rect(1, 0) /* alpha */,
                              a.gsl_data() /* A */, v.gsl_data() /* x */,
                              gsl_complex_rect(0, 0)/* beta */, res.gsl_data() /* y */);
    return res;
}

Matrix_Complex GSL::outer(const Vector_Complex&a, Vector_Complex& b)
{
    Matrix_Complex res(a.size(), b.size(), gsl_complex_rect(0, 0));
    gsl_blas_zgerc(gsl_complex_rect(1.0, 0), a.gsl_data(), b.gsl_data(), res.gsl_data());
    return res;
}

Matrix_Complex::View Matrix_Complex::view()
{
    return View(*this, 0, 0, this->num_rows(), this->num_columns());
}

const Matrix_Complex::View Matrix_Complex::view() const
{
    return View(*this, 0, 0, this->num_rows(), this->num_columns());
}

Matrix_Complex::Const_View Matrix_Complex::cview() const
{
    return Const_View(*this, 0, 0, this->num_rows(), this->num_columns());
}

Matrix_Complex::View Matrix_Complex::view(size_t k1, size_t k2, size_t n1, size_t n2)
{
    return View(*this, k1, k2, n1, n2);
}

const Matrix_Complex::View Matrix_Complex::view(size_t k1, size_t k2, size_t n1, size_t n2) const
{
    return View(*this, k1, k2, n1, n2);
}

Matrix_Complex::Const_View Matrix_Complex::cview(size_t k1, size_t k2, size_t n1, size_t n2) const
{
    return Const_View(*this, k1, k2, n1, n2);
}


Vector_Complex::View Matrix_Complex::row(size_t row)
{
    return gsl_matrix_complex_row(this->gsl_mat_m.get(), row);
}

Vector_Complex::Const_View Matrix_Complex::row(size_t row) const
{
    return gsl_matrix_complex_const_row(this->gsl_mat_m.get(), row);
}

Vector_Complex::Const_View Matrix_Complex::crow(size_t row) const
{
    return gsl_matrix_complex_const_row(this->gsl_mat_m.get(), row);
}

Vector_Complex::View Matrix_Complex::column(size_t column)
{
    return gsl_matrix_complex_column(this->gsl_mat_m.get(), column);
}

Vector_Complex::Const_View Matrix_Complex::column(size_t column) const
{
    return gsl_matrix_complex_const_column(this->gsl_mat_m.get(), column);
}

Vector_Complex::Const_View Matrix_Complex::ccolumn(size_t column) const
{
    return gsl_matrix_complex_const_column(this->gsl_mat_m.get(), column);
}

Vector_Complex::View Matrix_Complex::operator[](size_t row)
{
    return gsl_matrix_complex_row(this->gsl_mat_m.get(), row);
}

Vector_Complex::Const_View Matrix_Complex::operator[](size_t row) const
{
    return gsl_matrix_complex_const_row(this->gsl_mat_m.get(), row);
}

Vector_Complex::View Matrix_Complex::at(size_t row)
{
    if(!(row < this->gsl_mat_m->size1)){
        throw std::out_of_range("Row index " + std::to_string(row) + " out of range.");
    }
    return (*this)[row];
}

Vector_Complex::Const_View Matrix_Complex::at(size_t row) const
{
    if(!(row < this->gsl_mat_m->size1)){
        throw std::out_of_range("Row index " + std::to_string(row) + " out of range.");
    }
    return (*this)[row];
}

Complex& Matrix_Complex::operator()(size_t i, size_t j)
{
    return *reinterpret_cast<Complex*>(gsl_matrix_complex_ptr(this->gsl_mat_m.get(), i, j));
}

const Complex& Matrix_Complex::operator()(size_t i, size_t j) const
{
    return *reinterpret_cast<const Complex*>(gsl_matrix_complex_const_ptr(this->gsl_mat_m.get(), i, j));
}

Complex& Matrix_Complex::at(size_t row, size_t column)
{
    if(!(row < this->gsl_mat_m->size1) || !(column < this->gsl_mat_m->size2)){
        throw std::out_of_range("(Row, Column) index (" + std::to_string(row) +
            ", " + std::to_string(column) + ") out of range.");
    }
    return (*this)(row, column);
}

const Complex& Matrix_Complex::at(size_t row, size_t column) const
{
    if(!(row < this->gsl_mat_m->size1) || !(column < this->gsl_mat_m->size2)){
        throw std::out_of_range("(Row, Column) index (" + std::to_string(row) +
            ", " + std::to_string(column) + ") out of range.");
    }
    return (*this)(row, column);
}

Vector_Complex::View Matrix_Complex::subrow(size_t i, size_t offset, size_t n)
{
    return gsl_matrix_complex_subrow(this->gsl_mat_m.get(), i, offset, n);
}
Vector_Complex::Const_View Matrix_Complex::subrow(size_t i, size_t offset, size_t n) const
{
    return gsl_matrix_complex_const_subrow(this->gsl_mat_m.get(), i, offset, n);
}
Vector_Complex::Const_View Matrix_Complex::csubrow(size_t i, size_t offset, size_t n) const
{
    return gsl_matrix_complex_const_subrow(this->gsl_mat_m.get(), i, offset, n);
}

Vector_Complex::View Matrix_Complex::subcolumn(size_t i, size_t offset, size_t n)
{
    return gsl_matrix_complex_subcolumn(this->gsl_mat_m.get(), i, offset, n);
}
Vector_Complex::Const_View Matrix_Complex::subcolumn(size_t i, size_t offset, size_t n) const
{
    return gsl_matrix_complex_const_subcolumn(this->gsl_mat_m.get(), i, offset, n);
}
Vector_Complex::Const_View Matrix_Complex::csubcolumn(size_t i, size_t offset, size_t n) const
{
    return gsl_matrix_complex_const_subcolumn(this->gsl_mat_m.get(), i, offset, n);
}

Vector_Complex::View Matrix_Complex::diagonal()
{
    return gsl_matrix_complex_diagonal(this->gsl_mat_m.get());
}
Vector_Complex::Const_View Matrix_Complex::diagonal() const
{
    return gsl_matrix_complex_const_diagonal(this->gsl_mat_m.get());
}
Vector_Complex::Const_View Matrix_Complex::cdiagonal() const
{
    return gsl_matrix_complex_const_diagonal(this->gsl_mat_m.get());
}

Vector_Complex::View Matrix_Complex::subdiagonal(size_t k)
{
    return gsl_matrix_complex_subdiagonal(this->gsl_mat_m.get(), k);
}
Vector_Complex::Const_View Matrix_Complex::subdiagonal(size_t k) const
{
    return gsl_matrix_complex_const_subdiagonal(this->gsl_mat_m.get(), k);
}
Vector_Complex::Const_View Matrix_Complex::csubdiagonal(size_t k) const
{
    return gsl_matrix_complex_const_subdiagonal(this->gsl_mat_m.get(), k);
}

Vector_Complex::View Matrix_Complex::superdiagonal(size_t k)
{
    return gsl_matrix_complex_superdiagonal(this->gsl_mat_m.get(), k);
}
Vector_Complex::Const_View Matrix_Complex::superdiagonal(size_t k) const
{
    return gsl_matrix_complex_const_superdiagonal(this->gsl_mat_m.get(), k);
}
Vector_Complex::Const_View Matrix_Complex::csuperdiagonal(size_t k) const
{
    return gsl_matrix_complex_const_superdiagonal(this->gsl_mat_m.get(), k);
}

std::string Matrix_Complex::to_string() const
{
    std::string res = "";
    for(const auto& row : this->cview()){
        res += std::to_string(row) + "\n";
    }
    return res;
}

std::string std::to_string(const GSL::Matrix_Complex& m)
{
    return m.to_string();
}

std::ostream& GSL::operator<<(std::ostream& os, const Matrix_Complex& m)
{
    os << m.to_string();
    return os;
}


/**********************************************************************************************
**********************************************************************************************/


/**********************************************************************************************
* MATRIX VIEW                                                                                                                            *
**********************************************************************************************/

Matrix_Complex::View::View(const Matrix_Complex& m)
 : View(m, 0, 0, m.num_rows(), m.num_columns())
{}

Matrix_Complex::View::View(const Matrix_Complex& m, size_t k1, size_t k2, size_t n1, size_t n2)
 : gsl_mat_view_m(gsl_matrix_complex_submatrix(m.gsl_mat_m.get(), k1, k2, n1, n2))
{}

Matrix_Complex::View::View(GSL::Block& b, size_t n1, size_t n2)
 : View(b, 0, n1, n2)
{}

Matrix_Complex::View::View(GSL::Block& b, size_t offset, size_t n1, size_t n2)
 : gsl_mat_view_m(gsl_matrix_complex_view_array(b.data() + offset, n1, n2))
{}

Matrix_Complex::View::View(GSL::Block& b, size_t offset, size_t n1, size_t n2, size_t tda)
 : gsl_mat_view_m(gsl_matrix_complex_view_array_with_tda(b.data() + offset, n1, n2, tda))
{}

Matrix_Complex::View::View(double* data, size_t n1, size_t n2)
 : View(data, 0, n1, n2)
{}

Matrix_Complex::View::View(double* data, size_t offset, size_t n1, size_t n2)
 : gsl_mat_view_m(gsl_matrix_complex_view_array(data + offset, n1, n2))
{}

Matrix_Complex::View::View(double* data, size_t offset, size_t n1, size_t n2, size_t tda)
 : gsl_mat_view_m(gsl_matrix_complex_view_array_with_tda(data + offset, n1, n2, tda))
{}

Matrix_Complex::View::View(Vector_Complex& v, size_t n1, size_t n2)
 : gsl_mat_view_m(gsl_matrix_complex_view_vector(v.gsl_data(), n1, n2))
{}

Matrix_Complex::View::View(Vector_Complex& v, size_t n1, size_t n2, size_t tda)
 : gsl_mat_view_m(gsl_matrix_complex_view_vector_with_tda(v.gsl_data(), n1, n2, tda))
{}

Matrix_Complex::View::operator Matrix_Complex()
{
    return Matrix_Complex(&this->gsl_mat_view_m.matrix);
}

Matrix_Complex::View::operator const Matrix_Complex() const
{
    return Matrix_Complex(const_cast<gsl_matrix_complex*>(&this->gsl_mat_view_m.matrix));
}

gsl_matrix_complex* Matrix_Complex::View::gsl_data()
{
    return &this->gsl_mat_view_m.matrix;
}

const gsl_matrix_complex* Matrix_Complex::View::gsl_data() const
{
    return &this->gsl_mat_view_m.matrix;
}

Matrix_Complex::View Matrix_Complex::View::view()
{
    return View(*this, 0, 0, this->num_rows(), this->num_columns());
}

Matrix_Complex::Const_View Matrix_Complex::View::view() const
{
    return Const_View(*this, 0, 0, this->num_rows(), this->num_columns());
}

Matrix_Complex::Const_View Matrix_Complex::View::cview() const
{
    return Const_View(*this, 0, 0, this->num_rows(), this->num_columns());
}

Matrix_Complex::View Matrix_Complex::View::view(size_t k1, size_t k2, size_t n1, size_t n2)
{
    return View(*this, k1, k2, n1, n2);
}

Matrix_Complex::Const_View Matrix_Complex::View::view(size_t k1, size_t k2, size_t n1, size_t n2) const
{
    return Const_View(*this, k1, k2, n1, n2);
}

Matrix_Complex::Const_View Matrix_Complex::View::cview(size_t k1, size_t k2, size_t n1, size_t n2) const
{
    return Const_View(*this, k1, k2, n1, n2);
}

size_t Matrix_Complex::View::num_rows() const
{
    return this->gsl_mat_view_m.matrix.size1;
}

size_t Matrix_Complex::View::num_columns() const
{
    return this->gsl_mat_view_m.matrix.size2;
}

std::pair<size_t, size_t> Matrix_Complex::View::dim() const
{
    return {this->gsl_mat_view_m.matrix.size1, this->gsl_mat_view_m.matrix.size2};
}

size_t Matrix_Complex::View::tda() const
{
    return this->gsl_mat_view_m.matrix.tda;
}

Matrix_Complex::View& Matrix_Complex::View::operator+=(const Matrix_Complex& other)
{
    gsl_matrix_complex_add(&this->gsl_mat_view_m.matrix, other.gsl_mat_m.get());
    return *this;

}

Matrix_Complex::View& Matrix_Complex::View::operator-=(const Matrix_Complex& other)
{
    gsl_matrix_complex_sub(&this->gsl_mat_view_m.matrix, other.gsl_mat_m.get());
    return *this;
}

Matrix_Complex::View& Matrix_Complex::View::operator*=(const Matrix_Complex& other)
{
    gsl_matrix_complex_mul_elements(&this->gsl_mat_view_m.matrix, other.gsl_mat_m.get());
    return *this;
}

Matrix_Complex::View& Matrix_Complex::View::operator/=(const Matrix_Complex& other)
{
    gsl_matrix_complex_div_elements(&this->gsl_mat_view_m.matrix, other.gsl_mat_m.get());
    return *this;
}

Matrix_Complex::View& Matrix_Complex::View::operator+=(Complex s)
{
    gsl_matrix_complex_add_constant(&this->gsl_mat_view_m.matrix, s);
    return *this;
}

Matrix_Complex::View& Matrix_Complex::View::operator-=(Complex s)
{
    gsl_matrix_complex_add_constant(&this->gsl_mat_view_m.matrix, -s);
    return *this;
}

Matrix_Complex::View& Matrix_Complex::View::operator*=(Complex s)
{
    gsl_matrix_complex_scale(&this->gsl_mat_view_m.matrix, s);
    return *this;
}

Matrix_Complex::View& Matrix_Complex::View::operator/=(Complex s)
{
    gsl_matrix_complex_scale(&this->gsl_mat_view_m.matrix, 1/s);
    return *this;
}

Matrix_Complex::View& Matrix_Complex::View::multiply(const Matrix_Complex& other)
{
    gsl_blas_zgemm(CblasNoTrans /* op(A) */, CblasNoTrans /* op(B) */, gsl_complex_rect(1, 0) /* alpha */,
                                &this->gsl_mat_view_m.matrix /* A */, other.gsl_mat_m.get() /* B */,
                                gsl_complex_rect(0, 0) /* beta */, &this->gsl_mat_view_m.matrix /* C */);
    return *this;
}

Vector_Complex::View Matrix_Complex::View::row(size_t row)
{
    return gsl_matrix_complex_row(&this->gsl_mat_view_m.matrix, row);
}

Vector_Complex::Const_View Matrix_Complex::View::row(size_t row) const
{
    return gsl_matrix_complex_const_row(&this->gsl_mat_view_m.matrix, row);
}

Vector_Complex::Const_View Matrix_Complex::View::crow(size_t row) const
{
    return gsl_matrix_complex_const_row(&this->gsl_mat_view_m.matrix, row);
}

Vector_Complex::View Matrix_Complex::View::column(size_t column)
{
    return gsl_matrix_complex_column(&this->gsl_mat_view_m.matrix, column);
}

Vector_Complex::Const_View Matrix_Complex::View::column(size_t column) const
{
    return gsl_matrix_complex_const_column(&this->gsl_mat_view_m.matrix, column);
}

Vector_Complex::Const_View Matrix_Complex::View::ccolumn(size_t column) const
{
    return gsl_matrix_complex_const_column(&this->gsl_mat_view_m.matrix, column);
}


Vector_Complex::View Matrix_Complex::View::subrow(size_t i, size_t offset, size_t n)
{
    return gsl_matrix_complex_subrow(&this->gsl_mat_view_m.matrix, i,  offset, n);
}

Vector_Complex::Const_View Matrix_Complex::View::subrow(size_t i, size_t offset, size_t n) const
{
    return gsl_matrix_complex_const_subrow(&this->gsl_mat_view_m.matrix, i, offset, n);
}

Vector_Complex::Const_View Matrix_Complex::View::csubrow(size_t i, size_t offset, size_t n) const
{
    return gsl_matrix_complex_const_subrow(&this->gsl_mat_view_m.matrix, i, offset, n);
}

Vector_Complex::View Matrix_Complex::View::subcolumn(size_t i, size_t offset, size_t n)
{
    return gsl_matrix_complex_subcolumn(&this->gsl_mat_view_m.matrix, i, offset, n);
}

Vector_Complex::Const_View Matrix_Complex::View::subcolumn(size_t i, size_t offset, size_t n) const
{
    return gsl_matrix_complex_const_subcolumn(&this->gsl_mat_view_m.matrix, i, offset, n);
}

Vector_Complex::Const_View Matrix_Complex::View::csubcolumn(size_t i, size_t offset, size_t n) const
{
    return gsl_matrix_complex_const_subcolumn(&this->gsl_mat_view_m.matrix, i, offset, n);
}

Vector_Complex::View Matrix_Complex::View::diagonal()
{
    return gsl_matrix_complex_diagonal(&this->gsl_mat_view_m.matrix);
}

Vector_Complex::Const_View Matrix_Complex::View::diagonal() const
{
    return gsl_matrix_complex_const_diagonal(&this->gsl_mat_view_m.matrix);
}

Vector_Complex::Const_View Matrix_Complex::View::cdiagonal() const
{
    return gsl_matrix_complex_const_diagonal(&this->gsl_mat_view_m.matrix);
}

Vector_Complex::View Matrix_Complex::View::subdiagonal(size_t k)
{
    return gsl_matrix_complex_subdiagonal(&this->gsl_mat_view_m.matrix, k);
}

Vector_Complex::Const_View Matrix_Complex::View::subdiagonal(size_t k) const
{
    return gsl_matrix_complex_const_subdiagonal(&this->gsl_mat_view_m.matrix, k);
}

Vector_Complex::Const_View Matrix_Complex::View::csubdiagonal(size_t k) const
{
    return gsl_matrix_complex_const_subdiagonal(&this->gsl_mat_view_m.matrix, k);
}

Vector_Complex::View Matrix_Complex::View::superdiagonal(size_t k)
{
    return gsl_matrix_complex_superdiagonal(&this->gsl_mat_view_m.matrix, k);
}

Vector_Complex::Const_View Matrix_Complex::View::superdiagonal(size_t k) const
{
    return gsl_matrix_complex_const_superdiagonal(&this->gsl_mat_view_m.matrix, k);
}

Vector_Complex::Const_View Matrix_Complex::View::csuperdiagonal(size_t k) const
{
    return gsl_matrix_complex_const_superdiagonal(&this->gsl_mat_view_m.matrix, k);
}

Vector_Complex::View Matrix_Complex::View::operator[](size_t row)
{
    return gsl_matrix_complex_row(&this->gsl_mat_view_m.matrix, row);
}

Vector_Complex::Const_View Matrix_Complex::View::operator[](size_t row) const
{
    return gsl_matrix_complex_const_row(&this->gsl_mat_view_m.matrix, row);
}

Vector_Complex::View Matrix_Complex::View::at(size_t row)
{
    if(!(row < this->gsl_mat_view_m.matrix.size1)){
        throw std::out_of_range("Row index " + std::to_string(row) + " out of range.");
    }
    return (*this)[row];
}

Vector_Complex::Const_View Matrix_Complex::View::at(size_t row) const
{
    if(!(row < this->gsl_mat_view_m.matrix.size1)){
        throw std::out_of_range("Row index " + std::to_string(row) + " out of range.");
    }
    return (*this)[row];
}

Complex& Matrix_Complex::View::operator()(size_t i, size_t j)
{
    return *reinterpret_cast<Complex*>(gsl_matrix_complex_ptr(&this->gsl_mat_view_m.matrix, i, j));
}

const Complex& Matrix_Complex::View::operator()(size_t i, size_t j) const
{
    return *reinterpret_cast<const Complex*>(gsl_matrix_complex_const_ptr(&this->gsl_mat_view_m.matrix, i, j));
}

Complex& Matrix_Complex::View::at(size_t row, size_t column)
{
    if(!(row < this->gsl_mat_view_m.matrix.size1) || !(column < this->gsl_mat_view_m.matrix.size2)){
        throw std::out_of_range("(Row, Column) index (" + std::to_string(row) +
            ", " + std::to_string(column) + ") out of range.");
    }
    return (*this)(row, column);
}

const Complex& Matrix_Complex::View::at(size_t row, size_t column) const
{
    if(!(row < this->gsl_mat_view_m.matrix.size1) || !(column < this->gsl_mat_view_m.matrix.size2)){
        throw std::out_of_range("(Row, Column) index (" + std::to_string(row) +
            ", " + std::to_string(column) + ") out of range.");
    }
    return (*this)(row, column);
}

Matrix_Complex::View& Matrix_Complex::View::swap(Matrix_Complex::View& mv)
{
    gsl_matrix_complex_swap(&this->gsl_mat_view_m.matrix, &mv.gsl_mat_view_m.matrix);
    return *this;
}

Matrix_Complex::View& Matrix_Complex::View::swap(Matrix_Complex::View&& mv)
{
    gsl_matrix_complex_swap(&this->gsl_mat_view_m.matrix, &mv.gsl_mat_view_m.matrix);
    return *this;
}

Matrix_Complex::View& Matrix_Complex::View::swap(Matrix_Complex& m)
{
    gsl_matrix_complex_swap(&this->gsl_mat_view_m.matrix, m.gsl_mat_m.get());
    return *this;
}

Matrix_Complex::View& Matrix_Complex::View::swap(Matrix_Complex&& m)
{
    gsl_matrix_complex_swap(&this->gsl_mat_view_m.matrix, m.gsl_mat_m.get());
    return *this;
}

Matrix_Complex::View& Matrix_Complex::View::copy(const Matrix_Complex::View& mv)
{
    gsl_matrix_complex_memcpy(&this->gsl_mat_view_m.matrix, &mv.gsl_mat_view_m.matrix);
    return *this;
}

Matrix_Complex::View& Matrix_Complex::View::copy(Matrix_Complex::View&& mv)
{
    gsl_matrix_complex_swap(&this->gsl_mat_view_m.matrix, &mv.gsl_mat_view_m.matrix);
    return *this;
}

Matrix_Complex::View& Matrix_Complex::View::copy(const Matrix_Complex& m)
{
    gsl_matrix_complex_memcpy(&this->gsl_mat_view_m.matrix, m.gsl_mat_m.get());
    return *this;
}

Matrix_Complex::View& Matrix_Complex::View::copy(Matrix_Complex&& m)
{
    gsl_matrix_complex_swap(&this->gsl_mat_view_m.matrix, m.gsl_mat_m.get());
    return *this;
}

Matrix_Complex::View& Matrix_Complex::View::transpose_copy(const Matrix_Complex& other)
{
    gsl_matrix_complex_transpose_memcpy(&this->gsl_mat_view_m.matrix, other.gsl_mat_m.get());
    return *this;
}

Matrix_Complex::View& Matrix_Complex::View::swap_rows(size_t i, size_t j)
{
    gsl_matrix_complex_swap_rows(&this->gsl_mat_view_m.matrix, i, j);
    return *this;
}

Matrix_Complex::View& Matrix_Complex::View::swap_columns(size_t i, size_t j)
{
    gsl_matrix_complex_swap_columns(&this->gsl_mat_view_m.matrix, i, j);
    return *this;
}

Matrix_Complex::View& Matrix_Complex::View::swap_rowcol(size_t i, size_t j)
{
    gsl_matrix_complex_swap_rowcol(&this->gsl_mat_view_m.matrix, i, j);
    return *this;
}

Matrix_Complex::View& Matrix_Complex::View::transpose()
{
    gsl_matrix_complex_transpose(&this->gsl_mat_view_m.matrix);
    return *this;
}

Matrix_Complex::View& Matrix_Complex::View::T()
{
    return this->transpose();
}

Matrix_Complex::View& Matrix_Complex::View::set_all(Complex val)
{
    gsl_matrix_complex_set_all(&this->gsl_mat_view_m.matrix, val);
    return *this;
}

Matrix_Complex::View& Matrix_Complex::View::set_zero()
{
    gsl_matrix_complex_set_zero(&this->gsl_mat_view_m.matrix);
    return *this;
}

Matrix_Complex::View& Matrix_Complex::View::set(size_t i, size_t j, Complex val)
{
    gsl_matrix_complex_set(&this->gsl_mat_view_m.matrix, i, j, val);
    return *this;
}

Matrix_Complex::View& Matrix_Complex::View::set_identity()
{
    gsl_matrix_complex_set_identity(&this->gsl_mat_view_m.matrix);
    return *this;
}

Complex Matrix_Complex::View::get(size_t i, size_t j) const
{
    return gsl_matrix_complex_get(&this->gsl_mat_view_m.matrix, i, j);
}

bool Matrix_Complex::View::isnull() const
{
    return gsl_matrix_complex_isnull(&this->gsl_mat_view_m.matrix);
}

bool Matrix_Complex::View::ispos() const
{
    return gsl_matrix_complex_ispos(&this->gsl_mat_view_m.matrix);
}

bool Matrix_Complex::View::isneg() const
{
    return gsl_matrix_complex_isneg(&this->gsl_mat_view_m.matrix);
}

bool Matrix_Complex::View::isnonneg() const
{
    return gsl_matrix_complex_isnonneg(&this->gsl_mat_view_m.matrix);
}

Matrix_Complex::View& Matrix_Complex::View::operator=(const Matrix_Complex& m)
{
    return this->copy(m);
}

Matrix_Complex::View& Matrix_Complex::View::operator=(Matrix_Complex&& m)
{
    return this->swap(m);
}

Matrix_Complex::View::iterator Matrix_Complex::View::rows_begin() noexcept
{
    return Row_Iterator(this, 0);
}

Matrix_Complex::View::const_iterator Matrix_Complex::View::rows_begin() const noexcept
{
    return Const_Row_Iterator(this, 0);
}

Matrix_Complex::View::const_iterator Matrix_Complex::View::rows_cbegin() const noexcept
{
    return Const_Row_Iterator(this, 0);
}

Matrix_Complex::View::iterator Matrix_Complex::View::rows_end() noexcept
{
    return Row_Iterator(this, this->gsl_mat_view_m.matrix.size1);
}

Matrix_Complex::View::const_iterator Matrix_Complex::View::rows_end() const noexcept
{
    return Const_Row_Iterator(this, this->gsl_mat_view_m.matrix.size1);
}

Matrix_Complex::View::const_iterator Matrix_Complex::View::rows_cend() const noexcept
{
    return Const_Row_Iterator(this, this->gsl_mat_view_m.matrix.size1);
}

Matrix_Complex::View::reverse_iterator Matrix_Complex::View::rows_rbegin() noexcept
{
    return std::reverse_iterator<iterator>(this->end());
}

Matrix_Complex::View::const_reverse_iterator Matrix_Complex::View::rows_rbegin() const noexcept
{
    return std::reverse_iterator<const_iterator>(this->end());
}

Matrix_Complex::View::const_reverse_iterator Matrix_Complex::View::rows_crbegin() const noexcept
{
    return std::reverse_iterator<const_iterator>(this->cend());
}

Matrix_Complex::View::reverse_iterator Matrix_Complex::View::rows_rend() noexcept
{
    return std::reverse_iterator<iterator>(this->begin());
}

Matrix_Complex::View::const_reverse_iterator Matrix_Complex::View::rows_rend() const noexcept
{
    return std::reverse_iterator<const_iterator>(this->begin());
}

Matrix_Complex::View::const_reverse_iterator Matrix_Complex::View::rows_crend() const noexcept
{
    return std::reverse_iterator<const_iterator>(this->cbegin());
}

Matrix_Complex::View::value_type Matrix_Complex::View::rows_front()
{
    return *this->begin();
}

Matrix_Complex::View::const_value_type Matrix_Complex::View::rows_front() const
{
    return *this->begin();
}

Matrix_Complex::View::value_type Matrix_Complex::View::rows_back()
{
        return *(--this->end());
}

Matrix_Complex::View::const_value_type Matrix_Complex::View::rows_back() const
{
    return *(--this->end());
}


Matrix_Complex::View::Column_Iterator Matrix_Complex::View::columns_begin() noexcept
{
    return Column_Iterator(this, 0);
}

Matrix_Complex::View::Const_Column_Iterator Matrix_Complex::View::columns_begin() const noexcept
{
    return Const_Column_Iterator(this, 0);
}

Matrix_Complex::View::Const_Column_Iterator Matrix_Complex::View::columns_cbegin() const noexcept
{
    return Const_Column_Iterator(this, 0);
}

Matrix_Complex::View::Column_Iterator Matrix_Complex::View::columns_end() noexcept
{
    return Column_Iterator(this, this->gsl_mat_view_m.matrix.size2);
}

Matrix_Complex::View::Const_Column_Iterator Matrix_Complex::View::columns_end() const noexcept
{
    return Const_Column_Iterator(this, this->gsl_mat_view_m.matrix.size2);
}

Matrix_Complex::View::Const_Column_Iterator Matrix_Complex::View::columns_cend() const noexcept
{
    return Const_Column_Iterator(this, this->gsl_mat_view_m.matrix.size2);
}

std::reverse_iterator<Matrix_Complex::View::Column_Iterator> Matrix_Complex::View::columns_rbegin() noexcept
{
    return std::reverse_iterator<Column_Iterator>(this->columns_end());
}

std::reverse_iterator<Matrix_Complex::View::Const_Column_Iterator> Matrix_Complex::View::columns_rbegin() const noexcept
{
    return std::reverse_iterator<Const_Column_Iterator>(this->columns_end());
}

std::reverse_iterator<Matrix_Complex::View::Const_Column_Iterator> Matrix_Complex::View::columns_crbegin() const noexcept
{
    return std::reverse_iterator<Const_Column_Iterator>(this->columns_cend());
}

std::reverse_iterator<Matrix_Complex::View::Column_Iterator> Matrix_Complex::View::columns_rend() noexcept
{
    return std::reverse_iterator<Column_Iterator>(this->columns_begin());
}

std::reverse_iterator<Matrix_Complex::View::Const_Column_Iterator> Matrix_Complex::View::columns_rend() const noexcept
{
    return std::reverse_iterator<Const_Column_Iterator>(this->columns_begin());
}

std::reverse_iterator<Matrix_Complex::View::Const_Column_Iterator> Matrix_Complex::View::columns_crend() const noexcept
{
    return std::reverse_iterator<Const_Column_Iterator>(this->columns_cbegin());
}

Matrix_Complex::View::value_type Matrix_Complex::View::columns_front()
{
    return *this->columns_begin();
}

Matrix_Complex::View::const_value_type Matrix_Complex::View::columns_front() const
{
    return *this->columns_begin();
}

Matrix_Complex::View::value_type Matrix_Complex::View::columns_back()
{
        return *(--this->columns_end());
}

Matrix_Complex::View::const_value_type Matrix_Complex::View::columns_back() const
{
    return *(--this->columns_end());
}


Matrix_Complex::View::diagonal_iterator Matrix_Complex::View::diagonals_begin() noexcept
{
    return diagonal_iterator(this, 0);
}

Matrix_Complex::View::const_diagonal_iterator Matrix_Complex::View::diagonals_begin() const noexcept
{
    return const_diagonal_iterator(this, 0);
}

Matrix_Complex::View::const_diagonal_iterator Matrix_Complex::View::diagonals_cbegin() const noexcept
{
    return const_diagonal_iterator(this, 0);
}

Matrix_Complex::View::diagonal_iterator Matrix_Complex::View::diagonals_end() noexcept
{
    return diagonal_iterator(this, this->gsl_mat_view_m.matrix.size1 + this->gsl_mat_view_m.matrix.size2);
}

Matrix_Complex::View::const_diagonal_iterator Matrix_Complex::View::diagonals_end() const noexcept
{
    return const_diagonal_iterator(this, this->gsl_mat_view_m.matrix.size1 + this->gsl_mat_view_m.matrix.size2);
}

Matrix_Complex::View::const_diagonal_iterator Matrix_Complex::View::diagonals_cend() const noexcept
{
    return const_diagonal_iterator(this, this->gsl_mat_view_m.matrix.size1 + this->gsl_mat_view_m.matrix.size2);
}

std::reverse_iterator<Matrix_Complex::View::Diagonal_Iterator> Matrix_Complex::View::diagonals_rbegin() noexcept
{
    return std::reverse_iterator<Diagonal_Iterator>(this->diagonals_end());
}

Matrix_Complex::View::const_reverse_diagonal_iterator Matrix_Complex::View::diagonals_rbegin() const noexcept
{
    return const_reverse_diagonal_iterator(this->diagonals_end());
}

Matrix_Complex::View::const_reverse_diagonal_iterator Matrix_Complex::View::diagonals_crbegin() const noexcept
{
    return const_reverse_diagonal_iterator(this->diagonals_cend());
}

Matrix_Complex::View::reverse_diagonal_iterator Matrix_Complex::View::diagonals_rend() noexcept
{
    return reverse_diagonal_iterator(this->diagonals_begin());
}

Matrix_Complex::View::const_reverse_diagonal_iterator Matrix_Complex::View::diagonals_rend() const noexcept
{
    return const_reverse_diagonal_iterator(this->diagonals_begin());
}

Matrix_Complex::View::const_reverse_diagonal_iterator Matrix_Complex::View::diagonals_crend() const noexcept
{
    return const_reverse_diagonal_iterator(this->diagonals_cbegin());
}

Matrix_Complex::View::value_type Matrix_Complex::View::diagonals_front()
{
    return *this->diagonals_begin();
}

Matrix_Complex::View::const_value_type Matrix_Complex::View::diagonals_front() const
{
    return *this->diagonals_begin();
}

Matrix_Complex::View::value_type Matrix_Complex::View::diagonals_back()
{
    return *(--this->diagonals_end());
}

Matrix_Complex::View::const_value_type Matrix_Complex::View::diagonals_back() const
{
    return *(--this->diagonals_end());
}


/**********************************************************************************************
* MATRIX ITERATOR                                                                                                                    *
**********************************************************************************************/

Matrix_Complex::View::Iterator::Iterator()
 : m_m(nullptr), vector_view_m(nullptr, 0), index_m()
{}

Matrix_Complex::View::Iterator::Iterator(Matrix_Complex::View* m, size_t i)
 : m_m(m), vector_view_m(nullptr, 0), index_m(i)
{}

Matrix_Complex::View::Const_Iterator::Const_Iterator()
 : m_m(nullptr), vector_view_m(nullptr, 0), index_m()
{}

Matrix_Complex::View::Const_Iterator::Const_Iterator(const Matrix_Complex::View* m, size_t i)
 : m_m(m), vector_view_m(nullptr, 0), index_m(i)
{}

Matrix_Complex::View::Row_Iterator::reference Matrix_Complex::View::Row_Iterator::operator*()
{
    return gsl_matrix_complex_row(&this->m_m->gsl_mat_view_m.matrix, this->index_m);
}

Matrix_Complex::View::Row_Iterator::pointer Matrix_Complex::View::Row_Iterator::operator->()
{
    this->vector_view_m = gsl_matrix_complex_row(&this->m_m->gsl_mat_view_m.matrix, this->index_m);
    return &vector_view_m;
}

Matrix_Complex::View::Column_Iterator::reference Matrix_Complex::View::Column_Iterator::operator*()
{
    return gsl_matrix_complex_column(&this->m_m->gsl_mat_view_m.matrix, this->index_m);
}

Matrix_Complex::View::Column_Iterator::pointer Matrix_Complex::View::Column_Iterator::operator->()
{
    this->vector_view_m = gsl_matrix_complex_column(&this->m_m->gsl_mat_view_m.matrix, this->index_m);
    return &vector_view_m;
}

Matrix_Complex::View::Diagonal_Iterator::reference Matrix_Complex::View::Diagonal_Iterator::operator*()
{
    size_t max_dim = std::max(this->m_m->gsl_mat_view_m.matrix.size1, this->m_m->gsl_mat_view_m.matrix.size2) ;
    if(this->index_m < max_dim){
        return gsl_matrix_complex_subdiagonal(&this->m_m->gsl_mat_view_m.matrix, max_dim - this->index_m - 1);
    }else{
        return gsl_matrix_complex_superdiagonal(&this->m_m->gsl_mat_view_m.matrix, this->index_m % max_dim);
    }
}

Matrix_Complex::View::Diagonal_Iterator::pointer Matrix_Complex::View::Diagonal_Iterator::operator->()
{
    size_t max_dim = std::max(this->m_m->gsl_mat_view_m.matrix.size1, this->m_m->gsl_mat_view_m.matrix.size2) ;
    if(this->index_m < max_dim){
        this->vector_view_m = gsl_matrix_complex_subdiagonal(&this->m_m->gsl_mat_view_m.matrix, max_dim - this->index_m - 1);
    }else{
        this->vector_view_m = gsl_matrix_complex_superdiagonal(&this->m_m->gsl_mat_view_m.matrix, this->index_m % max_dim);
    }
    return &vector_view_m;
}

Matrix_Complex::View::Row_Iterator::difference_type Matrix_Complex::View::Row_Iterator::operator-(Row_Iterator const& other)
{
    return this->index_m - other.index_m;
}

Matrix_Complex::View::Column_Iterator::difference_type Matrix_Complex::View::Column_Iterator::operator-(Column_Iterator const& other)
{
    return this->index_m - other.index_m;
}

Matrix_Complex::View::Diagonal_Iterator::difference_type Matrix_Complex::View::Diagonal_Iterator::operator-(Diagonal_Iterator const& other)
{
    return this->index_m - other.index_m;
}

bool Matrix_Complex::View::Iterator::operator==(const Iterator& other)
{
    return this->index_m == other.index_m;
}

bool Matrix_Complex::View::Iterator::operator!=(const Iterator& other)
{
    return !(*this == other);
}

bool Matrix_Complex::View::Iterator::operator<=(const Iterator& other)
{
    return this->index_m <= other.index_m;
}

bool Matrix_Complex::View::Iterator::operator>=(const Iterator& other)
{
    return this->index_m >= other.index_m;
}

bool Matrix_Complex::View::Iterator::operator<(const Iterator& other)
{
    return !(*this >= other);
}

bool Matrix_Complex::View::Iterator::operator>(const Iterator& other)
{
    return !(*this <= other);
}

/**********************************************************************************************
**********************************************************************************************/


/**********************************************************************************************
* MATRIX VIEW CONST ITERATOR                                                                                               *
**********************************************************************************************/

Matrix_Complex::View::Const_Row_Iterator::difference_type
  Matrix_Complex::View::Const_Row_Iterator::operator-(Const_Row_Iterator const& other)
{
    return this->index_m - other.index_m;
}

Matrix_Complex::View::Const_Column_Iterator::difference_type
  Matrix_Complex::View::Const_Column_Iterator::operator-(Const_Column_Iterator const& other)
{
    return this->index_m - other.index_m;
}

Matrix_Complex::View::Const_Diagonal_Iterator::difference_type
  Matrix_Complex::View::Const_Diagonal_Iterator::operator-(Const_Diagonal_Iterator const& other)
{
    return this->index_m - other.index_m;
}

Matrix_Complex::View::Const_Row_Iterator::const_reference Matrix_Complex::View::Const_Row_Iterator::operator*()
{
    return gsl_matrix_complex_const_row(
            const_cast<gsl_matrix_complex*>(&this->m_m->gsl_mat_view_m.matrix)
            , this->index_m);
}

Matrix_Complex::View::Const_Row_Iterator::pointer
  Matrix_Complex::View::Const_Row_Iterator::operator->()
{
    this->vector_view_m =
        gsl_matrix_complex_row(
            const_cast<gsl_matrix_complex*>(&this->m_m->gsl_mat_view_m.matrix)
            , this->index_m);
    return reinterpret_cast<Vector_Complex::Const_View*>(&vector_view_m);
}


Matrix_Complex::View::Const_Column_Iterator::const_reference Matrix_Complex::View::Const_Column_Iterator::operator*()
{
    return gsl_matrix_complex_const_column(
            const_cast<gsl_matrix_complex*>(&this->m_m->gsl_mat_view_m.matrix)
            , this->index_m);
}

Matrix_Complex::View::Const_Column_Iterator::pointer
  Matrix_Complex::View::Const_Column_Iterator::operator->()
{
    this->vector_view_m =
        gsl_matrix_complex_column(
            const_cast<gsl_matrix_complex*>(&this->m_m->gsl_mat_view_m.matrix)
            , this->index_m);
    return reinterpret_cast<Vector_Complex::Const_View*>(&vector_view_m);
}

Matrix_Complex::View::Const_Diagonal_Iterator::const_reference Matrix_Complex::View::Const_Diagonal_Iterator::operator*()
{
    size_t max_dim =
        std::max(this->m_m->gsl_mat_view_m.matrix.size1, this->m_m->gsl_mat_view_m.matrix.size2) ;
    if(this->index_m < max_dim){
        return gsl_matrix_complex_const_subdiagonal(
                const_cast<gsl_matrix_complex*>(&this->m_m->gsl_mat_view_m.matrix)
                , max_dim - this->index_m - 1);
    }else{
        return gsl_matrix_complex_const_superdiagonal(
                const_cast<gsl_matrix_complex*>(&this->m_m->gsl_mat_view_m.matrix)
                , this->index_m % max_dim);
    }
}

Matrix_Complex::View::Const_Diagonal_Iterator::pointer
  Matrix_Complex::View::Const_Diagonal_Iterator::operator->()
{
    size_t max_dim =
        std::max(this->m_m->gsl_mat_view_m.matrix.size1, this->m_m->gsl_mat_view_m.matrix.size2) ;
    if(this->index_m < max_dim){
        this->vector_view_m =
            gsl_matrix_complex_subdiagonal(
                const_cast<gsl_matrix_complex*>(&this->m_m->gsl_mat_view_m.matrix)
                , max_dim - this->index_m - 1);
    }else{
        this->vector_view_m =
            gsl_matrix_complex_superdiagonal(
                const_cast<gsl_matrix_complex*>(&this->m_m->gsl_mat_view_m.matrix)
                , this->index_m % max_dim);
    }
    return reinterpret_cast<Vector_Complex::Const_View*>(&vector_view_m);
}

bool Matrix_Complex::View::Const_Iterator::operator==(const Const_Iterator& other)
{
    return this->index_m == other.index_m;
}

bool Matrix_Complex::View::Const_Iterator::operator!=(const Const_Iterator& other)
{
    return !(*this == other);
}

bool Matrix_Complex::View::Const_Iterator::operator<=(const Const_Iterator& other)
{
    return this->index_m <= other.index_m;
}

bool Matrix_Complex::View::Const_Iterator::operator>=(const Const_Iterator& other)
{
    return this->index_m >= other.index_m;
}

bool Matrix_Complex::View::Const_Iterator::operator<(const Const_Iterator& other)
{
    return !(*this >= other);
}

bool Matrix_Complex::View::Const_Iterator::operator>(const Const_Iterator& other)
{
    return !(*this <= other);
}

/**********************************************************************************************
**********************************************************************************************/


/**********************************************************************************************
* MATRIX VIEW ROW ITERATOR                                                                                                   *
**********************************************************************************************/

Matrix_Complex::View::Row_Iterator::Row_Iterator()
 : Matrix_Complex::View::Iterator()
{}

Matrix_Complex::View::Row_Iterator::Row_Iterator(Matrix_Complex::View* m, size_t i)
 : Matrix_Complex::View::Iterator(m, i)
{}

/**********************************************************************************************
**********************************************************************************************/

/**********************************************************************************************
* MATRIX VIEW CONST_ROW ITERATOR                                                                                      *
**********************************************************************************************/

Matrix_Complex::View::Const_Row_Iterator::Const_Row_Iterator()
 : Matrix_Complex::View::Const_Iterator()
{}

Matrix_Complex::View::Const_Row_Iterator::Const_Row_Iterator(const Matrix_Complex::View* m, size_t i)
 : Matrix_Complex::View::Const_Iterator(m, i)
{}


/**********************************************************************************************
**********************************************************************************************/

/**********************************************************************************************
* MATRIX VIEW COLUMN ITERATOR                                                                                             *
**********************************************************************************************/

Matrix_Complex::View::Column_Iterator::Column_Iterator()
 : Matrix_Complex::View::Iterator()
{}

Matrix_Complex::View::Column_Iterator::Column_Iterator(Matrix_Complex::View* m, size_t i)
 : Matrix_Complex::View::Iterator(m, i)
{}

/**********************************************************************************************
**********************************************************************************************/

/**********************************************************************************************
* MATRIX VIEW CONST_COLUMN ITERATOR                                                                                *
**********************************************************************************************/

Matrix_Complex::View::Const_Column_Iterator::Const_Column_Iterator()
 : Matrix_Complex::View::Const_Iterator()
{}

Matrix_Complex::View::Const_Column_Iterator::Const_Column_Iterator(const Matrix_Complex::View* m, size_t i)
 : Matrix_Complex::View::Const_Iterator(m, i)
{}

/**********************************************************************************************
**********************************************************************************************/


/**********************************************************************************************
* MATRIX VIEW DIAGONAL ITERATOR                                                                                          *
**********************************************************************************************/

Matrix_Complex::View::Diagonal_Iterator::Diagonal_Iterator()
 : Matrix_Complex::View::Iterator()
{}

Matrix_Complex::View::Diagonal_Iterator::Diagonal_Iterator(Matrix_Complex::View* m, size_t i)
 : Matrix_Complex::View::Iterator(m, i)
{}

/**********************************************************************************************
**********************************************************************************************/


/**********************************************************************************************
* MATRIX VIEW CONST DIAGONAL ITERATOR                                                                              *
**********************************************************************************************/

Matrix_Complex::View::Const_Diagonal_Iterator::Const_Diagonal_Iterator()
 : Matrix_Complex::View::Const_Iterator()
{}

Matrix_Complex::View::Const_Diagonal_Iterator::Const_Diagonal_Iterator(const Matrix_Complex::View* m, size_t i)
 : Matrix_Complex::View::Const_Iterator(m, i)
{}

/**********************************************************************************************
**********************************************************************************************/


/**********************************************************************************************
* MATRIX CONST VIEW                                                                                                                *
**********************************************************************************************/

Matrix_Complex::Const_View::Const_View(const Matrix_Complex& m, size_t k1, size_t k2, size_t n1, size_t n2)
 : gsl_mat_view_m(gsl_matrix_complex_const_submatrix(m.gsl_mat_m.get(), k1, k2, n1, n2))
{}

Matrix_Complex::Const_View::Const_View(const GSL::Block& b, size_t n1, size_t n2)
 : Const_View(b, 0, n1, n2)
{}

Matrix_Complex::Const_View::Const_View(const GSL::Block& b, size_t offset, size_t n1, size_t n2)
 : gsl_mat_view_m(gsl_matrix_complex_const_view_array(b.data() + offset, n1, n2))
{}

Matrix_Complex::Const_View::Const_View(const GSL::Block& b, size_t offset, size_t n1, size_t n2, size_t tda)
 : gsl_mat_view_m(gsl_matrix_complex_const_view_array_with_tda(b.data() + offset, n1, n2, tda))
{}

Matrix_Complex::Const_View::Const_View(const double* data, size_t n1, size_t n2)
 : Const_View(data, 0, n1, n2)
{}

Matrix_Complex::Const_View::Const_View(const double* data, size_t offset, size_t n1, size_t n2)
 : gsl_mat_view_m(gsl_matrix_complex_const_view_array(data + offset, n1, n2))
{}

Matrix_Complex::Const_View::Const_View(const double* data, size_t offset, size_t n1, size_t n2, size_t tda)
 : gsl_mat_view_m(gsl_matrix_complex_const_view_array_with_tda(data + offset, n1, n2, tda))
{}

Matrix_Complex::Const_View::Const_View(const Vector_Complex& v, size_t n1, size_t n2)
 : gsl_mat_view_m(gsl_matrix_complex_const_view_vector(v.gsl_data(), n1, n2))
{}

Matrix_Complex::Const_View::Const_View(const Vector_Complex& v, size_t n1, size_t n2, size_t tda)
 : gsl_mat_view_m(gsl_matrix_complex_const_view_vector_with_tda(v.gsl_data(), n1, n2, tda))
{}

size_t Matrix_Complex::Const_View::num_rows() const
{
    return this->gsl_mat_view_m.matrix.size1;
}

size_t Matrix_Complex::Const_View::num_columns() const
{
    return this->gsl_mat_view_m.matrix.size2;
}

std::pair<size_t, size_t> Matrix_Complex::Const_View::dim() const
{
    return {this->gsl_mat_view_m.matrix.size1, this->gsl_mat_view_m.matrix.size2};
}

size_t Matrix_Complex::Const_View::tda() const
{
    return this->gsl_mat_view_m.matrix.tda;
}

Complex Matrix_Complex::Const_View::get(size_t i, size_t j)
{
    return gsl_matrix_complex_get(&this->gsl_mat_view_m.matrix, i, j);
}

bool Matrix_Complex::Const_View::isnull() const
{
    return gsl_matrix_complex_isnull(&this->gsl_mat_view_m.matrix);
}

bool Matrix_Complex::Const_View::ispos() const
{
    return gsl_matrix_complex_ispos(&this->gsl_mat_view_m.matrix);
}

bool Matrix_Complex::Const_View::isneg() const
{
    return gsl_matrix_complex_isneg(&this->gsl_mat_view_m.matrix);
}

bool Matrix_Complex::Const_View::isnonneg() const
{
    return gsl_matrix_complex_isnonneg(&this->gsl_mat_view_m.matrix);
}

Vector_Complex::Const_View Matrix_Complex::Const_View::row(size_t row) const
{
    return gsl_matrix_complex_const_row(&this->gsl_mat_view_m.matrix, row);
}

Vector_Complex::Const_View Matrix_Complex::Const_View::crow(size_t row) const
{
    return gsl_matrix_complex_const_row(&this->gsl_mat_view_m.matrix, row);
}


Vector_Complex::Const_View Matrix_Complex::Const_View::column(size_t column) const
{
    return gsl_matrix_complex_const_column(&this->gsl_mat_view_m.matrix, column);
}

Vector_Complex::Const_View Matrix_Complex::Const_View::ccolumn(size_t column) const
{
    return gsl_matrix_complex_const_column(&this->gsl_mat_view_m.matrix, column);
}


Vector_Complex::Const_View Matrix_Complex::Const_View::subrow(size_t i, size_t offset, size_t n) const
{
    return gsl_matrix_complex_const_subrow(&this->gsl_mat_view_m.matrix, i, offset, n);
}

Vector_Complex::Const_View Matrix_Complex::Const_View::csubrow(size_t i, size_t offset, size_t n) const
{
    return gsl_matrix_complex_const_subrow(&this->gsl_mat_view_m.matrix, i, offset, n);
}

Vector_Complex::Const_View Matrix_Complex::Const_View::subcolumn(size_t i, size_t offset, size_t n) const
{
    return gsl_matrix_complex_const_subcolumn(&this->gsl_mat_view_m.matrix, i, offset, n);
}

Vector_Complex::Const_View Matrix_Complex::Const_View::csubcolumn(size_t i, size_t offset, size_t n) const
{
    return gsl_matrix_complex_const_subcolumn(&this->gsl_mat_view_m.matrix, i, offset, n);
}

Vector_Complex::Const_View Matrix_Complex::Const_View::diagonal() const
{
    return gsl_matrix_complex_const_diagonal(&this->gsl_mat_view_m.matrix);
}

Vector_Complex::Const_View Matrix_Complex::Const_View::cdiagonal() const
{
    return gsl_matrix_complex_const_diagonal(&this->gsl_mat_view_m.matrix);
}

Vector_Complex::Const_View Matrix_Complex::Const_View::subdiagonal(size_t k) const
{
    return gsl_matrix_complex_const_subdiagonal(&this->gsl_mat_view_m.matrix, k);
}

Vector_Complex::Const_View Matrix_Complex::Const_View::csubdiagonal(size_t k) const
{
    return gsl_matrix_complex_const_subdiagonal(&this->gsl_mat_view_m.matrix, k);
}

Vector_Complex::Const_View Matrix_Complex::Const_View::superdiagonal(size_t k) const
{
    return gsl_matrix_complex_const_superdiagonal(&this->gsl_mat_view_m.matrix, k);
}

Vector_Complex::Const_View Matrix_Complex::Const_View::csuperdiagonal(size_t k) const
{
    return gsl_matrix_complex_const_superdiagonal(&this->gsl_mat_view_m.matrix, k);
}

Vector_Complex::Const_View Matrix_Complex::Const_View::operator[](size_t row) const
{
    return gsl_matrix_complex_const_row(&this->gsl_mat_view_m.matrix, row);
}

Vector_Complex::Const_View Matrix_Complex::Const_View::at(size_t row) const
{
    if(!(row < this->gsl_mat_view_m.matrix.size1)){
        throw std::out_of_range("(Row, Column) index (" + std::to_string(row) +
            ", " + std::to_string(row) + ") out of range.");
    }
    return gsl_matrix_complex_const_row(&this->gsl_mat_view_m.matrix, row);
}

const Complex& Matrix_Complex::Const_View::operator()(size_t i, size_t j) const
{
    return *reinterpret_cast<const Complex*>(gsl_matrix_complex_const_ptr(&this->gsl_mat_view_m.matrix, i, j));
}

const Complex& Matrix_Complex::Const_View::at(size_t row, size_t column) const
{
    if(!(row < this->gsl_mat_view_m.matrix.size1) || !(column < this->gsl_mat_view_m.matrix.size2)){
        throw std::out_of_range("(Row, Column) index (" + std::to_string(row) +
            ", " + std::to_string(column) + ") out of range.");
    }
    return (*this)(row, column);
}

Matrix_Complex::Const_View::operator const Matrix_Complex() const
{
    return Matrix_Complex(const_cast<gsl_matrix_complex*>(&this->gsl_mat_view_m.matrix));
}

const gsl_matrix_complex* Matrix_Complex::Const_View::gsl_data() const
{
    return &this->gsl_mat_view_m.matrix;
}

Matrix_Complex::Const_View::const_row_iterator Matrix_Complex::Const_View::rows_begin() const noexcept
{
    return const_row_iterator(this, 0);
}

Matrix_Complex::Const_View::const_row_iterator Matrix_Complex::Const_View::rows_cbegin() const noexcept
{
    return const_row_iterator(this, 0);
}

Matrix_Complex::Const_View::const_row_iterator Matrix_Complex::Const_View::rows_end() const noexcept
{
    return const_row_iterator(this, this->gsl_mat_view_m.matrix.size1);
}

Matrix_Complex::Const_View::const_row_iterator Matrix_Complex::Const_View::rows_cend() const noexcept
{
    return const_row_iterator(this, this->gsl_mat_view_m.matrix.size1);
}

Matrix_Complex::Const_View::const_reverse_row_iterator Matrix_Complex::Const_View::rows_rbegin() const noexcept
{
    return const_reverse_row_iterator(this->rows_end());
}

Matrix_Complex::Const_View::const_reverse_row_iterator Matrix_Complex::Const_View::rows_crbegin() const noexcept
{
    return const_reverse_row_iterator(this->rows_cend());
}

Matrix_Complex::Const_View::const_reverse_row_iterator Matrix_Complex::Const_View::rows_rend() const noexcept
{
    return const_reverse_row_iterator(this->rows_begin());
}

Matrix_Complex::Const_View::const_reverse_row_iterator Matrix_Complex::Const_View::rows_crend() const noexcept
{
    return const_reverse_row_iterator(this->rows_cbegin());
}

Matrix_Complex::Const_View::const_value_type Matrix_Complex::Const_View::rows_front() const
{
    return *this->rows_begin();
}

Matrix_Complex::Const_View::const_value_type Matrix_Complex::Const_View::rows_back() const
{
    return *(--this->rows_end());
}


Matrix_Complex::Const_View::const_column_iterator Matrix_Complex::Const_View::columns_begin() const noexcept
{
    return const_column_iterator(this, 0);
}

Matrix_Complex::Const_View::const_column_iterator Matrix_Complex::Const_View::columns_cbegin() const noexcept
{
    return const_column_iterator(this, 0);
}

Matrix_Complex::Const_View::const_column_iterator Matrix_Complex::Const_View::columns_end() const noexcept
{
    return const_column_iterator(this, this->gsl_mat_view_m.matrix.size2);
}

Matrix_Complex::Const_View::const_column_iterator Matrix_Complex::Const_View::columns_cend() const noexcept
{
    return const_column_iterator(this, this->gsl_mat_view_m.matrix.size2);
}

Matrix_Complex::Const_View::const_reverse_column_iterator Matrix_Complex::Const_View::columns_rbegin() const noexcept
{
    return const_reverse_column_iterator(this->columns_end());
}

Matrix_Complex::Const_View::const_reverse_column_iterator Matrix_Complex::Const_View::columns_crbegin() const noexcept
{
    return const_reverse_column_iterator(this->columns_cend());
}

Matrix_Complex::Const_View::const_reverse_column_iterator Matrix_Complex::Const_View::columns_rend() const noexcept
{
    return const_reverse_column_iterator(this->columns_begin());
}

Matrix_Complex::Const_View::const_reverse_column_iterator Matrix_Complex::Const_View::columns_crend() const noexcept
{
    return const_reverse_column_iterator(this->columns_cbegin());
}

Matrix_Complex::Const_View::const_value_type Matrix_Complex::Const_View::columns_front() const
{
    return *this->columns_begin();
}

Matrix_Complex::Const_View::const_value_type Matrix_Complex::Const_View::columns_back() const
{
    return *(--this->columns_end());
}

Matrix_Complex::Const_View::const_diagonal_iterator Matrix_Complex::Const_View::diagonals_begin() const noexcept
{
    return const_diagonal_iterator(this, 0);
}

Matrix_Complex::Const_View::const_diagonal_iterator Matrix_Complex::Const_View::diagonals_cbegin() const noexcept
{
    return const_diagonal_iterator(this, 0);
}

Matrix_Complex::Const_View::const_diagonal_iterator Matrix_Complex::Const_View::diagonals_end() const noexcept
{
    return const_diagonal_iterator(this, this->gsl_mat_view_m.matrix.size1 + this->gsl_mat_view_m.matrix.size2);
}

Matrix_Complex::Const_View::const_diagonal_iterator Matrix_Complex::Const_View::diagonals_cend() const noexcept
{
    return const_diagonal_iterator(this, this->gsl_mat_view_m.matrix.size1 + this->gsl_mat_view_m.matrix.size2);
}

Matrix_Complex::Const_View::const_reverse_diagonal_iterator Matrix_Complex::Const_View::diagonals_rbegin() const noexcept
{
    return const_reverse_diagonal_iterator(this->diagonals_end());
}

Matrix_Complex::Const_View::const_reverse_diagonal_iterator Matrix_Complex::Const_View::diagonals_crbegin() const noexcept
{
    return const_reverse_diagonal_iterator(this->diagonals_cend());
}

Matrix_Complex::Const_View::const_reverse_diagonal_iterator Matrix_Complex::Const_View::diagonals_rend() const noexcept
{
    return const_reverse_diagonal_iterator(this->diagonals_begin());
}

Matrix_Complex::Const_View::const_reverse_diagonal_iterator Matrix_Complex::Const_View::diagonals_crend() const noexcept
{
    return const_reverse_diagonal_iterator(this->diagonals_cbegin());
}

Matrix_Complex::Const_View::const_value_type Matrix_Complex::Const_View::diagonals_front() const
{
    return *this->diagonals_begin();
}

Matrix_Complex::Const_View::const_value_type Matrix_Complex::Const_View::diagonals_back() const
{
    return *(--this->diagonals_end());
}

/**********************************************************************************************
**********************************************************************************************/


/**********************************************************************************************
* MATRIX CONST VIEW CONST ITERATOR                                                                                    *
**********************************************************************************************/

Matrix_Complex::Const_View::Const_Iterator::Const_Iterator()
 : m_m(nullptr), vector_view_m(nullptr, 0), index_m()
{}

Matrix_Complex::Const_View::Const_Iterator::Const_Iterator(const Matrix_Complex::Const_View* m, size_t i)
 : m_m(m), vector_view_m(nullptr, 0), index_m(i)
{}

Matrix_Complex::Const_View::Const_Row_Iterator::pointer Matrix_Complex::Const_View::Const_Row_Iterator::operator->()
{
    this->vector_view_m =
        gsl_matrix_complex_row(
            const_cast<gsl_matrix_complex*>(&this->m_m->gsl_mat_view_m.matrix)
            , this->index_m);
    return reinterpret_cast<Vector_Complex::Const_View*>(&vector_view_m);
}

Matrix_Complex::Const_View::Const_Row_Iterator::const_reference Matrix_Complex::Const_View::Const_Row_Iterator::operator*()
{
    return gsl_matrix_complex_const_row(
            const_cast<gsl_matrix_complex*>(&this->m_m->gsl_mat_view_m.matrix)
            , this->index_m);
}

Matrix_Complex::Const_View::Const_Column_Iterator::pointer Matrix_Complex::Const_View::Const_Column_Iterator::operator->()
{
    this->vector_view_m =
        gsl_matrix_complex_column(
            const_cast<gsl_matrix_complex*>(&this->m_m->gsl_mat_view_m.matrix)
            , this->index_m);
return reinterpret_cast<Vector_Complex::Const_View*>(&vector_view_m);
}

Matrix_Complex::Const_View::Const_Column_Iterator::const_reference Matrix_Complex::Const_View::Const_Column_Iterator::operator*()
{
    return gsl_matrix_complex_const_column(
            const_cast<gsl_matrix_complex*>(&this->m_m->gsl_mat_view_m.matrix)
            , this->index_m);
}

Matrix_Complex::Const_View::Const_Diagonal_Iterator::pointer Matrix_Complex::Const_View::Const_Diagonal_Iterator::operator->()
{
    size_t max_dim =
        std::max(this->m_m->gsl_mat_view_m.matrix.size1, this->m_m->gsl_mat_view_m.matrix.size2) ;
    if(this->index_m < max_dim){
        this->vector_view_m =
            gsl_matrix_complex_subdiagonal(
                const_cast<gsl_matrix_complex*>(&this->m_m->gsl_mat_view_m.matrix)
                , max_dim - this->index_m - 1);
    }else{
        this->vector_view_m =
            gsl_matrix_complex_superdiagonal(
                const_cast<gsl_matrix_complex*>(&this->m_m->gsl_mat_view_m.matrix)
                , this->index_m % max_dim);
    }
    return reinterpret_cast<Vector_Complex::Const_View*>(&vector_view_m);
}

Matrix_Complex::Const_View::Const_Diagonal_Iterator::const_reference Matrix_Complex::Const_View::Const_Diagonal_Iterator::operator*()
{
    size_t max_dim =
        std::max(this->m_m->gsl_mat_view_m.matrix.size1, this->m_m->gsl_mat_view_m.matrix.size2) ;
    if(this->index_m < max_dim){
        return gsl_matrix_complex_const_subdiagonal(
                const_cast<gsl_matrix_complex*>(&this->m_m->gsl_mat_view_m.matrix)
                , max_dim - this->index_m - 1);
    }else{
        return gsl_matrix_complex_const_superdiagonal(
                const_cast<gsl_matrix_complex*>(&this->m_m->gsl_mat_view_m.matrix)
                , this->index_m % max_dim);
    }
}

Matrix_Complex::Const_View::Const_Row_Iterator::difference_type
  Matrix_Complex::Const_View::Const_Row_Iterator::operator-(Const_Row_Iterator const& other)
{
    return this->index_m - other.index_m;
}

Matrix_Complex::Const_View::Const_Column_Iterator::difference_type
  Matrix_Complex::Const_View::Const_Column_Iterator::operator-(Const_Column_Iterator const& other)
{
    return this->index_m - other.index_m;
}

Matrix_Complex::Const_View::Const_Diagonal_Iterator::difference_type
  Matrix_Complex::Const_View::Const_Diagonal_Iterator::operator-(Const_Diagonal_Iterator const& other)
{
    return this->index_m - other.index_m;
}

bool Matrix_Complex::Const_View::Const_Iterator::operator==(const Const_Iterator& other)
{
    return this->index_m == other.index_m;
}

bool Matrix_Complex::Const_View::Const_Iterator::operator!=(const Const_Iterator& other)
{
    return !(*this == other);
}

bool Matrix_Complex::Const_View::Const_Iterator::operator<=(const Const_Iterator& other)
{
    return this->index_m <= other.index_m;
}

bool Matrix_Complex::Const_View::Const_Iterator::operator>=(const Const_Iterator& other)
{
    return this->index_m >= other.index_m;
}

bool Matrix_Complex::Const_View::Const_Iterator::operator<(const Const_Iterator& other)
{
    return !(*this >= other);
}

bool Matrix_Complex::Const_View::Const_Iterator::operator>(const Const_Iterator& other)
{
    return !(*this <= other);
}

/**********************************************************************************************
**********************************************************************************************/


/**********************************************************************************************
* MATRIX CONST VIEW  CONST ROW ITERATOR                                                                          *
**********************************************************************************************/

Matrix_Complex::Const_View::Const_Row_Iterator::Const_Row_Iterator()
 : Matrix_Complex::Const_View::Const_Iterator()
{}

Matrix_Complex::Const_View::Const_Row_Iterator::Const_Row_Iterator(const Matrix_Complex::Const_View* m, size_t i)
 : Matrix_Complex::Const_View::Const_Iterator(m, i)
{}
/**********************************************************************************************
**********************************************************************************************/


/**********************************************************************************************
* MATRIX CONST VIEW  CONST COLUMN ITERATOR                                                                    *
**********************************************************************************************/

Matrix_Complex::Const_View::Const_Column_Iterator::Const_Column_Iterator()
 : Matrix_Complex::Const_View::Const_Iterator()
{}

Matrix_Complex::Const_View::Const_Column_Iterator::Const_Column_Iterator(const Matrix_Complex::Const_View* m, size_t i)
 : Matrix_Complex::Const_View::Const_Iterator(m, i)
{}
/**********************************************************************************************
**********************************************************************************************/


/**********************************************************************************************
* MATRIX CONST VIEW  CONST DIAGONAL ITERATOR                                                                 *
**********************************************************************************************/

Matrix_Complex::Const_View::Const_Diagonal_Iterator::Const_Diagonal_Iterator()
 : Matrix_Complex::Const_View::Const_Iterator()
{}

Matrix_Complex::Const_View::Const_Diagonal_Iterator::Const_Diagonal_Iterator(const Matrix_Complex::Const_View* m, size_t i)
 : Matrix_Complex::Const_View::Const_Iterator(m, i)
{}
/**********************************************************************************************
**********************************************************************************************/

#if 0
 int main()
{
    Block b(16);

    Matrix_Complex m(2, 2, 0);
    m(0, 0) = 0;
    m(0, 1) = 5;
    m(1, 1) = 2;
    /********************************************************************************************
    *  m = [ 0  5 ]                                                                                                                          *
    *         [ 0  1 ]                                                                                                                           *
    ********************************************************************************************/
    Vector_Complex v(4, 4);
    /********************************************************************************************
    * v = [ 4 4 4 4 ]                                                                                                                       *
    ********************************************************************************************/
    Matrix_Complex::View bv(b, 4, 4);
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
        row = Vector_Complex(3, i++);
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
