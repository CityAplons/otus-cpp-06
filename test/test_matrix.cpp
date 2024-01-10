#include <gtest/gtest.h>

#include "matrix.hpp"

TEST(TestBasicWork, BasicAssertions)
{
    using namespace otus;

    Matrix<int, -1> matrix;
    EXPECT_EQ(matrix.size(), 0);

    auto a = matrix[0][0];
    EXPECT_EQ(a, -1);
    EXPECT_EQ(matrix.size(), 0);

    matrix[100][100] = 314;
    EXPECT_EQ(matrix[100][100], 314);
    EXPECT_EQ(matrix.size(), 1);

    for (auto c : matrix) {
        int x;
        int y;
        int v;
        std::tie(x, y, v) = c;
        EXPECT_EQ(x, 100);
        EXPECT_EQ(y, 100);
        EXPECT_EQ(v, 314);
    }
}
