#include "complex.h"
#include <gtest/gtest.h>

TEST(ComplexTest, TestEqual)
{
	double re = 5.0, im = 1.3;
	GSL::Complex a(re, im);
	EXPECT_EQ(a.re(), re) << "Real parts do not match! " << a.re() << " != " << re;
	EXPECT_EQ(a.im(), im) << "Imaginary parts do not match " << a.im() << " != " << im;
}
