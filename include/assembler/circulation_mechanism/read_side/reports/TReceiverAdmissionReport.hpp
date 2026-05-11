#pragma once
#include "TReceiverAdmissionReportId.hpp"
#include "TReceiverAdmissionIssueKind.hpp"
#include "../receiver_admission/TReceiverAdmissionDecision.hpp"

/*
    TReceiverAdmissionReport.hpp

    Current responsibility:
        Evidence report for receiver admission decision.

    Non-ownership:
        Does not call receiver.
*/
namespace assembler {
namespace circulation_mechanism {
namespace read_side {

struct TReceiverAdmissionReport final {
    TReceiverAdmissionReportId report_id{};
    TReceiverAdmissionDecision decision{};
    TReceiverAdmissionIssueKind issue{TReceiverAdmissionIssueKind::none};

    [[nodiscard]] constexpr bool is_valid() const noexcept {
        return report_id.is_valid() && decision.is_valid();
    }

    [[nodiscard]] constexpr bool passed() const noexcept {
        return is_valid() && issue == TReceiverAdmissionIssueKind::none && decision.accepted();
    }
};
} // namespace read_side
} // namespace circulation_mechanism
} // namespace assembler
