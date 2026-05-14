#pragma once
#include <string_view>
#include "assembler/communication_context/bindings/composition/TBindingCardinality.hpp"
#include "assembler/communication_context/bindings/composition/TBindingHandoffStyle.hpp"
/**
 * @file TBindingCompositionReadinessReport.hpp
 * @brief Report describing readiness of binding composition against a required protocol/binding profile.
 *
 * Records whether binding composition metadata satisfies selected protocol or
 * binding requirements. It is managerial evidence, not endpoint execution.
 */
namespace assembler::communication_context {
struct TBindingCompositionReadinessReport final {
    TBindingHandoffStyle observed_handoff_style{TBindingHandoffStyle::unknown};
    TBindingHandoffStyle required_handoff_style{TBindingHandoffStyle::unknown};
    TBindingCardinality observed_cardinality{TBindingCardinality::unknown};
    TBindingCardinality required_cardinality{TBindingCardinality::unknown};
    bool handoff_style_matched{false}, cardinality_matched{false};
    bool session_requirement_satisfied{false}, bridge_requirement_satisfied{false}, protocol_requirement_satisfied{false};
    std::string_view report_note{};
    [[nodiscard]] constexpr bool is_valid() const noexcept { return observed_handoff_style!=TBindingHandoffStyle::unknown && required_handoff_style!=TBindingHandoffStyle::unknown && observed_cardinality!=TBindingCardinality::unknown && required_cardinality!=TBindingCardinality::unknown; }
    [[nodiscard]] constexpr bool passed() const noexcept { return is_valid() && handoff_style_matched && cardinality_matched && session_requirement_satisfied && bridge_requirement_satisfied && protocol_requirement_satisfied; }
};
}
