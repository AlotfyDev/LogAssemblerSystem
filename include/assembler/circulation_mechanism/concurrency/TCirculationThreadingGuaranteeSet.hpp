#pragma once

/*
    TCirculationThreadingGuaranteeSet.hpp

    Responsibility:
        Fixed policy flags for what the engine promises or forbids regarding threading.

    Non-ownership:
        This is a policy descriptor, not synchronization code.
*/

namespace assembler {
namespace circulation_mechanism {
namespace concurrency {

struct TCirculationThreadingGuaranteeSet final {
    bool no_internal_threads{true};
    bool no_scheduler{true};
    bool independent_instances{true};
    bool no_shared_mutable_state_by_default{true};
    bool external_synchronization_required_for_shared_use{true};
    bool bounded_parallelism_requires_policy{true};

    [[nodiscard]] constexpr bool production_safe_default() const noexcept {
        return no_internal_threads
            && no_scheduler
            && independent_instances
            && no_shared_mutable_state_by_default
            && external_synchronization_required_for_shared_use
            && bounded_parallelism_requires_policy;
    }
};
} // namespace concurrency
} // namespace circulation_mechanism
} // namespace assembler
