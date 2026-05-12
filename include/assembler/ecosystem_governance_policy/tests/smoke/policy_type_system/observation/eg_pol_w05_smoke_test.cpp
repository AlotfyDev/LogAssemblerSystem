#include <cassert>

#include "assembler/ecosystem_governance/policy_type_system/identity/TPolicyId.hpp"
#include "assembler/ecosystem_governance/policy_type_system/lifecycle/TPolicyLifecycleState.hpp"
#include "assembler/ecosystem_governance/policy_type_system/observation/TPolicyObservationId.hpp"
#include "assembler/ecosystem_governance/policy_type_system/observation/TPolicyObservationKind.hpp"
#include "assembler/ecosystem_governance/policy_type_system/observation/TPolicyEvidenceRef.hpp"
#include "assembler/ecosystem_governance/policy_type_system/observation/TPolicyTraceRef.hpp"
#include "assembler/ecosystem_governance/policy_type_system/observation/TPolicyAuditMarker.hpp"
#include "assembler/ecosystem_governance/policy_type_system/observation/TPolicyObservationRecord.hpp"
#include "assembler/ecosystem_governance/policy_type_system/observation/TPolicyAuditTrail.hpp"
#include "assembler/ecosystem_governance/policy_type_system/observation/TPolicyObservationView.hpp"

int main()
{
    using namespace assembler::ecosystem_governance::policy_type_system;

    constexpr TPolicyId policy_id{42};
    constexpr TPolicyObservationId observation_id{7};
    constexpr TPolicyTraceRef trace{100, 2};
    constexpr TPolicyEvidenceRef evidence{55, TPolicyEvidenceKind::lifecycle_evidence};

    static_assert(observation_id.IsValid(), "observation id should be valid");
    static_assert(IsLifecycleRelated(TPolicyObservationKind::activation), "activation is lifecycle-related");
    static_assert(!IsReplacementRelated(TPolicyObservationKind::activation), "activation is not replacement-related");
    static_assert(trace.IsPresent(), "trace should be present");
    static_assert(evidence.IsPresent(), "evidence should be present");

    TPolicyObservationRecord record{
        observation_id,
        policy_id,
        TPolicyObservationKind::activation,
        TPolicyLifecycleState::active,
        evidence,
        trace,
        9001};

    assert(record.IsStructurallyComplete());
    assert(record.HasEvidence());
    assert(record.HasTrace());

    TPolicyAuditMarker marker{observation_id, policy_id, TPolicyObservationKind::activation, trace};
    assert(marker.IsComplete());

    TPolicyAuditTrail trail;
    assert(trail.Empty());
    trail.Add(marker);
    assert(trail.Count() == 1);

    TPolicyObservationView view = TPolicyObservationView::From(record);
    assert(view.IsPresent());
    assert(view.evidence_present);
    assert(view.trace_present);
    assert(view.note_code == 9001);

    return 0;
}
