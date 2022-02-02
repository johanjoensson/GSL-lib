#include "GSLpp/vector_complex.h"
#include "GSLpp/block.h"
#include <gsl/gsl_blas.h>
#include <algorithm>

using namespace GSL;

/**********************************************************************************************
* VECTOR                                                                                                                                    *
**********************************************************************************************/

Vector_Complex::Vector_Complex(size_t n)
 : gsl_vec_m(gsl_vector_complex_alloc(n), gsl_vector_complex_free)
{}

Vector_Complex::Vector_Complex(size_t n, Complex val)
 : gsl_vec_m(gsl_vector_complex_alloc(n), gsl_vector_complex_free)
{
    gsl_vector_complex_set_all(this->gsl_vec_m.get(), val);
}

Vector_Complex::Vector_Complex(std::initializer_list<Complex> l)
 : Vector_Complex(l.size())
{
    std::transform(l.begin(), l.end(), this->view().begin(),
        [](const Complex& c)
        {
            return c;
        });
}


Vector_Complex::Vector_Complex(gsl_vector_complex* v)
 : gsl_vec_m(v, [](gsl_vector_complex*){})
{}

gsl_vector_complex* Vector_Complex::gsl_data()
{
    return gsl_vec_m.get();
}

const gsl_vector_complex* Vector_Complex::gsl_data() const
{
    return gsl_vec_m.get();
}

void Vector_Complex::copy(const Vector_Complex& other)
{
    gsl_vector_complex_memcpy(this->gsl_vec_m.get(), other.gsl_vec_m.get());
}

void Vector_Complex::swap(Vector_Complex& other)
{
    gsl_vector_complex_swap(this->gsl_vec_m.get(), other.gsl_vec_m.get());
}

void Vector_Complex::swap_elements(size_t i, size_t j)
{
    gsl_vector_complex_swap_elements(this->gsl_vec_m.get(), i, j);
}

void Vector_Complex::reverse()
{
    gsl_vector_complex_reverse(this->gsl_vec_m.get());
}

Vector_Complex Vector_Complex::clone() const
{
    Vector_Complex res(this->gsl_vec_m->size);
    res.copy(*this);
    return res;
}

size_t Vector_Complex::size() const
{
    return this->gsl_vec_m->size;
}

void Vector_Complex::set_all(Complex val)
{
    gsl_vector_complex_set_all(this->gsl_vec_m.get(), val);
}

void Vector_Complex::set_zero()
{
    gsl_vector_complex_set_zero(this->gsl_vec_m.get());
}

void Vector_Complex::set_basis(size_t i)
{
    gsl_vector_complex_set_basis(this->gsl_vec_m.get(), i);
}

void Vector_Complex::set(size_t i, Complex val)
{
    gsl_vector_complex_set(this->gsl_vec_m.get(), i, val);
}

Complex Vector_Complex::get(size_t i) const
{
    return gsl_vector_complex_get(this->gsl_vec_m.get(), i);
}

Complex& Vector_Complex::operator[](const size_t i)
{
    return *reinterpret_cast<Complex*>(gsl_vector_complex_ptr(this->gsl_vec_m.get(), i));
}

const Complex& Vector_Complex::operator[](const size_t i) const
{
    return *reinterpret_cast<Complex*>(gsl_vector_complex_ptr(this->gsl_vec_m.get(), i));
}

Complex& Vector_Complex::at(const size_t i)
{
    if(!(i < this->size())){
        throw std::out_of_range("Index " + std::to_string(i) + " out of range.");
    }
    return (*this)[i];
}

const Complex& Vector_Complex::at(const size_t i) const
{
    if(!(i < this->size())){
        throw std::out_of_range("Index " + std::to_string(i) + " out of range.");
    }
    return (*this)[i];
}

Vector_Complex& Vector_Complex::conjugate()
{
    std::transform(this->imag().view().begin(), this->imag().view().end(), this->imag().begin(),
        [](double i)
        {
            return -i;
        });
    return *this;
}

Vector_Complex& Vector_Complex::operator+=(const Vector_Complex& other)
{
    gsl_vector_complex_add(this->gsl_vec_m.get(), other.gsl_vec_m.get());
    return *this;
}

Vector_Complex& Vector_Complex::operator-=(Complex s)
{
    return *this += -s;
}

Vector_Complex& Vector_Complex::operator-=(const Vector_Complex& other)
{
    gsl_vector_complex_sub(this->gsl_vec_m.get(), other.gsl_vec_m.get());
    return *this;
}

Vector_Complex& Vector_Complex::operator*=(const Vector_Complex& other)
{
    gsl_vector_complex_mul(this->gsl_vec_m.get(), other.gsl_vec_m.get());
    return *this;
}

Vector_Complex& Vector_Complex::operator/=(const Vector_Complex& other)
{
    gsl_vector_complex_div(this->gsl_vec_m.get(), other.gsl_vec_m.get());
    return *this;
}

Vector_Complex& Vector_Complex::operator+=(const Vector& other)
{
    Vector::View v = this->real();
    v += other;
    return *this;
}

Vector_Complex& Vector_Complex::operator-=(const Vector& other)
{
    Vector::View v = this->real();
    v -= other;
    return *this;
}

Vector_Complex& Vector_Complex::operator*=(const Vector& other)
{
    Vector::View v = this->real();
    v *= other;
    return *this;
}

Vector_Complex& Vector_Complex::operator/=(const Vector& other)
{
    Vector::View v = this->real();
    v /= other;
    return *this;
}

Vector_Complex& Vector_Complex::operator/=(Complex s)
{
    return *this *= 1/s;
}

Vector_Complex Vector_Complex::operator-() const
{
    Vector_Complex res(this->size(), Complex(0));
    res -= *this;
    return res;
}

Vector_Complex& Vector_Complex::operator+=(Complex s)
{
    gsl_vector_complex_add_constant(this->gsl_vec_m.get(), s);
    return *this;
}

Vector_Complex& Vector_Complex::operator*=(Complex s)
{
    gsl_vector_complex_scale(this->gsl_vec_m.get(), s);
    return *this;
}

Vector_Complex GSL::operator+(const Vector_Complex& a, const Vector_Complex& b)
{
    Vector_Complex result{a.clone()};
    result += b;
    return result;
}

Vector_Complex GSL::operator-(const Vector_Complex& a, const Vector_Complex& b)
{
    Vector_Complex result{a.clone()};
    result -= b;
    return result;
}

Vector_Complex GSL::operator*(const Vector_Complex& a, const Vector_Complex& b)
{
    Vector_Complex result{a.clone()};
    result *= b;
    return result;
}

Vector_Complex GSL::operator/(const Vector_Complex& a, const Vector_Complex& b)
{
    Vector_Complex result{a.clone()};
    result /= b;
    return result;
}

Vector_Complex GSL::operator+(const Vector_Complex& a, const Vector& b)
{
    Vector_Complex result{a.clone()};
    Vector::View result_real = result.real();
    result_real += b;
    return result;
}

