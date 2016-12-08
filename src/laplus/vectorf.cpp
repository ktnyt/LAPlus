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
#include "laplus/matrixf.hpp"
#include "laplus/typedef.hpp"

#include <random>

#include <immintrin.h>

namespace laplus {

// Generators
Vectorf Vectorf::Uniform(const std::size_t size)
{ return Uniform(size, 0.0, 1.0); }

Vectorf Vectorf::Uniform(const std::size_t size, const float max)
{ return Uniform(size, 0.0, max); }

Vectorf Vectorf::Uniform(const std::size_t size,
                         const float min, const float max)
{
  Vectorf result(size);
  std::mt19937 generator;
  std::uniform_real_distribution<float> distribution(min, max);
  for(std::size_t i = 0; i < size; ++i) {
    result[i] = distribution(generator);
  }
  return result;
}

Vectorf Vectorf::Normal(const std::size_t size)
{ return Normal(size, 0.0, 1.0); }

Vectorf Vectorf::Normal(const std::size_t size,
                        const float mean, const float stddev)
{
  Vectorf result(size);
  std::mt19937 generator;
  std::normal_distribution<float> distribution(mean, stddev);
  for(std::size_t i = 0; i < size; ++i) {
    result[i] = distribution(generator);
  }
  return result;
}

// Constructors and Destructor
Vectorf::Vectorf(const std::size_t size)
  : internal::SharedArray<float>(size)
  , offset(0), stride(1), length(size)
{}

Vectorf::Vectorf(const vector1d<float>& values)
  : internal::SharedArray<float>(values.size())
  , offset(0), stride(1), length(values.size())
{
  for(std::size_t i = 0; i < size(); ++i) {
    internal::SharedArray<float>::operator[](offset + stride * i)= values[i];
  }
}

Vectorf::Vectorf(const Vectorf& other, std::size_t offset,
                 std::size_t stride, std::size_t length)
  : internal::SharedArray<float>(other)
  , offset(offset), stride(stride), length(length)
{}

Vectorf::Vectorf(const Vectorf& other)
  : internal::SharedArray<float>(other)
  , offset(other.offset), stride(other.stride), length(other.length)
{}

Vectorf::Vectorf(Vectorf&& other) noexcept
  : internal::SharedArray<float>(std::forward<Vectorf>(other))
  , offset(other.offset), stride(other.stride), length(other.length)
{
  other.length = 0;
}

Vectorf::~Vectorf() {}

// Assignment Operators
Vectorf& Vectorf::operator=(const Vectorf& other)
{
  Vectorf another(other);
  *this = std::move(another);
  return *this;
}

Vectorf& Vectorf::operator=(Vectorf&& other) noexcept
{
  using std::swap;
  swap(*this, other);
  return *this;
}

Vectorf& Vectorf::operator+=(const Vectorf& rhs)
{
  this->axpy(1.0, rhs);
  return *this;
}

Vectorf& Vectorf::operator-=(const Vectorf& rhs)
{
  *this += -rhs;
  return *this;
}

Vectorf& Vectorf::operator*=(const Vectorf& rhs)
{
  this->mul_inplace(rhs);
  return *this;
}

Vectorf& Vectorf::operator/=(const Vectorf& rhs)
{
  this->div_inplace(rhs);
  return *this;
}

Vectorf& Vectorf::operator^=(const Vectorf& rhs)
{
  this->pow_inplace(rhs);
  return *this;
}

Vectorf& Vectorf::operator+=(const float rhs)
{
  this->add_inplace(rhs);
  return *this;
}

Vectorf& Vectorf::operator-=(const float rhs)
{
  this->sub_inplace(rhs);
  return *this;
}

Vectorf& Vectorf::operator*=(const float rhs)
{
  this->mul_inplace(rhs);
  return *this;
}

Vectorf& Vectorf::operator/=(const float rhs)
{
  this->div_inplace(rhs);
  return *this;
}

Vectorf& Vectorf::operator^=(const float rhs)
{
  this->pow_inplace(rhs);
  return *this;
}

// Arithmetic Operators
Vectorf Vectorf::operator+() const
{ return this->clone(); }

Vectorf Vectorf::operator-() const
{
  Vectorf result(this->clone());
  result.scal(-1.0);
  return result;
}

Vectorf Vectorf::operator+(const Vectorf& other) const
{
  Vectorf result(this->clone());
  result += other;
  return result;
}

Vectorf Vectorf::operator-(const Vectorf& other) const
{
  Vectorf result(this->clone());
  result -= other;
  return result;
}

Vectorf Vectorf::operator*(const Vectorf& other) const
{
  Vectorf result(this->clone());
  result *= other;
  return result;
}

Vectorf Vectorf::operator/(const Vectorf& other) const
{
  Vectorf result(this->clone());
  result /= other;
  return result;
}

Vectorf Vectorf::operator^(const Vectorf& other) const
{
  Vectorf result(this->clone());
  result ^= other;
  return result;
}

Vectorf Vectorf::operator+(const float value) const
{
  Vectorf result(this->clone());
  result += value;
  return result;
}

Vectorf Vectorf::operator-(const float value) const
{
  Vectorf result(this->clone());
  result -= value;
  return result;
}

Vectorf Vectorf::operator*(const float value) const
{
  Vectorf result(this->clone());
  result *= value;
  return result;
}

Vectorf Vectorf::operator/(const float value) const
{
  Vectorf result(this->clone());
  result /= value;
  return result;
}

Vectorf Vectorf::operator^(const float value) const
{
  Vectorf result(this->clone());
  result ^= value;
  return result;
}

Vectorf operator+(const float& value, const Vectorf& vector)
{ return vector + value; }

Vectorf operator-(const float& value, const Vectorf& vector)
{ return -vector + value; }

Vectorf operator*(const float& value, const Vectorf& vector)
{ return vector * value; }

Vectorf operator/(const float& value, const Vectorf& vector)
{
  Vectorf result(vector.clone());
  for(std::size_t i = 0; i < result.length; ++i) {
    result[i] = value / result[i];
  }
  return result;
}

Vectorf operator^(const float& value, const Vectorf& vector)
{
  Vectorf result(vector.clone());
  for(std::size_t i = 0; i < result.length; ++i) {
    result[i] = std::pow(value, result[i]);
  }
  return result;
}

// Miscellaneous Operators
float& Vectorf::operator[](const std::size_t index) const
{ return internal::SharedArray<float>::operator[](offset + stride * index); }

float& Vectorf::operator()(const std::size_t index) const
{ return (*this)[index]; }

std::ostream& operator<<(std::ostream& ostream, const Vectorf& vector)
{
  ostream << "[";
  for(std::size_t i = 0; i < vector.size(); ++i) {
    if(i != 0) ostream << " ";
    ostream << vector[i];
  }
  return ostream << "]";
}

//Utilities
void swap(Vectorf& a, Vectorf& b)
{
  using std::swap;
  swap(static_cast<internal::SharedArray<float>&>(a),
            static_cast<internal::SharedArray<float>&>(b));
  swap(a.offset, b.offset);
  swap(a.stride, b.stride);
  swap(a.length, b.length);
}

Vectorf Vectorf::clone() const
{
  Vectorf result(this->length);
  result.copy(*this);
  return result;
}

// Accessors
const std::size_t Vectorf::size() const
{ return length; }

const std::size_t Vectorf::aligned_size() const
{ return internal::align<float>(length); }

// Level 1 BLAS
void Vectorf::swap(Vectorf& other)
{ cblas_sswap(this->length, other.get() + other.offset, other.stride,
                            this->get() + this->offset, this->stride); }

void Vectorf::scal(const float alpha)
{ cblas_sscal(this->length, alpha, this->get() + this->offset, this->stride); }

void Vectorf::copy(const Vectorf& other)
{
  assert(this->length == other.length);
  cblas_scopy(this->length, other.get() + other.offset, other.stride,
                            this->get() + this->offset, this->stride);
}

void Vectorf::axpy(const float alpha, const Vectorf& other)
{
  assert(this->length == other.length);
  cblas_saxpy(this->length, alpha, other.get() + other.offset, other.stride,
                                   this->get() + this->offset, this->stride);
}

const float Vectorf::dot(const Vectorf& other) const
{
  assert(this->length == other.length);
  return cblas_sdot(this->length, other.get() + other.offset, other.stride,
                                  this->get() + this->offset, this->stride);
}

const float Vectorf::nrm2() const
{ return cblas_snrm2(this->length, this->get() + this->offset, this->stride); }

const float Vectorf::asum() const
{ return cblas_sasum(this->length, this->get() + this->offset, this->stride); }

const std::size_t Vectorf::iamax() const
{ return cblas_isamax(this->length, this->get() + this->offset, this->stride); }

// Level 2 BLAS
void Vectorf::gemv(const float alpha, const Matrixf& A,
                   const Vectorf& x, const float beta)
{
  assert(this->length == A.rows());
  assert(x.length == A.cols());
  cblas_sgemv(CblasRowMajor, A.trans, A.rows(), A.cols(),
              alpha, A.get(), A.cols(), x.get() + x.offset, x.stride,
              beta, this->get() + this->offset, this->stride);
}

// Arithmetic Functions
void Vectorf::mul_inplace(const Vectorf& other)
{
  assert(this->length == other.length);
  if(this->length == this->aligned_size()
  && other.length == other.aligned_size()) {
    contiguous_mul_inplace(other);
  } else {
    for(std::size_t i = 0; i < this->length; ++i) {
      (*this)[i] *= other[i];
    }
  }
}

void Vectorf::div_inplace(const Vectorf& other)
{
  assert(this->length == other.length);
  if(this->length == this->aligned_size()
  && other.length == other.aligned_size()) {
    contiguous_div_inplace(other);
  } else {
    for(std::size_t i = 0; i < this->length; ++i) {
      (*this)[i] /= other[i];
    }
  }
}

void Vectorf::pow_inplace(const Vectorf& other)
{
  assert(this->length == other.length);
  for(std::size_t i = 0; i < this->length; ++i) {
    (*this)[i] = std::pow((*this)[i], other[i]);
  }
}

void Vectorf::contiguous_mul_inplace(const Vectorf& other)
{
  __m256* const x = (__m256*)(this->get());
  const __m256* const y = (__m256*)(other.get());
  for(std::size_t i = 0; i < this->aligned_size(); i += 8) {
    __m256 v0 = _mm256_loadu_ps(this->get() + i);
    __m256 v1 = _mm256_loadu_ps(other.get() + i);
    __m256 v2 = _mm256_mul_ps(v0, v1);
    _mm256_storeu_ps(this->get() + i, v2);
  }
}

void Vectorf::contiguous_div_inplace(const Vectorf& other)
{
  __m256* const x = (__m256*)(this->get());
  const __m256* const y = (__m256*)(other.get());
  for(std::size_t i = 0; i < this->aligned_size(); i += 8) {
    __m256 v0 = _mm256_loadu_ps(this->get() + i);
    __m256 v1 = _mm256_loadu_ps(other.get() + i);
    __m256 v2 = _mm256_div_ps(v0, v1);
    _mm256_storeu_ps(this->get() + i, v2);
  }
}

void Vectorf::add_inplace(const float value)
{ for(std::size_t i = 0; i < this->length; ++i) (*this)[i] += value; }

void Vectorf::sub_inplace(const float value)
{ for(std::size_t i = 0; i < this->length; ++i) (*this)[i] -= value; }

void Vectorf::mul_inplace(const float value)
{ for(std::size_t i = 0; i < this->length; ++i) (*this)[i] *= value; }

void Vectorf::div_inplace(const float value)
{ for(std::size_t i = 0; i < this->length; ++i) (*this)[i] /= value; }

void Vectorf::pow_inplace(const float value)
{ for(std::size_t i = 0; i < this->length; ++i)
    (*this)[i] = std::pow((*this)[i], value); }

void Vectorf::log_inplace()
{ for(std::size_t i = 0; i < this->length; ++i)
    (*this)[i] = std::log((*this)[i]); }

void Vectorf::apply_inplace(const std::function<float(float)>& f)
{ for(std::size_t i = 0; i < this->length; ++i) (*this)[i] = f((*this)[i]); }

Vectorf Vectorf::mul(const Vectorf& other) const
{
  Vectorf result(this->clone());
  result.mul_inplace(other);
  return result;
}

Vectorf Vectorf::div(const Vectorf& other) const
{
  Vectorf result(this->clone());
  result.div_inplace(other);
  return result;
}

Vectorf Vectorf::pow(const Vectorf& other) const
{
  Vectorf result(this->clone());
  result.pow_inplace(other);
  return result;
}

Vectorf Vectorf::add(const float value) const
{
  Vectorf result(this->clone());
  result.add_inplace(value);
  return result;
}

Vectorf Vectorf::sub(const float value) const
{
  Vectorf result(this->clone());
  result.sub_inplace(value);
  return result;
}

Vectorf Vectorf::mul(const float value) const
{
  Vectorf result(this->clone());
  result.mul_inplace(value);
  return result;
}

Vectorf Vectorf::div(const float value) const
{
  Vectorf result(this->clone());
  result.div_inplace(value);
  return result;
}

Vectorf Vectorf::pow(const float value) const
{
  Vectorf result(this->clone());
  result.pow_inplace(value);
  return result;
}

Vectorf Vectorf::log() const
{
  Vectorf result(this->clone());
  result.log_inplace();
  return result;
}

Vectorf Vectorf::apply(const std::function<float(float)>& f)
{
  Vectorf result(this->clone());
  result.apply_inplace(f);
  return result;
}

// Extensions
const float Vectorf::sum() const
{
  float sum = 0.0;
  for(std::size_t i = 0; i < length; ++i) {
    sum += (*this)[i];
  }
  return sum;
}

const float Vectorf::maxCoeff() const
{
  float max_v = (*this)[0];
  for(std::size_t i = 1; i < length; ++i) {
    if(max_v < (*this)[i]) {
      max_v = (*this)[i];
    }
  }
  return max_v;
}

const float Vectorf::minCoeff() const
{
  float min_v = (*this)[0];
  for(std::size_t i = 1; i < length; ++i) {
    if(min_v > (*this)[i]) {
      min_v = (*this)[i];
    }
  }
  return min_v;
}

const float Vectorf::maxCoeff(std::size_t& max_i) const
{
  max_i = 0;
  float max_v = (*this)[max_i];
  for(std::size_t i = 1; i < length; ++i) {
    if(max_v < (*this)[i]) {
      max_v = (*this)[i];
      max_i = i;
    }
  }
  return max_v;
}

const float Vectorf::minCoeff(std::size_t& min_i) const
{
  min_i = 0;
  float min_v = (*this)[min_i];
  for(std::size_t i = 1; i < length; ++i) {
    if(min_v > (*this)[i]) {
      min_v = (*this)[i];
      min_i = i;
    }
  }
  return min_v;
}

// Linear Algebra
float Vectorf::inner(const Vectorf& other) const
{ return this->dot(other); }

Vectorf Vectorf::dot(const Matrixf& other) const
{ return Vectorf(Matrixf(*this).dot(other)); }

// Non-member functions
const bool operator==(const Vectorf& a, const Vectorf& b)
{
  assert(a.size() == b.size());
  for(std::size_t i = 0; i < a.size(); ++i) {
    if(a[i] != b[i]) return false;
  }
  return true;
}

const bool operator!=(const Vectorf& a, const Vectorf& b)
{ return !(a == b); }

const bool operator==(const Vectorf& a, const vector1d<float>& b)
{
  assert(a.size() == b.size());
  for(std::size_t i = 0; i < a.size(); ++i) {
    if(a[i] != b[i]) return false;
  }
  return true;
}

const bool operator!=(const Vectorf& a, const vector1d<float>& b)
{ return !(a == b); }

const bool operator==(const vector1d<float>& a, const Vectorf& b)
{ return b == a; }

const bool operator!=(const vector1d<float>& a, const Vectorf& b)
{ return b != a; }

}  // namespace laplus
