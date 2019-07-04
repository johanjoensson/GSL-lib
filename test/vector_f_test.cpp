#include "GSLpp/vector.h"
#include <gtest/gtest.h>
#include <iostream>

TEST(Vector_fTest, TestConstruction)
{
    GSL::Vector_f v(3);
    EXPECT_FLOAT_EQ(v[0], 0.);
    EXPECT_FLOAT_EQ(v[1], 0.);
    EXPECT_FLOAT_EQ(v[2], 0.);
}

TEST(Vector_fTest, TestConstructionInitializerList)
{
    float a = 1., b = 2., c = 3.;
    GSL::Vector_f v{a, b, c};
    EXPECT_FLOAT_EQ(v[0], 1.);
    EXPECT_FLOAT_EQ(v[1], 2.);
    EXPECT_FLOAT_EQ(v[2], 3.);
}

TEST(Vector_fTest, TestConstructionCopy)
{
    float a = 1., b = 2., c = 3.;
    GSL::Vector_f v1{a, b, c};
    GSL::Vector_f v2{v1};
    EXPECT_FLOAT_EQ(v1[0], v2[0]);
    EXPECT_FLOAT_EQ(v1[1], v2[1]);
    EXPECT_FLOAT_EQ(v1[2], v2[2]);
}

TEST(Vector_fTest, TestConstructionMove)
{
    float a = 1., b = 2., c = 3.;
    GSL::Vector_f v1{a, b, c};
    GSL::Vector_f v2{std::move(v1)};
    EXPECT_FLOAT_EQ(v2[0], 1.);
    EXPECT_FLOAT_EQ(v2[1], 2.);
    EXPECT_FLOAT_EQ(v2[2], 3.);
}

TEST(Vector_fTest, TestEqual)
{

    float a = 1., b = 2., c = 3.;
    GSL::Vector_f v1{a, b, c};
    GSL::Vector_f v2{v1};

    EXPECT_EQ(v1, v2);
}

TEST(Vector_fTest, TestNotEqual)
{

    float a = 1., b = 2., c = 3.;
    GSL::Vector_f v1{a, b, c};
    GSL::Vector_f v2{a +1, b, c};

    EXPECT_NE(v1, v2);
}

TEST(Vector_fTest, TestCopy)
{

    float a = 1., b = 2., c = 3.;
    GSL::Vector_f v1{a, b, c};
    GSL::Vector_f v2;
    v2 = v1;

    EXPECT_EQ(v1, v2);
}

TEST(Vector_fTest, TestMove)
{

    float a = 1., b = 2., c = 3.;
    GSL::Vector_f v1{a, b, c}, v1s{a, b, c};
    GSL::Vector_f v2;
    v2 = std::move(v1);

    EXPECT_EQ(v2, v1s);
}

TEST(Vector_fTest, TestDecayToGSLVector_f)
{
    float a = 1., b = 2., c = 3.;
    GSL::Vector_f v{a, b, c};
    gsl_vector_float gv = v;

    EXPECT_FLOAT_EQ(gsl_vector_float_get(&gv, 0), a);
}

TEST(Vector_fTest, TestSize)
{
    float a = 1., b = 2., c = 3.;
    GSL::Vector_f v{a, b, c};

    EXPECT_EQ(v.size(), 3);
}

TEST(Vector_fTest, TestDim)
{
    float a = 1., b = 2., c = 3.;
    GSL::Vector_f v{a, b, c};

    EXPECT_EQ(v.dim(), 3);
}

TEST(Vector_fTest, TestCopyFun)
{
    float a = 1., b = 2., c = 3.;
    GSL::Vector_f v{a, b, c}, v2;
    v2.copy(v);

    EXPECT_EQ(v, v2);
}

TEST(Vector_fTest, TestNorm)
{
    float a = 1., b = 2., c = 3.;
    GSL::Vector_f v{a, b, c};

    EXPECT_FLOAT_EQ(v.norm<float>(), std::sqrt(a*a + b*b + c*c));
}

