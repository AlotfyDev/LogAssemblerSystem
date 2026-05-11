#pragma once
#include <cstdint>
namespace assembler {
namespace circulation_mechanism {

enum class TIngressBoundaryStatus : std::uint8_t { unbound, bound, ready, blocked, mismatch, closed };
} // namespace circulation_mechanism
} // namespace assembler
