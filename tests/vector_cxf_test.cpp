#include "GSLpp/complex.h"
#include "GSLpp/vector.h"
#include <gtest/gtest.h>
#include <iostream>
#include <cmath>

TEST(Vector_cxfTest, TestConstruction)
{
    GSL::Vector_cxf v(3);

    EXPECT_EQ(v[0], GSL::Complex_f{});
    EXPECT_EQ(v[1], GSL::Complex_f{});
    EXPECT_EQ(v[2], GSL::Complex_f{});
}

TEST(Vector_cxfTest, TestConstructionInitializerList)
{
    GSL::Complex_f a = 1.f, b = 2.f, c = 3.f;
    GSL::Vector_cxf v{a, b, c};
    EXPECT_EQ(v[0], GSL::Complex_f{1.f});
    EXPECT_EQ(v[1], GSL::Complex_f{2.f});
    EXPECT_EQ(v[2], GSL::Complex_f{3.f});
}

TEST(Vector_cxfTest, TestConstructionCopy)
{
    GSL::Complex_f a = 1.f, b = 2.f, c = 3.f;
    GSL::Vector_cxf v1{a, b, c};
    GSL::Vector_cxf v2{v1};
    EXPECT_EQ(v1[0], GSL::Complex_f{v2[0]});
    EXPECT_EQ(v1[1], GSL::Complex_f{v2[1]});
    EXPECT_EQ(v1[2], GSL::Complex_f{v2[2]});
}

TEST(Vector_cxfTest, TestConstructionMove)
{
    GSL::Complex_f a = 1.f, b = 2.f, c = 3.f;
    GSL::Vector_cxf v1{a, b, c};
    GSL::Vector_cxf v2{std::move(v1)};
    EXPECT_EQ(v2[0], GSL::Complex_f{1.f});
    EXPECT_EQ(v2[1], GSL::Complex_f{2.f});
    EXPECT_EQ(v2[2], GSL::Complex_f{3.f});
}

TEST(Vector_cxfTest, TestEqual)
{

    GSL::Complex_f a = 1.f, b = 2.f, c = 3.f;
    GSL::Vector_cxf v1{a, b, c};
    GSL::Vector_cxf v2{v1};

    EXPECT_EQ(v1, v2);
}

TEST(Vector_cxfTest, TestNotEqual)
{

    GSL::Complex_f a = 1.f, b = 2.f, c = 3.f;
    GSL::Vector_cxf v1{a, b, c};
    GSL::Vector_cxf v2{a +1, b, c};

    EXPECT_NE(v1, v2);
}

TEST(Vector_cxfTest, TestCopy)
{

    GSL::Complex_f a = 1.f, b = 2.f, c = 3.f;
    GSL::Vector_cxf v1{a, b, c};
    GSL::Vector_cxf v2;
    v2 = v1;

    EXPECT_EQ(v1, v2);
}

TEST(Vector_cxfTest, TestMove)
{

    GSL::Complex_f a = 1.f, b = 2.f, c = 3.f;
    GSL::Vector_cxf v1{a, b, c}, v1s{a, b, c};
    GSL::Vector_cxf v2;
    v2 = std::move(v1);

    EXPECT_EQ(v2, v1s);
}

TEST(Vector_cxfTest, TestDecayToGSLVector_cxf)
{
    GSL::Complex_f a = 1.f, b = 2.f, c = 3.f;
    GSL::Vector_cxf v{a, b, c};
    gsl_vector_complex_float gv = v;

    EXPECT_EQ(gsl_vector_complex_float_get(&gv, 0), a);
}

TEST(Vector_cxfTest, TestSize)
{
    GSL::Complex_f a = 1.f, b = 2.f, c = 3.f;
    GSL::Vector_cxf v{a, b, c};

    EXPECT_EQ(v.size(), 3);
}

TEST(Vector_cxfTest, TestDim)
{
    GSL::Complex_f a = 1.f, b = 2.f, c = 3.f;
    GSL::Vector_cxf v{a, b, c};

    EXPECT_EQ(v.dim(), 3);
}

TEST(Vector_cxfTest, TestCopyFun)
{
    GSL::Complex_f a = 1.f, b = 2.f, c = 3.f;
    GSL::Vector_cxf v{a, b, c}, v2;
    v2.copy(v);

    EXPECT_EQ(v, v2);
}

TEST(Vector_cxfTest, TestNorm)
{
    GSL::Complex_f a = 1.f, b = 2.f, c = 3.f;
    GSL::Vector_cxf v{a, b, c};

    EXPECT_FLOAT_EQ(v.norm<float>(), std::sqrt(a.re()*a.re() + b.re()*b.re() + c.re()*c.re()));
}

