#include "GSLpp/complex.h"
#include "GSLpp/vector.h"
#include <gtest/gtest.h>
#include <iostream>
#include <cmath>

TEST(Vector_cxldTest, TestConstruction)
{
    GSL::Vector_cxld v(3);

    EXPECT_EQ(v[0], GSL::Complex_ld{});
    EXPECT_EQ(v[1], GSL::Complex_ld{});
    EXPECT_EQ(v[2], GSL::Complex_ld{});
}

TEST(Vector_cxldTest, TestConstructionInitializerList)
{
    GSL::Complex_ld a = 1.l, b = 2.l, c = 3.l;
    GSL::Vector_cxld v{a, b, c};
    EXPECT_EQ(v[0], GSL::Complex_ld{1.l});
    EXPECT_EQ(v[1], GSL::Complex_ld{2.l});
    EXPECT_EQ(v[2], GSL::Complex_ld{3.l});
}

TEST(Vector_cxldTest, TestConstructionCopy)
{
    GSL::Complex_ld a = 1.l, b = 2.l, c = 3.l;
    GSL::Vector_cxld v1{a, b, c};
    GSL::Vector_cxld v2{v1};
    EXPECT_EQ(v1[0], GSL::Complex_ld{v2[0]});
    EXPECT_EQ(v1[1], GSL::Complex_ld{v2[1]});
    EXPECT_EQ(v1[2], GSL::Complex_ld{v2[2]});
}

TEST(Vector_cxldTest, TestConstructionMove)
{
    GSL::Complex_ld a = 1.l, b = 2.l, c = 3.l;
    GSL::Vector_cxld v1{a, b, c};
    GSL::Vector_cxld v2{std::move(v1)};
    EXPECT_EQ(v2[0], GSL::Complex_ld{1.l});
    EXPECT_EQ(v2[1], GSL::Complex_ld{2.l});
    EXPECT_EQ(v2[2], GSL::Complex_ld{3.l});
}

TEST(Vector_cxldTest, TestEqual)
{

    GSL::Complex_ld a = 1.l, b = 2.l, c = 3.l;
    GSL::Vector_cxld v1{a, b, c};
    GSL::Vector_cxld v2{v1};

    EXPECT_EQ(v1, v2);
}

TEST(Vector_cxldTest, TestNotEqual)
{

    GSL::Complex_ld a = 1.l, b = 2.l, c = 3.l;
    GSL::Vector_cxld v1{a, b, c};
    GSL::Vector_cxld v2{a +1, b, c};

    EXPECT_NE(v1, v2);
}

TEST(Vector_cxldTest, TestCopy)
{

    GSL::Complex_ld a = 1.l, b = 2.l, c = 3.l;
    GSL::Vector_cxld v1{a, b, c};
    GSL::Vector_cxld v2;
    v2 = v1;

    EXPECT_EQ(v1, v2);
}

TEST(Vector_cxldTest, TestMove)
{

    GSL::Complex_ld a = 1.l, b = 2.l, c = 3.l;
    GSL::Vector_cxld v1{a, b, c}, v1s{a, b, c};
    GSL::Vector_cxld v2;
    v2 = std::move(v1);

    EXPECT_EQ(v2, v1s);
}

TEST(Vector_cxldTest, TestDecayToGSLVector_cxld)
{
    GSL::Complex_ld a = 1.l, b = 2.l, c = 3.l;
    GSL::Vector_cxld v{a, b, c};
    gsl_vector_complex_long_double gv = v;

    EXPECT_EQ(gsl_vector_complex_long_double_get(&gv, 0), a);
}

TEST(Vector_cxldTest, TestSize)
{
    GSL::Complex_ld a = 1.l, b = 2.l, c = 3.l;
    GSL::Vector_cxld v{a, b, c};

    EXPECT_EQ(v.size(), 3);
}

TEST(Vector_cxldTest, TestDim)
{
    GSL::Complex_ld a = 1.l, b = 2.l, c = 3.l;
    GSL::Vector_cxld v{a, b, c};

    EXPECT_EQ(v.dim(), 3);
}

TEST(Vector_cxldTest, TestCopyFun)
{
    GSL::Complex_ld a = 1.l, b = 2.l, c = 3.l;
    GSL::Vector_cxld v{a, b, c}, v2;
    v2.copy(v);

    EXPECT_EQ(v, v2);
}

TEST(Vector_cxldTest, TestNorm)
{
    GSL::Complex_ld a = 1.l, b = 2.l, c = 3.l;
    GSL::Vector_cxld v{a, b, c};

    EXPECT_EQ(v.norm<long double>(), std::sqrt(a.re()*a.re() + b.re()*b.re() + c.re()*c.re()));
}

