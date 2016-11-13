/******************************************************************************
 *
 * laplus/benchmark.cpp
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

#include "laplus.hpp"
#include "benchmark/benchmark.h"

namespace lp = laplus;

static void DOT1024(benchmark::State& state)
{
  lp::Array<1024, 1024> a0(1.0);
  lp::Array<1024, 1024> a1(1.0);
  lp::Array<1024, 1024> a2;

  while(state.KeepRunning()) {
    a2.dot_inplace(a1, a0);
  }
}

static void GEMM1024(benchmark::State& state)
{
  lp::Array<1024, 1024> a0(1.0);
  lp::Array<1024, 1024> a1(1.0);
  lp::Array<1024, 1024> a2;

  while(state.KeepRunning()) {
    a2.gemm(1.0, a0, a1, 0.0);
  }
}

BENCHMARK(DOT1024);
BENCHMARK(GEMM1024);

BENCHMARK_MAIN();
