#pragma once
#include <cstdint>
namespace assembler {
namespace circulation_mechanism {

struct TRegistryProfileSwitchReport final {
    std::uint64_t before_generation{0};
    std::uint64_t after_generation{0};
    bool accepted{false};
    [[nodiscard]] constexpr bool is_valid() const noexcept { return before_generation > 0U && after_generation > before_generation; }
    [[nodiscard]] constexpr bool switched() const noexcept { return accepted && is_valid(); }
};
} // namespace circulation_mechanism
} // namespace assembler
