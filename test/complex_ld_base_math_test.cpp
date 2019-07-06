#include "GSLpp/complex.h"
#include <gtest/gtest.h>

TEST(Complex_ldBaseMathTest, TestUm)
{
    long double re = 1l, im = 2l;
    GSL::Complex_ld z(re, im);
    GSL::Complex_ld z2(z.negate());
    EXPECT_EQ(-z.re(), z2.re());
    EXPECT_EQ(-z.im(), z2.im());
}

TEST(Complex_ldBaseMathTest, TestIncrementC)
{
    long double re = 1l, im = 2l;
    GSL::Complex_ld z(re, im);
    GSL::Complex_ld dz(re/10l, im/5l);
    GSL::Complex_ld z2(1.1l, 2.4l);
    z += dz;
    EXPECT_EQ(z.re(), z2.re());
    EXPECT_EQ(z.im(), z2.im());
}

TEST(Complex_ldBaseMathTest, TestDecrementC)
{
    long double re = 1l, im = 2l;
    GSL::Complex_ld z(re, im);
    GSL::Complex_ld dz(re/10l, im/5l);
    GSL::Complex_ld z2(0.9l, 1.6l);
    z -= dz;
    EXPECT_EQ(z.re(), z2.re());
    EXPECT_EQ(z.im(), z2.im());
}

TEST(Complex_ldBaseMathTest, TestScaleC)
{
    long double re = 1l, im = 2l;
    GSL::Complex_ld z(re, im);
    GSL::Complex_ld dz(re/10l, im/5l);
    GSL::Complex_ld z2(-0.7l, 0.6l);
    z *= dz;
    EXPECT_EQ(z.re(), z2.re());
    EXPECT_EQ(z.im(), z2.im());
}

TEST(Complex_ldBaseMathTest, TestDivC)
{
    long double re = 1l, im = 2l;
    GSL::Complex_ld z(re, im);
    GSL::Complex_ld dz(re/10l, im/5l);
    GSL::Complex_ld z2 = z;
    z /= dz;
    z2 *= dz.recipr();
    EXPECT_EQ(z.re(), z2.re());
    EXPECT_EQ(z.im(), z2.im());
}

TEST(Complex_ldBaseMathTest, TestIncrementR)
{
    long double re = 1l, im = 2l;
    GSL::Complex_ld z(re, im);
    long double dz = 0.1l;
    GSL::Complex_ld z2(1.1l, 2l);
    z += dz;
    EXPECT_EQ(z.re(), z2.re());
    EXPECT_EQ(z.im(), z2.im());
}

TEST(Complex_ldBaseMathTest, TestDecrementR)
{
    long double re = 1l, im = 2l;
    GSL::Complex_ld z(re, im);
    long double dz = 0.1l;
    GSL::Complex_ld z2(0.9l, 2l);
    z -= dz;
    EXPECT_EQ(z.re(), z2.re());
    EXPECT_EQ(z.im(), z2.im());
}

TEST(Complex_ldBaseMathTest, TestScaleR)
{
    long double re = 1l, im = 2l;
    GSL::Complex_ld z(re, im);
    long double dz = 0.1l;
    GSL::Complex_ld z2(0.1l, 0.2l);
    z *= dz;
    EXPECT_EQ(z.re(), z2.re());
    EXPECT_EQ(z.im(), z2.im());
}

TEST(Complex_ldBaseMathTest, TestDivR)
{
    long double re = 1l, im = 2l;
    GSL::Complex_ld z(re, im);
    long double dz = 0.1l;
    GSL::Complex_ld z2 = z;
    z /= dz;
    z2 *= 1l/dz;
    EXPECT_EQ(z.re(), z2.re());
    EXPECT_EQ(z.im(), z2.im());
}

TEST(Complex_ldBaseMathTest, TestAddC)
{
    long double re = 1l, im = 2l;
    GSL::Complex_ld z(re, im);
    GSL::Complex_ld dz(re/10l, im/5l);
    GSL::Complex_ld z2(1.1l, 2.4l);
    EXPECT_EQ((z + dz).re(), z2.re());
    EXPECT_EQ((z + dz).im(), z2.im());
}

TEST(Complex_ldBaseMathTest, TestSubC)
{
    long double re = 1l, im = 2l;
    GSL::Complex_ld z(re, im);
    GSL::Complex_ld dz(re/10l, im/5l);
    GSL::Complex_ld z2(0.9l, 1.6l);
    EXPECT_EQ((z - dz).re(), z2.re());
    EXPECT_EQ((z - dz).im(), z2.im());
}

TEST(Complex_ldBaseMathTest, TestMultC)
{
    long double re = 1l, im = 2l;
    GSL::Complex_ld z(re, im);
    GSL::Complex_ld dz(re/10l, im/5l);
    GSL::Complex_ld z2(-0.7l, 0.6l);
    EXPECT_EQ((z*dz).re(), z2.re());
    EXPECT_EQ((z*dz).im(), z2.im());
}

TEST(Complex_ldBaseMathTest, TestDivideC)
{
    long double re = 1l, im = 2l;
    GSL::Complex_ld z(re, im);
    GSL::Complex_ld dz(re/10l, im/5l);
    GSL::Complex_ld z2 = z * dz.recipr();
    EXPECT_EQ((z/dz).re(), z2.re());
    EXPECT_EQ((z/dz).im(), z2.im());
}

TEST(Complex_ldBaseMathTest, TestAddR)
{
    long double re = 1l, im = 2l;
    GSL::Complex_ld z(re, im);
    long double dz = 0.1l;
    GSL::Complex_ld z2(1.1l, 2l);
    EXPECT_EQ((z + dz).re(), z2.re());
    EXPECT_EQ((z + dz).im(), z2.im());
}

TEST(Complex_ldBaseMathTest, TestSubR)
{
    long double re = 1l, im = 2l;
    GSL::Complex_ld z(re, im);
    long double dz = 0.1l;
    GSL::Complex_ld z2(0.9l, 2l);
    EXPECT_EQ((z - dz).re(), z2.re());
    EXPECT_EQ((z - dz).im(), z2.im());
}

TEST(Complex_ldBaseMathTest, TestMulR)
{
    long double re = 1l, im = 2l;
    GSL::Complex_ld z(re, im);
    long double dz = 0.1l;
    GSL::Complex_ld z2(0.1l, 0.2l);
    EXPECT_EQ((z*dz).re(), z2.re());
    EXPECT_EQ((z*dz).im(), z2.im());
}

TEST(Complex_ldBaseMathTest, TestDivideR)
{
    long double re = 1l, im = 2l;
    GSL::Complex_ld z(re, im);
    long double dz = 0.1l;
    GSL::Complex_ld z2 = z*(1l/dz);
    EXPECT_EQ((z/dz).re(), z2.re());
    EXPECT_EQ((z/dz).im(), z2.im());
}
