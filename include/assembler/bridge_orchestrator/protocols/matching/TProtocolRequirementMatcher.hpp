#pragma once
#include "assembler/communication_context/protocols/requirements/TProtocolRequirementMatchResult.hpp"
#include "assembler/communication_context/protocols/requirements/TProtocolRequirementReport.hpp"
#include "assembler/communication_context/protocols/requirements/TProtocolRequirementSet.hpp"

/**
 * @file TProtocolRequirementMatcher.hpp
 * @brief Managerial matcher that produces protocol requirement match reports.
 *
 * This is an initial bounded matcher. It accepts external evidence flags from
 * participant/carrier/binding subsystems and converts them into the existing
 * protocol requirement result/report shapes.
 */
namespace assembler::communication_context {
    struct TProtocolRequirementMatcher final {
        template <typename RequirementSet>
        [[nodiscard]] static constexpr TProtocolRequirementReport match(
            const RequirementSet& set,
            bool participants_ok,
            bool carriers_ok,
            bool bindings_ok,
            std::string_view name = "protocol_requirement_match_report") noexcept
        {
            const bool ok = set.is_valid() && participants_ok && carriers_ok && bindings_ok;
            const auto result = TProtocolRequirementMatchResult{
                ok ? TProtocolRequirementMatchStatus::matched : TProtocolRequirementMatchStatus::missing_carrier_capability,
                ok ? (set.participant_count + set.carrier_count + set.binding_count) : 0u,
                ok ? 0u : (set.participant_count + set.carrier_count + set.binding_count),
                0u,
                bindings_ok ? 0u : set.binding_count,
                ok ? "protocol requirements matched" : "protocol requirements not satisfied"
            };
            return TProtocolRequirementReport::from_set_and_match(set, result, name);
        }
    };
}
