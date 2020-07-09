#include "GSLpp/vector.h"
#include <gtest/gtest.h>
#include <iostream>
#include <cmath>

TEST(Vector_usTest, TestConstruction)
{
    GSL::Vector_us v(3);
    EXPECT_EQ(v[0], 0.);
    EXPECT_EQ(v[1], 0.);
    EXPECT_EQ(v[2], 0.);
}

TEST(Vector_usTest, TestConstructionInitializerList)
{
    unsigned short a =1, b = 2, c = 3.;
    GSL::Vector_us v{a, b, c};
    EXPECT_EQ(v[0], 1.);
    EXPECT_EQ(v[1], 2.);
    EXPECT_EQ(v[2], 3.);
}

TEST(Vector_usTest, TestConstructionCopy)
{
    unsigned short a =1, b = 2, c = 3.;
    GSL::Vector_us v1{a, b, c};
    GSL::Vector_us v2{v1};
    EXPECT_EQ(v1[0], v2[0]);
    EXPECT_EQ(v1[1], v2[1]);
    EXPECT_EQ(v1[2], v2[2]);
}

TEST(Vector_usTest, TestConstructionMove)
{
    unsigned short a =1, b = 2, c = 3.;
    GSL::Vector_us v1{a, b, c};
    GSL::Vector_us v2{std::move(v1)};
    EXPECT_EQ(v2[0], 1.);
    EXPECT_EQ(v2[1], 2.);
    EXPECT_EQ(v2[2], 3.);
}

TEST(Vector_usTest, TestEqual)
{

    unsigned short a =1, b = 2, c = 3.;
    GSL::Vector_us v1{a, b, c};
    GSL::Vector_us v2{v1};

    EXPECT_EQ(v1, v2);
}

TEST(Vector_usTest, TestNotEqual)
{

    unsigned short a =1, b = 2, c = 3.;
    GSL::Vector_us v1{a, b, c};
    GSL::Vector_us v2{static_cast<unsigned short>(a +1), b, c};

    EXPECT_NE(v1, v2);
}

TEST(Vector_usTest, TestCopy)
{

    unsigned short a =1, b = 2, c = 3.;
    GSL::Vector_us v1{a, b, c};
    GSL::Vector_us v2;
    v2 = v1;

    EXPECT_EQ(v1, v2);
}

TEST(Vector_usTest, TestMove)
{

    unsigned short a =1, b = 2, c = 3.;
    GSL::Vector_us v1{a, b, c}, v1s{a, b, c};
    GSL::Vector_us v2;
    v2 = std::move(v1);

    EXPECT_EQ(v2, v1s);
}

TEST(Vector_usTest, TestDecayToGSLVector_us)
{
    unsigned short a =1, b = 2, c = 3.;
    GSL::Vector_us v{a, b, c};
    gsl_vector_ushort gv = v;

    EXPECT_EQ(gsl_vector_ushort_get(&gv, 0), a);
}

TEST(Vector_usTest, TestSize)
{
    unsigned short a = 1, b = 2, c = 3.;
    GSL::Vector_us v{a, b, c};

    EXPECT_EQ(v.size(), 3);
}

TEST(Vector_usTest, TestDim)
{
    unsigned short a =1, b = 2, c = 3.;
    GSL::Vector_us v{a, b, c};

    EXPECT_EQ(v.dim(), 3);
}

TEST(Vector_usTest, TestCopyFun)
{
    unsigned short a =1, b = 2, c = 3.;
    GSL::Vector_us v{a, b, c}, v2;
    v2.copy(v);

    EXPECT_EQ(v, v2);
}

TEST(Vector_usTest, TestNorm)
{
    unsigned short a =1, b = 2, c = 3.;
    GSL::Vector_us v{a, b, c};

    EXPECT_EQ(v.norm<double>(), std::sqrt(a*a + b*b + c*c));
}

TEST(Vector_usTest, TestNormalize)
{
    unsigned short a =1, b = 2, c = 3.;
    GSL::Vector_us v{a, b, c};
    v.normalize<double>();

    EXPECT_EQ(v.norm<double>(), 1.);
}

TEST(Vector_usTest, TestDot)
{
    GSL::Vector_us v1{1, 0, 0}, v2{0, 1, 0};

    EXPECT_EQ(v1.dot(v2), 0.);
}

TEST(Vector_usTest, TestCross)
{
    GSL::Vector_us v1{1, 0, 0}, v2{0, 1, 0}, v3{0, 0, 1};

    EXPECT_EQ(v1.cross(v2), v3);
}

TEST(Vector_usTest, TestIncrement)
{
    GSL::Vector_us v1{1, 0, 0}, v2{0, 1, 0}, v3{1, 1, 0};

    EXPECT_EQ(v1 += v2, v3);
}

TEST(Vector_usTest, TestDecrement)
{
    GSL::Vector_us v1{1, 2, 0}, v2{0, 1, 0}, v3{1, 1, 0};

    EXPECT_EQ(v1 -= v2, v3);
}

