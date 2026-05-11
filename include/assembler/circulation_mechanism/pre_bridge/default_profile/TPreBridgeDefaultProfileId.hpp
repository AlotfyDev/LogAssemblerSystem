#pragma once
    #include <cstdint>
    #include <functional>

    /*
        TPreBridgeDefaultProfileId.hpp

        Delivery:
            CME-PREBRIDGE-PROD-W02 — PreBridge Configuration And Default Injection Profile

        Current responsibility:
            Identifies one default PreBridge injection profile.

        Production capabilities:
            - typed identity atom
            - invalid/from_raw/raw/is_valid helpers
            - equality / inequality
            - std::hash specialization

        Explicit non-ownership:
            - Does not allocate containers.
            - Does not execute runtime.
            - Does not own ReadSide profile.
            - Does not invoke bridge or receiver.
    */
    namespace assembler {
namespace circulation_mechanism {
namespace pre_bridge {

    struct TPreBridgeDefaultProfileId final {
        using value_type = std::uint64_t;
        static constexpr value_type k_invalid_value = 0U;
        value_type value{k_invalid_value};

        constexpr TPreBridgeDefaultProfileId() noexcept = default;
        constexpr explicit TPreBridgeDefaultProfileId(value_type input) noexcept : value(input) {}

        [[nodiscard]] static constexpr TPreBridgeDefaultProfileId invalid() noexcept { return TPreBridgeDefaultProfileId{k_invalid_value}; }
        [[nodiscard]] static constexpr TPreBridgeDefaultProfileId from_raw(value_type input) noexcept { return TPreBridgeDefaultProfileId{input}; }
        [[nodiscard]] constexpr value_type raw() const noexcept { return value; }
        [[nodiscard]] constexpr bool is_valid() const noexcept { return value != k_invalid_value; }

        [[nodiscard]] friend constexpr bool operator==(TPreBridgeDefaultProfileId lhs, TPreBridgeDefaultProfileId rhs) noexcept { return lhs.value == rhs.value; }
        [[nodiscard]] friend constexpr bool operator!=(TPreBridgeDefaultProfileId lhs, TPreBridgeDefaultProfileId rhs) noexcept { return !(lhs == rhs); }
    };
    } // namespace pre_bridge
} // namespace circulation_mechanism
} // namespace assembler

    namespace std {
    template<> struct hash<assembler::circulation_mechanism::pre_bridge::TPreBridgeDefaultProfileId> {
        std::size_t operator()(const assembler::circulation_mechanism::pre_bridge::TPreBridgeDefaultProfileId& input) const noexcept {
            return std::hash<assembler::circulation_mechanism::pre_bridge::TPreBridgeDefaultProfileId::value_type>{}(input.raw());
        }
    };
    }
