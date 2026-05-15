#pragma once

#include <array>
#include <string_view>

#include "assembler/communication_context/bridge_carriers/kinds/TAsccCarrierKind.hpp"

/**
 * @file TCarrierProtocolBindingMap.hpp
 * @brief Canonical semantic binding map between carrier kinds and protocol families.
 *
 * This component defines the operational semantic relationship between:
 *
 * - carrier runtime semantics
 * - protocol admission/runtime semantics
 *
 * The goal is NOT transport registration.
 * The goal is semantic compatibility projection.
 *
 * This map is consumed by:
 *
 * - protocol readiness evaluation
 * - protocol admission policies
 * - participant compatibility validation
 * - binding/runtime diagnostics
 * - pipeline composition layers
 *
 * This component intentionally exists inside bridge_carriers because carrier
 * semantics are the stable vocabulary shared across protocol domains.
 */

namespace assembler::communication_context
{
    enum class TCarrierProtocolCompatibility
    {
        unknown,
        compatible,
        conditionally_compatible,
        incompatible
    };

    [[nodiscard]] constexpr std::string_view to_string(
        TCarrierProtocolCompatibility compatibility) noexcept
    {
        switch (compatibility)
        {
            case TCarrierProtocolCompatibility::unknown:
                return "unknown";

            case TCarrierProtocolCompatibility::compatible:
                return "compatible";

            case TCarrierProtocolCompatibility::conditionally_compatible:
                return "conditionally_compatible";

            case TCarrierProtocolCompatibility::incompatible:
                return "incompatible";
        }

        return "unknown";
    }

    struct TCarrierProtocolBindingEntry final
    {
        TAsccCarrierKind carrier_kind{
            TAsccCarrierKind::unknown};

        std::string_view protocol_family{};

        TCarrierProtocolCompatibility compatibility{
            TCarrierProtocolCompatibility::unknown};

        std::string_view rationale{};

        [[nodiscard]] constexpr bool valid() const noexcept
        {
            return carrier_kind != TAsccCarrierKind::unknown
                && !protocol_family.empty()
                && compatibility != TCarrierProtocolCompatibility::unknown;
        }
    };

    template <std::size_t Capacity>
    struct TCarrierProtocolBindingMap final
    {
        std::array<TCarrierProtocolBindingEntry, Capacity> entries{};
        std::size_t count{0};

        [[nodiscard]] constexpr bool valid() const noexcept
        {
            return count <= Capacity;
        }

        constexpr bool register_binding(
            TCarrierProtocolBindingEntry entry) noexcept
        {
            if (!valid() || !entry.valid())
            {
                return false;
            }

            if (count >= Capacity)
            {
                return false;
            }

            entries[count++] = entry;
            return true;
        }

        [[nodiscard]] constexpr const TCarrierProtocolBindingEntry*
        find_binding(
            TAsccCarrierKind carrier_kind,
            std::string_view protocol_family) const noexcept
        {
            for (std::size_t index = 0;
                 index < count;
                 ++index)
            {
                const auto& entry = entries[index];

                if (entry.carrier_kind == carrier_kind
                    && entry.protocol_family == protocol_family)
                {
                    return &entry;
                }
            }

            return nullptr;
        }

        [[nodiscard]] constexpr TCarrierProtocolCompatibility compatibility_of(
            TAsccCarrierKind carrier_kind,
            std::string_view protocol_family) const noexcept
        {
            const auto* binding =
                find_binding(carrier_kind, protocol_family);

            return binding != nullptr
                ? binding->compatibility
                : TCarrierProtocolCompatibility::unknown;
        }

        [[nodiscard]] constexpr bool compatible(
            TAsccCarrierKind carrier_kind,
            std::string_view protocol_family) const noexcept
        {
            const auto compatibility =
                compatibility_of(carrier_kind, protocol_family);

            return compatibility
                == TCarrierProtocolCompatibility::compatible
                || compatibility
                    == TCarrierProtocolCompatibility::conditionally_compatible;
        }
    };
}
