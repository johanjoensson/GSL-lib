#include "vector.h"
#include <gsl/gsl_blas.h>

using namespace GSL;
Vector::Vector()
{
    gsl_vec = nullptr;
    count = nullptr;
}

Vector::Vector(const size_t n)
{
    gsl_vec = gsl_vector_calloc(n);
    if(gsl_vec == nullptr){
        throw std::runtime_error("Memory allocation (gsl_vector_calloc)"
        " failed!");
    }
    count = new int;
    *count = 1;
}

Vector::Vector(Vector& v)
 : gsl_vec(v.gsl_vec),  count(v.count)
{
    (*count)++;
}

Vector::Vector(const Vector& v)
 : gsl_vec(v.gsl_vec),  count(v.count)
{
    (*count)++;
}

Vector::Vector(Vector&& v)
 : gsl_vec(v.gsl_vec),  count(nullptr)
{
    std::swap(count, v.count);
    v.gsl_vec = nullptr;
}

Vector::Vector(gsl_vector& v)
{
    gsl_vec = new gsl_vector;
    *gsl_vec = v;
    gsl_vec->owner = 0;
    count = new int;
    *count = 1;
}


Vector::Vector(const gsl_vector& v)
{
    gsl_vec = gsl_vector_calloc(v.size);
    gsl_vector_memcpy(gsl_vec, &v);
    count = new int;
    *count = 1;
}

Vector::~Vector()
{
    // Make sure there is an allocated gsl_vector
    if(count != nullptr){
        // Reduce the number of references to the gsl_vector by one
        *count -= 1;
        // If there are no more references to the vector, deallocate the memory
        if(*count <= 0){
            delete count;
            count = nullptr;
            if(gsl_vec != nullptr){
                gsl_vector_free(gsl_vec);
                gsl_vec = nullptr;
            }
        }
    }
}

void Vector::normalize() const
{
    double norm = this->norm();
    int stat = gsl_vector_scale(this->gsl_vec, 1./norm);
    if(stat){
		std::string error_str =   gsl_strerror(stat);
		throw std::runtime_error("Error in normalization.\nGSL error: "
        + error_str);
    }
}

double Vector::norm() const
{
    return gsl_blas_dnrm2(this->gsl_vec);
}

Vector& Vector::operator= (const Vector &a)
{
    // If &a and this are the same object, do nothing
    // especially do not deallocate any memory!
    if(this == &a){
        return *this;
    }

    if(count != nullptr){
        (*count)--;
        if(*count == 0){
			if(gsl_vec->size != 0){
				gsl_vector_free(gsl_vec);
			}else{
				delete gsl_vec;
			}
			delete count;
		}else if(*count < 0){
			gsl_vector_memcpy(this->gsl_vec, a.gsl_vec);
			*count = 0;
		}else{
			this->gsl_vec = a.gsl_vec;
			this->count = a.count ;
			++(*count);
		}
    }


    return *this;
}

Vector& Vector::operator= (Vector&& a)
{
    gsl_vector *tmp_vec = a.gsl_vec;
    a.gsl_vec = this->gsl_vec;
    this->gsl_vec = tmp_vec;

    int* tmp_size = a.count;
    a.count = this->count;
    this->count = tmp_size;

    return *this;
}

double& Vector::operator[] (const int index)
{
    double *res = gsl_vector_ptr(gsl_vec, index);
    if (res == nullptr){
        throw std::runtime_error("Index out of range!");
    }
    return *res;
}

Vector& Vector::operator+= (const Vector& b)
{
    int stat = gsl_vector_add(this->gsl_vec, b.gsl_vec);
    if(stat){
		std::string error_str =   gsl_strerror(stat);
		throw std::runtime_error("Error in vector addition.\nGSL error: "
        + error_str);
	}
    return *this;
}

Vector& Vector::operator-= (const Vector& b)
{
    int stat = gsl_vector_sub(this->gsl_vec, b.gsl_vec);
    if(stat){
		std::string error_str =   gsl_strerror(stat);
		throw std::runtime_error("Error in vector subtraction.\nGSL error: "
        + error_str);
	}
    return *this;
}