TEST(Vector_cxfTest, TestNormalize)
{
    GSL::Complex_f a = 1.f, b = 2.f, c = 3.f;
    GSL::Vector_cxf v{a, b, c};
    v.normalize<float>();

    EXPECT_FLOAT_EQ(v.norm<float>(), 1.f);
}

TEST(Vector_cxfTest, TestDot)
{
    GSL::Vector_cxf v1{1.f, 0.f, 0.f}, v2{0.f, 1.f, 0.f};

    EXPECT_EQ(v1.dot(v2), GSL::Complex_f{0.f});
}

TEST(Vector_cxfTest, TestCross)
{
    GSL::Vector_cxf v1{1.f, 0.f, 0.f}, v2{0.f, 1.f, 0.f}, v3{0.f, 0.f, 1.f};

    EXPECT_EQ(v1.cross(v2), v3);
}

TEST(Vector_cxfTest, TestIncrement)
{
    GSL::Vector_cxf v1{1.f, 0.f, 0.f}, v2{0.f, 1.f, 0.f}, v3{1.f, 1.f, 0.f};

    EXPECT_EQ(v1 += v2, v3);
}

TEST(Vector_cxfTest, TestDecrement)
{
    GSL::Vector_cxf v1{1.f, 0.f, 0.f}, v2{0.f, 1.f, 0.f}, v3{1.f, -1.f, 0.f};

    EXPECT_EQ(v1 -= v2, v3);
}

TEST(Vector_cxfTest, TestElMultScale)
{
    GSL::Vector_cxf v1{3.f, 2.f, 2.f}, v2{2.f, 3.f, 4.f}, v3{6.f, 6.f, 8.f};

    EXPECT_EQ(v1 *= v2, v3);
}

TEST(Vector_cxfTest, TestElDivScale)
{
    GSL::Vector_cxf v1{8.f, 4.f, 2.f}, v2{6.f, 3.f, 2.f}, v3{8.f/6, 4.f/3, 2.f/2};

    EXPECT_EQ(v1 /= v2, v3);
}

TEST(Vector_cxfTest, TestMultScale)
{
    GSL::Vector_cxf v1{3.f, 2.f, 2.f}, v2{9.f, 6.f, 6.f};

    EXPECT_EQ(v1 *= GSL::Complex_f{3}, v2);
}

TEST(Vector_cxfTest, TestDivScale)
{
    GSL::Vector_cxf v1{8.f, 4.f, 2.f}, v2{4.f, 2.f, 1.f};

    EXPECT_EQ(v1 /= GSL::Complex_f{2.f}, v2);
}

TEST(Vector_cxfTest, TestAddition)
{
    GSL::Vector_cxf v1{1.f, 0.f, 0.f}, v2{0.f, 1.f, 0.f}, v3{1.f, 1.f, 0.f};

    EXPECT_EQ(v1 + v2, v3);
}

TEST(Vector_cxfTest, TestSubtraction)
{
    GSL::Vector_cxf v1{1.f, 0.f, 0.f}, v2{0.f, 1.f, 0.f}, v3{1.f, -1.f, 0.f};

    EXPECT_EQ(v1 - v2, v3);
}

TEST(Vector_cxfTest, TestElMult)
{
    GSL::Vector_cxf v1{3.f, 2.f, 2.f}, v2{2.f, 3.f, 4.f}, v3{6.f, 6.f, 8.f};

    EXPECT_EQ(v1 * v2, v3);
}

TEST(Vector_cxfTest, TestElDiv)
{
    GSL::Vector_cxf v1{8.f, 4.f, 2.f}, v2{6.f, 3.f, 2.f}, v3{8.f/6, 4.f/3, 2.f/2};

    EXPECT_EQ(v1 / v2, v3);
}

TEST(Vector_cxfTest, TestScalarMult)
{
    GSL::Vector_cxf v1{3.f, 2.f, 2.f}, v2{9.f, 6.f, 6.f};

    EXPECT_EQ(v1 * GSL::Complex_f(3.f), v2);
}

TEST(Vector_cxfTest, TestScalarDiv)
{
    GSL::Vector_cxf v1{8.f, 4.f, 2.f}, v2{4.f, 2.f, 1.f};

    EXPECT_EQ(v1 / GSL::Complex_f(2.f), v2);
}

TEST(Vector_cxfTest, TestScalarMult2)
{
    GSL::Vector_cxf v1{3.f, 2.f, 2.f}, v2{9.f, 6.f, 6.f};

    EXPECT_EQ(GSL::Complex_f(3.f) * v1, v2);
}

