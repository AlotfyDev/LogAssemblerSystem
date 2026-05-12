#include <cassert>

#include "assembler/ecosystem_governance/policy_type_system/source_publication/TPolicyPublicationView.hpp"

using namespace assembler::ecosystem_governance::policy_type_system;

int main()
{
    TPolicySourceDescriptor source{};
    source.source_id = 11;
    source.source_kind = TPolicySourceKind::authored_source;
    source.base_identity_source = TPolicySource::configured;
    source.trust_level = TPolicySourceTrustLevel::review_required;
    source.ingestion_state = TPolicySourceIngestionState::source_validated;
    source.source_name = "unit-test-source";
    source.provenance_note = "smoke";

    assert(source.IsValidDescriptor());
    assert(source.RequiresReview());
    assert(source.IsIngested());
    assert(source.IsSourceValidated());

    TPolicyPublicationRecord record{};
    record.publication_record_id = 22;
    record.policy_id = TPolicyId{1001};
    record.policy_version = TPolicyVersion{1, 0, 0};
    record.source_descriptor = source;
    record.publication_state = TPolicyPublicationState::published;
    record.visibility = TPolicyRegistryVisibility::assignment_visible;
    record.authority_evidence_id = 33;

    assert(record.IsValidRecord());
    assert(record.IsPublishedRecord());
    assert(record.HasAuthorityEvidence());
    assert(IsAssignmentVisible(record.publication_state));

    TPolicyVersionLineage lineage{};
    lineage.lineage_id = 44;
    lineage.source_policy_id = TPolicyId{1001};
    lineage.source_version = TPolicyVersion{1, 0, 0};
    lineage.target_policy_id = TPolicyId{1001};
    lineage.target_version = TPolicyVersion{0, 9, 0};
    lineage.version_relation = TPolicyVersionLineageKind::rollback_to;
    lineage.replacement_relation = TPolicyReplacementLineageKind::rollback_replacement;
    lineage.authority_evidence_id = 55;

    assert(lineage.IsValidLineage());
    assert(lineage.IsRollbackRelated());
    assert(!lineage.IsForbiddenReplacement());

    TPolicyPublicationView view{};
    view.publication_records.push_back(record);
    view.version_lineages.push_back(lineage);

    assert(view.PublicationRecordCount() == 1);
    assert(view.LineageCount() == 1);
    assert(view.HasAnyPublishedRecord());
    assert(view.HasAnyRollbackLineage());
    assert(view.AllRecordsValid());
    assert(view.IsViewOnly());

    return 0;
}
