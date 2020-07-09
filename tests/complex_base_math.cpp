#include "GSLpp/complex.h"
#include <gtest/gtest.h>

TEST(ComplexBaseMathTest, TestUm)
{
    double re = 1, im = 2;
    GSL::Complex z(re, im);
    GSL::Complex z2(z.negate());
    EXPECT_EQ(-z, z2);
}

TEST(ComplexBaseMathTest, TestIncrementC)
{
    double re = 1, im = 2;
    GSL::Complex z(re, im);
    GSL::Complex dz(re/10, im/5);
    GSL::Complex z2(1.1, 2.4);
    z += dz;
    EXPECT_EQ(z, z2);
}

TEST(ComplexBaseMathTest, TestDecrementC)
{
    double re = 1, im = 2;
    GSL::Complex z(re, im);
    GSL::Complex dz(re/10, im/5);
    GSL::Complex z2(0.9, 1.6);
    z -= dz;
    EXPECT_EQ(z, z2);
}

TEST(ComplexBaseMathTest, TestScaleC)
{
    double re = 1, im = 2;
    GSL::Complex z(re, im);
    GSL::Complex dz(re/10, im/5);
    GSL::Complex z2(-0.7, 0.6);
    z *= dz;
    EXPECT_DOUBLE_EQ(z.re(), z2.re());
    EXPECT_DOUBLE_EQ(z.im(), z2.im());
}

TEST(ComplexBaseMathTest, TestDivC)
{
    double re = 1, im = 2;
    GSL::Complex z(re, im);
    GSL::Complex dz(re/10, im/5);
    GSL::Complex z2 = z;
    z /= dz;
    z2 *= dz.recipr();
    EXPECT_DOUBLE_EQ(z.re(), z2.re());
    EXPECT_DOUBLE_EQ(z.im(), z2.im());
}

TEST(ComplexBaseMathTest, TestIncrementR)
{
    double re = 1, im = 2;
    GSL::Complex z(re, im);
    double dz = 0.1;
    GSL::Complex z2(1.1, 2);
    z += dz;
    EXPECT_EQ(z, z2);
}

TEST(ComplexBaseMathTest, TestDecrementR)
{
    double re = 1, im = 2;
    GSL::Complex z(re, im);
    double dz = 0.1;
    GSL::Complex z2(0.9, 2);
    z -= dz;
    EXPECT_EQ(z, z2);
}

TEST(ComplexBaseMathTest, TestScaleR)
{
    double re = 1, im = 2;
    GSL::Complex z(re, im);
    double dz = 0.1;
    GSL::Complex z2(0.1, 0.2);
    z *= dz;
    EXPECT_DOUBLE_EQ(z.re(), z2.re());
    EXPECT_DOUBLE_EQ(z.im(), z2.im());
}

TEST(ComplexBaseMathTest, TestDivR)
{
    double re = 1, im = 2;
    GSL::Complex z(re, im);
    double dz = 0.1;
    GSL::Complex z2 = z;
    z /= dz;
    z2 *= 1/dz;
    EXPECT_DOUBLE_EQ(z.re(), z2.re());
    EXPECT_DOUBLE_EQ(z.im(), z2.im());
}

TEST(ComplexBaseMathTest, TestAddC)
{
    double re = 1, im = 2;
    GSL::Complex z(re, im);
    GSL::Complex dz(re/10, im/5);
    GSL::Complex z2(1.1, 2.4);
    EXPECT_EQ(z+dz, z2);
}

TEST(ComplexBaseMathTest, TestSubC)
{
    double re = 1, im = 2;
    GSL::Complex z(re, im);
    GSL::Complex dz(re/10, im/5);
    GSL::Complex z2(0.9, 1.6);
    EXPECT_EQ(z-dz, z2);
}

TEST(ComplexBaseMathTest, TestMultC)
{
    double re = 1, im = 2;
    GSL::Complex z(re, im);
    GSL::Complex dz(re/10, im/5);
    GSL::Complex z2(-0.7, 0.6);
    EXPECT_DOUBLE_EQ((z*dz).re(), z2.re());
    EXPECT_DOUBLE_EQ((z*dz).im(), z2.im());
}

TEST(ComplexBaseMathTest, TestDivideC)
{
    double re = 1, im = 2;
    GSL::Complex z(re, im);
    GSL::Complex dz(re/10, im/5);
    GSL::Complex z2 = z * dz.recipr();
    EXPECT_DOUBLE_EQ((z/dz).re(), z2.re());
    EXPECT_DOUBLE_EQ((z/dz).im(), z2.im());
}

TEST(ComplexBaseMathTest, TestAddR)
{
    double re = 1, im = 2;
    GSL::Complex z(re, im);
    double dz = 0.1;
    GSL::Complex z2(1.1, 2);
    EXPECT_EQ(z+ dz, z2);
}

TEST(ComplexBaseMathTest, TestSubR)
{
    double re = 1, im = 2;
    GSL::Complex z(re, im);
    double dz = 0.1;
    GSL::Complex z2(0.9, 2);
    EXPECT_EQ(z - dz, z2);
}

TEST(ComplexBaseMathTest, TestMulR)
{
    double re = 1, im = 2;
    GSL::Complex z(re, im);
    double dz = 0.1;
    GSL::Complex z2(0.1, 0.2);
    EXPECT_DOUBLE_EQ((z*dz).re(), z2.re());
    EXPECT_DOUBLE_EQ((z*dz).im(), z2.im());
}

TEST(ComplexBaseMathTest, TestDivideR)
{
    double re = 1, im = 2;
    GSL::Complex z(re, im);
    double dz = 0.1;
    GSL::Complex z2 = z*(1/dz);
    EXPECT_DOUBLE_EQ((z/dz).re(), z2.re());
    EXPECT_DOUBLE_EQ((z/dz).im(), z2.im());
}
