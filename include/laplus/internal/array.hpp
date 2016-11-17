/******************************************************************************
 *
 * laplus/internal/array.hpp
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

#ifndef __LAPLUS_INTERNAL_ARRAY_HPP__
#define __LAPLUS_INTERNAL_ARRAY_HPP__

#include <cassert>
#include <vector>
#include <algorithm>
#include <memory>
#include <utility>

namespace laplus {
namespace internal {

template<typename T>
class Array {
public:
  Array();
  Array(T*, std::size_t);
  Array(const Array&);
  Array(Array&&) noexcept;
  virtual ~Array();
  Array& operator=(const Array&);
  Array& operator=(Array&&) noexcept;
  T& operator[](const std::size_t) const;
  template<typename U>
  friend void swap(Array<U>&, Array<U>&);
  T* const get() const;
  void set(T* const, const std::size_t);
  const std::size_t size() const;
  const bool empty() const;
private:
  T* buffer;
  std::size_t length;
};

}  // namespace internal
}  // namespace laplus

#include "laplus/internal/array_impl.hpp"

#endif  // __LAPLUS_INTERNAL_ARRAY_HPP__
