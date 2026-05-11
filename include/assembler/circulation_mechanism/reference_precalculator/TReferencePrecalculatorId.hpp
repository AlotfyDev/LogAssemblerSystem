#pragma once
    #include <cstdint>
    #include <functional>

    /*
        TReferencePrecalculatorId.hpp

        Delivery:
            CME-REFPREC-PROD-W01 — Production Locating And Ref Supply Contract

        Current responsibility:
            Identity of a ReferencePrecalculator instance.

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

    struct TReferencePrecalculatorId final {
        using value_type = std::uint64_t;
        static constexpr value_type k_invalid_value = 0U;
        value_type value{k_invalid_value};

        constexpr TReferencePrecalculatorId() noexcept = default;
        constexpr explicit TReferencePrecalculatorId(value_type input) noexcept : value(input) {}

        [[nodiscard]] static constexpr TReferencePrecalculatorId invalid() noexcept { return TReferencePrecalculatorId{k_invalid_value}; }
        [[nodiscard]] static constexpr TReferencePrecalculatorId from_raw(value_type input) noexcept { return TReferencePrecalculatorId{input}; }
        [[nodiscard]] constexpr value_type raw() const noexcept { return value; }
        [[nodiscard]] constexpr bool is_valid() const noexcept { return value != k_invalid_value; }

        [[nodiscard]] friend constexpr bool operator==(TReferencePrecalculatorId lhs, TReferencePrecalculatorId rhs) noexcept { return lhs.value == rhs.value; }
        [[nodiscard]] friend constexpr bool operator!=(TReferencePrecalculatorId lhs, TReferencePrecalculatorId rhs) noexcept { return !(lhs == rhs); }
    };
    } // namespace circulation_mechanism
} // namespace assembler

    namespace std {
    template<> struct hash<assembler::circulation_mechanism::TReferencePrecalculatorId> {
        std::size_t operator()(const assembler::circulation_mechanism::TReferencePrecalculatorId& input) const noexcept {
            return std::hash<assembler::circulation_mechanism::TReferencePrecalculatorId::value_type>{}(input.raw());
        }
    };
    }
