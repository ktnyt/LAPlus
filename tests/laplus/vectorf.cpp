/******************************************************************************
 *
 * laplus/vectorf.cpp
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

#include "laplus/vectorf.hpp"
#include "gtest/gtest.h"

#include <vector>

namespace laplus {

TEST(LAPlusVectorf, ConstructorSize) {
  std::size_t s0 = 3;
  Vectorf v0(s0);

  ASSERT_FALSE(v0.empty());
  ASSERT_EQ(v0.use_count(), 1);
  ASSERT_EQ(v0.size(), s0);
}

TEST(LAPlusVectorf, ConstructorVector) {
  std::vector<float> t0 = {0, 1, 2};
  Vectorf v0(t0);

  ASSERT_FALSE(v0.empty());
  ASSERT_EQ(v0.use_count(), 1);
  ASSERT_EQ(v0.size(), t0.size());
  ASSERT_EQ(v0, t0);
}

TEST(LAPlusVectorf, ConstructorCopy) {
  std::size_t s0 = 3;
  Vectorf v0(s0);

  ASSERT_FALSE(v0.empty());
  ASSERT_EQ(v0.use_count(), 1);
  ASSERT_EQ(v0.size(), s0);

  {
    Vectorf v1(v0);

    ASSERT_FALSE(v0.empty());
    ASSERT_EQ(v0.use_count(), 2);
    ASSERT_EQ(v0.size(), s0);

    ASSERT_FALSE(v1.empty());
    ASSERT_EQ(v1.use_count(), 2);
    ASSERT_EQ(v1.size(), s0);

    ASSERT_EQ(v0, v1);
    ASSERT_EQ(v0.get(), v1.get());
  }

  ASSERT_FALSE(v0.empty());
  ASSERT_EQ(v0.use_count(), 1);
  ASSERT_EQ(v0.size(), s0);
}

TEST(LAPlusVectorf, ConstructorMove) {
  std::size_t s0 = 3;
  Vectorf v0(s0);

  ASSERT_FALSE(v0.empty());
  ASSERT_EQ(v0.use_count(), 1);
  ASSERT_EQ(v0.size(), s0);

  Vectorf v1(std::move(v0));

  ASSERT_TRUE(v0.empty());
  ASSERT_EQ(v0.use_count(), 0);
  ASSERT_EQ(v0.size(), 0);

  ASSERT_FALSE(v1.empty());
  ASSERT_EQ(v1.use_count(), 1);
  ASSERT_EQ(v1.size(), s0);
}

TEST(LAPlusVectorf, ConstructorWindow) {
  std::vector<float> t0 = {1 ,2, 3, 4, 5, 6, 7, 8, 9};
  Vectorf v0(t0);

  ASSERT_FALSE(v0.empty());
  ASSERT_EQ(v0.use_count(), 1);
  ASSERT_EQ(v0.size(), t0.size());
  ASSERT_EQ(v0, t0);

  {
    std::vector<float> t1 = {1, 4, 7};
    Vectorf v1(v0, 0, 3, 3);

    ASSERT_FALSE(v0.empty());
    ASSERT_EQ(v0.use_count(), 2);
    ASSERT_EQ(v0.size(), t0.size());
    ASSERT_EQ(v0, t0);

    ASSERT_FALSE(v1.empty());
    ASSERT_EQ(v1.use_count(), 2);
    ASSERT_EQ(v1.size(), t1.size());
    ASSERT_EQ(v1, t1);

    ASSERT_EQ(v0.get(), v1.get());

    {
      std::vector<float> t2 = {2, 5, 8};
      Vectorf v2(v0, 1, 3, 3);

      ASSERT_FALSE(v0.empty());
      ASSERT_EQ(v0.use_count(), 3);
      ASSERT_EQ(v0.size(), t0.size());
      ASSERT_EQ(v0, t0);

      ASSERT_FALSE(v1.empty());
      ASSERT_EQ(v1.use_count(), 3);
      ASSERT_EQ(v1.size(), t1.size());
      ASSERT_EQ(v1, t1);

      ASSERT_FALSE(v2.empty());
      ASSERT_EQ(v2.use_count(), 3);
      ASSERT_EQ(v2.size(), t2.size());
      ASSERT_EQ(v2, t2);

      ASSERT_EQ(v0.get(), v1.get());
      ASSERT_EQ(v0.get(), v2.get());

      {
        std::vector<float> t3 = {3, 6, 9};
        Vectorf v3(v0, 2, 3, 3);

        ASSERT_FALSE(v0.empty());
        ASSERT_EQ(v0.use_count(), 4);
        ASSERT_EQ(v0.size(), t0.size());
        ASSERT_EQ(v0, t0);

        ASSERT_FALSE(v1.empty());
        ASSERT_EQ(v1.use_count(), 4);
        ASSERT_EQ(v1.size(), t1.size());
        ASSERT_EQ(v1, t1);

        ASSERT_FALSE(v2.empty());
        ASSERT_EQ(v2.use_count(), 4);
        ASSERT_EQ(v2.size(), t2.size());
        ASSERT_EQ(v2, t2);

        ASSERT_FALSE(v3.empty());
        ASSERT_EQ(v3.use_count(), 4);
        ASSERT_EQ(v3.size(), t3.size());
        ASSERT_EQ(v3, t3);

        ASSERT_EQ(v0.get(), v1.get());
        ASSERT_EQ(v0.get(), v2.get());
        ASSERT_EQ(v0.get(), v3.get());
      }

      ASSERT_FALSE(v0.empty());
      ASSERT_EQ(v0.use_count(), 3);
      ASSERT_EQ(v0.size(), t0.size());
      ASSERT_EQ(v0, t0);

      ASSERT_FALSE(v1.empty());
      ASSERT_EQ(v1.use_count(), 3);
      ASSERT_EQ(v1.size(), t1.size());
      ASSERT_EQ(v1, t1);

      ASSERT_FALSE(v2.empty());
      ASSERT_EQ(v2.use_count(), 3);
      ASSERT_EQ(v2.size(), t2.size());
      ASSERT_EQ(v2, t2);

      ASSERT_EQ(v0.get(), v1.get());
      ASSERT_EQ(v0.get(), v2.get());
    }

    ASSERT_FALSE(v0.empty());
    ASSERT_EQ(v0.use_count(), 2);
    ASSERT_EQ(v0.size(), t0.size());
    ASSERT_EQ(v0, t0);

    ASSERT_FALSE(v1.empty());
    ASSERT_EQ(v1.use_count(), 2);
    ASSERT_EQ(v1.size(), t1.size());
    ASSERT_EQ(v1, t1);

    ASSERT_EQ(v0.get(), v1.get());
  }

  ASSERT_FALSE(v0.empty());
  ASSERT_EQ(v0.use_count(), 1);
  ASSERT_EQ(v0.size(), t0.size());
  ASSERT_EQ(v0, t0);
}

TEST(LAPlusVectorf, OperatorAssignmentCopy) {
  std::size_t s0 = 3;
  Vectorf v0(s0);

  ASSERT_FALSE(v0.empty());
  ASSERT_EQ(v0.use_count(), 1);
  ASSERT_EQ(v0.size(), s0);

  {
    Vectorf v1 = v0;

    ASSERT_FALSE(v0.empty());
    ASSERT_EQ(v0.use_count(), 2);
    ASSERT_EQ(v0.size(), s0);

    ASSERT_FALSE(v1.empty());
    ASSERT_EQ(v1.use_count(), 2);
    ASSERT_EQ(v1.size(), s0);

    ASSERT_EQ(v0, v1);
    ASSERT_EQ(v0.get(), v1.get());
  }

  ASSERT_FALSE(v0.empty());
  ASSERT_EQ(v0.use_count(), 1);
  ASSERT_EQ(v0.size(), s0);
}

TEST(LAPlusVectorf, OperatorAssignmentMove) {
  std::size_t s0 = 3;
  Vectorf v0(s0);

  ASSERT_FALSE(v0.empty());
  ASSERT_EQ(v0.use_count(), 1);
  ASSERT_EQ(v0.size(), s0);

  Vectorf v1 = std::move(v0);

  ASSERT_TRUE(v0.empty());
  ASSERT_EQ(v0.use_count(), 0);
  ASSERT_EQ(v0.size(), 0);

  ASSERT_FALSE(v1.empty());
  ASSERT_EQ(v1.use_count(), 1);
  ASSERT_EQ(v1.size(), s0);
}

TEST(LAPlusVectorf, OperatorAssignmentAdd) {
  Vectorf v0({1, 2, 3, 4, 5, 6});
  Vectorf v1({1, 2, 3, 4, 5, 6});
  std::vector<float> t0({1, 2, 3, 4, 5, 6});
  std::vector<float> t1({2, 4, 6, 8, 10, 12});

  ASSERT_EQ(v0, t0);
  ASSERT_EQ(v1, t0);
  ASSERT_EQ(v0.use_count(), 1);
  ASSERT_EQ(v1.use_count(), 1);

  v1 += v0;

  ASSERT_EQ(v0, t0);
  ASSERT_EQ(v1, t1);
  ASSERT_EQ(v0.use_count(), 1);
  ASSERT_EQ(v1.use_count(), 1);
}

TEST(LAPlusVectorf, OperatorAssignmentSub) {
  Vectorf v0({1, 2, 3, 4, 5, 6});
  Vectorf v1({1, 2, 3, 4, 5, 6});
  std::vector<float> t0({1, 2, 3, 4, 5, 6});
  std::vector<float> t1({0, 0, 0, 0, 0, 0});

  ASSERT_EQ(v0, t0);
  ASSERT_EQ(v1, t0);
  ASSERT_EQ(v0.use_count(), 1);
  ASSERT_EQ(v1.use_count(), 1);

  v1 -= v0;

  ASSERT_EQ(v0, t0);
  ASSERT_EQ(v1, t1);
  ASSERT_EQ(v0.use_count(), 1);
  ASSERT_EQ(v1.use_count(), 1);
}

TEST(LAPlusVectorf, OperatorAssignmentMul) {
  Vectorf v0({1, 2, 3, 4, 5, 6});
  Vectorf v1({1, 2, 3, 4, 5, 6});
  std::vector<float> t0({1, 2, 3, 4, 5, 6});
  std::vector<float> t1({1, 4, 9, 16, 25, 36});

  ASSERT_EQ(v0, t0);
  ASSERT_EQ(v1, t0);
  ASSERT_EQ(v0.use_count(), 1);
  ASSERT_EQ(v1.use_count(), 1);

  v1 *= v0;

  ASSERT_EQ(v0, t0);
  ASSERT_EQ(v1, t1);
  ASSERT_EQ(v0.use_count(), 1);
  ASSERT_EQ(v1.use_count(), 1);
}

TEST(LAPlusVectorf, OperatorAssignmentDiv) {
  Vectorf v0({1, 2, 3, 4, 5, 6});
  Vectorf v1({1, 2, 3, 4, 5, 6});
  std::vector<float> t0({1, 2, 3, 4, 5, 6});
  std::vector<float> t1({1, 1, 1, 1, 1, 1});

  ASSERT_EQ(v0, t0);
  ASSERT_EQ(v1, t0);
  ASSERT_EQ(v0.use_count(), 1);
  ASSERT_EQ(v1.use_count(), 1);

  v1 /= v0;

  ASSERT_EQ(v0, t0);
  ASSERT_EQ(v1, t1);
  ASSERT_EQ(v0.use_count(), 1);
  ASSERT_EQ(v1.use_count(), 1);
}

TEST(LAPlusVectorf, OperatorAssignmentPow) {
  Vectorf v0({1, 2, 3, 4, 5, 6});
  Vectorf v1({2, 2, 2, 2, 2, 2});
  std::vector<float> t0({1, 2, 3, 4, 5, 6});
  std::vector<float> t1({2, 2, 2, 2, 2, 2});
  std::vector<float> t2({2, 4, 8, 16, 32, 64});

  ASSERT_EQ(v0, t0);
  ASSERT_EQ(v1, t1);
  ASSERT_EQ(v0.use_count(), 1);
  ASSERT_EQ(v1.use_count(), 1);

  v1 ^= v0;

  ASSERT_EQ(v0, t0);
  ASSERT_EQ(v1, t2);
  ASSERT_EQ(v0.use_count(), 1);
  ASSERT_EQ(v1.use_count(), 1);
}

TEST(LAPlusVectorf, OperatorAssignmentAddFloat) {
  Vectorf v0({1, 2, 3, 4, 5, 6});
  std::vector<float> t0({1, 2, 3, 4, 5, 6});
  std::vector<float> t1({2, 3, 4, 5, 6, 7});

  ASSERT_EQ(v0, t0);
  ASSERT_EQ(v0.use_count(), 1);

  v0 += 1.;

  ASSERT_EQ(v0, t1);
  ASSERT_EQ(v0.use_count(), 1);
}

TEST(LAPlusVectorf, OperatorAssignmentSubFloat) {
  Vectorf v0({1, 2, 3, 4, 5, 6});
  std::vector<float> t0({1, 2, 3, 4, 5, 6});
  std::vector<float> t1({0, 1, 2, 3, 4, 5});

  ASSERT_EQ(v0, t0);
  ASSERT_EQ(v0.use_count(), 1);

  v0 -= 1.;

  ASSERT_EQ(v0, t1);
  ASSERT_EQ(v0.use_count(), 1);
}

TEST(LAPlusVectorf, OperatorAssignmentMulFloat) {
  Vectorf v0({1, 2, 3, 4, 5, 6});
  std::vector<float> t0({1, 2, 3, 4, 5, 6});
  std::vector<float> t1({2, 4, 6, 8, 10, 12});

  ASSERT_EQ(v0, t0);
  ASSERT_EQ(v0.use_count(), 1);

  v0 *= 2.;

  ASSERT_EQ(v0, t1);
  ASSERT_EQ(v0.use_count(), 1);
}

TEST(LAPlusVectorf, OperatorAssignmentDivFloat) {
  Vectorf v0({1, 2, 3, 4, 5, 6});
  std::vector<float> t0({1, 2, 3, 4, 5, 6});
  std::vector<float> t1({.5, 1, 1.5, 2, 2.5, 3});

  ASSERT_EQ(v0, t0);
  ASSERT_EQ(v0.use_count(), 1);

  v0 /= 2.;

  ASSERT_EQ(v0, t1);
  ASSERT_EQ(v0.use_count(), 1);
}

TEST(LAPlusVectorf, OperatorAssignmentPowFloat) {
  Vectorf v0({1, 2, 3, 4, 5, 6});
  std::vector<float> t0({1, 2, 3, 4, 5, 6});
  std::vector<float> t1({1, 4, 9, 16, 25, 36});

  ASSERT_EQ(v0, t0);
  ASSERT_EQ(v0.use_count(), 1);

  v0 ^= 2.;

  ASSERT_EQ(v0, t1);
  ASSERT_EQ(v0.use_count(), 1);
}

TEST(LAPlusVectorf, OperatorArithmeticAdd) {
  Vectorf v0({1, 2, 3, 4, 5, 6});
  Vectorf v1({1, 2, 3, 4, 5, 6});
  Vectorf v2(6);
  std::vector<float> t0({1, 2, 3, 4, 5, 6});
  std::vector<float> t1({0, 0, 0, 0, 0, 0});
  std::vector<float> t2({2, 4, 6, 8, 10, 12});

  ASSERT_EQ(v0, t0);
  ASSERT_EQ(v1, t0);
  ASSERT_EQ(v2, t1);
  ASSERT_EQ(v0.use_count(), 1);
  ASSERT_EQ(v1.use_count(), 1);
  ASSERT_EQ(v2.use_count(), 1);

  v2 = v1 + v0;

  ASSERT_EQ(v0, t0);
  ASSERT_EQ(v1, t0);
  ASSERT_EQ(v2, t2);
  ASSERT_EQ(v0.use_count(), 1);
  ASSERT_EQ(v1.use_count(), 1);
  ASSERT_EQ(v2.use_count(), 1);
}

TEST(LAPlusVectorf, OperatorArithmeticSub) {
  Vectorf v0({1, 2, 3, 4, 5, 6});
  Vectorf v1({0, 0, 0, 0, 0, 0});
  Vectorf v2(6);
  std::vector<float> t0({1, 2, 3, 4, 5, 6});
  std::vector<float> t1({0, 0, 0, 0, 0, 0});
  std::vector<float> t2({-1, -2, -3, -4, -5, -6});

  ASSERT_EQ(v0, t0);
  ASSERT_EQ(v1, t1);
  ASSERT_EQ(v2, t1);
  ASSERT_EQ(v0.use_count(), 1);
  ASSERT_EQ(v1.use_count(), 1);
  ASSERT_EQ(v2.use_count(), 1);

  v2 = v1 - v0;

  ASSERT_EQ(v0, t0);
  ASSERT_EQ(v1, t1);
  ASSERT_EQ(v2, t2);
  ASSERT_EQ(v0.use_count(), 1);
  ASSERT_EQ(v1.use_count(), 1);
  ASSERT_EQ(v2.use_count(), 1);
}

TEST(LAPlusVectorf, OperatorArithmeticMul) {
  Vectorf v0({1, 2, 3, 4, 5, 6});
  Vectorf v1({1, 2, 3, 4, 5, 6});
  Vectorf v2(6);
  std::vector<float> t0({1, 2, 3, 4, 5, 6});
  std::vector<float> t1({0, 0, 0, 0, 0, 0});
  std::vector<float> t2({1, 4, 9, 16, 25, 36});

  ASSERT_EQ(v0, t0);
  ASSERT_EQ(v1, t0);
  ASSERT_EQ(v2, t1);
  ASSERT_EQ(v0.use_count(), 1);
  ASSERT_EQ(v1.use_count(), 1);
  ASSERT_EQ(v2.use_count(), 1);

  v2 = v1 * v0;

  ASSERT_EQ(v0, t0);
  ASSERT_EQ(v1, t0);
  ASSERT_EQ(v2, t2);
  ASSERT_EQ(v0.use_count(), 1);
  ASSERT_EQ(v1.use_count(), 1);
  ASSERT_EQ(v2.use_count(), 1);
}

TEST(LAPlusVectorf, OperatorArithmeticDiv) {
  Vectorf v0({1, 2, 3, 4, 5, 6});
  Vectorf v1({1, 2, 3, 4, 5, 6});
  Vectorf v2(6);
  std::vector<float> t0({1, 2, 3, 4, 5, 6});
  std::vector<float> t1({0, 0, 0, 0, 0, 0});
  std::vector<float> t2({1, 1, 1, 1, 1, 1});

  ASSERT_EQ(v0, t0);
  ASSERT_EQ(v1, t0);
  ASSERT_EQ(v2, t1);
  ASSERT_EQ(v0.use_count(), 1);
  ASSERT_EQ(v1.use_count(), 1);
  ASSERT_EQ(v2.use_count(), 1);

  v2 = v1 / v0;

  ASSERT_EQ(v0, t0);
  ASSERT_EQ(v1, t0);
  ASSERT_EQ(v2, t2);
  ASSERT_EQ(v0.use_count(), 1);
  ASSERT_EQ(v1.use_count(), 1);
  ASSERT_EQ(v2.use_count(), 1);
}

TEST(LAPlusVectorf, OperatorArithmeticPow) {
  Vectorf v0({1, 2, 3, 4, 5, 6});
  Vectorf v1({2, 2, 2, 2, 2, 2});
  Vectorf v2(6);
  std::vector<float> t0({1, 2, 3, 4, 5, 6});
  std::vector<float> t1({2, 2, 2, 2, 2, 2});
  std::vector<float> t2({0, 0, 0, 0, 0, 0});
  std::vector<float> a3({2, 4, 8, 16, 32, 64});

  ASSERT_EQ(v0, t0);
  ASSERT_EQ(v1, t1);
  ASSERT_EQ(v2, t2);
  ASSERT_EQ(v0.use_count(), 1);
  ASSERT_EQ(v1.use_count(), 1);
  ASSERT_EQ(v2.use_count(), 1);

  v2 = v1 ^ v0;

  ASSERT_EQ(v0, t0);
  ASSERT_EQ(v1, t1);
  ASSERT_EQ(v2, a3);
  ASSERT_EQ(v0.use_count(), 1);
  ASSERT_EQ(v1.use_count(), 1);
  ASSERT_EQ(v2.use_count(), 1);
}

TEST(LAPlusVectorf, OperatorArithmeticAddFloatR) {
  Vectorf v0({1, 2, 3, 4, 5, 6});
  Vectorf v1(6);
  std::vector<float> t0({1, 2, 3, 4, 5, 6});
  std::vector<float> t1({0, 0, 0, 0, 0, 0});
  std::vector<float> t2({2, 3, 4, 5, 6, 7});

  ASSERT_EQ(v0, t0);
  ASSERT_EQ(v1, t1);
  ASSERT_EQ(v0.use_count(), 1);
  ASSERT_EQ(v1.use_count(), 1);

  v1 = v0 + 1.;

  ASSERT_EQ(v0, t0);
  ASSERT_EQ(v1, t2);
  ASSERT_EQ(v0.use_count(), 1);
  ASSERT_EQ(v1.use_count(), 1);
}

TEST(LAPlusVectorf, OperatorArithmeticAddFloatL) {
  Vectorf v0({1, 2, 3, 4, 5, 6});
  Vectorf v1(6);
  std::vector<float> t0({1, 2, 3, 4, 5, 6});
  std::vector<float> t1({0, 0, 0, 0, 0, 0});
  std::vector<float> t2({2, 3, 4, 5, 6, 7});

  ASSERT_EQ(v0, t0);
  ASSERT_EQ(v1, t1);
  ASSERT_EQ(v0.use_count(), 1);
  ASSERT_EQ(v1.use_count(), 1);

  v1 = 1. + v0;

  ASSERT_EQ(v0, t0);
  ASSERT_EQ(v1, t2);
  ASSERT_EQ(v0.use_count(), 1);
  ASSERT_EQ(v1.use_count(), 1);
}

TEST(LAPlusVectorf, OperatorArithmeticSubFloatR) {
  Vectorf v0({1, 2, 3, 4, 5, 6});
  Vectorf v1(6);
  std::vector<float> t0({1, 2, 3, 4, 5, 6});
  std::vector<float> t1({0, 0, 0, 0, 0, 0});
  std::vector<float> t2({0, 1, 2, 3, 4, 5});

  ASSERT_EQ(v0, t0);
  ASSERT_EQ(v1, t1);
  ASSERT_EQ(v0.use_count(), 1);
  ASSERT_EQ(v1.use_count(), 1);

  v1 = v0 - 1.;

  ASSERT_EQ(v0, t0);
  ASSERT_EQ(v1, t2);
  ASSERT_EQ(v0.use_count(), 1);
  ASSERT_EQ(v1.use_count(), 1);
}

TEST(LAPlusVectorf, OperatorArithmeticSubFloatL) {
  Vectorf v0({1, 2, 3, 4, 5, 6});
  Vectorf v1(6);
  std::vector<float> t0({1, 2, 3, 4, 5, 6});
  std::vector<float> t1({0, 0, 0, 0, 0, 0});
  std::vector<float> t2({0, -1, -2, -3, -4, -5});

  ASSERT_EQ(v0, t0);
  ASSERT_EQ(v1, t1);
  ASSERT_EQ(v0.use_count(), 1);
  ASSERT_EQ(v1.use_count(), 1);

  v1 = 1. - v0;

  ASSERT_EQ(v0, t0);
  ASSERT_EQ(v1, t2);
  ASSERT_EQ(v0.use_count(), 1);
  ASSERT_EQ(v1.use_count(), 1);
}

TEST(LAPlusVectorf, OperatorArithmeticMulFloatR) {
  Vectorf v0({1, 2, 3, 4, 5, 6});
  Vectorf v1(6);
  std::vector<float> t0({1, 2, 3, 4, 5, 6});
  std::vector<float> t1({0, 0, 0, 0, 0, 0});
  std::vector<float> t2({2, 4, 6, 8, 10, 12});

  ASSERT_EQ(v0, t0);
  ASSERT_EQ(v1, t1);
  ASSERT_EQ(v0.use_count(), 1);
  ASSERT_EQ(v1.use_count(), 1);

  v1 = v0 * 2.;

  ASSERT_EQ(v0, t0);
  ASSERT_EQ(v1, t2);
  ASSERT_EQ(v0.use_count(), 1);
  ASSERT_EQ(v1.use_count(), 1);
}

TEST(LAPlusVectorf, OperatorArithmeticMulFloatL) {
  Vectorf v0({1, 2, 3, 4, 5, 6});
  Vectorf v1(6);
  std::vector<float> t0({1, 2, 3, 4, 5, 6});
  std::vector<float> t1({0, 0, 0, 0, 0, 0});
  std::vector<float> t2({2, 4, 6, 8, 10, 12});

  ASSERT_EQ(v0, t0);
  ASSERT_EQ(v1, t1);
  ASSERT_EQ(v0.use_count(), 1);
  ASSERT_EQ(v1.use_count(), 1);

  v1 = 2 * v0;

  ASSERT_EQ(v0, t0);
  ASSERT_EQ(v1, t2);
  ASSERT_EQ(v0.use_count(), 1);
  ASSERT_EQ(v1.use_count(), 1);
}

TEST(LAPlusVectorf, OperatorArithmeticDivFloatR) {
  Vectorf v0({1, 2, 3, 4, 5, 6});
  Vectorf v1(6);
  std::vector<float> t0({1, 2, 3, 4, 5, 6});
  std::vector<float> t1({0, 0, 0, 0, 0, 0});
  std::vector<float> t2({.5, 1, 1.5, 2, 2.5, 3});

  ASSERT_EQ(v0, t0);
  ASSERT_EQ(v1, t1);
  ASSERT_EQ(v0.use_count(), 1);
  ASSERT_EQ(v1.use_count(), 1);

  v1 = v0 / 2.;

  ASSERT_EQ(v0, t0);
  ASSERT_EQ(v1, t2);
  ASSERT_EQ(v0.use_count(), 1);
  ASSERT_EQ(v1.use_count(), 1);
}

TEST(LAPlusVectorf, OperatorArithmeticDivFloatL) {
  Vectorf v0({1, 2, 3, 4, 5, 6});
  Vectorf v1(6);
  std::vector<float> t0({1, 2, 3, 4, 5, 6});
  std::vector<float> t1({0, 0, 0, 0, 0, 0});
  std::vector<float> t2({1 / 1., 1 / 2., 1 / 3., 1 / 4., 1 / 5., 1 / 6.});

  ASSERT_EQ(v0, t0);
  ASSERT_EQ(v1, t1);
  ASSERT_EQ(v0.use_count(), 1);
  ASSERT_EQ(v1.use_count(), 1);

  v1 = 1. / v0;

  ASSERT_EQ(v0, t0);
  ASSERT_EQ(v1, t2);
  ASSERT_EQ(v0.use_count(), 1);
  ASSERT_EQ(v1.use_count(), 1);
}

TEST(LAPlusVectorf, OperatorArithmeticPowFloatR) {
  Vectorf v0({1, 2, 3, 4, 5, 6});
  Vectorf v1(6);
  std::vector<float> t0({1, 2, 3, 4, 5, 6});
  std::vector<float> t1({0, 0, 0, 0, 0, 0});
  std::vector<float> t2({1, 4, 9, 16, 25, 36});

  ASSERT_EQ(v0, t0);
  ASSERT_EQ(v1, t1);
  ASSERT_EQ(v0.use_count(), 1);
  ASSERT_EQ(v1.use_count(), 1);

  v1 = v0 ^ 2;

  ASSERT_EQ(v0, t0);
  ASSERT_EQ(v1, t2);
  ASSERT_EQ(v0.use_count(), 1);
  ASSERT_EQ(v1.use_count(), 1);
}

TEST(LAPlusVectorf, OperatorSubscript) {
  std::vector<float> t0 = {0, 1, 2};
  std::vector<float> t1 = {42, 1, 2};

  Vectorf v0(t0);
  Vectorf v1(v0);

  ASSERT_FALSE(v0.empty());
  ASSERT_EQ(v0.use_count(), 2);
  ASSERT_EQ(v0, t0);

  ASSERT_FALSE(v1.empty());
  ASSERT_EQ(v1.use_count(), 2);
  ASSERT_EQ(v1, t0);

  v0[0] = 42;

  ASSERT_FALSE(v0.empty());
  ASSERT_EQ(v0.use_count(), 2);
  ASSERT_EQ(v0, t1);

  ASSERT_FALSE(v1.empty());
  ASSERT_EQ(v1.use_count(), 2);
  ASSERT_EQ(v1, t1);
}

TEST(LAPlusVectorf, Swap) {
  std::vector<float> t0 = {0, 1, 2};
  std::vector<float> t1 = {1, 2, 3};

  Vectorf v0(t0);
  Vectorf v1(t1);

  ASSERT_FALSE(v0.empty());
  ASSERT_EQ(v0.use_count(), 1);
  ASSERT_EQ(v0, t0);

  ASSERT_FALSE(v1.empty());
  ASSERT_EQ(v1.use_count(), 1);
  ASSERT_EQ(v1, t1);

  ASSERT_NE(v0, v1);

  swap(v0, v1);

  ASSERT_FALSE(v0.empty());
  ASSERT_EQ(v0.use_count(), 1);
  ASSERT_EQ(v0, t1);

  ASSERT_FALSE(v1.empty());
  ASSERT_EQ(v1.use_count(), 1);
  ASSERT_EQ(v1, t0);

  ASSERT_NE(v0, v1);
}

TEST(LAPlusVectorf, Clone) {
  std::vector<float> t0 = {1, 2, 3};

  Vectorf v0(t0);

  ASSERT_FALSE(v0.empty());
  ASSERT_EQ(v0.use_count(), 1);
  ASSERT_EQ(v0, t0);

  Vectorf v1 = v0.clone();

  ASSERT_FALSE(v0.empty());
  ASSERT_EQ(v0.use_count(), 1);
  ASSERT_EQ(v0, t0);

  ASSERT_FALSE(v1.empty());
  ASSERT_EQ(v1.use_count(), 1);
  ASSERT_EQ(v1, t0);  
}

TEST(LAPlusVectorf, SwapWindow) {
  std::vector<float> t0 = {1, 2, 3, 4, 5, 6};
  std::vector<float> t1 = {1, 2, 3};
  std::vector<float> t2 = {4 ,5, 6};

  Vectorf v0(t0);
  Vectorf v1(v0, 0, 1, 3);
  Vectorf v2(v0, 3, 1, 3);

  ASSERT_FALSE(v0.empty());
  ASSERT_EQ(v0.use_count(), 3);
  ASSERT_EQ(v0, t0);

  ASSERT_FALSE(v1.empty());
  ASSERT_EQ(v1.use_count(), 3);
  ASSERT_EQ(v1, t1);

  ASSERT_FALSE(v2.empty());
  ASSERT_EQ(v2.use_count(), 3);
  ASSERT_EQ(v2, t2);

  ASSERT_NE(v1, v2);

  ASSERT_EQ(v1.get(), v2.get());

  swap(v1, v2);

  ASSERT_FALSE(v0.empty());
  ASSERT_EQ(v0.use_count(), 3);
  ASSERT_EQ(v0, t0);

  ASSERT_FALSE(v1.empty());
  ASSERT_EQ(v1.use_count(), 3);
  ASSERT_EQ(v1, t2);

  ASSERT_FALSE(v2.empty());
  ASSERT_EQ(v2.use_count(), 3);
  ASSERT_EQ(v2, t1);

  ASSERT_NE(v1, v2);

  ASSERT_EQ(v1.get(), v2.get());
}

TEST(LAPlusVectorf, Level1BLAS_SWAP) {
  std::vector<float> t0 = {0, 1, 2};
  std::vector<float> t1 = {1, 2, 3};

  Vectorf v0(t0);
  Vectorf v1(t1);

  ASSERT_FALSE(v0.empty());
  ASSERT_EQ(v0.use_count(), 1);
  ASSERT_EQ(v0, t0);

  ASSERT_FALSE(v1.empty());
  ASSERT_EQ(v1.use_count(), 1);
  ASSERT_EQ(v1, t1);

  ASSERT_NE(v0, v1);

  v0.swap(v1);

  ASSERT_FALSE(v0.empty());
  ASSERT_EQ(v0.use_count(), 1);
  ASSERT_EQ(v0, t1);

  ASSERT_FALSE(v1.empty());
  ASSERT_EQ(v1.use_count(), 1);
  ASSERT_EQ(v1, t0);

  ASSERT_NE(v0, v1);
}

TEST(LAPlusVectorf, Level1BLAS_SWAPWindow) {
  std::vector<float> t0 = {1, 2, 3, 4, 5, 6};
  std::vector<float> t1 = {1, 2, 3, 4, 5, 6};
  std::vector<float> t2 = {1, 3, 5};
  std::vector<float> t3 = {2, 4, 6};
  std::vector<float> t4 = {2, 2, 4, 4, 6, 6};
  std::vector<float> t5 = {1, 1, 3, 3, 5, 5};

  Vectorf v0(t0);
  Vectorf v1(t1);
  Vectorf v2(v0, 0, 2, 3);
  Vectorf v3(v1, 1, 2, 3);

  ASSERT_FALSE(v0.empty());
  ASSERT_EQ(v0.use_count(), 2);
  ASSERT_EQ(v0, t0);

  ASSERT_FALSE(v1.empty());
  ASSERT_EQ(v1.use_count(), 2);
  ASSERT_EQ(v1, t1);

  ASSERT_FALSE(v2.empty());
  ASSERT_EQ(v2.use_count(), 2);
  ASSERT_EQ(v2, t2);

  ASSERT_FALSE(v3.empty());
  ASSERT_EQ(v3.use_count(), 2);
  ASSERT_EQ(v3, t3);

  ASSERT_EQ(v0.get(), v2.get());
  ASSERT_EQ(v1.get(), v3.get());
  ASSERT_NE(v0.get(), v1.get());
  ASSERT_NE(v2.get(), v3.get());

  v2.swap(v3);

  ASSERT_FALSE(v0.empty());
  ASSERT_EQ(v0.use_count(), 2);
  ASSERT_EQ(v0, t4);

  ASSERT_FALSE(v1.empty());
  ASSERT_EQ(v1.use_count(), 2);
  ASSERT_EQ(v1, t5);

  ASSERT_FALSE(v2.empty());
  ASSERT_EQ(v2.use_count(), 2);
  ASSERT_EQ(v2, t3);

  ASSERT_FALSE(v3.empty());
  ASSERT_EQ(v3.use_count(), 2);
  ASSERT_EQ(v3, t2);

  ASSERT_EQ(v0.get(), v2.get());
  ASSERT_EQ(v1.get(), v3.get());
  ASSERT_NE(v0.get(), v1.get());
  ASSERT_NE(v2.get(), v3.get());
}

TEST(LAPlusVectorf, Level1BLAS_SCAL) {
  std::vector<float> t0 = {1, 2, 3};
  std::vector<float> t1 = {2, 4, 6};

  Vectorf v0(t0);

  ASSERT_FALSE(v0.empty());
  ASSERT_EQ(v0.use_count(), 1);
  ASSERT_EQ(v0, t0);

  v0.scal(2.);

  ASSERT_FALSE(v0.empty());
  ASSERT_EQ(v0.use_count(), 1);
  ASSERT_EQ(v0, t1);
}

TEST(LAPlusVectorf, Level1BLAS_SCALWindow) {
  std::vector<float> t0 = {1, 2, 3, 4, 5, 6};
  std::vector<float> t1 = {1, 3, 5};
  std::vector<float> t2 = {2, 2, 6, 4, 10, 6};
  std::vector<float> t3 = {2, 6, 10};

  Vectorf v0(t0);
  Vectorf v1(v0, 0, 2, 3);

  ASSERT_FALSE(v0.empty());
  ASSERT_EQ(v0.use_count(), 2);
  ASSERT_EQ(v0, t0);

  ASSERT_FALSE(v1.empty());
  ASSERT_EQ(v1.use_count(), 2);
  ASSERT_EQ(v1, t1);

  v1.scal(2.);

  ASSERT_FALSE(v0.empty());
  ASSERT_EQ(v0.use_count(), 2);
  ASSERT_EQ(v0, t2);

  ASSERT_FALSE(v1.empty());
  ASSERT_EQ(v1.use_count(), 2);
  ASSERT_EQ(v1, t3);
}

TEST(LAPlusVectorf, Level1BLAS_COPY) {
  std::vector<float> t0 = {1, 2, 3};
  std::vector<float> t1 = {2, 4, 6};

  Vectorf v0(t0);
  Vectorf v1(t1);

  ASSERT_FALSE(v0.empty());
  ASSERT_EQ(v0.use_count(), 1);
  ASSERT_EQ(v0, t0);

  ASSERT_FALSE(v1.empty());
  ASSERT_EQ(v1.use_count(), 1);
  ASSERT_EQ(v1, t1);

  v1.copy(v0);

  ASSERT_FALSE(v0.empty());
  ASSERT_EQ(v0.use_count(), 1);
  ASSERT_EQ(v0, t0);

  ASSERT_FALSE(v1.empty());
  ASSERT_EQ(v1.use_count(), 1);
  ASSERT_EQ(v1, t0);
}

TEST(LAPlusVectorf, Level1BLAS_COPYWindow) {
  std::vector<float> t0 = {1, 2, 3, 4, 5, 6};
  std::vector<float> t1 = {1, 3, 5};
  std::vector<float> t2 = {0, 0, 0};

  Vectorf v0(t0);
  Vectorf v1(v0, 0, 2, 3);
  Vectorf v2(3);

  ASSERT_FALSE(v0.empty());
  ASSERT_EQ(v0.use_count(), 2);
  ASSERT_EQ(v0, t0);

  ASSERT_FALSE(v1.empty());
  ASSERT_EQ(v1.use_count(), 2);
  ASSERT_EQ(v1, t1);

  ASSERT_FALSE(v2.empty());
  ASSERT_EQ(v2.use_count(), 1);
  ASSERT_EQ(v2, t2);

  v2.copy(v1);

  ASSERT_FALSE(v0.empty());
  ASSERT_EQ(v0.use_count(), 2);
  ASSERT_EQ(v0, t0);

  ASSERT_FALSE(v1.empty());
  ASSERT_EQ(v1.use_count(), 2);
  ASSERT_EQ(v1, t1);

  ASSERT_FALSE(v2.empty());
  ASSERT_EQ(v2.use_count(), 1);
  ASSERT_EQ(v2, t1);
}

TEST(LAPlusVectorf, Level1BLAS_AXPY) {
  std::vector<float> t0 = {1, 2, 3};
  std::vector<float> t1 = {3, 6, 9};

  Vectorf v0(t0);
  Vectorf v1(t0);

  ASSERT_FALSE(v0.empty());
  ASSERT_EQ(v0.use_count(), 1);
  ASSERT_EQ(v0, t0);

  ASSERT_FALSE(v1.empty());
  ASSERT_EQ(v1.use_count(), 1);
  ASSERT_EQ(v1, t0);

  v1.axpy(2., v0);

  ASSERT_FALSE(v0.empty());
  ASSERT_EQ(v0.use_count(), 1);
  ASSERT_EQ(v0, t0);

  ASSERT_FALSE(v1.empty());
  ASSERT_EQ(v1.use_count(), 1);
  ASSERT_EQ(v1, t1);
}

TEST(LAPlusVectorf, Level1BLAS_AXPYWindow) {
  std::vector<float> t0 = {1, 2, 3, 4, 5, 6};
  std::vector<float> t1 = {1, 3, 5};
  std::vector<float> t2 = {1, 2, 3};
  std::vector<float> t3 = {3, 8, 13};

  Vectorf v0(t0);
  Vectorf v1(v0, 0, 2, 3);
  Vectorf v2(t2);

  ASSERT_FALSE(v0.empty());
  ASSERT_EQ(v0.use_count(), 2);
  ASSERT_EQ(v0, t0);

  ASSERT_FALSE(v1.empty());
  ASSERT_EQ(v1.use_count(), 2);
  ASSERT_EQ(v1, t1);

  ASSERT_FALSE(v2.empty());
  ASSERT_EQ(v2.use_count(), 1);
  ASSERT_EQ(v2, t2);

  v2.axpy(2., v1);

  ASSERT_FALSE(v0.empty());
  ASSERT_EQ(v0.use_count(), 2);
  ASSERT_EQ(v0, t0);

  ASSERT_FALSE(v1.empty());
  ASSERT_EQ(v1.use_count(), 2);
  ASSERT_EQ(v1, t1);

  ASSERT_FALSE(v2.empty());
  ASSERT_EQ(v2.use_count(), 1);
  ASSERT_EQ(v2, t3);
}

TEST(LAPlusVectorf, Level1BLAS_DOT) {
  std::vector<float> t0 = {1, 2, 3};

  Vectorf v0(t0);
  Vectorf v1(t0);

  ASSERT_FALSE(v0.empty());
  ASSERT_EQ(v0.use_count(), 1);
  ASSERT_EQ(v0, t0);

  ASSERT_FALSE(v1.empty());
  ASSERT_EQ(v1.use_count(), 1);
  ASSERT_EQ(v1, t0);

  float f0 = v1.dot(v0);

  ASSERT_FALSE(v0.empty());
  ASSERT_EQ(v0.use_count(), 1);
  ASSERT_EQ(v0, t0);

  ASSERT_FALSE(v1.empty());
  ASSERT_EQ(v1.use_count(), 1);
  ASSERT_EQ(v1, t0);

  ASSERT_FLOAT_EQ(f0, 14);
}

TEST(LAPlusVectorf, Level1BLAS_NRM2) {
  std::vector<float> t0 = {1, 2, 3};
  Vectorf v0(t0);

  ASSERT_FALSE(v0.empty());
  ASSERT_EQ(v0.use_count(), 1);
  ASSERT_EQ(v0, t0);

  float f0 = v0.nrm2();

  ASSERT_FALSE(v0.empty());
  ASSERT_EQ(v0.use_count(), 1);
  ASSERT_EQ(v0, t0);

  ASSERT_FLOAT_EQ(f0, 3.741657);
}

TEST(LAPlusVectorf, Level1BLAS_ASUM) {
  std::vector<float> t0 = {1, 2, 3};
  Vectorf v0(t0);

  ASSERT_FALSE(v0.empty());
  ASSERT_EQ(v0.use_count(), 1);
  ASSERT_EQ(v0, t0);

  float f0 = v0.asum();

  ASSERT_FALSE(v0.empty());
  ASSERT_EQ(v0.use_count(), 1);
  ASSERT_EQ(v0, t0);

  ASSERT_FLOAT_EQ(f0, 6);
}

TEST(LAPlusVectorf, Level1BLAS_IAMAX) {
  std::vector<float> t0 = {1, 2, 3};
  Vectorf v0(t0);

  ASSERT_FALSE(v0.empty());
  ASSERT_EQ(v0.use_count(), 1);
  ASSERT_EQ(v0, t0);

  std::size_t s0 = v0.iamax();

  ASSERT_FALSE(v0.empty());
  ASSERT_EQ(v0.use_count(), 1);
  ASSERT_EQ(v0, t0);

  ASSERT_EQ(s0, 2);
}

TEST(LAPlusVectorf, MulInplace) {
  Vectorf v0({1, 2, 3, 4, 5, 6});
  Vectorf v1({1, 2, 3, 4, 5, 6});
  std::vector<float> t0({1, 2, 3, 4, 5, 6});
  std::vector<float> t1({1, 4, 9, 16, 25, 36});

  ASSERT_EQ(v0, t0);
  ASSERT_EQ(v1, t0);
  ASSERT_EQ(v0.use_count(), 1);
  ASSERT_EQ(v1.use_count(), 1);

  v1.mul_inplace(v0);

  ASSERT_EQ(v0, t0);
  ASSERT_EQ(v1, t1);
  ASSERT_EQ(v0.use_count(), 1);
  ASSERT_EQ(v1.use_count(), 1);
}

TEST(LAPlusVectorf, DivInplace) {
  Vectorf v0({1, 2, 3, 4, 5, 6});
  Vectorf v1({1, 2, 3, 4, 5, 6});
  std::vector<float> t0({1, 2, 3, 4, 5, 6});
  std::vector<float> t1({1, 1, 1, 1, 1, 1});

  ASSERT_EQ(v0, t0);
  ASSERT_EQ(v1, t0);
  ASSERT_EQ(v0.use_count(), 1);
  ASSERT_EQ(v1.use_count(), 1);

  v1.div_inplace(v0);

  ASSERT_EQ(v0, t0);
  ASSERT_EQ(v1, t1);
  ASSERT_EQ(v0.use_count(), 1);
  ASSERT_EQ(v1.use_count(), 1);
}

TEST(LAPlusVectorf, PowInplace) {
  Vectorf v0({1, 2, 3, 4, 5, 6});
  Vectorf v1({2, 2, 2, 2, 2, 2});
  std::vector<float> t0({1, 2, 3, 4, 5, 6});
  std::vector<float> t1({2, 2, 2, 2, 2, 2});
  std::vector<float> t2({2, 4, 8, 16, 32, 64});

  ASSERT_EQ(v0, t0);
  ASSERT_EQ(v1, t1);
  ASSERT_EQ(v0.use_count(), 1);
  ASSERT_EQ(v1.use_count(), 1);

  v1.pow_inplace(v0);

  ASSERT_EQ(v0, t0);
  ASSERT_EQ(v1, t2);
  ASSERT_EQ(v0.use_count(), 1);
  ASSERT_EQ(v1.use_count(), 1);
}

TEST(LAPlusVectorf, AddInplaceFloat) {
  Vectorf v0({1, 2, 3, 4, 5, 6});
  std::vector<float> t0({1, 2, 3, 4, 5, 6});
  std::vector<float> t1({2, 3, 4, 5, 6, 7});

  ASSERT_EQ(v0, t0);
  ASSERT_EQ(v0.use_count(), 1);

  v0.add_inplace(1.);

  ASSERT_EQ(v0, t1);
  ASSERT_EQ(v0.use_count(), 1);
}

TEST(LAPlusVectorf, SubInplaceFloat) {
  Vectorf v0({1, 2, 3, 4, 5, 6});
  std::vector<float> t0({1, 2, 3, 4, 5, 6});
  std::vector<float> t1({0, 1, 2, 3, 4, 5});

  ASSERT_EQ(v0, t0);
  ASSERT_EQ(v0.use_count(), 1);

  v0.sub_inplace(1.);

  ASSERT_EQ(v0, t1);
  ASSERT_EQ(v0.use_count(), 1);
}

TEST(LAPlusVectorf, MulInplaceFloat) {
  Vectorf v0({1, 2, 3, 4, 5, 6});
  std::vector<float> t0({1, 2, 3, 4, 5, 6});
  std::vector<float> t1({2, 4, 6, 8, 10, 12});

  ASSERT_EQ(v0, t0);
  ASSERT_EQ(v0.use_count(), 1);

  v0.mul_inplace(2.);

  ASSERT_EQ(v0, t1);
  ASSERT_EQ(v0.use_count(), 1);
}

TEST(LAPlusVectorf, DivInplaceFloat) {
  Vectorf v0({1, 2, 3, 4, 5, 6});
  std::vector<float> t0({1, 2, 3, 4, 5, 6});
  std::vector<float> t1({.5, 1, 1.5, 2, 2.5, 3});

  ASSERT_EQ(v0, t0);
  ASSERT_EQ(v0.use_count(), 1);

  v0.div_inplace(2.);

  ASSERT_EQ(v0, t1);
  ASSERT_EQ(v0.use_count(), 1);
}

TEST(LAPlusVectorf, PowInplaceFloat) {
  Vectorf v0({1, 2, 3, 4, 5, 6});
  std::vector<float> t0({1, 2, 3, 4, 5, 6});
  std::vector<float> t1({1, 4, 9, 16, 25, 36});

  ASSERT_EQ(v0, t0);
  ASSERT_EQ(v0.use_count(), 1);

  v0.pow_inplace(2.);

  ASSERT_EQ(v0, t1);
  ASSERT_EQ(v0.use_count(), 1);
}

TEST(LAPlusVectorf, Mul) {
  Vectorf v0({1, 2, 3, 4, 5, 6});
  Vectorf v1({1, 2, 3, 4, 5, 6});
  Vectorf v2(6);
  std::vector<float> t0({1, 2, 3, 4, 5, 6});
  std::vector<float> t1({0, 0, 0, 0, 0, 0});
  std::vector<float> t2({1, 4, 9, 16, 25, 36});

  ASSERT_EQ(v0, t0);
  ASSERT_EQ(v1, t0);
  ASSERT_EQ(v2, t1);
  ASSERT_EQ(v0.use_count(), 1);
  ASSERT_EQ(v1.use_count(), 1);
  ASSERT_EQ(v2.use_count(), 1);

  v2 = v1.mul(v0);

  ASSERT_EQ(v0, t0);
  ASSERT_EQ(v1, t0);
  ASSERT_EQ(v2, t2);
  ASSERT_EQ(v0.use_count(), 1);
  ASSERT_EQ(v1.use_count(), 1);
  ASSERT_EQ(v2.use_count(), 1);
}

TEST(LAPlusVectorf, Div) {
  Vectorf v0({1, 2, 3, 4, 5, 6});
  Vectorf v1({1, 2, 3, 4, 5, 6});
  Vectorf v2(6);
  std::vector<float> t0({1, 2, 3, 4, 5, 6});
  std::vector<float> t1({0, 0, 0, 0, 0, 0});
  std::vector<float> t2({1, 1, 1, 1, 1, 1});

  ASSERT_EQ(v0, t0);
  ASSERT_EQ(v1, t0);
  ASSERT_EQ(v2, t1);
  ASSERT_EQ(v0.use_count(), 1);
  ASSERT_EQ(v1.use_count(), 1);
  ASSERT_EQ(v2.use_count(), 1);

  v2 = v1.div(v0);

  ASSERT_EQ(v0, t0);
  ASSERT_EQ(v1, t0);
  ASSERT_EQ(v2, t2);
  ASSERT_EQ(v0.use_count(), 1);
  ASSERT_EQ(v1.use_count(), 1);
  ASSERT_EQ(v2.use_count(), 1);
}

TEST(LAPlusVectorf, Pow) {
  Vectorf v0({1, 2, 3, 4, 5, 6});
  Vectorf v1({2, 2, 2, 2, 2, 2});
  Vectorf v2(6);
  std::vector<float> t0({1, 2, 3, 4, 5, 6});
  std::vector<float> t1({2, 2, 2, 2, 2, 2});
  std::vector<float> t2({0, 0, 0, 0, 0, 0});
  std::vector<float> a3({2, 4, 8, 16, 32, 64});

  ASSERT_EQ(v0, t0);
  ASSERT_EQ(v1, t1);
  ASSERT_EQ(v2, t2);
  ASSERT_EQ(v0.use_count(), 1);
  ASSERT_EQ(v1.use_count(), 1);
  ASSERT_EQ(v2.use_count(), 1);

  v2 = v1.pow(v0);

  ASSERT_EQ(v0, t0);
  ASSERT_EQ(v1, t1);
  ASSERT_EQ(v2, a3);
  ASSERT_EQ(v0.use_count(), 1);
  ASSERT_EQ(v1.use_count(), 1);
  ASSERT_EQ(v2.use_count(), 1);
}

TEST(LAPlusVectorf, AddFloat) {
  Vectorf v0({1, 2, 3, 4, 5, 6});
  Vectorf v1(6);
  std::vector<float> t0({1, 2, 3, 4, 5, 6});
  std::vector<float> t1({0, 0, 0, 0, 0, 0});
  std::vector<float> t2({2, 3, 4, 5, 6, 7});

  ASSERT_EQ(v0, t0);
  ASSERT_EQ(v1, t1);
  ASSERT_EQ(v0.use_count(), 1);
  ASSERT_EQ(v1.use_count(), 1);

  v1 = v0.add(1.);

  ASSERT_EQ(v0, t0);
  ASSERT_EQ(v1, t2);
  ASSERT_EQ(v0.use_count(), 1);
  ASSERT_EQ(v1.use_count(), 1);
}

TEST(LAPlusVectorf, SubFloat) {
  Vectorf v0({1, 2, 3, 4, 5, 6});
  Vectorf v1(6);
  std::vector<float> t0({1, 2, 3, 4, 5, 6});
  std::vector<float> t1({0, 0, 0, 0, 0, 0});
  std::vector<float> t2({0, 1, 2, 3, 4, 5});

  ASSERT_EQ(v0, t0);
  ASSERT_EQ(v1, t1);
  ASSERT_EQ(v0.use_count(), 1);
  ASSERT_EQ(v1.use_count(), 1);

  v1 = v0.sub(1.);

  ASSERT_EQ(v0, t0);
  ASSERT_EQ(v1, t2);
  ASSERT_EQ(v0.use_count(), 1);
  ASSERT_EQ(v1.use_count(), 1);
}

TEST(LAPlusVectorf, MulFloat) {
  Vectorf v0({1, 2, 3, 4, 5, 6});
  Vectorf v1(6);
  std::vector<float> t0({1, 2, 3, 4, 5, 6});
  std::vector<float> t1({0, 0, 0, 0, 0, 0});
  std::vector<float> t2({2, 4, 6, 8, 10, 12});

  ASSERT_EQ(v0, t0);
  ASSERT_EQ(v1, t1);
  ASSERT_EQ(v0.use_count(), 1);
  ASSERT_EQ(v1.use_count(), 1);

  v1 = v0.mul(2.);

  ASSERT_EQ(v0, t0);
  ASSERT_EQ(v1, t2);
  ASSERT_EQ(v0.use_count(), 1);
  ASSERT_EQ(v1.use_count(), 1);
}

TEST(LAPlusVectorf, DivFloat) {
  Vectorf v0({1, 2, 3, 4, 5, 6});
  Vectorf v1(6);
  std::vector<float> t0({1, 2, 3, 4, 5, 6});
  std::vector<float> t1({0, 0, 0, 0, 0, 0});
  std::vector<float> t2({.5, 1, 1.5, 2, 2.5, 3});

  ASSERT_EQ(v0, t0);
  ASSERT_EQ(v1, t1);
  ASSERT_EQ(v0.use_count(), 1);
  ASSERT_EQ(v1.use_count(), 1);

  v1 = v0.div(2.);

  ASSERT_EQ(v0, t0);
  ASSERT_EQ(v1, t2);
  ASSERT_EQ(v0.use_count(), 1);
  ASSERT_EQ(v1.use_count(), 1);
}

TEST(LAPlusVectorf, PowFloat) {
  Vectorf v0({1, 2, 3, 4, 5, 6});
  Vectorf v1(6);
  std::vector<float> t0({1, 2, 3, 4, 5, 6});
  std::vector<float> t1({0, 0, 0, 0, 0, 0});
  std::vector<float> t2({1, 4, 9, 16, 25, 36});

  ASSERT_EQ(v0, t0);
  ASSERT_EQ(v1, t1);
  ASSERT_EQ(v0.use_count(), 1);
  ASSERT_EQ(v1.use_count(), 1);

  v1 = v0.pow(2.);

  ASSERT_EQ(v0, t0);
  ASSERT_EQ(v1, t2);
  ASSERT_EQ(v0.use_count(), 1);
  ASSERT_EQ(v1.use_count(), 1);
}

float square(float v) { return v * v; }

TEST(LAPlusVectorf, ApplyInplace) {
  Vectorf v0({1, 2, 3, 4, 5, 6});
  std::vector<float> t0({1, 2, 3, 4, 5, 6});
  std::vector<float> t1({1, 4, 9, 16, 25, 36});

  ASSERT_EQ(v0, t0);
  ASSERT_EQ(v0.use_count(), 1);

  v0.apply_inplace(square);

  ASSERT_EQ(v0, t1);
  ASSERT_EQ(v0.use_count(), 1);
}

TEST(LAPlusVectorf, Apply) {
  Vectorf v0({1, 2, 3, 4, 5, 6});
  Vectorf v1(6);
  std::vector<float> t0({1, 2, 3, 4, 5, 6});
  std::vector<float> t1({0, 0, 0, 0, 0, 0});
  std::vector<float> t2({1, 4, 9, 16, 25, 36});

  ASSERT_EQ(v0, t0);
  ASSERT_EQ(v1, t1);
  ASSERT_EQ(v0.use_count(), 1);
  ASSERT_EQ(v1.use_count(), 1);

  v1 = v0.apply(square);

  ASSERT_EQ(v0, t0);
  ASSERT_EQ(v1, t2);
  ASSERT_EQ(v0.use_count(), 1);
  ASSERT_EQ(v1.use_count(), 1);
}

TEST(LAPlusVectorf, maxCoeff) {
  Vectorf v0({1, 2, 3, 2, 1});
  std::vector<float> t0({1, 2, 3, 2, 1});

  ASSERT_EQ(v0, t0);
  ASSERT_EQ(v0.use_count(), 1);

  float f0 = v0.maxCoeff();

  ASSERT_EQ(v0, t0);
  ASSERT_EQ(v0.use_count(), 1);
  ASSERT_FLOAT_EQ(f0, 3);
}

TEST(LAPlusVectorf, minCoeff) {
  Vectorf v0({-1, -2, -3, -2, -1});
  std::vector<float> t0({-1, -2, -3, -2, -1});

  ASSERT_EQ(v0, t0);
  ASSERT_EQ(v0.use_count(), 1);

  float f0 = v0.minCoeff();

  ASSERT_EQ(v0, t0);
  ASSERT_EQ(v0.use_count(), 1);
  ASSERT_FLOAT_EQ(f0, -3);
}

TEST(LAPlusVectorf, maxCoeffIndex) {
  Vectorf v0({1, 2, 3, 2, 1});
  std::vector<float> t0({1, 2, 3, 2, 1});

  ASSERT_EQ(v0, t0);
  ASSERT_EQ(v0.use_count(), 1);

  std::size_t s0;
  float f0 = v0.maxCoeff(s0);

  ASSERT_EQ(v0, t0);
  ASSERT_EQ(v0.use_count(), 1);
  ASSERT_EQ(s0, 2);
  ASSERT_FLOAT_EQ(f0, 3);
}

TEST(LAPlusVectorf, minCoeffIndex) {
  Vectorf v0({-1, -2, -3, -2, -1});
  std::vector<float> t0({-1, -2, -3, -2, -1});

  ASSERT_EQ(v0, t0);
  ASSERT_EQ(v0.use_count(), 1);

  std::size_t s0;
  float f0 = v0.minCoeff(s0);

  ASSERT_EQ(v0, t0);
  ASSERT_EQ(v0.use_count(), 1);
  ASSERT_EQ(s0, 2);
  ASSERT_FLOAT_EQ(f0, -3);
}

}  // namespace laplus
