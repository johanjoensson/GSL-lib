#include "GSLpp/matrix.h"
#include "GSLpp/vector.h"
#include <gtest/gtest.h>

TEST(Matrix_uiTest, TestConstruction)
{
    size_t rows = 2, columns = 2;
    GSL::Matrix_ui m(rows, columns);

    for(size_t i = 0; i < rows; i++){
        for(size_t j = 0; j < columns; j++){
            EXPECT_EQ(m[i][j], 0);
        }
    }
}

TEST(Matrix_uiTest, TestConstructionInitializerList)
{
    GSL::Matrix_ui m{{1, 2}, {3, 4}};
    size_t rows = 2, columns = 2;
    for(size_t i = 0; i < rows; i++){
        for(size_t j = 0; j < columns; j++){
            EXPECT_EQ(m[i][j], columns*i+j+1);
        }
    }
}

TEST(Matrix_uiTest, TestConstructionCopy)
{
    size_t rows = 2, columns = 2;
    GSL::Matrix_ui m1{{1, 2}, {3, 4}}, m2(m1);
    for(size_t i = 0; i < rows; i++){
        for(size_t j = 0; j < columns; j++){
            EXPECT_EQ(m1[i][j], m2[i][j]);
        }
    }
}

TEST(Matrix_uiTest, TestConstructionMove)
{
    size_t rows = 2, columns = 2;
    GSL::Matrix_ui m1{{1, 2}, {3, 4}}, m2(std::move(m1));
    for(size_t i = 0; i < rows; i++){
        for(size_t j = 0; j < columns; j++){
            EXPECT_EQ(m2[i][j], columns*i+j+1);
        }
    }
}

TEST(Matrix_uiTest, TestEqual)
{
    GSL::Matrix_ui m1{{1, 2}, {3, 4}}, m2(m1);
    EXPECT_TRUE(m1 == m2);
}

TEST(Matrix_uiTest, TestNequal)
{
    GSL::Matrix_ui m1{{1, 2}, {3, 4}}, m2(m1);
    EXPECT_FALSE(m1 != m2);
}

TEST(Matrix_uiTest, TestCopy)
{
    GSL::Matrix_ui m1{{1, 2}, {3, 4}}, m2;
    m2 = m1;
    EXPECT_EQ(m1, m2);
}

TEST(Matrix_uiTest, TestMove)
{
    GSL::Matrix_ui m1{{1, 2}, {3, 4}}, m1s(m1), m2;
    m2 = std::move(m1);
    EXPECT_EQ(m1s, m2);
}

TEST(Matrix_uiTest, TestCopy2)
{
    GSL::Matrix_ui m1{{1, 2}, {3, 4}}, m2;
    m2.copy(m1);
    EXPECT_EQ(m1, m2);
}

TEST(Matrix_uiTest, TestDecayToGSLMatrix_ui)
{
    GSL::Matrix_ui m{{1, 2}, {3, 4}};
    gsl_matrix_uint gm = m;
    EXPECT_EQ(gsl_matrix_uint_get(&gm, 0, 1), 2);
}

TEST(Matrix_uiTest, TestDim)
{
    GSL::Matrix_ui m{{1, 2}, {3, 4}, {5, 6}};
    std::pair<size_t, size_t> d(3,2);
    EXPECT_EQ(m.dim(), d);
}

TEST(Matrix_uiTest, TestSize)
{
    GSL::Matrix_ui m{{1, 2}, {3, 4}, {5, 6}};
    std::pair<size_t, size_t> d(3,2);
    EXPECT_EQ(m.size(), d);
}

TEST(Matrix_uiTest, TestAddAssign)
{
    GSL::Matrix_ui m{{1, 2}, {3, 4}, {5, 6}}, n{{1, 2}, {3, 4}, {5, 6}};
    m += n;
    GSL::Matrix_ui res{{2, 4}, {6, 8}, {10, 12}};
    EXPECT_EQ(m, res);
}

