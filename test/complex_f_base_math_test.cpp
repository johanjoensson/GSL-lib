#include "GSLpp/complex.h"
#include <gtest/gtest.h>

TEST(Complex_fBaseMathTest, TestUm)
{
    double re = 1, im = 2;
    GSL::Complex_f z(re, im);
    GSL::Complex_f z2(z.negate());
    EXPECT_EQ(-z, z2);
}

TEST(Complex_fBaseMathTest, TestIncrementC)
{
    double re = 1, im = 2;
    GSL::Complex_f z(re, im);
    GSL::Complex_f dz(re/10, im/5);
    GSL::Complex_f z2(1.1, 2.4);
    z += dz;
    EXPECT_EQ(z, z2);
}

TEST(Complex_fBaseMathTest, TestDecrementC)
{
    double re = 1, im = 2;
    GSL::Complex_f z(re, im);
    GSL::Complex_f dz(re/10, im/5);
    GSL::Complex_f z2(0.9, 1.6);
    z -= dz;
    EXPECT_EQ(z, z2);
}

TEST(Complex_fBaseMathTest, TestScaleC)
{
    double re = 1, im = 2;
    GSL::Complex_f z(re, im);
    GSL::Complex_f dz(re/10, im/5);
    GSL::Complex_f z2(-0.7, 0.6);
    z *= dz;
    EXPECT_DOUBLE_EQ(z.re(), z2.re());
    EXPECT_DOUBLE_EQ(z.im(), z2.im());
}

TEST(Complex_fBaseMathTest, TestDivC)
{
    double re = 1, im = 2;
    GSL::Complex_f z(re, im);
    GSL::Complex_f dz(re/10, im/5);
    GSL::Complex_f z2 = z;
    z /= dz;
    z2 *= dz.recipr();
    EXPECT_DOUBLE_EQ(z.re(), z2.re());
    EXPECT_DOUBLE_EQ(z.im(), z2.im());
}

TEST(Complex_fBaseMathTest, TestIncrementR)
{
    double re = 1, im = 2;
    GSL::Complex_f z(re, im);
    double dz = 0.1;
    GSL::Complex_f z2(1.1, 2);
    z += dz;
    EXPECT_EQ(z, z2);
}

TEST(Complex_fBaseMathTest, TestDecrementR)
{
    double re = 1, im = 2;
    GSL::Complex_f z(re, im);
    double dz = 0.1;
    GSL::Complex_f z2(0.9, 2);
    z -= dz;
    EXPECT_EQ(z, z2);
}

TEST(Complex_fBaseMathTest, TestScaleR)
{
    double re = 1, im = 2;
    GSL::Complex_f z(re, im);
    double dz = 0.1;
    GSL::Complex_f z2(0.1, 0.2);
    z *= dz;
    EXPECT_DOUBLE_EQ(z.re(), z2.re());
    EXPECT_DOUBLE_EQ(z.im(), z2.im());
}

TEST(Complex_fBaseMathTest, TestDivR)
{
    double re = 1, im = 2;
    GSL::Complex_f z(re, im);
    double dz = 0.1;
    GSL::Complex_f z2 = z;
    z /= dz;
    z2 *= 1/dz;
    EXPECT_DOUBLE_EQ(z.re(), z2.re());
    EXPECT_DOUBLE_EQ(z.im(), z2.im());
}

TEST(Complex_fBaseMathTest, TestAddC)
{
    double re = 1, im = 2;
    GSL::Complex_f z(re, im);
    GSL::Complex_f dz(re/10, im/5);
    GSL::Complex_f z2(1.1, 2.4);
    EXPECT_EQ(z+dz, z2);
}

TEST(Complex_fBaseMathTest, TestSubC)
{
    double re = 1, im = 2;
    GSL::Complex_f z(re, im);
    GSL::Complex_f dz(re/10, im/5);
    GSL::Complex_f z2(0.9, 1.6);
    EXPECT_EQ(z-dz, z2);
}

TEST(Complex_fBaseMathTest, TestMultC)
{
    double re = 1, im = 2;
    GSL::Complex_f z(re, im);
    GSL::Complex_f dz(re/10, im/5);
    GSL::Complex_f z2(-0.7, 0.6);
    EXPECT_DOUBLE_EQ((z*dz).re(), z2.re());
    EXPECT_DOUBLE_EQ((z*dz).im(), z2.im());
}

TEST(Complex_fBaseMathTest, TestDivideC)
{
    double re = 1, im = 2;
    GSL::Complex_f z(re, im);
    GSL::Complex_f dz(re/10, im/5);
    GSL::Complex_f z2 = z * dz.recipr();
    EXPECT_DOUBLE_EQ((z/dz).re(), z2.re());
    EXPECT_DOUBLE_EQ((z/dz).im(), z2.im());
}

TEST(Complex_fBaseMathTest, TestAddR)
{
    double re = 1, im = 2;
    GSL::Complex_f z(re, im);
    double dz = 0.1;
    GSL::Complex_f z2(1.1, 2);
    EXPECT_EQ(z+ dz, z2);
}

TEST(Complex_fBaseMathTest, TestSubR)
{
    double re = 1, im = 2;
    GSL::Complex_f z(re, im);
    double dz = 0.1;
    GSL::Complex_f z2(0.9, 2);
    EXPECT_EQ(z - dz, z2);
}

TEST(Complex_fBaseMathTest, TestMulR)
{
    double re = 1, im = 2;
    GSL::Complex_f z(re, im);
    double dz = 0.1;
    GSL::Complex_f z2(0.1, 0.2);
    EXPECT_DOUBLE_EQ((z*dz).re(), z2.re());
    EXPECT_DOUBLE_EQ((z*dz).im(), z2.im());
}

TEST(Complex_fBaseMathTest, TestDivideR)
{
    double re = 1, im = 2;
    GSL::Complex_f z(re, im);
    double dz = 0.1;
    GSL::Complex_f z2 = z*(1/dz);
    EXPECT_DOUBLE_EQ((z/dz).re(), z2.re());
    EXPECT_DOUBLE_EQ((z/dz).im(), z2.im());
}