Vector_Complex GSL::operator+(const Vector& a, const Vector_Complex& b)
{
    return b  + a;
}

Vector_Complex GSL::operator-(const Vector_Complex& a, const Vector& b)
{
    Vector_Complex result{a.clone()};
    Vector::View result_real = result.real();
    result_real -= b;
    return result;
}

Vector_Complex GSL::operator-(const Vector& a, const Vector_Complex& b)
{
    return -(b  - a);
}

Vector_Complex GSL::operator*(const Vector_Complex& a, const Vector& b)
{
    Vector_Complex result{a.clone()};
    Vector::View result_real = result.real();
    result_real *= b;
    return result;
}

Vector_Complex GSL::operator*(const Vector& a, const Vector_Complex& b)
{
    return b*a;
}

Vector_Complex GSL::operator/(const Vector_Complex& a, const Vector& b)
{
    Vector_Complex result{a.clone()};
    Vector::View result_real = result.real();
    Vector::View result_imag = result.imag();
    result_real /= b;
    result_imag /= b;
    return result;
}

Vector_Complex GSL::operator/(const Vector& a, const Vector_Complex& b)
{
    Vector_Complex result{b.clone()};
    std::transform(a.view().begin(), a.view().end(), b.view().begin(), result.view().begin(),
        [](double a_i, const GSL::Complex& b_i)
        {
            return a_i*b_i.conjugate()/b_i.abs2();
        });

    return result;
}

Vector_Complex GSL::operator+(const Vector_Complex& a, Complex s)
{
    Vector_Complex result{a.clone()};
    result += s;
    return result;
}

Vector_Complex GSL::operator+(Complex s, const Vector_Complex& a)
{
    return a + s;
}

Vector_Complex GSL::operator-(const Vector_Complex& a, Complex s)
{
    Vector_Complex result{a.clone()};
    result -= s;
    return result;
}
Vector_Complex GSL::operator-(Complex s, const Vector_Complex& a)
{
    return a - s;
}

Vector_Complex GSL::operator*(const Vector_Complex& a, Complex s)
{
    Vector_Complex result{a.clone()};
    result *= s;
    return result;
}

Vector_Complex GSL::operator*(Complex s, const Vector_Complex& a)
{
    return a*s;
}

Vector_Complex GSL::operator/(const Vector_Complex& a, Complex s)
{
    Vector_Complex result{a.clone()};
    result /= s;
    return result;
}

/*
double Vector_Complex::max() const
{
    return gsl_vector_complex_max(this->gsl_vec_m.get());
}

double Vector_Complex::min() const
{
    return gsl_vector_complex_min(this->gsl_vec_m.get());
}

std::pair<double, double> Vector_Complex::minmax() const
{
    std::pair<double, double> res;
    gsl_vector_complex_minmax(this->gsl_vec_m.get(), &res.first, &res.second);
    return res;
}

size_t Vector_Complex::max_index() const
{
    return gsl_vector_complex_max_index(this->gsl_vec_m.get());
}
size_t Vector_Complex::min_index() const
{
    return gsl_vector_complex_min_index(this->gsl_vec_m.get());
}
std::pair<size_t, size_t> Vector_Complex::minmax_index() const
{
    std::pair<size_t, size_t> res;
    gsl_vector_complex_minmax_index(this->gsl_vec_m.get(), &res.first, &res.second);
    return res;
}
*/

bool Vector_Complex::isnull() const
{
    return gsl_vector_complex_isnull(this->gsl_vec_m.get());
}

bool Vector_Complex::ispos() const
{
    return gsl_vector_complex_ispos(this->gsl_vec_m.get());
}

bool Vector_Complex::isneg() const
{
    return gsl_vector_complex_isneg(this->gsl_vec_m.get());
}

bool Vector_Complex::isnonneg() const
{
    return gsl_vector_complex_isnonneg(this->gsl_vec_m.get());
}

double Vector_Complex::norm() const
{
    return ::norm(*this);
}

double Vector_Complex::l1_norm() const
{
    return ::l1_norm(*this);
}

double Vector_Complex::norm2() const
{
    return ::norm2(*this);
}

bool GSL::operator==(const Vector_Complex& a, const Vector_Complex& b)
{
    return gsl_vector_complex_equal(a.gsl_vec_m.get(), b.gsl_vec_m.get());
}

bool GSL::operator!=(const Vector_Complex& a, const Vector_Complex& b)
{return !(a == b);}

std::string Vector_Complex::to_string() const
{
    std::string res = "(";
    for(const auto elem : this->cview()){
        res += std::to_string(elem) + "  ";
    }
    res += ")";
    return res;
}

Vector_Complex GSL::zeros_complex(size_t n)
{
    return Vector_Complex(n, Complex(0));
}

Vector_Complex GSL::unit_complex(size_t n, size_t i)
{
    Vector_Complex res(n);
    res.set_basis(i);
    return res;
}

Complex GSL::dotc(const Vector_Complex& a, const Vector_Complex& b)
{
    gsl_complex res;
    gsl_blas_zdotc(a.gsl_vec_m.get(), b.gsl_vec_m.get(), &res);
    return res;
}

Complex GSL::dotu(const Vector_Complex& a, const Vector_Complex& b)
{
    gsl_complex res;
    gsl_blas_zdotu(a.gsl_vec_m.get(), b.gsl_vec_m.get(), &res);
    return res;
}

Vector_Complex GSL::cross(const Vector_Complex& a, const Vector_Complex& b)
{
    Vector_Complex res(3);
    res[0] = a[1]*b[2] - a[2]*b[1];
    res[1] = a[2]*b[0] - a[0]*b[2];
    res[2] = a[0]*b[1] - a[1]*b[0];
    return res;
}

double GSL::norm(const Vector_Complex& a)
{
    return gsl_blas_dznrm2(a.gsl_vec_m.get());
}

double GSL::norm2(const Vector_Complex& a)
{
    return dot(a, a).real();
}

double GSL::l1_norm(const Vector_Complex& a)
{
    return gsl_blas_dzasum(a.gsl_vec_m.get());
}

Vector_Complex GSL::normalize(const Vector_Complex& a)
{
    return a/Complex(norm(a));
}

Vector_Complex GSL::mirror(const Vector_Complex& v, const Vector_Complex& a)
{
    return v - 2*dot(v, a)*a/Complex(norm2(a));
}

Vector_Complex::View Vector_Complex::view()
{
    return View(*this, 0, this->size());
}

const Vector_Complex::View Vector_Complex::view() const
{
    return View(*this, 0, this->size());
}

Vector_Complex::View Vector_Complex::view(const size_t offset, const size_t size)
{
    return View(*this, offset, size);
}

const Vector_Complex::View Vector_Complex::view(const size_t offset, const size_t size) const
{
    return View(*this, offset, size);
}

Vector_Complex::View Vector_Complex::view(const size_t offset, const size_t stride, const size_t size)
{
    return View(*this, offset, stride, size);
}

const Vector_Complex::View Vector_Complex::view(const size_t offset, const size_t stride, const size_t size) const
{
    return View(*this, offset, stride, size);
}

