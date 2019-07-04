#include "GSLpp/vector.h"
#include <gtest/gtest.h>
#include <iostream>

TEST(Vector_sTest, TestConstruction)
{
    GSL::Vector_s v(3);
    EXPECT_EQ(v[0], 0.);
    EXPECT_EQ(v[1], 0.);
    EXPECT_EQ(v[2], 0.);
}

TEST(Vector_sTest, TestConstructionInitializerList)
{
    short a = 1, b = 2, c = 3.;
    GSL::Vector_s v{a, b, c};
    EXPECT_EQ(v[0], 1.);
    EXPECT_EQ(v[1], 2.);
    EXPECT_EQ(v[2], 3.);
}

TEST(Vector_sTest, TestConstructionCopy)
{
    short a = 1, b = 2, c = 3.;
    GSL::Vector_s v1{a, b, c};
    GSL::Vector_s v2{v1};
    EXPECT_EQ(v1[0], v2[0]);
    EXPECT_EQ(v1[1], v2[1]);
    EXPECT_EQ(v1[2], v2[2]);
}

TEST(Vector_sTest, TestConstructionMove)
{
    short a = 1, b = 2, c = 3.;
    GSL::Vector_s v1{a, b, c};
    GSL::Vector_s v2{std::move(v1)};
    EXPECT_EQ(v2[0], 1.);
    EXPECT_EQ(v2[1], 2.);
    EXPECT_EQ(v2[2], 3.);
}

TEST(Vector_sTest, TestEqual)
{

    short a = 1, b = 2, c = 3.;
    GSL::Vector_s v1{a, b, c};
    GSL::Vector_s v2{v1};

    EXPECT_EQ(v1, v2);
}

TEST(Vector_sTest, TestNotEqual)
{

    short a = 1, b = 2, c = 3.;
    GSL::Vector_s v1{a, b, c};
    GSL::Vector_s v2{static_cast<short>(a +1), b, c};

    EXPECT_NE(v1, v2);
}

TEST(Vector_sTest, TestCopy)
{

    short a = 1, b = 2, c = 3.;
    GSL::Vector_s v1{a, b, c};
    GSL::Vector_s v2;
    v2 = v1;

    EXPECT_EQ(v1, v2);
}

TEST(Vector_sTest, TestMove)
{

    short a = 1, b = 2, c = 3.;
    GSL::Vector_s v1{a, b, c}, v1s{a, b, c};
    GSL::Vector_s v2;
    v2 = std::move(v1);

    EXPECT_EQ(v2, v1s);
}

TEST(Vector_sTest, TestDecayToGSLVector_s)
{
    short a = 1, b = 2, c = 3.;
    GSL::Vector_s v{a, b, c};
    gsl_vector_short gv = v;

    EXPECT_EQ(gsl_vector_short_get(&gv, 0), a);
}

TEST(Vector_sTest, TestSize)
{
    short a = 1, b = 2, c = 3.;
    GSL::Vector_s v{a, b, c};

    EXPECT_EQ(v.size(), 3);
}

TEST(Vector_sTest, TestDim)
{
    short a = 1, b = 2, c = 3.;
    GSL::Vector_s v{a, b, c};

    EXPECT_EQ(v.dim(), 3);
}

TEST(Vector_sTest, TestCopyFun)
{
    short a = 1, b = 2, c = 3.;
    GSL::Vector_s v{a, b, c}, v2;
    v2.copy(v);

    EXPECT_EQ(v, v2);
}

TEST(Vector_sTest, TestNorm)
{
    short a = 1, b = 2, c = 3.;
    GSL::Vector_s v{a, b, c};

    EXPECT_EQ(v.norm<double>(), std::sqrt(a*a + b*b + c*c));
}

TEST(Vector_sTest, TestNormalize)
{
    short a = 1, b = 2, c = 3.;
    GSL::Vector_s v{a, b, c};
    v.normalize<short>();

    EXPECT_EQ(v.norm<double>(), 1.);
}

TEST(Vector_sTest, TestDot)
{
    GSL::Vector_s v1{1, 0, 0}, v2{0, 1, 0};

    EXPECT_EQ(v1.dot(v2), 0.);
}

TEST(Vector_sTest, TestCross)
{
    GSL::Vector_s v1{1, 0, 0}, v2{0, 1, 0}, v3{0, 0, 1};

    EXPECT_EQ(v1.cross(v2), v3);
}

TEST(Vector_sTest, TestIncrement)
{
    GSL::Vector_s v1{1, 0, 0}, v2{0, 1, 0}, v3{1, 1, 0};

    EXPECT_EQ(v1 += v2, v3);
}

TEST(Vector_sTest, TestDecrement)
{
    GSL::Vector_s v1{1, 0, 0}, v2{0, 1, 0}, v3{1, -1, 0};

    EXPECT_EQ(v1 -= v2, v3);
}

TEST(Vector_sTest, TestElMultScale)
{
    GSL::Vector_s v1{3, 2, 2}, v2{2, 3, 4}, v3{6, 6, 8};

    EXPECT_EQ(v1 *= v2, v3);
}

