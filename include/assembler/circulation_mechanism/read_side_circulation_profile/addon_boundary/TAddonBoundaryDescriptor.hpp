#pragma once

#include "TAddonBoundaryId.hpp"
#include "TAddonBoundaryKind.hpp"
#include "TAddonBoundaryStatus.hpp"

    /*
        TAddonBoundaryDescriptor.hpp

        Delivery:
            CME-RSCP-PROD-W04 — Diagnostics And Addon Boundary Integration

        Current responsibility:
            Production descriptor for read-side addon boundary readiness and capabilities.

        Production capabilities:
            - classifies addon kind,
            - classifies readiness status,
            - declares support for receiver acknowledgement,
            - declares support for backpressure,
            - declares support for retry,
            - declares whether boundary is diagnostic-only,
            - validates readiness without invoking addon.

        Architectural role:
            Addon boundary descriptor is a contract surface. It is not addon runtime.

        Explicit non-ownership:
            - Does not call addon.
            - Does not persist payload.
            - Does not export telemetry.
            - Does not own receiver behavior.
    */
namespace assembler {
namespace circulation_mechanism {
namespace read_side_circulation_profile {

struct TAddonBoundaryDescriptor final {
    TAddonBoundaryId boundary_id{};
    TAddonBoundaryKind kind{TAddonBoundaryKind::unknown};
    TAddonBoundaryStatus status{TAddonBoundaryStatus::undefined};
    bool supports_receiver_ack{false};
    bool supports_backpressure{false};
    bool supports_retry{false};
    bool diagnostic_only{false};

    [[nodiscard]] constexpr bool is_valid() const noexcept {
        return boundary_id.is_valid() && kind != TAddonBoundaryKind::unknown;
    }

    [[nodiscard]] constexpr bool ready() const noexcept {
        return is_valid() && status == TAddonBoundaryStatus::ready;
    }

    [[nodiscard]] constexpr bool deferred_or_diagnostic_only() const noexcept {
        return status == TAddonBoundaryStatus::deferred || diagnostic_only;
    }

    [[nodiscard]] constexpr bool can_receive_runtime_material() const noexcept {
        return ready() && !diagnostic_only;
    }

    [[nodiscard]] constexpr bool is_persistence_boundary() const noexcept {
        return kind == TAddonBoundaryKind::database_adapter || kind == TAddonBoundaryKind::file_sink_adapter;
    }

    [[nodiscard]] constexpr bool is_telemetry_boundary() const noexcept {
        return kind == TAddonBoundaryKind::open_telemetry_adapter;
    }
};
} // namespace read_side_circulation_profile
} // namespace circulation_mechanism
} // namespace assembler
