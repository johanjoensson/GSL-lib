#include "GSLpp/matrix.h"
#include "GSLpp/vector.h"
#include <gtest/gtest.h>

TEST(Matrix_fTest, TestConstruction)
{
    size_t rows = 2, columns = 2;
    GSL::Matrix_f m(rows, columns);

    for(size_t i = 0; i < rows; i++){
        for(size_t j = 0; j < columns; j++){
            EXPECT_FLOAT_EQ(m[i][j], 0);
        }
    }
}

TEST(Matrix_fTest, TestConstructionInitializerList)
{
    GSL::Matrix_f m{{1, 2}, {3, 4}};
    size_t rows = 2, columns = 2;
    for(size_t i = 0; i < rows; i++){
        for(size_t j = 0; j < columns; j++){
            EXPECT_FLOAT_EQ(m[i][j], columns*i+j+1);
        }
    }
}

TEST(Matrix_fTest, TestConstructionCopy)
{
    size_t rows = 2, columns = 2;
    GSL::Matrix_f m1{{1, 2}, {3, 4}}, m2(m1);
    for(size_t i = 0; i < rows; i++){
        for(size_t j = 0; j < columns; j++){
            EXPECT_FLOAT_EQ(m1[i][j], m2[i][j]);
        }
    }
}

TEST(Matrix_fTest, TestConstructionMove)
{
    size_t rows = 2, columns = 2;
    GSL::Matrix_f m1{{1, 2}, {3, 4}}, m2(std::move(m1));
    for(size_t i = 0; i < rows; i++){
        for(size_t j = 0; j < columns; j++){
            EXPECT_FLOAT_EQ(m2[i][j], columns*i+j+1);
        }
    }
}

TEST(Matrix_fTest, TestEqual)
{
    GSL::Matrix_f m1{{1, 2}, {3, 4}}, m2(m1);
    EXPECT_TRUE(m1 == m2);
}

TEST(Matrix_fTest, TestNequal)
{
    GSL::Matrix_f m1{{1, 2}, {3, 4}}, m2(m1);
    EXPECT_FALSE(m1 != m2);
}

TEST(Matrix_fTest, TestCopy)
{
    GSL::Matrix_f m1{{1, 2}, {3, 4}}, m2;
    m2 = m1;
    EXPECT_EQ(m1, m2);
}

TEST(Matrix_fTest, TestMove)
{
    GSL::Matrix_f m1{{1, 2}, {3, 4}}, m1s(m1), m2;
    m2 = std::move(m1);
    EXPECT_EQ(m1s, m2);
}

TEST(Matrix_fTest, TestCopy2)
{
    GSL::Matrix_f m1{{1, 2}, {3, 4}}, m2;
    m2.copy(m1);
    EXPECT_EQ(m1, m2);
}

TEST(Matrix_fTest, TestDecayToGSLMatrix_f)
{
    GSL::Matrix_f m{{1, 2}, {3, 4}};
    gsl_matrix_float gm = m;
    EXPECT_FLOAT_EQ(gsl_matrix_float_get(&gm, 0, 1), 2);
}

TEST(Matrix_fTest, TestDim)
{
    GSL::Matrix_f m{{1, 2}, {3, 4}, {5, 6}};
    std::pair<size_t, size_t> d(3,2);
    EXPECT_EQ(m.dim(), d);
}

TEST(Matrix_fTest, TestSize)
{
    GSL::Matrix_f m{{1, 2}, {3, 4}, {5, 6}};
    std::pair<size_t, size_t> d(3,2);
    EXPECT_EQ(m.size(), d);
}

TEST(Matrix_fTest, TestAddAssign)
{
    GSL::Matrix_f m{{1, 2}, {3, 4}, {5, 6}}, n{{1, 2}, {3, 4}, {5, 6}};
    m += n;
    GSL::Matrix_f res{{2, 4}, {6, 8}, {10, 12}};
    EXPECT_EQ(m, res);
}

