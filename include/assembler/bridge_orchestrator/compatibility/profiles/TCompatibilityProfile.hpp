#pragma once
#include <string_view>

/**
 * @file TCompatibilityProfile.hpp
 * @brief Profile selecting which compatibility dimensions/rule packs apply.
 */
namespace assembler::communication_context {
    enum class TCompatibilityProfileKind { unknown, strict_binding_only, component_admission, session_preparation, protocol_admission, diagnostic_review };
    struct TCompatibilityProfile final {
        TCompatibilityProfileKind kind{TCompatibilityProfileKind::unknown};
        bool include_participants{false};
        bool include_channels{false};
        bool include_bindings{false};
        bool include_obligations{false};
        bool include_carriers{false};
        bool include_sessions{false};
        bool include_protocols{false};
        std::string_view profile_name{};
        [[nodiscard]] constexpr bool is_valid() const noexcept { return kind != TCompatibilityProfileKind::unknown; }
        [[nodiscard]] static constexpr TCompatibilityProfile component_admission_profile() noexcept {
            return {TCompatibilityProfileKind::component_admission, true, true, true, true, true, true, true, "component_admission"};
        }
    };
}
