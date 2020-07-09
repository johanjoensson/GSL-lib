#include "GSLpp/matrix.h"
#include "GSLpp/vector.h"
#include <gtest/gtest.h>

TEST(Matrix_ldTest, TestConstruction)
{
    size_t rows = 2, columns = 2;
    GSL::Matrix_ld m(rows, columns);

    for(size_t i = 0; i < rows; i++){
        for(size_t j = 0; j < columns; j++){
            EXPECT_EQ(m[i][j], 0);
        }
    }
}

TEST(Matrix_ldTest, TestConstructionInitializerList)
{
    GSL::Matrix_ld m{{1, 2}, {3, 4}};
    size_t rows = 2, columns = 2;
    for(size_t i = 0; i < rows; i++){
        for(size_t j = 0; j < columns; j++){
            EXPECT_EQ(m[i][j], static_cast<long double>(columns*i+j)+1);
        }
    }
}

TEST(Matrix_ldTest, TestConstructionCopy)
{
    size_t rows = 2, columns = 2;
    GSL::Matrix_ld m1{{1, 2}, {3, 4}}, m2(m1);
    for(size_t i = 0; i < rows; i++){
        for(size_t j = 0; j < columns; j++){
            EXPECT_EQ(m1[i][j], m2[i][j]);
        }
    }
}

TEST(Matrix_ldTest, TestConstructionMove)
{
    size_t rows = 2, columns = 2;
    GSL::Matrix_ld m1{{1, 2}, {3, 4}}, m2(std::move(m1));
    for(size_t i = 0; i < rows; i++){
        for(size_t j = 0; j < columns; j++){
            EXPECT_EQ(m2[i][j], static_cast<long double>(columns*i+j)+1);
        }
    }
}

TEST(Matrix_ldTest, TestEqual)
{
    GSL::Matrix_ld m1{{1, 2}, {3, 4}}, m2(m1);
    EXPECT_TRUE(m1 == m2);
}

TEST(Matrix_ldTest, TestNequal)
{
    GSL::Matrix_ld m1{{1, 2}, {3, 4}}, m2(m1);
    EXPECT_FALSE(m1 != m2);
}

TEST(Matrix_ldTest, TestCopy)
{
    GSL::Matrix_ld m1{{1, 2}, {3, 4}}, m2;
    m2 = m1;
    EXPECT_EQ(m1, m2);
}

TEST(Matrix_ldTest, TestMove)
{
    GSL::Matrix_ld m1{{1, 2}, {3, 4}}, m1s(m1), m2;
    m2 = std::move(m1);
    EXPECT_EQ(m1s, m2);
}

TEST(Matrix_ldTest, TestCopy2)
{
    GSL::Matrix_ld m1{{1, 2}, {3, 4}}, m2;
    m2.copy(m1);
    EXPECT_EQ(m1, m2);
}

TEST(Matrix_ldTest, TestDecayToGSLMatrix_ld)
{
    GSL::Matrix_ld m{{1, 2}, {3, 4}};
    gsl_matrix_long_double gm = m;
    EXPECT_EQ(gsl_matrix_long_double_get(&gm, 0, 1), 2);
}

TEST(Matrix_ldTest, TestDim)
{
    GSL::Matrix_ld m{{1, 2}, {3, 4}, {5, 6}};
    std::pair<size_t, size_t> d(3,2);
    EXPECT_EQ(m.dim(), d);
}

TEST(Matrix_ldTest, TestSize)
{
    GSL::Matrix_ld m{{1, 2}, {3, 4}, {5, 6}};
    std::pair<size_t, size_t> d(3,2);
    EXPECT_EQ(m.size(), d);
}

TEST(Matrix_ldTest, TestAddAssign)
{
    GSL::Matrix_ld m{{1, 2}, {3, 4}, {5, 6}}, n{{1, 2}, {3, 4}, {5, 6}};
    m += n;
    GSL::Matrix_ld res{{2, 4}, {6, 8}, {10, 12}};
    EXPECT_EQ(m, res);
}

