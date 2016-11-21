/******************************************************************************
 *
 * laplus/math.cpp
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

#include "laplus/math.hpp"

#include <cmath>
#include <algorithm>

namespace laplus {

float sigmoid(const float x)
{ return std::tanh(x * 0.5) * 0.5 + 0.5; }

float dsigmoid(const float y)
{ return y * (1.0 - y); }

float tanh(const float x)
{ return std::tanh(x); }

float dtanh(const float y)
{ return 1 - (y * y); }

float relu(const float x)
{ return std::max(0.0, x); }

float relu(const float y)
{ return y > 0.0 ? 1.0 : 0.0; }

}  // namespace laplus


