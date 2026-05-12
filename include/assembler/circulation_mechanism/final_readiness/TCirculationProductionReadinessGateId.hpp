#pragma once
    #include <cstdint>
    #include <functional>

    /*
        TCirculationProductionReadinessGateId.hpp

        Delivery:
            CME-PROD-HARDEN-W08 — Final Production Readiness Gate

        Current responsibility:
            Identifies one final production readiness gate evaluation.

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

    struct TCirculationProductionReadinessGateId final {
        using value_type = std::uint64_t;
        static constexpr value_type k_invalid_value = 0U;
        value_type value{k_invalid_value};

        constexpr TCirculationProductionReadinessGateId() noexcept = default;
        constexpr explicit TCirculationProductionReadinessGateId(value_type input) noexcept : value(input) {}

        [[nodiscard]] static constexpr TCirculationProductionReadinessGateId invalid() noexcept { return TCirculationProductionReadinessGateId{k_invalid_value}; }
        [[nodiscard]] static constexpr TCirculationProductionReadinessGateId from_raw(value_type input) noexcept { return TCirculationProductionReadinessGateId{input}; }
        [[nodiscard]] constexpr value_type raw() const noexcept { return value; }
        [[nodiscard]] constexpr bool is_valid() const noexcept { return value != k_invalid_value; }

        [[nodiscard]] friend constexpr bool operator==(TCirculationProductionReadinessGateId lhs, TCirculationProductionReadinessGateId rhs) noexcept { return lhs.value == rhs.value; }
        [[nodiscard]] friend constexpr bool operator!=(TCirculationProductionReadinessGateId lhs, TCirculationProductionReadinessGateId rhs) noexcept { return !(lhs == rhs); }
    };
    } // namespace final_readiness
} // namespace circulation_mechanism
} // namespace assembler


    namespace std {
    template<> struct hash<assembler::circulation_mechanism::final_readiness::TCirculationProductionReadinessGateId> {
        std::size_t operator()(const assembler::circulation_mechanism::final_readiness::TCirculationProductionReadinessGateId& input) const noexcept {
            return std::hash<assembler::circulation_mechanism::final_readiness::TCirculationProductionReadinessGateId::value_type>{}(input.raw());
        }
    };
    }