TEST(Vector_fTest, TestNormalize)
{
    float a = 1., b = 2., c = 3.;
    GSL::Vector_f v{a, b, c};
    v.normalize<float>();

    EXPECT_FLOAT_EQ(v.norm<float>(), 1.);
}

TEST(Vector_fTest, TestDot)
{
    GSL::Vector_f v1{1., 0., 0.}, v2{0., 1., 0.};

    EXPECT_FLOAT_EQ(v1.dot(v2), 0.);
}

TEST(Vector_fTest, TestCross)
{
    GSL::Vector_f v1{1., 0., 0.}, v2{0., 1., 0.}, v3{0., 0., 1.};

    EXPECT_EQ(v1.cross(v2), v3);
}

TEST(Vector_fTest, TestIncrement)
{
    GSL::Vector_f v1{1., 0., 0.}, v2{0., 1., 0.}, v3{1., 1., 0.};

    EXPECT_EQ(v1 += v2, v3);
}

TEST(Vector_fTest, TestDecrement)
{
    GSL::Vector_f v1{1., 0., 0.}, v2{0., 1., 0.}, v3{1., -1., 0.};

    EXPECT_EQ(v1 -= v2, v3);
}

TEST(Vector_fTest, TestElMultScale)
{
    GSL::Vector_f v1{3., 2., 2.}, v2{2., 3., 4.}, v3{6., 6., 8.};

    EXPECT_EQ(v1 *= v2, v3);
}

TEST(Vector_fTest, TestElDivScale)
{
    GSL::Vector_f v1{8., 4., 2.}, v2{6., 3., 2.}, v3{8./6, 4./3, 2./2};

    EXPECT_EQ(v1 /= v2, v3);
}

TEST(Vector_fTest, TestMultScale)
{
    GSL::Vector_f v1{3., 2., 2.}, v2{9., 6., 6.};

    EXPECT_EQ(v1 *= 3, v2);
}

TEST(Vector_fTest, TestDivScale)
{
    GSL::Vector_f v1{8., 4., 2.}, v2{4., 2., 1.};

    EXPECT_EQ(v1 /= 2, v2);
}

TEST(Vector_fTest, TestAddition)
{
    GSL::Vector_f v1{1., 0., 0.}, v2{0., 1., 0.}, v3{1., 1., 0.};

    EXPECT_EQ(v1 + v2, v3);
}

TEST(Vector_fTest, TestSubtraction)
{
    GSL::Vector_f v1{1., 0., 0.}, v2{0., 1., 0.}, v3{1., -1., 0.};

    EXPECT_EQ(v1 - v2, v3);
}

TEST(Vector_fTest, TestElMult)
{
    GSL::Vector_f v1{3., 2., 2.}, v2{2., 3., 4.}, v3{6., 6., 8.};

    EXPECT_EQ(v1 * v2, v3);
}

TEST(Vector_fTest, TestElDiv)
{
    GSL::Vector_f v1{8., 4., 2.}, v2{6., 3., 2.}, v3{8./6, 4./3, 2./2};

    EXPECT_EQ(v1 / v2, v3);
}

TEST(Vector_fTest, TestScalarMult)
{
    GSL::Vector_f v1{3., 2., 2.}, v2{9., 6., 6.};

    EXPECT_EQ(v1 * 3., v2);
}

TEST(Vector_fTest, TestScalarDiv)
{
    GSL::Vector_f v1{8., 4., 2.}, v2{4., 2., 1.};

    EXPECT_EQ(v1 / 2., v2);
}

TEST(Vector_fTest, TestScalarMult2)
{
    GSL::Vector_f v1{3., 2., 2.}, v2{9., 6., 6.};

    EXPECT_EQ(3. * v1, v2);
}

TEST(Vector_fTest, TestBegin)
{
    GSL::Vector_f v{1., 2., 3.};
    EXPECT_FLOAT_EQ(*v.begin(), 1.);
}

TEST(Vector_fTest, TestcBegin)
{
    GSL::Vector_f v{1., 2., 3.};
    EXPECT_FLOAT_EQ(*v.cbegin(), 1.);
}

