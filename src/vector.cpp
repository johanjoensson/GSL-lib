#include "GSLpp/vector.h"
#include "GSLpp/block.h"
#include <gsl/gsl_blas.h>
#include <algorithm>

using namespace GSL;

/**********************************************************************************************
* VECTOR                                                                                                                                    *
**********************************************************************************************/

Vector::Vector(size_t n)
 : gsl_vec_m(gsl_vector_alloc(n), gsl_vector_free)
{}

Vector::Vector(size_t n, double val)
 : gsl_vec_m(gsl_vector_alloc(n), gsl_vector_free)
{
    gsl_vector_set_all(this->gsl_vec_m.get(), val);
}

Vector::Vector(std::initializer_list<double> l)
 : Vector(l.size())
{
    std::transform(l.begin(), l.end(), this->view().begin(),
        [](double a)
        {
            return a;
        }
    );
}


Vector::Vector(gsl_vector* v)
 : gsl_vec_m(v, [](gsl_vector*){})
{}

gsl_vector* Vector::gsl_data()
{
    return gsl_vec_m.get();
}

const gsl_vector* Vector::gsl_data() const
{
    return gsl_vec_m.get();
}

void Vector::copy(const Vector& other)
{
    gsl_vector_memcpy(this->gsl_vec_m.get(), other.gsl_vec_m.get());
}

void Vector::swap(Vector& other)
{
    gsl_vector_swap(this->gsl_vec_m.get(), other.gsl_vec_m.get());
}

void Vector::swap_elements(size_t i, size_t j)
{
    gsl_vector_swap_elements(this->gsl_vec_m.get(), i, j);
}

void Vector::reverse()
{
    gsl_vector_reverse(this->gsl_vec_m.get());
}

Vector Vector::clone() const
{
    Vector res(this->gsl_vec_m->size);
    res.copy(*this);
    return res;
}

size_t Vector::size() const
{
    return this->gsl_vec_m->size;
}

void Vector::set_all(double val)
{
    gsl_vector_set_all(this->gsl_vec_m.get(), val);
}

void Vector::set_zero()
{
    gsl_vector_set_zero(this->gsl_vec_m.get());
}

void Vector::set_basis(size_t i)
{
    gsl_vector_set_basis(this->gsl_vec_m.get(), i);
}

void Vector::set(size_t i, double val)
{
    gsl_vector_set(this->gsl_vec_m.get(), i, val);
}

double Vector::get(size_t i) const
{
    return gsl_vector_get(this->gsl_vec_m.get(), i);
}

double& Vector::operator[](const size_t i)
{
    return *gsl_vector_ptr(this->gsl_vec_m.get(), i);
}

const double& Vector::operator[](const size_t i) const
{
    return *gsl_vector_ptr(this->gsl_vec_m.get(), i);
}

double& Vector::at(const size_t i)
{
    if(!(i < this->size())){
        throw std::out_of_range("Index " + std::to_string(i) + " out of range.");
    }
    return (*this)[i];
}

const double& Vector::at(const size_t i) const
{
    if(!(i < this->size())){
        throw std::out_of_range("Index " + std::to_string(i) + " out of range.");
    }
    return (*this)[i];
}


Vector& Vector::operator+=(const Vector& other)
{
    gsl_vector_add(this->gsl_vec_m.get(), other.gsl_vec_m.get());
    return *this;
}

Vector& Vector::operator-=(double s)
{
    return *this += -s;
}

Vector& Vector::operator-=(const Vector& other)
{
    gsl_vector_sub(this->gsl_vec_m.get(), other.gsl_vec_m.get());
    return *this;
}

Vector& Vector::operator*=(const Vector& other)
{
    gsl_vector_mul(this->gsl_vec_m.get(), other.gsl_vec_m.get());
    return *this;
}

Vector& Vector::operator/=(const Vector& other)
{
    gsl_vector_div(this->gsl_vec_m.get(), other.gsl_vec_m.get());
    return *this;
}

Vector& Vector::operator/=(double s)
{
    return *this *= 1/s;
}

Vector Vector::operator-() const
{
    Vector res(this->size(), 0);
    res -= *this;
    return res;
}

Vector& Vector::operator+=(double s)
{
    gsl_vector_add_constant(this->gsl_vec_m.get(), s);
    return *this;
}

Vector& Vector::operator*=(double s)
{
    gsl_vector_scale(this->gsl_vec_m.get(), s);
    return *this;
}

Vector GSL::operator+(const Vector& a, const Vector& b)
{
    Vector result{a.clone()};
    result += b;
    return result;
}

Vector GSL::operator-(const Vector& a, const Vector& b)
{
    Vector result{a.clone()};
    result -= b;
    return result;
}

Vector GSL::operator*(const Vector& a, const Vector& b)
{
    Vector result{a.clone()};
    result *= b;
    return result;
}

Vector GSL::operator/(const Vector& a, const Vector& b)
{
    Vector result{a.clone()};
    result /= b;
    return result;
}

Vector GSL::operator+(const Vector& a, double s)
{
    Vector result{a.clone()};
    result += s;
    return result;
}

Vector GSL::operator+(double s, const Vector& a)
{
    return a + s;
}

Vector GSL::operator-(const Vector& a, double s)
{
    Vector result{a.clone()};
    result -= s;
    return result;
}
Vector GSL::operator-(double s, const Vector& a)
{
    return a - s;
}

