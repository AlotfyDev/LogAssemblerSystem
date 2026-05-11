#pragma once
    #include <cstdint>
    #include <functional>

    /*
        TPreBridgeBindingSetId.hpp

        Delivery:
            CME-PREBRIDGE-PROD-W02 — PreBridge Configuration And Default Injection Profile

        Current responsibility:
            Identifies one PreBridge binding set descriptor.

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

    struct TPreBridgeBindingSetId final {
        using value_type = std::uint64_t;
        static constexpr value_type k_invalid_value = 0U;
        value_type value{k_invalid_value};

        constexpr TPreBridgeBindingSetId() noexcept = default;
        constexpr explicit TPreBridgeBindingSetId(value_type input) noexcept : value(input) {}

        [[nodiscard]] static constexpr TPreBridgeBindingSetId invalid() noexcept { return TPreBridgeBindingSetId{k_invalid_value}; }
        [[nodiscard]] static constexpr TPreBridgeBindingSetId from_raw(value_type input) noexcept { return TPreBridgeBindingSetId{input}; }
        [[nodiscard]] constexpr value_type raw() const noexcept { return value; }
        [[nodiscard]] constexpr bool is_valid() const noexcept { return value != k_invalid_value; }

        [[nodiscard]] friend constexpr bool operator==(TPreBridgeBindingSetId lhs, TPreBridgeBindingSetId rhs) noexcept { return lhs.value == rhs.value; }
        [[nodiscard]] friend constexpr bool operator!=(TPreBridgeBindingSetId lhs, TPreBridgeBindingSetId rhs) noexcept { return !(lhs == rhs); }
    };
    } // namespace pre_bridge
} // namespace circulation_mechanism
} // namespace assembler

    namespace std {
    template<> struct hash<assembler::circulation_mechanism::pre_bridge::TPreBridgeBindingSetId> {
        std::size_t operator()(const assembler::circulation_mechanism::pre_bridge::TPreBridgeBindingSetId& input) const noexcept {
            return std::hash<assembler::circulation_mechanism::pre_bridge::TPreBridgeBindingSetId::value_type>{}(input.raw());
        }
    };
    }
