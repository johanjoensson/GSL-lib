#include "GSLpp/matrix.h"
#include "GSLpp/vector.h"
#include <gtest/gtest.h>

TEST(Matrix_cxTest, TestConstruction)
{
    size_t rows = 2, columns = 2;
    GSL::Matrix_cx m(rows, columns);

    for(size_t i = 0; i < rows; i++){
        for(size_t j = 0; j < columns; j++){
            EXPECT_EQ(m[i][j], GSL::Matrix_cx::value_type{0});
        }
    }
}

TEST(Matrix_cxTest, TestConstructionInitializerList)
{
    GSL::Matrix_cx m{{1, 2}, {3, 4}};
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
    GSL::Matrix_cx m1{{1, 2}, {3, 4}}, m2(m1);
    for(size_t i = 0; i < rows; i++){
        for(size_t j = 0; j < columns; j++){
            EXPECT_EQ(m1[i][j], static_cast<GSL::Matrix_cx::value_type>(m2[i][j]));
        }
    }
}

TEST(Matrix_cxTest, TestConstructionMove)
{
    size_t rows = 2, columns = 2;
    GSL::Matrix_cx m1{{1, 2}, {3, 4}}, m2(std::move(m1));
    for(size_t i = 0; i < rows; i++){
        for(size_t j = 0; j < columns; j++){
            EXPECT_EQ(m2[i][j], GSL::Complex(static_cast<double>(columns*i+j+1)));
        }
    }
}

TEST(Matrix_cxTest, TestEqual)
{
    GSL::Matrix_cx m1{{1, 2}, {3, 4}}, m2(m1);
    EXPECT_TRUE(m1 == m2);
}

TEST(Matrix_cxTest, TestNequal)
{
    GSL::Matrix_cx m1{{1, 2}, {3, 4}}, m2(m1);
    EXPECT_FALSE(m1 != m2);
}

TEST(Matrix_cxTest, TestCopy)
{
    GSL::Matrix_cx m1{{1, 2}, {3, 4}}, m2;
    m2 = m1;
    EXPECT_EQ(m1, m2);
}

TEST(Matrix_cxTest, TestMove)
{
    GSL::Matrix_cx m1{{1, 2}, {3, 4}}, m1s(m1), m2;
    m2 = std::move(m1);
    EXPECT_EQ(m1s, m2);
}

TEST(Matrix_cxTest, TestCopy2)
{
    GSL::Matrix_cx m1{{1, 2}, {3, 4}}, m2;
    m2.copy(m1);
    EXPECT_EQ(m1, m2);
}

TEST(Matrix_cxTest, TestDecayToGSLMatrix_cx)
{
    GSL::Matrix_cx m{{1, 2}, {3, 4}};
    gsl_matrix_complex gm = m;
    EXPECT_EQ(gsl_matrix_complex_get(&gm, 0, 1), GSL::Matrix_cx::value_type{2});
}

TEST(Matrix_cxTest, TestDim)
{
    GSL::Matrix_cx m{{1, 2}, {3, 4}, {5, 6}};
    std::pair<size_t, size_t> d(3,2);
    EXPECT_EQ(m.dim(), d);
}

TEST(Matrix_cxTest, TestSize)
{
    GSL::Matrix_cx m{{1, 2}, {3, 4}, {5, 6}};
    std::pair<size_t, size_t> d(3,2);
    EXPECT_EQ(m.size(), d);
}

TEST(Matrix_cxTest, TestAddAssign)
{
    GSL::Matrix_cx m{{1, 2}, {3, 4}, {5, 6}}, n{{1, 2}, {3, 4}, {5, 6}};
    m += n;
    GSL::Matrix_cx res{{2, 4}, {6, 8}, {10, 12}};
    EXPECT_EQ(m, res);
}

TEST(Matrix_cxTest, TestSubAssign)
{
    GSL::Matrix_cx m{{1, 2}, {3, 4}, {5, 6}}, n{{1, 2}, {3, 4}, {5, 6}};
    m -= n;
    GSL::Matrix_cx res{{0, 0}, {0, 0}, {0, 0}};
    EXPECT_EQ(m, res);
}

