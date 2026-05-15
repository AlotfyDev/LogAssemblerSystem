#pragma once

/**
 * @file TDiagnosticBuilderRegistry.hpp
 * @brief Bounded/static catalog of diagnostic builders available in ASCC.
 */
namespace assembler::communication_context {
    struct TDiagnosticBuilderRegistry final {
        bool bridge_builder_available{true};
        bool registry_builder_available{true};
        bool protocol_builder_available{false};
        bool session_builder_available{false};

        [[nodiscard]] constexpr bool is_valid() const noexcept {
            return bridge_builder_available || registry_builder_available || protocol_builder_available || session_builder_available;
        }
    };
}
