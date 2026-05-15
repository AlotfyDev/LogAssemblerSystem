#pragma once
#include <cstddef>
#include <string_view>

/**
 * @file TIntegrationBoundaryRuntimeView.hpp
 * @brief Read-only runtime view for integration boundary handoff subsystem.
 */
namespace assembler::communication_context {
    struct TIntegrationBoundaryRuntimeView final {
        std::size_t accepted_count{0u};
        std::size_t completed_count{0u};
        std::size_t failed_count{0u};
        bool runtime_ready{false};
        std::string_view runtime_name{"integration_boundary_runtime"};
        [[nodiscard]] constexpr bool is_valid() const noexcept { return !runtime_name.empty(); }
        [[nodiscard]] constexpr bool ready() const noexcept { return is_valid() && runtime_ready; }
    };
}
