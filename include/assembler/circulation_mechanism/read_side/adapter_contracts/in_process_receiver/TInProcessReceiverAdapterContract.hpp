#pragma once
    #include "../common/TReadSideAdapterContract.hpp"

    /*
        TInProcessReceiverAdapterContract.hpp

        Current responsibility:
            Convenience contract factory for `in_process_receiver` adapter boundary.

        Non-ownership:
            Does not implement adapter runtime.
    */
    namespace assembler {
namespace circulation_mechanism {
namespace read_side {

    struct TInProcessReceiverAdapterContract final {
        [[nodiscard]] static constexpr TReadSideAdapterContract make(
            TReadSideAdapterContractId id,
            TReadSideAdapterStatus status = TReadSideAdapterStatus::ready,
            bool external_runtime_required = true) noexcept
        {
            return TReadSideAdapterContract{id, TReadSideAdapterKind::in_process_receiver, status, TReadSideAdapterCapabilitySet{true, true, true, true, true, false, false, false, false, false}, external_runtime_required};
        }
    };
    } // namespace read_side
} // namespace circulation_mechanism
} // namespace assembler