TEST(Vector_fTest, TestIterPreIncrement)
{
    GSL::Vector_f v{1., 2., 3.};
    EXPECT_FLOAT_EQ(*++v.begin(), 2.);
}

TEST(Vector_fTest, TestIterPostIncrement)
{
    GSL::Vector_f v{1., 2., 3.};
    auto it = v.begin();
    it++;
    EXPECT_FLOAT_EQ(*it, 2.);
}

TEST(Vector_fTest, TestIterPreDecrement)
{
    GSL::Vector_f v{1., 2., 3.};
    EXPECT_FLOAT_EQ(*--(++v.begin()), 1.);
}

TEST(Vector_fTest, TestIterPostDecrement)
{
    GSL::Vector_f v{1., 2., 3.};
    auto it = v.begin();
    it++; it--;
    EXPECT_FLOAT_EQ(*it, 1.);
}

TEST(Vector_fTest, TestIterStepIncrement)
{
    GSL::Vector_f v{1., 2., 3.};
    auto it = v.begin();
    it += 2;
    EXPECT_FLOAT_EQ(*it, 3.);
}

TEST(Vector_fTest, TestIterStep)
{
    GSL::Vector_f v{1., 2., 3.};
    auto it = v.begin();
    EXPECT_FLOAT_EQ(*(it + 2), 3.);
}

TEST(Vector_fTest, TestIterStepForward)
{
    GSL::Vector_f v{1., 2., 3.};
    auto it = v.begin();
    EXPECT_FLOAT_EQ(*(2 + it), 3.);
}

TEST(Vector_fTest, TestIterStepDecrement)
{
    GSL::Vector_f v{1., 2., 3.};
    auto it = v.begin();
    it += 2;
    it -= 2;
    EXPECT_FLOAT_EQ(*it, 1.);
}

TEST(Vector_fTest, TestIterStepBack)
{
    GSL::Vector_f v{1., 2., 3.};
    auto it = v.begin() + 2;
    EXPECT_FLOAT_EQ(*(it - 2), 1.);
}

TEST(Vector_fTest, TestIterDiff)
{
    GSL::Vector_f v{1., 2., 3.};
    auto it = v.begin() + 2;
    EXPECT_EQ(it - v.begin(), 2.);
}

TEST(Vector_fTest, TestIterEq)
{
    GSL::Vector_f v{1., 2., 3.};
    auto it1 = v.begin() + 2;
    auto it2 = v.begin();
    it2 += 2;

    EXPECT_EQ(it1, it2);
}

TEST(Vector_fTest, TestIterNeq)
{
    GSL::Vector_f v{1., 2., 3.};
    auto it1 = v.begin() + 2;
    auto it2 = v.begin();

    EXPECT_NE(it1, it2);
}

TEST(Vector_fTest, TestEnd)
{
    GSL::Vector_f v{1., 2., 3.};
    auto it1 = v.begin() + 2;
    auto it2 = v.end();

    EXPECT_EQ(it1, --it2);
}

TEST(Vector_fTest, TestcIterPreIncrement)
{
    GSL::Vector_f v{1., 2., 3.};
    EXPECT_FLOAT_EQ(*++v.cbegin(), 2.);
}

TEST(Vector_fTest, TestcIterPostIncrement)
{
    GSL::Vector_f v{1., 2., 3.};
    auto it = v.cbegin();
    it++;
    EXPECT_FLOAT_EQ(*it, 2.);
}

TEST(Vector_fTest, TestcIterPreDecrement)
{
    GSL::Vector_f v{1., 2., 3.};
    EXPECT_FLOAT_EQ(*--(++v.cbegin()), 1.);
}

TEST(Vector_fTest, TestcIterPostDecrement)
{
    GSL::Vector_f v{1., 2., 3.};
    auto it = v.cbegin();
    it++; it--;
    EXPECT_FLOAT_EQ(*it, 1.);
}

TEST(Vector_fTest, TestcIterStepIncrement)
{
    GSL::Vector_f v{1., 2., 3.};
    auto it = v.cbegin();
    it += 2;
    EXPECT_FLOAT_EQ(*it, 3.);
}

