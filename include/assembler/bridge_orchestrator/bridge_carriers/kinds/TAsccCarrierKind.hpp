#pragma once

#include <string_view>

namespace assembler::communication_context
{
    enum class TAsccCarrierKind
    {
        unknown,
        correlation_token,
        readiness_view,
        placement_request,
        admission_result,
        placement_handle,
        load_signal,
        next_destination_request,
        bridge_result,
        bridge_error,
        carrier_result,
        carrier_error,
        boundary_handoff_request,
        boundary_handoff_result,
        boundary_handoff_handle,
        binding_view,
        session_view,
        protocol_view,
        bridge_view,
        diagnostic_record
    };

    [[nodiscard]] constexpr bool is_primary_exchange_carrier(TAsccCarrierKind kind) noexcept
    {
        return kind == TAsccCarrierKind::readiness_view
            || kind == TAsccCarrierKind::placement_request
            || kind == TAsccCarrierKind::admission_result
            || kind == TAsccCarrierKind::placement_handle
            || kind == TAsccCarrierKind::load_signal
            || kind == TAsccCarrierKind::next_destination_request
            || kind == TAsccCarrierKind::bridge_result
            || kind == TAsccCarrierKind::bridge_error
            || kind == TAsccCarrierKind::carrier_result
            || kind == TAsccCarrierKind::carrier_error;
    }

    [[nodiscard]] constexpr bool is_boundary_carrier(TAsccCarrierKind kind) noexcept
    {
        return kind == TAsccCarrierKind::boundary_handoff_request
            || kind == TAsccCarrierKind::boundary_handoff_result
            || kind == TAsccCarrierKind::boundary_handoff_handle;
    }

    [[nodiscard]] constexpr bool is_view_or_diagnostic_carrier(TAsccCarrierKind kind) noexcept
    {
        return kind == TAsccCarrierKind::binding_view
            || kind == TAsccCarrierKind::session_view
            || kind == TAsccCarrierKind::protocol_view
            || kind == TAsccCarrierKind::bridge_view
            || kind == TAsccCarrierKind::diagnostic_record;
    }

    [[nodiscard]] constexpr std::string_view to_string(TAsccCarrierKind kind) noexcept
    {
        switch (kind)
        {
            case TAsccCarrierKind::unknown: return "unknown";
            case TAsccCarrierKind::correlation_token: return "correlation_token";
            case TAsccCarrierKind::readiness_view: return "readiness_view";
            case TAsccCarrierKind::placement_request: return "placement_request";
            case TAsccCarrierKind::admission_result: return "admission_result";
            case TAsccCarrierKind::placement_handle: return "placement_handle";
            case TAsccCarrierKind::load_signal: return "load_signal";
            case TAsccCarrierKind::next_destination_request: return "next_destination_request";
            case TAsccCarrierKind::bridge_result: return "bridge_result";
            case TAsccCarrierKind::bridge_error: return "bridge_error";
            case TAsccCarrierKind::carrier_result: return "carrier_result";
            case TAsccCarrierKind::carrier_error: return "carrier_error";
            case TAsccCarrierKind::boundary_handoff_request: return "boundary_handoff_request";
            case TAsccCarrierKind::boundary_handoff_result: return "boundary_handoff_result";
            case TAsccCarrierKind::boundary_handoff_handle: return "boundary_handoff_handle";
            case TAsccCarrierKind::binding_view: return "binding_view";
            case TAsccCarrierKind::session_view: return "session_view";
            case TAsccCarrierKind::protocol_view: return "protocol_view";
            case TAsccCarrierKind::bridge_view: return "bridge_view";
            case TAsccCarrierKind::diagnostic_record: return "diagnostic_record";
        }
        return "unknown";
    }
}
