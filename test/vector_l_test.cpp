#include "GSLpp/vector.h"
#include <gtest/gtest.h>
#include <iostream>

TEST(Vector_lTest, TestConstruction)
{
    GSL::Vector_l v(3);
    EXPECT_EQ(v[0], 0.);
    EXPECT_EQ(v[1], 0.);
    EXPECT_EQ(v[2], 0.);
}

TEST(Vector_lTest, TestConstructionInitializerList)
{
    long a = 1, b = 2, c = 3.;
    GSL::Vector_l v{a, b, c};
    EXPECT_EQ(v[0], 1.);
    EXPECT_EQ(v[1], 2.);
    EXPECT_EQ(v[2], 3.);
}

TEST(Vector_lTest, TestConstructionCopy)
{
    long a = 1, b = 2, c = 3.;
    GSL::Vector_l v1{a, b, c};
    GSL::Vector_l v2{v1};
    EXPECT_EQ(v1[0], v2[0]);
    EXPECT_EQ(v1[1], v2[1]);
    EXPECT_EQ(v1[2], v2[2]);
}

TEST(Vector_lTest, TestConstructionMove)
{
    long a = 1, b = 2, c = 3.;
    GSL::Vector_l v1{a, b, c};
    GSL::Vector_l v2{std::move(v1)};
    EXPECT_EQ(v2[0], 1.);
    EXPECT_EQ(v2[1], 2.);
    EXPECT_EQ(v2[2], 3.);
}

TEST(Vector_lTest, TestEqual)
{

    long a = 1, b = 2, c = 3.;
    GSL::Vector_l v1{a, b, c};
    GSL::Vector_l v2{v1};

    EXPECT_EQ(v1, v2);
}

TEST(Vector_lTest, TestNotEqual)
{

    long a = 1, b = 2, c = 3.;
    GSL::Vector_l v1{a, b, c};
    GSL::Vector_l v2{a +1, b, c};

    EXPECT_NE(v1, v2);
}

TEST(Vector_lTest, TestCopy)
{

    long a = 1, b = 2, c = 3.;
    GSL::Vector_l v1{a, b, c};
    GSL::Vector_l v2;
    v2 = v1;

    EXPECT_EQ(v1, v2);
}

TEST(Vector_lTest, TestMove)
{

    long a = 1, b = 2, c = 3.;
    GSL::Vector_l v1{a, b, c}, v1s{a, b, c};
    GSL::Vector_l v2;
    v2 = std::move(v1);

    EXPECT_EQ(v2, v1s);
}

TEST(Vector_lTest, TestDecayToGSLVector_l)
{
    long a = 1, b = 2, c = 3.;
    GSL::Vector_l v{a, b, c};
    gsl_vector_long gv = v;

    EXPECT_EQ(gsl_vector_long_get(&gv, 0), a);
}

TEST(Vector_lTest, TestSize)
{
    long a = 1, b = 2, c = 3.;
    GSL::Vector_l v{a, b, c};

    EXPECT_EQ(v.size(), 3);
}

TEST(Vector_lTest, TestDim)
{
    long a = 1, b = 2, c = 3.;
    GSL::Vector_l v{a, b, c};

    EXPECT_EQ(v.dim(), 3);
}

TEST(Vector_lTest, TestCopyFun)
{
    long a = 1, b = 2, c = 3.;
    GSL::Vector_l v{a, b, c}, v2;
    v2.copy(v);

    EXPECT_EQ(v, v2);
}

TEST(Vector_lTest, TestNorm)
{
    long a = 1, b = 2, c = 3.;
    GSL::Vector_l v{a, b, c};

    EXPECT_EQ(v.norm<double>(), std::sqrt(a*a + b*b + c*c));
}

TEST(Vector_lTest, TestNormalize)
{
    long a = 1, b = 2, c = 3.;
    GSL::Vector_l v{a, b, c};
    v.normalize<int>();

    EXPECT_EQ(v.norm<double>(), 1.);
}

TEST(Vector_lTest, TestDot)
{
    GSL::Vector_l v1{1, 0, 0}, v2{0, 1, 0};

    EXPECT_EQ(v1.dot(v2), 0.);
}

TEST(Vector_lTest, TestCross)
{
    GSL::Vector_l v1{1, 0, 0}, v2{0, 1, 0}, v3{0, 0, 1};

    EXPECT_EQ(v1.cross(v2), v3);
}

TEST(Vector_lTest, TestIncrement)
{
    GSL::Vector_l v1{1, 0, 0}, v2{0, 1, 0}, v3{1, 1, 0};

    EXPECT_EQ(v1 += v2, v3);
}

TEST(Vector_lTest, TestDecrement)
{
    GSL::Vector_l v1{1, 0, 0}, v2{0, 1, 0}, v3{1, -1, 0};

    EXPECT_EQ(v1 -= v2, v3);
}

TEST(Vector_lTest, TestElMultScale)
{
    GSL::Vector_l v1{3, 2, 2}, v2{2, 3, 4}, v3{6, 6, 8};

    EXPECT_EQ(v1 *= v2, v3);
}

