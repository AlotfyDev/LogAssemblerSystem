
#include "assembler/circulation_mechanism/circulation_mechanism_runtime_core.hpp"

using namespace assembler::circulation_mechanism;

int main() {
    constexpr TCirculationConfigurationDescriptor invalid_cfg{
        TCirculationConfigurationId::from_raw(1),
        TCirculationConfigurationStatus::draft,
        TCirculationProfileKind::pre_bridge,
        TCirculationApiVersion::from_raw(1),
        TCirculationProfileVersion::from_raw(1)
    };
    static_assert(!invalid_cfg.ready_for_runtime(), "draft config not runtime ready");

    constexpr auto bad_compat = TCirculationCompatibilityReport::evaluate(
        TCirculationApiVersion::from_raw(3),
        TCirculationApiVersion::from_raw(2),
        TCirculationProfileVersion::from_raw(1),
        TCirculationProfileVersion::from_raw(2)
    );
    static_assert(!bad_compat.compatible(), "newer requested API incompatible");

    constexpr auto invalid_transition = validate_transition(
        TCirculationLifecycleStatus::stopped,
        TCirculationLifecycleStatus::running
    );
    static_assert(invalid_transition.rejected(), "stopped cannot jump to running");

    return 0;
}
