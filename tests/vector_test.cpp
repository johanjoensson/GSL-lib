#include "GSLpp/vector.h"
#include <gtest/gtest.h>
#include <cmath>

TEST(VectorTest, TestConstruction)
{
    GSL::Vector v(3,0);
    EXPECT_DOUBLE_EQ(v[0], 0.);
    EXPECT_DOUBLE_EQ(v[1], 0.);
    EXPECT_DOUBLE_EQ(v[2], 0.);
}

TEST(VectorTest, TestConstructionInitializerList)
{
    double a = 1., b = 2., c = 3.;
    GSL::Vector v{a, b, c};
    EXPECT_DOUBLE_EQ(v[0], 1.);
    EXPECT_DOUBLE_EQ(v[1], 2.);
    EXPECT_DOUBLE_EQ(v[2], 3.);
}

TEST(VectorTest, TestConstructionCopy)
{
    double a = 1., b = 2., c = 3.;
    GSL::Vector v1{a, b, c};
    GSL::Vector v2{v1.clone()};
    EXPECT_DOUBLE_EQ(v1[0], v2[0]);
    EXPECT_DOUBLE_EQ(v1[1], v2[1]);
    EXPECT_DOUBLE_EQ(v1[2], v2[2]);
}

TEST(VectorTest, TestConstructionMove)
{
    double a = 1., b = 2., c = 3.;
    GSL::Vector v1{a, b, c};
    GSL::Vector v2{std::move(v1)};
    EXPECT_DOUBLE_EQ(v2[0], 1.);
    EXPECT_DOUBLE_EQ(v2[1], 2.);
    EXPECT_DOUBLE_EQ(v2[2], 3.);
}

TEST(VectorTest, TestEqual)
{

    double a = 1., b = 2., c = 3.;
    GSL::Vector v1{a, b, c};
    GSL::Vector v2{v1.clone()};

    EXPECT_EQ(v1, v2);
}

TEST(VectorTest, TestNotEqual)
{

    double a = 1., b = 2., c = 3.;
    GSL::Vector v1{a, b, c};
    GSL::Vector v2{a +1, b, c};

    EXPECT_NE(v1, v2);
}

TEST(VectorTest, TestCopy)
{

    double a = 1., b = 2., c = 3.;
    GSL::Vector v1{a, b, c};
    GSL::Vector v2 = v1.clone();

    EXPECT_EQ(v1, v2);
}

TEST(VectorTest, TestMove)
{

    double a = 1., b = 2., c = 3.;
    GSL::Vector v1{a, b, c}, v1s{a, b, c};
    GSL::Vector v2 = std::move(v1);

    EXPECT_EQ(v2, v1s);
}

TEST(VectorTest, TestDecayToGSLVector)
{
    double a = 1., b = 2., c = 3.;
    GSL::Vector v{a, b, c};
    gsl_vector gv = *v.gsl_data();

    EXPECT_DOUBLE_EQ(gsl_vector_get(&gv, 0), a);
}

TEST(VectorTest, TestSize)
{
    double a = 1., b = 2., c = 3.;
    GSL::Vector v{a, b, c};

    EXPECT_EQ(v.size(), 3);
}

// TEST(VectorTest, TestDim)
// {
//     double a = 1., b = 2., c = 3.;
//     GSL::Vector v{a, b, c};
//
//     EXPECT_EQ(v.dim(), 3);
// }

TEST(VectorTest, TestCopyFun)
{
    double a = 1., b = 2., c = 3.;
    GSL::Vector v{a, b, c}, v2(v.size());
    v2.copy(v);

    EXPECT_EQ(v, v2);
}

TEST(VectorTest, TestNorm)
{
    double a = 1., b = 2., c = 3.;
    GSL::Vector v{a, b, c};

    EXPECT_DOUBLE_EQ(v.norm(), std::sqrt(a*a + b*b + c*c));
}

TEST(VectorTest, TestNormalize)
{
    double a = 1., b = 2., c = 3.;
    GSL::Vector v{a, b, c};
    v = normalize(v);

    EXPECT_DOUBLE_EQ(v.norm(), 1.);
}

TEST(VectorTest, TestDot)
{
    GSL::Vector v1{1., 0., 0.}, v2{0., 1., 0.};

    EXPECT_DOUBLE_EQ(GSL::dot(v1,v2), 0.);
}

TEST(VectorTest, TestCross)
{
    GSL::Vector v1{1., 0., 0.}, v2{0., 1., 0.}, v3{0., 0., 1.};

    EXPECT_EQ(GSL::cross(v2, v3), v1);
}

TEST(VectorTest, TestIncrement)
{
    GSL::Vector v1{1., 0., 0.}, v2{0., 1., 0.}, v3{1., 1., 0.};

    EXPECT_EQ(v1 += v2, v3);
}

