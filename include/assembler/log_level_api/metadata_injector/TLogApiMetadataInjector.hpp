#pragma once

/*
    LOGAPI-W04 — Metadata Struct And Field Values

    This header belongs to the Log Level API metadata struct and field value layer.

    Responsibility:
        Define metadata struct descriptors, metadata fields, mutable metadata
        values, update sets, prepared metadata blocks, and metadata injector
        configuration surfaces.

    Boundary:
        Metadata is not content.
        Metadata is not stabilized timestamp.
        Metadata does not define content schema fields, required/default validator
        inputs, concrete validators, timestamp stabilization algorithms, envelope
        assembly, communication bindings, or policy assignment.

    Doctrine:
        Content + metadata struct + stabilized timestamp meet later inside the
        envelope through the envelope assembler.
*/

#include "TLogApiMetadataInjectionIssue.hpp"
#include "TLogApiMetadataInjectionResult.hpp"
#include "TLogApiMetadataInjectorConfig.hpp"
#include "TLogApiMetadataUpdateSet.hpp"

namespace assembler::log_level_api::metadata_injector {

/*
    Configuration-time/simple preparation component for metadata values.

    It prepares a metadata block from configured field values plus optional
    updates. It does not mutate content and does not stabilize timestamps.
*/
class TLogApiMetadataInjector final {
public:
    [[nodiscard]] static TLogApiMetadataInjectionResult Prepare(
        const TLogApiMetadataInjectorConfig& config,
        const TLogApiMetadataUpdateSet& updates = {}
    ) {
        TLogApiMetadataInjectionResult result{};

        if (!config.IsReady()) {
            result.issues.push_back({
                "LOGAPI_METADATA_CONFIG_NOT_READY",
                "Metadata injector config must be resolved before preparing metadata.",
                true
            });
            return result;
        }

        result.block.descriptor = config.metadata_struct;
        result.block.values = config.default_values;

        for (const auto& update : updates.updates) {
            bool applied = false;
            for (auto& current : result.block.values.values) {
                if (current.field_id.value == update.field_id.value) {
                    current = update;
                    applied = true;
                    break;
                }
            }
            if (!applied) {
                result.block.values.values.push_back(update);
            }
        }

        if (!result.block.IsReadyForEnvelope()) {
            result.issues.push_back({
                "LOGAPI_METADATA_BLOCK_NOT_READY",
                "Prepared metadata block is missing required configured field values.",
                true
            });
        }

        return result;
    }
};

} // namespace assembler::log_level_api::metadata_injector
