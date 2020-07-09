#include "GSLpp/vector.h"
#include <gtest/gtest.h>
#include <iostream>
#include <cmath>

TEST(Vector_ldTest, TestConstruction)
{
    GSL::Vector_ld v(3);
    EXPECT_EQ(v[0], 0.l);
    EXPECT_EQ(v[1], 0.l);
    EXPECT_EQ(v[2], 0.l);
}

TEST(Vector_ldTest, TestConstructionInitializerList)
{
    long double a = 1.l, b = 2.l, c = 3.l;
    GSL::Vector_ld v{a, b, c};
    EXPECT_EQ(v[0], 1.l);
    EXPECT_EQ(v[1], 2.l);
    EXPECT_EQ(v[2], 3.l);
}

TEST(Vector_ldTest, TestConstructionCopy)
{
    long double a = 1.l, b = 2.l, c = 3.l;
    GSL::Vector_ld v1{a, b, c};
    GSL::Vector_ld v2{v1};
    EXPECT_EQ(v1[0], v2[0]);
    EXPECT_EQ(v1[1], v2[1]);
    EXPECT_EQ(v1[2], v2[2]);
}

TEST(Vector_ldTest, TestConstructionMove)
{
    long double a = 1.l, b = 2.l, c = 3.l;
    GSL::Vector_ld v1{a, b, c};
    GSL::Vector_ld v2{std::move(v1)};
    EXPECT_EQ(v2[0], 1.l);
    EXPECT_EQ(v2[1], 2.l);
    EXPECT_EQ(v2[2], 3.l);
}

TEST(Vector_ldTest, TestEqual)
{

    long double a = 1.l, b = 2.l, c = 3.l;
    GSL::Vector_ld v1{a, b, c};
    GSL::Vector_ld v2{v1};

    EXPECT_EQ(v1, v2);
}

TEST(Vector_ldTest, TestNotEqual)
{

    long double a = 1.l, b = 2.l, c = 3.l;
    GSL::Vector_ld v1{a, b, c};
    GSL::Vector_ld v2{a +1, b, c};

    EXPECT_NE(v1, v2);
}

TEST(Vector_ldTest, TestCopy)
{

    long double a = 1.l, b = 2.l, c = 3.l;
    GSL::Vector_ld v1{a, b, c};
    GSL::Vector_ld v2;
    v2 = v1;

    EXPECT_EQ(v1, v2);
}

TEST(Vector_ldTest, TestMove)
{

    long double a = 1.l, b = 2.l, c = 3.l;
    GSL::Vector_ld v1{a, b, c}, v1s{a, b, c};
    GSL::Vector_ld v2;
    v2 = std::move(v1);

    EXPECT_EQ(v2, v1s);
}

TEST(Vector_ldTest, TestDecayToGSLVector_ld)
{
    long double a = 1.l, b = 2.l, c = 3.l;
    GSL::Vector_ld v{a, b, c};
    gsl_vector_long_double gv = v;

    EXPECT_EQ(gsl_vector_long_double_get(&gv, 0), a);
}

TEST(Vector_ldTest, TestSize)
{
    long double a = 1.l, b = 2.l, c = 3.l;
    GSL::Vector_ld v{a, b, c};

    EXPECT_EQ(v.size(), 3);
}

TEST(Vector_ldTest, TestDim)
{
    long double a = 1.l, b = 2.l, c = 3.l;
    GSL::Vector_ld v{a, b, c};

    EXPECT_EQ(v.dim(), 3);
}

TEST(Vector_ldTest, TestCopyFun)
{
    long double a = 1.l, b = 2.l, c = 3.l;
    GSL::Vector_ld v{a, b, c}, v2;
    v2.copy(v);

    EXPECT_EQ(v, v2);
}

TEST(Vector_ldTest, TestNorm)
{
    long double a = 1.l, b = 2.l, c = 3.l;
    GSL::Vector_ld v{a, b, c};

    EXPECT_EQ(v.norm<long double>(), std::sqrt(a*a + b*b + c*c));
}

TEST(Vector_ldTest, TestNormalize)
{
    long double a = 1.l, b = 2.l, c = 3.l;
    GSL::Vector_ld v{a, b, c};
    v.normalize<long double>();
    long double diff = std::abs(v.norm<long double>() - 1.l);

    EXPECT_TRUE(diff < 1e-10l);
}

