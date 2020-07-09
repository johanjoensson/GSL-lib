#include "GSLpp/matrix.h"
#include "GSLpp/vector.h"
#include "GSLpp/complex.h"
#include <gtest/gtest.h>

TEST(Matrix_cxldTest, TestConstruction)
{
    size_t rows = 2, columns = 2;
    GSL::Matrix_cxld m(rows, columns);

    for(size_t i = 0; i < rows; i++){
        for(size_t j = 0; j < columns; j++){
            EXPECT_EQ(m[i][j], GSL::Matrix_cxld::value_type{0});
        }
    }
}

TEST(Matrix_cxldTest, TestConstructionInitializerList)
{
    GSL::Matrix_cxld m{{1, 2}, {3, 4}};
    size_t rows = 2, columns = 2;
    for(size_t i = 0; i < rows; i++){
        for(size_t j = 0; j < columns; j++){
            EXPECT_EQ(m[i][j], GSL::Complex_ld(static_cast<long double>(columns*i+j+1)));
        }
    }
}

TEST(Matrix_cxldTest, TestConstructionCopy)
{
    size_t rows = 2, columns = 2;
    GSL::Matrix_cxld m1{{1, 2}, {3, 4}}, m2(m1);
    for(size_t i = 0; i < rows; i++){
        for(size_t j = 0; j < columns; j++){
            EXPECT_EQ(m1[i][j], GSL::Matrix_cxld::value_type{m2[i][j]});
        }
    }
}

TEST(Matrix_cxldTest, TestConstructionMove)
{
    size_t rows = 2, columns = 2;
    GSL::Matrix_cxld m1{{1, 2}, {3, 4}}, m2(std::move(m1));
    for(size_t i = 0; i < rows; i++){
        for(size_t j = 0; j < columns; j++){
            EXPECT_EQ(m2[i][j], GSL::Complex_ld(static_cast<long double>(columns*i+j+1)));
        }
    }
}

TEST(Matrix_cxldTest, TestEqual)
{
    GSL::Matrix_cxld m1{{1, 2}, {3, 4}}, m2(m1);
    EXPECT_TRUE(m1 == m2);
}

TEST(Matrix_cxldTest, TestNequal)
{
    GSL::Matrix_cxld m1{{1, 2}, {3, 4}}, m2(m1);
    EXPECT_FALSE(m1 != m2);
}

TEST(Matrix_cxldTest, TestCopy)
{
    GSL::Matrix_cxld m1{{1, 2}, {3, 4}}, m2;
    m2 = m1;
    EXPECT_EQ(m1, m2);
}

TEST(Matrix_cxldTest, TestMove)
{
    GSL::Matrix_cxld m1{{1, 2}, {3, 4}}, m1s(m1), m2;
    m2 = std::move(m1);
    EXPECT_EQ(m1s, m2);
}

TEST(Matrix_cxldTest, TestCopy2)
{
    GSL::Matrix_cxld m1{{1, 2}, {3, 4}}, m2;
    m2.copy(m1);
    EXPECT_EQ(m1, m2);
}

TEST(Matrix_cxldTest, TestDecayToGSLMatrix_cxld)
{
    GSL::Matrix_cxld m{{1, 2}, {3, 4}};
    gsl_matrix_complex_long_double gm = m;
    EXPECT_EQ(gsl_matrix_complex_long_double_get(&gm, 0, 1), GSL::Matrix_cxld::value_type{2});
}

TEST(Matrix_cxldTest, TestDim)
{
    GSL::Matrix_cxld m{{1, 2}, {3, 4}, {5, 6}};
    std::pair<size_t, size_t> d(3,2);
    EXPECT_EQ(m.dim(), d);
}

TEST(Matrix_cxldTest, TestSize)
{
    GSL::Matrix_cxld m{{1, 2}, {3, 4}, {5, 6}};
    std::pair<size_t, size_t> d(3,2);
    EXPECT_EQ(m.size(), d);
}

TEST(Matrix_cxldTest, TestAddAssign)
{
    GSL::Matrix_cxld m{{1, 2}, {3, 4}, {5, 6}}, n{{1, 2}, {3, 4}, {5, 6}};
    m += n;
    GSL::Matrix_cxld res{{2, 4}, {6, 8}, {10, 12}};
    EXPECT_EQ(m, res);
}

TEST(Matrix_cxldTest, TestSubAssign)
{
    GSL::Matrix_cxld m{{1, 2}, {3, 4}, {5, 6}}, n{{1, 2}, {3, 4}, {5, 6}};
    m -= n;
    GSL::Matrix_cxld res{{0, 0}, {0, 0}, {0, 0}};
    EXPECT_EQ(m, res);
}

