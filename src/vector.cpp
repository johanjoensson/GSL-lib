#include "vector.h"
#include <gsl/gsl_blas.h>
#include <stdexcept>

using namespace GSL;

std::ostream& GSL::operator<< (std::ostream& os, const BaseVector& a)
{
    return (os << a.to_string());
}

Vector::Vector()
 : BaseVector(), gsl_vec(nullptr)
{}

Vector::Vector(const size_t n)
 :  BaseVector(), gsl_vec(gsl_vector_calloc(n), gsl_vector_free)
{
    if(gsl_vec == nullptr){
        throw std::runtime_error("Memory allocation (gsl_vector_calloc)"
        " failed!");
    }
}

Vector::Vector(const Vector& v)
 :  BaseVector(), gsl_vec(v.gsl_vec)
{}

Vector::Vector(Vector&& v)
 :  BaseVector(), gsl_vec(nullptr)
{
    std::swap(gsl_vec, v.gsl_vec);
}

Vector::Vector(const gsl_vector& v)
 : BaseVector(), gsl_vec(nullptr)
{
    gsl_vec = std::shared_ptr<gsl_vector>(new gsl_vector);
    *gsl_vec = v;
}

Vector::Vector(std::initializer_list<double> l)
 : Vector(l.size())
{
    for(size_t i = 0; i < l.size(); i++){
        gsl_vector_set(gsl_vec.get(), i, l.begin()[i]);
    }
}

Vector::~Vector()
{}

void Vector::normalize() const
{
    double norm = this->norm();
    int stat = gsl_vector_scale(this->gsl_vec.get(), 1./norm);
    if(stat){
		std::string error_str =   gsl_strerror(stat);
		throw std::runtime_error("Error in normalization.\nGSL error: "
        + error_str);
    }
}

double Vector::norm() const
{
    return gsl_blas_dnrm2(this->gsl_vec.get());
}

size_t Vector::dim() const
{
	if(gsl_vec != nullptr){
		return gsl_vec->size;
	}else{
		return 0;
	}
}

Vector& Vector::operator= (const Vector &a)
{
    if(this == &a){
        return *this;
    }

    // this is not part of a matrix
    if(gsl_vec == nullptr || gsl_vec->owner == 1){
        gsl_vec = a.gsl_vec;
        // this is part of a matrix
    }else if(gsl_vec->owner == 0){
        if(a.gsl_vec.get() != nullptr){
            gsl_vector_memcpy(gsl_vec.get(), a.gsl_vec.get());
        }
    }else{
        throw std::runtime_error("Unknown owner value " + std::to_string(gsl_vec->owner));
    }

    return *this;
}

Vector& Vector::operator= (Vector&& a)
{
    // Check if the vector owns the data
    if(gsl_vec == nullptr || gsl_vec->owner == 1){
        std::swap(gsl_vec, a.gsl_vec);
    // If not, this vector is part of a matrix
    // -> copy the data, dont move the reference
    }else if(gsl_vec->owner == 0){
        gsl_vector_memcpy(gsl_vec.get(), a.gsl_vec.get());
    }
    return *this;
}

double& Vector::operator[] (const size_t index)
{
    double *res = gsl_vector_ptr(gsl_vec.get(), index);
    if (res == nullptr){
        throw std::runtime_error("Index out of range!");
    }
    return *res;
}

Vector& Vector::operator+= (const Vector& b)
{
    int stat = gsl_vector_add(this->gsl_vec.get(), b.gsl_vec.get());
    if(stat){
		std::string error_str =   gsl_strerror(stat);
		throw std::runtime_error("Error in vector addition.\nGSL error: "
        + error_str);
	}
    return *this;
}

Vector& Vector::operator-= (const Vector& b)
{
    int stat = gsl_vector_sub(this->gsl_vec.get(), b.gsl_vec.get());
    if(stat){
		std::string error_str =   gsl_strerror(stat);
		throw std::runtime_error("Error in vector subtraction.\nGSL error: "
        + error_str);
	}
    return *this;
}

Vector& Vector::operator*= (const Vector& b)
{
    int stat = gsl_vector_mul(this->gsl_vec.get(), b.gsl_vec.get());
    if(stat){
		std::string error_str =   gsl_strerror(stat);
		throw std::runtime_error("Error in vector multiplication.\nGSL error: "
        + error_str);
	}
    return *this;
}