TEST(Vector_lTest, TestElDivScale)
{
    GSL::Vector_l v1{8, 4, 2}, v2{6, 3, 2}, v3{8/6, 4/3, 2/2};

    EXPECT_EQ(v1 /= v2, v3);
}

TEST(Vector_lTest, TestMultScale)
{
    GSL::Vector_l v1{3, 2, 2}, v2{9, 6, 6};

    EXPECT_EQ(v1 *= 3, v2);
}

TEST(Vector_lTest, TestDivScale)
{
    GSL::Vector_l v1{8, 4, 2}, v2{4, 2, 1};

    EXPECT_EQ(v1 /= 2, v2);
}

TEST(Vector_lTest, TestAddition)
{
    GSL::Vector_l v1{1, 0, 0}, v2{0, 1, 0}, v3{1, 1, 0};

    EXPECT_EQ(v1 + v2, v3);
}

TEST(Vector_lTest, TestSubtraction)
{
    GSL::Vector_l v1{1, 0, 0}, v2{0, 1, 0}, v3{1, -1, 0};

    EXPECT_EQ(v1 - v2, v3);
}

TEST(Vector_lTest, TestElMult)
{
    GSL::Vector_l v1{3, 2, 2}, v2{2, 3, 4}, v3{6, 6, 8};

    EXPECT_EQ(v1 * v2, v3);
}

TEST(Vector_lTest, TestElDiv)
{
    GSL::Vector_l v1{8, 4, 2}, v2{6, 3, 2}, v3{8/6, 4/3, 2/2};

    EXPECT_EQ(v1 / v2, v3);
}

TEST(Vector_lTest, TestScalarMult)
{
    GSL::Vector_l v1{3, 2, 2}, v2{9, 6, 6};

    EXPECT_EQ(v1 * 3, v2);
}

TEST(Vector_lTest, TestScalarDiv)
{
    GSL::Vector_l v1{8, 4, 2}, v2{4, 2, 1};

    EXPECT_EQ(v1 / 2, v2);
}

TEST(Vector_lTest, TestScalarMult2)
{
    GSL::Vector_l v1{3, 2, 2}, v2{9, 6, 6};

    EXPECT_EQ(3. * v1, v2);
}

TEST(Vector_lTest, TestBegin)
{
    GSL::Vector_l v{1, 2, 3};
    EXPECT_EQ(*v.begin(), 1.);
}

TEST(Vector_lTest, TestcBegin)
{
    GSL::Vector_l v{1, 2, 3};
    EXPECT_EQ(*v.cbegin(), 1.);
}

TEST(Vector_lTest, TestIterPreIncrement)
{
    GSL::Vector_l v{1, 2, 3};
    EXPECT_EQ(*++v.begin(), 2.);
}

TEST(Vector_lTest, TestIterPostIncrement)
{
    GSL::Vector_l v{1, 2, 3};
    auto it = v.begin();
    it++;
    EXPECT_EQ(*it, 2.);
}

TEST(Vector_lTest, TestIterPreDecrement)
{
    GSL::Vector_l v{1, 2, 3};
    EXPECT_EQ(*--(++v.begin()), 1.);
}

TEST(Vector_lTest, TestIterPostDecrement)
{
    GSL::Vector_l v{1, 2, 3};
    auto it = v.begin();
    it++; it--;
    EXPECT_EQ(*it, 1.);
}

TEST(Vector_lTest, TestIterStepIncrement)
{
    GSL::Vector_l v{1, 2, 3};
    auto it = v.begin();
    it += 2;
    EXPECT_EQ(*it, 3.);
}

TEST(Vector_lTest, TestIterStep)
{
    GSL::Vector_l v{1, 2, 3};
    auto it = v.begin();
    EXPECT_EQ(*(it + 2), 3.);
}

TEST(Vector_lTest, TestIterStepForward)
{
    GSL::Vector_l v{1, 2, 3};
    auto it = v.begin();
    EXPECT_EQ(*(2 + it), 3.);
}

TEST(Vector_lTest, TestIterStepDecrement)
{
    GSL::Vector_l v{1, 2, 3};
    auto it = v.begin();
    it += 2;
    it -= 2;
    EXPECT_EQ(*it, 1.);
}

TEST(Vector_lTest, TestIterStepBack)
{
    GSL::Vector_l v{1, 2, 3};
    auto it = v.begin() + 2;
    EXPECT_EQ(*(it - 2), 1.);
}

TEST(Vector_lTest, TestIterDiff)
{
    GSL::Vector_l v{1, 2, 3};
    auto it = v.begin() + 2;
    EXPECT_EQ(it - v.begin(), 2.);
}

TEST(Vector_lTest, TestIterEq)
{
    GSL::Vector_l v{1, 2, 3};
    auto it1 = v.begin() + 2;
    auto it2 = v.begin();
    it2 += 2;

    EXPECT_EQ(it1, it2);
}

TEST(Vector_lTest, TestIterNeq)
{
    GSL::Vector_l v{1, 2, 3};
    auto it1 = v.begin() + 2;
    auto it2 = v.begin();

    EXPECT_NE(it1, it2);
}