Vector_Complex::Const_View Vector_Complex::cview() const
{
    return Const_View(*this, 0, this->size());
}

Vector_Complex::Const_View Vector_Complex::cview(const size_t offset, const size_t size) const
{
    return Const_View(*this, offset, size);
}

Vector_Complex::Const_View Vector_Complex::cview(const size_t offset, const size_t stride, const size_t size) const
{
    return Const_View(*this, offset, stride, size);
}

Vector::View Vector_Complex::real()
{
    return Vector::View(gsl_vector_complex_real(this->gsl_vec_m.get()));
}

Vector::Const_View Vector_Complex::real() const
{
    return Vector::Const_View(gsl_vector_complex_const_real(this->gsl_vec_m.get()));
}

Vector::View Vector_Complex::imag()
{
    return Vector::View(gsl_vector_complex_imag(this->gsl_vec_m.get()));
}

Vector::Const_View Vector_Complex::imag() const
{
    return Vector::Const_View(gsl_vector_complex_const_imag(this->gsl_vec_m.get()));
}

std::ostream& GSL::operator<<(std::ostream& os, const Vector_Complex& v)
{
    return os << v.to_string();
}

/**********************************************************************************************
**********************************************************************************************/


/**********************************************************************************************
* VECTOR VIEW                                                                                                                           *
**********************************************************************************************/

Vector_Complex::View::View(const Vector_Complex& v)
 : View(v ,0, v.size())
{}

Vector_Complex::View::View(const Vector_Complex& v, size_t offset, size_t size)
 : gsl_vec_view_m(gsl_vector_complex_subvector(v.gsl_vec_m.get(), offset, size))
{}

Vector_Complex::View::View(const Vector_Complex& v, size_t offset, size_t stride, size_t size)
 : gsl_vec_view_m(gsl_vector_complex_subvector_with_stride(v.gsl_vec_m.get(), offset, stride, size))
{}

Vector_Complex::View::View(Block& b)
 : View(b, 0, b.size())
{}

Vector_Complex::View::View(Block& b, size_t offset, size_t size)
 : gsl_vec_view_m(gsl_vector_complex_view_array(b.data() + offset, size))
{}

Vector_Complex::View::View(Block& b, size_t offset, size_t stride, size_t size)
 : gsl_vec_view_m(gsl_vector_complex_view_array_with_stride(b.data() + offset, stride, size))
{}

Vector_Complex::View::View(double* data, size_t size)
 : View(data, 0, size)
{}

Vector_Complex::View::View(double* data, size_t offset, size_t size)
 : gsl_vec_view_m(gsl_vector_complex_view_array(data + offset, size))
{}

Vector_Complex::View::View(double* data, size_t offset, size_t stride, size_t size)
 : gsl_vec_view_m(gsl_vector_complex_view_array_with_stride(data + offset, stride, size))
{}

Vector_Complex::View::View(gsl_vector_complex_view v)
 : gsl_vec_view_m(v)
{}

Vector_Complex::View::operator Vector_Complex()
{
    return Vector_Complex(&this->gsl_vec_view_m.vector);
}

Vector_Complex::View::operator const Vector_Complex() const
{
    return Vector_Complex(const_cast<gsl_vector_complex*>(&this->gsl_vec_view_m.vector));
}

gsl_vector_complex* Vector_Complex::View::gsl_data()
{
    return &this->gsl_vec_view_m.vector;
}

const gsl_vector_complex* Vector_Complex::View::gsl_data() const
{
    return &this->gsl_vec_view_m.vector;
}

size_t Vector_Complex::View::size() const
{
    return this->gsl_vec_view_m.vector.size;
}

size_t Vector_Complex::View::stride() const
{
    return this->gsl_vec_view_m.vector.stride;
}

Complex& Vector_Complex::View::operator[](const size_t i)
{
    return *reinterpret_cast<Complex*>(gsl_vector_complex_ptr(&gsl_vec_view_m.vector, i));
}

const Complex& Vector_Complex::View::operator[](const size_t i) const
{
    return *reinterpret_cast<const Complex*>(gsl_vector_complex_const_ptr(&gsl_vec_view_m.vector, i));
}

Complex& Vector_Complex::View::at(const size_t i)
{
    if(!(i < this->size())){
        throw std::out_of_range("Index " + std::to_string(i) + " out of range.");
    }
    return (*this)[i];
}

const Complex& Vector_Complex::View::at(const size_t i) const
{
    if(!(i < this->size())){
        throw std::out_of_range("Index " + std::to_string(i) + " out of range.");
    }
    return (*this)[i];
}

Vector_Complex::View& Vector_Complex::View::swap(Vector_Complex& v)
{
    gsl_vector_complex_swap(&this->gsl_vec_view_m.vector, v.gsl_vec_m.get());
    return *this;
}
Vector_Complex::View& Vector_Complex::View::swap(View& vv)
{
    gsl_vector_complex_swap(&this->gsl_vec_view_m.vector, &vv.gsl_vec_view_m.vector);
    return *this;
}

Vector_Complex::View& Vector_Complex::View::swap(Vector_Complex&& v)
{
    gsl_vector_complex_swap(&this->gsl_vec_view_m.vector, v.gsl_vec_m.get());
    return *this;
}
Vector_Complex::View& Vector_Complex::View::swap(View&& vv)
{
    gsl_vector_complex_swap(&this->gsl_vec_view_m.vector, &vv.gsl_vec_view_m.vector);
    return *this;
}

Vector_Complex::View& Vector_Complex::View::copy(const View& vv)
{
    gsl_vector_complex_memcpy(&this->gsl_vec_view_m.vector, &vv.gsl_vec_view_m.vector);
    return *this;
}

Vector_Complex::View& Vector_Complex::View::copy(View&& vv)
{
    gsl_vector_complex_swap(&this->gsl_vec_view_m.vector, &vv.gsl_vec_view_m.vector);
    return *this;
}

Vector_Complex::View& Vector_Complex::View::copy(const Vector_Complex& vv)
{
    gsl_vector_complex_memcpy(&this->gsl_vec_view_m.vector, vv.gsl_vec_m.get());
    return *this;
}

Vector_Complex::View& Vector_Complex::View::copy(Vector_Complex&& vv)
{
    gsl_vector_complex_swap(&this->gsl_vec_view_m.vector, vv.gsl_vec_m.get());
    return *this;
}


Vector_Complex::View& Vector_Complex::View::swap_elements(size_t i, size_t j)
{
    gsl_vector_complex_swap_elements(&this->gsl_vec_view_m.vector, i, j);
    return *this;
}

Vector_Complex::View& Vector_Complex::View::reverse()
{
    gsl_vector_complex_reverse(&this->gsl_vec_view_m.vector);
    return *this;
}

Vector_Complex Vector_Complex::View::clone() const
{
    Vector_Complex res(this->size());
    gsl_vector_complex_memcpy(res.gsl_vec_m.get(), &this->gsl_vec_view_m.vector);
    return res;
}

