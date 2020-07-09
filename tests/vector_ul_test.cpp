#include "GSLpp/vector.h"
#include <gtest/gtest.h>
#include <iostream>
#include <cmath>

TEST(Vector_ulTest, TestConstruction)
{
    GSL::Vector_ul v(3);
    EXPECT_EQ(v[0], 0.);
    EXPECT_EQ(v[1], 0.);
    EXPECT_EQ(v[2], 0.);
}

TEST(Vector_ulTest, TestConstructionInitializerList)
{
    unsigned long a =1, b = 2, c = 3.;
    GSL::Vector_ul v{a, b, c};
    EXPECT_EQ(v[0], 1.);
    EXPECT_EQ(v[1], 2.);
    EXPECT_EQ(v[2], 3.);
}

TEST(Vector_ulTest, TestConstructionCopy)
{
    unsigned long a =1, b = 2, c = 3.;
    GSL::Vector_ul v1{a, b, c};
    GSL::Vector_ul v2{v1};
    EXPECT_EQ(v1[0], v2[0]);
    EXPECT_EQ(v1[1], v2[1]);
    EXPECT_EQ(v1[2], v2[2]);
}

TEST(Vector_ulTest, TestConstructionMove)
{
    unsigned long a =1, b = 2, c = 3.;
    GSL::Vector_ul v1{a, b, c};
    GSL::Vector_ul v2{std::move(v1)};
    EXPECT_EQ(v2[0], 1.);
    EXPECT_EQ(v2[1], 2.);
    EXPECT_EQ(v2[2], 3.);
}

TEST(Vector_ulTest, TestEqual)
{

    unsigned long a =1, b = 2, c = 3.;
    GSL::Vector_ul v1{a, b, c};
    GSL::Vector_ul v2{v1};

    EXPECT_EQ(v1, v2);
}

TEST(Vector_ulTest, TestNotEqual)
{

    unsigned long a =1, b = 2, c = 3.;
    GSL::Vector_ul v1{a, b, c};
    GSL::Vector_ul v2{a +1, b, c};

    EXPECT_NE(v1, v2);
}

TEST(Vector_ulTest, TestCopy)
{

    unsigned long a =1, b = 2, c = 3.;
    GSL::Vector_ul v1{a, b, c};
    GSL::Vector_ul v2;
    v2 = v1;

    EXPECT_EQ(v1, v2);
}

TEST(Vector_ulTest, TestMove)
{

    unsigned long a =1, b = 2, c = 3.;
    GSL::Vector_ul v1{a, b, c}, v1s{a, b, c};
    GSL::Vector_ul v2;
    v2 = std::move(v1);

    EXPECT_EQ(v2, v1s);
}

TEST(Vector_ulTest, TestDecayToGSLVector_ul)
{
    unsigned long a =1, b = 2, c = 3.;
    GSL::Vector_ul v{a, b, c};
    gsl_vector_ulong gv = v;

    EXPECT_EQ(gsl_vector_ulong_get(&gv, 0), a);
}

TEST(Vector_ulTest, TestSize)
{
    unsigned long a = 1, b = 2, c = 3.;
    GSL::Vector_ul v{a, b, c};

    EXPECT_EQ(v.size(), 3);
}

TEST(Vector_ulTest, TestDim)
{
    unsigned long a =1, b = 2, c = 3.;
    GSL::Vector_ul v{a, b, c};

    EXPECT_EQ(v.dim(), 3);
}

TEST(Vector_ulTest, TestCopyFun)
{
    unsigned long a =1, b = 2, c = 3.;
    GSL::Vector_ul v{a, b, c}, v2;
    v2.copy(v);

    EXPECT_EQ(v, v2);
}

TEST(Vector_ulTest, TestNorm)
{
    unsigned long a =1, b = 2, c = 3.;
    GSL::Vector_ul v{a, b, c};

    EXPECT_EQ(v.norm<double>(), std::sqrt(a*a + b*b + c*c));
}

