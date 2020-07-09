#include "GSLpp/vector.h"
#include <gtest/gtest.h>
#include <iostream>
#include <cmath>

TEST(Vector_ucTest, TestConstruction)
{
    GSL::Vector_uc v(3);
    EXPECT_EQ(v[0], 0.);
    EXPECT_EQ(v[1], 0.);
    EXPECT_EQ(v[2], 0.);
}

TEST(Vector_ucTest, TestConstructionInitializerList)
{
    unsigned char a =1, b = 2, c = 3.;
    GSL::Vector_uc v{a, b, c};
    EXPECT_EQ(v[0], 1.);
    EXPECT_EQ(v[1], 2.);
    EXPECT_EQ(v[2], 3.);
}

TEST(Vector_ucTest, TestConstructionCopy)
{
    unsigned char a =1, b = 2, c = 3.;
    GSL::Vector_uc v1{a, b, c};
    GSL::Vector_uc v2{v1};
    EXPECT_EQ(v1[0], v2[0]);
    EXPECT_EQ(v1[1], v2[1]);
    EXPECT_EQ(v1[2], v2[2]);
}

TEST(Vector_ucTest, TestConstructionMove)
{
    unsigned char a =1, b = 2, c = 3.;
    GSL::Vector_uc v1{a, b, c};
    GSL::Vector_uc v2{std::move(v1)};
    EXPECT_EQ(v2[0], 1.);
    EXPECT_EQ(v2[1], 2.);
    EXPECT_EQ(v2[2], 3.);
}

TEST(Vector_ucTest, TestEqual)
{

    unsigned char a =1, b = 2, c = 3.;
    GSL::Vector_uc v1{a, b, c};
    GSL::Vector_uc v2{v1};

    EXPECT_EQ(v1, v2);
}

TEST(Vector_ucTest, TestNotEqual)
{

    unsigned char a =1, b = 2, c = 3.;
    GSL::Vector_uc v1{a, b, c};
    GSL::Vector_uc v2{static_cast<unsigned char>(a +1), b, c};

    EXPECT_NE(v1, v2);
}

TEST(Vector_ucTest, TestCopy)
{

    unsigned char a =1, b = 2, c = 3.;
    GSL::Vector_uc v1{a, b, c};
    GSL::Vector_uc v2;
    v2 = v1;

    EXPECT_EQ(v1, v2);
}

TEST(Vector_ucTest, TestMove)
{

    unsigned char a =1, b = 2, c = 3.;
    GSL::Vector_uc v1{a, b, c}, v1s{a, b, c};
    GSL::Vector_uc v2;
    v2 = std::move(v1);

    EXPECT_EQ(v2, v1s);
}

TEST(Vector_ucTest, TestDecayToGSLVector_uc)
{
    unsigned char a =1, b = 2, c = 3.;
    GSL::Vector_uc v{a, b, c};
    gsl_vector_uchar gv = v;

    EXPECT_EQ(gsl_vector_uchar_get(&gv, 0), a);
}

TEST(Vector_ucTest, TestSize)
{
    unsigned char a = 1, b = 2, c = 3.;
    GSL::Vector_uc v{a, b, c};

    EXPECT_EQ(v.size(), 3);
}

TEST(Vector_ucTest, TestDim)
{
    unsigned char a =1, b = 2, c = 3.;
    GSL::Vector_uc v{a, b, c};

    EXPECT_EQ(v.dim(), 3);
}

TEST(Vector_ucTest, TestCopyFun)
{
    unsigned char a =1, b = 2, c = 3.;
    GSL::Vector_uc v{a, b, c}, v2;
    v2.copy(v);

    EXPECT_EQ(v, v2);
}

TEST(Vector_ucTest, TestNorm)
{
    unsigned char a =1, b = 2, c = 3.;
    GSL::Vector_uc v{a, b, c};

    EXPECT_EQ(v.norm<double>(), std::sqrt(a*a + b*b + c*c));
}

