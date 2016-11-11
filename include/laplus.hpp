/******************************************************************************
 *
 * laplus.hpp
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

#ifndef __LAPLUS__
#define __LAPLUS__

#include <cassert>
#include <cmath>
#include <cstring>
#include <array>
#include <ostream>
#include <algorithm>
#include <functional>
#include <memory>
#include <type_traits>
#include "cblas.h"

namespace laplus {

using Transpose = CBLAS_TRANSPOSE;

template<std::size_t Rows, std::size_t Cols=1, bool Trans=false>
class Array;

template<bool Trans>
class Array<1, 1, Trans> {
public:
  /* Construtors & Destructor */
  Array() = delete;

private:
  Array(const Array& other)
    : shared(other.shared), buffer(other.buffer)
    , offset(other.offset), stride(other.stride) {}

  Array(Array&& other) noexcept
    : shared(other.shared), buffer(other.buffer)
    , offset(other.offset), stride(other.stride)
  { other.shared = nullptr; }

  template<std::size_t Rows>
  Array(const Array<Rows>& other, const std::size_t offset, const std::size_t stride)
    : shared(other.shared), buffer(other.buffer), offset(offset), stride(stride) {}

public:
  virtual ~Array() {}

  /* Assignment Operators */
  void operator=(const float& value) { *(this->buffer + this->offset) = value; }

  template<bool Trans2>
  Array& operator+=(const Array<1, 1, Trans2>& rhs)
  {
    (float&)(*this) += (float&)(rhs);
    return *this;
  }

  template<bool Trans2>
  Array& operator-=(const Array<1, 1, Trans2>& rhs)
  {
    (float&)(*this) -= (float&)(rhs);
    return *this;
  }

  template<bool Trans2>
  Array& operator*=(const Array<1, 1, Trans2>& rhs)
  {
    (float&)(*this) *= (float&)(rhs);
    return *this;
  }

  template<bool Trans2>
  Array& operator/=(const Array<1, 1, Trans2>& rhs)
  {
    (float&)(*this) /= (float&)(rhs);
    return *this;
  }

  template<bool Trans2>
  Array& operator^=(const Array<1, 1, Trans2>& rhs)
  {
    (float&)(*this) ^= std::pow((float&)(*this), (float&)(rhs));
    return *this;
  }

  /* Arithmetic Operators */
  template<bool Trans2>
  const Array operator+(const Array<1, 1, Trans2>& other) const
  {
    Array result(*this);
    result += other;
    return result;
  }

  template<bool Trans2>
  const Array operator-(const Array<1, 1, Trans2>& other) const
  {
    Array result(*this);
    result -= other;
    return result;
  }

  template<bool Trans2>
  const Array operator*(const Array<1, 1, Trans2>& other) const
  {
    Array result(*this);
    result *= other;
    return result;
  }

  template<bool Trans2>
  const Array operator/(const Array<1, 1, Trans2>& other) const
  {
    Array result(*this);
    result /= other;
    return result;
  }

  template<bool Trans2>
  const Array operator^(const Array<1, 1, Trans2>& other) const
  {
    Array result(*this);
    result ^= other;
    return result;
  }

  /* Implicit Casts */
  operator float&() { return *(this->buffer + this->offset); }

  /* Miscellaneous Operators */
  friend std::ostream& operator<<(std::ostream& ostream, const Array& array)
  { return ostream << *(array.buffer + array.offset); }
private:
  std::shared_ptr<float> shared;
  float* buffer;
  std::size_t offset;
  std::size_t stride;
};

template<bool Trans1, bool Trans2>
bool operator==(const Array<1, 1, Trans1>& array1, const Array<1, 1, Trans2>& array2)
{ return (float&)(array1) == (float&)(array2); }

template<bool Trans1, bool Trans2>
bool operator!=(const Array<1, 1, Trans1>& array1, const Array<1, 1, Trans2>& array2)
{ return (float&)(array1) != (float&)(array2); }

template<bool Trans1, bool Trans2>
bool operator< (const Array<1, 1, Trans1>& array1, const Array<1, 1, Trans1>& array2)
{ return (float&)(array1) < (float&)(array2); }

template<bool Trans1, bool Trans2>
bool operator> (const Array<1, 1, Trans2>& array1, const Array<1, 1, Trans2>& array2)
{ return (float&)(array2) < (float&)(array1); }