TEST(Matrix_cxldTest, TestMultAssign)
{
    GSL::Matrix_cxld m{{1, 2}, {3, 4}, {5, 6}}, n{{1, 2, 3}, {4, 5, 6}};
    std::cout << m << "\n";
    std::cout << n << "\n";
    m *= n;
    GSL::Matrix_cxld res{{9, 12, 15}, {19, 26, 33}, {29, 40, 51}};

    size_t rows = 3, columns = 3;
    for(size_t i = 0; i < rows; i++){
        for(size_t j = 0; j < columns; j++){
            EXPECT_EQ(m[i][j], GSL::Matrix_cxld::value_type{res[i][j]});
        }
    }
}

TEST(Matrix_cxldTest, TestDivAssign)
{
    GSL::Matrix_cxld m{{1, 2}, {3, 4}, {5, 6}}, n{{1, 2}, {3, 4}, {5, 6}};
    m /= n;
    GSL::Matrix_cxld res{{1, 1}, {1, 1}, {1, 1}};
    long double diff;
    size_t rows = 3, columns = 2;
    for(size_t i = 0; i < rows; i++){
        for(size_t j = 0; j < columns; j++){
	    diff = std::abs(GSL::Matrix_cxld::value_type{m[i][j]}.abs() - GSL::Matrix_cxld::value_type{res[i][j]}.abs());
            EXPECT_TRUE(diff < 1e-10l);
        }
    }
}

TEST(Matrix_cxldTest, TestMultScaleAssign)
{
    GSL::Matrix_cxld m{{1, 2}, {3, 4}, {5, 6}};
    m *= 2;
    GSL::Matrix_cxld res{{2, 4}, {6, 8}, {10, 12}};
    EXPECT_EQ(m, res);
}

TEST(Matrix_cxldTest, TestDivScaleAssign)
{
    GSL::Matrix_cxld m{{1, 2}, {3, 4}, {5, 6}};
    m /= 2;
    GSL::Matrix_cxld res{{0.5l, 1}, {1.5l, 2}, {2.5l, 3}};
    EXPECT_EQ(m, res);
}

TEST(Matrix_cxldTest, TestAdd)
{
    GSL::Matrix_cxld m{{1, 2}, {3, 4}, {5, 6}}, n{{1, 2}, {3, 4}, {5, 6}};
    GSL::Matrix_cxld res{{2, 4}, {6, 8}, {10, 12}};
    EXPECT_EQ(m+n, res);
}

TEST(Matrix_cxldTest, TestSub)
{
    GSL::Matrix_cxld m{{1, 2}, {3, 4}, {5, 6}}, n{{1, 2}, {3, 4}, {5, 6}};
    GSL::Matrix_cxld res{{0, 0}, {0, 0}, {0, 0}};
    EXPECT_EQ(m-n, res);
}

TEST(Matrix_cxldTest, TestMult)
{
    GSL::Matrix_cxld m{{1, 2}, {3, 4}, {5, 6}}, n{{1, 2, 3}, {4, 5, 6}};
    GSL::Matrix_cxld res{{9, 12, 15}, {19, 26, 33}, {29, 40, 51}};
    size_t rows = 3, columns = 3;
    for(size_t i = 0; i < rows; i++){
        for(size_t j = 0; j < columns; j++){
            EXPECT_EQ(GSL::Matrix_cxld::value_type{(m*n)[i][j]}, GSL::Matrix_cxld::value_type{res[i][j]});
        }
    }
}

TEST(Matrix_cxldTest, TestDiv)
{
    GSL::Matrix_cxld m{{1, 2}, {3, 4}, {5, 6}}, n{{1, 2}, {3, 4}, {5, 6}};
    GSL::Matrix_cxld res{{1, 1}, {1, 1}, {1, 1}};
    long double diff;
    size_t rows = 3, columns = 2;
    for(size_t i = 0; i < rows; i++){
        for(size_t j = 0; j < columns; j++){
	    diff = std::abs(GSL::Matrix_cxld::value_type{(m/n)[i][j]}.abs() - GSL::Matrix_cxld::value_type{res[i][j]}.abs());
            EXPECT_TRUE(diff < 1e-10l);
        }
    }
}

TEST(Matrix_cxldTest, TestMultScale)
{
    GSL::Matrix_cxld m{{1, 2}, {3, 4}, {5, 6}};
    GSL::Matrix_cxld res{{2, 4}, {6, 8}, {10, 12}};
    EXPECT_EQ(m*GSL::Matrix_cxld::value_type{2}, res);
}