TEST(Matrix_cxTest, TestMultAssign)
{
    GSL::Matrix_cx m{{1, 2}, {3, 4}, {5, 6}}, n{{1, 2, 3}, {4, 5, 6}};
    m *= n;
    GSL::Matrix_cx res{{9, 12, 15}, {19, 26, 33}, {29, 40, 51}};
    EXPECT_EQ(m, res);
}

TEST(Matrix_cxTest, TestDivAssign)
{
    GSL::Matrix_cx m{{1, 2}, {3, 4}, {5, 6}}, n{{1, 2}, {3, 4}, {5, 6}};
    m /= n;
    GSL::Matrix_cx res{{1, 1}, {1, 1}, {1, 1}};
    EXPECT_EQ(m, res);
}

TEST(Matrix_cxTest, TestMultScaleAssign)
{
    GSL::Matrix_cx m{{1, 2}, {3, 4}, {5, 6}};
    m *= 2;
    GSL::Matrix_cx res{{2, 4}, {6, 8}, {10, 12}};
    EXPECT_EQ(m, res);
}

TEST(Matrix_cxTest, TestDivScaleAssign)
{
    GSL::Matrix_cx m{{1, 2}, {3, 4}, {5, 6}};
    m /= 2;
    GSL::Matrix_cx res{{0.5, 1}, {1.5, 2}, {2.5, 3}};
    EXPECT_EQ(m, res);
}

TEST(Matrix_cxTest, TestAdd)
{
    GSL::Matrix_cx m{{1, 2}, {3, 4}, {5, 6}}, n{{1, 2}, {3, 4}, {5, 6}};
    GSL::Matrix_cx res{{2, 4}, {6, 8}, {10, 12}};
    EXPECT_EQ(m+n, res);
}

TEST(Matrix_cxTest, TestSub)
{
    GSL::Matrix_cx m{{1, 2}, {3, 4}, {5, 6}}, n{{1, 2}, {3, 4}, {5, 6}};
    GSL::Matrix_cx res{{0, 0}, {0, 0}, {0, 0}};
    EXPECT_EQ(m-n, res);
}

TEST(Matrix_cxTest, TestMult)
{
    GSL::Matrix_cx m{{1, 2}, {3, 4}, {5, 6}}, n{{1, 2, 3}, {4, 5, 6}};
    GSL::Matrix_cx res{{9, 12, 15}, {19, 26, 33}, {29, 40, 51}};
    EXPECT_EQ(m*n, res);
}

TEST(Matrix_cxTest, TestDiv)
{
    GSL::Matrix_cx m{{1, 2}, {3, 4}, {5, 6}}, n{{1, 2}, {3, 4}, {5, 6}};
    GSL::Matrix_cx res{{1, 1}, {1, 1}, {1, 1}};
    EXPECT_EQ(m/n, res);
}

TEST(Matrix_cxTest, TestMultScale)
{
    GSL::Matrix_cx m{{1, 2}, {3, 4}, {5, 6}};
    GSL::Matrix_cx res{{2, 4}, {6, 8}, {10, 12}};
    EXPECT_EQ(m*GSL::Matrix_cx::value_type{2}, res);
}

TEST(Matrix_cxTest, TestMultScale2)
{
    GSL::Matrix_cx m{{1, 2}, {3, 4}, {5, 6}};
    GSL::Matrix_cx res{{2, 4}, {6, 8}, {10, 12}};
    EXPECT_EQ(GSL::Matrix_cx::value_type{2}*m, res);
}

TEST(Matrix_cxTest, TestDivScale)
{
    GSL::Matrix_cx m{{1, 2}, {3, 4}, {5, 6}};
    GSL::Matrix_cx res{{0.5, 1}, {1.5, 2}, {2.5, 3}};
    EXPECT_EQ(m/GSL::Matrix_cx::value_type{2}, res);
}

