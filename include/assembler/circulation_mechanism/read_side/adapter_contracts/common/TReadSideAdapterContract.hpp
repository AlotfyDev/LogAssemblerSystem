#pragma once
#include "TReadSideAdapterContractId.hpp"
#include "TReadSideAdapterKind.hpp"
#include "TReadSideAdapterStatus.hpp"
#include "TReadSideAdapterCapabilitySet.hpp"
#include "TReadSidePayloadRef.hpp"
#include "TReadSideAdapterInvocationStatus.hpp"

/*
    TReadSideAdapterContract.hpp

    Delivery:
        CME-READSIDE-PROD-W04 — Addon And Receiver Adapter Contracts

    Current responsibility:
        Generic callable contract descriptor/evaluator for read-side adapters.

    Production capabilities:
        - adapter identity, kind, status
        - capability declaration
        - external runtime requirement flag
        - payload/capability readiness evaluation
        - does not execute the adapter

    Explicit non-ownership:
        - Does not call external code.
        - Does not persist/export/write.
        - Does not own receiver implementation.
*/
namespace assembler {
namespace circulation_mechanism {
namespace read_side {

struct TReadSideAdapterContract final {
    TReadSideAdapterContractId contract_id{};
    TReadSideAdapterKind kind{TReadSideAdapterKind::unknown};
    TReadSideAdapterStatus status{TReadSideAdapterStatus::undefined};
    TReadSideAdapterCapabilitySet capabilities{};
    bool external_runtime_required{true};

    [[nodiscard]] constexpr bool is_valid() const noexcept {
        return contract_id.is_valid() && kind != TReadSideAdapterKind::unknown;
    }

    [[nodiscard]] constexpr bool ready() const noexcept {
        return is_valid() && status == TReadSideAdapterStatus::ready;
    }

    [[nodiscard]] constexpr TReadSideAdapterInvocationStatus evaluate(
        TReadSidePayloadRef payload,
        TReadSideAdapterCapabilityKind required_capability,
        bool external_runtime_available) const noexcept
    {
        if (!is_valid()) return TReadSideAdapterInvocationStatus::rejected_invalid_contract;
        if (!ready()) return TReadSideAdapterInvocationStatus::rejected_not_ready;
        if (!payload.is_valid()) return TReadSideAdapterInvocationStatus::rejected_payload_invalid;
        if (!capabilities.supports(required_capability)) return TReadSideAdapterInvocationStatus::rejected_capability_missing;
        if (external_runtime_required && !external_runtime_available) return TReadSideAdapterInvocationStatus::rejected_external_runtime_required;
        return TReadSideAdapterInvocationStatus::accepted;
    }
};
} // namespace read_side
} // namespace circulation_mechanism
} // namespace assembler
