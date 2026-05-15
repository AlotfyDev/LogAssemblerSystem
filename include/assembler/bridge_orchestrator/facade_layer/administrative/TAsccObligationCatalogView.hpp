#pragma once
#include <string_view>

/**
 * @file TAsccObligationCatalogView.hpp
 * @brief Administrative facade catalog for ASCC obligation support.
 */
namespace assembler::communication_context {
    struct TAsccObligationCatalogView final {
        bool supports_plugin_adapter_obligations{false};
        bool supports_port_obligations{false};
        bool supports_primary_placement_flow{false};
        std::string_view catalog_name{"ascc_obligation_catalog"};
        [[nodiscard]] constexpr bool is_valid() const noexcept { return !catalog_name.empty(); }
    };
}
