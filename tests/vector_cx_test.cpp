#include "GSLpp/complex.h"
#include "GSLpp/vector_complex.h"
#include <gtest/gtest.h>
#include <iostream>
#include <cmath>

TEST(Vector_cxTest, TestConstruction)
{
    GSL::Vector_Complex v(3, 0);

    EXPECT_EQ(v[0], GSL::Complex{0});
    EXPECT_EQ(v[1], GSL::Complex{0});
    EXPECT_EQ(v[2], GSL::Complex{0});
}

TEST(Vector_cxTest, TestConstructionInitializerList)
{
    GSL::Complex a = 1., b = 2., c = 3.;
    GSL::Vector_Complex v{a, b, c};
    EXPECT_EQ(v[0], GSL::Complex{1.});
    EXPECT_EQ(v[1], GSL::Complex{2.});
    EXPECT_EQ(v[2], GSL::Complex{3.});
}

TEST(Vector_cxTest, TestConstructionCopy)
{
    GSL::Complex a = 1., b = 2., c = 3.;
    GSL::Vector_Complex v1{a, b, c};
    GSL::Vector_Complex v2{v1.clone()};
    EXPECT_EQ(v1[0], GSL::Complex{v2[0]});
    EXPECT_EQ(v1[1], GSL::Complex{v2[1]});
    EXPECT_EQ(v1[2], GSL::Complex{v2[2]});
}

TEST(Vector_cxTest, TestConstructionMove)
{
    GSL::Complex a = 1., b = 2., c = 3.;
    GSL::Vector_Complex v1{a, b, c};
    GSL::Vector_Complex v2{std::move(v1)};
    EXPECT_EQ(v2[0], GSL::Complex{1.});
    EXPECT_EQ(v2[1], GSL::Complex{2.});
    EXPECT_EQ(v2[2], GSL::Complex{3.});
}

TEST(Vector_cxTest, TestEqual)
{

    GSL::Complex a = 1., b = 2., c = 3.;
    GSL::Vector_Complex v1{a, b, c};
    GSL::Vector_Complex v2{v1.clone()};

    EXPECT_EQ(v1, v2);
}

TEST(Vector_cxTest, TestNotEqual)
{

    GSL::Complex a = 1., b = 2., c = 3.;
    GSL::Vector_Complex v1{a, b, c};
    GSL::Vector_Complex v2{a +1, b, c};

    EXPECT_NE(v1, v2);
}

TEST(Vector_cxTest, TestCopy)
{

    GSL::Complex a = 1., b = 2., c = 3.;
    GSL::Vector_Complex v1{a, b, c};
    GSL::Vector_Complex v2 = v1.clone();

    EXPECT_EQ(v1, v2);
}

TEST(Vector_cxTest, TestMove)
{

    GSL::Complex a = 1., b = 2., c = 3.;
    GSL::Vector_Complex v1{a, b, c}, v1s{a, b, c};
    GSL::Vector_Complex v2 = std::move(v1);

    EXPECT_EQ(v2, v1s);
}

TEST(Vector_cxTest, TestDecayToGSLVector_cx)
{
    GSL::Complex a = 1., b = 2., c = 3.;
    GSL::Vector_Complex v{a, b, c};
    gsl_vector_complex gv = *v.gsl_data();

    EXPECT_EQ(GSL::Complex{gsl_vector_complex_get(&gv, 0)}, GSL::Complex{a});
}

TEST(Vector_cxTest, TestSize)
{
    GSL::Complex a = 1., b = 2., c = 3.;
    GSL::Vector_Complex v{a, b, c};

    EXPECT_EQ(v.size(), 3);
}

// TEST(Vector_cxTest, TestDim)
// {
//     GSL::Complex a = 1., b = 2., c = 3.;
//     GSL::Vector_Complex v{a, b, c};
//
//     EXPECT_EQ(v.dim(), 3);
// }

TEST(Vector_cxTest, TestCopyFun)
{
    GSL::Complex a = 1., b = 2., c = 3.;
    GSL::Vector_Complex v{a, b, c}, v2(3);
    v2.copy(v);

    EXPECT_EQ(v, v2);
}

TEST(Vector_cxTest, TestNorm)
{
    GSL::Complex a = 1., b = 2., c = 3.;
    GSL::Vector_Complex v{a, b, c};

    EXPECT_DOUBLE_EQ(v.norm(), std::sqrt(a.real()*a.real() + b.real()*b.real() + c.real()*c.real()));
}