Vector_Complex::View& Vector_Complex::View::set_all(Complex val)
{
        gsl_vector_complex_set_all(&this->gsl_vec_view_m.vector, val);
        return *this;
}

Vector_Complex::View& Vector_Complex::View::set_zero()
{
        gsl_vector_complex_set_zero(&this->gsl_vec_view_m.vector);
        return *this;
}

Vector_Complex::View& Vector_Complex::View::set(size_t i, Complex val)
{
    gsl_vector_complex_set(&this->gsl_vec_view_m.vector, i, val);
    return *this;
}

Vector_Complex::View& Vector_Complex::View::set_basis(size_t i)
{
    gsl_vector_complex_set_basis(&this->gsl_vec_view_m.vector, i);
    return *this;
}

Complex Vector_Complex::View::get(size_t i) const
{
    return gsl_vector_complex_get(&this->gsl_vec_view_m.vector, i);
}

/*
double Vector_Complex::View::max() const
{
        return gsl_vector_complex_max(&this->gsl_vec_view_m.vector);
}


double Vector_Complex::View::min() const
{
    return gsl_vector_complex_min(&this->gsl_vec_view_m.vector);
}

std::pair<double, double> Vector_Complex::View::minmax() const
{
    std::pair<double, double> res;
    gsl_vector_complex_minmax(&this->gsl_vec_view_m.vector, &res.first, &res.second);
    return res;
}

size_t Vector_Complex::View::max_index() const
{
    return gsl_vector_complex_min_index(&this->gsl_vec_view_m.vector);
}

size_t Vector_Complex::View::min_index() const
{
    return gsl_vector_complex_max_index(&this->gsl_vec_view_m.vector);
}
std::pair<size_t, size_t> Vector_Complex::View::minmax_index() const
{
    std::pair<size_t, size_t> res;
    gsl_vector_complex_minmax_index(&this->gsl_vec_view_m.vector, &res.first, &res.second);
    return res;
}
*/

bool Vector_Complex::View::isnull() const
{
    return gsl_vector_complex_isnull(&this->gsl_vec_view_m.vector);
}

bool Vector_Complex::View::ispos() const
{
    return gsl_vector_complex_ispos(&this->gsl_vec_view_m.vector);
}

bool Vector_Complex::View::isneg() const
{
        return gsl_vector_complex_isneg(&this->gsl_vec_view_m.vector);
}

bool Vector_Complex::View::isnonneg() const
{
    return gsl_vector_complex_isnonneg(&this->gsl_vec_view_m.vector);
}

double Vector_Complex::View::norm() const
{
    return ::norm(*this);
}

double Vector_Complex::View::norm2() const
{
    return ::norm2(*this);
}

double Vector_Complex::View::l1_norm() const
{
    return ::l1_norm(*this);
}

Vector_Complex::View& Vector_Complex::View::operator=(const Vector_Complex& v)
{
    return this->copy(v);
}

Vector_Complex::View& Vector_Complex::View::operator=(Vector_Complex&& v)
{
    return this->swap(v);
}

Vector_Complex::View& Vector_Complex::View::conjugate()
{
    std::transform(this->imag().view().begin(), this->imag().view().end(), this->imag().begin(),
        [](double i)
        {
            return -i;
        });
    return *this;
}

Vector_Complex::View& Vector_Complex::View::operator+=(const Vector_Complex& other)
{
    gsl_vector_complex_add(&this->gsl_vec_view_m.vector, other.gsl_vec_m.get());
    return *this;
}

Vector_Complex::View& Vector_Complex::View::operator-=(const Vector_Complex& other)
{
    gsl_vector_complex_sub(&this->gsl_vec_view_m.vector, other.gsl_vec_m.get());
    return *this;
}

Vector_Complex::View& Vector_Complex::View::operator*=(const Vector_Complex& other)
{
    gsl_vector_complex_mul(&this->gsl_vec_view_m.vector, other.gsl_vec_m.get());
    return *this;
}

Vector_Complex::View& Vector_Complex::View::operator/=(const Vector_Complex& other)
{
    gsl_vector_complex_div(&this->gsl_vec_view_m.vector, other.gsl_vec_m.get());
    return *this;
}

Vector_Complex::View& Vector_Complex::View::operator+=(const Vector& other)
{
    Vector::View v = this->real();
    v += other;
    return *this;
}

Vector_Complex::View& Vector_Complex::View::operator-=(const Vector& other)
{
    Vector::View v = this->real();
    v -= other;
    return *this;
}

Vector_Complex::View& Vector_Complex::View::operator*=(const Vector& other)
{
    Vector::View v = this->real();
    v *= other;
    return *this;
}

Vector_Complex::View& Vector_Complex::View::operator/=(const Vector& other)
{
    Vector::View v = this->real();
    v /= other;
    return *this;
}

Vector_Complex::View& Vector_Complex::View::operator+=(Complex s)
{
    gsl_vector_complex_add_constant(&this->gsl_vec_view_m.vector, s);
    return *this;
}

Vector_Complex::View& Vector_Complex::View::operator-=(Complex s)
{
    gsl_vector_complex_add_constant(&this->gsl_vec_view_m.vector, -s);
    return *this;
}

Vector_Complex::View& Vector_Complex::View::operator*=(Complex s)
{
    gsl_vector_complex_scale(&this->gsl_vec_view_m.vector, s);
    return *this;
}

Vector_Complex::View& Vector_Complex::View::operator/=(Complex s)
{
    gsl_vector_complex_scale(&this->gsl_vec_view_m.vector, 1/s);
    return *this;
}

Vector::View Vector_Complex::View::real()
{
    return Vector::View(gsl_vector_complex_real(&this->gsl_vec_view_m.vector));
}

Vector::Const_View Vector_Complex::View::real() const
{
    return Vector::Const_View(gsl_vector_complex_const_real(&this->gsl_vec_view_m.vector));
}

Vector::View Vector_Complex::View::imag()
{
    return Vector::View(gsl_vector_complex_imag(&this->gsl_vec_view_m.vector));
}

Vector::Const_View Vector_Complex::View::imag() const
{
    return Vector::Const_View(gsl_vector_complex_const_imag(&this->gsl_vec_view_m.vector));
}

Vector_Complex Vector_Complex::View::operator-() const
{
    Vector_Complex result(this->size(), Complex{0,0});
    result -= *this;
    return result;
}

Vector_Complex::View Vector_Complex::View::view()
{
    return gsl_vector_complex_subvector(&this->gsl_vec_view_m.vector, 0,  this->size());
}

Vector_Complex::Const_View Vector_Complex::View::view() const
{
    return gsl_vector_complex_const_subvector(&this->gsl_vec_view_m.vector, 0,  this->size());
}

Vector_Complex::View Vector_Complex::View::view(const size_t offset, const size_t size)
{
    return gsl_vector_complex_subvector(&this->gsl_vec_view_m.vector, offset,  size);
}

