#include "GSLpp/matrix.h"
#include "GSLpp/vector.h"
#include <gtest/gtest.h>

TEST(Matrix_iTest, TestConstruction)
{
    size_t rows = 2, columns = 2;
    GSL::Matrix_i m(rows, columns);

    for(size_t i = 0; i < rows; i++){
        for(size_t j = 0; j < columns; j++){
            EXPECT_EQ(m[i][j], 0);
        }
    }
}

TEST(Matrix_iTest, TestConstructionInitializerList)
{
    GSL::Matrix_i m{{1, 2}, {3, 4}};
    size_t rows = 2, columns = 2;
    for(size_t i = 0; i < rows; i++){
        for(size_t j = 0; j < columns; j++){
            EXPECT_EQ(m[i][j], columns*i+j+1);
        }
    }
}

TEST(Matrix_iTest, TestConstructionCopy)
{
    size_t rows = 2, columns = 2;
    GSL::Matrix_i m1{{1, 2}, {3, 4}}, m2(m1);
    for(size_t i = 0; i < rows; i++){
        for(size_t j = 0; j < columns; j++){
            EXPECT_EQ(m1[i][j], m2[i][j]);
        }
    }
}

TEST(Matrix_iTest, TestConstructionMove)
{
    size_t rows = 2, columns = 2;
    GSL::Matrix_i m1{{1, 2}, {3, 4}}, m2(std::move(m1));
    for(size_t i = 0; i < rows; i++){
        for(size_t j = 0; j < columns; j++){
            EXPECT_EQ(m2[i][j], columns*i+j+1);
        }
    }
}

TEST(Matrix_iTest, TestEqual)
{
    GSL::Matrix_i m1{{1, 2}, {3, 4}}, m2(m1);
    EXPECT_TRUE(m1 == m2);
}

TEST(Matrix_iTest, TestNequal)
{
    GSL::Matrix_i m1{{1, 2}, {3, 4}}, m2(m1);
    EXPECT_FALSE(m1 != m2);
}

TEST(Matrix_iTest, TestCopy)
{
    GSL::Matrix_i m1{{1, 2}, {3, 4}}, m2;
    m2 = m1;
    EXPECT_EQ(m1, m2);
}

TEST(Matrix_iTest, TestMove)
{
    GSL::Matrix_i m1{{1, 2}, {3, 4}}, m1s(m1), m2;
    m2 = std::move(m1);
    EXPECT_EQ(m1s, m2);
}

TEST(Matrix_iTest, TestCopy2)
{
    GSL::Matrix_i m1{{1, 2}, {3, 4}}, m2;
    m2.copy(m1);
    EXPECT_EQ(m1, m2);
}

TEST(Matrix_iTest, TestDecayToGSLMatrix_i)
{
    GSL::Matrix_i m{{1, 2}, {3, 4}};
    gsl_matrix_int gm = m;
    EXPECT_EQ(gsl_matrix_int_get(&gm, 0, 1), 2);
}

TEST(Matrix_iTest, TestDim)
{
    GSL::Matrix_i m{{1, 2}, {3, 4}, {5, 6}};
    std::pair<size_t, size_t> d(3,2);
    EXPECT_EQ(m.dim(), d);
}

TEST(Matrix_iTest, TestSize)
{
    GSL::Matrix_i m{{1, 2}, {3, 4}, {5, 6}};
    std::pair<size_t, size_t> d(3,2);
    EXPECT_EQ(m.size(), d);
}

TEST(Matrix_iTest, TestAddAssign)
{
    GSL::Matrix_i m{{1, 2}, {3, 4}, {5, 6}}, n{{1, 2}, {3, 4}, {5, 6}};
    m += n;
    GSL::Matrix_i res{{2, 4}, {6, 8}, {10, 12}};
    EXPECT_EQ(m, res);
}