TEST(Vector_cxldTest, TestNormalize)
{
    GSL::Complex_ld a = 1.l, b = 2.l, c = 3.l;
    GSL::Vector_cxld v{a, b, c};
    v.normalize<long double>();
    long double diff = std::abs(v.norm<long double>() - 1.l);
    EXPECT_TRUE( diff < 1e-10l);
}

TEST(Vector_cxldTest, TestDot)
{
    GSL::Vector_cxld v1{1.l, 0.l, 0.l}, v2{0.l, 1.l, 0.l};

    EXPECT_EQ(v1.dot(v2), GSL::Complex_ld{0.l});
}

TEST(Vector_cxldTest, TestCross)
{
    GSL::Vector_cxld v1{1.l, 0.l, 0.l}, v2{0.l, 1.l, 0.l}, v3{0.l, 0.l, 1.l};

    EXPECT_EQ(v1.cross(v2), v3);
}

TEST(Vector_cxldTest, TestIncrement)
{
    GSL::Vector_cxld v1{1.l, 0.l, 0.l}, v2{0.l, 1.l, 0.l}, v3{1.l, 1.l, 0.l};

    EXPECT_EQ(v1 += v2, v3);
}

TEST(Vector_cxldTest, TestDecrement)
{
    GSL::Vector_cxld v1{1.l, 0.l, 0.l}, v2{0.l, 1.l, 0.l}, v3{1.l, -1.l, 0.l};

    EXPECT_EQ(v1 -= v2, v3);
}

TEST(Vector_cxldTest, TestElMultScale)
{
    GSL::Vector_cxld v1{3.l, 2.l, 2.l}, v2{2.l, 3.l, 4.l}, v3{6.l, 6.l, 8.l};

    EXPECT_EQ(v1 *= v2, v3);
}

TEST(Vector_cxldTest, TestElDivScale)
{
    GSL::Vector_cxld v1{8.l, 4.l, 2.l}, v2{6.l, 3.l, 2.l}, v3{8.l/6, 4.l/3, 2.l/2};

    v1 /= v2;
    long double diff = std::abs(v1.norm<long double>() - v3.norm<long double>());
    EXPECT_TRUE(diff < 1e-10l);
}

TEST(Vector_cxldTest, TestMultScale)
{
    GSL::Vector_cxld v1{3.l, 2.l, 2.l}, v2{9.l, 6.l, 6.l};

    EXPECT_EQ(v1 *= GSL::Complex_ld{3}, v2);
}

TEST(Vector_cxldTest, TestDivScale)
{
    GSL::Vector_cxld v1{8.l, 4.l, 2.l}, v2{4.l, 2.l, 1.l};
    v1 /= GSL::Complex_ld{2.l};

    EXPECT_EQ(v1, v2);
}

TEST(Vector_cxldTest, TestAddition)
{
    GSL::Vector_cxld v1{1.l, 0.l, 0.l}, v2{0.l, 1.l, 0.l}, v3{1.l, 1.l, 0.l};

    EXPECT_EQ(v1 + v2, v3);
}

TEST(Vector_cxldTest, TestSubtraction)
{
    GSL::Vector_cxld v1{1.l, 0.l, 0.l}, v2{0.l, 1.l, 0.l}, v3{1.l, -1.l, 0.l};

    EXPECT_EQ(v1 - v2, v3);
}

TEST(Vector_cxldTest, TestElMult)
{
    GSL::Vector_cxld v1{3.l, 2.l, 2.l}, v2{2.l, 3.l, 4.l}, v3{6.l, 6.l, 8.l};

    EXPECT_EQ(v1 * v2, v3);
}

TEST(Vector_cxldTest, TestElDiv)
{
    GSL::Vector_cxld v1{8.l, 4.l, 2.l}, v2{6.l, 3.l, 2.l}, v3{8.l/6, 4.l/3, 2.l/2};

    long double diff = std::abs((v1 / v2).norm<long double>() - v3.norm<long double>());
    EXPECT_TRUE(diff < 1e-10l);
}

TEST(Vector_cxldTest, TestScalarMult)
{
    GSL::Vector_cxld v1{3.l, 2.l, 2.l}, v2{9.l, 6.l, 6.l};

    EXPECT_EQ(v1 * GSL::Complex_ld(3.l), v2);
}

TEST(Vector_cxldTest, TestScalarDiv)
{
    GSL::Vector_cxld v1{8.l, 4.l, 2.l}, v2{4.l, 2.l, 1.l};

    EXPECT_EQ(v1 / GSL::Complex_ld(2.l), v2);
}

TEST(Vector_cxldTest, TestScalarMult2)
{
    GSL::Vector_cxld v1{3.l, 2.l, 2.l}, v2{9.l, 6.l, 6.l};

    EXPECT_EQ(GSL::Complex_ld(3.l) * v1, v2);
}