TEST(Vector_ldTest, TestDot)
{
    GSL::Vector_ld v1{1.l, 0.l, 0.l}, v2{0.l, 1.l, 0.l};

    EXPECT_EQ(v1.dot(v2), 0.l);
}

TEST(Vector_ldTest, TestCross)
{
    GSL::Vector_ld v1{1.l, 0.l, 0.l}, v2{0.l, 1.l, 0.l}, v3{0.l, 0.l, 1.l};

    EXPECT_EQ(v1.cross(v2), v3);
}

TEST(Vector_ldTest, TestIncrement)
{
    GSL::Vector_ld v1{1.l, 0.l, 0.l}, v2{0.l, 1.l, 0.l}, v3{1.l, 1.l, 0.l};

    EXPECT_EQ(v1 += v2, v3);
}

TEST(Vector_ldTest, TestDecrement)
{
    GSL::Vector_ld v1{1.l, 0.l, 0.l}, v2{0.l, 1.l, 0.l}, v3{1.l, -1.l, 0.l};

    EXPECT_EQ(v1 -= v2, v3);
}

TEST(Vector_ldTest, TestElMultScale)
{
    GSL::Vector_ld v1{3.l, 2.l, 2.l}, v2{2.l, 3.l, 4.l}, v3{6.l, 6.l, 8.l};

    EXPECT_EQ(v1 *= v2, v3);
}

TEST(Vector_ldTest, TestElDivScale)
{
    GSL::Vector_ld v1{8.l, 4.l, 2.l}, v2{6.l, 3.l, 2.l}, v3{8.l/6, 4.l/3, 2.l/2};

    EXPECT_EQ((v1 /= v2).norm<long double>(), v3.norm<long double>());
}

TEST(Vector_ldTest, TestMultScale)
{
    GSL::Vector_ld v1{3.l, 2.l, 2.l}, v2{9.l, 6.l, 6.l};

    EXPECT_EQ(v1 *= 3, v2);
}

TEST(Vector_ldTest, TestDivScale)
{
    GSL::Vector_ld v1{8.l, 4.l, 2.l}, v2{4.l, 2.l, 1.l};

    EXPECT_EQ((v1 /= 2).norm<long double>(), v2.norm<long double>());
}

TEST(Vector_ldTest, TestAddition)
{
    GSL::Vector_ld v1{1.l, 0.l, 0.l}, v2{0.l, 1.l, 0.l}, v3{1.l, 1.l, 0.l};

    EXPECT_EQ(v1 + v2, v3);
}

TEST(Vector_ldTest, TestSubtraction)
{
    GSL::Vector_ld v1{1.l, 0.l, 0.l}, v2{0.l, 1.l, 0.l}, v3{1.l, -1.l, 0.l};

    EXPECT_EQ(v1 - v2, v3);
}

TEST(Vector_ldTest, TestElMult)
{
    GSL::Vector_ld v1{3.l, 2.l, 2.l}, v2{2.l, 3.l, 4.l}, v3{6.l, 6.l, 8.l};

    EXPECT_EQ(v1 * v2, v3);
}

TEST(Vector_ldTest, TestElDiv)
{
    GSL::Vector_ld v1{8.l, 4.l, 2.l}, v2{6.l, 3.l, 2.l}, v3{8.l/6, 4.l/3, 2.l/2};

    EXPECT_EQ((v1 / v2).norm<long double>(), v3.norm<long double>());
}

TEST(Vector_ldTest, TestScalarMult)
{
    GSL::Vector_ld v1{3.l, 2.l, 2.l}, v2{9.l, 6.l, 6.l};

    EXPECT_EQ(v1 * 3.l, v2);
}

TEST(Vector_ldTest, TestScalarDiv)
{
    GSL::Vector_ld v1{8.l, 4.l, 2.l}, v2{4.l, 2.l, 1.l};

    EXPECT_EQ(v1 / 2.l, v2);
}

TEST(Vector_ldTest, TestScalarMult2)
{
    GSL::Vector_ld v1{3.l, 2.l, 2.l}, v2{9.l, 6.l, 6.l};

    EXPECT_EQ(3.l * v1, v2);
}

