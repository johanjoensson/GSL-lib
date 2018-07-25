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

int main()
{
	Complex_Matrix m(4,4);
	Complex_Matrix n(4,3);

	Complex_Vector v(4);
	v.set(0, Complex(1.2, -0.4));
	v.set(1, Complex(0.34, -0.5));
	v.set(2, Complex(8.2,0));
	v.set(3,Complex(3.2,0));

	n[0].set(0,Complex(0.25, -12.3));
	n[1].set(1, Complex(0.25, 0));
	n[2].set(2, Complex(0., 1.4));

	m[0].set(0, Complex(0.3, 0.89));
	m[1].set(1, Complex(1.2, 0));

	std::cout << m << std::endl;
	std::cout << n << std::endl;
	std::cout << v << std::endl;
	std::cout << v*m*n << std::endl;

	return 0;
}
