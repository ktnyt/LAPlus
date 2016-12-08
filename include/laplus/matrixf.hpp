/******************************************************************************
 *
 * laplus/matrixf.hpp
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

#ifndef __LAPLUS_MATRIXF_HPP__
#define __LAPLUS_MATRIXF_HPP__

#include "laplus/vectorf.hpp"

#include <cmath>
#include <vector>
#include <ostream>
#include <utility>
#include "cblas.h"

namespace laplus {

class Matrixf : public Vectorf {
  friend class Vectorf;
public:
  // Generators
  static Matrixf Uniform(const std::size_t, const std::size_t);
  static Matrixf Uniform(const std::size_t, const std::size_t, const float);
  static Matrixf Uniform(const std::size_t, const std::size_t,
                         const float, const float);

  static Matrixf Normal(const std::size_t, const std::size_t);
  static Matrixf Normal(const std::size_t, const std::size_t,
                        const float, const float);

  static Matrixf Identity(const std::size_t);

  // Constructors and Destructor
  Matrixf()=delete;
  Matrixf(const std::size_t, const std::size_t);
  Matrixf(const std::pair<std::size_t, std::size_t>);
  Matrixf(const std::vector<float>&, const std::size_t, const std::size_t);
  Matrixf(const std::vector<std::vector<float>>&);
  Matrixf(const Matrixf&);
  Matrixf(Matrixf&&) noexcept;
  explicit Matrixf(const Vectorf&);
  virtual ~Matrixf();

  // Assignment Operators
  Matrixf& operator=(const Matrixf&);
  Matrixf& operator=(Matrixf&&) noexcept;

  Matrixf& operator+=(const Matrixf&);
  Matrixf& operator-=(const Matrixf&);
  Matrixf& operator*=(const Matrixf&);
  Matrixf& operator/=(const Matrixf&);
  Matrixf& operator^=(const Matrixf&);

  Matrixf& operator+=(const float);
  Matrixf& operator-=(const float);
  Matrixf& operator*=(const float);
  Matrixf& operator/=(const float);
  Matrixf& operator^=(const float);

  // Arithmetic Operators
  Matrixf operator+() const;
  Matrixf operator-() const;

  Matrixf operator+(const Matrixf&) const;
  Matrixf operator-(const Matrixf&) const;
  Matrixf operator*(const Matrixf&) const;
  Matrixf operator/(const Matrixf&) const;
  Matrixf operator^(const Matrixf&) const;

  Matrixf operator+(const float) const;
  Matrixf operator-(const float) const;
  Matrixf operator*(const float) const;
  Matrixf operator/(const float) const;
  Matrixf operator^(const float) const;

  friend Matrixf operator+(const float&, const Matrixf&);
  friend Matrixf operator-(const float&, const Matrixf&);
  friend Matrixf operator*(const float&, const Matrixf&);
  friend Matrixf operator/(const float&, const Matrixf&);
  friend Matrixf operator^(const float&, const Matrixf&);

  // Miscellaneous Operators
  const Vectorf operator[](const std::size_t) const;
  float& operator()(const std::size_t, const std::size_t) const;
  friend std::ostream& operator<<(std::ostream&, const Matrixf&);

  // Utilities
  friend void swap(Matrixf&, Matrixf&);
  Matrixf clone() const;
  Matrixf transpose() const;
  Matrixf reshape(const std::size_t, const std::size_t) const;

  // Accessors
  const std::size_t rows() const;
  const std::size_t cols() const;
  const std::size_t ldim() const;
  const Vectorf row(const std::size_t) const;
  const Vectorf col(const std::size_t) const;

  void set_row(const std::size_t, const Vectorf&);
  void set_col(const std::size_t, const Vectorf&);

  // Level 2 BLAS
  void ger(const float, const Vectorf&, const Vectorf&);

  // Level 3 BLAS
  void gemm(const float, const Matrixf&, const Matrixf&, const float);

  // Arithmetic Functions
  Matrixf mul(const Matrixf&) const;
  Matrixf div(const Matrixf&) const;
  Matrixf pow(const Matrixf&) const;

  Matrixf add(const float) const;
  Matrixf sub(const float) const;
  Matrixf mul(const float) const;
  Matrixf div(const float) const;
  Matrixf pow(const float) const;

  Matrixf log() const;

  Matrixf apply(const std::function<float(float)>&);

  // Extensions
  const float maxCoeff() const;
  const float minCoeff() const;

  const float maxCoeff(std::size_t&, std::size_t&) const;
  const float minCoeff(std::size_t&, std::size_t&) const;

  // Linear Algebra
  Matrixf dot(const Matrixf&) const;
  Vectorf dot(const Vectorf&) const;
  void dot(const Matrixf&, const Matrixf&);
private:
  std::pair<std::size_t, std::size_t> shape;
  CBLAS_TRANSPOSE trans;
};

const bool operator==(const Matrixf&, const Matrixf&);
const bool operator!=(const Matrixf&, const Matrixf&);

const bool operator==(const Matrixf&, const std::vector<float>&);
const bool operator!=(const Matrixf&, const std::vector<float>&);

const bool operator==(const std::vector<float>&, const Matrixf&);
const bool operator!=(const std::vector<float>&, const Matrixf&);

const bool operator==(const Matrixf&, const std::vector<std::vector<float>>&);
const bool operator!=(const Matrixf&, const std::vector<std::vector<float>>&);

const bool operator==(const std::vector<std::vector<float>>&, const Matrixf&);
const bool operator!=(const std::vector<std::vector<float>>&, const Matrixf&);

}  // namespace laplus

#endif  // __LAPLUS_MATRIXF_HPP__
