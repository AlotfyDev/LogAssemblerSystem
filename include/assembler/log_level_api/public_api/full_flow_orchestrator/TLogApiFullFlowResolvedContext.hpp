#pragma once

/*
    LOGAPI-EXT-W01 — Public API Full Flow Orchestrator

    Responsibility:
        Define a production-oriented public API orchestration skeleton that
        connects:
            public content-only request
            → parser
            → metadata preparation
            → timestamp stabilization
            → final envelope shaping
            → envelope exposure
            → circulation handoff contract

    Boundary:
        This wave does not implement specialized JSON/C-struct/MT5 parser routing,
        real circulation admission, envelope streaming, persistence, policy
        assignment, bridge orchestration, or external receiver behavior.

    Doctrine:
        Configure first. Consume content only.
        No per-call schema/metadata/validator/timestamp/assembler/circulation/policy
        configuration is allowed.
*/

#include "assembler/log_level_api/public_api/TLogApiPublicResolvedContext.hpp"
#include "assembler/log_level_api/metadata_injector/TLogApiMetadataInjectorConfig.hpp"
#include "assembler/log_level_api/timestamp_stabilizer/TLogApiTimestampStabilizerConfig.hpp"

namespace assembler::log_level_api::public_api::full_flow_orchestrator {

/*
    Full-flow resolved context.

    All references/configurations must be resolved before the public call.
    Nothing here should be supplied as per-call material by the payload producer.
*/
struct TLogApiFullFlowResolvedContext final {
    assembler::log_level_api::public_api::TLogApiPublicResolvedContext public_context{};
    const assembler::log_level_api::metadata_injector::TLogApiMetadataInjectorConfig* metadata_config{nullptr};
    const assembler::log_level_api::timestamp_stabilizer::TLogApiTimestampStabilizerConfig* timestamp_config{nullptr};

    [[nodiscard]] bool IsReady() const noexcept {
        return public_context.IsReady()
            && metadata_config != nullptr
            && metadata_config->IsReady()
            && timestamp_config != nullptr
            && timestamp_config->IsResolved();
    }
};

} // namespace assembler::log_level_api::public_api::full_flow_orchestrator