Vector GSL::operator*(const Vector& a, double s)
{
    Vector result{a.clone()};
    result *= s;
    return result;
}

Vector GSL::operator*(double s, const Vector& a)
{
    return a*s;
}

Vector GSL::operator/(const Vector& a, double s)
{
    Vector result{a.clone()};
    result /= s;
    return result;
}

double Vector::max() const
{
    return gsl_vector_max(this->gsl_vec_m.get());
}

double Vector::min() const
{
    return gsl_vector_min(this->gsl_vec_m.get());
}

std::pair<double, double> Vector::minmax() const
{
    std::pair<double, double> res;
    gsl_vector_minmax(this->gsl_vec_m.get(), &res.first, &res.second);
    return res;
}

size_t Vector::max_index() const
{
    return gsl_vector_max_index(this->gsl_vec_m.get());
}
size_t Vector::min_index() const
{
    return gsl_vector_min_index(this->gsl_vec_m.get());
}
std::pair<size_t, size_t> Vector::minmax_index() const
{
    std::pair<size_t, size_t> res;
    gsl_vector_minmax_index(this->gsl_vec_m.get(), &res.first, &res.second);
    return res;
}

bool Vector::isnull() const
{
    return gsl_vector_isnull(this->gsl_vec_m.get());
}

bool Vector::ispos() const
{
    return gsl_vector_ispos(this->gsl_vec_m.get());
}

bool Vector::isneg() const
{
    return gsl_vector_isneg(this->gsl_vec_m.get());
}

bool Vector::isnonneg() const
{
    return gsl_vector_isnonneg(this->gsl_vec_m.get());
}

double Vector::norm() const
{
    return ::norm(*this);
}

double Vector::l1_norm() const
{
    return ::l1_norm(*this);
}

double Vector::norm2() const
{
    return ::norm2(*this);
}

bool GSL::operator==(const Vector& a, const Vector& b)
{
    return gsl_vector_equal(a.gsl_vec_m.get(), b.gsl_vec_m.get());
}

bool GSL::operator!=(const Vector& a, const Vector& b)
{return !(a == b);}

std::string Vector::to_string() const
{
    std::string res = "(";
    for(const auto elem : this->cview()){
        res += std::to_string(elem) + "  ";
    }
    res += ")";
    return res;
}

Vector GSL::zeros(size_t n)
{
    return Vector(n, 0);
}

Vector GSL::unit(size_t n, size_t i)
{
    Vector res(n);
    res.set_basis(i);
    return res;
}

double GSL::dot(const Vector& a, const Vector& b)
{
    double res;
    gsl_blas_ddot(a.gsl_vec_m.get(), b.gsl_vec_m.get(), &res);
    return res;
}

Vector GSL::cross(const Vector& a, const Vector& b)
{
    Vector res(3);
    res[0] = a[1]*b[2] - a[2]*b[1];
    res[1] = a[2]*b[0] - a[0]*b[2];
    res[2] = a[0]*b[1] - a[1]*b[0];
    return res;
}


double GSL::norm(const Vector& a)
{
    return gsl_blas_dnrm2(a.gsl_vec_m.get());
}

double GSL::norm2(const Vector& a)
{
    return dot(a, a);
}

double GSL::l1_norm(const Vector& a)
{
    return gsl_blas_dasum(a.gsl_vec_m.get());
}

Vector GSL::normalize(const Vector& a)
{
    return a/norm(a);
}

Vector GSL::mirror(const Vector& v, const Vector& a)
{
    return v - 2*dot(v, a)*a/norm2(a);
}


Vector::View Vector::view()
{
    return View(*this, 0, this->size());
}

const Vector::View Vector::view() const
{
    return View(*this, 0, this->size());
}

Vector::View Vector::view(const size_t offset, const size_t size)
{
    return View(*this, offset, size);
}

const Vector::View Vector::view(const size_t offset, const size_t size) const
{
    return View(*this, offset, size);
}

Vector::View Vector::view(const size_t offset, const size_t stride, const size_t size)
{
    return View(*this, offset, stride, size);
}

const Vector::View Vector::view(const size_t offset, const size_t stride, const size_t size) const
{
    return View(*this, offset, stride, size);
}

Vector::Const_View Vector::cview() const
{
    return Const_View(*this, 0, this->size());
}

Vector::Const_View Vector::cview(const size_t offset, const size_t size) const
{
    return Const_View(*this, offset, size);
}

Vector::Const_View Vector::cview(const size_t offset, const size_t stride, const size_t size) const
{
    return Const_View(*this, offset, stride, size);
}

std::ostream& GSL::operator<<(std::ostream& os, const Vector& v)
{
    return os << v.to_string();
}

/**********************************************************************************************
**********************************************************************************************/


/**********************************************************************************************
* VECTOR VIEW                                                                                                                           *
**********************************************************************************************/

Vector::View::View(const Vector& v)
 : View(v ,0, v.size())
{}

Vector::View::View(const Vector& v, size_t offset, size_t size)
 : gsl_vec_view_m(gsl_vector_subvector(v.gsl_vec_m.get(), offset, size))
{}

Vector::View::View(const Vector& v, size_t offset, size_t stride, size_t size)
 : gsl_vec_view_m(gsl_vector_subvector_with_stride(v.gsl_vec_m.get(), offset, stride, size))
{}

