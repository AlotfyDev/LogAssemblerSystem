#pragma once
#include "../TCirculationRuntimeDescriptor.hpp"

/*
    TCirculationRuntimeView.hpp

    Responsibility:
        Read-only projection of shared runtime descriptor.
*/
namespace assembler {
namespace circulation_mechanism {

struct TCirculationRuntimeView final {
    TCirculationRuntimeDescriptor runtime{};
    [[nodiscard]] constexpr bool is_valid() const noexcept { return runtime.is_valid(); }
    [[nodiscard]] constexpr bool configured() const noexcept { return runtime.configured(); }
};
} // namespace circulation_mechanism
} // namespace assembler
