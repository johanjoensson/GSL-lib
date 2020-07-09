#include "GSLpp/vector.h"
#include <gtest/gtest.h>
#include <iostream>
#include <cmath>

TEST(Vector_uiTest, TestConstruction)
{
    GSL::Vector_ui v(3);
    EXPECT_EQ(v[0], 0.);
    EXPECT_EQ(v[1], 0.);
    EXPECT_EQ(v[2], 0.);
}

TEST(Vector_uiTest, TestConstructionInitializerList)
{
    unsigned int a =1, b = 2, c = 3.;
    GSL::Vector_ui v{a, b, c};
    EXPECT_EQ(v[0], 1.);
    EXPECT_EQ(v[1], 2.);
    EXPECT_EQ(v[2], 3.);
}

TEST(Vector_uiTest, TestConstructionCopy)
{
    unsigned int a =1, b = 2, c = 3.;
    GSL::Vector_ui v1{a, b, c};
    GSL::Vector_ui v2{v1};
    EXPECT_EQ(v1[0], v2[0]);
    EXPECT_EQ(v1[1], v2[1]);
    EXPECT_EQ(v1[2], v2[2]);
}

TEST(Vector_uiTest, TestConstructionMove)
{
    unsigned int a =1, b = 2, c = 3.;
    GSL::Vector_ui v1{a, b, c};
    GSL::Vector_ui v2{std::move(v1)};
    EXPECT_EQ(v2[0], 1.);
    EXPECT_EQ(v2[1], 2.);
    EXPECT_EQ(v2[2], 3.);
}

TEST(Vector_uiTest, TestEqual)
{

    unsigned int a =1, b = 2, c = 3.;
    GSL::Vector_ui v1{a, b, c};
    GSL::Vector_ui v2{v1};

    EXPECT_EQ(v1, v2);
}

TEST(Vector_uiTest, TestNotEqual)
{

    unsigned int a =1, b = 2, c = 3.;
    GSL::Vector_ui v1{a, b, c};
    GSL::Vector_ui v2{a +1, b, c};

    EXPECT_NE(v1, v2);
}

TEST(Vector_uiTest, TestCopy)
{

    unsigned int a =1, b = 2, c = 3.;
    GSL::Vector_ui v1{a, b, c};
    GSL::Vector_ui v2;
    v2 = v1;

    EXPECT_EQ(v1, v2);
}

TEST(Vector_uiTest, TestMove)
{

    unsigned int a =1, b = 2, c = 3.;
    GSL::Vector_ui v1{a, b, c}, v1s{a, b, c};
    GSL::Vector_ui v2;
    v2 = std::move(v1);

    EXPECT_EQ(v2, v1s);
}

TEST(Vector_uiTest, TestDecayToGSLVector_ui)
{
    unsigned int a =1, b = 2, c = 3.;
    GSL::Vector_ui v{a, b, c};
    gsl_vector_uint gv = v;

    EXPECT_EQ(gsl_vector_uint_get(&gv, 0), a);
}

TEST(Vector_uiTest, TestSize)
{
    unsigned int a = 1, b = 2, c = 3.;
    GSL::Vector_ui v{a, b, c};

    EXPECT_EQ(v.size(), 3);
}

TEST(Vector_uiTest, TestDim)
{
    unsigned int a =1, b = 2, c = 3.;
    GSL::Vector_ui v{a, b, c};

    EXPECT_EQ(v.dim(), 3);
}

TEST(Vector_uiTest, TestCopyFun)
{
    unsigned int a =1, b = 2, c = 3.;
    GSL::Vector_ui v{a, b, c}, v2;
    v2.copy(v);

    EXPECT_EQ(v, v2);
}

TEST(Vector_uiTest, TestNorm)
{
    unsigned int a =1, b = 2, c = 3.;
    GSL::Vector_ui v{a, b, c};

    EXPECT_EQ(v.norm<double>(), std::sqrt(a*a + b*b + c*c));
}