TEST(Matrix_cxTest, TestTranspose)
{
    GSL::Matrix_cx m{{1, 2}, {3, 4}, {5, 6}};
    GSL::Matrix_cx res{{1, 3, 5},{2, 4, 6}};
    EXPECT_EQ(m.transpose(), res);
}

TEST(Matrix_cxTest, TestHermitian)
{
    GSL::Matrix_cx m{{{1, 6}, {2, 5}}, {{3, 4}, {4, 3}}, {{5, 2}, {6, 1}}};
    GSL::Matrix_cx res{{{1, -6}, {3, -4}, {5, -2}},{{2, -5}, {4, -3}, {6, -1}}};
    EXPECT_EQ(m.hermitian_transpose(), res);
}

TEST(Matrix_cxTest, TestGetRow)
{
    GSL::Matrix_cx m{{1, 2}, {3, 4}, {5, 6}};
    GSL::Vector_cx res{5, 6};
    EXPECT_EQ(m.get_row(2), res);
}

TEST(Matrix_cxTest, TestSetRow)
{
    GSL::Matrix_cx m{{1, 2}, {3, 4}, {5, 6}};
    GSL::Matrix_cx res{{1, 2}, {7, 8}, {5, 6}};
    m.get_row(1) = GSL::Vector_cx{7, 8};
    EXPECT_EQ(m, res);
}

TEST(Matrix_cxTest, TestGetCol)
{
    GSL::Matrix_cx m{{1, 2}, {3, 4}, {5, 6}};
    GSL::Vector_cx res{2, 4, 6};
    EXPECT_EQ(m.get_col(1), res);
}

TEST(Matrix_cxTest, TestSetCol)
{
    GSL::Matrix_cx m{{1, 2}, {3, 4}, {5, 6}};
    GSL::Matrix_cx res{{7, 2}, {8, 4}, {9, 6}};
    m.get_col(0) = GSL::Vector_cx{7, 8, 9};
    EXPECT_EQ(m, res);
}

TEST(Matrix_cxTest, TestBegin)
{
    GSL::Matrix_cx m{{1, 2}, {3, 4}, {5, 6}};
    GSL::Vector_cx res{1, 2};

    EXPECT_EQ(*m.begin(), res);
}

TEST(Matrix_cxTest, TestcBegin)
{
    GSL::Matrix_cx m{{1, 2}, {3, 4}, {5, 6}};
    GSL::Vector_cx res{1, 2};

    EXPECT_EQ(*m.cbegin(), res);
}

TEST(Matrix_cxTest, TestFront)
{
    GSL::Matrix_cx m{{1, 2}, {3, 4}, {5, 6}};
    GSL::Vector_cx res{1, 2};

    EXPECT_EQ(m.front(), res);
}

TEST(Matrix_cxTest, TestBack)
{
    GSL::Matrix_cx m{{1, 2}, {3, 4}, {5, 6}};
    GSL::Vector_cx res{5, 6};

    EXPECT_EQ(m.back(), res);
}

TEST(Matrix_cxTest, TestAt)
{
    GSL::Matrix_cx m{{1, 2}, {3, 4}, {5, 6}};
    GSL::Vector_cx res{3, 4};

    EXPECT_EQ(m.at(1), res);
}

TEST(Matrix_cxTest, TestAt2)
{
    GSL::Matrix_cx m{{1, 2}, {3, 4}, {5, 6}};
    GSL::Matrix_cx::value_type res{5};

    EXPECT_EQ(m.at(2, 0), res);
}

TEST(Matrix_cxTest, TestIterPreIncrement)
{
    GSL::Matrix_cx m{{1, 2}, {3, 4}, {5, 6}};
    EXPECT_EQ(*++m.begin(), m.at(1));
}

TEST(Matrix_cxTest, TestIterPostIncrement)
{
    GSL::Matrix_cx m{{1, 2}, {3, 4}, {5, 6}};
    auto it = m.begin();
    it++;
    EXPECT_EQ(*it, m.at(1));
}

TEST(Matrix_cxTest, TestIterPreDecrement)
{
    GSL::Matrix_cx m{{1, 2}, {3, 4}, {5, 6}};
    EXPECT_EQ(*--(++m.begin()), m.at(0));
}

