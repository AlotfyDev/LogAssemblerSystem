#pragma once
    #include <cstdint>
    #include <functional>

    /*
        TReadSideEngineReportId.hpp

        Delivery:
            CME-READSIDE-PROD-W01 — ReadSide Engine Facade And Injection Surface

        Current responsibility:
            Identifies one ReadSide engine report.

        Production capabilities:
            - typed identity atom
            - invalid/from_raw/raw/is_valid helpers
            - equality / inequality
            - std::hash specialization

        Explicit non-ownership:
            - Does not own PreBridge runtime.
            - Does not own Bridge Orchestrator internals.
            - Does not implement receiver/addon behavior.
            - Does not perform persistence or telemetry export.
    */
    namespace assembler {
namespace circulation_mechanism {
namespace read_side {

    struct TReadSideEngineReportId final {
        using value_type = std::uint64_t;
        static constexpr value_type k_invalid_value = 0U;
        value_type value{k_invalid_value};

        constexpr TReadSideEngineReportId() noexcept = default;
        constexpr explicit TReadSideEngineReportId(value_type input) noexcept : value(input) {}

        [[nodiscard]] static constexpr TReadSideEngineReportId invalid() noexcept { return TReadSideEngineReportId{k_invalid_value}; }
        [[nodiscard]] static constexpr TReadSideEngineReportId from_raw(value_type input) noexcept { return TReadSideEngineReportId{input}; }
        [[nodiscard]] constexpr value_type raw() const noexcept { return value; }
        [[nodiscard]] constexpr bool is_valid() const noexcept { return value != k_invalid_value; }

        [[nodiscard]] friend constexpr bool operator==(TReadSideEngineReportId lhs, TReadSideEngineReportId rhs) noexcept { return lhs.value == rhs.value; }
        [[nodiscard]] friend constexpr bool operator!=(TReadSideEngineReportId lhs, TReadSideEngineReportId rhs) noexcept { return !(lhs == rhs); }
    };
    } // namespace read_side
} // namespace circulation_mechanism
} // namespace assembler


    namespace std {
    template<> struct hash<assembler::circulation_mechanism::read_side::TReadSideEngineReportId> {
        std::size_t operator()(const assembler::circulation_mechanism::read_side::TReadSideEngineReportId& input) const noexcept {
            return std::hash<assembler::circulation_mechanism::read_side::TReadSideEngineReportId::value_type>{}(input.raw());
        }
    };
    }