template<bool Trans1, bool Trans2>
bool operator<=(const Array<1, 1, Trans1>& array1, const Array<1, 1, Trans2>& array2)
{ return !((float&)(array1) > (float&)(array2)); }

template<bool Trans1, bool Trans2>
bool operator>=(const Array<1, 1, Trans1>& array1, const Array<1, 1, Trans2>& array2)
{ return !((float&)(array2) < (float&)(array1)); }

template<std::size_t Rows, std::size_t Cols, bool Trans>
class Array {
  template<std::size_t Rows2, std::size_t Cols2, bool Trans2>
  friend class Array;
  static constexpr std::size_t Size = Rows * Cols;
  static constexpr Transpose trans = Trans ? CblasTrans : CblasNoTrans;
public:
  /* Constructors & Destructor */
  Array(const float value=0.0)
    : shared(std::shared_ptr<float>(new float[Rows*Cols], std::default_delete<float[]>()))
    , buffer(shared.get()), offset(0), stride(1)
  { for(std::size_t i = 0; i < Rows * Cols; ++i) *(this->buffer + i) = value; }

  Array(const std::array<float, Rows*Cols> values)
    : shared(std::shared_ptr<float>(new float[Rows*Cols], std::default_delete<float[]>()))
    , buffer(shared.get()), offset(0), stride(1)
  { std::copy(values.begin(), values.end(), this->buffer); }

  Array(const Array& other)
    : shared(other.shared), buffer(other.buffer)
    , offset(other.offset), stride(other.stride) {}

  Array(Array&& other) noexcept
    : shared(other.shared), buffer(other.buffer)
    , offset(other.offset), stride(other.stride)
  { other.shared = nullptr; }

  virtual ~Array() {}

  /* Assignment Operators */
  Array& operator=(const Array& other)
  {
    Array another(other);
    *this = std::move(another);
    return *this;
  }

  Array& operator=(Array&& other) noexcept
  {
    swap(*this, other);
    return *this;
  }

  Array& operator+=(const Array& rhs)
  {
    this->axpy(1.0, rhs);
    return *this;
  }

  Array& operator-=(const Array& rhs)
  {
    *this += -rhs;
    return *this;
  }

  Array& operator*=(const Array& rhs)
  {
    this->mul(rhs);
    return *this;
  }

  Array& operator*=(const float rhs)
  {
    this->scal(rhs);
    return *this;
  }

  Array& operator/=(const Array& rhs)
  {
    this->div(rhs);
    return *this;
  }

  Array& operator/=(const float rhs)
  {
    this->scal(1/rhs);
    return *this;
  }

  Array& operator^=(const Array& rhs)
  {
    this->pow(rhs);
    return *this;
  }

  Array& operator^=(const float value)
  {
    this->pow(value);
    return *this;
  }

  /* Arithmetic Operators */
  Array operator+() const { return this->clone(); }

  Array operator-() const
  {
    Array result(this->clone());
    result.scal(-1.0);
    return result;
  }

  Array operator+(const Array& other) const
  {
    Array result(this->clone());
    result += other;
    return result;
  }

  Array operator-(const Array& other) const
  {
    Array result(this->clone());
    result -= other;
    return result;
  }

  Array operator*(const Array& other) const
  {
    Array result(this->clone());
    result *= other;
    return result;
  }

  Array operator*(const float other) const
  {
    Array result(this->clone());
    result *= other;
    return result;
  }

  friend Array operator*(const float value, const Array& array)
  {
    return array * value;
  }

  Array operator/(const Array& other) const
  {
    Array result(this->clone());
    result /= other;
    return result;
  }

  Array operator/(const float other) const
  {
    Array result(this->clone());
    result /= other;
    return result;
  }

  friend Array operator/(const float value, const Array& array)
  {
    return array / value;
  }

  Array operator^(const Array& other) const
  {
    Array result(this->clone());
    result ^= other;
    return result;
  }

  Array operator^(const float other) const
  {
    Array result(this->clone());
    result ^= other;
    return result;
  }

  /* Member Access Operators */
  Array<Cols> operator[](const std::size_t index) const
  {
    std::size_t offset = Trans ? index : Cols * index;
    std::size_t stride = Trans ? Rows : 1;
    return Array<Cols>(*this, this->offset + offset, this->stride * stride);
  }

  float& operator()(const std::size_t i) const
  { return *(this->buffer + this->offset + this->stride * i); }