TEST(Vector_ulTest, TestNormalize)
{
    unsigned long a =1, b = 2, c = 3.;
    GSL::Vector_ul v{a, b, c};
    v.normalize<double>();

    EXPECT_EQ(v.norm<double>(), 1.);
}

TEST(Vector_ulTest, TestDot)
{
    GSL::Vector_ul v1{1, 0, 0}, v2{0, 1, 0};

    EXPECT_EQ(v1.dot(v2), 0.);
}

TEST(Vector_ulTest, TestCross)
{
    GSL::Vector_ul v1{1, 0, 0}, v2{0, 1, 0}, v3{0, 0, 1};

    EXPECT_EQ(v1.cross(v2), v3);
}

TEST(Vector_ulTest, TestIncrement)
{
    GSL::Vector_ul v1{1, 0, 0}, v2{0, 1, 0}, v3{1, 1, 0};

    EXPECT_EQ(v1 += v2, v3);
}

TEST(Vector_ulTest, TestDecrement)
{
    GSL::Vector_ul v1{1, 2, 0}, v2{0, 1, 0}, v3{1, 1, 0};

    EXPECT_EQ(v1 -= v2, v3);
}

TEST(Vector_ulTest, TestElMultScale)
{
    GSL::Vector_ul v1{3, 2, 2}, v2{2, 3, 4}, v3{6, 6, 8};

    EXPECT_EQ(v1 *= v2, v3);
}

TEST(Vector_ulTest, TestElDivScale)
{
    GSL::Vector_ul v1{8, 4, 2}, v2{6, 3, 2}, v3{8/6, 4/3, 2/2};

    EXPECT_EQ(v1 /= v2, v3);
}

TEST(Vector_ulTest, TestMultScale)
{
    GSL::Vector_ul v1{3, 2, 2}, v2{9, 6, 6};

    EXPECT_EQ(v1 *= 3, v2);
}

TEST(Vector_ulTest, TestDivScale)
{
    GSL::Vector_ul v1{8, 4, 2}, v2{4, 2, 1};

    EXPECT_EQ(v1 /= 2, v2);
}

TEST(Vector_ulTest, TestAddition)
{
    GSL::Vector_ul v1{1, 0, 0}, v2{0, 1, 0}, v3{1, 1, 0};

    EXPECT_EQ(v1 + v2, v3);
}

TEST(Vector_ulTest, TestSubtraction)
{
    GSL::Vector_ul v1{1, 2, 0}, v2{0, 1, 0}, v3{1, 1, 0};

    EXPECT_EQ(v1 - v2, v3);
}

TEST(Vector_ulTest, TestElMult)
{
    GSL::Vector_ul v1{3, 2, 2}, v2{2, 3, 4}, v3{6, 6, 8};

    EXPECT_EQ(v1 * v2, v3);
}

TEST(Vector_ulTest, TestElDiv)
{
    GSL::Vector_ul v1{8, 4, 2}, v2{6, 3, 2}, v3{8/6, 4/3, 2/2};

    EXPECT_EQ(v1 / v2, v3);
}

TEST(Vector_ulTest, TestScalarMult)
{
    GSL::Vector_ul v1{3, 2, 2}, v2{9, 6, 6};

    EXPECT_EQ(v1 * 3, v2);
}

TEST(Vector_ulTest, TestScalarDiv)
{
    GSL::Vector_ul v1{8, 4, 2}, v2{4, 2, 1};

    EXPECT_EQ(v1 / 2, v2);
}

TEST(Vector_ulTest, TestScalarMult2)
{
    GSL::Vector_ul v1{3, 2, 2}, v2{9, 6, 6};

    EXPECT_EQ(3. * v1, v2);
}

TEST(Vector_ulTest, TestBegin)
{
    GSL::Vector_ul v{1, 2, 3};
    EXPECT_EQ(*v.begin(), 1.);
}

