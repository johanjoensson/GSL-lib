#include <iostream>
#include <stdexcept>
#include "GSLpp/complex.h"
#include "GSLpp/vector.h"
#include "GSLpp/matrix.h"
#include "GSLpp/divided_difference.h"
#include "GSLpp/special_functions.h"
#include "GSLpp/polynomial.h"
#include "GSLpp/linalg.h"

#include <gsl/gsl_sf_result.h>
#include <gsl/gsl_matrix.h>

using namespace GSL;

bool test_equal()
{
	GSL::Vector a(3), b(3);
	a[0] = 1.0;
	a[1] = 2.3;
	a[2] = 0.244;

	b[0] = 8;
	b[1] = 7.42;
	b[2] = 9.4;

	if(!(a != b)){
		throw std::runtime_error("Vector != implemented incorrectly!");
	}
	if(a == b){
		throw std::runtime_error("Vector == implemented incorrectly!");
	}

	return true;
}

bool test_addition()
{
	GSL::Vector a(4), b(4), c(4);
	a[0] = 1.2;
	a[1] = 2.6;
	a[2] = 8;
	a[3] = 4.76;
	b[0] = 2.98;
	b[1] = 1./2;
	b[2] = 0.24;
	b[3] = 1/3.;
	c[0] = 4.18;
	c[1] = 3.1;
	c[2] = 8.24;
	c[3] = 4.76 + 1/3.;
	if(a + b != c){
		throw std::runtime_error("Vector addition implemented incorrectly!");
	}

	return true;
}


void test_vector()
{
	std::cout << "Testing real vectors and matrices" << std::endl;
	std::cout << std::string(80, '*') << std::endl;
	Vector v(3), a1(3), a2(3), a3(3);
	Vector u = {1., 2.3, 4.2, 1.24, 5};

	v[0] = 1.2;

	a1[0] = 1.0;
	a2[1] = 1.0;
	a3[2] = 1.0;

	std::cout << "(a1|a2) = " << a1.dot(a2) << "\n";
	std::cout << "(a1|a1) = " << a1.dot(a1) << "\n";
	std::cout << "a1 x a2 = " << a1.cross(a2) << "\n";
	std::cout << "Setting up matrix m\n";
	Matrix m(3,3);
	Matrix t;
	t = m;
	std::cout << "m set up\n";
	m[0][0] = a1[0];
	std::cout << t << "\n";
//	std::cout << "m = " << m << "\n";
	std::cout << "Setting first row of m\n";
	m[1] = a2;
//	std::cout << "\n\nm = " << m << "\n";
	m[2] = 1*a3 + 0.24*a1 + 0*a2;
	std::cout << "First row of m set up\n";
	std::cout << "\n\nm = " << m << "\n";

	std::cout << "Setting up matrix n\n";
	Matrix n = {{1.2 , 3}, {2,4}};
	std::cout << "n = " << n << "\n";
	std::cout << n[0] << "\n";

	std::cout << "Setting up matrix A\n";
	Matrix A(3,3);

	A[1] = m[2];
	A[1] = m[1];

	GSL::Vector c = m[2] + 3*m[1] - 1.2*m[0];
	std::cout << "v = " << v << std::endl;
	std::cout << "u = " << u << std::endl;
	std::cout << "n = " << n << std::endl;
	std::cout << "m = " << m << std::endl;

	std::cout << "m*v = " << m*v << std::endl;

	std::cout << "m/2 = " << m/2 << std::endl;
	std::cout << "0.5*m = " << 0.5* m << std::endl;

	std::cout << "m[0] = " << m[0] << std::endl;
	std::cout << "m[1] = " << m[1] << std::endl;
	std::cout << "m[2] = " << m[2] << std::endl;

	std::cout << "Changing diagoal of m" << std::endl;

	std::cout << "m.diag() = m[2]." << std::endl;
//	m.diag() = m[2];
//	std::cout <<"m.diag() = " << m.diag() << std::endl;


	std::cout << m[0] << " == " << a1 << " = " << (m[0] == a1) << std::endl;
	std::cout << m[0] << " != " << a1 << " = " << (m[0] != a1) << std::endl;
	test_equal();
	test_addition();
	std::cout << "m[0] x a2 = " << m[0] << " x " << a2 << " = " << m[0].cross(a2) << std::endl;
	std::cout << std::string(80, '*') << std::endl;

	std::cout << "Iterating over v :\n";
	for(auto val : v){
		std::cout << val << " ";
	}
	std::cout << "\n";
	GSL::Vector test;
}


void test_complex_vector()
{
	std::cout << "Testing complex vectors and matrices" << std::endl;
	std::cout << std::string(80, '*') << std::endl;
	Vector_cx v(3), a1(3), a2(3), a3(3);
	Vector_cx u = {Complex(1.0,0), Complex(1.3,2.1)};


	v[0] = Complex(1.2, 0.43);
	v[2] = Complex(0.24, 100.345);

	a1[0] = Complex(1.0, 0);
	a2[1] = Complex(1.0, 0.1);
	a3[2] = Complex(1.0, 0);

	Matrix_cx m(3,3);
	m[0][0] = Complex(1.0, 0.);
	m[1] = a2;
	m[2] = a3+2*a1;

	Matrix_cx n = {{Complex(1, 2.4), Complex(1.0, 0)},
						{Complex(1.3, 2.1), Complex(0.0, 1.2)},
						{Complex(1, 1), Complex(2.4, 4.65)}};
	std::cout << "v = " << v << std::endl;
	std::cout << "u = " << u << std::endl;
	std::cout << "n = " << n << std::endl;
	std::cout << "m = " << m << std::endl;
	std::cout << "m*v = " << m*v << std::endl;

	std::cout << "m[0] = " << m[0] << std::endl;
	std::cout << "m[1] = " << m[1] << std::endl;
	std::cout << "m[2] = " << m[2] << std::endl;

	std::cout << m[0] << " == " << a1 << " = " << (m[0] == a1) << std::endl;
	std::cout << m[1] << " != " << a2 << " = " << (m[0] != a1) << std::endl;
	std::cout << std::string(80, '*') << std::endl;
}

void test_linalg()
{
	Matrix_cx m(3,3);
	m[0][0] = Complex(1, 0);
	m[1][1] = Complex(1, 0);
	m[2][2] = Complex(1, 0);
	std::cout << m << std::endl;
	std::cout << cholesky_decomp(m) << std::endl;
}

int main()
{
	test_vector();
	test_complex_vector();

	test_linalg();

	return 0;
}
