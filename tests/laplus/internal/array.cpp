/******************************************************************************
 *
 * laplus/internal/array.cpp
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

#include "laplus/internal/array.hpp"
#include "gtest/gtest.h"

namespace laplus {
namespace internal {

TEST(LAPlusInternalArray, ConstructorDefault) {
  Array<int> a0;

  ASSERT_TRUE(a0.empty());
  ASSERT_EQ(a0.get(), nullptr);
  ASSERT_EQ(a0.size(), 0);
}

TEST(LAPlusInternalArray, ConstructorPtrSize) {
  std::size_t s0 = 3;
  int* p0 = new int[s0];
  *(p0 + 0) = 0;
  *(p0 + 1) = 1;
  *(p0 + 2) = 2;

  Array<int> a0(p0, s0);

  ASSERT_FALSE(a0.empty());
  ASSERT_EQ(a0.get(), p0);
  ASSERT_EQ(a0[0], *(p0 + 0));
  ASSERT_EQ(a0[1], *(p0 + 1));
  ASSERT_EQ(a0[2], *(p0 + 2));

  delete[] p0;
}

TEST(LAPlusInternalArray, ConstructorCopy) {
  std::size_t s0 = 3;
  int* p0 = new int[s0];
  *(p0 + 0) = 0;
  *(p0 + 1) = 1;
  *(p0 + 2) = 2;

  Array<int> a0(p0, s0);

  ASSERT_FALSE(a0.empty());
  ASSERT_EQ(a0.get(), p0);
  ASSERT_EQ(a0.size(), s0);
  ASSERT_EQ(a0[0], *(p0 + 0));
  ASSERT_EQ(a0[1], *(p0 + 1));
  ASSERT_EQ(a0[2], *(p0 + 2));

  Array<int> a1(a0);

  ASSERT_FALSE(a1.empty());
  ASSERT_EQ(a1.get(), a0.get());
  ASSERT_EQ(a1.size(), a0.size());
  ASSERT_EQ(a1[0], *(p0 + 0));
  ASSERT_EQ(a1[1], *(p0 + 1));
  ASSERT_EQ(a1[2], *(p0 + 2));

  delete[] p0;
}

TEST(LAPlusInternalArray, ConstructorMove) {
  std::size_t s0 = 3;
  int* p0 = new int[s0];
  *(p0 + 0) = 0;
  *(p0 + 1) = 1;
  *(p0 + 2) = 2;

  Array<int> a0(p0, s0);

  ASSERT_FALSE(a0.empty());
  ASSERT_EQ(a0.get(), p0);
  ASSERT_EQ(a0.size(), s0);
  ASSERT_EQ(a0[0], *(p0 + 0));
  ASSERT_EQ(a0[1], *(p0 + 1));
  ASSERT_EQ(a0[2], *(p0 + 2));

  Array<int> a1(std::move(a0));

  ASSERT_TRUE(a0.empty());
  ASSERT_EQ(a0.get(), nullptr);
  ASSERT_EQ(a0.size(), 0);

  ASSERT_FALSE(a1.empty());
  ASSERT_EQ(a1.get(), p0);
  ASSERT_EQ(a1.size(), s0);
  ASSERT_EQ(a1[0], *(p0 + 0));
  ASSERT_EQ(a1[1], *(p0 + 1));
  ASSERT_EQ(a1[2], *(p0 + 2));

  delete[] p0;
}

TEST(LAPlusInternalArray, OperatorAssignmentCopy) {
  std::size_t s0 = 3;
  int* p0 = new int[s0];
  *(p0 + 0) = 0;
  *(p0 + 1) = 1;
  *(p0 + 2) = 2;

  Array<int> a0(p0, s0);

  ASSERT_FALSE(a0.empty());
  ASSERT_EQ(a0.get(), p0);
  ASSERT_EQ(a0.size(), s0);
  ASSERT_EQ(a0[0], *(p0 + 0));
  ASSERT_EQ(a0[1], *(p0 + 1));
  ASSERT_EQ(a0[2], *(p0 + 2));

  Array<int> a1;

  a1 = a0;

  ASSERT_FALSE(a1.empty());
  ASSERT_EQ(a1.get(), a0.get());
  ASSERT_EQ(a1.size(), a0.size());
  ASSERT_EQ(a1[0], *(p0 + 0));
  ASSERT_EQ(a1[1], *(p0 + 1));
  ASSERT_EQ(a1[2], *(p0 + 2));

  delete[] p0;
}

TEST(LAPlusInternalArray, OperatorAssignmentMove) {
  std::size_t s0 = 3;
  int* p0 = new int[s0];
  *(p0 + 0) = 0;
  *(p0 + 1) = 1;
  *(p0 + 2) = 2;

  Array<int> a0(p0, s0);

  ASSERT_FALSE(a0.empty());
  ASSERT_EQ(a0.get(), p0);
  ASSERT_EQ(a0.size(), s0);
  ASSERT_EQ(a0[0], *(p0 + 0));
  ASSERT_EQ(a0[1], *(p0 + 1));
  ASSERT_EQ(a0[2], *(p0 + 2));

  Array<int> a1;

  a1 = std::move(a0);

  ASSERT_TRUE(a0.empty());
  ASSERT_EQ(a0.get(), nullptr);
  ASSERT_EQ(a0.size(), 0);

  ASSERT_FALSE(a1.empty());
  ASSERT_EQ(a1.get(), p0);
  ASSERT_EQ(a1.size(), s0);
  ASSERT_EQ(a1[0], *(p0 + 0));
  ASSERT_EQ(a1[1], *(p0 + 1));
  ASSERT_EQ(a1[2], *(p0 + 2));

  delete[] p0;
}

TEST(LAPlusInternalArray, Swap) {
  std::size_t s0 = 3;
  int* p0 = new int[s0];
  *(p0 + 0) = 0;
  *(p0 + 1) = 1;
  *(p0 + 2) = 2;

  Array<int> a0(p0, s0);

  std::size_t s1 = 3;
  int* p1 = new int[s1];
  *(p1 + 0) = 1;
  *(p1 + 1) = 2;
  *(p1 + 2) = 3;

  Array<int> a1(p1, s1);

  ASSERT_FALSE(a0.empty());
  ASSERT_EQ(a0.get(), p0);
  ASSERT_EQ(a0.size(), s0);
  ASSERT_EQ(a0[0], *(p0 + 0));
  ASSERT_EQ(a0[1], *(p0 + 1));
  ASSERT_EQ(a0[2], *(p0 + 2));

  ASSERT_FALSE(a1.empty());
  ASSERT_EQ(a1.get(), p1);
  ASSERT_EQ(a1.size(), s1);
  ASSERT_EQ(a1[0], *(p1 + 0));
  ASSERT_EQ(a1[1], *(p1 + 1));
  ASSERT_EQ(a1[2], *(p1 + 2));

  swap(a0, a1);

  ASSERT_FALSE(a0.empty());
  ASSERT_EQ(a0.get(), p1);
  ASSERT_EQ(a0.size(), s1);
  ASSERT_EQ(a0[0], *(p1 + 0));
  ASSERT_EQ(a0[1], *(p1 + 1));
  ASSERT_EQ(a0[2], *(p1 + 2));

  ASSERT_FALSE(a1.empty());
  ASSERT_EQ(a1.get(), p0);
  ASSERT_EQ(a1.size(), s1);
  ASSERT_EQ(a1[0], *(p0 + 0));
  ASSERT_EQ(a1[1], *(p0 + 1));
  ASSERT_EQ(a1[2], *(p0 + 2));

  delete[] p0;
  delete[] p1;
}

TEST(LAPlusInternalArray, Set) {
  std::size_t s0 = 3;
  int* p0 = new int[s0];
  *(p0 + 0) = 0;
  *(p0 + 1) = 1;
  *(p0 + 2) = 2;

  Array<int> a0;

  ASSERT_TRUE(a0.empty());
  ASSERT_EQ(a0.get(), nullptr);
  ASSERT_EQ(a0.size(), 0);

  a0.set(p0, s0);

  ASSERT_FALSE(a0.empty());
  ASSERT_EQ(a0.get(), p0);
  ASSERT_EQ(a0[0], *(p0 + 0));
  ASSERT_EQ(a0[1], *(p0 + 1));
  ASSERT_EQ(a0[2], *(p0 + 2));

  delete[] p0;
}

}  // namespace internal
}  // namespace laplus


