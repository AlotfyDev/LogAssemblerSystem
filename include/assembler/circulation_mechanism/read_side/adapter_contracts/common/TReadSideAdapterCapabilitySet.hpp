#pragma once
#include "TReadSideAdapterCapabilityKind.hpp"

/*
    TReadSideAdapterCapabilitySet.hpp

    Current responsibility:
        Fixed capability flags for adapter contract validation.

    Non-ownership:
        Does not implement capabilities.
*/
namespace assembler {
namespace circulation_mechanism {
namespace read_side {

struct TReadSideAdapterCapabilitySet final {
    bool accept_payload{false};
    bool acknowledge{false};
    bool reject{false};
    bool backpressure_signal{false};
    bool retry_signal{false};
    bool persist_snapshot{false};
    bool export_telemetry{false};
    bool write_file{false};
    bool emit_diagnostic{false};
    bool foreign_abi_call{false};

    [[nodiscard]] constexpr bool supports(TReadSideAdapterCapabilityKind kind) const noexcept {
        switch (kind) {
            case TReadSideAdapterCapabilityKind::accept_payload: return accept_payload;
            case TReadSideAdapterCapabilityKind::acknowledge: return acknowledge;
            case TReadSideAdapterCapabilityKind::reject: return reject;
            case TReadSideAdapterCapabilityKind::backpressure_signal: return backpressure_signal;
            case TReadSideAdapterCapabilityKind::retry_signal: return retry_signal;
            case TReadSideAdapterCapabilityKind::persist_snapshot: return persist_snapshot;
            case TReadSideAdapterCapabilityKind::export_telemetry: return export_telemetry;
            case TReadSideAdapterCapabilityKind::write_file: return write_file;
            case TReadSideAdapterCapabilityKind::emit_diagnostic: return emit_diagnostic;
            case TReadSideAdapterCapabilityKind::foreign_abi_call: return foreign_abi_call;
            default: return false;
        }
    }
};
} // namespace read_side
} // namespace circulation_mechanism
} // namespace assembler