TEST(Vector_lTest, TestEnd)
{
    GSL::Vector_l v{1, 2, 3};
    auto it1 = v.begin() + 2;
    auto it2 = v.end();

    EXPECT_EQ(it1, --it2);
}

TEST(Vector_lTest, TestcIterPreIncrement)
{
    GSL::Vector_l v{1, 2, 3};
    EXPECT_EQ(*++v.cbegin(), 2.);
}

TEST(Vector_lTest, TestcIterPostIncrement)
{
    GSL::Vector_l v{1, 2, 3};
    auto it = v.cbegin();
    it++;
    EXPECT_EQ(*it, 2.);
}

TEST(Vector_lTest, TestcIterPreDecrement)
{
    GSL::Vector_l v{1, 2, 3};
    EXPECT_EQ(*--(++v.cbegin()), 1.);
}

TEST(Vector_lTest, TestcIterPostDecrement)
{
    GSL::Vector_l v{1, 2, 3};
    auto it = v.cbegin();
    it++; it--;
    EXPECT_EQ(*it, 1.);
}

TEST(Vector_lTest, TestcIterStepIncrement)
{
    GSL::Vector_l v{1, 2, 3};
    auto it = v.cbegin();
    it += 2;
    EXPECT_EQ(*it, 3.);
}

TEST(Vector_lTest, TestcIterStep)
{
    GSL::Vector_l v{1, 2, 3};
    auto it = v.cbegin();
    EXPECT_EQ(*(it + 2), 3.);
}

TEST(Vector_lTest, TestcIterStepForward)
{
    GSL::Vector_l v{1, 2, 3};
    auto it = v.cbegin();
    EXPECT_EQ(*(2 + it), 3.);
}

TEST(Vector_lTest, TestcIterStepDecrement)
{
    GSL::Vector_l v{1, 2, 3};
    auto it = v.cbegin();
    it += 2;
    it -= 2;
    EXPECT_EQ(*it, 1.);
}

TEST(Vector_lTest, TestcIterStepBack)
{
    GSL::Vector_l v{1, 2, 3};
    auto it = v.cbegin() + 2;
    EXPECT_EQ(*(it - 2), 1.);
}

TEST(Vector_lTest, TestcIterDiff)
{
    GSL::Vector_l v{1, 2, 3};
    auto it = v.cbegin() + 2;
    EXPECT_EQ(it - v.cbegin(), 2.);
}

TEST(Vector_lTest, TestcIterEq)
{
    GSL::Vector_l v{1, 2, 3};
    auto it1 = v.cbegin() + 2;
    auto it2 = v.cbegin();
    it2 += 2;

    EXPECT_EQ(it1, it2);
}

TEST(Vector_lTest, TestcIterNeq)
{
    GSL::Vector_l v{1, 2, 3};
    auto it1 = v.cbegin() + 2;
    auto it2 = v.cbegin();

    EXPECT_NE(it1, it2);
}

TEST(Vector_lTest, TestcEnd)
{
    GSL::Vector_l v{1, 2, 3};
    auto it1 = v.cbegin() + 2;
    auto it2 = v.cend();

    EXPECT_EQ(it1, --it2);
}

TEST(Vector_lTest, TestRbegin)
{
    GSL::Vector_l v{1, 2, 3};
    auto it1 = v.rbegin();

    EXPECT_EQ(*it1, 3.);
}

TEST(Vector_lTest, TestRend)
{
    GSL::Vector_l v{1, 2, 3};
    auto it1 = v.rend();

    EXPECT_EQ(*--it1, 1.);
}

TEST(Vector_lTest, TestcRbegin)
{
    GSL::Vector_l v{1, 2, 3};
    auto it1 = v.crbegin();

    EXPECT_EQ(*it1, 3.);
}

TEST(Vector_lTest, TestcRend)
{
    GSL::Vector_l v{1, 2, 3};
    auto it1 = v.crend();

    EXPECT_EQ(*--it1, 1.);
}

TEST(Vector_lTest, TestFront)
{
    GSL::Vector_l v{1, 2, 3};
    EXPECT_EQ(v.front(), 1.);
}

TEST(Vector_lTest, TestBack)
{
    GSL::Vector_l v{1, 2, 3};
    EXPECT_EQ(v.back(), 3.);
}

TEST(Vector_lTest, TestAt)
{
    GSL::Vector_l v{1, 2, 3};
    EXPECT_EQ(v.at(1), 2.);
}

TEST(Vector_lTest, TestAssign1)
{
    GSL::Vector_l v1{1, 2, 3};
    GSL::Vector_l v2{3, 4, 5};
    v2.assign(v1.begin(), v1.end());
    EXPECT_EQ(v1, v2);
}

TEST(Vector_lTest, TestAssign2)
{
    GSL::Vector_l v1{1, 2, 3};
    GSL::Vector_l v2{3, 3, 3, 3};
    v1.assign(4, 3.);
    EXPECT_EQ(v1, v2);
}

TEST(Vector_lTest, TestAssign3)
{
    GSL::Vector_l v1{1, 2, 3};
    GSL::Vector_l v2{3, 4};
    v1.assign({3, 4});
    EXPECT_EQ(v1, v2);
}