TEST(Vector_ulTest, TestcBegin)
{
    GSL::Vector_ul v{1, 2, 3};
    EXPECT_EQ(*v.cbegin(), 1.);
}

TEST(Vector_ulTest, TestIterPreIncrement)
{
    GSL::Vector_ul v{1, 2, 3};
    EXPECT_EQ(*++v.begin(), 2.);
}

TEST(Vector_ulTest, TestIterPostIncrement)
{
    GSL::Vector_ul v{1, 2, 3};
    auto it = v.begin();
    it++;
    EXPECT_EQ(*it, 2.);
}

TEST(Vector_ulTest, TestIterPreDecrement)
{
    GSL::Vector_ul v{1, 2, 3};
    EXPECT_EQ(*--(++v.begin()), 1.);
}

TEST(Vector_ulTest, TestIterPostDecrement)
{
    GSL::Vector_ul v{1, 2, 3};
    auto it = v.begin();
    it++; it--;
    EXPECT_EQ(*it, 1.);
}

TEST(Vector_ulTest, TestIterStepIncrement)
{
    GSL::Vector_ul v{1, 2, 3};
    auto it = v.begin();
    it += 2;
    EXPECT_EQ(*it, 3.);
}

TEST(Vector_ulTest, TestIterStep)
{
    GSL::Vector_ul v{1, 2, 3};
    auto it = v.begin();
    EXPECT_EQ(*(it + 2), 3.);
}

TEST(Vector_ulTest, TestIterStepDecrement)
{
    GSL::Vector_ul v{1, 2, 3};
    auto it = v.begin();
    it += 2;
    it -= 2;
    EXPECT_EQ(*it, 1.);
}

TEST(Vector_ulTest, TestIterStepBack)
{
    GSL::Vector_ul v{1, 2, 3};
    auto it = v.begin() + 2;
    EXPECT_EQ(*(it - 2), 1.);
}

TEST(Vector_ulTest, TestIterDiff)
{
    GSL::Vector_ul v{1, 2, 3};
    auto it = v.begin() + 2;
    EXPECT_EQ(it - v.begin(), 2.);
}

TEST(Vector_ulTest, TestIterEq)
{
    GSL::Vector_ul v{1, 2, 3};
    auto it1 = v.begin() + 2;
    auto it2 = v.begin();
    it2 += 2;

    EXPECT_EQ(it1, it2);
}

TEST(Vector_ulTest, TestIterNeq)
{
    GSL::Vector_ul v{1, 2, 3};
    auto it1 = v.begin() + 2;
    auto it2 = v.begin();

    EXPECT_NE(it1, it2);
}

TEST(Vector_ulTest, TestEnd)
{
    GSL::Vector_ul v{1, 2, 3};
    auto it1 = v.begin() + 2;
    auto it2 = v.end();

    EXPECT_EQ(it1, --it2);
}

TEST(Vector_ulTest, TestcIterPreIncrement)
{
    GSL::Vector_ul v{1, 2, 3};
    EXPECT_EQ(*++v.cbegin(), 2.);
}

TEST(Vector_ulTest, TestcIterPostIncrement)
{
    GSL::Vector_ul v{1, 2, 3};
    auto it = v.cbegin();
    it++;
    EXPECT_EQ(*it, 2.);
}

TEST(Vector_ulTest, TestcIterPreDecrement)
{
    GSL::Vector_ul v{1, 2, 3};
    EXPECT_EQ(*--(++v.cbegin()), 1.);
}

TEST(Vector_ulTest, TestcIterPostDecrement)
{
    GSL::Vector_ul v{1, 2, 3};
    auto it = v.cbegin();
    it++; it--;
    EXPECT_EQ(*it, 1.);
}

TEST(Vector_ulTest, TestcIterStepIncrement)
{
    GSL::Vector_ul v{1, 2, 3};
    auto it = v.cbegin();
    it += 2;
    EXPECT_EQ(*it, 3.);
}

