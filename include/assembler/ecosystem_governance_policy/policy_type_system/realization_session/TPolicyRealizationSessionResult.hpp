#pragma once

#include <algorithm>
#include <cstdint>
#include <string>
#include <vector>

#include "assembler/ecosystem_governance/policy_type_system/realization_session/TPolicyRealizationSessionIssue.hpp"

namespace assembler::ecosystem_governance::policy_type_system
{

/*
 * File: TPolicyRealizationSessionResult.hpp
 * Wave: EG-POL-W22_PolicyRealizationSession
 * Domain: ecosystem_governance / policy_type_system / realization_session
 *
 * Architectural boundary:
 *   W22 introduces the Policy Realization Session model after W21 introduced
 *   the PolicyRealizer interface and result vocabulary. A realization session
 *   is the lifecycle scope around one governed interaction between a policy
 *   realization request, a realization contract/context, a runtime plan,
 *   readiness evidence, and a realizer interface participant. It is not an
 *   executor, not a scheduler, not target invocation, not target mutation, not
 *   material circulation behavior, not communication binding, and not add-on
 *   execution.
 *
 * Relationship to prior waves:
 *   - W01 supplies identity and source/version/scope vocabulary.
 *   - W06 supplies realization-binding and target-kind descriptors.
 *   - W09 supplies TPolicy as a semantic aggregate, not executor.
 *   - W10 supplies non-executing assignment basics.
 *   - W12 supplies family/scope foundations.
 *   - W13 supplies target-capability contracts.
 *   - W14 supplies compatibility matrix/reporting foundations.
 *   - W15 supplies assignment lifecycle and conflict vocabulary.
 *   - W16 and W17 supply publication and registry-versioning views.
 *   - W18 supplies realization contracts, contexts, requests, failures, traces.
 *   - W19 supplies runtime readiness gates, issues, reports, evaluators.
 *   - W20 supplies pre-execution runtime plans.
 *   - W21 supplies realizer interface, status, capability, result, and view.
 *
 * Relationship to Phase A architecture:
 *   Phase A states: Assigned != Active != Runtime-Ready != Realized != Executed.
 *   W22 introduces a session scope that can bind readiness evidence, runtime
 *   plan, request, and realizer identity into a trackable lifecycle. Opening a
 *   session does not mean realization succeeded, and completing a session does
 *   not claim target mutation or downstream success.
 *
 * Explicit non-responsibilities:
 *   This file does not implement TPolicyExecutor, runtime execution engine,
 *   direct target invocation, target mutation, material circulation behavior,
 *   communication binding, add-on execution, source parsing, persistent
 *   registry storage, telemetry, logging, or database persistence.
 *
 * Current implementation posture:
 *   The code is a conservative C++17 header-only foundation. The comments
 *   document the complete architectural responsibility while implementation
 *   remains a compact set of value carriers, enum vocabularies, and read-only
 *   views suitable for compile smoke testing.
 *
 * File responsibility:
 * *   TPolicyRealizationSessionResult describes session lifecycle outcomes such as opened, rejected, deferred, inspected, completed, or failed. It is not a realization result and must not claim runtime target mutation or downstream success.
 */
enum class TPolicyRealizationSessionResultKind : std::uint8_t
{
    unknown = 0,
    opened = 1,
    rejected = 2,
    deferred = 3,
    inspected = 4,
    completed = 5,
    cancelled = 6,
    failed = 7,
    blocked = 8,
    forbidden = 9
};

[[nodiscard]] constexpr bool IsPositive(TPolicyRealizationSessionResultKind kind) noexcept
{
    return kind == TPolicyRealizationSessionResultKind::opened ||
           kind == TPolicyRealizationSessionResultKind::inspected ||
           kind == TPolicyRealizationSessionResultKind::completed;
}

struct TPolicyRealizationSessionResult final
{
    TPolicyRealizationSessionResultKind kind{TPolicyRealizationSessionResultKind::unknown};
    std::vector<TPolicyRealizationSessionIssue> issues{};
    std::uint64_t trace_id{0};
    std::string note{};

    [[nodiscard]] bool IsPositive() const noexcept { return policy_type_system::IsPositive(kind); }
    [[nodiscard]] bool HasBlockingIssue() const noexcept
    {
        return kind == TPolicyRealizationSessionResultKind::rejected ||
               kind == TPolicyRealizationSessionResultKind::failed ||
               kind == TPolicyRealizationSessionResultKind::blocked ||
               kind == TPolicyRealizationSessionResultKind::forbidden ||
               std::any_of(issues.begin(), issues.end(), [](const TPolicyRealizationSessionIssue& issue) { return issue.IsBlocking(); });
    }
};

} // namespace assembler::ecosystem_governance::policy_type_system
