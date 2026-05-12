
#include "assembler/circulation_mechanism/circulation_mechanism_runtime_core.hpp"

using namespace assembler::circulation_mechanism;

int main() {
    constexpr TCirculationConfigurationDescriptor cfg{
        TCirculationConfigurationId::from_raw(1),
        TCirculationConfigurationStatus::validated,
        TCirculationProfileKind::pre_bridge,
        TCirculationApiVersion::from_raw(1),
        TCirculationProfileVersion::from_raw(1)
    };
    static_assert(cfg.is_valid(), "configuration valid");
    static_assert(cfg.ready_for_runtime(), "configuration ready");

    constexpr auto compat = TCirculationCompatibilityReport::evaluate(
        TCirculationApiVersion::from_raw(1),
        TCirculationApiVersion::from_raw(2),
        TCirculationProfileVersion::from_raw(1),
        TCirculationProfileVersion::from_raw(2)
    );
    static_assert(compat.compatible(), "versions compatible");

    constexpr auto ok = validate_transition(
        TCirculationLifecycleStatus::configured,
        TCirculationLifecycleStatus::constructed
    );
    static_assert(ok.accepted, "lifecycle transition accepted");

    constexpr auto bad = validate_transition(
        TCirculationLifecycleStatus::running,
        TCirculationLifecycleStatus::configured
    );
    static_assert(bad.rejected(), "invalid lifecycle transition rejected");

    constexpr TCirculationRuntimeDescriptor runtime{
        TCirculationRuntimeId::from_raw(3),
        cfg,
        TCirculationLifecycleStatus::configured
    };
    static_assert(runtime.is_valid(), "runtime descriptor valid");
    static_assert(runtime.configured(), "runtime configured");

    constexpr TCirculationRuntimeView view{runtime};
    static_assert(view.configured(), "runtime view configured");

    constexpr TCirculationRuntimeReport report{
        TCirculationRuntimeId::from_raw(3),
        TCirculationLifecycleStatus::configured,
        TCirculationLifecycleStatus::constructed,
        TCirculationRuntimeIssueKind::none
    };
    static_assert(report.passed(), "runtime report passed");

    return 0;
}
