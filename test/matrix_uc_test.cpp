#include "GSLpp/matrix.h"
#include "GSLpp/vector.h"
#include <gtest/gtest.h>

TEST(Matrix_ucTest, TestConstruction)
{
    size_t rows = 2, columns = 2;
    GSL::Matrix_uc m(rows, columns);

    for(size_t i = 0; i < rows; i++){
        for(size_t j = 0; j < columns; j++){
            EXPECT_EQ(m[i][j], 0);
        }
    }
}

TEST(Matrix_ucTest, TestConstructionInitializerList)
{
    GSL::Matrix_uc m{{1, 2}, {3, 4}};
    size_t rows = 2, columns = 2;
    for(size_t i = 0; i < rows; i++){
        for(size_t j = 0; j < columns; j++){
            EXPECT_EQ(m[i][j], columns*i+j+1);
        }
    }
}

TEST(Matrix_ucTest, TestConstructionCopy)
{
    size_t rows = 2, columns = 2;
    GSL::Matrix_uc m1{{1, 2}, {3, 4}}, m2(m1);
    for(size_t i = 0; i < rows; i++){
        for(size_t j = 0; j < columns; j++){
            EXPECT_EQ(m1[i][j], m2[i][j]);
        }
    }
}

TEST(Matrix_ucTest, TestConstructionMove)
{
    size_t rows = 2, columns = 2;
    GSL::Matrix_uc m1{{1, 2}, {3, 4}}, m2(std::move(m1));
    for(size_t i = 0; i < rows; i++){
        for(size_t j = 0; j < columns; j++){
            EXPECT_EQ(m2[i][j], columns*i+j+1);
        }
    }
}

TEST(Matrix_ucTest, TestEqual)
{
    GSL::Matrix_uc m1{{1, 2}, {3, 4}}, m2(m1);
    EXPECT_TRUE(m1 == m2);
}

TEST(Matrix_ucTest, TestNequal)
{
    GSL::Matrix_uc m1{{1, 2}, {3, 4}}, m2(m1);
    EXPECT_FALSE(m1 != m2);
}

TEST(Matrix_ucTest, TestCopy)
{
    GSL::Matrix_uc m1{{1, 2}, {3, 4}}, m2;
    m2 = m1;
    EXPECT_EQ(m1, m2);
}

TEST(Matrix_ucTest, TestMove)
{
    GSL::Matrix_uc m1{{1, 2}, {3, 4}}, m1s(m1), m2;
    m2 = std::move(m1);
    EXPECT_EQ(m1s, m2);
}

TEST(Matrix_ucTest, TestCopy2)
{
    GSL::Matrix_uc m1{{1, 2}, {3, 4}}, m2;
    m2.copy(m1);
    EXPECT_EQ(m1, m2);
}

TEST(Matrix_ucTest, TestDecayToGSLMatrix_uc)
{
    GSL::Matrix_uc m{{1, 2}, {3, 4}};
    gsl_matrix_uchar gm = m;
    EXPECT_EQ(gsl_matrix_uchar_get(&gm, 0, 1), 2);
}

TEST(Matrix_ucTest, TestDim)
{
    GSL::Matrix_uc m{{1, 2}, {3, 4}, {5, 6}};
    std::pair<size_t, size_t> d(3,2);
    EXPECT_EQ(m.dim(), d);
}

TEST(Matrix_ucTest, TestSize)
{
    GSL::Matrix_uc m{{1, 2}, {3, 4}, {5, 6}};
    std::pair<size_t, size_t> d(3,2);
    EXPECT_EQ(m.size(), d);
}

TEST(Matrix_ucTest, TestAddAssign)
{
    GSL::Matrix_uc m{{1, 2}, {3, 4}, {5, 6}}, n{{1, 2}, {3, 4}, {5, 6}};
    m += n;
    GSL::Matrix_uc res{{2, 4}, {6, 8}, {10, 12}};
    EXPECT_EQ(m, res);
}

