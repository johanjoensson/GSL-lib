#include "vector.h"
#include <gsl/gsl_blas.h>
#include <stdexcept>

using namespace GSL;


BaseVector::~BaseVector()
{
    if(count != nullptr){
        if(*count <= 0){
            delete count;
        }
    }
}


BaseVector::BaseVector()
 : count(nullptr), matrix(false)
{}


/*******************************************************************************
*!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
*! This is not implemented correctly, something is wrong!
*!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
*******************************************************************************/
BaseVector::BaseVector(const BaseVector& v)
: count(v.count), matrix(v.matrix)
{
    if(v.count != nullptr){
        (*count)++;
    }
}

/*******************************************************************************
*!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
*! This is not implemented correctly, something is wrong!
*!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
*******************************************************************************/
BaseVector::BaseVector(BaseVector& v)
: BaseVector()
{
    count = v.count;
    if(v.count != nullptr){
        (*count)++;
    }
    matrix = v.matrix;
}

/*******************************************************************************
*!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
*! This is not implemented correctly, something is wrong!
*!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
*******************************************************************************/
BaseVector::BaseVector(BaseVector&& v)
: BaseVector()
{
    std::swap(count, v.count);
    std::swap(matrix, v.matrix);
}

std::ostream& GSL::operator<< (std::ostream& os, const BaseVector& a)
{
    return (os << a.to_string());
}

Vector::Vector()
: BaseVector(), gsl_vec(nullptr)
{
}

Vector::Vector(const size_t n)
 : BaseVector()
{
    count = new int;
    *count = 1;
    gsl_vec = gsl_vector_calloc(n);
    if(gsl_vec == nullptr){
        throw std::runtime_error("Memory allocation (gsl_vector_calloc)"
        " failed!");
    }
}

Vector::Vector(Vector& v)
 : BaseVector(v), gsl_vec(v.gsl_vec)
{
}

void Vector::print_count()
{
    std::cout << "Adress of count pointer is " << count << std::endl;
}

/*******************************************************************************
*!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
*! This is not implemented correctly, something is wrong!
*!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
*******************************************************************************/
Vector::Vector(const Vector& v)
 : BaseVector(v), gsl_vec(v.gsl_vec)
{
}

/*******************************************************************************
*!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
*! This is not implemented correctly, something is wrong!
*!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
*******************************************************************************/
Vector::Vector(Vector&& v)
 : BaseVector(v), gsl_vec(nullptr)
{
    std::swap(gsl_vec, v.gsl_vec);
}

Vector::Vector(gsl_vector& v)
 : Vector()
{
    gsl_vec = new gsl_vector;
    *gsl_vec = v;
    gsl_vec->owner = 0;
    count = new int;
    *count = 1;
}


Vector::Vector(const gsl_vector& v)
 : Vector()
{
    gsl_vec = gsl_vector_calloc(v.size);
    gsl_vector_memcpy(gsl_vec, &v);
    count = new int;
    *count = 1;
}

/*******************************************************************************
*!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
*! This is not implemented correctly, something is wrong!
*!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
*******************************************************************************/
Vector::~Vector()
{
    // Make sure there is an allocated gsl_vector
    if(count != nullptr){
        (*count)--;
        if(matrix){
            if(*count <= 0){
                delete gsl_vec;
                gsl_vec = nullptr;
                *count = 0;
            }
        }
        if(*count <= 0){
            if(gsl_vec != nullptr){
                gsl_vector_free(gsl_vec);
                gsl_vec = nullptr;
            }
        }
    }else if(gsl_vec != nullptr){
        gsl_vector_free(gsl_vec);
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
    if(this == &a){
        return *this;
    }

    // this is not part of a matrix
    if(!matrix){
        if(count != nullptr){
            (*count)--;
            if(*count <= 0){
                gsl_vector_free(gsl_vec);
                gsl_vec = nullptr;
                delete count;
                count = nullptr;
            }
        }
        gsl_vec = a.gsl_vec;
        matrix = a.matrix;
        count = a.count;
        if(count != nullptr){
            (*count)++;
        }
    // this is part of a matrix
    }else{
        if(a.gsl_vec != nullptr){
            gsl_vector_memcpy(gsl_vec, a.gsl_vec);
        }
    }

    return *this;
}

Vector& Vector::operator= (Vector&& a)
{
	if(matrix){
		gsl_vector tmp= *this->gsl_vec;
		gsl_vector_memcpy(this->gsl_vec, a.gsl_vec);
		gsl_vector_memcpy(a.gsl_vec, &tmp);
	}else{
		std::swap(gsl_vec, a.gsl_vec);
		std::swap(count, a.count);
	}
    
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

std::string Vector::to_string() const
{
    std::string res = "";
    double tmp = 0;
    res += "( ";
    for(unsigned int i = 0; i < this->gsl_vec->size; i++){
        tmp = gsl_vector_get(this->gsl_vec, i);
        res += std::to_string(tmp) + " ";
    }
    res += ")";
    return res;
}

double GSL::dot(const Vector& a, const Vector& b)
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
/*******************************************************************************
*!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
*! This is not implemented correctly, something is wrong!
*!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
*******************************************************************************/
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
    // Make sure the dimesnions of the gsl_vectors are the same
    }else if(this->gsl_vec->size != a.gsl_vec->size){
        gsl_vector_free(this->gsl_vec);
        this->gsl_vec = gsl_vector_alloc(a.gsl_vec->size);
        *this->count = 1;
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

bool GSL::operator==(const Vector& a, const Vector& b)
{
    return gsl_vector_equal(a.gsl_vec, b.gsl_vec);
}

// bool GSL::operator==(const Vector& u, const Vector& v)
// {
//     return gsl_vector_equal(u.gsl_vec, v.gsl_vec);
// }
bool GSL::operator!=(const Vector& a, const Vector& b)
{
    return !(a == b);
}