TEST(Matrix_iTest, TestSubAssign)
{
    GSL::Matrix_i m{{1, 2}, {3, 4}, {5, 6}}, n{{1, 2}, {3, 4}, {5, 6}};
    m -= n;
    GSL::Matrix_i res{{0, 0}, {0, 0}, {0, 0}};
    EXPECT_EQ(m, res);
}

TEST(Matrix_iTest, TestMultAssign)
{
    GSL::Matrix_i m{{1, 2}, {3, 4}, {5, 6}}, n{{1, 2, 3}, {4, 5, 6}};
    m *= n;
    GSL::Matrix_i res{{9, 12, 15}, {19, 26, 33}, {29, 40, 51}};
    EXPECT_EQ(m, res);
}

TEST(Matrix_iTest, TestDivAssign)
{
    GSL::Matrix_i m{{1, 2}, {3, 4}, {5, 6}}, n{{1, 2}, {3, 4}, {5, 6}};
    m /= n;
    GSL::Matrix_i res{{1, 1}, {1, 1}, {1, 1}};
    EXPECT_EQ(m, res);
}

TEST(Matrix_iTest, TestMultScaleAssign)
{
    GSL::Matrix_i m{{1, 2}, {3, 4}, {5, 6}};
    m *= 2;
    GSL::Matrix_i res{{2, 4}, {6, 8}, {10, 12}};
    EXPECT_EQ(m, res);
}

TEST(Matrix_iTest, TestDivScaleAssign)
{
    GSL::Matrix_i m{{1, 2}, {3, 4}, {5, 6}};
    m /= 2;
    GSL::Matrix_i res{{0, 1}, {1, 2}, {2, 3}};
    EXPECT_EQ(m, res);
}

TEST(Matrix_iTest, TestAdd)
{
    GSL::Matrix_i m{{1, 2}, {3, 4}, {5, 6}}, n{{1, 2}, {3, 4}, {5, 6}};
    GSL::Matrix_i res{{2, 4}, {6, 8}, {10, 12}};
    EXPECT_EQ(m+n, res);
}

TEST(Matrix_iTest, TestSub)
{
    GSL::Matrix_i m{{1, 2}, {3, 4}, {5, 6}}, n{{1, 2}, {3, 4}, {5, 6}};
    GSL::Matrix_i res{{0, 0}, {0, 0}, {0, 0}};
    EXPECT_EQ(m-n, res);
}

TEST(Matrix_iTest, TestMult)
{
    GSL::Matrix_i m{{1, 2}, {3, 4}, {5, 6}}, n{{1, 2, 3}, {4, 5, 6}};
    GSL::Matrix_i res{{9, 12, 15}, {19, 26, 33}, {29, 40, 51}};
    EXPECT_EQ(m*n, res);
}

TEST(Matrix_iTest, TestDiv)
{
    GSL::Matrix_i m{{1, 2}, {3, 4}, {5, 6}}, n{{1, 2}, {3, 4}, {5, 6}};
    GSL::Matrix_i res{{1, 1}, {1, 1}, {1, 1}};
    EXPECT_EQ(m/n, res);
}

TEST(Matrix_iTest, TestMultScale)
{
    GSL::Matrix_i m{{1, 2}, {3, 4}, {5, 6}};
    GSL::Matrix_i res{{2, 4}, {6, 8}, {10, 12}};
    EXPECT_EQ(m*2, res);
}

TEST(Matrix_iTest, TestMultScale2)
{
    GSL::Matrix_i m{{1, 2}, {3, 4}, {5, 6}};
    GSL::Matrix_i res{{2, 4}, {6, 8}, {10, 12}};
    EXPECT_EQ(2*m, res);
}

TEST(Matrix_iTest, TestDivScale)
{
    GSL::Matrix_i m{{1, 2}, {3, 4}, {5, 6}};
    GSL::Matrix_i res{{0, 1}, {1, 2}, {2, 3}};
    EXPECT_EQ(m/2, res);
}

