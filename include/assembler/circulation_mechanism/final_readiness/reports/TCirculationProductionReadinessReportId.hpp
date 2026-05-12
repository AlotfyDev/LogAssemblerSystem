#pragma once
    #include <cstdint>
    #include <functional>

    /*
        TCirculationProductionReadinessReportId.hpp

        Delivery:
            CME-PROD-HARDEN-W08 — Final Production Readiness Gate

        Current responsibility:
            Identifies one final production readiness report.

        Production capabilities:
            - typed identity atom
            - invalid/from_raw/raw/is_valid helpers
            - equality / inequality
            - std::hash specialization

        Explicit non-ownership:
            - Does not execute runtime.
            - Does not deploy.
            - Does not run CI.
            - Does not mutate components.
            - Does not certify external bridge/receiver/addon implementations.
    */
    namespace assembler {
namespace circulation_mechanism {
namespace final_readiness {

    struct TCirculationProductionReadinessReportId final {
        using value_type = std::uint64_t;
        static constexpr value_type k_invalid_value = 0U;
        value_type value{k_invalid_value};

        constexpr TCirculationProductionReadinessReportId() noexcept = default;
        constexpr explicit TCirculationProductionReadinessReportId(value_type input) noexcept : value(input) {}

        [[nodiscard]] static constexpr TCirculationProductionReadinessReportId invalid() noexcept { return TCirculationProductionReadinessReportId{k_invalid_value}; }
        [[nodiscard]] static constexpr TCirculationProductionReadinessReportId from_raw(value_type input) noexcept { return TCirculationProductionReadinessReportId{input}; }
        [[nodiscard]] constexpr value_type raw() const noexcept { return value; }
        [[nodiscard]] constexpr bool is_valid() const noexcept { return value != k_invalid_value; }

        [[nodiscard]] friend constexpr bool operator==(TCirculationProductionReadinessReportId lhs, TCirculationProductionReadinessReportId rhs) noexcept { return lhs.value == rhs.value; }
        [[nodiscard]] friend constexpr bool operator!=(TCirculationProductionReadinessReportId lhs, TCirculationProductionReadinessReportId rhs) noexcept { return !(lhs == rhs); }
    };
    } // namespace final_readiness
} // namespace circulation_mechanism
} // namespace assembler


    namespace std {
    template<> struct hash<assembler::circulation_mechanism::final_readiness::TCirculationProductionReadinessReportId> {
        std::size_t operator()(const assembler::circulation_mechanism::final_readiness::TCirculationProductionReadinessReportId& input) const noexcept {
            return std::hash<assembler::circulation_mechanism::final_readiness::TCirculationProductionReadinessReportId::value_type>{}(input.raw());
        }
    };
    }
