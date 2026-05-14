#pragma once
#include <array>
#include <cstddef>
#include <string_view>
#include "assembler/communication_context/bridge_carriers/kinds/TAsccCarrierKind.hpp"
namespace assembler::communication_context
{
    template <std::size_t Capacity>
    struct TAsccCarrierCatalogView final
    {
        std::array<TAsccCarrierKind, Capacity> supported_carriers{};
        std::size_t count{0u};
        std::string_view catalog_name{"ascc_carrier_catalog"};
        [[nodiscard]] constexpr bool is_valid() const noexcept { return count <= Capacity && !catalog_name.empty(); }
        constexpr bool add(TAsccCarrierKind kind) noexcept
        {
            if (count >= Capacity || kind == TAsccCarrierKind::unknown) return false;
            supported_carriers[count++] = kind;
            return true;
        }
        [[nodiscard]] constexpr bool supports(TAsccCarrierKind kind) const noexcept
        {
            for (std::size_t i = 0u; i < count; ++i) if (supported_carriers[i] == kind) return true;
            return false;
        }
    };
}
