#pragma once
#include "TAccessRefId.hpp"
#include "TAccessRefDirection.hpp"
#include "assembler/circulation_mechanism/state/TReferenceValidityState.hpp"
namespace assembler {
namespace circulation_mechanism {

struct TNextRefToken final {
    TAccessRefId id{};
    TAccessRefDirection direction{TAccessRefDirection::ingress};
    TReferenceValidityState validity{TReferenceValidityState::prepared};
    [[nodiscard]] constexpr bool is_valid() const noexcept { return id.is_valid(); }
};
} // namespace circulation_mechanism
} // namespace assembler
