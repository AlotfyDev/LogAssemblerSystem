#pragma once

#include <string_view>

/**
 * @file TAsccRegistryCatalogView.hpp
 * @brief Administrative facade view over ASCC registry catalogs.
 *
 * @section purpose Purpose
 * Exposes registry catalog counts/capacity information to Pipeline Composer
 * without exposing mutable registry internals.
 */

namespace assembler::communication_context
{
    struct TAsccRegistryCatalogView final
    {
        std::size_t channel_count{0u};
        std::size_t binding_count{0u};
        std::size_t session_count{0u};
        std::size_t protocol_count{0u};
        std::size_t bridge_count{0u};
        std::string_view catalog_name{"ascc_registry_catalog"};

        [[nodiscard]] constexpr bool is_valid() const noexcept
        {
            return !catalog_name.empty();
        }

        [[nodiscard]] constexpr std::size_t total_count() const noexcept
        {
            return channel_count + binding_count + session_count + protocol_count + bridge_count;
        }
    };
}
