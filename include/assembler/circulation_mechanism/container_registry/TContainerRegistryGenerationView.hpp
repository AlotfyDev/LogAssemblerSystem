#pragma once
#include <cstdint>
namespace assembler {
namespace circulation_mechanism {

struct TContainerRegistryGenerationView final {
    std::uint64_t generation{0};
    [[nodiscard]] constexpr bool is_valid() const noexcept { return generation > 0U; }
};
} // namespace circulation_mechanism
} // namespace assembler