Vector::View::View(Block& b)
 : View(b, 0, b.size())
{}

Vector::View::View(Block& b, size_t offset, size_t size)
 : gsl_vec_view_m(gsl_vector_view_array(b.data() + offset, size))
{}

Vector::View::View(Block& b, size_t offset, size_t stride, size_t size)
 : gsl_vec_view_m(gsl_vector_view_array_with_stride(b.data() + offset, stride, size))
{}

Vector::View::View(double* data, size_t size)
 : View(data, 0, size)
{}

Vector::View::View(double* data, size_t offset, size_t size)
 : gsl_vec_view_m(gsl_vector_view_array(data + offset, size))
{}

Vector::View::View(double* data, size_t offset, size_t stride, size_t size)
 : gsl_vec_view_m(gsl_vector_view_array_with_stride(data + offset, stride, size))
{}

Vector::View::View(gsl_vector_view v)
 : gsl_vec_view_m(v)
{}

Vector::View::operator Vector()
{
    return Vector(&this->gsl_vec_view_m.vector);
}

gsl_vector* Vector::View::gsl_data()
{
    return &this->gsl_vec_view_m.vector;
}

const gsl_vector* Vector::View::gsl_data() const
{
    return &this->gsl_vec_view_m.vector;
}

Vector::View::operator const Vector() const
{
    return Vector(const_cast<gsl_vector*>(&this->gsl_vec_view_m.vector));
}

size_t Vector::View::size() const
{
    return this->gsl_vec_view_m.vector.size;
}

size_t Vector::View::stride() const
{
    return this->gsl_vec_view_m.vector.stride;
}

double& Vector::View::operator[](const size_t i)
{
    return *gsl_vector_ptr(&gsl_vec_view_m.vector, i);
}

const double& Vector::View::operator[](const size_t i) const
{
    return *gsl_vector_const_ptr(&gsl_vec_view_m.vector, i);
}

double& Vector::View::at(const size_t i)
{
    if(!(i < this->size())){
        throw std::out_of_range("Index " + std::to_string(i) + " out of range.");
    }
    return (*this)[i];
}

const double& Vector::View::at(const size_t i) const
{
    if(!(i < this->size())){
        throw std::out_of_range("Index " + std::to_string(i) + " out of range.");
    }
    return (*this)[i];
}

// Vector::View& Vector::View::swap(Vector& v)
// {
//     gsl_vector_swap(&this->gsl_vec_view_m.vector, v.gsl_vec_m.get());
//     return *this;
// }
// Vector::View& Vector::View::swap(View& vv)
// {
//     gsl_vector_swap(&this->gsl_vec_view_m.vector, &vv.gsl_vec_view_m.vector);
//     return *this;
// }

Vector::View& Vector::View::swap(Vector&& v)
{
    gsl_vector_swap(&this->gsl_vec_view_m.vector, v.gsl_vec_m.get());
    return *this;
}
Vector::View& Vector::View::swap(View&& vv)
{
    gsl_vector_swap(&this->gsl_vec_view_m.vector, &vv.gsl_vec_view_m.vector);
    return *this;
}

Vector::View& Vector::View::copy(const View& vv)
{
    gsl_vector_memcpy(&this->gsl_vec_view_m.vector, &vv.gsl_vec_view_m.vector);
    return *this;
}

// Vector::View& Vector::View::copy(View&& vv)
// {
//     gsl_vector_swap(&this->gsl_vec_view_m.vector, &vv.gsl_vec_view_m.vector);
//     return *this;
// }

Vector::View& Vector::View::copy(const Vector& vv)
{
    gsl_vector_memcpy(&this->gsl_vec_view_m.vector, vv.gsl_vec_m.get());
    return *this;
}

// Vector::View& Vector::View::copy(Vector&& vv)
// {
//     gsl_vector_swap(&this->gsl_vec_view_m.vector, vv.gsl_vec_m.get());
//     return *this;
// }


Vector::View& Vector::View::swap_elements(size_t i, size_t j)
{
    gsl_vector_swap_elements(&this->gsl_vec_view_m.vector, i, j);
    return *this;
}

Vector::View& Vector::View::reverse()
{
    gsl_vector_reverse(&this->gsl_vec_view_m.vector);
    return *this;
}

Vector Vector::View::clone() const
{
    Vector res(this->size());
    gsl_vector_memcpy(res.gsl_vec_m.get(), &this->gsl_vec_view_m.vector);
    return res;
}

Vector::View& Vector::View::set_all(double val)
{
        gsl_vector_set_all(&this->gsl_vec_view_m.vector, val);
        return *this;
}

Vector::View& Vector::View::set_zero()
{
        gsl_vector_set_zero(&this->gsl_vec_view_m.vector);
        return *this;
}

Vector::View& Vector::View::set(size_t i, double val)
{
    gsl_vector_set(&this->gsl_vec_view_m.vector, i, val);
    return *this;
}

Vector::View& Vector::View::set_basis(size_t i)
{
    gsl_vector_set_basis(&this->gsl_vec_view_m.vector, i);
    return *this;
}

double Vector::View::get(size_t i) const
{
    return gsl_vector_get(&this->gsl_vec_view_m.vector, i);
}


double Vector::View::max() const
{
        return gsl_vector_max(&this->gsl_vec_view_m.vector);
}

