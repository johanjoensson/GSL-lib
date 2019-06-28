#include "GSLpp/complex.h"
#include "GSLpp/vector.h"
#include <gtest/gtest.h>
#include <iostream>

TEST(Vector_cxTest, TestConstruction)
{
    GSL::Vector_cx v(3);

    EXPECT_EQ(v[0], GSL::Complex{});
    EXPECT_EQ(v[1], GSL::Complex{});
    EXPECT_EQ(v[2], GSL::Complex{});
}

TEST(Vector_cxTest, TestConstructionInitializerList)
{
    GSL::Complex a = 1., b = 2., c = 3.;
    GSL::Vector_cx v{a, b, c};
    EXPECT_EQ(v[0], GSL::Complex{1.});
    EXPECT_EQ(v[1], GSL::Complex{2.});
    EXPECT_EQ(v[2], GSL::Complex{3.});
}

TEST(Vector_cxTest, TestConstructionCopy)
{
    GSL::Complex a = 1., b = 2., c = 3.;
    GSL::Vector_cx v1{a, b, c};
    GSL::Vector_cx v2{v1};
    EXPECT_EQ(v1[0], GSL::Complex{v2[0]});
    EXPECT_EQ(v1[1], GSL::Complex{v2[1]});
    EXPECT_EQ(v1[2], GSL::Complex{v2[2]});
}

TEST(Vector_cxTest, TestConstructionMove)
{
    GSL::Complex a = 1., b = 2., c = 3.;
    GSL::Vector_cx v1{a, b, c};
    GSL::Vector_cx v2{std::move(v1)};
    EXPECT_EQ(v2[0], GSL::Complex{1.});
    EXPECT_EQ(v2[1], GSL::Complex{2.});
    EXPECT_EQ(v2[2], GSL::Complex{3.});
}

TEST(Vector_cxTest, TestEqual)
{

    GSL::Complex a = 1., b = 2., c = 3.;
    GSL::Vector_cx v1{a, b, c};
    GSL::Vector_cx v2{v1};

    EXPECT_EQ(v1, v2);
}

TEST(Vector_cxTest, TestNotEqual)
{

    GSL::Complex a = 1., b = 2., c = 3.;
    GSL::Vector_cx v1{a, b, c};
    GSL::Vector_cx v2{a +1, b, c};

    EXPECT_NE(v1, v2);
}

TEST(Vector_cxTest, TestCopy)
{

    GSL::Complex a = 1., b = 2., c = 3.;
    GSL::Vector_cx v1{a, b, c};
    GSL::Vector_cx v2;
    v2 = v1;

    EXPECT_EQ(v1, v2);
}

TEST(Vector_cxTest, TestMove)
{

    GSL::Complex a = 1., b = 2., c = 3.;
    GSL::Vector_cx v1{a, b, c}, v1s{a, b, c};
    GSL::Vector_cx v2;
    v2 = std::move(v1);

    EXPECT_EQ(v2, v1s);
}

TEST(Vector_cxTest, TestDecayToGSLVector_cx)
{
    GSL::Complex a = 1., b = 2., c = 3.;
    GSL::Vector_cx v{a, b, c};
    gsl_vector_complex gv = v;

    EXPECT_EQ(gsl_vector_complex_get(&gv, 0), a);
}

TEST(Vector_cxTest, TestSize)
{
    GSL::Complex a = 1., b = 2., c = 3.;
    GSL::Vector_cx v{a, b, c};

    EXPECT_EQ(v.size(), 3);
}

TEST(Vector_cxTest, TestDim)
{
    GSL::Complex a = 1., b = 2., c = 3.;
    GSL::Vector_cx v{a, b, c};

    EXPECT_EQ(v.dim(), 3);
}

TEST(Vector_cxTest, TestCopyFun)
{
    GSL::Complex a = 1., b = 2., c = 3.;
    GSL::Vector_cx v{a, b, c}, v2;
    v2.copy(v);

    EXPECT_EQ(v, v2);
}

TEST(Vector_cxTest, TestNorm)
{
    GSL::Complex a = 1., b = 2., c = 3.;
    GSL::Vector_cx v{a, b, c};

    EXPECT_DOUBLE_EQ(v.norm<double>(), std::sqrt(a.re()*a.re() + b.re()*b.re() + c.re()*c.re()));
}

