#pragma once
#include "reports/TReadSideProfileIssueKind.hpp"

namespace assembler {
namespace circulation_mechanism {
namespace read_side_circulation_profile {

struct TReadSideProfileValidationResult final {
    bool accepted{false};
    TReadSideProfileIssueKind issue{TReadSideProfileIssueKind::none};
    [[nodiscard]] constexpr bool rejected() const noexcept { return !accepted; }
};
[[nodiscard]] constexpr TReadSideProfileValidationResult accepted_profile() noexcept {
    return TReadSideProfileValidationResult{true, TReadSideProfileIssueKind::none};
}
[[nodiscard]] constexpr TReadSideProfileValidationResult rejected_profile(TReadSideProfileIssueKind issue) noexcept {
    return TReadSideProfileValidationResult{false, issue};
}
} // namespace read_side_circulation_profile
} // namespace circulation_mechanism
} // namespace assembler
