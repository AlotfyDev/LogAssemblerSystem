#pragma once
    #include <cstdint>
    #include <functional>

    /*
        TEvictionReportId.hpp

        Delivery:
            CME-EVICTION-PROD-W01 — Production SafePoint Candidate Contract

        Current responsibility:
            Identifies one eviction report.

        Production capabilities:
            - typed identity atom
            - invalid/from_raw/raw/is_valid helpers
            - equality / inequality
            - std::hash specialization

        Explicit non-ownership:
            - Does not mutate registry.
            - Does not execute eviction by itself.
            - Does not delete persistence.
            - Does not own bridge/read-side retry.
    */
    namespace assembler {
namespace circulation_mechanism {

    struct TEvictionReportId final {
        using value_type = std::uint64_t;
        static constexpr value_type k_invalid_value = 0U;
        value_type value{k_invalid_value};
        constexpr TEvictionReportId() noexcept = default;
        constexpr explicit TEvictionReportId(value_type input) noexcept : value(input) {}
        [[nodiscard]] static constexpr TEvictionReportId invalid() noexcept { return TEvictionReportId{k_invalid_value}; }
        [[nodiscard]] static constexpr TEvictionReportId from_raw(value_type input) noexcept { return TEvictionReportId{input}; }
        [[nodiscard]] constexpr value_type raw() const noexcept { return value; }
        [[nodiscard]] constexpr bool is_valid() const noexcept { return value != k_invalid_value; }
        [[nodiscard]] friend constexpr bool operator==(TEvictionReportId lhs, TEvictionReportId rhs) noexcept { return lhs.value == rhs.value; }
        [[nodiscard]] friend constexpr bool operator!=(TEvictionReportId lhs, TEvictionReportId rhs) noexcept { return !(lhs == rhs); }
    };
    } // namespace circulation_mechanism
} // namespace assembler

    namespace std {
    template<> struct hash<assembler::circulation_mechanism::TEvictionReportId> {
        std::size_t operator()(const assembler::circulation_mechanism::TEvictionReportId& input) const noexcept {
            return std::hash<assembler::circulation_mechanism::TEvictionReportId::value_type>{}(input.raw());
        }
    };
    }
