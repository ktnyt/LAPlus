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

#include "benchmark/benchmark.h"
#include "laplus.hpp"

namespace lp = laplus;

static void dot(benchmark::State& state)
{
  int M = state.range(0);
  int K = state.range(1);
  int N = state.range(2);

  lp::Matrixf A(M, K);
  lp::Matrixf B(K, N);

  while(state.KeepRunning()) {
    lp::Matrixf C = A.dot(B);
  }
}

static void Step(benchmark::internal::Benchmark* b)
{
  int m = 1;
  for(int i = 0; i < 3; ++i) {
    m *= 8;

    int n = 1;
    for(int j = 0; j < 3; ++j) {
      n *= 8;

      int o = 1;
      for(int k = 0; k < 3; ++k) {
        o *= 8;

        if((m <= n) &&(n <= o)) b->Args({m, n, o});
      }
    }
  }
}

BENCHMARK(dot)->Apply(Step);

BENCHMARK_MAIN();