TEST(Vector_cxfTest, TestBegin)
{
    GSL::Vector_cxf v{1.f, 2.f, 3.f};
    EXPECT_EQ(*v.begin(), GSL::Complex_f{1.f});
}

TEST(Vector_cxfTest, TestcBegin)
{
    GSL::Vector_cxf v{1.f, 2.f, 3.f};
    EXPECT_EQ(*v.cbegin(), GSL::Complex_f{1.f});
}

TEST(Vector_cxfTest, TestIterPreIncrement)
{
    GSL::Vector_cxf v{1.f, 2.f, 3.f};
    EXPECT_EQ(*++v.begin(), GSL::Complex_f{2.f});
}

TEST(Vector_cxfTest, TestIterPostIncrement)
{
    GSL::Vector_cxf v{1.f, 2.f, 3.f};
    auto it = v.begin();
    it++;
    EXPECT_EQ(*it, GSL::Complex_f{2.f});
}

TEST(Vector_cxfTest, TestIterPreDecrement)
{
    GSL::Vector_cxf v{1.f, 2.f, 3.f};
    EXPECT_EQ(*--(++v.begin()), GSL::Complex_f{1.f});
}

TEST(Vector_cxfTest, TestIterPostDecrement)
{
    GSL::Vector_cxf v{1.f, 2.f, 3.f};
    auto it = v.begin();
    it++; it--;
    EXPECT_EQ(*it, GSL::Complex_f{1.f});
}

TEST(Vector_cxfTest, TestIterStepIncrement)
{
    GSL::Vector_cxf v{1.f, 2.f, 3.f};
    auto it = v.begin();
    it += 2;
    EXPECT_EQ(*it, GSL::Complex_f{3.f});
}

TEST(Vector_cxfTest, TestIterStep)
{
    GSL::Vector_cxf v{1.f, 2.f, 3.f};
    auto it = v.begin();
    EXPECT_EQ(*(it + 2), GSL::Complex_f{3.f});
}

TEST(Vector_cxfTest, TestIterStepDecrement)
{
    GSL::Vector_cxf v{1.f, 2.f, 3.f};
    auto it = v.begin();
    it += 2;
    it -= 2;
    EXPECT_EQ(*it, GSL::Complex_f{1.f});
}

TEST(Vector_cxfTest, TestIterStepBack)
{
    GSL::Vector_cxf v{1.f, 2.f, 3.f};
    auto it = v.begin() + 2;
    EXPECT_EQ(*(it - 2), GSL::Complex_f{1.f});
}

TEST(Vector_cxfTest, TestIterDiff)
{
    GSL::Vector_cxf v{1.f, 2.f, 3.f};
    auto it = v.begin() + 2;
    EXPECT_EQ(it - v.begin(), 2.f);
}

TEST(Vector_cxfTest, TestIterEq)
{
    GSL::Vector_cxf v{1.f, 2.f, 3.f};
    auto it1 = v.begin() + 2;
    auto it2 = v.begin();
    it2 += 2;

    EXPECT_EQ(it1, it2);
}

TEST(Vector_cxfTest, TestIterNeq)
{
    GSL::Vector_cxf v{1.f, 2.f, 3.f};
    auto it1 = v.begin() + 2;
    auto it2 = v.begin();

    EXPECT_NE(it1, it2);
}

TEST(Vector_cxfTest, TestEnd)
{
    GSL::Vector_cxf v{1.f, 2.f, 3.f};
    auto it1 = v.begin() + 2;
    auto it2 = v.end();

    EXPECT_EQ(it1, --it2);
}

TEST(Vector_cxfTest, TestcIterPreIncrement)
{
    GSL::Vector_cxf v{1.f, 2.f, 3.f};
    EXPECT_EQ(*++v.cbegin(), GSL::Complex_f{2.f});
}

TEST(Vector_cxfTest, TestcIterPostIncrement)
{
    GSL::Vector_cxf v{1.f, 2.f, 3.f};
    auto it = v.cbegin();
    it++;
    EXPECT_EQ(*it, GSL::Complex_f{2.f});
}

TEST(Vector_cxfTest, TestcIterPreDecrement)
{
    GSL::Vector_cxf v{1.f, 2.f, 3.f};
    EXPECT_EQ(*--(++v.cbegin()), GSL::Complex_f{1.f});
}

TEST(Vector_cxfTest, TestcIterPostDecrement)
{
    GSL::Vector_cxf v{1.f, 2.f, 3.f};
    auto it = v.cbegin();
    it++; it--;
    EXPECT_EQ(*it, GSL::Complex_f{1.f});
}

