#pragma once
#include "TBundleAgentId.hpp"
#include "TContainerFamilyId.hpp"
#include "TBundleScalingPlan.hpp"

/*
    TBundleScalingReport.hpp

    Responsibility:
        Evidence of planned/applied scaling.

    Non-ownership:
        Does not mutate registry or reset containers.
*/
namespace assembler {
namespace circulation_mechanism {

struct TBundleScalingReport final {
    TBundleAgentId bundle_agent_id{};
    TContainerFamilyId family_id{};
    TBundleScalingPlan plan{};
    std::uint64_t before_generation{0};
    std::uint64_t after_generation{0};

    [[nodiscard]] constexpr bool is_valid() const noexcept {
        return bundle_agent_id.is_valid() && family_id.is_valid();
    }

    [[nodiscard]] constexpr bool applied() const noexcept {
        return is_valid() && plan.accepted() && after_generation > before_generation;
    }
};
} // namespace circulation_mechanism
} // namespace assembler