Vector_Complex::Const_View Vector_Complex::View::view(const size_t offset, const size_t size) const
{
    return gsl_vector_complex_const_subvector(&this->gsl_vec_view_m.vector, offset,  size);
}

Vector_Complex::View Vector_Complex::View::view(const size_t offset, const size_t stride, const size_t size)
{
    return gsl_vector_complex_subvector_with_stride(&this->gsl_vec_view_m.vector, offset, stride, size);
}

Vector_Complex::Const_View Vector_Complex::View::view(const size_t offset, const size_t stride, const size_t size) const
{
    return gsl_vector_complex_const_subvector_with_stride(&this->gsl_vec_view_m.vector, offset, stride, size);
}

Vector_Complex::Const_View Vector_Complex::View::cview() const
{
    return gsl_vector_complex_const_subvector(&this->gsl_vec_view_m.vector, 0,  this->size());
}

Vector_Complex::Const_View Vector_Complex::View::cview(const size_t offset, const size_t size) const
{
    return gsl_vector_complex_const_subvector(&this->gsl_vec_view_m.vector, offset,  size);
}

Vector_Complex::Const_View Vector_Complex::View::cview(const size_t offset, const size_t stride, const size_t size) const
{
    return gsl_vector_complex_const_subvector_with_stride(&this->gsl_vec_view_m.vector, offset, stride,  size);
}

Vector_Complex::View::iterator Vector_Complex::View::begin() noexcept
{
    return Iterator(this, 0);
}

Vector_Complex::View::const_iterator Vector_Complex::View::begin() const noexcept
{
    return Const_Iterator(this, 0);
}

Vector_Complex::View::const_iterator Vector_Complex::View::cbegin() const noexcept
{
    return Const_Iterator(this, 0);
}

Vector_Complex::View::iterator Vector_Complex::View::end() noexcept
{
    return Iterator(this, this->size());
}

Vector_Complex::View::const_iterator Vector_Complex::View::end() const noexcept
{
    return Const_Iterator(this, this->size());
}

Vector_Complex::View::const_iterator Vector_Complex::View::cend() const noexcept
{
    return Const_Iterator(this, this->size());
}

Vector_Complex::View::reverse_iterator Vector_Complex::View::rbegin() noexcept
{
    return std::reverse_iterator<Iterator>(this->end());
}

Vector_Complex::View::const_reverse_iterator Vector_Complex::View::rbegin() const noexcept
{
    return std::reverse_iterator<Const_Iterator>(this->end());
}

Vector_Complex::View::const_reverse_iterator Vector_Complex::View::crbegin() const noexcept
{
    return std::reverse_iterator<Const_Iterator>(this->cend());
}

Vector_Complex::View::reverse_iterator Vector_Complex::View::rend() noexcept
{
    return std::reverse_iterator<Iterator>(this->begin());
}

Vector_Complex::View::const_reverse_iterator Vector_Complex::View::rend() const noexcept
{
    return std::reverse_iterator<Const_Iterator>(this->begin());
}

Vector_Complex::View::const_reverse_iterator Vector_Complex::View::crend() const noexcept
{
    return std::reverse_iterator<Const_Iterator>(this->begin());
}

Complex& Vector_Complex::View::front()
{
    return *this->begin();
}

const Complex& Vector_Complex::View::front() const
{
    return *this->begin();
}

Complex& Vector_Complex::View::back()
{
    return *(this->begin() + this->size() - 1);
}

const Complex& Vector_Complex::View::back() const
{
    return *(this->begin() + this->size() - 1);
}

/**********************************************************************************************
**********************************************************************************************/


/**********************************************************************************************
* VECTOR VIEW ITERATOR                                                                                                          *
**********************************************************************************************/
Vector_Complex::View::Iterator::Iterator()
 : v_m(), data_m(nullptr)
{}

Vector_Complex::View::Iterator::Iterator(Vector_Complex::View* v, size_t i)
 : v_m(v->gsl_vec_view_m), data_m(reinterpret_cast<gsl_complex*>(v->gsl_vec_view_m.vector.data + sizeof(gsl_complex)/sizeof(double)*i*v->gsl_vec_view_m.vector.stride))
{}

Vector_Complex::View::Iterator::reference
  Vector_Complex::View::Iterator::operator*()
{
    return *reinterpret_cast<pointer>(data_m);
}

Vector_Complex::View::Iterator::const_reference
  Vector_Complex::View::Iterator::operator*() const
{
    return *reinterpret_cast<pointer>(data_m);
}

Vector_Complex::View::Iterator::pointer
  Vector_Complex::View::Iterator::operator->()
{
    return &(*reinterpret_cast<pointer>(data_m));
}

Vector_Complex::View::Iterator::reference
  Vector_Complex::View::Iterator::operator[](size_t n)
{
    return *reinterpret_cast<pointer>(data_m + n*v_m.vector.stride);
}

Vector_Complex::View::Iterator::const_reference
  Vector_Complex::View::Iterator::operator[](size_t n) const
{
    return *reinterpret_cast<pointer>(data_m + n*v_m.vector.stride);
}

Vector_Complex::View::Iterator& Vector_Complex::View::Iterator::operator++()
{
    data_m += v_m.vector.stride;
    return *this;
}

Vector_Complex::View::Iterator& Vector_Complex::View::Iterator::operator--()
{
    data_m -= v_m.vector.stride;
    return *this;
}

Vector_Complex::View::Iterator  Vector_Complex::View::Iterator::operator++(int)
{
    Iterator tmp(*this);
    data_m += v_m.vector.stride;
    return tmp;
}

Vector_Complex::View::Iterator  Vector_Complex::View::Iterator::operator--(int)
{
    Iterator tmp(*this);data_m -= v_m.vector.stride;return tmp;
}

Vector_Complex::View::Iterator& Vector_Complex::View::Iterator::operator+=(size_t n)
{
    data_m += n*v_m.vector.stride;return *this;
}

Vector_Complex::View::Iterator& Vector_Complex::View::Iterator::operator-=(size_t n)
{
    data_m -= n*v_m.vector.stride;return *this;
}

Vector_Complex::View::Iterator Vector_Complex::View::Iterator::operator+(size_t n)   const
{
    Iterator tmp(*this);return tmp += n*v_m.vector.stride;
}

Vector_Complex::View::Iterator Vector_Complex::View::Iterator::operator-(size_t n)   const
{
    Iterator tmp(*this);
    return tmp -= n*v_m.vector.stride;
}

Vector_Complex::View::Iterator::difference_type
  Vector_Complex::View::Iterator::operator-(Iterator const& other) const
{
    return (data_m - other.data_m)
        /
        static_cast<difference_type>(v_m.vector.stride);
}

bool Vector_Complex::View::Iterator::operator<(Iterator const& other)  const
{
    return data_m <  other.data_m;
}

bool Vector_Complex::View::Iterator::operator<=(Iterator const& other) const
{
    return data_m <= other.data_m;
}

bool Vector_Complex::View::Iterator::operator>(Iterator const& other)  const
{
    return data_m >  other.data_m;
}

