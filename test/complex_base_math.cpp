#include "GSLpp/complex.h"
#include <gtest/gtest.h>

TEST(ComplexBaseTest, TestIncrement)
{
    double re = 1, im = 2;
    GSL::Complex z(re, im);
    GSL::Complex dz(re/10, im/5);
    GSL::Complex z2(1.1, 2.4);
    z += dz;
    EXPECT_EQ(z, z2);
}
