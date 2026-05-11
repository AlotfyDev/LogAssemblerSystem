#pragma once
#include <cstdint>

namespace assembler {
namespace circulation_mechanism {
namespace pre_bridge {

struct TPreBridgeDiagnosticsBinding final {
    bool diagnostics_enabled{true};
    bool collector_required{false};
    bool export_boundary_required{false};

    [[nodiscard]] constexpr bool is_valid() const noexcept {
        return diagnostics_enabled || (!collector_required && !export_boundary_required);
    }
};
} // namespace pre_bridge
} // namespace circulation_mechanism
} // namespace assembler