Vector& Vector::operator/= (const Vector& b)
{
    int stat = gsl_vector_div(this->gsl_vec.get(), b.gsl_vec.get());
    if(stat){
		std::string error_str =   gsl_strerror(stat);
		throw std::runtime_error("Error in vector division.\nGSL error: "
        + error_str);
	}
    return *this;
}

Vector& Vector::operator*= (const double s)
{
    int stat = gsl_vector_scale(this->gsl_vec.get(), s);
    if(stat){
		std::string error_str =   gsl_strerror(stat);
		throw std::runtime_error("Error in vector multiplication.\nGSL error: "
        + error_str);
	}
    return *this;
}

Vector& Vector::operator/= (const double s)
{
    int stat = gsl_vector_scale(this->gsl_vec.get(), 1./s);
    if(stat){
		std::string error_str =   gsl_strerror(stat);
		throw std::runtime_error("Error in vector division.\nGSL error: "
        + error_str);
	}
    return *this;
}

Vector GSL::operator+(Vector a, const Vector& b)
{
	Vector tmp(a.gsl_vec->size);
	gsl_vector_memcpy(tmp.gsl_vec.get(), a.gsl_vec.get());
	return tmp += b;
}

Vector GSL::operator-(Vector a, const Vector& b)
{
	Vector tmp(a.gsl_vec->size);
	gsl_vector_memcpy(tmp.gsl_vec.get(), a.gsl_vec.get());
	return tmp -= b;
}

Vector GSL::operator*(Vector a, const Vector& b)
{
	Vector tmp(a.gsl_vec->size);
	gsl_vector_memcpy(tmp.gsl_vec.get(), a.gsl_vec.get());
	return tmp *= b;
}

Vector GSL::operator/(Vector a, const Vector& b)
{
	Vector tmp(a.gsl_vec->size);
	gsl_vector_memcpy(tmp.gsl_vec.get(), a.gsl_vec.get());
	return tmp /= b;
}

Vector GSL::operator*(Vector a, const double s)
{
	Vector tmp(a.gsl_vec->size);
	gsl_vector_memcpy(tmp.gsl_vec.get(), a.gsl_vec.get());
	return tmp *= s;
}

Vector GSL::operator* (const double s, Vector a)
{
    return a*s;
}

Vector GSL::operator/(Vector a, const double s)
{
	Vector tmp(a.gsl_vec->size);
	gsl_vector_memcpy(tmp.gsl_vec.get(), a.gsl_vec.get());
	return tmp /= s;
}

Vector GSL::operator-(const Vector& a)
{
    Vector res(a.gsl_vec.get()->size);

    return res - a;
}

std::string Vector::to_string() const
{
    std::string res = "";
    double tmp = 0;
    res += "( ";
    for(unsigned int i = 0; i < this->gsl_vec.get()->size; i++){
        tmp = gsl_vector_get(this->gsl_vec.get(), i);
        res += std::to_string(tmp);
        if(i < this->gsl_vec.get()->size - 1){
            res += ",";
        }
        res += " ";
    }
    res += ")";
    return res;
}

double GSL::dot(const Vector& a, const Vector& b)
{
    size_t size_a = a.gsl_vec.get()->size;
    size_t size_b = b.gsl_vec.get()->size;
    if(size_a != size_b){
		throw std::runtime_error("Error in dot product!\nDot product "
        "(scalar product) only defined for vectors of equal length!");
    }


    double res;
    int stat = gsl_blas_ddot(a.gsl_vec.get(), b.gsl_vec.get(), &res);
    if(stat){
		std::string error_str =   gsl_strerror(stat);
		throw std::runtime_error("Error in vector dot product.\nGSL error: "
        + error_str);
	}
    return res;
}


Vector GSL::cross(const Vector& a, const Vector& b)
{
    size_t size_a = a.gsl_vec.get()->size;
    size_t size_b = b.gsl_vec.get()->size;
    if(size_a != size_b){
		throw std::runtime_error("Error in cross product!\nCross product "
        "(vector product) only defined for vectors of equal length!");
    } else if(size_a != 3 || size_b !=3){
		throw std::runtime_error("Error in cross product!\nCross product "
        "(vector product) only defined for vectors of length 3!");
    }

    double a_tmp[3], b_tmp[3];
    a_tmp[0] = gsl_vector_get(a.gsl_vec.get(), 0);
    b_tmp[0] = gsl_vector_get(b.gsl_vec.get(), 0);
    a_tmp[1] = gsl_vector_get(a.gsl_vec.get(), 1);
    b_tmp[1] = gsl_vector_get(b.gsl_vec.get(), 1);
    a_tmp[2] = gsl_vector_get(a.gsl_vec.get(), 2);
    b_tmp[2] = gsl_vector_get(b.gsl_vec.get(), 2);
    Vector res(3);

    (res)[0] = a_tmp[1]*b_tmp[2] - a_tmp[2]*b_tmp[1];
    (res)[1] = a_tmp[2]*b_tmp[0] - a_tmp[0]*b_tmp[2];
    (res)[2] = a_tmp[0]*b_tmp[1] - a_tmp[1]*b_tmp[0];

    return res;
}