TEST(Vector_uiTest, TestNormalize)
{
    unsigned int a =1, b = 2, c = 3.;
    GSL::Vector_ui v{a, b, c};
    v.normalize<double>();

    EXPECT_EQ(v.norm<double>(), 1.);
}

TEST(Vector_uiTest, TestDot)
{
    GSL::Vector_ui v1{1, 0, 0}, v2{0, 1, 0};

    EXPECT_EQ(v1.dot(v2), 0.);
}

TEST(Vector_uiTest, TestCross)
{
    GSL::Vector_ui v1{1, 0, 0}, v2{0, 1, 0}, v3{0, 0, 1};

    EXPECT_EQ(v1.cross(v2), v3);
}

TEST(Vector_uiTest, TestIncrement)
{
    GSL::Vector_ui v1{1, 0, 0}, v2{0, 1, 0}, v3{1, 1, 0};

    EXPECT_EQ(v1 += v2, v3);
}

TEST(Vector_uiTest, TestDecrement)
{
    GSL::Vector_ui v1{1, 2, 0}, v2{0, 1, 0}, v3{1, 1, 0};

    EXPECT_EQ(v1 -= v2, v3);
}

TEST(Vector_uiTest, TestElMultScale)
{
    GSL::Vector_ui v1{3, 2, 2}, v2{2, 3, 4}, v3{6, 6, 8};

    EXPECT_EQ(v1 *= v2, v3);
}

TEST(Vector_uiTest, TestElDivScale)
{
    GSL::Vector_ui v1{8, 4, 2}, v2{6, 3, 2}, v3{8/6, 4/3, 2/2};

    EXPECT_EQ(v1 /= v2, v3);
}

TEST(Vector_uiTest, TestMultScale)
{
    GSL::Vector_ui v1{3, 2, 2}, v2{9, 6, 6};

    EXPECT_EQ(v1 *= 3, v2);
}

TEST(Vector_uiTest, TestDivScale)
{
    GSL::Vector_ui v1{8, 4, 2}, v2{4, 2, 1};

    EXPECT_EQ(v1 /= 2, v2);
}

TEST(Vector_uiTest, TestAddition)
{
    GSL::Vector_ui v1{1, 0, 0}, v2{0, 1, 0}, v3{1, 1, 0};

    EXPECT_EQ(v1 + v2, v3);
}

TEST(Vector_uiTest, TestSubtraction)
{
    GSL::Vector_ui v1{1, 2, 0}, v2{0, 1, 0}, v3{1, 1, 0};

    EXPECT_EQ(v1 - v2, v3);
}

TEST(Vector_uiTest, TestElMult)
{
    GSL::Vector_ui v1{3, 2, 2}, v2{2, 3, 4}, v3{6, 6, 8};

    EXPECT_EQ(v1 * v2, v3);
}

TEST(Vector_uiTest, TestElDiv)
{
    GSL::Vector_ui v1{8, 4, 2}, v2{6, 3, 2}, v3{8/6, 4/3, 2/2};

    EXPECT_EQ(v1 / v2, v3);
}

TEST(Vector_uiTest, TestScalarMult)
{
    GSL::Vector_ui v1{3, 2, 2}, v2{9, 6, 6};

    EXPECT_EQ(v1 * 3, v2);
}

TEST(Vector_uiTest, TestScalarDiv)
{
    GSL::Vector_ui v1{8, 4, 2}, v2{4, 2, 1};

    EXPECT_EQ(v1 / 2, v2);
}

TEST(Vector_uiTest, TestScalarMult2)
{
    GSL::Vector_ui v1{3, 2, 2}, v2{9, 6, 6};

    EXPECT_EQ(3. * v1, v2);
}

TEST(Vector_uiTest, TestBegin)
{
    GSL::Vector_ui v{1, 2, 3};
    EXPECT_EQ(*v.begin(), 1.);
}

