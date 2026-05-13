#include "assembler/communication_context/bindings/composition/TBindingCompositionSurface.hpp"

int main()
{
    using namespace assembler::communication_context;

    static_assert(ASCC_COMP_W04_BINDING_COMPOSITION_SURFACE_AVAILABLE,
                  "W04 binding composition surface must be available");

    const auto bridge_metadata =
        TBindingCompositionMetadata::strict_static_one_to_one_bridge_mediated();
    const auto bridge_requirement =
        TBindingCompositionRequirement::bridge_mediated_one_to_one();
    const auto bridge_report =
        TBindingCompositionReport::evaluate(
            bridge_metadata,
            bridge_requirement,
            "bridge-mediated one-to-one must satisfy bridge requirement");

    if (!bridge_metadata.is_valid()) return 1;
    if (!bridge_metadata.is_bridge_mediated()) return 2;
    if (!bridge_report.passed()) return 3;

    const auto direct_metadata =
        TBindingCompositionMetadata::direct_single_writer_compatible();
    const auto direct_requirement =
        TBindingCompositionRequirement::direct_single_writer();
    const auto direct_report =
        TBindingCompositionReport::evaluate(
            direct_metadata,
            direct_requirement,
            "direct single-writer binding must not require bridge/session/protocol");

    if (!direct_metadata.is_valid()) return 4;
    if (!direct_metadata.is_direct()) return 5;
    if (direct_metadata.requires_bridge || direct_metadata.requires_session || direct_metadata.requires_protocol) return 6;
    if (!direct_report.passed()) return 7;

    const auto passive_metadata =
        TBindingCompositionMetadata::passive_pull_bridge_mediated();

    if (!passive_metadata.is_valid()) return 8;
    if (!passive_metadata.is_bridge_mediated()) return 9;
    if (!passive_metadata.requires_bridge || !passive_metadata.requires_session || !passive_metadata.requires_protocol) return 10;

    const auto diagnostic_metadata =
        TBindingCompositionMetadata::diagnostic_only();
    const auto diagnostic_requirement =
        TBindingCompositionRequirement::diagnostic_only();
    const auto diagnostic_report =
        TBindingCompositionReport::evaluate(
            diagnostic_metadata,
            diagnostic_requirement,
            "diagnostic-only binding must not claim payload delivery");

    if (!diagnostic_metadata.is_valid()) return 11;
    if (!diagnostic_metadata.is_diagnostic_only()) return 12;
    if (diagnostic_metadata.can_claim_payload_delivery()) return 13;
    if (!diagnostic_report.passed()) return 14;

    const auto wrong_requirement =
        TBindingCompositionRequirement::direct_single_writer("wrong_direct_requirement");
    const auto wrong_report =
        TBindingCompositionReport::evaluate(
            bridge_metadata,
            wrong_requirement,
            "bridge metadata must not satisfy direct requirement");

    if (!wrong_report.failed()) return 15;
    if (wrong_report.handoff_style_matched) return 16;

    const auto view = TBindingCompositionView::from_metadata(bridge_metadata);
    if (!view.is_valid()) return 17;
    if (!view.requires_bridge || !view.requires_session || !view.requires_protocol) return 18;

    return 0;
}