TEST(Matrix_ucTest, TestSubAssign)
{
    GSL::Matrix_uc m{{1, 2}, {3, 4}, {5, 6}}, n{{1, 2}, {3, 4}, {5, 6}};
    m -= n;
    GSL::Matrix_uc res{{0, 0}, {0, 0}, {0, 0}};
    EXPECT_EQ(m, res);
}

TEST(Matrix_ucTest, TestMultAssign)
{
    GSL::Matrix_uc m{{1, 2}, {3, 4}, {5, 6}}, n{{1, 2, 3}, {4, 5, 6}};
    m *= n;
    GSL::Matrix_uc res{{9, 12, 15}, {19, 26, 33}, {29, 40, 51}};
    EXPECT_EQ(m, res);
}

TEST(Matrix_ucTest, TestDivAssign)
{
    GSL::Matrix_uc m{{1, 2}, {3, 4}, {5, 6}}, n{{1, 2}, {3, 4}, {5, 6}};
    m /= n;
    GSL::Matrix_uc res{{1, 1}, {1, 1}, {1, 1}};
    EXPECT_EQ(m, res);
}

TEST(Matrix_ucTest, TestMultScaleAssign)
{
    GSL::Matrix_uc m{{1, 2}, {3, 4}, {5, 6}};
    m *= 2;
    GSL::Matrix_uc res{{2, 4}, {6, 8}, {10, 12}};
    EXPECT_EQ(m, res);
}

TEST(Matrix_ucTest, TestDivScaleAssign)
{
    GSL::Matrix_uc m{{1, 2}, {3, 4}, {5, 6}};
    m /= 2;
    GSL::Matrix_uc res{{0, 1}, {1, 2}, {2, 3}};
    EXPECT_EQ(m, res);
}

TEST(Matrix_ucTest, TestAdd)
{
    GSL::Matrix_uc m{{1, 2}, {3, 4}, {5, 6}}, n{{1, 2}, {3, 4}, {5, 6}};
    GSL::Matrix_uc res{{2, 4}, {6, 8}, {10, 12}};
    EXPECT_EQ(m+n, res);
}

TEST(Matrix_ucTest, TestSub)
{
    GSL::Matrix_uc m{{1, 2}, {3, 4}, {5, 6}}, n{{1, 2}, {3, 4}, {5, 6}};
    GSL::Matrix_uc res{{0, 0}, {0, 0}, {0, 0}};
    EXPECT_EQ(m-n, res);
}

TEST(Matrix_ucTest, TestMult)
{
    GSL::Matrix_uc m{{1, 2}, {3, 4}, {5, 6}}, n{{1, 2, 3}, {4, 5, 6}};
    GSL::Matrix_uc res{{9, 12, 15}, {19, 26, 33}, {29, 40, 51}};
    EXPECT_EQ(m*n, res);
}

TEST(Matrix_ucTest, TestDiv)
{
    GSL::Matrix_uc m{{1, 2}, {3, 4}, {5, 6}}, n{{1, 2}, {3, 4}, {5, 6}};
    GSL::Matrix_uc res{{1, 1}, {1, 1}, {1, 1}};
    EXPECT_EQ(m/n, res);
}

TEST(Matrix_ucTest, TestMultScale)
{
    GSL::Matrix_uc m{{1, 2}, {3, 4}, {5, 6}};
    GSL::Matrix_uc res{{2, 4}, {6, 8}, {10, 12}};
    EXPECT_EQ(m*2, res);
}

TEST(Matrix_ucTest, TestMultScale2)
{
    GSL::Matrix_uc m{{1, 2}, {3, 4}, {5, 6}};
    GSL::Matrix_uc res{{2, 4}, {6, 8}, {10, 12}};
    EXPECT_EQ(2*m, res);
}

TEST(Matrix_ucTest, TestDivScale)
{
    GSL::Matrix_uc m{{1, 2}, {3, 4}, {5, 6}};
    GSL::Matrix_uc res{{0, 1}, {1, 2}, {2, 3}};
    EXPECT_EQ(m/2, res);
}

