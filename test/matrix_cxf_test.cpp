#include "GSLpp/matrix.h"
#include "GSLpp/vector.h"
#include <gtest/gtest.h>

TEST(Matrix_cxfTest, TestConstruction)
{
    size_t rows = 2, columns = 2;
    GSL::Matrix_cxf m(rows, columns);

    for(size_t i = 0; i < rows; i++){
        for(size_t j = 0; j < columns; j++){
            EXPECT_EQ(m[i][j], GSL::Matrix_cxf::value_type{0});
        }
    }
}

TEST(Matrix_cxfTest, TestConstructionInitializerList)
{
    GSL::Matrix_cxf m{{1, 2}, {3, 4}};
    size_t rows = 2, columns = 2;
    for(size_t i = 0; i < rows; i++){
        for(size_t j = 0; j < columns; j++){
            EXPECT_EQ(m[i][j], GSL::Matrix_cxf::value_type{columns*i+j+1});
        }
    }
}

TEST(Matrix_cxfTest, TestConstructionCopy)
{
    size_t rows = 2, columns = 2;
    GSL::Matrix_cxf m1{{1, 2}, {3, 4}}, m2(m1);
    for(size_t i = 0; i < rows; i++){
        for(size_t j = 0; j < columns; j++){
            EXPECT_EQ(m1[i][j], GSL::Matrix_cxf::value_type{m2[i][j]});
        }
    }
}

TEST(Matrix_cxfTest, TestConstructionMove)
{
    size_t rows = 2, columns = 2;
    GSL::Matrix_cxf m1{{1, 2}, {3, 4}}, m2(std::move(m1));
    for(size_t i = 0; i < rows; i++){
        for(size_t j = 0; j < columns; j++){
            EXPECT_EQ(m2[i][j], GSL::Matrix_cxf::value_type{columns*i+j+1});
        }
    }
}

TEST(Matrix_cxfTest, TestEqual)
{
    GSL::Matrix_cxf m1{{1, 2}, {3, 4}}, m2(m1);
    EXPECT_TRUE(m1 == m2);
}

TEST(Matrix_cxfTest, TestNequal)
{
    GSL::Matrix_cxf m1{{1, 2}, {3, 4}}, m2(m1);
    EXPECT_FALSE(m1 != m2);
}

TEST(Matrix_cxfTest, TestCopy)
{
    GSL::Matrix_cxf m1{{1, 2}, {3, 4}}, m2;
    m2 = m1;
    EXPECT_EQ(m1, m2);
}

TEST(Matrix_cxfTest, TestMove)
{
    GSL::Matrix_cxf m1{{1, 2}, {3, 4}}, m1s(m1), m2;
    m2 = std::move(m1);
    EXPECT_EQ(m1s, m2);
}

TEST(Matrix_cxfTest, TestCopy2)
{
    GSL::Matrix_cxf m1{{1, 2}, {3, 4}}, m2;
    m2.copy(m1);
    EXPECT_EQ(m1, m2);
}

TEST(Matrix_cxfTest, TestDecayToGSLMatrix_cxf)
{
    GSL::Matrix_cxf m{{1, 2}, {3, 4}};
    gsl_matrix_complex_float gm = m;
    EXPECT_EQ(gsl_matrix_complex_float_get(&gm, 0, 1), GSL::Matrix_cxf::value_type{2});
}

TEST(Matrix_cxfTest, TestDim)
{
    GSL::Matrix_cxf m{{1, 2}, {3, 4}, {5, 6}};
    std::pair<size_t, size_t> d(3,2);
    EXPECT_EQ(m.dim(), d);
}

TEST(Matrix_cxfTest, TestSize)
{
    GSL::Matrix_cxf m{{1, 2}, {3, 4}, {5, 6}};
    std::pair<size_t, size_t> d(3,2);
    EXPECT_EQ(m.size(), d);
}

TEST(Matrix_cxfTest, TestAddAssign)
{
    GSL::Matrix_cxf m{{1, 2}, {3, 4}, {5, 6}}, n{{1, 2}, {3, 4}, {5, 6}};
    m += n;
    GSL::Matrix_cxf res{{2, 4}, {6, 8}, {10, 12}};
    EXPECT_EQ(m, res);
}