TEST(Matrix_ldTest, TestSubAssign)
{
    GSL::Matrix_ld m{{1, 2}, {3, 4}, {5, 6}}, n{{1, 2}, {3, 4}, {5, 6}};
    m -= n;
    GSL::Matrix_ld res{{0, 0}, {0, 0}, {0, 0}};
    EXPECT_EQ(m, res);
}

TEST(Matrix_ldTest, TestMultAssign)
{
    GSL::Matrix_ld m{{1, 2}, {3, 4}, {5, 6}}, n{{1, 2, 3}, {4, 5, 6}};
    m *= n;
    GSL::Matrix_ld res{{9, 12, 15}, {19, 26, 33}, {29, 40, 51}};
    EXPECT_EQ(m, res);
}

TEST(Matrix_ldTest, TestDivAssign)
{
    GSL::Matrix_ld m{{1, 2}, {3, 4}, {5, 6}}, n{{1, 2}, {3, 4}, {5, 6}};
    m /= n;
    GSL::Matrix_ld res{{1, 1}, {1, 1}, {1, 1}};
    EXPECT_EQ(m, res);
}

TEST(Matrix_ldTest, TestMultScaleAssign)
{
    GSL::Matrix_ld m{{1, 2}, {3, 4}, {5, 6}};
    m *= 2;
    GSL::Matrix_ld res{{2, 4}, {6, 8}, {10, 12}};
    EXPECT_EQ(m, res);
}

TEST(Matrix_ldTest, TestDivScaleAssign)
{
    GSL::Matrix_ld m{{1, 2}, {3, 4}, {5, 6}};
    m /= 2;
    GSL::Matrix_ld res{{0.5l, 1}, {1.5l, 2}, {2.5l, 3}};
    EXPECT_EQ(m, res);
}

TEST(Matrix_ldTest, TestAdd)
{
    GSL::Matrix_ld m{{1, 2}, {3, 4}, {5, 6}}, n{{1, 2}, {3, 4}, {5, 6}};
    GSL::Matrix_ld res{{2, 4}, {6, 8}, {10, 12}};
    EXPECT_EQ(m+n, res);
}

TEST(Matrix_ldTest, TestSub)
{
    GSL::Matrix_ld m{{1, 2}, {3, 4}, {5, 6}}, n{{1, 2}, {3, 4}, {5, 6}};
    GSL::Matrix_ld res{{0, 0}, {0, 0}, {0, 0}};
    EXPECT_EQ(m-n, res);
}

TEST(Matrix_ldTest, TestMult)
{
    GSL::Matrix_ld m{{1, 2}, {3, 4}, {5, 6}}, n{{1, 2, 3}, {4, 5, 6}};
    GSL::Matrix_ld res{{9, 12, 15}, {19, 26, 33}, {29, 40, 51}};
    EXPECT_EQ(m*n, res);
}

TEST(Matrix_ldTest, TestDiv)
{
    GSL::Matrix_ld m{{1, 2}, {3, 4}, {5, 6}}, n{{1, 2}, {3, 4}, {5, 6}};
    GSL::Matrix_ld res{{1, 1}, {1, 1}, {1, 1}};
    EXPECT_EQ(m/n, res);
}

TEST(Matrix_ldTest, TestMultScale)
{
    GSL::Matrix_ld m{{1, 2}, {3, 4}, {5, 6}};
    GSL::Matrix_ld res{{2, 4}, {6, 8}, {10, 12}};
    EXPECT_EQ(m*2, res);
}

TEST(Matrix_ldTest, TestMultScale2)
{
    GSL::Matrix_ld m{{1, 2}, {3, 4}, {5, 6}};
    GSL::Matrix_ld res{{2, 4}, {6, 8}, {10, 12}};
    EXPECT_EQ(2*m, res);
}

TEST(Matrix_ldTest, TestDivScale)
{
    GSL::Matrix_ld m{{1, 2}, {3, 4}, {5, 6}};
    GSL::Matrix_ld res{{0.5l, 1}, {1.5l, 2}, {2.5l, 3}};
    EXPECT_EQ(m/2, res);
}