// Make this a copy of the Vector a
// Copy the data, not just the pointers!
void Vector::copy(const Vector& a)
{
    if(this->gsl_vec.get() == nullptr){
        throw std::runtime_error("Error in vector allocation!");
    }
    int stat = gsl_vector_memcpy(this->gsl_vec.get(), a.gsl_vec.get());
    if(stat){
		std::string error_str =   gsl_strerror(stat);
		throw std::runtime_error("Error in memory copying.\nGSL error: "
        + error_str);
	}
}

bool GSL::operator==(const Vector& a, const Vector& b)
{
    if(a.gsl_vec.get() == nullptr && b.gsl_vec.get() == nullptr){
        return true;
    }else if(a.gsl_vec.get() == nullptr || b.gsl_vec.get() == nullptr){
        return false;
    }
    return gsl_vector_equal(a.gsl_vec.get(), b.gsl_vec.get());
}

bool GSL::operator!=(const Vector& a, const Vector& b)
{
    return !(a == b);
}

bool Vector::iterator::operator==(const Vector::iterator& it) const
{
    return data_m == it.data_m;
}

bool Vector::iterator::operator!=(const Vector::iterator& it) const
{
    return !(*this == it);
}

bool Vector::iterator::operator<(const Vector::iterator& it) const
{
    return data_m < it.data_m;
}

bool Vector::iterator::operator>(const Vector::iterator& it) const
{
    return data_m > it.data_m;
}

bool Vector::iterator::operator<=(const Vector::iterator& it) const
{
    return !(*this > it);
}

bool Vector::iterator::operator>=(const Vector::iterator& it) const
{
    return !(*this < it);
}

Vector::iterator& Vector::iterator::operator++()
{
    (this->data_m)++;
    return *this;
}

Vector::iterator Vector::iterator::operator++(int)
{
    Vector::iterator tmp = *this;
    (*this)++;
    return tmp;
}


Vector::iterator& Vector::iterator::operator--()
{
    (this->data_m)--;
    return *this;
}

Vector::iterator Vector::iterator::operator--(int)
{
    Vector::iterator tmp = *this;
    (*this)--;
    return tmp;
}

Vector::iterator& Vector::iterator::operator+=(Vector::size_type n)
{
    this->data_m += n;
    return *this;
}


Vector::iterator Vector::iterator::operator+(Vector::size_type n) const
{
    Vector::iterator tmp = *this;
    tmp += n;
    return tmp;
}

Vector::iterator GSL::operator+(Vector::size_type n, const Vector::iterator& it)
{
    Vector::iterator tmp = it;
    tmp += n;
    return tmp;
}

Vector::iterator& Vector::iterator::operator-=(Vector::size_type n)
{
    this->data_m -= n;
    return *this;
}


Vector::iterator Vector::iterator::operator-(Vector::size_type n) const
{
    Vector::iterator tmp = *this;
    tmp -= n;
    return tmp;
}


Vector::difference_type Vector::iterator::operator-(const Vector::iterator it) const
{
    return data_m - it.data_m;
}


Vector::reference Vector::iterator::operator*() const
{
    return *data_m;
}

Vector::const_iterator::const_iterator(const Vector::iterator& it)
 : data_m(it.data_m)
{}

bool Vector::const_iterator::operator==(const Vector::const_iterator& it) const
{
    return data_m == it.data_m;
}

bool Vector::const_iterator::operator!=(const Vector::const_iterator& it) const
{
    return !(*this == it);
}

bool Vector::const_iterator::operator<(const Vector::const_iterator& it) const
{
    return data_m < it.data_m;
}

bool Vector::const_iterator::operator>(const Vector::const_iterator& it) const
{
    return data_m > it.data_m;
}

bool Vector::const_iterator::operator<=(const Vector::const_iterator& it) const
{
    return !(*this > it);
}

bool Vector::const_iterator::operator>=(const Vector::const_iterator& it) const
{
    return !(*this < it);
}