TEST(Matrix_fTest, TestSubAssign)
{
    GSL::Matrix_f m{{1, 2}, {3, 4}, {5, 6}}, n{{1, 2}, {3, 4}, {5, 6}};
    m -= n;
    GSL::Matrix_f res{{0, 0}, {0, 0}, {0, 0}};
    EXPECT_EQ(m, res);
}

TEST(Matrix_fTest, TestMultAssign)
{
    GSL::Matrix_f m{{1, 2}, {3, 4}, {5, 6}}, n{{1, 2, 3}, {4, 5, 6}};
    m *= n;
    GSL::Matrix_f res{{9, 12, 15}, {19, 26, 33}, {29, 40, 51}};
    EXPECT_EQ(m, res);
}

TEST(Matrix_fTest, TestDivAssign)
{
    GSL::Matrix_f m{{1, 2}, {3, 4}, {5, 6}}, n{{1, 2}, {3, 4}, {5, 6}};
    m /= n;
    GSL::Matrix_f res{{1, 1}, {1, 1}, {1, 1}};
    EXPECT_EQ(m, res);
}

TEST(Matrix_fTest, TestMultScaleAssign)
{
    GSL::Matrix_f m{{1, 2}, {3, 4}, {5, 6}};
    m *= 2;
    GSL::Matrix_f res{{2, 4}, {6, 8}, {10, 12}};
    EXPECT_EQ(m, res);
}

TEST(Matrix_fTest, TestDivScaleAssign)
{
    GSL::Matrix_f m{{1, 2}, {3, 4}, {5, 6}};
    m /= 2;
    GSL::Matrix_f res{{0.5, 1}, {1.5, 2}, {2.5, 3}};
    EXPECT_EQ(m, res);
}

TEST(Matrix_fTest, TestAdd)
{
    GSL::Matrix_f m{{1, 2}, {3, 4}, {5, 6}}, n{{1, 2}, {3, 4}, {5, 6}};
    GSL::Matrix_f res{{2, 4}, {6, 8}, {10, 12}};
    EXPECT_EQ(m+n, res);
}

TEST(Matrix_fTest, TestSub)
{
    GSL::Matrix_f m{{1, 2}, {3, 4}, {5, 6}}, n{{1, 2}, {3, 4}, {5, 6}};
    GSL::Matrix_f res{{0, 0}, {0, 0}, {0, 0}};
    EXPECT_EQ(m-n, res);
}

TEST(Matrix_fTest, TestMult)
{
    GSL::Matrix_f m{{1, 2}, {3, 4}, {5, 6}}, n{{1, 2, 3}, {4, 5, 6}};
    GSL::Matrix_f res{{9, 12, 15}, {19, 26, 33}, {29, 40, 51}};
    EXPECT_EQ(m*n, res);
}

TEST(Matrix_fTest, TestDiv)
{
    GSL::Matrix_f m{{1, 2}, {3, 4}, {5, 6}}, n{{1, 2}, {3, 4}, {5, 6}};
    GSL::Matrix_f res{{1, 1}, {1, 1}, {1, 1}};
    EXPECT_EQ(m/n, res);
}

TEST(Matrix_fTest, TestMultScale)
{
    GSL::Matrix_f m{{1, 2}, {3, 4}, {5, 6}};
    GSL::Matrix_f res{{2, 4}, {6, 8}, {10, 12}};
    EXPECT_EQ(m*2, res);
}

TEST(Matrix_fTest, TestMultScale2)
{
    GSL::Matrix_f m{{1, 2}, {3, 4}, {5, 6}};
    GSL::Matrix_f res{{2, 4}, {6, 8}, {10, 12}};
    EXPECT_EQ(2*m, res);
}

TEST(Matrix_fTest, TestDivScale)
{
    GSL::Matrix_f m{{1, 2}, {3, 4}, {5, 6}};
    GSL::Matrix_f res{{0.5, 1}, {1.5, 2}, {2.5, 3}};
    EXPECT_EQ(m/2, res);
}

