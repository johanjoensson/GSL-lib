#include "GSLpp/complex.h"
#include <gtest/gtest.h>

TEST(Complex_ldBaseMathTest, TestUm)
{
    double re = 1, im = 2;
    GSL::Complex_ld z(re, im);
    GSL::Complex_ld z2(z.negate());
    EXPECT_DOUBLE_EQ(-z.re(), z2.re());
    EXPECT_DOUBLE_EQ(-z.im(), z2.im());
}

TEST(Complex_ldBaseMathTest, TestIncrementC)
{
    double re = 1, im = 2;
    GSL::Complex_ld z(re, im);
    GSL::Complex_ld dz(re/10, im/5);
    GSL::Complex_ld z2(1.1, 2.4);
    z += dz;
    EXPECT_DOUBLE_EQ(z.re(), z2.re());
    EXPECT_DOUBLE_EQ(z.im(), z2.im());
}

TEST(Complex_ldBaseMathTest, TestDecrementC)
{
    double re = 1, im = 2;
    GSL::Complex_ld z(re, im);
    GSL::Complex_ld dz(re/10, im/5);
    GSL::Complex_ld z2(0.9, 1.6);
    z -= dz;
    EXPECT_DOUBLE_EQ(z.re(), z2.re());
    EXPECT_DOUBLE_EQ(z.im(), z2.im());
}

TEST(Complex_ldBaseMathTest, TestScaleC)
{
    double re = 1, im = 2;
    GSL::Complex_ld z(re, im);
    GSL::Complex_ld dz(re/10, im/5);
    GSL::Complex_ld z2(-0.7, 0.6);
    z *= dz;
    EXPECT_DOUBLE_EQ(z.re(), z2.re());
    EXPECT_DOUBLE_EQ(z.im(), z2.im());
}

TEST(Complex_ldBaseMathTest, TestDivC)
{
    double re = 1, im = 2;
    GSL::Complex_ld z(re, im);
    GSL::Complex_ld dz(re/10, im/5);
    GSL::Complex_ld z2 = z;
    z /= dz;
    z2 *= dz.recipr();
    EXPECT_DOUBLE_EQ(z.re(), z2.re());
    EXPECT_DOUBLE_EQ(z.im(), z2.im());
}

TEST(Complex_ldBaseMathTest, TestIncrementR)
{
    double re = 1, im = 2;
    GSL::Complex_ld z(re, im);
    double dz = 0.1;
    GSL::Complex_ld z2(1.1, 2);
    z += dz;
    EXPECT_DOUBLE_EQ(z.re(), z2.re());
    EXPECT_DOUBLE_EQ(z.im(), z2.im());
}

TEST(Complex_ldBaseMathTest, TestDecrementR)
{
    double re = 1, im = 2;
    GSL::Complex_ld z(re, im);
    double dz = 0.1;
    GSL::Complex_ld z2(0.9, 2);
    z -= dz;
    EXPECT_DOUBLE_EQ(z.re(), z2.re());
    EXPECT_DOUBLE_EQ(z.im(), z2.im());
}

TEST(Complex_ldBaseMathTest, TestScaleR)
{
    double re = 1, im = 2;
    GSL::Complex_ld z(re, im);
    double dz = 0.1;
    GSL::Complex_ld z2(0.1, 0.2);
    z *= dz;
    EXPECT_DOUBLE_EQ(z.re(), z2.re());
    EXPECT_DOUBLE_EQ(z.im(), z2.im());
}

TEST(Complex_ldBaseMathTest, TestDivR)
{
    double re = 1, im = 2;
    GSL::Complex_ld z(re, im);
    double dz = 0.1;
    GSL::Complex_ld z2 = z;
    z /= dz;
    z2 *= 1/dz;
    EXPECT_DOUBLE_EQ(z.re(), z2.re());
    EXPECT_DOUBLE_EQ(z.im(), z2.im());
}

TEST(Complex_ldBaseMathTest, TestAddC)
{
    double re = 1, im = 2;
    GSL::Complex_ld z(re, im);
    GSL::Complex_ld dz(re/10, im/5);
    GSL::Complex_ld z2(1.1, 2.4);
    EXPECT_DOUBLE_EQ((z + dz).re(), z2.re());
    EXPECT_DOUBLE_EQ((z + dz).im(), z2.im());
}

TEST(Complex_ldBaseMathTest, TestSubC)
{
    double re = 1, im = 2;
    GSL::Complex_ld z(re, im);
    GSL::Complex_ld dz(re/10, im/5);
    GSL::Complex_ld z2(0.9, 1.6);
    EXPECT_DOUBLE_EQ((z - dz).re(), z2.re());
    EXPECT_DOUBLE_EQ((z - dz).im(), z2.im());
}

TEST(Complex_ldBaseMathTest, TestMultC)
{
    double re = 1, im = 2;
    GSL::Complex_ld z(re, im);
    GSL::Complex_ld dz(re/10, im/5);
    GSL::Complex_ld z2(-0.7, 0.6);
    EXPECT_DOUBLE_EQ((z*dz).re(), z2.re());
    EXPECT_DOUBLE_EQ((z*dz).im(), z2.im());
}

TEST(Complex_ldBaseMathTest, TestDivideC)
{
    double re = 1, im = 2;
    GSL::Complex_ld z(re, im);
    GSL::Complex_ld dz(re/10, im/5);
    GSL::Complex_ld z2 = z * dz.recipr();
    EXPECT_DOUBLE_EQ((z/dz).re(), z2.re());
    EXPECT_DOUBLE_EQ((z/dz).im(), z2.im());
}

TEST(Complex_ldBaseMathTest, TestAddR)
{
    double re = 1, im = 2;
    GSL::Complex_ld z(re, im);
    double dz = 0.1;
    GSL::Complex_ld z2(1.1, 2);
    EXPECT_DOUBLE_EQ((z + dz).re(), z2.re());
    EXPECT_DOUBLE_EQ((z + dz).im(), z2.im());
}

TEST(Complex_ldBaseMathTest, TestSubR)
{
    double re = 1, im = 2;
    GSL::Complex_ld z(re, im);
    double dz = 0.1;
    GSL::Complex_ld z2(0.9, 2);
    EXPECT_DOUBLE_EQ((z - dz).re(), z2.re());
    EXPECT_DOUBLE_EQ((z - dz).im(), z2.im());
}

TEST(Complex_ldBaseMathTest, TestMulR)
{
    double re = 1, im = 2;
    GSL::Complex_ld z(re, im);
    double dz = 0.1;
    GSL::Complex_ld z2(0.1, 0.2);
    EXPECT_DOUBLE_EQ((z*dz).re(), z2.re());
    EXPECT_DOUBLE_EQ((z*dz).im(), z2.im());
}

TEST(Complex_ldBaseMathTest, TestDivideR)
{
    double re = 1, im = 2;
    GSL::Complex_ld z(re, im);
    double dz = 0.1;
    GSL::Complex_ld z2 = z*(1/dz);
    EXPECT_DOUBLE_EQ((z/dz).re(), z2.re());
    EXPECT_DOUBLE_EQ((z/dz).im(), z2.im());
}