TEST(Vector_ucTest, TestNormalize)
{
    unsigned char a =1, b = 2, c = 3.;
    GSL::Vector_uc v{a, b, c};
    v.normalize<double>();

    EXPECT_EQ(v.norm<double>(), 1.);
}

TEST(Vector_ucTest, TestDot)
{
    GSL::Vector_uc v1{1, 0, 0}, v2{0, 1, 0};

    EXPECT_EQ(v1.dot(v2), 0.);
}

TEST(Vector_ucTest, TestCross)
{
    GSL::Vector_uc v1{1, 0, 0}, v2{0, 1, 0}, v3{0, 0, 1};

    EXPECT_EQ(v1.cross(v2), v3);
}

TEST(Vector_ucTest, TestIncrement)
{
    GSL::Vector_uc v1{1, 0, 0}, v2{0, 1, 0}, v3{1, 1, 0};

    EXPECT_EQ(v1 += v2, v3);
}

TEST(Vector_ucTest, TestDecrement)
{
    GSL::Vector_uc v1{1, 2, 0}, v2{0, 1, 0}, v3{1, 1, 0};

    EXPECT_EQ(v1 -= v2, v3);
}

TEST(Vector_ucTest, TestElMultScale)
{
    GSL::Vector_uc v1{3, 2, 2}, v2{2, 3, 4}, v3{6, 6, 8};

    EXPECT_EQ(v1 *= v2, v3);
}

TEST(Vector_ucTest, TestElDivScale)
{
    GSL::Vector_uc v1{8, 4, 2}, v2{6, 3, 2}, v3{8/6, 4/3, 2/2};

    EXPECT_EQ(v1 /= v2, v3);
}

TEST(Vector_ucTest, TestMultScale)
{
    GSL::Vector_uc v1{3, 2, 2}, v2{9, 6, 6};

    EXPECT_EQ(v1 *= 3, v2);
}

TEST(Vector_ucTest, TestDivScale)
{
    GSL::Vector_uc v1{8, 4, 2}, v2{4, 2, 1};

    EXPECT_EQ(v1 /= 2, v2);
}

TEST(Vector_ucTest, TestAddition)
{
    GSL::Vector_uc v1{1, 0, 0}, v2{0, 1, 0}, v3{1, 1, 0};

    EXPECT_EQ(v1 + v2, v3);
}

TEST(Vector_ucTest, TestSubtraction)
{
    GSL::Vector_uc v1{1, 2, 0}, v2{0, 1, 0}, v3{1, 1, 0};

    EXPECT_EQ(v1 - v2, v3);
}

TEST(Vector_ucTest, TestElMult)
{
    GSL::Vector_uc v1{3, 2, 2}, v2{2, 3, 4}, v3{6, 6, 8};

    EXPECT_EQ(v1 * v2, v3);
}

TEST(Vector_ucTest, TestElDiv)
{
    GSL::Vector_uc v1{8, 4, 2}, v2{6, 3, 2}, v3{8/6, 4/3, 2/2};

    EXPECT_EQ(v1 / v2, v3);
}

TEST(Vector_ucTest, TestScalarMult)
{
    GSL::Vector_uc v1{3, 2, 2}, v2{9, 6, 6};

    EXPECT_EQ(v1 * 3, v2);
}

TEST(Vector_ucTest, TestScalarDiv)
{
    GSL::Vector_uc v1{8, 4, 2}, v2{4, 2, 1};

    EXPECT_EQ(v1 / 2, v2);
}

TEST(Vector_ucTest, TestScalarMult2)
{
    GSL::Vector_uc v1{3, 2, 2}, v2{9, 6, 6};

    EXPECT_EQ(3. * v1, v2);
}

TEST(Vector_ucTest, TestBegin)
{
    GSL::Vector_uc v{1, 2, 3};
    EXPECT_EQ(*v.begin(), 1.);
}