  float& operator()(const std::size_t i, const std::size_t j) const
  {
    if(Cols == 1) return (*this)(i);
    return *(this->buffer + (Trans ? Rows : Cols) * i + j);
  }

  /* Miscellaneous Operators */
  friend std::ostream& operator<<(std::ostream& ostream, const Array& array)
  {
    ostream << "[";
    for(std::size_t i = 0; i < Rows; ++i) {
      if(i > 0 && Cols > 1) ostream << std::endl;
      if(i > 0) ostream << " ";
      if(Cols > 1) ostream << "[";
      for(std::size_t j = 0; j < Cols; ++j) {
        if(j > 0) ostream << " ";
        if(Trans) ostream << array(j, i);
        else ostream << array(i, j);
      }
      if(Cols > 1) ostream << "]";
    }
    return ostream << "]";
  }

  /* Utilities */
  friend void swap(Array& a, Array& b)
  {
    std::swap(a.shared, b.shared);
    std::swap(a.buffer, b.buffer);
    std::swap(a.offset, b.offset);
    std::swap(a.stride, b.stride);
  }

  Array clone() const
  {
    Array cloned;
    cloned.copy(*this);
    return cloned;
  }

  /* Accessors */
  static constexpr std::size_t rows() { return Rows; }
  static constexpr std::size_t cols() { return Cols; }
  static constexpr std::size_t size() { return Size; }
  const std::size_t use_count() const { return shared.use_count(); }

  /* Level 1 BLAS */
  void scal(const float alpha)
  { cblas_sscal(Size, alpha, this->buffer + this->offset, this->stride); }

  void copy(const Array& other)
  { cblas_scopy(Size, other.buffer + other.offset, other.stride,
                      this->buffer + this->offset, this->stride); }

  void axpy(const float alpha, const Array& other)
  { cblas_saxpy(Size, alpha, other.buffer + other.offset, other.stride,
                             this->buffer + this->offset, this->stride); }

  const float dot(const Array& other) const
  { return cblas_sdot(Size, other.buffer + other.offset, other.stride,
                            this->buffer + this->offset, this->stride); }

  const float norm() const
  { return cblas_snrm2(Size, this->buffer + this->offset, this->stride); }

  const float asum() const
  { return cblas_sasum(Size, this->buffer + this->offset, this->stride); }

  const float iamax() const
  { return cblas_isamax(Size, this->buffer + this->offset, this->stride); }

  /* Level 2 BLAS */
  template<std::size_t Rows2, std::size_t Cols2>
  void gemv(const float alpha, const Array<Rows2*Cols2, Rows*Cols>& A,
            const Array<Rows2, Cols2>& x, const float beta)
  { cblas_sgemv(CblasColMajor, A.trans, Rows * Cols, Rows2 * Cols2, alpha,
                A.buffer, Rows * Cols, x.buffer + x.offset, x.stride, beta,
                this->buffer + this->offset, this->stride); }

  template<std::size_t Rows1, std::size_t Cols1, std::size_t Rows2, std::size_t Cols2>
  void ger(const float alpha, const Array<Rows1, Cols1>& y,
                              const Array<Rows2, Cols2>& x)
  { cblas_sger(CblasColMajor, Rows2 * Cols2, Rows1 * Cols1, alpha,
               x.buffer + x.offset, x.stride, y.buffer + x.offset, y.stride,
               this->buffer, Rows2 * Cols2); }

  /* Level 3 BLAS */
  template<std::size_t Shared>
  void gemm(const float alpha, const Array<Shared, Rows, false>& A,
            const Array<Cols, Shared, false>& B, const float beta)
  { cblas_sgemm(CblasColMajor, A.trans, B.trans, Rows, Cols, Shared,
                alpha, A.buffer, Rows, B.buffer, Shared,
                beta, this->buffer, Cols); }

  template<std::size_t Shared>
  void gemm(const float alpha, const Array<Shared, Rows, true>& A,
            const Array<Cols, Shared, false>& B, const float beta)
  { cblas_sgemm(CblasColMajor, A.trans, B.trans, Rows, Cols, Shared,
                alpha, A.buffer, Shared, B.buffer, Shared,
                beta, this->buffer, Cols); }