Vector& Vector::operator*= (const Vector& b)
{
    int stat = gsl_vector_mul(this->gsl_vec, b.gsl_vec);
    if(stat){
		std::string error_str =   gsl_strerror(stat);
		throw std::runtime_error("Error in vector multiplication.\nGSL error: "
        + error_str);
	}
    return *this;
}

Vector& Vector::operator/= (const Vector& b)
{
    int stat = gsl_vector_div(this->gsl_vec, b.gsl_vec);
    if(stat){
		std::string error_str =   gsl_strerror(stat);
		throw std::runtime_error("Error in vector division.\nGSL error: "
        + error_str);
	}
    return *this;
}

Vector& Vector::operator*= (const double s)
{
    int stat = gsl_vector_scale(this->gsl_vec, s);
    if(stat){
		std::string error_str =   gsl_strerror(stat);
		throw std::runtime_error("Error in vector multiplication.\nGSL error: "
        + error_str);
	}
    return *this;
}

Vector& Vector::operator/= (const double s)
{
    int stat = gsl_vector_scale(this->gsl_vec, 1./s);
    if(stat){
		std::string error_str =   gsl_strerror(stat);
		throw std::runtime_error("Error in vector division.\nGSL error: "
        + error_str);
	}
    return *this;
}

Vector Vector::operator+ (const Vector& b) const
{
    Vector res(this->gsl_vec->size);
    int stat = gsl_vector_memcpy(res.gsl_vec, this->gsl_vec);
    if(stat){
		std::string error_str =   gsl_strerror(stat);
		throw std::runtime_error("Error in memory copying.\nGSL error: "
        + error_str);
	}
    stat = gsl_vector_add(res.gsl_vec, b.gsl_vec);
    if(stat){
		std::string error_str =   gsl_strerror(stat);
		throw std::runtime_error("Error in vector addition.\nGSL error: "
        + error_str);
	}

    return res;
}

Vector Vector::operator- (const Vector& b) const
{
    Vector res(this->gsl_vec->size);
    int stat = gsl_vector_memcpy(res.gsl_vec, this->gsl_vec);
    if(stat){
		std::string error_str =   gsl_strerror(stat);
		throw std::runtime_error("Error in memory copying.\nGSL error: "
        + error_str);
	}
    stat = gsl_vector_sub(res.gsl_vec, b.gsl_vec);
    if(stat){
		std::string error_str =   gsl_strerror(stat);
		throw std::runtime_error("Error in vector subtraction.\nGSL error: "
        + error_str);
	}

    return res;
}

Vector Vector::operator* (const Vector& b) const
{
    Vector res(this->gsl_vec->size);
    int stat = gsl_vector_memcpy(res.gsl_vec, this->gsl_vec);
    if(stat){
		std::string error_str =   gsl_strerror(stat);
		throw std::runtime_error("Error in memory copying.\nGSL error: "
        + error_str);
	}
    stat = gsl_vector_mul(res.gsl_vec, b.gsl_vec);
    if(stat){
		std::string error_str =   gsl_strerror(stat);
		throw std::runtime_error("Error in vector multiplication.\nGSL error: "
        + error_str);
	}

    return res;
}

Vector Vector::operator/ (const Vector& b) const
{
    Vector res(this->gsl_vec->size);
    int stat = gsl_vector_memcpy(res.gsl_vec, this->gsl_vec);
    if(stat){
		std::string error_str =   gsl_strerror(stat);
		throw std::runtime_error("Error in memory copying.\nGSL error: "
        + error_str);
	}
    stat = gsl_vector_div(res.gsl_vec, b.gsl_vec);
    if(stat){
		std::string error_str =   gsl_strerror(stat);
		throw std::runtime_error("Error in vector division.\nGSL error: "
        + error_str);
	}

    return res;
}