TEST(Vector_usTest, TestElMultScale)
{
    GSL::Vector_us v1{3, 2, 2}, v2{2, 3, 4}, v3{6, 6, 8};

    EXPECT_EQ(v1 *= v2, v3);
}

TEST(Vector_usTest, TestElDivScale)
{
    GSL::Vector_us v1{8, 4, 2}, v2{6, 3, 2}, v3{8/6, 4/3, 2/2};

    EXPECT_EQ(v1 /= v2, v3);
}

TEST(Vector_usTest, TestMultScale)
{
    GSL::Vector_us v1{3, 2, 2}, v2{9, 6, 6};

    EXPECT_EQ(v1 *= 3, v2);
}

TEST(Vector_usTest, TestDivScale)
{
    GSL::Vector_us v1{8, 4, 2}, v2{4, 2, 1};

    EXPECT_EQ(v1 /= 2, v2);
}

TEST(Vector_usTest, TestAddition)
{
    GSL::Vector_us v1{1, 0, 0}, v2{0, 1, 0}, v3{1, 1, 0};

    EXPECT_EQ(v1 + v2, v3);
}

TEST(Vector_usTest, TestSubtraction)
{
    GSL::Vector_us v1{1, 2, 0}, v2{0, 1, 0}, v3{1, 1, 0};

    EXPECT_EQ(v1 - v2, v3);
}

TEST(Vector_usTest, TestElMult)
{
    GSL::Vector_us v1{3, 2, 2}, v2{2, 3, 4}, v3{6, 6, 8};

    EXPECT_EQ(v1 * v2, v3);
}

TEST(Vector_usTest, TestElDiv)
{
    GSL::Vector_us v1{8, 4, 2}, v2{6, 3, 2}, v3{8/6, 4/3, 2/2};

    EXPECT_EQ(v1 / v2, v3);
}

TEST(Vector_usTest, TestScalarMult)
{
    GSL::Vector_us v1{3, 2, 2}, v2{9, 6, 6};

    EXPECT_EQ(v1 * 3, v2);
}

TEST(Vector_usTest, TestScalarDiv)
{
    GSL::Vector_us v1{8, 4, 2}, v2{4, 2, 1};

    EXPECT_EQ(v1 / 2, v2);
}

TEST(Vector_usTest, TestScalarMult2)
{
    GSL::Vector_us v1{3, 2, 2}, v2{9, 6, 6};

    EXPECT_EQ(3. * v1, v2);
}

TEST(Vector_usTest, TestBegin)
{
    GSL::Vector_us v{1, 2, 3};
    EXPECT_EQ(*v.begin(), 1.);
}

TEST(Vector_usTest, TestcBegin)
{
    GSL::Vector_us v{1, 2, 3};
    EXPECT_EQ(*v.cbegin(), 1.);
}

TEST(Vector_usTest, TestIterPreIncrement)
{
    GSL::Vector_us v{1, 2, 3};
    EXPECT_EQ(*++v.begin(), 2.);
}

TEST(Vector_usTest, TestIterPostIncrement)
{
    GSL::Vector_us v{1, 2, 3};
    auto it = v.begin();
    it++;
    EXPECT_EQ(*it, 2.);
}

TEST(Vector_usTest, TestIterPreDecrement)
{
    GSL::Vector_us v{1, 2, 3};
    EXPECT_EQ(*--(++v.begin()), 1.);
}

TEST(Vector_usTest, TestIterPostDecrement)
{
    GSL::Vector_us v{1, 2, 3};
    auto it = v.begin();
    it++; it--;
    EXPECT_EQ(*it, 1.);
}

TEST(Vector_usTest, TestIterStepIncrement)
{
    GSL::Vector_us v{1, 2, 3};
    auto it = v.begin();
    it += 2;
    EXPECT_EQ(*it, 3.);
}

TEST(Vector_usTest, TestIterStep)
{
    GSL::Vector_us v{1, 2, 3};
    auto it = v.begin();
    EXPECT_EQ(*(it + 2), 3.);
}

TEST(Vector_usTest, TestIterStepDecrement)
{
    GSL::Vector_us v{1, 2, 3};
    auto it = v.begin();
    it += 2;
    it -= 2;
    EXPECT_EQ(*it, 1.);
}

TEST(Vector_usTest, TestIterStepBack)
{
    GSL::Vector_us v{1, 2, 3};
    auto it = v.begin() + 2;
    EXPECT_EQ(*(it - 2), 1.);
}

TEST(Vector_usTest, TestIterDiff)
{
    GSL::Vector_us v{1, 2, 3};
    auto it = v.begin() + 2;
    EXPECT_EQ(it - v.begin(), 2.);
}

TEST(Vector_usTest, TestIterEq)
{
    GSL::Vector_us v{1, 2, 3};
    auto it1 = v.begin() + 2;
    auto it2 = v.begin();
    it2 += 2;

    EXPECT_EQ(it1, it2);
}

TEST(Vector_usTest, TestIterNeq)
{
    GSL::Vector_us v{1, 2, 3};
    auto it1 = v.begin() + 2;
    auto it2 = v.begin();

    EXPECT_NE(it1, it2);
}

