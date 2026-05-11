#pragma once
    #include "../common/TReadSideAdapterContract.hpp"

    /*
        TDiagnosticSinkAdapterContract.hpp

        Current responsibility:
            Convenience contract factory for `diagnostic_sink_adapter` adapter boundary.

        Non-ownership:
            Does not implement adapter runtime.
    */
    namespace assembler {
namespace circulation_mechanism {
namespace read_side {

    struct TDiagnosticSinkAdapterContract final {
        [[nodiscard]] static constexpr TReadSideAdapterContract make(
            TReadSideAdapterContractId id,
            TReadSideAdapterStatus status = TReadSideAdapterStatus::ready,
            bool external_runtime_required = true) noexcept
        {
            return TReadSideAdapterContract{id, TReadSideAdapterKind::diagnostic_sink_adapter, status, TReadSideAdapterCapabilitySet{false, false, false, false, false, false, false, false, true, false}, external_runtime_required};
        }
    };
    } // namespace read_side
} // namespace circulation_mechanism
} // namespace assembler
