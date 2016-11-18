/******************************************************************************
 *
 * laplus/vectorf.hpp
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

#ifndef __LAPLUS_VECTORF_HPP__
#define __LAPLUS_VECTORF_HPP__

#include "laplus/internal/shared_array.hpp"

#include <cmath>
#include <vector>
#include <ostream>
#include <functional>
#include <memory>
#include "cblas.h"

namespace laplus {

class Matrixf;

class Vectorf : public internal::SharedArray<float> {
  friend class Matrixf;
public:
  // Constructors and Destructor
  Vectorf()=delete;
  Vectorf(const std::size_t);
  Vectorf(const std::vector<float>&);
  Vectorf(const Vectorf&);
  Vectorf(Vectorf&&) noexcept;
  Vectorf(const Vectorf&, std::size_t, std::size_t, std::size_t);
  virtual ~Vectorf();

  // Assignment Operators
  Vectorf& operator=(const Vectorf&);
  Vectorf& operator=(Vectorf&&) noexcept;

  Vectorf& operator+=(const Vectorf&);
  Vectorf& operator-=(const Vectorf&);
  Vectorf& operator*=(const Vectorf&);
  Vectorf& operator/=(const Vectorf&);
  Vectorf& operator^=(const Vectorf&);

  Vectorf& operator+=(const float);
  Vectorf& operator-=(const float);
  Vectorf& operator*=(const float);
  Vectorf& operator/=(const float);
  Vectorf& operator^=(const float);

  // Arithmetic Operators
  Vectorf operator+() const;
  Vectorf operator-() const;

  Vectorf operator+(const Vectorf&) const;
  Vectorf operator-(const Vectorf&) const;
  Vectorf operator*(const Vectorf&) const;
  Vectorf operator/(const Vectorf&) const;
  Vectorf operator^(const Vectorf&) const;

  Vectorf operator+(const float) const;
  Vectorf operator-(const float) const;
  Vectorf operator*(const float) const;
  Vectorf operator/(const float) const;
  Vectorf operator^(const float) const;

  friend Vectorf operator+(const float&, const Vectorf&);
  friend Vectorf operator-(const float&, const Vectorf&);
  friend Vectorf operator*(const float&, const Vectorf&);
  friend Vectorf operator/(const float&, const Vectorf&);
  friend Vectorf operator^(const float&, const Vectorf&);

  // Miscellaneous Operators
  float& operator[](const std::size_t) const;
  float& operator()(const std::size_t) const;
  friend std::ostream& operator<<(std::ostream&, const Vectorf&);

  // Utilities
  friend void swap(Vectorf&, Vectorf&);
  Vectorf clone() const;

  // Accessors
  const std::size_t size() const;

  // Level 1 BLAS
  void swap(Vectorf&);
  void scal(const float);
  void copy(const Vectorf&);
  void axpy(const float, const Vectorf&);
  const float dot(const Vectorf&) const;
  const float nrm2() const;
  const float asum() const;
  const std::size_t iamax() const;

  // Level 2 BLAS
  void gemv(const float, const Matrixf&, const Vectorf&, const float);

  // Arithmetic Functions
  void mul_inplace(const Vectorf&);
  void div_inplace(const Vectorf&);
  void pow_inplace(const Vectorf&);

  void add_inplace(const float);
  void sub_inplace(const float);
  void mul_inplace(const float);
  void div_inplace(const float);
  void pow_inplace(const float);

  void log_inplace();

  Vectorf mul(const Vectorf&) const;
  Vectorf div(const Vectorf&) const;
  Vectorf pow(const Vectorf&) const;

  Vectorf add(const float) const;
  Vectorf sub(const float) const;
  Vectorf mul(const float) const;
  Vectorf div(const float) const;
  Vectorf pow(const float) const;

  Vectorf log() const;

  void apply_inplace(const std::function<float(float)>&);
  Vectorf apply(const std::function<float(float)>&);

  // Extensions
  const float maxCoeff() const;
  const float minCoeff() const;

  const float maxCoeff(std::size_t&) const;
  const float minCoeff(std::size_t&) const;
private:
  std::size_t offset;
  std::size_t stride;
  std::size_t length;
};

// Non-member functions
const bool operator==(const Vectorf& a, const Vectorf& b);
const bool operator!=(const Vectorf& a, const Vectorf& b);

const bool operator==(const Vectorf& a, const std::vector<float>& b);
const bool operator!=(const Vectorf& a, const std::vector<float>& b);

const bool operator==(const std::vector<float>& a, const Vectorf& b);
const bool operator!=(const std::vector<float>& a, const Vectorf& b);

}  // namespace laplus

#endif  // __LAPLUS_VECTORF_HPP__