TEST(Vector_ucTest, TestcBegin)
{
    GSL::Vector_uc v{1, 2, 3};
    EXPECT_EQ(*v.cbegin(), 1.);
}

TEST(Vector_ucTest, TestIterPreIncrement)
{
    GSL::Vector_uc v{1, 2, 3};
    EXPECT_EQ(*++v.begin(), 2.);
}

TEST(Vector_ucTest, TestIterPostIncrement)
{
    GSL::Vector_uc v{1, 2, 3};
    auto it = v.begin();
    it++;
    EXPECT_EQ(*it, 2.);
}

TEST(Vector_ucTest, TestIterPreDecrement)
{
    GSL::Vector_uc v{1, 2, 3};
    EXPECT_EQ(*--(++v.begin()), 1.);
}

TEST(Vector_ucTest, TestIterPostDecrement)
{
    GSL::Vector_uc v{1, 2, 3};
    auto it = v.begin();
    it++; it--;
    EXPECT_EQ(*it, 1.);
}

TEST(Vector_ucTest, TestIterStepIncrement)
{
    GSL::Vector_uc v{1, 2, 3};
    auto it = v.begin();
    it += 2;
    EXPECT_EQ(*it, 3.);
}

TEST(Vector_ucTest, TestIterStep)
{
    GSL::Vector_uc v{1, 2, 3};
    auto it = v.begin();
    EXPECT_EQ(*(it + 2), 3.);
}

TEST(Vector_ucTest, TestIterStepDecrement)
{
    GSL::Vector_uc v{1, 2, 3};
    auto it = v.begin();
    it += 2;
    it -= 2;
    EXPECT_EQ(*it, 1.);
}

TEST(Vector_ucTest, TestIterStepBack)
{
    GSL::Vector_uc v{1, 2, 3};
    auto it = v.begin() + 2;
    EXPECT_EQ(*(it - 2), 1.);
}

TEST(Vector_ucTest, TestIterDiff)
{
    GSL::Vector_uc v{1, 2, 3};
    auto it = v.begin() + 2;
    EXPECT_EQ(it - v.begin(), 2.);
}

TEST(Vector_ucTest, TestIterEq)
{
    GSL::Vector_uc v{1, 2, 3};
    auto it1 = v.begin() + 2;
    auto it2 = v.begin();
    it2 += 2;

    EXPECT_EQ(it1, it2);
}

TEST(Vector_ucTest, TestIterNeq)
{
    GSL::Vector_uc v{1, 2, 3};
    auto it1 = v.begin() + 2;
    auto it2 = v.begin();

    EXPECT_NE(it1, it2);
}

TEST(Vector_ucTest, TestEnd)
{
    GSL::Vector_uc v{1, 2, 3};
    auto it1 = v.begin() + 2;
    auto it2 = v.end();

    EXPECT_EQ(it1, --it2);
}

TEST(Vector_ucTest, TestcIterPreIncrement)
{
    GSL::Vector_uc v{1, 2, 3};
    EXPECT_EQ(*++v.cbegin(), 2.);
}

TEST(Vector_ucTest, TestcIterPostIncrement)
{
    GSL::Vector_uc v{1, 2, 3};
    auto it = v.cbegin();
    it++;
    EXPECT_EQ(*it, 2.);
}

TEST(Vector_ucTest, TestcIterPreDecrement)
{
    GSL::Vector_uc v{1, 2, 3};
    EXPECT_EQ(*--(++v.cbegin()), 1.);
}

TEST(Vector_ucTest, TestcIterPostDecrement)
{
    GSL::Vector_uc v{1, 2, 3};
    auto it = v.cbegin();
    it++; it--;
    EXPECT_EQ(*it, 1.);
}

TEST(Vector_ucTest, TestcIterStepIncrement)
{
    GSL::Vector_uc v{1, 2, 3};
    auto it = v.cbegin();
    it += 2;
    EXPECT_EQ(*it, 3.);
}