double Vector::View::min() const
{
    return gsl_vector_min(&this->gsl_vec_view_m.vector);
}

std::pair<double, double> Vector::View::minmax() const
{
    std::pair<double, double> res;
    gsl_vector_minmax(&this->gsl_vec_view_m.vector, &res.first, &res.second);
    return res;
}

size_t Vector::View::max_index() const
{
    return gsl_vector_min_index(&this->gsl_vec_view_m.vector);
}

size_t Vector::View::min_index() const
{
    return gsl_vector_max_index(&this->gsl_vec_view_m.vector);
}
std::pair<size_t, size_t> Vector::View::minmax_index() const
{
    std::pair<size_t, size_t> res;
    gsl_vector_minmax_index(&this->gsl_vec_view_m.vector, &res.first, &res.second);
    return res;
}

bool Vector::View::isnull() const
{
    return gsl_vector_isnull(&this->gsl_vec_view_m.vector);
}

bool Vector::View::ispos() const
{
    return gsl_vector_ispos(&this->gsl_vec_view_m.vector);
}

bool Vector::View::isneg() const
{
        return gsl_vector_isneg(&this->gsl_vec_view_m.vector);
}

bool Vector::View::isnonneg() const
{
    return gsl_vector_isnonneg(&this->gsl_vec_view_m.vector);
}

double Vector::View::norm() const
{
    return ::norm(*this);
}

double Vector::View::norm2() const
{
    return ::norm2(*this);
}

double Vector::View::l1_norm() const
{
    return ::l1_norm(*this);
}

Vector::View& Vector::View::operator=(const Vector& v)
{
    return this->copy(v);
}

Vector::View& Vector::View::operator=(Vector&& v)
{
    return this->swap(v);
}

Vector::View& Vector::View::operator+=(const Vector& other)
{
    gsl_vector_add(&this->gsl_vec_view_m.vector, other.gsl_vec_m.get());
    return *this;
}

Vector::View& Vector::View::operator-=(const Vector& other)
{
    gsl_vector_sub(&this->gsl_vec_view_m.vector, other.gsl_vec_m.get());
    return *this;
}

Vector::View& Vector::View::operator*=(const Vector& other)
{
    gsl_vector_mul(&this->gsl_vec_view_m.vector, other.gsl_vec_m.get());
    return *this;
}

Vector::View& Vector::View::operator/=(const Vector& other)
{
    gsl_vector_div(&this->gsl_vec_view_m.vector, other.gsl_vec_m.get());
    return *this;
}

Vector::View& Vector::View::operator+=(double s)
{
    gsl_vector_add_constant(&this->gsl_vec_view_m.vector, s);
    return *this;
}

Vector::View& Vector::View::operator-=(double s)
{
    gsl_vector_add_constant(&this->gsl_vec_view_m.vector, -s);
    return *this;
}

Vector::View& Vector::View::operator*=(double s)
{
    gsl_vector_scale(&this->gsl_vec_view_m.vector, s);
    return *this;
}

Vector::View& Vector::View::operator/=(double s)
{
    gsl_vector_scale(&this->gsl_vec_view_m.vector, 1/s);
    return *this;
}

Vector Vector::View::operator-() const
{
    Vector res(this->size(), 0);
    res -= *this;
    return res;
}


Vector::View Vector::View::view()
{
    return gsl_vector_subvector(&this->gsl_vec_view_m.vector, 0,  this->size());
}

Vector::Const_View Vector::View::view() const
{
    return gsl_vector_const_subvector(&this->gsl_vec_view_m.vector, 0,  this->size());
}

Vector::View Vector::View::view(const size_t offset, const size_t size)
{
    return gsl_vector_subvector(&this->gsl_vec_view_m.vector, offset,  size);
}

Vector::Const_View Vector::View::view(const size_t offset, const size_t size) const
{
    return gsl_vector_const_subvector(&this->gsl_vec_view_m.vector, offset,  size);
}

Vector::View Vector::View::view(const size_t offset, const size_t stride, const size_t size)
{
    return gsl_vector_subvector_with_stride(&this->gsl_vec_view_m.vector, offset, stride, size);
}

Vector::Const_View Vector::View::view(const size_t offset, const size_t stride, const size_t size) const
{
    return gsl_vector_const_subvector_with_stride(&this->gsl_vec_view_m.vector, offset, stride, size);
}

Vector::Const_View Vector::View::cview() const
{
    return gsl_vector_const_subvector(&this->gsl_vec_view_m.vector, 0,  this->size());
}

Vector::Const_View Vector::View::cview(const size_t offset, const size_t size) const
{
    return gsl_vector_const_subvector(&this->gsl_vec_view_m.vector, offset,  size);
}

Vector::Const_View Vector::View::cview(const size_t offset, const size_t stride, const size_t size) const
{
    return gsl_vector_const_subvector_with_stride(&this->gsl_vec_view_m.vector, offset, stride,  size);
}

Vector::View::iterator Vector::View::begin() noexcept
{
    return Iterator(this, 0);
}

Vector::View::const_iterator Vector::View::begin() const noexcept
{
    return Const_Iterator(this, 0);
}

Vector::View::const_iterator Vector::View::cbegin() const noexcept
{
    return Const_Iterator(this, 0);
}

Vector::View::iterator Vector::View::end() noexcept
{
    return Iterator(this, this->size());
}

