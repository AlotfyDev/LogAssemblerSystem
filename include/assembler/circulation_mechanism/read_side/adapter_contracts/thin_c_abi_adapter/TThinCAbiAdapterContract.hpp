#pragma once
    #include "../common/TReadSideAdapterContract.hpp"

    /*
        TThinCAbiAdapterContract.hpp

        Current responsibility:
            Convenience contract factory for `thin_c_abi_adapter` adapter boundary.

        Non-ownership:
            Does not implement adapter runtime.
    */
    namespace assembler {
namespace circulation_mechanism {
namespace read_side {

    struct TThinCAbiAdapterContract final {
        [[nodiscard]] static constexpr TReadSideAdapterContract make(
            TReadSideAdapterContractId id,
            TReadSideAdapterStatus status = TReadSideAdapterStatus::ready,
            bool external_runtime_required = true) noexcept
        {
            return TReadSideAdapterContract{id, TReadSideAdapterKind::thin_c_abi_adapter, status, TReadSideAdapterCapabilitySet{true, false, false, false, false, false, false, false, false, true}, external_runtime_required};
        }
    };
    } // namespace read_side
} // namespace circulation_mechanism
} // namespace assembler