TEST(Vector_cxldTest, TestBegin)
{
    GSL::Vector_cxld v{1.l, 2.l, 3.l};
    EXPECT_EQ(*v.begin(), GSL::Complex_ld{1.l});
}

TEST(Vector_cxldTest, TestcBegin)
{
    GSL::Vector_cxld v{1.l, 2.l, 3.l};
    EXPECT_EQ(*v.cbegin(), GSL::Complex_ld{1.l});
}

TEST(Vector_cxldTest, TestIterPreIncrement)
{
    GSL::Vector_cxld v{1.l, 2.l, 3.l};
    EXPECT_EQ(*++v.begin(), GSL::Complex_ld{2.l});
}

TEST(Vector_cxldTest, TestIterPostIncrement)
{
    GSL::Vector_cxld v{1.l, 2.l, 3.l};
    auto it = v.begin();
    it++;
    EXPECT_EQ(*it, GSL::Complex_ld{2.l});
}

TEST(Vector_cxldTest, TestIterPreDecrement)
{
    GSL::Vector_cxld v{1.l, 2.l, 3.l};
    EXPECT_EQ(*--(++v.begin()), GSL::Complex_ld{1.l});
}

TEST(Vector_cxldTest, TestIterPostDecrement)
{
    GSL::Vector_cxld v{1.l, 2.l, 3.l};
    auto it = v.begin();
    it++; it--;
    EXPECT_EQ(*it, GSL::Complex_ld{1.l});
}

TEST(Vector_cxldTest, TestIterStepIncrement)
{
    GSL::Vector_cxld v{1.l, 2.l, 3.l};
    auto it = v.begin();
    it += 2;
    EXPECT_EQ(*it, GSL::Complex_ld{3.l});
}

TEST(Vector_cxldTest, TestIterStep)
{
    GSL::Vector_cxld v{1.l, 2.l, 3.l};
    auto it = v.begin();
    EXPECT_EQ(*(it + 2), GSL::Complex_ld{3.l});
}

TEST(Vector_cxldTest, TestIterStepDecrement)
{
    GSL::Vector_cxld v{1.l, 2.l, 3.l};
    auto it = v.begin();
    it += 2;
    it -= 2;
    EXPECT_EQ(*it, GSL::Complex_ld{1.l});
}

TEST(Vector_cxldTest, TestIterStepBack)
{
    GSL::Vector_cxld v{1.l, 2.l, 3.l};
    auto it = v.begin() + 2;
    EXPECT_EQ(*(it - 2), GSL::Complex_ld{1.l});
}

TEST(Vector_cxldTest, TestIterDiff)
{
    GSL::Vector_cxld v{1.l, 2.l, 3.l};
    auto it = v.begin() + 2;
    EXPECT_EQ(it - v.begin(), 2.l);
}

TEST(Vector_cxldTest, TestIterEq)
{
    GSL::Vector_cxld v{1.l, 2.l, 3.l};
    auto it1 = v.begin() + 2;
    auto it2 = v.begin();
    it2 += 2;

    EXPECT_EQ(it1, it2);
}

TEST(Vector_cxldTest, TestIterNeq)
{
    GSL::Vector_cxld v{1.l, 2.l, 3.l};
    auto it1 = v.begin() + 2;
    auto it2 = v.begin();

    EXPECT_NE(it1, it2);
}

TEST(Vector_cxldTest, TestEnd)
{
    GSL::Vector_cxld v{1.l, 2.l, 3.l};
    auto it1 = v.begin() + 2;
    auto it2 = v.end();

    EXPECT_EQ(it1, --it2);
}

TEST(Vector_cxldTest, TestcIterPreIncrement)
{
    GSL::Vector_cxld v{1.l, 2.l, 3.l};
    EXPECT_EQ(*++v.cbegin(), GSL::Complex_ld{2.l});
}

TEST(Vector_cxldTest, TestcIterPostIncrement)
{
    GSL::Vector_cxld v{1.l, 2.l, 3.l};
    auto it = v.cbegin();
    it++;
    EXPECT_EQ(*it, GSL::Complex_ld{2.l});
}

TEST(Vector_cxldTest, TestcIterPreDecrement)
{
    GSL::Vector_cxld v{1.l, 2.l, 3.l};
    EXPECT_EQ(*--(++v.cbegin()), GSL::Complex_ld{1.l});
}

TEST(Vector_cxldTest, TestcIterPostDecrement)
{
    GSL::Vector_cxld v{1.l, 2.l, 3.l};
    auto it = v.cbegin();
    it++; it--;
    EXPECT_EQ(*it, GSL::Complex_ld{1.l});
}