bool Vector_Complex::View::Iterator::operator>=(Iterator const& other) const
{
    return data_m >= other.data_m;
}

bool Vector_Complex::View::Iterator::operator!=(const Iterator &other) const
{
    return data_m != other.data_m;
}

bool Vector_Complex::View::Iterator::operator==(const Iterator &other) const
{
    return data_m == other.data_m;
}

/**********************************************************************************************
**********************************************************************************************/


/**********************************************************************************************
* VECTOR VIEW CONST_ITERATOR                                                                                              *
**********************************************************************************************/

Vector_Complex::View::Const_Iterator::Const_Iterator()
 : v_m(), data_m(nullptr)
{}

Vector_Complex::View::Const_Iterator::Const_Iterator(const Vector_Complex::View* v, size_t i)
 : v_m(v->gsl_vec_view_m), data_m(reinterpret_cast<gsl_complex*>(v->gsl_vec_view_m.vector.data + sizeof(gsl_complex)/sizeof(double)*i*v->gsl_vec_view_m.vector.stride))
{}

Vector_Complex::View::Const_Iterator::reference Vector_Complex::View::Const_Iterator::operator*()
{
    return *reinterpret_cast<pointer>(data_m);
}
Vector_Complex::View::Const_Iterator::const_reference Vector_Complex::View::Const_Iterator::operator*() const
{
    return *reinterpret_cast<pointer>(data_m);
}

Vector_Complex::View::Const_Iterator::pointer Vector_Complex::View::Const_Iterator::operator->()
{
    return &*reinterpret_cast<pointer>(data_m);
}

Vector_Complex::View::Const_Iterator::reference       Vector_Complex::View::Const_Iterator::operator[](size_t n)
{
    return *reinterpret_cast<pointer>(data_m + n*v_m.vector.stride);
}

Vector_Complex::View::Const_Iterator::const_reference Vector_Complex::View::Const_Iterator::operator[](size_t n) const
{
    return *reinterpret_cast<pointer>(data_m + n*v_m.vector.stride);
}

Vector_Complex::View::Const_Iterator& Vector_Complex::View::Const_Iterator::operator++()       {data_m += v_m.vector.stride;return *this;}
Vector_Complex::View::Const_Iterator& Vector_Complex::View::Const_Iterator::operator--()       {data_m -= v_m.vector.stride;return *this;}
Vector_Complex::View::Const_Iterator  Vector_Complex::View::Const_Iterator::operator++(int)    {Const_Iterator tmp(*this);data_m += v_m.vector.stride;return tmp;}
Vector_Complex::View::Const_Iterator  Vector_Complex::View::Const_Iterator::operator--(int)    {Const_Iterator tmp(*this);data_m -= v_m.vector.stride;return tmp;}

Vector_Complex::View::Const_Iterator& Vector_Complex::View::Const_Iterator::operator+=(size_t n)  {data_m += n*v_m.vector.stride;return *this;}
Vector_Complex::View::Const_Iterator& Vector_Complex::View::Const_Iterator::operator-=(size_t n)  {data_m -= n*v_m.vector.stride;return *this;}

Vector_Complex::View::Const_Iterator Vector_Complex::View::Const_Iterator::operator+(size_t n)   const {Const_Iterator tmp(*this);return tmp += n*v_m.vector.stride;}
Vector_Complex::View::Const_Iterator Vector_Complex::View::Const_Iterator::operator-(size_t n)   const {Const_Iterator tmp(*this);return tmp -= n*v_m.vector.stride;}

Vector_Complex::View::Const_Iterator::difference_type Vector_Complex::View::Const_Iterator::operator-(const Const_Iterator& other) const
{
    return (data_m - other.data_m)
        /
        static_cast<difference_type>(v_m.vector.stride);
}

bool Vector_Complex::View::Const_Iterator::operator<(const Const_Iterator& other)  const
{
    return data_m <  other.data_m;
}

bool Vector_Complex::View::Const_Iterator::operator<=(const Const_Iterator& other) const
{
    return data_m <= other.data_m;
}

bool Vector_Complex::View::Const_Iterator::operator>(const Const_Iterator& other)  const
{
    return data_m >  other.data_m;
}

bool Vector_Complex::View::Const_Iterator::operator>=(const Const_Iterator& other) const
{
    return data_m >= other.data_m;
}

bool Vector_Complex::View::Const_Iterator::operator!=(const Const_Iterator &other) const
{
    return data_m != other.data_m;
}

bool Vector_Complex::View::Const_Iterator::operator==(const Const_Iterator &other) const
{
    return data_m == other.data_m;
}

/**********************************************************************************************
**********************************************************************************************/


/**********************************************************************************************
* VECTOR CONST_VIEW                                                                                                              *
**********************************************************************************************/

Vector_Complex::Const_View::Const_View(const Vector_Complex& v)
 : Const_View(v ,0, v.size())
{}

Vector_Complex::Const_View::Const_View(const Vector_Complex& v, size_t offset, size_t size)
 : gsl_vec_view_m(gsl_vector_complex_const_subvector(v.gsl_vec_m.get(), offset, size))
{}

Vector_Complex::Const_View::Const_View(const Vector_Complex& v, size_t offset, size_t stride, size_t size)
 : gsl_vec_view_m(gsl_vector_complex_const_subvector_with_stride(v.gsl_vec_m.get(), offset, stride, size))
{}

Vector_Complex::Const_View::Const_View(const Block& b)
 : Const_View(b, 0, b.size())
{}

Vector_Complex::Const_View::Const_View(const Block& b, size_t offset, size_t size)
 : gsl_vec_view_m(gsl_vector_complex_const_view_array(b.data() + offset, size))
{}

Vector_Complex::Const_View::Const_View(const Block& b, size_t offset, size_t stride, size_t size)
 : gsl_vec_view_m(gsl_vector_complex_const_view_array_with_stride(b.data() + offset, stride, size))
{}

Vector_Complex::Const_View::Const_View(const double* data, size_t size)
 : Const_View(data, 0, size)
{}

Vector_Complex::Const_View::Const_View(const double* data, size_t offset, size_t size)
 : gsl_vec_view_m(gsl_vector_complex_const_view_array(data + offset, size))
{}

Vector_Complex::Const_View::Const_View(const double* data, size_t offset, size_t stride, size_t size)
 : gsl_vec_view_m(gsl_vector_complex_const_view_array_with_stride(data + offset, stride, size))
{}

Vector_Complex::Const_View::Const_View(gsl_vector_complex_const_view v)
 : gsl_vec_view_m(v)
{}

Vector_Complex::Const_View::operator const Vector_Complex() const
{
    return Vector_Complex(const_cast<gsl_vector_complex*>(&this->gsl_vec_view_m.vector));
}

const gsl_vector_complex* Vector_Complex::Const_View::gsl_data() const
{
    return &this->gsl_vec_view_m.vector;
}


const Complex& Vector_Complex::Const_View::operator[](const size_t i) const
{
    return *reinterpret_cast<const Complex*>(gsl_vector_complex_const_ptr(&gsl_vec_view_m.vector, i));
}