TEST(Vector_uiTest, TestcBegin)
{
    GSL::Vector_ui v{1, 2, 3};
    EXPECT_EQ(*v.cbegin(), 1.);
}

TEST(Vector_uiTest, TestIterPreIncrement)
{
    GSL::Vector_ui v{1, 2, 3};
    EXPECT_EQ(*++v.begin(), 2.);
}

TEST(Vector_uiTest, TestIterPostIncrement)
{
    GSL::Vector_ui v{1, 2, 3};
    auto it = v.begin();
    it++;
    EXPECT_EQ(*it, 2.);
}

TEST(Vector_uiTest, TestIterPreDecrement)
{
    GSL::Vector_ui v{1, 2, 3};
    EXPECT_EQ(*--(++v.begin()), 1.);
}

TEST(Vector_uiTest, TestIterPostDecrement)
{
    GSL::Vector_ui v{1, 2, 3};
    auto it = v.begin();
    it++; it--;
    EXPECT_EQ(*it, 1.);
}

TEST(Vector_uiTest, TestIterStepIncrement)
{
    GSL::Vector_ui v{1, 2, 3};
    auto it = v.begin();
    it += 2;
    EXPECT_EQ(*it, 3.);
}

TEST(Vector_uiTest, TestIterStep)
{
    GSL::Vector_ui v{1, 2, 3};
    auto it = v.begin();
    EXPECT_EQ(*(it + 2), 3.);
}

TEST(Vector_uiTest, TestIterStepDecrement)
{
    GSL::Vector_ui v{1, 2, 3};
    auto it = v.begin();
    it += 2;
    it -= 2;
    EXPECT_EQ(*it, 1.);
}

TEST(Vector_uiTest, TestIterStepBack)
{
    GSL::Vector_ui v{1, 2, 3};
    auto it = v.begin() + 2;
    EXPECT_EQ(*(it - 2), 1.);
}

TEST(Vector_uiTest, TestIterDiff)
{
    GSL::Vector_ui v{1, 2, 3};
    auto it = v.begin() + 2;
    EXPECT_EQ(it - v.begin(), 2.);
}

TEST(Vector_uiTest, TestIterEq)
{
    GSL::Vector_ui v{1, 2, 3};
    auto it1 = v.begin() + 2;
    auto it2 = v.begin();
    it2 += 2;

    EXPECT_EQ(it1, it2);
}

TEST(Vector_uiTest, TestIterNeq)
{
    GSL::Vector_ui v{1, 2, 3};
    auto it1 = v.begin() + 2;
    auto it2 = v.begin();

    EXPECT_NE(it1, it2);
}

TEST(Vector_uiTest, TestEnd)
{
    GSL::Vector_ui v{1, 2, 3};
    auto it1 = v.begin() + 2;
    auto it2 = v.end();

    EXPECT_EQ(it1, --it2);
}

TEST(Vector_uiTest, TestcIterPreIncrement)
{
    GSL::Vector_ui v{1, 2, 3};
    EXPECT_EQ(*++v.cbegin(), 2.);
}

TEST(Vector_uiTest, TestcIterPostIncrement)
{
    GSL::Vector_ui v{1, 2, 3};
    auto it = v.cbegin();
    it++;
    EXPECT_EQ(*it, 2.);
}

TEST(Vector_uiTest, TestcIterPreDecrement)
{
    GSL::Vector_ui v{1, 2, 3};
    EXPECT_EQ(*--(++v.cbegin()), 1.);
}

TEST(Vector_uiTest, TestcIterPostDecrement)
{
    GSL::Vector_ui v{1, 2, 3};
    auto it = v.cbegin();
    it++; it--;
    EXPECT_EQ(*it, 1.);
}

TEST(Vector_uiTest, TestcIterStepIncrement)
{
    GSL::Vector_ui v{1, 2, 3};
    auto it = v.cbegin();
    it += 2;
    EXPECT_EQ(*it, 3.);
}

