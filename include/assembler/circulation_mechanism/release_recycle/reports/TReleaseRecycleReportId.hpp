#pragma once
    #include <cstdint>
    #include <functional>

    /*
        TReleaseRecycleReportId.hpp

        Delivery:
            CME-RELEASE-RECYCLE-PROD-W01 — Production Lifecycle Contract

        Current responsibility:
            Identifies one release/recycle report.

        Production capabilities:
            - typed identity atom
            - invalid/from_raw/raw/is_valid helpers
            - equality / inequality
            - std::hash specialization

        Explicit non-ownership:
            - Does not execute bridge or receiver lifecycle.
            - Does not mutate registry by itself.
            - Does not prove final delivery.
    */
    namespace assembler {
namespace circulation_mechanism {

    struct TReleaseRecycleReportId final {
        using value_type = std::uint64_t;
        static constexpr value_type k_invalid_value = 0U;
        value_type value{k_invalid_value};
        constexpr TReleaseRecycleReportId() noexcept = default;
        constexpr explicit TReleaseRecycleReportId(value_type input) noexcept : value(input) {}
        [[nodiscard]] static constexpr TReleaseRecycleReportId invalid() noexcept { return TReleaseRecycleReportId{k_invalid_value}; }
        [[nodiscard]] static constexpr TReleaseRecycleReportId from_raw(value_type input) noexcept { return TReleaseRecycleReportId{input}; }
        [[nodiscard]] constexpr value_type raw() const noexcept { return value; }
        [[nodiscard]] constexpr bool is_valid() const noexcept { return value != k_invalid_value; }
        [[nodiscard]] friend constexpr bool operator==(TReleaseRecycleReportId lhs, TReleaseRecycleReportId rhs) noexcept { return lhs.value == rhs.value; }
        [[nodiscard]] friend constexpr bool operator!=(TReleaseRecycleReportId lhs, TReleaseRecycleReportId rhs) noexcept { return !(lhs == rhs); }
    };
    } // namespace circulation_mechanism
} // namespace assembler

    namespace std {
    template<> struct hash<assembler::circulation_mechanism::TReleaseRecycleReportId> {
        std::size_t operator()(const assembler::circulation_mechanism::TReleaseRecycleReportId& input) const noexcept {
            return std::hash<assembler::circulation_mechanism::TReleaseRecycleReportId::value_type>{}(input.raw());
        }
    };
    }