TEST(Matrix_cxfTest, TestSubAssign)
{
    GSL::Matrix_cxf m{{1, 2}, {3, 4}, {5, 6}}, n{{1, 2}, {3, 4}, {5, 6}};
    m -= n;
    GSL::Matrix_cxf res{{0, 0}, {0, 0}, {0, 0}};
    EXPECT_EQ(m, res);
}

TEST(Matrix_cxfTest, TestMultAssign)
{
    GSL::Matrix_cxf m{{1, 2}, {3, 4}, {5, 6}}, n{{1, 2, 3}, {4, 5, 6}};
    m *= n;
    GSL::Matrix_cxf res{{9, 12, 15}, {19, 26, 33}, {29, 40, 51}};
    EXPECT_EQ(m, res);
}

TEST(Matrix_cxfTest, TestDivAssign)
{
    GSL::Matrix_cxf m{{1, 2}, {3, 4}, {5, 6}}, n{{1, 2}, {3, 4}, {5, 6}};
    m /= n;
    GSL::Matrix_cxf res{{1, 1}, {1, 1}, {1, 1}};
    EXPECT_EQ(m, res);
}

TEST(Matrix_cxfTest, TestMultScaleAssign)
{
    GSL::Matrix_cxf m{{1, 2}, {3, 4}, {5, 6}};
    m *= 2;
    GSL::Matrix_cxf res{{2, 4}, {6, 8}, {10, 12}};
    EXPECT_EQ(m, res);
}

TEST(Matrix_cxfTest, TestDivScaleAssign)
{
    GSL::Matrix_cxf m{{1, 2}, {3, 4}, {5, 6}};
    m /= 2;
    GSL::Matrix_cxf res{{0.5, 1}, {1.5, 2}, {2.5, 3}};
    EXPECT_EQ(m, res);
}

TEST(Matrix_cxfTest, TestAdd)
{
    GSL::Matrix_cxf m{{1, 2}, {3, 4}, {5, 6}}, n{{1, 2}, {3, 4}, {5, 6}};
    GSL::Matrix_cxf res{{2, 4}, {6, 8}, {10, 12}};
    EXPECT_EQ(m+n, res);
}

TEST(Matrix_cxfTest, TestSub)
{
    GSL::Matrix_cxf m{{1, 2}, {3, 4}, {5, 6}}, n{{1, 2}, {3, 4}, {5, 6}};
    GSL::Matrix_cxf res{{0, 0}, {0, 0}, {0, 0}};
    EXPECT_EQ(m-n, res);
}

TEST(Matrix_cxfTest, TestMult)
{
    GSL::Matrix_cxf m{{1, 2}, {3, 4}, {5, 6}}, n{{1, 2, 3}, {4, 5, 6}};
    GSL::Matrix_cxf res{{9, 12, 15}, {19, 26, 33}, {29, 40, 51}};
    EXPECT_EQ(m*n, res);
}

TEST(Matrix_cxfTest, TestDiv)
{
    GSL::Matrix_cxf m{{1, 2}, {3, 4}, {5, 6}}, n{{1, 2}, {3, 4}, {5, 6}};
    GSL::Matrix_cxf res{{1, 1}, {1, 1}, {1, 1}};
    EXPECT_EQ(m/n, res);
}

TEST(Matrix_cxfTest, TestMultScale)
{
    GSL::Matrix_cxf m{{1, 2}, {3, 4}, {5, 6}};
    GSL::Matrix_cxf res{{2, 4}, {6, 8}, {10, 12}};
    EXPECT_EQ(m*GSL::Matrix_cxf::value_type{2}, res);
}

TEST(Matrix_cxfTest, TestMultScale2)
{
    GSL::Matrix_cxf m{{1, 2}, {3, 4}, {5, 6}};
    GSL::Matrix_cxf res{{2, 4}, {6, 8}, {10, 12}};
    EXPECT_EQ(GSL::Matrix_cxf::value_type{2}*m, res);
}

TEST(Matrix_cxfTest, TestDivScale)
{
    GSL::Matrix_cxf m{{1, 2}, {3, 4}, {5, 6}};
    GSL::Matrix_cxf res{{0.5, 1}, {1.5, 2}, {2.5, 3}};
    EXPECT_EQ(m/GSL::Matrix_cxf::value_type{2}, res);
}

