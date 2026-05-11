#pragma once
#include "../TCirculationConcurrencyProfile.hpp"

namespace assembler {
namespace circulation_mechanism {
namespace concurrency {

struct TIndependentInstanceProfile final {
    [[nodiscard]] static constexpr TCirculationConcurrencyProfile make(TCirculationConcurrencyProfileId id) noexcept {
        return TCirculationConcurrencyProfile{
            id,
            TCirculationConcurrencyMode::single_writer_independent_instances,
            TCirculationMutationAuthorityKind::single_writer,
            TCirculationThreadingGuaranteeSet{true, true, true, true, true, true},
            false, false, false, false, false, false, false
        };
    }
};
} // namespace concurrency
} // namespace circulation_mechanism
} // namespace assembler