Vector::const_iterator& Vector::const_iterator::operator++()
{
    (this->data_m)++;
    return *this;
}

Vector::const_iterator Vector::const_iterator::operator++(int)
{
    Vector::const_iterator tmp = *this;
    (*this)++;
    return tmp;
}

Vector::const_iterator& Vector::const_iterator::operator--()
{
    (this->data_m)--;
    return *this;
}

Vector::const_iterator Vector::const_iterator::operator--(int)
{
    Vector::const_iterator tmp = *this;
    (*this)--;
    return tmp;
}

Vector::const_iterator& Vector::const_iterator::operator+=(size_type n)
{
    this->data_m += n;
    return *this;
}

Vector::const_iterator Vector::const_iterator::operator+(size_type n) const
{
    Vector::const_iterator tmp = *this;
    tmp += n;
    return tmp;
}

Vector::const_iterator GSL::operator+(Vector::size_type n, const Vector::const_iterator& it)
{
    Vector::const_iterator tmp = it;
    tmp += n;
    return tmp;
}

Vector::const_iterator& Vector::const_iterator::operator-=(Vector::size_type n)
{
    this->data_m -= n;
    return *this;
}

Vector::const_iterator Vector::const_iterator::operator-(Vector::size_type n) const
{
    Vector::const_iterator tmp = *this;
    tmp -= n;
    return tmp;
}

Vector::difference_type Vector::const_iterator::operator-(Vector::const_iterator it) const
{
    return data_m - it.data_m;
}

const Vector::reference Vector::const_iterator::operator*() const
{
    return *data_m;
}

Vector::iterator Vector::begin()
{
    return iterator(gsl_vector_ptr(gsl_vec.get(), 0));
}

Vector::const_iterator Vector::begin() const
{
    return const_iterator(gsl_vector_ptr(gsl_vec.get(), 0));
}

Vector::const_iterator Vector::cbegin() const
{
    return const_iterator(gsl_vector_ptr(gsl_vec.get(), 0));
}

Vector::iterator Vector::end()
{
    return this->begin() + gsl_vec.get()->size;
}

Vector::const_iterator Vector::end() const
{
    return this->begin() + gsl_vec.get()->size;
}
Vector::const_iterator Vector::cend() const
{
    return this->begin() + gsl_vec.get()->size;
}

Vector::reverse_iterator Vector::rbegin()
{
    return reverse_iterator(--(this->end()));
}

Vector::const_reverse_iterator Vector::rbegin() const
{
    return const_reverse_iterator(--(this->end()));
}

Vector::const_reverse_iterator Vector::crbegin() const
{
    return const_reverse_iterator(--(this->cend()));
}

Vector::reverse_iterator Vector::rend()
{
    return reverse_iterator(--(this->begin()));
}

Vector::const_reverse_iterator Vector::rend() const
{
    return const_reverse_iterator(--(this->begin()));
}

Vector::const_reverse_iterator Vector::crend() const
{
    return const_reverse_iterator(--(this->cbegin()));
}

Vector::reference Vector::front()
{
    return *(this->begin());
}

Vector::const_reference Vector::front() const
{
    return *(this->cbegin());
}

Vector::reference Vector::back()
{
    return *(this->rbegin());
}

Vector::const_reference Vector::back() const
{
    return *(this->crend());
}
/*
template<class ...Args>
void emplace_front(Args&&...); //optional
template<class ...Args>
void emplace_back(Args&&...); //optional
void push_front(const T&); //optional
void push_front(T&&); //optional
void push_back(const T&); //optional
void push_back(T&&); //optional
void pop_front(); //optional
void pop_back(); //optional
reference operator[](size_type); //optional
const_reference operator[](size_type) const; //optional
reference at(size_type); //optional
const_reference at(size_type) const; //optional

template<class ...Args>
iterator emplace(const_iterator, Args&&...); //optional
iterator insert(const_iterator, const T&); //optional
iterator insert(const_iterator, T&&); //optional
iterator insert(const_iterator, size_type, T&); //optional
template<class iter>
iterator insert(const_iterator, iter, iter); //optional
iterator insert(const_iterator, std::initializer_list<T>); //optional
iterator erase(const_iterator); //optional
iterator erase(const_iterator, const_iterator); //optional
void clear(); //optional
template<class iter>
void assign(iter, iter); //optional
void assign(std::initializer_list<T>); //optional
void assign(size_type, const T&); //optional
*/
