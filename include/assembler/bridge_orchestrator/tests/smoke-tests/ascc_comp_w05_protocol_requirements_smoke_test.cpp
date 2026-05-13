#include "assembler/communication_context/protocols/requirements/TProtocolRequirementSurface.hpp"

int main()
{
    using namespace assembler::communication_context;

    static_assert(ASCC_COMP_W05_PROTOCOL_REQUIREMENTS_AVAILABLE,
                  "W05 protocol requirement surface must be available");

    constexpr auto set = TProtocolRequirementSet<4u, 12u, 2u>::envelope_placement_requirements();

    static_assert(set.is_valid(), "envelope placement requirement set must be valid");
    static_assert(set.participant_count == 2u, "content + receiver participants required");
    static_assert(set.carrier_count >= 4u, "carrier requirements should be present");
    static_assert(set.binding_count == 1u, "binding requirement should be present");
    static_assert(set.bindings[0].requires_bridge, "envelope placement is bridge mediated");
    static_assert(set.bindings[0].requires_session, "envelope placement requires a session model");
    static_assert(set.bindings[0].requires_protocol, "envelope placement requires protocol participation");

    constexpr auto ok = TProtocolRequirementMatchResult::matched(
        set.carrier_count + set.participant_count + set.binding_count);

    constexpr auto report_ok = TProtocolRequirementReport::from_set_and_match(
        set,
        ok,
        "w05_protocol_requirements_ok");

    static_assert(report_ok.passed(), "complete requirements should pass");
    static_assert(!report_ok.failed(), "complete requirements must not fail");

    constexpr auto missing = TProtocolRequirementMatchResult::missing_carrier(1u);
    constexpr auto report_missing = TProtocolRequirementReport::from_set_and_match(
        set,
        missing,
        "w05_missing_carrier");

    static_assert(report_missing.failed(), "missing carrier should fail");

    constexpr auto bad_binding = TProtocolRequirementMatchResult::binding_failed();
    constexpr auto report_binding = TProtocolRequirementReport::from_set_and_match(
        set,
        bad_binding,
        "w05_binding_failure");

    static_assert(report_binding.failed(), "binding mismatch should fail");

    return 0;
}
