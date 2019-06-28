#include "GSLpp/vector.h"
#include <gtest/gtest.h>
#include <iostream>

TEST(Vector_cTest, TestConstruction)
{
    GSL::Vector_c v(3);
    EXPECT_EQ(v[0], 0);
    EXPECT_EQ(v[1], 0);
    EXPECT_EQ(v[2], 0);
}

TEST(Vector_cTest, TestConstructionInitializerList)
{
    char a = 1, b = 2, c = 3;
    GSL::Vector_c v{a, b, c};
    EXPECT_EQ(v[0], 1);
    EXPECT_EQ(v[1], 2);
    EXPECT_EQ(v[2], 3);
}

TEST(Vector_cTest, TestConstructionCopy)
{
    char a = 1, b = 2, c = 3;
    GSL::Vector_c v1{a, b, c};
    GSL::Vector_c v2{v1};
    EXPECT_EQ(v1[0], v2[0]);
    EXPECT_EQ(v1[1], v2[1]);
    EXPECT_EQ(v1[2], v2[2]);
}

TEST(Vector_cTest, TestConstructionMove)
{
    char a = 1, b = 2, c = 3;
    GSL::Vector_c v1{a, b, c};
    GSL::Vector_c v2{std::move(v1)};
    EXPECT_EQ(v2[0], 1);
    EXPECT_EQ(v2[1], 2);
    EXPECT_EQ(v2[2], 3);
}

TEST(Vector_cTest, TestEqual)
{

    char a = 1, b = 2, c = 3;
    GSL::Vector_c v1{a, b, c};
    GSL::Vector_c v2{v1};

    EXPECT_EQ(v1, v2);
}

TEST(Vector_cTest, TestNotEqual)
{

    char a = 1, b = 2, c = 3;
    GSL::Vector_c v1{a, b, c};
    GSL::Vector_c v2{static_cast<char>(a + 1), b, c};

    EXPECT_NE(v1, v2);
}

TEST(Vector_cTest, TestCopy)
{

    char a = 1, b = 2, c = 3;
    GSL::Vector_c v1{a, b, c};
    GSL::Vector_c v2;
    v2 = v1;

    EXPECT_EQ(v1, v2);
}

TEST(Vector_cTest, TestMove)
{

    char a = 1, b = 2, c = 3;
    GSL::Vector_c v1{a, b, c}, v1s{a, b, c};
    GSL::Vector_c v2;
    v2 = std::move(v1);

    EXPECT_EQ(v2, v1s);
}

TEST(Vector_cTest, TestDecayToGSLVector_c)
{
    char a = 1, b = 2, c = 3;
    GSL::Vector_c v{a, b, c};
    gsl_vector_char gv = v;

    EXPECT_EQ(gsl_vector_char_get(&gv, 0), a);
}

TEST(Vector_cTest, TestSize)
{
    char a = 1, b = 2, c = 3;
    GSL::Vector_c v{a, b, c};

    EXPECT_EQ(v.size(), 3);
}

TEST(Vector_cTest, TestDim)
{
    char a = 1, b = 2, c = 3;
    GSL::Vector_c v{a, b, c};

    EXPECT_EQ(v.dim(), 3);
}

TEST(Vector_cTest, TestCopyFun)
{
    char a = 1, b = 2, c = 3;
    GSL::Vector_c v{a, b, c}, v2;
    v2.copy(v);

    EXPECT_EQ(v, v2);
}

TEST(Vector_cTest, TestNorm)
{
    char a = 1, b = 2, c = 3;
    GSL::Vector_c v{a, b, c};

    EXPECT_DOUBLE_EQ(v.norm<double>(), std::sqrt(a*a + b*b + c*c));
}

TEST(Vector_cTest, TestNormalize)
{
    char a = 1, b = 2, c = 3;
    GSL::Vector_c v{a, b, c};
    v.normalize<char>();

    EXPECT_DOUBLE_EQ(v.norm<double>(), 1);
}

TEST(Vector_cTest, TestDot)
{
    GSL::Vector_c v1{1, 0, 0}, v2{0, 1, 0};

    EXPECT_EQ(v1.dot(v2), 0);
}

TEST(Vector_cTest, TestCross)
{
    GSL::Vector_c v1{1, 0, 0}, v2{0, 1, 0}, v3{0, 0, 1};

    EXPECT_EQ(v1.cross(v2), v3);
}

TEST(Vector_cTest, TestIncrement)
{
    GSL::Vector_c v1{1, 0, 0}, v2{0, 1, 0}, v3{1, 1, 0};

    EXPECT_EQ(v1 += v2, v3);
}

TEST(Vector_cTest, TestDecrement)
{
    GSL::Vector_c v1{1, 0, 0}, v2{0, 1, 0}, v3{1, -1, 0};

    EXPECT_EQ(v1 -= v2, v3);
}

TEST(Vector_cTest, TestElMultScale)
{
    GSL::Vector_c v1{3, 2, 2}, v2{2, 3, 4}, v3{6, 6, 8};

    EXPECT_EQ(v1 *= v2, v3);
}

