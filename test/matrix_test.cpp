#include "GSLpp/matrix.h"
#include "GSLpp/vector.h"
#include <gtest/gtest.h>

TEST(MatrixTest, TestConstruction)
{
    size_t rows = 2, columns = 2;
    GSL::Matrix m(rows, columns);

    for(size_t i = 0; i < rows; i++){
        for(size_t j = 0; j < columns; j++){
            EXPECT_DOUBLE_EQ(m[i][j], 0);
        }
    }
}

TEST(MatrixTest, TestConstructionInitializerList)
{
    GSL::Matrix m{{1, 2}, {3, 4}};
    size_t rows = 2, columns = 2;
    for(size_t i = 0; i < rows; i++){
        for(size_t j = 0; j < columns; j++){
            EXPECT_DOUBLE_EQ(m[i][j], static_cast<double>(columns*i+j)+1);
        }
    }
}

TEST(MatrixTest, TestConstructionCopy)
{
    size_t rows = 2, columns = 2;
    GSL::Matrix m1{{1, 2}, {3, 4}}, m2(m1);
    for(size_t i = 0; i < rows; i++){
        for(size_t j = 0; j < columns; j++){
            EXPECT_DOUBLE_EQ(m1[i][j], m2[i][j]);
        }
    }
}

TEST(MatrixTest, TestConstructionMove)
{
    size_t rows = 2, columns = 2;
    GSL::Matrix m1{{1, 2}, {3, 4}}, m2(std::move(m1));
    for(size_t i = 0; i < rows; i++){
        for(size_t j = 0; j < columns; j++){
            EXPECT_DOUBLE_EQ(m2[i][j], static_cast<double>(columns*i+j)+1);
        }
    }
}

TEST(MatrixTest, TestEqual)
{
    GSL::Matrix m1{{1, 2}, {3, 4}}, m2(m1);
    EXPECT_TRUE(m1 == m2);
}

TEST(MatrixTest, TestNequal)
{
    GSL::Matrix m1{{1, 2}, {3, 4}}, m2(m1);
    EXPECT_FALSE(m1 != m2);
}

TEST(MatrixTest, TestCopy)
{
    GSL::Matrix m1{{1, 2}, {3, 4}}, m2;
    m2 = m1;
    EXPECT_EQ(m1, m2);
}

TEST(MatrixTest, TestMove)
{
    GSL::Matrix m1{{1, 2}, {3, 4}}, m1s(m1), m2;
    m2 = std::move(m1);
    EXPECT_EQ(m1s, m2);
}

TEST(MatrixTest, TestCopy2)
{
    GSL::Matrix m1{{1, 2}, {3, 4}}, m2;
    m2.copy(m1);
    EXPECT_EQ(m1, m2);
}

TEST(MatrixTest, TestDecayToGSLMatrix)
{
    GSL::Matrix m{{1, 2}, {3, 4}};
    gsl_matrix gm = m;
    EXPECT_DOUBLE_EQ(gsl_matrix_get(&gm, 0, 1), 2);
}

TEST(MatrixTest, TestDim)
{
    GSL::Matrix m{{1, 2}, {3, 4}, {5, 6}};
    std::pair<size_t, size_t> d(3,2);
    EXPECT_EQ(m.dim(), d);
}

TEST(MatrixTest, TestSize)
{
    GSL::Matrix m{{1, 2}, {3, 4}, {5, 6}};
    std::pair<size_t, size_t> d(3,2);
    EXPECT_EQ(m.size(), d);
}

TEST(MatrixTest, TestAddAssign)
{
    GSL::Matrix m{{1, 2}, {3, 4}, {5, 6}}, n{{1, 2}, {3, 4}, {5, 6}};
    m += n;
    GSL::Matrix res{{2, 4}, {6, 8}, {10, 12}};
    EXPECT_EQ(m, res);
}

TEST(MatrixTest, TestSubAssign)
{
    GSL::Matrix m{{1, 2}, {3, 4}, {5, 6}}, n{{1, 2}, {3, 4}, {5, 6}};
    m -= n;
    GSL::Matrix res{{0, 0}, {0, 0}, {0, 0}};
    EXPECT_EQ(m, res);
}

TEST(MatrixTest, TestMultAssign)
{
    GSL::Matrix m{{1, 2}, {3, 4}, {5, 6}}, n{{1, 2, 3}, {4, 5, 6}};
    m *= n;
    GSL::Matrix res{{9, 12, 15}, {19, 26, 33}, {29, 40, 51}};
    EXPECT_EQ(m, res);
}

TEST(MatrixTest, TestDivAssign)
{
    GSL::Matrix m{{1, 2}, {3, 4}, {5, 6}}, n{{1, 2}, {3, 4}, {5, 6}};
    m /= n;
    GSL::Matrix res{{1, 1}, {1, 1}, {1, 1}};
    EXPECT_EQ(m, res);
}

TEST(MatrixTest, TestMultScaleAssign)
{
    GSL::Matrix m{{1, 2}, {3, 4}, {5, 6}};
    m *= 2;
    GSL::Matrix res{{2, 4}, {6, 8}, {10, 12}};
    EXPECT_EQ(m, res);
}

