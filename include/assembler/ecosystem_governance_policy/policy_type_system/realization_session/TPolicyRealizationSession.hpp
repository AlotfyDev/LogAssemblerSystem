#pragma once

#include <cstdint>
#include <string>
#include <vector>

#include "assembler/ecosystem_governance/policy_type_system/realization_session/TPolicyRealizationSessionId.hpp"
#include "assembler/ecosystem_governance/policy_type_system/realization_session/TPolicyRealizationSessionState.hpp"
#include "assembler/ecosystem_governance/policy_type_system/realization_session/TPolicyRealizationSessionIssue.hpp"
#include "assembler/ecosystem_governance/policy_type_system/realization_session/TPolicyRealizationSessionOpenRequest.hpp"
#include "assembler/ecosystem_governance/policy_type_system/realization_session/TPolicyRealizationSessionResult.hpp"
#include "assembler/ecosystem_governance/policy_type_system/realization_session/TPolicyRealizationSessionView.hpp"
#include "assembler/ecosystem_governance/policy_type_system/realization_contract/TPolicyRealizationContractId.hpp"
#include "assembler/ecosystem_governance/policy_type_system/realization_contract/TPolicyRealizationContextId.hpp"
#include "assembler/ecosystem_governance/policy_type_system/policy_realizer/TPolicyRealizerId.hpp"

namespace assembler::ecosystem_governance::policy_type_system
{

/*
 * File: TPolicyRealizationSession.hpp
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
 * *   TPolicyRealizationSession is the governed lifecycle carrier for a realization session. It binds session identity, contract/context identity, readiness evidence, runtime plan reference, realizer identity, issues, and trace. It can produce lifecycle results and views, but it does not execute policy behavior or invoke targets.
 */
struct TPolicyRealizationSession final
{
    TPolicyRealizationSessionId id{};
    TPolicyRealizationSessionState state{TPolicyRealizationSessionState::unknown};
    TPolicyRealizationContractId contract_id{};
    TPolicyRealizationContextId context_id{};
    TPolicyRealizerId realizer_id{};
    std::uint64_t realization_request_id{0};
    std::uint64_t readiness_report_id{0};
    std::uint64_t runtime_plan_id{0};
    std::uint64_t authority_evidence_id{0};
    std::uint64_t trace_id{0};
    std::vector<TPolicyRealizationSessionIssue> issues{};
    std::string note{};

    [[nodiscard]] bool IsValidSession() const noexcept
    {
        return id.IsValid() &&
               contract_id.IsValid() &&
               context_id.IsValid() &&
               realization_request_id != 0 &&
               readiness_report_id != 0 &&
               authority_evidence_id != 0 &&
               trace_id != 0;
    }

    [[nodiscard]] bool HasRealizer() const noexcept { return realizer_id.IsValid(); }
    [[nodiscard]] bool HasPlan() const noexcept { return runtime_plan_id != 0; }
    [[nodiscard]] bool IsOpen() const noexcept { return policy_type_system::IsOpen(state); }
    [[nodiscard]] bool IsTerminal() const noexcept { return policy_type_system::IsTerminal(state); }

    [[nodiscard]] TPolicyRealizationSessionView View() const noexcept
    {
        return TPolicyRealizationSessionView{id, state, contract_id, context_id, realizer_id, readiness_report_id, runtime_plan_id, trace_id};
    }

    [[nodiscard]] TPolicyRealizationSessionResult ValidateForInspection() const
    {
        TPolicyRealizationSessionResult result{};
        result.trace_id = trace_id;
        if (!IsValidSession())
        {
            result.kind = TPolicyRealizationSessionResultKind::rejected;
            result.issues.push_back(TPolicyRealizationSessionIssue{TPolicyRealizationSessionIssueKind::missing_session_id, TPolicyRealizationSessionIssueSeverity::blocking, "session is missing required identity/evidence"});
            return result;
        }
        if (!HasRealizer())
        {
            result.kind = TPolicyRealizationSessionResultKind::deferred;
            result.issues.push_back(TPolicyRealizationSessionIssue{TPolicyRealizationSessionIssueKind::missing_realizer, TPolicyRealizationSessionIssueSeverity::warning, "no realizer identity attached yet"});
            return result;
        }
        result.kind = TPolicyRealizationSessionResultKind::inspected;
        return result;
    }
};

[[nodiscard]] inline TPolicyRealizationSession CreatePolicyRealizationSession(
    TPolicyRealizationSessionId session_id,
    const TPolicyRealizationSessionOpenRequest& request,
    TPolicyRealizerId realizer_id = {})
{
    TPolicyRealizationSession session{};
    session.id = session_id;
    session.state = request.IsValidOpenRequest() ? TPolicyRealizationSessionState::open : TPolicyRealizationSessionState::blocked;
    session.contract_id = request.realization_request.contract_id;
    session.context_id = request.realization_request.context_id;
    session.realizer_id = realizer_id;
    session.realization_request_id = request.realization_request.request_id;
    session.readiness_report_id = request.realization_request.readiness_report_id != 0 ? request.realization_request.readiness_report_id : request.readiness_report.trace.readiness_report_id;
    session.runtime_plan_id = request.runtime_plan.plan_id.value;
    session.authority_evidence_id = request.authority_evidence_id;
    session.trace_id = request.trace_id;
    session.note = request.note;
    if (!request.IsValidOpenRequest())
    {
        session.issues.push_back(TPolicyRealizationSessionIssue{TPolicyRealizationSessionIssueKind::missing_readiness, TPolicyRealizationSessionIssueSeverity::blocking, "open request did not satisfy realization session requirements"});
    }
    return session;
}

} // namespace assembler::ecosystem_governance::policy_type_system
