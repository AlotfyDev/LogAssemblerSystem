#pragma once

#include "TReportId.hpp"
#include "TReportKind.hpp"
#include "TReportStatus.hpp"
#include "TReportScopeKind.hpp"
#include "TReportEvidenceKind.hpp"
#include "TReportValidationResult.hpp"

#include <type_traits>

/*
    TReportDescriptor.hpp

    Delivery:
        CME-REPORTS-PROD-W01 — Production Evidence Contract

    Current responsibility:
        Defines an immutable, production-grade descriptor for report/evidence
        artifacts inside the Circulation Mechanism Engine.

    Production capabilities:
        - immutable descriptor fields after construction.
        - report kind, status, scope, and evidence classification.
        - validation for id/status/scope/evidence consistency.
        - explicit downstream-proof flag that is rejected in CME reports.
        - helpers for diagnostic, operational, boundary, and readiness reports.
        - non-aggregate descriptor to avoid mutation by consumers.

    Architectural role:
        A report is evidence within a declared scope. It is not an action, not a
        transition executor, not recovery, and not downstream proof.

    Explicit non-ownership:
        - Does not persist evidence.
        - Does not emit telemetry.
        - Does not mutate runtime behavior.
        - Does not prove final delivery or receiver acknowledgement.
        - Does not expand component authority.

    Anti-collapse:
        Report evidence must remain scoped. A report must not silently become a
        bridge-success proof, receiver-ack proof, persistence proof, or runtime
        recovery command.
*/

namespace assembler {
namespace circulation_mechanism {


class TReportDescriptor final
{
public:
    constexpr TReportDescriptor() noexcept = default;

    constexpr TReportDescriptor(
        TReportId id,
        TReportKind kind,
        TReportStatus status,
        TReportScopeKind scope,
        TReportEvidenceKind evidence,
        bool claims_downstream_success = false,
        bool claims_authority_expansion = false) noexcept
        : id_(id),
          kind_(kind),
          status_(status),
          scope_(scope),
          evidence_(evidence),
          claims_downstream_success_(claims_downstream_success),
          claims_authority_expansion_(claims_authority_expansion)
    {
    }

    [[nodiscard]] static constexpr TReportDescriptor operational(TReportId id) noexcept
    {
        return TReportDescriptor{id, TReportKind::operational, TReportStatus::complete, TReportScopeKind::local_component, TReportEvidenceKind::action_completed};
    }

    [[nodiscard]] static constexpr TReportDescriptor diagnostic(TReportId id) noexcept
    {
        return TReportDescriptor{id, TReportKind::diagnostic, TReportStatus::complete, TReportScopeKind::diagnostic, TReportEvidenceKind::diagnostic_detected};
    }

    [[nodiscard]] static constexpr TReportDescriptor invariant(TReportId id) noexcept
    {
        return TReportDescriptor{id, TReportKind::invariant, TReportStatus::complete, TReportScopeKind::diagnostic, TReportEvidenceKind::invariant_checked};
    }

    [[nodiscard]] static constexpr TReportDescriptor boundary(TReportId id) noexcept
    {
        return TReportDescriptor{id, TReportKind::boundary, TReportStatus::complete, TReportScopeKind::boundary, TReportEvidenceKind::boundary_observed};
    }

    [[nodiscard]] constexpr TReportId id() const noexcept { return id_; }
    [[nodiscard]] constexpr TReportKind kind() const noexcept { return kind_; }
    [[nodiscard]] constexpr TReportStatus status() const noexcept { return status_; }
    [[nodiscard]] constexpr TReportScopeKind scope() const noexcept { return scope_; }
    [[nodiscard]] constexpr TReportEvidenceKind evidence() const noexcept { return evidence_; }
    [[nodiscard]] constexpr bool claims_downstream_success() const noexcept { return claims_downstream_success_; }
    [[nodiscard]] constexpr bool claims_authority_expansion() const noexcept { return claims_authority_expansion_; }

    [[nodiscard]] constexpr bool is_valid() const noexcept
    {
        return id_.is_valid() && status_ != TReportStatus::invalid;
    }

    [[nodiscard]] constexpr bool is_complete() const noexcept
    {
        return status_ == TReportStatus::complete;
    }

    [[nodiscard]] constexpr bool is_diagnostic() const noexcept
    {
        return kind_ == TReportKind::diagnostic || kind_ == TReportKind::invariant;
    }

    [[nodiscard]] constexpr bool is_boundary_scoped() const noexcept
    {
        return scope_ == TReportScopeKind::boundary;
    }

    [[nodiscard]] constexpr TReportValidationResult validate() const noexcept
    {
        if (!id_.is_valid())
        {
            return rejected_report_contract(TReportContractIssueKind::invalid_id);
        }

        if (status_ == TReportStatus::invalid)
        {
            return rejected_report_contract(TReportContractIssueKind::invalid_status);
        }

        if (claims_downstream_success_)
        {
            return rejected_report_contract(TReportContractIssueKind::downstream_proof_claim);
        }

        if (claims_authority_expansion_)
        {
            return rejected_report_contract(TReportContractIssueKind::authority_expansion_claim);
        }

        if (kind_ == TReportKind::boundary && scope_ != TReportScopeKind::boundary)
        {
            return rejected_report_contract(TReportContractIssueKind::scope_kind_mismatch);
        }

        if (kind_ == TReportKind::invariant && evidence_ != TReportEvidenceKind::invariant_checked)
        {
            return rejected_report_contract(TReportContractIssueKind::scope_kind_mismatch);
        }

        return accepted_report_contract();
    }

private:
    TReportId id_{TReportId::invalid()};
    TReportKind kind_{TReportKind::operational};
    TReportStatus status_{TReportStatus::created};
    TReportScopeKind scope_{TReportScopeKind::local_component};
    TReportEvidenceKind evidence_{TReportEvidenceKind::action_attempted};
    bool claims_downstream_success_{false};
    bool claims_authority_expansion_{false};
};

static_assert(!std::is_aggregate<TReportDescriptor>::value,
    "TReportDescriptor must not expose mutable aggregate fields.");

} // namespace circulation_mechanism
} // namespace assembler