TEST(Matrix_cxldTest, TestMultScale2)
{
    GSL::Matrix_cxld m{{1, 2}, {3, 4}, {5, 6}};
    GSL::Matrix_cxld res{{2, 4}, {6, 8}, {10, 12}};
    EXPECT_EQ(GSL::Matrix_cxld::value_type{2}*m, res);
}

TEST(Matrix_cxldTest, TestDivScale)
{
    GSL::Matrix_cxld m{{1, 2}, {3, 4}, {5, 6}};
    GSL::Matrix_cxld res{{0.5l, 1}, {1.5l, 2}, {2.5l, 3}};
    EXPECT_EQ(m/GSL::Matrix_cxld::value_type{2}, res);
}

TEST(Matrix_cxldTest, TestTranspose)
{
    GSL::Matrix_cxld m{{1, 2}, {3, 4}, {5, 6}};
    GSL::Matrix_cxld res{{1, 3, 5},{2, 4, 6}};
    EXPECT_EQ(m.transpose(), res);
}

TEST(Matrix_cxldTest, TestHermitian)
{
    GSL::Matrix_cxld m{{{1, 6}, {2, 5}}, {{3, 4}, {4, 3}}, {{5, 2}, {6, 1}}};
    GSL::Matrix_cxld res{{{1, -6}, {3, -4}, {5, -2}},{{2, -5}, {4, -3}, {6, -1}}};
    EXPECT_EQ(m.hermitian_transpose(), res);
}

TEST(Matrix_cxldTest, TestGetRow)
{
    GSL::Matrix_cxld m{{1, 2}, {3, 4}, {5, 6}};
    GSL::Vector_cxld res{5, 6};
    EXPECT_EQ(m.get_row(2), res);
}

TEST(Matrix_cxldTest, TestSetRow)
{
    GSL::Matrix_cxld m{{1, 2}, {3, 4}, {5, 6}};
    GSL::Matrix_cxld res{{1, 2}, {7, 8}, {5, 6}};
    m.get_row(1) = GSL::Vector_cxld{7, 8};
    EXPECT_EQ(m, res);
}

TEST(Matrix_cxldTest, TestGetCol)
{
    GSL::Matrix_cxld m{{1, 2}, {3, 4}, {5, 6}};
    GSL::Vector_cxld res{2, 4, 6};
    EXPECT_EQ(m.get_col(1), res);
}

TEST(Matrix_cxldTest, TestSetCol)
{
    GSL::Matrix_cxld m{{1, 2}, {3, 4}, {5, 6}};
    GSL::Matrix_cxld res{{7, 2}, {8, 4}, {9, 6}};
    m.get_col(0) = GSL::Vector_cxld{7, 8, 9};
    EXPECT_EQ(m, res);
}

TEST(Matrix_cxldTest, TestBegin)
{
    GSL::Matrix_cxld m{{1, 2}, {3, 4}, {5, 6}};
    GSL::Vector_cxld res{1, 2};

    EXPECT_EQ(*m.begin(), res);
}

TEST(Matrix_cxldTest, TestcBegin)
{
    GSL::Matrix_cxld m{{1, 2}, {3, 4}, {5, 6}};
    GSL::Vector_cxld res{1, 2};

    EXPECT_EQ(*m.cbegin(), res);
}

TEST(Matrix_cxldTest, TestFront)
{
    GSL::Matrix_cxld m{{1, 2}, {3, 4}, {5, 6}};
    GSL::Vector_cxld res{1, 2};

    EXPECT_EQ(m.front(), res);
}

TEST(Matrix_cxldTest, TestBack)
{
    GSL::Matrix_cxld m{{1, 2}, {3, 4}, {5, 6}};
    GSL::Vector_cxld res{5, 6};

    EXPECT_EQ(m.back(), res);
}

TEST(Matrix_cxldTest, TestAt)
{
    GSL::Matrix_cxld m{{1, 2}, {3, 4}, {5, 6}};
    GSL::Vector_cxld res{3, 4};

    EXPECT_EQ(m.at(1), res);
}

TEST(Matrix_cxldTest, TestAt2)
{
    GSL::Matrix_cxld m{{1, 2}, {3, 4}, {5, 6}};
    GSL::Matrix_cxld::value_type res{5};

    EXPECT_EQ(m.at(2, 0), res);
}

TEST(Matrix_cxldTest, TestIterPreIncrement)
{
    GSL::Matrix_cxld m{{1, 2}, {3, 4}, {5, 6}};
    EXPECT_EQ(*++m.begin(), m.at(1));
}

