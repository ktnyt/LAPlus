/******************************************************************************
 *
 * laplus/internal/array_impl.hpp
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

std::size_t align(const std::size_t size)
{ return size + (size % (256 / (sizeof(T) * 8))); }

}  // unnamed namespace

template<typename T>
Array<T>::Array() : buffer(nullptr), length(0) {}

template<typename T>
Array<T>::Array(T* const ptr, std::size_t size)
  : buffer(ptr), length(size)
{}

template<typename T>
Array<T>::Array(const Array<T>& other)
  : buffer(other.buffer), length(other.length)
{}

template<typename T>
Array<T>::Array(Array<T>&& other) noexcept
  : buffer(other.buffer), length(other.length)
{
  other.buffer = nullptr;
  other.length = 0;
}

template<typename T>
Array<T>::~Array() {}

template<typename T>
Array<T>& Array<T>::operator=(const Array<T>& other)
{
  Array another(other);
  *this = std::move(another);
  return *this;
}

template<typename T>
Array<T>& Array<T>::operator=(Array<T>&& other) noexcept
{
  using std::swap;
  swap(*this, other);
  return *this;
}

template<typename T>
T& Array<T>::operator[](std::size_t index) const
{
  assert(index < align<T>(this->length));
  return *(this->buffer + index);
}

template<typename T>
void swap(Array<T>& a, Array<T>& b)
{
  using std::swap;
  swap(a.buffer, b.buffer);
  swap(a.length, b.length);
}

template<typename T>
T* const Array<T>::get() const
{ return buffer; }

template<typename T>
void Array<T>::set(T* const ptr, const std::size_t size)
{
  this->buffer = ptr;
  this->length = size;
}

template<typename T>
const std::size_t Array<T>::size() const
{ return length; }

template<typename T>
const bool Array<T>::empty() const
{ return buffer == nullptr; }

}  // namespace internal
}  // namespace laplus