  template<std::size_t Shared>
  void gemm(const float alpha, const Array<Shared, Rows, false>& A,
            const Array<Cols, Shared, true>& B, const float beta)
  { cblas_sgemm(CblasColMajor, A.trans, B.trans, Rows, Cols, Shared,
                alpha, A.buffer, Rows, B.buffer, Cols,
                beta, this->buffer, Cols); }

  template<std::size_t Shared>
  void gemm(const float alpha, const Array<Shared, Rows, true>& A,
            const Array<Cols, Shared, true>& B, const float beta)
  { cblas_sgemm(CblasColMajor, A.trans, B.trans, Rows, Cols, Shared,
                alpha, A.buffer, Shared, B.buffer, Cols,
                beta, this->buffer, Cols); }

  /* Extensions */
  Array(const Array<Cols, Rows, !Trans>& other)
    : shared(other.shared), buffer(other.buffer)
    , offset(other.offset), stride(other.stride) {}

  Array<Cols, Rows, !Trans> transpose() const
  { return Array<Cols, Rows, !Trans>(*this); }

  template<std::size_t Rows2, std::size_t Cols2>
  Array(const Array<Rows2, Cols2, Trans>& other)
    : shared(other.shared), buffer(other.buffer)
    , offset(other.offset), stride(other.stride)
  { static_assert(Rows2*Cols2==Size, "total size of new array must be unchanged"); }

  template<std::size_t Rows2, std::size_t Cols2>
  Array<Rows2, Cols2, Trans> reshape() const
  { return Array<Rows2, Cols2, Trans>(*this); }

  template<std::size_t Rows2>
  Array(const Array<Rows2, Rows*Cols>& other,
         const std::size_t offset, const std::size_t stride)
    : shared(other.shared), buffer(other.buffer), offset(offset), stride(stride)
  {}

  const float maxCoeff()
  {
    std::size_t max_i = 0;
    float max_v = (*this)(max_i);
    for(std::size_t i = 0; i < Size; ++i) {
      if(max_v < (*this)(i)) {
        max_v = (*this)(i);
        max_i = i;
      }
    }
    return max_v;
  }

  const float maxCoeff(std::size_t* max_i)
  {
    *max_i = 0;
    float max_v = (*this)(*max_i);
    for(std::size_t i = 0; i < Size; ++i) {
      if(max_v < (*this)(i)) {
        max_v = (*this)(i);
        *max_i = i;
      }
    }
    return max_v;
  }

  const float maxCoeff(std::size_t* max_i, std::size_t* max_j)
  {
    *max_i = 0;
    *max_j = 0;
    float max_v = (*this)(*max_i, *max_j);
    for(std::size_t i = 0; i < Rows; ++i) {
      for(std::size_t j = 0; j < Cols; ++j) {
        if(max_v < (*this)(i, j)) {
          max_v = (*this)(i, j);
          *max_i = i;
          *max_j = j;
        }
      }
    }
    return max_v;
  }

  const float minCoeff()
  {
    std::size_t min_i = 0;
    float min_v = (*this)(min_i);
    for(std::size_t i = 0; i < Size; ++i) {
      if(min_v > (*this)(i)) {
        min_v = (*this)(i);
        min_i = i;
      }
    }
    return min_v;
  }

  const float minCoeff(std::size_t* min_i)
  {
    *min_i = 0;
    float min_v = (*this)(*min_i);
    for(std::size_t i = 0; i < Size; ++i) {
      if(min_v > (*this)(i)) {
        min_v = (*this)(i);
        *min_i = i;
      }
    }
    return min_v;
  }

  const float minCoeff(std::size_t* min_i, std::size_t* min_j)
  {
    *min_i = 0;
    *min_j = 0;
    float min_v = (*this)(*min_i, *min_j);
    for(std::size_t i = 0; i < Rows; ++i) {
      for(std::size_t j = 0; j < Cols; ++j) {
        if(min_v > (*this)(i, j)) {
          min_v = (*this)(i, j);
          *min_i = i;
          *min_j = j;
        }
      }
    }
    return min_v;
  }

  /* Linear Algebra */
  template<std::size_t Shared, bool Trans2>
  Array<Rows, Shared> dot(const Array<Cols, Shared, Trans2>& other) const
  {
    Array<Rows, Shared> result;
    result.gemm(1.0, other, *this, 0.0);
    return result;
  }

  template<std::size_t Shared, bool Trans1, bool Trans2>
  void dot_inplace(const Array<Rows, Shared, Trans1>& A, const Array<Shared, Cols, Trans2>& B)
  {
    this->gemm(1.0, B, A, 0.0);
  }

