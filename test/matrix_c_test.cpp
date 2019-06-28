#include "GSLpp/matrix.h"
#include "GSLpp/vector.h"
#include <gtest/gtest.h>

TEST(Matrix_cTest, TestConstruction)
{
    size_t rows = 2, columns = 2;
    GSL::Matrix_c m(rows, columns);

    for(size_t i = 0; i < rows; i++){
        for(size_t j = 0; j < columns; j++){
            EXPECT_EQ(m[i][j], 0);
        }
    }
}

TEST(Matrix_cTest, TestConstructionInitializerList)
{
    GSL::Matrix_c m{{1, 2}, {3, 4}};
    size_t rows = 2, columns = 2;
    for(size_t i = 0; i < rows; i++){
        for(size_t j = 0; j < columns; j++){
            EXPECT_EQ(m[i][j], columns*i+j+1);
        }
    }
}

TEST(Matrix_cTest, TestConstructionCopy)
{
    size_t rows = 2, columns = 2;
    GSL::Matrix_c m1{{1, 2}, {3, 4}}, m2(m1);
    for(size_t i = 0; i < rows; i++){
        for(size_t j = 0; j < columns; j++){
            EXPECT_EQ(m1[i][j], m2[i][j]);
        }
    }
}

TEST(Matrix_cTest, TestConstructionMove)
{
    size_t rows = 2, columns = 2;
    GSL::Matrix_c m1{{1, 2}, {3, 4}}, m2(std::move(m1));
    for(size_t i = 0; i < rows; i++){
        for(size_t j = 0; j < columns; j++){
            EXPECT_EQ(m2[i][j], columns*i+j+1);
        }
    }
}

TEST(Matrix_cTest, TestEqual)
{
    GSL::Matrix_c m1{{1, 2}, {3, 4}}, m2(m1);
    EXPECT_TRUE(m1 == m2);
}

TEST(Matrix_cTest, TestNequal)
{
    GSL::Matrix_c m1{{1, 2}, {3, 4}}, m2(m1);
    EXPECT_FALSE(m1 != m2);
}

TEST(Matrix_cTest, TestCopy)
{
    GSL::Matrix_c m1{{1, 2}, {3, 4}}, m2;
    m2 = m1;
    EXPECT_EQ(m1, m2);
}

TEST(Matrix_cTest, TestMove)
{
    GSL::Matrix_c m1{{1, 2}, {3, 4}}, m1s(m1), m2;
    m2 = std::move(m1);
    EXPECT_EQ(m1s, m2);
}

TEST(Matrix_cTest, TestCopy2)
{
    GSL::Matrix_c m1{{1, 2}, {3, 4}}, m2;
    m2.copy(m1);
    EXPECT_EQ(m1, m2);
}

TEST(Matrix_cTest, TestDecayToGSLMatrix_c)
{
    GSL::Matrix_c m{{1, 2}, {3, 4}};
    gsl_matrix_char gm = m;
    EXPECT_EQ(gsl_matrix_char_get(&gm, 0, 1), 2);
}

TEST(Matrix_cTest, TestDim)
{
    GSL::Matrix_c m{{1, 2}, {3, 4}, {5, 6}};
    std::pair<size_t, size_t> d(3,2);
    EXPECT_EQ(m.dim(), d);
}

TEST(Matrix_cTest, TestSize)
{
    GSL::Matrix_c m{{1, 2}, {3, 4}, {5, 6}};
    std::pair<size_t, size_t> d(3,2);
    EXPECT_EQ(m.size(), d);
}

TEST(Matrix_cTest, TestAddAssign)
{
    GSL::Matrix_c m{{1, 2}, {3, 4}, {5, 6}}, n{{1, 2}, {3, 4}, {5, 6}};
    m += n;
    GSL::Matrix_c res{{2, 4}, {6, 8}, {10, 12}};
    EXPECT_EQ(m, res);
}