TEST(Vector_ulTest, TestcIterStep)
{
    GSL::Vector_ul v{1, 2, 3};
    auto it = v.cbegin();
    EXPECT_EQ(*(it + 2), 3.);
}

TEST(Vector_ulTest, TestcIterStepDecrement)
{
    GSL::Vector_ul v{1, 2, 3};
    auto it = v.cbegin();
    it += 2;
    it -= 2;
    EXPECT_EQ(*it, 1.);
}

TEST(Vector_ulTest, TestcIterStepBack)
{
    GSL::Vector_ul v{1, 2, 3};
    auto it = v.cbegin() + 2;
    EXPECT_EQ(*(it - 2), 1.);
}

TEST(Vector_ulTest, TestcIterDiff)
{
    GSL::Vector_ul v{1, 2, 3};
    auto it = v.cbegin() + 2;
    EXPECT_EQ(it - v.cbegin(), 2.);
}

TEST(Vector_ulTest, TestcIterEq)
{
    GSL::Vector_ul v{1, 2, 3};
    auto it1 = v.cbegin() + 2;
    auto it2 = v.cbegin();
    it2 += 2;

    EXPECT_EQ(it1, it2);
}

TEST(Vector_ulTest, TestcIterNeq)
{
    GSL::Vector_ul v{1, 2, 3};
    auto it1 = v.cbegin() + 2;
    auto it2 = v.cbegin();

    EXPECT_NE(it1, it2);
}

TEST(Vector_ulTest, TestcEnd)
{
    GSL::Vector_ul v{1, 2, 3};
    auto it1 = v.cbegin() + 2;
    auto it2 = v.cend();

    EXPECT_EQ(it1, --it2);
}

TEST(Vector_ulTest, TestRbegin)
{
    GSL::Vector_ul v{1, 2, 3};
    auto it1 = v.rbegin();

    EXPECT_EQ(*it1, 3.);
}

TEST(Vector_ulTest, TestRend)
{
    GSL::Vector_ul v{1, 2, 3};
    auto it1 = v.rend();

    EXPECT_EQ(*--it1, 1.);
}

TEST(Vector_ulTest, TestcRbegin)
{
    GSL::Vector_ul v{1, 2, 3};
    auto it1 = v.crbegin();

    EXPECT_EQ(*it1, 3.);
}

TEST(Vector_ulTest, TestcRend)
{
    GSL::Vector_ul v{1, 2, 3};
    auto it1 = v.crend();

    EXPECT_EQ(*--it1, 1.);
}

TEST(Vector_ulTest, TestFront)
{
    GSL::Vector_ul v{1, 2, 3};
    EXPECT_EQ(v.front(), 1.);
}

TEST(Vector_ulTest, TestBack)
{
    GSL::Vector_ul v{1, 2, 3};
    EXPECT_EQ(v.back(), 3.);
}

TEST(Vector_ulTest, TestAt)
{
    GSL::Vector_ul v{1, 2, 3};
    EXPECT_EQ(v.at(1), 2.);
}

TEST(Vector_ulTest, TestAssign1)
{
    GSL::Vector_ul v1{1, 2, 3};
    GSL::Vector_ul v2{3, 4, 5};
    v2.assign(v1.begin(), v1.end());
    EXPECT_EQ(v1, v2);
}

TEST(Vector_ulTest, TestAssign2)
{
    GSL::Vector_ul v1{1, 2, 3};
    GSL::Vector_ul v2{3, 3, 3, 3};
    v1.assign(4, 3.);
    EXPECT_EQ(v1, v2);
}

TEST(Vector_ulTest, TestAssign3)
{
    GSL::Vector_ul v1{1, 2, 3};
    GSL::Vector_ul v2{3, 4};
    v1.assign({3, 4});
    EXPECT_EQ(v1, v2);
}