TEST(Matrix_fTest, TestTranspose)
{
    GSL::Matrix_f m{{1, 2}, {3, 4}, {5, 6}};
    GSL::Matrix_f res{{1, 3, 5},{2, 4, 6}};
    EXPECT_EQ(m.transpose(), res);
}

TEST(Matrix_fTest, TestHermitian)
{
    GSL::Matrix_f m{{1, 2}, {3, 4}, {5, 6}};
    GSL::Matrix_f res{{1, 3, 5},{2, 4, 6}};
    EXPECT_EQ(m.hermitian_transpose(), res);
}

TEST(Matrix_fTest, TestGetRow)
{
    GSL::Matrix_f m{{1, 2}, {3, 4}, {5, 6}};
    GSL::Vector_f res{5, 6};
    EXPECT_EQ(m.get_row(2), res);
}

TEST(Matrix_fTest, TestSetRow)
{
    GSL::Matrix_f m{{1, 2}, {3, 4}, {5, 6}};
    GSL::Matrix_f res{{1, 2}, {7, 8}, {5, 6}};
    m.get_row(1) = GSL::Vector_f{7, 8};
    EXPECT_EQ(m, res);
}

TEST(Matrix_fTest, TestGetCol)
{
    GSL::Matrix_f m{{1, 2}, {3, 4}, {5, 6}};
    GSL::Vector_f res{2, 4, 6};
    EXPECT_EQ(m.get_col(1), res);
}

TEST(Matrix_fTest, TestSetCol)
{
    GSL::Matrix_f m{{1, 2}, {3, 4}, {5, 6}};
    GSL::Matrix_f res{{7, 2}, {8, 4}, {9, 6}};
    m.get_col(0) = GSL::Vector_f{7, 8, 9};
    EXPECT_EQ(m, res);
}

TEST(Matrix_fTest, TestBegin)
{
    GSL::Matrix_f m{{1, 2}, {3, 4}, {5, 6}};
    GSL::Vector_f res{1, 2};

    EXPECT_EQ(*m.begin(), res);
}

TEST(Matrix_fTest, TestcBegin)
{
    GSL::Matrix_f m{{1, 2}, {3, 4}, {5, 6}};
    GSL::Vector_f res{1, 2};

    EXPECT_EQ(*m.cbegin(), res);
}

TEST(Matrix_fTest, TestFront)
{
    GSL::Matrix_f m{{1, 2}, {3, 4}, {5, 6}};
    GSL::Vector_f res{1, 2};

    EXPECT_EQ(m.front(), res);
}

TEST(Matrix_fTest, TestBack)
{
    GSL::Matrix_f m{{1, 2}, {3, 4}, {5, 6}};
    GSL::Vector_f res{5, 6};

    EXPECT_EQ(m.back(), res);
}

TEST(Matrix_fTest, TestAt)
{
    GSL::Matrix_f m{{1, 2}, {3, 4}, {5, 6}};
    GSL::Vector_f res{3, 4};

    EXPECT_EQ(m.at(1), res);
}

TEST(Matrix_fTest, TestAt2)
{
    GSL::Matrix_f m{{1, 2}, {3, 4}, {5, 6}};
    GSL::Matrix_f::value_type res{5};

    EXPECT_EQ(m.at(2, 0), res);
}

TEST(Matrix_fTest, TestIterPreIncrement)
{
    GSL::Matrix_f m{{1, 2}, {3, 4}, {5, 6}};
    EXPECT_EQ(*++m.begin(), m.at(1));
}

TEST(Matrix_fTest, TestIterPostIncrement)
{
    GSL::Matrix_f m{{1, 2}, {3, 4}, {5, 6}};
    auto it = m.begin();
    it++;
    EXPECT_EQ(*it, m.at(1));
}

TEST(Matrix_fTest, TestIterPreDecrement)
{
    GSL::Matrix_f m{{1, 2}, {3, 4}, {5, 6}};
    EXPECT_EQ(*--(++m.begin()), m.at(0));
}