TEST(Matrix_uiTest, TestSubAssign)
{
    GSL::Matrix_ui m{{1, 2}, {3, 4}, {5, 6}}, n{{1, 2}, {3, 4}, {5, 6}};
    m -= n;
    GSL::Matrix_ui res{{0, 0}, {0, 0}, {0, 0}};
    EXPECT_EQ(m, res);
}

TEST(Matrix_uiTest, TestMultAssign)
{
    GSL::Matrix_ui m{{1, 2}, {3, 4}, {5, 6}}, n{{1, 2, 3}, {4, 5, 6}};
    m *= n;
    GSL::Matrix_ui res{{9, 12, 15}, {19, 26, 33}, {29, 40, 51}};
    EXPECT_EQ(m, res);
}

TEST(Matrix_uiTest, TestDivAssign)
{
    GSL::Matrix_ui m{{1, 2}, {3, 4}, {5, 6}}, n{{1, 2}, {3, 4}, {5, 6}};
    m /= n;
    GSL::Matrix_ui res{{1, 1}, {1, 1}, {1, 1}};
    EXPECT_EQ(m, res);
}

TEST(Matrix_uiTest, TestMultScaleAssign)
{
    GSL::Matrix_ui m{{1, 2}, {3, 4}, {5, 6}};
    m *= 2;
    GSL::Matrix_ui res{{2, 4}, {6, 8}, {10, 12}};
    EXPECT_EQ(m, res);
}

TEST(Matrix_uiTest, TestDivScaleAssign)
{
    GSL::Matrix_ui m{{1, 2}, {3, 4}, {5, 6}};
    m /= 2;
    GSL::Matrix_ui res{{0, 1}, {1, 2}, {2, 3}};
    EXPECT_EQ(m, res);
}

TEST(Matrix_uiTest, TestAdd)
{
    GSL::Matrix_ui m{{1, 2}, {3, 4}, {5, 6}}, n{{1, 2}, {3, 4}, {5, 6}};
    GSL::Matrix_ui res{{2, 4}, {6, 8}, {10, 12}};
    EXPECT_EQ(m+n, res);
}

TEST(Matrix_uiTest, TestSub)
{
    GSL::Matrix_ui m{{1, 2}, {3, 4}, {5, 6}}, n{{1, 2}, {3, 4}, {5, 6}};
    GSL::Matrix_ui res{{0, 0}, {0, 0}, {0, 0}};
    EXPECT_EQ(m-n, res);
}

TEST(Matrix_uiTest, TestMult)
{
    GSL::Matrix_ui m{{1, 2}, {3, 4}, {5, 6}}, n{{1, 2, 3}, {4, 5, 6}};
    GSL::Matrix_ui res{{9, 12, 15}, {19, 26, 33}, {29, 40, 51}};
    EXPECT_EQ(m*n, res);
}

TEST(Matrix_uiTest, TestDiv)
{
    GSL::Matrix_ui m{{1, 2}, {3, 4}, {5, 6}}, n{{1, 2}, {3, 4}, {5, 6}};
    GSL::Matrix_ui res{{1, 1}, {1, 1}, {1, 1}};
    EXPECT_EQ(m/n, res);
}

TEST(Matrix_uiTest, TestMultScale)
{
    GSL::Matrix_ui m{{1, 2}, {3, 4}, {5, 6}};
    GSL::Matrix_ui res{{2, 4}, {6, 8}, {10, 12}};
    EXPECT_EQ(m*2, res);
}

TEST(Matrix_uiTest, TestMultScale2)
{
    GSL::Matrix_ui m{{1, 2}, {3, 4}, {5, 6}};
    GSL::Matrix_ui res{{2, 4}, {6, 8}, {10, 12}};
    EXPECT_EQ(2*m, res);
}

TEST(Matrix_uiTest, TestDivScale)
{
    GSL::Matrix_ui m{{1, 2}, {3, 4}, {5, 6}};
    GSL::Matrix_ui res{{0, 1}, {1, 2}, {2, 3}};
    EXPECT_EQ(m/2, res);
}

