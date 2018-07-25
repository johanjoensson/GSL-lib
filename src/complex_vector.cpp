#include "complex_vector.h"
#include <gsl/gsl_blas.h>
#include <gsl/gsl_complex_math.h>

using namespace GSL;
Complex_Vector::Complex_Vector()
{
    gsl_vec = nullptr;
    data = nullptr;
    count = nullptr;
}

Complex_Vector::Complex_Vector(const size_t n)
{
    gsl_vec = gsl_vector_complex_calloc(n);
    if(gsl_vec == nullptr){
        throw std::runtime_error("Memory allocation (gsl_vector_complex_alloc)"
        " failed!");
    }
    data = gsl_vec->data;
    count = new size_t;
    *count = 1;
}

Complex_Vector::Complex_Vector(Complex_Vector& v)
 : gsl_vec(v.gsl_vec), data(v.data), count(v.count)
{
    (*count)++;
}

Complex_Vector::Complex_Vector(const Complex_Vector& v)
 : gsl_vec(v.gsl_vec), data(v.data), count(v.count)
{
    (*count)++;
}

Complex_Vector::Complex_Vector(Complex_Vector&& v)
 : gsl_vec(v.gsl_vec), data(v.data), count(nullptr)
{
    std::swap(count, v.count);
    v.gsl_vec = nullptr;
    v.data = nullptr;
}

Complex_Vector::~Complex_Vector()
{
    // Make sure there is an allocated gsl_vector_complex
    if(count != nullptr){
        // Reduce the number of references to the gsl_vector_complex by one
        *count -= 1;
        // If there are no more references to the vector, deallocate the memory
        if(*count <= 0){
            delete count;
            if(gsl_vec != nullptr){
                gsl_vector_complex_free(gsl_vec);
            }
        }
    }
}

void Complex_Vector::normalize() const
{
    double norm = this->norm();
    int stat = gsl_vector_complex_scale(this->gsl_vec, gsl_complex_rect(1./norm, 0.));
    if(stat){
		std::string error_str =   gsl_strerror(stat);
		throw std::runtime_error("Error in normalization.\nGSL error: "
        + error_str);
    }
}

double Complex_Vector::norm() const
{
    return gsl_blas_dznrm2(this->gsl_vec);
}

Complex_Vector& Complex_Vector::operator= (const Complex_Vector &a)
{
    // If &a and this are the same object, do nothing
    // especially do not deallocate any memory!
    if(this == &a){
        return *this;
    }
    if(this->gsl_vec != nullptr && this->count != nullptr){
        gsl_vector_complex_free(gsl_vec);
    }
    delete count;

    this->gsl_vec = a.gsl_vec;
    this->data = a.data;
    this->count = a.count ;
    ++(*count);

    return *this;
}

Complex_Vector& Complex_Vector::operator= (Complex_Vector&& a)
{
    gsl_vector_complex *tmp_vec = a.gsl_vec;
    a.gsl_vec = this->gsl_vec;
    this->gsl_vec = tmp_vec;

    size_t* tmp_size = a.count;
    a.count = this->count;
    this->count = tmp_size;

    return *this;
}

Complex Complex_Vector::operator[] (const int index)
{
    gsl_complex res = gsl_vector_complex_get(gsl_vec, index);
/*    if (&res == nullptr){
        throw std::runtime_error("Index outside of range!");
    }
*/
    return Complex(res);
}

Complex_Vector& Complex_Vector::operator+= (const Complex_Vector& b)
{
    int stat = gsl_vector_complex_add(this->gsl_vec, b.gsl_vec);
    if(stat){
		std::string error_str =   gsl_strerror(stat);
		throw std::runtime_error("Error in vector addition.\nGSL error: "
        + error_str);
	}
    return *this;
}

Complex_Vector& Complex_Vector::operator-= (const Complex_Vector& b)
{
    int stat = gsl_vector_complex_sub(this->gsl_vec, b.gsl_vec);
    if(stat){
		std::string error_str =   gsl_strerror(stat);
		throw std::runtime_error("Error in vector subtraction.\nGSL error: "
        + error_str);
	}
    return *this;
}

Complex_Vector& Complex_Vector::operator*= (const Complex_Vector& b)
{
    int stat = gsl_vector_complex_mul(this->gsl_vec, b.gsl_vec);
    if(stat){
		std::string error_str =   gsl_strerror(stat);
		throw std::runtime_error("Error in vector multiplication.\nGSL error: "
        + error_str);
	}
    return *this;
}

Complex_Vector& Complex_Vector::operator/= (const Complex_Vector& b)
{
    int stat = gsl_vector_complex_div(this->gsl_vec, b.gsl_vec);
    if(stat){
		std::string error_str =   gsl_strerror(stat);
		throw std::runtime_error("Error in vector division.\nGSL error: "
        + error_str);
	}
    return *this;
}

