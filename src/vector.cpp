#include "vector.h"
#include <gsl/gsl_blas.h>
#include <stdexcept>

using namespace GSL;

BaseVector::~BaseVector()
{}


BaseVector::BaseVector()
{}

std::ostream& GSL::operator<< (std::ostream& os, const BaseVector& a)
{
    return (os << a.to_string());
}

Vector::Vector()
: BaseVector(), gsl_vec(nullptr)
{}

Vector::Vector(const size_t n)
 : BaseVector()
{
    gsl_vec = std::shared_ptr<gsl_vector>(gsl_vector_calloc(n), gsl_vector_free);
    if(gsl_vec == nullptr){
        throw std::runtime_error("Memory allocation (gsl_vector_calloc)"
        " failed!");
    }
}

Vector::Vector(Vector& v)
 : BaseVector(), gsl_vec(v.gsl_vec)
{}

Vector::Vector(const Vector& v)
 : BaseVector(), gsl_vec(v.gsl_vec)
{}

Vector::Vector(Vector&& v)
 : BaseVector(), gsl_vec(nullptr)
{
    std::swap(gsl_vec, v.gsl_vec);
}

Vector::Vector(gsl_vector& v)
 : Vector()
{
    gsl_vec = std::shared_ptr<gsl_vector>(new gsl_vector);
    *gsl_vec = v;
    gsl_vec->owner = 0;
}


Vector::Vector(const gsl_vector& v)
 : Vector()
{
    gsl_vec = std::shared_ptr<gsl_vector>(new gsl_vector);
    *gsl_vec = v;
    gsl_vec->owner = 0;
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
    if(gsl_vec == nullptr || gsl_vec->owner == 1){
        std::swap(gsl_vec, a.gsl_vec);
    }else if(gsl_vec->owner == 0){
        gsl_vector_memcpy(gsl_vec.get(), a.gsl_vec.get());
    }else{
        throw std::runtime_error("Unknown owner value " + std::to_string(gsl_vec->owner));
    }

    return *this;
}

double& Vector::operator[] (const int index)
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


Vector Vector::operator+ (const Vector& b) const
{
    Vector res(this->gsl_vec.get()->size);

    int stat = gsl_vector_memcpy(res.gsl_vec.get(), this->gsl_vec.get());
    if(stat){
		std::string error_str =   gsl_strerror(stat);
		throw std::runtime_error("Error in memory copying.\nGSL error: "
        + error_str);
	}

    stat = gsl_vector_add(res.gsl_vec.get(), b.gsl_vec.get());
    if(stat){
		std::string error_str =   gsl_strerror(stat);
		throw std::runtime_error("Error in vector addition.\nGSL error: "
        + error_str);
	}

    return res;
}


Vector Vector::operator- (const Vector& b) const
{
    Vector res(this->gsl_vec.get()->size);
    int stat = gsl_vector_memcpy(res.gsl_vec.get(), this->gsl_vec.get());
    if(stat){
		std::string error_str =   gsl_strerror(stat);
		throw std::runtime_error("Error in memory copying.\nGSL error: "
        + error_str);
	}
    stat = gsl_vector_sub(res.gsl_vec.get(), b.gsl_vec.get());
    if(stat){
		std::string error_str =   gsl_strerror(stat);
		throw std::runtime_error("Error in vector subtraction.\nGSL error: "
        + error_str);
	}

    return res;
}

Vector Vector::operator* (const Vector& b) const
{
    Vector res(this->gsl_vec.get()->size);
    int stat = gsl_vector_memcpy(res.gsl_vec.get(), this->gsl_vec.get());
    if(stat){
		std::string error_str =   gsl_strerror(stat);
		throw std::runtime_error("Error in memory copying.\nGSL error: "
        + error_str);
	}
    stat = gsl_vector_mul(res.gsl_vec.get(), b.gsl_vec.get());
    if(stat){
		std::string error_str =   gsl_strerror(stat);
		throw std::runtime_error("Error in vector multiplication.\nGSL error: "
        + error_str);
	}

    return res;
}

Vector Vector::operator/ (const Vector& b) const
{
    Vector res(this->gsl_vec.get()->size);
    int stat = gsl_vector_memcpy(res.gsl_vec.get(), this->gsl_vec.get());
    if(stat){
		std::string error_str =   gsl_strerror(stat);
		throw std::runtime_error("Error in memory copying.\nGSL error: "
        + error_str);
	}
    stat = gsl_vector_div(res.gsl_vec.get(), b.gsl_vec.get());
    if(stat){
		std::string error_str =   gsl_strerror(stat);
		throw std::runtime_error("Error in vector division.\nGSL error: "
        + error_str);
	}

    return res;
}

Vector Vector::operator* (const double& s) const
{
    Vector res(this->gsl_vec.get()->size);
    int stat = gsl_vector_memcpy(res.gsl_vec.get(), this->gsl_vec.get());
    if(stat){
		std::string error_str =   gsl_strerror(stat);
		throw std::runtime_error("Error in memory copying.\nGSL error: "
        + error_str);
	}
    stat = gsl_vector_scale(res.gsl_vec.get(), s);
    if(stat){
		std::string error_str =   gsl_strerror(stat);
		throw std::runtime_error("Error in vector scaling.\nGSL error: "
        + error_str);
	}

    return res;
}

Vector GSL::operator* (const double& s, const Vector& a)
{
    return a*s;
}

Vector Vector::operator/ (const double& s) const
{

    Vector res(this->gsl_vec.get()->size);
    int stat = gsl_vector_memcpy(res.gsl_vec.get(), this->gsl_vec.get());
    if(stat){
		std::string error_str =   gsl_strerror(stat);
		throw std::runtime_error("Error in memory copying.\nGSL error: "
        + error_str);
	}
    stat = gsl_vector_scale(res.gsl_vec.get(), 1./s);
    if(stat){
		std::string error_str =   gsl_strerror(stat);
		throw std::runtime_error("Error in vector scaling.\nGSL error: "
        + error_str);
	}

    return res;
}

Vector GSL::operator- (const Vector& a)
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
    int size_a = a.gsl_vec.get()->size;
    int size_b = b.gsl_vec.get()->size;
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
    int size_a = a.gsl_vec.get()->size;
    int size_b = b.gsl_vec.get()->size;
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
/*******************************************************************************
*!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
*! This is not implemented correctly, something is wrong!
*!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
*******************************************************************************/
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
    return gsl_vector_equal(a.gsl_vec.get(), b.gsl_vec.get());
}

bool GSL::operator!=(const Vector& a, const Vector& b)
{
    return !(a == b);
}
