#pragma once
#include "TCommunicationBindingKind.hpp"
#include "TBindingCompatibilityStatus.hpp"
namespace assembler {
namespace circulation_mechanism {

struct TCommunicationBindingCompatibility final {
    TCommunicationBindingKind kind{TCommunicationBindingKind::diagnostic_only};
    TBindingCompatibilityStatus status{TBindingCompatibilityStatus::unknown};
    [[nodiscard]] constexpr bool compatible() const noexcept { return status == TBindingCompatibilityStatus::compatible; }
};
} // namespace circulation_mechanism
} // namespace assembler
