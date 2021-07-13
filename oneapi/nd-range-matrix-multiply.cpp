// Copyright (C) 2020 Intel Corporation

// SPDX-License-Identifier: MIT

#include <CL/sycl.hpp>
#include <algorithm>
#include <iostream>
#include <random>
#include <iomanip>
#include <chrono>
using namespace sycl;

#if defined(__clang__)
  #pragma clang diagnostic push
  #pragma clang diagnostic ignored "-Wpass-failed"
#endif

int main() {
  // Set up queue on any available device
  queue Q;

  // Initialize input and output memory on the host
  constexpr size_t N = 256;
  constexpr size_t B = 4;
  std::vector<float> a(N * N), b(N * N), c(N * N);
  std::default_random_engine gen(42);
  std::uniform_real_distribution<float> dist(0.0, 1.0);
  auto rng = [&]() {
    return dist(gen);
  };
  std::generate(a.begin(), a.end(), rng);
  std::generate(b.begin(), b.end(), rng);
  std::fill(c.begin(), c.end(), 0);

  auto start = std::chrono::high_resolution_clock::now();
  {
    // Create buffers associated with inputs and output
    buffer<float, 2> a_buf(a.data(), range<2>(N, N)),
        b_buf(b.data(), range<2>(N, N)), c_buf(c.data(), range<2>(N, N));

    // Submit the kernel to the queue
    Q.submit([&](handler& h) {
      accessor a{a_buf, h};
      accessor b{b_buf, h};
      accessor c{c_buf, h};

// START CODE SNIP
      range global{N, N};
      range local{B, B};
      h.parallel_for(nd_range{global, local}, [=](nd_item<2> it) {
        int j = it.get_global_id(0);
        int i = it.get_global_id(1);

        for (int k = 0; k < N; ++k) {
          c[j][i] += a[j][k] * b[k][i];
        }
// END CODE SNIP
      });
    });
  }
  auto elapsed = std::chrono::high_resolution_clock::now() - start;
  long long microseconds = std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count();

  // Check that all outputs match serial execution.
  auto start_check = std::chrono::high_resolution_clock::now();
  bool passed = true;
  int item = 0;
  for (int j = 0; j < N; ++j) {
    for (int i = 0; i < N; ++i) {
      float gold = 0;
      for (int k = 0; k < N; ++k) {
        gold += a[j * N + k] * b[k * N + i];
      }
      std::cout << std::setfill('0') << std::setw(7) << std::fixed << std::setprecision(4)  << c[j * N + i] << " ";
      item++;
      if(item % 16 == 0) std::cout << std::endl;
      if (std::abs(gold - c[j * N + i]) / gold > 1.0E-06) {
        passed = false;
      }
    }
  }
  auto elapsed_check = std::chrono::high_resolution_clock::now() - start;
  long long microseconds_check = std::chrono::duration_cast<std::chrono::microseconds>(elapsed_check).count();

  std::cout << "================================================================" << std::endl;
  std::cout << "Elapsed microseconds : " << microseconds << std::endl;
  std::cout << "Elapsed microseconds for check : " << microseconds_check << std::endl;
  std::cout << ((passed) ? "SUCCESS" : "FAILURE") << std::endl;
  return (passed) ? 0 : 1;
}

#if defined(__clang__)
  #pragma clang diagnostic pop
#endif
