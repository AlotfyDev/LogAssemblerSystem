#pragma once
#include "TAccessRefId.hpp"
#include "TAccessRefKind.hpp"
#include "TAccessRefDirection.hpp"
#include "TAccessRefScope.hpp"
#include "assembler/circulation_mechanism/state/TReferenceValidityState.hpp"
namespace assembler {
namespace circulation_mechanism {

struct TSlotAccessRef final {
    TAccessRefId id{};
    TAccessRefKind kind{TAccessRefKind::slot_access};
    TAccessRefDirection direction{TAccessRefDirection::internal_slot};
    TAccessRefScope scope{};
    TReferenceValidityState validity{TReferenceValidityState::prepared};
    [[nodiscard]] constexpr bool is_valid() const noexcept { return id.is_valid() && scope.is_valid(); }
    [[nodiscard]] constexpr bool can_be_consumed() const noexcept { return is_valid() && is_usable(validity); }
};
} // namespace circulation_mechanism
} // namespace assembler