Vector::View::const_iterator Vector::View::end() const noexcept
{
    return Const_Iterator(this, this->size());
}

Vector::View::const_iterator Vector::View::cend() const noexcept
{
    return Const_Iterator(this, this->size());
}

Vector::View::reverse_iterator Vector::View::rbegin() noexcept
{
    return std::reverse_iterator<Iterator>(this->end());
}

Vector::View::const_reverse_iterator Vector::View::rbegin() const noexcept
{
    return std::reverse_iterator<Const_Iterator>(this->end());
}

Vector::View::const_reverse_iterator Vector::View::crbegin() const noexcept
{
    return std::reverse_iterator<Const_Iterator>(this->cend());
}

Vector::View::reverse_iterator Vector::View::rend() noexcept
{
    return std::reverse_iterator<Iterator>(this->begin());
}

Vector::View::const_reverse_iterator Vector::View::rend() const noexcept
{
    return std::reverse_iterator<Const_Iterator>(this->begin());
}

Vector::View::const_reverse_iterator Vector::View::crend() const noexcept
{
    return std::reverse_iterator<Const_Iterator>(this->begin());
}

double& Vector::View::front()
{
    return *this->begin();
}

const double& Vector::View::front() const
{
    return *this->begin();
}

double& Vector::View::back()
{
    return *(this->begin() + this->size() - 1);
}

const double& Vector::View::back() const
{
    return *(this->begin() + this->size() - 1);
}

/**********************************************************************************************
**********************************************************************************************/


/**********************************************************************************************
* VECTOR VIEW ITERATOR                                                                                                          *
**********************************************************************************************/
Vector::View::Iterator::Iterator()
 : v_m(nullptr), data_m(nullptr)
{}

Vector::View::Iterator::Iterator(Vector::View* v, size_t i)
 : v_m(v), data_m(v->gsl_vec_view_m.vector.data + i*v->gsl_vec_view_m.vector.stride)
{}

Vector::View::Iterator::reference
  Vector::View::Iterator::operator*()
{
    return *data_m;
}

const Vector::View::Iterator::reference
  Vector::View::Iterator::operator*() const
{
    return *data_m;
}

Vector::View::Iterator::pointer
  Vector::View::Iterator::operator->()
{
    return &(*data_m);
}

Vector::View::Iterator::reference
  Vector::View::Iterator::operator[](size_t n)
{
    return *(data_m + n*v_m->gsl_vec_view_m.vector.stride);
}

const Vector::View::Iterator::reference
  Vector::View::Iterator::operator[](size_t n) const
{
    return *(data_m + n*v_m->gsl_vec_view_m.vector.stride);
}

Vector::View::Iterator& Vector::View::Iterator::operator++()
{
    data_m += v_m->gsl_vec_view_m.vector.stride;return *this;
}

Vector::View::Iterator& Vector::View::Iterator::operator--()
{
    data_m -= v_m->gsl_vec_view_m.vector.stride;return *this;
}

Vector::View::Iterator  Vector::View::Iterator::operator++(int)
{
    Iterator tmp(*this);data_m += v_m->gsl_vec_view_m.vector.stride;
    return tmp;
}

Vector::View::Iterator  Vector::View::Iterator::operator--(int)
{
    Iterator tmp(*this);data_m -= v_m->gsl_vec_view_m.vector.stride;return tmp;
}

Vector::View::Iterator& Vector::View::Iterator::operator+=(size_t n)
{
    data_m += n*v_m->gsl_vec_view_m.vector.stride;return *this;
}

Vector::View::Iterator& Vector::View::Iterator::operator-=(size_t n)
{
    data_m -= n*v_m->gsl_vec_view_m.vector.stride;return *this;
}

Vector::View::Iterator Vector::View::Iterator::operator+(size_t n)   const
{
    Iterator tmp(*this);return tmp += n*v_m->gsl_vec_view_m.vector.stride;
}

Vector::View::Iterator Vector::View::Iterator::operator-(size_t n)   const
{
    Iterator tmp(*this);
    return tmp -= n*v_m->gsl_vec_view_m.vector.stride;
}

Vector::View::Iterator::difference_type
  Vector::View::Iterator::operator-(Iterator const& other) const
{
    return (data_m - other.data_m)
        /
        static_cast<difference_type>(v_m->gsl_vec_view_m.vector.stride);
}

bool Vector::View::Iterator::operator<(Iterator const& other)  const
{
    return data_m <  other.data_m;
}

bool Vector::View::Iterator::operator<=(Iterator const& other) const
{
    return data_m <= other.data_m;
}

bool Vector::View::Iterator::operator>(Iterator const& other)  const
{
    return data_m >  other.data_m;
}

bool Vector::View::Iterator::operator>=(Iterator const& other) const
{
    return data_m >= other.data_m;
}

bool Vector::View::Iterator::operator!=(const Iterator &other) const
{
    return data_m != other.data_m;
}

bool Vector::View::Iterator::operator==(const Iterator &other) const
{
    return data_m == other.data_m;
}

/**********************************************************************************************
**********************************************************************************************/


/**********************************************************************************************
* VECTOR VIEW CONST_ITERATOR                                                                                              *
**********************************************************************************************/

Vector::View::Const_Iterator::Const_Iterator()
 : v_m(nullptr), data_m(nullptr)
{}