TEST(Matrix_cxfTest, TestTranspose)
{
    GSL::Matrix_cxf m{{1, 2}, {3, 4}, {5, 6}};
    GSL::Matrix_cxf res{{1, 3, 5},{2, 4, 6}};
    EXPECT_EQ(m.transpose(), res);
}

TEST(Matrix_cxfTest, TestHermitian)
{
    GSL::Matrix_cxf m{{{1, 6}, {2, 5}}, {{3, 4}, {4, 3}}, {{5, 2}, {6, 1}}};
    GSL::Matrix_cxf res{{{1, -6}, {3, -4}, {5, -2}},{{2, -5}, {4, -3}, {6, -1}}};
    EXPECT_EQ(m.hermitian_transpose(), res);
}

TEST(Matrix_cxfTest, TestGetRow)
{
    GSL::Matrix_cxf m{{1, 2}, {3, 4}, {5, 6}};
    GSL::Vector_cxf res{5, 6};
    EXPECT_EQ(m.get_row(2), res);
}

TEST(Matrix_cxfTest, TestSetRow)
{
    GSL::Matrix_cxf m{{1, 2}, {3, 4}, {5, 6}};
    GSL::Matrix_cxf res{{1, 2}, {7, 8}, {5, 6}};
    m.get_row(1) = GSL::Vector_cxf{7, 8};
    EXPECT_EQ(m, res);
}

TEST(Matrix_cxfTest, TestGetCol)
{
    GSL::Matrix_cxf m{{1, 2}, {3, 4}, {5, 6}};
    GSL::Vector_cxf res{2, 4, 6};
    EXPECT_EQ(m.get_col(1), res);
}

TEST(Matrix_cxfTest, TestSetCol)
{
    GSL::Matrix_cxf m{{1, 2}, {3, 4}, {5, 6}};
    GSL::Matrix_cxf res{{7, 2}, {8, 4}, {9, 6}};
    m.get_col(0) = GSL::Vector_cxf{7, 8, 9};
    EXPECT_EQ(m, res);
}

TEST(Matrix_cxfTest, TestBegin)
{
    GSL::Matrix_cxf m{{1, 2}, {3, 4}, {5, 6}};
    GSL::Vector_cxf res{1, 2};

    EXPECT_EQ(*m.begin(), res);
}

TEST(Matrix_cxfTest, TestcBegin)
{
    GSL::Matrix_cxf m{{1, 2}, {3, 4}, {5, 6}};
    GSL::Vector_cxf res{1, 2};

    EXPECT_EQ(*m.cbegin(), res);
}

TEST(Matrix_cxfTest, TestFront)
{
    GSL::Matrix_cxf m{{1, 2}, {3, 4}, {5, 6}};
    GSL::Vector_cxf res{1, 2};

    EXPECT_EQ(m.front(), res);
}

TEST(Matrix_cxfTest, TestBack)
{
    GSL::Matrix_cxf m{{1, 2}, {3, 4}, {5, 6}};
    GSL::Vector_cxf res{5, 6};

    EXPECT_EQ(m.back(), res);
}

TEST(Matrix_cxfTest, TestAt)
{
    GSL::Matrix_cxf m{{1, 2}, {3, 4}, {5, 6}};
    GSL::Vector_cxf res{3, 4};

    EXPECT_EQ(m.at(1), res);
}

TEST(Matrix_cxfTest, TestAt2)
{
    GSL::Matrix_cxf m{{1, 2}, {3, 4}, {5, 6}};
    GSL::Matrix_cxf::value_type res{5};

    EXPECT_EQ(m.at(2, 0), res);
}

TEST(Matrix_cxfTest, TestIterPreIncrement)
{
    GSL::Matrix_cxf m{{1, 2}, {3, 4}, {5, 6}};
    EXPECT_EQ(*++m.begin(), m.at(1));
}

TEST(Matrix_cxfTest, TestIterPostIncrement)
{
    GSL::Matrix_cxf m{{1, 2}, {3, 4}, {5, 6}};
    auto it = m.begin();
    it++;
    EXPECT_EQ(*it, m.at(1));
}

