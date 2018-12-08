#include "complex_vector.h"
#include <gsl/gsl_blas.h>
#include <gsl/gsl_complex_math.h>

using namespace GSL;

Complex_Vector::Complex_Vector(const size_t n)
 : BaseVector(), gsl_vec(gsl_vector_complex_calloc(n), gsl_vector_complex_free)
{
    if(gsl_vec.get() == nullptr){
        throw std::runtime_error("Memory allocation (gsl_vector_complex_alloc)"
        " failed!");
    }
}


Complex_Vector::Complex_Vector(const Complex_Vector& v)
 : BaseVector(),  gsl_vec(v.gsl_vec)
{}

Complex_Vector::Complex_Vector(Complex_Vector&& v)
 : BaseVector(), gsl_vec(nullptr)
{
    std::swap(gsl_vec, v.gsl_vec);
}

Complex_Vector::Complex_Vector(const gsl_vector_complex& v)
 : Complex_Vector(v.size)
{
    gsl_vector_complex_memcpy(gsl_vec.get(), &v);
    gsl_vec->owner = 0;
}

Complex_Vector::Complex_Vector(std::initializer_list<Complex> l)
 : Complex_Vector(l.size())
{
    for(size_t i = 0; i < l.size(); i++){
        gsl_vector_complex_set(gsl_vec.get(), i, *l.begin()[i].gsl_c);
    }
}

Complex_Vector::~Complex_Vector()
{}

void Complex_Vector::normalize() const
{
    double norm = this->norm();
    int stat = gsl_vector_complex_scale(this->gsl_vec.get(), gsl_complex_rect(1./norm, 0.));
    if(stat){
		std::string error_str =   gsl_strerror(stat);
		throw std::runtime_error("Error in normalization.\nGSL error: "
        + error_str);
    }
}

double Complex_Vector::norm() const
{
    return gsl_blas_dznrm2(this->gsl_vec.get());
}

Complex_Vector& Complex_Vector::operator= (const Complex_Vector &a)
{
    if(this == &a){
        return *this;
    }

    // this is not part of a matrix
    if(gsl_vec->owner == 1){
        gsl_vec = a.gsl_vec;
        // this is part of a matrix
    }else if(gsl_vec->owner == 0){
        if(a.gsl_vec.get() != nullptr){
            gsl_vector_complex_memcpy(gsl_vec.get(), a.gsl_vec.get());
        }
    }else{
        throw std::runtime_error("Unknown owner value " + std::to_string(gsl_vec->owner));
    }

    return *this;
}

Complex_Vector& Complex_Vector::operator= (Complex_Vector&& a)
{
    if(gsl_vec->owner == 1){
        std::swap(gsl_vec, a.gsl_vec);
    }else if(gsl_vec->owner == 0){
        if(a.gsl_vec.get() != nullptr){
            gsl_vector_complex_memcpy(gsl_vec.get(), a.gsl_vec.get());
        }
    }
    return *this;
}

Complex Complex_Vector::operator[] (const size_t index)
{
    gsl_complex* res = gsl_vector_complex_ptr(gsl_vec.get(), index);
    if(res == nullptr){
        throw std::runtime_error("Index out of range!");
    }

    return Complex(res);
}

Complex_Vector& Complex_Vector::operator+= (const Complex_Vector& b)
{
    int stat = gsl_vector_complex_add(this->gsl_vec.get(), b.gsl_vec.get());
    if(stat){
		std::string error_str =   gsl_strerror(stat);
		throw std::runtime_error("Error in vector addition.\nGSL error: "
        + error_str);
	}
    return *this;
}

Complex_Vector& Complex_Vector::operator-= (const Complex_Vector& b)
{
    int stat = gsl_vector_complex_sub(this->gsl_vec.get(), b.gsl_vec.get());
    if(stat){
		std::string error_str =   gsl_strerror(stat);
		throw std::runtime_error("Error in vector subtraction.\nGSL error: "
        + error_str);
	}
    return *this;
}

Complex_Vector& Complex_Vector::operator*= (const Complex_Vector& b)
{
    int stat = gsl_vector_complex_mul(this->gsl_vec.get(), b.gsl_vec.get());
    if(stat){
		std::string error_str =   gsl_strerror(stat);
		throw std::runtime_error("Error in vector multiplication.\nGSL error: "
        + error_str);
	}
    return *this;
}

Complex_Vector& Complex_Vector::operator/= (const Complex_Vector& b)
{
    int stat = gsl_vector_complex_div(this->gsl_vec.get(), b.gsl_vec.get());
    if(stat){
		std::string error_str =   gsl_strerror(stat);
		throw std::runtime_error("Error in vector division.\nGSL error: "
        + error_str);
	}
    return *this;
}

