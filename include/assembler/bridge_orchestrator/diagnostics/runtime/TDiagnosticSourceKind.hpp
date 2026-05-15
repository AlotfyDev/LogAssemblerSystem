#pragma once
#include <string_view>

/**
 * @file TDiagnosticSourceKind.hpp
 * @brief Diagnostic source taxonomy for ASCC component diagnostics.
 */
namespace assembler::communication_context {
    enum class TDiagnosticSourceKind {
        unknown, bridge_core, protocol, session, binding, channel, registry, participant, carrier, obligation, compatibility, facade, integration_boundary
    };
    [[nodiscard]] constexpr std::string_view to_string(TDiagnosticSourceKind kind) noexcept {
        switch (kind) {
            case TDiagnosticSourceKind::unknown: return "unknown";
            case TDiagnosticSourceKind::bridge_core: return "bridge_core";
            case TDiagnosticSourceKind::protocol: return "protocol";
            case TDiagnosticSourceKind::session: return "session";
            case TDiagnosticSourceKind::binding: return "binding";
            case TDiagnosticSourceKind::channel: return "channel";
            case TDiagnosticSourceKind::registry: return "registry";
            case TDiagnosticSourceKind::participant: return "participant";
            case TDiagnosticSourceKind::carrier: return "carrier";
            case TDiagnosticSourceKind::obligation: return "obligation";
            case TDiagnosticSourceKind::compatibility: return "compatibility";
            case TDiagnosticSourceKind::facade: return "facade";
            case TDiagnosticSourceKind::integration_boundary: return "integration_boundary";
        }
        return "unknown";
    }
}
