#include "GSLpp/interp.h"
#include <gtest/gtest.h>

TEST(InterpolationTest, TestConstruction)
{
    GSL::Interpolation f({0, 1, 2, 3}, {0, 2, 4, 6}, GSL::Linear);

    ASSERT_DOUBLE_EQ(f(1.5), 3.0);
}