Complex_Vector& Complex_Vector::operator*= (const double s)
{
    int stat = gsl_vector_complex_scale(this->gsl_vec.get(), gsl_complex_rect(s,0.));
    if(stat){
		std::string error_str =   gsl_strerror(stat);
		throw std::runtime_error("Error in vector multiplication.\nGSL error: "
        + error_str);
	}
    return *this;
}

Complex_Vector& Complex_Vector::operator/= (const double s)
{
    int stat = gsl_vector_complex_scale(this->gsl_vec.get(), gsl_complex_rect(1./s,0.));
    if(stat){
		std::string error_str =   gsl_strerror(stat);
		throw std::runtime_error("Error in vector division.\nGSL error: "
        + error_str);
	}
    return *this;
}

Complex_Vector Complex_Vector::operator+ (const Complex_Vector& b) const
{
    Complex_Vector res(this->gsl_vec.get()->size);
    int stat = gsl_vector_complex_memcpy(res.gsl_vec.get(), this->gsl_vec.get());
    if(stat){
		std::string error_str =   gsl_strerror(stat);
		throw std::runtime_error("Error in memory copying.\nGSL error: "
        + error_str);
	}
    stat = gsl_vector_complex_add(res.gsl_vec.get(), b.gsl_vec.get());
    if(stat){
		std::string error_str =   gsl_strerror(stat);
		throw std::runtime_error("Error in vector addition.\nGSL error: "
        + error_str);
	}

    return res;
}

Complex_Vector Complex_Vector::operator- (const Complex_Vector& b) const
{
    Complex_Vector res(this->gsl_vec.get()->size);
    int stat = gsl_vector_complex_memcpy(res.gsl_vec.get(), this->gsl_vec.get());
    if(stat){
		std::string error_str =   gsl_strerror(stat);
		throw std::runtime_error("Error in memory copying.\nGSL error: "
        + error_str);
	}
    stat = gsl_vector_complex_sub(res.gsl_vec.get(), b.gsl_vec.get());
    if(stat){
		std::string error_str =   gsl_strerror(stat);
		throw std::runtime_error("Error in vector subtraction.\nGSL error: "
        + error_str);
	}

    return res;
}

Complex_Vector Complex_Vector::operator* (const Complex_Vector& b) const
{
    Complex_Vector res(this->gsl_vec.get()->size);
    int stat = gsl_vector_complex_memcpy(res.gsl_vec.get(), this->gsl_vec.get());
    if(stat){
		std::string error_str =   gsl_strerror(stat);
		throw std::runtime_error("Error in memory copying.\nGSL error: "
        + error_str);
	}
    stat = gsl_vector_complex_mul(res.gsl_vec.get(), b.gsl_vec.get());
    if(stat){
		std::string error_str =   gsl_strerror(stat);
		throw std::runtime_error("Error in vector multiplication.\nGSL error: "
        + error_str);
	}

    return res;
}

Complex_Vector Complex_Vector::operator/ (const Complex_Vector& b) const
{
    Complex_Vector res(this->gsl_vec.get()->size);
    int stat = gsl_vector_complex_memcpy(res.gsl_vec.get(), this->gsl_vec.get());
    if(stat){
		std::string error_str =   gsl_strerror(stat);
		throw std::runtime_error("Error in memory copying.\nGSL error: "
        + error_str);
	}
    stat = gsl_vector_complex_div(res.gsl_vec.get(), b.gsl_vec.get());
    if(stat){
		std::string error_str =   gsl_strerror(stat);
		throw std::runtime_error("Error in vector division.\nGSL error: "
        + error_str);
	}

    return res;
}

Complex_Vector Complex_Vector::operator* (const double& s) const
{
    Complex_Vector res(this->gsl_vec.get()->size);
    int stat = gsl_vector_complex_memcpy(res.gsl_vec.get(), this->gsl_vec.get());
    if(stat){
		std::string error_str =   gsl_strerror(stat);
		throw std::runtime_error("Error in memory copying.\nGSL error: "
        + error_str);
	}
    stat = gsl_vector_complex_scale(res.gsl_vec.get(), gsl_complex_rect(s, 0.));
    if(stat){
		std::string error_str =   gsl_strerror(stat);
		throw std::runtime_error("Error in vector scaling.\nGSL error: "
        + error_str);
	}

    return res;
}

Complex_Vector GSL::operator* (const double& s, const Complex_Vector& a)
{
    return a*s;
}

