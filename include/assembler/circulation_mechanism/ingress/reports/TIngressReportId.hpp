#pragma once
    #include <cstdint>
    #include <functional>

    /*
        TIngressReportId.hpp

        Delivery:
            CME-INGRESS-PROD-W01 — Production Placement Execution Contract

        Current responsibility:
            Identifies one ingress report.

        Explicit non-ownership:
            - Does not own payload semantics.
            - Does not calculate references.
            - Does not own bridge/read-side lifecycle.
    */
    namespace assembler {
namespace circulation_mechanism {

    struct TIngressReportId final {
        using value_type = std::uint64_t;
        static constexpr value_type k_invalid_value = 0U;
        value_type value{k_invalid_value};
        constexpr TIngressReportId() noexcept = default;
        constexpr explicit TIngressReportId(value_type v) noexcept : value(v) {}
        [[nodiscard]] static constexpr TIngressReportId invalid() noexcept { return TIngressReportId{k_invalid_value}; }
        [[nodiscard]] static constexpr TIngressReportId from_raw(value_type v) noexcept { return TIngressReportId{v}; }
        [[nodiscard]] constexpr value_type raw() const noexcept { return value; }
        [[nodiscard]] constexpr bool is_valid() const noexcept { return value != k_invalid_value; }

        [[nodiscard]] friend constexpr bool operator==(TIngressReportId a, TIngressReportId b) noexcept { return a.value == b.value; }
        [[nodiscard]] friend constexpr bool operator!=(TIngressReportId a, TIngressReportId b) noexcept { return !(a==b); }
    };
    } // namespace circulation_mechanism
} // namespace assembler

    namespace std {
    template<> struct hash<assembler::circulation_mechanism::TIngressReportId> {
        std::size_t operator()(const assembler::circulation_mechanism::TIngressReportId& x) const noexcept {
            return std::hash<assembler::circulation_mechanism::TIngressReportId::value_type>{}(x.raw());
        }
    };
    }
