#pragma once
#include "TDispatchReportId.hpp"
#include "assembler/circulation_mechanism/dispatcher/TDispatcherId.hpp"
namespace assembler {
namespace circulation_mechanism {

struct TPushDispatchAttemptReport final {
    TDispatchReportId report_id{};
    TDispatcherId dispatcher_id{};
    bool attempted{false};
    bool accepted{false};
    [[nodiscard]] constexpr bool is_valid() const noexcept { return report_id.is_valid() && dispatcher_id.is_valid(); }
};
} // namespace circulation_mechanism
} // namespace assembler
