#pragma once
#include "TCommunicationBindingReportId.hpp"
#include "TCommunicationBindingIssueKind.hpp"
#include "assembler/circulation_mechanism/communication_bindings/TCommunicationBindingId.hpp"
#include "assembler/circulation_mechanism/communication_bindings/TCommunicationBindingKind.hpp"
#include "assembler/circulation_mechanism/communication_bindings/TCommunicationBindingStatus.hpp"
#include "assembler/circulation_mechanism/communication_bindings/TBindingCompatibilityStatus.hpp"
namespace assembler {
namespace circulation_mechanism {

struct TCommunicationBindingReport final {
    TCommunicationBindingReportId report_id{};
    TCommunicationBindingId binding_id{};
    TCommunicationBindingKind kind{TCommunicationBindingKind::ingress_placement};
    TCommunicationBindingStatus status{TCommunicationBindingStatus::unbound};
    TBindingCompatibilityStatus compatibility{TBindingCompatibilityStatus::unknown};
    TCommunicationBindingIssueKind issue{TCommunicationBindingIssueKind::none};
    [[nodiscard]] constexpr bool is_valid() const noexcept { return report_id.is_valid() && binding_id.is_valid(); }
    [[nodiscard]] constexpr bool passed() const noexcept { return compatibility == TBindingCompatibilityStatus::compatible && issue == TCommunicationBindingIssueKind::none; }
};
} // namespace circulation_mechanism
} // namespace assembler
