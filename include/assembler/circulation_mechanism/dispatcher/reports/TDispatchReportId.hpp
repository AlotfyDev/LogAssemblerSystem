#pragma once
    #include <cstdint>
    #include <functional>

    /*
        TDispatchReportId.hpp

        Delivery:
            CME-DISPATCHER-PROD-W01 — Production Exposure Execution Contract

        Current responsibility:
            Identifies a dispatch report.

        Explicit non-ownership:
            - Does not own bridge protocol.
            - Does not own receiver lifecycle.
            - Does not execute persistence.
            - Does not parse payload content.
    */
    namespace assembler {
namespace circulation_mechanism {

    struct TDispatchReportId final {
        using value_type = std::uint64_t;
        static constexpr value_type k_invalid_value = 0U;
        value_type value{k_invalid_value};
        constexpr TDispatchReportId() noexcept = default;
        constexpr explicit TDispatchReportId(value_type v) noexcept : value(v) {}
        [[nodiscard]] static constexpr TDispatchReportId invalid() noexcept { return TDispatchReportId{k_invalid_value}; }
        [[nodiscard]] static constexpr TDispatchReportId from_raw(value_type v) noexcept { return TDispatchReportId{v}; }
        [[nodiscard]] constexpr value_type raw() const noexcept { return value; }
        [[nodiscard]] constexpr bool is_valid() const noexcept { return value != k_invalid_value; }

        [[nodiscard]] friend constexpr bool operator==(TDispatchReportId a, TDispatchReportId b) noexcept { return a.value == b.value; }
        [[nodiscard]] friend constexpr bool operator!=(TDispatchReportId a, TDispatchReportId b) noexcept { return !(a==b); }
    };
    } // namespace circulation_mechanism
} // namespace assembler

    namespace std {
    template<> struct hash<assembler::circulation_mechanism::TDispatchReportId> {
        std::size_t operator()(const assembler::circulation_mechanism::TDispatchReportId& x) const noexcept {
            return std::hash<assembler::circulation_mechanism::TDispatchReportId::value_type>{}(x.raw());
        }
    };
    }
