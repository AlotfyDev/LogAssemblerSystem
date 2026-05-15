#pragma once
#include <string_view>

/**
 * @file TAsccDiagnosticCatalogView.hpp
 * @brief Administrative facade catalog for ASCC diagnostic capabilities.
 */
namespace assembler::communication_context {
    struct TAsccDiagnosticCatalogView final {
        bool supports_bridge_diagnostics{true};
        bool supports_registry_diagnostics{true};
        bool supports_runtime_collection{true};
        bool supports_export_boundary{false};
        std::string_view catalog_name{"ascc_diagnostic_catalog"};

        [[nodiscard]] constexpr bool is_valid() const noexcept {
            return !catalog_name.empty();
        }
    };
}
