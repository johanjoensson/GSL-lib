#include "GSLpp/matrix.h"
#include "GSLpp/vector.h"
#include <gtest/gtest.h>

TEST(Matrix_sTest, TestConstruction)
{
    size_t rows = 2, columns = 2;
    GSL::Matrix_s m(rows, columns);

    for(size_t i = 0; i < rows; i++){
        for(size_t j = 0; j < columns; j++){
            EXPECT_EQ(m[i][j], 0);
        }
    }
}

TEST(Matrix_sTest, TestConstructionInitializerList)
{
    GSL::Matrix_s m{{1, 2}, {3, 4}};
    size_t rows = 2, columns = 2;
    for(size_t i = 0; i < rows; i++){
        for(size_t j = 0; j < columns; j++){
            EXPECT_EQ(m[i][j], columns*i+j+1);
        }
    }
}

TEST(Matrix_sTest, TestConstructionCopy)
{
    size_t rows = 2, columns = 2;
    GSL::Matrix_s m1{{1, 2}, {3, 4}}, m2(m1);
    for(size_t i = 0; i < rows; i++){
        for(size_t j = 0; j < columns; j++){
            EXPECT_EQ(m1[i][j], m2[i][j]);
        }
    }
}

TEST(Matrix_sTest, TestConstructionMove)
{
    size_t rows = 2, columns = 2;
    GSL::Matrix_s m1{{1, 2}, {3, 4}}, m2(std::move(m1));
    for(size_t i = 0; i < rows; i++){
        for(size_t j = 0; j < columns; j++){
            EXPECT_EQ(m2[i][j], columns*i+j+1);
        }
    }
}

TEST(Matrix_sTest, TestEqual)
{
    GSL::Matrix_s m1{{1, 2}, {3, 4}}, m2(m1);
    EXPECT_TRUE(m1 == m2);
}

TEST(Matrix_sTest, TestNequal)
{
    GSL::Matrix_s m1{{1, 2}, {3, 4}}, m2(m1);
    EXPECT_FALSE(m1 != m2);
}

TEST(Matrix_sTest, TestCopy)
{
    GSL::Matrix_s m1{{1, 2}, {3, 4}}, m2;
    m2 = m1;
    EXPECT_EQ(m1, m2);
}

TEST(Matrix_sTest, TestMove)
{
    GSL::Matrix_s m1{{1, 2}, {3, 4}}, m1s(m1), m2;
    m2 = std::move(m1);
    EXPECT_EQ(m1s, m2);
}

TEST(Matrix_sTest, TestCopy2)
{
    GSL::Matrix_s m1{{1, 2}, {3, 4}}, m2;
    m2.copy(m1);
    EXPECT_EQ(m1, m2);
}

TEST(Matrix_sTest, TestDecayToGSLMatrix_s)
{
    GSL::Matrix_s m{{1, 2}, {3, 4}};
    gsl_matrix_short gm = m;
    EXPECT_EQ(gsl_matrix_short_get(&gm, 0, 1), 2);
}

TEST(Matrix_sTest, TestDim)
{
    GSL::Matrix_s m{{1, 2}, {3, 4}, {5, 6}};
    std::pair<size_t, size_t> d(3,2);
    EXPECT_EQ(m.dim(), d);
}

TEST(Matrix_sTest, TestSize)
{
    GSL::Matrix_s m{{1, 2}, {3, 4}, {5, 6}};
    std::pair<size_t, size_t> d(3,2);
    EXPECT_EQ(m.size(), d);
}

TEST(Matrix_sTest, TestAddAssign)
{
    GSL::Matrix_s m{{1, 2}, {3, 4}, {5, 6}}, n{{1, 2}, {3, 4}, {5, 6}};
    m += n;
    GSL::Matrix_s res{{2, 4}, {6, 8}, {10, 12}};
    EXPECT_EQ(m, res);
}