TEST(Matrix_cxfTest, TestIterPreDecrement)
{
    GSL::Matrix_cxf m{{1, 2}, {3, 4}, {5, 6}};
    EXPECT_EQ(*--(++m.begin()), m.at(0));
}

TEST(Matrix_cxfTest, TestIterPostDecrement)
{
    GSL::Matrix_cxf m{{1, 2}, {3, 4}, {5, 6}};
    auto it = m.begin();
    (it++)--;
    EXPECT_EQ(*it, m.at(0));
}

TEST(Matrix_cxfTest, TestIterAddAssign)
{
    GSL::Matrix_cxf m{{1, 2}, {3, 4}, {5, 6}};
    auto it = m.begin();
    it += 2;
    EXPECT_EQ(*it, m.at(2));
}

TEST(Matrix_cxfTest, TestIterSubAssign)
{
    GSL::Matrix_cxf m{{1, 2}, {3, 4}, {5, 6}};
    auto it = m.begin();
    it += 2;
    it -= 1;
    EXPECT_EQ(*it, m.at(1));
}

TEST(Matrix_cxfTest, TestIterAdd)
{
    GSL::Matrix_cxf m{{1, 2}, {3, 4}, {5, 6}};
    auto it = m.begin();
    EXPECT_EQ(*(it + 2), m.at(2));
}

TEST(Matrix_cxfTest, TestIterAdd2)
{
    GSL::Matrix_cxf m{{1, 2}, {3, 4}, {5, 6}};
    auto it = m.begin();
    EXPECT_EQ(*(2 + it), m.at(2));
}

TEST(Matrix_cxfTest, TestIterSub)
{
    GSL::Matrix_cxf m{{1, 2}, {3, 4}, {5, 6}};
    auto it = m.begin();
    it += 2;
    EXPECT_EQ(*(it - 1), m.at(1));
}

TEST(Matrix_cxfTest, TestIterSub2)
{
    GSL::Matrix_cxf m{{1, 2}, {3, 4}, {5, 6}};
    auto it1 = m.begin(), it2 = m.begin();
    it2 += 2;
    EXPECT_EQ(it2 - it1, 2);
}

TEST(Matrix_cxfTest, TestIterEq)
{
    GSL::Matrix_cxf m{{1, 2}, {3, 4}, {5, 6}};
    auto it1 = m.begin(), it2 = m.begin();
    it2 += 2;
    EXPECT_EQ(*++(++it1), *it2);
}

TEST(Matrix_cxfTest, TestIterNeq)
{
    GSL::Matrix_cxf m{{1, 2}, {3, 4}, {5, 6}};
    auto it = m.begin();
    GSL::Vector_cxf res{*it};
    EXPECT_NE(res, *(it + 1));
}

TEST(Matrix_cxfTest, TestEnd)
{
    GSL::Matrix_cxf m{{1, 2}, {3, 4}, {5, 6}};
    auto it1 = m.end();
    EXPECT_EQ(*--it1, *(m.begin() + 2));
}

TEST(Matrix_cxfTest, TestcEnd)
{
    GSL::Matrix_cxf m{{1, 2}, {3, 4}, {5, 6}};
    auto it1 = m.cend();
    EXPECT_EQ(*--it1, *(m.begin() + 2));
}

TEST(Matrix_cxfTest, TestRbegin)
{
    GSL::Matrix_cxf m{{1, 2}, {3, 4}, {5, 6}};
    GSL::Vector_cxf res{5, 6};
    EXPECT_EQ(*m.rbegin(), res);
}

TEST(Matrix_cxfTest, TestcRbegin)
{
    GSL::Matrix_cxf m{{1, 2}, {3, 4}, {5, 6}};
    GSL::Vector_cxf res{5, 6};
    EXPECT_EQ(*m.crbegin(), res);
}

TEST(Matrix_cxfTest, TestRend)
{
    GSL::Matrix_cxf m{{1, 2}, {3, 4}, {5, 6}};
    auto it1 = m.rend();
    EXPECT_EQ(*--it1, *(m.rbegin() + 2));
}

TEST(Matrix_cxfTest, TestcRend)
{
    GSL::Matrix_cxf m{{1, 2}, {3, 4}, {5, 6}};
    auto it1 = m.crend();
    EXPECT_EQ(*--it1, *(m.crbegin() + 2));
}
