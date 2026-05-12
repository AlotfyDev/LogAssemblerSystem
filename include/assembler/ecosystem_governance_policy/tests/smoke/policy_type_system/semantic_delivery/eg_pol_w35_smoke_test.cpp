#include <cassert>

#include "assembler/ecosystem_governance/policy_type_system/semantic_delivery/TPolicySemanticDeliveryBoundary.hpp"
#include "assembler/ecosystem_governance/policy_type_system/semantic_delivery/TPolicySemanticDeliveryView.hpp"

using namespace assembler::ecosystem_governance::policy_type_system::semantic_delivery;

int main()
{
    TPolicyGovernanceSemanticBundleDto dto;
    dto.id = TPolicyBundleDtoId{"bundle-log-level-validation-v1"};
    dto.policy_id_ref = "policy.validation.v1";
    dto.family_ref = "validation_policy_family";
    dto.version_ref = "1.0.0";
    dto.scope_ref = "system.log_level_api.validator";
    dto.publication_snapshot_ref = "publication-snapshot-001";
    dto.add_semantic_part(TPolicySemanticPayloadRef{"identity", "identity-ref"});
    dto.add_semantic_part(TPolicySemanticPayloadRef{"clauses", "clauses-ref"});
    dto.add_semantic_part(TPolicySemanticPayloadRef{"replacement", "replacement-ref"});

    assert(dto.has_identity());
    assert(dto.semantic_part_count() == 3U);
    assert(dto.has_semantic_part("clauses"));

    TPolicySemanticDeliveryBoundary boundary;
    boundary.boundary_name = "log-level-api-semantic-delivery";
    boundary.source_governance_scope = "ecosystem_governance";
    boundary.target_domain = "log_level_api";
    boundary.admission.accepted = true;
    boundary.admission.reason = "semantic bundle shape accepted";

    assert(boundary.can_deliver(dto));

    auto report = boundary.deliver_descriptor_only(dto);
    assert(report.bundle_id == dto.id);
    assert(report.status == TPolicySemanticDeliveryStatus::delivered);
    assert(!report.has_blockers());

    report.add_issue(TPolicySemanticDeliveryIssue{"WARN_SCOPE_REVIEW", "Scope should be reviewed by target domain", TPolicySemanticDeliveryIssueSeverity::warning});
    assert(report.issue_count() == 1U);
    assert(!report.has_blockers());

    TPolicySemanticDeliveryView view{dto.id, report.status, report.target_domain, dto.semantic_part_count(), report.issue_count(), report.has_blockers()};
    assert(view.semantic_part_count == 3U);
    assert(view.issue_count == 1U);
    assert(!view.has_blockers);

    boundary.admission.require("target capability declaration");
    assert(!boundary.can_deliver(dto));

    return 0;
}