TEST(Vector_cxTest, TestNormalize)
{
    GSL::Complex a = 1., b = 2., c = 3.;
    GSL::Vector_cx v{a, b, c};
    v.normalize<double>();

    EXPECT_DOUBLE_EQ(v.norm<double>(), 1.);
}

TEST(Vector_cxTest, TestDot)
{
    GSL::Vector_cx v1{1., 0., 0.}, v2{0., 1., 0.};

    EXPECT_EQ(v1.dot(v2), GSL::Complex{0.});
}

TEST(Vector_cxTest, TestCross)
{
    GSL::Vector_cx v1{1., 0., 0.}, v2{0., 1., 0.}, v3{0., 0., 1.};

    EXPECT_EQ(v1.cross(v2), v3);
}

TEST(Vector_cxTest, TestIncrement)
{
    GSL::Vector_cx v1{1., 0., 0.}, v2{0., 1., 0.}, v3{1., 1., 0.};

    EXPECT_EQ(v1 += v2, v3);
}

TEST(Vector_cxTest, TestDecrement)
{
    GSL::Vector_cx v1{1., 0., 0.}, v2{0., 1., 0.}, v3{1., -1., 0.};

    EXPECT_EQ(v1 -= v2, v3);
}

TEST(Vector_cxTest, TestElMultScale)
{
    GSL::Vector_cx v1{3., 2., 2.}, v2{2., 3., 4.}, v3{6., 6., 8.};

    EXPECT_EQ(v1 *= v2, v3);
}

TEST(Vector_cxTest, TestElDivScale)
{
    GSL::Vector_cx v1{8., 4., 2.}, v2{6., 3., 2.}, v3{8./6, 4./3, 2./2};

    EXPECT_EQ(v1 /= v2, v3);
}

TEST(Vector_cxTest, TestMultScale)
{
    GSL::Vector_cx v1{3., 2., 2.}, v2{9., 6., 6.};

    EXPECT_EQ(v1 *= GSL::Complex{3}, v2);
}

TEST(Vector_cxTest, TestDivScale)
{
    GSL::Vector_cx v1{8., 4., 2.}, v2{4., 2., 1.};

    EXPECT_EQ(v1 /= GSL::Complex{2.}, v2);
}

TEST(Vector_cxTest, TestAddition)
{
    GSL::Vector_cx v1{1., 0., 0.}, v2{0., 1., 0.}, v3{1., 1., 0.};

    EXPECT_EQ(v1 + v2, v3);
}

TEST(Vector_cxTest, TestSubtraction)
{
    GSL::Vector_cx v1{1., 0., 0.}, v2{0., 1., 0.}, v3{1., -1., 0.};

    EXPECT_EQ(v1 - v2, v3);
}

TEST(Vector_cxTest, TestElMult)
{
    GSL::Vector_cx v1{3., 2., 2.}, v2{2., 3., 4.}, v3{6., 6., 8.};

    EXPECT_EQ(v1 * v2, v3);
}

TEST(Vector_cxTest, TestElDiv)
{
    GSL::Vector_cx v1{8., 4., 2.}, v2{6., 3., 2.}, v3{8./6, 4./3, 2./2};

    EXPECT_EQ(v1 / v2, v3);
}

TEST(Vector_cxTest, TestScalarMult)
{
    GSL::Vector_cx v1{3., 2., 2.}, v2{9., 6., 6.};

    EXPECT_EQ(v1 * GSL::Complex(3.), v2);
}

TEST(Vector_cxTest, TestScalarDiv)
{
    GSL::Vector_cx v1{8., 4., 2.}, v2{4., 2., 1.};

    EXPECT_EQ(v1 / GSL::Complex(2.), v2);
}

TEST(Vector_cxTest, TestScalarMult2)
{
    GSL::Vector_cx v1{3., 2., 2.}, v2{9., 6., 6.};

    EXPECT_EQ(GSL::Complex(3.) * v1, v2);
}

TEST(Vector_cxTest, TestBegin)
{
    GSL::Vector_cx v{1., 2., 3.};
    EXPECT_EQ(*v.begin(), GSL::Complex{1.});
}

TEST(Vector_cxTest, TestcBegin)
{
    GSL::Vector_cx v{1., 2., 3.};
    EXPECT_EQ(*v.cbegin(), GSL::Complex{1.});
}

