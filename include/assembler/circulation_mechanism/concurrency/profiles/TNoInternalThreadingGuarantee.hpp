#pragma once
#include "../TCirculationThreadingGuaranteeSet.hpp"

namespace assembler {
namespace circulation_mechanism {
namespace concurrency {

struct TNoInternalThreadingGuarantee final {
    [[nodiscard]] static constexpr TCirculationThreadingGuaranteeSet make() noexcept {
        return TCirculationThreadingGuaranteeSet{true, true, true, true, true, true};
    }
};
} // namespace concurrency
} // namespace circulation_mechanism
} // namespace assembler
