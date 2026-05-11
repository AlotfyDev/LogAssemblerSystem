#pragma once

#include "TCirculationConcurrencyProfileId.hpp"
#include "TCirculationConcurrencyMode.hpp"
#include "TCirculationMutationAuthorityKind.hpp"
#include "TCirculationThreadingGuaranteeSet.hpp"
#include "TCirculationConcurrencyIssueKind.hpp"

/*
    TCirculationConcurrencyProfile.hpp

    Delivery:
        CME-PROD-HARDEN-W06 — Threading And Concurrency Policy

    Current responsibility:
        Defines production concurrency policy for one circulation subsystem or shared core.

    Production capabilities:
        - declares single-writer / independent-instance default
        - declares mutation authority
        - declares guarantees
        - rejects hidden internal threading, scheduler ownership, unbounded parallelism
        - keeps bridge/receiver runtime out of the engine

    Explicit non-ownership:
        - Does not spawn threads.
        - Does not schedule tasks.
        - Does not implement locks.
        - Does not own bridge/receiver concurrency.
*/

namespace assembler {
namespace circulation_mechanism {
namespace concurrency {

struct TCirculationConcurrencyProfile final {
    TCirculationConcurrencyProfileId profile_id{};
    TCirculationConcurrencyMode mode{TCirculationConcurrencyMode::single_writer_independent_instances};
    TCirculationMutationAuthorityKind mutation_authority{TCirculationMutationAuthorityKind::single_writer};
    TCirculationThreadingGuaranteeSet guarantees{};
    bool multi_writer_requested{false};
    bool shared_mutable_state_requested{false};
    bool internal_threading_requested{false};
    bool scheduler_ownership_requested{false};
    bool unbounded_parallelism_requested{false};
    bool bridge_runtime_owned{false};
    bool receiver_runtime_owned{false};

    [[nodiscard]] constexpr bool is_valid() const noexcept {
        return profile_id.is_valid();
    }

    [[nodiscard]] constexpr TCirculationConcurrencyIssueKind validation_issue() const noexcept {
        if (!profile_id.is_valid()) return TCirculationConcurrencyIssueKind::invalid_profile_id;
        if (multi_writer_requested) return TCirculationConcurrencyIssueKind::multi_writer_requested;
        if (shared_mutable_state_requested) return TCirculationConcurrencyIssueKind::shared_mutable_state_requested;
        if (internal_threading_requested) return TCirculationConcurrencyIssueKind::internal_threading_requested;
        if (scheduler_ownership_requested) return TCirculationConcurrencyIssueKind::scheduler_ownership_requested;
        if (unbounded_parallelism_requested) return TCirculationConcurrencyIssueKind::unbounded_parallelism_requested;
        if (bridge_runtime_owned) return TCirculationConcurrencyIssueKind::bridge_runtime_leak;
        if (receiver_runtime_owned) return TCirculationConcurrencyIssueKind::receiver_runtime_leak;
        return TCirculationConcurrencyIssueKind::none;
    }

    [[nodiscard]] constexpr bool accepted() const noexcept {
        return validation_issue() == TCirculationConcurrencyIssueKind::none
            && guarantees.production_safe_default()
            && mutation_authority == TCirculationMutationAuthorityKind::single_writer
            && (mode == TCirculationConcurrencyMode::single_writer_single_instance
                || mode == TCirculationConcurrencyMode::single_writer_independent_instances);
    }
};
} // namespace concurrency
} // namespace circulation_mechanism
} // namespace assembler