Vector::View::Const_Iterator::Const_Iterator(const Vector::View* v, size_t i)
 : v_m(v), data_m(v->gsl_vec_view_m.vector.data + i*v->gsl_vec_view_m.vector.stride)
{}

Vector::View::Const_Iterator::reference Vector::View::Const_Iterator::operator*() {return *data_m;}
const Vector::View::Const_Iterator::reference Vector::View::Const_Iterator::operator*() const {return *data_m;}
Vector::View::Const_Iterator::pointer Vector::View::Const_Iterator::operator->() {return &(*data_m);}
Vector::View::Const_Iterator::reference       Vector::View::Const_Iterator::operator[](size_t n)       {return *(data_m + n*v_m->gsl_vec_view_m.vector.stride);}
const Vector::View::Const_Iterator::reference Vector::View::Const_Iterator::operator[](size_t n) const {return *(data_m + n*v_m->gsl_vec_view_m.vector.stride);}

Vector::View::Const_Iterator& Vector::View::Const_Iterator::operator++()       {data_m += v_m->gsl_vec_view_m.vector.stride;return *this;}
Vector::View::Const_Iterator& Vector::View::Const_Iterator::operator--()       {data_m -= v_m->gsl_vec_view_m.vector.stride;return *this;}
Vector::View::Const_Iterator  Vector::View::Const_Iterator::operator++(int)    {Const_Iterator tmp(*this);data_m += v_m->gsl_vec_view_m.vector.stride;return tmp;}
Vector::View::Const_Iterator  Vector::View::Const_Iterator::operator--(int)    {Const_Iterator tmp(*this);data_m -= v_m->gsl_vec_view_m.vector.stride;return tmp;}

Vector::View::Const_Iterator& Vector::View::Const_Iterator::operator+=(size_t n)  {data_m += n*v_m->gsl_vec_view_m.vector.stride;return *this;}
Vector::View::Const_Iterator& Vector::View::Const_Iterator::operator-=(size_t n)  {data_m -= n*v_m->gsl_vec_view_m.vector.stride;return *this;}

Vector::View::Const_Iterator Vector::View::Const_Iterator::operator+(size_t n)   const {Const_Iterator tmp(*this);return tmp += n*v_m->gsl_vec_view_m.vector.stride;}
Vector::View::Const_Iterator Vector::View::Const_Iterator::operator-(size_t n)   const {Const_Iterator tmp(*this);return tmp -= n*v_m->gsl_vec_view_m.vector.stride;}

Vector::View::Const_Iterator::difference_type Vector::View::Const_Iterator::operator-(const Const_Iterator& other) const
{
    return (data_m - other.data_m)
        /
        static_cast<difference_type>(v_m->gsl_vec_view_m.vector.stride);
}

bool Vector::View::Const_Iterator::operator<(const Const_Iterator& other)  const
{
    return data_m <  other.data_m;
}

bool Vector::View::Const_Iterator::operator<=(const Const_Iterator& other) const
{
    return data_m <= other.data_m;
}

bool Vector::View::Const_Iterator::operator>(const Const_Iterator& other)  const
{
    return data_m >  other.data_m;
}

bool Vector::View::Const_Iterator::operator>=(const Const_Iterator& other) const
{
    return data_m >= other.data_m;
}

bool Vector::View::Const_Iterator::operator!=(const Const_Iterator &other) const
{
    return data_m != other.data_m;
}

bool Vector::View::Const_Iterator::operator==(const Const_Iterator &other) const
{
    return data_m == other.data_m;
}

/**********************************************************************************************
**********************************************************************************************/


/**********************************************************************************************
* VECTOR CONST_VIEW                                                                                                              *
**********************************************************************************************/

Vector::Const_View::Const_View(const Vector& v)
 : Const_View(v ,0, v.size())
{}

Vector::Const_View::Const_View(const Vector& v, size_t offset, size_t size)
 : gsl_vec_view_m(gsl_vector_const_subvector(v.gsl_vec_m.get(), offset, size))
{}

Vector::Const_View::Const_View(const Vector& v, size_t offset, size_t stride, size_t size)
 : gsl_vec_view_m(gsl_vector_const_subvector_with_stride(v.gsl_vec_m.get(), offset, stride, size))
{}

Vector::Const_View::Const_View(const Block& b)
 : Const_View(b, 0, b.size())
{}

Vector::Const_View::Const_View(const Block& b, size_t offset, size_t size)
 : gsl_vec_view_m(gsl_vector_const_view_array(b.data() + offset, size))
{}

Vector::Const_View::Const_View(const Block& b, size_t offset, size_t stride, size_t size)
 : gsl_vec_view_m(gsl_vector_const_view_array_with_stride(b.data() + offset, stride, size))
{}

Vector::Const_View::Const_View(const double* data, size_t size)
 : Const_View(data, 0, size)
{}

Vector::Const_View::Const_View(const double* data, size_t offset, size_t size)
 : gsl_vec_view_m(gsl_vector_const_view_array(data + offset, size))
{}

Vector::Const_View::Const_View(const double* data, size_t offset, size_t stride, size_t size)
 : gsl_vec_view_m(gsl_vector_const_view_array_with_stride(data + offset, stride, size))
{}

Vector::Const_View::Const_View(gsl_vector_const_view v)
 : gsl_vec_view_m(v)
{}

Vector::Const_View::operator const Vector() const
{
    return Vector(const_cast<gsl_vector*>(&this->gsl_vec_view_m.vector));
}