TEST(Matrix_cTest, TestSubAssign)
{
    GSL::Matrix_c m{{1, 2}, {3, 4}, {5, 6}}, n{{1, 2}, {3, 4}, {5, 6}};
    m -= n;
    GSL::Matrix_c res{{0, 0}, {0, 0}, {0, 0}};
    EXPECT_EQ(m, res);
}

TEST(Matrix_cTest, TestMultAssign)
{
    GSL::Matrix_c m{{1, 2}, {3, 4}, {5, 6}}, n{{1, 2, 3}, {4, 5, 6}};
    m *= n;
    GSL::Matrix_c res{{9, 12, 15}, {19, 26, 33}, {29, 40, 51}};
    EXPECT_EQ(m, res);
}

TEST(Matrix_cTest, TestDivAssign)
{
    GSL::Matrix_c m{{1, 2}, {3, 4}, {5, 6}}, n{{1, 2}, {3, 4}, {5, 6}};
    m /= n;
    GSL::Matrix_c res{{1, 1}, {1, 1}, {1, 1}};
    EXPECT_EQ(m, res);
}

TEST(Matrix_cTest, TestMultScaleAssign)
{
    GSL::Matrix_c m{{1, 2}, {3, 4}, {5, 6}};
    m *= 2;
    GSL::Matrix_c res{{2, 4}, {6, 8}, {10, 12}};
    EXPECT_EQ(m, res);
}

TEST(Matrix_cTest, TestDivScaleAssign)
{
    GSL::Matrix_c m{{1, 2}, {3, 4}, {5, 6}};
    m /= 2;
    GSL::Matrix_c res{{0, 1}, {1, 2}, {2, 3}};
    EXPECT_EQ(m, res);
}

TEST(Matrix_cTest, TestAdd)
{
    GSL::Matrix_c m{{1, 2}, {3, 4}, {5, 6}}, n{{1, 2}, {3, 4}, {5, 6}};
    GSL::Matrix_c res{{2, 4}, {6, 8}, {10, 12}};
    EXPECT_EQ(m+n, res);
}

TEST(Matrix_cTest, TestSub)
{
    GSL::Matrix_c m{{1, 2}, {3, 4}, {5, 6}}, n{{1, 2}, {3, 4}, {5, 6}};
    GSL::Matrix_c res{{0, 0}, {0, 0}, {0, 0}};
    EXPECT_EQ(m-n, res);
}

TEST(Matrix_cTest, TestMult)
{
    GSL::Matrix_c m{{1, 2}, {3, 4}, {5, 6}}, n{{1, 2, 3}, {4, 5, 6}};
    GSL::Matrix_c res{{9, 12, 15}, {19, 26, 33}, {29, 40, 51}};
    EXPECT_EQ(m*n, res);
}

TEST(Matrix_cTest, TestDiv)
{
    GSL::Matrix_c m{{1, 2}, {3, 4}, {5, 6}}, n{{1, 2}, {3, 4}, {5, 6}};
    GSL::Matrix_c res{{1, 1}, {1, 1}, {1, 1}};
    EXPECT_EQ(m/n, res);
}

TEST(Matrix_cTest, TestMultScale)
{
    GSL::Matrix_c m{{1, 2}, {3, 4}, {5, 6}};
    GSL::Matrix_c res{{2, 4}, {6, 8}, {10, 12}};
    EXPECT_EQ(m*2, res);
}

TEST(Matrix_cTest, TestMultScale2)
{
    GSL::Matrix_c m{{1, 2}, {3, 4}, {5, 6}};
    GSL::Matrix_c res{{2, 4}, {6, 8}, {10, 12}};
    EXPECT_EQ(2*m, res);
}

TEST(Matrix_cTest, TestDivScale)
{
    GSL::Matrix_c m{{1, 2}, {3, 4}, {5, 6}};
    GSL::Matrix_c res{{0, 1}, {1, 2}, {2, 3}};
    EXPECT_EQ(m/2, res);
}

