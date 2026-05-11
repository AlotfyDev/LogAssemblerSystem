#pragma once
#include "../TCirculationRuntimeId.hpp"
#include "TCirculationRuntimeIssueKind.hpp"
#include "../lifecycle/TCirculationLifecycleStatus.hpp"

/*
    TCirculationRuntimeReport.hpp

    Responsibility:
        Shared runtime lifecycle/config report.
*/
namespace assembler {
namespace circulation_mechanism {

struct TCirculationRuntimeReport final {
    TCirculationRuntimeId runtime_id{};
    TCirculationLifecycleStatus before{TCirculationLifecycleStatus::unconfigured};
    TCirculationLifecycleStatus after{TCirculationLifecycleStatus::unconfigured};
    TCirculationRuntimeIssueKind issue{TCirculationRuntimeIssueKind::none};

    [[nodiscard]] constexpr bool is_valid() const noexcept { return runtime_id.is_valid(); }
    [[nodiscard]] constexpr bool passed() const noexcept { return is_valid() && issue == TCirculationRuntimeIssueKind::none; }
};
} // namespace circulation_mechanism
} // namespace assembler
