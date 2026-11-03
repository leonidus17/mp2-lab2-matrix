#include <gtest/gtest.h>
#include "tmatrix.h"
#include <sstream>


TEST(DynamicMatrixTest, DefaultConstructor) {
    TDynamicMatrix<int> m(3);
    for (size_t i = 0; i < 3; ++i) {
        for (size_t j = 0; j < 3; ++j) {
            EXPECT_EQ(m[i][j], 0);
        }
    }
}

TEST(DynamicMatrixTest, Comparison) {
    TDynamicMatrix<int> m1(2);
    TDynamicMatrix<int> m2(2);
    TDynamicMatrix<int> m3(2);

    m1[0][0] = 5;
    m2[0][0] = 5;
    m3[0][0] = 9;

    EXPECT_TRUE(m1 == m2);
    EXPECT_FALSE(m1 == m3);
}


TEST(DynamicMatrixTest, ScalarMultiplication) {
    TDynamicMatrix<int> m(2);
    m[0][0] = 2;
    m[1][1] = 3;

    TDynamicMatrix<int> res = m * 10;
    EXPECT_EQ(res[0][0], 20);
    EXPECT_EQ(res[1][1], 30);
    EXPECT_EQ(res[0][1], 0);
}

TEST(DynamicMatrixTest, MatrixAdditionAndSubtraction) {
    TDynamicMatrix<int> m1(2);
    TDynamicMatrix<int> m2(2);

    m1[0][0] = 1; m1[1][1] = 2;
    m2[0][0] = 3; m2[1][1] = 4;

    TDynamicMatrix<int> sum = m1 + m2;
    EXPECT_EQ(sum[0][0], 4);
    EXPECT_EQ(sum[1][1], 6);

    TDynamicMatrix<int> diff = m2 - m1;
    EXPECT_EQ(diff[0][0], 2);
    EXPECT_EQ(diff[1][1], 2);
}

TEST(DynamicMatrixTest, MatrixMultiplication) {
    TDynamicMatrix<int> m1(2);
    TDynamicMatrix<int> m2(2);

    m1[0][0] = 1; m1[0][1] = 2;
    m1[1][0] = 3; m1[1][1] = 4;

    m2[0][0] = 5; m2[0][1] = 6;
    m2[1][0] = 7; m2[1][1] = 8;

    TDynamicMatrix<int> res = m1 * m2;
    EXPECT_EQ(res[0][0], 19);
    EXPECT_EQ(res[0][1], 22);
    EXPECT_EQ(res[1][0], 43);
    EXPECT_EQ(res[1][1], 50);
}

TEST(DynamicMatrixTest, MatrixVectorMultiplication) {
    TDynamicMatrix<int> m(2);
    m[0][0] = 2; m[1][1] = 3;

    int arr[] = { 10, 20 };
    TDynamicVector<int> v(arr, 2);

    TDynamicVector<int> res = m * v;
    EXPECT_EQ(res[0], 20);  // 2*10 + 0*20
    EXPECT_EQ(res[1], 60);  // 0*10 + 3*20
}


TEST(DynamicMatrixTest, DimensionMismatchThrows) {
    TDynamicMatrix<int> m1(2);
    TDynamicMatrix<int> m2(3);

    EXPECT_THROW(m1 + m2, std::out_of_range);
    EXPECT_THROW(m1 * m2, std::out_of_range);

    TDynamicVector<int> v(3);
    EXPECT_THROW(m1 * v, std::out_of_range);
}


TEST(DynamicMatrixTest, IO) {
    TDynamicMatrix<int> m(2);
    m[0][0] = 1; m[0][1] = 2;
    m[1][0] = 3; m[1][1] = 4;

    std::stringstream ss;
    ss << m;
    EXPECT_EQ(ss.str(), "1 2 \n3 4 \n");
}