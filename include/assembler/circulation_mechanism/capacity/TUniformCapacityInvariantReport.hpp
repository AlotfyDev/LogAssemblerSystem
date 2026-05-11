#pragma once
#include "TCapacityProfileId.hpp"
#include "TCapacityIssueKind.hpp"

/*
    TUniformCapacityInvariantReport.hpp

    Responsibility:
        Reports whether active containers match the uniform capacity profile.
*/
namespace assembler {
namespace circulation_mechanism {

struct TUniformCapacityInvariantReport final
{
    TCapacityProfileId profile_id{};
    TCapacityIssueKind issue_kind{TCapacityIssueKind::none};
    bool all_active_containers_match{false};

    [[nodiscard]] constexpr bool passed() const noexcept
    {
        return profile_id.is_valid() && all_active_containers_match && issue_kind == TCapacityIssueKind::none;
    }
};
} // namespace circulation_mechanism
} // namespace assembler