TEST(Matrix_uiTest, TestTranspose)
{
    GSL::Matrix_ui m{{1, 2}, {3, 4}, {5, 6}};
    GSL::Matrix_ui res{{1, 3, 5},{2, 4, 6}};
    EXPECT_EQ(m.transpose(), res);
}

TEST(Matrix_uiTest, TestHermitian)
{
    GSL::Matrix_ui m{{1, 2}, {3, 4}, {5, 6}};
    GSL::Matrix_ui res{{1, 3, 5},{2, 4, 6}};
    EXPECT_EQ(m.hermitian_transpose(), res);
}

TEST(Matrix_uiTest, TestGetRow)
{
    GSL::Matrix_ui m{{1, 2}, {3, 4}, {5, 6}};
    GSL::Vector_ui res{5, 6};
    EXPECT_EQ(m.get_row(2), res);
}

TEST(Matrix_uiTest, TestSetRow)
{
    GSL::Matrix_ui m{{1, 2}, {3, 4}, {5, 6}};
    GSL::Matrix_ui res{{1, 2}, {7, 8}, {5, 6}};
    m.get_row(1) = GSL::Vector_ui{7, 8};
    EXPECT_EQ(m, res);
}

TEST(Matrix_uiTest, TestGetCol)
{
    GSL::Matrix_ui m{{1, 2}, {3, 4}, {5, 6}};
    GSL::Vector_ui res{2, 4, 6};
    EXPECT_EQ(m.get_col(1), res);
}

TEST(Matrix_uiTest, TestSetCol)
{
    GSL::Matrix_ui m{{1, 2}, {3, 4}, {5, 6}};
    GSL::Matrix_ui res{{7, 2}, {8, 4}, {9, 6}};
    m.get_col(0) = GSL::Vector_ui{7, 8, 9};
    EXPECT_EQ(m, res);
}

TEST(Matrix_uiTest, TestBegin)
{
    GSL::Matrix_ui m{{1, 2}, {3, 4}, {5, 6}};
    GSL::Vector_ui res{1, 2};

    EXPECT_EQ(*m.begin(), res);
}

TEST(Matrix_uiTest, TestcBegin)
{
    GSL::Matrix_ui m{{1, 2}, {3, 4}, {5, 6}};
    GSL::Vector_ui res{1, 2};

    EXPECT_EQ(*m.cbegin(), res);
}

TEST(Matrix_uiTest, TestFront)
{
    GSL::Matrix_ui m{{1, 2}, {3, 4}, {5, 6}};
    GSL::Vector_ui res{1, 2};

    EXPECT_EQ(m.front(), res);
}

TEST(Matrix_uiTest, TestBack)
{
    GSL::Matrix_ui m{{1, 2}, {3, 4}, {5, 6}};
    GSL::Vector_ui res{5, 6};

    EXPECT_EQ(m.back(), res);
}

TEST(Matrix_uiTest, TestAt)
{
    GSL::Matrix_ui m{{1, 2}, {3, 4}, {5, 6}};
    GSL::Vector_ui res{3, 4};

    EXPECT_EQ(m.at(1), res);
}

TEST(Matrix_uiTest, TestAt2)
{
    GSL::Matrix_ui m{{1, 2}, {3, 4}, {5, 6}};
    GSL::Matrix_ui::value_type res{5};

    EXPECT_EQ(m.at(2, 0), res);
}

TEST(Matrix_uiTest, TestIterPreIncrement)
{
    GSL::Matrix_ui m{{1, 2}, {3, 4}, {5, 6}};
    EXPECT_EQ(*++m.begin(), m.at(1));
}

TEST(Matrix_uiTest, TestIterPostIncrement)
{
    GSL::Matrix_ui m{{1, 2}, {3, 4}, {5, 6}};
    auto it = m.begin();
    EXPECT_EQ(*it++, m.at(0));
    EXPECT_EQ(*it, m.at(1));
}

TEST(Matrix_uiTest, TestIterPreDecrement)
{
    GSL::Matrix_ui m{{1, 2}, {3, 4}, {5, 6}};
    EXPECT_EQ(*--(++m.begin()), m.at(0));
}

