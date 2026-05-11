#pragma once
    #include <cstdint>
    #include <functional>

    /*
        TReadSideAdapterReportId.hpp

        Delivery:
            CME-READSIDE-PROD-W04 — Addon And Receiver Adapter Contracts

        Current responsibility:
            Identifies one read-side adapter report.

        Production capabilities:
            - typed identity atom
            - invalid/from_raw/raw/is_valid helpers
            - equality / inequality
            - std::hash specialization

        Explicit non-ownership:
            - Does not implement the adapter runtime.
            - Does not persist payload.
            - Does not export telemetry.
            - Does not call external systems by itself.
            - Does not mutate PreBridge runtime.
    */
    namespace assembler {
namespace circulation_mechanism {
namespace read_side {

    struct TReadSideAdapterReportId final {
        using value_type = std::uint64_t;
        static constexpr value_type k_invalid_value = 0U;
        value_type value{k_invalid_value};

        constexpr TReadSideAdapterReportId() noexcept = default;
        constexpr explicit TReadSideAdapterReportId(value_type input) noexcept : value(input) {}

        [[nodiscard]] static constexpr TReadSideAdapterReportId invalid() noexcept { return TReadSideAdapterReportId{k_invalid_value}; }
        [[nodiscard]] static constexpr TReadSideAdapterReportId from_raw(value_type input) noexcept { return TReadSideAdapterReportId{input}; }
        [[nodiscard]] constexpr value_type raw() const noexcept { return value; }
        [[nodiscard]] constexpr bool is_valid() const noexcept { return value != k_invalid_value; }

        [[nodiscard]] friend constexpr bool operator==(TReadSideAdapterReportId lhs, TReadSideAdapterReportId rhs) noexcept { return lhs.value == rhs.value; }
        [[nodiscard]] friend constexpr bool operator!=(TReadSideAdapterReportId lhs, TReadSideAdapterReportId rhs) noexcept { return !(lhs == rhs); }
    };
    } // namespace read_side
} // namespace circulation_mechanism
} // namespace assembler

    namespace std {
    template<> struct hash<assembler::circulation_mechanism::read_side::TReadSideAdapterReportId> {
        std::size_t operator()(const assembler::circulation_mechanism::read_side::TReadSideAdapterReportId& input) const noexcept {
            return std::hash<assembler::circulation_mechanism::read_side::TReadSideAdapterReportId::value_type>{}(input.raw());
        }
    };
    }