TEST(VectorTest, TestDecrement)
{
    GSL::Vector v1{1., 0., 0.}, v2{0., 1., 0.}, v3{1., -1., 0.};

    EXPECT_EQ(v1 -= v2, v3);
}

TEST(VectorTest, TestElMultScale)
{
    GSL::Vector v1{3., 2., 2.}, v2{2., 3., 4.}, v3{6., 6., 8.};

    EXPECT_EQ(v1 *= v2, v3);
}

TEST(VectorTest, TestElDivScale)
{
    GSL::Vector v1{8., 4., 2.}, v2{6., 3., 2.}, v3{8./6, 4./3, 2./2};

    EXPECT_EQ(v1 /= v2, v3);
}

TEST(VectorTest, TestMultScale)
{
    GSL::Vector v1{3., 2., 2.}, v2{9., 6., 6.};

    EXPECT_EQ(v1 *= 3, v2);
}

TEST(VectorTest, TestDivScale)
{
    GSL::Vector v1{8., 4., 2.}, v2{4., 2., 1.};

    EXPECT_EQ(v1 /= 2, v2);
}

TEST(VectorTest, TestAddition)
{
    GSL::Vector v1{1., 0., 0.}, v2{0., 1., 0.}, v3{1., 1., 0.};

    EXPECT_EQ(v1 + v2, v3);
}

TEST(VectorTest, TestSubtraction)
{
    GSL::Vector v1{1., 0., 0.}, v2{0., 1., 0.}, v3{1., -1., 0.};

    EXPECT_EQ(v1 - v2, v3);
}

TEST(VectorTest, TestElMult)
{
    GSL::Vector v1{3., 2., 2.}, v2{2., 3., 4.}, v3{6., 6., 8.};

    EXPECT_EQ(v1 * v2, v3);
}

TEST(VectorTest, TestElDiv)
{
    GSL::Vector v1{8., 4., 2.}, v2{6., 3., 2.}, v3{8./6, 4./3, 2./2};

    EXPECT_EQ(v1 / v2, v3);
}

TEST(VectorTest, TestScalarMult)
{
    GSL::Vector v1{3., 2., 2.}, v2{9., 6., 6.};

    EXPECT_EQ(v1 * 3., v2);
}

TEST(VectorTest, TestScalarDiv)
{
    GSL::Vector v1{8., 4., 2.}, v2{4., 2., 1.};

    EXPECT_EQ(v1 / 2., v2);
}

TEST(VectorTest, TestScalarMult2)
{
    GSL::Vector v1{3., 2., 2.}, v2{9., 6., 6.};

    EXPECT_EQ(3. * v1, v2);
}

TEST(VectorTest, TestBegin)
{
    GSL::Vector v{1., 2., 3.};
    EXPECT_DOUBLE_EQ(*v.view().begin(), 1.);
}

TEST(VectorTest, TestcBegin)
{
    GSL::Vector v{1., 2., 3.};
    EXPECT_DOUBLE_EQ(*v.view().cbegin(), 1.);
}

TEST(VectorTest, TestIterPreIncrement)
{
    GSL::Vector v{1., 2., 3.};
    EXPECT_DOUBLE_EQ(*++v.view().begin(), 2.);
}

TEST(VectorTest, TestIterPostIncrement)
{
    GSL::Vector v{1., 2., 3.};
    auto it = v.view().begin();
    it++;
    EXPECT_DOUBLE_EQ(*it, 2.);
}

TEST(VectorTest, TestIterPreDecrement)
{
    GSL::Vector v{1., 2., 3.};
    EXPECT_DOUBLE_EQ(*--(++v.view().begin()), 1.);
}

TEST(VectorTest, TestIterPostDecrement)
{
    GSL::Vector v{1., 2., 3.};
    auto it = v.view().begin();
    it++; it--;
    EXPECT_DOUBLE_EQ(*it, 1.);
}

TEST(VectorTest, TestIterStepIncrement)
{
    GSL::Vector v{1., 2., 3.};
    auto it = v.view().begin();
    it += 2;
    EXPECT_DOUBLE_EQ(*it, 3.);
}

TEST(VectorTest, TestIterStep)
{
    GSL::Vector v{1., 2., 3.};
    auto it = v.view().begin();
    EXPECT_DOUBLE_EQ(*(it + 2), 3.);
}

TEST(VectorTest, TestIterStepDecrement)
{
    GSL::Vector v{1., 2., 3.};
    auto it = v.view().begin();
    it += 2;
    it -= 2;
    EXPECT_DOUBLE_EQ(*it, 1.);
}

TEST(VectorTest, TestIterStepBack)
{
    GSL::Vector v{1., 2., 3.};
    auto it = v.view().begin() + 2;
    EXPECT_DOUBLE_EQ(*(it - 2), 1.);
}

TEST(VectorTest, TestIterDiff)
{
    GSL::Vector v{1., 2., 3.};
    auto it = v.view().begin() + 2;
    EXPECT_EQ(it - v.view().begin(), 2.);
}

