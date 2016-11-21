/******************************************************************************
 *
 * dfa_layer.cpp
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

#include "dfa_layer.hpp"
#include <cmath>

namespace lp = laplus;

DFALayer::DFALayer(const std::size_t n_input,
                   const std::size_t n_output,
                   const std::size_t n_final)
  : W(lp::Matrixf::Normal(n_input, n_output, 0.0, std::sqrt((float)n_input)))
  , B(lp::Matrixf::Normal(n_final, n_output, 0.0, std::sqrt((float)n_final)))
{
  W /= std::sqrt(static_cast<float>(n_input));
  B /= std::sqrt(static_cast<float>(n_final));
}

lp::Matrixf DFALayer::operator()(lp::Matrixf x)
{ return x.dot(W).apply(lp::sigmoid); }

void DFALayer::update(lp::Matrixf e, lp::Matrixf x, lp::Matrixf y, float lr)
{
  lp::Matrixf d_x = e.dot(B) * y.apply(lp::dsigmoid);
  lp::Matrixf d_W = -x.transpose().dot(d_x);
  W += d_W * lr;
}