TEST(Matrix_fTest, TestIterPostDecrement)
{
    GSL::Matrix_f m{{1, 2}, {3, 4}, {5, 6}};
    auto it = m.begin();
    (it++)--;
    EXPECT_EQ(*it, m.at(0));
}

TEST(Matrix_fTest, TestIterAddAssign)
{
    GSL::Matrix_f m{{1, 2}, {3, 4}, {5, 6}};
    auto it = m.begin();
    it += 2;
    EXPECT_EQ(*it, m.at(2));
}

TEST(Matrix_fTest, TestIterSubAssign)
{
    GSL::Matrix_f m{{1, 2}, {3, 4}, {5, 6}};
    auto it = m.begin();
    it += 2;
    it -= 1;
    EXPECT_EQ(*it, m.at(1));
}

TEST(Matrix_fTest, TestIterAdd)
{
    GSL::Matrix_f m{{1, 2}, {3, 4}, {5, 6}};
    auto it = m.begin();
    EXPECT_EQ(*(it + 2), m.at(2));
}

TEST(Matrix_fTest, TestIterAdd2)
{
    GSL::Matrix_f m{{1, 2}, {3, 4}, {5, 6}};
    auto it = m.begin();
    EXPECT_EQ(*(2 + it), m.at(2));
}

TEST(Matrix_fTest, TestIterSub)
{
    GSL::Matrix_f m{{1, 2}, {3, 4}, {5, 6}};
    auto it = m.begin();
    it += 2;
    EXPECT_EQ(*(it - 1), m.at(1));
}

TEST(Matrix_fTest, TestIterSub2)
{
    GSL::Matrix_f m{{1, 2}, {3, 4}, {5, 6}};
    auto it1 = m.begin(), it2 = m.begin();
    it2 += 2;
    EXPECT_EQ(it2 - it1, 2);
}

TEST(Matrix_fTest, TestIterEq)
{
    GSL::Matrix_f m{{1, 2}, {3, 4}, {5, 6}};
    auto it1 = m.begin(), it2 = m.begin();
    it2 += 2;
    EXPECT_EQ(*++(++it1), *it2);
}

TEST(Matrix_fTest, TestIterNeq)
{
    GSL::Matrix_f m{{1, 2}, {3, 4}, {5, 6}};
    auto it = m.begin();
    GSL::Vector_f res{*it};
    EXPECT_NE(res, *(it + 1));
}

TEST(Matrix_fTest, TestEnd)
{
    GSL::Matrix_f m{{1, 2}, {3, 4}, {5, 6}};
    auto it1 = m.end();
    EXPECT_EQ(*--it1, *(m.begin() + 2));
}

TEST(Matrix_fTest, TestcEnd)
{
    GSL::Matrix_f m{{1, 2}, {3, 4}, {5, 6}};
    auto it1 = m.cend();
    EXPECT_EQ(*--it1, *(m.begin() + 2));
}

TEST(Matrix_fTest, TestRbegin)
{
    GSL::Matrix_f m{{1, 2}, {3, 4}, {5, 6}};
    GSL::Vector_f res{5, 6};
    EXPECT_EQ(*m.rbegin(), res);
}

TEST(Matrix_fTest, TestcRbegin)
{
    GSL::Matrix_f m{{1, 2}, {3, 4}, {5, 6}};
    GSL::Vector_f res{5, 6};
    EXPECT_EQ(*m.crbegin(), res);
}

TEST(Matrix_fTest, TestRend)
{
    GSL::Matrix_f m{{1, 2}, {3, 4}, {5, 6}};
    auto it1 = m.rend();
    EXPECT_EQ(*--it1, *(m.rbegin() + 2));
}

TEST(Matrix_fTest, TestcRend)
{
    GSL::Matrix_f m{{1, 2}, {3, 4}, {5, 6}};
    auto it1 = m.crend();
    EXPECT_EQ(*--it1, *(m.crbegin() + 2));
}
