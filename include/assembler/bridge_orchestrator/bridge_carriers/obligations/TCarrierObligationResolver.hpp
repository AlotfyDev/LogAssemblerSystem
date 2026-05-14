#pragma once
#include <string_view>
#include "assembler/communication_context/bridge_carriers/kinds/TAsccCarrierKind.hpp"
namespace assembler::communication_context
{
    struct TCarrierObligationResolution final
    {
        TAsccCarrierKind carrier_kind{TAsccCarrierKind::unknown};
        std::string_view operation_family{};
        std::string_view adapter_obligation{};
        std::string_view port_obligation{};
        [[nodiscard]] constexpr bool is_valid() const noexcept
        {
            return carrier_kind != TAsccCarrierKind::unknown && !operation_family.empty();
        }
    };
    struct TCarrierObligationResolver final
    {
        [[nodiscard]] static constexpr TCarrierObligationResolution resolve_envelope_placement(TAsccCarrierKind kind) noexcept
        {
            switch (kind)
            {
                case TAsccCarrierKind::placement_request:
                    return {kind, "envelope_placement", "adapter.prepare_placement_request", "port.admit"};
                case TAsccCarrierKind::placement_handle:
                    return {kind, "envelope_placement", "adapter.accept_placement_handle", "port.produce_placement_handle"};
                case TAsccCarrierKind::load_signal:
                    return {kind, "envelope_placement", "adapter.emit_load_signal", "port.receive_load_signal"};
                case TAsccCarrierKind::admission_result:
                    return {kind, "envelope_placement", "adapter.consume_admission_result", "port.produce_admission_result"};
                default:
                    return {kind, "envelope_placement", {}, {}};
            }
        }
    };
}
