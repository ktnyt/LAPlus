/******************************************************************************
 *
 * laplus.cpp
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

#include "laplus.hpp"
#include "gtest/gtest.h"

namespace laplus {
namespace test {

TEST(ArrayConstructor, Default)
{
  Array<3, 2> t0;
  std::array<float, 6> a0({0, 0, 0, 0, 0, 0});

  ASSERT_EQ(t0, a0);
}

TEST(ArrayConstructor, StdArray)
{
  Array<3, 2> t0({1, 2, 3, 4, 5, 6});
  std::array<float, 6> a0({1, 2, 3, 4, 5, 6});

  ASSERT_EQ(t0, a0);
}

TEST(ArrayConstructor, Copy)
{
  Array<3, 2> t0({1, 2, 3, 4, 5, 6});
  std::array<float, 6> a0({1, 2, 3, 4, 5, 6});

  ASSERT_EQ(t0, a0);
  ASSERT_EQ(t0.use_count(), 1);

  {
    Array<3, 2> t1(t0);
    ASSERT_EQ(t0.use_count(), 2);
    ASSERT_EQ(t1.use_count(), 2);
    ASSERT_EQ(t1, a0);
  }

  ASSERT_EQ(t0.use_count(), 1);
}

TEST(ArrayConstructor, Move)
{
  Array<3, 2> t0(Array<3, 2>({1, 2, 3, 4, 5, 6}));
  std::array<float, 6> a0({1, 2, 3, 4, 5, 6});

  ASSERT_EQ(t0, a0);
  ASSERT_EQ(t0.use_count(), 1);
}

TEST(ArrayAssignmentOperator, Copy)
{
  Array<3, 2> t0({1, 2, 3, 4, 5, 6});
  std::array<float, 6> a0({1, 2, 3, 4, 5, 6});

  ASSERT_EQ(t0, a0);
  ASSERT_EQ(t0.use_count(), 1);

  {
    Array<3, 2> t1 = t0;
    ASSERT_EQ(t0.use_count(), 2);
    ASSERT_EQ(t1.use_count(), 2);
    ASSERT_EQ(t1, a0);
  }

  {
    Array<3, 2> t1;
    ASSERT_EQ(t1.use_count(), 1);
    t1 = t0;
    ASSERT_EQ(t0.use_count(), 2);
    ASSERT_EQ(t1.use_count(), 2);
    ASSERT_EQ(t1, a0);
  }

  ASSERT_EQ(t0.use_count(), 1);
}

TEST(ArrayAssignmentOperator, Move)
{
  Array<3, 2> t0 = Array<3, 2>({1, 2, 3, 4, 5, 6});
  std::array<float, 6> a0({1, 2, 3, 4, 5, 6});

  ASSERT_EQ(t0, a0);
  ASSERT_EQ(t0.use_count(), 1);
}

TEST(ArrayAssignmentOperator, Add)
{
  Array<3, 2> t0({1, 2, 3, 4, 5, 6});
  Array<3, 2> t1({1, 2, 3, 4, 5, 6});
  std::array<float, 6> a0({1, 2, 3, 4, 5, 6});
  std::array<float, 6> a1({2, 4, 6, 8, 10, 12});

  ASSERT_EQ(t0, a0);
  ASSERT_EQ(t1, a0);
  ASSERT_EQ(t0.use_count(), 1);
  ASSERT_EQ(t1.use_count(), 1);

  t1 += t0;

  ASSERT_EQ(t0, a0);
  ASSERT_EQ(t1, a1);
  ASSERT_EQ(t0.use_count(), 1);
  ASSERT_EQ(t1.use_count(), 1);
}

TEST(ArrayAssignmentOperator, Sub)
{
  Array<3, 2> t0({1, 2, 3, 4, 5, 6});
  Array<3, 2> t1({1, 2, 3, 4, 5, 6});
  std::array<float, 6> a0({1, 2, 3, 4, 5, 6});
  std::array<float, 6> a1({0, 0, 0, 0, 0, 0});

  ASSERT_EQ(t0, a0);
  ASSERT_EQ(t1, a0);
  ASSERT_EQ(t0.use_count(), 1);
  ASSERT_EQ(t1.use_count(), 1);

  t1 -= t0;

  ASSERT_EQ(t0, a0);
  ASSERT_EQ(t1, a1);
  ASSERT_EQ(t0.use_count(), 1);
  ASSERT_EQ(t1.use_count(), 1);
}

TEST(ArrayAssignmentOperator, Mul)
{
  Array<3, 2> t0({1, 2, 3, 4, 5, 6});
  Array<3, 2> t1({1, 2, 3, 4, 5, 6});
  std::array<float, 6> a0({1, 2, 3, 4, 5, 6});
  std::array<float, 6> a1({1, 4, 9, 16, 25, 36});

  ASSERT_EQ(t0, a0);
  ASSERT_EQ(t1, a0);
  ASSERT_EQ(t0.use_count(), 1);
  ASSERT_EQ(t1.use_count(), 1);

  t1 *= t0;

  ASSERT_EQ(t0, a0);
  ASSERT_EQ(t1, a1);
  ASSERT_EQ(t0.use_count(), 1);
  ASSERT_EQ(t1.use_count(), 1);
}

TEST(ArrayAssignmentOperator, MulFloat)
{
  Array<3, 2> t0({1, 2, 3, 4, 5, 6});
  std::array<float, 6> a0({1, 2, 3, 4, 5, 6});
  std::array<float, 6> a1({2, 4, 6, 8, 10, 12});

  ASSERT_EQ(t0, a0);
  ASSERT_EQ(t0.use_count(), 1);

  t0 *= 2;

  ASSERT_EQ(t0, a1);
  ASSERT_EQ(t0.use_count(), 1);
}

TEST(ArrayAssignmentOperator, Div)
{
  Array<3, 2> t0({1, 2, 3, 4, 5, 6});
  Array<3, 2> t1({1, 2, 3, 4, 5, 6});
  std::array<float, 6> a0({1, 2, 3, 4, 5, 6});
  std::array<float, 6> a1({1, 1, 1, 1, 1, 1});

  ASSERT_EQ(t0, a0);
  ASSERT_EQ(t1, a0);
  ASSERT_EQ(t0.use_count(), 1);
  ASSERT_EQ(t1.use_count(), 1);

  t1 /= t0;

  ASSERT_EQ(t0, a0);
  ASSERT_EQ(t1, a1);
  ASSERT_EQ(t0.use_count(), 1);
  ASSERT_EQ(t1.use_count(), 1);
}

TEST(ArrayAssignmentOperator, DivFloat)
{
  Array<3, 2> t0({1, 2, 3, 4, 5, 6});
  std::array<float, 6> a0({1, 2, 3, 4, 5, 6});
  std::array<float, 6> a1({.5, 1, 1.5, 2, 2.5, 3});

  ASSERT_EQ(t0, a0);
  ASSERT_EQ(t0.use_count(), 1);

  t0 /= 2.0;

  ASSERT_EQ(t0, a1);
  ASSERT_EQ(t0.use_count(), 1);
}

TEST(ArrayAssignmentOperator, Pow)
{
  Array<3, 2> t0({1, 2, 3, 4, 5, 6});
  Array<3, 2> t1({2, 2, 2, 2, 2, 2});
  std::array<float, 6> a0({1, 2, 3, 4, 5, 6});
  std::array<float, 6> a1({2, 4, 8, 16, 32, 64});
  std::array<float, 6> a2({2, 2, 2, 2, 2, 2});

  ASSERT_EQ(t0, a0);
  ASSERT_EQ(t1, a2);
  ASSERT_EQ(t0.use_count(), 1);
  ASSERT_EQ(t1.use_count(), 1);

  t1 ^= t0;

  ASSERT_EQ(t0, a0);
  ASSERT_EQ(t1, a1);
  ASSERT_EQ(t0.use_count(), 1);
  ASSERT_EQ(t1.use_count(), 1);
}

TEST(ArrayAssignmentOperator, PowFloat)
{
  Array<3, 2> t0({1, 2, 3, 4, 5, 6});
  std::array<float, 6> a0({1, 2, 3, 4, 5, 6});
  std::array<float, 6> a1({1, 4, 9, 16, 25, 36});

  ASSERT_EQ(t0, a0);
  ASSERT_EQ(t0.use_count(), 1);

  t0 ^= 2.0;

  ASSERT_EQ(t0, a1);
  ASSERT_EQ(t0.use_count(), 1);
}

TEST(ArrayArithmeticOperator, Add)
{
  Array<3, 2> t0({1, 2, 3, 4, 5, 6});
  Array<3, 2> t1({1, 2, 3, 4, 5, 6});
  Array<3, 2> t2;
  std::array<float, 6> a0({1, 2, 3, 4, 5, 6});
  std::array<float, 6> a1({0, 0, 0, 0, 0, 0});
  std::array<float, 6> a2({2, 4, 6, 8, 10, 12});

  ASSERT_EQ(t0, a0);
  ASSERT_EQ(t1, a0);
  ASSERT_EQ(t2, a1);
  ASSERT_EQ(t0.use_count(), 1);
  ASSERT_EQ(t1.use_count(), 1);
  ASSERT_EQ(t2.use_count(), 1);

  t2 = t1 + t0;

  ASSERT_EQ(t0, a0);
  ASSERT_EQ(t1, a0);
  ASSERT_EQ(t2, a2);
  ASSERT_EQ(t0.use_count(), 1);
  ASSERT_EQ(t1.use_count(), 1);
  ASSERT_EQ(t2.use_count(), 1);
}

TEST(ArrayArithmeticOperator, Sub)
{
  Array<3, 2> t0({1, 2, 3, 4, 5, 6});
  Array<3, 2> t1({0, 0, 0, 0, 0, 0});
  Array<3, 2> t2;
  std::array<float, 6> a0({1, 2, 3, 4, 5, 6});
  std::array<float, 6> a1({0, 0, 0, 0, 0, 0});
  std::array<float, 6> a2({-1, -2, -3, -4, -5, -6});

  ASSERT_EQ(t0, a0);
  ASSERT_EQ(t1, a1);
  ASSERT_EQ(t2, a1);
  ASSERT_EQ(t0.use_count(), 1);
  ASSERT_EQ(t1.use_count(), 1);
  ASSERT_EQ(t2.use_count(), 1);

  t2 = t1 - t0;

  ASSERT_EQ(t0, a0);
  ASSERT_EQ(t1, a1);
  ASSERT_EQ(t2, a2);
  ASSERT_EQ(t0.use_count(), 1);
  ASSERT_EQ(t1.use_count(), 1);
  ASSERT_EQ(t2.use_count(), 1);
}

TEST(ArrayArithmeticOperator, Mul)
{
  Array<3, 2> t0({1, 2, 3, 4, 5, 6});
  Array<3, 2> t1({1, 2, 3, 4, 5, 6});
  Array<3, 2> t2;
  std::array<float, 6> a0({1, 2, 3, 4, 5, 6});
  std::array<float, 6> a1({0, 0, 0, 0, 0, 0});
  std::array<float, 6> a2({1, 4, 9, 16, 25, 36});

  ASSERT_EQ(t0, a0);
  ASSERT_EQ(t1, a0);
  ASSERT_EQ(t2, a1);
  ASSERT_EQ(t0.use_count(), 1);
  ASSERT_EQ(t1.use_count(), 1);
  ASSERT_EQ(t2.use_count(), 1);

  t2 = t1 * t0;

  ASSERT_EQ(t0, a0);
  ASSERT_EQ(t1, a0);
  ASSERT_EQ(t2, a2);
  ASSERT_EQ(t0.use_count(), 1);
  ASSERT_EQ(t1.use_count(), 1);
  ASSERT_EQ(t2.use_count(), 1);
}

TEST(ArrayArithmeticOperator, MulFloatR)
{
  Array<3, 2> t0({1, 2, 3, 4, 5, 6});
  Array<3, 2> t1;
  std::array<float, 6> a0({1, 2, 3, 4, 5, 6});
  std::array<float, 6> a1({0, 0, 0, 0, 0, 0});
  std::array<float, 6> a2({2, 4, 6, 8, 10, 12});

  ASSERT_EQ(t0, a0);
  ASSERT_EQ(t1, a1);
  ASSERT_EQ(t0.use_count(), 1);
  ASSERT_EQ(t1.use_count(), 1);

  t1 = t0 * 2;

  ASSERT_EQ(t0, a0);
  ASSERT_EQ(t1, a2);
  ASSERT_EQ(t0.use_count(), 1);
  ASSERT_EQ(t1.use_count(), 1);
}

TEST(ArrayArithmeticOperator, MulFloatL)
{
  Array<3, 2> t0({1, 2, 3, 4, 5, 6});
  Array<3, 2> t1;
  std::array<float, 6> a0({1, 2, 3, 4, 5, 6});
  std::array<float, 6> a1({0, 0, 0, 0, 0, 0});
  std::array<float, 6> a2({2, 4, 6, 8, 10, 12});

  ASSERT_EQ(t0, a0);
  ASSERT_EQ(t1, a1);
  ASSERT_EQ(t0.use_count(), 1);
  ASSERT_EQ(t1.use_count(), 1);

  t1 = 2 * t0;

  ASSERT_EQ(t0, a0);
  ASSERT_EQ(t1, a2);
  ASSERT_EQ(t0.use_count(), 1);
  ASSERT_EQ(t1.use_count(), 1);
}

TEST(ArrayArithmeticOperator, Div)
{
  Array<3, 2> t0({1, 2, 3, 4, 5, 6});
  Array<3, 2> t1({1, 2, 3, 4, 5, 6});
  Array<3, 2> t2;
  std::array<float, 6> a0({1, 2, 3, 4, 5, 6});
  std::array<float, 6> a1({0, 0, 0, 0, 0, 0});
  std::array<float, 6> a2({1, 1, 1, 1, 1, 1});

  ASSERT_EQ(t0, a0);
  ASSERT_EQ(t1, a0);
  ASSERT_EQ(t2, a1);
  ASSERT_EQ(t0.use_count(), 1);
  ASSERT_EQ(t1.use_count(), 1);
  ASSERT_EQ(t2.use_count(), 1);

  t2 = t1 / t0;

  ASSERT_EQ(t0, a0);
  ASSERT_EQ(t1, a0);
  ASSERT_EQ(t2, a2);
  ASSERT_EQ(t0.use_count(), 1);
  ASSERT_EQ(t1.use_count(), 1);
  ASSERT_EQ(t2.use_count(), 1);
}

TEST(ArrayArithmeticOperator, DivFloat)
{
  Array<3, 2> t0({1, 2, 3, 4, 5, 6});
  Array<3, 2> t1;
  std::array<float, 6> a0({1, 2, 3, 4, 5, 6});
  std::array<float, 6> a1({0, 0, 0, 0, 0, 0});
  std::array<float, 6> a2({.5, 1, 1.5, 2, 2.5, 3});

  ASSERT_EQ(t0, a0);
  ASSERT_EQ(t1, a1);
  ASSERT_EQ(t0.use_count(), 1);
  ASSERT_EQ(t1.use_count(), 1);

  t1 = t0 / 2.0;

  ASSERT_EQ(t0, a0);
  ASSERT_EQ(t1, a2);
  ASSERT_EQ(t0.use_count(), 1);
  ASSERT_EQ(t1.use_count(), 1);
}

TEST(ArrayArithmeticOperator, Pow)
{
  Array<3, 2> t0({1, 2, 3, 4, 5, 6});
  Array<3, 2> t1({2, 2, 2, 2, 2, 2});
  Array<3, 2> t2;
  std::array<float, 6> a0({1, 2, 3, 4, 5, 6});
  std::array<float, 6> a1({2, 2, 2, 2, 2, 2});
  std::array<float, 6> a2({0, 0, 0, 0, 0, 0});
  std::array<float, 6> a3({2, 4, 8, 16, 32, 64});

  ASSERT_EQ(t0, a0);
  ASSERT_EQ(t1, a1);
  ASSERT_EQ(t2, a2);
  ASSERT_EQ(t0.use_count(), 1);
  ASSERT_EQ(t1.use_count(), 1);
  ASSERT_EQ(t2.use_count(), 1);

  t2 = t1 ^ t0;

  ASSERT_EQ(t0, a0);
  ASSERT_EQ(t1, a1);
  ASSERT_EQ(t2, a3);
  ASSERT_EQ(t0.use_count(), 1);
  ASSERT_EQ(t1.use_count(), 1);
  ASSERT_EQ(t2.use_count(), 1);
}

TEST(ArrayArithmeticOperator, PowFloat)
{
  Array<3, 2> t0({1, 2, 3, 4, 5, 6});
  Array<3, 2> t1;
  std::array<float, 6> a0({1, 2, 3, 4, 5, 6});
  std::array<float, 6> a1({0, 0, 0, 0, 0, 0});
  std::array<float, 6> a2({1, 4, 9, 16, 25, 36});

  ASSERT_EQ(t0, a0);
  ASSERT_EQ(t1, a1);
  ASSERT_EQ(t0.use_count(), 1);
  ASSERT_EQ(t1.use_count(), 1);

  t1 = t0 ^ 2;

  ASSERT_EQ(t0, a0);
  ASSERT_EQ(t1, a2);
  ASSERT_EQ(t0.use_count(), 1);
  ASSERT_EQ(t1.use_count(), 1);
}

TEST(ArrayMemberAccessOperator, Subscript)
{
  Array<3, 2> t0({1, 2, 3, 4, 5, 6});
  std::array<float, 6> a0({1, 2, 3, 4, 5, 6});

  ASSERT_EQ(t0, a0);
  ASSERT_EQ(t0.use_count(), 1);

  {
    Array<2> t1 = t0[0];
    std::array<float, 2> a1({1, 2});
    ASSERT_EQ(t1, a1);
    ASSERT_EQ(t0.use_count(), 2);
    ASSERT_EQ(t1.use_count(), 2);
  }

  ASSERT_EQ(t0.use_count(), 1);

  {
    Array<2> t1 = t0[1];
    std::array<float, 2> a1({3, 4});
    ASSERT_EQ(t1, a1);
    ASSERT_EQ(t0.use_count(), 2);
    ASSERT_EQ(t1.use_count(), 2);
  }

  ASSERT_EQ(t0.use_count(), 1);

  {
    Array<2> t1 = t0[2];
    std::array<float, 2> a1({5, 6});
    ASSERT_EQ(t1, a1);
    ASSERT_EQ(t0.use_count(), 2);
    ASSERT_EQ(t1.use_count(), 2);
  }

  ASSERT_EQ(t0.use_count(), 1);
}

TEST(ArrayMemberAccessOperator, FunctionSingle)
{
  Array<3, 2> t0({1, 2, 3, 4, 5, 6});
  std::array<float, 6> a0({1, 2, 3, 4, 5, 6});

  ASSERT_EQ(t0, a0);
  ASSERT_EQ(t0.use_count(), 1);

  for(std::size_t i = 0; i < 6; ++i) {
    ASSERT_FLOAT_EQ(t0(i), a0[i]);
  }
}

TEST(ArrayMemberAccessOperator, FunctionDouble)
{
  Array<3, 2> t0({1, 2, 3, 4, 5, 6});
  std::array<float, 6> a0({1, 2, 3, 4, 5, 6});

  ASSERT_EQ(t0, a0);
  ASSERT_EQ(t0.use_count(), 1);

  for(std::size_t i = 0; i < 3; ++i) {
    for(std::size_t j = 0; j < 2; ++j) {
      ASSERT_FLOAT_EQ(t0(i, j), a0[2 * i + j]);
    }
  }
}

TEST(ArrayUtilities, Swap)
{
  Array<3, 2> t0({1, 2, 3, 4, 5, 6});
  Array<3, 2> t1({6, 5, 4, 3, 2, 1});
  std::array<float, 6> a0({1, 2, 3, 4, 5, 6});
  std::array<float, 6> a1({6, 5, 4, 3, 2, 1});

  ASSERT_EQ(t0, a0);
  ASSERT_EQ(t1, a1);
  ASSERT_EQ(t0.use_count(), 1);
  ASSERT_EQ(t1.use_count(), 1);

  swap(t0, t1);

  ASSERT_EQ(t0, a1);
  ASSERT_EQ(t1, a0);
  ASSERT_EQ(t0.use_count(), 1);
  ASSERT_EQ(t1.use_count(), 1);
}

TEST(ArrayUtilities, Clone)
{
  Array<3, 2> t0({1, 2, 3, 4, 5, 6});
  Array<3, 2> t1({6, 5, 4, 3, 2, 1});
  std::array<float, 6> a0({1, 2, 3, 4, 5, 6});
  std::array<float, 6> a1({6, 5, 4, 3, 2, 1});

  ASSERT_EQ(t0, a0);
  ASSERT_EQ(t1, a1);
  ASSERT_EQ(t0.use_count(), 1);
  ASSERT_EQ(t1.use_count(), 1);

  t1 = t0.clone();

  ASSERT_EQ(t0, a0);
  ASSERT_EQ(t1, a0);
  ASSERT_EQ(t0.use_count(), 1);
  ASSERT_EQ(t1.use_count(), 1);
}

TEST(ArrayAccessors, Rows)
{
  Array<3, 2> t0({1, 2, 3, 4, 5, 6});

  ASSERT_EQ(t0.rows(), 3);
}

TEST(ArrayAccessors, Cols)
{
  Array<3, 2> t0({1, 2, 3, 4, 5, 6});

  ASSERT_EQ(t0.cols(), 2);
}

TEST(ArrayAccessors, Size)
{
  Array<3, 2> t0({1, 2, 3, 4, 5, 6});

  ASSERT_EQ(t0.size(), 6);
}

TEST(ArrayLevel1BLAS, SCAL)
{
  Array<3, 2> t0({1, 2, 3, 4, 5, 6});
  std::array<float, 6> a0({1, 2, 3, 4, 5, 6});
  std::array<float, 6> a1({2, 4, 6, 8, 10, 12});

  ASSERT_EQ(t0, a0);
  ASSERT_EQ(t0.use_count(), 1);

  t0.scal(2.0);

  ASSERT_EQ(t0, a1);
  ASSERT_EQ(t0.use_count(), 1);
}

TEST(ArrayLevel1BLAS, COPY)
{
  Array<3, 2> t0({1, 2, 3, 4, 5, 6});
  Array<3, 2> t1;
  std::array<float, 6> a0({1, 2, 3, 4, 5, 6});
  std::array<float, 6> a1({0, 0, 0, 0, 0, 0});

  ASSERT_EQ(t0, a0);
  ASSERT_EQ(t1, a1);
  ASSERT_EQ(t0.use_count(), 1);
  ASSERT_EQ(t1.use_count(), 1);

  t1.copy(t0);

  ASSERT_EQ(t0, a0);
  ASSERT_EQ(t1, a0);
  ASSERT_EQ(t0.use_count(), 1);
  ASSERT_EQ(t1.use_count(), 1);
}

TEST(ArrayLevel1BLAS, AXPY)
{
  Array<3, 2> t0({1, 2, 3, 4, 5, 6});
  Array<3, 2> t1({1, 2, 3, 4, 5, 6});
  std::array<float, 6> a0({1, 2, 3, 4, 5, 6});
  std::array<float, 6> a1({3, 6, 9, 12, 15, 18});

  ASSERT_EQ(t0, a0);
  ASSERT_EQ(t1, a0);
  ASSERT_EQ(t0.use_count(), 1);
  ASSERT_EQ(t1.use_count(), 1);

  t1.axpy(2.0, t0);

  ASSERT_EQ(t0, a0);
  ASSERT_EQ(t1, a1);
  ASSERT_EQ(t0.use_count(), 1);
  ASSERT_EQ(t1.use_count(), 1);
}

TEST(ArrayLevel1BLAS, DOT)
{
  Array<3, 2> t0({1, 2, 3, 4, 5, 6});
  Array<3, 2> t1({1, 2, 3, 4, 5, 6});
  std::array<float, 6> a0({1, 2, 3, 4, 5, 6});

  ASSERT_EQ(t0, a0);
  ASSERT_EQ(t1, a0);
  ASSERT_EQ(t0.use_count(), 1);
  ASSERT_EQ(t1.use_count(), 1);

  float f0 = t1.dot(t0);
  float f1 = t0.dot(t1);

  ASSERT_EQ(t0, a0);
  ASSERT_EQ(t1, a0);
  ASSERT_EQ(t0.use_count(), 1);
  ASSERT_EQ(t1.use_count(), 1);

  ASSERT_FLOAT_EQ(f0, 91);
  ASSERT_FLOAT_EQ(f1, 91);
}

TEST(ArrayLevel1BLAS, NORM)
{
  Array<3, 2> t0({1, 2, 3, 4, 5, 6});
  std::array<float, 6> a0({1, 2, 3, 4, 5, 6});

  ASSERT_EQ(t0, a0);
  ASSERT_EQ(t0.use_count(), 1);

  float f0 = t0.norm();

  ASSERT_EQ(t0, a0);
  ASSERT_EQ(t0.use_count(), 1);

  ASSERT_FLOAT_EQ(f0, 9.53939);
}

TEST(ArrayLevel1BLAS, ASUM)
{
  Array<3, 2> t0({1, -2, 3, -4, 5, -6});
  std::array<float, 6> a0({1, -2, 3, -4, 5, -6});

  ASSERT_EQ(t0, a0);
  ASSERT_EQ(t0.use_count(), 1);

  float f0 = t0.asum();

  ASSERT_EQ(t0, a0);
  ASSERT_EQ(t0.use_count(), 1);

  ASSERT_FLOAT_EQ(f0, 21);
}

TEST(ArrayLevel1BLAS, IAMAX)
{
  Array<3, 2> t0({1, -2, 3, -6, 5, -4});
  std::array<float, 6> a0({1, -2, 3, -6, 5, -4});

  ASSERT_EQ(t0, a0);
  ASSERT_EQ(t0.use_count(), 1);

  std::size_t s0 = t0.iamax();

  ASSERT_EQ(t0, a0);
  ASSERT_EQ(t0.use_count(), 1);

  ASSERT_EQ(s0, 3);
}

TEST(ArrayLevel2BLAS, GEMV)
{
  Array<3, 2> t0({1, 2, 3, 4, 5, 6});
  Array<3> t1({1, 2, 3});
  Array<2> t2({1, 2});
  std::array<float, 6> a0({1, 2, 3, 4, 5, 6});
  std::array<float, 3> a1({1, 2, 3});
  std::array<float, 2> a2({1, 2});
  std::array<float, 2> a3({46, 60});

  ASSERT_EQ(t0, a0);
  ASSERT_EQ(t1, a1);
  ASSERT_EQ(t2, a2);
  ASSERT_EQ(t0.use_count(), 1);
  ASSERT_EQ(t1.use_count(), 1);
  ASSERT_EQ(t2.use_count(), 1);

  t2.gemv(2.0, t0, t1, 2.0);

  ASSERT_EQ(t0, a0);
  ASSERT_EQ(t1, a1);
  ASSERT_EQ(t2, a3);
  ASSERT_EQ(t0.use_count(), 1);
  ASSERT_EQ(t1.use_count(), 1);
  ASSERT_EQ(t2.use_count(), 1);
}

TEST(ArrayLevel2BLAS, GER)
{
  Array<3> t0({1, 2, 3});
  Array<2> t1({1, 2});
  Array<3, 2> t2({1, 2, 3, 4, 5, 6});
  std::array<float, 3> a0({1, 2, 3});
  std::array<float, 2> a1({1, 2});
  std::array<float, 6> a2({1, 2, 3, 4, 5, 6});
  std::array<float, 6> a3({3, 6, 7, 12, 11, 18});

  ASSERT_EQ(t0, a0);
  ASSERT_EQ(t1, a1);
  ASSERT_EQ(t2, a2);
  ASSERT_EQ(t0.use_count(), 1);
  ASSERT_EQ(t1.use_count(), 1);
  ASSERT_EQ(t2.use_count(), 1);

  t2.ger(2.0, t0, t1);

  ASSERT_EQ(t0, a0);
  ASSERT_EQ(t1, a1);
  ASSERT_EQ(t2, a3);
  ASSERT_EQ(t0.use_count(), 1);
  ASSERT_EQ(t1.use_count(), 1);
  ASSERT_EQ(t2.use_count(), 1);
}

TEST(ArrayLevel3BLAS, GEMM)
{
  Array<3, 2> t0({1, 2, 3, 4, 5, 6});
  Array<2, 3> t1({1, 2, 3, 4, 5, 6});
  Array<2, 2> t2({1, 2, 3, 4});
  Array<2, 2> t3({1, 2, 3, 4});
  Array<2, 2> t4({1, 2, 3, 4});
  Array<2, 2> t5({1, 2, 3, 4});
  std::array<float, 6> a0({1, 2, 3, 4, 5, 6});
  std::array<float, 4> a1({1, 2, 3, 4});
  std::array<float, 4> a2({46, 60, 104, 136});
  std::array<float, 4> a3({72, 92, 94, 120});
  std::array<float, 4> a4({30, 68, 70, 162});
  std::array<float, 4> a5({46, 102, 62, 136});

  ASSERT_EQ(t0, a0);
  ASSERT_EQ(t1, a0);
  ASSERT_EQ(t2, a1);
  ASSERT_EQ(t3, a1);
  ASSERT_EQ(t4, a1);
  ASSERT_EQ(t5, a1);
  ASSERT_EQ(t0.use_count(), 1);
  ASSERT_EQ(t1.use_count(), 1);
  ASSERT_EQ(t2.use_count(), 1);
  ASSERT_EQ(t3.use_count(), 1);
  ASSERT_EQ(t4.use_count(), 1);
  ASSERT_EQ(t5.use_count(), 1);

  t2.gemm(2.0, t0, t1, 2.0);
  t3.gemm(2.0, t0, t0.transpose(), 2.0);
  t4.gemm(2.0, t1.transpose(), t1, 2.0);
  t5.gemm(2.0, t1.transpose(), t0.transpose(), 2.0);

  ASSERT_EQ(t0, a0);
  ASSERT_EQ(t1, a0);
  ASSERT_EQ(t2, a2);
  ASSERT_EQ(t3, a3);
  ASSERT_EQ(t4, a4);
  ASSERT_EQ(t5, a5);
  ASSERT_EQ(t0.use_count(), 1);
  ASSERT_EQ(t1.use_count(), 1);
  ASSERT_EQ(t2.use_count(), 1);
  ASSERT_EQ(t3.use_count(), 1);
  ASSERT_EQ(t4.use_count(), 1);
  ASSERT_EQ(t5.use_count(), 1);
}

TEST(ArrayLinearAlgebra, Dot)
{
  Array<3, 2> t0({1, 2, 3, 4, 5, 6});
  Array<2, 3> t1({1, 2, 3, 4, 5, 6});
  Array<2, 2> t2;
  Array<2, 2> t3;
  Array<2, 2> t4;
  Array<2, 2> t5;
  std::array<float, 6> a0({1, 2, 3, 4, 5, 6});
  std::array<float, 4> a1({0, 0, 0, 0});
  std::array<float, 4> a2({22, 28, 49, 64});
  std::array<float, 4> a3({35, 44, 44, 56});
  std::array<float, 4> a4({14, 32, 32, 77});
  std::array<float, 4> a5({22, 49, 28, 64});

  ASSERT_EQ(t0, a0);
  ASSERT_EQ(t1, a0);
  ASSERT_EQ(t2, a1);
  ASSERT_EQ(t3, a1);
  ASSERT_EQ(t4, a1);
  ASSERT_EQ(t5, a1);
  ASSERT_EQ(t0.use_count(), 1);
  ASSERT_EQ(t1.use_count(), 1);
  ASSERT_EQ(t2.use_count(), 1);
  ASSERT_EQ(t3.use_count(), 1);
  ASSERT_EQ(t4.use_count(), 1);
  ASSERT_EQ(t5.use_count(), 1);

  t2 = t1.dot(t0);
  t3 = t0.transpose().dot(t0);
  t4 = t1.dot(t1.transpose());
  t5 = t0.transpose().dot(t1.transpose());

  ASSERT_EQ(t0, a0);
  ASSERT_EQ(t1, a0);
  ASSERT_EQ(t2, a2);
  ASSERT_EQ(t3, a3);
  ASSERT_EQ(t4, a4);
  ASSERT_EQ(t5, a5);
  ASSERT_EQ(t0.use_count(), 1);
  ASSERT_EQ(t1.use_count(), 1);
  ASSERT_EQ(t2.use_count(), 1);
  ASSERT_EQ(t3.use_count(), 1);
  ASSERT_EQ(t4.use_count(), 1);
  ASSERT_EQ(t5.use_count(), 1);
}

TEST(ArrayLinearAlgebra, DotInplace)
{
  Array<3, 2> t0({1, 2, 3, 4, 5, 6});
  Array<2, 3> t1({1, 2, 3, 4, 5, 6});
  Array<2, 2> t2;
  Array<2, 2> t3;
  Array<2, 2> t4;
  Array<2, 2> t5;
  std::array<float, 6> a0({1, 2, 3, 4, 5, 6});
  std::array<float, 4> a1({0, 0, 0, 0});
  std::array<float, 4> a2({22, 28, 49, 64});
  std::array<float, 4> a3({35, 44, 44, 56});
  std::array<float, 4> a4({14, 32, 32, 77});
  std::array<float, 4> a5({22, 49, 28, 64});

  ASSERT_EQ(t0, a0);
  ASSERT_EQ(t1, a0);
  ASSERT_EQ(t2, a1);
  ASSERT_EQ(t3, a1);
  ASSERT_EQ(t4, a1);
  ASSERT_EQ(t5, a1);
  ASSERT_EQ(t0.use_count(), 1);
  ASSERT_EQ(t1.use_count(), 1);
  ASSERT_EQ(t2.use_count(), 1);
  ASSERT_EQ(t3.use_count(), 1);
  ASSERT_EQ(t4.use_count(), 1);
  ASSERT_EQ(t5.use_count(), 1);

  t2.dot_inplace(t1, t0);
  t3.dot_inplace(t0.transpose(), t0);
  t4.dot_inplace(t1, t1.transpose());
  t5.dot_inplace(t0.transpose(), t1.transpose());

  ASSERT_EQ(t0, a0);
  ASSERT_EQ(t1, a0);
  ASSERT_EQ(t2, a2);
  ASSERT_EQ(t3, a3);
  ASSERT_EQ(t4, a4);
  ASSERT_EQ(t5, a5);
  ASSERT_EQ(t0.use_count(), 1);
  ASSERT_EQ(t1.use_count(), 1);
  ASSERT_EQ(t2.use_count(), 1);
  ASSERT_EQ(t3.use_count(), 1);
  ASSERT_EQ(t4.use_count(), 1);
  ASSERT_EQ(t5.use_count(), 1);
}

TEST(ArrayArithmetic, Mul)
{
  Array<3, 2> t0({1, 2, 3, 4, 5, 6});
  Array<3, 2> t1({1, 2, 3, 4, 5, 6});
  std::array<float, 6> a0({1, 2, 3, 4, 5, 6});
  std::array<float, 6> a1({1, 4, 9, 16, 25, 36});

  ASSERT_EQ(t0, a0);
  ASSERT_EQ(t1, a0);
  ASSERT_EQ(t0.use_count(), 1);
  ASSERT_EQ(t1.use_count(), 1);

  t1.mul(t0);

  ASSERT_EQ(t0, a0);
  ASSERT_EQ(t1, a1);
  ASSERT_EQ(t0.use_count(), 1);
  ASSERT_EQ(t1.use_count(), 1);
}

TEST(ArrayArithmetic, Div)
{
  Array<3, 2> t0({1, 2, 3, 4, 5, 6});
  Array<3, 2> t1({1, 2, 3, 4, 5, 6});
  std::array<float, 6> a0({1, 2, 3, 4, 5, 6});
  std::array<float, 6> a1({1, 1, 1, 1, 1, 1});

  ASSERT_EQ(t0, a0);
  ASSERT_EQ(t1, a0);
  ASSERT_EQ(t0.use_count(), 1);
  ASSERT_EQ(t1.use_count(), 1);

  t1.div(t0);

  ASSERT_EQ(t0, a0);
  ASSERT_EQ(t1, a1);
  ASSERT_EQ(t0.use_count(), 1);
  ASSERT_EQ(t1.use_count(), 1);
}

TEST(ArrayArithmetic, Pow)
{
  Array<3, 2> t0({1, 2, 3, 4, 5, 6});
  Array<3, 2> t1({2, 2, 2, 2, 2, 2});
  std::array<float, 6> a0({1, 2, 3, 4, 5, 6});
  std::array<float, 6> a1({2, 4, 8, 16, 32, 64});
  std::array<float, 6> a2({2, 2, 2, 2, 2, 2});

  ASSERT_EQ(t0, a0);
  ASSERT_EQ(t1, a2);
  ASSERT_EQ(t0.use_count(), 1);
  ASSERT_EQ(t1.use_count(), 1);

  t1.pow(t0);

  ASSERT_EQ(t0, a0);
  ASSERT_EQ(t1, a1);
  ASSERT_EQ(t0.use_count(), 1);
  ASSERT_EQ(t1.use_count(), 1);
}

TEST(ArrayArithmetic, PowFloat)
{
  Array<3, 2> t0({1, 2, 3, 4, 5, 6});
  std::array<float, 6> a0({1, 2, 3, 4, 5, 6});
  std::array<float, 6> a1({1, 4, 9, 16, 25, 36});

  ASSERT_EQ(t0, a0);
  ASSERT_EQ(t0.use_count(), 1);

  t0.pow(2.0);

  ASSERT_EQ(t0, a1);
  ASSERT_EQ(t0.use_count(), 1);
}

}
}
