#include "GSLpp/complex_float.h"
#include <gtest/gtest.h>

TEST(Complex_floatTest, TestConstructionGSLComplex_f)
{
	float re = 5.0f, im = 1.3f;
	gsl_complex_float c;
	c.dat[0] = re;
	c.dat[1] = im;
	GSL::Complex_float a(c);
	EXPECT_FLOAT_EQ(a.real(), re) << "Real parts do not match! " << a.real() << " != " << re;
	EXPECT_FLOAT_EQ(a.imag(), im) << "Imaginary parts do not match " << a.imag() << " != " << im;
}

TEST(Complex_floatTest, TestConstructionRealImag)
{
	float re = 5.0f, im = 1.3f;
	GSL::Complex_float a(re, im);
	EXPECT_FLOAT_EQ(a.real(), re) << "Real parts do not match! " << a.real() << " != " << re;
	EXPECT_FLOAT_EQ(a.imag(), im) << "Imaginary parts do not match " << a.imag() << " != " << im;
}

TEST(Complex_floatTest, TestConstructionCopy)
{
	float re = 5.0f, im = 1.3f;
	GSL::Complex_float a(re, im);
	GSL::Complex_float b(a);
	EXPECT_FLOAT_EQ(b.real(), re) << "Real parts do not match! " << b.real() << " != " << re;
	EXPECT_FLOAT_EQ(b.imag(), im) << "Imaginary parts do not match " << b.imag() << " != " << im;
}

TEST(Complex_floatTest, TestConstructionMove)
{
	float re = 5.0f, im = 1.3f;
	GSL::Complex_float a(re, im);
	GSL::Complex_float b(std::move(a));
	EXPECT_FLOAT_EQ(b.real(), re) << "Real parts do not match! " << b.real() << " != " << re;
	EXPECT_FLOAT_EQ(b.imag(), im) << "Imaginary parts do not match " << b.imag() << " != " << im;
}

TEST(Complex_floatTest, TestEqual)
{
	float re = 5.0f, im = 1.3f;
	GSL::Complex_float a(re, im);
	GSL::Complex_float b(re, im);
	EXPECT_EQ(a, b) << "Complex_float numbers not equal! " << a.real() << " != " << re - 1;
}

TEST(Complex_floatTest, TestNotEqual)
{
	float re = 5.0f, im = 1.3f;
	GSL::Complex_float a(re, im);
	GSL::Complex_float b(re + 1, im - 1);
	EXPECT_NE(a, b) << "Complex_float numbers are equal! " << a << " == " << b;
}

TEST(Complex_floatTest, TestCopy)
{
	float re = 4.3f, im = 5;
	GSL::Complex_float a, b = GSL::Complex_float(re, im);
	a = b;
	EXPECT_FLOAT_EQ(a.real(), re) << "Real parts do not match! " << a.real() << " != " << re;
	EXPECT_FLOAT_EQ(a.imag(), im) << "Imaginary parts do not match " << a.imag() << " != " << im;

}

TEST(Complex_floatTest, TestMove)
{
	float re = 4.3f, im = 5;
	GSL::Complex_float a, b = GSL::Complex_float(re, im);
	a = std::move(b);
	EXPECT_FLOAT_EQ(a.real(), re) << "Real parts do not match! " << a.real() << " != " << re;
	EXPECT_FLOAT_EQ(a.imag(), im) << "Imaginary parts do not match " << a.imag() << " != " << im;

}

TEST(Complex_floatTest, TestDecayToGSLComplex_f)
{
	float re = 3, im = 4;
	GSL::Complex_float z1(re, im);
	gsl_complex_float z2;
	z2.dat[0] = re;
	z2.dat[1] = im;
	EXPECT_FLOAT_EQ(z1.real(), z2.dat[0]);
	EXPECT_FLOAT_EQ(z1.imag(), z2.dat[1]);
}

/*
TEST(Complex_floatTest, TestAbs)
{
	float re = 3, im = 4;
	GSL::Complex_float z(re, im);
	EXPECT_FLOAT_EQ(z.abs(), 5) << "Absolute value not correct! z = " << z.real()
		<< " + " << z.imag() <<"i |z| != " << z.abs();
}

TEST(Complex_floatTest, TestArg)
{
	float re = 0, im = 1;
	GSL::Complex_float z(re, im);
	EXPECT_FLOAT_EQ(z.arg(), static_cast<float>(M_PI)/2) << "Argument not correct! z = " << z.real()
		<< " + " << z.imag() <<"i arg(z) != " << z.arg();
}

TEST(Complex_floatTest, TestAbs2)
{
	float re = 3, im = 4;
	GSL::Complex_float z(re, im);
	EXPECT_FLOAT_EQ(z.abs2(), 25) << "Absolute value not correct! z = " << z.real()
		<< " + " << z.imag() <<"i |z|^2 != " << z.abs2();
}

TEST(Complex_floatTest, TestLogAbs)
{
	float re = 3, im = 4;
	GSL::Complex_float z(re, im);
	EXPECT_FLOAT_EQ(z.logabs(), std::log(5.f)) << "Absolute value not correct! z = " << z.real()
		<< " + " << z.imag() <<"i ln |z| != " << z.logabs();
}

TEST(Complex_floatTest, TestConjugate)
{
	float re = 3, im = 4;
	GSL::Complex_float z1(re, im);
	GSL::Complex_float z2(re, -im);
	EXPECT_EQ(z1.conjugate(), z2) << "Complex_float conjugate not correct! z = " <<
		z1.conjugate().real()	<< " + " << z1.conjugate().imag() <<" z* != " << z2;
}

TEST(Complex_floatTest, TestRecipr)
{
	float re = 3.f/8, im = 1.f/2;
	GSL::Complex_float z1(re, im);
	GSL::Complex_float z2(re/z1.abs2(), -im/z1.abs2());
	EXPECT_FLOAT_EQ(z1.recipr().real(), z2.real()) << "Reciprocal not correct! 1.f/z = " <<
		z1.recipr() <<"  != " << z2;
	EXPECT_FLOAT_EQ(z1.recipr().imag(), z2.imag()) << "Reciprocal not correct! 1.f/z = " <<
		z1.recipr() <<"  != " << z2;
}

TEST(Complex_floatTest, TestNegate)
{
	float re = 3, im = 4;
	GSL::Complex_float z1(re, im);
	GSL::Complex_float z2(-re, -im);
	EXPECT_EQ(z1.negate(), z2) << "Negate not correct! z = " <<
		z1.negate().real()	<< " + " << z1.negate().imag() <<"  != " << z2;
}
*/