TEST(Vector_cxTest, TestIterPreIncrement)
{
    GSL::Vector_cx v{1., 2., 3.};
    EXPECT_EQ(*++v.begin(), GSL::Complex{2.});
}

TEST(Vector_cxTest, TestIterPostIncrement)
{
    GSL::Vector_cx v{1., 2., 3.};
    auto it = v.begin();
    it++;
    EXPECT_EQ(*it, GSL::Complex{2.});
}

TEST(Vector_cxTest, TestIterPreDecrement)
{
    GSL::Vector_cx v{1., 2., 3.};
    EXPECT_EQ(*--(++v.begin()), GSL::Complex{1.});
}

TEST(Vector_cxTest, TestIterPostDecrement)
{
    GSL::Vector_cx v{1., 2., 3.};
    auto it = v.begin();
    it++; it--;
    EXPECT_EQ(*it, GSL::Complex{1.});
}

TEST(Vector_cxTest, TestIterStepIncrement)
{
    GSL::Vector_cx v{1., 2., 3.};
    auto it = v.begin();
    it += 2;
    EXPECT_EQ(*it, GSL::Complex{3.});
}

TEST(Vector_cxTest, TestIterStep)
{
    GSL::Vector_cx v{1., 2., 3.};
    auto it = v.begin();
    EXPECT_EQ(*(it + 2), GSL::Complex{3.});
}

TEST(Vector_cxTest, TestIterStepForward)
{
    GSL::Vector_cx v{1., 2., 3.};
    auto it = v.begin();
    EXPECT_EQ(*(2 + it), GSL::Complex{3.});
}

TEST(Vector_cxTest, TestIterStepDecrement)
{
    GSL::Vector_cx v{1., 2., 3.};
    auto it = v.begin();
    it += 2;
    it -= 2;
    EXPECT_EQ(*it, GSL::Complex{1.});
}

TEST(Vector_cxTest, TestIterStepBack)
{
    GSL::Vector_cx v{1., 2., 3.};
    auto it = v.begin() + 2;
    EXPECT_EQ(*(it - 2), GSL::Complex{1.});
}

TEST(Vector_cxTest, TestIterDiff)
{
    GSL::Vector_cx v{1., 2., 3.};
    auto it = v.begin() + 2;
    EXPECT_EQ(it - v.begin(), 2.);
}

TEST(Vector_cxTest, TestIterEq)
{
    GSL::Vector_cx v{1., 2., 3.};
    auto it1 = v.begin() + 2;
    auto it2 = v.begin();
    it2 += 2;

    EXPECT_EQ(it1, it2);
}

TEST(Vector_cxTest, TestIterNeq)
{
    GSL::Vector_cx v{1., 2., 3.};
    auto it1 = v.begin() + 2;
    auto it2 = v.begin();

    EXPECT_NE(it1, it2);
}

TEST(Vector_cxTest, TestEnd)
{
    GSL::Vector_cx v{1., 2., 3.};
    auto it1 = v.begin() + 2;
    auto it2 = v.end();

    EXPECT_EQ(it1, --it2);
}

TEST(Vector_cxTest, TestcIterPreIncrement)
{
    GSL::Vector_cx v{1., 2., 3.};
    EXPECT_EQ(*++v.cbegin(), GSL::Complex{2.});
}

TEST(Vector_cxTest, TestcIterPostIncrement)
{
    GSL::Vector_cx v{1., 2., 3.};
    auto it = v.cbegin();
    it++;
    EXPECT_EQ(*it, GSL::Complex{2.});
}

TEST(Vector_cxTest, TestcIterPreDecrement)
{
    GSL::Vector_cx v{1., 2., 3.};
    EXPECT_EQ(*--(++v.cbegin()), GSL::Complex{1.});
}

TEST(Vector_cxTest, TestcIterPostDecrement)
{
    GSL::Vector_cx v{1., 2., 3.};
    auto it = v.cbegin();
    it++; it--;
    EXPECT_EQ(*it, GSL::Complex{1.});
}

TEST(Vector_cxTest, TestcIterStepIncrement)
{
    GSL::Vector_cx v{1., 2., 3.};
    auto it = v.cbegin();
    it += 2;
    EXPECT_EQ(*it, GSL::Complex{3.});
}

