#include <iostream>
#include "vector.h"
#include "matrix.h"
#include "complex_matrix.h"
#include "complex_vector.h"
#include "complex.h"
#include "special_functions.h"

#include <gsl/gsl_sf_result.h>
#include <gsl/gsl_matrix.h>

using namespace GSL;

void test_vector()
{
std::cout << "Testing real vectors and matrices" << std::endl;
	Vector v(3), a1(3), a2(3), a3(3);
	v[0] = 1.2;

	a1[0] = 1.0;
	a2[1] = 1.0;
	a3[2] = 1.0;

	Matrix m(3,3);
	m[0][0] = 1.0;
	m[1] = a2;
	m[2] = a3;

	std::cout << "v = " << v << std::endl;
	std::cout << "m = " << m << std::endl;
	std::cout << "m*v = " << m*v << std::endl;

	std::cout << "m[0] = " << m[0] << std::endl;
	std::cout << "m[1] = " << m[1] << std::endl;
	std::cout << "m[2] = " << m[2] << std::endl;
}

void test_complex_vector()
{
std::cout << "Testing complex vectors and matrices" << std::endl;
	Complex_Vector v(3), a1(3), a2(3), a3(3);
	v[0] = Complex(1.2, 0);

	a1[0] = Complex(1.0, 0);
	a2[1] = Complex(0., 1.0);
	a3[2] = Complex(0.5, 0.5);

	Complex_Matrix m(3,3);
	m[0][0] = Complex(1.0, 0);
	m[1] = a2;
	m[2] = a3;

	std::cout << "v = " << v << std::endl;
	std::cout << "m = " << m << std::endl;
	std::cout << "m*v = " << m*v << std::endl;

	std::cout << "m[0] = " << m[0] << std::endl;
	std::cout << "m[1] = " << m[1] << std::endl;
	std::cout << "m[2] = " << m[2] << std::endl;
}
int main()
{
	test_vector();
	test_complex_vector();
	return 0;
}
