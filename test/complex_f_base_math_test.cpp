#include "GSLpp/complex.h"
#include <gtest/gtest.h>

TEST(Complex_fBaseMathTest, TestUm)
{
    float re = 1, im = 2;
    GSL::Complex_f z(re, im);
    GSL::Complex_f z2(z.negate());
    EXPECT_EQ(-z, z2);
}

TEST(Complex_fBaseMathTest, TestIncrementC)
{
    float re = 1, im = 2;
    GSL::Complex_f z(re, im);
    GSL::Complex_f dz(re/10, im/5);
    GSL::Complex_f z2(1.1f, 2.4f);
    z += dz;
    EXPECT_EQ(z, z2);
}

TEST(Complex_fBaseMathTest, TestDecrementC)
{
    float re = 1, im = 2;
    GSL::Complex_f z(re, im);
    GSL::Complex_f dz(re/10, im/5);
    GSL::Complex_f z2(0.9f, 1.6f);
    z -= dz;
    EXPECT_EQ(z, z2);
}

TEST(Complex_fBaseMathTest, TestScaleC)
{
    float re = 1, im = 2;
    GSL::Complex_f z(re, im);
    GSL::Complex_f dz(re/10, im/5);
    GSL::Complex_f z2(-0.7f, 0.6f);
    z *= dz;
    EXPECT_DOUBLE_EQ(z.re(), z2.re());
    EXPECT_DOUBLE_EQ(z.im(), z2.im());
}

TEST(Complex_fBaseMathTest, TestDivC)
{
    float re = 1, im = 2;
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
    float re = 1, im = 2;
    GSL::Complex_f z(re, im);
    float dz = 0.1f;
    GSL::Complex_f z2(1.1f, 2);
    z += dz;
    EXPECT_EQ(z, z2);
}

TEST(Complex_fBaseMathTest, TestDecrementR)
{
    float re = 1, im = 2;
    GSL::Complex_f z(re, im);
    float dz = 0.1f;
    GSL::Complex_f z2(0.9f, 2);
    z -= dz;
    EXPECT_EQ(z, z2);
}

TEST(Complex_fBaseMathTest, TestScaleR)
{
    float re = 1, im = 2;
    GSL::Complex_f z(re, im);
    float dz = 0.1f;
    GSL::Complex_f z2(0.1f, 0.2f);
    z *= dz;
    EXPECT_DOUBLE_EQ(z.re(), z2.re());
    EXPECT_DOUBLE_EQ(z.im(), z2.im());
}

TEST(Complex_fBaseMathTest, TestDivR)
{
    float re = 1, im = 2;
    GSL::Complex_f z(re, im);
    float dz = 0.1f;
    GSL::Complex_f z2 = z;
    z /= dz;
    z2 *= 1/dz;
    EXPECT_DOUBLE_EQ(z.re(), z2.re());
    EXPECT_DOUBLE_EQ(z.im(), z2.im());
}

TEST(Complex_fBaseMathTest, TestAddC)
{
    float re = 1, im = 2;
    GSL::Complex_f z(re, im);
    GSL::Complex_f dz(re/10, im/5);
    GSL::Complex_f z2(1.1f, 2.4f);
    EXPECT_EQ(z+dz, z2);
}

TEST(Complex_fBaseMathTest, TestSubC)
{
    float re = 1, im = 2;
    GSL::Complex_f z(re, im);
    GSL::Complex_f dz(re/10, im/5);
    GSL::Complex_f z2(0.9f, 1.6f);
    EXPECT_EQ(z-dz, z2);
}

TEST(Complex_fBaseMathTest, TestMultC)
{
    float re = 1, im = 2;
    GSL::Complex_f z(re, im);
    GSL::Complex_f dz(re/10, im/5);
    GSL::Complex_f z2(-0.7f, 0.6f);
    EXPECT_DOUBLE_EQ((z*dz).re(), z2.re());
    EXPECT_DOUBLE_EQ((z*dz).im(), z2.im());
}

TEST(Complex_fBaseMathTest, TestDivideC)
{
    float re = 1, im = 2;
    GSL::Complex_f z(re, im);
    GSL::Complex_f dz(re/10, im/5);
    GSL::Complex_f z2 = z * dz.recipr();
    EXPECT_DOUBLE_EQ((z/dz).re(), z2.re());
    EXPECT_DOUBLE_EQ((z/dz).im(), z2.im());
}

TEST(Complex_fBaseMathTest, TestAddR)
{
    float re = 1, im = 2;
    GSL::Complex_f z(re, im);
    float dz = 0.1f;
    GSL::Complex_f z2(1.1f, 2);
    EXPECT_EQ(z+ dz, z2);
}

TEST(Complex_fBaseMathTest, TestSubR)
{
    float re = 1, im = 2;
    GSL::Complex_f z(re, im);
    float dz = 0.1f;
    GSL::Complex_f z2(0.9f, 2);
    EXPECT_EQ(z - dz, z2);
}

TEST(Complex_fBaseMathTest, TestMulR)
{
    float re = 1, im = 2;
    GSL::Complex_f z(re, im);
    float dz = 0.1f;
    GSL::Complex_f z2(0.1f, 0.2f);
    EXPECT_DOUBLE_EQ((z*dz).re(), z2.re());
    EXPECT_DOUBLE_EQ((z*dz).im(), z2.im());
}

TEST(Complex_fBaseMathTest, TestDivideR)
{
    float re = 1, im = 2;
    GSL::Complex_f z(re, im);
    float dz = 0.1f;
    GSL::Complex_f z2 = z*(1/dz);
    EXPECT_DOUBLE_EQ((z/dz).re(), z2.re());
    EXPECT_DOUBLE_EQ((z/dz).im(), z2.im());
}