const gsl_vector* Vector::Const_View::gsl_data() const
{
    return &this->gsl_vec_view_m.vector;
}

const double& Vector::Const_View::operator[](const size_t i) const
{
    return *gsl_vector_const_ptr(&gsl_vec_view_m.vector, i);
}

size_t Vector::Const_View::size() const
{
    return this->gsl_vec_view_m.vector.size;
}

size_t Vector::Const_View::stride() const
{
    return this->gsl_vec_view_m.vector.stride;
}

const double& Vector::Const_View::at(const size_t i) const
{
    if(!(i < this->size())){
        throw std::out_of_range("Index " + std::to_string(i) + " out of range.");
    }
    return (*this)[i];
}


Vector Vector::Const_View::clone() const
{
    Vector res(this->size());
    res.copy(*this);
    return res;
}

double Vector::Const_View::get(size_t i) const
{
    return gsl_vector_get(&this->gsl_vec_view_m.vector, i);
}


double Vector::Const_View::max() const
{
    return gsl_vector_max(&this->gsl_vec_view_m.vector);
}

double Vector::Const_View::min() const
{
    return gsl_vector_min(&this->gsl_vec_view_m.vector);
}

std::pair<double, double> Vector::Const_View::minmax() const
{
    std::pair<double, double> res;
    gsl_vector_minmax(&this->gsl_vec_view_m.vector, &res.first, &res.second);
    return res;
}

size_t Vector::Const_View::max_index() const
{
    return gsl_vector_max_index(&this->gsl_vec_view_m.vector);
}

size_t Vector::Const_View::min_index() const
{
    return gsl_vector_min_index(&this->gsl_vec_view_m.vector);
}

std::pair<size_t, size_t> Vector::Const_View::minmax_index() const
{
    std::pair<size_t, size_t> res;
    gsl_vector_minmax_index(&this->gsl_vec_view_m.vector, &res.first, &res.second);
    return res;
}

double Vector::Const_View::norm() const
{
    return ::norm(*this);
}

double Vector::Const_View::norm2() const
{
    return ::norm2(*this);
}

double Vector::Const_View::l1_norm() const
{
    return ::l1_norm(*this);
}

bool Vector::Const_View::isnull() const
{
    return gsl_vector_isnull(&this->gsl_vec_view_m.vector);
}
bool Vector::Const_View::ispos() const
{
    return gsl_vector_ispos(&this->gsl_vec_view_m.vector);
}
bool Vector::Const_View::isneg() const
{
    return gsl_vector_isneg(&this->gsl_vec_view_m.vector);
}
bool Vector::Const_View::isnonneg() const
{
    return gsl_vector_isnonneg(&this->gsl_vec_view_m.vector);
}

Vector Vector::Const_View::operator-() const
{
    Vector res(this->size(), 0);
    res -= *this;
    return res;
}

Vector::Const_View Vector::Const_View::view() const
{
    return gsl_vector_const_subvector(&this->gsl_vec_view_m.vector, 0, this->size());
}

Vector::Const_View Vector::Const_View::view(const size_t offset, const size_t size) const
{
    return gsl_vector_const_subvector(&this->gsl_vec_view_m.vector, offset, size);
}

Vector::Const_View Vector::Const_View::view(const size_t offset, const size_t stride, const size_t size) const
{
    return gsl_vector_const_subvector_with_stride(&this->gsl_vec_view_m.vector, offset, stride, size);
}

Vector::Const_View Vector::Const_View::cview() const
{
    return gsl_vector_const_subvector(&this->gsl_vec_view_m.vector, 0, this->size());
}

Vector::Const_View Vector::Const_View::cview(const size_t offset, const size_t size) const
{
    return gsl_vector_const_subvector(&this->gsl_vec_view_m.vector, offset, size);
}

Vector::Const_View Vector::Const_View::cview(const size_t offset, const size_t stride, const size_t size) const
{
    return gsl_vector_const_subvector_with_stride(&this->gsl_vec_view_m.vector, offset, stride, size);
}

Vector::Const_View::const_iterator Vector::Const_View::begin() const noexcept
{
    return Const_Iterator(this, 0);
}

Vector::Const_View::const_iterator Vector::Const_View::cbegin() const noexcept
{
    return Const_Iterator(this, 0);
}


Vector::Const_View::const_iterator Vector::Const_View::end() const noexcept
{
    return Const_Iterator(this, this->size());
}

Vector::Const_View::const_iterator Vector::Const_View::cend() const noexcept
{
    return Const_Iterator(this, this->size());
}

Vector::Const_View::const_reverse_iterator Vector::Const_View::rbegin() const noexcept
{
    return std::reverse_iterator<Const_Iterator>(this->end());
}

Vector::Const_View::const_reverse_iterator Vector::Const_View::crbegin() const noexcept
{
    return std::reverse_iterator<Const_Iterator>(this->cend());
}

Vector::Const_View::const_reverse_iterator Vector::Const_View::rend() const noexcept
{
    return std::reverse_iterator<Const_Iterator>(this->begin());
}

Vector::Const_View::const_reverse_iterator Vector::Const_View::crend() const noexcept
{
    return std::reverse_iterator<Const_Iterator>(this->begin());
}

const double& Vector::Const_View::front() const
{
    return *this->begin();
}

