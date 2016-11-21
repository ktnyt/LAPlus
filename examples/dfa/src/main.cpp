/******************************************************************************
 *
 * main.cpp
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

#include <iostream>
#include <iomanip>
#include <vector>
#include "mnist/mnist_reader.hpp"
#include "layer.hpp"
#include "dfa_layer.hpp"
#include "laplus.hpp"

namespace lp = laplus;

float cross_entropy(lp::Matrixf y, lp::Matrixf t) {
  return (-y * (t + 1e-10f).log()).sum() / t.rows();
}

float accuracy(lp::Matrixf y, lp::Matrixf t) {
  float total = 0.0f;
  for(std::size_t i = 0; i < y.rows(); ++i) {
    std::size_t max_y, max_t;
    y[i].maxCoeff(max_y);
    t[i].maxCoeff(max_t);
    if(max_y == max_t) {
      total += 1.0;
    }
  }
  return total / y.rows();
}

int main() {
  auto mnist = mnist::read_dataset<std::vector, std::vector, unsigned char, unsigned char>();

  std::vector<std::vector<unsigned char> > train_images = mnist.training_images;
  std::vector<unsigned char> train_labels = mnist.training_labels;

  std::vector<std::vector<unsigned char> > test_images = mnist.test_images;
  std::vector<unsigned char> test_labels = mnist.test_labels;

  std::size_t N_train = train_images.size();
  std::size_t N_test = test_images.size();
  std::size_t x_shape = train_images[0].size();
  std::size_t y_shape = 10;
  std::size_t n_epoch = 20;

  lp::Matrixf x_train(N_train, x_shape);
  lp::Matrixf y_train(N_train, y_shape);

  lp::Matrixf x_test(N_test, x_shape);
  lp::Matrixf y_test(N_test, y_shape);

  for(std::size_t i = 0; i < N_train; ++i) {
    for(std::size_t j = 0; j < x_shape; ++j) {
      x_train(i, j) = static_cast<float>(train_images[i][j]) / 255.0;
    }
    for(std::size_t j = 0; j < y_shape; ++j) {
      y_train(i, j) = train_labels[i] == j ? 1.0f : 0.0f;
    }
    if(i < N_test) {
      for(std::size_t j = 0; j < x_shape; ++j) {
        x_test(i, j) = static_cast<float>(test_images[i][j]) / 255.0;
      }
      for(std::size_t j = 0; j < y_shape; ++j) {
        y_test(i, j) = test_labels[i] == j ? 1.0f : 0.0f;
      }
    }
  }

  std::vector<std::size_t> perm;
  for(std::size_t i = 0; i < N_train; ++i) {
    perm.push_back(i);
  }

  std::size_t batchsize = 100;

  DFALayer layer0(28 * 28, 1000, 10);
  Layer layer1(1000, 10);  

  for(std::size_t epoch = 0; epoch < n_epoch; ++epoch) {
    std::cerr << "Epoch: " << epoch + 1 << std::endl;
    std::random_shuffle(perm.begin(), perm.end());

    { /* Training */
      float acc = 0.0f;
      float loss = 0.0f;

      for(std::size_t i = 0; i < N_train; i += batchsize) {
        std::vector<std::size_t> indices(perm.begin() + i, perm.begin() + i + batchsize);

        lp::Matrixf x(batchsize, x_shape);
        lp::Matrixf t(batchsize, y_shape);

        for(std::size_t i = 0; i < batchsize; ++i) {
          x.set_row(i, x_train.row(indices[i]));
          t.set_row(i, y_train.row(indices[i]));
        }

        lp::Matrixf h = layer0(x);
        lp::Matrixf y = layer1(h);
        lp::Matrixf e = y - t;

        layer0.update(e, x, h, 0.1);
        layer1.update(e, h, 0.1);

        loss += cross_entropy(y, t) * batchsize;
        acc += accuracy(y, t) * batchsize;
      }

      std::cerr
        << "Train Loss: " << std::setprecision(7) << std::setw(8) << loss / N_train
        << "\tAccuracy: "  << std::setprecision(4) << std::setw(5) << acc / N_train * 100
        << "%" << std::endl;
    }

    { /* Training */
      float acc = 0.0f;
      float loss = 0.0f;

      for(std::size_t i = 0; i < N_test; i += batchsize) {
        lp::Matrixf x(batchsize, x_shape);
        lp::Matrixf t(batchsize, y_shape);

        for(std::size_t i = 0; i < batchsize; ++i) {
          x.set_row(i, x_test.row(i));
          t.set_row(i, y_test.row(i));
        }

        lp::Matrixf h = layer0(x);
        lp::Matrixf y = layer1(h);

        loss += cross_entropy(y, t) * batchsize;
        acc += accuracy(y, t) * batchsize;
      }

      std::cerr
        << "Test Loss:  " << std::setprecision(7) << std::setw(8) << loss / N_test
        << "\tAccuracy: "  << std::setprecision(4) << std::setw(5) << acc / N_test * 100
        << "%" << std::endl;
    }
  }

  return 0;
}