TEST(Vector_cxldTest, TestcIterStepIncrement)
{
    GSL::Vector_cxld v{1.l, 2.l, 3.l};
    auto it = v.cbegin();
    it += 2;
    EXPECT_EQ(*it, GSL::Complex_ld{3.l});
}

TEST(Vector_cxldTest, TestcIterStep)
{
    GSL::Vector_cxld v{1.l, 2.l, 3.l};
    auto it = v.cbegin();
    EXPECT_EQ(*(it + 2), GSL::Complex_ld{3.l});
}

TEST(Vector_cxldTest, TestcIterStepDecrement)
{
    GSL::Vector_cxld v{1.l, 2.l, 3.l};
    auto it = v.cbegin();
    it += 2;
    it -= 2;
    EXPECT_EQ(*it, GSL::Complex_ld{1.l});
}

TEST(Vector_cxldTest, TestcIterStepBack)
{
    GSL::Vector_cxld v{1.l, 2.l, 3.l};
    auto it = v.cbegin() + 2;
    EXPECT_EQ(*(it - 2), GSL::Complex_ld{1.l});
}

TEST(Vector_cxldTest, TestcIterDiff)
{
    GSL::Vector_cxld v{1.l, 2.l, 3.l};
    auto it = v.cbegin() + 2;
    EXPECT_EQ(it - v.cbegin(), 2.l);
}

TEST(Vector_cxldTest, TestcIterEq)
{
    GSL::Vector_cxld v{1.l, 2.l, 3.l};
    auto it1 = v.cbegin() + 2;
    auto it2 = v.cbegin();
    it2 += 2;

    EXPECT_EQ(it1, it2);
}

TEST(Vector_cxldTest, TestcIterNeq)
{
    GSL::Vector_cxld v{1.l, 2.l, 3.l};
    auto it1 = v.cbegin() + 2;
    auto it2 = v.cbegin();

    EXPECT_NE(it1, it2);
}

TEST(Vector_cxldTest, TestcEnd)
{
    GSL::Vector_cxld v{1.l, 2.l, 3.l};
    auto it1 = v.cbegin() + 2;
    auto it2 = v.cend();

    EXPECT_EQ(it1, --it2);
}

TEST(Vector_cxldTest, TestRbegin)
{
    GSL::Vector_cxld v{1.l, 2.l, 3.l};
    auto it1 = v.rbegin();

    EXPECT_EQ(*it1, GSL::Complex_ld{3.l});
}

TEST(Vector_cxldTest, TestRend)
{
    GSL::Vector_cxld v{1.l, 2.l, 3.l};
    auto it1 = v.rend();

    EXPECT_EQ(*--it1, GSL::Complex_ld{1.l});
}

TEST(Vector_cxldTest, TestcRbegin)
{
    GSL::Vector_cxld v{1.l, 2.l, 3.l};
    auto it1 = v.crbegin();

    EXPECT_EQ(*it1, GSL::Complex_ld{3.l});
}

TEST(Vector_cxldTest, TestcRend)
{
    GSL::Vector_cxld v{1.l, 2.l, 3.l};
    auto it1 = v.crend();

    EXPECT_EQ(*--it1, GSL::Complex_ld{1.l});
}

TEST(Vector_cxldTest, TestFront)
{
    GSL::Vector_cxld v{1.l, 2.l, 3.l};
    EXPECT_EQ(v.front(), GSL::Complex_ld{1.l});
}

TEST(Vector_cxldTest, TestBack)
{
    GSL::Vector_cxld v{1.l, 2.l, 3.l};
    EXPECT_EQ(v.back(), GSL::Complex_ld{3.l});
}

TEST(Vector_cxldTest, TestAt)
{
    GSL::Vector_cxld v{1.l, 2.l, 3.l};
    EXPECT_EQ(v.at(1), GSL::Complex_ld{2.l});
}

TEST(Vector_cxldTest, TestAssign1)
{
    GSL::Vector_cxld v1{1.l, 2.l, 3.l};
    GSL::Vector_cxld v2{3.l, 4.l, 5.l};
    v2.assign(v1.begin(), v1.end());
    EXPECT_EQ(v1, v2);
}

TEST(Vector_cxldTest, TestAssign2)
{
    GSL::Vector_cxld v1{1.l, 2.l, 3.l};
    GSL::Vector_cxld v2{3.l, 3.l, 3.l, 3.l};
    v1.assign(4, GSL::Complex_ld(3.l));
    EXPECT_EQ(v1, v2);
}

TEST(Vector_cxldTest, TestAssign3)
{
    GSL::Vector_cxld v1{1.l, 2.l, 3.l};
    GSL::Vector_cxld v2{3.l, 4.l};
    v1.assign({{3.l}, {4.l}});
    EXPECT_EQ(v1, v2);
}
