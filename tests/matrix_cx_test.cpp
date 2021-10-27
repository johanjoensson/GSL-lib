#include "GSLpp/matrix_complex.h"
#include "GSLpp/vector_complex.h"
#include "GSLpp/complex.h"
#include <gtest/gtest.h>

TEST(Matrix_cxTest, TestConstruction)
{
    size_t rows = 2, columns = 2;
    GSL::Matrix_Complex m(rows, columns, GSL::Complex(0));

    for(size_t i = 0; i < rows; i++){
        for(size_t j = 0; j < columns; j++){
            EXPECT_EQ(m[i][j], GSL::Complex{0});
        }
    }
}

TEST(Matrix_cxTest, TestConstructionInitializerList)
{
    GSL::Matrix_Complex m{{1, 2}, {3, 4}};
    size_t rows = 2, columns = 2;
    for(size_t i = 0; i < rows; i++){
        for(size_t j = 0; j < columns; j++){
            EXPECT_EQ(m[i][j], GSL::Complex(static_cast<double>(columns*i+j+1)));
        }
    }
}

TEST(Matrix_cxTest, TestConstructionCopy)
{
    size_t rows = 2, columns = 2;
    GSL::Matrix_Complex m1{{1, 2}, {3, 4}}, m2(m1.clone());
    for(size_t i = 0; i < rows; i++){
        for(size_t j = 0; j < columns; j++){
            EXPECT_EQ(m1[i][j], m2[i][j]);
        }
    }
}

TEST(Matrix_cxTest, TestConstructionMove)
{
    size_t rows = 2, columns = 2;
    GSL::Matrix_Complex m1{{1, 2}, {3, 4}}, m2(std::move(m1));
    for(size_t i = 0; i < rows; i++){
        for(size_t j = 0; j < columns; j++){
            EXPECT_EQ(m2[i][j], GSL::Complex(static_cast<double>(columns*i+j+1)));
        }
    }
}

TEST(Matrix_cxTest, TestEqual)
{
    GSL::Matrix_Complex m1{{1, 2}, {3, 4}}, m2(m1.clone());
    EXPECT_TRUE(m1 == m2);
}

TEST(Matrix_cxTest, TestNequal)
{
    GSL::Matrix_Complex m1{{1, 2}, {3, 4}}, m2(m1.clone());
    EXPECT_FALSE(m1 != m2);
}

TEST(Matrix_cxTest, TestCopy)
{
    GSL::Matrix_Complex m1{{1, 2}, {3, 4}};
    GSL::Matrix_Complex m2 = m1.clone();
    EXPECT_EQ(m1, m2);
}

TEST(Matrix_cxTest, TestMove)
{
    GSL::Matrix_Complex m1{{1, 2}, {3, 4}}, m1s(m1.clone());
    GSL::Matrix_Complex m2 = std::move(m1);
    EXPECT_EQ(m1s, m2);
}

TEST(Matrix_cxTest, TestCopy2)
{
    GSL::Matrix_Complex m1{{1, 2}, {3, 4}}, m2(2,2);
    m2.copy(m1);
    EXPECT_EQ(m1, m2);
}

TEST(Matrix_cxTest, TestDecayToGSLMatrix_cx)
{
    GSL::Matrix_Complex m{{1, 2}, {3, 4}};
    gsl_matrix_complex gm = *m.gsl_data();
    EXPECT_EQ(GSL::Complex(gsl_matrix_complex_get(&gm, 0, 1)), GSL::Complex{2});
}

TEST(Matrix_cxTest, TestDim)
{
    GSL::Matrix_Complex m{{1, 2}, {3, 4}, {5, 6}};
    std::pair<size_t, size_t> d(3,2);
    EXPECT_EQ(m.dim(), d);
}

TEST(Matrix_cxTest, TestSize)
{
    GSL::Matrix_Complex m{{1, 2}, {3, 4}, {5, 6}};
    std::pair<size_t, size_t> d(3,2);
    EXPECT_EQ(m.dim(), d);
}

TEST(Matrix_cxTest, TestAddAssign)
{
    GSL::Matrix_Complex m{{1, 2}, {3, 4}, {5, 6}}, n{{1, 2}, {3, 4}, {5, 6}};
    m += n;
    GSL::Matrix_Complex res{{2, 4}, {6, 8}, {10, 12}};
    EXPECT_EQ(m, res);
}

