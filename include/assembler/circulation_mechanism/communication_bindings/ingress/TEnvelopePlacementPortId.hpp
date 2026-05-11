#pragma once
    #include <cstdint>
    #include <functional>
    /*
        TEnvelopePlacementPortId.hpp

        Delivery:
            CME-COMMBIND-PROD-W01 — Production Boundary And Exposure Contracts

        Current responsibility:
            Identifies an ingress envelope placement port.

        Production capabilities:
            - typed identity atom
            - invalid/from_raw/raw/is_valid helpers
            - equality / inequality
            - std::hash specialization

        Explicit non-ownership:
            - Does not execute adapter runtime.
            - Does not move/copy payload.
            - Does not own bridge protocol.
            - Does not own receiver lifecycle.
    */
    namespace assembler {
namespace circulation_mechanism {

    struct TEnvelopePlacementPortId final {
        using value_type = std::uint64_t;
        static constexpr value_type k_invalid_value = 0U;
        value_type value{k_invalid_value};
        constexpr TEnvelopePlacementPortId() noexcept = default;
        constexpr explicit TEnvelopePlacementPortId(value_type input) noexcept : value(input) {}
        [[nodiscard]] static constexpr TEnvelopePlacementPortId invalid() noexcept { return TEnvelopePlacementPortId{k_invalid_value}; }
        [[nodiscard]] static constexpr TEnvelopePlacementPortId from_raw(value_type input) noexcept { return TEnvelopePlacementPortId{input}; }
        [[nodiscard]] constexpr value_type raw() const noexcept { return value; }
        [[nodiscard]] constexpr bool is_valid() const noexcept { return value != k_invalid_value; }
        [[nodiscard]] friend constexpr bool operator==(TEnvelopePlacementPortId lhs, TEnvelopePlacementPortId rhs) noexcept { return lhs.value == rhs.value; }
        [[nodiscard]] friend constexpr bool operator!=(TEnvelopePlacementPortId lhs, TEnvelopePlacementPortId rhs) noexcept { return !(lhs == rhs); }
    };
    } // namespace circulation_mechanism
} // namespace assembler

    namespace std {
    template<> struct hash<assembler::circulation_mechanism::TEnvelopePlacementPortId> {
        std::size_t operator()(const assembler::circulation_mechanism::TEnvelopePlacementPortId& input) const noexcept {
            return std::hash<assembler::circulation_mechanism::TEnvelopePlacementPortId::value_type>{}(input.raw());
        }
    };
    }
