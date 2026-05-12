#include <cassert>
#include <iostream>

#include "assembler/ecosystem_governance/policy_type_system/policy_realizer/TPolicyRealizer.hpp"

using namespace assembler::ecosystem_governance::policy_type_system;

namespace
{
class TDummyRealizer final : public TPolicyRealizer
{
public:
    [[nodiscard]] TPolicyRealizerView View() const override
    {
        return TPolicyRealizerView{
            TPolicyRealizerId{21},
            TPolicyRealizerStatus::ready,
            "dummy-realizer-interface",
            {TPolicyRealizerCapability::accepts_runtime_plan,
             TPolicyRealizerCapability::consumes_readiness_report,
             TPolicyRealizerCapability::supports_dry_run,
             TPolicyRealizerCapability::produces_result_report}
        };
    }

    [[nodiscard]] bool CanAccept(const TPolicyRuntimePlan& plan,
                                 const TPolicyRuntimeReadinessReport& readiness) const override
    {
        return plan.plan_id.IsValid() && readiness.contract_id.IsValid();
    }

    [[nodiscard]] TPolicyRealizerResult InspectPlan(const TPolicyRuntimePlan& plan,
                                                    const TPolicyRuntimeReadinessReport& readiness) const override
    {
        if (!CanAccept(plan, readiness))
        {
            TPolicyRealizerResult result{};
            result.kind = TPolicyRealizerResultKind::readiness_missing;
            result.issues.push_back(TPolicyRealizerIssue{"missing_input", "plan or readiness report is missing", true, false});
            return result;
        }
        TPolicyRealizerResult result{};
        result.kind = TPolicyRealizerResultKind::accepted;
        result.note = "plan accepted for interface inspection only";
        return result;
    }
};
}

int main()
{
    TDummyRealizer realizer{};
    auto view = realizer.View();
    assert(view.realizer_id.IsValid());
    assert(view.IsReady());
    assert(view.HasCapability(TPolicyRealizerCapability::accepts_runtime_plan));

    TPolicyRuntimePlan plan{};
    plan.plan_id.value = 1001;

    TPolicyRuntimeReadinessReport readiness{};
    readiness.contract_id.value = 2002;

    assert(realizer.CanAccept(plan, readiness));
    auto result = realizer.InspectPlan(plan, readiness);
    assert(result.IsPositive());
    assert(!result.HasBlockingIssue());

    TPolicyRuntimeReadinessReport missing{};
    auto rejected = realizer.InspectPlan(plan, missing);
    assert(rejected.HasBlockingIssue());

    std::cout << "EG-POL-W21 smoke test passed\n";
    return 0;
}