TEST(Matrix_cxTest, TestIterPostDecrement)
{
    GSL::Matrix_cx m{{1, 2}, {3, 4}, {5, 6}};
    auto it = m.begin();
    (it++)--;
    EXPECT_EQ(*it, m.at(0));
}

TEST(Matrix_cxTest, TestIterAddAssign)
{
    GSL::Matrix_cx m{{1, 2}, {3, 4}, {5, 6}};
    auto it = m.begin();
    it += 2;
    EXPECT_EQ(*it, m.at(2));
}

TEST(Matrix_cxTest, TestIterSubAssign)
{
    GSL::Matrix_cx m{{1, 2}, {3, 4}, {5, 6}};
    auto it = m.begin();
    it += 2;
    it -= 1;
    EXPECT_EQ(*it, m.at(1));
}

TEST(Matrix_cxTest, TestIterAdd)
{
    GSL::Matrix_cx m{{1, 2}, {3, 4}, {5, 6}};
    auto it = m.begin();
    EXPECT_EQ(*(it + 2), m.at(2));
}

TEST(Matrix_cxTest, TestIterAdd2)
{
    GSL::Matrix_cx m{{1, 2}, {3, 4}, {5, 6}};
    auto it = m.begin();
    EXPECT_EQ(*(2 + it), m.at(2));
}

TEST(Matrix_cxTest, TestIterSub)
{
    GSL::Matrix_cx m{{1, 2}, {3, 4}, {5, 6}};
    auto it = m.begin();
    it += 2;
    EXPECT_EQ(*(it - 1), m.at(1));
}

TEST(Matrix_cxTest, TestIterSub2)
{
    GSL::Matrix_cx m{{1, 2}, {3, 4}, {5, 6}};
    auto it1 = m.begin(), it2 = m.begin();
    it2 += 2;
    EXPECT_EQ(it2 - it1, 2);
}

TEST(Matrix_cxTest, TestIterEq)
{
    GSL::Matrix_cx m{{1, 2}, {3, 4}, {5, 6}};
    auto it1 = m.begin(), it2 = m.begin();
    it2 += 2;
    EXPECT_EQ(*++(++it1), *it2);
}

TEST(Matrix_cxTest, TestIterNeq)
{
    GSL::Matrix_cx m{{1, 2}, {3, 4}, {5, 6}};
    auto it = m.begin();
    GSL::Vector_cx res{*it};
    EXPECT_NE(res, *(it + 1));
}

TEST(Matrix_cxTest, TestEnd)
{
    GSL::Matrix_cx m{{1, 2}, {3, 4}, {5, 6}};
    auto it1 = m.end();
    EXPECT_EQ(*--it1, *(m.begin() + 2));
}

TEST(Matrix_cxTest, TestcEnd)
{
    GSL::Matrix_cx m{{1, 2}, {3, 4}, {5, 6}};
    auto it1 = m.cend();
    EXPECT_EQ(*--it1, *(m.begin() + 2));
}

TEST(Matrix_cxTest, TestRbegin)
{
    GSL::Matrix_cx m{{1, 2}, {3, 4}, {5, 6}};
    GSL::Vector_cx res{5, 6};
    EXPECT_EQ(*m.rbegin(), res);
}

TEST(Matrix_cxTest, TestcRbegin)
{
    GSL::Matrix_cx m{{1, 2}, {3, 4}, {5, 6}};
    GSL::Vector_cx res{5, 6};
    EXPECT_EQ(*m.crbegin(), res);
}

TEST(Matrix_cxTest, TestRend)
{
    GSL::Matrix_cx m{{1, 2}, {3, 4}, {5, 6}};
    auto it1 = m.rend();
    EXPECT_EQ(*--it1, *(m.rbegin() + 2));
}

TEST(Matrix_cxTest, TestcRend)
{
    GSL::Matrix_cx m{{1, 2}, {3, 4}, {5, 6}};
    auto it1 = m.crend();
    EXPECT_EQ(*--it1, *(m.crbegin() + 2));
}
