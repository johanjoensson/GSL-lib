#include "GSLpp/complex.h"
#include <gtest/gtest.h>

TEST(Complex_fTest, TestConstructionGSLComplex_f)
{
	double re = 5.0, im = 1.3;
	gsl_complex_float c;
	c.dat[0] = re;
	c.dat[1] = im;
	GSL::Complex_f a(c);
	EXPECT_FLOAT_EQ(a.re(), re) << "Real parts do not match! " << a.re() << " != " << re;
	EXPECT_FLOAT_EQ(a.im(), im) << "Imaginary parts do not match " << a.im() << " != " << im;
}

TEST(Complex_fTest, TestConstructionRealImag)
{
	double re = 5.0, im = 1.3;
	GSL::Complex_f a(re, im);
	EXPECT_FLOAT_EQ(a.re(), re) << "Real parts do not match! " << a.re() << " != " << re;
	EXPECT_FLOAT_EQ(a.im(), im) << "Imaginary parts do not match " << a.im() << " != " << im;
}

TEST(Complex_fTest, TestConstructionCopy)
{
	double re = 5.0, im = 1.3;
	GSL::Complex_f a(re, im);
	GSL::Complex_f b(a);
	EXPECT_FLOAT_EQ(b.re(), re) << "Real parts do not match! " << b.re() << " != " << re;
	EXPECT_FLOAT_EQ(b.im(), im) << "Imaginary parts do not match " << b.im() << " != " << im;
}

TEST(Complex_fTest, TestConstructionMove)
{
	double re = 5.0, im = 1.3;
	GSL::Complex_f a(re, im);
	GSL::Complex_f b(std::move(a));
	EXPECT_FLOAT_EQ(b.re(), re) << "Real parts do not match! " << b.re() << " != " << re;
	EXPECT_FLOAT_EQ(b.im(), im) << "Imaginary parts do not match " << b.im() << " != " << im;
}

TEST(Complex_fTest, TestEqual)
{
	double re = 5.0, im = 1.3;
	GSL::Complex_f a(re, im);
	GSL::Complex_f b(re, im);
	EXPECT_EQ(a, b) << "Complex_f numbers not equal! " << a.re() << " != " << re - 1;
}

TEST(Complex_fTest, TestNotEqual)
{
	double re = 5.0, im = 1.3;
	GSL::Complex_f a(re, im);
	GSL::Complex_f b(re + 1, im - 1);
	EXPECT_NE(a, b) << "Complex_f numbers are equal! " << a << " == " << b;
}

TEST(Complex_fTest, TestCopy)
{
	double re = 4.3, im = 5;
	GSL::Complex_f a, b = GSL::Complex_f(re, im);
	a = b;
	EXPECT_FLOAT_EQ(a.re(), re) << "Real parts do not match! " << a.re() << " != " << re;
	EXPECT_FLOAT_EQ(a.im(), im) << "Imaginary parts do not match " << a.im() << " != " << im;

}

TEST(Complex_fTest, TestMove)
{
	double re = 4.3, im = 5;
	GSL::Complex_f a, b = GSL::Complex_f(re, im);
	a = std::move(b);
	EXPECT_FLOAT_EQ(a.re(), re) << "Real parts do not match! " << a.re() << " != " << re;
	EXPECT_FLOAT_EQ(a.im(), im) << "Imaginary parts do not match " << a.im() << " != " << im;

}

TEST(Complex_fTest, TestDecayToGSLComplex_f)
{
	double re = 3, im = 4;
	GSL::Complex_f z1(re, im);
	gsl_complex_float z2;
	z2.dat[0] = re;
	z2.dat[1] = im;
	EXPECT_FLOAT_EQ(z1.re(), z2.dat[0]);
	EXPECT_FLOAT_EQ(z1.im(), z2.dat[1]);
}

TEST(Complex_fTest, TestAbs)
{
	double re = 3, im = 4;
	GSL::Complex_f z(re, im);
	EXPECT_FLOAT_EQ(z.abs(), 5) << "Absolute value not correct! z = " << z.re()
	 << " + " << z.im() <<"i |z| != " << z.abs();
}

TEST(Complex_fTest, TestArg)
{
	double re = 0, im = 1;
	GSL::Complex_f z(re, im);
	EXPECT_FLOAT_EQ(z.arg(), M_PI/2) << "Argument not correct! z = " << z.re()
	 << " + " << z.im() <<"i arg(z) != " << z.arg();
}

TEST(Complex_fTest, TestAbs2)
{
	double re = 3, im = 4;
	GSL::Complex_f z(re, im);
	EXPECT_FLOAT_EQ(z.abs2(), 25) << "Absolute value not correct! z = " << z.re()
	 << " + " << z.im() <<"i |z|^2 != " << z.abs2();
}

TEST(Complex_fTest, TestLogAbs)
{
	double re = 3, im = 4;
	GSL::Complex_f z(re, im);
	EXPECT_FLOAT_EQ(z.logabs(), std::log(5)) << "Absolute value not correct! z = " << z.re()
	 << " + " << z.im() <<"i ln |z| != " << z.logabs();
}

TEST(Complex_fTest, TestConjugate)
{
	double re = 3, im = 4;
	GSL::Complex_f z1(re, im);
	GSL::Complex_f z2(re, -im);
	EXPECT_EQ(z1.conjugate(), z2) << "Complex_f conjugate not correct! z = " <<
	z1.conjugate().re()	<< " + " << z1.conjugate().im() <<" z* != " << z2;
}

TEST(Complex_fTest, TestRecipr)
{
	double re = 3./8, im = 1./2.;
	GSL::Complex_f z1(re, im);
	GSL::Complex_f z2(re/z1.abs2(), -im/z1.abs2());
	EXPECT_FLOAT_EQ(z1.recipr().re(), z2.re()) << "Reciprocal not correct! 1/z = " <<
	z1.recipr() <<"  != " << z2;
	EXPECT_FLOAT_EQ(z1.recipr().im(), z2.im()) << "Reciprocal not correct! 1/z = " <<
	z1.recipr() <<"  != " << z2;
}

TEST(Complex_fTest, TestNegate)
{
	double re = 3, im = 4;
	GSL::Complex_f z1(re, im);
	GSL::Complex_f z2(-re, -im);
	EXPECT_EQ(z1.negate(), z2) << "Negate not correct! z = " <<
	z1.negate().re()	<< " + " << z1.negate().im() <<"  != " << z2;
}
