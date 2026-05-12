#include "assembler/ecosystem_governance/policy_audit_export/TPolicyAuditExportBoundary.hpp"
#include <cassert>

int main()
{
    using namespace assembler::ecosystem_governance::policy_audit_export;

    TPolicyAuditExportBoundary boundary{};
    boundary.descriptor.boundary_id.value = "audit-export-boundary-001";
    boundary.descriptor.medium_kind = TPolicyAuditExportMediumKind::diagnostic_boundary;
    boundary.descriptor.owner_domain = "ecosystem_governance/policy_audit_export";
    boundary.last_admission = TPolicyAuditExportAdmission::accept("smoke_test");

    TPolicyAuditExportRecordRef record{};
    record.record_id = "record-001";
    record.record_kind = "runtime_readiness_report";
    assert(boundary.admit_record(record).admitted);

    boundary.records.push_back(record);
    auto report = boundary.describe("report-001");
    assert(report.ok());
    assert(report.records.size() == 1);
    return 0;
}