TEST(Vector_uiTest, TestcIterStep)
{
    GSL::Vector_ui v{1, 2, 3};
    auto it = v.cbegin();
    EXPECT_EQ(*(it + 2), 3.);
}

TEST(Vector_uiTest, TestcIterStepDecrement)
{
    GSL::Vector_ui v{1, 2, 3};
    auto it = v.cbegin();
    it += 2;
    it -= 2;
    EXPECT_EQ(*it, 1.);
}

TEST(Vector_uiTest, TestcIterStepBack)
{
    GSL::Vector_ui v{1, 2, 3};
    auto it = v.cbegin() + 2;
    EXPECT_EQ(*(it - 2), 1.);
}

TEST(Vector_uiTest, TestcIterDiff)
{
    GSL::Vector_ui v{1, 2, 3};
    auto it = v.cbegin() + 2;
    EXPECT_EQ(it - v.cbegin(), 2.);
}

TEST(Vector_uiTest, TestcIterEq)
{
    GSL::Vector_ui v{1, 2, 3};
    auto it1 = v.cbegin() + 2;
    auto it2 = v.cbegin();
    it2 += 2;

    EXPECT_EQ(it1, it2);
}

TEST(Vector_uiTest, TestcIterNeq)
{
    GSL::Vector_ui v{1, 2, 3};
    auto it1 = v.cbegin() + 2;
    auto it2 = v.cbegin();

    EXPECT_NE(it1, it2);
}

TEST(Vector_uiTest, TestcEnd)
{
    GSL::Vector_ui v{1, 2, 3};
    auto it1 = v.cbegin() + 2;
    auto it2 = v.cend();

    EXPECT_EQ(it1, --it2);
}

TEST(Vector_uiTest, TestRbegin)
{
    GSL::Vector_ui v{1, 2, 3};
    auto it1 = v.rbegin();

    EXPECT_EQ(*it1, 3.);
}

TEST(Vector_uiTest, TestRend)
{
    GSL::Vector_ui v{1, 2, 3};
    auto it1 = v.rend();

    EXPECT_EQ(*--it1, 1.);
}

TEST(Vector_uiTest, TestcRbegin)
{
    GSL::Vector_ui v{1, 2, 3};
    auto it1 = v.crbegin();

    EXPECT_EQ(*it1, 3.);
}

TEST(Vector_uiTest, TestcRend)
{
    GSL::Vector_ui v{1, 2, 3};
    auto it1 = v.crend();

    EXPECT_EQ(*--it1, 1.);
}

TEST(Vector_uiTest, TestFront)
{
    GSL::Vector_ui v{1, 2, 3};
    EXPECT_EQ(v.front(), 1.);
}

TEST(Vector_uiTest, TestBack)
{
    GSL::Vector_ui v{1, 2, 3};
    EXPECT_EQ(v.back(), 3.);
}

TEST(Vector_uiTest, TestAt)
{
    GSL::Vector_ui v{1, 2, 3};
    EXPECT_EQ(v.at(1), 2.);
}

TEST(Vector_uiTest, TestAssign1)
{
    GSL::Vector_ui v1{1, 2, 3};
    GSL::Vector_ui v2{3, 4, 5};
    v2.assign(v1.begin(), v1.end());
    EXPECT_EQ(v1, v2);
}

TEST(Vector_uiTest, TestAssign2)
{
    GSL::Vector_ui v1{1, 2, 3};
    GSL::Vector_ui v2{3, 3, 3, 3};
    v1.assign(4, 3.);
    EXPECT_EQ(v1, v2);
}

TEST(Vector_uiTest, TestAssign3)
{
    GSL::Vector_ui v1{1, 2, 3};
    GSL::Vector_ui v2{3, 4};
    v1.assign({3, 4});
    EXPECT_EQ(v1, v2);
}