TEST(Matrix_iTest, TestTranspose)
{
    GSL::Matrix_i m{{1, 2}, {3, 4}, {5, 6}};
    GSL::Matrix_i res{{1, 3, 5},{2, 4, 6}};
    EXPECT_EQ(m.transpose(), res);
}

TEST(Matrix_iTest, TestHermitian)
{
    GSL::Matrix_i m{{1, 2}, {3, 4}, {5, 6}};
    GSL::Matrix_i res{{1, 3, 5},{2, 4, 6}};
    EXPECT_EQ(m.hermitian_transpose(), res);
}

TEST(Matrix_iTest, TestGetRow)
{
    GSL::Matrix_i m{{1, 2}, {3, 4}, {5, 6}};
    GSL::Vector_i res{5, 6};
    EXPECT_EQ(m.get_row(2), res);
}

TEST(Matrix_iTest, TestSetRow)
{
    GSL::Matrix_i m{{1, 2}, {3, 4}, {5, 6}};
    GSL::Matrix_i res{{1, 2}, {7, 8}, {5, 6}};
    m.get_row(1) = GSL::Vector_i{7, 8};
    EXPECT_EQ(m, res);
}

TEST(Matrix_iTest, TestGetCol)
{
    GSL::Matrix_i m{{1, 2}, {3, 4}, {5, 6}};
    GSL::Vector_i res{2, 4, 6};
    EXPECT_EQ(m.get_col(1), res);
}

TEST(Matrix_iTest, TestSetCol)
{
    GSL::Matrix_i m{{1, 2}, {3, 4}, {5, 6}};
    GSL::Matrix_i res{{7, 2}, {8, 4}, {9, 6}};
    m.get_col(0) = GSL::Vector_i{7, 8, 9};
    EXPECT_EQ(m, res);
}

TEST(Matrix_iTest, TestBegin)
{
    GSL::Matrix_i m{{1, 2}, {3, 4}, {5, 6}};
    GSL::Vector_i res{1, 2};

    EXPECT_EQ(*m.begin(), res);
}

TEST(Matrix_iTest, TestcBegin)
{
    GSL::Matrix_i m{{1, 2}, {3, 4}, {5, 6}};
    GSL::Vector_i res{1, 2};

    EXPECT_EQ(*m.cbegin(), res);
}

TEST(Matrix_iTest, TestFront)
{
    GSL::Matrix_i m{{1, 2}, {3, 4}, {5, 6}};
    GSL::Vector_i res{1, 2};

    EXPECT_EQ(m.front(), res);
}

TEST(Matrix_iTest, TestBack)
{
    GSL::Matrix_i m{{1, 2}, {3, 4}, {5, 6}};
    GSL::Vector_i res{5, 6};

    EXPECT_EQ(m.back(), res);
}

TEST(Matrix_iTest, TestAt)
{
    GSL::Matrix_i m{{1, 2}, {3, 4}, {5, 6}};
    GSL::Vector_i res{3, 4};

    EXPECT_EQ(m.at(1), res);
}

TEST(Matrix_iTest, TestAt2)
{
    GSL::Matrix_i m{{1, 2}, {3, 4}, {5, 6}};
    GSL::Matrix_i::value_type res{5};

    EXPECT_EQ(m.at(2, 0), res);
}

TEST(Matrix_iTest, TestIterPreIncrement)
{
    GSL::Matrix_i m{{1, 2}, {3, 4}, {5, 6}};
    EXPECT_EQ(*++m.begin(), m.at(1));
}

TEST(Matrix_iTest, TestIterPostIncrement)
{
    GSL::Matrix_i m{{1, 2}, {3, 4}, {5, 6}};
    auto it = m.begin();
    it++;
    EXPECT_EQ(*it, m.at(1));
}

TEST(Matrix_iTest, TestIterPreDecrement)
{
    GSL::Matrix_i m{{1, 2}, {3, 4}, {5, 6}};
    EXPECT_EQ(*--(++m.begin()), m.at(0));
}