TEST(Vector_sTest, TestElDivScale)
{
    GSL::Vector_s v1{8, 4, 2}, v2{6, 3, 2}, v3{8/6, 4/3, 2/2};

    EXPECT_EQ(v1 /= v2, v3);
}

TEST(Vector_sTest, TestMultScale)
{
    GSL::Vector_s v1{3, 2, 2}, v2{9, 6, 6};

    EXPECT_EQ(v1 *= 3, v2);
}

TEST(Vector_sTest, TestDivScale)
{
    GSL::Vector_s v1{8, 4, 2}, v2{4, 2, 1};

    EXPECT_EQ(v1 /= 2, v2);
}

TEST(Vector_sTest, TestAddition)
{
    GSL::Vector_s v1{1, 0, 0}, v2{0, 1, 0}, v3{1, 1, 0};

    EXPECT_EQ(v1 + v2, v3);
}

TEST(Vector_sTest, TestSubtraction)
{
    GSL::Vector_s v1{1, 0, 0}, v2{0, 1, 0}, v3{1, -1, 0};

    EXPECT_EQ(v1 - v2, v3);
}

TEST(Vector_sTest, TestElMult)
{
    GSL::Vector_s v1{3, 2, 2}, v2{2, 3, 4}, v3{6, 6, 8};

    EXPECT_EQ(v1 * v2, v3);
}

TEST(Vector_sTest, TestElDiv)
{
    GSL::Vector_s v1{8, 4, 2}, v2{6, 3, 2}, v3{8/6, 4/3, 2/2};

    EXPECT_EQ(v1 / v2, v3);
}

TEST(Vector_sTest, TestScalarMult)
{
    GSL::Vector_s v1{3, 2, 2}, v2{9, 6, 6};

    EXPECT_EQ(v1 * 3, v2);
}

TEST(Vector_sTest, TestScalarDiv)
{
    GSL::Vector_s v1{8, 4, 2}, v2{4, 2, 1};

    EXPECT_EQ(v1 / 2, v2);
}

TEST(Vector_sTest, TestScalarMult2)
{
    GSL::Vector_s v1{3, 2, 2}, v2{9, 6, 6};

    EXPECT_EQ(3. * v1, v2);
}

TEST(Vector_sTest, TestBegin)
{
    GSL::Vector_s v{1, 2, 3};
    EXPECT_EQ(*v.begin(), 1.);
}

TEST(Vector_sTest, TestcBegin)
{
    GSL::Vector_s v{1, 2, 3};
    EXPECT_EQ(*v.cbegin(), 1.);
}

TEST(Vector_sTest, TestIterPreIncrement)
{
    GSL::Vector_s v{1, 2, 3};
    EXPECT_EQ(*++v.begin(), 2.);
}

TEST(Vector_sTest, TestIterPostIncrement)
{
    GSL::Vector_s v{1, 2, 3};
    auto it = v.begin();
    it++;
    EXPECT_EQ(*it, 2.);
}

TEST(Vector_sTest, TestIterPreDecrement)
{
    GSL::Vector_s v{1, 2, 3};
    EXPECT_EQ(*--(++v.begin()), 1.);
}

TEST(Vector_sTest, TestIterPostDecrement)
{
    GSL::Vector_s v{1, 2, 3};
    auto it = v.begin();
    it++; it--;
    EXPECT_EQ(*it, 1.);
}

TEST(Vector_sTest, TestIterStepIncrement)
{
    GSL::Vector_s v{1, 2, 3};
    auto it = v.begin();
    it += 2;
    EXPECT_EQ(*it, 3.);
}

TEST(Vector_sTest, TestIterStep)
{
    GSL::Vector_s v{1, 2, 3};
    auto it = v.begin();
    EXPECT_EQ(*(it + 2), 3.);
}

TEST(Vector_sTest, TestIterStepForward)
{
    GSL::Vector_s v{1, 2, 3};
    auto it = v.begin();
    EXPECT_EQ(*(2 + it), 3.);
}

TEST(Vector_sTest, TestIterStepDecrement)
{
    GSL::Vector_s v{1, 2, 3};
    auto it = v.begin();
    it += 2;
    it -= 2;
    EXPECT_EQ(*it, 1.);
}

TEST(Vector_sTest, TestIterStepBack)
{
    GSL::Vector_s v{1, 2, 3};
    auto it = v.begin() + 2;
    EXPECT_EQ(*(it - 2), 1.);
}

TEST(Vector_sTest, TestIterDiff)
{
    GSL::Vector_s v{1, 2, 3};
    auto it = v.begin() + 2;
    EXPECT_EQ(it - v.begin(), 2.);
}

TEST(Vector_sTest, TestIterEq)
{
    GSL::Vector_s v{1, 2, 3};
    auto it1 = v.begin() + 2;
    auto it2 = v.begin();
    it2 += 2;

    EXPECT_EQ(it1, it2);
}

TEST(Vector_sTest, TestIterNeq)
{
    GSL::Vector_s v{1, 2, 3};
    auto it1 = v.begin() + 2;
    auto it2 = v.begin();

    EXPECT_NE(it1, it2);
}

