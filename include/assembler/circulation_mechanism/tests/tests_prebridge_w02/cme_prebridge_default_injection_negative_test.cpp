
#include "assembler/circulation_mechanism/circulation_mechanism_pre_bridge.hpp"

using namespace assembler::circulation_mechanism;
using namespace assembler::circulation_mechanism::pre_bridge;

int main()
{
    constexpr TPreBridgeDefaultInjectionProfile invalid{};
    static_assert(!invalid.is_valid(), "default constructed profile invalid");
    static_assert(invalid.validation_issue() == TPreBridgeConfigurationIssueKind::invalid_default_profile_id,
        "invalid profile id expected");

    constexpr TPreBridgeReferenceSupplyBinding invalid_supply{
        TReferenceSupplyPolicy{0U, 0U, true},
        true
    };
    static_assert(!invalid_supply.is_valid(), "invalid supply binding rejected");

    constexpr TPreBridgeDiagnosticsBinding diag_disabled_with_required{
        false,
        true,
        false
    };
    static_assert(!diag_disabled_with_required.is_valid(), "collector cannot be required if diagnostics disabled");

    return 0;
}
