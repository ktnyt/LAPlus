/******************************************************************************
 *
 * laplus/internal/shared_array.cpp
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

#include "laplus/internal/shared_array.hpp"
#include "gtest/gtest.h"

#include <vector>

namespace laplus {
namespace internal {

TEST(LAPlusInternalSharedArray, ConstructorSize) {
  SharedArray<int> a0(3);

  ASSERT_FALSE(a0.empty());
  ASSERT_EQ(a0.use_count(), 1);
  ASSERT_EQ(a0.size(), 3);
  ASSERT_EQ(a0[0], 0);
  ASSERT_EQ(a0[1], 0);
  ASSERT_EQ(a0[2], 0);
}

TEST(LAPlusInternalSharedArray, ConstructorVector) {
  std::vector<int> v0 = {0, 1, 2};
  SharedArray<int> a0(v0);

  ASSERT_FALSE(a0.empty());
  ASSERT_EQ(a0.use_count(), 1);
  ASSERT_EQ(a0.size(), v0.size());
  ASSERT_EQ(a0[0], v0[0]);
  ASSERT_EQ(a0[1], v0[1]);
  ASSERT_EQ(a0[2], v0[2]);
}

TEST(LAPlusInternalSharedArray, ConstructorCopy) {
  std::vector<int> v0 = {0, 1, 2};
  SharedArray<int> a0(v0);

  ASSERT_FALSE(a0.empty());
  ASSERT_EQ(a0.use_count(), 1);
  ASSERT_EQ(a0.size(), v0.size());
  ASSERT_EQ(a0[0], v0[0]);
  ASSERT_EQ(a0[1], v0[1]);
  ASSERT_EQ(a0[2], v0[2]);

  {
    SharedArray<int> a1(a0);

    ASSERT_FALSE(a0.empty());
    ASSERT_EQ(a0.use_count(), 2);
    ASSERT_EQ(a0.size(), v0.size());
    ASSERT_EQ(a0[0], v0[0]);
    ASSERT_EQ(a0[1], v0[1]);
    ASSERT_EQ(a0[2], v0[2]);

    ASSERT_FALSE(a1.empty());
    ASSERT_EQ(a1.use_count(), 2);
    ASSERT_EQ(a1.size(), v0.size());
    ASSERT_EQ(a1[0], v0[0]);
    ASSERT_EQ(a1[1], v0[1]);
    ASSERT_EQ(a1[2], v0[2]);

    ASSERT_EQ(a0.get(), a1.get());
  }

  ASSERT_FALSE(a0.empty());
  ASSERT_EQ(a0.use_count(), 1);
  ASSERT_EQ(a0.size(), v0.size());
  ASSERT_EQ(a0[0], v0[0]);
  ASSERT_EQ(a0[1], v0[1]);
  ASSERT_EQ(a0[2], v0[2]);
}

TEST(LAPlusInternalSharedArray, ConstructorMove) {
  std::vector<int> v0 = {0, 1, 2};
  SharedArray<int> a0(v0);

  ASSERT_FALSE(a0.empty());
  ASSERT_EQ(a0.use_count(), 1);
  ASSERT_EQ(a0.size(), v0.size());
  ASSERT_EQ(a0[0], v0[0]);
  ASSERT_EQ(a0[1], v0[1]);
  ASSERT_EQ(a0[2], v0[2]);

  SharedArray<int> a1(std::move(a0));

  ASSERT_TRUE(a0.empty());
  ASSERT_EQ(a0.use_count(), 0);
  ASSERT_EQ(a0.size(), 0);

  ASSERT_FALSE(a1.empty());
  ASSERT_EQ(a1.use_count(), 1);
  ASSERT_EQ(a1.size(), v0.size());
  ASSERT_EQ(a1[0], v0[0]);
  ASSERT_EQ(a1[1], v0[1]);
  ASSERT_EQ(a1[2], v0[2]);

  ASSERT_NE(a0.get(), a1.get());
}

TEST(LAPlusInternalSharedArray, OperatorAssignmentCopy) {
  std::vector<int> v0 = {0, 1, 2};
  SharedArray<int> a0(v0);

  ASSERT_FALSE(a0.empty());
  ASSERT_EQ(a0.use_count(), 1);
  ASSERT_EQ(a0.size(), v0.size());
  ASSERT_EQ(a0[0], v0[0]);
  ASSERT_EQ(a0[1], v0[1]);
  ASSERT_EQ(a0[2], v0[2]);

  {
    SharedArray<int> a1 = a0;

    ASSERT_FALSE(a0.empty());
    ASSERT_EQ(a0.use_count(), 2);
    ASSERT_EQ(a0.size(), v0.size());
    ASSERT_EQ(a0[0], v0[0]);
    ASSERT_EQ(a0[1], v0[1]);
    ASSERT_EQ(a0[2], v0[2]);

    ASSERT_FALSE(a1.empty());
    ASSERT_EQ(a1.use_count(), 2);
    ASSERT_EQ(a1.size(), v0.size());
    ASSERT_EQ(a1[0], v0[0]);
    ASSERT_EQ(a1[1], v0[1]);
    ASSERT_EQ(a1[2], v0[2]);

    ASSERT_EQ(a0.get(), a1.get());
  }

  ASSERT_FALSE(a0.empty());
  ASSERT_EQ(a0.use_count(), 1);
  ASSERT_EQ(a0.size(), v0.size());
  ASSERT_EQ(a0[0], v0[0]);
  ASSERT_EQ(a0[1], v0[1]);
  ASSERT_EQ(a0[2], v0[2]);
}

TEST(LAPlusInternalSharedArray, OperatorAssignmentMove) {
  std::vector<int> v0 = {0, 1, 2};
  SharedArray<int> a0(v0);

  ASSERT_FALSE(a0.empty());
  ASSERT_EQ(a0.use_count(), 1);
  ASSERT_EQ(a0.size(), v0.size());
  ASSERT_EQ(a0[0], v0[0]);
  ASSERT_EQ(a0[1], v0[1]);
  ASSERT_EQ(a0[2], v0[2]);

  SharedArray<int> a1 = std::move(a0);

  ASSERT_TRUE(a0.empty());
  ASSERT_EQ(a0.use_count(), 0);
  ASSERT_EQ(a0.size(), 0);

  ASSERT_FALSE(a1.empty());
  ASSERT_EQ(a1.use_count(), 1);
  ASSERT_EQ(a1.size(), v0.size());
  ASSERT_EQ(a1[0], v0[0]);
  ASSERT_EQ(a1[1], v0[1]);
  ASSERT_EQ(a1[2], v0[2]);

  ASSERT_NE(a0.get(), a1.get());
}

TEST(LAPlusInternalSharedArray, Swap) {
  std::vector<int> v0 = {0, 1, 2};
  SharedArray<int> a0(v0);

  std::vector<int> v1 = {1, 2, 3};
  SharedArray<int> a1(v1);

  ASSERT_FALSE(a0.empty());
  ASSERT_EQ(a0.use_count(), 1);
  ASSERT_EQ(a0.size(), v0.size());
  ASSERT_EQ(a0[0], v0[0]);
  ASSERT_EQ(a0[1], v0[1]);
  ASSERT_EQ(a0[2], v0[2]);

  ASSERT_FALSE(a1.empty());
  ASSERT_EQ(a1.use_count(), 1);
  ASSERT_EQ(a1.size(), v1.size());
  ASSERT_EQ(a1[0], v1[0]);
  ASSERT_EQ(a1[1], v1[1]);
  ASSERT_EQ(a1[2], v1[2]);

  swap(v0, v1);

  ASSERT_FALSE(a0.empty());
  ASSERT_EQ(a0.use_count(), 1);
  ASSERT_EQ(a0.size(), v1.size());
  ASSERT_EQ(a0[0], v1[0]);
  ASSERT_EQ(a0[1], v1[1]);
  ASSERT_EQ(a0[2], v1[2]);

  ASSERT_FALSE(a1.empty());
  ASSERT_EQ(a1.use_count(), 1);
  ASSERT_EQ(a1.size(), v0.size());
  ASSERT_EQ(a1[0], v0[0]);
  ASSERT_EQ(a1[1], v0[1]);
  ASSERT_EQ(a1[2], v0[2]);
}

}  // namespace internal
}  // namespace laplus


