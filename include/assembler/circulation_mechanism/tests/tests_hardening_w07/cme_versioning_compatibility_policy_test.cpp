#include "assembler/circulation_mechanism/circulation_mechanism_versioning.hpp"
using namespace assembler::circulation_mechanism::versioning;

int main() {
    constexpr TCirculationVersionSet requested{TCirculationApiVersion::from_raw(1), TCirculationProfileVersion::from_raw(1), TCirculationSchemaVersion::from_raw(1)};
    constexpr TCirculationVersionSet supported{TCirculationApiVersion::from_raw(2), TCirculationProfileVersion::from_raw(2), TCirculationSchemaVersion::from_raw(2)};
    constexpr TCirculationFeatureFlagSet flags{};
    constexpr auto report = TCirculationCompatibilityPolicy::evaluate(TCirculationCompatibilityReportId::from_raw(1), requested, supported, flags);
    static_assert(report.compatible(), "requested <= supported is compatible");
    static_assert(report.status == TCirculationCompatibilityStatus::compatible_with_deprecation, "legacy compatibility makes compatibility deprecated");
    constexpr TCirculationCompatibilityView view{report};
    static_assert(view.compatible(), "view compatible");
    return 0;
}