TEST(Matrix_ldTest, TestTranspose)
{
    GSL::Matrix_ld m{{1, 2}, {3, 4}, {5, 6}};
    GSL::Matrix_ld res{{1, 3, 5},{2, 4, 6}};
    EXPECT_EQ(m.transpose(), res);
}

TEST(Matrix_ldTest, TestHermitian)
{
    GSL::Matrix_ld m{{1, 2}, {3, 4}, {5, 6}};
    GSL::Matrix_ld res{{1, 3, 5},{2, 4, 6}};
    EXPECT_EQ(m.hermitian_transpose(), res);
}

TEST(Matrix_ldTest, TestGetRow)
{
    GSL::Matrix_ld m{{1, 2}, {3, 4}, {5, 6}};
    GSL::Vector_ld res{5, 6};
    EXPECT_EQ(m.get_row(2), res);
}

TEST(Matrix_ldTest, TestSetRow)
{
    GSL::Matrix_ld m{{1, 2}, {3, 4}, {5, 6}};
    GSL::Matrix_ld res{{1, 2}, {7, 8}, {5, 6}};
    m.get_row(1) = GSL::Vector_ld{7, 8};
    EXPECT_EQ(m, res);
}

TEST(Matrix_ldTest, TestGetCol)
{
    GSL::Matrix_ld m{{1, 2}, {3, 4}, {5, 6}};
    GSL::Vector_ld res{2, 4, 6};
    EXPECT_EQ(m.get_col(1), res);
}

TEST(Matrix_ldTest, TestSetCol)
{
    GSL::Matrix_ld m{{1, 2}, {3, 4}, {5, 6}};
    GSL::Matrix_ld res{{7, 2}, {8, 4}, {9, 6}};
    m.get_col(0) = GSL::Vector_ld{7, 8, 9};
    EXPECT_EQ(m, res);
}

TEST(Matrix_ldTest, TestBegin)
{
    GSL::Matrix_ld m{{1, 2}, {3, 4}, {5, 6}};
    GSL::Vector_ld res{1, 2};

    EXPECT_EQ(*m.begin(), res);
}

TEST(Matrix_ldTest, TestcBegin)
{
    GSL::Matrix_ld m{{1, 2}, {3, 4}, {5, 6}};
    GSL::Vector_ld res{1, 2};

    EXPECT_EQ(*m.cbegin(), res);
}

TEST(Matrix_ldTest, TestFront)
{
    GSL::Matrix_ld m{{1, 2}, {3, 4}, {5, 6}};
    GSL::Vector_ld res{1, 2};

    EXPECT_EQ(m.front(), res);
}

TEST(Matrix_ldTest, TestBack)
{
    GSL::Matrix_ld m{{1, 2}, {3, 4}, {5, 6}};
    GSL::Vector_ld res{5, 6};

    EXPECT_EQ(m.back(), res);
}

TEST(Matrix_ldTest, TestAt)
{
    GSL::Matrix_ld m{{1, 2}, {3, 4}, {5, 6}};
    GSL::Vector_ld res{3, 4};

    EXPECT_EQ(m.at(1), res);
}

TEST(Matrix_ldTest, TestAt2)
{
    GSL::Matrix_ld m{{1, 2}, {3, 4}, {5, 6}};
    GSL::Matrix_ld::value_type res{5};

    EXPECT_EQ(m.at(2, 0), res);
}

TEST(Matrix_ldTest, TestIterPreIncrement)
{
    GSL::Matrix_ld m{{1, 2}, {3, 4}, {5, 6}};
    EXPECT_EQ(*++m.begin(), m.at(1));
}

TEST(Matrix_ldTest, TestIterPostIncrement)
{
    GSL::Matrix_ld m{{1, 2}, {3, 4}, {5, 6}};
    auto it = m.begin();
    EXPECT_EQ(*it++, m.at(0));
    EXPECT_EQ(*it, m.at(1));
}

TEST(Matrix_ldTest, TestIterPreDecrement)
{
    GSL::Matrix_ld m{{1, 2}, {3, 4}, {5, 6}};
    EXPECT_EQ(*--(++m.begin()), m.at(0));
}

