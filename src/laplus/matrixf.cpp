/******************************************************************************
 *
 * laplus/matrixf.cpp
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

#include "laplus/matrixf.hpp"
#include "laplus/typedef.hpp"

namespace laplus {

namespace {

vector1d<float> flatten(const vector2d<float>& vectors)
{
  vector1d<float> result;
  for(const vector1d<float>& vector: vectors) {
    for(const float& value: vector) {
      result.push_back(value);
    }
  }
  return result;
}

shape_t get_shape(const vector2d<float>& vectors)
{
  std::size_t rows = vectors.size();
  std::size_t cols = vectors.front().size();
  for(const vector1d<float>& vector: vectors) {
    assert(vector.size() == cols);
  }
  return std::pair<std::size_t, std::size_t>(rows, cols);
}

shape_t flip(const shape_t& shape)
{ return shape_t(shape.second, shape.first); }

}  // unnamed namespace

// Constructors and Destructor
Matrixf::Matrixf(const std::size_t rows, const std::size_t cols)
  : Vectorf(rows * cols), shape(shape_t(rows, cols)), trans(CblasNoTrans)
{}

Matrixf::Matrixf(const shape_t shape)
  : Vectorf(shape.first * shape.second), shape(shape), trans(CblasNoTrans)
{}

Matrixf::Matrixf(const vector1d<float>& values,
                 const std::size_t rows, const std::size_t cols)
  : Vectorf(values), shape(shape_t(rows, cols)), trans(CblasNoTrans)
{ assert(values.size() == rows * cols); }

Matrixf::Matrixf(const vector2d<float>& values)
  : Vectorf(flatten(values)), shape(get_shape(values)), trans(CblasNoTrans)
{}

Matrixf::Matrixf(const Matrixf& other)
  : Vectorf(other), shape(other.shape), trans(other.trans)
{}

Matrixf::Matrixf(Matrixf&& other) noexcept
  : Vectorf(std::forward<Matrixf>(other))
  , shape(other.shape), trans(other.trans)
{ other.shape = shape_t(0, 0); }

Matrixf::~Matrixf() {}

// Assignment Operators
Matrixf& Matrixf::operator=(const Matrixf& other)
{
  Matrixf another(other);
  *this = std::move(another);
  return *this;
}

Matrixf& Matrixf::operator=(Matrixf&& other) noexcept
{
  using std::swap;
  swap(*this, other);
  return other;
}

// Miscellaneous Operators
const Vectorf Matrixf::operator[](const std::size_t index) const
{
  if(trans == CblasTrans)
    return Vectorf(*this, index, shape.first, shape.second);
  return Vectorf(*this, index * shape.second, 1, shape.second);
}

float& Matrixf::operator()(const std::size_t i, const std::size_t j) const
{
  if(trans == CblasTrans)
    return Vectorf::operator[](i + shape.first * j);
  return Vectorf::operator[](i * shape.second + j);
}

std::ostream& operator<<(std::ostream& ostream, const Matrixf& matrix)
{
  ostream << "[";
  for(std::size_t i = 0; i < matrix.rows(); ++i) {
    if(i != 0) ostream << std::endl << " ";
    ostream << matrix[i];
  }
  return ostream << "]";
}

// Utilities
void swap(Matrixf& a, Matrixf& b)
{
  using std::swap;
  swap(static_cast<Vectorf&>(a), static_cast<Vectorf&>(b));
  swap(a.shape, b.shape);
  swap(a.trans, b.trans);
}

Matrixf Matrixf::clone() const
{
  Matrixf other(this->shape);
  other.copy(*this);
  return other;
}

Matrixf Matrixf::transpose() const
{
  Matrixf other(*this);
  other.shape = flip(shape);
  other.trans = (trans == CblasTrans) ? CblasNoTrans : CblasTrans;
  return other;
}

Matrixf Matrixf::reshape(const std::size_t rows, const std::size_t cols) const
{
  assert(rows * cols == this->size());
  Matrixf other(*this);
  other.shape = shape_t(rows, cols);
  return other;
}

// Accessors
const std::size_t Matrixf::rows() const
{ return shape.first; }

const std::size_t Matrixf::cols() const
{ return shape.second; }

const std::size_t Matrixf::ldim() const
{ return (trans == CblasTrans) ? rows() : cols(); }

// Level 2 BLAS
void Matrixf::ger(const float alpha, const Vectorf& x, const Vectorf& y)
{
  assert(this->rows() == x.size());
  assert(this->cols() == y.size());
  cblas_sger(CblasRowMajor, this->rows(), this->cols(), alpha,
             x.get() + x.offset, x.stride, y.get() + y.offset, y.stride,
             this->get(), this->cols());
}

// Level 3 BLAS
void Matrixf::gemm(const float alpha, const Matrixf& A,
                   const Matrixf& B, const float beta)
{
  assert(this->rows() == A.rows());
  assert(this->cols() == B.cols());
  assert(A.cols() == B.rows());
  std::size_t ldb = (B.trans == CblasTrans) ? B.rows() : B.cols();
  cblas_sgemm(CblasRowMajor, A.trans, B.trans, A.rows(), B.cols(), A.cols(),
              alpha, A.get(), A.ldim(), B.get(), B.ldim(),
              beta, this->get(), this->ldim());
}

// Extensions
const float Matrixf::maxCoeff(std::size_t& max_i, std::size_t& max_j) const
{
  float max_v = (*this)(0, 0);
  for(std::size_t i = 1; i < this->rows(); ++i) {
    for(std::size_t j = 1; j < this->cols(); ++j) {
      if(max_v < (*this)(i, j)) {
        max_v = (*this)(i, j);
        max_i = i;
        max_j = j;
      }
    }
  }
  return max_v;
}

const float Matrixf::minCoeff(std::size_t& min_i, std::size_t& min_j) const
{
  float min_v = (*this)(0, 0);
  for(std::size_t i = 1; i < this->rows(); ++i) {
    for(std::size_t j = 1; j < this->cols(); ++j) {
      if(min_v > (*this)(i, j)) {
        min_v = (*this)(i, j);
        min_i = i;
        min_j = j;
      }
    }
  }
  return min_v;
}

// Linear Algebra
Matrixf Matrixf::dot(const Matrixf& other) const
{
  Matrixf result(this->rows(), other.cols());
  result.gemm(1.0, *this, other, 0.0);
  return result;
}

const bool operator==(const Matrixf& a, const Matrixf& b)
{
  assert(a.rows() == b.rows());
  assert(a.cols() == b.cols());
  for(std::size_t i = 0; i < a.rows(); ++i) {
    for(std::size_t j = 0; j < b.cols(); ++j) {
      if(a(i, j) != b(i, j)) return false;
    }
  }
  return true;
}

const bool operator!=(const Matrixf& a, const Matrixf& b)
{ return !(a == b); }

const bool operator==(const Matrixf& matrix, const vector1d<float>& vector)
{
  std::size_t k = 0;
  for(std::size_t i = 0; i < matrix.rows(); ++i) {
    for(std::size_t j = 0; j < matrix.cols(); ++j, ++k) {
      if(matrix(i, j) != vector[k]) return false;
    }
  }
  return true;
}

const bool operator!=(const Matrixf& matrix, const vector1d<float>& vector)
{ return !(matrix == vector); }

const bool operator==(const Matrixf& matrix, const vector2d<float>& vector)
{
  for(std::size_t i = 0; i < matrix.rows(); ++i) {
    for(std::size_t j = 0; j < matrix.cols(); ++j) {
      if(matrix(i, j) != vector[i][j]) return false;
    }
  }
  return true;
}

const bool operator!=(const Matrixf& matrix, const vector2d<float>& vector)
{ return !(matrix == vector); }

const bool operator==(const vector1d<float>& vector, const Matrixf& matrix)
{ return matrix == vector; }

const bool operator!=(const vector1d<float>& vector, const Matrixf& matrix)
{ return matrix != vector; }

const bool operator==(const vector2d<float>& vector, const Matrixf& matrix)
{ return matrix == vector; }

const bool operator!=(const vector2d<float>& vector, const Matrixf& matrix)
{ return matrix != vector; }

}  // namespace laplus