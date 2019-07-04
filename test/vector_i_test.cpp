#include "GSLpp/vector.h"
#include <gtest/gtest.h>
#include <iostream>

TEST(Vector_iTest, TestConstruction)
{
    GSL::Vector_i v(3);
    EXPECT_EQ(v[0], 0.);
    EXPECT_EQ(v[1], 0.);
    EXPECT_EQ(v[2], 0.);
}

TEST(Vector_iTest, TestConstructionInitializerList)
{
    int a = 1, b = 2, c = 3.;
    GSL::Vector_i v{a, b, c};
    EXPECT_EQ(v[0], 1.);
    EXPECT_EQ(v[1], 2.);
    EXPECT_EQ(v[2], 3.);
}

TEST(Vector_iTest, TestConstructionCopy)
{
    int a = 1, b = 2, c = 3.;
    GSL::Vector_i v1{a, b, c};
    GSL::Vector_i v2{v1};
    EXPECT_EQ(v1[0], v2[0]);
    EXPECT_EQ(v1[1], v2[1]);
    EXPECT_EQ(v1[2], v2[2]);
}

TEST(Vector_iTest, TestConstructionMove)
{
    int a = 1, b = 2, c = 3.;
    GSL::Vector_i v1{a, b, c};
    GSL::Vector_i v2{std::move(v1)};
    EXPECT_EQ(v2[0], 1.);
    EXPECT_EQ(v2[1], 2.);
    EXPECT_EQ(v2[2], 3.);
}

TEST(Vector_iTest, TestEqual)
{

    int a = 1, b = 2, c = 3.;
    GSL::Vector_i v1{a, b, c};
    GSL::Vector_i v2{v1};

    EXPECT_EQ(v1, v2);
}

TEST(Vector_iTest, TestNotEqual)
{

    int a = 1, b = 2, c = 3.;
    GSL::Vector_i v1{a, b, c};
    GSL::Vector_i v2{a +1, b, c};

    EXPECT_NE(v1, v2);
}

TEST(Vector_iTest, TestCopy)
{

    int a = 1, b = 2, c = 3.;
    GSL::Vector_i v1{a, b, c};
    GSL::Vector_i v2;
    v2 = v1;

    EXPECT_EQ(v1, v2);
}

TEST(Vector_iTest, TestMove)
{

    int a = 1, b = 2, c = 3.;
    GSL::Vector_i v1{a, b, c}, v1s{a, b, c};
    GSL::Vector_i v2;
    v2 = std::move(v1);

    EXPECT_EQ(v2, v1s);
}

TEST(Vector_iTest, TestDecayToGSLVector_i)
{
    int a = 1, b = 2, c = 3.;
    GSL::Vector_i v{a, b, c};
    gsl_vector_int gv = v;

    EXPECT_EQ(gsl_vector_int_get(&gv, 0), a);
}

TEST(Vector_iTest, TestSize)
{
    int a = 1, b = 2, c = 3.;
    GSL::Vector_i v{a, b, c};

    EXPECT_EQ(v.size(), 3);
}

TEST(Vector_iTest, TestDim)
{
    int a = 1, b = 2, c = 3.;
    GSL::Vector_i v{a, b, c};

    EXPECT_EQ(v.dim(), 3);
}

TEST(Vector_iTest, TestCopyFun)
{
    int a = 1, b = 2, c = 3.;
    GSL::Vector_i v{a, b, c}, v2;
    v2.copy(v);

    EXPECT_EQ(v, v2);
}

TEST(Vector_iTest, TestNorm)
{
    int a = 1, b = 2, c = 3.;
    GSL::Vector_i v{a, b, c};

    EXPECT_EQ(v.norm<double>(), std::sqrt(a*a + b*b + c*c));
}

TEST(Vector_iTest, TestNormalize)
{
    int a = 1, b = 2, c = 3.;
    GSL::Vector_i v{a, b, c};
    v.normalize<int>();

    EXPECT_EQ(v.norm<double>(), 1.);
}

TEST(Vector_iTest, TestDot)
{
    GSL::Vector_i v1{1, 0, 0}, v2{0, 1, 0};

    EXPECT_EQ(v1.dot(v2), 0.);
}

TEST(Vector_iTest, TestCross)
{
    GSL::Vector_i v1{1, 0, 0}, v2{0, 1, 0}, v3{0, 0, 1};

    EXPECT_EQ(v1.cross(v2), v3);
}

TEST(Vector_iTest, TestIncrement)
{
    GSL::Vector_i v1{1, 0, 0}, v2{0, 1, 0}, v3{1, 1, 0};

    EXPECT_EQ(v1 += v2, v3);
}

TEST(Vector_iTest, TestDecrement)
{
    GSL::Vector_i v1{1, 0, 0}, v2{0, 1, 0}, v3{1, -1, 0};

    EXPECT_EQ(v1 -= v2, v3);
}

TEST(Vector_iTest, TestElMultScale)
{
    GSL::Vector_i v1{3, 2, 2}, v2{2, 3, 4}, v3{6, 6, 8};

    EXPECT_EQ(v1 *= v2, v3);
}