TEST(Matrix_cxldTest, TestIterPostIncrement)
{
    GSL::Matrix_cxld m{{1, 2}, {3, 4}, {5, 6}};
    auto it = m.begin();
    EXPECT_EQ(*it++, m.at(0));
    EXPECT_EQ(*it, m.at(1));
}

TEST(Matrix_cxldTest, TestIterPreDecrement)
{
    GSL::Matrix_cxld m{{1, 2}, {3, 4}, {5, 6}};
    EXPECT_EQ(*--(++m.begin()), m.at(0));
}

TEST(Matrix_cxldTest, TestIterPostDecrement)
{
    GSL::Matrix_cxld m{{1, 2}, {3, 4}, {5, 6}};
    auto it = ++m.begin();
    EXPECT_EQ(*it--, m.at(1));
    EXPECT_EQ(*it, m.at(0));
}

TEST(Matrix_cxldTest, TestIterAddAssign)
{
    GSL::Matrix_cxld m{{1, 2}, {3, 4}, {5, 6}};
    auto it = m.begin();
    it += 2;
    EXPECT_EQ(*it, m.at(2));
}

TEST(Matrix_cxldTest, TestIterSubAssign)
{
    GSL::Matrix_cxld m{{1, 2}, {3, 4}, {5, 6}};
    auto it = m.begin();
    it += 2;
    it -= 1;
    EXPECT_EQ(*it, m.at(1));
}

TEST(Matrix_cxldTest, TestIterAdd)
{
    GSL::Matrix_cxld m{{1, 2}, {3, 4}, {5, 6}};
    auto it = m.begin();
    EXPECT_EQ(*(it + 2), m.at(2));
}

TEST(Matrix_cxldTest, TestIterAdd2)
{
    GSL::Matrix_cxld m{{1, 2}, {3, 4}, {5, 6}};
    auto it = m.begin();
    EXPECT_EQ(*(2 + it), m.at(2));
}

TEST(Matrix_cxldTest, TestIterSub)
{
    GSL::Matrix_cxld m{{1, 2}, {3, 4}, {5, 6}};
    auto it = m.begin();
    it += 2;
    EXPECT_EQ(*(it - 1), m.at(1));
}

TEST(Matrix_cxldTest, TestIterSub2)
{
    GSL::Matrix_cxld m{{1, 2}, {3, 4}, {5, 6}};
    auto it1 = m.begin(), it2 = m.begin();
    it2 += 2;
    EXPECT_EQ(it2 - it1, 2);
}

TEST(Matrix_cxldTest, TestIterEq)
{
    GSL::Matrix_cxld m{{1, 2}, {3, 4}, {5, 6}};
    auto it1 = m.begin(), it2 = m.begin();
    it2 += 2;
    EXPECT_EQ(*++(++it1), *it2);
}

TEST(Matrix_cxldTest, TestIterNeq)
{
    GSL::Matrix_cxld m{{1, 2}, {3, 4}, {5, 6}};
    auto it = m.begin();
    GSL::Vector_cxld res{*it};
    EXPECT_NE(res, *(it + 1));
}

TEST(Matrix_cxldTest, TestEnd)
{
    GSL::Matrix_cxld m{{1, 2}, {3, 4}, {5, 6}};
    auto it1 = m.end();
    EXPECT_EQ(*--it1, *(m.begin() + 2));
}

TEST(Matrix_cxldTest, TestcEnd)
{
    GSL::Matrix_cxld m{{1, 2}, {3, 4}, {5, 6}};
    auto it1 = m.cend();
    EXPECT_EQ(*--it1, *(m.begin() + 2));
}

TEST(Matrix_cxldTest, TestRbegin)
{
    GSL::Matrix_cxld m{{1, 2}, {3, 4}, {5, 6}};
    GSL::Vector_cxld res{5, 6};
    EXPECT_EQ(*m.rbegin(), res);
}

TEST(Matrix_cxldTest, TestcRbegin)
{
    GSL::Matrix_cxld m{{1, 2}, {3, 4}, {5, 6}};
    GSL::Vector_cxld res{5, 6};
    EXPECT_EQ(*m.crbegin(), res);
}

TEST(Matrix_cxldTest, TestRend)
{
    GSL::Matrix_cxld m{{1, 2}, {3, 4}, {5, 6}};
    auto it1 = m.rend();
    EXPECT_EQ(*--it1, *(m.rbegin() + 2));
}

TEST(Matrix_cxldTest, TestcRend)
{
    GSL::Matrix_cxld m{{1, 2}, {3, 4}, {5, 6}};
    auto it1 = m.crend();
    EXPECT_EQ(*--it1, *(m.crbegin() + 2));
}