TEST(Vector_usTest, TestEnd)
{
    GSL::Vector_us v{1, 2, 3};
    auto it1 = v.begin() + 2;
    auto it2 = v.end();

    EXPECT_EQ(it1, --it2);
}

TEST(Vector_usTest, TestcIterPreIncrement)
{
    GSL::Vector_us v{1, 2, 3};
    EXPECT_EQ(*++v.cbegin(), 2.);
}

TEST(Vector_usTest, TestcIterPostIncrement)
{
    GSL::Vector_us v{1, 2, 3};
    auto it = v.cbegin();
    it++;
    EXPECT_EQ(*it, 2.);
}

TEST(Vector_usTest, TestcIterPreDecrement)
{
    GSL::Vector_us v{1, 2, 3};
    EXPECT_EQ(*--(++v.cbegin()), 1.);
}

TEST(Vector_usTest, TestcIterPostDecrement)
{
    GSL::Vector_us v{1, 2, 3};
    auto it = v.cbegin();
    it++; it--;
    EXPECT_EQ(*it, 1.);
}

TEST(Vector_usTest, TestcIterStepIncrement)
{
    GSL::Vector_us v{1, 2, 3};
    auto it = v.cbegin();
    it += 2;
    EXPECT_EQ(*it, 3.);
}

TEST(Vector_usTest, TestcIterStep)
{
    GSL::Vector_us v{1, 2, 3};
    auto it = v.cbegin();
    EXPECT_EQ(*(it + 2), 3.);
}

TEST(Vector_usTest, TestcIterStepDecrement)
{
    GSL::Vector_us v{1, 2, 3};
    auto it = v.cbegin();
    it += 2;
    it -= 2;
    EXPECT_EQ(*it, 1.);
}

TEST(Vector_usTest, TestcIterStepBack)
{
    GSL::Vector_us v{1, 2, 3};
    auto it = v.cbegin() + 2;
    EXPECT_EQ(*(it - 2), 1.);
}

TEST(Vector_usTest, TestcIterDiff)
{
    GSL::Vector_us v{1, 2, 3};
    auto it = v.cbegin() + 2;
    EXPECT_EQ(it - v.cbegin(), 2.);
}

TEST(Vector_usTest, TestcIterEq)
{
    GSL::Vector_us v{1, 2, 3};
    auto it1 = v.cbegin() + 2;
    auto it2 = v.cbegin();
    it2 += 2;

    EXPECT_EQ(it1, it2);
}

TEST(Vector_usTest, TestcIterNeq)
{
    GSL::Vector_us v{1, 2, 3};
    auto it1 = v.cbegin() + 2;
    auto it2 = v.cbegin();

    EXPECT_NE(it1, it2);
}

TEST(Vector_usTest, TestcEnd)
{
    GSL::Vector_us v{1, 2, 3};
    auto it1 = v.cbegin() + 2;
    auto it2 = v.cend();

    EXPECT_EQ(it1, --it2);
}

TEST(Vector_usTest, TestRbegin)
{
    GSL::Vector_us v{1, 2, 3};
    auto it1 = v.rbegin();

    EXPECT_EQ(*it1, 3.);
}

TEST(Vector_usTest, TestRend)
{
    GSL::Vector_us v{1, 2, 3};
    auto it1 = v.rend();

    EXPECT_EQ(*--it1, 1.);
}

TEST(Vector_usTest, TestcRbegin)
{
    GSL::Vector_us v{1, 2, 3};
    auto it1 = v.crbegin();

    EXPECT_EQ(*it1, 3.);
}

TEST(Vector_usTest, TestcRend)
{
    GSL::Vector_us v{1, 2, 3};
    auto it1 = v.crend();

    EXPECT_EQ(*--it1, 1.);
}

TEST(Vector_usTest, TestFront)
{
    GSL::Vector_us v{1, 2, 3};
    EXPECT_EQ(v.front(), 1.);
}

TEST(Vector_usTest, TestBack)
{
    GSL::Vector_us v{1, 2, 3};
    EXPECT_EQ(v.back(), 3.);
}

TEST(Vector_usTest, TestAt)
{
    GSL::Vector_us v{1, 2, 3};
    EXPECT_EQ(v.at(1), 2.);
}

TEST(Vector_usTest, TestAssign1)
{
    GSL::Vector_us v1{1, 2, 3};
    GSL::Vector_us v2{3, 4, 5};
    v2.assign(v1.begin(), v1.end());
    EXPECT_EQ(v1, v2);
}

TEST(Vector_usTest, TestAssign2)
{
    GSL::Vector_us v1{1, 2, 3};
    GSL::Vector_us v2{3, 3, 3, 3};
    v1.assign(4, 3.);
    EXPECT_EQ(v1, v2);
}

TEST(Vector_usTest, TestAssign3)
{
    GSL::Vector_us v1{1, 2, 3};
    GSL::Vector_us v2{3, 4};
    v1.assign({3, 4});
    EXPECT_EQ(v1, v2);
}