TEST(Matrix_uiTest, TestIterPostDecrement)
{
    GSL::Matrix_ui m{{1, 2}, {3, 4}, {5, 6}};
    auto it = ++m.begin();
    EXPECT_EQ(*it--, m.at(1));
    EXPECT_EQ(*it, m.at(0));
}

TEST(Matrix_uiTest, TestIterAddAssign)
{
    GSL::Matrix_ui m{{1, 2}, {3, 4}, {5, 6}};
    auto it = m.begin();
    it += 2;
    EXPECT_EQ(*it, m.at(2));
}

TEST(Matrix_uiTest, TestIterSubAssign)
{
    GSL::Matrix_ui m{{1, 2}, {3, 4}, {5, 6}};
    auto it = m.begin();
    it += 2;
    it -= 1;
    EXPECT_EQ(*it, m.at(1));
}

TEST(Matrix_uiTest, TestIterAdd)
{
    GSL::Matrix_ui m{{1, 2}, {3, 4}, {5, 6}};
    auto it = m.begin();
    EXPECT_EQ(*(it + 2), m.at(2));
}

TEST(Matrix_uiTest, TestIterAdd2)
{
    GSL::Matrix_ui m{{1, 2}, {3, 4}, {5, 6}};
    auto it = m.begin();
    EXPECT_EQ(*(2 + it), m.at(2));
}

TEST(Matrix_uiTest, TestIterSub)
{
    GSL::Matrix_ui m{{1, 2}, {3, 4}, {5, 6}};
    auto it = m.begin();
    it += 2;
    EXPECT_EQ(*(it - 1), m.at(1));
}

TEST(Matrix_uiTest, TestIterSub2)
{
    GSL::Matrix_ui m{{1, 2}, {3, 4}, {5, 6}};
    auto it1 = m.begin(), it2 = m.begin();
    it2 += 2;
    EXPECT_EQ(it2 - it1, 2);
}

TEST(Matrix_uiTest, TestIterEq)
{
    GSL::Matrix_ui m{{1, 2}, {3, 4}, {5, 6}};
    auto it1 = m.begin(), it2 = m.begin();
    it2 += 2;
    EXPECT_EQ(*++(++it1), *it2);
}

TEST(Matrix_uiTest, TestIterNeq)
{
    GSL::Matrix_ui m{{1, 2}, {3, 4}, {5, 6}};
    auto it = m.begin();
    GSL::Vector_ui res{*it};
    EXPECT_NE(res, *(it + 1));
}

TEST(Matrix_uiTest, TestEnd)
{
    GSL::Matrix_ui m{{1, 2}, {3, 4}, {5, 6}};
    auto it1 = m.end();
    EXPECT_EQ(*--it1, *(m.begin() + 2));
}

TEST(Matrix_uiTest, TestcEnd)
{
    GSL::Matrix_ui m{{1, 2}, {3, 4}, {5, 6}};
    auto it1 = m.cend();
    EXPECT_EQ(*--it1, *(m.begin() + 2));
}

TEST(Matrix_uiTest, TestRbegin)
{
    GSL::Matrix_ui m{{1, 2}, {3, 4}, {5, 6}};
    GSL::Vector_ui res{5, 6};
    EXPECT_EQ(*m.rbegin(), res);
}

TEST(Matrix_uiTest, TestcRbegin)
{
    GSL::Matrix_ui m{{1, 2}, {3, 4}, {5, 6}};
    GSL::Vector_ui res{5, 6};
    EXPECT_EQ(*m.crbegin(), res);
}

TEST(Matrix_uiTest, TestRend)
{
    GSL::Matrix_ui m{{1, 2}, {3, 4}, {5, 6}};
    auto it1 = m.rend();
    EXPECT_EQ(*--it1, *(m.rbegin() + 2));
}

TEST(Matrix_uiTest, TestcRend)
{
    GSL::Matrix_ui m{{1, 2}, {3, 4}, {5, 6}};
    auto it1 = m.crend();
    EXPECT_EQ(*--it1, *(m.crbegin() + 2));
}
