#pragma once
#include <array>
#include <cstddef>
#include "assembler/communication_context/diagnostics/runtime/TDiagnosticSourceKind.hpp"

/**
 * @file TDiagnosticSourceRegistry.hpp
 * @brief Bounded registry of enabled diagnostic sources for an ASCC component profile.
 */
namespace assembler::communication_context {
    template <std::size_t Capacity>
    struct TDiagnosticSourceRegistry final {
        std::array<TDiagnosticSourceKind, Capacity> sources{};
        std::size_t count{0u};

        [[nodiscard]] constexpr bool is_valid() const noexcept { return count <= Capacity; }

        constexpr bool enable(TDiagnosticSourceKind source) noexcept {
            if (count >= Capacity || source == TDiagnosticSourceKind::unknown) return false;
            sources[count++] = source;
            return true;
        }

        [[nodiscard]] constexpr bool includes(TDiagnosticSourceKind source) const noexcept {
            for (std::size_t i = 0u; i < count; ++i) if (sources[i] == source) return true;
            return false;
        }
    };
}