TEST(Matrix_sTest, TestSubAssign)
{
    GSL::Matrix_s m{{1, 2}, {3, 4}, {5, 6}}, n{{1, 2}, {3, 4}, {5, 6}};
    m -= n;
    GSL::Matrix_s res{{0, 0}, {0, 0}, {0, 0}};
    EXPECT_EQ(m, res);
}

TEST(Matrix_sTest, TestMultAssign)
{
    GSL::Matrix_s m{{1, 2}, {3, 4}, {5, 6}}, n{{1, 2, 3}, {4, 5, 6}};
    m *= n;
    GSL::Matrix_s res{{9, 12, 15}, {19, 26, 33}, {29, 40, 51}};
    EXPECT_EQ(m, res);
}

TEST(Matrix_sTest, TestDivAssign)
{
    GSL::Matrix_s m{{1, 2}, {3, 4}, {5, 6}}, n{{1, 2}, {3, 4}, {5, 6}};
    m /= n;
    GSL::Matrix_s res{{1, 1}, {1, 1}, {1, 1}};
    EXPECT_EQ(m, res);
}

TEST(Matrix_sTest, TestMultScaleAssign)
{
    GSL::Matrix_s m{{1, 2}, {3, 4}, {5, 6}};
    m *= 2;
    GSL::Matrix_s res{{2, 4}, {6, 8}, {10, 12}};
    EXPECT_EQ(m, res);
}

TEST(Matrix_sTest, TestDivScaleAssign)
{
    GSL::Matrix_s m{{1, 2}, {3, 4}, {5, 6}};
    m /= 2;
    GSL::Matrix_s res{{0, 1}, {1, 2}, {2, 3}};
    EXPECT_EQ(m, res);
}

TEST(Matrix_sTest, TestAdd)
{
    GSL::Matrix_s m{{1, 2}, {3, 4}, {5, 6}}, n{{1, 2}, {3, 4}, {5, 6}};
    GSL::Matrix_s res{{2, 4}, {6, 8}, {10, 12}};
    EXPECT_EQ(m+n, res);
}

TEST(Matrix_sTest, TestSub)
{
    GSL::Matrix_s m{{1, 2}, {3, 4}, {5, 6}}, n{{1, 2}, {3, 4}, {5, 6}};
    GSL::Matrix_s res{{0, 0}, {0, 0}, {0, 0}};
    EXPECT_EQ(m-n, res);
}

TEST(Matrix_sTest, TestMult)
{
    GSL::Matrix_s m{{1, 2}, {3, 4}, {5, 6}}, n{{1, 2, 3}, {4, 5, 6}};
    GSL::Matrix_s res{{9, 12, 15}, {19, 26, 33}, {29, 40, 51}};
    EXPECT_EQ(m*n, res);
}

TEST(Matrix_sTest, TestDiv)
{
    GSL::Matrix_s m{{1, 2}, {3, 4}, {5, 6}}, n{{1, 2}, {3, 4}, {5, 6}};
    GSL::Matrix_s res{{1, 1}, {1, 1}, {1, 1}};
    EXPECT_EQ(m/n, res);
}

TEST(Matrix_sTest, TestMultScale)
{
    GSL::Matrix_s m{{1, 2}, {3, 4}, {5, 6}};
    GSL::Matrix_s res{{2, 4}, {6, 8}, {10, 12}};
    EXPECT_EQ(m*2, res);
}

TEST(Matrix_sTest, TestMultScale2)
{
    GSL::Matrix_s m{{1, 2}, {3, 4}, {5, 6}};
    GSL::Matrix_s res{{2, 4}, {6, 8}, {10, 12}};
    EXPECT_EQ(2*m, res);
}

TEST(Matrix_sTest, TestDivScale)
{
    GSL::Matrix_s m{{1, 2}, {3, 4}, {5, 6}};
    GSL::Matrix_s res{{0, 1}, {1, 2}, {2, 3}};
    EXPECT_EQ(m/2, res);
}