TEST(MatrixTest, TestDivScaleAssign)
{
    GSL::Matrix m{{1, 2}, {3, 4}, {5, 6}};
    m /= 2;
    GSL::Matrix res{{0.5, 1}, {1.5, 2}, {2.5, 3}};
    EXPECT_EQ(m, res);
}

TEST(MatrixTest, TestAdd)
{
    GSL::Matrix m{{1, 2}, {3, 4}, {5, 6}}, n{{1, 2}, {3, 4}, {5, 6}};
    GSL::Matrix res{{2, 4}, {6, 8}, {10, 12}};
    EXPECT_EQ(m+n, res);
}

TEST(MatrixTest, TestSub)
{
    GSL::Matrix m{{1, 2}, {3, 4}, {5, 6}}, n{{1, 2}, {3, 4}, {5, 6}};
    GSL::Matrix res{{0, 0}, {0, 0}, {0, 0}};
    EXPECT_EQ(m-n, res);
}

TEST(MatrixTest, TestMult)
{
    GSL::Matrix m{{1, 2}, {3, 4}, {5, 6}}, n{{1, 2, 3}, {4, 5, 6}};
    GSL::Matrix res{{9, 12, 15}, {19, 26, 33}, {29, 40, 51}};
    EXPECT_EQ(m*n, res);
}

TEST(MatrixTest, TestDiv)
{
    GSL::Matrix m{{1, 2}, {3, 4}, {5, 6}}, n{{1, 2}, {3, 4}, {5, 6}};
    GSL::Matrix res{{1, 1}, {1, 1}, {1, 1}};
    EXPECT_EQ(m/n, res);
}

TEST(MatrixTest, TestMultScale)
{
    GSL::Matrix m{{1, 2}, {3, 4}, {5, 6}};
    GSL::Matrix res{{2, 4}, {6, 8}, {10, 12}};
    EXPECT_EQ(m*double(2), res);
}

TEST(MatrixTest, TestMultScale2)
{
    GSL::Matrix m{{1, 2}, {3, 4}, {5, 6}};
    GSL::Matrix res{{2, 4}, {6, 8}, {10, 12}};
    EXPECT_EQ(2*m, res);
}

TEST(MatrixTest, TestDivScale)
{
    GSL::Matrix m{{1, 2}, {3, 4}, {5, 6}};
    GSL::Matrix res{{0.5, 1}, {1.5, 2}, {2.5, 3}};
    EXPECT_EQ(m/2, res);
}

TEST(MatrixTest, TestTranspose)
{
    GSL::Matrix m{{1, 2}, {3, 4}, {5, 6}};
    GSL::Matrix res{{1, 3, 5},{2, 4, 6}};
    EXPECT_EQ(m.transpose(), res);
}

TEST(MatrixTest, TestHermitian)
{
    GSL::Matrix m{{1, 2}, {3, 4}, {5, 6}};
    GSL::Matrix res{{1, 3, 5},{2, 4, 6}};
    EXPECT_EQ(m.hermitian_transpose(), res);
}

TEST(MatrixTest, TestGetRow)
{
    GSL::Matrix m{{1, 2}, {3, 4}, {5, 6}};
    GSL::Vector res{5, 6};
    EXPECT_EQ(m.get_row(2), res);
}

TEST(MatrixTest, TestSetRow)
{
    GSL::Matrix m{{1, 2}, {3, 4}, {5, 6}};
    GSL::Matrix res{{1, 2}, {7, 8}, {5, 6}};
    m.get_row(1) = GSL::Vector{7, 8};
    EXPECT_EQ(m, res);
}

TEST(MatrixTest, TestGetCol)
{
    GSL::Matrix m{{1, 2}, {3, 4}, {5, 6}};
    GSL::Vector res{2, 4, 6};
    EXPECT_EQ(m.get_col(1), res);
}

TEST(MatrixTest, TestSetCol)
{
    GSL::Matrix m{{1, 2}, {3, 4}, {5, 6}};
    GSL::Matrix res{{7, 2}, {8, 4}, {9, 6}};
    m.get_col(0) = GSL::Vector{7, 8, 9};
    EXPECT_EQ(m, res);
}

TEST(MatrixTest, TestBegin)
{
    GSL::Matrix m{{1, 2}, {3, 4}, {5, 6}};
    GSL::Vector res{1, 2};

    EXPECT_EQ(*m.begin(), res);
}

TEST(MatrixTest, TestcBegin)
{
    GSL::Matrix m{{1, 2}, {3, 4}, {5, 6}};
    GSL::Vector res{1, 2};

    EXPECT_EQ(*m.cbegin(), res);
}

TEST(MatrixTest, TestFront)
{
    GSL::Matrix m{{1, 2}, {3, 4}, {5, 6}};
    GSL::Vector res{1, 2};

    EXPECT_EQ(m.front(), res);
}

