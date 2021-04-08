#include <GSLpp/complex.h>
#include <gtest/gtest.h>

TEST(ComplexTest, TestConstructionGSLComplex)
{
	double re = 5.0, im = 1.3;
	gsl_complex c = gsl_complex_rect(re, im);
	GSL::Complex a(c);
	EXPECT_EQ(a.re(), re) << "Real parts do not match! " << a.re() << " != " << re;
	EXPECT_EQ(a.im(), im) << "Imaginary parts do not match " << a.im() << " != " << im;
}

TEST(ComplexTest, TestConstructionRealImag)
{
	double re = 5.0, im = 1.3;
	GSL::Complex a(re, im);
	EXPECT_EQ(a.re(), re) << "Real parts do not match! " << a.re() << " != " << re;
	EXPECT_EQ(a.im(), im) << "Imaginary parts do not match " << a.im() << " != " << im;
}

TEST(ComplexTest, TestConstructionCopy)
{
	double re = 5.0, im = 1.3;
	GSL::Complex a(re, im);
	GSL::Complex b(a);
	EXPECT_EQ(b.re(), re) << "Real parts do not match! " << b.re() << " != " << re;
	EXPECT_EQ(b.im(), im) << "Imaginary parts do not match " << b.im() << " != " << im;
}

TEST(ComplexTest, TestConstructionMove)
{
	double re = 5.0, im = 1.3;
	GSL::Complex a(re, im);
	GSL::Complex b(std::move(a));
	EXPECT_EQ(b.re(), re) << "Real parts do not match! " << b.re() << " != " << re;
	EXPECT_EQ(b.im(), im) << "Imaginary parts do not match " << b.im() << " != " << im;
}

TEST(ComplexTest, TestEqual)
{
	double re = 5.0, im = 1.3;
	GSL::Complex a(re, im);
	GSL::Complex b(re, im);
	EXPECT_EQ(a, b) << "Complex numbers not equal! " << a.re() << " != " << re - 1;
}

TEST(ComplexTest, TestNotEqual)
{
	double re = 5.0, im = 1.3;
	GSL::Complex a(re, im);
	GSL::Complex b(re + 1, im - 1);
	EXPECT_NE(a, b) << "Complex numbers are equal! " << a << " == " << b;
}

TEST(ComplexTest, TestCopy)
{
	double re = 4.3, im = 5;
	GSL::Complex a, b = GSL::Complex(re, im);
	a = b;
	EXPECT_EQ(a.re(), re) << "Real parts do not match! " << a.re() << " != " << re;
	EXPECT_EQ(a.im(), im) << "Imaginary parts do not match " << a.im() << " != " << im;

}

TEST(ComplexTest, TestMove)
{
	double re = 4.3, im = 5;
	GSL::Complex a, b = GSL::Complex(re, im);
	a = std::move(b);
	EXPECT_EQ(a.re(), re) << "Real parts do not match! " << a.re() << " != " << re;
	EXPECT_EQ(a.im(), im) << "Imaginary parts do not match " << a.im() << " != " << im;

}

TEST(ComplexTest, TestDecayToGSLComplex)
{
	double re = 3, im = 4;
	GSL::Complex z1(re, im);
	EXPECT_DOUBLE_EQ(gsl_complex_abs(z1), 5) << "GSL::Complex does not decay to gsl_complex correctly";
}

TEST(ComplexTest, TestAbs)
{
	double re = 3, im = 4;
	GSL::Complex z(re, im);
	EXPECT_DOUBLE_EQ(z.abs(), 5) << "Absolute value not correct! z = " << z.re()
	 << " + " << z.im() <<"i |z| != " << z.abs();
}

TEST(ComplexTest, TestArg)
{
	double re = 0, im = 1;
	GSL::Complex z(re, im);
	EXPECT_DOUBLE_EQ(z.arg(), M_PI/2) << "Argument not correct! z = " << z.re()
	 << " + " << z.im() <<"i arg(z) != " << z.arg();
}

TEST(ComplexTest, TestAbs2)
{
	double re = 3, im = 4;
	GSL::Complex z(re, im);
	EXPECT_DOUBLE_EQ(z.abs2(), 25) << "Absolute value not correct! z = " << z.re()
	 << " + " << z.im() <<"i |z|^2 != " << z.abs2();
}

TEST(ComplexTest, TestLogAbs)
{
	double re = 3, im = 4;
	GSL::Complex z(re, im);
	EXPECT_DOUBLE_EQ(z.logabs(), std::log(5)) << "Absolute value not correct! z = " << z.re()
	 << " + " << z.im() <<"i ln |z| != " << z.logabs();
}

TEST(ComplexTest, TestConjugate)
{
	double re = 3, im = 4;
	GSL::Complex z1(re, im);
	GSL::Complex z2(re, -im);
	EXPECT_EQ(z1.conjugate(), z2) << "Complex conjugate not correct! z = " <<
	z1.conjugate().re()	<< " + " << z1.conjugate().im() <<" z* != " << z2;
}

TEST(ComplexTest, TestRecipr)
{
	double re = 3./8, im = 1./2.;
	GSL::Complex z1(re, im);
	GSL::Complex z2(re/z1.abs2(), -im/z1.abs2());
	EXPECT_DOUBLE_EQ(z1.recipr().re(), z2.re()) << "Reciprocal not correct! 1/z = " <<
	z1.recipr() <<"  != " << z2;
	EXPECT_DOUBLE_EQ(z1.recipr().im(), z2.im()) << "Reciprocal not correct! 1/z = " <<
	z1.recipr() <<"  != " << z2;
}

TEST(ComplexTest, TestNegate)
{
	double re = 3, im = 4;
	GSL::Complex z1(re, im);
	GSL::Complex z2(-re, -im);
	EXPECT_EQ(z1.negate(), z2) << "Negate not correct! z = " <<
	z1.negate().re()	<< " + " << z1.negate().im() <<"  != " << z2;
}