TEST(Matrix_sTest, TestTranspose)
{
    GSL::Matrix_s m{{1, 2}, {3, 4}, {5, 6}};
    GSL::Matrix_s res{{1, 3, 5},{2, 4, 6}};
    EXPECT_EQ(m.transpose(), res);
}

TEST(Matrix_sTest, TestHermitian)
{
    GSL::Matrix_s m{{1, 2}, {3, 4}, {5, 6}};
    GSL::Matrix_s res{{1, 3, 5},{2, 4, 6}};
    EXPECT_EQ(m.hermitian_transpose(), res);
}

TEST(Matrix_sTest, TestGetRow)
{
    GSL::Matrix_s m{{1, 2}, {3, 4}, {5, 6}};
    GSL::Vector_s res{5, 6};
    EXPECT_EQ(m.get_row(2), res);
}

TEST(Matrix_sTest, TestSetRow)
{
    GSL::Matrix_s m{{1, 2}, {3, 4}, {5, 6}};
    GSL::Matrix_s res{{1, 2}, {7, 8}, {5, 6}};
    m.get_row(1) = GSL::Vector_s{7, 8};
    EXPECT_EQ(m, res);
}

TEST(Matrix_sTest, TestGetCol)
{
    GSL::Matrix_s m{{1, 2}, {3, 4}, {5, 6}};
    GSL::Vector_s res{2, 4, 6};
    EXPECT_EQ(m.get_col(1), res);
}

TEST(Matrix_sTest, TestSetCol)
{
    GSL::Matrix_s m{{1, 2}, {3, 4}, {5, 6}};
    GSL::Matrix_s res{{7, 2}, {8, 4}, {9, 6}};
    m.get_col(0) = GSL::Vector_s{7, 8, 9};
    EXPECT_EQ(m, res);
}

TEST(Matrix_sTest, TestBegin)
{
    GSL::Matrix_s m{{1, 2}, {3, 4}, {5, 6}};
    GSL::Vector_s res{1, 2};

    EXPECT_EQ(*m.begin(), res);
}

TEST(Matrix_sTest, TestcBegin)
{
    GSL::Matrix_s m{{1, 2}, {3, 4}, {5, 6}};
    GSL::Vector_s res{1, 2};

    EXPECT_EQ(*m.cbegin(), res);
}

TEST(Matrix_sTest, TestFront)
{
    GSL::Matrix_s m{{1, 2}, {3, 4}, {5, 6}};
    GSL::Vector_s res{1, 2};

    EXPECT_EQ(m.front(), res);
}

TEST(Matrix_sTest, TestBack)
{
    GSL::Matrix_s m{{1, 2}, {3, 4}, {5, 6}};
    GSL::Vector_s res{5, 6};

    EXPECT_EQ(m.back(), res);
}

TEST(Matrix_sTest, TestAt)
{
    GSL::Matrix_s m{{1, 2}, {3, 4}, {5, 6}};
    GSL::Vector_s res{3, 4};

    EXPECT_EQ(m.at(1), res);
}

TEST(Matrix_sTest, TestAt2)
{
    GSL::Matrix_s m{{1, 2}, {3, 4}, {5, 6}};
    GSL::Matrix_s::value_type res{5};

    EXPECT_EQ(m.at(2, 0), res);
}

TEST(Matrix_sTest, TestIterPreIncrement)
{
    GSL::Matrix_s m{{1, 2}, {3, 4}, {5, 6}};
    EXPECT_EQ(*++m.begin(), m.at(1));
}

TEST(Matrix_sTest, TestIterPostIncrement)
{
    GSL::Matrix_s m{{1, 2}, {3, 4}, {5, 6}};
    auto it = m.begin();
    EXPECT_EQ(*it++, m.at(0));
    EXPECT_EQ(*it, m.at(1));
}

TEST(Matrix_sTest, TestIterPreDecrement)
{
    GSL::Matrix_s m{{1, 2}, {3, 4}, {5, 6}};
    EXPECT_EQ(*--(++m.begin()), m.at(0));
}