  /* Arithmetic */
  void mul(const Array& other)
  { for(std::size_t i = 0; i < Size; ++i) (*this)(i) *= other(i); }

  void div(const Array& other)
  { for(std::size_t i = 0; i < Size; ++i) (*this)(i) /= other(i); }

  void pow(const Array& other)
  { for(std::size_t i = 0; i < Size; ++i) (*this)(i) = std::pow((*this)(i), other(i)); }

  void pow(const float value)
  { for(std::size_t i = 0; i < Size; ++i) (*this)(i) = std::pow((*this)(i), value); }

  void apply(const std::function<float(float)>& f)
  { for(std::size_t i = 0; i < Size; ++i) (*this)(i) = f((*this)(i)); }

  Array unaryExpr(const std::function<float(float)>& f)
  {
    Array result(this->clone());
    result.apply(f);
    return result;
  }
private:
  std::shared_ptr<float> shared;
  float* buffer;
  std::size_t offset;
  std::size_t stride;
};

template<std::size_t Rows, std::size_t Cols, bool Trans>
bool operator==(const Array<Rows, Cols, Trans>& array1, const Array<Rows, Cols, Trans>& array2)
{
  for(std::size_t i = 0; i < Rows; ++i) {
    for(std::size_t j = 0; j < Cols; ++j) {
      if(array1(i, j) != array2(i, j)) return false;
    }
  }
  return true;
}

template<std::size_t Rows, std::size_t Cols>
bool operator==(const Array<Rows, Cols, false>& array1, const Array<Rows, Cols, true>& array2)
{
  for(std::size_t i = 0; i < Rows; ++i) {
    for(std::size_t j = 0; j < Cols; ++j) {
      if(array1(i, j) != array2(j, i)) return false;
    }
  }
  return true;
}

template<std::size_t Rows, std::size_t Cols>
bool operator==(const Array<Rows, Cols, true>& array1, const Array<Rows, Cols, false>& array2)
{
  return array2 == array1;
}

template<std::size_t Rows, std::size_t Cols, bool Trans>
bool operator!=(const Array<Rows, Cols, Trans>& array1, const Array<Rows, Cols, Trans>& array2)
{ return !(array1 == array2); }

template<std::size_t Rows, std::size_t Cols>
bool operator==(const Array<Rows, Cols, false>& array1,
                const std::array<float, Rows*Cols>& array2)
{
  for(std::size_t i = 0; i < Rows; ++i) {
    for(std::size_t j = 0; j < Cols; ++j) {
      if(array1(i, j) != array2[Cols * i + j]) return false;
    }
  }
  return true;
}

template<std::size_t Rows, std::size_t Cols>
bool operator==(const Array<Rows, Cols, true>& array1,
                const std::array<float, Rows*Cols>& array2)
{
  for(std::size_t i = 0; i < Rows; ++i) {
    for(std::size_t j = 0; j < Cols; ++j) {
      if(array1(j, i) != array2[Cols * i + j]) return false;
    }
  }
  return true;
}

template<std::size_t Rows, std::size_t Cols, bool Trans>
bool operator==(const std::array<float, Rows*Cols>& array1,
                const Array<Rows, Cols, Trans>& array2)
{ return array2 == array1; }

template<std::size_t Rows, std::size_t Cols, bool Trans>
bool operator!=(const Array<Rows, Cols, Trans>& array1,
                const std::array<float, Rows*Cols>& array2)
{ return !(array1 == array2); }

template<std::size_t Rows, std::size_t Cols, bool Trans>
bool operator!=(const std::array<float, Rows*Cols>& array1,
                const Array<Rows, Cols, Trans>& array2)
{ return !(array2 == array1); }

template<std::size_t Rows, std::size_t Cols, std::size_t Shared, bool Trans1, bool Trans2>
Array<Rows, Cols> dot(const Array<Rows, Shared, Trans1>& A, const Array<Shared, Cols, Trans2>& B)
{
  Array<Rows, Cols> result;
  result.gemm(1.0, B, A, 0.0);
  return result;
}

template<std::size_t Rows, std::size_t Cols>
Array<Rows, Cols> outer(const Array<Rows>& x, const Array<Cols>& y)
{
  Array<Rows, Cols> result;
  result.ger(1.0, x, y);
  return result;
}

}

#endif
