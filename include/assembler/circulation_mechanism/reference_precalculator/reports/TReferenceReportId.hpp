#pragma once
    #include <cstdint>
    #include <functional>

    /*
        TReferenceReportId.hpp

        Delivery:
            CME-REFPREC-PROD-W01 — Production Locating And Ref Supply Contract

        Current responsibility:
            Identity of a reference-precalculation report.

        Production capabilities:
            - typed identity/locator atom.
            - invalid()/from_raw()/raw()/is_valid().
            - equality/inequality.
            - hash specialization.


        Explicit non-ownership:
            - Does not own containers or slots.
            - Does not execute ingress or dispatch.
            - Does not own bridge/receiver lifecycle.
    */
    namespace assembler {
namespace circulation_mechanism {

    struct TReferenceReportId final {
        using value_type = std::uint64_t;
        static constexpr value_type k_invalid_value = 0U;
        value_type value{k_invalid_value};

        constexpr TReferenceReportId() noexcept = default;
        constexpr explicit TReferenceReportId(value_type input) noexcept : value(input) {}

        [[nodiscard]] static constexpr TReferenceReportId invalid() noexcept { return TReferenceReportId{k_invalid_value}; }
        [[nodiscard]] static constexpr TReferenceReportId from_raw(value_type input) noexcept { return TReferenceReportId{input}; }
        [[nodiscard]] constexpr value_type raw() const noexcept { return value; }
        [[nodiscard]] constexpr bool is_valid() const noexcept { return value != k_invalid_value; }

        [[nodiscard]] friend constexpr bool operator==(TReferenceReportId lhs, TReferenceReportId rhs) noexcept { return lhs.value == rhs.value; }
        [[nodiscard]] friend constexpr bool operator!=(TReferenceReportId lhs, TReferenceReportId rhs) noexcept { return !(lhs == rhs); }
    };
    } // namespace circulation_mechanism
} // namespace assembler

    namespace std {
    template<> struct hash<assembler::circulation_mechanism::TReferenceReportId> {
        std::size_t operator()(const assembler::circulation_mechanism::TReferenceReportId& input) const noexcept {
            return std::hash<assembler::circulation_mechanism::TReferenceReportId::value_type>{}(input.raw());
        }
    };
    }
