#include "GSLpp/complex.h"
#include <gtest/gtest.h>

TEST(Complex_ldTest, TestConstructionGSLComplex_ld)
{
	double re = 5.0, im = 1.3;
	gsl_complex_long_double c;
	c.dat[0] = re;
	c.dat[1] = im;
	GSL::Complex_ld a(c);
	EXPECT_EQ(a.re(), re) << "Real parts do not match! " << a.re() << " != " << re;
	EXPECT_EQ(a.im(), im) << "Imaginary parts do not match " << a.im() << " != " << im;
}

TEST(Complex_ldTest, TestConstructionRealImag)
{
	double re = 5.0, im = 1.3;
	GSL::Complex_ld a(re, im);
	EXPECT_EQ(a.re(), re) << "Real parts do not match! " << a.re() << " != " << re;
	EXPECT_EQ(a.im(), im) << "Imaginary parts do not match " << a.im() << " != " << im;
}

TEST(Complex_ldTest, TestConstructionCopy)
{
	double re = 5.0, im = 1.3;
	GSL::Complex_ld a(re, im);
	GSL::Complex_ld b(a);
	EXPECT_EQ(b.re(), re) << "Real parts do not match! " << b.re() << " != " << re;
	EXPECT_EQ(b.im(), im) << "Imaginary parts do not match " << b.im() << " != " << im;
}

TEST(Complex_ldTest, TestConstructionMove)
{
	double re = 5.0, im = 1.3;
	GSL::Complex_ld a(re, im);
	GSL::Complex_ld b(std::move(a));
	EXPECT_EQ(b.re(), re) << "Real parts do not match! " << b.re() << " != " << re;
	EXPECT_EQ(b.im(), im) << "Imaginary parts do not match " << b.im() << " != " << im;
}

TEST(Complex_ldTest, TestEqual)
{
	double re = 5.0, im = 1.3;
	GSL::Complex_ld a(re, im);
	GSL::Complex_ld b(re, im);
	EXPECT_EQ(a, b) << "Complex_ld numbers not equal! " << a.re() << " != " << re - 1;
}

TEST(Complex_ldTest, TestNotEqual)
{
	double re = 5.0, im = 1.3;
	GSL::Complex_ld a(re, im);
	GSL::Complex_ld b(re + 1, im - 1);
	EXPECT_NE(a, b) << "Complex_ld numbers are equal! " << a << " == " << b;
}

TEST(Complex_ldTest, TestCopy)
{
	double re = 4.3, im = 5;
	GSL::Complex_ld a, b = GSL::Complex_ld(re, im);
	a = b;
	EXPECT_EQ(a.re(), re) << "Real parts do not match! " << a.re() << " != " << re;
	EXPECT_EQ(a.im(), im) << "Imaginary parts do not match " << a.im() << " != " << im;

}

TEST(Complex_ldTest, TestMove)
{
	double re = 4.3, im = 5;
	GSL::Complex_ld a, b = GSL::Complex_ld(re, im);
	a = std::move(b);
	EXPECT_EQ(a.re(), re) << "Real parts do not match! " << a.re() << " != " << re;
	EXPECT_EQ(a.im(), im) << "Imaginary parts do not match " << a.im() << " != " << im;

}

TEST(Complex_ldTest, TestDecayToGSLComplex_ld)
{
	double re = 3, im = 4;
	GSL::Complex_ld z1(re, im);
	gsl_complex_long_double z2;
	z2.dat[0] = re;
	z2.dat[1] = im;
	EXPECT_DOUBLE_EQ(z1.re(), z2.dat[0]);
	EXPECT_DOUBLE_EQ(z1.im(), z2.dat[1]);
}

TEST(Complex_ldTest, TestAbs)
{
	double re = 3, im = 4;
	GSL::Complex_ld z(re, im);
	EXPECT_DOUBLE_EQ(z.abs(), 5) << "Absolute value not correct! z = " << z.re()
	 << " + " << z.im() <<"i |z| != " << z.abs();
}

TEST(Complex_ldTest, TestArg)
{
	double re = 0, im = 1;
	GSL::Complex_ld z(re, im);
	EXPECT_DOUBLE_EQ(z.arg(), M_PI/2) << "Argument not correct! z = " << z.re()
	 << " + " << z.im() <<"i arg(z) != " << z.arg();
}

TEST(Complex_ldTest, TestAbs2)
{
	double re = 3, im = 4;
	GSL::Complex_ld z(re, im);
	EXPECT_DOUBLE_EQ(z.abs2(), 25) << "Absolute value not correct! z = " << z.re()
	 << " + " << z.im() <<"i |z|^2 != " << z.abs2();
}

TEST(Complex_ldTest, TestLogAbs)
{
	double re = 3, im = 4;
	GSL::Complex_ld z(re, im);
	EXPECT_DOUBLE_EQ(z.logabs(), std::log(5)) << "Absolute value not correct! z = " << z.re()
	 << " + " << z.im() <<"i ln |z| != " << z.logabs();
}

TEST(Complex_ldTest, TestConjugate)
{
	double re = 3, im = 4;
	GSL::Complex_ld z1(re, im);
	GSL::Complex_ld z2(re, -im);
	EXPECT_EQ(z1.conjugate(), z2) << "Complex_ld conjugate not correct! z = " <<
	z1.conjugate().re()	<< " + " << z1.conjugate().im() <<" z* != " << z2;
}

TEST(Complex_ldTest, TestRecipr)
{
	double re = 3./8, im = 1./2.;
	GSL::Complex_ld z1(re, im);
	GSL::Complex_ld z2(re/z1.abs2(), -im/z1.abs2());
	EXPECT_DOUBLE_EQ(z1.recipr().re(), z2.re()) << "Reciprocal not correct! 1/z = " <<
	z1.recipr() <<"  != " << z2;
	EXPECT_DOUBLE_EQ(z1.recipr().im(), z2.im()) << "Reciprocal not correct! 1/z = " <<
	z1.recipr() <<"  != " << z2;
}

TEST(Complex_ldTest, TestNegate)
{
	double re = 3, im = 4;
	GSL::Complex_ld z1(re, im);
	GSL::Complex_ld z2(-re, -im);
	EXPECT_EQ(z1.negate().re(), z2.re());
	EXPECT_EQ(z1.negate().im(), z2.im());
}