Complex_Vector& Complex_Vector::operator*= (const double s)
{
    int stat = gsl_vector_complex_scale(this->gsl_vec, gsl_complex_rect(s,0.));
    if(stat){
		std::string error_str =   gsl_strerror(stat);
		throw std::runtime_error("Error in vector multiplication.\nGSL error: "
        + error_str);
	}
    return *this;
}

Complex_Vector& Complex_Vector::operator/= (const double s)
{
    int stat = gsl_vector_complex_scale(this->gsl_vec, gsl_complex_rect(1./s,0.));
    if(stat){
		std::string error_str =   gsl_strerror(stat);
		throw std::runtime_error("Error in vector division.\nGSL error: "
        + error_str);
	}
    return *this;
}

Complex_Vector Complex_Vector::operator+ (const Complex_Vector& b) const
{
    Complex_Vector res(this->gsl_vec->size);
    int stat = gsl_vector_complex_memcpy(res.gsl_vec, this->gsl_vec);
    if(stat){
		std::string error_str =   gsl_strerror(stat);
		throw std::runtime_error("Error in memory copying.\nGSL error: "
        + error_str);
	}
    stat = gsl_vector_complex_add(res.gsl_vec, b.gsl_vec);
    if(stat){
		std::string error_str =   gsl_strerror(stat);
		throw std::runtime_error("Error in vector addition.\nGSL error: "
        + error_str);
	}

    return res;
}

Complex_Vector Complex_Vector::operator- (const Complex_Vector& b) const
{
    Complex_Vector res(this->gsl_vec->size);
    int stat = gsl_vector_complex_memcpy(res.gsl_vec, this->gsl_vec);
    if(stat){
		std::string error_str =   gsl_strerror(stat);
		throw std::runtime_error("Error in memory copying.\nGSL error: "
        + error_str);
	}
    stat = gsl_vector_complex_sub(res.gsl_vec, b.gsl_vec);
    if(stat){
		std::string error_str =   gsl_strerror(stat);
		throw std::runtime_error("Error in vector subtraction.\nGSL error: "
        + error_str);
	}

    return res;
}

Complex_Vector Complex_Vector::operator* (const Complex_Vector& b) const
{
    Complex_Vector res(this->gsl_vec->size);
    int stat = gsl_vector_complex_memcpy(res.gsl_vec, this->gsl_vec);
    if(stat){
		std::string error_str =   gsl_strerror(stat);
		throw std::runtime_error("Error in memory copying.\nGSL error: "
        + error_str);
	}
    stat = gsl_vector_complex_mul(res.gsl_vec, b.gsl_vec);
    if(stat){
		std::string error_str =   gsl_strerror(stat);
		throw std::runtime_error("Error in vector multiplication.\nGSL error: "
        + error_str);
	}

    return res;
}

Complex_Vector Complex_Vector::operator/ (const Complex_Vector& b) const
{
    Complex_Vector res(this->gsl_vec->size);
    int stat = gsl_vector_complex_memcpy(res.gsl_vec, this->gsl_vec);
    if(stat){
		std::string error_str =   gsl_strerror(stat);
		throw std::runtime_error("Error in memory copying.\nGSL error: "
        + error_str);
	}
    stat = gsl_vector_complex_div(res.gsl_vec, b.gsl_vec);
    if(stat){
		std::string error_str =   gsl_strerror(stat);
		throw std::runtime_error("Error in vector division.\nGSL error: "
        + error_str);
	}

    return res;
}

Complex_Vector Complex_Vector::operator* (const double& s) const
{
    Complex_Vector res(this->gsl_vec->size);
    int stat = gsl_vector_complex_memcpy(res.gsl_vec, this->gsl_vec);
    if(stat){
		std::string error_str =   gsl_strerror(stat);
		throw std::runtime_error("Error in memory copying.\nGSL error: "
        + error_str);
	}
    stat = gsl_vector_complex_scale(res.gsl_vec, gsl_complex_rect(s, 0.));
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
    Complex_Vector res(this->gsl_vec->size);
    int stat = gsl_vector_complex_memcpy(res.gsl_vec, this->gsl_vec);
    if(stat){
		std::string error_str =   gsl_strerror(stat);
		throw std::runtime_error("Error in memory copying.\nGSL error: "
        + error_str);
	}
    stat = gsl_vector_complex_scale(res.gsl_vec, gsl_complex_rect(1./s,0));
    if(stat){
		std::string error_str =   gsl_strerror(stat);
		throw std::runtime_error("Error in vector scaling.\nGSL error: "
        + error_str);
	}

    return res;
}