TEST(Vector_ldTest, TestBegin)
{
    GSL::Vector_ld v{1.l, 2.l, 3.l};
    EXPECT_EQ(*v.begin(), 1.l);
}

TEST(Vector_ldTest, TestcBegin)
{
    GSL::Vector_ld v{1.l, 2.l, 3.l};
    EXPECT_EQ(*v.cbegin(), 1.l);
}

TEST(Vector_ldTest, TestIterPreIncrement)
{
    GSL::Vector_ld v{1.l, 2.l, 3.l};
    EXPECT_EQ(*++v.begin(), 2.l);
}

TEST(Vector_ldTest, TestIterPostIncrement)
{
    GSL::Vector_ld v{1.l, 2.l, 3.l};
    auto it = v.begin();
    it++;
    EXPECT_EQ(*it, 2.l);
}

TEST(Vector_ldTest, TestIterPreDecrement)
{
    GSL::Vector_ld v{1.l, 2.l, 3.l};
    EXPECT_EQ(*--(++v.begin()), 1.l);
}

TEST(Vector_ldTest, TestIterPostDecrement)
{
    GSL::Vector_ld v{1.l, 2.l, 3.l};
    auto it = v.begin();
    it++; it--;
    EXPECT_EQ(*it, 1.l);
}

TEST(Vector_ldTest, TestIterStepIncrement)
{
    GSL::Vector_ld v{1.l, 2.l, 3.l};
    auto it = v.begin();
    it += 2;
    EXPECT_EQ(*it, 3.l);
}

TEST(Vector_ldTest, TestIterStep)
{
    GSL::Vector_ld v{1.l, 2.l, 3.l};
    auto it = v.begin();
    EXPECT_EQ(*(it + 2), 3.l);
}

TEST(Vector_ldTest, TestIterStepDecrement)
{
    GSL::Vector_ld v{1.l, 2.l, 3.l};
    auto it = v.begin();
    it += 2;
    it -= 2;
    EXPECT_EQ(*it, 1.l);
}

TEST(Vector_ldTest, TestIterStepBack)
{
    GSL::Vector_ld v{1.l, 2.l, 3.l};
    auto it = v.begin() + 2;
    EXPECT_EQ(*(it - 2), 1.l);
}

TEST(Vector_ldTest, TestIterDiff)
{
    GSL::Vector_ld v{1.l, 2.l, 3.l};
    auto it = v.begin() + 2;
    EXPECT_EQ(it - v.begin(), 2.l);
}

TEST(Vector_ldTest, TestIterEq)
{
    GSL::Vector_ld v{1.l, 2.l, 3.l};
    auto it1 = v.begin() + 2;
    auto it2 = v.begin();
    it2 += 2;

    EXPECT_EQ(it1, it2);
}

TEST(Vector_ldTest, TestIterNeq)
{
    GSL::Vector_ld v{1.l, 2.l, 3.l};
    auto it1 = v.begin() + 2;
    auto it2 = v.begin();

    EXPECT_NE(it1, it2);
}

TEST(Vector_ldTest, TestEnd)
{
    GSL::Vector_ld v{1.l, 2.l, 3.l};
    auto it1 = v.begin() + 2;
    auto it2 = v.end();

    EXPECT_EQ(it1, --it2);
}

TEST(Vector_ldTest, TestcIterPreIncrement)
{
    GSL::Vector_ld v{1.l, 2.l, 3.l};
    EXPECT_EQ(*++v.cbegin(), 2.l);
}

TEST(Vector_ldTest, TestcIterPostIncrement)
{
    GSL::Vector_ld v{1.l, 2.l, 3.l};
    auto it = v.cbegin();
    it++;
    EXPECT_EQ(*it, 2.l);
}

TEST(Vector_ldTest, TestcIterPreDecrement)
{
    GSL::Vector_ld v{1.l, 2.l, 3.l};
    EXPECT_EQ(*--(++v.cbegin()), 1.l);
}

TEST(Vector_ldTest, TestcIterPostDecrement)
{
    GSL::Vector_ld v{1.l, 2.l, 3.l};
    auto it = v.cbegin();
    it++; it--;
    EXPECT_EQ(*it, 1.l);
}

