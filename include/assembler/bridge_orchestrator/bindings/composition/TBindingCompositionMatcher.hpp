#pragma once
#include <string_view>
#include "assembler/communication_context/bindings/composition/TBindingCompositionReadinessReport.hpp"
#include "assembler/communication_context/protocols/requirements/TProtocolBindingRequirement.hpp"
/**
 * @file TBindingCompositionMatcher.hpp
 * @brief Managerial matcher between binding composition metadata and protocol binding requirements.
 *
 * Matches observed binding composition shape against protocol binding
 * requirements. It is a policy/readiness helper and must not execute endpoints.
 */
namespace assembler::communication_context {
struct TBindingCompositionMatcher final {
    [[nodiscard]] static constexpr TBindingCompositionReadinessReport match(
        TBindingHandoffStyle observed_handoff_style, TBindingCardinality observed_cardinality,
        bool session_available, bool bridge_available, bool protocol_available,
        TProtocolBindingRequirement requirement, std::string_view note = {}) noexcept {
        return TBindingCompositionReadinessReport{
            observed_handoff_style, requirement.required_handoff_style,
            observed_cardinality, requirement.required_cardinality,
            observed_handoff_style==requirement.required_handoff_style,
            observed_cardinality==requirement.required_cardinality,
            !requirement.requires_session || session_available,
            !requirement.requires_bridge || bridge_available,
            !requirement.requires_protocol || protocol_available,
            note
        };
    }
};
}