Vector Vector::operator* (const double& s) const
{
    Vector res(this->gsl_vec->size);
    int stat = gsl_vector_memcpy(res.gsl_vec, this->gsl_vec);
    if(stat){
		std::string error_str =   gsl_strerror(stat);
		throw std::runtime_error("Error in memory copying.\nGSL error: "
        + error_str);
	}
    stat = gsl_vector_scale(res.gsl_vec, s);
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

    Vector res(this->gsl_vec->size);
    int stat = gsl_vector_memcpy(res.gsl_vec, this->gsl_vec);
    if(stat){
		std::string error_str =   gsl_strerror(stat);
		throw std::runtime_error("Error in memory copying.\nGSL error: "
        + error_str);
	}
    stat = gsl_vector_scale(res.gsl_vec, 1./s);
    if(stat){
		std::string error_str =   gsl_strerror(stat);
		throw std::runtime_error("Error in vector scaling.\nGSL error: "
        + error_str);
	}

    return res;
}

Vector GSL::operator- (const Vector& a)
{
    Vector res(a.gsl_vec->size);

    return res - a;
}

std::ostream& operator<<(std::ostream& os, const Vector& a)
{
    unsigned int size_a = a.gsl_vec->size;
    double tmp;

    os << "( ";
    for(unsigned int i = 0; i < size_a; i++){
        tmp = gsl_vector_get(a.gsl_vec, i);
        os << tmp << " ";
    }
    os << ")";
    return os;
}


double GSL:: dot(const Vector& a, const Vector& b)
{
    int size_a = a.gsl_vec->size;
    int size_b = b.gsl_vec->size;
    if(size_a != size_b){
		throw std::runtime_error("Error in dot product!\nDot product "
        "(scalar product) only defined for vectors of equal length!");
    }


    double res;
    int stat = gsl_blas_ddot(a.gsl_vec, b.gsl_vec, &res);
    if(stat){
		std::string error_str =   gsl_strerror(stat);
		throw std::runtime_error("Error in vector dot product.\nGSL error: "
        + error_str);
	}
    return res;
}


Vector GSL::cross(const Vector& a, const Vector& b)
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

    double a_tmp[3], b_tmp[3];
    a_tmp[0] = gsl_vector_get(a.gsl_vec, 0);
    b_tmp[0] = gsl_vector_get(b.gsl_vec, 0);
    a_tmp[1] = gsl_vector_get(a.gsl_vec, 1);
    b_tmp[1] = gsl_vector_get(b.gsl_vec, 1);
    a_tmp[2] = gsl_vector_get(a.gsl_vec, 2);
    b_tmp[2] = gsl_vector_get(b.gsl_vec, 2);
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
        this->gsl_vec = gsl_vector_alloc(a.gsl_vec->size);
        this->count = new int;
        *this->count = 1;
    // Other vectors are using the data
    }else if(*this->count > 1){
        *this->count -= 1;
        // Create new data array
        this->gsl_vec = gsl_vector_alloc(a.gsl_vec->size);
        this->count = new int;
        *this->count = 1;
    // No other vector is using the data!
    // Make sure the dimesnions of the gsl_vector s arthe same
    }else if(this->gsl_vec->size != a.gsl_vec->size){
        gsl_vector_free(this->gsl_vec);
        this->gsl_vec = gsl_vector_alloc(a.gsl_vec->size);
    }
    if(this->gsl_vec == nullptr){
        throw std::runtime_error("Error in vector allocation!");
    }
    int stat = gsl_vector_memcpy(this->gsl_vec, a.gsl_vec);
    if(stat){
		std::string error_str =   gsl_strerror(stat);
		throw std::runtime_error("Error in memory copying.\nGSL error: "
        + error_str);
	}
}

bool GSL::operator==(const Vector& u, const Vector& v)
{
    return gsl_vector_equal(u.gsl_vec, v.gsl_vec);
}
bool GSL::operator!=(const Vector& u, const Vector& v)
{
    return !(u == v);
}
