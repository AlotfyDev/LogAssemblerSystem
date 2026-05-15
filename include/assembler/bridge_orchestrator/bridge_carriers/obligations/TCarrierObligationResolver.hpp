#pragma once

#include <array>
#include <string_view>

#include "assembler/communication_context/bridge_carriers/kinds/TAsccCarrierKind.hpp"

/**
 * @file TCarrierObligationResolver.hpp
 * @brief Semantic obligation resolution layer for ASCC bridge carriers.
 *
 * This component resolves the operational obligation families associated with
 * carrier runtime semantics.
 *
 * The purpose is NOT generic policy execution.
 * The purpose is bounded operational obligation classification.
 *
 * This resolver exists to answer questions such as:
 *
 * - Which obligation family applies to this carrier kind?
 * - Does this carrier require admission validation?
 * - Does this carrier require evidence persistence?
 * - Does this carrier require protocol confirmation?
 * - Does this carrier require participant acknowledgment?
 *
 * The resolver is consumed by:
 *
 * - obligations/
 * - protocols/
 * - sessions/
 * - participants/
 * - diagnostics/
 * - facade readiness projections
 * - pipeline composition/runtime orchestration
 *
 * The resolver intentionally remains semantic and bounded.
 * It does NOT execute runtime actions.
 */

namespace assembler::communication_context
{
    enum class TCarrierObligationFamily
    {
        unknown,

        admission,
        validation,
        persistence,
        acknowledgment,
        protocol_confirmation,
        compatibility,
        diagnostics,
        auditing,
        recovery
    };

    [[nodiscard]] constexpr std::string_view to_string(
        TCarrierObligationFamily family) noexcept
    {
        switch (family)
        {
            case TCarrierObligationFamily::unknown:
                return "unknown";

            case TCarrierObligationFamily::admission:
                return "admission";

            case TCarrierObligationFamily::validation:
                return "validation";

            case TCarrierObligationFamily::persistence:
                return "persistence";

            case TCarrierObligationFamily::acknowledgment:
                return "acknowledgment";

            case TCarrierObligationFamily::protocol_confirmation:
                return "protocol_confirmation";

            case TCarrierObligationFamily::compatibility:
                return "compatibility";

            case TCarrierObligationFamily::diagnostics:
                return "diagnostics";

            case TCarrierObligationFamily::auditing:
                return "auditing";

            case TCarrierObligationFamily::recovery:
                return "recovery";
        }

        return "unknown";
    }

    struct TCarrierObligationBinding final
    {
        TAsccCarrierKind carrier_kind{
            TAsccCarrierKind::unknown};

        TCarrierObligationFamily obligation_family{
            TCarrierObligationFamily::unknown};

        bool mandatory{false};

        std::string_view rationale{};

        [[nodiscard]] constexpr bool valid() const noexcept
        {
            return carrier_kind != TAsccCarrierKind::unknown
                && obligation_family
                    != TCarrierObligationFamily::unknown;
        }
    };

    template <std::size_t Capacity>
    struct TCarrierObligationResolver final
    {
        std::array<TCarrierObligationBinding, Capacity> bindings{};
        std::size_t count{0};

        [[nodiscard]] constexpr bool valid() const noexcept
        {
            return count <= Capacity;
        }

        constexpr bool register_binding(
            TCarrierObligationBinding binding) noexcept
        {
            if (!valid() || !binding.valid())
            {
                return false;
            }

            if (count >= Capacity)
            {
                return false;
            }

            bindings[count++] = binding;
            return true;
        }

        [[nodiscard]] constexpr const TCarrierObligationBinding*
        find_binding(
            TAsccCarrierKind carrier_kind,
            TCarrierObligationFamily family) const noexcept
        {
            for (std::size_t index = 0;
                 index < count;
                 ++index)
            {
                const auto& binding = bindings[index];

                if (binding.carrier_kind == carrier_kind
                    && binding.obligation_family == family)
                {
                    return &binding;
                }
            }

            return nullptr;
        }

        [[nodiscard]] constexpr bool requires(
            TAsccCarrierKind carrier_kind,
            TCarrierObligationFamily family) const noexcept
        {
            const auto* binding =
                find_binding(carrier_kind, family);

            return binding != nullptr
                && binding->mandatory;
        }

        [[nodiscard]] constexpr bool supports(
            TAsccCarrierKind carrier_kind,
            TCarrierObligationFamily family) const noexcept
        {
            return find_binding(carrier_kind, family) != nullptr;
        }
    };
}