TEST(Vector_fTest, TestcIterStep)
{
    GSL::Vector_f v{1., 2., 3.};
    auto it = v.cbegin();
    EXPECT_FLOAT_EQ(*(it + 2), 3.);
}

TEST(Vector_fTest, TestcIterStepForward)
{
    GSL::Vector_f v{1., 2., 3.};
    auto it = v.cbegin();
    EXPECT_FLOAT_EQ(*(2 + it), 3.);
}

TEST(Vector_fTest, TestcIterStepDecrement)
{
    GSL::Vector_f v{1., 2., 3.};
    auto it = v.cbegin();
    it += 2;
    it -= 2;
    EXPECT_FLOAT_EQ(*it, 1.);
}

TEST(Vector_fTest, TestcIterStepBack)
{
    GSL::Vector_f v{1., 2., 3.};
    auto it = v.cbegin() + 2;
    EXPECT_FLOAT_EQ(*(it - 2), 1.);
}

TEST(Vector_fTest, TestcIterDiff)
{
    GSL::Vector_f v{1., 2., 3.};
    auto it = v.cbegin() + 2;
    EXPECT_EQ(it - v.cbegin(), 2.);
}

TEST(Vector_fTest, TestcIterEq)
{
    GSL::Vector_f v{1., 2., 3.};
    auto it1 = v.cbegin() + 2;
    auto it2 = v.cbegin();
    it2 += 2;

    EXPECT_EQ(it1, it2);
}

TEST(Vector_fTest, TestcIterNeq)
{
    GSL::Vector_f v{1., 2., 3.};
    auto it1 = v.cbegin() + 2;
    auto it2 = v.cbegin();

    EXPECT_NE(it1, it2);
}

TEST(Vector_fTest, TestcEnd)
{
    GSL::Vector_f v{1., 2., 3.};
    auto it1 = v.cbegin() + 2;
    auto it2 = v.cend();

    EXPECT_EQ(it1, --it2);
}

TEST(Vector_fTest, TestRbegin)
{
    GSL::Vector_f v{1., 2., 3.};
    auto it1 = v.rbegin();

    EXPECT_FLOAT_EQ(*it1, 3.);
}

TEST(Vector_fTest, TestRend)
{
    GSL::Vector_f v{1., 2., 3.};
    auto it1 = v.rend();

    EXPECT_FLOAT_EQ(*--it1, 1.);
}

TEST(Vector_fTest, TestcRbegin)
{
    GSL::Vector_f v{1., 2., 3.};
    auto it1 = v.crbegin();

    EXPECT_FLOAT_EQ(*it1, 3.);
}

TEST(Vector_fTest, TestcRend)
{
    GSL::Vector_f v{1., 2., 3.};
    auto it1 = v.crend();

    EXPECT_EQ(*--it1, 1.);
}

TEST(Vector_fTest, TestFront)
{
    GSL::Vector_f v{1., 2., 3.};
    EXPECT_FLOAT_EQ(v.front(), 1.);
}

TEST(Vector_fTest, TestBack)
{
    GSL::Vector_f v{1., 2., 3.};
    EXPECT_FLOAT_EQ(v.back(), 3.);
}

TEST(Vector_fTest, TestAt)
{
    GSL::Vector_f v{1., 2., 3.};
    EXPECT_FLOAT_EQ(v.at(1), 2.);
}

TEST(Vector_fTest, TestAssign1)
{
    GSL::Vector_f v1{1., 2., 3.};
    GSL::Vector_f v2{3., 4., 5.};
    v2.assign(v1.begin(), v1.end());
    EXPECT_EQ(v1, v2);
}

TEST(Vector_fTest, TestAssign2)
{
    GSL::Vector_f v1{1., 2., 3.};
    GSL::Vector_f v2{3., 3., 3., 3.};
    v1.assign(4, 3.);
    EXPECT_EQ(v1, v2);
}

TEST(Vector_fTest, TestAssign3)
{
    GSL::Vector_f v1{1., 2., 3.};
    GSL::Vector_f v2{3., 4.};
    v1.assign({3., 4.});
    EXPECT_EQ(v1, v2);
}
