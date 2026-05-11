#pragma once
    #include <cstdint>
    #include <functional>

    /*
        TPreBridgeEngineReportId.hpp

        Delivery:
            CME-PREBRIDGE-PROD-W01 — PreBridge Engine Facade And Injection Surface

        Current responsibility:
            Identifies one PreBridge engine report.

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

    struct TPreBridgeEngineReportId final {
        using value_type = std::uint64_t;
        static constexpr value_type k_invalid_value = 0U;
        value_type value{k_invalid_value};

        constexpr TPreBridgeEngineReportId() noexcept = default;
        constexpr explicit TPreBridgeEngineReportId(value_type input) noexcept : value(input) {}

        [[nodiscard]] static constexpr TPreBridgeEngineReportId invalid() noexcept { return TPreBridgeEngineReportId{k_invalid_value}; }
        [[nodiscard]] static constexpr TPreBridgeEngineReportId from_raw(value_type input) noexcept { return TPreBridgeEngineReportId{input}; }
        [[nodiscard]] constexpr value_type raw() const noexcept { return value; }
        [[nodiscard]] constexpr bool is_valid() const noexcept { return value != k_invalid_value; }

        [[nodiscard]] friend constexpr bool operator==(TPreBridgeEngineReportId lhs, TPreBridgeEngineReportId rhs) noexcept { return lhs.value == rhs.value; }
        [[nodiscard]] friend constexpr bool operator!=(TPreBridgeEngineReportId lhs, TPreBridgeEngineReportId rhs) noexcept { return !(lhs == rhs); }
    };
    } // namespace pre_bridge
} // namespace circulation_mechanism
} // namespace assembler

    namespace std {
    template<> struct hash<assembler::circulation_mechanism::pre_bridge::TPreBridgeEngineReportId> {
        std::size_t operator()(const assembler::circulation_mechanism::pre_bridge::TPreBridgeEngineReportId& input) const noexcept {
            return std::hash<assembler::circulation_mechanism::pre_bridge::TPreBridgeEngineReportId::value_type>{}(input.raw());
        }
    };
    }
