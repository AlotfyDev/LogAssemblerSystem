#pragma once
#include <cstdint>
#include <string_view>
#include "TProtocolCarrierRequirement.hpp"

namespace assembler::bridge_orchestrator::protocols::requirements {

enum class TBindingHandoffStyle { unknown, direct, bridge_mediated, passive_pull, push, hybrid, diagnostic_only };
enum class TBindingCardinality { unknown, one_to_one, one_to_many, many_to_one, many_to_many };

struct TProtocolBindingRequirement final {
    std::uint64_t requirement_id{0};
    TBridgeProtocolKind protocol{TBridgeProtocolKind::unknown};
    TBindingHandoffStyle required_handoff_style{TBindingHandoffStyle::unknown};
    TBindingCardinality required_cardinality{TBindingCardinality::unknown};
    bool requires_session{false};
    bool requires_bridge{false};
    bool requires_protocol{true};
    bool required{true};
    std::string_view note{};

    constexpr bool is_valid() const noexcept {
        return requirement_id != 0 && protocol != TBridgeProtocolKind::unknown &&
               required_handoff_style != TBindingHandoffStyle::unknown && required_cardinality != TBindingCardinality::unknown;
    }

    static constexpr TProtocolBindingRequirement envelope_placement() noexcept {
        return {1, TBridgeProtocolKind::envelope_placement, TBindingHandoffStyle::bridge_mediated,
                TBindingCardinality::one_to_one, true, true, true, true, "envelope placement requires mediated bridge/session protocol"};
    }
};

} // namespace assembler::bridge_orchestrator::protocols::requirements
