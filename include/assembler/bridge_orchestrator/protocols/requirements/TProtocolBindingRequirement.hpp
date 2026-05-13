#pragma once

#include <cstdint>
#include <string_view>

#include "assembler/communication_context/bindings/composition/TBindingCardinality.hpp"
#include "assembler/communication_context/bindings/composition/TBindingHandoffStyle.hpp"
#include "assembler/communication_context/protocols/kinds/TBridgeProtocolKind.hpp"
#include "assembler/communication_context/protocols/requirements/TProtocolRequirementKind.hpp"

/**
 * @file TProtocolBindingRequirement.hpp
 * @brief Binding-composition requirement declared by an ASCC protocol.
 *
 * @section ascc_comp_w05 Purpose
 * This type connects protocol requirements to W04 binding composition metadata.
 * It declares the handoff style, cardinality, and bridge/session/protocol
 * expectations needed by a protocol family.
 */

namespace assembler::communication_context
{
    struct TProtocolBindingRequirement final
    {
        std::uint64_t requirement_id{0u};
        TBridgeProtocolKind protocol{TBridgeProtocolKind::unknown};
        TBindingHandoffStyle required_handoff_style{TBindingHandoffStyle::unknown};
        TBindingCardinality required_cardinality{TBindingCardinality::unknown};
        bool requires_session{false};
        bool requires_bridge{false};
        bool requires_protocol{true};
        bool required{true};
        std::string_view note{};

        [[nodiscard]] constexpr bool is_valid() const noexcept
        {
            return requirement_id != 0u
                && protocol != TBridgeProtocolKind::unknown
                && required_handoff_style != TBindingHandoffStyle::unknown
                && required_cardinality != TBindingCardinality::unknown;
        }

        [[nodiscard]] constexpr bool is_required() const noexcept
        {
            return required;
        }

        [[nodiscard]] constexpr TProtocolRequirementKind requirement_kind() const noexcept
        {
            return TProtocolRequirementKind::binding_composition_requirement;
        }

        [[nodiscard]] static constexpr TProtocolBindingRequirement make(
            std::uint64_t id,
            TBridgeProtocolKind protocol_kind,
            TBindingHandoffStyle handoff_style,
            TBindingCardinality cardinality,
            bool session_required,
            bool bridge_required,
            bool protocol_required = true,
            bool is_required_binding = true,
            std::string_view requirement_note = {}) noexcept
        {
            return TProtocolBindingRequirement{
                id,
                protocol_kind,
                handoff_style,
                cardinality,
                session_required,
                bridge_required,
                protocol_required,
                is_required_binding,
                requirement_note
            };
        }

        [[nodiscard]] static constexpr TProtocolBindingRequirement envelope_placement(
            std::uint64_t id = 1u,
            std::string_view requirement_note = "envelope placement requires mediated bridge/session protocol") noexcept
        {
            return make(
                id,
                TBridgeProtocolKind::envelope_placement,
                TBindingHandoffStyle::bridge_mediated,
                TBindingCardinality::one_to_one,
                true,
                true,
                true,
                true,
                requirement_note);
        }
    };
}