std::ostream& operator<<(std::ostream& os, const Complex_Vector& a)
{
    unsigned int size_a = a.gsl_vec->size;
    Complex tmp;

    os << "( ";
    for(unsigned int i = 0; i < size_a; i++){
        tmp = Complex(gsl_vector_complex_get(a.gsl_vec, i));
        os << tmp << " ";
    }
    os << ")";
    return os;
}


Complex GSL::dot(const Complex_Vector& a, const Complex_Vector& b)
{
    int size_a = a.gsl_vec->size;
    int size_b = b.gsl_vec->size;
    if(size_a != size_b){
		throw std::runtime_error("Error in dot product!\nDot product "
        "(scalar product) only defined for vectors of equal length!");
    }


    gsl_complex res = gsl_complex_rect(0,0);
    int stat = gsl_blas_zdotc(a.gsl_vec, b.gsl_vec, &res);
    if(stat){
		std::string error_str =   gsl_strerror(stat);
		throw std::runtime_error("Error in vector dot product.\nGSL error: "
        + error_str);
	}
    return Complex(res);
}


Complex_Vector GSL::cross(const Complex_Vector& a, const Complex_Vector& b)
{
    int size_a = a.gsl_vec->size;
    int size_b = b.gsl_vec->size;
    if(size_a != size_b){
		throw std::runtime_error("Error in cross product!\nCross product "
        "(vector product) only defined for vectors of equal length!");
    } else if(size_a != 3 || size_b !=3){
		throw std::runtime_error("Error in cross product!\nCross product "
        "(vector product) only defined for vectors of length 3!");
    }

    Complex a_tmp[3], b_tmp[3], tmp;
    a_tmp[0] = Complex(gsl_vector_complex_get(a.gsl_vec, 0));
    b_tmp[0] = Complex(gsl_vector_complex_get(b.gsl_vec, 0));
    a_tmp[1] = Complex(gsl_vector_complex_get(a.gsl_vec, 1));
    b_tmp[1] = Complex(gsl_vector_complex_get(b.gsl_vec, 1));
    a_tmp[2] = Complex(gsl_vector_complex_get(a.gsl_vec, 2));
    b_tmp[2] = Complex(gsl_vector_complex_get(b.gsl_vec, 2));
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
    if(a.count == nullptr){
		throw std::runtime_error("Trying to copy uninitialized Vector!\n");
    }
    /* Special cases to consider:
        * This Vector is not initialized => Initialize it and copy data from a
        * This Vector shares it's data with other vectors => allocate new
            gsl_vector and copy the data from a into it (reducing count on the
            old vector)
        * This Vector is the only vector using the data => copy the data
            directly from a
        * a is uninitialized => raise an error
    */
    // This Vector is uninitialized
    if(this->count == nullptr){
        this->gsl_vec = gsl_vector_complex_alloc(a.gsl_vec->size);
        this->count = new size_t;
        *this->count = 1;
    // Other vectors are using the data
    }else if(*this->count > 1){
        *this->count -= 1;
        // Create new data array
        this->gsl_vec = gsl_vector_complex_alloc(a.gsl_vec->size);
        this->count = new size_t;
        *this->count = 1;
    // No other vector is using the data!
    // Make sure the dimesnions of the gsl_vector s arthe same
    }else if(this->gsl_vec->size != a.gsl_vec->size){
        gsl_vector_complex_free(this->gsl_vec);
        this->gsl_vec = gsl_vector_complex_alloc(a.gsl_vec->size);
    }
    if(this->gsl_vec == nullptr){
        throw std::runtime_error("Error in vector allocation!");
    }
    int stat = gsl_vector_complex_memcpy(this->gsl_vec, a.gsl_vec);
    if(stat){
		std::string error_str =   gsl_strerror(stat);
		throw std::runtime_error("Error in memory copying.\nGSL error: "
        + error_str);
	}
    this->data = this->gsl_vec->data;
}

void Complex_Vector::set(size_t i, const Complex& z)
{
    gsl_vector_complex_set(this->gsl_vec, i, z.gsl_c);
}

Complex Complex_Vector::get(size_t i)
{
    return Complex(gsl_vector_complex_get(this->gsl_vec, i));
}
/*
int main()
{
    Vector a(3);
    Vector c;
    a[0] = 1;
    a[1] = 1;
    a[2] = 1;
    Vector b(2);
    b.copy(a*2);
    c.copy(2*b);
    a.normalize();
    Vector t = cross(b,a);
    std::cout << "a : " << a << std::endl;
    std::cout << "b : " << b << std::endl;
    std::cout << "c : " << t << std::endl;

    return 0;
}
*/
