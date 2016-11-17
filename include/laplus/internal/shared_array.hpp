/******************************************************************************
 *
 * laplus/internal/shared_array.hpp
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

#ifndef __LAPLUS_INTERNAL_SHARED_ARRAY_HPP__
#define __LAPLUS_INTERNAL_SHARED_ARRAY_HPP__

#include "laplus/internal/array.hpp"

#include <cassert>
#include <vector>
#include <algorithm>
#include <memory>
#include <utility>

namespace laplus {
namespace internal {

template<typename T>
class SharedArray : public Array<T> {
public:
  SharedArray(const std::size_t);
  SharedArray(const std::vector<T>&);
  SharedArray(const SharedArray&);
  SharedArray(SharedArray&&) noexcept;
  virtual ~SharedArray();
  SharedArray& operator=(const SharedArray&);
  SharedArray& operator=(SharedArray&&) noexcept;
  template<typename U>
  friend void swap(SharedArray<U>&, SharedArray<U>&);
  const std::size_t use_count() const;
private:
  std::shared_ptr<T> shared;
};

}  // namespace internal
}  // namespace laplus

#include "laplus/internal/shared_array_impl.hpp"

#endif  // __LAPLUS_INTERNAL_SHARED_ARRAY_HPP__

