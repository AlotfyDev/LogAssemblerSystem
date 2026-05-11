#pragma once
#include "TContainerRegistryOperationStatus.hpp"
#include "assembler/circulation_mechanism/ids/TContainerRegistryIndex.hpp"

namespace assembler {
namespace circulation_mechanism {

struct TContainerRegistryOperationResult final {
    TContainerRegistryOperationStatus status{TContainerRegistryOperationStatus::not_attempted};
    TContainerRegistryIndex index{};
    std::uint64_t before_generation{0};
    std::uint64_t after_generation{0};

    [[nodiscard]] constexpr bool accepted() const noexcept { return status == TContainerRegistryOperationStatus::accepted; }
    [[nodiscard]] constexpr bool rejected() const noexcept { return !accepted(); }
    [[nodiscard]] constexpr bool generation_changed() const noexcept { return before_generation != after_generation; }
};
} // namespace circulation_mechanism
} // namespace assembler
