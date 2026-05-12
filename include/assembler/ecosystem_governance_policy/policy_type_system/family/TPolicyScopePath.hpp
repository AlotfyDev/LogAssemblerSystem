#pragma once

#include <cstddef>
#include <string>
#include <utility>
#include <vector>

#include "assembler/ecosystem_governance/policy_type_system/identity/TPolicyScope.hpp"

namespace assembler::ecosystem_governance::policy_type_system
{

/*
 * File: TPolicyScopePath.hpp

 * Wave: EG-POL-W12_Policy_Family_And_Scope
 * Domain: ecosystem_governance / policy_type_system / family
 *
 * Architectural boundary:
 *   W12 is the first implementation wave after Phase A architecture completion.
 *   It introduces the policy-family and policy-scope vocabulary needed before
 *   target capability contracts, compatibility evaluators, assignment lifecycle
 *   implementation, publication/versioning implementation, runtime readiness,
 *   or any future TPolicyRealizer. The wave remains descriptive and
 *   non-executing.
 *
 * Relationship to prior waves:
 *   - W01 provides primitive policy identity, including TPolicyFamilyId and
 *     TPolicyScope.
 *   - W09 provides the TPolicy aggregate, which may later contain or reference
 *     family profile information.
 *   - W10 provides assignment basics; W12 does not activate assignments.
 *   - W11 provides registry basics; W12 does not become a registry.
 *
 * Relationship to Phase A architecture:
 *   This wave implements the smallest code-level vocabulary derived from
 *   EG-POL-ARCH-001_Policy_Family_Taxonomy_And_Scope_Model and prepares later
 *   implementation of EG-POL-ARCH-002 and EG-POL-ARCH-003 without crossing into
 *   target invocation, policy realization, or runtime execution.
 *
 * Explicit non-responsibilities:
 *   This file does not implement target capability surfaces, target ownership,
 *   compatibility evaluation against concrete targets, assignment lifecycle,
 *   policy source ingestion, registry persistence, policy realization, runtime
 *   scheduling, telemetry, logging, or material circulation behavior.
 *
 * Current implementation posture:
 *   The current code is a C++17 header-only foundational block. The opening
 *   documentation describes the full architectural responsibility even when the
 *   code intentionally exposes only conservative value carriers and simple
 *   helper functions.

 * File responsibility:
 *   TPolicyScopePath is a descriptive hierarchy for where a policy family or
 *   policy instance is intended to govern. It refines the primitive W01
 *   TPolicyScope enum into a path-like value object without creating target
 *   ownership, runtime target handles, or service-location behavior.
 */
struct TPolicyScopePath final
{
    using segment_container = std::vector<std::string>;

    TPolicyScope scope{TPolicyScope::unspecified};
    segment_container segments{};

    TPolicyScopePath() = default;

    explicit TPolicyScopePath(TPolicyScope s) : scope(s) {}

    TPolicyScopePath(TPolicyScope s, segment_container segs)
        : scope(s), segments(std::move(segs)) {}

    [[nodiscard]] bool IsSpecified() const noexcept
    {
        return policy_type_system::IsSpecified(scope);
    }

    [[nodiscard]] bool Empty() const noexcept
    {
        return segments.empty();
    }

    [[nodiscard]] std::size_t Size() const noexcept
    {
        return segments.size();
    }

    void Push(std::string segment)
    {
        if (!segment.empty())
        {
            segments.push_back(std::move(segment));
        }
    }

    [[nodiscard]] std::string ToString(char separator = '.') const
    {
        std::string out;
        for (std::size_t i = 0; i < segments.size(); ++i)
        {
            if (i != 0) out.push_back(separator);
            out += segments[i];
        }
        return out;
    }
};

[[nodiscard]] inline bool HasPrefix(const TPolicyScopePath& candidate, const TPolicyScopePath& prefix) noexcept
{
    if (prefix.segments.size() > candidate.segments.size()) return false;
    for (std::size_t i = 0; i < prefix.segments.size(); ++i)
    {
        if (candidate.segments[i] != prefix.segments[i]) return false;
    }
    return true;
}

} // namespace assembler::ecosystem_governance::policy_type_system
