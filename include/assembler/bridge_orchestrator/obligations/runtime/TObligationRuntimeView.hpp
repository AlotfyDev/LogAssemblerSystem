#pragma once
#include <cstddef>
#include <string_view>

/**
 * @file TObligationRuntimeView.hpp
 * @brief Read-only runtime view for ASCC obligation execution support.
 */
namespace assembler::communication_context {
    struct TObligationRuntimeView final {
        std::size_t invocation_count{0u};
        std::size_t failed_invocations{0u};
        bool runtime_ready{false};
        std::string_view runtime_name{"obligation_runtime"};
        [[nodiscard]] constexpr bool is_valid() const noexcept { return !runtime_name.empty(); }
        [[nodiscard]] constexpr bool ready() const noexcept { return is_valid() && runtime_ready; }
    };
}