size_t Vector_Complex::Const_View::size() const
{
    return this->gsl_vec_view_m.vector.size;
}

size_t Vector_Complex::Const_View::stride() const
{
    return this->gsl_vec_view_m.vector.stride;
}

const Complex& Vector_Complex::Const_View::at(const size_t i) const
{
    if(!(i < this->size())){
        throw std::out_of_range("Index " + std::to_string(i) + " out of range.");
    }
    return (*this)[i];
}


Vector_Complex Vector_Complex::Const_View::clone() const
{
    Vector_Complex res(this->size());
    res.copy(*this);
    return res;
}

Complex Vector_Complex::Const_View::get(size_t i) const
{
    return gsl_vector_complex_get(&this->gsl_vec_view_m.vector, i);
}

/*
double Vector_Complex::Const_View::max() const
{
    return gsl_vector_complex_max(&this->gsl_vec_view_m.vector);
}

double Vector_Complex::Const_View::min() const
{
    return gsl_vector_complex_min(&this->gsl_vec_view_m.vector);
}

std::pair<double, double> Vector_Complex::Const_View::minmax() const
{
    std::pair<double, double> res;
    gsl_vector_complex_minmax(&this->gsl_vec_view_m.vector, &res.first, &res.second);
    return res;
}

size_t Vector_Complex::Const_View::max_index() const
{
    return gsl_vector_complex_max_index(&this->gsl_vec_view_m.vector);
}

size_t Vector_Complex::Const_View::min_index() const
{
    return gsl_vector_complex_min_index(&this->gsl_vec_view_m.vector);
}

std::pair<size_t, size_t> Vector_Complex::Const_View::minmax_index() const
{
    std::pair<size_t, size_t> res;
    gsl_vector_complex_minmax_index(&this->gsl_vec_view_m.vector, &res.first, &res.second);
    return res;
}
*/

double Vector_Complex::Const_View::norm() const
{
    return ::norm(*this);
}

double Vector_Complex::Const_View::norm2() const
{
    return ::norm2(*this);
}

double Vector_Complex::Const_View::l1_norm() const
{
    return ::l1_norm(*this);
}

bool Vector_Complex::Const_View::isnull() const
{
    return gsl_vector_complex_isnull(&this->gsl_vec_view_m.vector);
}
bool Vector_Complex::Const_View::ispos() const
{
    return gsl_vector_complex_ispos(&this->gsl_vec_view_m.vector);
}
bool Vector_Complex::Const_View::isneg() const
{
    return gsl_vector_complex_isneg(&this->gsl_vec_view_m.vector);
}
bool Vector_Complex::Const_View::isnonneg() const
{
    return gsl_vector_complex_isnonneg(&this->gsl_vec_view_m.vector);
}

Vector::Const_View Vector_Complex::Const_View::real() const
{
    return Vector::Const_View(gsl_vector_complex_const_real(&this->gsl_vec_view_m.vector));
}

Vector::Const_View Vector_Complex::Const_View::imag() const
{
    return Vector::Const_View(gsl_vector_complex_const_imag(&this->gsl_vec_view_m.vector));
}

Vector_Complex Vector_Complex::Const_View::operator-() const
{
    Vector_Complex result(this->size(), Complex{0,0});
    result -= *this;
    return result;
}


// Complex GSL::dotc(const Vector_Complex::Const_View& a, const Vector_Complex::Const_View& b)
// {
//     gsl_complex res;
//     gsl_blas_zdotc(&a.gsl_vec_view_m.vector, &b.gsl_vec_view_m.vector, &res);
//     return res;
// }
//
// Complex GSL::dotu(const Vector_Complex::Const_View& a, const Vector_Complex::Const_View& b)
// {
//     gsl_complex res;
//     gsl_blas_zdotu(&a.gsl_vec_view_m.vector, &b.gsl_vec_view_m.vector, &res);
//     return res;
// }

// double GSL::norm(const Vector_Complex::Const_View& a)
// {
//     return gsl_blas_dznrm2(&a.gsl_vec_view_m.vector);
// }
//
// double GSL::norm2(const Vector_Complex::Const_View& a)
// {
//     return dot(a, a).real();
// }
//
// double GSL::l1_norm(const Vector_Complex::Const_View& a)
// {
//     return gsl_blas_dzasum(&a.gsl_vec_view_m.vector);
// }
//
// Vector_Complex GSL::normalize(const Vector_Complex::Const_View& a)
// {
//     return a/Complex(norm(a));
// }
//
// Vector_Complex GSL::mirror(const Vector_Complex::Const_View& v, const Vector_Complex::Const_View& a)
// {
//     return v - 2*dot(v, a)*a/Complex(norm2(a));
// }
//
// bool GSL::operator==(const Vector_Complex::Const_View& a, const Vector_Complex::Const_View& b)
// {
//     return gsl_vector_complex_equal(&a.gsl_vec_view_m.vector, &b.gsl_vec_view_m.vector);
// }
//
// bool GSL::operator!=(const Vector_Complex::Const_View& a, const Vector_Complex::Const_View& b)
// {
//     return !(a == b);
// }

Vector_Complex::Const_View Vector_Complex::Const_View::view() const
{
    return gsl_vector_complex_const_subvector(&this->gsl_vec_view_m.vector, 0, this->size());
}

Vector_Complex::Const_View Vector_Complex::Const_View::view(const size_t offset, const size_t size) const
{
    return gsl_vector_complex_const_subvector(&this->gsl_vec_view_m.vector, offset, size);
}

Vector_Complex::Const_View Vector_Complex::Const_View::view(const size_t offset, const size_t stride, const size_t size) const
{
    return gsl_vector_complex_const_subvector_with_stride(&this->gsl_vec_view_m.vector, offset, stride, size);
}

Vector_Complex::Const_View Vector_Complex::Const_View::cview() const
{
    return gsl_vector_complex_const_subvector(&this->gsl_vec_view_m.vector, 0, this->size());
}

Vector_Complex::Const_View Vector_Complex::Const_View::cview(const size_t offset, const size_t size) const
{
    return gsl_vector_complex_const_subvector(&this->gsl_vec_view_m.vector, offset, size);
}

Vector_Complex::Const_View Vector_Complex::Const_View::cview(const size_t offset, const size_t stride, const size_t size) const
{
    return gsl_vector_complex_const_subvector_with_stride(&this->gsl_vec_view_m.vector, offset, stride, size);
}

Vector_Complex::Const_View::const_iterator Vector_Complex::Const_View::begin() const noexcept
{
    return Const_Iterator(this, 0);
}

Vector_Complex::Const_View::const_iterator Vector_Complex::Const_View::cbegin() const noexcept
{
    return Const_Iterator(this, 0);
}


Vector_Complex::Const_View::const_iterator Vector_Complex::Const_View::end() const noexcept
{
    return Const_Iterator(this, this->size());
}

Vector_Complex::Const_View::const_iterator Vector_Complex::Const_View::cend() const noexcept
{
    return Const_Iterator(this, this->size());
}