Complex_Vector Complex_Vector::operator/ (const double& s) const
{
    Complex_Vector res(this->gsl_vec.get()->size);
    int stat = gsl_vector_complex_memcpy(res.gsl_vec.get(), this->gsl_vec.get());
    if(stat){
		std::string error_str =   gsl_strerror(stat);
		throw std::runtime_error("Error in memory copying.\nGSL error: "
        + error_str);
	}
    stat = gsl_vector_complex_scale(res.gsl_vec.get(), gsl_complex_rect(1./s,0));
    if(stat){
		std::string error_str =   gsl_strerror(stat);
		throw std::runtime_error("Error in vector scaling.\nGSL error: "
        + error_str);
	}

    return res;
}

Complex_Vector GSL::operator- (const Complex_Vector& a)
{
    Complex_Vector res(a.gsl_vec.get()->size);

    return res - a;
}

bool GSL::operator==(const Complex_Vector& u, const Complex_Vector& v)
{
    return gsl_vector_complex_equal(u.gsl_vec.get(), v.gsl_vec.get());
}

bool GSL::operator!=(const Complex_Vector& u, const Complex_Vector& v)
{
    return !(u == v);
}

std::string Complex_Vector::to_string() const
{
    std::string res = "";
    Complex tmp(0,0);
    res += "( ";
    for(unsigned int i = 0; i < this->gsl_vec.get()->size; i++){
        tmp = Complex(gsl_vector_complex_get(this->gsl_vec.get(), i));
        res += tmp.to_string();
        if(i < this->gsl_vec.get()->size - 1){
            res += ",";
        }
        res += " ";
    }
    res += ")";
    return res;
}


Complex GSL::dot(const Complex_Vector& a, const Complex_Vector& b)
{
    size_t size_a = a.gsl_vec.get()->size;
    size_t size_b = b.gsl_vec.get()->size;
    if(size_a != size_b){
		throw std::runtime_error("Error in dot product!\nDot product "
        "(scalar product) only defined for vectors of equal length!");
    }


    gsl_complex res = gsl_complex_rect(0,0);
    int stat = gsl_blas_zdotc(a.gsl_vec.get(), b.gsl_vec.get(), &res);
    if(stat){
		std::string error_str =   gsl_strerror(stat);
		throw std::runtime_error("Error in vector dot product.\nGSL error: "
        + error_str);
	}
    return Complex(res);
}


Complex_Vector GSL::cross(const Complex_Vector& a, const Complex_Vector& b)
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

    Complex a_tmp[3], b_tmp[3], tmp;
    a_tmp[0] = Complex(gsl_vector_complex_get(a.gsl_vec.get(), 0));
    b_tmp[0] = Complex(gsl_vector_complex_get(b.gsl_vec.get(), 0));
    a_tmp[1] = Complex(gsl_vector_complex_get(a.gsl_vec.get(), 1));
    b_tmp[1] = Complex(gsl_vector_complex_get(b.gsl_vec.get(), 1));
    a_tmp[2] = Complex(gsl_vector_complex_get(a.gsl_vec.get(), 2));
    b_tmp[2] = Complex(gsl_vector_complex_get(b.gsl_vec.get(), 2));
    Complex_Vector res(3);

    tmp  = a_tmp[1]*b_tmp[2] - a_tmp[2]*b_tmp[1];
    (res)[0] = gsl_complex_rect(tmp.re, tmp.im);
    tmp = a_tmp[2]*b_tmp[0] - a_tmp[0]*b_tmp[2];
    (res)[1] = gsl_complex_rect(tmp.re, tmp.im);
    tmp = a_tmp[0]*b_tmp[1] - a_tmp[1]*b_tmp[0];
    (res)[2] = gsl_complex_rect(tmp.re, tmp.im);

    return res;
}

// Make this a copy of the Vector a
// Copy the data, not just the pointers!
void Complex_Vector::copy(const Complex_Vector& a)
{
    if(this->gsl_vec.get() == nullptr){
        throw std::runtime_error("Error in vector allocation!");
    }
    int stat = gsl_vector_complex_memcpy(this->gsl_vec.get(), a.gsl_vec.get());
    if(stat){
		std::string error_str =   gsl_strerror(stat);
		throw std::runtime_error("Error in memory copying.\nGSL error: "
        + error_str);
	}
}

void Complex_Vector::set(size_t i, const Complex& z)
{
    gsl_vector_complex_set(this->gsl_vec.get(), i, *z.gsl_c);
}

Complex Complex_Vector::get(size_t i)
{
    return Complex(gsl_vector_complex_get(this->gsl_vec.get(), i));
}
