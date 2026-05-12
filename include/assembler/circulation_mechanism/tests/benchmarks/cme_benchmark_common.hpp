#pragma once
#include <chrono>
#include <cstdint>
#include <iostream>

namespace cme_bench {
struct BenchmarkResult final {
    const char* name{""};
    std::uint64_t iterations{0};
    std::uint64_t elapsed_ns{0};
    void print() const {
        std::cout << name << ",iterations=" << iterations << ",elapsed_ns=" << elapsed_ns << '\n';
    }
};

template <typename Fn>
BenchmarkResult run(const char* name, std::uint64_t iterations, Fn&& fn) {
    const auto start = std::chrono::steady_clock::now();
    for (std::uint64_t i = 0; i < iterations; ++i) {
        fn(i);
    }
    const auto end = std::chrono::steady_clock::now();
    return BenchmarkResult{
        name,
        iterations,
        static_cast<std::uint64_t>(std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count())
    };
}
}
