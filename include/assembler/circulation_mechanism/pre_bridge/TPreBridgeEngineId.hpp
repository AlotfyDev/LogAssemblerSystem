#pragma once
    #include <cstdint>
    #include <functional>

    /*
        TPreBridgeEngineId.hpp

        Delivery:
            CME-PREBRIDGE-PROD-W01 — PreBridge Engine Facade And Injection Surface

        Current responsibility:
            Identifies one injectable PreBridge circulation engine instance.

        Production capabilities:
            - typed identity atom
            - invalid/from_raw/raw/is_valid helpers
            - equality / inequality
            - std::hash specialization

        Explicit non-ownership:
            - Does not own ReadSide runtime.
            - Does not own bridge protocol/session.
            - Does not own final receiver lifecycle.
    */
    namespace assembler {
namespace circulation_mechanism {
namespace pre_bridge {

    struct TPreBridgeEngineId final {
        using value_type = std::uint64_t;
        static constexpr value_type k_invalid_value = 0U;
        value_type value{k_invalid_value};

        constexpr TPreBridgeEngineId() noexcept = default;
        constexpr explicit TPreBridgeEngineId(value_type input) noexcept : value(input) {}

        [[nodiscard]] static constexpr TPreBridgeEngineId invalid() noexcept { return TPreBridgeEngineId{k_invalid_value}; }
        [[nodiscard]] static constexpr TPreBridgeEngineId from_raw(value_type input) noexcept { return TPreBridgeEngineId{input}; }
        [[nodiscard]] constexpr value_type raw() const noexcept { return value; }
        [[nodiscard]] constexpr bool is_valid() const noexcept { return value != k_invalid_value; }

        [[nodiscard]] friend constexpr bool operator==(TPreBridgeEngineId lhs, TPreBridgeEngineId rhs) noexcept { return lhs.value == rhs.value; }
        [[nodiscard]] friend constexpr bool operator!=(TPreBridgeEngineId lhs, TPreBridgeEngineId rhs) noexcept { return !(lhs == rhs); }
    };
    } // namespace pre_bridge
} // namespace circulation_mechanism
} // namespace assembler

    namespace std {
    template<> struct hash<assembler::circulation_mechanism::pre_bridge::TPreBridgeEngineId> {
        std::size_t operator()(const assembler::circulation_mechanism::pre_bridge::TPreBridgeEngineId& input) const noexcept {
            return std::hash<assembler::circulation_mechanism::pre_bridge::TPreBridgeEngineId::value_type>{}(input.raw());
        }
    };
    }