TEST(Vector_sTest, TestEnd)
{
    GSL::Vector_s v{1, 2, 3};
    auto it1 = v.begin() + 2;
    auto it2 = v.end();

    EXPECT_EQ(it1, --it2);
}

TEST(Vector_sTest, TestcIterPreIncrement)
{
    GSL::Vector_s v{1, 2, 3};
    EXPECT_EQ(*++v.cbegin(), 2.);
}

TEST(Vector_sTest, TestcIterPostIncrement)
{
    GSL::Vector_s v{1, 2, 3};
    auto it = v.cbegin();
    it++;
    EXPECT_EQ(*it, 2.);
}

TEST(Vector_sTest, TestcIterPreDecrement)
{
    GSL::Vector_s v{1, 2, 3};
    EXPECT_EQ(*--(++v.cbegin()), 1.);
}

TEST(Vector_sTest, TestcIterPostDecrement)
{
    GSL::Vector_s v{1, 2, 3};
    auto it = v.cbegin();
    it++; it--;
    EXPECT_EQ(*it, 1.);
}

TEST(Vector_sTest, TestcIterStepIncrement)
{
    GSL::Vector_s v{1, 2, 3};
    auto it = v.cbegin();
    it += 2;
    EXPECT_EQ(*it, 3.);
}

TEST(Vector_sTest, TestcIterStep)
{
    GSL::Vector_s v{1, 2, 3};
    auto it = v.cbegin();
    EXPECT_EQ(*(it + 2), 3.);
}

TEST(Vector_sTest, TestcIterStepForward)
{
    GSL::Vector_s v{1, 2, 3};
    auto it = v.cbegin();
    EXPECT_EQ(*(2 + it), 3.);
}

TEST(Vector_sTest, TestcIterStepDecrement)
{
    GSL::Vector_s v{1, 2, 3};
    auto it = v.cbegin();
    it += 2;
    it -= 2;
    EXPECT_EQ(*it, 1.);
}

TEST(Vector_sTest, TestcIterStepBack)
{
    GSL::Vector_s v{1, 2, 3};
    auto it = v.cbegin() + 2;
    EXPECT_EQ(*(it - 2), 1.);
}

TEST(Vector_sTest, TestcIterDiff)
{
    GSL::Vector_s v{1, 2, 3};
    auto it = v.cbegin() + 2;
    EXPECT_EQ(it - v.cbegin(), 2.);
}

TEST(Vector_sTest, TestcIterEq)
{
    GSL::Vector_s v{1, 2, 3};
    auto it1 = v.cbegin() + 2;
    auto it2 = v.cbegin();
    it2 += 2;

    EXPECT_EQ(it1, it2);
}

TEST(Vector_sTest, TestcIterNeq)
{
    GSL::Vector_s v{1, 2, 3};
    auto it1 = v.cbegin() + 2;
    auto it2 = v.cbegin();

    EXPECT_NE(it1, it2);
}

TEST(Vector_sTest, TestcEnd)
{
    GSL::Vector_s v{1, 2, 3};
    auto it1 = v.cbegin() + 2;
    auto it2 = v.cend();

    EXPECT_EQ(it1, --it2);
}

TEST(Vector_sTest, TestRbegin)
{
    GSL::Vector_s v{1, 2, 3};
    auto it1 = v.rbegin();

    EXPECT_EQ(*it1, 3.);
}

TEST(Vector_sTest, TestRend)
{
    GSL::Vector_s v{1, 2, 3};
    auto it1 = v.rend();

    EXPECT_EQ(*--it1, 1.);
}

TEST(Vector_sTest, TestcRbegin)
{
    GSL::Vector_s v{1, 2, 3};
    auto it1 = v.crbegin();

    EXPECT_EQ(*it1, 3.);
}

TEST(Vector_sTest, TestcRend)
{
    GSL::Vector_s v{1, 2, 3};
    auto it1 = v.crend();

    EXPECT_EQ(*--it1, 1.);
}

TEST(Vector_sTest, TestFront)
{
    GSL::Vector_s v{1, 2, 3};
    EXPECT_EQ(v.front(), 1.);
}

TEST(Vector_sTest, TestBack)
{
    GSL::Vector_s v{1, 2, 3};
    EXPECT_EQ(v.back(), 3.);
}

TEST(Vector_sTest, TestAt)
{
    GSL::Vector_s v{1, 2, 3};
    EXPECT_EQ(v.at(1), 2.);
}

TEST(Vector_sTest, TestAssign1)
{
    GSL::Vector_s v1{1, 2, 3};
    GSL::Vector_s v2{3, 4, 5};
    v2.assign(v1.begin(), v1.end());
    EXPECT_EQ(v1, v2);
}

TEST(Vector_sTest, TestAssign2)
{
    GSL::Vector_s v1{1, 2, 3};
    GSL::Vector_s v2{3, 3, 3, 3};
    v1.assign(4, 3.);
    EXPECT_EQ(v1, v2);
}

TEST(Vector_sTest, TestAssign3)
{
    GSL::Vector_s v1{1, 2, 3};
    GSL::Vector_s v2{3, 4};
    v1.assign({3, 4});
    EXPECT_EQ(v1, v2);
}
