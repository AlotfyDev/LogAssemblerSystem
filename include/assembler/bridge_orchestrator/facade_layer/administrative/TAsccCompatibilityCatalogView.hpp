#pragma once
#include <string_view>

/**
 * @file TAsccCompatibilityCatalogView.hpp
 * @brief Administrative facade catalog of supported ASCC compatibility profiles.
 */
namespace assembler::communication_context {
    struct TAsccCompatibilityCatalogView final {
        bool strict_binding_profile_available{true};
        bool component_admission_profile_available{true};
        std::string_view catalog_name{"ascc_compatibility_catalog"};
        [[nodiscard]] constexpr bool is_valid() const noexcept { return !catalog_name.empty(); }
    };
}