TEST(MatrixTest, TestBack)
{
    GSL::Matrix m{{1, 2}, {3, 4}, {5, 6}};
    GSL::Vector res{5, 6};

    EXPECT_EQ(m.back(), res);
}

TEST(MatrixTest, TestAt)
{
    GSL::Matrix m{{1, 2}, {3, 4}, {5, 6}};
    GSL::Vector res{3, 4};

    EXPECT_EQ(m.at(1), res);
}

TEST(MatrixTest, TestAt2)
{
    GSL::Matrix m{{1, 2}, {3, 4}, {5, 6}};
    GSL::Matrix::value_type res{5};

    EXPECT_EQ(m.at(2, 0), res);
}

TEST(MatrixTest, TestIterPreIncrement)
{
    GSL::Matrix m{{1, 2}, {3, 4}, {5, 6}};
    EXPECT_EQ(*++m.begin(), m.at(1));
}

TEST(MatrixTest, TestIterPostIncrement)
{
    GSL::Matrix m{{1, 2}, {3, 4}, {5, 6}};
    auto it = m.begin();
    it++;
    EXPECT_EQ(*it, m.at(1));
}

TEST(MatrixTest, TestIterPreDecrement)
{
    GSL::Matrix m{{1, 2}, {3, 4}, {5, 6}};
    EXPECT_EQ(*--(++m.begin()), m.at(0));
}

TEST(MatrixTest, TestIterPostDecrement)
{
    GSL::Matrix m{{1, 2}, {3, 4}, {5, 6}};
    auto it = m.begin();
    (it++)--;
    EXPECT_EQ(*it, m.at(0));
}

TEST(MatrixTest, TestIterAddAssign)
{
    GSL::Matrix m{{1, 2}, {3, 4}, {5, 6}};
    auto it = m.begin();
    it += 2;
    EXPECT_EQ(*it, m.at(2));
}

TEST(MatrixTest, TestIterSubAssign)
{
    GSL::Matrix m{{1, 2}, {3, 4}, {5, 6}};
    auto it = m.begin();
    it += 2;
    it -= 1;
    EXPECT_EQ(*it, m.at(1));
}

TEST(MatrixTest, TestIterAdd)
{
    GSL::Matrix m{{1, 2}, {3, 4}, {5, 6}};
    auto it = m.begin();
    EXPECT_EQ(*(it + 2), m.at(2));
}

TEST(MatrixTest, TestIterAdd2)
{
    GSL::Matrix m{{1, 2}, {3, 4}, {5, 6}};
    auto it = m.begin();
    EXPECT_EQ(*(2 + it), m.at(2));
}

TEST(MatrixTest, TestIterSub)
{
    GSL::Matrix m{{1, 2}, {3, 4}, {5, 6}};
    auto it = m.begin();
    it += 2;
    EXPECT_EQ(*(it - 1), m.at(1));
}

TEST(MatrixTest, TestIterSub2)
{
    GSL::Matrix m{{1, 2}, {3, 4}, {5, 6}};
    auto it1 = m.begin(), it2 = m.begin();
    it2 += 2;
    EXPECT_EQ(it2 - it1, 2);
}

TEST(MatrixTest, TestIterEq)
{
    GSL::Matrix m{{1, 2}, {3, 4}, {5, 6}};
    auto it1 = m.begin(), it2 = m.begin();
    it2 += 2;
    EXPECT_EQ(*++(++it1), *it2);
}

TEST(MatrixTest, TestIterNeq)
{
    GSL::Matrix m{{1, 2}, {3, 4}, {5, 6}};
    auto it = m.begin();
    GSL::Vector res{*it};
    EXPECT_NE(res, *(it + 1));
}

TEST(MatrixTest, TestEnd)
{
    GSL::Matrix m{{1, 2}, {3, 4}, {5, 6}};
    auto it1 = m.end();
    EXPECT_EQ(*--it1, *(m.begin() + 2));
}

TEST(MatrixTest, TestcEnd)
{
    GSL::Matrix m{{1, 2}, {3, 4}, {5, 6}};
    auto it1 = m.cend();
    EXPECT_EQ(*--it1, *(m.begin() + 2));
}

TEST(MatrixTest, TestRbegin)
{
    GSL::Matrix m{{1, 2}, {3, 4}, {5, 6}};
    GSL::Vector res{5, 6};
    EXPECT_EQ(*m.rbegin(), res);
}

TEST(MatrixTest, TestcRbegin)
{
    GSL::Matrix m{{1, 2}, {3, 4}, {5, 6}};
    GSL::Vector res{5, 6};
    EXPECT_EQ(*m.crbegin(), res);
}

TEST(MatrixTest, TestRend)
{
    GSL::Matrix m{{1, 2}, {3, 4}, {5, 6}};
    auto it1 = m.rend();
    EXPECT_EQ(*--it1, *(m.rbegin() + 2));
}

TEST(MatrixTest, TestcRend)
{
    GSL::Matrix m{{1, 2}, {3, 4}, {5, 6}};
    auto it1 = m.crend();
    EXPECT_EQ(*--it1, *(m.crbegin() + 2));
}