TEST(Matrix_ucTest, TestTranspose)
{
    GSL::Matrix_uc m{{1, 2}, {3, 4}, {5, 6}};
    GSL::Matrix_uc res{{1, 3, 5},{2, 4, 6}};
    EXPECT_EQ(m.transpose(), res);
}

TEST(Matrix_ucTest, TestHermitian)
{
    GSL::Matrix_uc m{{1, 2}, {3, 4}, {5, 6}};
    GSL::Matrix_uc res{{1, 3, 5},{2, 4, 6}};
    EXPECT_EQ(m.hermitian_transpose(), res);
}

TEST(Matrix_ucTest, TestGetRow)
{
    GSL::Matrix_uc m{{1, 2}, {3, 4}, {5, 6}};
    GSL::Vector_uc res{5, 6};
    EXPECT_EQ(m.get_row(2), res);
}

TEST(Matrix_ucTest, TestSetRow)
{
    GSL::Matrix_uc m{{1, 2}, {3, 4}, {5, 6}};
    GSL::Matrix_uc res{{1, 2}, {7, 8}, {5, 6}};
    m.get_row(1) = GSL::Vector_uc{7, 8};
    EXPECT_EQ(m, res);
}

TEST(Matrix_ucTest, TestGetCol)
{
    GSL::Matrix_uc m{{1, 2}, {3, 4}, {5, 6}};
    GSL::Vector_uc res{2, 4, 6};
    EXPECT_EQ(m.get_col(1), res);
}

TEST(Matrix_ucTest, TestSetCol)
{
    GSL::Matrix_uc m{{1, 2}, {3, 4}, {5, 6}};
    GSL::Matrix_uc res{{7, 2}, {8, 4}, {9, 6}};
    m.get_col(0) = GSL::Vector_uc{7, 8, 9};
    EXPECT_EQ(m, res);
}

TEST(Matrix_ucTest, TestBegin)
{
    GSL::Matrix_uc m{{1, 2}, {3, 4}, {5, 6}};
    GSL::Vector_uc res{1, 2};

    EXPECT_EQ(*m.begin(), res);
}

TEST(Matrix_ucTest, TestcBegin)
{
    GSL::Matrix_uc m{{1, 2}, {3, 4}, {5, 6}};
    GSL::Vector_uc res{1, 2};

    EXPECT_EQ(*m.cbegin(), res);
}

TEST(Matrix_ucTest, TestFront)
{
    GSL::Matrix_uc m{{1, 2}, {3, 4}, {5, 6}};
    GSL::Vector_uc res{1, 2};

    EXPECT_EQ(m.front(), res);
}

TEST(Matrix_ucTest, TestBack)
{
    GSL::Matrix_uc m{{1, 2}, {3, 4}, {5, 6}};
    GSL::Vector_uc res{5, 6};

    EXPECT_EQ(m.back(), res);
}

TEST(Matrix_ucTest, TestAt)
{
    GSL::Matrix_uc m{{1, 2}, {3, 4}, {5, 6}};
    GSL::Vector_uc res{3, 4};

    EXPECT_EQ(m.at(1), res);
}

TEST(Matrix_ucTest, TestAt2)
{
    GSL::Matrix_uc m{{1, 2}, {3, 4}, {5, 6}};
    GSL::Matrix_uc::value_type res{5};

    EXPECT_EQ(m.at(2, 0), res);
}

TEST(Matrix_ucTest, TestIterPreIncrement)
{
    GSL::Matrix_uc m{{1, 2}, {3, 4}, {5, 6}};
    EXPECT_EQ(*++m.begin(), m.at(1));
}

TEST(Matrix_ucTest, TestIterPostIncrement)
{
    GSL::Matrix_uc m{{1, 2}, {3, 4}, {5, 6}};
    auto it = m.begin();
    it++;
    EXPECT_EQ(*it, m.at(1));
}

TEST(Matrix_ucTest, TestIterPreDecrement)
{
    GSL::Matrix_uc m{{1, 2}, {3, 4}, {5, 6}};
    EXPECT_EQ(*--(++m.begin()), m.at(0));
}