TEST(Matrix_ldTest, TestIterPostDecrement)
{
    GSL::Matrix_ld m{{1, 2}, {3, 4}, {5, 6}};
    auto it = ++m.begin();
    EXPECT_EQ(*it--, m.at(1));
    EXPECT_EQ(*it, m.at(0));
}

TEST(Matrix_ldTest, TestIterAddAssign)
{
    GSL::Matrix_ld m{{1, 2}, {3, 4}, {5, 6}};
    auto it = m.begin();
    it += 2;
    EXPECT_EQ(*it, m.at(2));
}

TEST(Matrix_ldTest, TestIterSubAssign)
{
    GSL::Matrix_ld m{{1, 2}, {3, 4}, {5, 6}};
    auto it = m.begin();
    it += 2;
    it -= 1;
    EXPECT_EQ(*it, m.at(1));
}

TEST(Matrix_ldTest, TestIterAdd)
{
    GSL::Matrix_ld m{{1, 2}, {3, 4}, {5, 6}};
    auto it = m.begin();
    EXPECT_EQ(*(it + 2), m.at(2));
}

TEST(Matrix_ldTest, TestIterAdd2)
{
    GSL::Matrix_ld m{{1, 2}, {3, 4}, {5, 6}};
    auto it = m.begin();
    EXPECT_EQ(*(2 + it), m.at(2));
}

TEST(Matrix_ldTest, TestIterSub)
{
    GSL::Matrix_ld m{{1, 2}, {3, 4}, {5, 6}};
    auto it = m.begin();
    it += 2;
    EXPECT_EQ(*(it - 1), m.at(1));
}

TEST(Matrix_ldTest, TestIterSub2)
{
    GSL::Matrix_ld m{{1, 2}, {3, 4}, {5, 6}};
    auto it1 = m.begin(), it2 = m.begin();
    it2 += 2;
    EXPECT_EQ(it2 - it1, 2);
}

TEST(Matrix_ldTest, TestIterEq)
{
    GSL::Matrix_ld m{{1, 2}, {3, 4}, {5, 6}};
    auto it1 = m.begin(), it2 = m.begin();
    it2 += 2;
    EXPECT_EQ(*++(++it1), *it2);
}

TEST(Matrix_ldTest, TestIterNeq)
{
    GSL::Matrix_ld m{{1, 2}, {3, 4}, {5, 6}};
    auto it = m.begin();
    GSL::Vector_ld res{*it};
    EXPECT_NE(res, *(it + 1));
}

TEST(Matrix_ldTest, TestEnd)
{
    GSL::Matrix_ld m{{1, 2}, {3, 4}, {5, 6}};
    auto it1 = m.end();
    EXPECT_EQ(*--it1, *(m.begin() + 2));
}

TEST(Matrix_ldTest, TestcEnd)
{
    GSL::Matrix_ld m{{1, 2}, {3, 4}, {5, 6}};
    auto it1 = m.cend();
    EXPECT_EQ(*--it1, *(m.begin() + 2));
}

TEST(Matrix_ldTest, TestRbegin)
{
    GSL::Matrix_ld m{{1, 2}, {3, 4}, {5, 6}};
    GSL::Vector_ld res{5, 6};
    EXPECT_EQ(*m.rbegin(), res);
}

TEST(Matrix_ldTest, TestcRbegin)
{
    GSL::Matrix_ld m{{1, 2}, {3, 4}, {5, 6}};
    GSL::Vector_ld res{5, 6};
    EXPECT_EQ(*m.crbegin(), res);
}

TEST(Matrix_ldTest, TestRend)
{
    GSL::Matrix_ld m{{1, 2}, {3, 4}, {5, 6}};
    auto it1 = m.rend();
    EXPECT_EQ(*--it1, *(m.rbegin() + 2));
}

TEST(Matrix_ldTest, TestcRend)
{
    GSL::Matrix_ld m{{1, 2}, {3, 4}, {5, 6}};
    auto it1 = m.crend();
    EXPECT_EQ(*--it1, *(m.crbegin() + 2));
}
