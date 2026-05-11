#pragma once
    #include <cstdint>
    #include <functional>

    /*
        TCirculationConcurrencyReportId.hpp

        Delivery:
            CME-PROD-HARDEN-W06 — Threading And Concurrency Policy

        Current responsibility:
            Identifies one concurrency policy report.

        Production capabilities:
            - typed identity atom
            - invalid/from_raw/raw/is_valid helpers
            - equality / inequality
            - std::hash specialization

        Explicit non-ownership:
            - Does not create threads.
            - Does not schedule work.
            - Does not lock or unlock runtime objects.
            - Does not execute bridge or receiver runtime.
    */
    namespace assembler {
namespace circulation_mechanism {
namespace concurrency {

    struct TCirculationConcurrencyReportId final {
        using value_type = std::uint64_t;
        static constexpr value_type k_invalid_value = 0U;
        value_type value{k_invalid_value};

        constexpr TCirculationConcurrencyReportId() noexcept = default;
        constexpr explicit TCirculationConcurrencyReportId(value_type input) noexcept : value(input) {}

        [[nodiscard]] static constexpr TCirculationConcurrencyReportId invalid() noexcept { return TCirculationConcurrencyReportId{k_invalid_value}; }
        [[nodiscard]] static constexpr TCirculationConcurrencyReportId from_raw(value_type input) noexcept { return TCirculationConcurrencyReportId{input}; }
        [[nodiscard]] constexpr value_type raw() const noexcept { return value; }
        [[nodiscard]] constexpr bool is_valid() const noexcept { return value != k_invalid_value; }

        [[nodiscard]] friend constexpr bool operator==(TCirculationConcurrencyReportId lhs, TCirculationConcurrencyReportId rhs) noexcept { return lhs.value == rhs.value; }
        [[nodiscard]] friend constexpr bool operator!=(TCirculationConcurrencyReportId lhs, TCirculationConcurrencyReportId rhs) noexcept { return !(lhs == rhs); }
    };
    } // namespace concurrency
} // namespace circulation_mechanism
} // namespace assembler


    namespace std {
    template<> struct hash<assembler::circulation_mechanism::concurrency::TCirculationConcurrencyReportId> {
        std::size_t operator()(const assembler::circulation_mechanism::concurrency::TCirculationConcurrencyReportId& input) const noexcept {
            return std::hash<assembler::circulation_mechanism::concurrency::TCirculationConcurrencyReportId::value_type>{}(input.raw());
        }
    };
    }