Vector_Complex::Const_View::const_reverse_iterator Vector_Complex::Const_View::rbegin() const noexcept
{
    return std::reverse_iterator<Const_Iterator>(this->end());
}

Vector_Complex::Const_View::const_reverse_iterator Vector_Complex::Const_View::crbegin() const noexcept
{
    return std::reverse_iterator<Const_Iterator>(this->cend());
}

Vector_Complex::Const_View::const_reverse_iterator Vector_Complex::Const_View::rend() const noexcept
{
    return std::reverse_iterator<Const_Iterator>(this->begin());
}

Vector_Complex::Const_View::const_reverse_iterator Vector_Complex::Const_View::crend() const noexcept
{
    return std::reverse_iterator<Const_Iterator>(this->begin());
}

const Complex& Vector_Complex::Const_View::front() const
{
    return *this->begin();
}

const Complex& Vector_Complex::Const_View::back() const
{
    return *(this->begin() + this->size() - 1);
}

/**********************************************************************************************
**********************************************************************************************/



/**********************************************************************************************
* VECTOR CONST_VIEW CONST_ITERATOR                                                                                 *
**********************************************************************************************/

Vector_Complex::Const_View::Const_Iterator::Const_Iterator()
 : v_m(), data_m(nullptr)
{}

Vector_Complex::Const_View::Const_Iterator::Const_Iterator(const Vector_Complex::Const_View* v, size_t i)
 : v_m(v->gsl_vec_view_m), data_m(reinterpret_cast<gsl_complex*>(v->gsl_vec_view_m.vector.data + sizeof(gsl_complex)/sizeof(double)*i*v->gsl_vec_view_m.vector.stride))
{}

Vector_Complex::Const_View::Const_Iterator::reference
  Vector_Complex::Const_View::Const_Iterator::operator*()
{
    return *reinterpret_cast<pointer>(data_m);
}

Vector_Complex::Const_View::Const_Iterator::const_reference
  Vector_Complex::Const_View::Const_Iterator::operator*() const
{
    return *reinterpret_cast<pointer>(data_m);
}

Vector_Complex::Const_View::Const_Iterator::pointer
  Vector_Complex::Const_View::Const_Iterator::operator->()
{
    return &*reinterpret_cast<pointer>(data_m);
}

Vector_Complex::Const_View::Const_Iterator::reference
  Vector_Complex::Const_View::Const_Iterator::operator[](size_t n)
{
    return *reinterpret_cast<pointer>(data_m + n*v_m.vector.stride);
}

Vector_Complex::Const_View::Const_Iterator::const_reference
  Vector_Complex::Const_View::Const_Iterator::operator[](size_t n) const
{
    return *reinterpret_cast<pointer>(data_m + n*v_m.vector.stride);
}

Vector_Complex::Const_View::Const_Iterator& Vector_Complex::Const_View::Const_Iterator::operator++()
{
    data_m += v_m.vector.stride;return *this;
}

Vector_Complex::Const_View::Const_Iterator& Vector_Complex::Const_View::Const_Iterator::operator--()
{
    data_m -= v_m.vector.stride;return *this;
}

Vector_Complex::Const_View::Const_Iterator  Vector_Complex::Const_View::Const_Iterator::operator++(int)
{
    Const_Iterator tmp(*this);data_m += v_m.vector.stride;return tmp;
}

Vector_Complex::Const_View::Const_Iterator  Vector_Complex::Const_View::Const_Iterator::operator--(int)
{
    Const_Iterator tmp(*this);data_m -= v_m.vector.stride;return tmp;
}

Vector_Complex::Const_View::Const_Iterator& Vector_Complex::Const_View::Const_Iterator::operator+=(size_t n)
{
    data_m += n*v_m.vector.stride;return *this;
}

Vector_Complex::Const_View::Const_Iterator& Vector_Complex::Const_View::Const_Iterator::operator-=(size_t n)
{
    data_m -= n*v_m.vector.stride;return *this;
}

Vector_Complex::Const_View::Const_Iterator Vector_Complex::Const_View::Const_Iterator::operator+(size_t n)   const
{
    Const_Iterator tmp(*this);return tmp += n*v_m.vector.stride;
}

Vector_Complex::Const_View::Const_Iterator Vector_Complex::Const_View::Const_Iterator::operator-(size_t n)   const
{
    Const_Iterator tmp(*this);return tmp -= n*v_m.vector.stride;
}

Vector_Complex::Const_View::Const_Iterator::difference_type Vector_Complex::Const_View::Const_Iterator::operator-(const Const_Iterator& other) const
{
    return (data_m - other.data_m)
        /
        static_cast<difference_type>(v_m.vector.stride);
}

bool Vector_Complex::Const_View::Const_Iterator::operator<(const Const_Iterator& other)  const
{
    return data_m <  other.data_m;
}

bool Vector_Complex::Const_View::Const_Iterator::operator<=(const Const_Iterator& other) const
{
    return data_m <= other.data_m;
}

bool Vector_Complex::Const_View::Const_Iterator::operator>(const Const_Iterator& other)  const
{
    return data_m >  other.data_m;
}

bool Vector_Complex::Const_View::Const_Iterator::operator>=(const Const_Iterator& other) const
{
    return data_m >= other.data_m;
}

bool Vector_Complex::Const_View::Const_Iterator::operator!=(const Const_Iterator &other) const
{
    return data_m != other.data_m;
}

bool Vector_Complex::Const_View::Const_Iterator::operator==(const Const_Iterator &other) const
{
    return data_m == other.data_m;
}

/**********************************************************************************************
**********************************************************************************************/


void std::swap(GSL::Vector_Complex&a, GSL::Vector_Complex& b)
{
    a.swap(b);
}

std::string std::to_string(const GSL::Vector_Complex& v)
{
    return v.to_string();
}

#if 0
int main()
{
    Block b(100);

    Vector_Complex v(5, 2);
    Vector_Complex u(5, 4);
    Vector_Complex::View vv(v, 0, 2, 3);
    Vector_Complex::View vv2 = v.view();

    v[1] = 3;
    vv[0] = 5;


    std::cout << "v = (";
    for(const auto& val : v.view()){
        std::cout << val << ", ";
    }
    std::cout << ")\n";

    std::cout << "vv = (";
    for(auto val : vv){
        std::cout << val << ", ";
    }
    std::cout << ")\n";

    std::swap(u, v);

    Vector_Complex w = std::move(v);
    Vector_Complex::View bv(b);
    bv[0] = 5;
    std::cout << "bv[0] = " << bv[0] << "\n";

    Vector_Complex::View::Iterator it(&bv, 0);
    std::cout << "it[0] = " << it[0] << "\n";

    Vector_Complex::Const_View cv = w.cview();
    std::cout << "cv[2] = " << cv[2] << "\n";

    std::cout << "u + cv = " << u << " + " << cv << " = " << u + cv <<"\n";

    std::cout << "||cv|| = " << norm(cv) << "\n";
    return 0;
}
#endif