TEST(Vector_cTest, TestElDivScale)
{
    GSL::Vector_c v1{8, 4, 2}, v2{6, 3, 2}, v3{8/6, 4/3, 2/2};

    EXPECT_EQ(v1 /= v2, v3);
}

TEST(Vector_cTest, TestMultScale)
{
    GSL::Vector_c v1{3, 2, 2}, v2{9, 6, 6};

    EXPECT_EQ(v1 *= 3, v2);
}

TEST(Vector_cTest, TestDivScale)
{
    GSL::Vector_c v1{8, 4, 2}, v2{4, 2, 1};

    EXPECT_EQ(v1 /= 2, v2);
}

TEST(Vector_cTest, TestAddition)
{
    GSL::Vector_c v1{1, 0, 0}, v2{0, 1, 0}, v3{1, 1, 0};

    EXPECT_EQ(v1 + v2, v3);
}

TEST(Vector_cTest, TestSubtraction)
{
    GSL::Vector_c v1{1, 0, 0}, v2{0, 1, 0}, v3{1, -1, 0};

    EXPECT_EQ(v1 - v2, v3);
}

TEST(Vector_cTest, TestElMult)
{
    GSL::Vector_c v1{3, 2, 2}, v2{2, 3, 4}, v3{6, 6, 8};

    EXPECT_EQ(v1 * v2, v3);
}

TEST(Vector_cTest, TestElDiv)
{
    GSL::Vector_c v1{8, 4, 2}, v2{6, 3, 2}, v3{8/6, 4/3, 2/2};

    EXPECT_EQ(v1 / v2, v3);
}

TEST(Vector_cTest, TestScalarMult)
{
    GSL::Vector_c v1{3, 2, 2}, v2{9, 6, 6};

    EXPECT_EQ(v1 * 3, v2);
}

TEST(Vector_cTest, TestScalarDiv)
{
    GSL::Vector_c v1{8, 4, 2}, v2{4, 2, 1};

    EXPECT_EQ(v1 / 2, v2);
}

TEST(Vector_cTest, TestScalarMult2)
{
    GSL::Vector_c v1{3, 2, 2}, v2{9, 6, 6};

    EXPECT_EQ(3 * v1, v2);
}

TEST(Vector_cTest, TestBegin)
{
    GSL::Vector_c v{1, 2, 3};
    EXPECT_EQ(*v.begin(), 1);
}

TEST(Vector_cTest, TestcBegin)
{
    GSL::Vector_c v{1, 2, 3};
    EXPECT_EQ(*v.cbegin(), 1);
}

TEST(Vector_cTest, TestIterPreIncrement)
{
    GSL::Vector_c v{1, 2, 3};
    EXPECT_EQ(*++v.begin(), 2);
}

TEST(Vector_cTest, TestIterPostIncrement)
{
    GSL::Vector_c v{1, 2, 3};
    auto it = v.begin();
    it++;
    EXPECT_EQ(*it, 2);
}

TEST(Vector_cTest, TestIterPreDecrement)
{
    GSL::Vector_c v{1, 2, 3};
    EXPECT_EQ(*--(++v.begin()), 1);
}

TEST(Vector_cTest, TestIterPostDecrement)
{
    GSL::Vector_c v{1, 2, 3};
    auto it = v.begin();
    it++; it--;
    EXPECT_EQ(*it, 1);
}

TEST(Vector_cTest, TestIterStepIncrement)
{
    GSL::Vector_c v{1, 2, 3};
    auto it = v.begin();
    it += 2;
    EXPECT_EQ(*it, 3);
}

TEST(Vector_cTest, TestIterStep)
{
    GSL::Vector_c v{1, 2, 3};
    auto it = v.begin();
    EXPECT_EQ(*(it + 2), 3);
}

TEST(Vector_cTest, TestIterStepForward)
{
    GSL::Vector_c v{1, 2, 3};
    auto it = v.begin();
    EXPECT_EQ(*(2 + it), 3);
}

TEST(Vector_cTest, TestIterStepDecrement)
{
    GSL::Vector_c v{1, 2, 3};
    auto it = v.begin();
    it += 2;
    it -= 2;
    EXPECT_EQ(*it, 1);
}

TEST(Vector_cTest, TestIterStepBack)
{
    GSL::Vector_c v{1, 2, 3};
    auto it = v.begin() + 2;
    EXPECT_EQ(*(it - 2), 1);
}

TEST(Vector_cTest, TestIterDiff)
{
    GSL::Vector_c v{1, 2, 3};
    auto it = v.begin() + 2;
    EXPECT_EQ(it - v.begin(), 2);
}

TEST(Vector_cTest, TestIterEq)
{
    GSL::Vector_c v{1, 2, 3};
    auto it1 = v.begin() + 2;
    auto it2 = v.begin();
    it2 += 2;

    EXPECT_EQ(it1, it2);
}

TEST(Vector_cTest, TestIterNeq)
{
    GSL::Vector_c v{1, 2, 3};
    auto it1 = v.begin() + 2;
    auto it2 = v.begin();

    EXPECT_NE(it1, it2);
}

