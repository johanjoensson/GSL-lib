#include "GSLpp/complex.h"
#include <gtest/gtest.h>

TEST(ComplexTest, TestEqual)
{
	double re = 5.0, im = 1.3;
	GSL::Complex a(re, im);
	EXPECT_EQ(a.re(), re) << "Real parts do not match! " << a.re() << " != " << re;
	EXPECT_EQ(a.im(), im) << "Imaginary parts do not match " << a.im() << " != " << im;
}

TEST(ComplexTest, TestNotEqual)
{
	double re = 5.0, im = 1.3;
	GSL::Complex a(re, im);
	EXPECT_NE(a.re(), re - 1) << "Real parts do match! " << a.re() << " == " << re - 1;
	EXPECT_NE(a.im(), im + 2) << "Imaginary parts do match " << a.im() << " == " << im + 2;
}

TEST(ComplexTest, TestAssign)
{
	double re = 4.3, im = 5;
	GSL::Complex a, b = GSL::Complex(re, im);
	a = b;
	EXPECT_EQ(a.re(), re) << "Real parts do not match! " << a.re() << " != " << re;
	EXPECT_EQ(a.im(), im) << "Imaginary parts do not match " << a.im() << " != " << im;

}
