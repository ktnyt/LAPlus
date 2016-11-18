/******************************************************************************
 *
 * laplus/matrixf.cpp
 *
 * MIT License
 *
 * Copyright (c) 2016 Kotone Itaya
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to
 * deal in the Software without restriction, including without limitation the
 * rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 *
 *****************************************************************************/

#include "laplus/matrixf.hpp"
#include "laplus/vectorf.hpp"
#include "gtest/gtest.h"

namespace laplus {

TEST(LAPlusMatrixf, ConstructorSize) {
  std::size_t r0 = 2;
  std::size_t c0 = 3;
  std::size_t s0 = r0 * c0;

  Matrixf m0(r0, c0);

  ASSERT_FALSE(m0.empty());
  ASSERT_EQ(m0.use_count(), 1);
  ASSERT_EQ(m0.rows(), r0);
  ASSERT_EQ(m0.cols(), c0);
  ASSERT_EQ(m0.size(), s0);
}

TEST(LAPlusMatrixf, ConstructorVector) {
  std::size_t r0 = 2;
  std::size_t c0 = 3;
  std::size_t s0 = r0 * c0;
  std::vector<float> t0 = {1, 2, 3, 4, 5, 6};

  Matrixf m0(t0, r0, c0);

  ASSERT_FALSE(m0.empty());
  ASSERT_EQ(m0.use_count(), 1);
  ASSERT_EQ(m0.rows(), r0);
  ASSERT_EQ(m0.cols(), c0);
  ASSERT_EQ(m0.size(), s0);
  ASSERT_EQ(m0, t0);
}

TEST(LAPlusMatrixf, ConstructorVector2D) {
  std::size_t r0 = 2;
  std::size_t c0 = 3;
  std::size_t s0 = r0 * c0;
  std::vector<std::vector<float>> t0 = {{1, 2, 3},
                                        {4, 5, 6}};

  Matrixf m0(t0);

  ASSERT_FALSE(m0.empty());
  ASSERT_EQ(m0.use_count(), 1);
  ASSERT_EQ(m0.rows(), r0);
  ASSERT_EQ(m0.cols(), c0);
  ASSERT_EQ(m0.size(), s0);
  ASSERT_EQ(m0, t0);
}

TEST(LAPlusMatrixf, ConstructorCopy) {
  std::size_t r0 = 2;
  std::size_t c0 = 3;
  std::size_t s0 = r0 * c0;

  Matrixf m0(r0, c0);

  ASSERT_FALSE(m0.empty());
  ASSERT_EQ(m0.use_count(), 1);
  ASSERT_EQ(m0.rows(), r0);
  ASSERT_EQ(m0.cols(), c0);
  ASSERT_EQ(m0.size(), s0);

  {
    Matrixf m1(m0);

    ASSERT_FALSE(m0.empty());
    ASSERT_EQ(m0.use_count(), 2);
    ASSERT_EQ(m0.rows(), r0);
    ASSERT_EQ(m0.cols(), c0);
    ASSERT_EQ(m0.size(), s0);

    ASSERT_FALSE(m1.empty());
    ASSERT_EQ(m1.use_count(), 2);
    ASSERT_EQ(m1.rows(), r0);
    ASSERT_EQ(m1.cols(), c0);
    ASSERT_EQ(m1.size(), s0);
  }

  ASSERT_FALSE(m0.empty());
  ASSERT_EQ(m0.use_count(), 1);
  ASSERT_EQ(m0.rows(), r0);
  ASSERT_EQ(m0.cols(), c0);
  ASSERT_EQ(m0.size(), s0);
}

TEST(LAPlusMatrixf, ConstructorMove) {
  std::size_t r0 = 2;
  std::size_t c0 = 3;
  std::size_t s0 = r0 * c0;

  Matrixf m0(r0, c0);

  ASSERT_FALSE(m0.empty());
  ASSERT_EQ(m0.use_count(), 1);
  ASSERT_EQ(m0.rows(), r0);
  ASSERT_EQ(m0.cols(), c0);
  ASSERT_EQ(m0.size(), s0);

  Matrixf m1(std::move(m0));

  ASSERT_TRUE(m0.empty());
  ASSERT_EQ(m0.use_count(), 0);
  ASSERT_EQ(m0.rows(), 0);
  ASSERT_EQ(m0.cols(), 0);
  ASSERT_EQ(m0.size(), 0);

  ASSERT_FALSE(m1.empty());
  ASSERT_EQ(m1.use_count(), 1);
  ASSERT_EQ(m1.rows(), r0);
  ASSERT_EQ(m1.cols(), c0);
  ASSERT_EQ(m1.size(), s0);
}

TEST(LAPlusMatrixf, OperatorAssignmentCopy) {
  std::size_t r0 = 2;
  std::size_t c0 = 3;
  std::size_t s0 = r0 * c0;

  Matrixf m0(r0, c0);

  ASSERT_FALSE(m0.empty());
  ASSERT_EQ(m0.use_count(), 1);
  ASSERT_EQ(m0.rows(), r0);
  ASSERT_EQ(m0.cols(), c0);
  ASSERT_EQ(m0.size(), s0);

  {
    Matrixf m1 = m0;

    ASSERT_FALSE(m0.empty());
    ASSERT_EQ(m0.use_count(), 2);
    ASSERT_EQ(m0.rows(), r0);
    ASSERT_EQ(m0.cols(), c0);
    ASSERT_EQ(m0.size(), s0);

    ASSERT_FALSE(m1.empty());
    ASSERT_EQ(m1.use_count(), 2);
    ASSERT_EQ(m1.rows(), r0);
    ASSERT_EQ(m1.cols(), c0);
    ASSERT_EQ(m1.size(), s0);
  }

  ASSERT_FALSE(m0.empty());
  ASSERT_EQ(m0.use_count(), 1);
  ASSERT_EQ(m0.rows(), r0);
  ASSERT_EQ(m0.cols(), c0);
  ASSERT_EQ(m0.size(), s0);
}

TEST(LAPlusMatrixf, OperatorAssignmentMove) {
  std::size_t r0 = 2;
  std::size_t c0 = 3;
  std::size_t s0 = r0 * c0;

  Matrixf m0(r0, c0);

  ASSERT_FALSE(m0.empty());
  ASSERT_EQ(m0.use_count(), 1);
  ASSERT_EQ(m0.rows(), r0);
  ASSERT_EQ(m0.cols(), c0);
  ASSERT_EQ(m0.size(), s0);

  Matrixf m1 = std::move(m0);

  ASSERT_TRUE(m0.empty());
  ASSERT_EQ(m0.use_count(), 0);
  ASSERT_EQ(m0.rows(), 0);
  ASSERT_EQ(m0.cols(), 0);
  ASSERT_EQ(m0.size(), 0);

  ASSERT_FALSE(m1.empty());
  ASSERT_EQ(m1.use_count(), 1);
  ASSERT_EQ(m1.rows(), r0);
  ASSERT_EQ(m1.cols(), c0);
  ASSERT_EQ(m1.size(), s0);
}

TEST(LAPlusMatrixf, OperatorSubscript) {
  std::size_t r0 = 2;
  std::size_t c0 = 3;
  std::size_t s0 = r0 * c0;
  std::vector<std::vector<float>> t0 = {{1, 2, 3},
                                        {4, 5, 6}};
  std::vector<float> t1 = {1, 2, 3};
  std::vector<float> t2 = {4, 5, 6};

  Matrixf m0(t0);

  Vectorf v0 = m0[0];
  Vectorf v1 = m0[1];

  ASSERT_FALSE(m0.empty());
  ASSERT_EQ(m0.use_count(), 3);
  ASSERT_EQ(m0.rows(), r0);
  ASSERT_EQ(m0.cols(), c0);
  ASSERT_EQ(m0.size(), s0);
  ASSERT_EQ(m0, t0);

  ASSERT_FALSE(v0.empty());
  ASSERT_EQ(v0.use_count(), 3);
  ASSERT_EQ(v0.size(), c0);
  ASSERT_EQ(v0, t1);

  ASSERT_FALSE(v1.empty());
  ASSERT_EQ(v1.use_count(), 3);
  ASSERT_EQ(v1.size(), c0);
  ASSERT_EQ(v1, t2);
}

TEST(LAPlusMatrixf, Swap) {
  std::size_t r0 = 2;
  std::size_t c0 = 3;
  std::size_t s0 = r0 * c0;
  std::vector<std::vector<float>> t0 = {{1, 2, 3},
                                        {2, 3, 4}};
  std::vector<std::vector<float>> t1 = {{1, 2},
                                        {2, 3},
                                        {3, 4}};

  Matrixf m0(t0);
  Matrixf m1 = m0.transpose();

  ASSERT_FALSE(m0.empty());
  ASSERT_EQ(m0.use_count(), 2);
  ASSERT_EQ(m0.rows(), r0);
  ASSERT_EQ(m0.cols(), c0);
  ASSERT_EQ(m0.size(), s0);
  ASSERT_EQ(m0, t0);

  ASSERT_FALSE(m1.empty());
  ASSERT_EQ(m1.use_count(), 2);
  ASSERT_EQ(m1.rows(), c0);
  ASSERT_EQ(m1.cols(), r0);
  ASSERT_EQ(m1.size(), s0);
  ASSERT_EQ(m1, t1);

  swap(m0, m1);

  ASSERT_FALSE(m0.empty());
  ASSERT_EQ(m0.use_count(), 2);
  ASSERT_EQ(m0.rows(), c0);
  ASSERT_EQ(m0.cols(), r0);
  ASSERT_EQ(m0.size(), s0);
  ASSERT_EQ(m0, t1);

  ASSERT_FALSE(m1.empty());
  ASSERT_EQ(m1.use_count(), 2);
  ASSERT_EQ(m1.rows(), r0);
  ASSERT_EQ(m1.cols(), c0);
  ASSERT_EQ(m1.size(), s0);
  ASSERT_EQ(m1, t0);
}

TEST(LAPlusMatrixf, Clone) {
  std::size_t r0 = 2;
  std::size_t c0 = 3;
  std::size_t s0 = r0 * c0;
  std::vector<std::vector<float>> t0 = {{1, 2, 3},
                                        {2, 3, 4}};

  Matrixf m0(t0);

  ASSERT_FALSE(m0.empty());
  ASSERT_EQ(m0.use_count(), 1);
  ASSERT_EQ(m0.rows(), r0);
  ASSERT_EQ(m0.cols(), c0);
  ASSERT_EQ(m0.size(), s0);
  ASSERT_EQ(m0, t0);

  Matrixf m1 = m0.clone();

  ASSERT_FALSE(m1.empty());
  ASSERT_EQ(m1.use_count(), 1);
  ASSERT_EQ(m1.rows(), r0);
  ASSERT_EQ(m1.cols(), c0);
  ASSERT_EQ(m1.size(), s0);
  ASSERT_EQ(m1, t0);
}

TEST(LAPlusMatrixf, Transpose) {
  std::size_t r0 = 2;
  std::size_t c0 = 3;
  std::size_t s0 = r0 * c0;
  std::vector<std::vector<float>> t0 = {{1, 2, 3},
                                        {2, 3, 4}};
  std::vector<std::vector<float>> t1 = {{1, 2},
                                        {2, 3},
                                        {3, 4}};

  Matrixf m0(t0);

  ASSERT_FALSE(m0.empty());
  ASSERT_EQ(m0.use_count(), 1);
  ASSERT_EQ(m0.rows(), r0);
  ASSERT_EQ(m0.cols(), c0);
  ASSERT_EQ(m0.size(), s0);
  ASSERT_EQ(m0, t0);

  Matrixf m1 = m0.transpose();

  ASSERT_FALSE(m0.empty());
  ASSERT_EQ(m0.use_count(), 2);
  ASSERT_EQ(m0.rows(), r0);
  ASSERT_EQ(m0.cols(), c0);
  ASSERT_EQ(m0.size(), s0);
  ASSERT_EQ(m0, t0);

  ASSERT_FALSE(m1.empty());
  ASSERT_EQ(m1.use_count(), 2);
  ASSERT_EQ(m1.rows(), c0);
  ASSERT_EQ(m1.cols(), r0);
  ASSERT_EQ(m1.size(), s0);
  ASSERT_EQ(m1, t1);
}

TEST(LAPlusMatrixf, Reshape) {
  std::size_t r0 = 2;
  std::size_t c0 = 3;
  std::size_t s0 = r0 * c0;
  std::vector<std::vector<float>> t0 = {{1, 2, 3},
                                        {4, 5, 6}};
  std::vector<std::vector<float>> t1 = {{1, 2},
                                        {3, 4},
                                        {5, 6}};

  Matrixf m0(t0);

  ASSERT_FALSE(m0.empty());
  ASSERT_EQ(m0.use_count(), 1);
  ASSERT_EQ(m0.rows(), r0);
  ASSERT_EQ(m0.cols(), c0);
  ASSERT_EQ(m0.size(), s0);
  ASSERT_EQ(m0, t0);

  Matrixf m1 = m0.reshape(c0, r0);

  ASSERT_FALSE(m0.empty());
  ASSERT_EQ(m0.use_count(), 2);
  ASSERT_EQ(m0.rows(), r0);
  ASSERT_EQ(m0.cols(), c0);
  ASSERT_EQ(m0.size(), s0);
  ASSERT_EQ(m0, t0);

  ASSERT_FALSE(m1.empty());
  ASSERT_EQ(m1.use_count(), 2);
  ASSERT_EQ(m1.rows(), c0);
  ASSERT_EQ(m1.cols(), r0);
  ASSERT_EQ(m1.size(), s0);
  ASSERT_EQ(m1, t1);
}

TEST(LAPlusMatrixf, Level2BLAS_GEMV) {
  std::size_t r0 = 2;
  std::size_t c0 = 3;
  std::size_t s0 = r0 * c0;
  std::vector<std::vector<float>> t0 = {{1, 2, 3},
                                        {2, 3, 4}};
  std::vector<float> t1 = {1, 2, 3};
  std::vector<float> t2 = {1, 2};
  std::vector<float> t3 = {15, 22};

  Matrixf m0(t0);
  Vectorf v0(t1);
  Vectorf v1(t2);

  ASSERT_FALSE(m0.empty());
  ASSERT_EQ(m0.use_count(), 1);
  ASSERT_EQ(m0.rows(), r0);
  ASSERT_EQ(m0.cols(), c0);
  ASSERT_EQ(m0.size(), s0);
  ASSERT_EQ(m0, t0);

  ASSERT_FALSE(v0.empty());
  ASSERT_EQ(v0.use_count(), 1);
  ASSERT_EQ(v0.size(), c0);
  ASSERT_EQ(v0, t1);

  ASSERT_FALSE(v1.empty());
  ASSERT_EQ(v1.use_count(), 1);
  ASSERT_EQ(v1.size(), r0);
  ASSERT_EQ(v1, t2);

  v1.gemv(1.0, m0, v0, 1.0);

  ASSERT_FALSE(m0.empty());
  ASSERT_EQ(m0.use_count(), 1);
  ASSERT_EQ(m0.rows(), r0);
  ASSERT_EQ(m0.cols(), c0);
  ASSERT_EQ(m0.size(), s0);
  ASSERT_EQ(m0, t0);

  ASSERT_FALSE(v0.empty());
  ASSERT_EQ(v0.use_count(), 1);
  ASSERT_EQ(v0.size(), c0);
  ASSERT_EQ(v0, t1);

  ASSERT_FALSE(v1.empty());
  ASSERT_EQ(v1.use_count(), 1);
  ASSERT_EQ(v1.size(), r0);
  ASSERT_EQ(v1, t3);
}

TEST(LAPlusMatrixf, Level2BLAS_GER) {
  std::size_t r0 = 2;
  std::size_t c0 = 3;
  std::size_t s0 = r0 * c0;
  std::vector<float> t0 = {1, 2};
  std::vector<float> t1 = {1, 2, 3};
  std::vector<std::vector<float>> t2 = {{0, 0, 0},
                                        {0, 0, 0}};
  std::vector<std::vector<float>> t3 = {{1, 2, 3},
                                        {2, 4, 6}};

  Vectorf v0(t0);
  Vectorf v1(t1);
  Matrixf m0(r0, c0);

  ASSERT_FALSE(v0.empty());
  ASSERT_EQ(v0.use_count(), 1);
  ASSERT_EQ(v0.size(), r0);
  ASSERT_EQ(v0, t0);

  ASSERT_FALSE(v1.empty());
  ASSERT_EQ(v1.use_count(), 1);
  ASSERT_EQ(v1.size(), c0);
  ASSERT_EQ(v1, t1);

  ASSERT_FALSE(m0.empty());
  ASSERT_EQ(m0.use_count(), 1);
  ASSERT_EQ(m0.rows(), r0);
  ASSERT_EQ(m0.cols(), c0);
  ASSERT_EQ(m0.size(), s0);
  ASSERT_EQ(m0, t2);

  m0.ger(1.0, t0, t1);

  ASSERT_FALSE(v0.empty());
  ASSERT_EQ(v0.use_count(), 1);
  ASSERT_EQ(v0.size(), r0);
  ASSERT_EQ(v0, t0);

  ASSERT_FALSE(v1.empty());
  ASSERT_EQ(v1.use_count(), 1);
  ASSERT_EQ(v1.size(), c0);
  ASSERT_EQ(v1, t1);

  ASSERT_FALSE(m0.empty());
  ASSERT_EQ(m0.use_count(), 1);
  ASSERT_EQ(m0.rows(), r0);
  ASSERT_EQ(m0.cols(), c0);
  ASSERT_EQ(m0.size(), s0);
  ASSERT_EQ(m0, t3);
}

TEST(LAPlusMatrixf, Level3BLAS_GEMM) {
  std::size_t r0 = 2;
  std::size_t r1 = 3;
  std::size_t c0 = 3;
  std::size_t c1 = 4;
  std::size_t s0 = r0 * c0;
  std::size_t s1 = r1 * c1;
  std::size_t s2 = r0 * c1;
  std::size_t s3 = r0 * r0;
  std::size_t s4 = c1 * c1;
  std::vector<std::vector<float>> t0 = {{1, 2, 3},
                                        {2, 3, 4}};
  std::vector<std::vector<float>> t1 = {{1, 2, 3, 4},
                                        {2, 3, 4, 5},
                                        {3, 4, 5, 6}};
  std::vector<std::vector<float>> t2 = {{14, 20, 26, 32},
                                        {20, 29, 38, 47}};
  std::vector<std::vector<float>> t3 = {{14, 20},
                                        {20, 29}};
  std::vector<std::vector<float>> t4 = {{14, 20, 26, 32},
                                        {20, 29, 38, 47},
                                        {26, 38, 50, 62},
                                        {32, 47, 62, 77}};

  Matrixf m0(t0);
  Matrixf m1(t1);
  Matrixf m2(r0, c1);
  Matrixf m3(r0, r0);
  Matrixf m4(c1, c1);
  Matrixf m5(c1, r0);

  ASSERT_FALSE(m0.empty());
  ASSERT_EQ(m0.use_count(), 1);
  ASSERT_EQ(m0.rows(), r0);
  ASSERT_EQ(m0.cols(), c0);
  ASSERT_EQ(m0.size(), s0);
  ASSERT_EQ(m0, t0);

  ASSERT_FALSE(m1.empty());
  ASSERT_EQ(m1.use_count(), 1);
  ASSERT_EQ(m1.rows(), r1);
  ASSERT_EQ(m1.cols(), c1);
  ASSERT_EQ(m1.size(), s1);
  ASSERT_EQ(m1, t1);

  ASSERT_FALSE(m2.empty());
  ASSERT_EQ(m2.use_count(), 1);
  ASSERT_EQ(m2.rows(), r0);
  ASSERT_EQ(m2.cols(), c1);
  ASSERT_EQ(m2.size(), s2);

  m2.gemm(1.0, m0, m1, 0.0);

  ASSERT_FALSE(m0.empty());
  ASSERT_EQ(m0.use_count(), 1);
  ASSERT_EQ(m0.rows(), r0);
  ASSERT_EQ(m0.cols(), c0);
  ASSERT_EQ(m0.size(), s0);
  ASSERT_EQ(m0, t0);

  ASSERT_FALSE(m1.empty());
  ASSERT_EQ(m1.use_count(), 1);
  ASSERT_EQ(m1.rows(), r1);
  ASSERT_EQ(m1.cols(), c1);
  ASSERT_EQ(m1.size(), s1);
  ASSERT_EQ(m1, t1);

  ASSERT_FALSE(m2.empty());
  ASSERT_EQ(m2.use_count(), 1);
  ASSERT_EQ(m2.rows(), r0);
  ASSERT_EQ(m2.cols(), c1);
  ASSERT_EQ(m2.size(), s2);
  ASSERT_EQ(m2, t2);

  m3.gemm(1.0, m0, m0.transpose(), 0.0);

  ASSERT_FALSE(m0.empty());
  ASSERT_EQ(m0.use_count(), 1);
  ASSERT_EQ(m0.rows(), r0);
  ASSERT_EQ(m0.cols(), c0);
  ASSERT_EQ(m0.size(), s0);
  ASSERT_EQ(m0, t0);

  ASSERT_FALSE(m1.empty());
  ASSERT_EQ(m1.use_count(), 1);
  ASSERT_EQ(m1.rows(), r1);
  ASSERT_EQ(m1.cols(), c1);
  ASSERT_EQ(m1.size(), s1);
  ASSERT_EQ(m1, t1);

  ASSERT_FALSE(m3.empty());
  ASSERT_EQ(m3.use_count(), 1);
  ASSERT_EQ(m3.rows(), r0);
  ASSERT_EQ(m3.cols(), r0);
  ASSERT_EQ(m3.size(), s3);
  ASSERT_EQ(m3, t3);

  m4.gemm(1.0, m1.transpose(), m1, 0.0);

  ASSERT_FALSE(m0.empty());
  ASSERT_EQ(m0.use_count(), 1);
  ASSERT_EQ(m0.rows(), r0);
  ASSERT_EQ(m0.cols(), c0);
  ASSERT_EQ(m0.size(), s0);
  ASSERT_EQ(m0, t0);

  ASSERT_FALSE(m1.empty());
  ASSERT_EQ(m1.use_count(), 1);
  ASSERT_EQ(m1.rows(), r1);
  ASSERT_EQ(m1.cols(), c1);
  ASSERT_EQ(m1.size(), s1);
  ASSERT_EQ(m1, t1);

  ASSERT_FALSE(m4.empty());
  ASSERT_EQ(m4.use_count(), 1);
  ASSERT_EQ(m4.rows(), c1);
  ASSERT_EQ(m4.cols(), c1);
  ASSERT_EQ(m4.size(), s4);
  ASSERT_EQ(m4, t4);

  m5.gemm(1.0, m1.transpose(), m0.transpose(), 0.0);

  ASSERT_FALSE(m0.empty());
  ASSERT_EQ(m0.use_count(), 1);
  ASSERT_EQ(m0.rows(), r0);
  ASSERT_EQ(m0.cols(), c0);
  ASSERT_EQ(m0.size(), s0);
  ASSERT_EQ(m0, t0);

  ASSERT_FALSE(m1.empty());
  ASSERT_EQ(m1.use_count(), 1);
  ASSERT_EQ(m1.rows(), r1);
  ASSERT_EQ(m1.cols(), c1);
  ASSERT_EQ(m1.size(), s1);
  ASSERT_EQ(m1, t1);

  ASSERT_FALSE(m5.empty());
  ASSERT_EQ(m5.use_count(), 1);
  ASSERT_EQ(m5.rows(), c1);
  ASSERT_EQ(m5.cols(), r0);
  ASSERT_EQ(m5.size(), s2);
  ASSERT_EQ(m5, m2.transpose());
}

TEST(LAPlusMatrixf, maxCoeff) {
  std::size_t r0 = 5;
  std::size_t c0 = 5;
  std::size_t s0 = r0 * c0;
  std::vector<std::vector<float>> t0 = {{1, 2, 3, 2, 1},
                                        {2, 3, 4, 3, 2},
                                        {3, 4, 5, 4, 3},
                                        {2, 3, 4, 3, 2},
                                        {1, 2, 3, 2, 1}};

  Matrixf m0(t0);

  ASSERT_FALSE(m0.empty());
  ASSERT_EQ(m0.use_count(), 1);
  ASSERT_EQ(m0.rows(), r0);
  ASSERT_EQ(m0.cols(), c0);
  ASSERT_EQ(m0.size(), s0);
  ASSERT_EQ(m0, t0);

  std::size_t i0;
  std::size_t j0;

  float f0 = m0.maxCoeff(i0, j0);

  ASSERT_FALSE(m0.empty());
  ASSERT_EQ(m0.use_count(), 1);
  ASSERT_EQ(m0.rows(), r0);
  ASSERT_EQ(m0.cols(), c0);
  ASSERT_EQ(m0.size(), s0);
  ASSERT_EQ(m0, t0);

  ASSERT_FLOAT_EQ(f0, 5);
  ASSERT_EQ(i0, 2);
  ASSERT_EQ(j0, 2);
}

TEST(LAPlusMatrixf, Dot) {
  std::size_t r0 = 2;
  std::size_t r1 = 3;
  std::size_t c0 = 3;
  std::size_t c1 = 4;
  std::size_t s0 = r0 * c0;
  std::size_t s1 = r1 * c1;
  std::size_t s2 = r0 * c1;
  std::size_t s3 = r0 * r0;
  std::size_t s4 = c1 * c1;
  std::vector<std::vector<float>> t0 = {{1, 2, 3},
                                        {2, 3, 4}};
  std::vector<std::vector<float>> t1 = {{1, 2, 3, 4},
                                        {2, 3, 4, 5},
                                        {3, 4, 5, 6}};
  std::vector<std::vector<float>> t2 = {{14, 20, 26, 32},
                                        {20, 29, 38, 47}};
  std::vector<std::vector<float>> t3 = {{14, 20},
                                        {20, 29}};
  std::vector<std::vector<float>> t4 = {{14, 20, 26, 32},
                                        {20, 29, 38, 47},
                                        {26, 38, 50, 62},
                                        {32, 47, 62, 77}};

  Matrixf m0(t0);
  Matrixf m1(t1);

  ASSERT_FALSE(m0.empty());
  ASSERT_EQ(m0.use_count(), 1);
  ASSERT_EQ(m0.rows(), r0);
  ASSERT_EQ(m0.cols(), c0);
  ASSERT_EQ(m0.size(), s0);
  ASSERT_EQ(m0, t0);

  ASSERT_FALSE(m1.empty());
  ASSERT_EQ(m1.use_count(), 1);
  ASSERT_EQ(m1.rows(), r1);
  ASSERT_EQ(m1.cols(), c1);
  ASSERT_EQ(m1.size(), s1);
  ASSERT_EQ(m1, t1);

  Matrixf m2 = m0.dot(m1);

  ASSERT_FALSE(m0.empty());
  ASSERT_EQ(m0.use_count(), 1);
  ASSERT_EQ(m0.rows(), r0);
  ASSERT_EQ(m0.cols(), c0);
  ASSERT_EQ(m0.size(), s0);
  ASSERT_EQ(m0, t0);

  ASSERT_FALSE(m1.empty());
  ASSERT_EQ(m1.use_count(), 1);
  ASSERT_EQ(m1.rows(), r1);
  ASSERT_EQ(m1.cols(), c1);
  ASSERT_EQ(m1.size(), s1);
  ASSERT_EQ(m1, t1);

  ASSERT_FALSE(m2.empty());
  ASSERT_EQ(m2.use_count(), 1);
  ASSERT_EQ(m2.rows(), r0);
  ASSERT_EQ(m2.cols(), c1);
  ASSERT_EQ(m2.size(), s2);
  ASSERT_EQ(m2, t2);

  Matrixf m3 = m0.dot(m0.transpose());

  ASSERT_FALSE(m0.empty());
  ASSERT_EQ(m0.use_count(), 1);
  ASSERT_EQ(m0.rows(), r0);
  ASSERT_EQ(m0.cols(), c0);
  ASSERT_EQ(m0.size(), s0);
  ASSERT_EQ(m0, t0);

  ASSERT_FALSE(m1.empty());
  ASSERT_EQ(m1.use_count(), 1);
  ASSERT_EQ(m1.rows(), r1);
  ASSERT_EQ(m1.cols(), c1);
  ASSERT_EQ(m1.size(), s1);
  ASSERT_EQ(m1, t1);

  ASSERT_FALSE(m3.empty());
  ASSERT_EQ(m3.use_count(), 1);
  ASSERT_EQ(m3.rows(), r0);
  ASSERT_EQ(m3.cols(), r0);
  ASSERT_EQ(m3.size(), s3);
  ASSERT_EQ(m3, t3);

  Matrixf m4 = m1.transpose().dot(m1);

  ASSERT_FALSE(m0.empty());
  ASSERT_EQ(m0.use_count(), 1);
  ASSERT_EQ(m0.rows(), r0);
  ASSERT_EQ(m0.cols(), c0);
  ASSERT_EQ(m0.size(), s0);
  ASSERT_EQ(m0, t0);

  ASSERT_FALSE(m1.empty());
  ASSERT_EQ(m1.use_count(), 1);
  ASSERT_EQ(m1.rows(), r1);
  ASSERT_EQ(m1.cols(), c1);
  ASSERT_EQ(m1.size(), s1);
  ASSERT_EQ(m1, t1);

  ASSERT_FALSE(m4.empty());
  ASSERT_EQ(m4.use_count(), 1);
  ASSERT_EQ(m4.rows(), c1);
  ASSERT_EQ(m4.cols(), c1);
  ASSERT_EQ(m4.size(), s4);
  ASSERT_EQ(m4, t4);

  Matrixf m5 = m1.transpose().dot(m0.transpose());

  ASSERT_FALSE(m0.empty());
  ASSERT_EQ(m0.use_count(), 1);
  ASSERT_EQ(m0.rows(), r0);
  ASSERT_EQ(m0.cols(), c0);
  ASSERT_EQ(m0.size(), s0);
  ASSERT_EQ(m0, t0);

  ASSERT_FALSE(m1.empty());
  ASSERT_EQ(m1.use_count(), 1);
  ASSERT_EQ(m1.rows(), r1);
  ASSERT_EQ(m1.cols(), c1);
  ASSERT_EQ(m1.size(), s1);
  ASSERT_EQ(m1, t1);

  ASSERT_FALSE(m5.empty());
  ASSERT_EQ(m5.use_count(), 1);
  ASSERT_EQ(m5.rows(), c1);
  ASSERT_EQ(m5.cols(), r0);
  ASSERT_EQ(m5.size(), s2);
  ASSERT_EQ(m5, m2.transpose());
}

}  // namespace laplus