TEST(Matrix_cxTest, TestSubAssign)
{
    GSL::Matrix_Complex m{{1, 2}, {3, 4}, {5, 6}}, n{{1, 2}, {3, 4}, {5, 6}};
    m -= n;
    GSL::Matrix_Complex res{{0, 0}, {0, 0}, {0, 0}};
    EXPECT_EQ(m, res);
}

TEST(Matrix_cxTest, TestMultAssign)
{
    GSL::Matrix_Complex m{{1, 2}, {3, 4}, {5, 6}}, n{{2, 3}, {4, 5}, {6, 7}};
    m *= n;
    GSL::Matrix_Complex res{{2, 6}, {12, 20}, {30, 42}};
    EXPECT_EQ(m, res);
}

TEST(Matrix_cxTest, TestDivAssign)
{
    GSL::Matrix_Complex m{{1, 2}, {3, 4}, {5, 6}}, n{{1, 2}, {3, 4}, {5, 6}};
    m /= n;
    GSL::Matrix_Complex res{{1, 1}, {1, 1}, {1, 1}};
    EXPECT_EQ(m, res);
}

TEST(Matrix_cxTest, TestMultScaleAssign)
{
    GSL::Matrix_Complex m{{1, 2}, {3, 4}, {5, 6}};
    m *= 2;
    GSL::Matrix_Complex res{{2, 4}, {6, 8}, {10, 12}};
    EXPECT_EQ(m, res);
}

TEST(Matrix_cxTest, TestDivScaleAssign)
{
    GSL::Matrix_Complex m{{1, 2}, {3, 4}, {5, 6}};
    m /= 2;
    GSL::Matrix_Complex res{{0.5, 1}, {1.5, 2}, {2.5, 3}};
    EXPECT_EQ(m, res);
}

TEST(Matrix_cxTest, TestAdd)
{
    GSL::Matrix_Complex m{{1, 2}, {3, 4}, {5, 6}}, n{{1, 2}, {3, 4}, {5, 6}};
    GSL::Matrix_Complex res{{2, 4}, {6, 8}, {10, 12}};
    EXPECT_EQ(m+n, res);
}

TEST(Matrix_cxTest, TestSub)
{
    GSL::Matrix_Complex m{{1, 2}, {3, 4}, {5, 6}}, n{{1, 2}, {3, 4}, {5, 6}};
    GSL::Matrix_Complex res{{0, 0}, {0, 0}, {0, 0}};
    EXPECT_EQ(m-n, res);
}

TEST(Matrix_cxTest, TestMult)
{
    GSL::Matrix_Complex m{{1, 2}, {3, 4}, {5, 6}}, n{{2, 3}, {4, 5}, {6, 7}};
    GSL::Matrix_Complex res{{2, 6}, {12, 20}, {30, 42}};
    EXPECT_EQ(m*n, res);
}

TEST(Matrix_cxTest, TestDiv)
{
    GSL::Matrix_Complex m{{1, 2}, {3, 4}, {5, 6}}, n{{1, 2}, {3, 4}, {5, 6}};
    GSL::Matrix_Complex res{{1, 1}, {1, 1}, {1, 1}};
    EXPECT_EQ(m/n, res);
}

TEST(Matrix_cxTest, TestMultScale)
{
    GSL::Matrix_Complex m{{1, 2}, {3, 4}, {5, 6}};
    GSL::Matrix_Complex res{{2, 4}, {6, 8}, {10, 12}};
    EXPECT_EQ(m*GSL::Complex{2}, res);
}

TEST(Matrix_cxTest, TestMultScale2)
{
    GSL::Matrix_Complex m{{1, 2}, {3, 4}, {5, 6}};
    GSL::Matrix_Complex res{{2, 4}, {6, 8}, {10, 12}};
    EXPECT_EQ(GSL::Complex{2}*m, res);
}

TEST(Matrix_cxTest, TestDivScale)
{
    GSL::Matrix_Complex m{{1, 2}, {3, 4}, {5, 6}};
    GSL::Matrix_Complex res{{0.5, 1}, {1.5, 2}, {2.5, 3}};
    EXPECT_EQ(m/GSL::Complex{2}, res);
}