TEST(Matrix_sTest, TestIterPostDecrement)
{
    GSL::Matrix_s m{{1, 2}, {3, 4}, {5, 6}};
    auto it = ++m.begin();
    EXPECT_EQ(*it--, m.at(1));
    EXPECT_EQ(*it, m.at(0));
}

TEST(Matrix_sTest, TestIterAddAssign)
{
    GSL::Matrix_s m{{1, 2}, {3, 4}, {5, 6}};
    auto it = m.begin();
    it += 2;
    EXPECT_EQ(*it, m.at(2));
}

TEST(Matrix_sTest, TestIterSubAssign)
{
    GSL::Matrix_s m{{1, 2}, {3, 4}, {5, 6}};
    auto it = m.begin();
    it += 2;
    it -= 1;
    EXPECT_EQ(*it, m.at(1));
}

TEST(Matrix_sTest, TestIterAdd)
{
    GSL::Matrix_s m{{1, 2}, {3, 4}, {5, 6}};
    auto it = m.begin();
    EXPECT_EQ(*(it + 2), m.at(2));
}

TEST(Matrix_sTest, TestIterAdd2)
{
    GSL::Matrix_s m{{1, 2}, {3, 4}, {5, 6}};
    auto it = m.begin();
    EXPECT_EQ(*(2 + it), m.at(2));
}

TEST(Matrix_sTest, TestIterSub)
{
    GSL::Matrix_s m{{1, 2}, {3, 4}, {5, 6}};
    auto it = m.begin();
    it += 2;
    EXPECT_EQ(*(it - 1), m.at(1));
}

TEST(Matrix_sTest, TestIterSub2)
{
    GSL::Matrix_s m{{1, 2}, {3, 4}, {5, 6}};
    auto it1 = m.begin(), it2 = m.begin();
    it2 += 2;
    EXPECT_EQ(it2 - it1, 2);
}

TEST(Matrix_sTest, TestIterEq)
{
    GSL::Matrix_s m{{1, 2}, {3, 4}, {5, 6}};
    auto it1 = m.begin(), it2 = m.begin();
    it2 += 2;
    EXPECT_EQ(*++(++it1), *it2);
}

TEST(Matrix_sTest, TestIterNeq)
{
    GSL::Matrix_s m{{1, 2}, {3, 4}, {5, 6}};
    auto it = m.begin();
    GSL::Vector_s res{*it};
    EXPECT_NE(res, *(it + 1));
}

TEST(Matrix_sTest, TestEnd)
{
    GSL::Matrix_s m{{1, 2}, {3, 4}, {5, 6}};
    auto it1 = m.end();
    EXPECT_EQ(*--it1, *(m.begin() + 2));
}

TEST(Matrix_sTest, TestcEnd)
{
    GSL::Matrix_s m{{1, 2}, {3, 4}, {5, 6}};
    auto it1 = m.cend();
    EXPECT_EQ(*--it1, *(m.begin() + 2));
}

TEST(Matrix_sTest, TestRbegin)
{
    GSL::Matrix_s m{{1, 2}, {3, 4}, {5, 6}};
    GSL::Vector_s res{5, 6};
    EXPECT_EQ(*m.rbegin(), res);
}

TEST(Matrix_sTest, TestcRbegin)
{
    GSL::Matrix_s m{{1, 2}, {3, 4}, {5, 6}};
    GSL::Vector_s res{5, 6};
    EXPECT_EQ(*m.crbegin(), res);
}

TEST(Matrix_sTest, TestRend)
{
    GSL::Matrix_s m{{1, 2}, {3, 4}, {5, 6}};
    auto it1 = m.rend();
    EXPECT_EQ(*--it1, *(m.rbegin() + 2));
}

TEST(Matrix_sTest, TestcRend)
{
    GSL::Matrix_s m{{1, 2}, {3, 4}, {5, 6}};
    auto it1 = m.crend();
    EXPECT_EQ(*--it1, *(m.crbegin() + 2));
}