TEST(Vector_ucTest, TestcIterStep)
{
    GSL::Vector_uc v{1, 2, 3};
    auto it = v.cbegin();
    EXPECT_EQ(*(it + 2), 3.);
}

TEST(Vector_ucTest, TestcIterStepDecrement)
{
    GSL::Vector_uc v{1, 2, 3};
    auto it = v.cbegin();
    it += 2;
    it -= 2;
    EXPECT_EQ(*it, 1.);
}

TEST(Vector_ucTest, TestcIterStepBack)
{
    GSL::Vector_uc v{1, 2, 3};
    auto it = v.cbegin() + 2;
    EXPECT_EQ(*(it - 2), 1.);
}

TEST(Vector_ucTest, TestcIterDiff)
{
    GSL::Vector_uc v{1, 2, 3};
    auto it = v.cbegin() + 2;
    EXPECT_EQ(it - v.cbegin(), 2.);
}

TEST(Vector_ucTest, TestcIterEq)
{
    GSL::Vector_uc v{1, 2, 3};
    auto it1 = v.cbegin() + 2;
    auto it2 = v.cbegin();
    it2 += 2;

    EXPECT_EQ(it1, it2);
}

TEST(Vector_ucTest, TestcIterNeq)
{
    GSL::Vector_uc v{1, 2, 3};
    auto it1 = v.cbegin() + 2;
    auto it2 = v.cbegin();

    EXPECT_NE(it1, it2);
}

TEST(Vector_ucTest, TestcEnd)
{
    GSL::Vector_uc v{1, 2, 3};
    auto it1 = v.cbegin() + 2;
    auto it2 = v.cend();

    EXPECT_EQ(it1, --it2);
}

TEST(Vector_ucTest, TestRbegin)
{
    GSL::Vector_uc v{1, 2, 3};
    auto it1 = v.rbegin();

    EXPECT_EQ(*it1, 3.);
}

TEST(Vector_ucTest, TestRend)
{
    GSL::Vector_uc v{1, 2, 3};
    auto it1 = v.rend();

    EXPECT_EQ(*--it1, 1.);
}

TEST(Vector_ucTest, TestcRbegin)
{
    GSL::Vector_uc v{1, 2, 3};
    auto it1 = v.crbegin();

    EXPECT_EQ(*it1, 3.);
}

TEST(Vector_ucTest, TestcRend)
{
    GSL::Vector_uc v{1, 2, 3};
    auto it1 = v.crend();

    EXPECT_EQ(*--it1, 1.);
}

TEST(Vector_ucTest, TestFront)
{
    GSL::Vector_uc v{1, 2, 3};
    EXPECT_EQ(v.front(), 1.);
}

TEST(Vector_ucTest, TestBack)
{
    GSL::Vector_uc v{1, 2, 3};
    EXPECT_EQ(v.back(), 3.);
}

TEST(Vector_ucTest, TestAt)
{
    GSL::Vector_uc v{1, 2, 3};
    EXPECT_EQ(v.at(1), 2.);
}

TEST(Vector_ucTest, TestAssign1)
{
    GSL::Vector_uc v1{1, 2, 3};
    GSL::Vector_uc v2{3, 4, 5};
    v2.assign(v1.begin(), v1.end());
    EXPECT_EQ(v1, v2);
}

TEST(Vector_ucTest, TestAssign2)
{
    GSL::Vector_uc v1{1, 2, 3};
    GSL::Vector_uc v2{3, 3, 3, 3};
    v1.assign(4, 3.);
    EXPECT_EQ(v1, v2);
}

TEST(Vector_ucTest, TestAssign3)
{
    GSL::Vector_uc v1{1, 2, 3};
    GSL::Vector_uc v2{3, 4};
    v1.assign({3, 4});
    EXPECT_EQ(v1, v2);
}