TEST(VectorTest, TestIterEq)
{
    GSL::Vector v{1., 2., 3.};
    auto it1 = v.view().begin() + 2;
    auto it2 = v.view().begin();
    it2 += 2;

    EXPECT_EQ(it1, it2);
}

TEST(VectorTest, TestIterNeq)
{
    GSL::Vector v{1., 2., 3.};
    auto it1 = v.view().begin() + 2;
    auto it2 = v.view().begin();

    EXPECT_NE(it1, it2);
}

TEST(VectorTest, TestEnd)
{
    GSL::Vector v{1., 2., 3.};
    auto it1 = v.view().begin() + 2;
    auto it2 = v.view().end();

    EXPECT_EQ(it1, --it2);
}

TEST(VectorTest, TestcIterPreIncrement)
{
    GSL::Vector v{1., 2., 3.};
    EXPECT_DOUBLE_EQ(*++v.view().cbegin(), 2.);
}

TEST(VectorTest, TestcIterPostIncrement)
{
    GSL::Vector v{1., 2., 3.};
    auto it = v.view().cbegin();
    it++;
    EXPECT_DOUBLE_EQ(*it, 2.);
}

TEST(VectorTest, TestcIterPreDecrement)
{
    GSL::Vector v{1., 2., 3.};
    EXPECT_DOUBLE_EQ(*--(++v.view().cbegin()), 1.);
}

TEST(VectorTest, TestcIterPostDecrement)
{
    GSL::Vector v{1., 2., 3.};
    auto it = v.view().cbegin();
    it++; it--;
    EXPECT_DOUBLE_EQ(*it, 1.);
}

TEST(VectorTest, TestcIterStepIncrement)
{
    GSL::Vector v{1., 2., 3.};
    auto it = v.view().cbegin();
    it += 2;
    EXPECT_DOUBLE_EQ(*it, 3.);
}

TEST(VectorTest, TestcIterStep)
{
    GSL::Vector v{1., 2., 3.};
    auto it = v.view().cbegin();
    EXPECT_DOUBLE_EQ(*(it + 2), 3.);
}

TEST(VectorTest, TestcIterStepDecrement)
{
    GSL::Vector v{1., 2., 3.};
    auto it = v.view().cbegin();
    it += 2;
    it -= 2;
    EXPECT_DOUBLE_EQ(*it, 1.);
}

TEST(VectorTest, TestcIterStepBack)
{
    GSL::Vector v{1., 2., 3.};
    auto it = v.view().cbegin() + 2;
    EXPECT_DOUBLE_EQ(*(it - 2), 1.);
}

TEST(VectorTest, TestcIterDiff)
{
    GSL::Vector v{1., 2., 3.};
    auto it = v.view().cbegin() + 2;
    EXPECT_EQ(it - v.view().cbegin(), 2.);
}

TEST(VectorTest, TestcIterEq)
{
    GSL::Vector v{1., 2., 3.};
    auto it1 = v.view().cbegin() + 2;
    auto it2 = v.view().cbegin();
    it2 += 2;

    EXPECT_EQ(it1, it2);
}

TEST(VectorTest, TestcIterNeq)
{
    GSL::Vector v{1., 2., 3.};
    auto it1 = v.view().cbegin() + 2;
    auto it2 = v.view().cbegin();

    EXPECT_NE(it1, it2);
}

TEST(VectorTest, TestcEnd)
{
    GSL::Vector v{1., 2., 3.};
    auto it1 = v.view().cbegin() + 2;
    auto it2 = v.view().cend();

    EXPECT_EQ(it1, --it2);
}

TEST(VectorTest, TestRbegin)
{
    GSL::Vector v{1., 2., 3.};
    auto it1 = v.view().rbegin();

    EXPECT_DOUBLE_EQ(*it1, 3.);
}

TEST(VectorTest, TestRend)
{
    GSL::Vector v{1., 2., 3.};
    auto it1 = v.view().rend();

    EXPECT_DOUBLE_EQ(*--it1, 1.);
}

TEST(VectorTest, TestcRbegin)
{
    GSL::Vector v{1., 2., 3.};
    auto it1 = v.view().crbegin();

    EXPECT_DOUBLE_EQ(*it1, 3.);
}

TEST(VectorTest, TestcRend)
{
    GSL::Vector v{1., 2., 3.};
    auto it1 = v.view().crend();

    EXPECT_EQ(*--it1, 1.);
}

TEST(VectorTest, TestFront)
{
    GSL::Vector v{1., 2., 3.};
    EXPECT_DOUBLE_EQ(v.view().front(), 1.);
}

TEST(VectorTest, TestBack)
{
    GSL::Vector v{1., 2., 3.};
    EXPECT_DOUBLE_EQ(v.view().back(), 3.);
}

TEST(VectorTest, TestAt)
{
    GSL::Vector v{1., 2., 3.};
    EXPECT_DOUBLE_EQ(v.at(1), 2.);
}