TEST(Matrix_ucTest, TestIterPostDecrement)
{
    GSL::Matrix_uc m{{1, 2}, {3, 4}, {5, 6}};
    auto it = m.begin();
    (it++)--;
    EXPECT_EQ(*it, m.at(0));
}

TEST(Matrix_ucTest, TestIterAddAssign)
{
    GSL::Matrix_uc m{{1, 2}, {3, 4}, {5, 6}};
    auto it = m.begin();
    it += 2;
    EXPECT_EQ(*it, m.at(2));
}

TEST(Matrix_ucTest, TestIterSubAssign)
{
    GSL::Matrix_uc m{{1, 2}, {3, 4}, {5, 6}};
    auto it = m.begin();
    it += 2;
    it -= 1;
    EXPECT_EQ(*it, m.at(1));
}

TEST(Matrix_ucTest, TestIterAdd)
{
    GSL::Matrix_uc m{{1, 2}, {3, 4}, {5, 6}};
    auto it = m.begin();
    EXPECT_EQ(*(it + 2), m.at(2));
}

TEST(Matrix_ucTest, TestIterAdd2)
{
    GSL::Matrix_uc m{{1, 2}, {3, 4}, {5, 6}};
    auto it = m.begin();
    EXPECT_EQ(*(2 + it), m.at(2));
}

TEST(Matrix_ucTest, TestIterSub)
{
    GSL::Matrix_uc m{{1, 2}, {3, 4}, {5, 6}};
    auto it = m.begin();
    it += 2;
    EXPECT_EQ(*(it - 1), m.at(1));
}

TEST(Matrix_ucTest, TestIterSub2)
{
    GSL::Matrix_uc m{{1, 2}, {3, 4}, {5, 6}};
    auto it1 = m.begin(), it2 = m.begin();
    it2 += 2;
    EXPECT_EQ(it2 - it1, 2);
}

TEST(Matrix_ucTest, TestIterEq)
{
    GSL::Matrix_uc m{{1, 2}, {3, 4}, {5, 6}};
    auto it1 = m.begin(), it2 = m.begin();
    it2 += 2;
    EXPECT_EQ(*++(++it1), *it2);
}

TEST(Matrix_ucTest, TestIterNeq)
{
    GSL::Matrix_uc m{{1, 2}, {3, 4}, {5, 6}};
    auto it = m.begin();
    GSL::Vector_uc res{*it};
    EXPECT_NE(res, *(it + 1));
}

TEST(Matrix_ucTest, TestEnd)
{
    GSL::Matrix_uc m{{1, 2}, {3, 4}, {5, 6}};
    auto it1 = m.end();
    EXPECT_EQ(*--it1, *(m.begin() + 2));
}

TEST(Matrix_ucTest, TestcEnd)
{
    GSL::Matrix_uc m{{1, 2}, {3, 4}, {5, 6}};
    auto it1 = m.cend();
    EXPECT_EQ(*--it1, *(m.begin() + 2));
}

TEST(Matrix_ucTest, TestRbegin)
{
    GSL::Matrix_uc m{{1, 2}, {3, 4}, {5, 6}};
    GSL::Vector_uc res{5, 6};
    EXPECT_EQ(*m.rbegin(), res);
}

TEST(Matrix_ucTest, TestcRbegin)
{
    GSL::Matrix_uc m{{1, 2}, {3, 4}, {5, 6}};
    GSL::Vector_uc res{5, 6};
    EXPECT_EQ(*m.crbegin(), res);
}

TEST(Matrix_ucTest, TestRend)
{
    GSL::Matrix_uc m{{1, 2}, {3, 4}, {5, 6}};
    auto it1 = m.rend();
    EXPECT_EQ(*--it1, *(m.rbegin() + 2));
}

TEST(Matrix_ucTest, TestcRend)
{
    GSL::Matrix_uc m{{1, 2}, {3, 4}, {5, 6}};
    auto it1 = m.crend();
    EXPECT_EQ(*--it1, *(m.crbegin() + 2));
}