TEST(Vector_cxTest, TestNormalize)
{
    GSL::Complex a = 1., b = 2., c = 3.;
    GSL::Vector_Complex v{a, b, c};
    v = normalize(v);

    EXPECT_DOUBLE_EQ(v.norm(), 1.);
}

TEST(Vector_cxTest, TestDot)
{
    GSL::Vector_Complex v1{1., 0., 0.}, v2{0., 1., 0.};

    EXPECT_EQ(dot(v1, v2), GSL::Complex{0.});
}

TEST(Vector_cxTest, TestCross)
{
    GSL::Vector_Complex v1{1., 0., 0.}, v2{0., 1., 0.}, v3{0., 0., 1.};

    EXPECT_EQ(cross(v1, v2), v3);
}

TEST(Vector_cxTest, TestIncrement)
{
    GSL::Vector_Complex v1{1., 0., 0.}, v2{0., 1., 0.}, v3{1., 1., 0.};

    EXPECT_EQ(v1 += v2, v3);
}

TEST(Vector_cxTest, TestDecrement)
{
    GSL::Vector_Complex v1{1., 0., 0.}, v2{0., 1., 0.}, v3{1., -1., 0.};

    EXPECT_EQ(v1 -= v2, v3);
}

TEST(Vector_cxTest, TestElMultScale)
{
    GSL::Vector_Complex v1{3., 2., 2.}, v2{2., 3., 4.}, v3{6., 6., 8.};

    EXPECT_EQ(v1 *= v2, v3);
}

TEST(Vector_cxTest, TestElDivScale)
{
    GSL::Vector_Complex v1{8., 4., 2.}, v2{6., 3., 2.}, v3{8./6, 4./3, 2./2};

    EXPECT_EQ(v1 /= v2, v3);
}

TEST(Vector_cxTest, TestMultScale)
{
    GSL::Vector_Complex v1{3., 2., 2.}, v2{9., 6., 6.};

    EXPECT_EQ(v1 *= GSL::Complex{3}, v2);
}

TEST(Vector_cxTest, TestDivScale)
{
    GSL::Vector_Complex v1{8., 4., 2.}, v2{4., 2., 1.};

    EXPECT_EQ(v1 /= GSL::Complex{2.}, v2);
}

TEST(Vector_cxTest, TestAddition)
{
    GSL::Vector_Complex v1{1., 0., 0.}, v2{0., 1., 0.}, v3{1., 1., 0.};

    EXPECT_EQ(v1 + v2, v3);
}

TEST(Vector_cxTest, TestSubtraction)
{
    GSL::Vector_Complex v1{1., 0., 0.}, v2{0., 1., 0.}, v3{1., -1., 0.};

    EXPECT_EQ(v1 - v2, v3);
}

TEST(Vector_cxTest, TestElMult)
{
    GSL::Vector_Complex v1{3., 2., 2.}, v2{2., 3., 4.}, v3{6., 6., 8.};

    EXPECT_EQ(v1 * v2, v3);
}

TEST(Vector_cxTest, TestElDiv)
{
    GSL::Vector_Complex v1{8., 4., 2.}, v2{6., 3., 2.}, v3{8./6, 4./3, 2./2};

    EXPECT_EQ(v1 / v2, v3);
}

TEST(Vector_cxTest, TestScalarMult)
{
    GSL::Vector_Complex v1{3., 2., 2.}, v2{9., 6., 6.};

    EXPECT_EQ(v1 * GSL::Complex(3.), v2);
}

TEST(Vector_cxTest, TestScalarDiv)
{
    GSL::Vector_Complex v1{8., 4., 2.}, v2{4., 2., 1.};

    EXPECT_EQ(v1 / GSL::Complex(2.), v2);
}

TEST(Vector_cxTest, TestScalarMult2)
{
    GSL::Vector_Complex v1{3., 2., 2.}, v2{9., 6., 6.};

    EXPECT_EQ(GSL::Complex(3.) * v1, v2);
}

TEST(Vector_cxTest, TestBegin)
{
    GSL::Vector_Complex v{1., 2., 3.};
    EXPECT_EQ(*v.view().begin(), GSL::Complex{1.});
}