TEST(Vector_cxTest, TestcIterStep)
{
    GSL::Vector_cx v{1., 2., 3.};
    auto it = v.cbegin();
    EXPECT_EQ(*(it + 2), GSL::Complex{3.});
}

TEST(Vector_cxTest, TestcIterStepForward)
{
    GSL::Vector_cx v{1., 2., 3.};
    auto it = v.cbegin();
    EXPECT_EQ(*(2 + it), GSL::Complex{3.});
}

TEST(Vector_cxTest, TestcIterStepDecrement)
{
    GSL::Vector_cx v{1., 2., 3.};
    auto it = v.cbegin();
    it += 2;
    it -= 2;
    EXPECT_EQ(*it, GSL::Complex{1.});
}

TEST(Vector_cxTest, TestcIterStepBack)
{
    GSL::Vector_cx v{1., 2., 3.};
    auto it = v.cbegin() + 2;
    EXPECT_EQ(*(it - 2), GSL::Complex{1.});
}

TEST(Vector_cxTest, TestcIterDiff)
{
    GSL::Vector_cx v{1., 2., 3.};
    auto it = v.cbegin() + 2;
    EXPECT_EQ(it - v.cbegin(), 2.);
}

TEST(Vector_cxTest, TestcIterEq)
{
    GSL::Vector_cx v{1., 2., 3.};
    auto it1 = v.cbegin() + 2;
    auto it2 = v.cbegin();
    it2 += 2;

    EXPECT_EQ(it1, it2);
}

TEST(Vector_cxTest, TestcIterNeq)
{
    GSL::Vector_cx v{1., 2., 3.};
    auto it1 = v.cbegin() + 2;
    auto it2 = v.cbegin();

    EXPECT_NE(it1, it2);
}

TEST(Vector_cxTest, TestcEnd)
{
    GSL::Vector_cx v{1., 2., 3.};
    auto it1 = v.cbegin() + 2;
    auto it2 = v.cend();

    EXPECT_EQ(it1, --it2);
}

TEST(Vector_cxTest, TestRbegin)
{
    GSL::Vector_cx v{1., 2., 3.};
    auto it1 = v.rbegin();

    EXPECT_EQ(*it1, GSL::Complex{3.});
}

TEST(Vector_cxTest, TestRend)
{
    GSL::Vector_cx v{1., 2., 3.};
    auto it1 = v.rend();

    EXPECT_EQ(*--it1, GSL::Complex{1.});
}

TEST(Vector_cxTest, TestcRbegin)
{
    GSL::Vector_cx v{1., 2., 3.};
    auto it1 = v.crbegin();

    EXPECT_EQ(*it1, GSL::Complex{3.});
}

TEST(Vector_cxTest, TestcRend)
{
    GSL::Vector_cx v{1., 2., 3.};
    auto it1 = v.crend();

    EXPECT_EQ(*--it1, GSL::Complex{1.});
}

TEST(Vector_cxTest, TestFront)
{
    GSL::Vector_cx v{1., 2., 3.};
    EXPECT_EQ(v.front(), GSL::Complex{1.});
}

TEST(Vector_cxTest, TestBack)
{
    GSL::Vector_cx v{1., 2., 3.};
    EXPECT_EQ(v.back(), GSL::Complex{3.});
}

TEST(Vector_cxTest, TestAt)
{
    GSL::Vector_cx v{1., 2., 3.};
    EXPECT_EQ(v.at(1), GSL::Complex{2.});
}

TEST(Vector_cxTest, TestAssign1)
{
    GSL::Vector_cx v1{1., 2., 3.};
    GSL::Vector_cx v2{3., 4., 5.};
    v2.assign(v1.begin(), v1.end());
    EXPECT_EQ(v1, v2);
}

TEST(Vector_cxTest, TestAssign2)
{
    GSL::Vector_cx v1{1., 2., 3.};
    GSL::Vector_cx v2{3., 3., 3., 3.};
    v1.assign(4, GSL::Complex(3.));
    EXPECT_EQ(v1, v2);
}

TEST(Vector_cxTest, TestAssign3)
{
    GSL::Vector_cx v1{1., 2., 3.};
    GSL::Vector_cx v2{3., 4.};
    v1.assign({{3.}, {4.}});
    EXPECT_EQ(v1, v2);
}
