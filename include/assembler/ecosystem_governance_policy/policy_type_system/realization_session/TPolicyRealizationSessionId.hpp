#pragma once

#include <cstdint>

namespace assembler::ecosystem_governance::policy_type_system
{

/*
 * File: TPolicyRealizationSessionId.hpp
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
 * *   TPolicyRealizationSessionId provides stable identity for a realization session. It identifies a governed session scope only; it does not own a target, execute policy behavior, or imply that realization occurred.
 */
struct TPolicyRealizationSessionId final
{
    std::uint64_t value{0};

    [[nodiscard]] constexpr bool IsValid() const noexcept { return value != 0; }
    [[nodiscard]] constexpr explicit operator bool() const noexcept { return IsValid(); }
    [[nodiscard]] friend constexpr bool operator==(TPolicyRealizationSessionId lhs, TPolicyRealizationSessionId rhs) noexcept { return lhs.value == rhs.value; }
    [[nodiscard]] friend constexpr bool operator!=(TPolicyRealizationSessionId lhs, TPolicyRealizationSessionId rhs) noexcept { return !(lhs == rhs); }
    [[nodiscard]] friend constexpr bool operator<(TPolicyRealizationSessionId lhs, TPolicyRealizationSessionId rhs) noexcept { return lhs.value < rhs.value; }
};

} // namespace assembler::ecosystem_governance::policy_type_system
