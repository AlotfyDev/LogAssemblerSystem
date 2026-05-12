#pragma once

/*
    LOGAPI-W08 — Envelope Assembler Families

    This header belongs to the Log Level API envelope assembler family layer.

    Responsibility:
        Define envelope assembly input, assembly profile, assembly result, and
        two distinct assembler families:
            - plain envelope assembler
            - validator-composed envelope assembler

    Boundary:
        The assembler composes already prepared material into an envelope.
        It must not define content schemas, metadata field definitions, timestamp
        stabilization rules, concrete validators, API consuming behavior,
        communication bindings, circulation handoff, or policy assignment.

    Hot-path doctrine:
        Plain assembly and validator-composed assembly are separate types.
        The system must not branch inside one assembler flow to ask whether a
        validator exists. The assembler family is selected before the hot path.
*/

#include <string>

#include "assembler/log_level_api/api_configurator/TLogApiActiveProfile.hpp"
#include "assembler/log_level_api/api_configurator/TLogApiAssemblerFamilyKind.hpp"

#include "TLogApiEnvelopeAssemblerId.hpp"
#include "TLogApiEnvelopeAssemblerStatus.hpp"

namespace assembler::log_level_api::envelope_assembler {

/*
    Assembly profile resolved before the hot path.

    The profile names the assembler family. It does not perform runtime discovery.
*/
struct TLogApiEnvelopeAssemblyProfile final {
    TLogApiEnvelopeAssemblerId assembler_id{};
    TLogApiEnvelopeAssemblerStatus status{TLogApiEnvelopeAssemblerStatus::Unknown};
    assembler::log_level_api::api_configurator::TLogApiAssemblerFamilyKind family{
        assembler::log_level_api::api_configurator::TLogApiAssemblerFamilyKind::Unknown
    };

    std::string envelope_profile_name{"default.envelope.profile"};

    [[nodiscard]] bool IsResolved() const noexcept {
        return assembler_id.IsValid()
            && (status == TLogApiEnvelopeAssemblerStatus::Resolved
                || status == TLogApiEnvelopeAssemblerStatus::Active)
            && family != assembler::log_level_api::api_configurator::TLogApiAssemblerFamilyKind::Unknown
            && !envelope_profile_name.empty();
    }

    [[nodiscard]] static TLogApiEnvelopeAssemblyProfile FromActiveProfile(
        const assembler::log_level_api::api_configurator::TLogApiActiveProfile& active
    ) {
        TLogApiEnvelopeAssemblyProfile p{};
        p.assembler_id = TLogApiEnvelopeAssemblerId{1};
        p.status = active.IsReadyForConsumingPath()
            ? TLogApiEnvelopeAssemblerStatus::Resolved
            : TLogApiEnvelopeAssemblerStatus::Rejected;
        p.family = active.assembler_family;
        p.envelope_profile_name = "default.envelope.profile";
        return p;
    }
};

} // namespace assembler::log_level_api::envelope_assembler