TEST(Vector_iTest, TestElDivScale)
{
    GSL::Vector_i v1{8, 4, 2}, v2{6, 3, 2}, v3{8/6, 4/3, 2/2};

    EXPECT_EQ(v1 /= v2, v3);
}

TEST(Vector_iTest, TestMultScale)
{
    GSL::Vector_i v1{3, 2, 2}, v2{9, 6, 6};

    EXPECT_EQ(v1 *= 3, v2);
}

TEST(Vector_iTest, TestDivScale)
{
    GSL::Vector_i v1{8, 4, 2}, v2{4, 2, 1};

    EXPECT_EQ(v1 /= 2, v2);
}

TEST(Vector_iTest, TestAddition)
{
    GSL::Vector_i v1{1, 0, 0}, v2{0, 1, 0}, v3{1, 1, 0};

    EXPECT_EQ(v1 + v2, v3);
}

TEST(Vector_iTest, TestSubtraction)
{
    GSL::Vector_i v1{1, 0, 0}, v2{0, 1, 0}, v3{1, -1, 0};

    EXPECT_EQ(v1 - v2, v3);
}

TEST(Vector_iTest, TestElMult)
{
    GSL::Vector_i v1{3, 2, 2}, v2{2, 3, 4}, v3{6, 6, 8};

    EXPECT_EQ(v1 * v2, v3);
}

TEST(Vector_iTest, TestElDiv)
{
    GSL::Vector_i v1{8, 4, 2}, v2{6, 3, 2}, v3{8/6, 4/3, 2/2};

    EXPECT_EQ(v1 / v2, v3);
}

TEST(Vector_iTest, TestScalarMult)
{
    GSL::Vector_i v1{3, 2, 2}, v2{9, 6, 6};

    EXPECT_EQ(v1 * 3, v2);
}

TEST(Vector_iTest, TestScalarDiv)
{
    GSL::Vector_i v1{8, 4, 2}, v2{4, 2, 1};

    EXPECT_EQ(v1 / 2, v2);
}

TEST(Vector_iTest, TestScalarMult2)
{
    GSL::Vector_i v1{3, 2, 2}, v2{9, 6, 6};

    EXPECT_EQ(3. * v1, v2);
}

TEST(Vector_iTest, TestBegin)
{
    GSL::Vector_i v{1, 2, 3};
    EXPECT_EQ(*v.begin(), 1.);
}

TEST(Vector_iTest, TestcBegin)
{
    GSL::Vector_i v{1, 2, 3};
    EXPECT_EQ(*v.cbegin(), 1.);
}

TEST(Vector_iTest, TestIterPreIncrement)
{
    GSL::Vector_i v{1, 2, 3};
    EXPECT_EQ(*++v.begin(), 2.);
}

TEST(Vector_iTest, TestIterPostIncrement)
{
    GSL::Vector_i v{1, 2, 3};
    auto it = v.begin();
    it++;
    EXPECT_EQ(*it, 2.);
}

TEST(Vector_iTest, TestIterPreDecrement)
{
    GSL::Vector_i v{1, 2, 3};
    EXPECT_EQ(*--(++v.begin()), 1.);
}

TEST(Vector_iTest, TestIterPostDecrement)
{
    GSL::Vector_i v{1, 2, 3};
    auto it = v.begin();
    it++; it--;
    EXPECT_EQ(*it, 1.);
}

TEST(Vector_iTest, TestIterStepIncrement)
{
    GSL::Vector_i v{1, 2, 3};
    auto it = v.begin();
    it += 2;
    EXPECT_EQ(*it, 3.);
}

TEST(Vector_iTest, TestIterStep)
{
    GSL::Vector_i v{1, 2, 3};
    auto it = v.begin();
    EXPECT_EQ(*(it + 2), 3.);
}

TEST(Vector_iTest, TestIterStepForward)
{
    GSL::Vector_i v{1, 2, 3};
    auto it = v.begin();
    EXPECT_EQ(*(2 + it), 3.);
}

TEST(Vector_iTest, TestIterStepDecrement)
{
    GSL::Vector_i v{1, 2, 3};
    auto it = v.begin();
    it += 2;
    it -= 2;
    EXPECT_EQ(*it, 1.);
}

TEST(Vector_iTest, TestIterStepBack)
{
    GSL::Vector_i v{1, 2, 3};
    auto it = v.begin() + 2;
    EXPECT_EQ(*(it - 2), 1.);
}

TEST(Vector_iTest, TestIterDiff)
{
    GSL::Vector_i v{1, 2, 3};
    auto it = v.begin() + 2;
    EXPECT_EQ(it - v.begin(), 2.);
}

TEST(Vector_iTest, TestIterEq)
{
    GSL::Vector_i v{1, 2, 3};
    auto it1 = v.begin() + 2;
    auto it2 = v.begin();
    it2 += 2;

    EXPECT_EQ(it1, it2);
}

TEST(Vector_iTest, TestIterNeq)
{
    GSL::Vector_i v{1, 2, 3};
    auto it1 = v.begin() + 2;
    auto it2 = v.begin();

    EXPECT_NE(it1, it2);
}

