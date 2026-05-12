#include <cassert>
#include <iostream>

#include "assembler/ecosystem_governance/policy_registry/versioning/TPolicyRegistryVersionIndex.hpp"
#include "assembler/ecosystem_governance/policy_registry/versioning/TPolicyRegistryPublicationSnapshot.hpp"
#include "assembler/ecosystem_governance/policy_registry/versioning/TPolicyRegistryVersionedLookup.hpp"
#include "assembler/ecosystem_governance/policy_registry/versioning/TPolicyRegistryPublicationView.hpp"

int main()
{
    using namespace assembler::ecosystem_governance;
    using namespace assembler::ecosystem_governance::policy_registry;
    using namespace assembler::ecosystem_governance::policy_type_system;

    TPolicyRegistryEntryDescriptor descriptor{};
    descriptor.entry_id = TPolicyRegistryEntryId{1};
    descriptor.policy_id = TPolicyId{101};
    descriptor.family_id = TPolicyFamilyId{7};
    descriptor.version = TPolicyVersion{1, 0, 0};
    descriptor.scope = TPolicyScope::global_governance;
    descriptor.registry_status = TPolicyRegistryEntryStatus::registered;
    descriptor.structurally_complete = true;

    TPolicyPublicationRecord publication{};
    publication.publication_record_id = 501;
    publication.policy_id = descriptor.policy_id;
    publication.policy_version = descriptor.version;
    publication.source_descriptor.source_id = 12;
    publication.source_descriptor.source_kind = TPolicySourceKind::authored_source;
    publication.source_descriptor.base_identity_source = TPolicySource::configured;
    publication.source_descriptor.trust_level = TPolicySourceTrustLevel::review_required;
    publication.source_descriptor.source_name = "manual_policy_source";
    publication.source_descriptor.ingestion_state = TPolicySourceIngestionState::source_validated;
        publication.publication_state = TPolicyPublicationState::published;
    publication.visibility = TPolicyRegistryVisibility::production_visible;
    publication.authority_evidence_id = 9001;

    TPolicyRegistryVersionIndexRecord record{};
    record.registry_descriptor = descriptor;
    record.publication_record = publication;
    record.rollback_candidate = false;

    TPolicyRegistryVersionIndex index{};
    index.Add(record);
    assert(index.Count() == 1);

    const auto lookup = TPolicyRegistryVersionedLookup::LatestPublished(index, TPolicyFamilyId{7}, TPolicyScope::global_governance);
    assert(lookup.Found());
    assert(lookup.AssignmentEligible());

    const auto snapshot = TPolicyRegistryPublicationSnapshot::FromIndex(1, 1, index);
    assert(snapshot.IsValidSnapshot());
    assert(snapshot.published_count == 1);
    assert(snapshot.HasProductionVisibleRecord());

    const auto view = TPolicyRegistryPublicationView::FromSnapshot(snapshot);
    assert(view.IsValidView());
    assert(view.visible_records == 1);
    assert(view.has_production_visible_record);

    std::cout << "EG-POL-W17 smoke test passed\n";
    return 0;
}