TEST(Matrix_iTest, TestIterPostDecrement)
{
    GSL::Matrix_i m{{1, 2}, {3, 4}, {5, 6}};
    auto it = m.begin();
    (it++)--;
    EXPECT_EQ(*it, m.at(0));
}

TEST(Matrix_iTest, TestIterAddAssign)
{
    GSL::Matrix_i m{{1, 2}, {3, 4}, {5, 6}};
    auto it = m.begin();
    it += 2;
    EXPECT_EQ(*it, m.at(2));
}

TEST(Matrix_iTest, TestIterSubAssign)
{
    GSL::Matrix_i m{{1, 2}, {3, 4}, {5, 6}};
    auto it = m.begin();
    it += 2;
    it -= 1;
    EXPECT_EQ(*it, m.at(1));
}

TEST(Matrix_iTest, TestIterAdd)
{
    GSL::Matrix_i m{{1, 2}, {3, 4}, {5, 6}};
    auto it = m.begin();
    EXPECT_EQ(*(it + 2), m.at(2));
}

TEST(Matrix_iTest, TestIterAdd2)
{
    GSL::Matrix_i m{{1, 2}, {3, 4}, {5, 6}};
    auto it = m.begin();
    EXPECT_EQ(*(2 + it), m.at(2));
}

TEST(Matrix_iTest, TestIterSub)
{
    GSL::Matrix_i m{{1, 2}, {3, 4}, {5, 6}};
    auto it = m.begin();
    it += 2;
    EXPECT_EQ(*(it - 1), m.at(1));
}

TEST(Matrix_iTest, TestIterSub2)
{
    GSL::Matrix_i m{{1, 2}, {3, 4}, {5, 6}};
    auto it1 = m.begin(), it2 = m.begin();
    it2 += 2;
    EXPECT_EQ(it2 - it1, 2);
}

TEST(Matrix_iTest, TestIterEq)
{
    GSL::Matrix_i m{{1, 2}, {3, 4}, {5, 6}};
    auto it1 = m.begin(), it2 = m.begin();
    it2 += 2;
    EXPECT_EQ(*++(++it1), *it2);
}

TEST(Matrix_iTest, TestIterNeq)
{
    GSL::Matrix_i m{{1, 2}, {3, 4}, {5, 6}};
    auto it = m.begin();
    GSL::Vector_i res{*it};
    EXPECT_NE(res, *(it + 1));
}

TEST(Matrix_iTest, TestEnd)
{
    GSL::Matrix_i m{{1, 2}, {3, 4}, {5, 6}};
    auto it1 = m.end();
    EXPECT_EQ(*--it1, *(m.begin() + 2));
}

TEST(Matrix_iTest, TestcEnd)
{
    GSL::Matrix_i m{{1, 2}, {3, 4}, {5, 6}};
    auto it1 = m.cend();
    EXPECT_EQ(*--it1, *(m.begin() + 2));
}

TEST(Matrix_iTest, TestRbegin)
{
    GSL::Matrix_i m{{1, 2}, {3, 4}, {5, 6}};
    GSL::Vector_i res{5, 6};
    EXPECT_EQ(*m.rbegin(), res);
}

TEST(Matrix_iTest, TestcRbegin)
{
    GSL::Matrix_i m{{1, 2}, {3, 4}, {5, 6}};
    GSL::Vector_i res{5, 6};
    EXPECT_EQ(*m.crbegin(), res);
}

TEST(Matrix_iTest, TestRend)
{
    GSL::Matrix_i m{{1, 2}, {3, 4}, {5, 6}};
    auto it1 = m.rend();
    EXPECT_EQ(*--it1, *(m.rbegin() + 2));
}

TEST(Matrix_iTest, TestcRend)
{
    GSL::Matrix_i m{{1, 2}, {3, 4}, {5, 6}};
    auto it1 = m.crend();
    EXPECT_EQ(*--it1, *(m.crbegin() + 2));
}