TEST(Vector_iTest, TestEnd)
{
    GSL::Vector_i v{1, 2, 3};
    auto it1 = v.begin() + 2;
    auto it2 = v.end();

    EXPECT_EQ(it1, --it2);
}

TEST(Vector_iTest, TestcIterPreIncrement)
{
    GSL::Vector_i v{1, 2, 3};
    EXPECT_EQ(*++v.cbegin(), 2.);
}

TEST(Vector_iTest, TestcIterPostIncrement)
{
    GSL::Vector_i v{1, 2, 3};
    auto it = v.cbegin();
    it++;
    EXPECT_EQ(*it, 2.);
}

TEST(Vector_iTest, TestcIterPreDecrement)
{
    GSL::Vector_i v{1, 2, 3};
    EXPECT_EQ(*--(++v.cbegin()), 1.);
}

TEST(Vector_iTest, TestcIterPostDecrement)
{
    GSL::Vector_i v{1, 2, 3};
    auto it = v.cbegin();
    it++; it--;
    EXPECT_EQ(*it, 1.);
}

TEST(Vector_iTest, TestcIterStepIncrement)
{
    GSL::Vector_i v{1, 2, 3};
    auto it = v.cbegin();
    it += 2;
    EXPECT_EQ(*it, 3.);
}

TEST(Vector_iTest, TestcIterStep)
{
    GSL::Vector_i v{1, 2, 3};
    auto it = v.cbegin();
    EXPECT_EQ(*(it + 2), 3.);
}

TEST(Vector_iTest, TestcIterStepForward)
{
    GSL::Vector_i v{1, 2, 3};
    auto it = v.cbegin();
    EXPECT_EQ(*(2 + it), 3.);
}

TEST(Vector_iTest, TestcIterStepDecrement)
{
    GSL::Vector_i v{1, 2, 3};
    auto it = v.cbegin();
    it += 2;
    it -= 2;
    EXPECT_EQ(*it, 1.);
}

TEST(Vector_iTest, TestcIterStepBack)
{
    GSL::Vector_i v{1, 2, 3};
    auto it = v.cbegin() + 2;
    EXPECT_EQ(*(it - 2), 1.);
}

TEST(Vector_iTest, TestcIterDiff)
{
    GSL::Vector_i v{1, 2, 3};
    auto it = v.cbegin() + 2;
    EXPECT_EQ(it - v.cbegin(), 2.);
}

TEST(Vector_iTest, TestcIterEq)
{
    GSL::Vector_i v{1, 2, 3};
    auto it1 = v.cbegin() + 2;
    auto it2 = v.cbegin();
    it2 += 2;

    EXPECT_EQ(it1, it2);
}

TEST(Vector_iTest, TestcIterNeq)
{
    GSL::Vector_i v{1, 2, 3};
    auto it1 = v.cbegin() + 2;
    auto it2 = v.cbegin();

    EXPECT_NE(it1, it2);
}

TEST(Vector_iTest, TestcEnd)
{
    GSL::Vector_i v{1, 2, 3};
    auto it1 = v.cbegin() + 2;
    auto it2 = v.cend();

    EXPECT_EQ(it1, --it2);
}

TEST(Vector_iTest, TestRbegin)
{
    GSL::Vector_i v{1, 2, 3};
    auto it1 = v.rbegin();

    EXPECT_EQ(*it1, 3.);
}

TEST(Vector_iTest, TestRend)
{
    GSL::Vector_i v{1, 2, 3};
    auto it1 = v.rend();

    EXPECT_EQ(*--it1, 1.);
}

TEST(Vector_iTest, TestcRbegin)
{
    GSL::Vector_i v{1, 2, 3};
    auto it1 = v.crbegin();

    EXPECT_EQ(*it1, 3.);
}

TEST(Vector_iTest, TestcRend)
{
    GSL::Vector_i v{1, 2, 3};
    auto it1 = v.crend();

    EXPECT_EQ(*--it1, 1.);
}

TEST(Vector_iTest, TestFront)
{
    GSL::Vector_i v{1, 2, 3};
    EXPECT_EQ(v.front(), 1.);
}

TEST(Vector_iTest, TestBack)
{
    GSL::Vector_i v{1, 2, 3};
    EXPECT_EQ(v.back(), 3.);
}

TEST(Vector_iTest, TestAt)
{
    GSL::Vector_i v{1, 2, 3};
    EXPECT_EQ(v.at(1), 2.);
}

TEST(Vector_iTest, TestAssign1)
{
    GSL::Vector_i v1{1, 2, 3};
    GSL::Vector_i v2{3, 4, 5};
    v2.assign(v1.begin(), v1.end());
    EXPECT_EQ(v1, v2);
}

TEST(Vector_iTest, TestAssign2)
{
    GSL::Vector_i v1{1, 2, 3};
    GSL::Vector_i v2{3, 3, 3, 3};
    v1.assign(4, 3.);
    EXPECT_EQ(v1, v2);
}

TEST(Vector_iTest, TestAssign3)
{
    GSL::Vector_i v1{1, 2, 3};
    GSL::Vector_i v2{3, 4};
    v1.assign({3, 4});
    EXPECT_EQ(v1, v2);
}