TEST(Vector_ldTest, TestcIterStepIncrement)
{
    GSL::Vector_ld v{1.l, 2.l, 3.l};
    auto it = v.cbegin();
    it += 2;
    EXPECT_EQ(*it, 3.l);
}

TEST(Vector_ldTest, TestcIterStep)
{
    GSL::Vector_ld v{1.l, 2.l, 3.l};
    auto it = v.cbegin();
    EXPECT_EQ(*(it + 2), 3.l);
}

TEST(Vector_ldTest, TestcIterStepDecrement)
{
    GSL::Vector_ld v{1.l, 2.l, 3.l};
    auto it = v.cbegin();
    it += 2;
    it -= 2;
    EXPECT_EQ(*it, 1.l);
}

TEST(Vector_ldTest, TestcIterStepBack)
{
    GSL::Vector_ld v{1.l, 2.l, 3.l};
    auto it = v.cbegin() + 2;
    EXPECT_EQ(*(it - 2), 1.l);
}

TEST(Vector_ldTest, TestcIterDiff)
{
    GSL::Vector_ld v{1.l, 2.l, 3.l};
    auto it = v.cbegin() + 2;
    EXPECT_EQ(it - v.cbegin(), 2.l);
}

TEST(Vector_ldTest, TestcIterEq)
{
    GSL::Vector_ld v{1.l, 2.l, 3.l};
    auto it1 = v.cbegin() + 2;
    auto it2 = v.cbegin();
    it2 += 2;

    EXPECT_EQ(it1, it2);
}

TEST(Vector_ldTest, TestcIterNeq)
{
    GSL::Vector_ld v{1.l, 2.l, 3.l};
    auto it1 = v.cbegin() + 2;
    auto it2 = v.cbegin();

    EXPECT_NE(it1, it2);
}

TEST(Vector_ldTest, TestcEnd)
{
    GSL::Vector_ld v{1.l, 2.l, 3.l};
    auto it1 = v.cbegin() + 2;
    auto it2 = v.cend();

    EXPECT_EQ(it1, --it2);
}

TEST(Vector_ldTest, TestRbegin)
{
    GSL::Vector_ld v{1.l, 2.l, 3.l};
    auto it1 = v.rbegin();

    EXPECT_EQ(*it1, 3.l);
}

TEST(Vector_ldTest, TestRend)
{
    GSL::Vector_ld v{1.l, 2.l, 3.l};
    auto it1 = v.rend();

    EXPECT_EQ(*--it1, 1.l);
}

TEST(Vector_ldTest, TestcRbegin)
{
    GSL::Vector_ld v{1.l, 2.l, 3.l};
    auto it1 = v.crbegin();

    EXPECT_EQ(*it1, 3.l);
}

TEST(Vector_ldTest, TestcRend)
{
    GSL::Vector_ld v{1.l, 2.l, 3.l};
    auto it1 = v.crend();

    EXPECT_EQ(*--it1, 1.l);
}

TEST(Vector_ldTest, TestFront)
{
    GSL::Vector_ld v{1.l, 2.l, 3.l};
    EXPECT_EQ(v.front(), 1.l);
}

TEST(Vector_ldTest, TestBack)
{
    GSL::Vector_ld v{1.l, 2.l, 3.l};
    EXPECT_EQ(v.back(), 3.l);
}

TEST(Vector_ldTest, TestAt)
{
    GSL::Vector_ld v{1.l, 2.l, 3.l};
    EXPECT_EQ(v.at(1), 2.l);
}

TEST(Vector_ldTest, TestAssign1)
{
    GSL::Vector_ld v1{1.l, 2.l, 3.l};
    GSL::Vector_ld v2{3.l, 4.l, 5.l};
    v2.assign(v1.begin(), v1.end());
    EXPECT_EQ(v1, v2);
}

TEST(Vector_ldTest, TestAssign2)
{
    GSL::Vector_ld v1{1.l, 2.l, 3.l};
    GSL::Vector_ld v2{3.l, 3.l, 3.l, 3.l};
    v1.assign(4, 3.l);
    EXPECT_EQ(v1, v2);
}

TEST(Vector_ldTest, TestAssign3)
{
    GSL::Vector_ld v1{1.l, 2.l, 3.l};
    GSL::Vector_ld v2{3.l, 4.l};
    v1.assign({3.l, 4.l});
    EXPECT_EQ(v1, v2);
}
