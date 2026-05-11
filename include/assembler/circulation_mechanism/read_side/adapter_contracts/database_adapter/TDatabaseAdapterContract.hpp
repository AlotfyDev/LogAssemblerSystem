#pragma once
    #include "../common/TReadSideAdapterContract.hpp"

    /*
        TDatabaseAdapterContract.hpp

        Current responsibility:
            Convenience contract factory for `database_adapter` adapter boundary.

        Non-ownership:
            Does not implement adapter runtime.
    */
    namespace assembler {
namespace circulation_mechanism {
namespace read_side {

    struct TDatabaseAdapterContract final {
        [[nodiscard]] static constexpr TReadSideAdapterContract make(
            TReadSideAdapterContractId id,
            TReadSideAdapterStatus status = TReadSideAdapterStatus::ready,
            bool external_runtime_required = true) noexcept
        {
            return TReadSideAdapterContract{id, TReadSideAdapterKind::database_adapter, status, TReadSideAdapterCapabilitySet{true, true, true, false, false, true, false, false, false, false}, external_runtime_required};
        }
    };
    } // namespace read_side
} // namespace circulation_mechanism
} // namespace assembler