TEST(Matrix_cxTest, TestTranspose)
{
    GSL::Matrix_Complex m{{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    GSL::Matrix_Complex res{{1, 4, 7},{2, 5, 8}, {3, 6, 9}};
    EXPECT_EQ(m.transpose(), res);
}

TEST(Matrix_cxTest, TestHermitian)
{
    GSL::Matrix_Complex m{{{1, 6}, {2, 5}, {3, 4}}, {{4, 4}, {5, 3}, {6, 2}}, {{7, 2}, {8, 1}, {9, 0}}};
    std::cout << "m = " << m << "\n";
    std::cout << "mH = " << m.hermitian_transpose() << "\n";
    GSL::Matrix_Complex res{{{1, -6}, {4, -4}, {7, -2}}, {{2, -5}, {5, -3}, {8, -1}}, {{3, -4}, {6, -2}, {9, 0}}};
    EXPECT_EQ(m, res);
}

TEST(Matrix_cxTest, TestGetRow)
{
    GSL::Matrix_Complex m{{1, 2}, {3, 4}, {5, 6}};
    GSL::Vector_Complex res{5, 6};
    EXPECT_EQ(m.row(2), res);
}

TEST(Matrix_cxTest, TestSetRow)
{
    GSL::Matrix_Complex m{{1, 2}, {3, 4}, {5, 6}};
    GSL::Matrix_Complex res{{1, 2}, {7, 8}, {5, 6}};
    m.row(1) = GSL::Vector_Complex{7, 8};
    EXPECT_EQ(m, res);
}

TEST(Matrix_cxTest, TestGetCol)
{
    GSL::Matrix_Complex m{{1, 2}, {3, 4}, {5, 6}};
    GSL::Vector_Complex res{2, 4, 6};
    EXPECT_EQ(m.column(1), res);
}

TEST(Matrix_cxTest, TestSetCol)
{
    GSL::Matrix_Complex m{{1, 2}, {3, 4}, {5, 6}};
    GSL::Matrix_Complex res{{7, 2}, {8, 4}, {9, 6}};
    m.column(0) = GSL::Vector_Complex{7, 8, 9};
    EXPECT_EQ(m, res);
}

TEST(Matrix_cxTest, TestBegin)
{
    GSL::Matrix_Complex m{{1, 2}, {3, 4}, {5, 6}};
    GSL::Vector_Complex res{1, 2};

    EXPECT_EQ(*m.view().begin(), res);
}

TEST(Matrix_cxTest, TestcBegin)
{
    GSL::Matrix_Complex m{{1, 2}, {3, 4}, {5, 6}};
    GSL::Vector_Complex res{1, 2};

    EXPECT_EQ(*m.view().cbegin(), res);
}

TEST(Matrix_cxTest, TestFront)
{
    GSL::Matrix_Complex m{{1, 2}, {3, 4}, {5, 6}};
    GSL::Vector_Complex res{1, 2};

    EXPECT_EQ(m.view().front(), res);
}

TEST(Matrix_cxTest, TestBack)
{
    GSL::Matrix_Complex m{{1, 2}, {3, 4}, {5, 6}};
    GSL::Vector_Complex res{5, 6};

    EXPECT_EQ(m.view().back(), res);
}

TEST(Matrix_cxTest, TestAt)
{
    GSL::Matrix_Complex m{{1, 2}, {3, 4}, {5, 6}};
    GSL::Vector_Complex res{3, 4};

    EXPECT_EQ(m.at(1), res);
}

TEST(Matrix_cxTest, TestAt2)
{
    GSL::Matrix_Complex m{{1, 2}, {3, 4}, {5, 6}};
    GSL::Complex res{5};

    EXPECT_EQ(m.at(2, 0), res);
}

TEST(Matrix_cxTest, TestIterPreIncrement)
{
    GSL::Matrix_Complex m{{1, 2}, {3, 4}, {5, 6}};
    EXPECT_EQ(*++m.view().begin(), m.at(1));
}

TEST(Matrix_cxTest, TestIterPostIncrement)
{
    GSL::Matrix_Complex m{{1, 2}, {3, 4}, {5, 6}};
    auto it = m.view().begin();
    EXPECT_EQ(*it++, m.at(0));
    EXPECT_EQ(*it, m.at(1));
}

TEST(Matrix_cxTest, TestIterPreDecrement)
{
    GSL::Matrix_Complex m{{1, 2}, {3, 4}, {5, 6}};
    EXPECT_EQ(*--(++m.view().begin()), m.at(0));
}

TEST(Matrix_cxTest, TestIterPostDecrement)
{
    GSL::Matrix_Complex m{{1, 2}, {3, 4}, {5, 6}};
    auto it = ++m.view().begin();
    EXPECT_EQ(*it--, m.at(1));
    EXPECT_EQ(*it, m.at(0));
}

TEST(Matrix_cxTest, TestIterAddAssign)
{
    GSL::Matrix_Complex m{{1, 2}, {3, 4}, {5, 6}};
    auto it = m.view().begin();
    it += 2;
    EXPECT_EQ(*it, m.at(2));
}

TEST(Matrix_cxTest, TestIterSubAssign)
{
    GSL::Matrix_Complex m{{1, 2}, {3, 4}, {5, 6}};
    auto it = m.view().begin();
    it += 2;
    it -= 1;
    EXPECT_EQ(*it, m.at(1));
}

TEST(Matrix_cxTest, TestIterAdd)
{
    GSL::Matrix_Complex m{{1, 2}, {3, 4}, {5, 6}};
    auto it = m.view().begin();
    EXPECT_EQ(*(it + 2), m.at(2));
}

TEST(Matrix_cxTest, TestIterAdd2)
{
    GSL::Matrix_Complex m{{1, 2}, {3, 4}, {5, 6}};
    auto it = m.view().begin();
    EXPECT_EQ(*(2 + it), m.at(2));
}

TEST(Matrix_cxTest, TestIterSub)
{
    GSL::Matrix_Complex m{{1, 2}, {3, 4}, {5, 6}};
    auto it = m.view().begin();
    it += 2;
    EXPECT_EQ(*(it - 1), m.at(1));
}

TEST(Matrix_cxTest, TestIterSub2)
{
    GSL::Matrix_Complex m{{1, 2}, {3, 4}, {5, 6}};
    auto it1 = m.view().begin(), it2 = m.view().begin();
    it2 += 2;
    EXPECT_EQ(it2 - it1, 2);
}

TEST(Matrix_cxTest, TestIterEq)
{
    GSL::Matrix_Complex m{{1, 2}, {3, 4}, {5, 6}};
    auto it1 = m.view().begin(), it2 = m.view().begin();
    it2 += 2;
    EXPECT_EQ(*++(++it1), *it2);
}

TEST(Matrix_cxTest, TestIterNeq)
{
    GSL::Matrix_Complex m{{1, 2}, {3, 4}, {5, 6}};
    auto it = m.view().begin();
    GSL::Vector_Complex res{*it};
    EXPECT_NE(res, *(it + 1));
}

TEST(Matrix_cxTest, TestEnd)
{
    GSL::Matrix_Complex m{{1, 2}, {3, 4}, {5, 6}};
    auto it1 = m.view().end();
    EXPECT_EQ(*--it1, *(m.view().begin() + 2));
}

TEST(Matrix_cxTest, TestcEnd)
{
    GSL::Matrix_Complex m{{1, 2}, {3, 4}, {5, 6}};
    auto it1 = m.view().cend();
    EXPECT_EQ(*--it1, *(m.view().begin() + 2));
}

TEST(Matrix_cxTest, TestRbegin)
{
    GSL::Matrix_Complex m{{1, 2}, {3, 4}, {5, 6}};
    GSL::Vector_Complex res{5, 6};
    EXPECT_EQ(*m.view().rbegin(), res);
}

TEST(Matrix_cxTest, TestcRbegin)
{
    GSL::Matrix_Complex m{{1, 2}, {3, 4}, {5, 6}};
    GSL::Vector_Complex res{5, 6};
    EXPECT_EQ(*m.view().crbegin(), res);
}

TEST(Matrix_cxTest, TestRend)
{
    GSL::Matrix_Complex m{{1, 2}, {3, 4}, {5, 6}};
    auto it1 = m.view().rend();
    EXPECT_EQ(*--it1, *(m.view().rbegin() + 2));
}

TEST(Matrix_cxTest, TestcRend)
{
    GSL::Matrix_Complex m{{1, 2}, {3, 4}, {5, 6}};
    auto it1 = m.view().crend();
    EXPECT_EQ(*--it1, *(m.view().crbegin() + 2));
}