TEST(Matrix_cTest, TestTranspose)
{
    GSL::Matrix_c m{{1, 2}, {3, 4}, {5, 6}};
    GSL::Matrix_c res{{1, 3, 5},{2, 4, 6}};
    EXPECT_EQ(m.transpose(), res);
}

TEST(Matrix_cTest, TestHermitian)
{
    GSL::Matrix_c m{{1, 2}, {3, 4}, {5, 6}};
    GSL::Matrix_c res{{1, 3, 5},{2, 4, 6}};
    EXPECT_EQ(m.hermitian_transpose(), res);
}

TEST(Matrix_cTest, TestGetRow)
{
    GSL::Matrix_c m{{1, 2}, {3, 4}, {5, 6}};
    GSL::Vector_c res{5, 6};
    EXPECT_EQ(m.get_row(2), res);
}

TEST(Matrix_cTest, TestSetRow)
{
    GSL::Matrix_c m{{1, 2}, {3, 4}, {5, 6}};
    GSL::Matrix_c res{{1, 2}, {7, 8}, {5, 6}};
    m.get_row(1) = GSL::Vector_c{7, 8};
    EXPECT_EQ(m, res);
}

TEST(Matrix_cTest, TestGetCol)
{
    GSL::Matrix_c m{{1, 2}, {3, 4}, {5, 6}};
    GSL::Vector_c res{2, 4, 6};
    EXPECT_EQ(m.get_col(1), res);
}

TEST(Matrix_cTest, TestSetCol)
{
    GSL::Matrix_c m{{1, 2}, {3, 4}, {5, 6}};
    GSL::Matrix_c res{{7, 2}, {8, 4}, {9, 6}};
    m.get_col(0) = GSL::Vector_c{7, 8, 9};
    EXPECT_EQ(m, res);
}

TEST(Matrix_cTest, TestBegin)
{
    GSL::Matrix_c m{{1, 2}, {3, 4}, {5, 6}};
    GSL::Vector_c res{1, 2};

    EXPECT_EQ(*m.begin(), res);
}

TEST(Matrix_cTest, TestcBegin)
{
    GSL::Matrix_c m{{1, 2}, {3, 4}, {5, 6}};
    GSL::Vector_c res{1, 2};

    EXPECT_EQ(*m.cbegin(), res);
}

TEST(Matrix_cTest, TestFront)
{
    GSL::Matrix_c m{{1, 2}, {3, 4}, {5, 6}};
    GSL::Vector_c res{1, 2};

    EXPECT_EQ(m.front(), res);
}

TEST(Matrix_cTest, TestBack)
{
    GSL::Matrix_c m{{1, 2}, {3, 4}, {5, 6}};
    GSL::Vector_c res{5, 6};

    EXPECT_EQ(m.back(), res);
}

TEST(Matrix_cTest, TestAt)
{
    GSL::Matrix_c m{{1, 2}, {3, 4}, {5, 6}};
    GSL::Vector_c res{3, 4};

    EXPECT_EQ(m.at(1), res);
}

TEST(Matrix_cTest, TestAt2)
{
    GSL::Matrix_c m{{1, 2}, {3, 4}, {5, 6}};
    GSL::Matrix_c::value_type res{5};

    EXPECT_EQ(m.at(2, 0), res);
}

TEST(Matrix_cTest, TestIterPreIncrement)
{
    GSL::Matrix_c m{{1, 2}, {3, 4}, {5, 6}};
    EXPECT_EQ(*++m.begin(), m.at(1));
}

TEST(Matrix_cTest, TestIterPostIncrement)
{
    GSL::Matrix_c m{{1, 2}, {3, 4}, {5, 6}};
    auto it = m.begin();
    it++;
    EXPECT_EQ(*it, m.at(1));
}

TEST(Matrix_cTest, TestIterPreDecrement)
{
    GSL::Matrix_c m{{1, 2}, {3, 4}, {5, 6}};
    EXPECT_EQ(*--(++m.begin()), m.at(0));
}