TEST(Vector_cxfTest, TestcIterStepIncrement)
{
    GSL::Vector_cxf v{1.f, 2.f, 3.f};
    auto it = v.cbegin();
    it += 2;
    EXPECT_EQ(*it, GSL::Complex_f{3.f});
}

TEST(Vector_cxfTest, TestcIterStep)
{
    GSL::Vector_cxf v{1.f, 2.f, 3.f};
    auto it = v.cbegin();
    EXPECT_EQ(*(it + 2), GSL::Complex_f{3.f});
}

TEST(Vector_cxfTest, TestcIterStepDecrement)
{
    GSL::Vector_cxf v{1.f, 2.f, 3.f};
    auto it = v.cbegin();
    it += 2;
    it -= 2;
    EXPECT_EQ(*it, GSL::Complex_f{1.f});
}

TEST(Vector_cxfTest, TestcIterStepBack)
{
    GSL::Vector_cxf v{1.f, 2.f, 3.f};
    auto it = v.cbegin() + 2;
    EXPECT_EQ(*(it - 2), GSL::Complex_f{1.f});
}

TEST(Vector_cxfTest, TestcIterDiff)
{
    GSL::Vector_cxf v{1.f, 2.f, 3.f};
    auto it = v.cbegin() + 2;
    EXPECT_EQ(it - v.cbegin(), 2.f);
}

TEST(Vector_cxfTest, TestcIterEq)
{
    GSL::Vector_cxf v{1.f, 2.f, 3.f};
    auto it1 = v.cbegin() + 2;
    auto it2 = v.cbegin();
    it2 += 2;

    EXPECT_EQ(it1, it2);
}

TEST(Vector_cxfTest, TestcIterNeq)
{
    GSL::Vector_cxf v{1.f, 2.f, 3.f};
    auto it1 = v.cbegin() + 2;
    auto it2 = v.cbegin();

    EXPECT_NE(it1, it2);
}

TEST(Vector_cxfTest, TestcEnd)
{
    GSL::Vector_cxf v{1.f, 2.f, 3.f};
    auto it1 = v.cbegin() + 2;
    auto it2 = v.cend();

    EXPECT_EQ(it1, --it2);
}

TEST(Vector_cxfTest, TestRbegin)
{
    GSL::Vector_cxf v{1.f, 2.f, 3.f};
    auto it1 = v.rbegin();

    EXPECT_EQ(*it1, GSL::Complex_f{3.f});
}

TEST(Vector_cxfTest, TestRend)
{
    GSL::Vector_cxf v{1.f, 2.f, 3.f};
    auto it1 = v.rend();

    EXPECT_EQ(*--it1, GSL::Complex_f{1.f});
}

TEST(Vector_cxfTest, TestcRbegin)
{
    GSL::Vector_cxf v{1.f, 2.f, 3.f};
    auto it1 = v.crbegin();

    EXPECT_EQ(*it1, GSL::Complex_f{3.f});
}

TEST(Vector_cxfTest, TestcRend)
{
    GSL::Vector_cxf v{1.f, 2.f, 3.f};
    auto it1 = v.crend();

    EXPECT_EQ(*--it1, GSL::Complex_f{1.f});
}

TEST(Vector_cxfTest, TestFront)
{
    GSL::Vector_cxf v{1.f, 2.f, 3.f};
    EXPECT_EQ(v.front(), GSL::Complex_f{1.f});
}

TEST(Vector_cxfTest, TestBack)
{
    GSL::Vector_cxf v{1.f, 2.f, 3.f};
    EXPECT_EQ(v.back(), GSL::Complex_f{3.f});
}

TEST(Vector_cxfTest, TestAt)
{
    GSL::Vector_cxf v{1.f, 2.f, 3.f};
    EXPECT_EQ(v.at(1), GSL::Complex_f{2.f});
}

TEST(Vector_cxfTest, TestAssign1)
{
    GSL::Vector_cxf v1{1.f, 2.f, 3.f};
    GSL::Vector_cxf v2{3.f, 4.f, 5.f};
    v2.assign(v1.begin(), v1.end());
    EXPECT_EQ(v1, v2);
}

TEST(Vector_cxfTest, TestAssign2)
{
    GSL::Vector_cxf v1{1.f, 2.f, 3.f};
    GSL::Vector_cxf v2{3.f, 3.f, 3.f, 3.f};
    v1.assign(4, GSL::Complex_f(3.f));
    EXPECT_EQ(v1, v2);
}

TEST(Vector_cxfTest, TestAssign3)
{
    GSL::Vector_cxf v1{1.f, 2.f, 3.f};
    GSL::Vector_cxf v2{3.f, 4.f};
    v1.assign({{3.f}, {4.f}});
    EXPECT_EQ(v1, v2);
}
