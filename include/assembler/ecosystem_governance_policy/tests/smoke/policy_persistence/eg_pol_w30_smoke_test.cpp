#include "assembler/ecosystem_governance/policy_persistence/TPolicyPersistenceBoundary.hpp"

#include <cassert>
#include <string>

int main()
{
    using namespace assembler::ecosystem_governance::policy_persistence;

    TPolicyPersistenceBoundary boundary{};
    boundary.descriptor.id.value = "persist-boundary-001";
    boundary.descriptor.name = "policy_persistence_boundary_smoke";
    boundary.descriptor.medium = TPolicyPersistenceMediumKind::registry_export;
    boundary.descriptor.visibility = "test_visible";
    boundary.descriptor.retention_class = "snapshot_only";
    boundary.last_admission = TPolicyPersistenceAdmission::allow("smoke_test");
    boundary.latest_snapshot.snapshot_id = "snapshot-001";
    boundary.latest_snapshot.records.push_back({"record-001", "policy_registry_entry", "v1"});

    auto report = boundary.describe("report-001");
    assert(report.passed());
    assert(report.descriptor.valid());
    assert(report.snapshot.records.size() == 1U);
    assert(std::string(to_string(report.descriptor.medium)) == "registry_export");

    return 0;
}
