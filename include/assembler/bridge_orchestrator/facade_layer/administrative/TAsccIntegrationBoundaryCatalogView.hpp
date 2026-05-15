#pragma once
#include <string_view>

/**
 * @file TAsccIntegrationBoundaryCatalogView.hpp
 * @brief Administrative facade catalog for ASCC integration boundary support.
 */
namespace assembler::communication_context {
    struct TAsccIntegrationBoundaryCatalogView final {
        bool supports_boundary_ports{true};
        bool supports_handoff_requests{true};
        bool supports_export_contract{false};
        std::string_view catalog_name{"ascc_integration_boundary_catalog"};
        [[nodiscard]] constexpr bool is_valid() const noexcept { return !catalog_name.empty(); }
    };
}