TEST(Vector_cxTest, TestcBegin)
{
    GSL::Vector_Complex v{1., 2., 3.};
    EXPECT_EQ(*v.view().cbegin(), GSL::Complex{1.});
}

TEST(Vector_cxTest, TestIterPreIncrement)
{
    GSL::Vector_Complex v{1., 2., 3.};
    EXPECT_EQ(*++v.view().begin(), GSL::Complex{2.});
}

TEST(Vector_cxTest, TestIterPostIncrement)
{
    GSL::Vector_Complex v{1., 2., 3.};
    auto it = v.view().begin();
    it++;
    EXPECT_EQ(*it, GSL::Complex{2.});
}

TEST(Vector_cxTest, TestIterPreDecrement)
{
    GSL::Vector_Complex v{1., 2., 3.};
    EXPECT_EQ(*--(++v.view().begin()), GSL::Complex{1.});
}

TEST(Vector_cxTest, TestIterPostDecrement)
{
    GSL::Vector_Complex v{1., 2., 3.};
    auto it = v.view().begin();
    it++; it--;
    EXPECT_EQ(*it, GSL::Complex{1.});
}

TEST(Vector_cxTest, TestIterStepIncrement)
{
    GSL::Vector_Complex v{1., 2., 3.};
    auto it = v.view().begin();
    it += 2;
    EXPECT_EQ(*it, GSL::Complex{3.});
}

TEST(Vector_cxTest, TestIterStep)
{
    GSL::Vector_Complex v{1., 2., 3.};
    auto it = v.view().begin();
    EXPECT_EQ(*(it + 2), GSL::Complex{3.});
}

TEST(Vector_cxTest, TestIterStepDecrement)
{
    GSL::Vector_Complex v{1., 2., 3.};
    auto it = v.view().begin();
    it += 2;
    it -= 2;
    EXPECT_EQ(*it, GSL::Complex{1.});
}

TEST(Vector_cxTest, TestIterStepBack)
{
    GSL::Vector_Complex v{1., 2., 3.};
    auto it = v.view().begin() + 2;
    EXPECT_EQ(*(it - 2), GSL::Complex{1.});
}

TEST(Vector_cxTest, TestIterDiff)
{
    GSL::Vector_Complex v{1., 2., 3.};
    auto it = v.view().begin() + 2;
    EXPECT_EQ(it - v.view().begin(), 2.);
}

TEST(Vector_cxTest, TestIterEq)
{
    GSL::Vector_Complex v{1., 2., 3.};
    auto it1 = v.view().begin() + 2;
    auto it2 = v.view().begin();
    it2 += 2;

    EXPECT_EQ(it1, it2);
}

TEST(Vector_cxTest, TestIterNeq)
{
    GSL::Vector_Complex v{1., 2., 3.};
    auto it1 = v.view().begin() + 2;
    auto it2 = v.view().begin();

    EXPECT_NE(it1, it2);
}

TEST(Vector_cxTest, TestEnd)
{
    GSL::Vector_Complex v{1., 2., 3.};
    auto it1 = v.view().begin() + 2;
    auto it2 = v.view().end();

    EXPECT_EQ(*it1, *--it2);
}

TEST(Vector_cxTest, TestcIterPreIncrement)
{
    GSL::Vector_Complex v{1., 2., 3.};
    EXPECT_EQ(*++v.view().cbegin(), GSL::Complex{2.});
}

TEST(Vector_cxTest, TestcIterPostIncrement)
{
    GSL::Vector_Complex v{1., 2., 3.};
    auto it = v.view().cbegin();
    it++;
    EXPECT_EQ(*it, GSL::Complex{2.});
}

TEST(Vector_cxTest, TestcIterPreDecrement)
{
    GSL::Vector_Complex v{1., 2., 3.};
    EXPECT_EQ(*--(++v.view().cbegin()), GSL::Complex{1.});
}

TEST(Vector_cxTest, TestcIterPostDecrement)
{
    GSL::Vector_Complex v{1., 2., 3.};
    auto it = v.view().cbegin();
    it++; it--;
    EXPECT_EQ(*it, GSL::Complex{1.});
}

TEST(Vector_cxTest, TestcIterStepIncrement)
{
    GSL::Vector_Complex v{1., 2., 3.};
    auto it = v.view().cbegin();
    it += 2;
    EXPECT_EQ(*it, GSL::Complex{3.});
}

