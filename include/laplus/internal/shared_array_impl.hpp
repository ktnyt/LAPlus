/******************************************************************************
 *
 * laplus/internal/shared_array_impl.hpp
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

namespace laplus {
namespace internal {

namespace {

template<typename T>
using deleter = std::default_delete<T>;

template<typename T>
std::shared_ptr<T> make_shared(const std::size_t size)
{ return std::shared_ptr<T>(new T[align<T>(size)], deleter<T[]>()); }

} // unnamed namespace

template<typename T>
SharedArray<T>::SharedArray(const std::size_t size)
  : shared(make_shared<T>(size)), Array<T>()
{
  Array<T>::set(shared.get(), size);
  for(std::size_t i = 0; i < align<T>(size); ++i) {
    (*this)[i] = T();
  }
}

template<typename T>
SharedArray<T>::SharedArray(const std::vector<T>& values)
  : shared(make_shared<T>(values.size())), Array<T>()
{
  Array<T>::set(shared.get(), values.size());
  std::copy(values.begin(), values.end(), this->get());
}

template<typename T>
SharedArray<T>::SharedArray(const SharedArray<T>& other)
  : shared(other.shared), Array<T>(other)
{}

template<typename T>
SharedArray<T>::SharedArray(SharedArray<T>&& other) noexcept
  : shared(other.shared), Array<T>(std::forward<SharedArray<T>>(other))
{ other.shared = nullptr; }

template<typename T>
SharedArray<T>::~SharedArray() {}

template<typename T>
SharedArray<T>& SharedArray<T>::operator=(const SharedArray<T>& other)
{
  SharedArray<T> another(other);
  *this = std::move(another);
  return *this;
}

template<typename T>
SharedArray<T>& SharedArray<T>::operator=(SharedArray<T>&& other) noexcept
{
  using std::swap;
  swap(*this, other);
  return *this;
}

template<typename T>
void swap(SharedArray<T>& a, SharedArray<T>& b)
{
  using std::swap;
  swap(static_cast<Array<T>&>(a), static_cast<Array<T>&>(b));
  swap(a.shared, b.shared);
}

template<typename T>
const std::size_t SharedArray<T>::use_count() const
{ return shared.use_count(); }

}  // namespace internal
}  // namespace laplus