TEST(Vector_cTest, TestEnd)
{
    GSL::Vector_c v{1, 2, 3};
    auto it1 = v.begin() + 2;
    auto it2 = v.end();

    EXPECT_EQ(it1, --it2);
}

TEST(Vector_cTest, TestcIterPreIncrement)
{
    GSL::Vector_c v{1, 2, 3};
    EXPECT_EQ(*++v.cbegin(), 2);
}

TEST(Vector_cTest, TestcIterPostIncrement)
{
    GSL::Vector_c v{1, 2, 3};
    auto it = v.cbegin();
    it++;
    EXPECT_EQ(*it, 2);
}

TEST(Vector_cTest, TestcIterPreDecrement)
{
    GSL::Vector_c v{1, 2, 3};
    EXPECT_EQ(*--(++v.cbegin()), 1);
}

TEST(Vector_cTest, TestcIterPostDecrement)
{
    GSL::Vector_c v{1, 2, 3};
    auto it = v.cbegin();
    it++; it--;
    EXPECT_EQ(*it, 1);
}

TEST(Vector_cTest, TestcIterStepIncrement)
{
    GSL::Vector_c v{1, 2, 3};
    auto it = v.cbegin();
    it += 2;
    EXPECT_EQ(*it, 3);
}

TEST(Vector_cTest, TestcIterStep)
{
    GSL::Vector_c v{1, 2, 3};
    auto it = v.cbegin();
    EXPECT_EQ(*(it + 2), 3);
}

TEST(Vector_cTest, TestcIterStepForward)
{
    GSL::Vector_c v{1, 2, 3};
    auto it = v.cbegin();
    EXPECT_EQ(*(2 + it), 3);
}

TEST(Vector_cTest, TestcIterStepDecrement)
{
    GSL::Vector_c v{1, 2, 3};
    auto it = v.cbegin();
    it += 2;
    it -= 2;
    EXPECT_EQ(*it, 1);
}

TEST(Vector_cTest, TestcIterStepBack)
{
    GSL::Vector_c v{1, 2, 3};
    auto it = v.cbegin() + 2;
    EXPECT_EQ(*(it - 2), 1);
}

TEST(Vector_cTest, TestcIterDiff)
{
    GSL::Vector_c v{1, 2, 3};
    auto it = v.cbegin() + 2;
    EXPECT_EQ(it - v.cbegin(), 2);
}

TEST(Vector_cTest, TestcIterEq)
{
    GSL::Vector_c v{1, 2, 3};
    auto it1 = v.cbegin() + 2;
    auto it2 = v.cbegin();
    it2 += 2;

    EXPECT_EQ(it1, it2);
}

TEST(Vector_cTest, TestcIterNeq)
{
    GSL::Vector_c v{1, 2, 3};
    auto it1 = v.cbegin() + 2;
    auto it2 = v.cbegin();

    EXPECT_NE(it1, it2);
}

TEST(Vector_cTest, TestcEnd)
{
    GSL::Vector_c v{1, 2, 3};
    auto it1 = v.cbegin() + 2;
    auto it2 = v.cend();

    EXPECT_EQ(it1, --it2);
}

TEST(Vector_cTest, TestRbegin)
{
    GSL::Vector_c v{1, 2, 3};
    auto it1 = v.rbegin();

    EXPECT_EQ(*it1, 3);
}

TEST(Vector_cTest, TestRend)
{
    GSL::Vector_c v{1, 2, 3};
    auto it1 = v.rend();

    EXPECT_EQ(*--it1, 1);
}

TEST(Vector_cTest, TestcRbegin)
{
    GSL::Vector_c v{1, 2, 3};
    auto it1 = v.crbegin();

    EXPECT_EQ(*it1, 3);
}

TEST(Vector_cTest, TestcRend)
{
    GSL::Vector_c v{1, 2, 3};
    auto it1 = v.crend();

    EXPECT_EQ(*--it1, 1);
}

TEST(Vector_cTest, TestFront)
{
    GSL::Vector_c v{1, 2, 3};
    EXPECT_EQ(v.front(), 1);
}

TEST(Vector_cTest, TestBack)
{
    GSL::Vector_c v{1, 2, 3};
    EXPECT_EQ(v.back(), 3);
}

TEST(Vector_cTest, TestAt)
{
    GSL::Vector_c v{1, 2, 3};
    EXPECT_EQ(v.at(1), 2);
}

TEST(Vector_cTest, TestAssign1)
{
    GSL::Vector_c v1{1, 2, 3};
    GSL::Vector_c v2{3, 4, 5};
    v2.assign(v1.begin(), v1.end());
    EXPECT_EQ(v1, v2);
}

TEST(Vector_cTest, TestAssign2)
{
    GSL::Vector_c v1{1, 2, 3};
    GSL::Vector_c v2{3, 3, 3, 3};
    v1.assign(4, static_cast<char>(3));
    EXPECT_EQ(v1, v2);
}

TEST(Vector_cTest, TestAssign3)
{
    GSL::Vector_c v1{1, 2, 3};
    GSL::Vector_c v2{3, 4};
    v1.assign({3, 4});
    EXPECT_EQ(v1, v2);
}