TEST(Vector_cxTest, TestcIterStep)
{
    GSL::Vector_Complex v{1., 2., 3.};
    auto it = v.view().cbegin();
    EXPECT_EQ(*(it + 2), GSL::Complex{3.});
}

TEST(Vector_cxTest, TestcIterStepDecrement)
{
    GSL::Vector_Complex v{1., 2., 3.};
    auto it = v.view().cbegin();
    it += 2;
    it -= 2;
    EXPECT_EQ(*it, GSL::Complex{1.});
}

TEST(Vector_cxTest, TestcIterStepBack)
{
    GSL::Vector_Complex v{1., 2., 3.};
    auto it = v.view().cbegin() + 2;
    EXPECT_EQ(*(it - 2), GSL::Complex{1.});
}

TEST(Vector_cxTest, TestcIterDiff)
{
    GSL::Vector_Complex v{1., 2., 3.};
    auto it = v.view().cbegin() + 2;
    EXPECT_EQ(it - v.view().cbegin(), 2.);
}

TEST(Vector_cxTest, TestcIterEq)
{
    GSL::Vector_Complex v{1., 2., 3.};
    auto it1 = v.view().cbegin() + 2;
    auto it2 = v.view().cbegin();
    it2 += 2;

    EXPECT_EQ(it1, it2);
}

TEST(Vector_cxTest, TestcIterNeq)
{
    GSL::Vector_Complex v{1., 2., 3.};
    auto it1 = v.view().cbegin() + 2;
    auto it2 = v.view().cbegin();

    EXPECT_NE(it1, it2);
}

TEST(Vector_cxTest, TestcEnd)
{
    GSL::Vector_Complex v{1., 2., 3.};
    auto it1 = v.view().cbegin() + 2;
    auto it2 = v.view().cend();

    EXPECT_EQ(*it1, *--it2);
}

TEST(Vector_cxTest, TestRbegin)
{
    GSL::Vector_Complex v{1., 2., 3.};
    auto it1 = v.view().rbegin();

    EXPECT_EQ(*it1, GSL::Complex{3.});
}

TEST(Vector_cxTest, TestRend)
{
    GSL::Vector_Complex v{1., 2., 3.};
    auto it1 = v.view().rend();

    EXPECT_EQ(*--it1, GSL::Complex{1.});
}

TEST(Vector_cxTest, TestcRbegin)
{
    GSL::Vector_Complex v{1., 2., 3.};
    auto it1 = v.view().crbegin();

    EXPECT_EQ(*it1, GSL::Complex{3.});
}

TEST(Vector_cxTest, TestcRend)
{
    GSL::Vector_Complex v{1., 2., 3.};
    auto it1 = v.view().crend();

    EXPECT_EQ(*--it1, GSL::Complex{1.});
}

TEST(Vector_cxTest, TestFront)
{
    GSL::Vector_Complex v{1., 2., 3.};
    EXPECT_EQ(v.view().front(), GSL::Complex{1.});
}

TEST(Vector_cxTest, TestBack)
{
    GSL::Vector_Complex v{1., 2., 3.};
    EXPECT_EQ(v.view().back(), GSL::Complex{3.});
}

TEST(Vector_cxTest, TestAt)
{
    GSL::Vector_Complex v{1., 2., 3.};
    EXPECT_EQ(v.at(1), GSL::Complex{2.});
}

// TEST(Vector_cxTest, TestAssignBegin)
// {
//     GSL::Vector_Complex v1{1., 2., 3.};
//     GSL::Vector_Complex v2{3., 4., 5.};
//     v2.assign(v1.view().begin(), v1.view().end());
//     EXPECT_EQ(v1, v2);
// }

// TEST(Vector_cxTest, TestAssignVal)
// {
//     GSL::Vector_Complex v1{1., 2., 3.};
//     GSL::Vector_Complex v2{3., 3., 3., 3.};
//     v1.assign(4, GSL::Complex(3.));
//     EXPECT_EQ(v1, v2);
// }

// TEST(Vector_cxTest, TestAssignList)
// {
//     GSL::Vector_Complex v1{1., 2., 3.};
//     GSL::Vector_Complex v2{3., 4.};
//     v1.assign({{3.}, {4.}});
//     EXPECT_EQ(v1, v2);
// }