const double& Vector::Const_View::back() const
{
    return *(this->begin() + this->size() - 1);
}

/**********************************************************************************************
**********************************************************************************************/



/**********************************************************************************************
* VECTOR CONST_VIEW CONST_ITERATOR                                                                                 *
**********************************************************************************************/

Vector::Const_View::Const_Iterator::Const_Iterator()
 : v_m(nullptr), data_m(nullptr)
{}

Vector::Const_View::Const_Iterator::Const_Iterator(const Vector::Const_View* v, size_t i)
 : v_m(v), data_m(v->gsl_vec_view_m.vector.data + i*v->gsl_vec_view_m.vector.stride)
{}

Vector::Const_View::Const_Iterator::reference
  Vector::Const_View::Const_Iterator::operator*()
{
    return *data_m;
}

const Vector::Const_View::Const_Iterator::reference
  Vector::Const_View::Const_Iterator::operator*() const
{
    return *data_m;
}

Vector::Const_View::Const_Iterator::pointer
  Vector::Const_View::Const_Iterator::operator->()
{
    return &(*data_m);
}

Vector::Const_View::Const_Iterator::reference
  Vector::Const_View::Const_Iterator::operator[](size_t n)
{
    return *(data_m + n*v_m->gsl_vec_view_m.vector.stride);
}

const Vector::Const_View::Const_Iterator::reference
  Vector::Const_View::Const_Iterator::operator[](size_t n) const
{
    return *(data_m + n*v_m->gsl_vec_view_m.vector.stride);
}

Vector::Const_View::Const_Iterator& Vector::Const_View::Const_Iterator::operator++()
{
    data_m += v_m->gsl_vec_view_m.vector.stride;return *this;
}

Vector::Const_View::Const_Iterator& Vector::Const_View::Const_Iterator::operator--()
{
    data_m -= v_m->gsl_vec_view_m.vector.stride;return *this;
}

Vector::Const_View::Const_Iterator  Vector::Const_View::Const_Iterator::operator++(int)
{
    Const_Iterator tmp(*this);data_m += v_m->gsl_vec_view_m.vector.stride;return tmp;
}

Vector::Const_View::Const_Iterator  Vector::Const_View::Const_Iterator::operator--(int)
{
    Const_Iterator tmp(*this);data_m -= v_m->gsl_vec_view_m.vector.stride;return tmp;
}

Vector::Const_View::Const_Iterator& Vector::Const_View::Const_Iterator::operator+=(size_t n)
{
    data_m += n*v_m->gsl_vec_view_m.vector.stride;return *this;
}

Vector::Const_View::Const_Iterator& Vector::Const_View::Const_Iterator::operator-=(size_t n)
{
    data_m -= n*v_m->gsl_vec_view_m.vector.stride;return *this;
}

Vector::Const_View::Const_Iterator Vector::Const_View::Const_Iterator::operator+(size_t n)   const
{
    Const_Iterator tmp(*this);return tmp += n*v_m->gsl_vec_view_m.vector.stride;
}

Vector::Const_View::Const_Iterator Vector::Const_View::Const_Iterator::operator-(size_t n)   const
{
    Const_Iterator tmp(*this);return tmp -= n*v_m->gsl_vec_view_m.vector.stride;
}

Vector::Const_View::Const_Iterator::difference_type Vector::Const_View::Const_Iterator::operator-(const Const_Iterator& other) const
{
    return (data_m - other.data_m)
        /
        static_cast<difference_type>(v_m->gsl_vec_view_m.vector.stride);
}

bool Vector::Const_View::Const_Iterator::operator<(const Const_Iterator& other)  const
{
    return data_m <  other.data_m;
}

bool Vector::Const_View::Const_Iterator::operator<=(const Const_Iterator& other) const
{
    return data_m <= other.data_m;
}

bool Vector::Const_View::Const_Iterator::operator>(const Const_Iterator& other)  const
{
    return data_m >  other.data_m;
}

bool Vector::Const_View::Const_Iterator::operator>=(const Const_Iterator& other) const
{
    return data_m >= other.data_m;
}

bool Vector::Const_View::Const_Iterator::operator!=(const Const_Iterator &other) const
{
    return data_m != other.data_m;
}

bool Vector::Const_View::Const_Iterator::operator==(const Const_Iterator &other) const
{
    return data_m == other.data_m;
}

/**********************************************************************************************
**********************************************************************************************/


void std::swap(GSL::Vector&a, GSL::Vector& b)
{
    a.swap(b);
}

std::string std::to_string(const GSL::Vector& v)
{
    return v.to_string();
}

#if 0
int main()
{
    Block b(100);

    Vector v(5, 2);
    Vector u(5, 4);
    Vector::View vv(v, 0, 2, 3);
    Vector::View vv2 = v.view();

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

    Vector w = std::move(v);
    Vector::View bv(b);
    bv[0] = 5;
    std::cout << "bv[0] = " << bv[0] << "\n";

    Vector::View::Iterator it(&bv, 0);
    std::cout << "it[0] = " << it[0] << "\n";

    Vector::Const_View cv = w.cview();
    std::cout << "cv[2] = " << cv[2] << "\n";

    std::cout << "u + cv = " << u << " + " << cv << " = " << u + cv <<"\n";

    std::cout << "||cv|| = " << norm(cv) << "\n";
    return 0;
}
#endif
