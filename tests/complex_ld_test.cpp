#include "GSLpp/complex_long_double.h"
#include <gtest/gtest.h>

TEST(Complex_long_doubleTest, TestConstructionGSLComplex_ld)
{
	long double re = 5.l, im = 1.3l;
	gsl_complex_long_double c;
	c.dat[0] = re;
	c.dat[1] = im;
	GSL::Complex_long_double a(c);
	EXPECT_EQ(a.real(), re) << "Real parts do not match! " << a.real() << " != " << re;
	EXPECT_EQ(a.imag(), im) << "Imaginary parts do not match " << a.imag() << " != " << im;
}

TEST(Complex_long_doubleTest, TestConstructionRealImag)
{
	long double re = 5.l, im = 1.3l;
	GSL::Complex_long_double a(re, im);
	EXPECT_EQ(a.real(), re) << "Real parts do not match! " << a.real() << " != " << re;
	EXPECT_EQ(a.imag(), im) << "Imaginary parts do not match " << a.imag() << " != " << im;
}

TEST(Complex_long_doubleTest, TestConstructionCopy)
{
	long double re = 5.l, im = 1.3l;
	GSL::Complex_long_double a(re, im);
	GSL::Complex_long_double b(a);
	EXPECT_EQ(b.real(), re) << "Real parts do not match! " << b.real() << " != " << re;
	EXPECT_EQ(b.imag(), im) << "Imaginary parts do not match " << b.imag() << " != " << im;
}

TEST(Complex_long_doubleTest, TestConstructionMove)
{
	long double re = 5.l, im = 1.3l;
	GSL::Complex_long_double a(re, im);
	GSL::Complex_long_double b(std::move(a));
	EXPECT_EQ(b.real(), re) << "Real parts do not match! " << b.real() << " != " << re;
	EXPECT_EQ(b.imag(), im) << "Imaginary parts do not match " << b.imag() << " != " << im;
}

TEST(Complex_long_doubleTest, TestEqual)
{
	long double re = 5.l, im = 1.3l;
	GSL::Complex_long_double a(re, im);
	GSL::Complex_long_double b(re, im);
	EXPECT_EQ(a, b) << "Complex_long_double numbers not equal! " << a.real() << " != " << re - 1;
}

TEST(Complex_long_doubleTest, TestNotEqual)
{
	long double re = 5.l, im = 1.3l;
	GSL::Complex_long_double a(re, im);
	GSL::Complex_long_double b(re + 1, im - 1);
	EXPECT_NE(a, b) << "Complex_long_double numbers are equal! " << a << " == " << b;
}

TEST(Complex_long_doubleTest, TestCopy)
{
	long double re = 4.3l, im = 5.l;
	GSL::Complex_long_double a, b = GSL::Complex_long_double(re, im);
	a = b;
	EXPECT_EQ(a.real(), re) << "Real parts do not match! " << a.real() << " != " << re;
	EXPECT_EQ(a.imag(), im) << "Imaginary parts do not match " << a.imag() << " != " << im;

}

TEST(Complex_long_doubleTest, TestMove)
{
	long double re = 4.3l, im = 5.l;
	GSL::Complex_long_double a, b = GSL::Complex_long_double(re, im);
	a = std::move(b);
	EXPECT_EQ(a.real(), re) << "Real parts do not match! " << a.real() << " != " << re;
	EXPECT_EQ(a.imag(), im) << "Imaginary parts do not match " << a.imag() << " != " << im;

}

TEST(Complex_long_doubleTest, TestDecayToGSLComplex_ld)
{
	long double re = 3.l, im = 4.l;
	GSL::Complex_long_double z1(re, im);
	gsl_complex_long_double z2;
	z2.dat[0] = re;
	z2.dat[1] = im;
	EXPECT_EQ(z1.real(), z2.dat[0]);
	EXPECT_EQ(z1.imag(), z2.dat[1]);
}

/*
TEST(Complex_long_doubleTest, TestAbs)
{
	long double re = 3.l, im = 4.l;
	GSL::Complex_long_double z(re, im);
	EXPECT_EQ(z.abs(), 5.l) << "Absolute value not correct! z = " << z.real()
	 << " + " << z.imag() <<"i |z| != " << z.abs();
}

TEST(Complex_long_doubleTest, TestArg)
{
	long double re = 0, im = 1;
	GSL::Complex_long_double z(re, im);
	long double diff = std::abs(z.arg() - static_cast<long double>(M_PI)/2);
	EXPECT_TRUE(diff < 1e-10l) << "Argument not correct! z = " << z.real()
	 << " + " << z.imag() <<"i arg(z) != " << z.arg();
}

TEST(Complex_long_doubleTest, TestAbs2)
{
	long double re = 3.l, im = 4.l;
	GSL::Complex_long_double z(re, im);
	EXPECT_EQ(z.abs2(), 25.l) << "Absolute value not correct! z = " << z.real()
	 << " + " << z.imag() <<"i |z|^2 != " << z.abs2();
}

TEST(Complex_long_doubleTest, TestLogAbs)
{
	long double re = 3.l, im = 4.l;
	GSL::Complex_long_double z(re, im);
	long double diff = std::abs(z.logabs() - std::log(5.l)) ;
	EXPECT_TRUE(diff < 1e-10l) << "Absolute value not correct! z = " << z.real()
	 << " + " << z.imag() <<"i ln |z| != " << z.logabs();
}

TEST(Complex_long_doubleTest, TestConjugate)
{
	long double re = 3.l, im = 4.l;
	GSL::Complex_long_double z1(re, im);
	GSL::Complex_long_double z2(re, -im);
	EXPECT_EQ(z1.conjugate(), z2) << "Complex_long_double conjugate not correct! z = " <<
	z1.conjugate().real()	<< " + " << z1.conjugate().imag() <<" z* != " << z2;
}

TEST(Complex_long_doubleTest, TestRecipr)
{
	long double re = 3.l/8, im = 1.l/2;
	GSL::Complex_long_double z1(re, im);
	GSL::Complex_long_double z2(re/z1.abs2(), -im/z1.abs2());
	EXPECT_EQ(z1.recipr().real(), z2.real()) << "Reciprocal not correct! 1/z = " <<
	z1.recipr() <<"  != " << z2;
	EXPECT_EQ(z1.recipr().imag(), z2.imag()) << "Reciprocal not correct! 1/z = " <<
	z1.recipr() <<"  != " << z2;
}

TEST(Complex_long_doubleTest, TestNegate)
{
	long double re = 3.l, im = 4.l;
	GSL::Complex_long_double z1(re, im);
	GSL::Complex_long_double z2(-re, -im);
	EXPECT_EQ(z1.negate().real(), z2.real());
	EXPECT_EQ(z1.negate().imag(), z2.imag());
}
*/