TEST(Matrix_cTest, TestIterPostDecrement)
{
    GSL::Matrix_c m{{1, 2}, {3, 4}, {5, 6}};
    auto it = m.begin();
    (it++)--;
    EXPECT_EQ(*it, m.at(0));
}

TEST(Matrix_cTest, TestIterAddAssign)
{
    GSL::Matrix_c m{{1, 2}, {3, 4}, {5, 6}};
    auto it = m.begin();
    it += 2;
    EXPECT_EQ(*it, m.at(2));
}

TEST(Matrix_cTest, TestIterSubAssign)
{
    GSL::Matrix_c m{{1, 2}, {3, 4}, {5, 6}};
    auto it = m.begin();
    it += 2;
    it -= 1;
    EXPECT_EQ(*it, m.at(1));
}

TEST(Matrix_cTest, TestIterAdd)
{
    GSL::Matrix_c m{{1, 2}, {3, 4}, {5, 6}};
    auto it = m.begin();
    EXPECT_EQ(*(it + 2), m.at(2));
}

TEST(Matrix_cTest, TestIterAdd2)
{
    GSL::Matrix_c m{{1, 2}, {3, 4}, {5, 6}};
    auto it = m.begin();
    EXPECT_EQ(*(2 + it), m.at(2));
}

TEST(Matrix_cTest, TestIterSub)
{
    GSL::Matrix_c m{{1, 2}, {3, 4}, {5, 6}};
    auto it = m.begin();
    it += 2;
    EXPECT_EQ(*(it - 1), m.at(1));
}

TEST(Matrix_cTest, TestIterSub2)
{
    GSL::Matrix_c m{{1, 2}, {3, 4}, {5, 6}};
    auto it1 = m.begin(), it2 = m.begin();
    it2 += 2;
    EXPECT_EQ(it2 - it1, 2);
}

TEST(Matrix_cTest, TestIterEq)
{
    GSL::Matrix_c m{{1, 2}, {3, 4}, {5, 6}};
    auto it1 = m.begin(), it2 = m.begin();
    it2 += 2;
    EXPECT_EQ(*++(++it1), *it2);
}

TEST(Matrix_cTest, TestIterNeq)
{
    GSL::Matrix_c m{{1, 2}, {3, 4}, {5, 6}};
    auto it = m.begin();
    GSL::Vector_c res{*it};
    EXPECT_NE(res, *(it + 1));
}

TEST(Matrix_cTest, TestEnd)
{
    GSL::Matrix_c m{{1, 2}, {3, 4}, {5, 6}};
    auto it1 = m.end();
    EXPECT_EQ(*--it1, *(m.begin() + 2));
}

TEST(Matrix_cTest, TestcEnd)
{
    GSL::Matrix_c m{{1, 2}, {3, 4}, {5, 6}};
    auto it1 = m.cend();
    EXPECT_EQ(*--it1, *(m.begin() + 2));
}

TEST(Matrix_cTest, TestRbegin)
{
    GSL::Matrix_c m{{1, 2}, {3, 4}, {5, 6}};
    GSL::Vector_c res{5, 6};
    EXPECT_EQ(*m.rbegin(), res);
}

TEST(Matrix_cTest, TestcRbegin)
{
    GSL::Matrix_c m{{1, 2}, {3, 4}, {5, 6}};
    GSL::Vector_c res{5, 6};
    EXPECT_EQ(*m.crbegin(), res);
}

TEST(Matrix_cTest, TestRend)
{
    GSL::Matrix_c m{{1, 2}, {3, 4}, {5, 6}};
    auto it1 = m.rend();
    EXPECT_EQ(*--it1, *(m.rbegin() + 2));
}

TEST(Matrix_cTest, TestcRend)
{
    GSL::Matrix_c m{{1, 2}, {3, 4}, {5, 6}};
    auto it1 = m.crend();
    EXPECT_EQ(*--it1, *(m.crbegin() + 2));
}
